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

/*
 * Application side connection manager.
 * This module monitors application connection with Device Managhement Daemon(s)
 */

#ifndef BCMOLT_API_CONN_MGR_
#define BCMOLT_API_CONN_MGR_

#include <bcmos_system.h>
#include <bcmolt_msg.h>
#include <bcmtr_interface.h>
#include <bcmolt_api_topology.h>
#include <bcmolt_api_model_supporting_enums.h>

/** Connection manager flags */
typedef enum
{
    BCMOLT_API_CONN_MGR_FLAGS_NONE          = 0,
    BCMOLT_API_CONN_MGR_FLAGS_DISABLE_KA    = 0x1,   /**< Disable keep alive (for debugging) */
} bcmolt_api_conn_mgr_flags;

/* OLT connection status */
typedef enum
{
    BCMOLT_API_CONN_STATUS_DISCONNECTED = BCMOS_FALSE,
    BCMOLT_API_CONN_STATUS_CONNECTED    = BCMOS_TRUE
} bcmolt_api_conn_status;

/* Disconnect reason */
typedef enum
{
    BCMOLT_OLT_DISCONNECT_REASON_CONNECTED = 0, /**< This value is used when connection manager is connected with device management daemon */
    BCMOLT_OLT_DISCONNECT_REASON_KA_FAILURE = 1, /**< Keep Alive Failure. */
    BCMOLT_OLT_DISCONNECT_REASON_DAEMON_RESTART = 2, /**< Device Management Daemon Restart. */
} bcmolt_olt_disconnect_reason;

bcmos_errno bcmolt_api_conn_mgr_start(bcmolt_goid olt, bcmolt_loid loid,
    const bcmtr_conn_parms *tr_conn_parms, bcmolt_api_conn_mgr_flags flags);

bcmos_bool bcmolt_api_conn_mgr_is_connected(bcmolt_goid olt);

typedef void (*F_api_conn_mgr_connect_disconnect_ind)(bcmolt_goid olt,
    bcmolt_api_conn_status status, bcmolt_olt_disconnect_reason reason);

/* Subscribe to connect/disconnect indication callback.
   Multiple clients can subscribe
*/
bcmos_errno bcmolt_api_conn_mgr_ind_subscribe(F_api_conn_mgr_connect_disconnect_ind cb);

/* Unsubscribe connect/disconnect indication callback.
*/
bcmos_errno bcmolt_api_conn_mgr_ind_unsubscribe(F_api_conn_mgr_connect_disconnect_ind cb);


void bcmolt_api_conn_mgr_stop(bcmolt_goid olt);

void bcmolt_api_conn_mgr_stop_all(void);

#endif /* BCMOLT_API_CONN_MGR_H_ */
