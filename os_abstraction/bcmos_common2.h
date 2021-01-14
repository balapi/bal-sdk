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

#ifndef BCMOS_COMMON2_H_
#define BCMOS_COMMON2_H_

#ifndef BCMOS_SYSTEM_H_
#error Please do not include bcmos_common2.h directly. Include bcmos_system.h
#endif

/* \addtogroup system
 * @{
 */

#ifndef likely
#define likely(x)     (x)
#endif

#ifndef unlikely
#define unlikely(x)     (x)
#endif

#define BCMOS_MAX_NAME_LENGTH   48

/** \addtogroup system_task
 * @{
 */

/** Task control block */
struct bcmos_task
{
    /* OS independent fields */
    bcmos_task_parm parm;               /**< Task creation parameters */
    bcmos_module *modules[BCMOS_MAX_MODULES_PER_TASK];
    uint32_t active_modules;            /**< Bitmask of modules for which events are pending */
    bcmos_sem active_sem;               /**< Semaphore used to wait for module activity */
    bcmos_fastlock active_lock;         /**< Lock protecting active_modules */
    bcmos_module_id current_module;     /**< Current module */
    bcmos_bool destroy_request;         /**< Task destroy request pending */
    bcmos_bool destroyed;               /**< Set by task handler before it terminates */
    STAILQ_ENTRY(bcmos_task) list;      /**< Next task pointer */
    char name[BCMOS_MAX_NAME_LENGTH];   /**< Task name */
    bcmos_sys_task sys_task;            /**< OS-specific task extension */
    uint32_t magic;                     /* magic number */
#define BCMOS_TASK_MAGIC                (('t' << 24) | ('a' << 16) | ('s' << 8) | 'k')
#define BCMOS_TASK_MAGIC_DESTROYED      (('t' << 24) | ('a' << 16) | ('s' << 8) | '~')
};

/** \addtogroup system_mem
 * @{
 */

#ifndef BCMOS_CALLOC_INLINE

/** Allocate memory from the main heap and clear it
 * \ingroup system_heap
 * \param[in]   size
 * \returns memory block pointer or NULL
 */
#ifndef BCMOS_HEAP_DEBUG
static inline void *bcmos_calloc(uint32_t size)
{
    void *ptr = bcmos_alloc(size);
#else
static inline void *_bcmos_calloc(uint32_t size)
{
    void *ptr = _bcmos_alloc(size);
#endif
    if (ptr)
    {
        /* If using heap debug feature, the pointer returned by _bcmos_alloc() is the user pointer, meaning after the debug header. */
#ifdef BCMOS_HEAP_DEBUG
        size -= BCMOS_HEAP_DEBUG_OVERHEAD;
#endif
        memset(ptr, 0, size);
    }
    return ptr;
}

#endif /* #ifndef BCMOS_CALLOC_INLINE */

#ifndef BCMOS_DMA_ADDR_T_DEFINED
typedef unsigned long dma_addr_t;
#endif

#ifndef BCMOS_DMA_ALLOC_FREE_INLINE

/** Allocate DMA-able memory
 * \param[in]   device   Device id
 * \param[in]   size     Block size (bytes)
 * \param[out]  dma_addr DMA address
 * \returns memory block pointer or NULL
 */
void *bcmos_dma_alloc(uint8_t device, uint32_t size, dma_addr_t *dma_addr);

/** Release DMA-able memory
 * \param[in]   device   Device id
 * \param[in]   ptr      Block pointer
 */
void bcmos_dma_free(uint8_t device, void *ptr);

#endif /* #ifndef BCMOS_DMA_ALLOC_FREE_INLINE */

#ifndef BCMOS_VIRT_TO_PHYS_INLINE

/** Convert virtual address to physical address
 *
 * \param[in]   va      Virtual address
 * \returns - physical address va is mapped to
 */
unsigned long bcmos_virt_to_phys(void *va);

#endif /* #ifndef BCMOS_VIRT_TO_PHYS_INLINE */

/** @} */

/** \addtogroup blk_pool
 * @{
 */

/* Memory block header */
typedef struct bcmos_memblk bcmos_memblk;

/* Memory block list */
typedef STAILQ_HEAD(, bcmos_memblk) bcmos_memblk_list;

/* Block memory pool control block */
struct bcmos_blk_pool
{
    bcmos_fastlock lock;        /**< Pool protection lock */
    bcmos_memblk_list free_list;/**< Free block list */
#ifdef BCMOS_BLK_POOL_DEBUG
    DLIST_HEAD(, bcmos_memblk) allocated_list; /**< Allocated block list */
#endif
    bcmos_blk_pool_parm parm;   /**< Pool parameters */
    bcmos_blk_pool_stat stat;   /**< Pool statistics */
    void *start;                /**< Pool start pointer */
    char name[BCMOS_MAX_NAME_LENGTH];   /**< Pool name */
    uint32_t magic;             /**< magic number */
#define BCMOS_BLK_POOL_VALID            (('b'<<24) | ('l' << 16) | ('p' << 8) | 'o')
#define BCMOS_BLK_POOL_DELETED          (('b'<<24) | ('l' << 16) | ('p' << 8) | '~')
    STAILQ_ENTRY(bcmos_blk_pool) list; /* Pool list */
};

/* Total memory occupied by all block pools */
extern uint32_t bcmos_total_blk_pool_size;

/** @} blk_pool */

/** \addtogroup system_msg
 * @{
 */

/** Release message
 * \param[in]   msg             Message handle
 */
static inline void bcmos_msg_free(bcmos_msg *msg)
{
    if (msg->release)
    {
        msg->release(msg);
    }
    else
    {
        bcmos_free(msg);
    }
}

typedef STAILQ_HEAD(, bcmos_msg) bcmos_msg_list;

/** Simple Message queue control block.
 * Simple message queue doesn't support waiting on.
 * It is used in module queue mechanisms.
 */
typedef struct bcmos_msg_queue_nw
{
    bcmos_msg_queue_parm parm;  /**< Queue parameters */
    bcmos_msg_queue_stat stat;  /**< Queue statistics */
    bcmos_fastlock lock;        /**< Queue protection lock */
    bcmos_msg_list msgl;        /**< Message list */
    bcmos_msg_list msgl_urg;    /**< Urgent message list */
    uint32_t flags;             /**< Queue flags */
} bcmos_msg_queue_nw;

/** Message queue control block */
struct bcmos_msg_queue
{
    bcmos_msg_queue_nw q;       /**< Queue control block */
    bcmos_sem m;                /**< Mutex to suspend waiting task on */
    bcmos_bool is_waiting;      /**< TRUE if task is waiting on queue */
    char name[BCMOS_MAX_NAME_LENGTH];   /**< Queue name */
#ifdef BCMOS_MSG_QUEUE_REMOTE_SUPPORT
    long ep;                    /**< Endpoint handle (e.g., socket) */
    void *ep_extra_data;        /**< Extra data - depending on ep type */
    uint32_t ep_extra_data_size;/**< Extra data size */
    uint8_t *send_buf;          /**< Send buffer */
    uint8_t *recv_buf;          /**< Receive buffer */
    bcmos_msg_addr last_addr;   /**< Sender address of the last received message */
#define BCMOS_MSG_MAX_ADDR_LENGTH        256         /**< Max sender address length */
    bcmos_mutex send_lock;      /**< Mutex that protects send_buf */
#endif
    uint32_t magic;             /**< magic number */
#define BCMOS_MSG_QUEUE_VALID           (('m'<<24) | ('q' << 16) | ('u' << 8) | 'e')
#define BCMOS_MSG_QUEUE_DELETED         (('m'<<24) | ('q' << 16) | ('u' << 8) | '~')
    STAILQ_ENTRY(bcmos_msg_queue) list; /* Queue list */
};

/** Message queue group control block */
struct bcmos_msg_qgroup
{
    bcmos_msg_qgroup_parm parm; /**< Queue group parameters */
    bcmos_msg_list *msgl;       /**< Array of parm.nqueues message lists */
    bcmos_msg_queue_stat stat;  /**< Queue group statistics */
    bcmos_sem m;                /**< Mutex to suspend waiting task on */
    bcmos_fastlock lock;        /**< Queue group protection lock */
    uint32_t active_mask;       /**< Bitmask of queues containing messages */
    bcmos_bool is_waiting;      /**< TRUE if task is waiting on queue group */
    char name[BCMOS_MAX_NAME_LENGTH];   /**< Queue group name */
    uint32_t magic;             /**< magic number */
#define BCMOS_MSG_QGROUP_VALID           (('m'<<24) | ('q' << 16) | ('g' << 8) | 'r')
#define BCMOS_MSG_QGROUP_DELETED         (('m'<<24) | ('q' << 16) | ('g' << 8) | '~')
    STAILQ_ENTRY(bcmos_msg_qgroup) list; /* Queue group list */
};

/** Message pool control block */
struct bcmos_msg_pool
{
    bcmos_blk_pool blk_pool;    /**< Underlying block memory pool */
    bcmos_msg_pool_parm parm;   /**< Pool parameters */
};

/* Total memory occupied by all message pools */
extern uint32_t bcmos_total_msg_pool_size;

/** @} system_msg */

/** \addtogroup system_timer */

/* Timer precision. Must be a multiple of 2.
 * Timed expiration timestamp is rounded up to the nearest multiple of timer precision
 */
#define BCMOS_TIMER_PRECISION_US        32
#if (BCMOS_TIMER_PRECISION_US & (BCMOS_TIMER_PRECISION_US - 1))
    #error BCMOS_TIMER_PRECISION_US must be a multiple of 2
#endif

/* There are 2 timer implementations
 * - DLIST-based - works well when most of active timers have the same duration
 * - RB-tree based - more expensive in simple case, but scales better for large number of timers
 *                   with arbitrary durations
 */
#define BCMOS_TIMER_RB_TREE

/** Timer control block */
struct bcmos_timer
{
    bcmos_msg msg;                      /**< Timer message */
    bcmos_timer_parm parm;              /**< Timer parameters */
    F_bcmos_timer_handler handler;      /**< Timer handler */
    uint32_t period;                    /**< Timer period (us) if periodic */
    uint32_t expire_at;                 /**< Timestamp when timer should expire */
    uint32_t flags;                     /*   Internal flags */
#define BCMOS_TIMER_FLAG_RUNNING        0x00000001      /* Timer is running */
#define BCMOS_TIMER_FLAG_EXPIRED        0x00000002      /* Timer has expired, but not yet handled */
#define BCMOS_TIMER_FLAG_ACTIVE         (BCMOS_TIMER_FLAG_RUNNING | BCMOS_TIMER_FLAG_EXPIRED)
#define BCMOS_TIMER_FLAG_VALID          0x00000004
    bcmos_msg_queue_nw *queue;          /**< Queue expired timer is on */
    bcmos_task *task;                   /**< Task that executes timer handler (switches between module and system) */
    bcmos_task *owner_task;             /**< Task that owns the timer (owner of the module at creation time) */
#ifdef BCMOS_TIMER_RB_TREE
    RB_ENTRY(bcmos_timer) pool_entry;   /**< Timer pool entry */
#else
    TAILQ_ENTRY(bcmos_timer) pool_entry;
#endif
#ifdef BCMOS_TIMER_DEBUG
    uint32_t magic;                     /* magic number */
#define BCMOS_TIMER_MAGIC                (('t' << 24) | ('i' << 16) | ('m' << 8) | 'r')
#define BCMOS_TIMER_MAGIC_DESTROYED      (('t' << 24) | ('i' << 16) | ('m' << 8) | '~')
    /* Unlike the above entries, which the timer enters only when it is started, we need a separate entry (linked list)
     * for all timer, so in debug time we can traverse all system timers. */
    STAILQ_ENTRY(bcmos_timer) list;     /**< Next timer pointer */
#endif
};

/** Check if timer is valid
 * \param[in]   timer   Timer handle
 * \returns TRUE if timer is valid
 */
static inline bcmos_bool bcmos_timer_is_valid(const bcmos_timer *timer)
{
    return (timer->flags & BCMOS_TIMER_FLAG_VALID) != 0;
}

/** Check if timer is running
 * \param[in]   timer   Timer handle
 * \returns TRUE if timer is running
 */
static inline bcmos_bool bcmos_timer_is_running(const bcmos_timer *timer)
{
    return ((timer->flags & BCMOS_TIMER_FLAG_RUNNING) != 0) ||
        (timer->parm.periodic && ((timer->flags & BCMOS_TIMER_FLAG_EXPIRED) != 0));
}

static inline bcmos_timer *_bcmos_msg_to_timer(bcmos_msg *msg)
{
    BUG_ON(msg->type != BCMOS_MSG_ID_INTERNAL_TIMER);
    return (bcmos_timer *)msg;
}

/** @} */

/** \addtogroup system_module
 * @{
 */

/** Module control block */
struct bcmos_module
{
    bcmos_module_parm parm;     /**< Module parameters */
    bcmos_module_id id;         /**< Module id */
    int idx;                    /**< Module index in task control block */
    bcmos_msg_queue_nw msgq;    /**< Message queue */
    bcmos_task *my_task;        /**< Task the module is associated with */
    void *context;              /**< User-defined context */
    char name[BCMOS_MAX_NAME_LENGTH];   /**< Module name */
    bcmos_bool deleted;         /**< TRUE=module is being deleted */
};

/** @} system_module */

/** \addtogroup system_event
 * @{
 */

/** Event control block */
struct bcmos_event
{
    bcmos_msg msg;              /**< Message header. Used to deliver event to module's queue */
    bcmos_event_id id;          /**< Event set id */
    bcmos_event_parm parm;        /**< Event parameters */
    bcmos_fastlock lock;        /**< Protects event control block */
    uint32_t active_bits;       /**< Active event bits */

    bcmos_sem m;                /**< Mutex to suspend task on. Traditional mode only */
    bcmos_bool is_waiting;      /**< TRUE if task is waiting for event */
    char name[BCMOS_MAX_NAME_LENGTH];   /**< Event name */
};


static inline bcmos_event *_bcmos_msg_to_event(bcmos_msg *msg)
{
    BUG_ON(msg->type != BCMOS_MSG_ID_INTERNAL_EVENT);
    return (bcmos_event *)msg;
}

/** @} system_event */

/*
 * Low level services
 */

/** \addtogroup system_buf
 * @{
 */

#if !defined(BCMOS_BUF_OS_SPECIFIC) && !defined(BCMOS_BUF_DO_NOT_INLINE)
#define BCMOS_BUF_DATA_INLINE
#endif

#ifdef BCMOS_BUF_INLINE
#define BCMOS_BUF_ALLOC_FREE_INLINE
#define BCMOS_BUF_DATA_INLINE
#endif

#ifndef BCMOS_BUF_DATA_GUARD
#define BCMOS_BUF_DATA_GUARD            0
#endif

#ifndef BCMOS_BUF_DATA_ALIGNMENT
#define BCMOS_BUF_DATA_ALIGNMENT        64
#endif

#ifndef BCMOS_BUF_OS_SPECIFIC

/* Generic (not os-specific) sysb implementation */

/*
 * Network / transport buffer
 */


/* Memory block list */
typedef STAILQ_HEAD(, bcmos_buf) bcmos_buf_list_head;

typedef struct
{
    bcmos_buf_list_head head;           /**< Buffer list head */
} bcmos_buf_queue;

/* System buffer. We probably can use mbuf as well.  */
struct bcmos_buf
{
    uint8_t *start;
    uint8_t *data;
    bcmos_blk_pool *pool;
    uint32_t size;
    uint32_t len;
    STAILQ_ENTRY(bcmos_buf) list;      /**< Next buffer pointer */
    uint8_t channel;
};

#endif /* #ifndef BCMOS_BUF_OS_SPECIFIC */

#ifndef BCMTR_BUF_EXTRA_HEADROOM
#define BCMTR_BUF_EXTRA_HEADROOM 64
#endif

#ifndef BCMOS_BUF_ALLOC_FREE_INLINE

/** Allocate transport buffer.
 * The buffer can accommodate up to size bytes of data.
 * In addition it reserves BCMTR_BUF_EXTRA_HEADROOM headroom bytes
 * for extra headers.
 *
 * \param[in]   size    Data size
 * \returns buffer pointer or NULL if no memory
 */
bcmos_buf *bcmos_buf_alloc(uint32_t size);

 /** Release transport buffer allocated by bcmos_buf_alloc()
  *
  * \param[in]   buf    Buffer to be released
  */
void bcmos_buf_free(bcmos_buf *buf);

/** Clone transport buffer
 *
 * \param[in]   buf    Buffer to be cloned
 * \returns buffer pointer or NULL if no memory
 */
bcmos_buf *bcmos_buf_clone(bcmos_buf *buf);

#endif /* BCMOS_BUF_ALLOC_FREE_INLINE */

#ifndef BCMOS_BUF_DATA_INLINE

/** Get data length
 *
 * \param[in]   buf     Buffer
 * \returns data length
 */
uint32_t bcmos_buf_length(bcmos_buf *buf);

/** Set data length
 *
 * \param[in]   buf     Buffer
 * \param[in]   length  Data length
 * \returns 0=OK, or BCM_ERR_OVERFLOW if length exceeds size
 */
bcmos_errno bcmos_buf_length_set(bcmos_buf *buf, uint32_t length);

/** Get buffer data pointer.
 * \param[in]   buf     Buffer
 * \returns data pointer
 */
uint8_t *bcmos_buf_data(bcmos_buf *buf);

/* Add data block to the end of buffer data.
 * It is up to the caller to ensure that there is room in the buffer
 * Returns pointer of the beginning of the added block
 */
uint8_t *bcmos_buf_tail_push(bcmos_buf *buf, uint32_t length);

/* Add data block to the end of buffer data.
 * It is up to the caller to ensure that there is room in the buffer
 * Returns pointer of the beginning of the added block
 */
uint8_t * bcmos_buf_head_push(bcmos_buf *buf, uint32_t length);

/* Pull data from the head of the buffer
 * Returns pointer to the old head
 */
uint8_t *bcmos_buf_head_pull(bcmos_buf *buf, uint32_t length);

/* Get buffer channel. */
uint8_t bcmos_buf_channel(bcmos_buf *buf);

/* Set buffer channel. */
void bcmos_buf_channel_set(bcmos_buf *buf, uint8_t channel);

/** Initialize buffer queue
 * \param[in]   q       Buffer queue
 */
void bcmos_buf_queue_init(bcmos_buf_queue *q);

/* Check if buffer queue is empty
 * \param[in]   q       Buffer queue
 * \returns TRUE if the queue is empty
 */
bcmos_bool bcmos_buf_queue_is_empty(bcmos_buf_queue *q);

/** Enqueue buffer
 *
 * Must be called under lock, e.g., q->lock
 *
 * \param[in]   q       Buffer queue
 * \param[in]   buf     Buffer
 */
void bcmos_buf_queue_put(bcmos_buf_queue *q, bcmos_buf *buf);

/* Dequeue buffer
 *
 * Must be called under lock, e.g., q->lock
 *
 * Remove and return the 1st queued buffer.
 * \param[in]   q       Buffer queue
 * \returns the  buffer pointer
 */
bcmos_buf *bcmos_buf_queue_get(bcmos_buf_queue *q);

/* Peek into queue and return the 1st buffer without dequeing it
 *
 * Must be called under lock, e.g., q->lock
 * \param[in]   q       Buffer queue
 * \returns the  buffer pointer
 */
bcmos_buf *bcmos_buf_queue_peek(bcmos_buf_queue *q);

#else /* #ifndef BCMOS_BUF_DATA_INLINE */

#ifndef BCMOS_BUF_OS_SPECIFIC
/** Initialize buffer queue
 * \param[in]   q       Buffer queue
 */
static inline void bcmos_buf_queue_init(bcmos_buf_queue *q)
{
    STAILQ_INIT(&q->head);
}

/* Check if buffer queue is empty
 * \param[in]   q       Buffer queue
 * \returns TRUE if the queue is empty
 */
static inline bcmos_bool bcmos_buf_queue_is_empty(bcmos_buf_queue *q)
{
    return (bcmos_bool)STAILQ_EMPTY(&q->head);
}

/** Enqueue buffer
 *
 * Must be called under lock, e.g., q->lock
 *
 * \param[in]   q       Buffer queue
 * \param[in]   buf     Buffer
 */
static inline void bcmos_buf_queue_put(bcmos_buf_queue *q, bcmos_buf *buf)
{
    STAILQ_INSERT_TAIL(&q->head, buf, list);
}

/* Dequeue buffer
 *
 * Must be called under lock, e.g., q->lock
 *
 * Remove and return the 1st queued buffer.
 * \param[in]   q       Buffer queue
 * \returns the  buffer pointer
 */
static inline bcmos_buf *bcmos_buf_queue_get(bcmos_buf_queue *q)
{
    bcmos_buf *buf;
    buf = STAILQ_FIRST(&q->head);
    if (buf)
        STAILQ_REMOVE_HEAD(&q->head, list);
    return buf;
}

/* Peek into queue and return the 1st buffer without dequeing it
 *
 * Must be called under lock, e.g., q->lock
 * \param[in]   q       Buffer queue
 * \returns the  buffer pointer
 */
static inline bcmos_buf *bcmos_buf_queue_peek(bcmos_buf_queue *q)
{
    return STAILQ_FIRST(&q->head);
}

/* Initialize buffer */
static inline bcmos_buf *bcmos_buf_init(bcmos_buf *buf, uint8_t *start,
    uint8_t *data, uint32_t size, uint32_t len)
{
    BUG_ON((void *)(buf +1) != start);
    buf->start = start;
    buf->data = data;
    buf->size = size;
    buf->len = len;
    buf->pool = NULL;
    return buf;
}

/* Get data length */
static inline uint32_t bcmos_buf_length(bcmos_buf *buf)
{
    return buf->len;
}

/* Set data length */
static inline bcmos_errno bcmos_buf_length_set(bcmos_buf *buf, uint32_t length)
{
    if (unlikely(length > buf->size - (buf->data - buf->start)))
    {
        BCMOS_TRACE_ERR("!!!%s: length=%u size=%u data=%p start=%p data-start=%u\n",
            __FUNCTION__, length, buf->size, buf->data, buf->start, (uint32_t)(buf->data - buf->start));
        return BCM_ERR_OVERFLOW;
    }
    buf->len = length;
    return BCM_ERR_OK;
}

/* Get buffer data pointer. */
static inline uint8_t *bcmos_buf_data(bcmos_buf *buf)
{
    return buf->data;
}

/* Add data block to the end of buffer data.
 * It is up to the caller to ensure that there is room in the buffer
 * Returns pointer of the beginning of the added block
 */
static inline uint8_t *bcmos_buf_tail_push(bcmos_buf *buf, uint32_t length)
{
    uint8_t *end = buf->start + buf->size;
    uint8_t *tail = buf->data + buf->len;
    BUG_ON(tail + length > end);
    buf->len += length;
    return tail;
}

/* Add data block to beginning of buffer data.
 * It is up to the caller to ensure that there is sufficient headroom in the buffer
 * Returns pointer to the new head
 */
static inline uint8_t *bcmos_buf_head_push(bcmos_buf *buf, uint32_t length)
{
    BUG_ON(buf->data - buf->start < length);
    buf->data -= length;
    buf->len += length;
    return buf->data;
}

/* Pull data from the head of the buffer
 * Returns pointer to the old head
 */
static inline uint8_t *bcmos_buf_head_pull(bcmos_buf *buf, uint32_t length)
{
    uint8_t *old_head = buf->data;
    BUG_ON(buf->len < length);
    buf->data += length;
    buf->len -= length;
    return old_head;
}

/* Get buffer channel. */
static inline uint8_t bcmos_buf_channel(bcmos_buf *buf)
{
    return buf->channel;
}

/* Set buffer channel. */
static inline void bcmos_buf_channel_set(bcmos_buf *buf, uint8_t channel)
{
    buf->channel = channel;
}

#endif /* #ifndef BCMOS_BUF_OS_SPECIFIC */

#endif /* #ifdef BCMOS_BUF_DATA_INLINE */

/** @} bcmos_buf */

/** \addtogroup system_cache
 * @{
 */

#ifndef BCMOS_CACHE_INLINE

/** Invalidate address area in data cache. Dirty cache lines content is discarded.
 * \param[in]   start   Address area start
 * \param[in]   size    Address area size
 */
void bcmos_dcache_inv(void *start, uint32_t size);

/** Flush address area in data cache. Dirty cache lines are committed to memory.
 * \param[in]   start   Address area start
 * \param[in]   size    Address area size
 */
void bcmos_dcache_flush(void *start, uint32_t size);

#endif /* BCMOS_CACHE_INLINE */

/** Prepare for DMA write.
 * On h/w platforms that support DMA-cache coherency, this function should
 * perform write barrier.
 * On platforms that don't support DMA cache coherency this function should
 * flush the relevant dcache area
 *
 * \param[in]   start   DMA buffer start address
 * \param[in]   size    DMA buffer size
 */
static inline void bcmos_prepare_for_dma_write(void *start, uint32_t size)
{
#ifdef BCMOS_DMA_CACHE_COHERENCY
    bcmos_barrier();
#else
    bcmos_dcache_flush(start, size);
#endif
}

/** Prepare for DMA read.
 * On h/w platforms that support DMA-cache coherency, this function should
 * perform write barrier.
 * On platforms that don't support DMA cache coherency this function should
 * invalidate the relevant dcache area
 *
 * \param[in]   start   DMA buffer start address
 * \param[in]   size    DMA buffer size
 */
static inline void bcmos_prepare_for_dma_read(void *start, uint32_t size)
{
#ifdef BCMOS_DMA_CACHE_COHERENCY
    bcmos_barrier();
#else
    bcmos_dcache_inv(start, size);
#endif
}

/** @} system_cache */

/** \addtogroup system_interrupt
 * @{
 */

#ifdef BCMOS_INTERRUPT_INLINE
#define BCMOS_INTERRUPT_CONNECT_DISCONNECT_INLINE
#define BCMOS_INTERRUPT_ENABLE_DISABLE_INLINE
#endif

#ifndef BCMOS_INTERRUPT_CONNECT_DISCONNECT_INLINE

/** Connect system interrupt
 * \param[in]   irq     IRQ number
 * \param[in]   cpu     CPU number (for SMP)
 * \param[in]   flags   IRQ flags
 * \param[in]   isr     ISR
 * \param[in]   name    device name
 * \param[in]   priv    Private cookie
 * \returns 0=OK, <0- error
 */
int bcmos_int_connect(int irq, int cpu, int flags,
    int (*isr)(int irq, void *priv), const char *name, void *priv);

/** Disconnect system interrupt
 * \param[in]   irq     IRQ number
 * \param[in]   priv    Private cookie passed in bcmos_int_connect()
 * \returns 0=OK, <0- error
 */
void bcmos_int_disconnect(int irq, void *priv);
#endif

#ifndef BCMOS_INTERRUPT_ENABLE_DISABLE_INLINE
/** Unmask IRQ
 * \param[in]   irq IRQ
 */
void bcmos_int_enable(int irq);

/** Mask IRQ
 * \param[in]   irq IRQ
 */
void bcmos_int_disable(int irq);
#endif

#ifndef IRQ_HANDLED
#define IRQ_HANDLED     (1 << 0)
#endif

/** @} */

/* Get char, put char support */
#ifndef BCMOS_GETCHAR_INLINE
static inline int bcmos_getchar(void)
{
    return getchar();
}
#endif

#ifndef BCMOS_PUTCHAR_INLINE
void bcmos_putchar(int c);
#endif

#ifndef BCMOS_SEM_POST_IS_ALLOWED_INLINE
static inline bcmos_bool bcmos_sem_post_is_allowed(void)
{
    return BCMOS_TRUE;
}
#endif

/*
 * File IO
 */

typedef struct bcmos_file bcmos_file;

typedef enum
{
    BCMOS_FILE_FLAG_NONE        = 0,
    BCMOS_FILE_FLAG_READ        = 0x1,
    BCMOS_FILE_FLAG_WRITE       = 0x2,
    BCMOS_FILE_FLAG_APPEND      = 0x4,
} bcmos_file_flag;

#ifdef BCMOS_FILE_IO_OS_SPECIFIC

bcmos_file *bcmos_file_open(const char *path, bcmos_file_flag flags);

bcmos_errno bcmos_file_seek(bcmos_file *file, unsigned long offset);

int bcmos_file_read(bcmos_file *file, void *data, uint32_t size);

int bcmos_file_write(bcmos_file *file, const void *data, uint32_t size);

void bcmos_file_close(bcmos_file *file);

char *bcmos_file_gets(bcmos_file *file, char *s, int size);

#else

static inline bcmos_file *bcmos_file_open(const char *path, bcmos_file_flag flags)
{
    return NULL;
}

static inline int bcmos_file_read(bcmos_file *file, void *data, uint32_t size)
{
    return BCM_ERR_NOT_SUPPORTED;
}

static inline int bcmos_file_write(bcmos_file *file, const void *data, uint32_t size)
{
    return BCM_ERR_NOT_SUPPORTED;
}

static inline bcmos_errno bcmos_file_seek(bcmos_file *file, unsigned long offset)
{
    return BCM_ERR_NOT_SUPPORTED;
}

static inline void bcmos_file_close(bcmos_file *file)
{
}

static inline char *bcmos_file_gets(bcmos_file *file, char *s, int size)
{
    return NULL;
}
#endif

#endif /* BCMOS_COMMON2_H_ */
