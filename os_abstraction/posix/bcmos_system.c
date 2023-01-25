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
#ifdef BCMOS_MSG_QUEUE_DOMAIN_SOCKET
#include <sys/un.h>
#endif
#include <sys/resource.h>
#include <arpa/inet.h>

static F_bcmos_bug_handler _os_bug_handler;

/* task control blocks */
extern STAILQ_HEAD(task_list, bcmos_task) task_list;

/* global OS lock */
extern bcmos_mutex bcmos_res_lock;

/*
 * Init
 */

#define TIMER_SIG       SIGRTMIN

#if defined(CONFIG_ONU_SIM) && defined(SIMULATION_BUILD)
bcmos_bool is_high_resolution;
#endif

/* Initialize system library */
bcmos_errno bcmos_sys_init(void)
{
#if defined(CONFIG_ONU_SIM) && defined(SIMULATION_BUILD)
    is_high_resolution = BCMOS_TRUE;
    struct timespec res;

    clock_getres(CLOCK_REALTIME, &res);
    if (res.tv_nsec > 1000 && res.tv_sec == 0)
    {
        is_high_resolution = BCMOS_FALSE;
    }
#endif
    srand(bcmos_timestamp());
    return BCM_ERR_OK;
}

/* Clean-up system library */
void bcmos_sys_exit(void)
{
}

/*
 * Task management
 */

/*
 * Default task handler
 */

/* Create a new task */
bcmos_errno bcmos_task_create(bcmos_task *task, const bcmos_task_parm *parm)
{
    F_bcmos_task_handler handler;
    pthread_attr_t pthread_attr;
    struct sched_param pthread_sched_param = {};
#define MAX_PROCESS_NAME_LENGTH  16
    char process_name[MAX_PROCESS_NAME_LENGTH];
    int pthread_prio;
    uint32_t stack_size;
    void *data;
    int rc;

    if (!task || !parm)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "task %p, parm %p\n", task, parm);
    memset(task, 0, sizeof(*task));
    if (parm->handler)
    {
        /* "traditional task */
        handler = parm->handler;
        data = (void *)parm->data;
    }
    else
    {
        /* "integrated" task */
        handler = bcmos_dft_task_handler;
        data = task;

        /* Initialize and lock mutex to wait on */
        rc = bcmos_sem_create(&task->active_sem, 0, task->parm.flags, parm->name);
        if (rc)
        {
            BCMOS_TRACE_ERR("Task %s: can't create active_sem. Error %s (%d)\n",
                parm->name, bcmos_strerror(rc), rc);
            return rc;
        }
    }

    task->parm = *parm;
    /* Copy name to make sure that it is not released - in case it was on the stack */
    if (task->parm.name && task->name != task->parm.name)
    {
        strncpy(task->name, task->parm.name, sizeof(task->name) - 1);
        task->parm.name = task->name;
    }
    bcmos_fastlock_init(&task->active_lock, 0);
    bcmos_mutex_lock(&bcmos_res_lock);
    STAILQ_INSERT_TAIL(&task_list, task, list);
    bcmos_mutex_unlock(&bcmos_res_lock);
    task->magic = BCMOS_TASK_MAGIC;
    /* pthread priorities are 1..32, 32 being the highest */
    pthread_prio = 32 - (int)parm->priority;
    if (pthread_prio <= 0)
        pthread_prio = 1;
    stack_size = PTHREAD_STACK_MIN + (parm->stack_size ? parm->stack_size : BCMOS_DEFAULT_STACK_SIZE);
    rc = pthread_attr_init(&pthread_attr);
    pthread_sched_param.sched_priority = pthread_prio;
    rc = rc ? rc : pthread_attr_setinheritsched(&pthread_attr, PTHREAD_EXPLICIT_SCHED);
    rc = rc ? rc : pthread_attr_setschedpolicy(&pthread_attr, SCHED_RR);
    rc = rc ? rc : pthread_attr_setschedparam(&pthread_attr, &pthread_sched_param);
    rc = rc ? rc : pthread_attr_setstacksize(&pthread_attr, stack_size);

#if __GNUC__ > 7
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type" /* (void *(*)(void *)) cast requires this */
#endif
    rc = rc ? rc : pthread_create(&task->sys_task.t, &pthread_attr, (void *(*)(void *))handler, data);
    pthread_attr_destroy(&pthread_attr);
    if (rc == EPERM)
    {
        BCMOS_TRACE_INFO("Thread %s: priority %d is ignored. Start as root to honor priorities\n",
            parm->name, (int)parm->priority);
        rc = pthread_attr_init(&pthread_attr);
        rc = rc ? rc : pthread_attr_setstacksize(&pthread_attr, stack_size);
        rc = rc ? rc : pthread_create(&task->sys_task.t, NULL, (void *(*)(void *))handler, data);
    }
#if __GNUC__ > 7
#pragma GCC diagnostic pop
#endif

    if (rc)
    {
        bcmos_mutex_lock(&bcmos_res_lock);
        STAILQ_REMOVE(&task_list, task, bcmos_task, list);
        bcmos_mutex_unlock(&bcmos_res_lock);
        task->magic = 0;
        if (!parm->handler)
        {
            bcmos_sem_destroy(&task->active_sem);
        }
        BCMOS_TRACE_RETURN(BCM_ERR_SYSCALL_ERR, "%s (%d)\n", strerror(rc), rc);
    }

    if (task->parm.name)
    {
        strncpy(process_name, parm->name, sizeof(process_name) - 1);
        process_name[sizeof(process_name) - 1] = 0;
        rc = pthread_setname_np(task->sys_task.t, process_name);
        if (rc)
        {
            BCMOS_TRACE_ERR("pthread_setname_np(%s) failed with error '%s'\n",
                parm->name, strerror(rc));
            /* Fall through and ignore the error */
        }
    }
    return BCM_ERR_OK;
}

/* Destroy task */
bcmos_errno bcmos_task_destroy(bcmos_task *task)
{
    void *res;
    int rc_cancel;
    int rc;

    if (task->magic != BCMOS_TASK_MAGIC)
    {
        return BCM_ERR_PARM;
    }
    task->destroy_request = BCMOS_TRUE;
    task->magic = BCMOS_TASK_MAGIC_DESTROYED;
    bcmos_mutex_lock(&bcmos_res_lock);
    STAILQ_REMOVE(&task_list, task, bcmos_task, list);
    bcmos_mutex_unlock(&bcmos_res_lock);
    /* The task may be waiting on semaphore. Kick it */
    if (!task->parm.handler)
    {
        bcmos_sem_post(&task->active_sem);
    }
    rc_cancel = pthread_cancel(task->sys_task.t);
    rc = pthread_join(task->sys_task.t, &res);
    return (rc || ((!rc_cancel) && (res != PTHREAD_CANCELED))) ? BCM_ERR_SYSCALL_ERR : 0;
}

/** Get current task
 * \returns task handle or NULL if not in task context
 */
bcmos_task *bcmos_task_current(void)
{
    pthread_t pt = pthread_self();
    bcmos_task *t, *tmp;

    STAILQ_FOREACH_SAFE(t, &task_list, list, tmp)
    {
        if (pthread_equal(pt, t->sys_task.t))
            break;
    }
    return t;
}

/*
 * Recursive mutex
 */

/* Create recursive mutex */
bcmos_errno bcmos_mutex_create(bcmos_mutex *mutex, uint32_t flags, const char *name)
{
    int err;
    err = pthread_mutexattr_init(&mutex->attr);
    err = err ? err : pthread_mutexattr_settype(&mutex->attr, PTHREAD_MUTEX_RECURSIVE_NP);
    err = err ? err : pthread_mutex_init(&mutex->m, &mutex->attr);
    if (err)
        BCMOS_TRACE_RETURN(BCM_ERR_SYSCALL_ERR, "errno=%s\n", strerror(err));
    return BCM_ERR_OK;
}

/** Destroy mutex
 * \param[in]   mutex   Mutex control block
 */
void bcmos_mutex_destroy(bcmos_mutex *mutex)
{
    pthread_mutex_destroy(&mutex->m);
    pthread_mutexattr_destroy(&mutex->attr);
}

/* Return whether a given mutex is valid or not */
bcmos_bool bcmos_mutex_is_valid(bcmos_mutex *mutex)
{
    return BCMOS_TRUE;
}

/* calculate absolute time equal to the current time + timeout */
static inline void _bcmos_get_abs_time(struct timespec *ts, uint32_t timeout)
{
    int rc;

    rc = clock_gettime(CLOCK_REALTIME, ts);
    BUG_ON(rc);
#if defined(CONFIG_ONU_SIM) && defined(SIMULATION_BUILD)
    if (!is_high_resolution)
    {
        ts->tv_sec += timeout / 1000;
        ts->tv_nsec += (timeout % 1000) * 1000000;
    }
    else
#endif
    {
        ts->tv_sec += timeout / 1000000;
        ts->tv_nsec += (timeout % 1000000) * 1000;
    }
    if (ts->tv_nsec > 1000000000)
    {
        ts->tv_sec += ts->tv_nsec / 1000000000;
        ts->tv_nsec %= 1000000000;
    }
}

/** Lock mutex
 */
void bcmos_mutex_lock(bcmos_mutex *mutex)
{
    int rc;
    rc = pthread_mutex_lock(&mutex->m);
    if (rc)
        BCMOS_TRACE_ERR("pthread_mutex_lock()->%d\n", rc);
    BUG_ON(rc);
    return;
}

/** Release mutex
 * \param[in]   mutex   Mutex control block
 */
void bcmos_mutex_unlock(bcmos_mutex *mutex)
{
    int rc;
    rc = pthread_mutex_unlock(&mutex->m);
    if (rc)
        BCMOS_TRACE_ERR("pthread_mutex_unlock()->%d\n", rc);
    BUG_ON(rc);
}

/*
 * Semaphores
 * Most of semaphore functions are inline
 */

/* Create semaphore */
bcmos_errno bcmos_sem_create(bcmos_sem *sem, uint32_t count, uint32_t flags, const char *name)
{
    sem_init(&sem->s, 0, count);
    return BCM_ERR_OK;
}

/* Destroy semaphore */
void bcmos_sem_destroy(bcmos_sem *sem)
{
    sem_destroy(&sem->s);
}

/* Return whether a given semaphore is valid or not */
bcmos_bool bcmos_sem_is_valid(bcmos_sem *sem)
{
    return BCMOS_TRUE;
}

/* Decrement semaphore counter. Wait if the counter is 0 */
bcmos_errno bcmos_sem_wait(bcmos_sem *sem, uint32_t timeout)
{
    int rc;
    struct timespec ts;

    /* Init end time if necessary */
    if (timeout && timeout != BCMOS_WAIT_FOREVER)
    {
        _bcmos_get_abs_time(&ts, timeout);
    }

    do
    {
        if (timeout == BCMOS_WAIT_FOREVER)
        {
            rc = sem_wait(&sem->s);
        }
        else if (timeout)
        {
            rc = sem_timedwait(&sem->s, &ts);
        }
        else
        {
            rc = sem_trywait(&sem->s);
        }
    } while (rc && errno == EINTR);

    if (rc)
    {
        bcmos_errno err;

        rc = errno;
        if (rc == ETIMEDOUT)
        {
            err = BCM_ERR_TIMEOUT;
        }
        else
        {
            err = BCM_ERR_INTERNAL;
            BCMOS_TRACE_ERR("sem_wait()->%d\n", rc);
        }
        return err;
    }

    return BCM_ERR_OK;
}


/*
 * Timers
 */

/** Get current timestamp
 * \returns the current system timestamp (us)
 */
uint32_t bcmos_timestamp(void)
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);

    uint32_t timestamp = tp.tv_sec * 1000000 + tp.tv_nsec / 1000;

#if defined(CONFIG_ONU_SIM) && defined(SIMULATION_BUILD)
    if (!is_high_resolution)
    {
        timestamp *= 1000;
    }
#endif

    return timestamp;
}

/** Get current timestamp - 64 bit
 * \returns the current system timestamp (us)
 */
uint64_t bcmos_timestamp64(void)
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    uint64_t timestamp = (uint64_t)tp.tv_sec * 1000000LL + (uint64_t)tp.tv_nsec / 1000LL;

#if defined(CONFIG_ONU_SIM) && defined(SIMULATION_BUILD)
    if (!is_high_resolution)
    {
        timestamp *= 1000LL;
    }
#endif

    return timestamp;
}

/*
 * Timer handlers
 */



/* For posix we must create timer task, because there is no way
 * to enforce protection between a signal handler and a thread
 */
static bcmos_task _bcmos_timer_task;
static sem_t _bcmos_timer_lock;

static int _bcmos_tmr_task_handler(long data)
{
    bcmos_sys_timer *timer = (bcmos_sys_timer *)data;
    bcmos_task *this_task = bcmos_task_current();

    if (!this_task)
        return 0;
    while(!this_task->destroy_request)
    {
        sem_wait(&_bcmos_timer_lock);
        timer->handler(timer->data);
    }
    this_task->destroyed = BCMOS_TRUE;

    return 0;
}

/* timer signal handler */
static void timer_sig_handler(int sig, siginfo_t *si, void *uc)
{
    BUG_ON(si->si_code != SI_TIMER);
    sem_post(&_bcmos_timer_lock);
}

/* Create timer */
bcmos_errno bcmos_sys_timer_create(bcmos_sys_timer *timer, bcmos_sys_timer_handler handler, void *data)
{
    static bcmos_task_parm tmr_task_parm = {
        .name = "tmr_task",
        .priority = BCMOS_TASK_PRIORITY_0,
        .handler = _bcmos_tmr_task_handler
    };
    bcmos_errno rc;

    struct sigaction sa;
    struct sigevent sev = {};

    if (!timer || !handler)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "timer %p, handler %p\n", timer, handler);

    timer->destroyed = BCMOS_FALSE;
    timer->handler = handler;
    timer->data = data;

    sem_init(&_bcmos_timer_lock, 0, 0);
    tmr_task_parm.data = (long)timer;
    rc = bcmos_task_create(&_bcmos_timer_task, &tmr_task_parm);
    if (rc)
        BCMOS_TRACE_RETURN(rc, "Can't create timer task\n");

    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sa.sa_sigaction = timer_sig_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(TIMER_SIG, &sa, NULL) == -1)
        perror("sigaction");
 
   /* Create librt timer */
   sev.sigev_notify = SIGEV_SIGNAL;
   sev.sigev_signo = TIMER_SIG;
   sev.sigev_value.sival_ptr = timer;
   if (timer_create(CLOCK_REALTIME, &sev, &timer->t) == -1)
       BCMOS_TRACE_RETURN(BCM_ERR_SYSCALL_ERR, "errno %s\n", strerror(errno));

   return BCM_ERR_OK;
}

/* Destroy timer */
void bcmos_sys_timer_destroy(bcmos_sys_timer *timer)
{
    timer->destroyed = BCMOS_TRUE;
    timer_delete(timer->t);
    sem_destroy(&_bcmos_timer_lock);
    bcmos_task_destroy(&_bcmos_timer_task);
}

/* (Re)start timer */
void bcmos_sys_timer_start(bcmos_sys_timer *timer, uint32_t delay)
{
    struct itimerspec its;

    if (timer->destroyed)
    {
        return;
    }

#if defined(CONFIG_ONU_SIM) && defined(SIMULATION_BUILD)
    if (!is_high_resolution)
    {
        its.it_value.tv_sec = delay / 1000;
        its.it_value.tv_nsec = (delay % 1000) * 1000000;
    }
    else
#endif
    {
        its.it_value.tv_sec = delay / 1000000;
        its.it_value.tv_nsec = (delay % 1000000) * 1000;
    }
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    if (timer_settime(timer->t, 0, &its, NULL) == -1)
    {
        BCMOS_TRACE_ERR("timer_settime errno %s\n", strerror(errno));
        BUG();
    }
}

/* Stop timer if running */
void bcmos_sys_timer_stop(bcmos_sys_timer *timer)
{
    struct itimerspec its;

    BUG_ON(!timer);
    memset(&its, 0, sizeof(its));
    timer_settime(timer->t, 0, &its, NULL);
}


/* Suspend current task for a time */
void bcmos_usleep(uint32_t us)
{
    uint32_t ts = bcmos_timestamp();
    uint32_t tse = ts + us;
    int32_t d = (us > 1000000) ? 1000000 : us;

    do
    {
        usleep(d);
        d = tse - bcmos_timestamp();
        if (d > 1000000) d = 1000000;
    } while (d > 0);
}

/*
 * Memory management
 */

/* Stubs */
void _bcmos_malloc_lock(void)
{
}

void _bcmos_malloc_unlock(void)
{
}

/** Allocate memory from the main heap */
#ifndef BCMOS_HEAP_DEBUG
void *bcmos_alloc(uint32_t size)
#else
void *_bcmos_alloc(uint32_t size)
#endif
{
    void *ptr;

    bcmos_dynamic_memory_allocation_block_check(size);
    ptr = malloc(size);
    if (!ptr)
        return ptr;

#ifdef BCMOS_HEAP_DEBUG
    ptr = bcmos_heap_debug_hdr_to_user_ptr(ptr);
#endif

    return ptr;
}

/** Release memory to the main pool
 * \param[in]   ptr
 */
#ifndef BCMOS_HEAP_DEBUG
void bcmos_free(void *ptr)
#else
void _bcmos_free(void *ptr)
#endif
{
#ifdef BCMOS_HEAP_DEBUG
    ptr = (void *)bcmos_heap_user_ptr_to_debug_hdr(ptr);
#endif
    free(ptr);
}

/*
 * Byte memory pool
 */

/* Memory block header */
typedef struct bcmos_byte_memblk
{
    bcmos_byte_pool *pool;      /** pool that owns the block */
    uint32_t size;              /** block size (bytes) including bcmos_byte_memblk header */
#ifdef BCMOS_MEM_CHECK
    uint32_t magic;             /** magic number */
#define BCMOS_MEM_MAGIC_ALLOC   (('m'<<24) | ('b' << 16) | ('l' << 8) | 'k')
#define BCMOS_MEM_MAGIC_FREE    (('m'<<24) | ('b' << 16) | ('l' << 8) | '~')
#endif
} bcmos_byte_memblk;

/* Create byte memory pool */
bcmos_errno bcmos_byte_pool_create(bcmos_byte_pool *pool, const bcmos_byte_pool_parm *parm)
{
    if (!pool || !parm)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "pool %p, parm %p\n", pool, parm);
    }

    BCM_MEMZERO_STRUCT(pool);
    pool->parm = *parm;
    if (!pool->parm.size)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "size %u\n", parm->size);
    }
    pool->magic = BCMOS_BYTE_POOL_VALID;
    return BCM_ERR_OK;
}

/* Destroy memory pool */
bcmos_errno bcmos_byte_pool_destroy(bcmos_byte_pool *pool)
{
    if (pool->allocated)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_STATE, "%u bytes of memory are still allocated from the pool %s\n",
            pool->allocated, pool->parm.name);
    }
    pool->magic = BCMOS_BYTE_POOL_DELETED;
    return BCM_ERR_OK;
}

/* Return whether a given byte pool is valid or not */
bcmos_bool bcmos_byte_pool_is_valid(bcmos_byte_pool *pool)
{
    return pool->magic == BCMOS_BYTE_POOL_VALID;
}

/* Allocate memory from memory pool */
void *bcmos_byte_pool_alloc(bcmos_byte_pool *pool, uint32_t size)
{
    bcmos_byte_memblk *blk;
    uint32_t byte_size;
    void *ptr;

#ifdef BCMOS_MEM_CHECK
    BUG_ON(pool->magic != BCMOS_BYTE_POOL_VALID);
#endif

    if (size + pool->allocated > pool->parm.size)
        return NULL;

    byte_size = size + sizeof(bcmos_byte_memblk);
#ifdef BCMOS_MEM_CHECK
    byte_size += sizeof(uint32_t); /* block suffix */
#endif
    /* ToDo: Maintain LL of allocated blocks */
    blk = (bcmos_byte_memblk *)malloc(byte_size);
    if (!blk)
        return NULL;
    ptr = (void *)(blk + 1);
    blk->size = byte_size;
    pool->allocated += byte_size;
    blk->pool = pool;
#ifdef BCMOS_MEM_CHECK
    blk->magic = BCMOS_MEM_MAGIC_ALLOC;
    *(uint32_t *)((long)blk + byte_size - sizeof(uint32_t)) = BCMOS_MEM_MAGIC_ALLOC;
#endif

    return ptr;
}

/* Release memory allocated using bcmos_byte_pool_alloc() */
void bcmos_byte_pool_free(void *ptr)
{
    bcmos_byte_memblk *blk;
    bcmos_byte_pool *pool;

    BUG_ON(!ptr);
    blk = (bcmos_byte_memblk *)((long)ptr - sizeof(bcmos_byte_memblk));
    pool = blk->pool;
#ifdef BCMOS_MEM_CHECK
    BUG_ON(pool->magic != BCMOS_BYTE_POOL_VALID);
    BUG_ON(blk->magic != BCMOS_MEM_MAGIC_ALLOC);
    BUG_ON(*(uint32_t *)((long)blk + blk->size - sizeof(uint32_t)) != BCMOS_MEM_MAGIC_ALLOC);
    blk->magic = BCMOS_MEM_MAGIC_FREE;
#endif
    pool->allocated -= blk->size;
    free(blk);
}

void _bcmos_backtrace(void)
{
    void *array[32];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace(array, sizeof(array)/sizeof(array[0]));
    strings = backtrace_symbols(array, size);
    /* Do not print backtrace if it was unable to unwind the call stack.
       The top 2 entries in the backtrace don't carry any useful info.
       The top one is the backtrace itself and the next one is the function
       that called BCMOS_TRACE_ERR macro.
    */
    if (size < 3 || strings == NULL)
        return;

    printf("Obtained %zd stack frames.\n", size);
    for (i = 0; i < size; i++)
        printf("%s\n", strings[i]);

    free(strings);
}

void bcmos_bug_handler_install(F_bcmos_bug_handler handler)
{
    _os_bug_handler = handler;
}

void bcmos_bug_handler_call(const char *error_msg, const char *file, int line)
{
    if (_os_bug_handler)
    {
        _os_bug_handler(error_msg, file, line);
        __builtin_unreachable();
    }
    else
    {
        abort();
    }
}

#ifdef SIMULATION_BUILD

#define BCMOS_MAX_IRQS 256
typedef int (*F_isr)(int irq, void *priv);
static F_isr isr_handler[BCMOS_MAX_IRQS];
static void *isr_priv[BCMOS_MAX_IRQS];
static bcmos_bool irq_enabled[BCMOS_MAX_IRQS];

#endif

void bcmos_int_enable(int irq)
{
#ifdef SIMULATION_BUILD
    if (irq >= BCMOS_MAX_IRQS)
    {
        BCMOS_TRACE_ERR("irq %d is out of range\n", irq);
        return;
    }
    if (!isr_handler[irq])
    {
        BCMOS_TRACE_ERR("irq %d is not connected\n", irq);
        return;
    }
    irq_enabled[irq] = BCMOS_TRUE;
#endif
}

void bcmos_int_disable(int irq)
{
#ifdef SIMULATION_BUILD
    if (irq >= BCMOS_MAX_IRQS)
    {
        BCMOS_TRACE_ERR("irq %d is out of range\n", irq);
        return;
    }
    irq_enabled[irq] = BCMOS_FALSE;
#endif
}

int bcmos_int_connect(int irq, int cpu, int flags,
    int (*isr)(int irq, void *priv), const char *name, void *priv)
{
#ifdef SIMULATION_BUILD
    if (irq >= BCMOS_MAX_IRQS)
    {
        BCMOS_TRACE_ERR("irq %d is out of range\n", irq);
        return BCM_ERR_RANGE;
    }
    if (isr_handler[irq])
    {
        BCMOS_TRACE_ERR("irq %d is already connected\n", irq);
        return BCM_ERR_ALREADY;
    }
    isr_handler[irq] = isr;
    isr_priv[irq] = priv;
#endif
    return 0;
}

void bcmos_int_disconnect(int irq, void *priv)
{
#ifdef SIMULATION_BUILD
    isr_handler[irq] = NULL;
    isr_priv[irq] = NULL;
#endif
}

#ifdef SIMULATION_BUILD
void bcmos_int_fire(int irq)
{
    if (irq >= BCMOS_MAX_IRQS)
    {
        BCMOS_TRACE_ERR("irq %d is out of range\n", irq);
        return;
    }
    if (!irq_enabled[irq])
    {
        BCMOS_TRACE_ERR("irq %d is disabled\n", irq);
        return;
    }
    if (!isr_handler[irq])
    {
        BCMOS_TRACE_ERR("irq %d is not connected\n", irq);
        return;
    }
    isr_handler[irq](irq, isr_priv[irq]);
}
#endif

/* Convert IPv4/IPv6 address from internal presentation to string */
bcmos_errno bcmos_ip_to_str(const bcmos_ip_address *ip, char *ip_str, int32_t ip_str_size)
{
    const char *dst = NULL;
    if (ip == NULL || ip_str == NULL)
        return BCM_ERR_PARM;
    if (ip->version == BCMOS_IP_VERSION_4)
    {
        struct in_addr addr = { .s_addr = ip->ipv4.u32 };
        dst = inet_ntop(AF_INET, &addr, ip_str, ip_str_size);
    }
    else if (ip->version == BCMOS_IP_VERSION_6)
    {
        struct in6_addr addr;
        memcpy(addr.s6_addr, ip->ipv6.u8, sizeof(addr.s6_addr));
        dst = inet_ntop(AF_INET6, &addr, ip_str, ip_str_size);
    }
    return (dst != NULL) ? BCM_ERR_OK : BCM_ERR_PARM;
}

/* Convert IPv4/IPv6 address from string to internal presentation */
bcmos_errno bcmos_str_to_ip(const char *ip_str, bcmos_ip_address *ip)
{
    if (ip == NULL || ip_str == NULL)
        return BCM_ERR_PARM;
    if (strchr(ip_str, ':') == NULL)
    {
        struct in_addr addr;
        if (!inet_aton(ip_str, &addr))
            return BCM_ERR_PARM;
        ip->version = BCMOS_IP_VERSION_4;
        ip->ipv4.u32 = addr.s_addr;
    }
    else
    {
        struct in6_addr addr;
        if (!inet_pton(AF_INET6, ip_str, &addr))
            return BCM_ERR_PARM;
        ip->version = BCMOS_IP_VERSION_6;
        memcpy(ip->ipv6.u8, addr.s6_addr, sizeof(ip->ipv6.u8));
    }
    return BCM_ERR_OK;
}


#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT

#ifdef BCMOS_MSG_QUEUE_UDP_SOCKET

static bcmos_errno _bcmos_parse_ip_port(const char *s, struct sockaddr_in *sa)
{
    uint32_t ip;
    int n;
    uint32_t ip1, ip2, ip3, ip4, port;

    /* ToDo: add support for
     * - host name
     * - IPv6
     */
    n = sscanf(s, "%u.%u.%u.%u:%u", &ip1, &ip2, &ip3, &ip4, &port);
    if (n != 5 || ip1 > 0xff || ip2 > 0xff || ip3 > 0xff || ip4 > 0xff || port > 0xffff)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Can't parse %s. Must be ip_address:port\n", s);
    }
    ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
    sa->sin_family = AF_INET;
    sa->sin_port = htons(port);
    sa->sin_addr.s_addr = htonl(ip);

    return BCM_ERR_OK;
}

#endif

bcmos_errno bcmos_msg_address_parse(const char *addr_string, bcmos_msg_queue_ep_type ep_type, bcmos_msg_addr *addr)
{
    bcmos_errno rc = BCM_ERR_OK;;

    if (!addr_string || !addr || !addr->len || !addr->addr)
        return BCM_ERR_PARM;

    switch (ep_type)
    {
#ifdef BCMOS_MSG_QUEUE_DOMAIN_SOCKET
    case BCMOS_MSG_QUEUE_EP_DOMAIN_SOCKET:   /**< Domain-socket address */
    {
        struct sockaddr_un sa = {};
        /* In linux path can start from 0 character */
        if (addr->len < sizeof(sa))
            return BCM_ERR_OVERFLOW;

        sa.sun_family = AF_UNIX;
        addr->type = ep_type;
        addr->len = sizeof(sa);
        strncpy(sa.sun_path, addr_string, sizeof(sa.sun_path) - 1);
        /* In linux path can start from 0 character */
        if (!sa.sun_path[0])
            strncpy(&sa.sun_path[1], addr_string + 1, sizeof(sa.sun_path) - 2);
        memcpy(addr->addr, &sa, sizeof(sa));
        break;
    }
#endif

#ifdef BCMOS_MSG_QUEUE_UDP_SOCKET
    case BCMOS_MSG_QUEUE_EP_UDP_SOCKET:      /**< UDP socket-based address in format ipv4_addr:udp_port */
    {
        struct sockaddr_in in = {};
        if (addr->len < sizeof(struct sockaddr_in))
            return BCM_ERR_OVERFLOW;
        rc = _bcmos_parse_ip_port(addr_string, &in);
        if (rc != BCM_ERR_OK)
            break;
        addr->type = ep_type;
        addr->len = sizeof(struct sockaddr_in);
        memcpy(addr->addr, &in, sizeof(struct sockaddr_in));
        break;
    }
#endif

    default:
        rc = BCM_ERR_NOT_SUPPORTED;
    }

    return rc;
}

#endif


/* Functions common for domain socket and UDP socket - based message queues */
#if defined(BCMOS_MSG_QUEUE_DOMAIN_SOCKET) || defined(BCMOS_MSG_QUEUE_UDP_SOCKET)

/** "send" to socket */
static bcmos_errno _bcmos_socket_send(bcmos_msg_queue *queue, bcmos_msg *m, uint8_t *buf, uint32_t buf_length)
{
    int rc;
    struct iovec iov = { .iov_base = buf, .iov_len = buf_length };
    struct msghdr msg = {
        .msg_iov = &iov, .msg_iovlen = 1, .msg_flags = 0,
        .msg_name = (void *)queue->ep_extra_data, .msg_namelen = queue->ep_extra_data_size
    };
    /* We must have transmit address either in message queue remote endpoint
     * or in the message itself. Otherwise, transmit is not supported */
    if (!queue->ep_extra_data_size)
    {
        if (!m->addr.len)
        return BCM_ERR_NOT_SUPPORTED;
        msg.msg_name = m->addr.addr;
        msg.msg_namelen = m->addr.len;
    }
    rc = sendmsg(queue->ep, &msg, 0);
    return (rc == buf_length) ? BCM_ERR_OK : BCM_ERR_COMM_FAIL;
}

/** "recv" from socket */
static bcmos_errno _bcmos_socket_recv(bcmos_msg_queue *queue, uint32_t timeout, uint8_t **buf, uint32_t *buf_length)
{
    struct iovec iov = { .iov_base = queue->recv_buf, .iov_len = queue->q.parm.max_mtu };
    struct msghdr msg = {
        .msg_iov = &iov, .msg_iovlen = 1,
        .msg_name = queue->last_addr.addr, .msg_namelen = BCMOS_MSG_MAX_ADDR_LENGTH
    };
    int rc;
    int wait = 0;

    if (timeout && timeout != BCMOS_WAIT_FOREVER)
    {
        fd_set read_fds;
        struct timeval tv;

        FD_ZERO(&read_fds);
        FD_SET(queue->ep, &read_fds);
        tv.tv_sec = timeout / 1000000;
        tv.tv_usec = (timeout % 1000000) * 1000;
        rc = select(queue->ep + 1, &read_fds, NULL, NULL, &tv);
        if (rc < 0)
        {
            return BCM_ERR_COMM_FAIL;
        }
        if (!rc || !FD_ISSET(queue->ep, &read_fds))
            return BCM_ERR_TIMEOUT;
        wait = MSG_DONTWAIT;
    }

    rc = recvmsg(queue->ep, &msg, wait);
    if (rc < 0)
    {
        return BCM_ERR_COMM_FAIL;
    }
    if (rc == 0)
        return BCM_ERR_NOENT;

    queue->last_addr.len = msg.msg_namelen;
    *buf = queue->recv_buf;
    *buf_length = rc;
    return BCM_ERR_OK;
}


static bcmos_errno _bcmos_socket_close(bcmos_msg_queue *queue)
{
    /* Close domain socket */
    if (queue->ep > 0)
    {
        close(queue->ep);
    }
    if (queue->ep_extra_data)
    {
        bcmos_free(queue->ep_extra_data);
    }
    if (queue->last_addr.addr)
    {
        bcmos_free(queue->last_addr.addr);
    }
    return BCM_ERR_OK;
}


/* Pack message for over-the-socket transmission.
 * This function is good for case when both queue ends are on the same CPU
 * and there is no need to do any translation.
 */
static bcmos_errno _bcmos_transparent_pack(bcmos_msg_queue *queue, bcmos_msg *msg, uint8_t **buf, uint32_t *buf_length)
{
    uint32_t size = BCMOS_MSG_HDR_SIZE + msg->size;

    if (size > queue->q.parm.max_mtu)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_OVERFLOW, "Attempt to send message longer than configured max_mtu %u > %u\n",
            size, queue->q.parm.max_mtu);
    }
    /* If there is sufficient head-room in the message, pack header in place.
     * Otherwise, copy the entire message to send_buf.
     */
    if (msg->start && msg->data && ((unsigned long)msg->data - (unsigned long)msg->start >= BCMOS_MSG_HDR_SIZE))
    {
        bcmos_msg_hdr_pack(msg, (uint8_t *)msg->data - BCMOS_MSG_HDR_SIZE, msg->size);
        *buf = (uint8_t *)msg->data - BCMOS_MSG_HDR_SIZE;
    }
    else
    {
    bcmos_msg_hdr_pack(msg, queue->send_buf, msg->size);
    if (msg->size)
    {
        BUG_ON(msg->data == NULL);
        memcpy(queue->send_buf + BCMOS_MSG_HDR_SIZE, msg->data, msg->size);
    }
    *buf = queue->send_buf;
    }
    *buf_length = size;
    return BCM_ERR_OK;
}

/** "unpack" message. In case of domain socket both queue ends are in the same CPU.
 * Message is sent as-is
 */
static bcmos_errno _bcmos_transparent_unpack(bcmos_msg_queue *queue, uint8_t *buf, uint32_t buf_length, bcmos_msg **msg)
{
    bcmos_msg *m;
    uint8_t *data_ptr;

    if (buf_length < BCMOS_MSG_HDR_SIZE)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_INTERNAL, "Received message is too short (%u)\n", buf_length);
    }

    /* Adjust buf_length to account for difference in packed and unpacked message header sizes */
    buf_length -= BCMOS_MSG_HDR_SIZE;
    buf_length += sizeof(bcmos_msg);
    buf_length += queue->last_addr.len;

    m = bcmos_alloc(buf_length);
    if (!m)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_NOMEM, "Received message discarded: %u bytes\n", buf_length);
    }

    bcmos_msg_hdr_unpack(buf, m);
    m->release = NULL;
    m->data_release = NULL;
    if (m->size != buf_length - sizeof(bcmos_msg) - queue->last_addr.len)
    {
        BCMOS_TRACE_ERR("Received message is insane. Expected data length %u, got %lu\n",
            m->size, buf_length - sizeof(bcmos_msg));
        bcmos_free(m);
        return BCM_ERR_INTERNAL;
    }

    data_ptr = (uint8_t *)(m + 1);
    if (queue->last_addr.len)
    {
        m->addr.addr = data_ptr;
        m->addr.len = queue->last_addr.len;
        memcpy(m->addr.addr, queue->last_addr.addr, queue->last_addr.len);
        data_ptr += queue->last_addr.len;;
    }
    else
    {
        m->addr.addr = NULL;
        m->addr.len = 0;
    }

    if (m->size)
    {
        m->data = m->start = data_ptr;
        memcpy(m->data, &buf[BCMOS_MSG_HDR_SIZE], m->size);
    }
    else
    {
        m->data = m->start = NULL;
    }

    *msg = m;

    return BCM_ERR_OK;
}


#endif

/* Domain-socket-based inter-process communication */
#ifdef BCMOS_MSG_QUEUE_DOMAIN_SOCKET

bcmos_errno bcmos_sys_msg_queue_domain_socket_open(bcmos_msg_queue *queue)
{
    struct sockaddr_un sa;
    bcmos_msg_addr addr = { .len = sizeof(sa), .addr = &sa };
    bcmos_errno rc = BCM_ERR_PARM;

    do
    {
        /* Open domain socket */
        queue->ep = socket(AF_UNIX, SOCK_DGRAM, 0);
        if (queue->ep < 0)
        {
            BCMOS_TRACE_ERR("Can't create domain socket. error %s\n", strerror(errno));
            break;
        }

        /* If local_ep_address is set - the queue supports receive */
        if (queue->q.parm.local_ep_address)
        {
            rc = bcmos_msg_address_parse(queue->q.parm.local_ep_address, BCMOS_MSG_QUEUE_EP_DOMAIN_SOCKET, &addr);
            if (rc)
            {
                BCMOS_TRACE_ERR("Can't parse domain socket address %s. error %s\n",
                    queue->q.parm.local_ep_address, bcmos_strerror(rc));
                break;
            }
            if (bind(queue->ep, (struct sockaddr *)&sa, sizeof(sa)) < 0)
            {
                int err = errno;
                BCMOS_TRACE_ERR("Can't bind domain socket to %s. error %s\n",
                queue->q.parm.local_ep_address, strerror(err));
                rc = BCM_ERR_PARM;
                break;
            }
        }

        /* If remote_ep_address is set - the queue supports transmit */
        if (queue->q.parm.remote_ep_address)
        {
            queue->ep_extra_data = bcmos_calloc(sizeof(struct sockaddr_un));
            if (!queue->ep_extra_data)
            {
                rc = BCM_ERR_NOMEM;
                break;
            }
            rc = bcmos_msg_address_parse(queue->q.parm.remote_ep_address, BCMOS_MSG_QUEUE_EP_DOMAIN_SOCKET, &addr);
            if (rc)
            {
                BCMOS_TRACE_ERR("Can't parse domain socket address %s. error %s\n",
                    queue->q.parm.remote_ep_address, bcmos_strerror(rc));
                break;
            }
            memcpy(queue->ep_extra_data, &sa, sizeof(sa));
            queue->ep_extra_data_size = sizeof(sa);
        }

        /* Allocate storage for last sender's address */
        queue->last_addr.addr = bcmos_calloc(BCMOS_MSG_MAX_ADDR_LENGTH);
        if (!queue->last_addr.addr)
        {
            rc = BCM_ERR_NOMEM;
            break;
        }

        /* Set callbacks */
        queue->q.parm.close = _bcmos_socket_close;
        queue->q.parm.send = _bcmos_socket_send;
        queue->q.parm.recv = _bcmos_socket_recv;
        if (!queue->q.parm.pack)
            queue->q.parm.pack = _bcmos_transparent_pack;
        if (!queue->q.parm.unpack)
            queue->q.parm.unpack = _bcmos_transparent_unpack;

        rc = BCM_ERR_OK;

    } while (0);

    if (rc)
        _bcmos_socket_close(queue);

    return rc;
}

#endif

/* UDP-socket-based inter-process communication */
#ifdef BCMOS_MSG_QUEUE_UDP_SOCKET

bcmos_errno bcmos_sys_msg_queue_udp_socket_open(bcmos_msg_queue *queue)
{
    struct sockaddr_in sa;
    bcmos_msg_addr addr = { .len = sizeof(sa), .addr = &sa };
    bcmos_errno rc = BCM_ERR_PARM;

    do
    {
        /* Open UDP socket */
        queue->ep = socket(AF_INET, SOCK_DGRAM, 0);
        if (queue->ep < 0)
        {
            BCMOS_TRACE_ERR("Can't create UDP socket. error %s\n", strerror(errno));
            break;
        }

        /* If local_ep_address is set - the queue supports receive */
        if (queue->q.parm.local_ep_address)
        {
            rc = bcmos_msg_address_parse(queue->q.parm.local_ep_address, BCMOS_MSG_QUEUE_EP_UDP_SOCKET, &addr);
            if (rc)
            {
                BCMOS_TRACE_ERR("Can't parse UDP socket address %s. error %s\n",
                    queue->q.parm.local_ep_address, bcmos_strerror(rc));
                break;
            }
            if (bind(queue->ep, (struct sockaddr *)&sa, sizeof(sa)) < 0)
            {
                int err = errno;
                BCMOS_TRACE_ERR("Can't bind UDP socket to %s. error %s\n",
                queue->q.parm.local_ep_address, strerror(err));
                rc = BCM_ERR_PARM;
                break;
            }
        }

        /* If remote_ep_address is set - the queue supports transmit */
        if (queue->q.parm.remote_ep_address)
        {
            queue->ep_extra_data = bcmos_calloc(sizeof(sa));
            if (!queue->ep_extra_data)
            {
                rc = BCM_ERR_NOMEM;
                break;
            }
            rc = bcmos_msg_address_parse(queue->q.parm.remote_ep_address, BCMOS_MSG_QUEUE_EP_UDP_SOCKET, &addr);
            if (rc)
            {
                BCMOS_TRACE_ERR("Can't parse domain socket address %s. error %s\n",
                    queue->q.parm.remote_ep_address, bcmos_strerror(rc));
                break;
            }
            memcpy(queue->ep_extra_data, &sa, sizeof(sa));
            queue->ep_extra_data_size = sizeof(sa);
        }

        /* Allocate storage for last sender's address */
        queue->last_addr.addr = bcmos_calloc(BCMOS_MSG_MAX_ADDR_LENGTH);
        if (!queue->last_addr.addr)
        {
            rc = BCM_ERR_NOMEM;
            break;
        }

        /* Set callbacks */
        queue->q.parm.close = _bcmos_socket_close;
        queue->q.parm.send = _bcmos_socket_send;
        queue->q.parm.recv = _bcmos_socket_recv;
        if (!queue->q.parm.pack)
            queue->q.parm.pack = _bcmos_transparent_pack;
        if (!queue->q.parm.unpack)
            queue->q.parm.unpack = _bcmos_transparent_unpack;

        rc = BCM_ERR_OK;

    } while (0);

    if (rc)
        _bcmos_socket_close(queue);

    return rc;
}
#endif

/*
 * File IO
 */

bcmos_file *bcmos_file_open(const char *path, bcmos_file_flag flags)
{
    FILE *fd;
    char *mode;

    if (flags & BCMOS_FILE_FLAG_APPEND)
        mode = "a";
    else if ((flags & (BCMOS_FILE_FLAG_READ | BCMOS_FILE_FLAG_WRITE)) == (BCMOS_FILE_FLAG_READ | BCMOS_FILE_FLAG_WRITE))
        mode = "r+";
    else if (flags & BCMOS_FILE_FLAG_READ)
        mode = "r";
    else if (flags & BCMOS_FILE_FLAG_WRITE)
        mode = "w";
    else
        return NULL;

    fd = fopen(path, mode);

    return (bcmos_file *)fd;
}

int bcmos_file_read(bcmos_file *file, void *data, uint32_t size)
{
    uint32_t bytes_read;

    bytes_read = fread(data, 1, size, (FILE *)file);
    if ((bytes_read < size) && ferror((FILE *)file))
    {
        BCMOS_TRACE_ERR("fread returned error %s\n", strerror(errno));
        return (int)BCM_ERR_IO;
    }
    return (int)bytes_read;
}

int bcmos_file_write(bcmos_file *file, const void *data, uint32_t size)
{
    uint32_t bytes_written;
    bytes_written = fwrite(data, 1, size, (FILE *)file);
    if ((bytes_written < size) && ferror((FILE *)file))
    {
        BCMOS_TRACE_ERR("fwrite returned error %s\n", strerror(errno));
        return (int)BCM_ERR_IO;
    }
    return (int)bytes_written;
}

bcmos_errno bcmos_file_seek(bcmos_file *file, unsigned long offset)
{
    int rc;
    rc = fseek((FILE *)file, offset, SEEK_SET);
    if (rc)
    {
        BCMOS_TRACE_ERR("fseek returned error %s\n", strerror(errno));
        return (int)BCM_ERR_IO;
    }
    return BCM_ERR_OK;
}

void bcmos_file_close(bcmos_file *file)
{
    fclose((FILE *)file);
}

char *bcmos_file_gets(bcmos_file *file, char *s, int size)
{
    return fgets(s, size, (FILE *)file);
}

void * __attribute__((weak)) bcmos_dma_alloc(uint8_t device, uint32_t size, dma_addr_t *dma_addr)
{
    void *ptr = bcmos_alloc(size);

    if (!ptr)
        return NULL;
    if (dma_addr)
        *dma_addr = bcmos_virt_to_phys(ptr);
    return ptr;

}

void __attribute__((weak)) bcmos_dma_free(uint8_t device, void *ptr)
{
    bcmos_free(ptr);
}


void  __attribute__((weak)) bcm_pci_write32(volatile uint32_t *address, uint32_t value)
{
#ifdef PCIE_HW_ENDIAN_SWAP
    *address = BCMOS_ENDIAN_CPU_TO_BIG_U32(value);
#else
    *address = BCMOS_ENDIAN_CPU_TO_LITTLE_U32(value);
#endif
}

uint32_t  __attribute__((weak)) bcm_pci_read32(const volatile uint32_t *address)
{
#ifdef PCIE_HW_ENDIAN_SWAP
    return BCMOS_ENDIAN_BIG_TO_CPU_U32(*address);
#else
    return BCMOS_ENDIAN_LITTLE_TO_CPU_U32(*address);
#endif
}
