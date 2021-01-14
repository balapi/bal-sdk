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

#ifndef BCMTR_INTERNAL_H_
#define BCMTR_INTERNAL_H_

#include <bcmos_system.h>
#include <bcmolt_msg_pack.h>
#include <bcmtr_interface.h>
#include <bcmtr_plugin.h>
#include <bcm_config.h>

#include "bcmtr_header.h"

/** Transport configuration parameters */
typedef struct
{
    bcmtr_plugin_cfg plugin_cfg;/**< Connection parameters */

    /** Limits and timeouts.
     * If not set, the appropriate BCM_TR_default defined in bcmConfig.h is used
     */
    uint32_t msg_timeout;       /**< Max time to wait for response or next message part (ms) */
    uint32_t max_requests;      /**< Max number of outstanding requests */
    uint32_t max_autos;         /**< Max number of multi-part autonomous messages */
    uint32_t max_fragments;     /**< Max number of multi-part message fragments */
    uint32_t msg_wait_timeout;  /**< Message waiting timeout (ms) */
    uint32_t msg_ready_timeout; /**< Time that transaction is kept after notifying application that it finished (ms) */
    uint32_t max_mtu;           /**< Max MTU size (bytes) */

    int rx_thread_priority;     /**< Receive thread priority. If set -1, Rx thread is NOT created */
} bcmtr_cfg;

/** Transport connection control block */
typedef struct bcmtr_conn bcmtr_conn;

/** Reassemble block */
typedef struct bcmtr_reass
{
    bcmos_buf_queue fragments;  /** Fragment list */
    int32_t last_fragment;      /** Last fragment number */
    uint32_t num_fragments;     /** Number of fragments filled in fragments array */
    uint32_t total_size;        /** Total size of received fragments */
} bcmtr_reass;

/** Transport header list head */
typedef TAILQ_HEAD(bcmtr_msg_list, bcmtr_msg) bcmtr_msg_list;

/** Transport transaction control block */
struct bcmtr_msg
{
    bcmos_buf *rx_buf;                  /**< Receive buffer info (response or autonomous) */
    uint32_t timestamp;                 /**< Message timestamp. Tx or last Rx */
    uint16_t ref_count;                 /**< tmsg block reference count */
    bcmtr_hdr hdr;                      /**< Transport header */
    TAILQ_ENTRY(bcmtr_msg) l;           /**< Transport message list entry */
    bcmtr_reass reass;                  /**< Segmentation/reassembling block */
    bcmolt_msg *msg;                    /**< Message reference */
    bcmolt_subchannel subch;            /**< Sub-channel via which message was received */
    bcmos_errno err;                    /**< Transport status */

    /* Transport header is cleared up to this point when released.
     * "err" field is the last in the section that gets cleared.
     * Do not move fields below above "err"!
     */
#define BCMTR_HDR_CLEAR_SIZE   (offsetof(bcmtr_msg, err) + sizeof(bcmos_errno))
    bcmos_msg os_msg;                   /**< OS message for request delivery */
    bcmtr_msg_list *free_list;          /**< Free list head reference */
    bcmtr_conn *conn;                   /**< Connection back reference */
    bcmos_sem sem;                      /**< "wait for response" semaphore */
};

/** Message handler context */
typedef struct bcmtr_handler bcmtr_handler;
struct bcmtr_handler
{
    f_bcmolt_msg_handler app_cb;        /**< Application callback function */
    bcmolt_auto_flags flags;            /**< Registration flag: call in context of transport rx thread or app module */
    bcmos_module_id module;             /**< Optional module to dispatch received message to */
    bcmolt_oltid olt;                   /**< OLT that requested the registration */
    STAILQ_ENTRY(bcmtr_handler) l;      /**< Transport handler list entry */
};

#ifdef BCM_SUBSYSTEM_EMBEDDED

/* Embedded side supports multiple host connections simultaneously
   - a primary connection with TrMUX
   - 0 or more additional Inband connections with remote applications
   bcmtr_client structure is used to keep track of "clients" connected with MAC device.
   For each "client" it is necessary to remember which auto indications this client subscribed for,
   in order to post indications only to the relevant clients.
*/

/** Remote client */
typedef struct bcmtr_client
{
    bcmolt_subchannel subch;            /**< Subchannel */
    bcmtr_conn *conn;                   /**< Connection struct reference */
    /** Registered autonomous indication masks */
    bcmolt_presence_mask auto_masks[BCMOLT_OBJ_ID__NUM_OF];
#define BCMTR_SILENCE_BEFORE_DISCONNECT_TIMEOUT     (5 * 1000 * 1000)
    bcmos_bool connected;               /**< Client connected */
} bcmtr_client;
#endif /* #ifdef BCM_SUBSYSTEM_EMBEDDED */

/** Transport connection control block */
struct bcmtr_conn
{
    char name[16];                      /**< Transport name */
    bcmolt_devid device;                /**< Device index */
    bcmolt_ldid ldid;                   /**< Device index on line card */
    bcmtr_cfg cfg;                      /**< Transport configuration parameters */
    bcmtr_driver driver;                /**< Transport driver */
    bcmtr_plugin_channel drv_priv;      /**< Plugin driver private data */
    bcmos_mutex mutex;                  /**< Mutex protecting the transport structure */
    uint32_t last_timeout_check;        /**< Last timeout check timestamp */
    uint32_t timeout_check_period;      /**< Time-out check period */
    bcmtr_msg_list msg_list;            /**< Message list head */
    bcmtr_msg_list free_req_list;       /**< Free request block list */
    bcmtr_msg_list free_auto_list;      /**< Free autonomous block list */
    bcmtr_msg *tmsg_array;              /**< Pre-allocated array of transport headers */
    bcmtr_stat stat;                    /**< Statistics */
    bcmos_bool connected;               /**< Transport state */
    uint16_t num_requests;              /**< Number of outstanding requests */
    uint16_t num_auto;                  /**< Number of autonomous messages being reassembled */
    uint16_t corr_tag;                  /**< Last used correlation tag */
};

#ifdef __cplusplus
extern "C" {
#endif

bcmos_errno bcmtr_cfg_init(bcmolt_devid device, bcmtr_cfg *cfg, bcmtr_driver *driver);

bcmos_errno _bcmtr_conn_get(bcmolt_devid device, bcmtr_conn **conn);

#ifdef __cplusplus
}
#endif

#endif /* BCMTR_INTERNAL_H_ */
