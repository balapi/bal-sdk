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

#include <bcmos_system.h>
#include <bcm_dev_log.h>
#include "bcmolt_host_dev_log.h"

dev_log_id log_group_bal;
dev_log_id log_group_bal_core;
dev_log_id log_group_bal_sw_util;
dev_log_id log_group_bal_swext;
dev_log_id log_group_bal_acl;
dev_log_id log_group_bal_erps;
dev_log_id log_group_bal_flow;
dev_log_id log_group_bal_group;
dev_log_id log_group_bal_inband;
dev_log_id log_group_bal_mac_table;
dev_log_id log_group_bal_lag;
dev_log_id log_group_bal_nni;
dev_log_id log_group_bal_policer;
dev_log_id log_group_bal_protection;
dev_log_id log_group_bal_sw_inni;
dev_log_id log_group_bal_tm_qmp;
dev_log_id log_group_bal_tm_queue;
dev_log_id log_group_bal_tm_sched;
dev_log_id log_group_bal_mac_util;
dev_log_id log_group_user_appl;
dev_log_id log_group_user_appl_itu;
dev_log_id log_group_user_appl_ieee;
dev_log_id log_group_onu_mgmt;

static dev_log_id _register_log_group(
    bcmolt_host_dev_log_flags flags,
    bcmolt_host_dev_log_flags filter,
    const char *name,
    dev_log_id parent)
{
    dev_log_id id;

    if ((flags & filter) == 0)
    {
        return DEV_LOG_INVALID_ID;
    }

#ifdef ENABLE_LOG
    id = bcm_dev_log_id_register(name, DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
    if (parent != DEV_LOG_INVALID_ID)
    {
        bcm_dev_log_group_add_log_id(parent, id);
    }
#else
    id = DEV_LOG_INVALID_ID;
#endif

    return id;
}

static dev_log_id _register_dev_mgmt_log_group(
    bcmolt_host_dev_log_flags flags,
    const char *name,
    dev_log_id parent)
{
    return _register_log_group(flags, BCMOLT_HOST_DEV_LOG_FLAGS_DEV_MGMT, name, parent);
}

static dev_log_id _register_user_appl_log_group(
    bcmolt_host_dev_log_flags flags,
    const char *name,
    dev_log_id parent)
{
    return _register_log_group(flags, BCMOLT_HOST_DEV_LOG_FLAGS_USER_APPL, name, parent);
}

void bcmolt_host_dev_log_init(bcmolt_host_dev_log_flags flags)
{
    log_group_bal = _register_dev_mgmt_log_group(flags, "bal", DEV_LOG_INVALID_ID);
    log_group_bal_core = _register_dev_mgmt_log_group(flags, "bal_core", log_group_bal);
    log_group_bal_sw_util = _register_dev_mgmt_log_group(flags, "sw_util", log_group_bal);
    log_group_bal_swext = _register_dev_mgmt_log_group(flags, "swext", log_group_bal);
    log_group_bal_acl = _register_dev_mgmt_log_group(flags, "access_control", log_group_bal);
    log_group_bal_erps = _register_dev_mgmt_log_group(flags, "erps", log_group_bal);
    log_group_bal_flow = _register_dev_mgmt_log_group(flags, "flow", log_group_bal);
    log_group_bal_group = _register_dev_mgmt_log_group(flags, "group", log_group_bal);
    log_group_bal_inband = _register_dev_mgmt_log_group(flags, "inband", log_group_bal);
    log_group_bal_mac_table = _register_dev_mgmt_log_group(flags, "mac_table", log_group_bal);
    log_group_bal_lag = _register_dev_mgmt_log_group(flags, "lag", log_group_bal);
    log_group_bal_nni = _register_dev_mgmt_log_group(flags, "nni", log_group_bal);
    log_group_bal_policer = _register_dev_mgmt_log_group(flags, "policer", log_group_bal);
    log_group_bal_protection = _register_dev_mgmt_log_group(flags, "protection", log_group_bal);
    log_group_bal_sw_inni = _register_dev_mgmt_log_group(flags, "switch_inni", log_group_bal);
    log_group_bal_tm_qmp = _register_dev_mgmt_log_group(flags, "tm_qmp", log_group_bal);
    log_group_bal_tm_queue = _register_dev_mgmt_log_group(flags, "tm_queue", log_group_bal);
    log_group_bal_tm_sched = _register_dev_mgmt_log_group(flags, "tm_sched", log_group_bal);
    log_group_bal_mac_util = _register_dev_mgmt_log_group(flags, "mac_util", log_group_bal);
    log_group_user_appl = _register_user_appl_log_group(flags, "USER_APPL", DEV_LOG_INVALID_ID);
    log_group_user_appl_itu = _register_user_appl_log_group(flags, "USER_APPL_ITU", log_group_user_appl);
    log_group_user_appl_ieee = _register_user_appl_log_group(flags, "USER_APPL_IEEE", log_group_user_appl);
    log_group_onu_mgmt = _register_user_appl_log_group(flags, "ONU_MGMT", DEV_LOG_INVALID_ID);
}
