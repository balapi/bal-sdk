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

/*
 * bcmos_system.h
 * Maple System Services
 * posix port: simulation
 */

#ifndef BCMOS_SYSTEM_H_
#define BCMOS_SYSTEM_H_
#if (!defined(__cplusplus) && !defined(_GNU_SOURCE))
    #define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <ctype.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <execinfo.h>
#include <limits.h>
#include <stdarg.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>
#include <inttypes.h>

/* posix port has only been tested in linux user space */
#define LINUX_USER_SPACE

/* Re-define GNU typeof as ISO __typeof__ */
#define typeof __typeof__

void _bcmos_backtrace(void);

#define BUG_ON_PRINT(condition, fmt, args...) \
    do \
    { \
        if (condition) \
        { \
            BCMOS_TRACE_ERR(fmt, ##args); \
            BCMOS_TRACE_ERR("Condition: " #condition); \
            abort(); \
        } \
    } while (0)

#define BUG_ON(condition)     BUG_ON_PRINT((condition), "BUG in %s %d!\n", __FUNCTION__, __LINE__)
#define BUG()                 BUG_ON(1)
#define BUG_UNLESS(condition) BUG_ON(!(condition))

/* If 'err' is not BCM_ERR_OK, there is a bug in the software - halt and print the specified message */
#define BUG_ON_ERROR(err, fmt, args...) \
    BUG_ON_PRINT((err) != BCM_ERR_OK, \
        "%s:%d: err=%s (%d): " fmt, \
        __FUNCTION__, __LINE__, bcmos_strerror(err), (err), ##args)

/* Specify here which system functions are inlined */

#define BCMOS_FASTLOCK_INLINE
/* #define BCMOS_SEM_WAIT_INLINE */
#define BCMOS_SEM_POST_INLINE
#define BCMOS_TRACE_PRINTF
/* #define BCMOS_BYTE_POOL_ALLOC_FREE_INLINE */
/* #define BCMOS_MALLOC_FREE_INLINE */
/* #define BCMOS_CALLOC_INLINE */
/* #define BCMOS_DMA_ALLOC_FREE_INLINE */
#define BCMOS_VIRT_TO_PHYS_INLINE
#define BCMOS_CACHE_INLINE

/* Supports file IO */
#define BCMOS_FILE_IO_OS_SPECIFIC

#include "bcmos_common.h"

/* posix-specific stuff */

/*
 * Synchronization
 */

/** \addtogroup system_mutex
 * @{
 */

/** Mutex control block */
struct bcmos_mutex
{
    pthread_mutex_t m;          /**< pthread mutex */
    pthread_mutexattr_t attr;   /**< pthread mutex attribute */
};

/** @} system_mutex */

/** \addtogroup system_fastlock
 * @{
 */

/** Fast lock control block */
struct bcmos_fastlock
{
    bcmos_mutex m;
};

/** Fastlock initializer. Can be used instead of calling bcmos_fastlock_init() */
#define BCMOS_FASTLOCK_INITIALIZER      { { PTHREAD_MUTEX_INITIALIZER } }

/* Init fastlock */
static inline void bcmos_fastlock_init(bcmos_fastlock *lock, uint32_t flags)
{
    bcmos_mutex_create(&lock->m, 0, NULL);
}

/* Take fast lock */
static inline long bcmos_fastlock_lock(bcmos_fastlock *lock)
{
    bcmos_mutex_lock(&lock->m);
    return 0;
}

/* Release fast lock */
static inline void bcmos_fastlock_unlock(bcmos_fastlock *lock, long flags)
{
    bcmos_mutex_unlock(&lock->m);
}

/** @} system_fastlock */

/** \addtogroup system_sem
 * @{
 */

/** Semaphore control block */
struct bcmos_sem
{
    sem_t s;            /**< pthread semaphore */
};

/* Increment semaphore counter */
static inline void bcmos_sem_post(bcmos_sem *sem)
{
    sem_post(&sem->s);
}

/** @} system_sem */

/** \addtogroup system_timer
 * @{
 */

/** System timer */
struct bcmos_sys_timer
{
    timer_t t;                          /**< librt timer */
    bcmos_sys_timer_handler handler;    /**< Timer handler */
    bcmos_bool destroyed;               /**< BCMOS_TRUE if the timer has been destroyed */
    void *data;                         /**< Parameter to be passed to the handler */
};

/** @} system_timer */

/** \addtogroup system_task
 * @{
 */

/* Default stack size (bytes).
 * PTHREAD_STACK_MIN will be added to this value when creating threads (to account for OS overheads). */
#define BCMOS_DEFAULT_STACK_SIZE (80 * 1024)

/** OS-specific task control block extension */
typedef struct bcmos_sys_task
{
    pthread_t t;                        /**< posix pthread */
} bcmos_sys_task;

/** @} system_task */

/** \addtogroup byte_pool
 * @{
 */

/** Memory pool control block */
struct bcmos_byte_pool
{
    bcmos_byte_pool_parm parm;  /**< Pool parameters */
    uint32_t allocated;         /**< Number of bytes allocated */
#ifdef BCMOS_MEM_CHECK
    uint32_t magic;             /**< magic number */
#define BCMOS_BYTE_POOL_VALID           (('b'<<24) | ('y' << 16) | ('p' << 8) | 'o')
#define BCMOS_BYTE_POOL_DELETED         (('b'<<24) | ('y' << 16) | ('p' << 8) | '~')
#endif
};

/** @} */

/* Print */
#define bcmos_sys_vprintf(fmt, args)        vprintf(fmt, args)

/* A few macros to enable linux kernel space compilation */
#define EXPORT_SYMBOL(_sym)

/*
 * The following low-level functions are mostly for simulation
 */

/*
 * DMA-able memory allocation
 */

#define BCMOS_DMA_ADDR_T_DEFINED
typedef unsigned long dma_addr_t;

/* Convert virtual address to physical address */
static inline unsigned long bcmos_virt_to_phys(volatile void *va)
{
    return (unsigned long)(va);
}

/* Invalidate address area in data cache. Dirty cache lines content is discarded. */
static inline void bcmos_dcache_inv(void *start, uint32_t size)
{
}

/* Flush address area in data cache. Dirty cache lines are committed to memory. */
static inline void bcmos_dcache_flush(void *start, uint32_t size)
{
}

/* write barrier */
static inline void bcmos_barrier(void)
{
}

/* Write 32 bit word to address across PCIs bus */
void bcm_pci_write32(volatile uint32_t *address, uint32_t value);

/* Read 32 bit word across PCIE bus */
uint32_t bcm_pci_read32(const volatile uint32_t *address);

/* Check in-irq status */
static inline bcmos_bool is_irq_mode(void)
{
    return BCMOS_FALSE;
}

/* Check if interrupts are disabled */
static inline bcmos_bool is_irq_disabled(void)
{
    return BCMOS_FALSE;
}

/* High-precision sleep is not available in POSIX, so fall back to default sleep. */
static inline void bcmos_precision_usleep(uint32_t timeout)
{
    bcmos_usleep(timeout);
}

#ifdef SIMULATION_BUILD

#define BCMOS_IRQ_SINGLE         0
#define BCMOS_IRQ_SHARED         1
#define BCMOS_IRQ_EDGE_TRIGGERED 2

/* Fire interrupt if enabled */
void bcmos_int_fire(int irq);

#endif

/*
 * Internal (to OS abstraction) functions for messaging over domain and UDP sockets
 */
#ifdef BCMOS_MSG_QUEUE_DOMAIN_SOCKET
bcmos_errno bcmos_sys_msg_queue_domain_socket_open(bcmos_msg_queue *queue);
#endif

#ifdef BCMOS_MSG_QUEUE_UDP_SOCKET
bcmos_errno bcmos_sys_msg_queue_udp_socket_open(bcmos_msg_queue *queue);
#endif

/* 2nd part of OS-independent declarations */
#include "bcmos_common2.h"

#endif /* BCMOS_SYSTEM_H_ */
