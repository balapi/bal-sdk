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

#ifndef BCMOLT_API_MODEL_TAGS_H_
#define BCMOLT_API_MODEL_TAGS_H_

#include <bcmos_system.h>
#include <bcmolt_api_model_api_structs.h>

/** All object/field tags included in the API object model. */
typedef enum
{
    BCMOLT_TAG__NONE = 0,
    BCMOLT_TAG_DEVICE = 1ULL << 0,
    BCMOLT_TAG_GPON = 1ULL << 1,
    BCMOLT_TAG_NGPON2 = 1ULL << 2,
    BCMOLT_TAG_SYSTEM = 1ULL << 3,
    BCMOLT_TAG_XGPON = 1ULL << 4,
    BCMOLT_TAG_XGS = 1ULL << 5,
} bcmolt_tag;

/* The following config modes are enabled for this build (based on tags). */
#define BCMOLT_CONFIG_MODE_DEVICE 1
#define BCMOLT_CONFIG_MODE_GPON 1
#define BCMOLT_CONFIG_MODE_NGPON2 1
#define BCMOLT_CONFIG_MODE_SYSTEM 1
#define BCMOLT_CONFIG_MODE_XGPON 1
#define BCMOLT_CONFIG_MODE_XGS 1

/** Get all tags that are currently active for a given access_control based on system state. */
bcmolt_tag bcmolt_access_control_get_active_tags(bcmolt_oltid olt, const bcmolt_access_control_key *key);

/** Get all tags that are currently active for a given bal_system based on system state. */
bcmolt_tag bcmolt_bal_system_get_active_tags(bcmolt_oltid olt, const bcmolt_bal_system_key *key);

/** Get all tags that are currently active for a given device based on system state. */
bcmolt_tag bcmolt_device_get_active_tags(bcmolt_oltid olt, const bcmolt_device_key *key);

/** Get all tags that are currently active for a given erps_interface based on system state. */
bcmolt_tag bcmolt_erps_interface_get_active_tags(bcmolt_oltid olt, const bcmolt_erps_interface_key *key);

/** Get all tags that are currently active for a given eth_oam based on system state. */
bcmolt_tag bcmolt_eth_oam_get_active_tags(bcmolt_oltid olt, const bcmolt_eth_oam_key *key);

/** Get all tags that are currently active for a given flow based on system state. */
bcmolt_tag bcmolt_flow_get_active_tags(bcmolt_oltid olt, const bcmolt_flow_key *key);

/** Get all tags that are currently active for a given gpio based on system state. */
bcmolt_tag bcmolt_gpio_get_active_tags(bcmolt_oltid olt, const bcmolt_gpio_key *key);

/** Get all tags that are currently active for a given group based on system state. */
bcmolt_tag bcmolt_group_get_active_tags(bcmolt_oltid olt, const bcmolt_group_key *key);

/** Get all tags that are currently active for a given inband_mgmt_channel based on system state. */
bcmolt_tag bcmolt_inband_mgmt_channel_get_active_tags(bcmolt_oltid olt, const bcmolt_inband_mgmt_channel_key *key);

/** Get all tags that are currently active for a given internal_nni based on system state. */
bcmolt_tag bcmolt_internal_nni_get_active_tags(bcmolt_oltid olt, const bcmolt_internal_nni_key *key);

/** Get all tags that are currently active for a given itupon_alloc based on system state. */
bcmolt_tag bcmolt_itupon_alloc_get_active_tags(bcmolt_oltid olt, const bcmolt_itupon_alloc_key *key);

/** Get all tags that are currently active for a given itupon_gem based on system state. */
bcmolt_tag bcmolt_itupon_gem_get_active_tags(bcmolt_oltid olt, const bcmolt_itupon_gem_key *key);

/** Get all tags that are currently active for a given lag_interface based on system state. */
bcmolt_tag bcmolt_lag_interface_get_active_tags(bcmolt_oltid olt, const bcmolt_lag_interface_key *key);

/** Get all tags that are currently active for a given log based on system state. */
bcmolt_tag bcmolt_log_get_active_tags(bcmolt_oltid olt, const bcmolt_log_key *key);

/** Get all tags that are currently active for a given log_file based on system state. */
bcmolt_tag bcmolt_log_file_get_active_tags(bcmolt_oltid olt, const bcmolt_log_file_key *key);

/** Get all tags that are currently active for a given ngpon2_channel based on system state. */
bcmolt_tag bcmolt_ngpon2_channel_get_active_tags(bcmolt_oltid olt, const bcmolt_ngpon2_channel_key *key);

/** Get all tags that are currently active for a given nni_interface based on system state. */
bcmolt_tag bcmolt_nni_interface_get_active_tags(bcmolt_oltid olt, const bcmolt_nni_interface_key *key);

/** Get all tags that are currently active for a given olt based on system state. */
bcmolt_tag bcmolt_olt_get_active_tags(bcmolt_oltid olt, const bcmolt_olt_key *key);

/** Get all tags that are currently active for a given onu based on system state. */
bcmolt_tag bcmolt_onu_get_active_tags(bcmolt_oltid olt, const bcmolt_onu_key *key);

/** Get all tags that are currently active for a given pbit_to_tc based on system state. */
bcmolt_tag bcmolt_pbit_to_tc_get_active_tags(bcmolt_oltid olt, const bcmolt_pbit_to_tc_key *key);

/** Get all tags that are currently active for a given policer_profile based on system state. */
bcmolt_tag bcmolt_policer_profile_get_active_tags(bcmolt_oltid olt, const bcmolt_policer_profile_key *key);

/** Get all tags that are currently active for a given pon_interface based on system state. */
bcmolt_tag bcmolt_pon_interface_get_active_tags(bcmolt_oltid olt, const bcmolt_pon_interface_key *key);

/** Get all tags that are currently active for a given protection_interface based on system state. */
bcmolt_tag bcmolt_protection_interface_get_active_tags(bcmolt_oltid olt, const bcmolt_protection_interface_key *key);

/** Get all tags that are currently active for a given software_error based on system state. */
bcmolt_tag bcmolt_software_error_get_active_tags(bcmolt_oltid olt, const bcmolt_software_error_key *key);

/** Get all tags that are currently active for a given switch_inni based on system state. */
bcmolt_tag bcmolt_switch_inni_get_active_tags(bcmolt_oltid olt, const bcmolt_switch_inni_key *key);

/** Get all tags that are currently active for a given tc_to_queue based on system state. */
bcmolt_tag bcmolt_tc_to_queue_get_active_tags(bcmolt_oltid olt, const bcmolt_tc_to_queue_key *key);

/** Get all tags that are currently active for a given tm_qmp based on system state. */
bcmolt_tag bcmolt_tm_qmp_get_active_tags(bcmolt_oltid olt, const bcmolt_tm_qmp_key *key);

/** Get all tags that are currently active for a given tm_queue based on system state. */
bcmolt_tag bcmolt_tm_queue_get_active_tags(bcmolt_oltid olt, const bcmolt_tm_queue_key *key);

/** Get all tags that are currently active for a given tm_sched based on system state. */
bcmolt_tag bcmolt_tm_sched_get_active_tags(bcmolt_oltid olt, const bcmolt_tm_sched_key *key);



/**
 * Get the system mode for a device on an OLT
 *
 * @param olt user appl = goid, daemon = n/a, embedded = n/a
 * @param device user appl = odid, daemon = ldid, embedded = n/a
 *
 * @return bcmolt_system_mode for device on OLT
 */
bcmolt_system_mode bcmolt_api_system_mode_get(bcmolt_oltid olt, bcmolt_devid device);

/**
 * Get tags associated with an API message
 *
 * @param dev user appl = goid, daemon = ldid, embedded = n/a
 * @param msg pointer to API message
 *
 * @return bcmolt_tags for API message
 */
bcmolt_tag bcmolt_api_msg_get_active_tags(bcmolt_devid dev, const bcmolt_msg *msg);

/**
 * Get tags associated with a device in the given system mode
 *
 * @param system_mode system mode of device
 * @param chip_family chip family of device
 *
 * @return bcmolt_tags for device
 */
bcmolt_tag bcmolt_dev_get_active_tags(bcmolt_system_mode system_mode, bcmolt_chip_family chip_family);

/**
 * Get tags associated with a PON NI in the given system mode
 *
 * @param pon_ni physical PON interface
 * @param chip_family chip family of device containing the PON NI
 * @param pon_type type of the PON NI (if any pon system mode)
 *
 * @return bcmolt_tags for PON NI
 */
bcmolt_tag bcmolt_pon_get_active_tags(
    bcmolt_pon_ni pon_ni,
    bcmolt_chip_family chip_family,
    bcmolt_pon_type pon_type);

/**
 * Get the PON type for a PON NI
 *
 * @param olt_id OLT ID
 * @param pon_ni PON NI
 *
 * @return bcmolt_pon_type for PON NI
 */
bcmolt_pon_type bcmolt_pon_get_type(bcmolt_oltid olt_id, bcmolt_pon_ni pon_ni);

#endif
