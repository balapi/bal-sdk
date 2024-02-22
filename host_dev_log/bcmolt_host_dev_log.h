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
#ifndef BCMOLT_HOST_DEV_LOG_H_
#define BCMOLT_HOST_DEV_LOG_H_

#include <bcmos_system.h>
#include <bcm_dev_log.h>

typedef enum
{
   BCMOLT_HOST_DEV_LOG_FLAGS_NONE = 0,
   BCMOLT_HOST_DEV_LOG_FLAGS_DEV_MGMT = 1 << 0,
   BCMOLT_HOST_DEV_LOG_FLAGS_USER_APPL = 1 << 1,
} bcmolt_host_dev_log_flags;

#ifdef ENABLE_LOG

extern dev_log_id log_group_bal; /* top-level BAL log group */
extern dev_log_id log_group_bal_core; /* BAL core log group */
extern dev_log_id log_group_bal_sw_util; /* BAL switch utils log group */
extern dev_log_id log_group_bal_swext; /* BAL switch extensions log group */
extern dev_log_id log_group_bal_acl; /* BAL access control object log group */
extern dev_log_id log_group_bal_erps; /* BAL ERPS object log group */
extern dev_log_id log_group_bal_flow; /* BAL flow object log group */
extern dev_log_id log_group_bal_group; /* BAL group object log group */
extern dev_log_id log_group_bal_inband; /* BAL inband management object log group */
extern dev_log_id log_group_bal_mac_table; /* BAL L2 MAC table object log group */
extern dev_log_id log_group_bal_lag; /* BAL LAG interface object log group */
extern dev_log_id log_group_bal_nni; /* BAL NNI interface object log group */
extern dev_log_id log_group_bal_policer; /* BAL policer object log group */
extern dev_log_id log_group_bal_protection; /* BAL protection interface object log group */
extern dev_log_id log_group_bal_sw_inni; /* BAL switch INNI object log group */
extern dev_log_id log_group_bal_tm_qmp; /* BAL TM QMP object log group */
extern dev_log_id log_group_bal_tm_queue; /* BAL TM queue object log group */
extern dev_log_id log_group_bal_tm_sched; /* BAL TM sched object log group */
extern dev_log_id log_group_bal_mac_util; /* BAL MAC utils log group */
extern dev_log_id log_group_user_appl; /* top-level user appl log group */
extern dev_log_id log_group_user_appl_itu; /* ITU user applications */
extern dev_log_id log_group_user_appl_ieee; /* IEEE user applications */
extern dev_log_id log_group_onu_mgmt; /* top-level ONU mgmt log group */

#endif

void bcmolt_host_dev_log_init(bcmolt_host_dev_log_flags flags);

#endif
