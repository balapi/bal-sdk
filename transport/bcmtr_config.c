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

#include "bcmtr_internal.h"
#include "bcmtr_interface.h"
#include "bcmtr_plugin.h"

#include <bcmtr_plugin_conn_mgr.h>

#if defined(BCM_OS_THREADX)
#include <bcmtr_plugin_pcie.h>
#endif

#if defined(PLUGIN_UNIX_DOMAIN)
#include <bcmtr_plugin_unix_domain.h>
#endif

#if defined(PLUGIN_TRMUX_DIRECT)
#include <bcmtr_plugin_trmux_direct.h>
#endif

#if defined(SIMULATION_BUILD) && defined(BCM_SUBSYSTEM_EMBEDDED) && defined(BCMTR_UDP_SUPPORT)
static int _bcmtr_assign_random_port(void)
{
    int port;

    port = rand() % 50000;
    if (port < 20000)
    {
        port += 20000;
    }

    return port;
}
#endif

/* Fetch configuration
 * set-up transport driver plugin
 * Eventually this function can read from config file or device control driver.
 * For now - hardcode
 */
bcmos_errno bcmtr_cfg_init(bcmolt_devid device, bcmtr_cfg *cfg, bcmtr_driver *driver)
{
    bcmos_errno rc = BCM_ERR_NOT_SUPPORTED;

    /* need a longer host msg_timeout when using inband communication from host to device */
    cfg->msg_timeout = BCMTR_MSG_TIMEOUT;
    cfg->max_fragments = BCMTR_MAX_FRAGMENTS;
    cfg->max_requests = BCMTR_MAX_REQUESTS;
    cfg->max_autos = BCMTR_MAX_AUTOS;
    cfg->max_mtu = BCMTR_MAX_MTU_SIZE;
    cfg->msg_wait_timeout = BCMTR_MSG_WAIT_MS;
    cfg->msg_ready_timeout = BCMTR_MSG_READY_MS;
    cfg->rx_thread_priority = TASK_PRIORITY_TRANSPORT_RX;

    switch(cfg->plugin_cfg.type)
    {
#if defined(BCMTR_UDP_SUPPORT)
    case BCMTR_TRANSPORT_TYPE_CONN_MGR:             /**< Network connection manager based transport */
        {
            if (!cfg->plugin_cfg.x.cm.udp.ip.u32)
            {
    #if defined(BCM_SUBSYSTEM_HOST) || defined(BCM_SUBSYSTEM_OPENCPU)
                cfg->plugin_cfg.x.cm.udp.ip.u32 = BCMTR_TR_UDP_OLT_IP;
    #else
                cfg->plugin_cfg.x.cm.udp.ip.u32 = BCMTR_TR_UDP_HOST_IP;
    #endif
            }

            if (!cfg->plugin_cfg.x.cm.udp.port)
            {
    #if defined(BCM_SUBSYSTEM_HOST) || defined(BCM_SUBSYSTEM_OPENCPU)
                cfg->plugin_cfg.x.cm.udp.port = BCMTR_TR_UDP_OLT_PORT;
    #else
        #ifndef SIMULATION_BUILD
                cfg->plugin_cfg.x.cm.udp.port = BCMTR_TR_UDP_HOST_PORT;
        #else
                /* Assign random UDP port for embedded simulation */
                cfg->plugin_cfg.x.cm.udp.port = _bcmtr_assign_random_port();
        #endif
    #endif
            }

            /* Initialize plugin */
            rc = bcmtr_plugin_cm_init(&cfg->plugin_cfg, driver);
        }
        break;
#endif /* #if defined(BCMTR_UDP_SUPPORT) */

#if defined(BCM_OS_THREADX)
    case BCMTR_TRANSPORT_TYPE_PCIE:             /**< PCIE transport */
        rc = bcmtr_plugin_pcie_init(&cfg->plugin_cfg, driver);
        break;
#endif

#if defined(PLUGIN_UNIX_DOMAIN)
    case BCMTR_TRANSPORT_TYPE_UNIX_DOMAIN:      /**< Unix domain socket transport */
        rc = bcmtr_plugin_unix_domain_init(&cfg->plugin_cfg, driver);
        break;
#endif

#if defined(PLUGIN_TRMUX_DIRECT)
    case BCMTR_TRANSPORT_TYPE_TRMUX:            /**< Direct interface with trmux */
        rc = bcmtr_plugin_trmux_init(&cfg->plugin_cfg, driver);
        break;
#endif

    default:
        rc = BCM_ERR_NOT_SUPPORTED;
        break;
    }

    if (rc != BCM_ERR_OK)
    {
        BCMOS_TRACE_ERR("Failed to initialize transport plugin 0x%x. Error %s\n",
            cfg->plugin_cfg.type, bcmos_strerror(rc));

    }

    return rc;
}
