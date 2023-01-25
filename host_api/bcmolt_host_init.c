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

#include <bcmolt_host_api.h>
#include <bcmtr_interface.h>
#include <bcmolt_conn_mgr.h>
#ifndef BCM_SUBSYSTEM_OPENCPU
#include <bcmolt_api_conn_mgr.h>
#endif
#include <bcmolt_serializer.h>
#include <bcmolt_host_dev_log.h>
#ifdef BCM_BOARD_SUPPORT
#include <bcmolt_board.h>
#endif

/* Initialize host subsystem */
bcmos_errno bcmolt_host_init(const bcmolt_host_init_parms *init_parms)
{
    bcmtr_conn_parms tr_conn_parms = {};
    bcmtr_init_parms tr_init_parms = {};
    bcmos_errno rc;

    /* Initialize OS abstraction */
    rc = bcmos_init();
    BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmolt_os_init()\n");

    /* Check parameters */
    if (init_parms->transport.type != BCM_HOST_API_CONN_LOCAL &&
        init_parms->transport.type != BCM_HOST_API_CONN_REMOTE)
    {
        bcmos_printf("%s: transport.type must be BCM_HOST_API_CONN_LOCAL or BCM_HOST_API_CONN_REMOTE\n",
            __FUNCTION__);
        return BCM_ERR_PARM;
    }

    bcmos_trace_level_set(BCMOS_TRACE_LEVEL_INFO);

#ifdef ENABLE_LOG
    /* Initialize logger */
    rc = bcm_log_init(&init_parms->log);
    BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmolt_log_init()\n");

    /* Initialize host-specific logger info */
    bcmolt_host_dev_log_init(BCMOLT_HOST_DEV_LOG_FLAGS_USER_APPL);
#endif

    /* Initialize serializer utility */
    bcmolt_serializer_init();

    /* Initialize transport */
    tr_conn_parms.type = (init_parms->transport.type == BCM_HOST_API_CONN_REMOTE) ?
        BCMTR_TRANSPORT_TYPE_CONN_MGR : BCMTR_TRANSPORT_TYPE_UNIX_DOMAIN;

    if (tr_conn_parms.type == BCMTR_TRANSPORT_TYPE_CONN_MGR)
    {
        bcmolt_cm_init_parms cm_init_parms = {};
        bcmolt_cm_enable_parms cm_enable_parms = {};
        bcmolt_cm_addr cm_addr;

        cm_addr.type = BCMOLT_CM_TRANSPORT_UDP;
        cm_addr.udp.ip = init_parms->transport.addr.ip;
        cm_addr.udp.port = init_parms->transport.addr.port;

        cm_init_parms.max_conns = BCMTR_MAX_DEVICES;
        cm_enable_parms.flags = BCMOLT_CM_FLAG_MATCH_BY_ADDR_DEV | BCMOLT_CM_FLAG_CREATE_RX_TASK;
        cm_enable_parms.local_addr.udp.port = init_parms->transport.listen_port;

        tr_conn_parms.x.cm = cm_addr;

        /* Initialize network connection manager */
        rc = bcmolt_cm_init(&cm_init_parms);
        BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmolt_cm_init()\n");

        /* Enable connection manager */
        rc = bcmolt_cm_enable(BCMOLT_CONN_TYPE_MASK_APP, &cm_enable_parms);
        BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmolt_cm_enable()\n");
    }

    /* Initialize board support */
#ifdef BCM_BOARD_SUPPORT
    bcmolt_board_init();
#endif

    /* Initialize API transport */
    rc = bcmtr_init(&tr_init_parms);
    BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmtr_init()\n");

#ifndef BCM_SUBSYSTEM_OPENCPU
    /* Initialize API layer */
    rc = bcmolt_api_init();
    BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmolt_api_init()\n");

    rc = bcmolt_api_utils_init();
    BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmolt_api_utils_init()\n");

    /* Start connection manager */
    {
        bcmolt_api_conn_mgr_flags conn_mgr_flags = init_parms->transport.disable_ka ?
            BCMOLT_API_CONN_MGR_FLAGS_DISABLE_KA : BCMOLT_API_CONN_MGR_FLAGS_NONE;
        bcmolt_loid olt;

        for (olt = 0; olt < BCM_MAX_OLTS_PER_LINE_CARD && rc == BCM_ERR_OK; olt++)
            rc = bcmolt_api_conn_mgr_start((bcmolt_goid)olt, olt, &tr_conn_parms, conn_mgr_flags);
        BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmolt_api_conn_mgr_start()\n");
    }
#else
    /* For open CPU connect transport to dev_mgmt_daemon directly */
    rc = bcmtr_connect(0, &tr_conn_parms);
    BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmtr_connect()\n");

    /* Initialize API layer */
    rc = bcmolt_api_init();
    BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmolt_api_init()\n");

    rc = bcmolt_api_utils_init();
    BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcmolt_api_utils_init()\n");

#endif

    return BCM_ERR_OK;
}
