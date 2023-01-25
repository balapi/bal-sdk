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
#include <bcmtr_plugin.h>
#include <bcm_config.h>
#include <bcmtr_plugin_conn_mgr.h>

/** Send data. */
static bcmos_errno bcmtr_cm_send(
    bcmtr_plugin_channel ch,
    bcmolt_devid device,
    bcmolt_subchannel subch,
    bcmos_buf *buf,
    bcmtr_send_flags flags)
{
    bcmolt_cm_conn_id conn_id = (bcmolt_cm_conn_id)ch;
    if ((subch & BCMTR_SUBCH_AUX) != 0)
    {
        conn_id = (bcmolt_cm_conn_id)(subch & ~BCMTR_SUBCH_AUX);
        subch = 0;
    }
    else
    {
        conn_id &= 0xffff;
    }
    return bcmolt_cm_send(conn_id, subch, buf);
}

/* Packet receive indication */
static void _bcmtr_recv_ind(bcmolt_conn_type conn_type, bcmolt_cm_conn_id conn_id,
    bcmolt_ldid device, bcmolt_subchannel subch, bcmos_buf *buf)
{
    /* For application connection ignore subch in the header (always 0) and derive it from conn_id */
    if (conn_type == BCMOLT_CONN_TYPE_APP)
    {
        subch = conn_id | BCMTR_SUBCH_AUX;
    }
#ifdef BCM_SUBSYSTEM_EMBEDDED
    bcmtr_packet_receive(EMBEDDED_DEVICE_ID, subch, buf);
#else
    bcmtr_packet_receive(device, subch, buf);
#endif
}

/** Close communication channel */
static bcmos_errno bcmtr_cm_close(bcmtr_plugin_channel ch)
{
    bcmolt_conn_type_mask conn_type_mask = (bcmolt_conn_type_mask)(ch >> 16);

    if ((conn_type_mask & BCMOLT_CONN_TYPE_MASK_MUX) != 0)
    {
        /* For the main (MUX) connction clear recv, but preserve connect, disconnect handlers.
           It is the responsibility of device management to handle connect/disconnect */
        bcmolt_cm_handlers handlers;
        bcmolt_cm_handlers_get(BCMOLT_CONN_TYPE_MUX, &handlers);
        handlers.recv = NULL;
        bcmolt_cm_handlers_set(BCMOLT_CONN_TYPE_MUX, &handlers);
    }
    if ((conn_type_mask & BCMOLT_CONN_TYPE_MASK_APP) != 0)
    {
        /* Application connections are managed by the transport layer */
        bcmolt_cm_handlers_set(BCMOLT_CONN_TYPE_APP, NULL);
    }

    bcmolt_cm_disconnect((bcmolt_cm_conn_id)(ch & 0xffff));
#ifdef BCM_SUBSYSTEM_EMBEDDED
    /* Disable all connection types besides MUX while disconnected. */
    conn_type_mask &= ~BCMOLT_CONN_TYPE_MASK_MUX;
    bcmolt_cm_disable(conn_type_mask);
#endif

    return BCM_ERR_OK;
}

/** Open communication channel */
static bcmos_errno bcmtr_cm_open(bcmolt_devid device, bcmtr_plugin_cfg *cfg, bcmtr_plugin_channel *ch)
{
    bcmolt_cm_handlers handlers;

    *ch = (bcmtr_plugin_channel)(cfg->mode << 16);

#if defined(BCM_SUBSYSTEM_HOST) || defined(BCM_SUBSYSTEM_OPENCPU)
    {
        /* Create connection in connection manager */
        bcmos_errno err;
        bcmolt_conn_type conn_type = ((cfg->mode & BCMOLT_CONN_TYPE_MASK_MUX) != 0) ?
            BCMOLT_CONN_TYPE_MUX : BCMOLT_CONN_TYPE_APP;
        bcmolt_cm_connect_parms conn_parms = {
            .device = cfg->ldid,
            .remote_addr = cfg->x.cm,
            .remote_conn_type = conn_type
        };
        bcmolt_cm_conn_id conn_id;

        err = bcmolt_cm_connect(conn_type, &conn_parms, &conn_id);
        if (err != BCM_ERR_OK)
            return err;
        *ch |= conn_id;
    }
#endif

    if ((cfg->mode & BCMOLT_CONN_TYPE_MASK_MUX) != 0)
    {
        bcmolt_cm_handlers_get(BCMOLT_CONN_TYPE_MUX, &handlers);
        handlers.recv = _bcmtr_recv_ind;
        /* Note that connect, disconnect handlers are preserved.
           It is the responsibility of device management to handle
           connect/disconnect
        */
        bcmolt_cm_handlers_set(BCMOLT_CONN_TYPE_MUX, &handlers);
    }
    if ((cfg->mode & BCMOLT_CONN_TYPE_MASK_APP) != 0)
    {
        bcmolt_cm_handlers_get(BCMOLT_CONN_TYPE_MUX, &handlers);
        handlers.recv = _bcmtr_recv_ind;
#ifdef BCM_SUBSYSTEM_EMBEDDED
        /* Direct application connections are handled by the transport layer */
        handlers.connect = bcmtr_client_connected,
        handlers.disconnect = bcmtr_client_disconnected,
#endif
        bcmolt_cm_handlers_set(BCMOLT_CONN_TYPE_APP, &handlers);
    }

    return BCM_ERR_OK;
}

/** Initialize plugin callbacks
 * \param[in,out]       driver Transport plugin driver structure
 * \return error code
 */
bcmos_errno bcmtr_plugin_cm_init(bcmtr_plugin_cfg *cfg, bcmtr_driver *driver)
{
    driver->open = bcmtr_cm_open;
    driver->close = bcmtr_cm_close;
    driver->send = bcmtr_cm_send;

    return BCM_ERR_OK;
}
