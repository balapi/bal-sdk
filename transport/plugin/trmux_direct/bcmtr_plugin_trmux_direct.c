/*
<:copyright-BRCM:2018-2020:proprietary:standard

 Copyright (c) 2018-2020 Broadcom. All Rights Reserved

 This program is the proprietary software of Broadcom and/or its
 licensors, and may only be used, duplicated, modified or distributed pursuant
 to the terms and conditions of a separate, written license agreement executed
 between you and Broadcom (an "Authorized License").  Except as set forth in
 an Authorized License, Broadcom grants no license (express or implied), right
 to use, or waiver of any kind with respect to the Software, and Broadcom
 expressly reserves all rights in and to the Software and all intellectual
 property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE
 NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY
 BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.

 Except as expressly set forth in the Authorized License,

 1. This program, including its structure, sequence and organization,
    constitutes the valuable trade secrets of Broadcom, and you shall use
    all reasonable efforts to protect the confidentiality thereof, and to
    use this information only in connection with your use of Broadcom
    integrated circuit products.

 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
    RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND
    ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT,
    FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
    COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE
    TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR
    PERFORMANCE OF THE SOFTWARE.

 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR
    ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
    INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY
    WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
    IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES;
    OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE
    SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS
    SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY
    LIMITED REMEDY.
:>
*/
/*
 * bcmtr_plugin_direct.c
 *
 * This plugin
 * - TX: forwards messages to trmux
 * - RX: waits on rx task's message queue
 */

#include <bcmos_system.h>

#include <bcmtr_plugin_trmux_direct.h>

typedef struct
{
    bcmolt_devid device;
    bcmos_task task;
    bcmtr_plugin_recv_info info;
    bcmos_mutex lock;
    bcmos_buf_queue queue;
    bcmos_sem sem;
    bcmos_bool active;
} bcmtr_direct_rx_data;
static bcmtr_direct_rx_data direct_rx_data[BCM_MAX_DEVS_PER_LINE_CARD];

/* Receive from trmux. Called in trmux context */
void bcmtr_direct_rx_from_trmux(bcmolt_devid device, bcmos_buf *buf, bcmtrmux_channel subch, void *data)
{
    bcmtr_direct_rx_data *rx_data = &direct_rx_data[device];
    bcmolt_subchannel tr_subch = subch;
    /* Put the buffer onto the rx queue and signal that message is available */
    memcpy(bcmos_buf_head_push(buf, sizeof(bcmolt_subchannel)), &tr_subch, sizeof(bcmolt_subchannel));
    bcmos_mutex_lock(&rx_data->lock);
    bcmos_buf_queue_put(&rx_data->queue, buf);
    bcmos_mutex_unlock(&rx_data->lock);
    bcmos_sem_post(&rx_data->sem);
}

/** Receive data. This function is called in context of the transport layer's RX task */
static bcmos_errno bcmtr_plugin_trmux_recv(bcmtr_plugin_channel ch, bcmolt_devid *device, bcmolt_subchannel *subch, bcmos_buf **pbuf)
{
    bcmtr_direct_rx_data *rx_data = (bcmtr_direct_rx_data *)ch;
    bcmos_buf *buf;
    bcmos_errno err;

    err = bcmos_sem_wait(&rx_data->sem, BCMTR_MSG_TIMEOUT * 1000);
    if (err)
        return err;
    bcmos_mutex_lock(&rx_data->lock);
    buf = bcmos_buf_queue_get(&rx_data->queue);
    bcmos_mutex_unlock(&rx_data->lock);
    if (buf == NULL)
        return BCM_ERR_COMM_FAIL;
    memcpy(subch, bcmos_buf_head_pull(buf, sizeof(bcmolt_subchannel)), sizeof(bcmolt_subchannel));
    *device = rx_data->device;
    *pbuf = buf;
    return BCM_ERR_OK;
}

/** Send data */
static bcmos_errno bcmtr_plugin_trmux_send(bcmtr_plugin_channel ch, bcmolt_devid device,
    bcmolt_subchannel subch, bcmos_buf *buf, bcmtr_send_flags flags)
{
    bcmtr_hdr hdr;
    bcmos_errno err = BCM_ERR_OK;

    /* Request:
     * CFG      --> device
     * OPER     --> device
     * AUTO     --> host
     * AUTO_CFG --> device
     * STAT     --> device
     * STAT_CFG --> device
     *
     * Response --> host
     */
    bcmtr_header_unpack(bcmos_buf_data(buf), &hdr);
    if (hdr.auto_reg_unreg)
    {
        bcmtrmux_rx_from_host(device, BCMTRMUX_CHANNEL_LOCAL_TRANSPORT, buf);
    }
    else
    {
        if (hdr.dir == BCMOLT_MSG_DIR_RESPONSE)
        {
            err = bcmtrmux_send_to_host(device, subch, buf);
        }
        else
        {
            const bcmolt_group_descr *group_descr;
            err = bcmolt_api_group_descr_get_by_group_id(hdr.obj, hdr.group_id, &group_descr);
            BCMOS_RETURN_IF_ERROR(err);
            if (group_descr->mgt_group == BCMOLT_MGT_GROUP_AUTO)
            {
                err = bcmtrmux_send_to_host(device, subch, buf);
            }
            else
            {
                err = bcmtrmux_send_to_device(device, BCMTRMUX_CHANNEL_LOCAL_TRANSPORT, buf);
            }
        }
    }
    return (err == BCM_ERR_NOT_CONNECTED) ? BCM_ERR_OK : err;
}

/** Close communication channel */
static bcmos_errno bcmtr_plugin_trmux_close(bcmtr_plugin_channel ch)
{
    bcmolt_devid device = (bcmolt_devid)ch;
    bcmtr_direct_rx_data *rx_data = &direct_rx_data[device];
    bcmos_buf *buf;

    /* Direct plugin supports only 1 application instance */
    if (device >= BCM_MAX_DEVS_PER_LINE_CARD)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Device %u is out of range\n", device);

    if (!rx_data->active)
        return BCM_ERR_ALREADY;

    bcmtrmux_channel_unregister(device, BCMTRMUX_CHANNEL_LOCAL_TRANSPORT);

    bcmos_task_destroy(&rx_data->task);
    bcmos_sem_destroy(&rx_data->sem);
    /* Drain rx queue */
    bcmos_mutex_lock(&rx_data->lock);
    while ((buf = bcmos_buf_queue_get(&rx_data->queue)) != NULL)
        bcmos_buf_free(buf);
    bcmos_mutex_unlock(&rx_data->lock);
    bcmos_mutex_destroy(&rx_data->lock);
    rx_data->active = BCMOS_FALSE;

    return BCM_ERR_OK;
}

/** Open communication channel */
static bcmos_errno bcmtr_plugin_trmux_open(bcmolt_devid device, bcmtr_plugin_cfg *cfg, bcmtr_plugin_channel *ch)
{
    bcmos_errno err;
    bcmtrmux_channel local_subch;
    bcmtr_direct_rx_data *rx_data = &direct_rx_data[device];
    char task_name[20] = {};

    if (device >= BCM_MAX_DEVS_PER_LINE_CARD)
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Device %u is out of range\n", device);

    if (rx_data->active)
        return BCM_ERR_ALREADY;

    bcmos_buf_queue_init(&rx_data->queue);
    err = bcmos_mutex_create(&rx_data->lock, 0, "rx_direct_queue");
    if (err != BCM_ERR_OK)
        goto err0;

    err = bcmos_sem_create(&rx_data->sem, 0, 0, "rx_direct_queue");
    if (err != BCM_ERR_OK)
        goto err1;

    /* Create transport RX task */
    rx_data->info.ch = (bcmtr_plugin_channel)rx_data;
    rx_data->info.recv = bcmtr_plugin_trmux_recv;
    snprintf(task_name, sizeof(task_name)-1, "tr_rx_direct_%u", device);
    err = bcmtr_rx_task_create(&rx_data->task, task_name, &rx_data->info);
    if (err != BCM_ERR_OK)
        goto err2;

    rx_data->device = device;
    /* Register trmux channel for local objects */
    local_subch = BCMTRMUX_CHANNEL_LOCAL_TRANSPORT;
    err = bcmtrmux_channel_register(device, &local_subch, bcmtr_direct_rx_from_trmux, NULL);
    if (err != BCM_ERR_OK)
        goto err3;

    rx_data->active = BCMOS_TRUE;
    *ch = (bcmtr_plugin_channel)device;

    return BCM_ERR_OK;

err3:
    bcmos_task_destroy(&rx_data->task);
err2:
    bcmos_sem_destroy(&rx_data->sem);
err1:
    bcmos_mutex_destroy(&rx_data->lock);
err0:
    return err;
}

/** Initialize plugin callbacks
 * \param[in,out]       driver Transport plugin driver structure
 * \return error code
 */
bcmos_errno bcmtr_plugin_trmux_init(bcmtr_plugin_cfg *cfg, bcmtr_driver *driver)
{
    driver->open = bcmtr_plugin_trmux_open;
    driver->close = bcmtr_plugin_trmux_close;
    driver->send = bcmtr_plugin_trmux_send;
    return BCM_ERR_OK;
}
