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

#ifndef BCMOLT_HOST_API_H_
#define BCMOLT_HOST_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <bcmos_system.h>
#include <bcmolt_api.h>
#include <bcm_dev_log.h>

/** IP (UDP) parameters */
typedef struct
{
    bcmos_ipv4_address ip;      /**< IP address in host format */
    uint16_t port;              /**< UDP port in host format */
} addr_ip_port;

typedef enum
{

    BCM_HOST_API_CONN_REMOTE,
    BCM_HOST_API_CONN_LOCAL

}bcm_host_api_conn;

/** Host subsystem initialization parameters */
typedef struct bcmolt_host_init_parms
{
    /** Transport initialization parameters */
    struct
    {
        /** Connection parameters with device management daemon */
        bcm_host_api_conn type;       /**< Connection type. Supported types are
                                         BCM_HOST_API_CONN_REMOTE - Network connection manager based transport
                                         BCM_HOST_API_CONN_LOCAL - Unix domain socket (linux only)
                                      */
        addr_ip_port addr;            /**< Device management daemon address (and port). Must be set if type==BCM_HOST_API_CONN_REMOTE */
        uint16_t listen_port;         /**< UDP port to listen on. 0=auto-assign */
        bcmos_bool disable_ka;        /**< Disable keep alive between application and device management daemon. This is a debug option */
    } transport;

    bcmos_bool use_default_logging; /**< TRUE when the user doesn't build with logging enabled, but wants the attached host api module to be able to log */

#ifdef ENABLE_LOG
    dev_log_init_parms log;
#endif

} bcmolt_host_init_parms;

/**
 * @brief  Initialize host subsystem
 * @note This function must be called first
 * @param  *init_parms: initialization parameters
 * @retval BCM_ERR_OK (0) if successful or error < 0
 */
bcmos_errno bcmolt_host_init(const bcmolt_host_init_parms *init_parms);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BCMOLT_HOST_API_H_ */
