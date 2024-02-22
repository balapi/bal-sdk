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
 * Host-specific transport functions
 */
static bcmos_task bcmtr_timeout_task;
static bcmos_task bcmtr_ind_task;

/* Create indication task */
static bcmos_errno _bcmtr_ind_task_create(void)
{
    bcmos_task_parm tp =
    {
        .name = "tr_ind",
        .priority = TASK_PRIORITY_TRANSPORT_IND
    };
    bcmos_module_parm mp = {};
    bcmos_errno err;

    err = bcmos_task_create(&bcmtr_ind_task, &tp);
    if (err == BCM_ERR_OK)
    {
        err = bcmos_module_create(BCMOS_MODULE_ID_TRANSPORT_IND, &bcmtr_ind_task, &mp);
        if (err != BCM_ERR_OK)
            bcmos_task_destroy(&bcmtr_ind_task);
    }
    return err;
}

/* Check for time-outs. returns number of messages timed out */
static int _bcmtr_check_timeout(bcmtr_conn *conn)
{
    bcmtr_msg *tmsg, *tmp;
    uint32_t now;
    int nmsg = 0;

    /* Transport lock */
    bcmos_mutex_lock(&conn->mutex);

    now = bcmos_timestamp();
    TAILQ_FOREACH_SAFE(tmsg, &conn->msg_list, l, tmp)
    {
        bcmolt_msg *msg = tmsg->msg;

        if (now - tmsg->timestamp <= conn->cfg.msg_timeout)
            continue;

        /* Giving up */
        if (msg || tmsg->hdr.keep_alive)
        {
            if (tmsg->err == BCM_ERR_IN_PROGRESS)
            {
                tmsg->err = BCM_ERR_TIMEOUT;
            }
            if (!tmsg->hdr.keep_alive)
            {
                BCMTR_CLD_CHECK_NOTIFY(
                    conn->device,
                    &tmsg->hdr,
                    BCMTR_CLD_EV_TIMEOUT,
                    bcmos_timestamp(),
                    NULL,
                    0,
                    msg,
                    msg->type);
            }
            TAILQ_REMOVE(&conn->msg_list, tmsg, l);
            _bcmtr_notify_ready(conn, tmsg);
            ++conn->stat.msg_req_timeout;
        }
        else
        {
            _bcmtr_tmsg_free(tmsg, &conn->msg_list);
            ++conn->stat.msg_reass_timeout;
        }
        ++nmsg;
    }

    conn->last_timeout_check = bcmos_timestamp();

    /* Release transport lock */
    bcmos_mutex_unlock(&conn->mutex);

    return nmsg;
}

/* Timeout task handler */
static int _bcmtr_timeout_task_handler(long arg)
{
    bcmos_task *my_task = bcmos_task_current();
    bcmtr_conn *conn;
    int dev;

    while(!my_task->destroy_request)
    {
        for (dev=0; dev<BCMTR_MAX_DEVICES; dev++)
        {
            conn = conn_info[dev].conn;
            if (conn != NULL && conn->connected)
            {
                /* Check for timeouts if any */
                if (bcmos_timestamp() - conn->last_timeout_check > conn->timeout_check_period)
                {
                    /* Check requests waiting for acknowledge and multi-part messages for timeout.
                    * Timed-out requests are retransmitted.
                    */
                    _bcmtr_check_timeout(conn);
                }
            }
        }
        bcmos_usleep(10000);
    }
    my_task->destroyed = BCMOS_TRUE;

    return 0;
}

/* Create timeout task */
static bcmos_errno _bcmtr_timeout_task_create(void)
{
    bcmos_errno err;
    bcmos_task_parm parm = {
        .priority = TASK_PRIORITY_TRANSPORT_TIMEOUT,
        .stack_size = BCMTR_TIMEOUT_THREAD_STACK,
        .handler = _bcmtr_timeout_task_handler,
        .name = "tr_timeout",
    };
    err = bcmos_task_create(&bcmtr_timeout_task, &parm);

    return err;
}

/* Transport IPC: unpacked message release callback */
static void _bcmtr_ipc_unpacked_msg_release(bcmos_msg *m)
{
    bcmolt_msg *msg = container_of(m, bcmolt_msg, os_msg);
    bcmolt_msg_free(msg);
}

/* Transport IPC: unpacked message handler.
 * Called in context of the target module as part of dispatching message to the user task.
 */
static void _bcmtr_ipc_unpacked_msg_handler(bcmos_module_id module_id, bcmos_msg *m)
{
    bcmolt_msg *msg = container_of(m, bcmolt_msg, os_msg);
    bcmtr_handler *h = (bcmtr_handler *)m->user_data;
    h->app_cb(h->olt, msg);
}

/* Deliver indication to subscribers. Indication is delivered as if received from the line.*/
bcmos_errno bcmtr_msg_dispatch(bcmolt_devid device, bcmolt_msg *msg)
{
    bcmtr_conn_info *info = &conn_info[device];
    bcmtr_handler_list *handlers_list;
    bcmtr_handler *h, *h_tmp;
    bcmolt_api_group_id msg_id;
    bcmos_module_id module;
    bcmolt_msg *clone;
    bcmos_errno err = BCM_ERR_OK;

    if (bcmolt_api_group_id_combine(msg->obj_type, msg->group, msg->subgroup, &msg_id) != BCM_ERR_OK)
    {
        BCMTR_LOG(device, ERROR, "Unexpected msg: obj=%d group=%d subgroup=%u\n",
            msg->obj_type, msg->group, msg->subgroup);
        return BCM_ERR_PARM;
    }

    handlers_list = &info->msg_handler_list[msg_id][0];
    STAILQ_FOREACH_SAFE(h, handlers_list, l, h_tmp)
    {
        if (!h->app_cb)
            continue;
        module = (h->module != BCMOS_MODULE_ID_NONE) ? h->module : BCMOS_MODULE_ID_TRANSPORT_IND;

        /* Clone message for every delivery because recepient is going to release it */
        clone = NULL;
        err = bcmolt_msg_clone(&clone, msg);
        if (err != BCM_ERR_OK)
        {
            BCMTR_LOG(device, ERROR, "Couldn't clone msg: obj=%d group=%d subgroup=%u. Error %s\n",
                msg->obj_type, msg->group, msg->subgroup, bcmos_strerror(err));
            break;
        }
        clone->os_msg.user_data = h;
        clone->os_msg.type = BCMOS_MSG_ID_INTERNAL_IPC;
        clone->os_msg.release = _bcmtr_ipc_unpacked_msg_release;
        clone->os_msg.handler = _bcmtr_ipc_unpacked_msg_handler;
        clone->device = device;
        bcmos_msg_send_to_module(module, &clone->os_msg, BCMOS_MSG_SEND_AUTO_FREE);
    }

    return err;
}

/* Send keep alive message to the managemnt daemon and wait for response */
bcmos_errno bcmtr_keep_alive(bcmolt_devid device, uint16_t *conn_id)
{
    bcmtr_conn *conn;
    bcmtr_msg *tmsg = NULL;
    bcmos_buf *buf = NULL;
    bcmos_errno err;

    err = _bcmtr_conn_get(device, &conn);
    if (err != BCM_ERR_OK)
        return err;

    bcmos_mutex_lock(&conn->mutex);

    tmsg = _bcmtr_tmsg_alloc(&conn->free_req_list);
    if (tmsg == NULL)
    {
        ++conn->stat.msg_no_mem;
        bcmos_mutex_unlock(&conn->mutex);
        return BCM_ERR_TOO_MANY_REQS;
    }

    tmsg->err = BCM_ERR_IN_PROGRESS;
    tmsg->timestamp = bcmos_timestamp();
    buf = bcmos_buf_alloc(BCMTR_HDR_SIZE);
    if (buf == NULL)
    {
        ++conn->stat.msg_no_mem;
        _bcmtr_tmsg_free(tmsg, NULL);
        bcmos_mutex_unlock(&conn->mutex);
        return BCM_ERR_NOMEM;
    }

    /* Build keel-alive transport header */
    tmsg->hdr.keep_alive = 1;
    tmsg->hdr.device = conn->ldid;
    tmsg->hdr.dir = BCMOLT_MSG_DIR_REQUEST;
    tmsg->hdr.corr_tag = ++corr_tag;
    /* Pack header into transmit buffer */
    bcmtr_header_pack(&tmsg->hdr, bcmos_buf_tail_push(buf, BCMTR_HDR_SIZE));
    /* Send and wait for reply or timeout */
    err = _bcmtr_send_to_line(conn, 0, buf, BCMTR_SEND_FLAGS_CALL);

    if (err == BCM_ERR_OK)
    {
        /* Insert to the list of pending messages */
        TAILQ_INSERT_TAIL(&conn->msg_list, tmsg, l);
        bcmos_mutex_unlock(&conn->mutex);

        /* Wait for response or timeout.
        * Message timeout is enforced by audit rather than semaphore timeout option
        */
        bcmos_sem_wait(&tmsg->sem, BCMOS_WAIT_FOREVER);

        err = tmsg->err;
        if (tmsg->err == BCM_ERR_OK)
            *conn_id = tmsg->hdr.conn_id;

        /* Retake the lock in order to safely release tmsg block */
        bcmos_mutex_lock(&conn->mutex);
    }

    /* Release transport message block */
    /* coverity[use] - Coverity is confused by the mutexes here, but it's OK */
    _bcmtr_tmsg_free(tmsg, NULL);
    bcmos_mutex_unlock(&conn->mutex);

    return err;
}

/* Send registration mask update to trmux & embedded system */
static bcmos_errno _bcmtr_auto_reg_update_send(bcmolt_devid device, bcmolt_obj_id obj)
{
    bcmtr_conn *conn;
    bcmtr_reg_unreg_msg msg;
    bcmos_buf *buf;
    bcmos_errno err;

    /* On the host, we need a connection in order to send message.
        If connection can't be established at this time, ignore it.
        api connection manager will re-instate registrations when connection is restored
    */
    err = _bcmtr_conn_get(device, &conn);
    if (err != BCM_ERR_OK)
        return err;

    /* Send registration info to the mux driver. It is just a header */
    memset(&msg, 0, sizeof(msg));
    msg.hdr.device = conn->ldid;
    msg.hdr.obj = obj;
    msg.hdr.auto_reg_unreg = 1;
    msg.auto_mask = conn_info[device].auto_masks[obj];

    /* Pack message */
    buf = bcmos_buf_alloc(BCMTR_REG_UNREG_MSG_SIZE);
    if (buf == NULL)
        return BCM_ERR_NOMEM;
    bcmtr_reg_unreg_msg_pack(&msg, bcmos_buf_tail_push(buf, BCMTR_REG_UNREG_MSG_SIZE));

    err = _bcmtr_send_to_line(conn, 0, buf, BCMTR_SEND_FLAGS_PRI_NORMAL);

    return err;
}

/* Propagate subscribtions for autonomous indication to device management daemon */
bcmos_errno bcmtr_msg_handler_register_install(bcmolt_devid device)
{
    bcmtr_conn *conn;
    bcmos_errno err = BCM_ERR_OK;
    bcmolt_obj_id obj;

    err = _bcmtr_conn_get(device, &conn);
    if (err != BCM_ERR_OK)
        return err;

    /* Send message to trmux or MAC device for each object for which there are subscription(s) */
    BCMOLT_API_FOR_EACH_OBJ_ID(obj)
    {
        if (conn_info[device].auto_masks[obj])
        {
            err = _bcmtr_auto_reg_update_send(device, obj);
            if (err)
                break;
        }
    }

    return err;
}

/* Handle autonomous message registration update. This message is unexpected on the host side */
static void _bcmtr_handle_auto_reg_unreg(bcmtr_conn *conn, bcmolt_subchannel subch, bcmos_buf *buf)
{
    BCMTR_LOG(conn->device, ERROR, "Unexpected auto reg_unreg msg\n");
    bcmos_buf_free(buf);
}

/* Handle keep-alive message. This message is unexpected on the host side */
static void _bcmtr_handle_keep_alive(bcmtr_conn *conn, bcmolt_subchannel subch, bcmos_buf *buf)
{
    BCMTR_LOG(conn->device, ERROR, "Unexpected keep_alive msg\n");
    bcmos_buf_free(buf);
}

/* Send indication. Just post it to TRMUX. It will do the rest */
static bcmos_errno _bcmtr_send_auto(bcmtr_conn *conn, bcmtr_msg *tmsg, bcmos_buf *buf, bcmtr_send_flags flags)
{
    return _bcmtr_fragment_if_needed_and_send(conn, 0, tmsg, buf, flags);
}
