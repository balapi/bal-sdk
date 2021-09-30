/*
<:copyright-BRCM:2016-2020:Apache:standard

 Copyright (c) 2016-2020 Broadcom. All Rights Reserved

 The term “Broadcom” refers to Broadcom Inc. and/or its subsidiaries

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

:>
 */

#include "bcmos_system.h"

/* task control blocks */
STAILQ_HEAD(task_list, bcmos_task) task_list = STAILQ_HEAD_INITIALIZER(task_list);

/* module control blocks */
bcmos_module *bcmos_modules[BCMOS_MODULE_ID__NUM_OF];

/* event control blocks */
bcmos_event *bcmos_events[BCMOS_EVENT_ID__NUM_OF];

/* Global trace level */
bcmos_trace_level bcmos_sys_trace_level = BCMOS_TRACE_LEVEL_ERROR;

/* Global OS mutex */
bcmos_mutex bcmos_res_lock;

/* Total memory occupied by block pools */
uint32_t bcmos_total_blk_pool_size;

/* Total memory occupied by message pools */
uint32_t bcmos_total_msg_pool_size;

f_bcmolt_sw_error_handler sw_error_handler;

/* Block pools */
static STAILQ_HEAD(blk_pool_list, bcmos_blk_pool) blk_pool_list = STAILQ_HEAD_INITIALIZER(blk_pool_list);

/* Message pools */
static STAILQ_HEAD(msg_pool_list, bcmos_blk_pool) msg_pool_list = STAILQ_HEAD_INITIALIZER(msg_pool_list);

/* Message queues */
static STAILQ_HEAD(msg_queue_list, bcmos_msg_queue) msg_queue_list = STAILQ_HEAD_INITIALIZER(msg_queue_list);

/* Message queue groups */
static STAILQ_HEAD(msg_qgroup_list, bcmos_msg_qgroup) msg_qgroup_list = STAILQ_HEAD_INITIALIZER(msg_qgroup_list);

/* Whether or not we should prevent any further dynamic memory allocation. */
static bcmos_bool bcmos_dynamic_memory_allocation_blocked;
static uint32_t bcmos_dynamic_memory_allocation_block_size_threshold;

/* Protection access to bcmos_dynamic_memory_allocation_block_suspended flag
   from more than one task */
static bcmos_mutex dynamic_mem_alloc_suspend_mutex;
static uint32_t dynamic_alloc_suspend_usage_count;

#ifdef BCMOS_HEAP_DEBUG

static DLIST_HEAD(bcmos_heap_memblk_hdr_list, bcmos_heap_memblk_hdr) bcmos_heap_memblk_hdr_list =
    DLIST_HEAD_INITIALIZER(bcmos_heap_memblk_hdr_list);

/* Lock used to protect memory blocks list */
static bcmos_mutex bcmos_heap_debug_lk;

static uint32_t bcmos_heap_debug_total_size;

static uint32_t bcmos_heap_debug_num_blocks;

/* Temporarily disable out of memory info print. This is typically used when it is expected that memory allocation may fail. */
bcmos_bool bcmos_heap_debug_out_of_memory_print_disabled;

/* Mark that initialization is done, in case we want to exclude initialization time allocations. */
bcmos_bool bcmos_heap_debug_init_done;

/* How many times to print out of memory info ? This will prevent re-printing of this info if there are multiple places that fail to allocate memory, thus reducing the amount of info we
 * have go through when debugging. */
static uint8_t bcmos_heap_debug_out_of_memory_print_count = 1;

static void bcmos_alloc_debug_print_cb(void *context, const char *fmt, ...)__attribute__((format(__printf__, 2, 3)));
#endif

#ifdef BCMOS_HEALTH_CHECK_ENABLED
/* protecton of global health check data accessed by multiple modules */
static bcmos_mutex health_check_data_mutex;
/* Healthcheck prototypes */
/* Initialize the health check for a particular module. */
static bcmos_errno bcmos_module_health_check_init(const bcmos_module* module);
/* Clean up the health check for a particular module. */
static bcmos_errno bcmos_module_health_check_destroy(bcmos_module_id module_id);
#endif

/* Lock used to protect msg registration / deregistration */
static bcmos_fastlock bcmos_msg_register_lock;

/* Shutdown mode: when this is set, we expect message handler deregistration to happen while messages are still being
 * sent/received. We should handle this gracefully. */
static bcmos_bool bcmos_msg_shutdown_mode = BCMOS_FALSE;

/* Timer management block */
typedef struct bcmos_timer_pool
{
    bcmos_fastlock lock;                        /* Pool protection lock */
    bcmos_sys_timer sys_timer;                  /* System timer handle */
    bcmos_task *sys_timer_task;                 /* System timer task, if any */
    bcmos_bool sys_timer_task_set;
    uint32_t num_active_timers;                 /* Number of active timers in the pool */
#ifdef BCMOS_TIMER_RB_TREE
    RB_HEAD(bcmos_timers, bcmos_timer) pool;    /* Timer pool. RB tree */
#else
    TAILQ_HEAD(bcmos_timers, bcmos_timer) pool; /* Timer pool: TAILQ */
#endif
} bcmos_timer_pool;

static int32_t _bcmos_timer_compare(bcmos_timer *t1, bcmos_timer *t2);

#ifdef BCMOS_TIMER_DEBUG
/* timer control blocks */
static STAILQ_HEAD(timer_list, bcmos_timer) timer_list = STAILQ_HEAD_INITIALIZER(timer_list);
#endif

/*
 * Macros for RB-TREE and TAILQ-based timer tool implementations
 */

#ifdef BCMOS_TIMER_RB_TREE

/* ARM compiler doesn't like unused inline functions. Disable the warning */
#if defined(ARM_V7)
#pragma diag_suppress 177
#elif defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-function"
#endif

/* Generate RB tree functions */
RB_GENERATE_INLINE(bcmos_timers, bcmos_timer, pool_entry, _bcmos_timer_compare)

#define TMR_POOL_INIT(tmr_pool)                 RB_INIT(&(tmr_pool)->pool)
#define TMR_POOL_INSERT(tmr_pool, tmr)          RB_INSERT(bcmos_timers, &(tmr_pool)->pool, tmr)
#define TMR_POOL_REMOVE(tmr_pool, tmr)          RB_REMOVE(bcmos_timers, &(tmr_pool)->pool, tmr)
#define TMR_POOL_FIRST(tmr_pool)                RB_MIN(bcmos_timers, &(tmr_pool)->pool)

#else

#define TMR_POOL_INIT(tmr_pool)                 TAILQ_INIT(&(tmr_pool)->pool)

#define TMR_POOL_INSERT(tmr_pool, tmr)                          \
    do \
    { \
        bcmos_timer *_last = TAILQ_LAST(&(tmr_pool)->pool, bcmos_timers);    \
        if (_last)                                              \
        {                                                       \
            if (_bcmos_timer_compare(tmr, _last) >= 0)          \
            {                                                   \
                TAILQ_INSERT_TAIL(&(tmr_pool)->pool, tmr, pool_entry); \
            }                                                   \
            else                                                \
            {                                                   \
                bcmos_timer *_t;                                \
                uint32_t iter = 0;                              \
                TAILQ_FOREACH(_t, &(tmr_pool)->pool, pool_entry) \
                {                                               \
                    BUG_ON(iter >= (tmr_pool)->num_active_timers);\
                    ++iter;                                     \
                    if (_bcmos_timer_compare(tmr, _t) <= 0)     \
                    {                                           \
                        TAILQ_INSERT_BEFORE(_t, tmr, pool_entry); \
                        break;                                  \
                    }                                           \
                }                                               \
            }                                                   \
        }                                                       \
        else                                                    \
        {                                                       \
            TAILQ_INSERT_HEAD(&(tmr_pool)->pool, tmr, pool_entry); \
        }                                                       \
        ++(tmr_pool)->num_active_timers;                        \
    } while (0)

#define TMR_POOL_REMOVE(tmr_pool, tmr)                          \
    do \
    { \
        BUG_ON(!(tmr_pool)->num_active_timers);                 \
        TAILQ_REMOVE(&(tmr_pool)->pool, tmr, pool_entry); \
        TAILQ_NEXT(tmr, pool_entry) = NULL; \
        --(tmr_pool)->num_active_timers;                        \
    } while (0)

#define TMR_POOL_FIRST(tmr_pool)                TAILQ_FIRST(&(tmr_pool)->pool)

#endif

#define BCMOS_TIMER_IS_RUNNING(tmr)             ((tmr->flags & BCMOS_TIMER_FLAG_RUNNING) != 0)
#define BCMOS_TIMER_IS_EXPIRED(tmr)             ((tmr->flags & BCMOS_TIMER_FLAG_EXPIRED) != 0)
#define BCMOS_TIMER_IS_VALID(tmr)               ((tmr->flags & BCMOS_TIMER_FLAG_VALID) != 0)
#define BCMOS_TIMER_IS_ACTIVE(tmr)              ((tmr->flags & BCMOS_TIMER_FLAG_ACTIVE) != 0)

static bcmos_bool bcmos_initialized;
static bcmos_timer_pool tmr_pool;
static void _sys_timer_handler(void *data);

/*
 * Print variables
 */

static bcmos_print_redirect_mode print_redirect_mode;
static bcmos_print_redirect_cb print_redirect_cb;
static void *print_redirect_cb_data;
static bcmos_mutex bcmos_print_lock;
#ifdef BCMOS_BUF_POOL_SIZE
static bcmos_blk_pool sys_buf_pool;
#ifdef BCMOS_BIG_BUF_POOL_SIZE
static bcmos_blk_pool sys_big_buf_pool;
#endif
static bcmos_errno bcmos_buf_pool_create(uint32_t pool_size, uint32_t blk_size, bcmos_blk_pool *blk_pool);
#endif

/** Initialize system library
 * \ingroup system
 * Must be called before any other system function
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_init(void)
{
    bcmos_errno rc;

    if (bcmos_initialized)
        return BCM_ERR_OK;
    rc = bcmos_sys_init();
    bcmos_mutex_create(&bcmos_res_lock, 0, "res_lock");
    bcmos_mutex_create(&bcmos_print_lock, 0, "print_lock");

#ifdef BCMOS_HEAP_DEBUG
    bcmos_mutex_create(&bcmos_heap_debug_lk, 0, "heap_debug_lock");
#endif

#ifdef BCMOS_HEALTH_CHECK_ENABLED
    bcmos_mutex_create(&health_check_data_mutex, 0, "health_check_mutex");
#endif

    bcmos_mutex_create(&dynamic_mem_alloc_suspend_mutex, 0, "dyn_alloc_susp_mutex");
    /* coverity[missing_lock] - this happens during initialization so doesn't need to be locked */
    dynamic_alloc_suspend_usage_count = 0;

    TMR_POOL_INIT(&tmr_pool);
    bcmos_fastlock_init(&tmr_pool.lock, 0);
    bcmos_fastlock_init(&bcmos_msg_register_lock, 0);
    rc = rc ? rc : bcmos_sys_timer_create(&tmr_pool.sys_timer, _sys_timer_handler, &tmr_pool);

    /* Create default buffer pool if so requested by compilation options */
#ifdef BCMOS_BUF_POOL_SIZE
#ifndef BCMOS_BUF_POOL_BUF_SIZE
#error BCMOS_BUF_POOL_BUF_SIZE must be defined
#endif
    rc = rc ? rc : bcmos_buf_pool_create(BCMOS_BUF_POOL_SIZE, BCMOS_BUF_POOL_BUF_SIZE, &sys_buf_pool);
#endif

    /* Create BIG_BUF pool */
#ifdef BCMOS_BIG_BUF_POOL_SIZE
#ifndef BCMOS_BIG_BUF_POOL_BUF_SIZE
#error BCMOS_BUF_POOL_BUF_SIZE must be defined
#endif
    rc = rc ? rc : bcmos_buf_pool_create(BCMOS_BIG_BUF_POOL_SIZE, BCMOS_BIG_BUF_POOL_BUF_SIZE, &sys_big_buf_pool);
#endif

    if (!rc)
    {
        bcmos_initialized = BCMOS_TRUE;
    }

    return rc;
}

/** Cleanup system library
 * \ingroup system
 */
void bcmos_exit(void)
{
    if (!bcmos_initialized)
        return;

#ifdef BCMOS_BUF_POOL_SIZE
    bcmos_blk_pool_reset(&sys_buf_pool);
    bcmos_blk_pool_destroy(&sys_buf_pool);
#endif

#ifdef BCMOS_BIG_BUF_POOL_SIZE
    bcmos_blk_pool_reset(&sys_big_buf_pool);
    bcmos_blk_pool_destroy(&sys_big_buf_pool);
#endif

    bcmos_sys_timer_destroy(&tmr_pool.sys_timer);
    bcmos_mutex_destroy(&bcmos_print_lock);
    bcmos_mutex_destroy(&bcmos_res_lock);

#ifdef BCMOS_HEAP_DEBUG
    bcmos_mutex_destroy(&bcmos_heap_debug_lk);
#endif

#ifdef BCMOS_HEALTH_CHECK_ENABLED
    bcmos_mutex_destroy(&health_check_data_mutex);
#endif

    bcmos_sys_exit();
    bcmos_initialized = BCMOS_FALSE;
}

/*
 * Heap debug service
 */
#ifdef BCMOS_HEAP_DEBUG

void bcmos_heap_debug_lock(void)
{
    bcmos_mutex_lock(&bcmos_heap_debug_lk);
}

void bcmos_heap_debug_unlock(void)
{
    bcmos_mutex_unlock(&bcmos_heap_debug_lk);
}

static inline void bcmos_heap_debug_memblk_set_hdr(bcmos_heap_memblk_hdr *hdr, uint32_t size, const char *fname, uint32_t line)
{
    strncpy(hdr->fname, fname, sizeof(hdr->fname) - 1);
    hdr->fname[sizeof(hdr->fname) - 1] = 0;
    hdr->timestamp = bcmos_timestamp();
    hdr->line = line;
    hdr->size = size;
    hdr->is_init_time = !bcmos_heap_debug_init_done;
    hdr->magic = BCMOS_HEAP_DEBUG_ALLOC_MAGIC;
}

/* Add newly allocated memory block to heap debug list. Returns "user" pointer */
void *bcmos_heap_debug_memblk_add(void *hdr_ptr, uint32_t size, const char *fname, uint32_t line)
{
    bcmos_heap_memblk_hdr *hdr = (bcmos_heap_memblk_hdr *)hdr_ptr;
    void *user_ptr;
    uint32_t magic = BCMOS_HEAP_DEBUG_ALLOC_MAGIC;

    if (hdr_ptr == NULL)
        return NULL;
    bcmos_heap_debug_memblk_set_hdr(hdr, size, fname, line);
    user_ptr = (void *)(hdr + 1);

    /* Initialize magic tail. */
    memcpy((void *)((long)user_ptr + size), &magic, sizeof(uint32_t));

    bcmos_heap_debug_lock();
    DLIST_INSERT_HEAD(&bcmos_heap_memblk_hdr_list, hdr, list);
    bcmos_heap_debug_total_size += size;
    ++bcmos_heap_debug_num_blocks;
    bcmos_heap_debug_unlock();

    return user_ptr;
}

/* Check memory block. Returns BCMOS_TRUE if the block is OK */
static bcmos_bool _bcmos_heap_debug_memblk_check(void *user_ptr, const char *fname,
    uint32_t line, bcmos_bool suppress_sw_err)
{
    bcmos_heap_memblk_hdr *hdr = bcmos_heap_user_ptr_to_debug_hdr(user_ptr);
    uint32_t magic;

    /* Check for corruption */
    if (hdr->magic != BCMOS_HEAP_DEBUG_ALLOC_MAGIC)
    {
        if (hdr->magic == BCMOS_HEAP_DEBUG_FREE_MAGIC)
        {
            if (suppress_sw_err)
            {
                BCMOS_TRACE(BCMOS_TRACE_LEVEL_ERROR, "The block is free %p (size %u). Freed in %s#%u at %u\n",
                    user_ptr, hdr->size, hdr->fname, hdr->line, hdr->timestamp);
            }
            else
            {
                BCMOS_TRACE_ERR("%s#%u: Double-free block %p (size %u). Already freed in %s#%u at \n",
                    fname, line, user_ptr, hdr->size, hdr->fname, hdr->line, hdr->timestamp);
            }
        }
        else
        {
            if (suppress_sw_err)
            {
                BCMOS_TRACE(BCMOS_TRACE_LEVEL_ERROR,
                    "Memory block %p (size %u) head corruption detected. Allocated in %s#%u at %u\n",
                    user_ptr, hdr->size, hdr->fname, hdr->line, hdr->timestamp);
            }
            else
            {
                BCMOS_TRACE_ERR(
                    "%s#%u: Memory block %p (size %u) head corruption detected. Allocated in %s#%u at %u\n",
                    fname, line, user_ptr, hdr->size, hdr->fname, hdr->line, hdr->timestamp);
            }
        }
        return BCMOS_FALSE;
    }

    /* Check for tail corruption */
    memcpy(&magic, (void *)((long)user_ptr + hdr->size), sizeof(uint32_t));
    if (magic != BCMOS_HEAP_DEBUG_ALLOC_MAGIC)
    {
        if (suppress_sw_err)
        {
            BCMOS_TRACE(BCMOS_TRACE_LEVEL_ERROR,
                "Memory block %p (size %u) tail corruption detected. Allocated in %s#%u\n",
                user_ptr, hdr->size, hdr->fname, hdr->line, hdr->timestamp);
        }
        else
        {
            BCMOS_TRACE_ERR(
                "%s#%u: Memory block %p (size %u) tail corruption detected. Allocated in %s#%u at %u\n",
                fname, line, user_ptr, hdr->size, hdr->fname, hdr->line, hdr->timestamp);
        }
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

/* Check memory block. Returns BCMOS_TRUE if the block is OK */
bcmos_bool bcmos_heap_debug_memblk_check(void *user_ptr)
{
    return _bcmos_heap_debug_memblk_check(user_ptr, "dummy", 0, BCMOS_TRUE);
}

/* Check memory block before freeing it. Returns BCMOS_TRUE if the block is OK */
bcmos_bool bcmos_heap_debug_memblk_check_and_del(void *user_ptr, const char *fname, uint32_t line)
{
    bcmos_heap_memblk_hdr *hdr = bcmos_heap_user_ptr_to_debug_hdr(user_ptr);
    uint32_t magic;
    bcmos_bool valid;

    if (user_ptr == NULL)
    {
        BCMOS_TRACE_ERR("Attempt to free NULL pointer in %s:%u\n", fname, line);
        return BCMOS_FALSE;
    }

    bcmos_heap_debug_lock();

    valid = _bcmos_heap_debug_memblk_check(user_ptr, fname, line, BCMOS_FALSE);
    if (valid)
    {
        DLIST_REMOVE(hdr, list);
        bcmos_heap_debug_total_size -= hdr->size;
        --bcmos_heap_debug_num_blocks;

        bcmos_heap_debug_unlock();

        bcmos_heap_debug_memblk_set_hdr(hdr, hdr->size, fname, line);
        magic = BCMOS_HEAP_DEBUG_FREE_MAGIC;

        /* Change magic tail to BCMOS_HEAP_DEBUG_FREE_MAGIC. */
        memcpy((void *)((long)user_ptr + hdr->size), &magic, sizeof(uint32_t));
    }
    else
    {
        bcmos_heap_debug_unlock();
    }

    return valid;
}

void *bcmos_heap_debug_memblk_get_next(void *prev)
{
    bcmos_heap_memblk_hdr *prev_hdr = bcmos_heap_user_ptr_to_debug_hdr(prev);
    bcmos_heap_memblk_hdr *hdr;

    hdr = prev ? DLIST_NEXT(prev_hdr, list) : DLIST_FIRST(&bcmos_heap_memblk_hdr_list);

    return bcmos_heap_debug_hdr_to_user_ptr(hdr);
}

void bcmos_heap_debug_info_get(uint32_t *num_blocks, uint32_t *total_size)
{
    *num_blocks = bcmos_heap_debug_num_blocks;
    *total_size = bcmos_heap_debug_total_size;
}

static void bcmos_alloc_debug_print_cb(void *context, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    bcmos_vprintf(fmt, ap);
    va_end(ap);
}

static void *bcmos_alloc_debug_add(void *user_ptr, uint32_t size, const char *fname, uint32_t line)
{
    if (!user_ptr)
    {
       if (!bcmos_heap_debug_out_of_memory_print_disabled && bcmos_heap_debug_out_of_memory_print_count--)
       {
           uint32_t num_blocks, total_size;

           bcmos_printf("Out of memory !\n");
           bcmos_heap_debug_info_get(&num_blocks, &total_size);
           bcmos_printf("Heap info: %u allocated blocks, total size %u\n", num_blocks, total_size);
           /* By default, we exclude initialization time allocations. */
           bcmos_heap_debug_print(bcmos_alloc_debug_print_cb, NULL, NULL, BCMOS_TRUE, 0, 0, 0, 0, 0, NULL);
       }
       return user_ptr;
    }

    return bcmos_heap_debug_memblk_add(bcmos_heap_user_ptr_to_debug_hdr(user_ptr), size, fname, line);
}

void *bcmos_alloc_debug(uint32_t size, const char *fname, uint32_t line)
{
    void *user_ptr = _bcmos_alloc(size + BCMOS_HEAP_DEBUG_OVERHEAD);

    return bcmos_alloc_debug_add(user_ptr, size, fname, line);
}

void *bcmos_calloc_debug(uint32_t size, const char *fname, uint32_t line)
{
    void *user_ptr = _bcmos_calloc(size + BCMOS_HEAP_DEBUG_OVERHEAD);

    return bcmos_alloc_debug_add(user_ptr, size, fname, line);
}

void bcmos_free_debug(void *ptr, const char *fname, uint32_t line)
{
    if (bcmos_heap_debug_memblk_check_and_del(ptr, fname, line))
        _bcmos_free(ptr);
}

bcmos_errno bcmos_heap_debug_print(bcmos_msg_print_cb print_cb, bcmos_hexdump_cb hexdump_cb, void *context, bcmos_bool exclude_init_time, uint32_t num_skip, uint32_t num_print,
    uint32_t data_bytes, uint32_t start_ts, uint32_t end_ts, const char *func)
{
    void *ptr = NULL;
    int n = 0;
    int n_printed = 0;

    print_cb(context, "Heap dump\n");
    print_cb(context,
        "Function                                 Line  Ptr              Size     Timestamp\n");

    bcmos_heap_debug_lock();
    while ((ptr = bcmos_heap_debug_memblk_get_next(ptr)) != NULL)
    {
        bcmos_heap_memblk_hdr *hdr = bcmos_heap_user_ptr_to_debug_hdr(ptr);

        ++n;
        if (num_skip && n < num_skip)
            continue;
        if (func && strcmp(func, hdr->fname))
            continue;
        if (end_ts && (int32_t)(hdr->timestamp - end_ts) >= 0)
            continue;
        if (start_ts && (int32_t)(hdr->timestamp - start_ts) < 0)
            break;
        if (exclude_init_time && hdr->is_init_time)
            continue;

        print_cb(context, "%-40s %-5u %-16p %-8u %u\n",
            hdr->fname, hdr->line, ptr, hdr->size, hdr->timestamp);
        bcmos_heap_debug_memblk_check(ptr);
        if (data_bytes)
        {
            uint32_t print_size = (data_bytes < hdr->size) ? data_bytes : hdr->size;
            hexdump_cb(print_cb, context, ptr, 0, print_size, "    ");
        }

        ++n_printed;
        if (num_print && n_printed >= num_print)
            break;
    }
    bcmos_heap_debug_unlock();

    print_cb(context, "%d blocks printed\n", n_printed);

    return BCM_ERR_OK;
}

#endif /* #ifdef BCMOS_HEAP_DEBUG */

/*
 * Common task services
 */

/* Query task info */
bcmos_errno bcmos_task_query(const bcmos_task *task, bcmos_task_parm *parm)
{
    if (task == NULL || task->magic != BCMOS_TASK_MAGIC || parm == NULL)
    {
        return BCM_ERR_PARM;
    }
    *parm = task->parm;
    return BCM_ERR_OK;
}

/** Task iterator
 * \param[in] prev      Previous task. *prev==NULL - get first
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_task_get_next(bcmos_task **prev)
{
    bcmos_task *task;
    if (prev == NULL)
    {
        return BCM_ERR_PARM;
    }
    task = *prev;
    if (task && task->magic != BCMOS_TASK_MAGIC)
    {
        return BCM_ERR_PARM;
    }
    if (task)
    {
        task = STAILQ_NEXT(task, list);
    }
    else
    {
        task = STAILQ_FIRST(&task_list);
    }
    *prev = task;
    if (!task)
    {
        return BCM_ERR_NO_MORE;
    }
    return BCM_ERR_OK;
}

/*
 * Message queue
 */

static void _bcmos_msgq_notify(bcmos_msg_queue *q, const char *txt)
{
    BCMOS_TRACE_INFO("Msg queue %s: %s\n", q->q.parm.name, txt);
}

/* Decrement in-queue statistics */
static inline void _bcmos_msgq_stat_dec(bcmos_msg_queue_nw *q)
{
    bcmos_msg_queue_stat *stat = &q->stat;
    uint32_t old_in = stat->msg_in;

    if (stat->msg_in == 0)
    {
        BCMOS_TRACE_ERR("Attempt to decrement statistics for an empty queue ('%s')\n", q->parm.name);
    }
    else
    {
        --stat->msg_in;
        ++stat->msg_received;
    }

    if (old_in == q->parm.low_wm)
    {
        q->parm.notify((bcmos_msg_queue *)q, "becomes uncongested");
        stat->is_congested = BCMOS_FALSE;
    }
}

/* Increment in-queue statistics */
static inline void _bcmos_msgq_stat_inc(bcmos_msg_queue_nw *q)
{
    bcmos_msg_queue_stat *stat = &q->stat;
    uint32_t old_in = stat->msg_in;

    ++stat->msg_in;
    ++stat->msg_sent;
    if (old_in == q->parm.high_wm)
    {
        q->parm.notify((bcmos_msg_queue *)q, "becomes congested");
        stat->is_congested = BCMOS_TRUE;
    }
    if (stat->is_congested)
        ++stat->msg_almost_full;
}

static void _bcmos_qgroup_notify(bcmos_msg_qgroup *qgroup, const char *txt)
{
    BCMOS_TRACE_INFO("Msg queue %s: %s\n", qgroup->parm.name, txt);
}

/* Decrement in-queue statistics for queue group */
static inline void _bcmos_qgroup_stat_dec(bcmos_msg_qgroup *qgroup)
{
    bcmos_msg_queue_stat *stat = &qgroup->stat;
    uint32_t old_in = stat->msg_in;

    if (stat->msg_in == 0)
    {
        BCMOS_TRACE_ERR("Attempt to decrement statistics for an empty queue ('%s')\n", qgroup->parm.name);
    }
    else
    {
        --stat->msg_in;
        ++stat->msg_received;
    }

    if (old_in == qgroup->parm.low_wm)
    {
        qgroup->parm.notify(qgroup, "becomes uncongested");
        stat->is_congested = BCMOS_FALSE;
    }
}

/* Increment in-queue statistics */
static inline void _bcmos_qgroup_stat_inc(bcmos_msg_qgroup *qgroup)
{
    bcmos_msg_queue_stat *stat = &qgroup->stat;
    uint32_t old_in = stat->msg_in;

    ++stat->msg_in;
    ++stat->msg_sent;
    if (old_in == qgroup->parm.high_wm)
    {
        qgroup->parm.notify(qgroup, "becomes congested");
        stat->is_congested = BCMOS_TRUE;
    }
    if (stat->is_congested)
        ++stat->msg_almost_full;
}

/* Get message from queue.
 * Urgent queue is checked 1st, then regular queue
 * Must be called under lock!
 * Returns msg or NULL if queue is empty
 */
static inline bcmos_msg *_bcmos_msg_get(bcmos_msg_queue_nw *q)
{
    bcmos_msg *msg;

    msg = STAILQ_FIRST(&q->msgl_urg);
    if (msg)
    {
        STAILQ_REMOVE_HEAD(&q->msgl_urg, next);
        _bcmos_msgq_stat_dec(q);
        return msg;
    }

    msg = STAILQ_FIRST(&q->msgl);
    if (msg)
    {
        STAILQ_REMOVE_HEAD(&q->msgl, next);
        _bcmos_msgq_stat_dec(q);
    }

    return msg;
}

/* Put message on queue.
 * Must be called under lock!
 * Returns error in case of queue overflow
 */
static inline bcmos_errno _bcmos_msg_put(bcmos_msg_queue_nw *q, bcmos_msg *msg, bcmos_msg_send_flags flags)
{
    /* Overflow check */
    if (q->stat.msg_in >= q->parm.size)
    {
        if (!(flags & BCMOS_MSG_SEND_NOLIMIT))
        {
            ++q->stat.msg_discarded;
            return BCM_ERR_OVERFLOW;
        }
    }
    /* Put onto the relevant queue */
    if ((flags & BCMOS_MSG_SEND_URGENT))
        STAILQ_INSERT_TAIL(&q->msgl_urg, msg, next);
    else
        STAILQ_INSERT_TAIL(&q->msgl, msg, next);
    _bcmos_msgq_stat_inc(q);

    return BCM_ERR_OK;
}

/* Create message queue without wait support */
static void bcmos_msg_queue_nw_init(bcmos_msg_queue_nw *q, const bcmos_msg_queue_parm *parm)
{
    q->parm = *parm;
    STAILQ_INIT(&q->msgl);
    STAILQ_INIT(&q->msgl_urg);
    bcmos_fastlock_init(&q->lock, parm->flags);
    memset(&q->stat, 0, sizeof(q->stat));
    q->flags = 0;
    if (!q->parm.size)
        q->parm.size = BCMOS_MSG_QUEUE_SIZE_UNLIMITED;
    if (!q->parm.high_wm)
        q->parm.high_wm = BCMOS_MSG_QUEUE_SIZE_UNLIMITED;
    if (!q->parm.low_wm)
        q->parm.low_wm = q->parm.high_wm;
    if (!q->parm.notify)
        q->parm.notify = _bcmos_msgq_notify;
}

/* Destroy message list */
static void bcmos_msg_list_destroy(bcmos_msg_list *l)
{
    bcmos_msg *msg, *tmp;
    STAILQ_FOREACH_SAFE(msg, l, next, tmp)
    {
        STAILQ_REMOVE_HEAD(l, next);
        bcmos_msg_free(msg);
    }
}

#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT

/* Remote queue support - common part of create/destroy */

static bcmos_errno _bcmos_msg_queue_destroy_remote_ep(bcmos_msg_queue *queue)
{
    if (queue->q.parm.close)
        queue->q.parm.close(queue);
    bcmos_mutex_destroy(&queue->send_lock);
    if (queue->send_buf)
        bcmos_free(queue->send_buf);
    if (queue->recv_buf)
        bcmos_free(queue->recv_buf);
    return BCM_ERR_OK;
}

static bcmos_errno _bcmos_msg_queue_create_remote_ep(bcmos_msg_queue *queue)
{
    bcmos_errno rc;

    /* Allocate tx and rx buffers */
    if (!queue->q.parm.max_mtu)
    {
        queue->q.parm.max_mtu = BCMOS_MSG_QUEUE_DEFAULT_MAX_MTU;
    }
    queue->send_buf = bcmos_calloc(queue->q.parm.max_mtu);
    if (!queue->send_buf)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_NOMEM, "Can't allocate send_buf\n");
    }

    queue->recv_buf = bcmos_calloc(queue->q.parm.max_mtu);
    if (!queue->recv_buf)
    {
        bcmos_free(queue->send_buf);
        BCMOS_TRACE_RETURN(BCM_ERR_NOMEM, "Can't allocate recv_buf\n");
    }
    bcmos_mutex_create(&queue->send_lock, 0, queue->q.parm.name);

    switch (queue->q.parm.ep_type)
    {
#ifdef BCMOS_MSG_QUEUE_DOMAIN_SOCKET
    case BCMOS_MSG_QUEUE_EP_DOMAIN_SOCKET:
        rc = bcmos_sys_msg_queue_domain_socket_open(queue);
        break;
#endif
#ifdef BCMOS_MSG_QUEUE_UDP_SOCKET
    case BCMOS_MSG_QUEUE_EP_UDP_SOCKET:
        rc = bcmos_sys_msg_queue_udp_socket_open(queue);
        break;
#endif
#ifdef BCMOS_MSG_QUEUE_USER_DEFINED
    case BCMOS_MSG_QUEUE_EP_USER_DEFINED:
        if (parm.open == NULL || parm.close == NULL || parm.send==NULL || parm.recv == NULL)
        {
            rc = BCM_ERR_PARM;
            break;
        }
        rc = parm.open(queue);
        break;
#endif
    default:
        rc = BCM_ERR_PARM;
        break;
    }

    if (rc)
    {
        _bcmos_msg_queue_destroy_remote_ep(queue);
    }

    return rc;
}

#endif /* #ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT */

/* Create message queue. */
bcmos_errno bcmos_msg_queue_create(bcmos_msg_queue *queue, const bcmos_msg_queue_parm *parm)
{
    bcmos_errno rc;

    if (!queue || !parm)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "queue %p, parm %p\n", queue, parm);
    memset(queue, 0, sizeof(*queue));
    queue->q.parm = *parm;

    if (parm->ep_type == BCMOS_MSG_QUEUE_EP_LOCAL)
    {
        rc = bcmos_sem_create(&queue->m, 0, parm->flags, queue->q.parm.name);
        if (!rc)
            bcmos_msg_queue_nw_init(&queue->q, parm);
    }
    else
#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT
    {
        rc = _bcmos_msg_queue_create_remote_ep(queue);
    }
#else
    {
        rc = BCM_ERR_PARM;
    }
#endif

    if (rc)
        return rc;

    queue->magic = BCMOS_MSG_QUEUE_VALID;
    /* Copy name to make sure that it is not released - in case it was on the stack */
    if (queue->q.parm.name)
    {
        strncpy(queue->name, queue->q.parm.name, sizeof(queue->name) - 1);
        queue->q.parm.name = queue->name;
    }
    bcmos_mutex_lock(&bcmos_res_lock);
    STAILQ_INSERT_TAIL(&msg_queue_list, queue, list);
    bcmos_mutex_unlock(&bcmos_res_lock);
    return BCM_ERR_OK;
}

/* Destroy queue */
bcmos_errno bcmos_msg_queue_destroy(bcmos_msg_queue *queue)
{
    bcmos_errno rc = BCM_ERR_OK;

    if (!queue || queue->magic != BCMOS_MSG_QUEUE_VALID)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "queue handle is invalid\n");
    }
    queue->magic = BCMOS_MSG_QUEUE_DELETED;
    bcmos_mutex_lock(&bcmos_res_lock);
    STAILQ_REMOVE(&msg_queue_list, queue, bcmos_msg_queue, list);
    bcmos_mutex_unlock(&bcmos_res_lock);

    if (queue->q.parm.ep_type == BCMOS_MSG_QUEUE_EP_LOCAL)
    {
        bcmos_sem_destroy(&queue->m);
        /* Release all pending messages */
        bcmos_msg_list_destroy(&queue->q.msgl_urg);
        bcmos_msg_list_destroy(&queue->q.msgl);
    }
#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT
    else
    {
        rc = _bcmos_msg_queue_destroy_remote_ep(queue);
    }
#endif

    return rc;
}

/* Get queue info */
bcmos_errno bcmos_msg_queue_query(const bcmos_msg_queue *queue, bcmos_msg_queue_info *info)
{
    if (!queue || !info)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "queue %p, info %p\n", queue, info);
    info->stat = queue->q.stat;
    info->parm = queue->q.parm;
    return BCM_ERR_OK;
}

/* Message queue iterator */
bcmos_errno bcmos_msg_queue_get_next(const bcmos_msg_queue **prev)
{
    const bcmos_msg_queue *queue;

    if (prev == NULL)
    {
        return BCM_ERR_PARM;
    }
    queue = *prev;
    if (queue && queue->magic != BCMOS_MSG_QUEUE_VALID)
    {
        return BCM_ERR_PARM;
    }
    if (queue)
    {
        queue = STAILQ_NEXT(queue, list);
    }
    else
    {
        queue = STAILQ_FIRST(&msg_queue_list);
    }
    *prev = queue;
    if (!queue)
    {
        return BCM_ERR_NO_MORE;
    }
    return BCM_ERR_OK;
}

#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT

/* Pack / unpack message header.
 * In the future we might adopt bcmolt_buf service into OS abstraction and use it
 * for packing / unpacking.
 */

void bcmos_msg_hdr_pack(const bcmos_msg *msg, uint8_t *buf, uint32_t data_size)
{
    uint16_t val16;
    uint32_t val32;
    val16 = BCMOS_ENDIAN_CPU_TO_BIG_U16(msg->type);
    memcpy(buf, &val16, sizeof(val16));
    buf[2] = (uint8_t)msg->instance;
    buf[3] = (uint8_t)msg->sender;
    val32 = BCMOS_ENDIAN_CPU_TO_BIG_U32(data_size);
    memcpy(&buf[4], &val32, sizeof(val32));
}

void bcmos_msg_hdr_unpack(const uint8_t *buf, bcmos_msg *msg)
{
    uint16_t val16;
    uint32_t val32;
    memcpy(&val16, buf, sizeof(val16));
    val16 = BCMOS_ENDIAN_BIG_TO_CPU_U16(val16);
    msg->type = (bcmos_msg_id)val16;
    msg->instance = (bcmos_msg_instance)buf[2];
    msg->sender = (bcmos_module_id)buf[3];
    memcpy(&val32, &buf[4], sizeof(val32));
    msg->size = BCMOS_ENDIAN_BIG_TO_CPU_U32(val32); /* can be overwritten by unpacker */
    msg->handler = NULL;
    msg->send_flags = 0;
}

/* Send message to remote EP wrapper */
static bcmos_errno _bcmos_msg_send_to_remote_ep(bcmos_msg_queue *queue, bcmos_msg *msg, bcmos_msg_send_flags flags)
{
    uint8_t *buf = NULL;
    uint32_t buf_length = 0;
    bcmos_errno rc;

    bcmos_mutex_lock(&queue->send_lock);
    rc = queue->q.parm.pack(queue, msg, &buf, &buf_length);
    rc = rc ? rc : queue->q.parm.send(queue, msg, buf, buf_length);
    bcmos_mutex_unlock(&queue->send_lock);

    /* Release if sent successfully or if auto-release flag is set */
    if (rc == BCM_ERR_OK || !(flags & BCMOS_MSG_SEND_NO_FREE_ON_ERROR))
    {
        bcmos_msg_free(msg);
    }
    if (buf && queue->q.parm.free_packed)
    {
        queue->q.parm.free_packed(queue, buf);
    }
    if (rc)
    {
        ++queue->q.stat.msg_discarded;
    }
    else
    {
        ++queue->q.stat.msg_sent;
    }

    return rc;
}

/* Receive message from remote EP wrapper */
static bcmos_errno _bcmos_msg_recv_from_remote_ep(bcmos_msg_queue *queue, uint32_t timeout, bcmos_msg **msg)
{
    uint8_t *buf = NULL;
    uint32_t buf_length = 0;
    bcmos_errno rc;

    rc = queue->q.parm.recv(queue, timeout, &buf, &buf_length);
    rc = rc ? rc : queue->q.parm.unpack(queue, buf, buf_length, msg);
    if (buf && queue->q.parm.free_packed)
    {
        queue->q.parm.free_packed(queue, buf);
    }
    if (!rc)
    {
        ++queue->q.stat.msg_received;
    }

    return rc;
}

#endif /* BCMOS_MSG_QUEUE_REMOTE_SUPPORT */

/* Send message to queue */
bcmos_errno bcmos_msg_send(bcmos_msg_queue *queue, bcmos_msg *msg, bcmos_msg_send_flags flags)
{
    long lock_flags;
    bcmos_errno rc;

#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT
    if (queue->q.parm.ep_type != BCMOS_MSG_QUEUE_EP_LOCAL)
    {
        return _bcmos_msg_send_to_remote_ep(queue, msg, flags);
    }
#endif

    lock_flags = bcmos_fastlock_lock(&queue->q.lock);
    rc = _bcmos_msg_put(&queue->q, msg, flags);
    if (rc)
    {
        bcmos_fastlock_unlock(&queue->q.lock, lock_flags);
        if (!(flags & BCMOS_MSG_SEND_NO_FREE_ON_ERROR))
        {
            bcmos_msg_free(msg);
        }
        BCMOS_TRACE_ERR("Overflow: Queue %s\n", queue->q.parm.name);
        return rc;
    }

    /* Success */
    if (queue->is_waiting)
    {
        /* Kick waiting task */
        queue->is_waiting = BCMOS_FALSE;
        bcmos_fastlock_unlock(&queue->q.lock, lock_flags);
        bcmos_sem_post(&queue->m);
    }
    else
    {
        bcmos_fastlock_unlock(&queue->q.lock, lock_flags);
    }

    return BCM_ERR_OK;
}

/* Send message to module (internal) - doesn't post any semaphores so it's safe to call under a fastlock */
static bcmos_errno _bcmos_msg_send_to_module(
    bcmos_module_id module_id,
    bcmos_msg *msg,
    bcmos_msg_send_flags flags,
    bcmos_sem **sem_to_post)
{
    bcmos_module *module = _bcmos_module_get(module_id);
    bcmos_task *task;
    long lock_flags, q_lock_flags;
    uint32_t active_modules;
    bcmos_errno rc;
    *sem_to_post = NULL;

    if (unlikely(!module || !msg->handler))
    {
        if (!module)
        {
            BCMOS_TRACE_ERR("Module %d doesn't exist\n", module_id);
            rc = BCM_ERR_NOENT;
        }
        else
        {
            BCMOS_TRACE_ERR("msg->handler is not set. msg->type=%d\n", msg->type);
            rc = BCM_ERR_PARM;
        }
        if (!(flags & BCMOS_MSG_SEND_NO_FREE_ON_ERROR))
        {
            bcmos_msg_free(msg);
        }
        return rc;
    }

    task = module->my_task;
    lock_flags = bcmos_fastlock_lock(&task->active_lock);

    /* Make sure that the module is not being destroyed */
    if (unlikely(module->deleted))
    {
        BCMOS_TRACE_INFO("Module %d is being destroyed\n", module_id);
        rc = BCM_ERR_NOENT;
        if (!(flags & BCMOS_MSG_SEND_NO_FREE_ON_ERROR))
        {
            bcmos_msg_free(msg);
        }
        bcmos_fastlock_unlock(&task->active_lock, lock_flags);
        return rc;
    }

    q_lock_flags = bcmos_fastlock_lock(&module->msgq.lock);

    rc = _bcmos_msg_put(&module->msgq, msg, flags);
    if (rc)
    {
        bcmos_fastlock_unlock(&module->msgq.lock, q_lock_flags);
        bcmos_fastlock_unlock(&task->active_lock, lock_flags);

        /* Queue overflow */
        if (!(flags & BCMOS_MSG_SEND_NO_FREE_ON_ERROR))
            bcmos_msg_free(msg);

        BCMOS_TRACE_ERR("Overflow: Queue %s\n", module->parm.qparm.name);

        return rc;
    }
    bcmos_fastlock_unlock(&module->msgq.lock, q_lock_flags);

    /* Success. Update active_modules task and kick the task */
    active_modules = task->active_modules;
    task->active_modules |= (1 << module->idx);
    bcmos_fastlock_unlock(&task->active_lock, lock_flags);

    /* Notify caller to kick task if there is a chance it was waiting */
    if (!active_modules)
        *sem_to_post = &task->active_sem;

    return BCM_ERR_OK;
}

/* Send message to module */
bcmos_errno bcmos_msg_send_to_module(bcmos_module_id module_id, bcmos_msg *msg, bcmos_msg_send_flags flags)
{
    bcmos_sem *sem_to_post;
    bcmos_errno err = _bcmos_msg_send_to_module(module_id, msg, flags, &sem_to_post);
    if (sem_to_post)
        bcmos_sem_post(sem_to_post);
    return err;
}

/* Get message from the head of message queue */
bcmos_errno bcmos_msg_recv(bcmos_msg_queue *queue, uint32_t timeout, bcmos_msg **msg)
{
    long lock_flags;

    if (!queue || !msg)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "queue %p, msg %p\n", queue, msg);

#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT
    if (queue->q.parm.ep_type != BCMOS_MSG_QUEUE_EP_LOCAL)
    {
        return _bcmos_msg_recv_from_remote_ep(queue, timeout, msg);
    }
#endif

    lock_flags = bcmos_fastlock_lock(&queue->q.lock);
    *msg = _bcmos_msg_get(&queue->q);
    if (*msg)
    {
        bcmos_fastlock_unlock(&queue->q.lock, lock_flags);
        return BCM_ERR_OK;
    }
    if (!timeout)
    {
        bcmos_fastlock_unlock(&queue->q.lock, lock_flags);
        return BCM_ERR_NOENT;
    }

    /* Receive with wait */
    queue->is_waiting = BCMOS_TRUE;
    bcmos_fastlock_unlock(&queue->q.lock, lock_flags);

    /* wait for it */
    bcmos_sem_wait(&queue->m, timeout);
    lock_flags = bcmos_fastlock_lock(&queue->q.lock);
    *msg = _bcmos_msg_get(&queue->q);
    queue->is_waiting = BCMOS_FALSE;
    bcmos_fastlock_unlock(&queue->q.lock, lock_flags);
    if (!*msg)
        return BCM_ERR_TIMEOUT;

    return BCM_ERR_OK;
}

/*
 * Queue group support
 */

/* Create message queue group. */
bcmos_errno bcmos_msg_qgroup_create(bcmos_msg_qgroup *qgroup, const bcmos_msg_qgroup_parm *parm)
{
    bcmos_errno rc;
    bcmos_qgroup_prty prty;

    if (!qgroup || !parm || !parm->nqueues || parm->nqueues>32)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "queue %p, parm %p nqueues %u\n", qgroup, parm, parm ? parm->nqueues: 0);
    memset(qgroup, 0, sizeof(*qgroup));
    rc = bcmos_sem_create(&qgroup->m, 0, parm->flags, NULL);
    if (rc)
        return rc;
    qgroup->parm = *parm;
    bcmos_fastlock_init(&qgroup->lock, parm->flags);
    if (!qgroup->parm.size)
        qgroup->parm.size = BCMOS_MSG_QUEUE_SIZE_UNLIMITED;
    if (!qgroup->parm.high_wm)
        qgroup->parm.high_wm = BCMOS_MSG_QUEUE_SIZE_UNLIMITED;
    if (!qgroup->parm.low_wm)
        qgroup->parm.low_wm = qgroup->parm.high_wm;
    if (!qgroup->parm.notify)
        qgroup->parm.notify = _bcmos_qgroup_notify;
    qgroup->msgl = bcmos_calloc(sizeof(bcmos_msg_list) * (uint32_t)parm->nqueues);
    if (!qgroup->msgl)
    {
        bcmos_msg_qgroup_destroy(qgroup);
        return BCM_ERR_NOMEM;
    }
    for (prty = 0; prty < qgroup->parm.nqueues; prty++)
    {
        STAILQ_INIT(&qgroup->msgl[prty]);
    }
    /* Copy name to make sure that it is not released - in case it was on the stack */
    if (qgroup->parm.name)
    {
        strncpy(qgroup->name, qgroup->parm.name, sizeof(qgroup->parm.name) - 1);
        qgroup->parm.name = qgroup->name;
    }
    qgroup->magic = BCMOS_MSG_QGROUP_VALID;
    bcmos_mutex_lock(&bcmos_res_lock);
    STAILQ_INSERT_TAIL(&msg_qgroup_list, qgroup, list);
    bcmos_mutex_unlock(&bcmos_res_lock);

    return BCM_ERR_OK;
}

/** Destroy queue group
 *
 * \param[in]   qgroup       Queue group handle
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_qgroup_destroy(bcmos_msg_qgroup *qgroup)
{
    bcmos_qgroup_prty prty;

    if (!qgroup || qgroup->magic != BCMOS_MSG_QGROUP_VALID)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "queue group handle is invalid\n");
    }

    qgroup->magic = BCMOS_MSG_QGROUP_DELETED;

    bcmos_mutex_lock(&bcmos_res_lock);
    STAILQ_REMOVE(&msg_qgroup_list, qgroup, bcmos_msg_qgroup, list);
    bcmos_mutex_unlock(&bcmos_res_lock);

    bcmos_sem_destroy(&qgroup->m);

    /* Release all pending messages */
    if (qgroup->msgl)
    {
        for (prty = 0; prty < qgroup->parm.nqueues; prty++)
        {
            bcmos_msg_list_destroy(&qgroup->msgl[prty]);
        }
        bcmos_free(qgroup->msgl);
    }
    return BCM_ERR_OK;

}

/** Get queue group info */
bcmos_errno bcmos_msg_qgroup_query(const bcmos_msg_qgroup *qgroup, bcmos_msg_qgroup_info *info)
{
    if (!qgroup || !info)
        return BCM_ERR_PARM;

    info->parm = qgroup->parm;
    info->stat = qgroup->stat;

    return BCM_ERR_OK;
}

/** Message queue group iterator
 * \param[in] prev      Previous queue group. *prev==NULL - get first
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_msg_qgroup_get_next(const bcmos_msg_qgroup **prev)
{
    const bcmos_msg_qgroup *qgrp;

    if (prev == NULL)
    {
        return BCM_ERR_PARM;
    }
    qgrp = *prev;
    if (qgrp && qgrp->magic != BCMOS_MSG_QGROUP_VALID)
    {
        return BCM_ERR_PARM;
    }
    if (qgrp)
    {
        qgrp = STAILQ_NEXT(qgrp, list);
    }
    else
    {
        qgrp = STAILQ_FIRST(&msg_qgroup_list);
    }
    *prev = qgrp;
    if (!qgrp)
    {
        return BCM_ERR_NO_MORE;
    }
    return BCM_ERR_OK;
}

/* get message from non-empty queue group queue */
static inline bcmos_msg *_bcmos_qgroup_msg_get(bcmos_msg_qgroup *qgroup, bcmos_qgroup_prty prty)
{
    bcmos_msg *msg;
    msg = STAILQ_FIRST(&qgroup->msgl[prty]);
    BUG_ON(!msg);
    STAILQ_REMOVE_HEAD(&qgroup->msgl[prty], next);
    if (STAILQ_EMPTY(&qgroup->msgl[prty]))
    {
        qgroup->active_mask &= ~(1 << prty);
    }
    return msg;
}

/* Send message to queue group */
bcmos_errno bcmos_msg_send_to_qgroup(bcmos_msg_qgroup *qgroup, bcmos_msg *msg, bcmos_qgroup_prty prty,
    bcmos_msg_send_flags flags)
{
    long lock_flags;
    bcmos_errno rc = BCM_ERR_OK;

    if (prty >= qgroup->parm.nqueues)
    {
        if (!(flags & BCMOS_MSG_SEND_NO_FREE_ON_ERROR))
        {
            bcmos_msg_free(msg);
        }
        return BCM_ERR_PARM;
    }
    msg->send_flags = flags;

    lock_flags = bcmos_fastlock_lock(&qgroup->lock);

    /* Put into the relevant queue */
    STAILQ_INSERT_TAIL(&qgroup->msgl[prty], msg, next);
    qgroup->active_mask |= (1 << prty);
    _bcmos_qgroup_stat_inc(qgroup);

    /* Overflow check */
    if ((qgroup->stat.msg_in > qgroup->parm.size))
    {
        bcmos_msg *m;
        bcmos_qgroup_prty i;
        /* Find the lowest-priority queue with data and discard the head message.
         * The loop always finds something because we've just added a message
         */
        for (i = qgroup->parm.nqueues - 1; (qgroup->active_mask & (1 << i)) == 0; i--);
        m = _bcmos_qgroup_msg_get(qgroup, i);
        --qgroup->stat.msg_in;
        ++qgroup->stat.msg_discarded;
        if (!(m->send_flags & BCMOS_MSG_SEND_NO_FREE_ON_ERROR))
        {
            bcmos_msg_free(m);
        }
        rc = BCM_ERR_OVERFLOW;
    }

    /* Kick waiting task */
    if (qgroup->is_waiting)
    {
        qgroup->is_waiting = BCMOS_FALSE;
        bcmos_fastlock_unlock(&qgroup->lock, lock_flags);
        bcmos_sem_post(&qgroup->m);
    }
    else
    {
        bcmos_fastlock_unlock(&qgroup->lock, lock_flags);
    }

    return rc;

}

/* Get highest priority message from queue group */
bcmos_errno bcmos_msg_recv_from_qgroup(bcmos_msg_qgroup *qgroup, uint32_t timeout, bcmos_msg **msg)
{
    long lock_flags;
    bcmos_qgroup_prty prty;

    if (!qgroup || !msg)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "qgroup %p, msg %p\n", qgroup, msg);

    lock_flags = bcmos_fastlock_lock(&qgroup->lock);
    if (!qgroup->active_mask)
    {
        if (!timeout)
        {
            bcmos_fastlock_unlock(&qgroup->lock, lock_flags);
            return BCM_ERR_NOENT;
        }

        /* Receive with wait */
        qgroup->is_waiting = BCMOS_TRUE;
        bcmos_fastlock_unlock(&qgroup->lock, lock_flags);

        /* wait for it */
        bcmos_sem_wait(&qgroup->m, timeout);

        /* Done waiting. Either got a message or a timeout */
        lock_flags = bcmos_fastlock_lock(&qgroup->lock);
        qgroup->is_waiting = BCMOS_FALSE;
        if (!qgroup->active_mask)
        {
            bcmos_fastlock_unlock(&qgroup->lock, lock_flags);
            return BCM_ERR_TIMEOUT;
        }
    }

    prty = (bcmos_qgroup_prty)(ffs(qgroup->active_mask) - 1);
    BUG_ON(prty >= qgroup->parm.nqueues);
    *msg = _bcmos_qgroup_msg_get(qgroup, prty);
    _bcmos_qgroup_stat_dec(qgroup);
    bcmos_fastlock_unlock(&qgroup->lock, lock_flags);

    return BCM_ERR_OK;
}

/*
 * Message registration and dispatch
 */

/* Hash entry */
typedef struct msg_hash_entry msg_hash_entry;

struct msg_hash_entry
{
    /* Key */
    uint32_t key;       /* msg_type + instance */

    /* Value */
    bcmos_module_id module_id;
    F_bcmos_msg_handler handler;

    /* List of entries with the same key */
    SLIST_ENTRY(msg_hash_entry) list;
};

/* Hash table */
static SLIST_HEAD(msg_hash, msg_hash_entry) msg_hash_table[BCMOS_MSG_HASH_SIZE];

/* Make hash key from msg_type and instance */
static inline uint32_t _bcmos_msg_hash_key(bcmos_msg_id msg_type, bcmos_msg_instance instance)
{
    return ((uint32_t)instance << 16) | (uint32_t)msg_type;
}

/* Hash function */
static inline uint32_t _bcmos_msg_hash_func(uint32_t key)
{
    key ^= (key >> 9);
    key ^= (key << 3);
    key ^= (key >> 15);
    return key % BCMOS_MSG_HASH_SIZE;
}

/* Find entry in hash */
static inline msg_hash_entry *_bcmos_msg_hash_find(bcmos_msg_id msg_type, bcmos_msg_instance instance)
{
    uint32_t key = _bcmos_msg_hash_key(msg_type, instance);
    uint32_t hash = _bcmos_msg_hash_func(key);
    msg_hash_entry *entry;
    SLIST_FOREACH(entry, &msg_hash_table[hash], list)
    {
        if (entry->key == key)
            break;
    }
    return entry;
}

/* Register message_type+instance --> module+handler */
bcmos_errno bcmos_msg_register(bcmos_msg_id msg_type, bcmos_msg_instance instance,
    bcmos_module_id module_id, F_bcmos_msg_handler handler)
{
    uint32_t key = _bcmos_msg_hash_key(msg_type, instance);
    uint32_t hash = _bcmos_msg_hash_func(key);
    msg_hash_entry *entry;
    long lock_flags;

    if (!handler)
        return BCM_ERR_PARM;

    entry = bcmos_calloc(sizeof(*entry));
    if (!entry)
        return BCM_ERR_NOMEM;

    entry->key = key;
    entry->module_id = module_id;
    entry->handler = handler;
    lock_flags = bcmos_fastlock_lock(&bcmos_msg_register_lock);
    if (_bcmos_msg_hash_find(msg_type, instance) != NULL)
    {
        bcmos_fastlock_unlock(&bcmos_msg_register_lock, lock_flags);
        bcmos_free(entry);
        return BCM_ERR_ALREADY;
    }
    SLIST_INSERT_HEAD(&msg_hash_table[hash], entry, list);
    bcmos_fastlock_unlock(&bcmos_msg_register_lock, lock_flags);

    return BCM_ERR_OK;
}

bcmos_errno bcmos_msg_unregister(bcmos_msg_id msg_type, bcmos_msg_instance instance, bcmos_module_id module_id)
{
    uint32_t key = _bcmos_msg_hash_key(msg_type, instance);
    uint32_t hash = _bcmos_msg_hash_func(key);
    msg_hash_entry *entry;
    long lock_flags;

    lock_flags = bcmos_fastlock_lock(&bcmos_msg_register_lock);
    entry = _bcmos_msg_hash_find(msg_type, instance);
    if (!entry)
    {
        bcmos_fastlock_unlock(&bcmos_msg_register_lock, lock_flags);
        return BCM_ERR_NOENT;
    }

    if (entry->module_id != module_id)
    {
        bcmos_fastlock_unlock(&bcmos_msg_register_lock, lock_flags);
        return BCM_ERR_INVALID_OP;
    }

    SLIST_REMOVE(&msg_hash_table[hash], entry, msg_hash_entry, list);
    bcmos_fastlock_unlock(&bcmos_msg_register_lock, lock_flags);
    bcmos_free(entry);

    return BCM_ERR_OK;
}

void bcmos_msg_shutdown_mode_set(bcmos_bool shutdown_mode)
{
    bcmos_msg_shutdown_mode = shutdown_mode;
}

bcmos_bool bcmos_msg_shutdown_mode_get(void)
{
    return bcmos_msg_shutdown_mode;
}

/* Dispatch message to registered module */
bcmos_errno bcmos_msg_dispatch(bcmos_msg *msg, bcmos_msg_send_flags flags)
{
    bcmos_errno err;

    if (unlikely(bcmos_msg_shutdown_mode))
    {
        /* In shutdown mode, we need to acquire the same lock used to protect bcmos_msg_register() /
         * bcmos_msg_unregister(), since we must support calling these functions concurrently. */
        msg_hash_entry *entry;
        bcmos_sem *sem_to_post = NULL;
        long lock_flags = bcmos_fastlock_lock(&bcmos_msg_register_lock);
        entry = _bcmos_msg_hash_find(msg->type, msg->instance);

        if (entry)
        {
            msg->handler = entry->handler;
            err = _bcmos_msg_send_to_module(entry->module_id, msg, flags, &sem_to_post);
        }
        else
        {
            /* Not found. Release automatically if requested. */
            if (!(flags & BCMOS_MSG_SEND_NO_FREE_ON_ERROR))
                bcmos_msg_free(msg);
            err = BCM_ERR_OK;
        }

        bcmos_fastlock_unlock(&bcmos_msg_register_lock, lock_flags);
        if (sem_to_post)
            bcmos_sem_post(sem_to_post);
    }
    else
    {
        msg_hash_entry *entry = _bcmos_msg_hash_find(msg->type, msg->instance);

        if (entry)
        {
            msg->handler = entry->handler;
            err = bcmos_msg_send_to_module(entry->module_id, msg, flags);
        }
        else
        {
            /* Not found. Release automatically if requested. */
            BCMOS_TRACE_ERR("Can't dispatch unregistered msg %d:%d\n", msg->type, msg->instance);
            if (!(flags & BCMOS_MSG_SEND_NO_FREE_ON_ERROR))
                bcmos_msg_free(msg);
            err = BCM_ERR_NOENT;
        }
    }

    return err;
}

bcmos_errno bcmos_msg_cancel(bcmos_msg *msg, bcmos_module_id module_id)
{
    bcmos_module *module = _bcmos_module_get(module_id);
    long flags;
    bcmos_errno rc;

    if (unlikely(module == NULL || module->deleted))
    {
        BCMOS_TRACE_ERR("Module %d doesn't exist or has been deleted\n", module_id);
        return BCM_ERR_NOENT;
    }

    flags = bcmos_fastlock_lock(&module->msgq.lock);

    if (STAILQ_REMOVE_SAFE(&module->msgq.msgl, msg, bcmos_msg, next) != NULL)
    {
        _bcmos_msgq_stat_dec(&module->msgq);
        rc = BCM_ERR_OK; /* removed a standard-priority message */
    }
    else if (STAILQ_REMOVE_SAFE(&module->msgq.msgl_urg, msg, bcmos_msg, next) != NULL)
    {
        _bcmos_msgq_stat_dec(&module->msgq);
        rc = BCM_ERR_OK; /* removed an urgent message */
    }
    else
    {
        rc = BCM_ERR_ALREADY; /* the message is not in the target queue */
    }

    bcmos_fastlock_unlock(&module->msgq.lock, flags);
    return rc;
}

/*
 * Task management
 */

/*
 * Default task handler
 */
/*lint -e{632,633,634}
 * There are a few warnings about
 * implicit bcmos_errno conversion to int. It is to bothersome now
 * to change task handler prototype everywhere and the warning is harmless
 */
int bcmos_dft_task_handler(long data)
{
    bcmos_task *task = (bcmos_task *)data;
    long flags = 0, q_flags = 0;
    uint32_t active_modules;
    int last_module = 0; /* 1-based last handled module index */
    bcmos_module *module;
    bcmos_msg *msg;
    bcmos_errno rc;
    int rc_int;

    /* Set / validate task timeout */
    rc = bcmos_task_timeout_set(task, task->parm.msg_wait_timeout, task->parm.timeout_handler);
    if (rc)
        return (int)rc;

    /* Call init callback if any */
    if (task->parm.init_handler)
    {
        rc_int = task->parm.init_handler(task->parm.data);
        if (rc_int)
        {
            BCMOS_TRACE_ERR("Task %s: init_handler returned error %s (%d)\n",
                task->parm.name, bcmos_strerror((bcmos_errno)rc_int), rc_int);
            bcmos_task_destroy(task);
            return rc_int;
        }
    }

    /* Wait for module activity */
    while (!task->destroy_request)
    {
        task->current_module = BCMOS_MODULE_ID_NONE;

        /* Wait for module activity */
        rc = bcmos_sem_wait(&task->active_sem, task->parm.msg_wait_timeout);
        if (rc == BCM_ERR_TIMEOUT)
        {
            F_bcmos_task_handler timeout_handler = task->parm.timeout_handler;

            /* Handle possible race condition */
            if (!timeout_handler)
                continue;
            rc_int = timeout_handler(data);
            if (rc_int)
            {
                BCMOS_TRACE_ERR("Task %s: terminated by timeout_handler. error %s (%d)\n",
                    task->parm.name, bcmos_strerror((bcmos_errno)rc_int), rc_int);
                break;
            }
            /* Keep waiting */
            continue;
        }

        /* RR active modules */
        do
        {
            flags = bcmos_fastlock_lock(&task->active_lock);
            active_modules = (task->active_modules >> last_module);
            if (!active_modules)
            {
                last_module = 0;
                active_modules = task->active_modules;
                if (!active_modules)
                {
                    /* No modules with work to do */
                    bcmos_fastlock_unlock(&task->active_lock, flags);
                    continue;
                }
            }
            last_module += ffs(active_modules);
            BUG_ON(last_module > BCMOS_MAX_MODULES_PER_TASK);
            module = task->modules[last_module - 1];
            BUG_ON(!module);

            q_flags = bcmos_fastlock_lock(&module->msgq.lock);
            /* Get message from the module's message queue */
            msg = _bcmos_msg_get(&module->msgq);
            if (!msg)
            {
                bcmos_fastlock_unlock(&module->msgq.lock, q_flags);
                task->active_modules &= ~(1 << (last_module - 1));
                bcmos_fastlock_unlock(&task->active_lock, flags);
                continue;
            }

            bcmos_fastlock_unlock(&module->msgq.lock, q_flags);
            bcmos_fastlock_unlock(&task->active_lock, flags);

            /* Handle the message */
            if (msg->handler)
            {
                task->current_module = module->id;
                msg->handler(module->id, msg);
            }
            else
            {
                BCMOS_TRACE_ERR("msg->handler is not set. msg->type=%d\n", msg->type);
                bcmos_msg_free(msg);
            }
        } while (task->active_modules);
    }

    return 0;
}

/* Set task message timeout.
 * The function is only supported in integration mode
 */
bcmos_errno bcmos_task_timeout_set(bcmos_task *task, uint32_t timeout, F_bcmos_task_handler timeout_handler)
{
    if (task->parm.handler)
    {
        BCMOS_TRACE_ERR("%s: The function is only supported in integration mode (task handler == NULL)\n", task->parm.name);
        return BCM_ERR_NOT_SUPPORTED;
    }
    if ((timeout && timeout != BCMOS_WAIT_FOREVER) && !timeout_handler)
    {
        BCMOS_TRACE_ERR("%s: timeout_handler is not set\n", task->parm.name);
        return BCM_ERR_PARM;
    }

    /* 0 means FOREVER here */
    if (!timeout)
        timeout = BCMOS_WAIT_FOREVER;

    task->parm.timeout_handler = timeout_handler;
    task->parm.msg_wait_timeout = timeout;

    return BCM_ERR_OK;
}

/*
 * Module
 */

/* Register module */
bcmos_errno bcmos_module_create(bcmos_module_id module_id, bcmos_task *task, bcmos_module_parm *parm)
{
    bcmos_module *module;
    bcmos_errno rc = BCM_ERR_OK;
    int i;

    if ((unsigned)module_id >= (unsigned)BCMOS_MODULE_ID__NUM_OF || !parm)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "module %d, parm %p\n", module_id, parm);
    if (!task)
        BCMOS_TRACE_RETURN(BCM_ERR_NOT_SUPPORTED, "No task\n");
    if (bcmos_modules[module_id])
        BCMOS_TRACE_RETURN(BCM_ERR_ALREADY, "module_id %d\n", module_id);

    module = bcmos_calloc(sizeof(bcmos_module));
    if (!module)
        BCMOS_TRACE_RETURN(BCM_ERR_NOMEM, "module_id %d\n", module_id);
    module->id = module_id;
    module->my_task = task;
    module->parm = *parm;
    module->context = (void *)parm->data;
    bcmos_msg_queue_nw_init(&module->msgq, &parm->qparm);
    /* Copy name to make sure that it is not released - in case it was on the stack */
    if (module->parm.qparm.name)
    {
        strncpy(module->name, module->parm.qparm.name, sizeof(module->name) - 1);
        module->parm.qparm.name = module->name;
    }

    /* Assign module id */
    for (i = 0; i < BCMOS_MAX_MODULES_PER_TASK; i++)
    {
        if (!task->modules[i])
        {
            task->modules[i] = module;
            module->idx = i;
            break;
        }
    }
    if (i ==  BCMOS_MAX_MODULES_PER_TASK)
    {
        bcmos_free(module);
        BCMOS_TRACE_RETURN(BCM_ERR_TOO_MANY, "module_id %d\n", module_id);
    }

    bcmos_modules[module_id] = module;

    /* Init module */
    if (parm->init)
    {
        rc = parm->init(parm->data);
    }

#ifdef BCMOS_HEALTH_CHECK_ENABLED
    if (rc == BCM_ERR_OK)
    {
        rc = bcmos_module_health_check_init(module);
    }
#endif

    if (rc)
    {
        bcmos_module_destroy(module_id);
    }

    return rc;
}

/* Un-register module */
bcmos_errno bcmos_module_destroy(bcmos_module_id module_id)
{
    bcmos_module *module = _bcmos_module_get(module_id);
    bcmos_task *task;
    long lock_flags, q_lock_flags;
    bcmos_msg_list msgl_urg, msgl;

    if (!module)
        BCMOS_TRACE_RETURN(BCM_ERR_NOENT, "module_id %d\n", module_id);

    module->deleted = BCMOS_TRUE;
    task = module->my_task;
    lock_flags = bcmos_fastlock_lock(&task->active_lock);
    task->modules[module->idx] = NULL;
    task->active_modules &= ~(1 << module->idx);

    /* Because we are not allowed to free memory (via bcmos_free()) when interrupts are locked, we only empty the linked list (via SLIST_INIT()) and the free comes outside the locked
     * section. */
    q_lock_flags = bcmos_fastlock_lock(&module->msgq.lock);
    msgl_urg = module->msgq.msgl_urg;
    msgl = module->msgq.msgl;
    STAILQ_INIT(&module->msgq.msgl_urg);
    STAILQ_INIT(&module->msgq.msgl);
    bcmos_fastlock_unlock(&module->msgq.lock, q_lock_flags);
    bcmos_fastlock_unlock(&task->active_lock, lock_flags);

    bcmos_msg_list_destroy(&msgl_urg);
    bcmos_msg_list_destroy(&msgl);

#ifdef BCMOS_HEALTH_CHECK_ENABLED
    bcmos_module_health_check_destroy(module_id);
#endif

    if (module->parm.exit)
        module->parm.exit(module->parm.data);
    bcmos_modules[module_id] = NULL;
    bcmos_free(module);

    return BCM_ERR_OK;
}

/* Get current module id in the current task */
bcmos_module_id bcmos_module_current(void)
{
    bcmos_task *task = bcmos_task_current();

    if (!task)
        return BCMOS_MODULE_ID_NONE;
    return task->current_module;
}

/* Get module context set by bcmos_module_context_set().
   This function can be called even while module is being destroyed */
void *bcmos_module_context(bcmos_module_id module_id)
{
    bcmos_module *module = _bcmos_module_get(module_id);
    if (!module)
        return NULL;
    return module->context;
}

/* Set module context */
bcmos_errno bcmos_module_context_set(bcmos_module_id module_id, void *context)
{
    bcmos_module *module = _bcmos_module_get(module_id);

    if (!module)
        BCMOS_TRACE_RETURN(BCM_ERR_NOENT, "module_id %d\n", module_id);
    module->context = context;
    return BCM_ERR_OK;
}

/* Query module info */
bcmos_errno bcmos_module_query(bcmos_module_id module_id, const bcmos_task **task, bcmos_msg_queue_info *info)
{
    bcmos_module *module = _bcmos_module_get(module_id);

    if (!module)
    {
        return BCM_ERR_NOENT;
    }
    if (task)
    {
        *task = module->my_task;
    }
    if (info)
    {
        info->parm = module->parm.qparm;
        info->stat = module->msgq.stat;
    }
    return BCM_ERR_OK;
}

/* Check that all created modules have a name assigned*/
bcmos_errno bcmos_modules_name_check(void)
{
    bcmos_errno rc = BCM_ERR_OK;
    bcmos_module_id m;

    /* Ensure that all registered modules have names */
    for (m = (bcmos_module_id)(BCMOS_MODULE_ID_NONE + 1); m < BCMOS_MODULE_ID__NUM_OF; m++)
    {
        bcmos_module *module = _bcmos_module_get(m);
        if (module != NULL && module->name[0] == '\0')
        {
            BCMOS_TRACE_ERR("Module %d does not have a name\n", m);
            rc = BCM_ERR_PARM;
        }
    }
    return rc;
}

/*
 * Events
 */

/* This function handles event arrival in module context */
static void _bcmos_ev_in_module_handler(bcmos_module_id module_id, bcmos_msg *msg)
{
    bcmos_event *ev = _bcmos_msg_to_event(msg);
    uint32_t active_bits;
    long lock_flags;

    active_bits = ev->active_bits & ev->parm.mask;

    lock_flags = bcmos_fastlock_lock(&ev->lock);
    ev->active_bits &= ~active_bits;
    ev->is_waiting = BCMOS_TRUE;
    bcmos_fastlock_unlock(&ev->lock, lock_flags);

    ev->parm.handler(ev->id, active_bits);
}

/* Release event message. Only called in exceptional situations,
 * such as module queue destroy. Do nothing.
 */
static void _bcmos_ev_msg_release(bcmos_msg *msg)
{
}

/* Create event set */
bcmos_errno bcmos_event_create(bcmos_event_id event_id, bcmos_event_parm *parm)
{
    bcmos_event *ev;
    bcmos_module *module = NULL;
    bcmos_errno rc;

    if ((unsigned)event_id >= (unsigned)BCMOS_EVENT_ID__NUM_OF)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "event_id %d\n", event_id);

    if (_bcmos_event_get(event_id))
        BCMOS_TRACE_RETURN(BCM_ERR_ALREADY, "event_id %d\n", event_id);

    if (parm && parm->module_id != BCMOS_MODULE_ID_NONE)
    {
        module = _bcmos_module_get(parm->module_id);
        if (!module)
            BCMOS_TRACE_RETURN(BCM_ERR_NOENT, "module_id %d\n", parm->module_id);
        if (!parm->handler || !parm->mask)
            BCMOS_TRACE_RETURN(BCM_ERR_PARM, "event_id %d, handler %p, mask %x\n", event_id, parm->handler, parm->mask);
    }

    ev = bcmos_calloc(sizeof(bcmos_event));
    if (!ev)
        BCMOS_TRACE_RETURN(BCM_ERR_NOMEM, "event_id %d\n", event_id);

    ev->id = event_id;
    if (parm)
        ev->parm = *parm;
    bcmos_fastlock_init(&ev->lock, ev->parm.flags);
    {
        rc = bcmos_sem_create(&ev->m, 0, ev->parm.flags, ev->parm.name);
        if (rc)
        {
            bcmos_free(ev);
            return rc;
        }
    }

    /* Initialize event message in integration mode */
    if (ev->parm.module_id != BCMOS_MODULE_ID_NONE)
    {
        ev->msg.handler = _bcmos_ev_in_module_handler;
        ev->msg.release = _bcmos_ev_msg_release;
        ev->msg.sender = BCMOS_MODULE_ID_NONE;
        ev->msg.type = BCMOS_MSG_ID_INTERNAL_EVENT;
        ev->is_waiting = BCMOS_TRUE;
    }

    /* Copy name to make sure that it is not released - in case it was on the stack */
    if (ev->parm.name)
    {
        strncpy(ev->name, ev->parm.name, sizeof(ev->name) - 1);
        ev->parm.name = ev->name;
    }

    bcmos_events[event_id] = ev;

    return BCM_ERR_OK;
}

/* Destroy event set created by bcmos_event_create() */
bcmos_errno bcmos_event_destroy(bcmos_event_id event_id)
{
    bcmos_event *ev = _bcmos_event_get(event_id);

    if (!ev)
        BCMOS_TRACE_RETURN(BCM_ERR_NOENT, "event_id %d\n", event_id);

    bcmos_events[event_id] = NULL;
    bcmos_sem_destroy(&ev->m);
    bcmos_free(ev);

    return BCM_ERR_OK;
}

/* Raise event */
bcmos_errno bcmos_event_raise(bcmos_event_id event_id, uint32_t active_bits)
{
    bcmos_event *ev = _bcmos_event_get(event_id);
    long lock_flags;

    if (!ev)
        BCMOS_TRACE_RETURN(BCM_ERR_NOENT, "event_id %d\n", event_id);

    lock_flags = bcmos_fastlock_lock(&ev->lock);
    ev->active_bits |= active_bits;
    if (ev->is_waiting && (ev->active_bits & ev->parm.mask))
    {
        ev->is_waiting = BCMOS_FALSE;
        bcmos_fastlock_unlock(&ev->lock, lock_flags);

        if (ev->parm.module_id != BCMOS_MODULE_ID_NONE)
            bcmos_msg_send_to_module(ev->parm.module_id, &ev->msg, (bcmos_msg_send_flags)(BCMOS_MSG_SEND_URGENT | BCMOS_MSG_SEND_NOLIMIT));
        else
            bcmos_sem_post(&ev->m);
    }
    else
    {
        bcmos_fastlock_unlock(&ev->lock, lock_flags);
    }

    return BCM_ERR_OK;
}

/* Wait for event */
bcmos_errno bcmos_event_recv(bcmos_event_id event_id, uint32_t mask,
    uint32_t timeout, uint32_t *active_bits)
{
    bcmos_event *ev = _bcmos_event_get(event_id);
    long lock_flags;

    BUG_ON(!active_bits);
    if (!ev)
        BCMOS_TRACE_RETURN(BCM_ERR_NOENT, "event_id %d is not registered\n", event_id);

    lock_flags = bcmos_fastlock_lock(&ev->lock);
    *active_bits = ev->active_bits & mask;
    if (*active_bits)
    {
        ev->active_bits &= ~ *active_bits;
        bcmos_fastlock_unlock(&ev->lock, lock_flags);
        return BCM_ERR_OK;
    }
    if (!timeout)
    {
        bcmos_fastlock_unlock(&ev->lock, lock_flags);
        return BCM_ERR_NOENT;
    }

    /* recv with wait */
    ev->is_waiting = BCMOS_TRUE;
    bcmos_fastlock_unlock(&ev->lock, lock_flags);

    /* wait for it */
    bcmos_sem_wait(&ev->m, timeout);
    /* Either got event or timeout */
    lock_flags = bcmos_fastlock_lock(&ev->lock);
    *active_bits = ev->active_bits & mask;
    ev->active_bits &= ~ *active_bits;
    ev->is_waiting = BCMOS_FALSE;
    bcmos_fastlock_unlock(&ev->lock, lock_flags);
    /* If we wait forever and we got an event that does not match the mask we wait on (this is the only possible reason getting here if waiting forever), then we
     * want to avoid returning BCM_ERR_TIMEOUT - it's not an error. */
    if (timeout != BCMOS_WAIT_FOREVER && !*active_bits)
        return BCM_ERR_TIMEOUT;
    return BCM_ERR_OK;
}

/*
 * Timer
 */

/* compare timestamps minding wrap-around
 * returns delta >= 0 if ts1 >= ts2
 */
static inline int32_t _bcmos_timer_ts_delta(uint32_t ts1, uint32_t ts2)
{
    int32_t delta = (int)(ts1 - ts2);
    return delta;
}

static int32_t _bcmos_timer_compare(struct bcmos_timer *t1, struct bcmos_timer *t2)
{
    int32_t delta = _bcmos_timer_ts_delta(t1->expire_at, t2->expire_at);
#if defined(BCMOS_TIMER_RB_TREE) && !defined(BCMOS_TIMER_RB_TREE_LIST)
    /* FreeBSD RB tree implementation doesn't support 2 nodes with the same key */
    if (!delta)
        delta = 1;
#endif
    return delta;
}

static inline void _bcmos_start_system_timer(bcmos_timer *head)
{
    if (head)
    {
        int32_t delay = _bcmos_timer_ts_delta(head->expire_at, bcmos_timestamp());
        /* Handle rare race condition when next timer expired while we were fiddling
         * with the pool. Just give it 1 more "tick". System handler handles all timers
         * expired (<now .. now + PRECISION/2)
         */
        if (delay <= 0)
        {
            delay = BCMOS_TIMER_PRECISION_US / 2;
        }
        bcmos_sys_timer_start(&tmr_pool.sys_timer, delay);
    }
    else
    {
        bcmos_sys_timer_stop(&tmr_pool.sys_timer);
    }
}

/*
 * Timer pool: RB tree or TAILQ-based implementation
 */
static void _bcmos_timer_pool_insert(bcmos_timer *timer, uint32_t delay, bcmos_bool start_sys_timer)
{
    long flags;
    bcmos_timer *head;

    flags = bcmos_fastlock_lock(&tmr_pool.lock);
    if (BCMOS_TIMER_IS_RUNNING(timer))
    {
        bcmos_fastlock_unlock(&tmr_pool.lock, flags);
        return;
    }
    timer->period = timer->parm.periodic ? delay : 0;
    timer->expire_at = BCMOS_ROUND_UP(bcmos_timestamp() + delay, BCMOS_TIMER_PRECISION_US / 2);
    TMR_POOL_INSERT(&tmr_pool, timer);
    timer->flags &= ~BCMOS_TIMER_FLAG_EXPIRED;
    timer->flags |= BCMOS_TIMER_FLAG_RUNNING;

    /* If new timer is at the top - kick system timer */
    if (start_sys_timer)
    {
        head = TMR_POOL_FIRST(&tmr_pool);
        if (timer == head)
        {
            _bcmos_start_system_timer(head);
        }
    }
    bcmos_fastlock_unlock(&tmr_pool.lock, flags);
}

static void _bcmos_timer_stop(bcmos_timer *timer)
{
    long flags;
    bcmos_bool was_top;
    bcmos_msg_queue_nw *queue;

    /* First take running timer out of the active pool */
    flags = bcmos_fastlock_lock(&tmr_pool.lock);
    timer->period = 0; /* Prevent periodic timer restart */
    if (BCMOS_TIMER_IS_RUNNING(timer))
    {
        timer->flags &= ~BCMOS_TIMER_FLAG_RUNNING;
        was_top = (timer == TMR_POOL_FIRST(&tmr_pool));
        TMR_POOL_REMOVE(&tmr_pool, timer);

        /* If timer was the top - stop/restart system timer */
        if (was_top)
        {
            _bcmos_start_system_timer(TMR_POOL_FIRST(&tmr_pool));
        }
    }
    bcmos_fastlock_unlock(&tmr_pool.lock, flags);

    /* Now timer is not in the active pool. Perhaps it is already in
     * destination module's queue. Take it out if yes.
     */
    queue = timer->queue;
    if (queue)
    {
        flags = bcmos_fastlock_lock(&queue->lock);
        /* Check queue again because the previous check was unprotected */
        if (timer->queue)
        {
            bcmos_msg_list *msg_list = ((timer->parm.flags & BCMOS_TIMER_PARM_FLAGS_NON_URGENT))
                ? &queue->msgl : &queue->msgl_urg;
            if (STAILQ_REMOVE_SAFE(msg_list, &timer->msg, bcmos_msg, next) != NULL)
            {
                _bcmos_msgq_stat_dec(queue);
            }
            timer->queue = NULL;
        }
        timer->flags &= ~BCMOS_TIMER_FLAG_EXPIRED;
        bcmos_fastlock_unlock(&queue->lock, flags);
    }

    /* If timer has already expired and we weren't able to stop it -
     * wait for expiration callback to finish before leaving _bcmos_timer_stop()
     */
    if (BCMOS_TIMER_IS_EXPIRED(timer))
    {
        bcmos_task *t = bcmos_task_current();

        /* Skip wait if timer is being stopped from the owner's task context */
        if (t != NULL && t != timer->owner_task && t != timer->task)
        {
            while (BCMOS_TIMER_IS_EXPIRED(timer) && BCMOS_TIMER_IS_VALID(timer))
            {
                bcmos_usleep(1000);
            }
            timer->flags &= ~BCMOS_TIMER_FLAG_EXPIRED;
        }
    }
}

/* System timer expiration handler.
 * Execute all timers that expired and restart system timer
 */
static void _sys_timer_handler(void *data)
{
    bcmos_timer_pool *pool = (bcmos_timer_pool *)data;
    bcmos_timer *timer;
    bcmos_timer_rc rc;
    long flags;

    BUG_ON(pool != &tmr_pool);
    if (!pool->sys_timer_task_set)
    {
        pool->sys_timer_task = bcmos_task_current();
        pool->sys_timer_task_set = BCMOS_TRUE;
    }
    flags = bcmos_fastlock_lock(&pool->lock);
    while ((timer=TMR_POOL_FIRST(pool)) != NULL)
    {
        /* Stop when reached timer that hasn't expired yet */
        if (_bcmos_timer_ts_delta(timer->expire_at, bcmos_timestamp()) > BCMOS_TIMER_PRECISION_US / 2)
            break;
        timer->flags |= BCMOS_TIMER_FLAG_EXPIRED;
        timer->flags &= ~BCMOS_TIMER_FLAG_RUNNING;
        timer->task = pool->sys_timer_task;
        /* IT: Barrier here ? */
        TMR_POOL_REMOVE(pool, timer);

        /* Execute handler. Unlock first and re-lock in the end
         * It is safe to unlock here because the top loop starts from MIN every time
         */
        bcmos_fastlock_unlock(&pool->lock, flags);
        rc = timer->handler(timer, timer->parm.data);
        if (!timer->parm.owner)
        {
            if (rc == BCMOS_TIMER_OK && timer->period)
            {
                uint32_t interval = timer->period;
                /* coverity[missing_lock] - it's OK to be unlocked here */
                timer->period = 0;
                _bcmos_timer_pool_insert(timer, interval, BCMOS_FALSE);
            }
            else
            {
                timer->flags &= ~BCMOS_TIMER_FLAG_EXPIRED;
            }
        }
        flags = bcmos_fastlock_lock(&pool->lock);
    }
    /* Finally kick system timer */
    _bcmos_start_system_timer(timer);
    bcmos_fastlock_unlock(&pool->lock, flags);
}

/* Send timer expiration to the target module as urgent message.
 * _bcmos_timer_in_module_handler() will get called in the module context
 */
static bcmos_timer_rc _bcmos_timer_send_to_module_handler(bcmos_timer *timer, long data)
{
    bcmos_errno rc;
    bcmos_module *module = _bcmos_module_get(timer->parm.owner);
    bcmos_msg_send_flags send_flags;
    if (!module)
    {
        /* Shouldn't happen, unless the module was destroyed */
        BCMOS_TRACE_ERR("_bcmos_timer_send_to_module_handler() -- no module=%u (timer->parm.handler=0x%p)\n", timer->parm.owner, timer->parm.handler);
        timer->flags &= ~BCMOS_TIMER_FLAG_EXPIRED;
        return BCMOS_TIMER_STOP;      /* will restart in module context if necessary */
    }
    timer->queue = &module->msgq;
    send_flags = BCMOS_MSG_SEND_NOLIMIT;
    if (!((timer->parm.flags & BCMOS_TIMER_PARM_FLAGS_NON_URGENT)))
        send_flags |= BCMOS_MSG_SEND_URGENT;
    rc = bcmos_msg_send_to_module(timer->parm.owner, &timer->msg, send_flags);
    if (rc)
    {
        /* Shouldn't happen, unless the module was destroyed. Very short race condition here */
        timer->queue = NULL;
        timer->flags &= ~BCMOS_TIMER_FLAG_EXPIRED;
        BCMOS_TRACE_INFO("_bcmos_timer_send_to_module_handler() --> %d\n", rc);
    }
    return BCMOS_TIMER_STOP; /* will restart in module context if necessary */
}

/* This function handles timer expiration in module context */
static void _bcmos_timer_in_module_handler(bcmos_module_id module_id, bcmos_msg *msg)
{
    bcmos_timer *timer = _bcmos_msg_to_timer(msg);
    bcmos_module *module = _bcmos_module_get(timer->parm.owner);
    bcmos_task *prev_timer_task = timer->task;
    bcmos_timer_rc rc;

    /* Call timer's callback function and restart the timer if necessary */
    timer->queue = NULL;
    /* module can't be NULL here. it is checked anyway to keep static code analyzer happy */
    if (module)
        timer->task = module->my_task;
    rc = timer->parm.handler(timer, timer->parm.data);
    timer->task = prev_timer_task;
    if (rc == BCMOS_TIMER_OK && timer->period)
        _bcmos_timer_pool_insert(timer, timer->period, BCMOS_TRUE);
    else
        timer->flags &= ~BCMOS_TIMER_FLAG_EXPIRED;
}

/* Release timer message. Only called in exceptional situations,
 * such as module queue destroy. Do nothing
 */
static void _bcmos_timer_msg_release(bcmos_msg *msg)
{
}

/* Create timer */
bcmos_errno bcmos_timer_create(bcmos_timer *timer, bcmos_timer_parm *parm)
{
    if (!timer || !parm || !parm->handler)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "timer %p, parm %p handler %p\n", timer, parm, parm ? parm->handler : NULL);
    memset(timer, 0, sizeof(bcmos_timer));
    timer->parm = *parm;
    if (parm->owner == BCMOS_MODULE_ID_NONE)
        timer->handler = parm->handler;
    else
    {
        bcmos_module *m = _bcmos_module_get(parm->owner);
        BCMOS_TRACE_CHECK_RETURN(m == NULL, BCM_ERR_NOENT, "module_id %d\n", parm->owner);
        timer->owner_task = m->my_task;
        timer->handler = _bcmos_timer_send_to_module_handler;
        timer->msg.handler = _bcmos_timer_in_module_handler;
        timer->msg.release = _bcmos_timer_msg_release;
        timer->msg.sender = BCMOS_MODULE_ID_NONE;
        timer->msg.type = BCMOS_MSG_ID_INTERNAL_TIMER;
    }
    timer->flags |= BCMOS_TIMER_FLAG_VALID;

#ifdef BCMOS_TIMER_DEBUG
    bcmos_mutex_lock(&bcmos_res_lock);
    timer->magic = BCMOS_TIMER_MAGIC;
    STAILQ_INSERT_TAIL(&timer_list, timer, list);
    bcmos_mutex_unlock(&bcmos_res_lock);
#endif

    return BCM_ERR_OK;
}

/* Destroy timer */
void bcmos_timer_destroy(bcmos_timer *timer)
{
    BUG_ON(!timer);
#ifdef BCMOS_TIMER_DEBUG
    BUG_ON(timer->magic != BCMOS_TIMER_MAGIC);
#endif
    bcmos_timer_stop(timer);
    timer->flags &= ~BCMOS_TIMER_FLAG_VALID;

#ifdef BCMOS_TIMER_DEBUG
    bcmos_mutex_lock(&bcmos_res_lock);
    timer->magic = BCMOS_TIMER_MAGIC_DESTROYED;
    STAILQ_REMOVE(&timer_list, timer, bcmos_timer, list);
    bcmos_mutex_unlock(&bcmos_res_lock);
#endif
}

/* (Re)start timer */
void bcmos_timer_start(bcmos_timer *timer, uint32_t delay)
{
    BUG_ON(!timer);
    if (!BCMOS_TIMER_IS_VALID(timer))
    {
    	BCMOS_TRACE_ERR("Timer is invalid\n");
    	return;
    }
    if ((int32_t)delay < 0)
    {
        BCMOS_TRACE_ERR("Attempt to start timer (%s) for period (%u) longer than 2^31-1. Reduced to 2^31-1\n",
            timer->parm.name ? timer->parm.name : "*unnamed*", delay);
        delay = 0x7fffffff;
    }

    if (BCMOS_TIMER_IS_RUNNING(timer) || BCMOS_TIMER_IS_EXPIRED(timer))
    {
        _bcmos_timer_stop(timer);
    }
    _bcmos_timer_pool_insert(timer, delay, BCMOS_TRUE);
}

/* Stop timer if running */
void bcmos_timer_stop(bcmos_timer *timer)
{
    BUG_ON(!timer);
    _bcmos_timer_stop(timer);
}

/** Set timer handler */
bcmos_errno bcmos_timer_handler_set(bcmos_timer *timer, F_bcmos_timer_handler handler, long data)
{
    BUG_ON(!timer);
    BUG_ON(!handler);
    timer->parm.handler = handler;
    timer->parm.data = data;
    if (timer->parm.owner == BCMOS_MODULE_ID_NONE)
        timer->handler = handler;
    return BCM_ERR_OK;
}

#ifdef BCMOS_TIMER_DEBUG
/* Query timer info */
bcmos_errno bcmos_timer_query(const bcmos_timer *timer, bcmos_timer_parm *parm)
{
    if (timer == NULL || timer->magic != BCMOS_TIMER_MAGIC || parm == NULL)
    {
        return BCM_ERR_PARM;
    }
    *parm = timer->parm;
    return BCM_ERR_OK;
}

/** Timer iterator
 * \param[in] prev      Previous timer. *prev==NULL - get first
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_timer_get_next(bcmos_timer **prev)
{
    bcmos_timer *timer;
    if (prev == NULL)
    {
        return BCM_ERR_PARM;
    }
    timer = *prev;
    if (timer && timer->magic != BCMOS_TIMER_MAGIC)
    {
        return BCM_ERR_PARM;
    }
    if (timer)
    {
        timer = STAILQ_NEXT(timer, list);
    }
    else
    {
        timer = STAILQ_FIRST(&timer_list);
    }
    *prev = timer;
    if (!timer)
    {
        return BCM_ERR_NO_MORE;
    }
    return BCM_ERR_OK;
}
#endif

/*
 * Block memory pool
 */

/* Memory block structure:
 * - bcmos_memblk
 * - blk_size bytes of user data
 * - [magic - for block overflow-corruption check]
 * - [padding to align to pointer size]
 */

struct bcmos_memblk
{
    STAILQ_ENTRY(bcmos_memblk) next; /**< Next block pointer */
    bcmos_blk_pool *pool;       /** pool that owns the block */
#ifdef BCMOS_MEM_CHECK
    uint32_t magic;             /** magic number */
#define BCMOS_MEM_MAGIC_ALLOC   (('m'<<24) | ('b' << 16) | ('l' << 8) | 'k')
#define BCMOS_MEM_MAGIC_FREE    (('m'<<24) | ('b' << 16) | ('l' << 8) | '~')
#define BCMOS_MEM_MAGIC_SUFFIX  (('m'<<24) | ('b' << 16) | ('l' << 8) | 's')
#endif
#ifdef BCMOS_BLK_POOL_DEBUG
    DLIST_ENTRY(bcmos_memblk) list;
    const char *func;        /** function name where the block was allocated/released. */
    int line;                /** line number where the block was allocated/released. */
#endif
};

/* Create byte memory pool */
bcmos_errno bcmos_blk_pool_create(bcmos_blk_pool *pool, const bcmos_blk_pool_parm *parm)
{
    uint32_t blk_size;

    if (!pool || !parm || !parm->blk_size)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "pool %p, parm %p, blk_size=%u, num_blks=%u\n",
            pool, parm, parm ? parm->blk_size : 0, parm ? parm->num_blks : 0);
    }
    if (parm->num_blks & parm->pool_size)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "One and only one of num_blks (%u) and pool_size (%u) must be set\n",
            parm->num_blks, parm->pool_size);
    }
    if (parm->num_blks && parm->start != NULL)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "num_blks!=0 can't be used with start!=NULL. Use byte size instead\n");
    }

    BCM_MEMZERO_STRUCT(pool);
    pool->parm = *parm;

    /* Copy name to make sure that it is not released - in case it was on the stack */
    if (pool->parm.name)
    {
        strncpy(pool->name, pool->parm.name, sizeof(pool->name) - 1);
        pool->parm.name = pool->name;
    }

    /*
     * Calculate total block size in bytes, including overheads
     */
    /* Round up block size to the nearest 32-bit word to make MAGIC check cheaper.
     * It doesn't affect the actual overhead size because of the final
     * rounding up to pointer size.
     */
    pool->parm.blk_size = BCMOS_ROUND_UP(pool->parm.blk_size, sizeof(uint32_t));
    blk_size = pool->parm.blk_size + sizeof(bcmos_memblk);
#ifdef BCMOS_MEM_CHECK
    blk_size += sizeof(uint32_t); /* room for magic after user data block */
#endif
    blk_size = BCMOS_ROUND_UP(blk_size, sizeof(void *));

    /* Derive num_blks / pool_size from one another */
    if (pool->parm.num_blks)
    {
        pool->parm.pool_size = parm->num_blks * blk_size;
    }
    else
    {
        pool->parm.num_blks = pool->parm.pool_size / blk_size;
        if (!pool->parm.num_blks)
        {
            BCMOS_TRACE_RETURN(BCM_ERR_PARM, "pool_size (%u) is too small\n", parm->pool_size);
        }
    }

    /* Allocate memory for the pool if "start" is not set */
    pool->start = pool->parm.start;
    if (!pool->start)
    {
        pool->start = bcmos_alloc(pool->parm.pool_size);
        if (!pool->start)
        {
            BCMOS_TRACE_RETURN(BCM_ERR_NOMEM, "Can't allocate memory for block pool %s\n", parm->name);
        }
    }

    bcmos_fastlock_init(&pool->lock, parm->flags);

    /* Put all blocks on free list */
    bcmos_blk_pool_reset(pool);

    pool->magic = BCMOS_BLK_POOL_VALID;
    if (!(pool->parm.flags & BCMOS_BLK_POOL_FLAG_MSG_POOL))
    {
        bcmos_mutex_lock(&bcmos_res_lock);
        STAILQ_INSERT_TAIL(&blk_pool_list, pool, list);
        bcmos_total_blk_pool_size += pool->parm.pool_size;
        bcmos_mutex_unlock(&bcmos_res_lock);
    }

    return BCM_ERR_OK;
}

/* Destroy memory pool */
bcmos_errno bcmos_blk_pool_destroy(bcmos_blk_pool *pool)
{
    if (!pool || pool->magic != BCMOS_BLK_POOL_VALID)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "pool handle is invalid\n");
    }
    if (pool->stat.free < pool->parm.num_blks)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_STATE, "%i blocks are still allocated from the pool %s\n",
            pool->parm.num_blks - pool->stat.free, pool->parm.name);
    }
    if (!(pool->parm.flags & BCMOS_BLK_POOL_FLAG_MSG_POOL))
    {
        bcmos_mutex_lock(&bcmos_res_lock);
        STAILQ_REMOVE(&blk_pool_list, pool, bcmos_blk_pool, list);
        bcmos_total_blk_pool_size -= pool->parm.pool_size;
        bcmos_mutex_unlock(&bcmos_res_lock);
    }
    if (!pool->parm.start && pool->start)
    {
        bcmos_free(pool->start);
    }
    pool->magic = BCMOS_BLK_POOL_DELETED;
    return BCM_ERR_OK;
}

/** Release all blocks in memory pool . Block content is not affected */
void bcmos_blk_pool_reset(bcmos_blk_pool *pool)
{
    uint32_t blk_size;
    bcmos_memblk *blk;
    uint32_t i;

    STAILQ_INIT(&pool->free_list);
#ifdef BCMOS_BLK_POOL_DEBUG
    DLIST_INIT(&pool->allocated_list);
#endif

    blk_size = pool->parm.blk_size + sizeof(bcmos_memblk);
#ifdef BCMOS_MEM_CHECK
    blk_size += sizeof(uint32_t); /* room for magic after user data block */
#endif
    blk_size = BCMOS_ROUND_UP(blk_size, sizeof(void *));

    /* Put all blocks on free list */
    blk = (bcmos_memblk *)pool->start;
    for (i = 0; i < pool->parm.num_blks; i++)
    {
        blk->pool = pool;
        STAILQ_INSERT_TAIL(&pool->free_list, blk, next);
#ifdef BCMOS_MEM_CHECK
        *(uint32_t *)((long)blk + sizeof(bcmos_memblk) + pool->parm.blk_size) = BCMOS_MEM_MAGIC_SUFFIX;
        blk->magic = BCMOS_MEM_MAGIC_FREE;
#endif
#ifdef BCMOS_BLK_POOL_DEBUG
        blk->line = 0;
        blk->func = NULL;
#endif
        blk = (bcmos_memblk *)((long)blk + blk_size);
    }

    /* Init statistics */
    memset(&pool->stat, 0, sizeof(pool->stat));
    pool->stat.free = pool->parm.num_blks;
}

/* Allocate block from block memory pool */
#ifdef BCMOS_BLK_POOL_DEBUG
void *bcmos_blk_pool_alloc_func(bcmos_blk_pool *pool, const char *func, int line)
#else
void *bcmos_blk_pool_alloc(bcmos_blk_pool *pool)
#endif
{
    bcmos_memblk *blk;
    long flags;

#ifdef BCMOS_MEM_CHECK
    BUG_ON(!pool);
    BUG_ON(pool->magic != BCMOS_BLK_POOL_VALID);
#endif
    flags = bcmos_fastlock_lock(&pool->lock);
    blk = STAILQ_FIRST(&pool->free_list);
    if (blk)
    {
        STAILQ_REMOVE_HEAD(&pool->free_list, next);
        ++pool->stat.allocated;
#ifdef BCMOS_MEM_CHECK
        blk->magic = BCMOS_MEM_MAGIC_ALLOC;
#endif
#ifdef BCMOS_BLK_POOL_DEBUG
        DLIST_INSERT_HEAD(&pool->allocated_list, blk, list);
        blk->func = func;
        blk->line = line;
#endif
        bcmos_fastlock_unlock(&pool->lock, flags);
        return (void *)(blk + 1);
    }

    /* No memory */
    ++pool->stat.alloc_failed;
    bcmos_fastlock_unlock(&pool->lock, flags);
    return NULL;
}

/* Allocate block from block memory pool and zero the block */
#ifdef BCMOS_BLK_POOL_DEBUG
void *bcmos_blk_pool_calloc_func(bcmos_blk_pool *pool, const char *func, int line)
{
    void *ptr = bcmos_blk_pool_alloc_func(pool, func, line);
    if (ptr)
    {
        memset(ptr, 0, pool->parm.blk_size);
    }
    return ptr;
}
#else
void *bcmos_blk_pool_calloc(bcmos_blk_pool *pool)
{
    void *ptr = bcmos_blk_pool_alloc(pool);
    if (ptr)
    {
        memset(ptr, 0, pool->parm.blk_size);
    }
    return ptr;
}
#endif

/* Release memory allocated using bcmos_pool_byte_alloc() or bcmos_pool_blk_alloc() */
#ifdef BCMOS_BLK_POOL_DEBUG
void bcmos_blk_pool_free_func(void *ptr, const char *func, int line)
#else
void bcmos_blk_pool_free(void *ptr)
#endif
{
    bcmos_memblk *blk;
    bcmos_blk_pool *pool;
    long flags;

    blk = (bcmos_memblk *)((long)ptr - sizeof(bcmos_memblk));
    pool = blk->pool;
#ifdef BCMOS_MEM_CHECK
    BUG_ON(pool == NULL);
#ifdef BCM_SUBSYSTEM_EMBEDDED
    BUG_ON_PRINT(pool->magic != BCMOS_BLK_POOL_VALID, "BUG in %s %d! BLOCK name='%s' pool magic=%u\n", __FUNCTION__, __LINE__, pool->parm.name, pool->magic);
#endif
    if (blk->magic != BCMOS_MEM_MAGIC_ALLOC)
    {
#ifdef BCMOS_BLK_POOL_DEBUG
        BCMOS_TRACE_ERR("bad magic 0x%08x instead of 0x%08x free=0x%08x. ptr=%p %s:%d prev %s:%d\n",
            blk->magic, BCMOS_MEM_MAGIC_ALLOC, BCMOS_MEM_MAGIC_FREE,
            ptr, func, line, blk->func, blk->line);
#else
        BCMOS_TRACE_ERR("bad magic 0x%08x instead of 0x%08x free=0x%08x. ptr=%p\n",
            blk->magic, BCMOS_MEM_MAGIC_ALLOC, BCMOS_MEM_MAGIC_FREE, ptr);
#endif
        BUG();
    }
    if (*(uint32_t *)((long)ptr + pool->parm.blk_size) != BCMOS_MEM_MAGIC_SUFFIX)
    {
#ifdef BCMOS_BLK_POOL_DEBUG
        BCMOS_TRACE_ERR("tail corruption. magic 0x%08x. ptr=%p %s:%d allocated in %s:%d\n",
            blk->magic, ptr, func, line, blk->func, blk->line);
#else
        BCMOS_TRACE_ERR("tail corruption. magic 0x%08x. ptr=%p\n", blk->magic, ptr);
#endif
        BUG();
    }
    blk->magic = BCMOS_MEM_MAGIC_FREE;
#endif
    flags = bcmos_fastlock_lock(&pool->lock);
    STAILQ_INSERT_HEAD(&pool->free_list, blk, next);
    ++pool->stat.released;
#ifdef BCMOS_BLK_POOL_DEBUG
    DLIST_REMOVE(blk, list);
    blk->func = func;
    blk->line = line;
#endif
    bcmos_fastlock_unlock(&pool->lock, flags);
}

/* Get pool info */
bcmos_errno bcmos_blk_pool_query(const bcmos_blk_pool *pool, bcmos_blk_pool_info *info)
{
    if (!pool || !info)
    {
        return BCM_ERR_PARM;
    }
    info->parm = pool->parm;
    info->stat = pool->stat;
    info->stat.free = pool->parm.num_blks - (info->stat.allocated - info->stat.released);
    return BCM_ERR_OK;
}

/* Block pool iterator */
bcmos_errno bcmos_blk_pool_get_next(const bcmos_blk_pool **prev)
{
    const bcmos_blk_pool *pool;

    if (prev == NULL)
    {
        return BCM_ERR_PARM;
    }
    pool = *prev;
    if (pool && pool->magic != BCMOS_BLK_POOL_VALID)
    {
        return BCM_ERR_PARM;
    }
    if (pool)
    {
        pool = STAILQ_NEXT(pool, list);
    }
    else
    {
        pool = STAILQ_FIRST(&blk_pool_list);
    }
    *prev = pool;
    if (!pool)
    {
        return BCM_ERR_NO_MORE;
    }
    return BCM_ERR_OK;
}

#ifdef BCMOS_BLK_POOL_DEBUG
bcmos_errno bcmos_blk_pool_allocated_blk_get_next(const bcmos_blk_pool *pool, const bcmos_memblk **prev, const char **func, int *line)
{
    const bcmos_memblk *blk;

    if (!pool || !prev)
    {
        return BCM_ERR_PARM;
    }
    blk = *prev;
    if (blk)
    {
        blk = DLIST_NEXT(blk, list);
    }
    else
    {
        blk = DLIST_FIRST(&pool->allocated_list);
    }
    *prev = blk;
    if (!blk)
    {
        return BCM_ERR_NO_MORE;
    }
    *func = blk->func;
    *line = blk->line;
    return BCM_ERR_OK;
}
#endif

/*
 * Message pool
 */

/* release message callback */
static void _bcmos_msg_pool_release(bcmos_msg *msg)
{
    if (msg->data_release)
        msg->data_release(msg);
    bcmos_blk_pool_free(msg);
}

/* Create message pool */
bcmos_errno bcmos_msg_pool_create(bcmos_msg_pool *pool, const bcmos_msg_pool_parm *parm)
{
    bcmos_blk_pool_parm pool_parm = {};
    bcmos_memblk *blk;
    bcmos_errno err;

    if (!pool || !parm || !parm->size)
    {
        return BCM_ERR_PARM;
    }
    BCM_MEMZERO_STRUCT(pool);
    pool->parm = *parm;
    pool_parm.num_blks = parm->size;
    pool_parm.blk_size = parm->data_size + sizeof(bcmos_msg);
    pool_parm.flags = parm->flags | BCMOS_BLK_POOL_FLAG_MSG_POOL;
    pool_parm.name = parm->name;

    /* Create underlying block pool */
    err = bcmos_blk_pool_create(&pool->blk_pool, &pool_parm);
    if (err)
    {
        return err;
    }
    pool->parm.name = pool->blk_pool.name;

    /* Pre-initialize all messages */
    STAILQ_FOREACH(blk, &pool->blk_pool.free_list, next)
    {
        bcmos_msg *msg = (bcmos_msg *)(blk + 1);
        msg->data = (void *)(msg + 1);
        msg->size = pool->parm.data_size;
        msg->release = _bcmos_msg_pool_release;
        msg->data_release = parm->data_release;
    }
    bcmos_mutex_lock(&bcmos_res_lock);
    STAILQ_INSERT_TAIL(&msg_pool_list, &pool->blk_pool, list);
    bcmos_total_msg_pool_size += pool->blk_pool.parm.pool_size;
    bcmos_mutex_unlock(&bcmos_res_lock);

    return BCM_ERR_OK;
}

/** Destroy message pool */
bcmos_errno bcmos_msg_pool_destroy(bcmos_msg_pool *pool)
{
    bcmos_errno rc;

    rc = bcmos_blk_pool_destroy(&pool->blk_pool);
    if (rc)
        return rc;

    bcmos_mutex_lock(&bcmos_res_lock);
    STAILQ_REMOVE(&msg_pool_list, &pool->blk_pool, bcmos_blk_pool, list);
    bcmos_total_msg_pool_size -= pool->blk_pool.parm.pool_size;
    bcmos_mutex_unlock(&bcmos_res_lock);

    pool->parm.size = pool->parm.data_size = 0;
    return BCM_ERR_OK;
}

/* Allocate message from pool */
#ifdef BCMOS_BLK_POOL_DEBUG
bcmos_msg *bcmos_msg_pool_alloc_func(bcmos_msg_pool *pool, const char *func, int line)
{
    return bcmos_blk_pool_alloc_func(&pool->blk_pool, func, line);
}
#else
bcmos_msg *bcmos_msg_pool_alloc(bcmos_msg_pool *pool)
{
    return bcmos_blk_pool_alloc(&pool->blk_pool);
}
#endif

/* Get pool info */
bcmos_errno bcmos_msg_pool_query(const bcmos_msg_pool *pool, bcmos_msg_pool_info *info)
{
    bcmos_blk_pool_info pool_info;
    bcmos_errno err;

    if (!pool || !info)
    {
        return BCM_ERR_PARM;
    }
    err = bcmos_blk_pool_query(&pool->blk_pool, &pool_info);
    if (err)
    {
        return err;
    }
    info->parm = pool->parm;
    info->stat = pool_info.stat;
    return BCM_ERR_OK;
}

/* Block pool iterator */
bcmos_errno bcmos_msg_pool_get_next(const bcmos_msg_pool **prev)
{
    const bcmos_msg_pool *pool;

    if (prev == NULL)
    {
        return BCM_ERR_PARM;
    }
    pool = *prev;
    if (pool && pool->blk_pool.magic != BCMOS_BLK_POOL_VALID)
    {
        return BCM_ERR_PARM;
    }
    if (pool)
    {
        pool = container_of(STAILQ_NEXT(&pool->blk_pool, list), bcmos_msg_pool, blk_pool);
    }
    else
    {
        pool = container_of(STAILQ_FIRST(&msg_pool_list), bcmos_msg_pool, blk_pool);
    }
    *prev = pool;
    if (!pool)
    {
        return BCM_ERR_NO_MORE;
    }
    return BCM_ERR_OK;
}

/** Lock all dynamic memory allocations. Any attempt to allocate memory from the heap after this is called will cause
 * an error. This includes bcmos_alloc, bcmos_block_pool_create, etc.
 *
 * For embedded applications, runtime dynamic memory allocation is generally undesirable, so this should be called
 * after system initialization.
 */
void bcmos_dynamic_memory_allocation_block(uint32_t allocation_block_size_threshold)
{
#ifndef ASPEN_VLSI_SIM
    bcmos_dynamic_memory_allocation_blocked = BCMOS_TRUE;
#endif
    bcmos_dynamic_memory_allocation_block_size_threshold = allocation_block_size_threshold;
}

void bcmos_dynamic_memory_allocation_unblock(void)
{
#ifndef ASPEN_VLSI_SIM
    bcmos_dynamic_memory_allocation_blocked = BCMOS_FALSE;
#endif
}

void bcmos_dynamic_memory_allocation_blocking_suspend(void)
{
    bcmos_mutex_lock(&dynamic_mem_alloc_suspend_mutex);
    dynamic_alloc_suspend_usage_count++;
    bcmos_mutex_unlock(&dynamic_mem_alloc_suspend_mutex);
}

void bcmos_dynamic_memory_allocation_blocking_resume(void)
{
    bcmos_mutex_lock(&dynamic_mem_alloc_suspend_mutex);

    if (dynamic_alloc_suspend_usage_count > 0)
        dynamic_alloc_suspend_usage_count--;
    else
        BCMOS_TRACE_ERR("Dynamic memory allocation blocking is already resumed\n");

    bcmos_mutex_unlock(&dynamic_mem_alloc_suspend_mutex);
}

void bcmos_dynamic_memory_allocation_block_check(uint32_t size)
{
    if (bcmos_dynamic_memory_allocation_blocked
        && size < bcmos_dynamic_memory_allocation_block_size_threshold
        && !dynamic_alloc_suspend_usage_count)
    {
        BCMOS_TRACE_ERR("dynamic memory allocation requested at runtime\n");
    }
}

/** Set up print redirection/cloning
 * \param[in]   mode    redirection/cloning mode
 * \param[in]   cb      redirection callback
 * \param[in]   data    opaque data to be passed to cb
 */
bcmos_errno bcmos_print_redirect(bcmos_print_redirect_mode mode, bcmos_print_redirect_cb cb, void *data)
{
    if (mode != BCMOS_PRINT_REDIRECT_MODE_NONE && cb == NULL)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Redirection callback must be set\n");
    }
    print_redirect_mode = mode;
    if (mode == BCMOS_PRINT_REDIRECT_MODE_NONE)
    {
        print_redirect_cb = NULL;
        print_redirect_cb_data = NULL;
    }
    else
    {
        print_redirect_cb = cb;
        print_redirect_cb_data = data;
    }
    return BCM_ERR_OK;
}

/* Print on the console with optional cloning / redirection */
/*lint -e{454}*/
int bcmos_vprintf(const char *format, va_list ap)
{
    int rc = 0;
    bcmos_bool protected_section = is_irq_mode() || is_irq_disabled() || !bcmos_initialized;

    /* Only protect if in task context */
    if (!protected_section)
    {
        bcmos_mutex_lock(&bcmos_print_lock);
    }
    if (print_redirect_mode != BCMOS_PRINT_REDIRECT_MODE_REDIRECT)
    {
        rc = bcmos_sys_vprintf(format, ap);
    }
    if (print_redirect_mode != BCMOS_PRINT_REDIRECT_MODE_NONE)
    {
        rc = print_redirect_cb(print_redirect_cb_data, format, ap);
    }
    if (!protected_section)
    {
        bcmos_mutex_unlock(&bcmos_print_lock);
    }

    return rc;
}
/*lint -e{454}*/

/* Print on the console with optional cloning / redirection */
int bcmos_printf(const char *format, ...)
{
    va_list args;
    int rc;

    va_start(args, format);
    rc = bcmos_vprintf(format, args);
    va_end(args);
    return rc;
}

#ifndef BCMOS_PUTCHAR_INLINE
/*lint -e{454}*/
void bcmos_putchar(int c)
{
    bcmos_bool protected_section = is_irq_mode() || is_irq_disabled() || !bcmos_initialized;

    /* Only protect if in task context */
    if (!protected_section)
    {
        bcmos_mutex_lock(&bcmos_print_lock);
    }
    putchar(c);
    fflush(stdout);
    if (!protected_section)
    {
        bcmos_mutex_unlock(&bcmos_print_lock);
    }
}
/*lint +e{454}*/
#endif

#ifndef BCMOS_BUF_OS_SPECIFIC

/*
 * Buffer allocation/release
 */

#ifdef BCMOS_BUF_POOL_SIZE
/* Create buffer pool */
static bcmos_errno bcmos_buf_pool_create(uint32_t pool_size, uint32_t blk_size, bcmos_blk_pool *blk_pool)
{
    char pool_name[32];
    bcmos_blk_pool_parm pool_parm = {};
    bcmos_errno rc;

    snprintf(pool_name, sizeof(pool_name) - 1, "sysbuf_%u", blk_size);
    pool_parm.name = pool_name;

    /* If buffer memory should be allocated by bcmos_dma_alloc - allocate
     * memory for the whole pool here */
    pool_parm.blk_size = blk_size + sizeof(bcmos_buf) + BCMTR_BUF_EXTRA_HEADROOM +
        2*BCMOS_BUF_DATA_ALIGNMENT + BCMOS_BUF_DATA_GUARD;

#ifdef BCMOS_BUF_IN_DMA_MEM
    pool_parm.pool_size = (pool_parm.blk_size + sizeof(bcmos_memblk)) * pool_size;
    pool_parm.start = bcmos_dma_alloc(0, pool_parm.pool_size, NULL);
    if (!pool_parm.start)
        return BCM_ERR_NOMEM;
#else
    pool_parm.num_blks = pool_size;
#endif

    rc = bcmos_blk_pool_create(blk_pool, &pool_parm);
    if (rc)
    {
#ifdef BCMOS_BUF_IN_DMA_MEM
        if (pool_parm.start)
            bcmos_dma_free(0, pool_parm.start);
#endif
    }

    return rc;
}
#endif

/* Allocate buffer */
bcmos_buf *__attribute__((weak)) bcmos_buf_alloc(uint32_t size)
{
    /* Allocate extra 2 * BCMOS_BUF_DATA_ALIGNMENT to make sure that neither data start nor end
     * end up in the middle of cache line
     */
    bcmos_buf *buf;

/* Allocate from the pool  */
#ifdef BCMOS_BUF_POOL_SIZE
    bcmos_blk_pool *pool = &sys_buf_pool;
    if (size > BCMOS_BUF_POOL_BUF_SIZE)
    {
#ifdef BCMOS_BIG_BUF_POOL_SIZE
        if (size <= BCMOS_BIG_BUF_POOL_BUF_SIZE)
        {
            /* size is to big for "normal" buffer pool, but not too big for "big buffer" pool */
            pool = &sys_big_buf_pool;
        }
        else
#endif
            pool = NULL;
    }
    if (pool != NULL)
        buf = bcmos_blk_pool_alloc(pool);
    else
#endif /* #ifdef BCMOS_BUF_POOL_SIZE */
    {
        /* Allocate from the heap */
        uint32_t alloc_size = sizeof(bcmos_buf) + size + BCMTR_BUF_EXTRA_HEADROOM +
            2 * BCMOS_BUF_DATA_ALIGNMENT - 1 + BCMOS_BUF_DATA_GUARD;
#ifdef BCMOS_BUF_DATA_UNIT_SIZE
#if BCMOS_BUF_DATA_UNIT_SIZE & (BCMOS_BUF_DATA_UNIT_SIZE - 1)
#error BCMOS_BUF_DATA_UNIT_SIZE must be a power of 2
#endif
        alloc_size = BCMOS_ROUND_UP(alloc_size, BCMOS_BUF_DATA_UNIT_SIZE);
#endif
#ifdef BCMOS_BUF_IN_DMA_MEM
        buf = bcmos_dma_alloc(0, alloc_size, NULL);
#else
        buf = bcmos_alloc(alloc_size);
#endif
    }

    if (!buf)
        return NULL;
    buf->start = (uint8_t *)(buf + 1) + BCMOS_BUF_DATA_GUARD;
    buf->data = (uint8_t *)(BCMOS_ROUND_UP((long)buf->start + BCMTR_BUF_EXTRA_HEADROOM, BCMOS_BUF_DATA_ALIGNMENT));
    buf->size = size + (buf->data - buf->start);
    buf->len = 0;
#ifdef BCMOS_BUF_POOL_SIZE
    buf->pool = pool;
#else
    buf->pool = NULL;
#endif
    return buf;
}

/* Release buffer */
void __attribute__((weak)) bcmos_buf_free(bcmos_buf *buf)
{
#ifdef BCMOS_BUF_POOL_SIZE
    /* Buffer might have been allocated from the system pool */
    if (buf->pool)
    {
        bcmos_blk_pool_free(buf);
        return;
    }
#endif

#ifdef BCMOS_BUF_IN_DMA_MEM
    bcmos_dma_free(0, buf);
#else
    bcmos_free(buf);
#endif
}

/* Clone transport buffer */
bcmos_buf *bcmos_buf_clone(bcmos_buf *buf)
{
    uint32_t len = bcmos_buf_length(buf);
    bcmos_buf *clone = bcmos_buf_alloc(len);
    if (!clone)
        return NULL;
    memcpy(bcmos_buf_data(clone), bcmos_buf_data(buf), len);
    bcmos_buf_length_set(clone, len);
    bcmos_buf_channel_set(clone, bcmos_buf_channel(buf));
    return clone;
}

#endif

/* Compile flag to control which platforms healthcheck is run on */
#ifdef BCMOS_HEALTH_CHECK_ENABLED

/* Define healthcheck information */
#define BCMOS_HC_DEBUG 0
#if BCMOS_HC_DEBUG
#define BCMOS_HEALTHCHECK_MODULE_PERIOD 10000000 /* timer delay 10 seconds * 1000000 usecs/sec */
#else
#define BCMOS_HEALTHCHECK_MODULE_PERIOD 60000000 /* timer delay 1 minute = 60 seconds * 1000000 usecs/sec */
#endif

typedef struct
{
    uint64_t last_timestamp;
    bcmos_bool was_created;
} healthcheck_info;

/* health check data store */
static healthcheck_info module_health[BCMOS_MODULE_ID__NUM_OF];

/* keep track of whether module health array has been initialized */
static bcmos_bool hc_init = BCMOS_FALSE;

/* Define a health check timer for each module */
#define SIZE_OF_HC_TMR_STR 20
#define MAX_LENGTH_TMR_NAME (BCMOS_MAX_NAME_LENGTH + SIZE_OF_HC_TMR_STR + 1)
typedef struct
{
    char timer_name[MAX_LENGTH_TMR_NAME];
    bcmos_timer healthcheck_timer;
} timer_info;

static timer_info hc_timer_info[BCMOS_MODULE_ID__NUM_OF];

/* define healthcheck info data accessors */
static void healthcheck_was_created_set(bcmos_module_id module_id)
{
    module_health[module_id].was_created = BCMOS_TRUE;
}

static bcmos_bool healthcheck_was_created_get(bcmos_module_id module_id)
{
    return module_health[module_id].was_created;
}

static void healthcheck_last_timestamp_set(bcmos_module_id module_id)
{
    bcmos_mutex_lock(&health_check_data_mutex);
    module_health[module_id].last_timestamp = bcmos_timestamp64();
    bcmos_mutex_unlock(&health_check_data_mutex);
}

static uint64_t healthcheck_last_timestamp_get(bcmos_module_id module_id)
{
    uint64_t timestamp = 0;

    bcmos_mutex_lock(&health_check_data_mutex);
    timestamp = module_health[module_id].last_timestamp;
    bcmos_mutex_unlock(&health_check_data_mutex);

    return timestamp;
}

/**
 * Function that returns whether a module is healthy. That is,
 * has it responded to health check timer expiry messages by
 * updating the last timestamp?
 *
 * @param period    Time in microseconds since last query.
 * @param module_id ID of module of interest
 *
 * @return True if healthy. False if not.
 */
bcmos_bool bcmos_module_is_healthy(uint32_t period, bcmos_module_id module_id)
{
    bcmos_bool healthy = BCMOS_TRUE;
    uint64_t now = bcmos_timestamp64();

    /* use accessors */
    uint64_t last_ts = healthcheck_last_timestamp_get(module_id);
    bcmos_bool was_created = healthcheck_was_created_get(module_id);

    if (was_created)
    {
        uint64_t time_since_last_ts = now - last_ts;
        if (time_since_last_ts > period)
        {
            healthy = BCMOS_FALSE;
            BCMOS_TRACE(BCMOS_TRACE_LEVEL_ERROR, "Healthcheck failure time_since_last_ts[%lu] = current_ts[%lu] - last_ts[%lu] > periodic[%lu] \n",
                        time_since_last_ts, now, last_ts, period);
        }
    }

    return healthy;
}

void healthcheck_print(bcmos_module_id module_id)
{
    bcmos_printf("\n");
    bcmos_printf("Module ID | Created | Last Timestamp\n");

    if (module_id == BCMOS_MODULE_ID__NUM_OF)
    {
        for (bcmos_module_id i = BCMOS_MODULE_ID_NONE; i < BCMOS_MODULE_ID__NUM_OF; i++)
        {
            bcmos_bool was_created = healthcheck_was_created_get(i);
            uint64_t last_ts = healthcheck_last_timestamp_get(i);
            if (last_ts != 0)
            {
                bcmos_printf("   %3d    | %7s | %14llu\n", i, (was_created) ? "yes" : "no", last_ts);
            }
        }
    }
    else
    {
        bcmos_printf("   %3d    | %7s | %14llu\n",
            module_id, (healthcheck_was_created_get(module_id)) ? "yes" : "no", healthcheck_last_timestamp_get(module_id));
    }
}

static bcmos_timer_rc bcmos_healthcheck_timer_expiry_handler (bcmos_timer * wdtimer, long data)
{
    /* update timestamp */
    bcmos_module_id module_id = wdtimer->parm.owner;
    healthcheck_last_timestamp_set(module_id);

    return BCMOS_TIMER_OK;
}

bcmos_errno bcmos_module_health_check_init(const bcmos_module* module)
{
    bcmos_errno rc = BCM_ERR_OK;
    bcmos_module_id module_id = module->id;
    char health_check_str[SIZE_OF_HC_TMR_STR] = "health_check_timer";

    /* initalize timer info array and timer name */
    /* use snprintf for safety */
    snprintf(hc_timer_info[module_id].timer_name, MAX_LENGTH_TMR_NAME, "%s%s", module->name, health_check_str);
    bcmos_timer_parm wd_timerparms =
    {
        .name     = hc_timer_info[module_id].timer_name,
        .owner    = module_id,
        .periodic = BCMOS_TRUE, /* repeat */
        .handler  = bcmos_healthcheck_timer_expiry_handler,
        .flags    = BCMOS_TIMER_PARM_FLAGS_NON_URGENT
    };

    /* Check that modules data store has already been initialized */
    if (hc_init == BCMOS_FALSE)
    {
        bcmos_printf("Health Check has not yet been properly initialized\n");
        return BCM_ERR_INTERNAL;
    }
    /* do not do a health check of device_mgmt */
    if (module_id == BCMOS_MODULE_ID_DEVICE_MGMT)
    {
        return rc;
    }

    /* initialize */
    healthcheck_last_timestamp_set(module_id);
    healthcheck_was_created_set(module_id);

    /* create and start the timer */
    rc = bcmos_timer_create(&hc_timer_info[module_id].healthcheck_timer, &wd_timerparms);

    if (!rc)
    {
        bcmos_timer_start(&hc_timer_info[module_id].healthcheck_timer, BCMOS_HEALTHCHECK_MODULE_PERIOD);
    }

    return rc;
}

bcmos_errno bcmos_module_health_check_destroy(bcmos_module_id module_id)
{
    bcmos_timer_destroy(&hc_timer_info[module_id].healthcheck_timer);
    return BCM_ERR_OK;
}

bcmos_errno bcmos_modules_healthcheck_init(void)
{
    /* initialize data store and timer info */
    memset(&module_health, 0, sizeof(module_health));
    memset(&hc_timer_info, 0, sizeof(hc_timer_info));
    hc_init = BCMOS_TRUE;

    return BCM_ERR_OK;
}
#endif

/* Copy string.
   The copy is allocated using bcmos_alloc() and should be released using bcmos_free()
*/
char *bcmos_strdup(const char *s)
{
    char *copy = (s != NULL) ? (char *)bcmos_alloc(strlen(s) + 1) : NULL;
    if (copy != NULL )
        strcpy(copy, s);
    return copy;
}

bcmos_oops_complete_cb_t bcmos_oops_complete_cb;

EXPORT_SYMBOL(bcmos_init);

EXPORT_SYMBOL(bcmos_msg_queue_create);
EXPORT_SYMBOL(bcmos_msg_queue_destroy);
EXPORT_SYMBOL(bcmos_msg_queue_query);
EXPORT_SYMBOL(bcmos_msg_queue_get_next);
EXPORT_SYMBOL(bcmos_msg_send);
EXPORT_SYMBOL(bcmos_msg_send_to_module);
EXPORT_SYMBOL(bcmos_msg_recv);
EXPORT_SYMBOL(bcmos_msg_register);
EXPORT_SYMBOL(bcmos_msg_unregister);
EXPORT_SYMBOL(bcmos_msg_dispatch);

EXPORT_SYMBOL(bcmos_msg_qgroup_create);
EXPORT_SYMBOL(bcmos_msg_qgroup_destroy);
EXPORT_SYMBOL(bcmos_msg_qgroup_query);
EXPORT_SYMBOL(bcmos_msg_recv_from_qgroup);
EXPORT_SYMBOL(bcmos_msg_send_to_qgroup);

EXPORT_SYMBOL(bcmos_task_timeout_set);
EXPORT_SYMBOL(bcmos_task_get_next);

EXPORT_SYMBOL(bcmos_module_create);
EXPORT_SYMBOL(bcmos_module_destroy);
EXPORT_SYMBOL(bcmos_module_current);
EXPORT_SYMBOL(bcmos_module_context);
EXPORT_SYMBOL(bcmos_module_context_set);
EXPORT_SYMBOL(bcmos_module_query);

EXPORT_SYMBOL(bcmos_event_create);
EXPORT_SYMBOL(bcmos_event_destroy);
EXPORT_SYMBOL(bcmos_event_raise);
EXPORT_SYMBOL(bcmos_event_recv);

EXPORT_SYMBOL(bcmos_timer_create);
EXPORT_SYMBOL(bcmos_timer_destroy);
EXPORT_SYMBOL(bcmos_timer_start);
EXPORT_SYMBOL(bcmos_timer_stop);
EXPORT_SYMBOL(bcmos_timer_handler_set);
#ifdef BCMOS_TIMER_DEBUG
EXPORT_SYMBOL(bcmos_timer_query);
EXPORT_SYMBOL(bcmos_timer_get_next);
#endif

EXPORT_SYMBOL(bcmos_blk_pool_create);
EXPORT_SYMBOL(bcmos_blk_pool_destroy);
EXPORT_SYMBOL(bcmos_blk_pool_reset);
#ifdef BCMOS_BLK_POOL_DEBUG
EXPORT_SYMBOL(bcmos_blk_pool_alloc_func);
EXPORT_SYMBOL(bcmos_blk_pool_calloc_func);
#else
EXPORT_SYMBOL(bcmos_blk_pool_alloc);
EXPORT_SYMBOL(bcmos_blk_pool_calloc);
#endif
EXPORT_SYMBOL(bcmos_blk_pool_free);
EXPORT_SYMBOL(bcmos_blk_pool_query);
EXPORT_SYMBOL(bcmos_blk_pool_get_next);
#ifdef BCMOS_BLK_POOL_DEBUG
EXPORT_SYMBOL(bcmos_blk_pool_allocated_blk_get_next);
#endif

EXPORT_SYMBOL(bcmos_msg_pool_create);
#ifdef BCMOS_BLK_POOL_DEBUG
EXPORT_SYMBOL(bcmos_msg_pool_alloc_func);
#else
EXPORT_SYMBOL(bcmos_msg_pool_alloc);
#endif
EXPORT_SYMBOL(bcmos_msg_pool_query);
EXPORT_SYMBOL(bcmos_msg_pool_destroy);
EXPORT_SYMBOL(bcmos_msg_pool_get_next);

EXPORT_SYMBOL(bcmos_print_redirect);
EXPORT_SYMBOL(bcmos_printf);
EXPORT_SYMBOL(bcmos_vprintf);

#ifndef BCMOS_BUF_OS_SPECIFIC
EXPORT_SYMBOL(bcmos_buf_alloc);
EXPORT_SYMBOL(bcmos_buf_free);
EXPORT_SYMBOL(bcmos_buf_clone);
#endif
EXPORT_SYMBOL(bcmos_oops_complete_cb);

EXPORT_SYMBOL(bcmos_dynamic_memory_allocation_block);
EXPORT_SYMBOL(bcmos_dynamic_memory_allocation_block_check);
EXPORT_SYMBOL(bcmos_strdup);
