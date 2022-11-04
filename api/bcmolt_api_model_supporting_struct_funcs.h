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

#ifndef BCMOLT_API_MODEL_SUPPORTING_STRUCT_FUNCS_H_
#define BCMOLT_API_MODEL_SUPPORTING_STRUCT_FUNCS_H_

#include <bcmos_system.h>
#include <bcmolt_buf.h>
#include <bcmolt_string.h>
#include <bcmolt_system_types.h>
#include "bcmolt_api_model_internal.h"
#include "bcmolt_api_model_supporting_structs.h"

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_intf_ref_set_default(bcmolt_intf_ref *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_intf_ref_validate(const bcmolt_intf_ref *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_fwd_action_set_default(bcmolt_access_control_fwd_action *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_fwd_action_validate(const bcmolt_access_control_fwd_action *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_pkt_modifier_set_default(bcmolt_access_control_pkt_modifier *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_pkt_modifier_validate(const bcmolt_access_control_pkt_modifier *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_action_set_default(bcmolt_action *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_action_validate(const bcmolt_action *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bin_str_16_set_default(bcmolt_bin_str_16 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bin_str_16_validate(const bcmolt_bin_str_16 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_aes_key_set_default(bcmolt_aes_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_aes_key_validate(const bcmolt_aes_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_aes_key_2_set_default(bcmolt_arr_aes_key_2 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_aes_key_2_validate(const bcmolt_arr_aes_key_2 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_calibration_record_8_set_default(bcmolt_arr_calibration_record_8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_calibration_record_8_validate(const bcmolt_arr_calibration_record_8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ds_frequency_offset_set_default(bcmolt_ds_frequency_offset *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ds_frequency_offset_validate(const bcmolt_ds_frequency_offset *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_id_set_default(bcmolt_pon_id *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_id_validate(const bcmolt_pon_id *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_channel_profile_set_default(bcmolt_channel_profile *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_channel_profile_validate(const bcmolt_channel_profile *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_channel_profile_8_set_default(bcmolt_arr_channel_profile_8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_channel_profile_8_validate(const bcmolt_arr_channel_profile_8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_intf_ref_16_set_default(bcmolt_arr_intf_ref_16 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_intf_ref_16_validate(const bcmolt_arr_intf_ref_16 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_link_state_8_set_default(bcmolt_arr_link_state_8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_link_state_8_validate(const bcmolt_arr_link_state_8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_nni_id_8_set_default(bcmolt_arr_nni_id_8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_nni_id_8_validate(const bcmolt_arr_nni_id_8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ploam_filter_set_default(bcmolt_ploam_filter *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ploam_filter_validate(const bcmolt_ploam_filter *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_ploam_filter_5_set_default(bcmolt_arr_ploam_filter_5 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_ploam_filter_5_validate(const bcmolt_arr_ploam_filter_5 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_policer_ref_set_default(bcmolt_policer_ref *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_policer_ref_validate(const bcmolt_policer_ref *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_policer_ref_4_set_default(bcmolt_arr_policer_ref_4 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_policer_ref_4_validate(const bcmolt_arr_policer_ref_4 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_power_consumption_channel_report_set_default(bcmolt_power_consumption_channel_report *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_power_consumption_channel_report_validate(const bcmolt_power_consumption_channel_report *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_power_consumption_channel_report_8_set_default(bcmolt_arr_power_consumption_channel_report_8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_power_consumption_channel_report_8_validate(const bcmolt_arr_power_consumption_channel_report_8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_queue_ref_set_default(bcmolt_tm_queue_ref *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_queue_ref_validate(const bcmolt_tm_queue_ref *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_tm_queue_ref_8_set_default(bcmolt_arr_tm_queue_ref_8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_tm_queue_ref_8_validate(const bcmolt_arr_tm_queue_ref_8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_u16_2_set_default(bcmolt_arr_u16_2 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_u16_2_validate(const bcmolt_arr_u16_2 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_u64_4_set_default(bcmolt_arr_u64_4 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_u64_4_validate(const bcmolt_arr_u64_4 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_u8_20_set_default(bcmolt_arr_u8_20 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_u8_20_validate(const bcmolt_arr_u8_20 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_u8_8_set_default(bcmolt_arr_u8_8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_u8_8_validate(const bcmolt_arr_u8_8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_burst_profile_set_default(bcmolt_xgpon_burst_profile *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_burst_profile_validate(const bcmolt_xgpon_burst_profile *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_arr_xgpon_burst_profile_4_set_default(bcmolt_arr_xgpon_burst_profile_4 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_arr_xgpon_burst_profile_4_validate(const bcmolt_arr_xgpon_burst_profile_4 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_automatic_onu_deactivation_set_default(bcmolt_automatic_onu_deactivation *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_automatic_onu_deactivation_validate(const bcmolt_automatic_onu_deactivation *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ber_monitor_params_set_default(bcmolt_ber_monitor_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ber_monitor_params_validate(const bcmolt_ber_monitor_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bin_str_set_default(bcmolt_bin_str *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bin_str_validate(const bcmolt_bin_str *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bin_str_10_set_default(bcmolt_bin_str_10 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bin_str_10_validate(const bcmolt_bin_str_10 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bin_str_13_set_default(bcmolt_bin_str_13 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bin_str_13_validate(const bcmolt_bin_str_13 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bin_str_36_set_default(bcmolt_bin_str_36 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bin_str_36_validate(const bcmolt_bin_str_36 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bin_str_4_set_default(bcmolt_bin_str_4 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bin_str_4_validate(const bcmolt_bin_str_4 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bin_str_40_set_default(bcmolt_bin_str_40 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bin_str_40_validate(const bcmolt_bin_str_40 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bin_str_48_set_default(bcmolt_bin_str_48 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bin_str_48_validate(const bcmolt_bin_str_48 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bin_str_8_set_default(bcmolt_bin_str_8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bin_str_8_validate(const bcmolt_bin_str_8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_cbr_rt_allocation_profile_set_default(bcmolt_cbr_rt_allocation_profile *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_cbr_rt_allocation_profile_validate(const bcmolt_cbr_rt_allocation_profile *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_layer_4_port_range_set_default(bcmolt_layer_4_port_range *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_layer_4_port_range_validate(const bcmolt_layer_4_port_range *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_classifier_ip_v_6_set_default(bcmolt_classifier_ip_v_6 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_classifier_ip_v_6_validate(const bcmolt_classifier_ip_v_6 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_classifier_set_default(bcmolt_classifier *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_classifier_validate(const bcmolt_classifier *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ddr_test_completed_set_default(bcmolt_ddr_test_completed *obj);

/** Initializes a union substructure to default values for a given type.
 *
 * \param obj Pointer to the structure to initialize.
 * \param type Union type to initialize.
 */
void bcmolt_ddr_test_completed_set_union_default(bcmolt_ddr_test_completed *obj, bcmolt_ddr_test_status type);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ddr_test_completed_validate(const bcmolt_ddr_test_completed *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_debug_device_cfg_set_default(bcmolt_debug_device_cfg *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_debug_device_cfg_validate(const bcmolt_debug_device_cfg *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_debug_flow_config_set_default(bcmolt_debug_flow_config *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_debug_flow_config_validate(const bcmolt_debug_flow_config *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_sched_ref_set_default(bcmolt_tm_sched_ref *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_sched_ref_validate(const bcmolt_tm_sched_ref *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_egress_qos_set_default(bcmolt_egress_qos *obj);

/** Initializes a union substructure to default values for a given type.
 *
 * \param obj Pointer to the structure to initialize.
 * \param type Union type to initialize.
 */
void bcmolt_egress_qos_set_union_default(bcmolt_egress_qos *obj, bcmolt_egress_qos_type type);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_egress_qos_validate(const bcmolt_egress_qos *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_str_64_set_default(bcmolt_str_64 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_str_64_validate(const bcmolt_str_64 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_embedded_image_entry_set_default(bcmolt_embedded_image_entry *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_embedded_image_entry_validate(const bcmolt_embedded_image_entry *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_embedded_image_entry_list_u8_max_4_set_default(bcmolt_embedded_image_entry_list_u8_max_4 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_embedded_image_entry_list_u8_max_4_validate(const bcmolt_embedded_image_entry_list_u8_max_4 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_intf_ref_set_default(bcmolt_erps_intf_ref *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_intf_ref_validate(const bcmolt_erps_intf_ref *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_extended_dba_priority_adjustment_set_default(bcmolt_extended_dba_priority_adjustment *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_extended_dba_priority_adjustment_validate(const bcmolt_extended_dba_priority_adjustment *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_str_32_set_default(bcmolt_str_32 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_str_32_validate(const bcmolt_str_32 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_firmware_sw_version_set_default(bcmolt_firmware_sw_version *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_firmware_sw_version_validate(const bcmolt_firmware_sw_version *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_intf_ref_set_default(bcmolt_flow_intf_ref *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_intf_ref_validate(const bcmolt_flow_intf_ref *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gem_port_configuration_set_default(bcmolt_gem_port_configuration *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gem_port_configuration_validate(const bcmolt_gem_port_configuration *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gem_port_id_list_u8_max_16_set_default(bcmolt_gem_port_id_list_u8_max_16 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gem_port_id_list_u8_max_16_validate(const bcmolt_gem_port_id_list_u8_max_16 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gpon_onu_alarm_state_set_default(bcmolt_gpon_onu_alarm_state *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gpon_onu_alarm_state_validate(const bcmolt_gpon_onu_alarm_state *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gpon_onu_alarms_set_default(bcmolt_gpon_onu_alarms *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gpon_onu_alarms_validate(const bcmolt_gpon_onu_alarms *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gpon_onu_alarms_thresholds_set_default(bcmolt_gpon_onu_alarms_thresholds *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gpon_onu_alarms_thresholds_validate(const bcmolt_gpon_onu_alarms_thresholds *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gpon_onu_params_set_default(bcmolt_gpon_onu_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gpon_onu_params_validate(const bcmolt_gpon_onu_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_power_level_set_default(bcmolt_pon_power_level *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_power_level_validate(const bcmolt_pon_power_level *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gpon_pon_params_set_default(bcmolt_gpon_pon_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gpon_pon_params_validate(const bcmolt_gpon_pon_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gpon_trx_set_default(bcmolt_gpon_trx *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gpon_trx_validate(const bcmolt_gpon_trx *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_group_member_info_set_default(bcmolt_group_member_info *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_group_member_info_validate(const bcmolt_group_member_info *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_group_member_info_list_u8_set_default(bcmolt_group_member_info_list_u8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_group_member_info_list_u8_validate(const bcmolt_group_member_info_list_u8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_group_members_update_command_set_default(bcmolt_group_members_update_command *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_group_members_update_command_validate(const bcmolt_group_members_update_command *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_host_port_params_set_default(bcmolt_host_port_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_host_port_params_validate(const bcmolt_host_port_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_host_sw_version_set_default(bcmolt_host_sw_version *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_host_sw_version_validate(const bcmolt_host_sw_version *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_hw_pon_id_set_default(bcmolt_hw_pon_id *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_hw_pon_id_validate(const bcmolt_hw_pon_id *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_str_256_set_default(bcmolt_str_256 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_str_256_validate(const bcmolt_str_256 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ieee_8021_as_tod_set_default(bcmolt_ieee_8021_as_tod *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ieee_8021_as_tod_validate(const bcmolt_ieee_8021_as_tod *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_inband_config_data_set_default(bcmolt_inband_config_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_inband_config_data_validate(const bcmolt_inband_config_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_inband_conn_data_set_default(bcmolt_inband_conn_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_inband_conn_data_validate(const bcmolt_inband_conn_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_indication_shaping_set_default(bcmolt_indication_shaping *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_indication_shaping_validate(const bcmolt_indication_shaping *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_inni_config_set_default(bcmolt_inni_config *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_inni_config_validate(const bcmolt_inni_config *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_intf_ref_list_u8_set_default(bcmolt_intf_ref_list_u8 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_intf_ref_list_u8_validate(const bcmolt_intf_ref_list_u8 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_serial_number_set_default(bcmolt_serial_number *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_serial_number_validate(const bcmolt_serial_number *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_onu_aes_key_set_default(bcmolt_itupon_onu_aes_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_onu_aes_key_validate(const bcmolt_itupon_onu_aes_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_onu_alarm_state_set_default(bcmolt_xgpon_onu_alarm_state *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_onu_alarm_state_validate(const bcmolt_xgpon_onu_alarm_state *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_ps_type_w_set_default(bcmolt_onu_ps_type_w *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_ps_type_w_validate(const bcmolt_onu_ps_type_w *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ngpon2_onu_params_set_default(bcmolt_ngpon2_onu_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ngpon2_onu_params_validate(const bcmolt_ngpon2_onu_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_onu_registration_keys_set_default(bcmolt_xgpon_onu_registration_keys *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_onu_registration_keys_validate(const bcmolt_xgpon_onu_registration_keys *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_request_registration_status_set_default(bcmolt_request_registration_status *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_request_registration_status_validate(const bcmolt_request_registration_status *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_onu_params_set_default(bcmolt_xgpon_onu_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_onu_params_validate(const bcmolt_xgpon_onu_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itu_onu_params_set_default(bcmolt_itu_onu_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itu_onu_params_validate(const bcmolt_itu_onu_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_available_bandwidth_set_default(bcmolt_pon_available_bandwidth *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_available_bandwidth_validate(const bcmolt_pon_available_bandwidth *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_drift_control_set_default(bcmolt_pon_drift_control *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_drift_control_validate(const bcmolt_pon_drift_control *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_activation_set_default(bcmolt_onu_activation *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_activation_validate(const bcmolt_onu_activation *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_key_exchange_set_default(bcmolt_key_exchange *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_key_exchange_validate(const bcmolt_key_exchange *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_power_management_configuration_set_default(bcmolt_onu_power_management_configuration *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_power_management_configuration_validate(const bcmolt_onu_power_management_configuration *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_periodic_standby_pon_monitoring_set_default(bcmolt_periodic_standby_pon_monitoring *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_periodic_standby_pon_monitoring_validate(const bcmolt_periodic_standby_pon_monitoring *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_prbs_checker_config_set_default(bcmolt_prbs_checker_config *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_prbs_checker_config_validate(const bcmolt_prbs_checker_config *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_prbs_generator_config_set_default(bcmolt_prbs_generator_config *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_prbs_generator_config_validate(const bcmolt_prbs_generator_config *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_prbs_status_set_default(bcmolt_prbs_status *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_prbs_status_validate(const bcmolt_prbs_status *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_protection_switching_set_default(bcmolt_itupon_protection_switching *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_protection_switching_validate(const bcmolt_itupon_protection_switching *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ituonu_upgrade_params_set_default(bcmolt_ituonu_upgrade_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ituonu_upgrade_params_validate(const bcmolt_ituonu_upgrade_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_upgrade_status_set_default(bcmolt_onu_upgrade_status *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_upgrade_status_validate(const bcmolt_onu_upgrade_status *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_upgrade_status_list_u32_max_128_set_default(bcmolt_onu_upgrade_status_list_u32_max_128 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_upgrade_status_list_u32_max_128_validate(const bcmolt_onu_upgrade_status_list_u32_max_128 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_onu_upgrade_status_set_default(bcmolt_pon_onu_upgrade_status *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_onu_upgrade_status_validate(const bcmolt_pon_onu_upgrade_status *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_onu_alarms_thresholds_set_default(bcmolt_xgpon_onu_alarms_thresholds *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_onu_alarms_thresholds_validate(const bcmolt_xgpon_onu_alarms_thresholds *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_onu_alarm_indication_control_set_default(bcmolt_xgpon_onu_alarm_indication_control *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_onu_alarm_indication_control_validate(const bcmolt_xgpon_onu_alarm_indication_control *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_multicast_key_set_default(bcmolt_xgpon_multicast_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_multicast_key_validate(const bcmolt_xgpon_multicast_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_tuning_configuration_set_default(bcmolt_onu_tuning_configuration *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_tuning_configuration_validate(const bcmolt_onu_tuning_configuration *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ngpon2_pon_params_set_default(bcmolt_ngpon2_pon_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ngpon2_pon_params_validate(const bcmolt_ngpon2_pon_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ploam_retransmission_set_default(bcmolt_ploam_retransmission *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ploam_retransmission_validate(const bcmolt_ploam_retransmission *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_operation_control_set_default(bcmolt_operation_control *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_operation_control_validate(const bcmolt_operation_control *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_periodic_ploams_set_default(bcmolt_periodic_ploams *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_periodic_ploams_validate(const bcmolt_periodic_ploams *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_pon_params_set_default(bcmolt_xgpon_pon_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_pon_params_validate(const bcmolt_xgpon_pon_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_dba_set_default(bcmolt_itupon_dba *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_dba_validate(const bcmolt_itupon_dba *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itu_pon_params_set_default(bcmolt_itu_pon_params *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itu_pon_params_validate(const bcmolt_itu_pon_params *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itu_tod_set_default(bcmolt_itu_tod *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itu_tod_validate(const bcmolt_itu_tod *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_onu_eqd_set_default(bcmolt_itupon_onu_eqd *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_onu_eqd_validate(const bcmolt_itupon_onu_eqd *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_onu_eqd_list_u32_set_default(bcmolt_itupon_onu_eqd_list_u32 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_onu_eqd_list_u32_validate(const bcmolt_itupon_onu_eqd_list_u32 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_global_parms_set_default(bcmolt_lag_global_parms *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_global_parms_validate(const bcmolt_lag_global_parms *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_members_update_command_set_default(bcmolt_lag_interface_members_update_command *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_members_update_command_validate(const bcmolt_lag_interface_members_update_command *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_local_mep_set_default(bcmolt_local_mep *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_local_mep_validate(const bcmolt_local_mep *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_log_level_msg_count_set_default(bcmolt_log_level_msg_count *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_log_level_msg_count_validate(const bcmolt_log_level_msg_count *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_log_level_per_file_set_default(bcmolt_log_level_per_file *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_log_level_per_file_validate(const bcmolt_log_level_per_file *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_str_48_set_default(bcmolt_str_48 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_str_48_validate(const bcmolt_str_48 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_meg_cfg_set_default(bcmolt_meg_cfg *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_meg_cfg_validate(const bcmolt_meg_cfg *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_mirror_action_set_default(bcmolt_mirror_action *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_mirror_action_validate(const bcmolt_mirror_action *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_link_status_set_default(bcmolt_nni_link_status *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_link_status_validate(const bcmolt_nni_link_status *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_id_list_u32_set_default(bcmolt_onu_id_list_u32 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_id_list_u32_validate(const bcmolt_onu_id_list_u32 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pcie_conn_data_set_default(bcmolt_pcie_conn_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pcie_conn_data_validate(const bcmolt_pcie_conn_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_policer_action_set_default(bcmolt_policer_action *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_policer_action_validate(const bcmolt_policer_action *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_alloc_sla_set_default(bcmolt_pon_alloc_sla *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_alloc_sla_validate(const bcmolt_pon_alloc_sla *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_distance_set_default(bcmolt_pon_distance *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_distance_validate(const bcmolt_pon_distance *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_protection_type_set_default(bcmolt_protection_type *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_protection_type_validate(const bcmolt_protection_type *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_remote_mep_set_default(bcmolt_remote_mep *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_remote_mep_validate(const bcmolt_remote_mep *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_rssi_measurement_result_set_default(bcmolt_rssi_measurement_result *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_rssi_measurement_result_validate(const bcmolt_rssi_measurement_result *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_service_discovery_set_default(bcmolt_service_discovery *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_service_discovery_validate(const bcmolt_service_discovery *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_stat_alarm_trigger_config_set_default(bcmolt_stat_alarm_trigger_config *obj);

/** Initializes a union substructure to default values for a given type.
 *
 * \param obj Pointer to the structure to initialize.
 * \param type Union type to initialize.
 */
void bcmolt_stat_alarm_trigger_config_set_union_default(bcmolt_stat_alarm_trigger_config *obj, bcmolt_stat_condition_type type);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_stat_alarm_trigger_config_validate(const bcmolt_stat_alarm_trigger_config *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_stat_alarm_soak_config_set_default(bcmolt_stat_alarm_soak_config *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_stat_alarm_soak_config_validate(const bcmolt_stat_alarm_soak_config *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_stat_alarm_config_set_default(bcmolt_stat_alarm_config *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_stat_alarm_config_validate(const bcmolt_stat_alarm_config *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_str_100_set_default(bcmolt_str_100 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_str_100_validate(const bcmolt_str_100 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_str_16_set_default(bcmolt_str_16 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_str_16_validate(const bcmolt_str_16 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_str_2000_set_default(bcmolt_str_2000 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_str_2000_validate(const bcmolt_str_2000 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_str_2048_set_default(bcmolt_str_2048 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_str_2048_validate(const bcmolt_str_2048 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_sw_error_set_default(bcmolt_sw_error *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_sw_error_validate(const bcmolt_sw_error *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_system_profile_set_default(bcmolt_system_profile *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_system_profile_validate(const bcmolt_system_profile *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_sched_param_set_default(bcmolt_tm_sched_param *obj);

/** Initializes a union substructure to default values for a given type.
 *
 * \param obj Pointer to the structure to initialize.
 * \param type Union type to initialize.
 */
void bcmolt_tm_sched_param_set_union_default(bcmolt_tm_sched_param *obj, bcmolt_tm_sched_param_type type);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_sched_param_validate(const bcmolt_tm_sched_param *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_sched_attachment_point_set_default(bcmolt_tm_sched_attachment_point *obj);

/** Initializes a union substructure to default values for a given type.
 *
 * \param obj Pointer to the structure to initialize.
 * \param type Union type to initialize.
 */
void bcmolt_tm_sched_attachment_point_set_union_default(bcmolt_tm_sched_attachment_point *obj, bcmolt_tm_sched_output_type type);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_sched_attachment_point_validate(const bcmolt_tm_sched_attachment_point *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_shaping_set_default(bcmolt_tm_shaping *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_shaping_validate(const bcmolt_tm_shaping *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_topology_map_set_default(bcmolt_topology_map *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_topology_map_validate(const bcmolt_topology_map *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_topology_map_list_u32_set_default(bcmolt_topology_map_list_u32 *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_topology_map_list_u32_validate(const bcmolt_topology_map_list_u32 *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_topology_set_default(bcmolt_topology *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_topology_validate(const bcmolt_topology *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_trap_config_set_default(bcmolt_trap_config *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_trap_config_validate(const bcmolt_trap_config *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_u64_list_u32_hex_set_default(bcmolt_u64_list_u32_hex *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_u64_list_u32_hex_validate(const bcmolt_u64_list_u32_hex *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_u8_list_u8_hex_set_default(bcmolt_u8_list_u8_hex *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_u8_list_u8_hex_validate(const bcmolt_u8_list_u8_hex *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_onu_alarms_set_default(bcmolt_xgpon_onu_alarms *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_onu_alarms_validate(const bcmolt_xgpon_onu_alarms *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_xgpon_trx_set_default(bcmolt_xgpon_trx *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_xgpon_trx_validate(const bcmolt_xgpon_trx *obj, bcmos_errno *err, bcmolt_string *err_details);




#endif
