/*
<:copyright-BRCM:2016-2019:Apache:standard

 Copyright (c) 2016-2019 Broadcom. All Rights Reserved

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

 *  :>
 */

#ifndef BCMOS_COMMON_H_
#define BCMOS_COMMON_H_

#ifndef BCMOS_SYSTEM_H_
#error Please do not include bcmos_common.h directly. Include bcmos_system.h
#endif

#include "bcmos_errno.h"
#include "bcmos_types.h"
#include "bcmos_queue.h"
#include "bcmos_tree.h"
/* Get constants, such as task, module, event id lists */
#include "bcmos_platform.h"
#include "bcmos_pack.h"
#include "bcmos_sysif.h"
#include "bcmos_endian.h"

#define MAX_TASK_NAME_SIZE          32
#define MAX_MODULE_NAME_SIZE        32
#define MAX_MSG_QUEUE_NAME_SIZE     32
#define MAX_TIMER_NAME_SIZE         32
#define MAX_POOL_NAME_SIZE          32
#define MAX_EVENT_NAME_SIZE         32
#define MAX_MUTEX_NAME_SIZE         32
#define MAX_SEM_NAME_SIZE           32
#define BCMOS_MSG_POOL_DEFAULT_SIZE 512

typedef long long_t;
typedef unsigned long ulong_t;

/* Define bcmos_bool - the boolean type for bcmos - based on C99 standard boolean type */

#ifndef BCMOS_BOOLEAN
#ifdef __cplusplus
typedef bool bcmos_bool;
#define BCMOS_FALSE false
#define BCMOS_TRUE true
#else
typedef _Bool bcmos_bool;
#define BCMOS_FALSE 0
#define BCMOS_TRUE 1
#endif
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define BCM_SIZEOFARRAY(arr) (sizeof(arr) / sizeof(*arr))
#define BCM_SIZEOFFIELD(s, f) (sizeof(((s *)NULL)->f))
#define BCM_MEMZERO_STRUCT(ptr) memset(ptr, 0, sizeof(*(ptr)))
#define BCM_MEMCPY_ARRAY(dst, src) memcpy(dst, src, MIN(sizeof(dst), sizeof(src)))
#define BCM_TAB "  "
#define BCM_TAB2 BCM_TAB BCM_TAB
#define BCM_TAB3 BCM_TAB2 BCM_TAB
#define BCM_TAB4 BCM_TAB2 BCM_TAB2
#define BCM_ALIGN_PTR(ptr, align_size) ((((unsigned long)ptr) + ((align_size) - 1)) & ~((align_size) - 1))

typedef void (*f_bcmolt_sw_error_handler)(uint8_t pon_ni, const char *file_name, uint32_t line_number);

/* Similar to BUG_ON(), with the following features:
 * 1. The condition is checked against BCM_ERR_OK.
 * 2. In case on an error, the macro returns from the calling function with the error code. */
#define BUG_ON_ERR_RET(f) \
    do \
    { \
        bcmos_errno _err; \
        _err = f; \
        BUG_ON(_err != BCM_ERR_OK); \
        return _err; \
    } \
    while (0)

/** \addtogroup system_init
 * @{
 */

/** Initialize system library
 * Must be called before any other system function
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_init(void);

/** Cleanup system library
 */
void bcmos_exit(void);

/** @} system_init */

/** \addtogroup system_mem
 * @{
 */

#ifndef BCMOS_MALLOC_FREE_INLINE

/** \defgroup system_heap Default Heap
 * @{
 */

/** Allocate memory from the main heap
 * \param[in]   size
 * \returns memory block pointer or NULL
 */
#ifndef BCMOS_HEAP_DEBUG
void *bcmos_alloc(uint32_t size);
#else
void *_bcmos_alloc(uint32_t size);
#endif

/** Release memory to the main pool
 * \param[in]   ptr
 */
#ifndef BCMOS_HEAP_DEBUG
void bcmos_free(void *ptr);
#else
void _bcmos_free(void *ptr);
#endif

/** @} system_heap */

#endif /* #ifndef BCMOS_MALLOC_FREE_INLINE */

typedef void (*bcmos_msg_print_cb)(void *context, const char *fmt, ...);
typedef void (*bcmos_hexdump_cb)(bcmos_msg_print_cb print_cb, void *context, const void *buffer, uint32_t offset, uint32_t count, const char *indent);

#ifdef BCMOS_HEAP_DEBUG

/* Heap debugging feature.
 * - Check dynamic memory blocks for corruption
 * - Keep track of where each memory block has been allocated to debug memory leaks
 * Each memory block is "sandwiched" between bcmos_heap_memblk_hdr and 32 bit magic protecting
 * the end of block;
 */

typedef struct bcmos_heap_memblk_hdr bcmos_heap_memblk_hdr;

struct bcmos_heap_memblk_hdr
{
#define BCMOS_HEAP_DEBUG_FNAME_LEN  40
    DLIST_ENTRY(bcmos_heap_memblk_hdr) list;    /**< Block list pointer */
    char fname[BCMOS_HEAP_DEBUG_FNAME_LEN];     /**< Function name */
    uint32_t line;                              /**< Line number */
    uint32_t size;                              /**< Block size */
    uint32_t timestamp;                         /**< Timestamp when the block was allocated/freed */
    bcmos_bool is_init_time;                    /**< Is this initialization time allocation */
    uint32_t magic;                             /**< Start of block magic number */
#define BCMOS_HEAP_DEBUG_ALLOC_MAGIC   ('a'<<24 | 'l'<<16 | 'l'<<8 | 'c')
#define BCMOS_HEAP_DEBUG_FREE_MAGIC    ('f'<<24 | 'r'<<16 | 'e'<<8 | 'e')
};
#define BCMOS_HEAP_DEBUG_OVERHEAD  (sizeof(bcmos_heap_memblk_hdr) + sizeof(uint32_t))

/* Add newly allocated memory block to heap debug list. Returns "user" pointer */
void *bcmos_heap_debug_memblk_add(void *hdr_ptr, uint32_t size, const char *fname, uint32_t line);

/* Check memory block. Returns BCMOS_TRUE if the block is OK */
bcmos_bool bcmos_heap_debug_memblk_check(void *user_ptr);

/* Check memory block before freeing it. Returns BCMOS_TRUE if the block is OK */
bcmos_bool bcmos_heap_debug_memblk_check_and_del(void *user_ptr, const char *fname, uint32_t line);

static inline void *bcmos_heap_debug_hdr_to_user_ptr(bcmos_heap_memblk_hdr *hdr)
{
    if (!hdr)
        return hdr;
    return hdr + 1;
}

static inline bcmos_heap_memblk_hdr *bcmos_heap_user_ptr_to_debug_hdr(void *user_ptr)
{
    if (!user_ptr)
        return (bcmos_heap_memblk_hdr *)NULL;
    return (bcmos_heap_memblk_hdr *)((long)user_ptr - sizeof(bcmos_heap_memblk_hdr));
}

/* Protect heap debug memblk list when traversing it.
 * While heap debug is locked, all memory allocation and free requests will stall
 */
void bcmos_heap_debug_lock(void);
void bcmos_heap_debug_unlock(void);

void *bcmos_heap_debug_memblk_get_next(void *prev);

void bcmos_heap_debug_info_get(uint32_t *num_blocks, uint32_t *total_size);

bcmos_errno bcmos_heap_debug_print(bcmos_msg_print_cb print_cb, bcmos_hexdump_cb hexdump_cb, void *context, bcmos_bool exclude_init_time, uint32_t num_skip, uint32_t num_print,
    uint32_t data_bytes, uint32_t start_ts, uint32_t end_ts, const char *func);

#define bcmos_alloc(size)       bcmos_alloc_debug(size, __FUNCTION__, __LINE__)

#define bcmos_free(ptr)         bcmos_free_debug(ptr, __FUNCTION__, __LINE__)

#define bcmos_calloc(size)      bcmos_calloc_debug(size, __FUNCTION__, __LINE__)

void *bcmos_alloc_debug(uint32_t size, const char *fname, uint32_t line);

void *bcmos_calloc_debug(uint32_t size, const char *fname, uint32_t line);

void bcmos_free_debug(void *ptr, const char *fname, uint32_t line);

/* Used for temporarily disabling the out of memory heap info print. By default it is enabled*/
extern bcmos_bool bcmos_heap_debug_out_of_memory_print_disabled;

/* Mark that initialization is done, in case we want to exclude initialization time allocations. */
extern bcmos_bool bcmos_heap_debug_init_done;

#endif /* #ifdef BCMOS_HEAP_DEBUG */

/* Copy string.
   The copy is allocated using bcmos_alloc() and should be released using bcmos_free()
*/
char *bcmos_strdup(const char *s);

/** \defgroup blk_pool Block Memory Pool
 * \ingroup system_mem
 * @{
 */

/** Block memory pool parameters */
typedef struct
{
    const char *name;   /**< Pool name */
    uint32_t blk_size;  /**< Memory block size > 0 */
    uint32_t num_blks;  /**< Number of blocks in the pool. If not set - it is derived from pool_size */
    void *start;        /**< Start address. Can be NULL */
    uint32_t pool_size; /**< Total pool size in bytes. Only 1 of pool_size, num_blks must be set */
    uint32_t flags;     /**< TBD flags */
#define BCMOS_BLK_POOL_FLAG_MSG_POOL  0x80000000 /* Used by message pool */
} bcmos_blk_pool_parm;

/** Block memory pool statistics */
typedef struct bcmos_blk_pool_stat
{
    uint32_t allocated;     /**< Number of blocks allocated */
    uint32_t released;      /**< Number of blocks released */
    uint32_t free;          /**< Number of free blocks in the pool */
    uint32_t alloc_failed;  /**< Number of allocation failures */
} bcmos_blk_pool_stat;

/** Block memory pool info */
typedef struct bcmos_blk_pool_info
{
    bcmos_blk_pool_parm parm;   /**< Pool parameters */
    bcmos_blk_pool_stat stat;   /**< Pool statistics */
} bcmos_blk_pool_info;

/** Block memory pool control block */
typedef struct bcmos_blk_pool bcmos_blk_pool;

/** Create block memory pool
 * \param[in,out]       pool    pool control block
 * \param[in]           parm    pool parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_blk_pool_create(bcmos_blk_pool *pool, const bcmos_blk_pool_parm *parm);

/** Destroy block memory pool
 * \param[in]   pool    pool handle
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_blk_pool_destroy(bcmos_blk_pool *pool);

/** Allocate block from block memory pool
 *
 * This allocates a single unit (unit_size bytes)
 * \param[in]   pool    Pool handle
 * \return memory block pointer or NULL.
 * It is guaranteed that the returned pointer is aligned to pointer size
 */
#ifdef BCMOS_BLK_POOL_DEBUG
void *bcmos_blk_pool_alloc_func(bcmos_blk_pool *pool, const char *func, int line);
#define bcmos_blk_pool_alloc(pool) bcmos_blk_pool_alloc_func(pool, __FUNCTION__, __LINE__)
#else
void *bcmos_blk_pool_alloc(bcmos_blk_pool *pool);
#endif

/** Allocate block from block memory pool and zero the block
 *
 * This allocates a single unit (unit_size bytes)
 * \param[in]   pool    Pool handle
 * \return memory block pointer or NULL.
 * It is guaranteed that the returned pointer is aligned to pointer size
 */
#ifdef BCMOS_BLK_POOL_DEBUG
void *bcmos_blk_pool_calloc_func(bcmos_blk_pool *pool, const char *func, int line);
#define bcmos_blk_pool_calloc(pool) bcmos_blk_pool_calloc_func(pool, __FUNCTION__, __LINE__)
#else
void *bcmos_blk_pool_calloc(bcmos_blk_pool *pool);
#endif

/** Release memory allocated using bcmos_blk_pool_alloc()
 *
 * \param[in]   ptr     pointer
 */
#ifdef BCMOS_BLK_POOL_DEBUG
void bcmos_blk_pool_free_func(void *ptr, const char *func, int line);
#define bcmos_blk_pool_free(ptr) bcmos_blk_pool_free_func(ptr, __FUNCTION__, __LINE__)
#else
void bcmos_blk_pool_free(void *ptr);
#endif

/** Release all blocks in memory pool. Block content is not affected
 * This function is useful when application wants to pre-initialize
 * some portion of each memory block at init time
 *
 * \param[in]   pool    Pool handle
 */
void bcmos_blk_pool_reset(bcmos_blk_pool *pool);

/** Get pool info
 *
 * The pool must be created using bcmos_blk_pool_create()
 * \param[in]   pool    Block memory pool handle
 * \param[out]  info    Block memory pool info
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_blk_pool_query(const bcmos_blk_pool *pool, bcmos_blk_pool_info *info);

/** Block pool iterator
 * \param[in] prev      Previous block pool. *prev==NULL - get first
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_blk_pool_get_next(const bcmos_blk_pool **prev);

#ifdef BCMOS_BLK_POOL_DEBUG
typedef struct bcmos_memblk bcmos_memblk;

/** Allocated block iterator within a given block pool
 * \param[in] pool      Block pool
 * \param[in] prev      Previous allocated block. *prev==NULL - get first
 * \param[out] func     Function in which the block was allocated
 * \param[out] line     Line number in which the block was allocated
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_blk_pool_allocated_blk_get_next(const bcmos_blk_pool *pool, const bcmos_memblk **prev, const char **func, int *line);
#endif

/** @} blk_pool */

/** \defgroup byte_pool Byte Memory Pool
 * \ingroup system_mem
 * @{
 */

/** Byte memory pool parameters */
typedef struct
{
    const char *name;   /**< Pool name */
    uint32_t size;      /**< Pool size (bytes) */
    void *start;        /**< Start address. Can be NULL */
} bcmos_byte_pool_parm;

/** Byte memory pool control block */
typedef struct bcmos_byte_pool bcmos_byte_pool;

/** Create byte memory pool
 * \param[in,out]       pool    pool control block
 * \param[in]           parm    pool parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_byte_pool_create(bcmos_byte_pool *pool, const bcmos_byte_pool_parm *parm);

/** Destroy byte memory pool
 * \param[in]   pool    pool handle
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_byte_pool_destroy(bcmos_byte_pool *pool);

#ifndef BCMOS_BYTE_POOL_ALLOC_FREE_INLINE
/** Allocate memory from byte memory pool
 *
 * This function can only be used with byte memory pools created
 * with unit_size==1
 * \param[in]   pool    Pool handle
 * \param[in]   size    Block size (bytes)
 * \return memory block pointer or NULL
 */
void *bcmos_byte_pool_alloc(bcmos_byte_pool *pool, uint32_t size);

/** Release memory allocated using bcmos_pool_byte_alloc()
 *
 * \param[in]   ptr     pointer
 */
void bcmos_byte_pool_free(void *ptr);

#endif /* BCMOS_BYTE_POOL_ALLOC_FREE_INLINE */

/** @} byte_pool */

/** Lock all dynamic memory allocations. Any attempt to allocate memory from the heap after this is called will cause
 * an error if allocation size is smaller than allocation_block_size_threshold.
 * This includes bcmos_alloc, bcmos_block_pool_create, etc.
 * Dynamic allocations with size >= allocation_block_size_threshold are still allowed.
 *
 * For embedded applications, runtime dynamic memory allocation is generally undesirable, so this should be called
 * after system initialization.
 */
void bcmos_dynamic_memory_allocation_block(uint32_t allocation_block_size_threshold);

/** Unlock all dynamic memory allocations. This should not generally be called at run-time, but sometimes it is
 * required for system re-initialization.
 */
void bcmos_dynamic_memory_allocation_unblock(void);

/** Unlock dynamic memory allocation temporarily (for certain cases where dynamic memory allocation is required).
 * If bcmos_dynamic_memory_allocation_block() has not been called, this will have no effect. */
void bcmos_dynamic_memory_allocation_blocking_suspend(void);

/** Re-lock dynamic memory allocations that were unlocked with bcmos_dynamic_memory_allocation_blocking_suspend(). */
void bcmos_dynamic_memory_allocation_blocking_resume(void);

/* Allow dynamic allocations bigger than BCMOS_DYNAMIC_MEMORY_ALLOCATION_BLOCK_THRESHOLD
   at run time. Big dynamic allocations are used for features like image download.
 */
#define BCMOS_DYNAMIC_MEMORY_ALLOCATION_BLOCK_THRESHOLD (64 * 1024)

/** Produces an error if dynamic memory allocations have been locked via bcmos_lock_dynamic_memory_allocation().
 */
void bcmos_dynamic_memory_allocation_block_check(uint32_t size);

/** @} system_mem */

/** \addtogroup system_task
 * @{
 */
#ifndef BCMOS_WAIT_FOREVER
#define BCMOS_WAIT_FOREVER        0xFFFFFFFF  /**< Wait timeout. Wait forever */
#endif
#ifndef BCMOS_NO_WAIT
#define BCMOS_NO_WAIT             0 /**< Wait timeout. Don't wait */
#endif
#define BCMOS_MICROSECONDS_IN_SECONDS   (1000000)

/** Task priority */
typedef enum
{
    BCMOS_TASK_PRIORITY_0, /**< Priority 0 - highest */
    BCMOS_TASK_PRIORITY_1, /**< Priority 1 */
    BCMOS_TASK_PRIORITY_2, /**< Priority 2 */
    BCMOS_TASK_PRIORITY_3, /**< Priority 3 */
    BCMOS_TASK_PRIORITY_4, /**< Priority 4 */
    BCMOS_TASK_PRIORITY_5, /**< Priority 5 */
    BCMOS_TASK_PRIORITY_6, /**< Priority 6 */
    BCMOS_TASK_PRIORITY_7, /**< Priority 7 */
    BCMOS_TASK_PRIORITY_8, /**< Priority 8 */
    BCMOS_TASK_PRIORITY_9, /**< Priority 9 */
    BCMOS_TASK_PRIORITY_10,/**< Priority 10 */
    BCMOS_TASK_PRIORITY_11,/**< Priority 11 */
    BCMOS_TASK_PRIORITY_12,/**< Priority 12 */
    BCMOS_TASK_PRIORITY_13,/**< Priority 13 */
    BCMOS_TASK_PRIORITY_14,/**< Priority 14 */
    BCMOS_TASK_PRIORITY_15,/**< Priority 15 */
    BCMOS_TASK_PRIORITY_16,/**< Priority 16 */
    BCMOS_TASK_PRIORITY_17,/**< Priority 17 */
    BCMOS_TASK_PRIORITY_18,/**< Priority 18 */
    BCMOS_TASK_PRIORITY_19,/**< Priority 19 */
    BCMOS_TASK_PRIORITY_20,/**< Priority 20 */
    BCMOS_TASK_PRIORITY_21,/**< Priority 21 */
    BCMOS_TASK_PRIORITY_22,/**< Priority 22 */
    BCMOS_TASK_PRIORITY_23,/**< Priority 23 */
    BCMOS_TASK_PRIORITY_24,/**< Priority 24 */
    BCMOS_TASK_PRIORITY_25,/**< Priority 25 */
    BCMOS_TASK_PRIORITY_26,/**< Priority 26 */
    BCMOS_TASK_PRIORITY_27,/**< Priority 27 */
    BCMOS_TASK_PRIORITY_28,/**< Priority 28 */
    BCMOS_TASK_PRIORITY_29,/**< Priority 29 */
    BCMOS_TASK_PRIORITY_30,/**< Priority 30 */
    BCMOS_TASK_PRIORITY_31,/**< Priority 31 - lowest */
} bcmos_task_priority;

/** Task handler */
typedef int (*F_bcmos_task_handler)(long data);

/* Default task handler */
extern int bcmos_dft_task_handler(long data);

/* This flags determines whether a task is to be suspended upon OOPS condition. */
#define BCMOS_TASK_FLAG_NO_SUSPEND_ON_OOPS (1 << 0)

/** Task parameters */
typedef struct
{
    const char *name;                   /**< Task name */
    bcmos_task_priority priority;       /**< Task priority */
    bcmos_core core;                    /**< CPU core the task is locked to */
    uint32_t stack_size;                /**< Task stack size */
    void *stack;                        /**< Stack location. NULL=allocate automatically */
    F_bcmos_task_handler init_handler;  /**< Optional "init" handler. Called once in the task context when it is created.
                                             This callback is only supported in integration mode (handler==NULL).
                                             init_handler returns bcmos_errno. If it returns value other than BCM_ERR_OK,
                                             the task is destroyed */
    F_bcmos_task_handler handler;       /**< Task handler. NULL=default (integration mode) */
    F_bcmos_task_handler timeout_handler;/**< This function is used only in integration mode (handler==NULL) if
                                              msg_wait_timeout is > 0. It is called if there were no messages for the task
                                              for longer than msg_wait_timeout us.
                                              If timeout handler returns value other than BCM_ERR_OK, task terminates.
                                        */
    uint32_t msg_wait_timeout;          /**< This parameter is used only in integration mode (handler==NULL) together with
                                             timeout_handler. If > 0 and there were no messages for longer than
                                             msg_wait_timeout us, timeout_handler is called.
                                        */
    long data;                          /**< Data passed to the task handler */
    uint32_t flags;                     /**< flags */
} bcmos_task_parm;

/** Task control block */
typedef struct bcmos_task bcmos_task;

/** Create a new task
 *
 * \param[in,out]  task    Task control block
 * \param[in]      parm    Task parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_task_create(bcmos_task *task, const bcmos_task_parm *parm);

/** Set task timeout
 *
 * This function is only used in integration mode (handler==NULL).
 * It sets max time the default task handler waits for message directed to one of the
 * task's modules.
 *
 * \param[in,out]  task                 Task control block
 * \param[in]      timeout              Max time (us) to wait for messages. 0=FOREVER
 *                                      Changing timeout from infinite to finite only takes effect
 *                                      after message is received by any task module.
 * \param[in]      timeout_handler      Handler to be called upon timeout. Must be != NULL if timeout > 0.
 *                                      If the handler returns error (!= BCM_ERR_OK), task terminates.
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_task_timeout_set(bcmos_task *task, uint32_t timeout, F_bcmos_task_handler timeout_handler);

/** Destroy task
 *
 * \param[in]   task            Task handle
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_task_destroy(bcmos_task *task);

/** Get current task
 * \returns task handle or NULL if not in task context
 */
bcmos_task *bcmos_task_current(void);

/** Query task info
 * \param[in]  task    Task control block
 * \param[out] parm    Task parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_task_query(const bcmos_task *task, bcmos_task_parm *parm);

/** Task iterator
 * \param[in] prev      Previous task. *prev==NULL - get first
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_task_get_next(bcmos_task **prev);


/** @} system_task */

/** \addtogroup system_msg
 * @{
 */

/** Message header */
typedef struct bcmos_msg bcmos_msg;

/** Message queue control block */
typedef struct bcmos_msg_queue bcmos_msg_queue;

/** Message queue group control block */
typedef struct bcmos_msg_qgroup bcmos_msg_qgroup;

#if defined(BCMOS_MSG_QUEUE_DOMAIN_SOCKET) || defined(BCMOS_MSG_QUEUE_UDP_SOCKET) || defined(BCMOS_MSG_QUEUE_USER_DEFINED)
#define BCMOS_MSG_QUEUE_REMOTE_SUPPORT
#endif

/** Message queue endpoint type */
typedef enum
{
    BCMOS_MSG_QUEUE_EP_LOCAL,           /**< Local endpoint (inter-thread communication) */
#ifdef BCMOS_MSG_QUEUE_DOMAIN_SOCKET
    BCMOS_MSG_QUEUE_EP_DOMAIN_SOCKET,   /**< Domain-socket based endpoint */
#endif
#ifdef BCMOS_MSG_QUEUE_UDP_SOCKET
    BCMOS_MSG_QUEUE_EP_UDP_SOCKET,      /**< UDP socket-based endpoint */
#endif
#ifdef BCMOS_MSG_QUEUE_USER_DEFINED
    BCMOS_MSG_QUEUE_EP_USER_DEFINED     /**< User-defined endpoint */
#endif
#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT
    BCMOS_MSG_QUEUE_EP_BY_ADDRESS       /**< Endpoint type is determined based on the address format */
#endif
} bcmos_msg_queue_ep_type;


/** Message queue parameters */
typedef struct
{
    const char *name;           /**< Queue name (for logging and debugging) */
    uint32_t size;              /**< Max queue size. 0=unlimited */
    uint32_t high_wm;           /**< Optional high water mark. Log is generated when queue occupancy exceeds hwm */
    uint32_t low_wm;            /**< Optional low water mark. Log is generated when queue occupancy drops below lwm */
    uint32_t flags;             /**< TBD flags. For example, single-core, m-core */
    void (*notify)(bcmos_msg_queue *q, const char *txt); /***< Called when queue congestion state changes */
    bcmos_msg_queue_ep_type ep_type; /**< Queue endpoint type */

#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT
    /* Remote message queue support allows queue endpoints to be located in
     * different processes or even processors.
     */
    const char *local_ep_address;       /**< Queue local endpoint address */
    const char *remote_ep_address;      /**< Queue local endpoint address */

    uint32_t max_mtu;                   /**< Max MTU size */
#define BCMOS_MSG_QUEUE_DEFAULT_MAX_MTU         (64*1024)

    /** Optional "pack" callback. Not needed if 2 processes are on the same core. */
    bcmos_errno (*pack)(bcmos_msg_queue *queue, bcmos_msg *msg, uint8_t **buf, uint32_t *buf_length);

    /** Optional "unpack" callback. Not needed if 2 processes are on the same core. */
    bcmos_errno (*unpack)(bcmos_msg_queue *queue, uint8_t *buf, uint32_t buf_length, bcmos_msg **msg);

    /** Optional callback that releases packed buffer */
    void (*free_packed)(bcmos_msg_queue *queue, uint8_t *buf);

    /** Optional "open" callback. Must be set for user-defined queue, NULL otherwise */
    bcmos_errno (*open)(bcmos_msg_queue *queue);

    /** Optional "close" callback. Must be set for user-defined queue, NULL otherwise */
    bcmos_errno (*close)(bcmos_msg_queue *queue);

    /** Optional "send" callback. Must be set for user-defined queue, NULL otherwise */
    bcmos_errno (*send)(bcmos_msg_queue *queue, bcmos_msg *msg, uint8_t *buf, uint32_t buf_length);

    /** Optional "recv" callback. Must be set for user-defined queue, NULL otherwise */
    bcmos_errno (*recv)(bcmos_msg_queue *queue, uint32_t timeout, uint8_t **buf, uint32_t *buf_length);
#endif

} bcmos_msg_queue_parm;

/** Message queue statistics */
typedef struct
{
    uint32_t msg_in;            /**< Number of messages currently in the queue */
    uint32_t msg_sent;          /**< Number of messages successfully submitted into the queue */
    uint32_t msg_received;      /**< Number of messages received from the queue */
    uint32_t msg_discarded;     /**< Number of messages discarded because of queue overflow */
    uint32_t msg_almost_full;   /**< Number of messages submitted to queue when it was above high water mark */
    bcmos_bool is_congested;    /**< True=the queue is currently congested */
} bcmos_msg_queue_stat;

/** Message queue info */
typedef struct
{
    bcmos_msg_queue_parm parm;    /**< Queue parameters */
    bcmos_msg_queue_stat stat;    /**< Queue statistics */
} bcmos_msg_queue_info;

/** Message priority in queue group */
typedef uint32_t bcmos_qgroup_prty;

/** Message queue group parameters */
typedef struct
{
    const char *name;           /**< Queue group name (for logging and debugging) */
    bcmos_qgroup_prty nqueues;  /**< Number of queues in the group */
    uint32_t size;              /**< Total number of messages that can be stored in queue group. 0=unlimited */
    uint32_t high_wm;           /**< Optional high water mark. Log is generated when queue occupancy exceeds hwm */
    uint32_t low_wm;            /**< Optional low water mark. Log is generated when queue occupancy drops below lwm */
    uint32_t flags;             /**< TBD flags. For example, single-core, m-core */
    void (*notify)(bcmos_msg_qgroup *qgrp, const char *txt); /***< Called when queue group congestion state changes */
} bcmos_msg_qgroup_parm;

/** Message queue group info */
typedef struct
{
    bcmos_msg_qgroup_parm parm; /**< Queue group parameters */
    bcmos_msg_queue_stat  stat; /**< Queue group statistics */
} bcmos_msg_qgroup_info;

/** Message recipient instance (e.g., optical link id) */
typedef uint16_t bcmos_msg_instance;

/** Message send flags */
typedef enum
{
    BCMOS_MSG_SEND_AUTO_FREE = 0x00000000,      /**< Automatically release message in case of error. This is the default behaviour */
    BCMOS_MSG_SEND_NO_FREE_ON_ERROR =0x00000001,/**< Do NOT free message in case of transmit error */
    BCMOS_MSG_SEND_URGENT    = 0x00000002,      /**< Urgent message */
    BCMOS_MSG_SEND_NOLIMIT   = 0x00000004,      /**< Ignore destination queue size limit */
} bcmos_msg_send_flags;

/** Registered message handler */
typedef void (*F_bcmos_msg_handler)(bcmos_module_id module_id, bcmos_msg *msg);
typedef bcmos_errno (*F_bcmos_module_init)(long data);
typedef void (*F_bcmos_module_exit)(long data);

#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT

typedef struct bcmos_msg_addr
{
    bcmos_msg_queue_ep_type type;       /**< Address type */
    uint32_t len;                       /**< Address length */
    void *addr;                         /**< Address pointer */
} bcmos_msg_addr;

/** Parse remote message address
 * \param[in]           addr_string          String containing address
 * \param[in]           addr_type            Address type
 * \param[in,out]       addr                 On input references buffer for address conversion.
 *                                           On output addr_len contains the converted address
 * \returns     BCM_ERR_OK, BCM_ERR_PARM, BCM_ERR_OVERFLOW
 */
bcmos_errno bcmos_msg_address_parse(const char *addr_string, bcmos_msg_queue_ep_type ep_type, bcmos_msg_addr *addr);

#endif /* BCMOS_MSG_QUEUE_REMOTE_SUPPORT */

/** Message header */
struct bcmos_msg
{
    bcmos_msg_id   type;        /**< Message type */
    bcmos_msg_instance instance;/**< Message recipient instance (e.g., optical link id) */
    bcmos_module_id sender;     /**< Sender module */
    F_bcmos_msg_handler handler;/**< Message handler. Can be set by the sender or message dispatcher */
    STAILQ_ENTRY(bcmos_msg) next; /**< Next message pointer */
    void *data;                 /**< Message data pointer */
    void *start;                /**< Message data block start (for release) */
    void *user_data;            /**< User pointer. Opaque for OS abstraction */
    uint32_t size;              /**< Message data size */
    bcmos_msg_send_flags send_flags;    /**< Flags the message was sent with */
#define BCMOS_MSG_QUEUE_SIZE_UNLIMITED    0xFFFFFFFF      /**< Unlimited queue */
#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT
    bcmos_msg_addr addr;        /**< Sender address for received message, destination address when sending */
#endif
    void (*release)(bcmos_msg *);       /**< Release callback */
    void (*data_release)(bcmos_msg *);  /**< Data release callback. Used when message is released to message pool */
};

/* Helper functions that pack / unpack message header for IPC */
#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT

/** Size of message header on the line for IPC */
#define BCMOS_MSG_HDR_SIZE      8

void bcmos_msg_hdr_pack(const bcmos_msg *msg, uint8_t *buf, uint32_t data_size);
void bcmos_msg_hdr_unpack(const uint8_t *buf, bcmos_msg *msg);

#endif

/** Create message queue.
 *
 * This function can be called explicitly in "traditional" mode
 * or implicitly by bcmos_module_create().
 * \param[in,out]  queue        Queue control block
 * \param[in]      parm         Queue parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_queue_create(bcmos_msg_queue *queue, const bcmos_msg_queue_parm *parm);

/** Destroy queue
 *
 * \param[in]   queue           Queue handle
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_queue_destroy(bcmos_msg_queue *queue);

/** Get queue info
 *
 * \param[in]   queue           Queue handle
 * \param[out]  info            Queue information
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_queue_query(const bcmos_msg_queue *queue, bcmos_msg_queue_info *info);

/** Message queue iterator
 * \param[in] prev      Previous queue. *prev==NULL - get first
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_msg_queue_get_next(const bcmos_msg_queue **prev);

/** Create message queue group.
 *
 * Queue group contains configurable number of queues. The queues are drained
 * in strict priority. Priority 0 is the highest.
 *
 * \param[in,out]  qgroup       Queue group control block
 * \param[in]      parm         Queue group parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_qgroup_create(bcmos_msg_qgroup *qgroup, const bcmos_msg_qgroup_parm *parm);

/** Destroy queue group
 *
 * \param[in]   qgroup       Queue group handle
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_qgroup_destroy(bcmos_msg_qgroup *qgroup);

/** Get queue group info
 *
 * \param[in]   qgroup       Queue group handle
 * \param[out]  info         Queue group information
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_qgroup_query(const bcmos_msg_qgroup *qgroup, bcmos_msg_qgroup_info *info);

/** Message queue group iterator
 * \param[in] prev      Previous queue group. *prev==NULL - get first
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_msg_qgroup_get_next(const bcmos_msg_qgroup **prev);

/** Send message to queue
 *
 * \param[in]   queue           Queue handle
 * \param[in]   msg             Message
 * \param[in]   flags           flags. Combination of \ref bcmos_msg_send_flags bits
 *
 * msg is released automatically regardless of bcmos_msg_send() outcome, unless
 * BCMOS_MSG_SEND_NO_FREE_ON_ERROR flag is set.
 *
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_send(bcmos_msg_queue *queue, bcmos_msg *msg, bcmos_msg_send_flags flags);

/** Send message to module
 *
 * For module to be able to receive the message, it must be registered
 * using bcmos_msg_register()
 *
 * \param[in]   module_id       Module id
 * \param[in]   msg             Message. msg->handler must be set
 * \param[in]   flags           flags. Combination of \ref bcmos_msg_send_flags bits
 *
 * msg is released automatically regardless of bcmos_msg_send_to_module() outcome, unless
 * BCMOS_MSG_SEND_NO_FREE_ON_ERROR flag is set.
 *
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_send_to_module(bcmos_module_id module_id, bcmos_msg *msg, bcmos_msg_send_flags flags);

/** Send message to queue group
 *
 * \param[in]   qgroup          Queue group handle
 * \param[in]   msg             Message
 * \param[in]   prty            Message priority in range 0-nqueues_in_group-1.
 *                              0 priority is the highest. If MAX number of messages are already queues
 *                              in the queue group, sending message can leave to discard of the head message
 *                              queued at lower priority
 * \param[in]   flags           BCMOS_MSG_SEND_AUTO_FREE or BCMOS_MSG_SEND_NO_FREE_ON_ERROR flag
 *
 *
 * msg is released automatically regardless of bcmos_msg_send_to_qgroup() outcome, unless
 * BCMOS_MSG_SEND_NO_FREE_ON_ERROR flag is set.
 *
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_send_to_qgroup(bcmos_msg_qgroup *qgroup, bcmos_msg *msg, bcmos_qgroup_prty prty,
    bcmos_msg_send_flags flags);

/** Get message from the head of message queue
 *
 * The function can lead to the calling task being suspended for a period
 * of time or indefinitely, until message is submitted to the queue.\n
 * The function is only used in "traditional tasks" (see \ref system_model).
 *
 * \param[in]   queue           Queue handle
 * \param[in]   timeout         timeout. can be 0, time in us or \ref BCMOS_WAIT_FOREVER
 * \param[out]  msg             Message handle
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_recv(bcmos_msg_queue *queue, uint32_t timeout, bcmos_msg **msg);

/** Get highest priority message from queue group
 *
 * The function can lead to the calling task being suspended for a period
 * of time or indefinitely, until message is submitted to the queue group.\n
 * The function is only used in "traditional tasks" (see \ref system_model).
 *
 * \param[in]   qgroup          Queue group handle
 * \param[in]   timeout         timeout. can be 0, time in us or \ref BCMOS_WAIT_FOREVER
 * \param[out]  msg             Message handle
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_recv_from_qgroup(bcmos_msg_qgroup *qgroup, uint32_t timeout, bcmos_msg **msg);

/** Dispatch message. Send to module that registered for it.
 *
 * The message must be registered using bcmos_msg_register()
 *
 * This function should be used if the message sender doesn't know the target module and/or
 * message handling callback.
 *
 * \param[in]   msg             Message handle
 * \param[in]   flags           flags. Combination of \ref bcmos_msg_send_flags bits
 *
 * msg is released automatically regardless of bcmos_msg_dispatch() outcome, unless
 * BCMOS_MSG_SEND_NO_FREE_ON_ERROR flag is set.
 *
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_dispatch(bcmos_msg *msg, bcmos_msg_send_flags flags);

/** Cancel a message that has been dispatched to another module.
 *
 * If the given message is present in the target module's message queue, it will be removed.
 *
 * \param[in]   msg             Message handle
 * \param[in]   module_id       ID of the module that owns the message queue
 *
 * \returns BCM_ERR_OK if message was removed from a queue, BCM_ERR_ALREADY if it was not present.
 *          Other error codes are unexpected.
 */
bcmos_errno bcmos_msg_cancel(bcmos_msg *msg, bcmos_module_id module_id);

/** Register message for "push-mode" delivery.
 *
 * When registered message is sent to the target module and
 * the module's task wakes up, message handler is called in the module's context.
 *
 * \param[in]   msg_type        Message type
 * \param[in]   instance        Message type instance
 * \param[in]   module_id       Target module id
 * \param[in]   handler         Message handler
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_register(bcmos_msg_id msg_type, bcmos_msg_instance instance,
    bcmos_module_id module_id, F_bcmos_msg_handler handler);

/** Un-register message registered by bcmos_msg_register()
 *
 * \param[in]   msg_type        Message type
 * \param[in]   instance        Message type instance
 * \param[in]   module_id       Target module id
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_unregister(bcmos_msg_id msg_type, bcmos_msg_instance instance,
    bcmos_module_id module_id);

/** Put the OS message infrastructure in "shutdown mode".
 *
 * When in shutdown mode, bcmos_msg_dispatch() will return BCM_ERR_OK instead of BCM_ERR_NOENT when a handler is not
 * found for the message. Additionally, bcmos_msg_dispatch() becomes safe to call concurrently with
 * bcmos_msg_unregister() (this is not true in normal operation).
 *
 * \param[in]   shutdown_mode   Whether or not to enable shutdown mode
 */
void bcmos_msg_shutdown_mode_set(bcmos_bool shutdown_mode);

/** Gets whether or not the OS message infrastructure is currently in "shutdown mode".
 * \returns BCMOS_TRUE if we are in shutdown mode, BCMOS_FALSE otherwise
 */
bcmos_bool bcmos_msg_shutdown_mode_get(void);

/** Helper type for storing message types alongside their handlers. */
typedef struct
{
    bcmos_msg_id msg_type;
    F_bcmos_msg_handler handler;
} bcmos_msg_id2handler;

/** Message pool */
typedef struct bcmos_msg_pool bcmos_msg_pool;

/** Message pool parameters */
typedef struct bcmos_msg_pool_parm
{
    const char *name;           /**< Pool name */
    uint32_t size;              /**< Number of messages in the pool */
    uint32_t data_size;         /**< Message data size */
    uint32_t flags;             /**< TBD flags */
    void (*data_release)(bcmos_msg *msg); /**< Optional data release callback. Called when message is released to the pool */
} bcmos_msg_pool_parm;

/** Message pool statistics */
typedef bcmos_blk_pool_stat bcmos_msg_pool_stat;

/** Message pool info */
typedef struct bcmos_msg_pool_info
{
    bcmos_msg_pool_parm parm;   /**< Pool parameters */
    bcmos_msg_pool_stat stat;   /**< Pool statistics */
} bcmos_msg_pool_info;

/** Create message pool
 *
 * Create pool containing pre-allocated messages with specified data size
 * \param[in]   pool    Message pool handle
 * \param[in]   parm    Message pool parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_pool_create(bcmos_msg_pool *pool, const bcmos_msg_pool_parm *parm);

/** Destroy message pool
 *
 * All messages must be released to the pool before it can be destroyed.
 *
 * \param[in]   pool    Message pool handle
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_pool_destroy(bcmos_msg_pool *pool);

/** Allocate message from pool
 *
 * The pool must be created using bcmos_pool_create()
 * \param[in]   pool    Message pool handle
 * \returns     msg pointer or NULL if the pool is empty.
 * "data" and "release" fields in the returned message are pre-set
 * Once no longer needed, the message must be released using bcmos_msg_free()
 */
#ifdef BCMOS_BLK_POOL_DEBUG
bcmos_msg *bcmos_msg_pool_alloc_func(bcmos_msg_pool *pool, const char *func, int line);
#define bcmos_msg_pool_alloc(pool) bcmos_msg_pool_alloc_func(pool, __FUNCTION__, __LINE__)
#else
bcmos_msg *bcmos_msg_pool_alloc(bcmos_msg_pool *pool);
#endif

/** Allocate message from pool and clear data
 *
 * The pool must be created using bcmos_pool_create()
 * \param[in]   pool    Message pool handle
 * \returns     msg pointer or NULL if the pool is empty.
 * "data" and "release" fields in the returned message are pre-set
 * Once no longer needed, the message must be released using bcmos_msg_free()
 */
#ifdef BCMOS_BLK_POOL_DEBUG
static inline bcmos_msg *bcmos_msg_pool_calloc_func(bcmos_msg_pool *pool, const char *func, int line)
{
    bcmos_msg *msg = bcmos_msg_pool_alloc_func(pool, func, line);
    if (msg)
    {
        memset(msg->data, 0, msg->size);
    }
    return msg;
}
#define bcmos_msg_pool_calloc(pool) bcmos_msg_pool_calloc_func(pool, __FUNCTION__, __LINE__)
#else
static inline bcmos_msg *bcmos_msg_pool_calloc(bcmos_msg_pool *pool)
{
    bcmos_msg *msg = bcmos_msg_pool_alloc(pool);
    if (msg)
    {
        memset(msg->data, 0, msg->size);
    }
    return msg;
}
#endif

/** Get pool info
 *
 * The pool must be created using bcmos_pool_create()
 * \param[in]   pool    Message pool handle
 * \param[out]  info    Message pool info
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_msg_pool_query(const bcmos_msg_pool *pool, bcmos_msg_pool_info *info);

/** Message pool iterator
 * \param[in] prev      Previous message pool. *prev==NULL - get first
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_msg_pool_get_next(const bcmos_msg_pool **prev);

/** @} system_msg */

/** \addtogroup system_module
 * @{
 */

/** Max number of modules per task. Must be <= 32 */
#define BCMOS_MAX_MODULES_PER_TASK        8

/** Module parameters */
typedef struct
{
    bcmos_msg_queue_parm qparm;  /**< Message queue parameters */
    F_bcmos_module_init init;    /**< Init callback */
    F_bcmos_module_exit exit;    /**< Exit callback */
    long data;                   /**< Module context initial value. Also passed to init and exit callbacks */
} bcmos_module_parm;

/** Module control block */
typedef struct bcmos_module bcmos_module;

/** Register module
 *
 * \param[in]   module_id       Module id
 * \param[in]   task            Owner task ID
 * \param[in]   parm            Module parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_module_create(bcmos_module_id module_id, bcmos_task *task, bcmos_module_parm *parm);

/** Un-register module
 *
 * \param[in]   module_id       Module id
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_module_destroy(bcmos_module_id module_id);

/** Get current module id in the current task
 *
 * \returns module_id
 */
bcmos_module_id bcmos_module_current(void);

/** Get module context
 *
 * Module context is initialized as module_parm.data and can be modified using
 * bcmos_module_context_set()
 *
 * \param[in]   module_id       Module_id
 * \returns context pointer set by bcmos_module_context_set() or
 *
 * NULL if module_id is invalid or context is not set.
 */
void *bcmos_module_context(bcmos_module_id module_id);

/** Set module context
 *
 * Context is an arbitrary structure used to store module-specific data.
 * Usually this function is called from module init() callback
 *
 * \param[in]   module_id       Module_id
 * \param[in]   context         Module context pointer
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_module_context_set(bcmos_module_id module_id, void *context);

/* module control blocks */
extern bcmos_module *bcmos_modules[BCMOS_MODULE_ID__NUM_OF];

static inline bcmos_module *_bcmos_module_get(bcmos_module_id module_id)
{
    bcmos_module *module = bcmos_modules[module_id];
    if ((unsigned)module_id >= BCMOS_MODULE_ID__NUM_OF)
        return NULL;
    return module;
}

/** Query module
 *
 * \param[in]   module_id       Module_id
 * \param[out]  task            Task that owns the module
 * \param[out]  info            Module queue info
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_module_query(bcmos_module_id module_id, const bcmos_task **task, bcmos_msg_queue_info *info);


/** Check that all registered bcmos_modules have a name
 *  assigned.
 *
 * \returns 0=OK or error code.
 */
bcmos_errno bcmos_modules_name_check(void);

/** @} system_module */

/** \addtogroup system_event
 * @{
 */

/** Registered event handler */
typedef void (*F_bcmos_event_handler)(bcmos_event_id event_id, uint32_t active_bits);

/** Event parameters */
typedef struct
{
    const char *name;                   /**< Event set name */
    bcmos_module_id module_id;          /**< Module id. The module must be registered */
    uint32_t mask;                      /**< Event bits module is interested in */
    F_bcmos_event_handler handler;      /**< Event handler. Called in module's context */
    uint32_t flags;                     /**< TBD flags. E.g., inter-core */
} bcmos_event_parm;

/** Event control block */
typedef struct bcmos_event bcmos_event;

/** Create event set
 *
 * \param[in]   event_id        Event set id
 * \param[in]   parm            Event parameters. Used in "integration" mode. NULL in "traditional" mode
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_event_create(bcmos_event_id event_id, bcmos_event_parm *parm);

/** Destroy event set created by bcmos_event_create()
 *
 * \param[in]   event_id        Event set id
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_event_destroy(bcmos_event_id event_id);

/** Raise event
 *
 * Raised event is delivered to module(s) that registered for it
 * using bcmos_event_register() or to the task waiting for event
 * using bcmos_event_recv()
 *
 * \param[in]   event_id        Event set id
 * \param[in]   active_bits     Active bit mask
 * \returns 0=OK or error code <0. Can only fail if event is not registered
 */
bcmos_errno bcmos_event_raise(bcmos_event_id event_id, uint32_t active_bits);

/** Wait for event
 *
 * This function is used in "traditional" mode.\n
 * The caller can block for a time or indefinitely
 *
 * \param[in]   event_id        Event set id
 * \param[in]   mask            Interesting bits. The functions returns when
 *                              - timeout expires
 *                              - event with (active_bits & mask) != 0 is raised
 * \param[in]   timeout         timeout. can be 0, time in us or \ref BCMOS_WAIT_FOREVER
 * \param[out]  active_bits     active bits in the event set. valid only if the function returns 0
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_event_recv(bcmos_event_id event_id, uint32_t mask,
    uint32_t timeout, uint32_t *active_bits);

/* Event set array */
extern bcmos_event *bcmos_events[BCMOS_EVENT_ID__NUM_OF];

/* Get event givern the event id */
static inline bcmos_event *_bcmos_event_get(bcmos_event_id event_id)
{
    bcmos_event *ev = bcmos_events[event_id];
    if ((unsigned)event_id >= BCMOS_EVENT_ID__NUM_OF)
        return NULL;
    return ev;
}

/** @} system_event */

/** \addtogroup system_timer
 * @{
 */

/** Max timer duration (us) */
#define BCMOS_MAX_TIMER_DURATION   0x80000000

/** Timer control block */
typedef struct bcmos_timer bcmos_timer;

/** Timer handler completion code */
typedef enum
{
    BCMOS_TIMER_OK,             /**< Restart timer if periodic or keep stopped if not */
    BCMOS_TIMER_STOP            /**< Do not restart periodic timer */
} bcmos_timer_rc;

/** Timer handler
 * \param[in]   timer   Expired timer handle
 * \param[in]   data    User data supplied at timer creation time
 * \returns \ref bcmos_timer_rc
 */
typedef bcmos_timer_rc (*F_bcmos_timer_handler)(bcmos_timer *timer, long data);

typedef enum
{
    BCMOS_TIMER_PARM_FLAGS_URGENT     = 0,       /**< Default behavior. If the timer owner is set, timer expiration
                                                      will be delivered as an urgent message. */
    BCMOS_TIMER_PARM_FLAGS_NON_URGENT = 1 << 0,  /**< If the timer owner is set, timer expiration will be delivered as
                                                      a normal (non-urgent) message. */
} bcmos_timer_parm_flags;

/** Timer parameters */
typedef struct
{
    const char *name;                   /**< Timer name */
    bcmos_module_id owner;              /**< Timer owner. If set, timer expiration is delivered to the module
                                             as a message */
    bcmos_bool periodic;                /**< TRUE=periodic */
    F_bcmos_timer_handler handler;      /**< Timer handler. Called in context of owner module
                                             if set or timer ISR if owner==BCMOS_MODULE_ID_NONE */
    long data;                          /**< data to pass to the handler */
    bcmos_timer_parm_flags flags;       /**< Flags to change the behavior of the timer */
} bcmos_timer_parm;

#ifndef BCMOS_TIMESTAMP_INLINE

/** Get current timestamp
 * \returns the current system timestamp (us)
 */
uint32_t bcmos_timestamp(void);

/** Get current 64 bit timestamp
 * \returns the current system timestamp (us)
 * \note There is no guarantee that all 64 bit carry information.
 *       However, it is guaranteed that the timestamp wraps around
 *       not oftener than every 50 days (ms resolution)
 */
uint64_t bcmos_timestamp64(void);

#endif /* #ifndef BCMOS_TIMESTAMP_INLINE */

/** Create timer
 *
 * \param[in,out]       timer   timer control block
 * \param[in]           parm    timer parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_timer_create(bcmos_timer *timer, bcmos_timer_parm *parm);

/** Destroy timer
 * The timer is stopped if running and destroyed
 * \param[in]   timer   timer handle
 */
void bcmos_timer_destroy(bcmos_timer *timer);

/** Set timer handler
 *
 * \param[in,out]       timer   timer control block
 * \param[in]           handler timer handler
 * \param[in]           data    data to be passed to the handler
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_timer_handler_set(bcmos_timer *timer, F_bcmos_timer_handler handler, long data);

/** (Re)start timer
 * Stop timer if running and start it.
 *
 * \param[in]   timer   timer handle
 * \param[in]   delay   delay in us
 */
void bcmos_timer_start(bcmos_timer *timer, uint32_t delay);

/** Stop timer if running
 *
 * \param[in]   timer   timer handle
 */
void bcmos_timer_stop(bcmos_timer *timer);

/** Suspend current task for a time
 *
 * \param[in]   us      sleep time (us)
 */

#ifdef BCMOS_TIMER_DEBUG
/** Query timer info
 * \param[in]  timer   Timer control block
 * \param[out] parm    Timer parameters
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_timer_query(const bcmos_timer *timer, bcmos_timer_parm *parm);

/** Timer iterator
 * \param[in] prev      Previous timer. *prev==NULL - get first
 * \return: BCM_ERR_OK, BCM_ERR_NOENT, BCM_ERR_NO_MORE
 */
bcmos_errno bcmos_timer_get_next(bcmos_timer **prev);
#endif

#ifndef BCMOS_USLEEP_INLINE
void bcmos_usleep(uint32_t us);
#endif /* #ifndef BCMOS_USLEEP_INLINE */

/** @} system_timer */

/** \addtogroup system_fastlock
 * @{
 */

/** Fast lock control block */
typedef struct bcmos_fastlock bcmos_fastlock;

#ifndef BCMOS_FASTLOCK_INLINE

/** Init fastlock
 * \param[in, out]      lock    fast lock control block
 * \param[in]           flags   flags - TBD. E.g., single core / SMP
 */
void bcmos_fastlock_init(bcmos_fastlock *lock, uint32_t flags);

/** Take fast lock
 * \param[in]   lock    fast lock
 * \returns value of interrupt flags that should be used in unlock
 */
long bcmos_fastlock_lock(bcmos_fastlock *lock);

/** Release fast lock
 * \param[in]   lock    fast lock
 * \param[in]   flags   interrupt flags
 */
void bcmos_fastlock_unlock(bcmos_fastlock *lock, long flags);

#endif /* #ifndef BCMOS_FASTLOCK_INLINE */

/** @} system_fastlock */

/** \addtogroup system_mutex
 * @{
 */

/** Mutex control block */
typedef struct bcmos_mutex bcmos_mutex;

#ifdef BCMOS_MUTEX_INLINE
#define BCMOS_MUTEX_CREATE_DESTROY_INLINE
#define BCMOS_MUTEX_LOCK_UNLOCK_INLINE
#endif

#ifndef BCMOS_MUTEX_CREATE_DESTROY_INLINE

/** Create recursive mutex
 * \param[in, out]      mutex   Mutex control block
 * \param[in]           flags   flags - TBD. E.g., single core / SMP
 * \param[in]           name name of the mutex (if OS supports), NULL means it will be auto-generated
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_mutex_create(bcmos_mutex *mutex, uint32_t flags, const char *name);

/** Destroy mutex
 * \param[in]   mutex   Mutex control block
 */
void bcmos_mutex_destroy(bcmos_mutex *mutex);

#endif /* BCMOS_MUTEX_CREATE_DESTROY_INLINE */


#ifndef BCMOS_MUTEX_LOCK_UNLOCK_INLINE

/** Lock mutex
 * \param[in]   mutex   Mutex control block
 */
void bcmos_mutex_lock(bcmos_mutex *mutex);

/** Release mutex
 * \param[in]   mutex   Mutex control block
 */
void bcmos_mutex_unlock(bcmos_mutex *mutex);

#endif /* #ifndef BCMOS_MUTEX_LOCK_UNLOCK_INLINE */

/** @} system_mutex */

/** \addtogroup system_sem
 * @{
 */

/** Semaphore control block */
typedef struct bcmos_sem bcmos_sem;

#ifdef BCMOS_SEM_INLINE
#define BCMOS_SEM_CREATE_DESTROY_INLINE
#define BCMOS_SEM_WAIT_INLINE
#define BCMOS_SEM_POST_INLINE
#endif

#ifndef BCMOS_SEM_CREATE_DESTROY_INLINE

/** Create semaphore
 * \param[in, out]    sem   semaphore control block
 * \param[in]         count initial value of semaphore counter
 * \param[in]         flags flags - TBD. E.g., single core / SMP
 * \param[in]         name name of the semaphore (if OS supports), NULL means it will be auto-generated
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_sem_create(bcmos_sem *sem, uint32_t count, uint32_t flags, const char *name);

/** Destroy semaphore
 * \param[in]   sem   semaphore control block
 */
void bcmos_sem_destroy(bcmos_sem *sem);

#endif /* BCMOS_SEM_CREATE_DESTROY_INLINE */

#ifndef BCMOS_SEM_WAIT_INLINE

/** Decrement semaphore counter. Wait if the counter is 0
 *
 * \param[in]   sem     semaphore control block
 * \param[in]   timeout timeout. can be 0, time in us or \ref BCMOS_WAIT_FOREVER
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_sem_wait(bcmos_sem *sem, uint32_t timeout);

#endif /* #ifndef BCMOS_SEM_WAIT_INLINE */

#ifndef BCMOS_SEM_POST_INLINE
/** Increment semaphore counter
 * \param[in]   sem   semaphore control block
 */
void bcmos_sem_post(bcmos_sem *sem);

#endif /* #ifndef BCMOS_SEM_POST_INLINE */

/** @} system_sem */

/*
 * print support
 */

/** Print cloning/redirection mode */
typedef enum
{
    BCMOS_PRINT_REDIRECT_MODE_NONE,     /**< No cloning, redirection */
    BCMOS_PRINT_REDIRECT_MODE_REDIRECT, /**< Redirect console output. Do not print on the serial console */
    BCMOS_PRINT_REDIRECT_MODE_CLONE     /**< Clone console output to redirection callback */
} bcmos_print_redirect_mode;

/** Print re-direction/cloning callback */
typedef int (*bcmos_print_redirect_cb)(void *data, const char *format, va_list ap);

/** Set up print redirection/cloning
 * \param[in]   mode    redirection/cloning mode
 * \param[in]   cb      redirection callback
 * \param[in]   data    opaque data to be passed to cb
 * \returns 0=OK or error <0
 */
bcmos_errno bcmos_print_redirect(bcmos_print_redirect_mode mode, bcmos_print_redirect_cb cb, void *data);

/* Print on the console with optional cloning / redirection
 * \param[in]   format  printf format
 * \param[in]   ap      argument list
 * \returns number of characters printed >= 0 or error < 0
 */
int bcmos_vprintf(const char *format, va_list ap);

/* Print on the console with optional cloning / redirection
 * \param[in]   format  printf format
 * \returns number of characters printed >= 0 or error < 0
 */
int bcmos_printf(const char *format, ...);


/** \addtogroup system_trace
 * @{
 */

/** Trace level */
typedef enum
{
    BCMOS_TRACE_LEVEL_NONE,     /**< No trace output */
    BCMOS_TRACE_LEVEL_ERROR,    /**< Trace errors */
    BCMOS_TRACE_LEVEL_WARNING,  /**< Trace errors + warnings */
    BCMOS_TRACE_LEVEL_INFO,     /**< Trace errors + warnings + info */
    BCMOS_TRACE_LEVEL_VERBOSE,  /**< Trace errors + warnings + info + verbose info */
    BCMOS_TRACE_LEVEL_DEBUG,    /**< Trace everything */
} bcmos_trace_level;

extern bcmos_trace_level bcmos_sys_trace_level;

#ifdef BCMOS_TRACE_PRINTF
#define BCMOS_TRACE_INLINE
#endif

#ifndef BCMOS_TRACE_INLINE
/** Print trace
 *
 * \param[in]   level           Record trace at level
 * \param[in]   format          printf-like format
 */
void bcmos_trace(bcmos_trace_level level, const char *format, ...);
#endif


/* Print trace */
#ifdef BCMOS_TRACE_PRINTF
#define bcmos_trace(level, fmt, args...)  bcmos_printf(fmt, ## args)
#endif

/** Set current trace level
 * \param[in]   level           New trace level
 * \returns old trace level
 */
static inline bcmos_trace_level bcmos_trace_level_set(bcmos_trace_level level)
{
    bcmos_trace_level old_level = bcmos_sys_trace_level;
    bcmos_sys_trace_level = level;
    return old_level;
}

/** Get current trace level
 * \returns trace level
 */
static inline bcmos_trace_level bcmos_trace_level_get(void)
{
    return bcmos_sys_trace_level;
}

/** Print trace conditionally, depending on the current trace level
 * \param[in]   level   Record trace at level
 * \param[in]   fmt     printf-like format
 * \param[in]   args    printf-like arguments
 */
#define BCMOS_TRACE(level, fmt, args...) \
    do \
    { \
        if (level <= bcmos_sys_trace_level) \
            bcmos_trace(level, "%s#%d> " fmt, __FUNCTION__, __LINE__, ## args); \
    } while (0)

/** Print error trace conditionally, depending on the current trace level
 * \param[in]   fmt     printf-like format
 * \param[in]   args    printf-like arguments
 */

extern f_bcmolt_sw_error_handler sw_error_handler;

#define BCMOS_TRACE_ERR(fmt, args...) \
    do \
    { \
        BCMOS_TRACE(BCMOS_TRACE_LEVEL_ERROR, "ERR: " fmt, ## args); \
        if (sw_error_handler != NULL) \
        { \
            sw_error_handler(0xff, __FILE__, __LINE__); \
        } \
        _bcmos_backtrace(); \
   } while (0)


/** Print info trace conditionally, depending on the current trace level
 * \param[in]   fmt     printf-like format
 * \param[in]   args    printf-like arguments
 */
#define BCMOS_TRACE_INFO(fmt, args...)          \
    BCMOS_TRACE(BCMOS_TRACE_LEVEL_INFO, "INF: " fmt, ## args)

/** Print verbose info trace conditionally, depending on the current trace level
 * \param[in]   fmt     printf-like format
 * \param[in]   args    printf-like arguments
 */
#define BCMOS_TRACE_VERBOSE(fmt, args...)      \
    BCMOS_TRACE(BCMOS_TRACE_LEVEL_VERBOSE, "VRB: " fmt, ## args)

/** Print debug trace conditionally, depending on the current trace level
 * \param[in]   fmt     printf-like format
 * \param[in]   args    printf-like arguments
 */
#define BCMOS_TRACE_DEBUG(fmt, args...)        \
    BCMOS_TRACE(BCMOS_TRACE_LEVEL_DEBUG, "DBG: " fmt, ## args)

/** Print trace conditionally based on return code and return
 * \param[in]   rc      return code
 * \param[in]   fmt     printf-like format
 * \param[in]   args    printf-like arguments
 * \returns rc
 */
#define BCMOS_TRACE_RETURN(rc, fmt, args...)    \
    do {                                        \
        if (rc)                                 \
            BCMOS_TRACE_ERR("status:%s :" fmt, bcmos_strerror(rc), ## args); \
        else                                    \
            BCMOS_TRACE_INFO("success: " fmt, ## args); \
        return rc;                              \
    } while (0)

#define BCMOS_TRACE_CHECK_RETURN(cond,rc,fmt,args...)    \
    do {                                        \
        if (cond)                                 \
        {\
            BCMOS_TRACE_ERR( #cond ": status:%s :" fmt, bcmos_strerror(rc), ## args); \
            return rc;                              \
        }\
    } while (0)

#define BCMOS_TRACE_CHECK_RETURN_TYPE(cond,err,ret,fmt,args...)    \
    do {                                        \
        if (cond)                                 \
        {\
            BCMOS_TRACE_ERR( #cond ": status:%s :" fmt, bcmos_strerror(err), ## args); \
            return ret;                              \
        }\
    } while (0)

#define BCMOS_TRACE_CHECK_RETURN_VOID(cond,err,fmt,args...)    \
    do {                                        \
        if (cond)                                 \
        {\
            BCMOS_TRACE_ERR( #cond ": status:%s :" fmt, bcmos_strerror(err), ## args); \
            return;                              \
        }\
    } while (0)

#define BCMOS_CHECK_RETURN(cond,err,ret)    \
    do {                                        \
        if (cond)                                 \
        {\
            BCMOS_TRACE_ERR( #cond ": status:%s\n", bcmos_strerror(err)); \
            return ret;                              \
        }\
    } while (0)
#define BCMOS_CHECK_RETURN_ERROR(cond,err) BCMOS_CHECK_RETURN(cond,err,err)
#define BCMOS_RETURN_ON_ERROR(err) BCMOS_CHECK_RETURN(BCM_ERR_OK != err, err, /*this space intentionally left blank*/)
#define BCMOS_RETURN_IF_ERROR(err) BCMOS_CHECK_RETURN_ERROR(BCM_ERR_OK != err, err)
#define BCMOS_BREAK_IF_ERROR(err) if (err != BCM_ERR_OK) break
#define BCMOS_TRACE_IF_ERROR(err) \
    do { \
        if ((err) != BCM_ERR_OK) \
            BCMOS_TRACE_ERR("error %s (%d)\n", bcmos_strerror(err), err); \
    } while (0)

/** @} system_trace */

/*
 * Low level services
 */

/** \addtogroup system_buf
 * @{
 */

/** Transport/network buffer */
typedef struct bcmos_buf bcmos_buf;

/** @} system_buf */

/** Round a number up to the specified power of 2 */
#define BCMOS_ROUND_UP(n, m) (((n) + (m) - 1) & ~((m) - 1))

/** Round a number up to the nearest word multiple */
#define BCMOS_ROUND_TO_WORD(n) BCMOS_ROUND_UP(n, sizeof(size_t))

/* BCMOS_DIVIDE_ROUND_UP(integer_dividend / integer_divisor) == (integer_dividend + integer_divisor - 1) / integer_divisor */
#define BCMOS_DIVIDE_ROUND_UP(n, m) (((n) + (m) - 1) / (m))

#define TAB "  "
#define TAB2 TAB  TAB
#define TAB3 TAB2 TAB
#define TAB4 TAB2 TAB2

static inline bcmos_bool bcmos_mac_is_zero(bcmos_mac_address *mac)
{
    if (mac->u8[0]==0 && mac->u8[1]==0 && mac->u8[2]==0 && mac->u8[3]==0 && mac->u8[4]==0 && mac->u8[5]==0)
        return BCMOS_TRUE;
    else
        return BCMOS_FALSE;
}

/**
 * Returns TRUE if module has been active since last periodic check.
 * Also returns true if module has not yet been created.
 *
 * @param period    Time in microseconds since last check
 * @param module_id Module ID
 *
 * @return True if healthy
 */
bcmos_bool bcmos_module_is_healthy(uint32_t period, bcmos_module_id module_id);


bcmos_errno bcmos_modules_healthcheck_init(void);

/**
 * This function is for debug purposes for the health check feature.
 *
 * @param module_id
 */
void healthcheck_print(bcmos_module_id module_id);

/* An optional callback to be executed on completion of an oops handling. */
typedef void (*bcmos_oops_complete_cb_t)(void);

extern bcmos_oops_complete_cb_t bcmos_oops_complete_cb;

#endif /* BCMOS_SYSTEM_COMMON_H_ */
