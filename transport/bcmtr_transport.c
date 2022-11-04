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

#include <bcmos_system.h>
#include <bcmolt_api_utils.h>
#include <bcmtr_interface.h>
#include <bcmtr_debug.h>
#include "bcmtr_header.h"
#include "bcmtr_internal.h"

dev_log_id bcmtr_log_id[BCMTR_MAX_DEVICES];

typedef STAILQ_HEAD(bcmtr_handler_list, bcmtr_handler) bcmtr_handler_list;

typedef struct
{
    bcmtr_conn *conn;                                                           /**< Connection dynamic info (allocated on connect) */
    bcmtr_handler_list msg_handler_list[BCMOLT_API_GROUP_ID__NUM_OF][BCMTR_MAX_INSTANCES];
    F_bcmtr_tx_overflow overflow_cb;                                            /**< Callback to be called in case of tx drop because of queue overflow */
#ifdef BCM_SUBSYSTEM_EMBEDDED
    bcmtr_conn *aux_conn;                                                       /**< Unmanaged connection - for uncontrolled clients */
#else
    bcmolt_presence_mask auto_masks[BCMOLT_OBJ_ID__NUM_OF];                     /* Per-object presence masks */
#endif
    bcmos_msg_pool ind_msg_pool;
#define BCMTR_MAX_HANDLERS_PER_MSG  8
    /* Max number of auto messages on the way to their handlers */
#define BCMTR_MAX_AUTO_IN_FLIGHT    (BCMTR_MAX_AUTOS * BCMTR_MAX_HANDLERS_PER_MSG)
} bcmtr_conn_info;

static bcmos_bool transport_initialized;

static bcmtr_conn_info conn_info[BCMTR_MAX_DEVICES]; /* Store connection info separately per OLT */

static bcmos_errno _bcmtr_connect(bcmolt_devid device, const bcmtr_conn_parms *conn_parms, bcmtr_conn **p_conn);

static bcmos_mutex conn_lock;

static bcmtr_init_parms init_parms;

static F_bcmtr_rx_translate rx_translate_cb;

static uint32_t corr_tag;

/* Global counters */
static struct
{
    uint32_t no_mem;    /**< Received data was discarded because there was no memory for RX buffer */
    uint32_t no_conn;   /**< Received data was received for device for which there is no active connection */
} bcmtr_global_stats;

static inline void _bcmtr_notify_ready(bcmtr_conn *conn, bcmtr_msg *tmsg);
static inline bcmtr_msg *_bcmtr_tmsg_alloc(bcmtr_msg_list *free_list);
static void _bcmtr_tmsg_free(bcmtr_msg *tmsg, bcmtr_msg_list *cur_list);
static inline bcmos_errno _bcmtr_send_to_line(bcmtr_conn *conn, bcmolt_subchannel subch,
    bcmos_buf *buf, bcmtr_send_flags flags);
static bcmos_errno _bcmtr_fragment_if_needed_and_send(
    bcmtr_conn *conn,
    bcmolt_subchannel subch,
    bcmtr_msg *tmsg,
    bcmos_buf *tx_buf,
    bcmtr_send_flags flags);
static void _bcmtr_disconnect1(bcmtr_conn *conn);

#ifdef BCM_SUBSYSTEM_HOST
#include "bcmtr_transport_host.c"
#else
#include "bcmtr_transport_embedded.c"
#endif

/* Get existing connection. If none - setup new */
bcmos_errno _bcmtr_conn_get(bcmolt_devid device, bcmtr_conn **conn)
{
    if (device >= BCMTR_MAX_DEVICES)
    {
        return BCM_ERR_RANGE;
    }
    *conn = conn_info[device].conn;
    if (*conn && (*conn)->connected)
    {
        return BCM_ERR_OK;
    }
    return BCM_ERR_NOT_CONNECTED;
}

/* Free segmentation/reassemble buffer list */
static inline void _bcmtr_reass_list_free(bcmtr_reass *reass)
{
    bcmos_buf *b;
    while ((b=bcmos_buf_queue_get(&reass->fragments)) != NULL)
        bcmos_buf_free(b);
}

/* Free transport header. Called under transport lock */
static void _bcmtr_tmsg_free(bcmtr_msg *tmsg, bcmtr_msg_list *cur_list)
{
    BUG_ON(!tmsg->ref_count);
    if (--tmsg->ref_count)
        return;
    /* Remove from the list it is in, if any */
    if (cur_list)
        TAILQ_REMOVE(cur_list, tmsg, l);
    if (tmsg->rx_buf)
        bcmos_buf_free(tmsg->rx_buf);
    _bcmtr_reass_list_free(&tmsg->reass);
    memset(tmsg, 0, BCMTR_HDR_CLEAR_SIZE);

    /* Request-response or autonomous ? */
    TAILQ_INSERT_TAIL(tmsg->free_list, tmsg, l);
}


/* Initialize segmentation/reassembling block */
static inline void _bcmtr_reass_init(bcmtr_reass *reass)
{
    bcmos_buf_queue_init(&reass->fragments);
    reass->last_fragment = -1;
}

/* Allocate transport header from the given free list.
 * Must be called under lock
 */
static inline bcmtr_msg *_bcmtr_tmsg_alloc(bcmtr_msg_list *free_list)
{
    bcmtr_msg *tmsg = TAILQ_FIRST(free_list);
    if (tmsg)
    {
        TAILQ_REMOVE(free_list, tmsg, l);
        _bcmtr_reass_init(&tmsg->reass);
        tmsg->ref_count = 1;
    }
    return tmsg;
}

/* Unpack message. *unpacked is set=NULL in case of error */
static inline bcmos_errno _bcmtr_msg_unpack(
    bcmtr_conn *conn,
    bcmos_buf *buf,
    bcmtr_hdr *hdr,
    uint32_t ts,
    bcmolt_msg **msg)
{
    bcmos_errno err;
    uint8_t *packed = bcmos_buf_data(buf);
    uint32_t packed_length = bcmos_buf_length(buf);
    bcmolt_buf stream;

    /* Unpack */
    bcmolt_buf_init(&stream, packed_length, packed);
    err = bcmolt_msg_unpack(&stream, msg);
    if (err != BCM_ERR_OK)
    {
        BCMTR_CLD_CHECK_NOTIFY(conn->device, hdr, BCMTR_CLD_EV_RECV_DISCARD, ts, packed, packed_length, NULL);
        ++conn->stat.unpack_errors;
        *msg = NULL;
        return err;
    }
    (*msg)->timestamp = ts;
    BCMTR_CLD_CHECK_NOTIFY(conn->device, hdr, BCMTR_CLD_EV_RECV, ts, packed, packed_length, *msg);

    return BCM_ERR_OK;
}

/** Default message handler - discard */
static void _bcmtr_dft_msg_handler(bcmolt_devid olt, bcmolt_msg *msg)
{
    bcmtr_conn *conn = conn_info[olt].conn;

    /* ToDo: log */

    if (conn)
        ++conn->stat.no_rx_handler;

    bcmolt_msg_free(msg);
}

/* Unpack message and hand over to app_cb */
static void _bcmtr_unpack_and_deliver(bcmtr_msg *tmsg, bcmtr_handler *handler)
{
    f_bcmolt_msg_handler app_cb = handler->app_cb ? handler->app_cb : _bcmtr_dft_msg_handler;
    bcmtr_conn *conn = tmsg->conn;
    bcmolt_msg *msg = NULL;
    bcmos_errno err = _bcmtr_msg_unpack(conn, tmsg->rx_buf, &tmsg->hdr, tmsg->timestamp, &msg);

    /* Translate indication if translation callback is set */
    if (err == BCM_ERR_OK && rx_translate_cb)
    {
        err = rx_translate_cb(conn->device, handler->olt, msg);
        if (err != BCM_ERR_OK)
        {
            /* Silently discard the message if it is intended for another OLT */
            if (err != BCM_ERR_MISMATCH)
                ++conn->stat.translate_errors;
            bcmolt_msg_free(msg);
        }
    }

    if (err == BCM_ERR_OK)
    {
        msg->corr_tag = tmsg->hdr.corr_tag;
        msg->subch = tmsg->subch;
        msg->device = tmsg->hdr.device;
        app_cb(rx_translate_cb ? handler->olt : (bcmolt_oltid)conn->device, msg);
    }
    /* Mark tmsg block as free. It will be released when tmsg->ref_count becomes 0 */
    bcmos_mutex_lock(&conn->mutex);
    _bcmtr_tmsg_free(tmsg, NULL);
    bcmos_mutex_unlock(&conn->mutex);
}

/* Transport IPC release callback */
static void _bcmtr_ipc_msg_release(bcmos_msg *m)
{
    bcmtr_msg *tmsg = (bcmtr_msg *)m->data;
    bcmtr_conn *conn = tmsg->conn;
    BCMTR_LOG(conn->device, ERROR, "Couldn't deliver transport message to recipient!\n");
    bcmos_mutex_lock(&conn->mutex);
    _bcmtr_tmsg_free(tmsg, NULL);
    bcmos_mutex_unlock(&conn->mutex);
}

/* Transport IPC message handler.
 * Called in context of the target module as part of dispatching message to the user task.
 */
static void _bcmtr_ipc_msg_handler(bcmos_module_id module_id, bcmos_msg *m)
{
    bcmtr_msg *tmsg = (bcmtr_msg *)m->data;
    bcmtr_handler *h = (bcmtr_handler *)m->user_data;
    /* Release message if it was allocated from ind_pool */
    if (m != &tmsg->os_msg)
    {
        m->data_release = NULL;
        bcmos_msg_free(m);
    }
    _bcmtr_unpack_and_deliver(tmsg, h);
}

/* Init IPC header in received message */
static inline void _bcmtr_msg_ipc_init(bcmtr_msg *tmsg)
{
    tmsg->os_msg.type = BCMOS_MSG_ID_INTERNAL_IPC;
    tmsg->os_msg.release = _bcmtr_ipc_msg_release;
    tmsg->os_msg.handler = _bcmtr_ipc_msg_handler;
    tmsg->os_msg.data = tmsg;
}

/* Pre-allocate transport header array, put all blocks on free lists */
static bcmos_errno _bcmtr_tmsg_list_alloc(bcmtr_conn *conn)
{
    int n_hdr, i;
    bcmtr_msg *tmsg;

    n_hdr = conn->cfg.max_requests + conn->cfg.max_autos;
    conn->tmsg_array = (bcmtr_msg *)bcmos_calloc(sizeof(bcmtr_msg) * n_hdr);
    if (!conn->tmsg_array)
        return BCM_ERR_NOMEM;

    tmsg = conn->tmsg_array;
    for (i=0; i<conn->cfg.max_requests; i++, tmsg++)
    {
        bcmos_errno rc;

        TAILQ_INSERT_TAIL(&conn->free_req_list, tmsg, l);
        tmsg->free_list = &conn->free_req_list;
        rc = bcmos_sem_create(&tmsg->sem, 0, 0, NULL);
        if (rc != BCM_ERR_OK)
            return rc;
        tmsg->conn = conn;
        _bcmtr_msg_ipc_init(tmsg);
    }
    for (i=0; i<conn->cfg.max_autos; i++, tmsg++)
    {
        TAILQ_INSERT_TAIL(&conn->free_auto_list, tmsg, l);
        tmsg->free_list = &conn->free_auto_list;
        tmsg->conn = conn;
        _bcmtr_msg_ipc_init(tmsg);
    }
    return BCM_ERR_OK;
}

/* Cleanup function - notify COMM_FAILURE for all pending requests */
static void _bcmtr_tmsg_list_free_pending(bcmtr_conn *conn)
{
    bcmtr_msg *tmsg, *tmp_tmsg;

    if (!conn->tmsg_array)
        return;

    /* Release pending requests */
    TAILQ_FOREACH_SAFE(tmsg, &conn->msg_list, l, tmp_tmsg)
    {
        bcmolt_msg *msg = tmsg->msg;
        /* Release waiting task if request-response */
        if (msg && tmsg->err == BCM_ERR_IN_PROGRESS)
        {
            msg->err = BCM_ERR_COMM_FAIL;
            bcmos_sem_post(&tmsg->sem);
        }
    }
}

/* Cleanup function - free transport headers */
static void _bcmtr_tmsg_list_free(bcmtr_conn *conn)
{
    bcmtr_msg *tmsg, *tmp_tmsg;

    if (!conn->tmsg_array)
        return;

    _bcmtr_tmsg_list_free_pending(conn);

    TAILQ_FOREACH_SAFE(tmsg, &conn->free_req_list, l, tmp_tmsg)
    {
        bcmos_sem_destroy(&tmsg->sem);
    }

    bcmos_free(conn->tmsg_array);
}

/* Find message by correlation tag
 * Called under lock
 */
static bcmtr_msg *_bcmtr_msg_get_by_corr_tag(const bcmtr_conn *conn, const bcmtr_hdr *hdr)
{
    bcmtr_msg *tmsg;

    TAILQ_FOREACH(tmsg, &conn->msg_list, l)
    {
        if (tmsg->hdr.corr_tag == hdr->corr_tag &&
            tmsg->hdr.obj      == hdr->obj      &&
            tmsg->hdr.group_id == hdr->group_id &&
            tmsg->err          == BCM_ERR_IN_PROGRESS)
            break;
    }
    return tmsg;
}

/* Message reassembler. Returns TRUE if message reassembling is completed */
static bcmos_bool _bcmtr_reassemble(bcmtr_conn *conn, bcmtr_msg *tmsg, bcmos_buf *buf)
{
    bcmtr_hdr *hdr = &tmsg->hdr;
    uint16_t frag_num = hdr->frag_number;
    bcmos_bool done = BCMOS_FALSE;
    bcmos_bool is_last;

    is_last = !hdr->more_fragments;

    /* Single-buffer message ? */
    if (is_last && !frag_num)
    {
        tmsg->rx_buf = buf;
        tmsg->err = BCM_ERR_OK;
        return BCMOS_TRUE;
    }

    /*
     * Multi-part message
     */

    /* Discard if invalid fragment number or duplicate.
     * Fragment reordering is NOT supported */
    if (frag_num >= conn->cfg.max_fragments ||
        (frag_num != tmsg->reass.last_fragment + 1))
    {
        bcmos_buf_free(buf);
        /* If last out-of range fragment was received report it.
         * We want to avoid request retransmission in this case */
        if (frag_num >= conn->cfg.max_fragments)
        {
            tmsg->err = BCM_ERR_TOO_MANY_FRAGS;
            return is_last;
        }
        ++conn->stat.frag_invalid;
        return BCMOS_FALSE;
    }

    tmsg->reass.total_size += bcmos_buf_length(buf);
    bcmos_buf_queue_put(&tmsg->reass.fragments, buf);
    tmsg->reass.num_fragments++;
    tmsg->reass.last_fragment = frag_num;
    done = is_last;
    ++conn->stat.frag_received;

    /* Reassemble if done */
    if (done)
    {
        /* Allocate big flat buffer */
        if ((tmsg->rx_buf = bcmos_buf_alloc(tmsg->reass.total_size)) != NULL)
        {
            uint8_t *body = bcmos_buf_data(tmsg->rx_buf);
            bcmos_buf *b;
            while ((b=bcmos_buf_queue_get(&tmsg->reass.fragments)) != NULL)
            {
                uint32_t frag_size = bcmos_buf_length(b);
                memcpy(body, bcmos_buf_data(b), frag_size);
                body += frag_size;
                bcmos_buf_free(b);
            }
            bcmos_buf_length_set(tmsg->rx_buf, tmsg->reass.total_size);
            tmsg->err = BCM_ERR_OK;
        }
        else
        {
            /* Reassembly buffer allocation failed */
            tmsg->err = BCM_ERR_NOMEM;
        }
    }

    return done;
}

/* Notify application that message is ready */
static inline void _bcmtr_notify_ready(bcmtr_conn *conn, bcmtr_msg *tmsg)
{
    bcmos_sem_post(&tmsg->sem);
}

/* Helper function for _bcmtr_notify_rx_req_auto */
static inline void _bcmtr_ind_deliver_to_module(
    bcmtr_conn *conn,
    bcmtr_msg *tmsg,
    bcmtr_handler *handler,
    bcmos_module_id module,
    const bcmolt_group_descr *group_descr,
    uint32_t *n_delivered)
{
    ++tmsg->ref_count;
    if (module != BCMOS_MODULE_ID_NONE)
    {
        bcmos_msg *msg = &tmsg->os_msg;
        /* If delivering to more than 1 destination, need to allocate separate message for each */
        if (*n_delivered)
        {
            msg = bcmos_msg_pool_alloc(&conn_info[conn->device].ind_msg_pool);
            if (msg == NULL)
            {
                BCMOS_TRACE_ERR("Can't deliver auto msg %d: too many messages in flight\n", group_descr->global_id);
                --tmsg->ref_count; /* restore ref_count */
                return;
            }
            msg->data = (void *)tmsg;
            msg->handler = _bcmtr_ipc_msg_handler;
            msg->data_release = _bcmtr_ipc_msg_release; /* In case of delivery failure */
        }
        msg->user_data = handler;
        bcmos_msg_send_to_module(module, msg, BCMOS_MSG_SEND_AUTO_FREE);
    }
    else
    {
        /* Call application handler. Don't do it under lock. Unlock here and re-lock afterwards */
        bcmos_mutex_unlock(&conn->mutex);
        _bcmtr_unpack_and_deliver(tmsg, handler);
        bcmos_mutex_lock(&conn->mutex);
    }
    ++(*n_delivered);
}

/* Notify request message (host:autonomous message, embedded:API request).
 * The function is called under connection lock
 */
static inline void _bcmtr_notify_rx_req_auto(bcmtr_conn *conn, bcmtr_msg *tmsg)
{
    bcmtr_conn_info *info = &conn_info[conn->device];
    bcmtr_handler_list *handlers_list;
    uint32_t n_delivered;
    bcmtr_handler *h, *h_tmp;
    const bcmolt_group_descr *group_descr;
    bcmos_module_id module;

    if (bcmolt_api_group_descr_get_by_group_id(tmsg->hdr.obj, tmsg->hdr.group_id, &group_descr) != BCM_ERR_OK)
    {
        BCMTR_LOG(conn->device, ERROR, "Unexpected msg: obj=%d group=%d\n", tmsg->hdr.obj, tmsg->hdr.group_id);
        _bcmtr_tmsg_free(tmsg, NULL);
        return;
    }
    if (tmsg->hdr.instance >= BCMTR_MAX_INSTANCES)
    {
        BCMTR_LOG(conn->device, ERROR, "Unexpected instance id: %u\n", tmsg->hdr.instance);
        _bcmtr_tmsg_free(tmsg, NULL);
        return;
    }

    handlers_list = &info->msg_handler_list[group_descr->global_id][tmsg->hdr.instance];
    n_delivered = 0;
    STAILQ_FOREACH_SAFE(h, handlers_list, l, h_tmp)
    {
        module = h->module;
#ifdef BCM_SUBSYSTEM_HOST
        if (module == BCMOS_MODULE_ID_NONE)
            module = BCMOS_MODULE_ID_TRANSPORT_IND;
#endif
        _bcmtr_ind_deliver_to_module(conn, tmsg, h, module, group_descr, &n_delivered);
    }

    /* Reduce reference count. The message will be freed when ref_count becomes 0 */
    _bcmtr_tmsg_free(tmsg, NULL);

    /* Discard message if there are no receivers */
    if (!n_delivered)
    {
        ++conn->stat.no_rx_handler;
    }
    else
    {
        ++conn->stat.msg_req_auto_received;
    }
}

static inline bcmos_errno _bcmtr_send_to_line(bcmtr_conn *conn, bcmolt_subchannel subch,
    bcmos_buf *buf, bcmtr_send_flags flags)
{
    if (!conn->driver.send)
    {
        /* Disconnected while sending. It shouldn't happen, but handle it anyway */
        bcmos_buf_free(buf);
        return BCM_ERR_NOT_CONNECTED;
    }
    return conn->driver.send(conn->drv_priv, conn->cfg.plugin_cfg.ldid, subch, buf, flags);
}

/*
 * Low-level fragment and send function.
 * It allocates a series of buffers up to MAX_MTU size, copies original data into them and sends.
 * The original buffer is released regardless of the outcome.
 */
static bcmos_errno _bcmtr_fragment_and_send(
    bcmtr_conn *conn,
    bcmolt_subchannel subch,
    bcmtr_msg *tmsg,
    bcmos_buf *tx_buf,
    bcmtr_send_flags flags)
{
    uint32_t frag_number = 0;
    bcmos_errno err = BCM_ERR_OK;
    uint32_t data_len = bcmos_buf_length(tx_buf);
    uint8_t *data = bcmos_buf_data(tx_buf);

    /* fragment & send loop.
     * "do { } while (0)" is used to simplify error handling
     */
    do
    {
        uint32_t send_len = data_len + BCMTR_HDR_SIZE;
        bcmos_buf *frag;

        if (send_len > conn->cfg.max_mtu)
        {
            send_len = conn->cfg.max_mtu;
            tmsg->hdr.more_fragments = BCMOS_TRUE;
        }
        else
        {
            tmsg->hdr.more_fragments = BCMOS_FALSE;
        }

        frag = bcmos_buf_alloc(send_len);
        if (frag == NULL)
        {
            err = BCM_ERR_NOMEM;
            break;
        }

        tmsg->hdr.frag_number = frag_number++;

        /* Pack correlation tag, command and length */
        bcmtr_header_pack(&tmsg->hdr, bcmos_buf_tail_push(frag, BCMTR_HDR_SIZE));
        memcpy(bcmos_buf_tail_push(frag, send_len - BCMTR_HDR_SIZE), data, send_len - BCMTR_HDR_SIZE);

        /* Send using customer-provided driver. Buffer ownership is passed to the plugin */
        err = _bcmtr_send_to_line(conn, subch, frag, flags);
        if (err)
        {
            break;
        }

        data_len -= (send_len - BCMTR_HDR_SIZE);
        data += (send_len - BCMTR_HDR_SIZE);

    } while (data_len);

    /* The original buffer is no longer needed */
    bcmos_buf_free(tx_buf);

    return err;
}

static bcmos_errno _bcmtr_fragment_if_needed_and_send(
    bcmtr_conn *conn,
    bcmolt_subchannel subch,
    bcmtr_msg *tmsg,
    bcmos_buf *tx_buf,
    bcmtr_send_flags flags)
{
    if (bcmos_buf_length(tx_buf) + BCMTR_HDR_SIZE <= conn->cfg.max_mtu)
    {
        /* Pack correlation tag, command and length. */
        bcmtr_header_pack(&tmsg->hdr, bcmos_buf_head_push(tx_buf, BCMTR_HDR_SIZE));

        /* Send using customer-provided driver */
        return _bcmtr_send_to_line(conn, subch, tx_buf, flags);
    }
    else
    {
        return _bcmtr_fragment_and_send(conn, subch, tmsg, tx_buf, flags);
    }
}

/* Allocate tx buffer and pack */
static bcmos_errno _bcmtr_pack(const bcmtr_conn *conn, bcmolt_msg *msg, bcmos_buf **pbuf)
{
    int32_t len = bcmolt_msg_get_packed_length(msg);
    bcmos_buf *buf;
    bcmolt_buf stream;
    bcmos_errno err;

    *pbuf = NULL;

    if (len < 0)
        return (bcmos_errno)len;

    /* Allocate buffer. Not transport buffers are always allocated with sufficient headroom */
    buf = bcmos_buf_alloc(len);
    if (buf == NULL)
        return BCM_ERR_NOMEM;

    /* Pack */
    bcmolt_buf_init(&stream, len, bcmos_buf_data(buf));
    err = bcmolt_msg_pack(msg, &stream);
    if (err)
    {
        bcmos_buf_free(buf);
        return err;
    }
    bcmos_buf_length_set(buf, bcmolt_buf_get_used(&stream));

    *pbuf = buf;

    return BCM_ERR_OK;
}

/* Pack and Send message.
 * Internal function.
 */
static bcmos_errno _bcmtr_send(bcmtr_conn *conn, bcmolt_msg *msg, bcmtr_send_flags flags, bcmtr_msg **ptmsg)
{
    bcmos_buf *tx_buf = NULL;
    bcmtr_msg *tmsg = NULL;
    bcmos_errno err;

    /* Allocate transport buffer and pack. If fails just return. Error is already reported */
    err = _bcmtr_pack(conn, msg, &tx_buf);
    if (err)
    {
        return err;
    }

    /* pack & transmit flow is done under lock.
     * "do { } while (0)" is used to simplify error handling
     */

    bcmos_mutex_lock(&conn->mutex);

    do
    {
        if (!conn->connected)
        {
            ++conn->stat.not_connected;
            err = BCM_ERR_NOT_CONNECTED;
            break;
        }

        /* Re-use existing tmsg block or allocate new one */
        if (ptmsg)
            tmsg = *ptmsg;

        /* Allocate message transport header */
        if (tmsg == NULL)
        {
            tmsg = _bcmtr_tmsg_alloc(&conn->free_req_list);
            if (tmsg == NULL)
            {
                ++conn->stat.msg_no_mem;
                err = BCM_ERR_TOO_MANY_REQS;
                break;
            }
        }
        tmsg->msg = msg;

        /* Fill transport header */
        bcmtr_header_fill(tmsg->msg, &tmsg->hdr);

        tmsg->err = BCM_ERR_IN_PROGRESS;
        tmsg->timestamp = bcmos_timestamp();
        msg->timestamp = tmsg->timestamp;

        BCMTR_CLD_CHECK_NOTIFY(
            conn->device,
            &tmsg->hdr,
            BCMTR_CLD_EV_SEND,
            tmsg->timestamp,
            bcmos_buf_data(tx_buf),
            bcmos_buf_length(tx_buf),
            msg);

        if (msg->group == BCMOLT_MGT_GROUP_AUTO)
        {
            /* Distribute indications to subscribed clients */
            err = _bcmtr_send_auto(conn, tmsg, tx_buf, flags);
        }
        else
        {
            err = _bcmtr_fragment_if_needed_and_send(conn, msg->subch, tmsg, tx_buf, flags);
        }

        /* At this point tx_buf ownership passed on */
        tx_buf = NULL;

        if (err != BCM_ERR_OK)
        {
            ++conn->stat.msg_comm_err;
            break;
        }

        ++conn->stat.msg_sent;

    } while (0);

    if (err != BCM_ERR_OK || ptmsg == NULL)
    {
        if (tmsg != NULL)
        {
            _bcmtr_tmsg_free(tmsg, NULL);
            tmsg = NULL;
        }
    }

    bcmos_mutex_unlock(&conn->mutex);

    if (tx_buf)
        bcmos_buf_free(tx_buf);

    if (ptmsg != NULL)
        *ptmsg = tmsg;

    return err;
}

/* Handle rx data. Returns number of messages that was identified and reassembled. Can be 0 or 1 */
static void _bcmtr_rx_packet(bcmtr_conn *conn, bcmolt_subchannel subch, bcmos_buf *buf)
{
    bcmtr_hdr hdr;
    bcmtr_msg *tmsg;
    bcmos_bool msg_done;
    bcmos_bool is_response;

    /* Transport lock. This lock is needed to
     * - allocate/release transport header
     * - update statistics
     */
    bcmos_mutex_lock(&conn->mutex);

    /* If some data was received - handle it */
    if (bcmos_buf_length(buf) < BCMTR_HDR_SIZE)
    {
        /* Message is too short */
        ++conn->stat.msg_comm_err;
        goto rx_free_buf_and_exit;
    }

    bcmtr_header_unpack(bcmos_buf_head_pull(buf, BCMTR_HDR_SIZE), &hdr);

    is_response = (hdr.dir == BCMOLT_MSG_DIR_RESPONSE);

    /* Handle internal messages: auto_reg_unreg and keep_alive */
    if (!is_response && (hdr.auto_reg_unreg || hdr.keep_alive))
    {
        /* Restore buffer */
        bcmos_buf_head_push(buf, BCMTR_HDR_SIZE);
        if (hdr.auto_reg_unreg)
        {
            _bcmtr_handle_auto_reg_unreg(conn, subch, buf);
        }
        else
        {
            _bcmtr_handle_keep_alive(conn, subch, buf);
        }
        bcmos_mutex_unlock(&conn->mutex);
        return;
    }

    /* Find transport header. If not found - allocate new for autonomous message */
    tmsg = _bcmtr_msg_get_by_corr_tag(conn, &hdr);
    if (!tmsg)
    {
        if (!is_response)
        {
            /* Allocate new transport block */
            tmsg = _bcmtr_tmsg_alloc(&conn->free_auto_list);
            if (!tmsg)
            {
                ++conn->stat.msg_too_many_auto;
                goto rx_free_buf_and_exit;
            }

            /*
             * The newly allocated message is put on the list of "messages in progress".
             * If it is a complete message, it is taken out of the list a few lines
             * later, before it is passed to application callback. If it is a fragment,
             * it stays on the list until message is fully reassembled or timed out
             */
            tmsg->err = BCM_ERR_IN_PROGRESS;
            TAILQ_INSERT_TAIL(&conn->msg_list, tmsg, l);
        }
        else
        {
            /* Response, but no request - discard */
            ++conn->stat.msg_no_req;
            BCMTR_CLD_CHECK_NOTIFY(conn->device, &hdr, BCMTR_CLD_EV_RECV_DISCARD,
                bcmos_timestamp(), bcmos_buf_data(buf), bcmos_buf_length(buf), NULL);
            goto rx_free_buf_and_exit;
        }
    }

    /* Reassemble. "buf" should not be used following this call */
    tmsg->timestamp = bcmos_timestamp();
    tmsg->hdr = hdr;
    tmsg->subch = subch;

    /*
     * Reassemble the message. _bcmtr_reassemble() function collects all message fragments
     * and returns BCMOS_TRUE when message is fully assembled.
     * Note that in majority of cases the message consists of only one fragment.
     *
     * The buf parameter is stored in tmsg and shouldn't be used after this point.
     */
    if (tmsg->hdr.keep_alive)
    {
        msg_done = BCMOS_TRUE;
        tmsg->err = BCM_ERR_OK;
        tmsg->rx_buf = buf;
    }
    else
    {
        msg_done = _bcmtr_reassemble(conn, tmsg, buf);
    }

    /* If expects more parts - nothing more to do here */
    if (!msg_done)
        goto rx_done;

    if (tmsg->err && !is_response)
    {
        _bcmtr_tmsg_free(tmsg, &conn->msg_list);
        goto rx_done;
    }

    /* Done with the message. Get it out of pending message queue to avoid race condition
     * when timeout happens while the message is in flight to the destination task.
     */
    TAILQ_REMOVE(&conn->msg_list, tmsg, l);

    /* Notify rx. conn->mutex is still taken */
    if (is_response)
    {
        ++conn->stat.msg_resp_received;
        /* Unlock connection and notify waiting task that response has been received */
        bcmos_mutex_unlock(&conn->mutex);
        _bcmtr_notify_ready(conn, tmsg);
    }
    else
    {
        /* Notify message recipient(s) that request or autonomous message has been received.
         * This function must be called under connection lock, so, the lock is released after the call.
         */
        _bcmtr_notify_rx_req_auto(conn, tmsg);
        bcmos_mutex_unlock(&conn->mutex);
    }

    return;

    /* Error return */
rx_free_buf_and_exit:
    bcmos_mutex_unlock(&conn->mutex);
    bcmos_buf_free(buf);
    return;

    /* return without a buffer */
rx_done:
    bcmos_mutex_unlock(&conn->mutex);
    return;
}

/*
 * Plugin support interface
 */

/** Pass received buffer to transport layer */
void bcmtr_packet_receive(bcmolt_devid device, bcmolt_subchannel subch, bcmos_buf *buf)
{
    bcmtr_conn *conn = NULL;
    if (device < BCMTR_MAX_DEVICES)
        conn = conn_info[device].conn;
    if (!conn || !conn->connected)
    {
        ++bcmtr_global_stats.no_conn;
        bcmos_buf_free(buf);
        return;
    }

    /* Forward received buffer to connection */
    _bcmtr_rx_packet(conn, subch, buf);
}

/* Increment RX_NO_MEM discard counter */
void bcmtr_rx_increment_rx_no_mem(bcmolt_devid device)
{
    ++bcmtr_global_stats.no_mem;
}

/* Rx thread handler */
static int _bcmtr_rx_task_handler(long data)
{
    bcmos_task *my_task = bcmos_task_current();
    bcmtr_plugin_recv_info *recv_info = (bcmtr_plugin_recv_info *)data;
    bcmolt_devid device;
    bcmos_buf *buf;
    bcmolt_subchannel subch;
    int rc;

    while(!my_task->destroy_request)
    {
        /* Plugin driver's recv - get pending rx packet is any.
         * The function is not allowed to block for more then BCMTR_MSG_TIMEOUT ms
         */
        rc = recv_info->recv(recv_info->ch, &device, &subch, &buf);
        if (rc != BCM_ERR_OK)
        {
            if (rc != BCM_ERR_TIMEOUT)
            {
                /* In case of timeout just continue, no sleep here.
                   It is normal situation that plugin didn't receive any packets during polling interval.
                   It is plugin's responsibility to block while it waits for receive, no need to sleep here.
                */
                if (rc == BCM_ERR_NOMEM)
                    ++bcmtr_global_stats.no_mem;
                bcmos_usleep(1000);
            }
            continue;
        }

        /* Got packet. Forward it to the relevant per-device connection */
        bcmtr_packet_receive(device, subch, buf);
    }
    my_task->destroyed = BCMOS_TRUE;

    return 0;
}

/* Create RX task to handle receive in polling mode */
bcmos_errno bcmtr_rx_task_create(bcmos_task *task, const char *name, bcmtr_plugin_recv_info *recv_info)
{
    bcmos_task_parm parm = {
        .priority = TASK_PRIORITY_TRANSPORT_RX,
        .stack_size = BCMTR_RX_THREAD_STACK,
        .handler = _bcmtr_rx_task_handler,
        .name = name,
        .data = (long)recv_info
    };
    bcmos_errno err;
    err = bcmos_task_create(task, &parm);
    return err;
}

/*
 * Internal transport interface
 */

static bcmos_errno _bcmtr_connect(bcmolt_devid device, const bcmtr_conn_parms *conn_parms, bcmtr_conn **p_conn)
{
    bcmtr_conn *conn;
    bcmos_errno err;
    bcmos_bool new_connection;

    bcmos_mutex_lock(&conn_lock);

    conn = *p_conn;
    new_connection = (conn == NULL);
    if (new_connection)
    {
        /* Allocate */
        conn = (bcmtr_conn *)bcmos_calloc(sizeof(*conn));
        if (conn == NULL)
        {
            bcmos_mutex_unlock(&conn_lock);
            return BCM_ERR_NOMEM;
        }
        snprintf(conn->name, sizeof(conn->name), "tr_rx%u", device);
        conn->device = device;
        TAILQ_INIT(&conn->free_req_list);
        TAILQ_INIT(&conn->free_auto_list);
        TAILQ_INIT(&conn->msg_list);
        bcmos_mutex_create(&conn->mutex, 0, NULL);
    }

    /* Set configuration parameters and initialize plugin */
    conn->cfg.plugin_cfg = *conn_parms;
    err = bcmtr_cfg_init(device, &conn->cfg, &conn->driver);

    /* Convert timeouts to us */
    conn->cfg.msg_timeout *= 1000;
    conn->cfg.msg_ready_timeout *= 1000;
    conn->cfg.msg_wait_timeout *= 1000;

    /* Set defaults */
    conn->timeout_check_period = conn->cfg.msg_wait_timeout;
    conn->last_timeout_check = bcmos_timestamp();

    if (new_connection)
    {
        /* Allocate and initialize transport blocks and put onto free request and autonomous lists */
        err = err ? err : _bcmtr_tmsg_list_alloc(conn);
    }

    /* Open/connect on driver level */
    err = err ? err : conn->driver.open(device, &conn->cfg.plugin_cfg, &conn->drv_priv);

    if (err)
        goto cleanup;

    conn->connected = BCMOS_TRUE;

    *p_conn = conn;
    bcmos_mutex_unlock(&conn_lock);

    return BCM_ERR_OK;

cleanup:
    /* Stop plugin */
    if (conn->driver.close)
        conn->driver.close(conn->drv_priv);

    /* Release memory if new connection */
    if (new_connection)
    {
        bcmos_mutex_destroy(&conn->mutex);
        _bcmtr_tmsg_list_free(conn);
        bcmos_free(conn);
    }

    bcmos_mutex_unlock(&conn_lock);

    return err;
}

/** Query whether or not the device is currently connected */
bcmos_errno bcmtr_is_connected(bcmolt_devid device, bcmos_bool *is_connected)
{
    bcmtr_conn *conn;
    if (device >= BCMTR_MAX_DEVICES)
    {
        return BCM_ERR_RANGE;
    }
    conn = conn_info[device].conn;
    *is_connected = (conn != NULL && conn->connected);
    return BCM_ERR_OK;
}

/** Get connection info */
bcmos_errno bcmtr_connect_info_get(bcmolt_devid device, bcmtr_conn_parms *conn_parms)
{
    bcmtr_conn *conn;
    bcmos_bool is_connected = BCMOS_FALSE;
    bcmos_errno err;

    err = bcmtr_is_connected(device, &is_connected);
    if (!is_connected)
        return (err != BCM_ERR_OK) ? err : BCM_ERR_NOT_CONNECTED;

    conn = conn_info[device].conn;
    *conn_parms = conn->cfg.plugin_cfg;
    return BCM_ERR_OK;
}

/** Open transport channel */
bcmos_errno bcmtr_connect(bcmolt_devid device, const bcmtr_conn_parms *conn_parms)
{
    bcmtr_conn **p_conn;
    bcmos_errno rc = BCM_ERR_OK;

    if (device >= BCMTR_MAX_DEVICES || conn_parms == NULL)
        return BCM_ERR_PARM;

    p_conn = &conn_info[device].conn;

#ifdef BCM_SUBSYSTEM_EMBEDDED
    /* Managed connection ? */
    if ((conn_parms->mode & BCMOLT_CONN_TYPE_MASK_MUX) != 0)
    {
        /* Generate random ID for keep-alive */
        srand(bcmos_timestamp());
        /* coverity[dont_call] - this doesn't need to be cryptographically secure */
        bcmtr_conn_id = (uint16_t)rand();
    }

    /* Separate unmanaged connection ? */
    if ((conn_parms->mode & BCMOLT_CONN_TYPE_MASK_APP) != 0 &&
        (conn_parms->mode & BCMOLT_CONN_TYPE_MASK_MUX) == 0)
    {
        /* Separate unmanaged connection can only be created if primary channel is connected */
        if (*p_conn == NULL || !(*p_conn)->connected)
        {
            BCMTR_LOG(device, ERROR, "Can't create unmanaged connection. Primary channel is not connected\n");
            return BCM_ERR_NOT_CONNECTED;
        }
        p_conn = &conn_info[device].aux_conn;
    }
#endif

    if (*p_conn == NULL || !(*p_conn)->connected)
    {
        /* Prepare unmanaged channel */
        rc = _bcmtr_connect(device, conn_parms, p_conn);
#ifdef BCM_SUBSYSTEM_EMBEDDED
        /* If primary connection is inband, it is used for managed and unmanaged "clients". In this case "aux_conn"
           pointer is equal to "conn".
           If primary connection is PCIE, additional connection is required for unmanaged clients.
           In this case aux_conn points to the separate connection structure.
        */
        if (rc == BCM_ERR_OK && (conn_parms->mode & BCMOLT_CONN_TYPE_MASK_APP) != 0)
        {
            /* The connection we just created supports unmanaged clients. If it is the same as primary,
               assign the aux_conn pointer. */
            if (conn_info[device].aux_conn == NULL)
                conn_info[device].aux_conn = conn_info[device].conn;
        }
#endif
    }

    return rc;
}

/** Close a single transport channel.
 * Connection structures are preserved
 */
static void _bcmtr_disconnect1(bcmtr_conn *conn)
{
    bcmos_mutex_lock(&conn->mutex);

    conn->connected = BCMOS_FALSE;

    /* Close connection at plugin level */
    if (conn->driver.close)
    {
        conn->driver.close(conn->drv_priv);
    }

    /* Cleanup plugin info */
    memset(&conn->driver, 0, sizeof(conn->driver));

    /* Release all pending messages */
    _bcmtr_tmsg_list_free_pending(conn);

    bcmos_mutex_unlock(&conn->mutex);
}

/** Close transport channel.
 * Connection structures are preserved
 */
bcmos_errno bcmtr_disconnect(bcmolt_devid device)
{
    bcmtr_conn *conn;

    if (device >= BCMTR_MAX_DEVICES)
    {
        return BCM_ERR_RANGE;
    }
    bcmos_mutex_lock(&conn_lock);
    conn = conn_info[device].conn;
    if (!conn)
    {
        bcmos_mutex_unlock(&conn_lock);
        return BCM_ERR_NOT_CONNECTED;
    }
    _bcmtr_disconnect1(conn);

#ifdef BCM_SUBSYSTEM_EMBEDDED
    /* Close connection and disconnect all clients */
    bcmtr_disconnect_aux();
    _bcmtr_client_disconnect_all(BCMOLT_CONN_TYPE_MUX);
#endif
    bcmos_mutex_unlock(&conn_lock);

    return BCM_ERR_OK;
}

/** Close transport channel */
static void _bcmtr_kill_connection(bcmolt_devid device)
{
    bcmtr_conn *conn;

    bcmos_mutex_lock(&conn_lock);
    conn = conn_info[device].conn;
    if (!conn)
    {
        bcmos_mutex_unlock(&conn_lock);
        return;
    }

    /* Disconnect */
    bcmtr_disconnect(device);

#ifdef BCM_SUBSYSTEM_EMBEDDED
    /* Kill auxiliary connection */
    if (conn_info[device].aux_conn && conn_info[device].aux_conn != conn)
    {
        bcmtr_conn *aux_conn = conn_info[device].aux_conn;
        /* coverity[sleep] - sleeping with a mutex here is intentional */
        bcmos_usleep(100000);
        bcmos_mutex_lock(&aux_conn->mutex);
        _bcmtr_tmsg_list_free(aux_conn);
        bcmos_mutex_unlock(&aux_conn->mutex);
        bcmos_mutex_destroy(&aux_conn->mutex);
        bcmos_free(aux_conn);
    }
    conn_info[device].aux_conn = NULL;
#endif

    conn_info[device].conn = NULL;

    /* Release memory */
    /* coverity[sleep] - sleeping with a mutex here is intentional */
    bcmos_usleep(100000);
    bcmos_mutex_lock(&conn->mutex);
    _bcmtr_tmsg_list_free(conn);
    bcmos_mutex_unlock(&conn->mutex);
    bcmos_mutex_destroy(&conn->mutex);
    bcmos_free(conn);
    bcmos_mutex_unlock(&conn_lock);
}

/*
 * External message interface
 */

/* Register for notification that transmit failed because tx_queue was full */
bcmos_errno bcmtr_tx_overflow_cb_register(bcmolt_devid device, F_bcmtr_tx_overflow cb)
{
    if (device >= BCMTR_MAX_DEVICES)
    {
        return BCM_ERR_RANGE;
    }

    conn_info[device].overflow_cb = cb;
    return BCM_ERR_OK;
}

/* Register optional callback that "translates" indication before it is delivered
 * \param[in]   cb              Callback to be called. NULL=unregister
 */
void bcmtr_rx_translate_cb_register(F_bcmtr_rx_translate cb)
{
    rx_translate_cb = cb;
}

/* Send message. Don't expect response. */
bcmos_errno bcmtr_send(bcmolt_devid device, bcmolt_msg *msg, bcmtr_send_flags flags)
{
    bcmtr_conn *conn;
    bcmos_errno err;

    err = _bcmtr_conn_get(device, &conn);
    if (err)
        return err;

    err = _bcmtr_send(conn, msg, flags, NULL);

    /* Auto-release response */
    if ((flags & BCMTR_SEND_FLAGS_AUTO_FREE) != 0)
    {
        bcmolt_msg_free(msg);
    }

    if (err)
    {
        if (err == BCM_ERR_QUEUE_FULL && conn_info[device].overflow_cb)
        {
            conn_info[device].overflow_cb(conn->device, flags);
        }
    }

    return err;
}

static bcmos_errno bcmtr_call_err(bcmolt_msg *msg, bcmos_errno err, const char *err_text)
{
    msg->dir = BCMOLT_MSG_DIR_RESPONSE;
    msg->err = err;
    if (err_text != NULL)
    {
        strncpy(msg->err_text, err_text, BCMOLT_MAX_ERR_TEXT_LENGTH-1);
        msg->err_text[BCMOLT_MAX_ERR_TEXT_LENGTH-1] = 0;
    }
    return err;
}

/* Send message and wait for response */
bcmos_errno bcmtr_call(bcmolt_devid device, bcmolt_msg *msg)
{
    bcmtr_msg *tmsg = NULL;
    bcmtr_conn *conn;
    bcmos_errno err;
    bcmolt_devid msg_dev = msg->device;
    bcmolt_subchannel subch = msg->subch;

    msg->err = BCM_ERR_OK;
    msg->dir = BCMOLT_MSG_DIR_REQUEST;
    msg->corr_tag = ++corr_tag;

    err = _bcmtr_conn_get(device, &conn);
    if (err)
    {
        return bcmtr_call_err(msg, err, NULL);
    }

    /* transmit request under connection lock */
    bcmos_mutex_lock(&conn->mutex);
    err = _bcmtr_send(conn, msg, BCMTR_SEND_FLAGS_CALL, &tmsg);
    if (err != BCM_ERR_OK)
    {
        bcmos_mutex_unlock(&conn->mutex);
        return bcmtr_call_err(msg, err, NULL);
    }
    TAILQ_INSERT_TAIL(&conn->msg_list, tmsg, l);
    bcmos_mutex_unlock(&conn->mutex);

    /* Wait for response or timeout.
     * Message timeout is enforced by audit rather than semaphore timeout option
     */
    bcmos_sem_wait(&tmsg->sem, BCMOS_WAIT_FOREVER);

    /* Connection could've been killed while we are waiting here.
     * It is indicated by COMM_FAILURE in msg->err.
     * In this case transport header (tmsg) is already released
     */
    if (msg->err == BCM_ERR_COMM_FAIL)
    {
        return bcmtr_call_err(msg, msg->err, NULL);
    }

    err = tmsg->err;
    if (!err)
    {
        err = _bcmtr_msg_unpack(conn, tmsg->rx_buf, &tmsg->hdr, tmsg->timestamp, &msg);
    }

    /* Take connection lock again in order to release transport header safely */
    bcmos_mutex_lock(&conn->mutex);
    _bcmtr_tmsg_free(tmsg, NULL);
    bcmos_mutex_unlock(&conn->mutex);

    if (msg)
    {
        /* Restore message fields */
        msg->device = msg_dev;
        msg->subch = subch;
        return bcmtr_call_err(msg, err ? err : msg->err, NULL);
    }
    else
    {
        return err;
    }
}

/* Register specific message handler */
static bcmos_errno _bcmtr_msg_handler_register(bcmolt_devid device, const bcmtr_handler_parm *parm,
    bcmos_bool *is_auto_mask_changed)
{
    bcmtr_handler *h, *h_tmp;
    bcmos_module_id module;
    bcmolt_api_group_id msg_id;
    bcmos_errno err;

    *is_auto_mask_changed = BCMOS_FALSE;

    /* Specific object/group/subgroup */
    err = bcmolt_api_group_id_combine(parm->object, parm->group, parm->subgroup, &msg_id);
    if (err)
        return err;

    if ((parm->flags & BCMOLT_AUTO_FLAGS_DISPATCH))
    {
        if (parm->module != BCMOS_MODULE_ID_NONE)
        {
            module = parm->module;
        }
        else
        {
            module = bcmos_module_current();
        }
    }
    else
    {
        module = BCMOS_MODULE_ID_NONE;
    }

    /* Make sure that the same handler isn't already registered */
    STAILQ_FOREACH_SAFE(h, &conn_info[device].msg_handler_list[msg_id][parm->instance], l, h_tmp)
    {
        if (h->app_cb == parm->app_cb && h->module == module && h->olt == parm->olt)
        {
            return BCM_ERR_ALREADY;
        }
    }

    h = (bcmtr_handler *)bcmos_calloc(sizeof(bcmtr_handler));
    if (!h)
        return BCM_ERR_NOMEM;
    h->app_cb = parm->app_cb;
    h->flags = parm->flags;
    h->module = module;
    h->olt = parm->olt;

    bcmos_mutex_lock(&conn_lock);

#ifdef BCM_SUBSYSTEM_HOST
    /* Registration with tr-mux is per device, per-object */
    if (parm->group == BCMOLT_MGT_GROUP_AUTO &&
        !(conn_info[device].auto_masks[parm->object] & (1ULL << parm->subgroup)))
    {
        *is_auto_mask_changed = BCMOS_TRUE;
        conn_info[device].auto_masks[parm->object] |= (1ULL << parm->subgroup);
    }
#else
    /* On the embedded side only allow 1 registration per message type */
    if (!STAILQ_EMPTY(&conn_info[device].msg_handler_list[msg_id][parm->instance]))
    {
        bcmos_mutex_unlock(&conn_lock);
        bcmos_free(h);
        return BCM_ERR_ALREADY;
    }
#endif

    /* Store the new handler */
    STAILQ_INSERT_TAIL(&conn_info[device].msg_handler_list[msg_id][parm->instance], h, l);

    bcmos_mutex_unlock(&conn_lock);

    return BCM_ERR_OK;
}

/** Register message handler
 *
 * \param[in]   device          OLT device index
 * \param[in]   parm            Registration parameters
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_msg_handler_register(bcmolt_devid device, const bcmtr_handler_parm *parm)
{
    bcmos_bool auto_mask_changed = BCMOS_FALSE;
    bcmos_errno err = BCM_ERR_OK;

    if (device >= BCMTR_MAX_DEVICES || !parm || !parm->app_cb || parm->instance >= BCMTR_MAX_INSTANCES)
    {
        return BCM_ERR_PARM;
    }

    if ((unsigned)parm->object >= BCMOLT_OBJ_ID__NUM_OF)
    {
        bcmtr_handler_parm p1 = *parm;
        BCMOLT_API_FOR_EACH_OBJ_ID(p1.object)
        {
            err = bcmtr_msg_handler_register(device, &p1);
            /* Ignore RANGE or NOENT error that indicate that the object being iterated doesn't have this group */
            /* Ignore ALREADY error that indicates that registration is already present for specific message and was skipped */
            if (err != BCM_ERR_OK && err != BCM_ERR_RANGE && err != BCM_ERR_NOENT && err != BCM_ERR_ALREADY)
            {
                return err;
            }
        }
        return BCM_ERR_OK;
    }

    if ((unsigned)parm->group == BCMOLT_MGT_GROUP_ANY)
    {
        bcmtr_handler_parm p1 = *parm;
        for (p1.group = BCMOLT_MGT_GROUP__BEGIN; p1.group < BCMOLT_MGT_GROUP__NUM_OF; p1.group++)
        {
            err = bcmtr_msg_handler_register(device, &p1);
            /* Ignore RANGE, NOENT and ALREADY errors for the same reasons mentioned above */
            if (err != BCM_ERR_OK && err != BCM_ERR_RANGE && err != BCM_ERR_NOENT && err != BCM_ERR_ALREADY)
            {
                return err;
            }
        }
        return BCM_ERR_OK;
    }

    if ((unsigned)parm->subgroup == BCMOLT_SUBGROUP_ANY)
    {
        bcmtr_handler_parm p1 = *parm;

        /* Note that subgroup operations, indications, etc start subgroup numbering at 1 (0 is reserved) but for group
         * types that don't have any subgroups, e.g. cfg, 0 is the only valid index. */
        for (p1.subgroup = 0; err == BCM_ERR_OK; p1.subgroup++)
        {
            bcmos_bool changed = BCMOS_FALSE;
            err = _bcmtr_msg_handler_register(device, &p1, &changed);

            /* Skip holes and handlers that have already been registered */
            if (err == BCM_ERR_NOENT || err == BCM_ERR_ALREADY)
            {
                err = BCM_ERR_OK;
                continue;
            }

            auto_mask_changed |= changed;
        }
        if (auto_mask_changed)
        {
            _bcmtr_auto_reg_update_send(device, parm->object);
        }
        return (err == BCM_ERR_RANGE) ? BCM_ERR_OK : err;
    }

    /* Specific object, group, subgroup */
    err = _bcmtr_msg_handler_register(device, parm, &auto_mask_changed);
    if (auto_mask_changed)
    {
        _bcmtr_auto_reg_update_send(device, parm->object);
    }

    return err;
}

/* Unregister autonomous message handler for specific object, group, subgroup */
static bcmos_errno _bcmtr_msg_handler_unregister(bcmolt_devid device, const bcmtr_handler_parm *parm,
    bcmos_bool *is_auto_mask_changed)
{
    bcmolt_api_group_id msg_id;
    bcmtr_handler *h, *h_tmp;
    bcmos_errno err = BCM_ERR_OK;

    *is_auto_mask_changed = BCMOS_FALSE;

    err = bcmolt_api_group_id_combine(parm->object, parm->group, parm->subgroup, &msg_id);
    if (err)
        return err;

    bcmos_mutex_lock(&conn_lock);

    STAILQ_FOREACH_SAFE(h, &conn_info[device].msg_handler_list[msg_id][parm->instance], l, h_tmp)
    {
        if ((h->app_cb == parm->app_cb && h->olt == parm->olt) || !parm->app_cb)
        {
            STAILQ_REMOVE(&conn_info[device].msg_handler_list[msg_id][parm->instance], h, bcmtr_handler, l);
            bcmos_free(h);
        }
    }

#ifdef BCM_SUBSYSTEM_HOST
    /* Check if registration mask changed */
    if (parm->group == BCMOLT_MGT_GROUP_AUTO)
    {
        int i;
        /* See if auto msg is no longer registered for for any instance */
        *is_auto_mask_changed = BCMOS_TRUE;
        for (i = 0; i < BCMTR_MAX_INSTANCES && *is_auto_mask_changed; i++)
        {
            if (!STAILQ_EMPTY(&conn_info[device].msg_handler_list[msg_id][i]))
            {
                *is_auto_mask_changed = BCMOS_FALSE;
                break;
            }
        }
        if (*is_auto_mask_changed)
        {
            conn_info[device].auto_masks[parm->object] &= ~(1ULL << parm->subgroup);
        }
    }
#endif
    bcmos_mutex_unlock(&conn_lock);

    return BCM_ERR_OK;
}



/* Unregister autonomous message handler */
bcmos_errno bcmtr_msg_handler_unregister(bcmolt_devid device, const bcmtr_handler_parm *parm)
{
    bcmos_bool auto_mask_changed = BCMOS_FALSE;
    bcmos_errno err = BCM_ERR_OK;

    if (device >= BCMTR_MAX_DEVICES || !parm || parm->instance >= BCMTR_MAX_INSTANCES)
    {
        return BCM_ERR_PARM;
    }

    if ((unsigned)parm->object >= BCMOLT_OBJ_ID__NUM_OF)
    {
        bcmtr_handler_parm p1 = *parm;
        BCMOLT_API_FOR_EACH_OBJ_ID(p1.object)
        {
            err = bcmtr_msg_handler_unregister(device, &p1);
            /* Ignore RANGE or NOENT error that indicate that the object being iterated doesn't have this group */
            if (err != BCM_ERR_OK && err != BCM_ERR_RANGE && err != BCM_ERR_NOENT)
            {
                return err;
            }
        }
        return BCM_ERR_OK;
    }

    if ((unsigned)parm->group == BCMOLT_MGT_GROUP_ANY)
    {
        bcmtr_handler_parm p1 = *parm;
        for (p1.group = BCMOLT_MGT_GROUP__BEGIN; p1.group < BCMOLT_MGT_GROUP__NUM_OF && !err; p1.group++)
        {
            err = bcmtr_msg_handler_unregister(device, &p1);
            /* Ignore RANGE and NOENT errors for the same reasons mentioned above */
            if (err != BCM_ERR_OK && err != BCM_ERR_RANGE && err != BCM_ERR_NOENT)
            {
                return err;
            }
        }
        return BCM_ERR_OK;
    }

    if ((unsigned)parm->subgroup == BCMOLT_SUBGROUP_ANY)
    {
        bcmtr_handler_parm p1 = *parm;

        /* Note that subgroup operations, indications, etc start subgroup numbering at 1 (0 is reserved) but for group
         * types that don't have any subgroups, e.g. cfg, 0 is the only valid index. */
        for (p1.subgroup = 0; err == BCM_ERR_OK; p1.subgroup++)
        {
            bcmos_bool changed = BCMOS_FALSE;
            err = _bcmtr_msg_handler_unregister(device, &p1, &changed);

            /* Skip holes */
            if (err == BCM_ERR_NOENT)
            {
                err = BCM_ERR_OK;
                continue;
            }

            auto_mask_changed |= changed;
        }
        if (auto_mask_changed)
        {
            _bcmtr_auto_reg_update_send(device, parm->object);
        }
        return (err == BCM_ERR_RANGE) ? BCM_ERR_OK : err;
    }

    /* Specific object, group, subgroup */
    err = _bcmtr_msg_handler_unregister(device, parm, &auto_mask_changed);
    if (auto_mask_changed)
    {
        _bcmtr_auto_reg_update_send(device, parm->object);
    }

    return err;
}

/** Get registration info
 *
 * \param[in]           device          OLT device index
 * \param[in,out]       parm            Registration parameters.
 *                                      instance, group, object, subgroup must be set
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_msg_handler_register_get(bcmolt_devid device, bcmtr_handler_parm *parm)
{
    bcmos_errno err;
    bcmolt_api_group_id msg_id;
    bcmtr_handler *h;

    if (!transport_initialized                  ||
        device >= BCMTR_MAX_DEVICES             ||
        !parm                                   ||
        parm->instance >= BCMTR_MAX_INSTANCES   ||
        (unsigned)parm->object >= BCMOLT_OBJ_ID__NUM_OF)
    {
        return BCM_ERR_PARM;
    }

    err = bcmolt_api_group_id_combine(parm->object, parm->group, parm->subgroup, &msg_id);
    if (err)
        return err;
    h = STAILQ_FIRST(&conn_info[device].msg_handler_list[msg_id][parm->instance]);
    if (h == NULL)
        return BCM_ERR_NOENT;

    parm->app_cb = h->app_cb;
    parm->flags = h->flags;
    parm->module = h->module;
    parm->olt = h->olt;

    return BCM_ERR_OK;
}

/* Get transport statistics */
bcmos_errno bcmtr_stat_get(bcmolt_devid device, bcmtr_stat *stat)
{
    bcmtr_conn *conn;
    bcmos_errno err;

    if (!stat)
    {
        return BCM_ERR_PARM;
    }
    err = _bcmtr_conn_get(device, &conn);
    if (err)
    {
        return err;
    }
    bcmos_mutex_lock(&conn->mutex);
    *stat = conn->stat;
    stat->msg_no_mem += bcmtr_global_stats.no_mem;
    stat->not_connected += bcmtr_global_stats.no_conn;
    memset(&conn->stat, 0, sizeof(conn->stat));
    bcmtr_global_stats.no_mem = bcmtr_global_stats.no_conn = 0;
    bcmos_mutex_unlock(&conn->mutex);

    return BCM_ERR_OK;
}


/** Initialize transport library.
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_init(bcmtr_init_parms *parms)
{
    bcmos_errno err = BCM_ERR_OK;
    bcmolt_devid device;

    if (transport_initialized)
        return BCM_ERR_OK;

    bcmos_printf("bcmtr_init: init transport library\n");

#ifdef ENABLE_LOG
    /* Create log ids */
    for (device = 0; device < BCMTR_MAX_DEVICES; device++)
    {
        if (!bcmtr_log_id[device] || bcmtr_log_id[device] == DEV_LOG_INVALID_ID)
        {
            char log_name[16];
            snprintf(log_name, sizeof(log_name) - 1, "transp_%u", device);
            bcmtr_log_id[device] = bcm_dev_log_id_register(log_name, DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
        }
    }
#endif

    /* Initialize handlers */
    for (device = 0; device < BCMTR_MAX_DEVICES; device++)
    {
        bcmolt_group_id group;
        for (group = 0; group < BCMOLT_API_GROUP_ID__NUM_OF; group++)
        {
            int inst;
            for (inst = 0; inst < BCMTR_MAX_INSTANCES; inst++)
            {
                STAILQ_INIT(&conn_info[device].msg_handler_list[group][inst]);
            }
        }
    }

#ifdef BCM_SUBSYSTEM_HOST
    err = _bcmtr_ind_task_create();
    if (err)
        return err;

    /* Allocate msg pools for indication delivery */
    for (device = 0; device < BCMTR_MAX_DEVICES && err == BCM_ERR_OK; device++)
    {
        bcmos_msg_pool_parm mp = {};
        char name[32];
        snprintf(name, sizeof(name) - 1, "transport_ind_%d", device);
        mp.name = name;
        mp.size = BCMTR_MAX_AUTO_IN_FLIGHT;
        err = bcmos_msg_pool_create(&conn_info[device].ind_msg_pool, &mp);
    }

    err = _bcmtr_timeout_task_create();
    if (err)
    {
        bcmos_task_destroy(&bcmtr_ind_task);
        return err;
    }
#else
    err = _bcmtr_client_timeout_task_create();
    if (err)
        return err;
#endif

    bcmos_mutex_create(&conn_lock, 0, NULL);

    init_parms = *parms;

    transport_initialized = BCMOS_TRUE;

    return err;
}

/** Release resources used by transport library.
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_exit(void)
{
    int i;

#ifdef BCM_SUBSYSTEM_HOST
    bcmos_task_destroy(&bcmtr_timeout_task);
    bcmos_task_destroy(&bcmtr_ind_task);

    /* Free msg pools for indication delivery */
    for (i = 0; i < BCMTR_MAX_DEVICES; i++)
    {
        bcmos_msg_pool_destroy(&conn_info[i].ind_msg_pool);
    }
#endif

    for (i = 0; i < BCMTR_MAX_DEVICES; i++)
    {
        _bcmtr_kill_connection(i);
    }

    bcmos_mutex_destroy(&conn_lock);

    return BCM_ERR_OK;
}
