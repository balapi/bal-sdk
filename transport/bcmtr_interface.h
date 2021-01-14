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

#ifndef BCMTR_INTERFACE_H_
#define BCMTR_INTERFACE_H_

#include <bcmos_system.h>
#include <bcmolt_api_model.h>
#include <bcmolt_conn_mgr.h>
#include <bcm_dev_log.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Transport type */
typedef enum
{
    BCMTR_TRANSPORT_TYPE_CONN_MGR,      /**< Network connection manager-based transport */
    BCMTR_TRANSPORT_TYPE_PCIE,          /**< PCIE transport */
    BCMTR_TRANSPORT_TYPE_UNIX_DOMAIN,   /**< Unix domain socket transport */
    BCMTR_TRANSPORT_TYPE_TRMUX,         /**< Direct interface with trmux */

    BCMTR_TRANSPORT_TYPE__NUM_OF
} bcmtr_transport_type;

/** Transport statistics */
typedef struct bcmtr_stat
{
    uint32_t msg_sent;                  /**< Messages sent */
    uint32_t msg_resp_received;         /**< Valid responses received */
    uint32_t msg_req_auto_received;     /**< Request or Autonomous message received */
    uint32_t msg_req_timeout;           /**< Number of requests that timed out */
    uint32_t msg_reass_timeout;         /**< Number of messages discarded due to reassemble timeout */
    uint32_t msg_no_req;                /**< Number of responses discarded because there was no matching request */
    uint32_t msg_no_mem;                /**< Number of memory allocation failures */
    uint32_t msg_comm_err;              /**< Messages discarded because of communication error */
    uint32_t msg_ready_timeout;         /**< Responses that have been reported to application but not peaked up */
    uint32_t msg_too_many_req;          /**< Number of requests discarded because there were too many outstanding requests */
    uint32_t msg_too_many_auto;         /**< Number of autonomous messages discarded because there were too many being reassembled */
    uint32_t not_connected;             /**< Number of TX messages discarded because connection was lost */
    uint32_t frag_received;             /**< Valid fragments received */
    uint32_t frag_invalid;              /**< Fragments discarded */
    uint32_t pack_errors;               /**< Message pack errors */
    uint32_t unpack_errors;             /**< Message unpack errors */
    uint32_t translate_errors;          /**< Message translation errors */
    uint32_t no_rx_handler;             /**< Message discarded because there was no rx handler */
} bcmtr_stat;

/** Transport message control block */
typedef struct bcmtr_msg bcmtr_msg;

/** Send flags */
typedef enum
{
    BCMTR_SEND_FLAGS_NONE               = 0,            /**< None */
    BCMTR_SEND_FLAGS_CALL               = 0x0001,       /**< Request/Response sequence */

    BCMTR_SEND_FLAGS_PRI_NORMAL         = 0,            /**< Normal priority */
    BCMTR_SEND_FLAGS_PRI_LO             = 0x0010,       /**< Low priority */
    BCMTR_SEND_FLAGS_PRI_HI             = 0x0020,       /**< High priority */

    BCMTR_SEND_FLAGS_LONG_WAIT          = 0x0100,       /**< Enable long wait until there is room in tx queue */
    BCMTR_SEND_FLAGS_SHORT_WAIT         = 0x0200,       /**< Enable short wait until there is room in tx queue */
    BCMTR_SEND_FLAGS_DO_NOT_WAIT        = 0x0400,       /**< Drop packet if TX q is full */

    /* Internal flags. Do NOT set explicitly */
    BCMTR_SEND_FLAGS_AUTO_FREE          = 0x2000,       /**< Release bcmolt_msg automatically when safe */

} bcmtr_send_flags;

#define BCMTR_SEND_FLAGS_WAIT_MASK (bcmtr_send_flags)(BCMTR_SEND_FLAGS_LONG_WAIT | BCMTR_SEND_FLAGS_SHORT_WAIT | BCMTR_SEND_FLAGS_DO_NOT_WAIT)

/* All subchannels application-level connections have the following bit set in subch id. Set internally */
#define BCMTR_SUBCH_AUX           0x8000

/** Transport handler registration parameters */
typedef struct bcmtr_handler_parm
{
    bcmolt_oltid olt;           /**< OLT instance */
    uint8_t instance;           /**< Instance (i.e, link) */
    bcmolt_mgt_group group;     /**< Message group. Can be BCMOLT_MGT_GROUP_ANY */
    bcmolt_obj_id object;       /**< Object. Can be BCMOLT_OBJECT_ANY */
    uint16_t subgroup;          /**< Message subgroup. Can be BCMOLT_SUBGROUP_ANY */
    f_bcmolt_msg_handler app_cb;/**< Message handler */
    bcmolt_auto_flags flags;    /**< Flags. app_cb is called in context of transport task
                                     or app module, depending on the flags */
    bcmos_module_id module;     /**< Target module id. Relevant only if flags == BCMOLT_AUTO_FLAGS_DISPATCH.
                                     BCMOS_MODULE_ID_NONE is replaced by the module calling registration function */
} bcmtr_handler_parm;

/** Transport connection parameters */
typedef struct bcmtr_conn_parms
{
    bcmtr_transport_type type;  /**< Transport type */
    bcmolt_conn_type_mask mode; /**< Connection mode (managed/unmanaged) */
    bcmolt_ldid ldid;           /**< Device id on line card */

    /** Type-specific configuration */
    union
    {
        /** Connection manager plugin parameters */
        bcmolt_cm_addr cm;
    } x;

} bcmtr_conn_parms;

/** Transport layer initialization parameters */
typedef struct bcmtr_init_parms
{
    uint32_t dummy;                     /* FFU */
} bcmtr_init_parms;

/** Initialize transport library.
 * \param[in]   parms   Initialization parameters
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_init(bcmtr_init_parms *parms);

/** Release resources used by transport library.
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_exit(void);

/** Query whether or not the device is currently connected
 *
 * \param[in]   device          OLT device index
 * \param[out]  is_connected    TRUE is returned if device is connected
 *
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_is_connected(bcmolt_devid device, bcmos_bool *is_connected);

/** Connect device
 *
 * \param[in]   device          OLT device index
 * \param[in]   conn_parm       Connection parameters
 *
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_connect(bcmolt_devid device, const bcmtr_conn_parms *conn_parms);

/** Get connection info
 *
 * \param[in]   device          OLT device index
 * \param[out]  conn_parm       Connection parameters
 *
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_connect_info_get(bcmolt_devid device, bcmtr_conn_parms *conn_parms);

#ifdef BCM_SUBSYSTEM_EMBEDDED

/* Disconnect auxiliary connection */
void bcmtr_disconnect_aux(void);

/** Disconnect client
 * \param[in]   mode            Mode: managed/unmanaged
 * \param[in]   subch           Subchannel
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_client_disconnect(bcmolt_conn_type mode, bcmolt_subchannel subch);

/** Client connected indication
 * \param[in]   mode            Mode: managed/unmanaged
 * \param[in]   conn_id         Connection id
 * \param[in]   subch           Subchannel
 * \param[in]   addr            Address
 * \param[in]   device          Device id
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_client_connected(bcmolt_conn_type conn_type, bcmolt_cm_conn_id conn_id,
    bcmolt_ldid device, const bcmolt_cm_addr *addr, bcmolt_subchannel subch);

/** Client disconnected indication
 * \param[in]   mode            Mode: managed/unmanaged
 * \param[in]   conn_id         Connection id
 */
void bcmtr_client_disconnected(bcmolt_conn_type mode, bcmolt_cm_conn_id conn_id);

#endif

/** Send message. Do not wait for response
 *
 * Set-up connection if necessary, pack message and send it to the remote side.
 * This function is intended for proxy and autonomous messages.
 *
 * \param[in]   device  OLT device index
 * \param[in]   msg     Application message to be sent
 * \param[in]   flags   flags (request/auto or reply)
 *
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_send(bcmolt_devid device, bcmolt_msg *msg, bcmtr_send_flags flags);

/** Send response message
 *
 * Send response to bcmtr_call(). This function is called by
 * message processing backend. Message ownership passes to the transport layer.
 * The msg passed to bcmtr_send_response is the same that was passed by the
 * transport layer to message processing backend.
 *
 * \param[in]   device  OLT device index
 * \param[in]   msg     Application message to be sent
 *
 * \returns BCM_ERR_OK or error code
 */
static inline bcmos_errno bcmtr_send_response(bcmolt_devid device, bcmolt_msg *msg)
{
    msg->dir = BCMOLT_MSG_DIR_RESPONSE;
    return bcmtr_send(
        device,
        msg,
        (bcmtr_send_flags)(BCMTR_SEND_FLAGS_CALL | BCMTR_SEND_FLAGS_SHORT_WAIT | BCMTR_SEND_FLAGS_AUTO_FREE));
}

/** Send request and wait for reply
 *
 * Set-up connection if necessary, pack message and send it to the remote side.
 * Wait for reply or timeout, unpack the reply and return.
 *
 * \param[in]        device  OLT device index
 * \param[in, out]   msg     Application message
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_call(bcmolt_devid device, bcmolt_msg *msg);

/** Register message handler
 *
 * \param[in]   device          OLT device index
 * \param[in]   parm            Registration parameters
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_msg_handler_register(bcmolt_devid device, const bcmtr_handler_parm *parm);

/** Unregister message handler
 *
 * \param[in]   device          OLT device index
 * \param[in]   parm            Registration parameters
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_msg_handler_unregister(bcmolt_devid device, const bcmtr_handler_parm *parm);

/** Get registration info
 *
 * \param[in]           device          OLT device index
 * \param[in,out]       parm            Registration parameters.
 *                                      instance, group, object, subgroup must be set
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_msg_handler_register_get(bcmolt_devid device, bcmtr_handler_parm *parm);

/** Get transport statistics
 *
 * \param[in]   device          OLT device index
 * \param[out]  stat            Statistics
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_stat_get(bcmolt_devid device, bcmtr_stat *stat);

/* Disconnect device */
bcmos_errno bcmtr_disconnect(bcmolt_devid device);

/* "dropped because of tx_queue overflow" indication */
typedef void (*F_bcmtr_tx_overflow)(bcmolt_devid device, bcmtr_send_flags send_flags);

/* Register for notification that transmit failed because
 * tx_queue was full
 * \param[in]   device          OLT device index
 * \param[in]   cb              Callback to be called. NULL=unregister
 * \returns 0=OK or error code < 0
 */
bcmos_errno bcmtr_tx_overflow_cb_register(bcmolt_devid device, F_bcmtr_tx_overflow cb);

/* Optional autonomous indication translation callback */
typedef bcmos_errno (*F_bcmtr_rx_translate)(bcmolt_devid device, bcmolt_oltid olt, bcmolt_msg *msg);

/* Register optional callback that "translates" indication before it is delivered
 * tx_queue was full
 * \param[in]   cb              Callback to be called. NULL=unregister
 */
void bcmtr_rx_translate_cb_register(F_bcmtr_rx_translate cb);

/* Increment RX_NO_MEM discard counter */
void bcmtr_rx_increment_rx_no_mem(bcmolt_devid device);

#ifdef BCM_SUBSYSTEM_HOST
/*
 * Connection manager support
 */

/* Send keep alive message to the managemnt daemon
 * \param[in]   device          Global device index
 * \param[out]  conn_id         Connection id returned by the managment daemon
 * \returns 0=OK or error code < 0
 */
bcmos_errno bcmtr_keep_alive(bcmolt_devid device, uint16_t *conn_id);

/* Propagate subscribtions for autonomous indication to device management daemon
 * \param[in]   device          OLT device index
 * \returns 0=OK or error code < 0
 */
bcmos_errno bcmtr_msg_handler_register_install(bcmolt_devid device);

/* Deliver indication to subscriber.
 * Indication is delivered as if received from the line.
 * \param[in]   device          OLT device index
 * \param[in]   msg             Message to be delivered to subscribers
 * \returns 0=OK or error code < 0
 */
bcmos_errno bcmtr_msg_dispatch(bcmolt_devid device, bcmolt_msg *msg);

#endif /* #ifdef BCM_SUBSYSTEM_HOST */

extern dev_log_id bcmtr_log_id[BCMTR_MAX_DEVICES];
#define BCMTR_LOG(device, level, fmt, ...)  BCM_LOG(level, bcmtr_log_id[device], fmt, ## __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* BCMTR_INTERFACE_H_ */
