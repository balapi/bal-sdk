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

/* bcmolt_conn_mgr_internal.h - Inband connection manager */

#ifndef BCMOLT_CONN_MGR_INTERNAL_H_
#define BCMOLT_CONN_MGR_INTERNAL_H_

#include <bcmolt_conn_mgr.h>
#include <bcm_dev_log.h>

extern dev_log_id cm_log_id;

#ifdef ENABLE_LOG
#define CM_LOG(level, fmt, ...) BCM_LOG(level, cm_log_id, fmt, ## __VA_ARGS__)
#define CM_LOG_ERR_RETURN(err, fmt, ...) \
    do \
    { \
        CM_LOG(ERROR, "%s: " fmt, bcmos_strerror(err), ## __VA_ARGS__); \
        return err; \
    } while (0)
#else
#define CM_LOG(level, fmt, ...) \
    do \
    { \
    } while (0)
#define CM_LOG_ERR_RETURN(err, fmt, ...) \
    do \
    { \
        return err; \
    } while (0)
#endif

/* IB connect message */
typedef struct __PACKED_ATTR_START__ bcmolt_cm_connect_msg
{
    uint8_t magic[8];   /* Message singature: @CM_CON@ */
#define BCMOLT_CM_CONN_MAGIC "@CM_CON@"
    uint8_t req_resp;   /* 0=request, 1=response */
#define BCMOLT_CM_CONN_REQUEST  0
#define BCMOLT_CM_CONN_RESPONSE 1
    uint8_t type;       /* 0=managed, 1=unmanaged, 2=fast */
    uint16_t corr_tag;  /* correlation tag (big endian) */
    int16_t status;     /* response: bcmos_errno (big endian) */
} __PACKED_ATTR_END__ bcmolt_cm_connect_msg;

/* Max time for connect_msg.request - connect_msg.response exchange */
#define BCMOLT_CM_CONNECT_MAX_TIME  (1000 * 1000)

/* IB disconnect message */
typedef struct __PACKED_ATTR_START__ bcmolt_cm_disconnect_msg
{
    uint8_t magic[8];   /* Message singature: @CM_DSC@ */
#define BCMOLT_CM_DISC_MAGIC "@CM_DSC@"
} __PACKED_ATTR_END__ bcmolt_cm_disconnect_msg;

/* Transport (network) connection handle */
typedef long bcmolt_cmll_conn_id;
#define BCMOLT_CMLL_CONN_ID_UNDEFINED     (-1)

/* Init flags */
typedef enum
{
    CMLL_INIT_FLAG_NONE               = 0,
    CMLL_INIT_FLAG_CREATE_RX_TASK     = 0x01,
    CMLL_INIT_FLAG_CREATE_ACCEPT_TASK = 0x02,
} bcmolt_cmll_init_flag;

/* Low-level driver */
typedef struct bcmolt_cmll_driver
{
    bcmolt_cmll_init_flag flags;
    /* Enable connection types */
    bcmos_errno (*enable)(bcmolt_conn_type_mask conn_type_mask, const bcmolt_cm_addr *local_addr,
        void *drv_data, long *ll_handle);
    /* Disable connection types */
    void (*disable)(long ll_handle);
    /* Check for new connection. Called from accept task if CMLL_INIT_FLAG_CREATE_ACCEPT_TASK flag is set */
    bcmos_errno (*check_accept)(long ll_handle, bcmolt_cmll_conn_id *ll_conn_id, bcmolt_cm_addr *addr);
    /* Check for new RX packet. Called from receive task if CMLL_INIT_FLAG_CREATE_RX_TASK flag is set */
    bcmos_errno (*check_recv)(long ll_handle, bcmolt_cmll_conn_id *ll_conn_id, bcmos_buf *buf,
        bcmolt_cm_addr *addr, bcmolt_cm_conn_id *conn_id);
    /* Send to peer */
    bcmos_errno (*send)(bcmolt_cmll_conn_id ll_conn_id, bcmos_buf *buf, const bcmolt_cm_addr *addr);
    /* Set low-level connection - IB connection mapping */
    void (*set_conn_id)(bcmolt_cmll_conn_id ll_conn_id, bcmolt_subchannel conn_id);
    /* Connect request */
    bcmos_errno (*connect)(long ll_handle, bcmolt_conn_type conn_type, bcmolt_subchannel conn_id,
        const bcmolt_cm_addr *addr, bcmolt_cmll_conn_id *ll_conn_id);
    /* Disconnect request */
    bcmos_errno (*disconnect)(bcmolt_cmll_conn_id ll_conn_id);
    /* Exit & cleanup */
    void (*cleanup)(void);
    /* Compare addresses */
    bcmos_bool (*addr_is_equal)(const bcmolt_cm_addr *addr1, const bcmolt_cm_addr *addr2);
} bcmolt_cmll_driver;

/* Initialize underlying transport.
   Returns *init_flags
 */
bcmos_errno bcmolt_cmll_init(const bcmolt_cm_init_parms *init_parms, bcmolt_cmll_driver *driver);

/*
 * Functions exposed by common IB code for use in low-level transport driver
 */
bcmos_errno bcmolt_cmll_notify_connect(bcmolt_cmll_conn_id ll_conn_id, void *drv_data, bcmolt_cm_addr *peer_addr);
void bcmolt_cmll_notify_disconnect(bcmolt_cmll_conn_id ll_conn_id, void *drv_data);
/* Notify that new RX packet has arrived. if conn_id==bcmolt_subchannel_UNDEFINED,
   common IB code looks up the connection by peer_addr
 */
void bcmolt_cmll_notify_recv(bcmolt_cmll_conn_id ll_conn_id, void *drv_data, bcmolt_cm_conn_id conn_id,
    bcmos_buf *buf, bcmolt_cm_addr *peer_addr);

#endif /* BCMOLT_CONN_MGR_INTERNAL_H_ */

