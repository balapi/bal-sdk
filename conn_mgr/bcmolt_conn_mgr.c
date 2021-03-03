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

/* bcmolt_conn_mgr.c - connection manager implementation */

#include <bcmolt_conn_mgr_internal.h>
#include <bcm_dev_log.h>

/* "connecttion" info */
typedef struct bcmolt_cm_conn
{
    bcmolt_cmll_conn_id ll_conn_id;
    bcmolt_ldid device;
    bcmolt_subchannel subch;
    bcmos_bool connected;
    bcmolt_cm_addr peer_addr;
    bcmolt_conn_type conn_type;
    bcmolt_cm_cookie cookie;
    uint32_t last_rx_ts;
} bcmolt_cm_conn;

/* "connection mode" info */
typedef struct bcmolt_cm_mode_info
{
    bcmolt_conn_type_mask conn_types;
    bcmolt_cm_enable_parms enable_parms;
    long ll_handle;
    bcmos_task rx_task;
    bcmos_bool rx_task_created;
    bcmos_task accept_task;
    bcmos_bool accept_task_created;
} bcmolt_cm_mode_info;

static bcmolt_cm_init_parms cm_init_parms;
static bcmolt_cm_mode_info cm_mode_info[BCMOLT_CONN_TYPE__NUM_OF];
static bcmolt_cm_mode_info *cm_mode_ptrs[BCMOLT_CONN_TYPE__NUM_OF];
static bcmolt_cm_handlers cm_handlers[BCMOLT_CONN_TYPE__NUM_OF];
static bcmolt_cm_conn *cm_conn_array;
static bcmolt_conn_type_mask cm_conn_types;
static struct
{
    bcmos_bool in_progress;
    bcmos_bool got_reply;
    uint16_t corr_tag;
    bcmos_errno status;
} cm_connect_pending;
static bcmos_mutex cm_conn_lock;

/* Low-level transport driver */
static bcmolt_cmll_driver cmll_driver;

dev_log_id cm_log_id = DEV_LOG_INVALID_ID;

static bcmos_errno _cm_accept_new_connection(bcmolt_cmll_conn_id ll_conn_id, bcmolt_conn_type conn_type,
    bcmolt_ldid device, bcmolt_cm_addr *addr, bcmolt_subchannel subch, bcmolt_cm_conn_id *conn_id);
static void _cm_connect_msg_handler(bcmolt_cmll_conn_id ll_conn_id, bcmolt_cm_conn_id conn_id,
    bcmos_buf *buf, bcmolt_ldid device, bcmolt_cm_addr *addr);
static void _cmll_notify_disconnect(bcmolt_cm_conn_id conn_id);

/*
 * Internal helpers
 */

/* Pull inband header from packet buffer */
static inline void _cm_packet_header_pull(bcmos_buf *buf, bcm_cm_packet_hdr *cm_hdr)
{
    memcpy(cm_hdr, bcmos_buf_head_pull(buf, sizeof(*cm_hdr)), sizeof(*cm_hdr));
    cm_hdr->device = BCMOS_ENDIAN_LITTLE_TO_CPU_U16(cm_hdr->device);
    cm_hdr->subch = BCMOS_ENDIAN_LITTLE_TO_CPU_U16(cm_hdr->subch);
}

/* Push inband header into packet buffer */
static inline void _cm_packet_header_push(bcmos_buf *buf, bcmolt_ldid device, bcmolt_subchannel subch)
{
    bcm_cm_packet_hdr cm_hdr =
    {
        .device = BCMOS_ENDIAN_CPU_TO_LITTLE_U16(device),
        .subch = BCMOS_ENDIAN_CPU_TO_LITTLE_U16(subch)
    };
    memcpy(bcmos_buf_head_push(buf, sizeof(cm_hdr)), &cm_hdr, sizeof(cm_hdr));
}

/* Check connection match */
static bcmos_bool _check_conn_match(bcmolt_cm_mode_info *info_ptr, const bcmolt_cm_conn *conn,
    bcmolt_cmll_conn_id ll_conn_id, const bcmolt_cm_addr *addr, bcmolt_ldid device,
    bcmolt_subchannel subch)
{
    if (ll_conn_id == conn->ll_conn_id                                              &&
        (((info_ptr->enable_parms.flags & BCMOLT_CM_FLAG_MATCH_BY_ADDR) == 0)   ||
            (cmll_driver.addr_is_equal(&conn->peer_addr, addr)))                    &&
        (((info_ptr->enable_parms.flags & BCMOLT_CM_FLAG_MATCH_BY_DEV) == 0)    ||
            (device == conn->device))                                               &&
        (((info_ptr->enable_parms.flags & BCMOLT_CM_FLAG_MATCH_BY_SUBCH) == 0)  ||
            (subch == conn->subch)) )
    {
        return BCMOS_TRUE;
    }
    return BCMOS_FALSE;
}

/* Handle RX packet */
static bcmos_errno _cmll_handle_recv(bcmolt_cm_mode_info *info_ptr, bcmolt_cmll_conn_id ll_conn_id, bcmos_buf *buf,
    bcmolt_cm_addr *addr, bcmolt_cm_conn_id *conn_id, bcmolt_ldid *device, bcmolt_subchannel *subch)
{
    bcmolt_cm_conn_id id = BCMOLT_CM_CONN_ID_UNDEFINED;
    bcmolt_cm_conn *conn = NULL;
    uint8_t *data;
    bcm_cm_packet_hdr cm_hdr;

    /* Pop inband packet header */
    if (bcmos_buf_length(buf) < sizeof(bcm_cm_packet_hdr))
    {
        /* Invalid buffer ? */
        return BCM_ERR_IO;
    }

    /* Pull inband packet header */
    _cm_packet_header_pull(buf, &cm_hdr);

    /* Identify connection, if not identified by low-level transport */
    if (*conn_id == BCMOLT_CM_CONN_ID_UNDEFINED)
    {
        /* Look up connection by address */
        for (id = 0; id < cm_init_parms.max_conns; id++)
        {
            conn = &cm_conn_array[id];
            if (!conn->connected)
                continue;
            if (_check_conn_match(info_ptr, conn, ll_conn_id, addr, cm_hdr.device, cm_hdr.subch))
                break;
        }
        if (id >= cm_init_parms.max_conns)
        {
            id = BCMOLT_CM_CONN_ID_UNDEFINED;
            conn = NULL;
        }
    }
    else if (*conn_id < cm_init_parms.max_conns && cm_conn_array[*conn_id].connected)
    {
        id = *conn_id;
        conn = &cm_conn_array[*conn_id];
    }

    /* Identify CM_SETUP and CM_DISCONNECT packets */
    data = bcmos_buf_data(buf);

    /* CONNECT request/response ? */
    if (!memcmp(data, BCMOLT_CM_CONN_MAGIC, 8))
    {
        CM_LOG(INFO, "Connect request/response received from the peer: conn_id=%u\n", (unsigned)id);
        _cm_connect_msg_handler(ll_conn_id, id, buf, cm_hdr.device, addr);
        return BCM_ERR_ALREADY;
    }

    /* If connection is not found, discard packet */
    if (conn == NULL)
    {
        bcmos_errno err;
        /* Note that in case of error other than BCM_ERR_ALREADY buf is released by the caller */
        if ((info_ptr->enable_parms.flags & BCMOLT_CM_FLAG_AUTO_ACCEPT) == 0)
            return BCM_ERR_NOT_CONNECTED;
        /* Auto-connect */
        err = _cm_accept_new_connection(ll_conn_id, info_ptr->enable_parms.auto_accept_conn_type,
            cm_hdr.device, addr, cm_hdr.subch, &id);
        if (err != BCM_ERR_OK)
            return err;
        conn = &cm_conn_array[id];
    }

    if (!memcmp(data, BCMOLT_CM_DISC_MAGIC, 8))
    {
        CM_LOG(INFO, "Disconnect request received from the peer: conn_id=%u\n", (unsigned)id);
        _cmll_notify_disconnect(id);
        bcmos_buf_free(buf);
        return BCM_ERR_ALREADY;
    }

    conn->last_rx_ts = bcmos_timestamp();
    *conn_id = id;
    if (device != NULL)
        *device = cm_hdr.device;
    if (subch != NULL)
        *subch = cm_hdr.subch;

    return BCM_ERR_OK;
}

/* Receive task handler */
static int _cm_rx_task_handler(long data)
{
    bcmos_task *this_task = bcmos_task_current();
    bcmolt_cm_mode_info *info_ptr = (bcmolt_cm_mode_info *)data;
    bcmos_buf *buf = NULL;
    bcmos_errno err;

    while (!this_task->destroy_request)
    {
        bcmolt_cmll_conn_id ll_conn_id = BCMOLT_CMLL_CONN_ID_UNDEFINED;
        bcmolt_cm_conn_id conn_id = BCMOLT_CM_CONN_ID_UNDEFINED;
        bcmolt_cm_addr addr = {};

        if (buf == NULL)
        {
            buf = bcmos_buf_alloc(cm_init_parms.max_mtu);
            if (buf == NULL)
            {
                bcmos_usleep(1000000);
                continue;
            }
        }

        /* Check for receive. The function waits for a short while and the times out */
        err = cmll_driver.check_recv(info_ptr->ll_handle, &ll_conn_id, buf, &addr, &conn_id);
        if (err != BCM_ERR_OK)
            continue;

        /* Got packet */
        bcmolt_cmll_notify_recv(ll_conn_id, info_ptr, conn_id, buf, &addr);
        buf = NULL;
    }

    return 0;
}

/* ACCEPT task handler */
static int _cm_accept_task_handler(long data)
{
    bcmos_task *this_task = bcmos_task_current();
    bcmolt_cm_mode_info *info_ptr = (bcmolt_cm_mode_info *)data;
    bcmolt_cm_addr addr = {};
    bcmos_errno err;

    while (!this_task->destroy_request)
    {
        bcmolt_cmll_conn_id ll_conn_id = BCMOLT_CMLL_CONN_ID_UNDEFINED;
        err = cmll_driver.check_accept(info_ptr->ll_handle, &ll_conn_id, &addr);
        if (err == BCM_ERR_OK)
        {
            bcmolt_cmll_notify_connect(ll_conn_id, info_ptr, &addr);
        }
    }

    return 0;
}

/* Get free connection block. The function is called under lock */
static bcmos_errno _cm_get_free_conn_block(bcmolt_cm_conn_id *conn_id)
{
    bcmolt_cm_conn_id id;

    if (!cm_conn_array || !conn_id)
        return BCM_ERR_PARM;

    /* Find unused connection id */
    for (id = 0; id < cm_init_parms.max_conns; id++)
    {
        if (!cm_conn_array[id].connected)
            break;
    }
    if (id >= cm_init_parms.max_conns)
    {
        CM_LOG_ERR_RETURN(BCM_ERR_NO_MORE, "Out of free connection blocks\n");
    }
    *conn_id = id;

    return BCM_ERR_OK;
}

/* Validate connect_msg.
   This function also populates cm_conn_pending block when sees connect_msg.response
   Returns:
    BCM_ERR_OK - valid request
    BCM_ERR_ALREADY - response
    BCM_ERR_IO - invalid message
*/
static bcmos_errno _cm_connect_msg_validate(bcmos_buf *buf, bcmolt_conn_type *conn_type)
{
    bcmolt_cm_connect_msg connect_msg;

    if (bcmos_buf_length(buf) < sizeof(bcmolt_cm_connect_msg))
    {
        CM_LOG_ERR_RETURN(BCM_ERR_IO, "Connect message length is invalid.\n");
    }
    memcpy(&connect_msg, bcmos_buf_data(buf), sizeof(connect_msg));
    if (connect_msg.req_resp != BCMOLT_CM_CONN_REQUEST)
    {
        if (connect_msg.req_resp != BCMOLT_CM_CONN_RESPONSE)
        {
            CM_LOG_ERR_RETURN(BCM_ERR_IO, "req_resp %u is invalid. Expected %d or %d\n",
                connect_msg.req_resp, BCMOLT_CM_CONN_REQUEST, BCMOLT_CM_CONN_RESPONSE);
        }
        /* Response. Fill up cm_conn_pending block */
        if (cm_connect_pending.in_progress && cm_connect_pending.corr_tag == connect_msg.corr_tag)
        {
            CM_LOG(INFO, "Got connect response. pending=%d corr_tag=0x%04x/0x%04x\n",
                cm_connect_pending.in_progress, cm_connect_pending.corr_tag, connect_msg.corr_tag);
            cm_connect_pending.status = (bcmos_errno)(unsigned long)BCMOS_ENDIAN_BIG_TO_CPU_U16((uint16_t)connect_msg.status);
            cm_connect_pending.got_reply = BCMOS_TRUE;
        }
        else
        {
            CM_LOG(ERROR, "Got unexpected connect_msg.response. pending=%d corr_tag=0x%04x/0x%04x\n",
                cm_connect_pending.in_progress, cm_connect_pending.corr_tag, connect_msg.corr_tag);
        }
        return BCM_ERR_ALREADY;
    }
    if (connect_msg.type >= (unsigned)BCMOLT_CONN_TYPE__NUM_OF)
    {
        CM_LOG_ERR_RETURN(BCM_ERR_IO, "Connection type %u is invalid\n", connect_msg.type);
    }
    *conn_type = (bcmolt_conn_type)connect_msg.type;
    CM_LOG(INFO, "Got connect request. corr_tag=0x%04x conn_type=%d\n",
        connect_msg.corr_tag, *conn_type);
    return BCM_ERR_OK;
}

/* Reply to connect_msg */
static void _cm_connect_msg_reply(bcmolt_cmll_conn_id ll_conn_id, bcmos_buf *buf, bcmos_errno err,
    bcmolt_ldid device, bcmolt_cm_addr *addr)
{
    bcmolt_cm_connect_msg *connect_msg = (bcmolt_cm_connect_msg *)bcmos_buf_data(buf);
    connect_msg->req_resp = BCMOLT_CM_CONN_RESPONSE;
    connect_msg->status = BCMOS_ENDIAN_CPU_TO_BIG_U16(err);
    _cm_packet_header_push(buf, device, 0);
    cmll_driver.send(ll_conn_id, buf, addr);
}

/* Update connection array. The function is called under lock */
static void _cm_connect_store_enable(bcmolt_cm_conn_id conn_id, bcmolt_conn_type conn_type,
    bcmolt_cmll_conn_id ll_conn_id, bcmolt_ldid device, const bcmolt_cm_addr *addr,
    bcmolt_subchannel subch)
{
    bcmolt_cm_conn *conn = &cm_conn_array[conn_id];
    conn->peer_addr = *addr;
    conn->conn_type = conn_type;
    conn->device = device;
    conn->ll_conn_id = ll_conn_id;
    conn->last_rx_ts = bcmos_timestamp();
    conn->connected = BCMOS_TRUE;
    conn->subch = subch;
    if (cmll_driver.set_conn_id)
        cmll_driver.set_conn_id(ll_conn_id, conn_id);
    CM_LOG(INFO, "created connection %u. type=%d peer:%d.%d.%d.%d:%u dev=%u\n",
        conn_id, conn_type,
        addr->udp.ip.u32 >> 24, (addr->udp.ip.u32 >> 16) & 0xff,
        (addr->udp.ip.u32 >> 8) & 0xff, addr->udp.ip.u32 & 0xff,
        addr->udp.port, device);
}


/* Check existing connection */
static bcmos_bool _cm_conn_exists(bcmolt_cmll_conn_id ll_conn_id, bcmolt_conn_type conn_type,
    const bcmolt_cm_addr *addr, bcmolt_ldid device, bcmolt_subchannel subch)
{
    bcmolt_cm_mode_info *info_ptr=cm_mode_ptrs[conn_type];
    bcmolt_cm_conn_id id;

    if (!cm_conn_array || info_ptr==NULL)
        return BCMOS_FALSE;

    /* Find a matching connection */
    for (id = 0; id < cm_init_parms.max_conns; id++)
    {
        bcmolt_cm_conn *conn = &cm_conn_array[id];
        if (!conn->connected)
            continue;
        if (_check_conn_match(info_ptr, conn, ll_conn_id, addr, device, subch))
            break;
    }
    return (id < cm_init_parms.max_conns) ? BCMOS_TRUE : BCMOS_FALSE;
}


/* Create a new connection */
static bcmos_errno _cm_accept_new_connection(bcmolt_cmll_conn_id ll_conn_id, bcmolt_conn_type conn_type,
    bcmolt_ldid device, bcmolt_cm_addr *addr, bcmolt_subchannel subch, bcmolt_cm_conn_id *conn_id)
{
    bcmos_errno err;

    bcmos_mutex_lock(&cm_conn_lock);

    /* Make sure that connection with the same peer and conn_type doesn't exist yet */
    if (_cm_conn_exists(ll_conn_id, conn_type, addr, device, subch))
    {
        CM_LOG(ERROR, "Connection exists. New connection request ignored\n");
        bcmos_mutex_unlock(&cm_conn_lock);
        return BCM_ERR_ALREADY;
    }

    err = _cm_get_free_conn_block(conn_id);

    /* Notify application. It has right to refuse */
    if (err == BCM_ERR_OK && cm_handlers[conn_type].connect != NULL)
    {
        err = cm_handlers[conn_type].connect(conn_type, *conn_id, device, addr, subch);
        if (err != BCM_ERR_OK)
            CM_LOG(ERROR, "Connection failed: peer refused to connect\n");
    }

    /* Setup connection if everything is good */
    if (err == BCM_ERR_OK)
    {
        _cm_connect_store_enable(*conn_id, conn_type, ll_conn_id, device, addr, subch);
    }
    bcmos_mutex_unlock(&cm_conn_lock);

    return err;
}


/* Handle "connect_msg" packet */
static void _cm_connect_msg_handler(bcmolt_cmll_conn_id ll_conn_id, bcmolt_cm_conn_id conn_id,
    bcmos_buf *buf, bcmolt_ldid device, bcmolt_cm_addr *addr)
{
    bcmolt_conn_type conn_type;
    bcmos_errno err;

    /* Validate connect_msg. Returns BCM_ERR_ALREADY in case of expected response */
    err = _cm_connect_msg_validate(buf, &conn_type);

    /* Stop here if validation failed */
    if (err != BCM_ERR_OK)
    {
        bcmos_buf_free(buf);
        return;
    }

    /* Notify client about the new connection. It has a right to refuse */
    err = _cm_accept_new_connection(ll_conn_id, conn_type, device, addr, 0, &conn_id);
    if (err != BCM_ERR_OK && err != BCM_ERR_ALREADY)
    {
        bcmos_buf_free(buf);
        return;
    }

    /* Reply to connect message. It frees the buffer */
    _cm_connect_msg_reply(ll_conn_id, buf, err, device, addr);
}

/* Get connection info control block ptr by connection type */
static bcmolt_cm_mode_info *_cm_info_ptr_by_conn_types(bcmolt_conn_type_mask conn_types)
{
    bcmolt_cm_mode_info *info_ptr = NULL;
    int conn_type;

    for (conn_type = 0; conn_type < (int)BCMOLT_CONN_TYPE__NUM_OF; conn_type++)
    {
        if ((conn_types & BCMOLT_CONN_TYPE_MASK(conn_type)) != 0)
        {
            if (info_ptr == NULL)
                info_ptr = &cm_mode_info[conn_type];
            cm_mode_ptrs[conn_type] = info_ptr;
        }
    }

    return info_ptr;
}

/* Send "connect_msg" and wait for reply */
static bcmos_errno _cm_connect_msg_send_and_wait(bcmolt_cmll_conn_id ll_conn_id,
    bcmolt_conn_type conn_type, bcmolt_ldid device, const bcmolt_cm_addr *addr)
{
    bcmolt_cm_mode_info *info_ptr = _cm_info_ptr_by_conn_types(BCMOLT_CONN_TYPE_MASK(conn_type));
    bcmos_buf *buf = bcmos_buf_alloc(sizeof(bcmolt_cm_connect_msg));
    bcmolt_cm_connect_msg *connect_msg;
    uint32_t start_ts;
    /* coverity[dont_call] - this doesn't need to be cryptographically secure */
    uint16_t corr_tag = rand();
    bcmos_errno err;

    if (buf == NULL)
        return BCM_ERR_NOMEM;
    connect_msg = (bcmolt_cm_connect_msg *)bcmos_buf_data(buf);
    memset(connect_msg, 0, sizeof(*connect_msg));
    memcpy(connect_msg->magic, BCMOLT_CM_CONN_MAGIC, sizeof(connect_msg->magic));
    connect_msg->req_resp = BCMOLT_CM_CONN_REQUEST;
    connect_msg->type = conn_type;
    connect_msg->status = 0;
    connect_msg->corr_tag = corr_tag;
    bcmos_buf_length_set(buf, sizeof(bcmolt_cm_connect_msg));

    /* Push common packet header */
    _cm_packet_header_push(buf, device, 0);

    cm_connect_pending.corr_tag = corr_tag;
    cm_connect_pending.got_reply = BCMOS_FALSE;
    cm_connect_pending.in_progress = BCMOS_TRUE;
    err = cmll_driver.send(ll_conn_id, buf, addr);
    if (err != BCM_ERR_OK)
    {
        cm_connect_pending.in_progress = BCMOS_FALSE;
        return err;
    }

    /* Now wait for response */
    start_ts = bcmos_timestamp();
    while(!cm_connect_pending.got_reply && (bcmos_timestamp() - start_ts) < BCMOLT_CM_CONNECT_MAX_TIME)
    {
        bcmos_usleep(1000);
        /* Check RX here if there is no task that does it in the background */
        if (!info_ptr->rx_task_created)
        {
            bcmolt_cm_conn_id conn_id;
            bcmolt_subchannel subch;

            buf = NULL;
            /* If there is connect-reply - it is handled internally by bcmolt_cm_recv */
            bcmolt_cm_recv(BCMOLT_CONN_TYPE_MASK(conn_type), &conn_id, &device, &subch, &buf);
            if (buf != NULL)
                bcmos_buf_free(buf);
        }
    }

    if (cm_connect_pending.got_reply)
        err = cm_connect_pending.status;
    else
        err = BCM_ERR_TIMEOUT;
    cm_connect_pending.in_progress = BCMOS_FALSE;

    return err;
}

static void _cmll_notify_disconnect(bcmolt_cm_conn_id conn_id)
{
    bcmolt_cm_conn *conn = &cm_conn_array[conn_id];
    if (conn_id >= cm_init_parms.max_conns || !conn->connected)
        return;
    if (cm_handlers[conn->conn_type].disconnect)
        cm_handlers[conn->conn_type].disconnect(conn->conn_type, conn_id);
    memset(conn, 0, sizeof(*conn));
    CM_LOG(INFO, "connection %u disconnected\n", conn_id);
}

/* Send "disconnect_msg" */
static void _cm_disconnect_msg_send(bcmolt_cmll_conn_id ll_conn_id, bcmolt_ldid device, const bcmolt_cm_addr *addr)
{
    bcmos_buf *buf = bcmos_buf_alloc(sizeof(bcmolt_cm_disconnect_msg));
    bcmolt_cm_disconnect_msg *disconnect_msg;

    if (buf == NULL)
        return;
    disconnect_msg = (bcmolt_cm_disconnect_msg *)bcmos_buf_data(buf);
    memcpy(disconnect_msg->magic, BCMOLT_CM_DISC_MAGIC, sizeof(disconnect_msg->magic));
    bcmos_buf_length_set(buf, sizeof(bcmolt_cm_disconnect_msg));
    _cm_packet_header_push(buf, device, 0);
    cmll_driver.send(ll_conn_id, buf, addr);
}

/*
 * External interfaces
 */

/* Enable specified connection type(s) */
bcmos_errno bcmolt_cm_enable(bcmolt_conn_type_mask conn_types, const bcmolt_cm_enable_parms *enable_parms)
{
    bcmolt_cm_mode_info *info_ptr;
    bcmos_errno err = BCM_ERR_OK;

    if (cm_conn_array == NULL || !cm_init_parms.max_conns)
        return BCM_ERR_STATE;

    if (!conn_types || enable_parms == NULL)
        return BCM_ERR_PARM;

    if ((cm_conn_types & conn_types) != 0)
        return BCM_ERR_ALREADY;

    info_ptr = _cm_info_ptr_by_conn_types(conn_types);
    BUG_ON(info_ptr == NULL);

    cm_conn_types |= conn_types;
    info_ptr->conn_types = conn_types;
    info_ptr->enable_parms = *enable_parms;
    info_ptr->ll_handle = 0;

    do
    {
        /* This can happen at runtime. Make sure dynamic memory allocations are un-blocked so we can create tasks. */
        bcmos_dynamic_memory_allocation_blocking_suspend();

        if (cmll_driver.enable)
        {
            err = cmll_driver.enable(conn_types, &enable_parms->local_addr, info_ptr, &info_ptr->ll_handle);
            if (err != BCM_ERR_OK)
                break;
        }

        /* Create RX task if necessary */
        if ((cmll_driver.flags & CMLL_INIT_FLAG_CREATE_RX_TASK) != 0 &&
            (enable_parms->flags & BCMOLT_CM_FLAG_CREATE_RX_TASK) != 0)
        {
            bcmos_task_parm tp =
            {
                .name = "cm_rx",
                .priority = TASK_PRIORITY_TRANSPORT_RX,
                .handler = _cm_rx_task_handler,
                .data = (long)info_ptr
            };
            err = bcmos_task_create(&info_ptr->rx_task, &tp);
            if (err != BCM_ERR_OK)
                break;
            info_ptr->rx_task_created = BCMOS_TRUE;
        }

        /* Create ACCEPT task if necessary */
        if ((cmll_driver.flags & CMLL_INIT_FLAG_CREATE_ACCEPT_TASK) != 0 &&
            (enable_parms->flags & BCMOLT_CM_FLAG_CREATE_ACCEPT_TASK) != 0)
        {
            bcmos_task_parm tp =
            {
                .name = "cm_accept",
                .priority = TASK_PRIORITY_TRANSPORT_RX,
                .handler = _cm_accept_task_handler,
                .data = (long)info_ptr
            };
            if (!cmll_driver.check_accept)
            {
                CM_LOG(ERROR, "transport driver check_accept must be set.\n");
                err = BCM_ERR_INTERNAL;
                break;
            }
            err = bcmos_task_create(&info_ptr->accept_task, &tp);
            if (err != BCM_ERR_OK)
                break;
            info_ptr->accept_task_created = BCMOS_TRUE;
        }

    } while(0);

    bcmos_dynamic_memory_allocation_blocking_resume();

    if (err != BCM_ERR_OK)
    {
        CM_LOG(ERROR, "Failed to enable channel(s) 0x%x. Error '%s'\n",
            conn_types, bcmos_strerror(err));
        bcmolt_cm_disable(conn_types);
        return err;
    }
    CM_LOG(INFO, "Channels 0x%x enabled.\n", conn_types);

    return BCM_ERR_OK;
}

/* Disable specified connection types */
void bcmolt_cm_disable(bcmolt_conn_type_mask conn_types)
{
    bcmolt_cm_mode_info *info_ptr = NULL;
    int conn_type;

    if ((cm_conn_types & conn_types) == 0)
        return;

    for (conn_type = 0; conn_type < (int)BCMOLT_CONN_TYPE__NUM_OF; conn_type++)
    {
        if ((conn_types & BCMOLT_CONN_TYPE_MASK(conn_type)) != 0)
        {
            info_ptr = cm_mode_ptrs[conn_type];
            cm_mode_ptrs[conn_type] = NULL;
        }
    }
    BUG_ON(info_ptr == NULL);
    BUG_ON(conn_types != info_ptr->conn_types);

    /* Kill RX task if necessary */
    if (info_ptr->rx_task_created)
    {
        bcmos_task_destroy(&info_ptr->rx_task);
        info_ptr->rx_task_created = BCMOS_FALSE;
    }

    /* Kill ACCEPT task if necessary */
    if (info_ptr->accept_task_created)
    {
        bcmos_task_destroy(&info_ptr->accept_task);
        info_ptr->accept_task_created = BCMOS_FALSE;
    }

    if (cmll_driver.disable)
    {
        cmll_driver.disable(info_ptr->ll_handle);
        info_ptr->ll_handle = 0;
    }

    cm_conn_types &= ~conn_types;

    CM_LOG(INFO, "Channels 0x%x disabled.\n", conn_types);
}

/* Initialize inband connection manager */
bcmos_errno bcmolt_cm_init(const bcmolt_cm_init_parms *init_parms)
{
    bcmolt_cm_init_parms init_parms_copy;
    bcmos_errno err;

    if (cm_conn_array != NULL)
        return BCM_ERR_ALREADY;
    if (init_parms == NULL || !init_parms->max_conns)
        return BCM_ERR_PARM;

#ifdef ENABLE_LOG
    if (cm_log_id == DEV_LOG_INVALID_ID)
    {
        cm_log_id = bcm_dev_log_id_register("cm_conn_mgr", DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
    }
#endif

    init_parms_copy = *init_parms;
    if (!init_parms_copy.max_mtu)
        init_parms_copy.max_mtu = BCMTR_MAX_MTU_SIZE + sizeof(bcm_cm_packet_hdr);

    /* Allocate connection array */
    cm_conn_array = bcmos_calloc(sizeof(bcmolt_cm_conn) * init_parms->max_conns);
    if (cm_conn_array == NULL)
        return BCM_ERR_NOMEM;

    err = bcmolt_cmll_init(&init_parms_copy, &cmll_driver);
    if (err != BCM_ERR_OK)
    {
        CM_LOG_ERR_RETURN(err, "transport driver init failed.\n");
    }

    /* check_recv callback is mandatory */
    if (cmll_driver.check_recv == NULL || cmll_driver.send == NULL)
    {
        CM_LOG_ERR_RETURN(BCM_ERR_INTERNAL, "transport driver: check_recv and send callbacks must be set.\n");
    }

    err = bcmos_mutex_create(&cm_conn_lock, 0, "cm_conn");
    if (err != BCM_ERR_OK)
    {
        CM_LOG_ERR_RETURN(err, "Can't create mutex\n");
    }

    cm_init_parms = init_parms_copy;

    CM_LOG(INFO, "Connection Manager initialized\n");

    return BCM_ERR_OK;
}

/*  Cleanup inband connection manager */
void bcmolt_cm_exit(void)
{
    bcmolt_cm_conn_id conn_id;
    int conn_type;

    if (cm_conn_array == NULL)
        return;

    /* Disconnect all */
    for (conn_id = 0; conn_id < cm_init_parms.max_conns; conn_id++)
    {
        if (cm_conn_array[conn_id].connected)
        {
            bcmolt_cm_disconnect(conn_id);
        }
    }

    /* Disable all connection types */
    for (conn_type = 0; conn_type < (int)BCMOLT_CONN_TYPE__NUM_OF; conn_type++)
    {
        if (cm_mode_ptrs[conn_type] != NULL)
        {
            bcmolt_cm_disable(cm_mode_ptrs[conn_type]->conn_types);
        }
    }

    /* Cleanup low-level transport */
    if (cmll_driver.cleanup)
        cmll_driver.cleanup();

    bcmos_mutex_destroy(&cm_conn_lock);

    bcmos_free(cm_conn_array);
    cm_conn_array = NULL;
    memset(&cm_init_parms, 0, sizeof(cm_init_parms));
    memset(&cmll_driver, 0, sizeof(cmll_driver));

    CM_LOG(INFO, "Connection Manager cleaned up\n");
}

/* Set connection handlers */
void bcmolt_cm_handlers_set(bcmolt_conn_type conn_type, const bcmolt_cm_handlers *handlers)
{
    const bcmolt_cm_handlers dummy_handlers = {};
    cm_handlers[conn_type] = handlers ? *handlers : dummy_handlers;
    CM_LOG(INFO, "Connection Manager handlers: connect=%s disconnect=%s recv=%s\n",
        (cm_handlers[conn_type].connect == NULL) ? "cleared" : "set",
        (cm_handlers[conn_type].disconnect == NULL) ? "cleared" : "set",
        (cm_handlers[conn_type].recv == NULL) ? "cleared" : "set");
}

void bcmolt_cm_handlers_get(bcmolt_conn_type conn_type, bcmolt_cm_handlers *handlers)
{
    BUG_ON(handlers == NULL);
    *handlers = cm_handlers[conn_type];
}

/* Connect to remote peer */
bcmos_errno bcmolt_cm_connect(bcmolt_conn_type conn_type, const bcmolt_cm_connect_parms *conn_parms,
    bcmolt_cm_conn_id *conn_id)
{
    bcmolt_cm_mode_info *info_ptr = cm_mode_ptrs[conn_type];
    bcmolt_cm_conn_id id;
    bcmolt_cmll_conn_id ll_conn_id = BCMOLT_CMLL_CONN_ID_UNDEFINED;
    bcmos_errno err;

    if (cm_conn_array==NULL || conn_parms==NULL || conn_id==NULL || info_ptr==NULL)
        return BCM_ERR_PARM;

    CM_LOG(INFO, "Requesting connect: type=%d peer:%d.%d.%d.%d:%u\n",
        conn_type,
        conn_parms->remote_addr.udp.ip.u32 >> 24, (conn_parms->remote_addr.udp.ip.u32 >> 16) & 0xff,
        (conn_parms->remote_addr.udp.ip.u32 >> 8) & 0xff, conn_parms->remote_addr.udp.ip.u32 & 0xff,
        conn_parms->remote_addr.udp.port);

    bcmos_mutex_lock(&cm_conn_lock);

    if (cm_connect_pending.in_progress)
    {
        bcmos_mutex_unlock(&cm_conn_lock);
        CM_LOG_ERR_RETURN(BCM_ERR_IN_PROGRESS, "Busy setting up another connection\n");
    }

    /* Find unused connection id */
    err = _cm_get_free_conn_block(&id);
    if (err != BCM_ERR_OK)
    {
        cm_connect_pending.in_progress = BCMOS_FALSE;
        bcmos_mutex_unlock(&cm_conn_lock);
        return err;
    }

    /* Connect low-level transport */
    if (cmll_driver.connect)
    {
        err = cmll_driver.connect(info_ptr->ll_handle, conn_type, id, &conn_parms->remote_addr, &ll_conn_id);
        if (err != BCM_ERR_OK)
        {
            cm_connect_pending.in_progress = BCMOS_FALSE;
            bcmos_mutex_unlock(&cm_conn_lock);
            CM_LOG_ERR_RETURN(err, "transport connect failed\n");
        }
    }

    /* Send connect request to the peer */
    /* coverity[sleep] - the (potential) sleep while we're holding a mutex is intentional */
    err = _cm_connect_msg_send_and_wait(ll_conn_id, conn_parms->remote_conn_type,
        conn_parms->device, &conn_parms->remote_addr);
    if (err != BCM_ERR_OK)
    {
        /* We are aborting this connection - let the other side know (in case the connect got delayed) */
        _cm_disconnect_msg_send(ll_conn_id, conn_parms->device, &conn_parms->remote_addr);
        cm_connect_pending.in_progress = BCMOS_FALSE;
        bcmos_mutex_unlock(&cm_conn_lock);
        CM_LOG(DEBUG, "transport connect failed: handshake failed. err=%s\n", bcmos_strerror(err));
        return err;
    }

    _cm_connect_store_enable(id, conn_type, ll_conn_id, conn_parms->device, &conn_parms->remote_addr, 0);

    *conn_id = id;
    bcmos_mutex_unlock(&cm_conn_lock);

    return BCM_ERR_OK;
}

/* Set opaque connection cookie */
bcmos_errno bcmolt_cm_cookie_set(bcmolt_cm_conn_id conn_id, bcmolt_cm_cookie cookie)
{
    if (cm_conn_array == NULL || conn_id >= cm_init_parms.max_conns)
        return BCM_ERR_PARM;
    cm_conn_array[conn_id].cookie = cookie;
    CM_LOG(DEBUG, "%s: conn_id=%u cookie=%ld\n", __FUNCTION__, conn_id, cookie);
    return BCM_ERR_OK;
}

/*  Get inband connection cookie */
bcmos_errno bcmolt_cm_cookie_get(bcmolt_cm_conn_id conn_id, bcmolt_cm_cookie *cookie)
{
    CM_LOG(DEBUG, "%s IN: conn_id=%u\n", __FUNCTION__, conn_id);
    *cookie = 0;
    if (cm_conn_array == NULL || conn_id >= cm_init_parms.max_conns)
        return BCM_ERR_PARM;
    if (!cm_conn_array[conn_id].connected)
        return BCM_ERR_NOT_CONNECTED;
    *cookie = cm_conn_array[conn_id].cookie;
    CM_LOG(DEBUG, "%s OUT: conn_id=%u cookie=%ld\n", __FUNCTION__, conn_id, *cookie);
    return BCM_ERR_OK;
}

/*  Get inband connection device */
bcmos_errno bcmolt_cm_device_get(bcmolt_cm_conn_id conn_id, bcmolt_ldid *device)
{
    //CM_LOG(DEBUG, "%s IN: conn_id=%u\n", __FUNCTION__, conn_id);
    if (cm_conn_array == NULL || conn_id >= cm_init_parms.max_conns)
        return BCM_ERR_PARM;
    if (!cm_conn_array[conn_id].connected)
        return BCM_ERR_NOT_CONNECTED;
    *device = cm_conn_array[conn_id].device;
    //CM_LOG(DEBUG, "%s OUT: conn_id=%u device=%u\n", __FUNCTION__, conn_id, *device);
    return BCM_ERR_OK;
}

/* Get client address associated with inband connection */
bcmos_errno bcmolt_cm_addr_get(bcmolt_cm_conn_id conn_id, bcmolt_cm_addr *addr)
{
    CM_LOG(DEBUG, "%s IN: conn_id=%u\n", __FUNCTION__, conn_id);
    if (cm_conn_array == NULL || conn_id >= cm_init_parms.max_conns)
        return BCM_ERR_PARM;
    if (!cm_conn_array[conn_id].connected)
        return BCM_ERR_NOT_CONNECTED;
    *addr = cm_conn_array[conn_id].peer_addr;
    CM_LOG(DEBUG, "%s OUT: conn_id=%u port=%u\n", __FUNCTION__, conn_id, addr->udp.port);
    return BCM_ERR_OK;
}

/* Send packet via inband connection */
bcmos_errno bcmolt_cm_send(bcmolt_cm_conn_id conn_id, bcmolt_subchannel subch, bcmos_buf *buf)
{
    bcmolt_cm_conn *conn = &cm_conn_array[conn_id];
    bcmos_errno err;

    if (cm_conn_array == NULL || conn_id >= cm_init_parms.max_conns)
    {
        bcmos_buf_free(buf);
        return BCM_ERR_PARM;
    }
    if (!conn->connected)
    {
        bcmos_buf_free(buf);
        return BCM_ERR_NOT_CONNECTED;
    }
    /* Add inband packet header */
    _cm_packet_header_push(buf, conn->device, subch);
    /* Send using low-level transport */
    err = cmll_driver.send(conn->ll_conn_id, buf, &conn->peer_addr);

    return err;
}

/* Receive packet via inband connection */
bcmos_errno bcmolt_cm_recv(bcmolt_conn_type_mask conn_types, bcmolt_cm_conn_id *conn_id,
    bcmolt_ldid *device, bcmolt_subchannel *subch, bcmos_buf **buf)
{
    bcmolt_cm_mode_info *info_ptr = NULL;
    bcmolt_cmll_conn_id ll_conn_id = BCMOLT_CMLL_CONN_ID_UNDEFINED;
    bcmolt_cm_addr addr = {};
    int conn_type;
    bcmos_errno err;

    /* Get info_ptr by conn_type */
    for (conn_type = 0; conn_type < (int)BCMOLT_CONN_TYPE__NUM_OF; conn_type++)
    {
        if ((conn_types & BCMOLT_CONN_TYPE_MASK(conn_type)) != 0)
        {
            info_ptr = cm_mode_ptrs[conn_type];
            break;
        }
    }
    if (!info_ptr)
        return BCM_ERR_NOT_CONNECTED;

    /* Check receive */
    *conn_id = BCMOLT_CM_CONN_ID_UNDEFINED;
    *buf = bcmos_buf_alloc(cm_init_parms.max_mtu);
    if (*buf == NULL)
        return BCM_ERR_NOMEM;
    err = cmll_driver.check_recv(info_ptr->ll_handle, &ll_conn_id, *buf, &addr, conn_id);
    /* Validate receive if any */
    err = (err != BCM_ERR_OK) ? err : _cmll_handle_recv(info_ptr, ll_conn_id, *buf, &addr, conn_id, device, subch);
    if (err != BCM_ERR_OK)
    {
        if (err != BCM_ERR_ALREADY)
            bcmos_buf_free(*buf);
        *buf = NULL;
        return err;
    }

    return BCM_ERR_OK;
}

/* Disconnect */
bcmos_errno bcmolt_cm_disconnect(bcmolt_cm_conn_id conn_id)
{
    bcmolt_cm_conn *conn = &cm_conn_array[conn_id];
    bcmolt_cm_conn_id id;
    bcmos_bool shared = BCMOS_FALSE;

    if (cm_conn_array == NULL || conn_id >= cm_init_parms.max_conns)
        return BCM_ERR_PARM;
    if (!conn->connected)
        return BCM_ERR_NOT_CONNECTED;

    CM_LOG(INFO, "Requesting disconnect: conn_id=%d type=%d peer=%d.%d.%d.%d:%u device=%u\n",
        conn_id, conn->conn_type,
        conn->peer_addr.udp.ip.u32 >> 24, (conn->peer_addr.udp.ip.u32 >> 16) & 0xff,
        (conn->peer_addr.udp.ip.u32 >> 8) & 0xff, conn->peer_addr.udp.ip.u32 & 0xff,
        conn->peer_addr.udp.port, conn->device);

    /* Notify application */
    if (cm_handlers[conn->conn_type].disconnect)
        cm_handlers[conn->conn_type].disconnect(conn->conn_type, conn_id);

    /* Notify peer and disconnect at low level if it is the last connection from this address */
    bcmos_mutex_lock(&cm_conn_lock);

    for (id = 0; id < cm_init_parms.max_conns && !shared; id++)
    {
        bcmolt_cm_conn *conn_tmp;
        if (id == conn_id)
            continue;
        conn_tmp = &cm_conn_array[id];
        if (!conn_tmp->connected)
            continue;
        if (!cmll_driver.addr_is_equal(&conn->peer_addr, &conn_tmp->peer_addr))
            continue;
        shared = BCMOS_TRUE;
    }

    if (!shared)
    {
        _cm_disconnect_msg_send(conn->ll_conn_id, conn->device, &conn->peer_addr);

        /* Disconnect at low level */
        if (cmll_driver.disconnect)
            cmll_driver.disconnect(conn->ll_conn_id);
    }

    /* Clear connection structure, including "connected" bool */
    memset(conn, 0, sizeof(*conn));

    bcmos_mutex_unlock(&cm_conn_lock);

    CM_LOG(INFO, "connection %u disconnected\n", conn_id);

    return BCM_ERR_OK;
}

/* connection iterator */
bcmos_errno bcmolt_cm_conn_get_next(bcmolt_conn_type_mask conn_type_mask, bcmolt_cm_conn_id *conn_id,
    uint32_t *last_rx_ts)
{
    int id;

    if (cm_conn_array == NULL || conn_id == NULL)
        return BCM_ERR_PARM;

    id = (*conn_id == BCMOLT_CM_CONN_ID_UNDEFINED) ? 0 : (int)(*conn_id + 1);
    for ( ; id < cm_init_parms.max_conns; id++)
    {
        if (cm_conn_array[id].connected &&
            (conn_type_mask & BCMOLT_CONN_TYPE_MASK(cm_conn_array[id].conn_type)) != 0)
        {
            *conn_id = id;
            if (last_rx_ts)
                *last_rx_ts = cm_conn_array[id].last_rx_ts;
            return BCM_ERR_OK;
        }
    }

    return BCM_ERR_NO_MORE;
}

/*
 * Low-level transport interface functions
 */

/* LL transport notifies that packet has been received.
   If LL transport can't identify connection, it passes BCMOLT_CONN_ID_UNDEFINED.
   In this case, connection manager will look the connection up by peer address
*/
void bcmolt_cmll_notify_recv(bcmolt_cmll_conn_id ll_conn_id, void *drv_data, bcmolt_cm_conn_id conn_id,
    bcmos_buf *buf, bcmolt_cm_addr *peer_addr)
{
    bcmolt_cm_mode_info *info_ptr = (bcmolt_cm_mode_info *)drv_data;
    bcmolt_cm_conn *conn;
    bcmolt_ldid device;
    bcmolt_subchannel subch;
    bcmos_errno err;

    /* Handle the received packet */
    err = _cmll_handle_recv(info_ptr, ll_conn_id, buf, peer_addr, &conn_id, &device, &subch);
    if (err != BCM_ERR_OK)
    {
        if (err != BCM_ERR_ALREADY)
            bcmos_buf_free(buf);
        return;
    }
    BUG_ON(conn_id >= cm_init_parms.max_conns);
    conn = &cm_conn_array[conn_id];
    if (cm_handlers[conn->conn_type].recv == NULL)
    {
        bcmos_buf_free(buf);
        return;
    }
    cm_handlers[conn->conn_type].recv(conn->conn_type, conn_id, device, subch, buf);
}

/* LL transport notifies disconnect */
void bcmolt_cmll_notify_disconnect(bcmolt_cmll_conn_id ll_conn_id, void *drv_data)
{
    int conn_id;
    CM_LOG(INFO, "LL disconnect. ll_conn_id=%lu\n", (unsigned long)ll_conn_id);

    /* Drop all connections that share the same low-level transport connection */
    for (conn_id = 0 ; conn_id < cm_init_parms.max_conns; conn_id++)
    {
        bcmolt_cm_conn *conn = &cm_conn_array[conn_id];
        if (cm_conn_array[conn_id].connected && conn->ll_conn_id == ll_conn_id)
        {
            _cmll_notify_disconnect(conn_id);
        }
    }
}

/* Low-level transport notifies about new connection.
   If this function returns error, the new connection is dropped.
*/
bcmos_errno bcmolt_cmll_notify_connect(bcmolt_cmll_conn_id ll_conn_id, void *drv_data, bcmolt_cm_addr *peer_addr)
{
    bcmolt_cm_mode_info *info_ptr = (bcmolt_cm_mode_info *)drv_data;
    bcmolt_cm_conn_id conn_id;
    bcmos_errno err = BCM_ERR_OK;
    bcmolt_cm_addr addr = {};
    bcmos_buf *buf;
    bcmolt_conn_type conn_type;
    bcm_cm_packet_hdr cm_hdr;

    if (cm_conn_array==NULL || peer_addr==NULL)
        return BCM_ERR_PARM;

    CM_LOG(INFO, "peer: %d.%d.%d.%d:%u\n",
        peer_addr->udp.ip.u32 >> 24, (peer_addr->udp.ip.u32 >> 16) & 0xff,
        (peer_addr->udp.ip.u32 >> 8) & 0xff, peer_addr->udp.ip.u32 & 0xff,
        peer_addr->udp.port);

    bcmos_mutex_lock(&cm_conn_lock);
    err = _cm_get_free_conn_block(&conn_id);
    if (err != BCM_ERR_OK)
    {
        bcmos_mutex_unlock(&cm_conn_lock);
        return err; /* already logged */
    }

    /* Check recv. It should contain setup packet */
    buf = bcmos_buf_alloc(cm_init_parms.max_mtu);
    if (buf == NULL)
    {
        bcmos_mutex_unlock(&cm_conn_lock);
        return BCM_ERR_NOMEM;
    }
    err = cmll_driver.check_recv(info_ptr->ll_handle, &ll_conn_id, buf, &addr, NULL);
    if (err != BCM_ERR_OK || bcmos_buf_length(buf) < sizeof(bcm_cm_packet_hdr) + sizeof(bcmolt_cm_connect_msg))
    {
        bcmos_mutex_unlock(&cm_conn_lock);
        bcmos_buf_free(buf);
        CM_LOG_ERR_RETURN(err, "connection failed: no setup packet\n");
    }

    /* Pull inband packet header */
    _cm_packet_header_pull(buf, &cm_hdr);

    /* Make sure that the received message is "connect" */
    if (memcmp(bcmos_buf_data(buf), BCMOLT_CM_CONN_MAGIC, 8))
    {
        /* Unexpected packet */
        bcmos_mutex_unlock(&cm_conn_lock);
        bcmos_buf_free(buf);
        CM_LOG_ERR_RETURN(BCM_ERR_IO, "connection failed: expected setup packet, got something else\n");
    }
    err = _cm_connect_msg_validate(buf, &conn_type);
    if (err != BCM_ERR_OK)
    {
        bcmos_mutex_unlock(&cm_conn_lock);
        bcmos_buf_free(buf);
        CM_LOG_ERR_RETURN(err, "connection failed: setup packet validation failed\n");
    }

    /* Notify application. It has right to refuse */
    if (cm_handlers[conn_type].connect)
    {
        err = cm_handlers[conn_type].connect(conn_type, conn_id, cm_hdr.device, &addr, 0);
        if (err != BCM_ERR_OK)
            CM_LOG(ERROR, "connection failed: application refused to connect\n");
    }

    /* Reply to connect message. It frees the buffer */
    _cm_connect_msg_reply(ll_conn_id, buf, err, cm_hdr.device, &addr);

    if (err == BCM_ERR_OK)
    {
        _cm_connect_store_enable(conn_id, conn_type, ll_conn_id, cm_hdr.device, &addr, 0);
    }
    bcmos_mutex_unlock(&cm_conn_lock);

    return err;
}
