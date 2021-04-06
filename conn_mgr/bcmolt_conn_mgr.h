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

/* bcmolt_conn_mgr.h - Connection manager */

#ifndef BCMOLT_CONN_MGR_H_
#define BCMOLT_CONN_MGR_H_

#include <bcmos_system.h>
#include <bcmolt_msg.h>

/** Connection id */
typedef uint16_t bcmolt_cm_conn_id;
#define BCMOLT_CM_CONN_ID_UNDEFINED     0xffff

#define BCMOLT_CONN_TYPE_MASK(type) (bcmolt_conn_type_mask)(1 << type)

/** Transport type */
typedef enum
{
    BCMOLT_CM_TRANSPORT_UDP         /**< UDP transport */
} bcmolt_cm_transport_type;

/** Transport address */
typedef struct bcmolt_cm_addr
{
    bcmolt_cm_transport_type type;

    /** Type-specific configuration */
    union
    {
        /** UDP parameters */
        struct
        {
            bcmos_ipv4_address ip;      /**< IP address in host format */
            uint16_t port;              /**< UDP port in host format */
        } udp;
    };
} bcmolt_cm_addr;

/* Packet header */
typedef struct __PACKED_ATTR_START__ bcm_cm_packet_hdr
{
    uint16_t device;
    uint16_t subch;
} __PACKED_ATTR_END__ bcm_cm_packet_hdr;

/** Connection cookie */
typedef long bcmolt_cm_cookie;

/** Initialisation parameters */
typedef struct bcmolt_cm_init_parms
{
    uint32_t   max_mtu;           /**< Max transfer unit size */
    uint32_t   max_conns;         /**< Max number of connections */
} bcmolt_cm_init_parms;

/** Enable parameters */
typedef struct bcmolt_cm_enable_parms
{
    bcmolt_cm_addr local_addr;  /**< Optional local address */
    uint32_t flags;             /**< Flags */
#define BCMOLT_CM_FLAG_MATCH_BY_ADDR        0x00000001    /* Match connections by address */
#define BCMOLT_CM_FLAG_MATCH_BY_DEV         0x00000002    /* Match connections by device */
#define BCMOLT_CM_FLAG_MATCH_BY_ADDR_DEV    (BCMOLT_CM_FLAG_MATCH_BY_ADDR | BCMOLT_CM_FLAG_MATCH_BY_DEV)
#define BCMOLT_CM_FLAG_MATCH_BY_SUBCH       0x00000004    /* Match connections by subchannel */
#define BCMOLT_CM_FLAG_CREATE_RX_TASK       0x00000010    /* Create RX task (if required) */
#define BCMOLT_CM_FLAG_CREATE_ACCEPT_TASK   0x00000020    /* Create ACCEPT task (if required) */
#define BCMOLT_CM_FLAG_AUTO_ACCEPT          0x00000040    /* Accept unmatching packets as new connection. Don't wait for "connect" message */
    bcmolt_conn_type auto_accept_conn_type; /**< Connection type for auto-accept mode */
} bcmolt_cm_enable_parms;

/** Connect parameters */
typedef struct bcmolt_cm_connect_parms
{
    bcmolt_ldid device;                 /**< Device */
    bcmolt_cm_addr remote_addr;         /**< Remote address */
    bcmolt_conn_type remote_conn_type;  /**< Remote connection type */
} bcmolt_cm_connect_parms;

/**
 * @brief  Initialize connection manager
 * @param[in]  init_parms:  Initialization parameters
 * @retval Error code
 */
bcmos_errno bcmolt_cm_init(const bcmolt_cm_init_parms *init_parms);

/**
 * @brief  Cleanup connection manager
 */
void bcmolt_cm_exit(void);

/**
 * @brief  Enable specified connection type(s)
 * @note This function must be called before bcmolt_cm_connect(), bcmolt_cm_send(), bcmolt_cm_recv()
 * @param[in]  conn_types:      connection types
 * @param[in]  enable_parms:    optional parameters
 * @retval Error code
 */
bcmos_errno bcmolt_cm_enable(bcmolt_conn_type_mask conn_types, const bcmolt_cm_enable_parms *enable_parms);

/**
 * @brief  Disable specified connection types
 * @note conn_types must match the mask specified in the relevant bcmolt_cm_enable()
 * @param[in]  conn_types:  Connection types to cleanup for
 */
void bcmolt_cm_disable(bcmolt_conn_type_mask conn_types);

/**
 * @brief New connection indication callback
 * @param[in]  conn_type:   New connection type
 * @param[in]  conn_id:     New connection id
 * @param[in]  device:      Device id
 * @param[in]  addr:        Address
 * @param[in]  subch:       Subchannel
 * @retval error code. If != BCM_ERR_OK, the connection is dropped
 */
typedef bcmos_errno (*bcmolt_cm_connect_cb)(bcmolt_conn_type conn_type, bcmolt_cm_conn_id conn_id,
    bcmolt_ldid device, const bcmolt_cm_addr *addr, bcmolt_subchannel subch);

/**
 * @brief  Disconnect indication
 * @param[in]  conn_id:     Connection id
 */
typedef void (*bcmolt_cm_disconnect_cb)(bcmolt_conn_type conn_type, bcmolt_cm_conn_id conn_id);

/**
 * @brief  Packet receive callback
 * @param[in]  conn_type:   New connection type
 * @param[in]  conn_id:     Connection id
 * @param[in]  device:      Device id
 * @param[in]  subch:       Managed subchannel id encoded in the packet
 * @param[in]  conn_id:     Connection id
 * @param[in]  buf:         Received packet
 */
typedef void (*bcmolt_cm_rx_cb)(bcmolt_conn_type conn_type, bcmolt_cm_conn_id conn_id,
    bcmolt_ldid device, bcmolt_subchannel subch, bcmos_buf *buf);

/** Connection handlers */
typedef struct bcmolt_cm_handlers
{
    bcmolt_cm_connect_cb connect;           /**< New connection callback */
    bcmolt_cm_disconnect_cb disconnect;     /**< Disconnect callback */
    bcmolt_cm_rx_cb recv;                   /**< Receive callback */
} bcmolt_cm_handlers;

/**
 * @brief  Set connection handlers
 * @param[in]  conn_type:       Connection type
 * @param[in]  handlers:        Handlers
 */
void bcmolt_cm_handlers_set(bcmolt_conn_type conn_type, const bcmolt_cm_handlers *handlers);

/**
 * @brief  Get connection handlers
 * @param[in]  conn_type:       Connection type
 * @param[out]  handlers:        Handlers
 */
void bcmolt_cm_handlers_get(bcmolt_conn_type conn_type, bcmolt_cm_handlers *handlers);

/**
 * @brief  Connect to MAC device
 * @note This function is called on the host side
 * @param[in]  conn_type:   Connection type
 * @param[in]  conn_parms:  Connection parameters
 * @param[out] conn_id:     New connection id
 * @retval Error code
 */
bcmos_errno bcmolt_cm_connect(bcmolt_conn_type conn_type, const bcmolt_cm_connect_parms *conn_parms,
    bcmolt_cm_conn_id *conn_id);

/**
 * @brief  Set opaque connection cookie
 * @note MAC device uses this function to store autonomous message registration masks
 * @param[in]  conn_id:     Connection id
 * @param[in]  cookie:      Connection cookie
 * @retval Error code
 */
bcmos_errno bcmolt_cm_cookie_set(bcmolt_cm_conn_id conn_id, bcmolt_cm_cookie cookie);

/**
 * @brief  Get connection cookie
 * @note MAC device uses this function to store autonomous message registration masks
 * @param[in]  conn_id:     Connection id
 * @param[out] cookie:      Connection cookie
 * @retval Error code
 */
bcmos_errno bcmolt_cm_cookie_get(bcmolt_cm_conn_id conn_id, bcmolt_cm_cookie *cookie);

/**
 * @brief  Get device associated with connection
 * @param[in]  conn_id:     Connection id
 * @param[out] device:      Device id on a line card
 * @retval Error code
 */
bcmos_errno bcmolt_cm_device_get(bcmolt_cm_conn_id conn_id, bcmolt_ldid *device);

/**
 * @brief  Get client address associated with connection
 * @param[in]  conn_id:     Connection id
 * @param[out] addr:        Address
 * @retval Error code
 */
bcmos_errno bcmolt_cm_addr_get(bcmolt_cm_conn_id conn_id, bcmolt_cm_addr *addr);

/**
 * @brief  Send packet via connection
 * @param[in]  conn_id:     Connection id
 * @param[in]  subch:       Sub-channel
 * @param[in]  buf:         Buffer to send. Buffer is released automatically.
 * @retval Error code
 */
bcmos_errno bcmolt_cm_send(bcmolt_cm_conn_id conn_id, bcmolt_subchannel subch, bcmos_buf *buf);

/**
 * @brief  Receive packet via connection
 * @note This function is called when channel is used in "pull mode", as opposed to
 *       registering recv callback
 * @param[in]  conn_types:  Connection types
 * @param[out] conn_id:     Connection id
 * @param[out] device:      Device (from packet header)
 * @param[out] subch:       Sub-channel (from packet header)
 * @param[in]  buf:         Received buffer
 * @retval Error code
 */
bcmos_errno bcmolt_cm_recv(bcmolt_conn_type_mask conn_types, bcmolt_cm_conn_id *conn_id,
    bcmolt_ldid *device, bcmolt_subchannel *subch, bcmos_buf **buf);

/**
 * @brief  Disconnect
 * @param[in]  conn_id:     Connection id. It becomes invalid.
 * @retval Error code
 */
bcmos_errno bcmolt_cm_disconnect(bcmolt_cm_conn_id conn_id);

/**
 * @brief  Connection iterator
 * @param[in]       conn_type_mask: Connection type(s)
 * @param[in,out]   conn_id:        Input: Previous connection id. BCMOLT_CM_CONN_ID_UNDEFINED == get first
 *                                  Output: next valid connection id of the requested type
 * @param[out]      last_rx_ts:     Last RX timestamp. Can be NULL
 * @retval  BCM_ERR_OK, BCM_ERR_PARM, BCM_ERR_NO_MORE
 */
bcmos_errno bcmolt_cm_conn_get_next(bcmolt_conn_type_mask conn_type_mask, bcmolt_cm_conn_id *conn_id,
    uint32_t *last_rx_ts);


#endif /* BCMOLT_CONN_MGR_H_ */
