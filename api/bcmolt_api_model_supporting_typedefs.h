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

#ifndef BCMOLT_API_MODEL_SUPPORTING_TYPEDEFS_H_
#define BCMOLT_API_MODEL_SUPPORTING_TYPEDEFS_H_

#include <bcmos_system.h>

/** \addtogroup object_model
 * @{
 */

/** bcmolt_access_control_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_access_control_id;
#define BCMOLT_ACCESS_CONTROL_ID_MIN ((bcmolt_access_control_id)0)
#define BCMOLT_ACCESS_CONTROL_ID_MAX ((bcmolt_access_control_id)6399)

/** bcmolt_bal_system_id: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_bal_system_id;
#define BCMOLT_BAL_SYSTEM_ID_MIN ((bcmolt_bal_system_id)0)
#define BCMOLT_BAL_SYSTEM_ID_MAX ((bcmolt_bal_system_id)0)

/** bcmolt_ber_interval: Typed alias for a 32-bit unsigned integer. */
typedef uint32_t bcmolt_ber_interval;
#define BCMOLT_BER_INTERVAL_BER_INTERVAL_NOT_CONFIGURED ((bcmolt_ber_interval)0)

/** bcmolt_burst_profile_index: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_burst_profile_index;
#define BCMOLT_BURST_PROFILE_INDEX_MIN ((bcmolt_burst_profile_index)0)
#define BCMOLT_BURST_PROFILE_INDEX_MAX ((bcmolt_burst_profile_index)3)

/** bcmolt_cookie: Typed alias for a 64-bit unsigned integer. */
typedef uint64_t bcmolt_cookie;

/** bcmolt_erps_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_erps_id;
#define BCMOLT_ERPS_ID_UNASSIGNED ((bcmolt_erps_id)65535U)
#define BCMOLT_ERPS_ID_MIN ((bcmolt_erps_id)0)
#define BCMOLT_ERPS_ID_MAX ((bcmolt_erps_id)4096)

/** bcmolt_eth_oam_id: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_eth_oam_id;
#define BCMOLT_ETH_OAM_ID_UNASSIGNED ((bcmolt_eth_oam_id)0)
#define BCMOLT_ETH_OAM_ID_MIN ((bcmolt_eth_oam_id)0)
#define BCMOLT_ETH_OAM_ID_MAX ((bcmolt_eth_oam_id)127)

/** bcmolt_group_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_group_id;
#define BCMOLT_GROUP_ID_INVALID ((bcmolt_group_id)65535U)

/** bcmolt_inband_mgmt_instance_id: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_inband_mgmt_instance_id;
#define BCMOLT_INBAND_MGMT_INSTANCE_ID_MIN ((bcmolt_inband_mgmt_instance_id)0)
#define BCMOLT_INBAND_MGMT_INSTANCE_ID_MAX ((bcmolt_inband_mgmt_instance_id)255)

/** bcmolt_interface_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_interface_id;
#define BCMOLT_INTERFACE_ID_INVALID ((bcmolt_interface_id)65535U)
#define BCMOLT_INTERFACE_ID_MIN ((bcmolt_interface_id)0)

/** bcmolt_l2_mac_table_id: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_l2_mac_table_id;
#define BCMOLT_L2_MAC_TABLE_ID_MIN ((bcmolt_l2_mac_table_id)0)
#define BCMOLT_L2_MAC_TABLE_ID_MAX ((bcmolt_l2_mac_table_id)0)

/** bcmolt_lag_interface_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_lag_interface_id;
#define BCMOLT_LAG_INTERFACE_ID_UNASSIGNED ((bcmolt_lag_interface_id)65535U)
#define BCMOLT_LAG_INTERFACE_ID_MIN ((bcmolt_lag_interface_id)0)
#define BCMOLT_LAG_INTERFACE_ID_MAX ((bcmolt_lag_interface_id)31)

/** bcmolt_mep_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_mep_id;
#define BCMOLT_MEP_ID_UNASSIGNED ((bcmolt_mep_id)65535U)
#define BCMOLT_MEP_ID_MAX ((bcmolt_mep_id)8192)
#define BCMOLT_MEP_ID_MIN ((bcmolt_mep_id)0)

/** bcmolt_mtu: Typed alias for a 32-bit unsigned integer. */
typedef uint32_t bcmolt_mtu;
#define BCMOLT_MTU_MIN ((bcmolt_mtu)4096)
#define BCMOLT_MTU_MAX ((bcmolt_mtu)16384)

/** bcmolt_policer_profile_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_policer_profile_id;
#define BCMOLT_POLICER_PROFILE_ID_UNASSIGNED ((bcmolt_policer_profile_id)65535U)
#define BCMOLT_POLICER_PROFILE_ID_MIN ((bcmolt_policer_profile_id)1)
#define BCMOLT_POLICER_PROFILE_ID_MAX ((bcmolt_policer_profile_id)1023)

/** bcmolt_protection_interface_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_protection_interface_id;
#define BCMOLT_PROTECTION_INTERFACE_ID_UNASSIGNED ((bcmolt_protection_interface_id)65535U)
#define BCMOLT_PROTECTION_INTERFACE_ID_MIN ((bcmolt_protection_interface_id)0)
#define BCMOLT_PROTECTION_INTERFACE_ID_MAX ((bcmolt_protection_interface_id)63)

/** bcmolt_service_port_id: Typed alias for a 32-bit unsigned integer. */
typedef uint32_t bcmolt_service_port_id;
#define BCMOLT_SERVICE_PORT_ID_INVALID ((bcmolt_service_port_id)65535UL)
#define BCMOLT_SERVICE_PORT_ID_NEXT_FREE ((bcmolt_service_port_id)65536UL)
#define BCMOLT_SERVICE_PORT_ID_MIN ((bcmolt_service_port_id)0)
#define BCMOLT_SERVICE_PORT_ID_MAX ((bcmolt_service_port_id)65536UL)

/** bcmolt_switch_inni_id: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_switch_inni_id;
#define BCMOLT_SWITCH_INNI_ID_INVALID ((bcmolt_switch_inni_id)255)

/** bcmolt_time_quanta: Typed alias for a 32-bit unsigned integer. */
typedef uint32_t bcmolt_time_quanta;

/** bcmolt_tm_priority: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_tm_priority;
#define BCMOLT_TM_PRIORITY_MIN ((bcmolt_tm_priority)0)

/** bcmolt_tm_qmp_id: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_tm_qmp_id;
#define BCMOLT_TM_QMP_ID_UNASSIGNED ((bcmolt_tm_qmp_id)255)
#define BCMOLT_TM_QMP_ID_MIN ((bcmolt_tm_qmp_id)0)
#define BCMOLT_TM_QMP_ID_MAX ((bcmolt_tm_qmp_id)15)

/** bcmolt_tm_queue_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_tm_queue_id;
#define BCMOLT_TM_QUEUE_ID_UNASSIGNED ((bcmolt_tm_queue_id)65535U)

/** bcmolt_tm_queue_profile_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_tm_queue_profile_id;
#define BCMOLT_TM_QUEUE_PROFILE_ID_UNASSIGNED ((bcmolt_tm_queue_profile_id)65535U)
#define BCMOLT_TM_QUEUE_PROFILE_ID_RESERVED_DEFAULT ((bcmolt_tm_queue_profile_id)0)
#define BCMOLT_TM_QUEUE_PROFILE_ID_RESERVED_CPU ((bcmolt_tm_queue_profile_id)63)
#define BCMOLT_TM_QUEUE_PROFILE_ID_MIN ((bcmolt_tm_queue_profile_id)0)
#define BCMOLT_TM_QUEUE_PROFILE_ID_MAX ((bcmolt_tm_queue_profile_id)63)

/** bcmolt_tm_queue_set_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_tm_queue_set_id;
#define BCMOLT_TM_QUEUE_SET_ID_QSET_NOT_USE ((bcmolt_tm_queue_set_id)32768U)
#define BCMOLT_TM_QUEUE_SET_ID_MIN ((bcmolt_tm_queue_set_id)0)
#define BCMOLT_TM_QUEUE_SET_ID_MAX ((bcmolt_tm_queue_set_id)65535U)

/** bcmolt_tm_sched_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_tm_sched_id;
#define BCMOLT_TM_SCHED_ID_UNKNOWN ((bcmolt_tm_sched_id)65535U)

/** bcmolt_tm_weight: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_tm_weight;
#define BCMOLT_TM_WEIGHT_MAX_WEIGHT ((bcmolt_tm_weight)63)
#define BCMOLT_TM_WEIGHT_MIN ((bcmolt_tm_weight)1)



/** @} */

#endif
