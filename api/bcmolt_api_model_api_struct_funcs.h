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

#ifndef BCMOLT_API_MODEL_API_STRUCT_FUNCS_H_
#define BCMOLT_API_MODEL_API_STRUCT_FUNCS_H_

#include <bcmos_system.h>
#include <bcmolt_buf.h>
#include <bcmolt_string.h>
#include <bcmolt_system_types.h>
#include "bcmolt_api_model_internal.h"
#include "bcmolt_api_model_api_structs.h"

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_key_set_default(bcmolt_access_control_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_key_validate(const bcmolt_access_control_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_cfg_data_set_default(bcmolt_access_control_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_cfg_data_validate(const bcmolt_access_control_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_access_control_multi_cfg_get_packed_length(const bcmolt_access_control_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_access_control_multi_cfg_pack(const bcmolt_access_control_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_access_control_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_access_control_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_stats_data_set_default(bcmolt_access_control_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_stats_data_validate(const bcmolt_access_control_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_access_control_multi_stats_get_packed_length(const bcmolt_access_control_multi_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_access_control_multi_stats_pack(const bcmolt_access_control_multi_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_access_control_multi_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_access_control_multi_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_receive_eth_packet_data_set_default(bcmolt_access_control_receive_eth_packet_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_receive_eth_packet_data_validate(const bcmolt_access_control_receive_eth_packet_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_interfaces_update_data_set_default(bcmolt_access_control_interfaces_update_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_interfaces_update_data_validate(const bcmolt_access_control_interfaces_update_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_stats_cfg_data_set_default(bcmolt_access_control_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_stats_cfg_data_validate(const bcmolt_access_control_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_stats_alarm_raised_data_set_default(bcmolt_access_control_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_stats_alarm_raised_data_validate(const bcmolt_access_control_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_stats_alarm_cleared_data_set_default(bcmolt_access_control_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_stats_alarm_cleared_data_validate(const bcmolt_access_control_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_access_control_auto_cfg_data_set_default(bcmolt_access_control_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_access_control_auto_cfg_data_validate(const bcmolt_access_control_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bal_system_cfg_data_set_default(bcmolt_bal_system_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bal_system_cfg_data_validate(const bcmolt_bal_system_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_bal_system_multi_cfg_get_packed_length(const bcmolt_bal_system_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_bal_system_multi_cfg_pack(const bcmolt_bal_system_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_bal_system_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_bal_system_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_bal_system_key_set_default(bcmolt_bal_system_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_bal_system_key_validate(const bcmolt_bal_system_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_key_set_default(bcmolt_device_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_key_validate(const bcmolt_device_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_cfg_data_set_default(bcmolt_device_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_cfg_data_validate(const bcmolt_device_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_device_multi_cfg_get_packed_length(const bcmolt_device_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_device_multi_cfg_pack(const bcmolt_device_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_device_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_device_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_connect_data_set_default(bcmolt_device_connect_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_connect_data_validate(const bcmolt_device_connect_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_host_keep_alive_data_set_default(bcmolt_device_host_keep_alive_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_host_keep_alive_data_validate(const bcmolt_device_host_keep_alive_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_set_8021_as_tod_string_data_set_default(bcmolt_device_set_8021_as_tod_string_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_set_8021_as_tod_string_data_validate(const bcmolt_device_set_8021_as_tod_string_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_image_transfer_start_data_set_default(bcmolt_device_image_transfer_start_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_image_transfer_start_data_validate(const bcmolt_device_image_transfer_start_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_image_transfer_data_data_set_default(bcmolt_device_image_transfer_data_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_image_transfer_data_data_validate(const bcmolt_device_image_transfer_data_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_run_ddr_test_data_set_default(bcmolt_device_run_ddr_test_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_run_ddr_test_data_validate(const bcmolt_device_run_ddr_test_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_device_ready_data_set_default(bcmolt_device_device_ready_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_device_ready_data_validate(const bcmolt_device_device_ready_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_device_keep_alive_data_set_default(bcmolt_device_device_keep_alive_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_device_keep_alive_data_validate(const bcmolt_device_device_keep_alive_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_connection_failure_data_set_default(bcmolt_device_connection_failure_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_connection_failure_data_validate(const bcmolt_device_connection_failure_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_connection_complete_data_set_default(bcmolt_device_connection_complete_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_connection_complete_data_validate(const bcmolt_device_connection_complete_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_disconnection_complete_data_set_default(bcmolt_device_disconnection_complete_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_disconnection_complete_data_validate(const bcmolt_device_disconnection_complete_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_sw_error_data_set_default(bcmolt_device_sw_error_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_sw_error_data_validate(const bcmolt_device_sw_error_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_sw_exception_data_set_default(bcmolt_device_sw_exception_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_sw_exception_data_validate(const bcmolt_device_sw_exception_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_image_transfer_complete_data_set_default(bcmolt_device_image_transfer_complete_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_image_transfer_complete_data_validate(const bcmolt_device_image_transfer_complete_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_ddr_test_complete_data_set_default(bcmolt_device_ddr_test_complete_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_ddr_test_complete_data_validate(const bcmolt_device_ddr_test_complete_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_sw_health_check_failure_data_set_default(bcmolt_device_sw_health_check_failure_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_sw_health_check_failure_data_validate(const bcmolt_device_sw_health_check_failure_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_change_inni_mux_data_set_default(bcmolt_device_change_inni_mux_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_change_inni_mux_data_validate(const bcmolt_device_change_inni_mux_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_inni_mux_configuration_completed_data_set_default(bcmolt_device_inni_mux_configuration_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_inni_mux_configuration_completed_data_validate(const bcmolt_device_inni_mux_configuration_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_tod_calibration_done_data_set_default(bcmolt_device_tod_calibration_done_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_tod_calibration_done_data_validate(const bcmolt_device_tod_calibration_done_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_device_auto_cfg_data_set_default(bcmolt_device_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_device_auto_cfg_data_validate(const bcmolt_device_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_interface_key_set_default(bcmolt_erps_interface_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_interface_key_validate(const bcmolt_erps_interface_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_interface_cfg_data_set_default(bcmolt_erps_interface_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_interface_cfg_data_validate(const bcmolt_erps_interface_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_erps_interface_multi_cfg_get_packed_length(const bcmolt_erps_interface_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_erps_interface_multi_cfg_pack(const bcmolt_erps_interface_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_erps_interface_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_erps_interface_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_interface_set_ring_port_control_data_set_default(bcmolt_erps_interface_set_ring_port_control_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_interface_set_ring_port_control_data_validate(const bcmolt_erps_interface_set_ring_port_control_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_interface_ring_port_control_data_set_default(bcmolt_erps_interface_ring_port_control_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_interface_ring_port_control_data_validate(const bcmolt_erps_interface_ring_port_control_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_interface_set_intf_opt_data_set_default(bcmolt_erps_interface_set_intf_opt_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_interface_set_intf_opt_data_validate(const bcmolt_erps_interface_set_intf_opt_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_interface_port_update_data_set_default(bcmolt_erps_interface_port_update_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_interface_port_update_data_validate(const bcmolt_erps_interface_port_update_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_interface_set_intf_opt_complete_data_set_default(bcmolt_erps_interface_set_intf_opt_complete_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_interface_set_intf_opt_complete_data_validate(const bcmolt_erps_interface_set_intf_opt_complete_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_interface_port_update_complete_data_set_default(bcmolt_erps_interface_port_update_complete_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_interface_port_update_complete_data_validate(const bcmolt_erps_interface_port_update_complete_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_erps_interface_auto_cfg_data_set_default(bcmolt_erps_interface_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_erps_interface_auto_cfg_data_validate(const bcmolt_erps_interface_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_key_set_default(bcmolt_eth_oam_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_key_validate(const bcmolt_eth_oam_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_cfg_data_set_default(bcmolt_eth_oam_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_cfg_data_validate(const bcmolt_eth_oam_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_eth_oam_multi_cfg_get_packed_length(const bcmolt_eth_oam_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_eth_oam_multi_cfg_pack(const bcmolt_eth_oam_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_eth_oam_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_eth_oam_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_ccm_event_data_set_default(bcmolt_eth_oam_ccm_event_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_ccm_event_data_validate(const bcmolt_eth_oam_ccm_event_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_stats_data_set_default(bcmolt_eth_oam_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_stats_data_validate(const bcmolt_eth_oam_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_eth_oam_multi_stats_get_packed_length(const bcmolt_eth_oam_multi_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_eth_oam_multi_stats_pack(const bcmolt_eth_oam_multi_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_eth_oam_multi_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_eth_oam_multi_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_set_mep_state_data_set_default(bcmolt_eth_oam_set_mep_state_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_set_mep_state_data_validate(const bcmolt_eth_oam_set_mep_state_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_state_change_data_set_default(bcmolt_eth_oam_state_change_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_state_change_data_validate(const bcmolt_eth_oam_state_change_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_stats_cfg_data_set_default(bcmolt_eth_oam_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_stats_cfg_data_validate(const bcmolt_eth_oam_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_stats_alarm_raised_data_set_default(bcmolt_eth_oam_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_stats_alarm_raised_data_validate(const bcmolt_eth_oam_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_stats_alarm_cleared_data_set_default(bcmolt_eth_oam_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_stats_alarm_cleared_data_validate(const bcmolt_eth_oam_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_eth_oam_auto_cfg_data_set_default(bcmolt_eth_oam_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_eth_oam_auto_cfg_data_validate(const bcmolt_eth_oam_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_cfg_data_set_default(bcmolt_flow_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_cfg_data_validate(const bcmolt_flow_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_flow_multi_cfg_get_packed_length(const bcmolt_flow_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_flow_multi_cfg_pack(const bcmolt_flow_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_flow_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_flow_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_key_set_default(bcmolt_flow_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_key_validate(const bcmolt_flow_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_stats_data_set_default(bcmolt_flow_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_stats_data_validate(const bcmolt_flow_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_flow_multi_stats_get_packed_length(const bcmolt_flow_multi_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_flow_multi_stats_pack(const bcmolt_flow_multi_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_flow_multi_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_flow_multi_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_send_eth_packet_data_set_default(bcmolt_flow_send_eth_packet_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_send_eth_packet_data_validate(const bcmolt_flow_send_eth_packet_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_src_binding_update_data_set_default(bcmolt_flow_src_binding_update_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_src_binding_update_data_validate(const bcmolt_flow_src_binding_update_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_stats_cfg_data_set_default(bcmolt_flow_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_stats_cfg_data_validate(const bcmolt_flow_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_stats_alarm_raised_data_set_default(bcmolt_flow_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_stats_alarm_raised_data_validate(const bcmolt_flow_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_stats_alarm_cleared_data_set_default(bcmolt_flow_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_stats_alarm_cleared_data_validate(const bcmolt_flow_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_flow_auto_cfg_data_set_default(bcmolt_flow_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_flow_auto_cfg_data_validate(const bcmolt_flow_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gpio_key_set_default(bcmolt_gpio_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gpio_key_validate(const bcmolt_gpio_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_gpio_cfg_data_set_default(bcmolt_gpio_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_gpio_cfg_data_validate(const bcmolt_gpio_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_gpio_multi_cfg_get_packed_length(const bcmolt_gpio_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_gpio_multi_cfg_pack(const bcmolt_gpio_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_gpio_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_gpio_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_group_cfg_data_set_default(bcmolt_group_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_group_cfg_data_validate(const bcmolt_group_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_group_multi_cfg_get_packed_length(const bcmolt_group_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_group_multi_cfg_pack(const bcmolt_group_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_group_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_group_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_group_key_set_default(bcmolt_group_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_group_key_validate(const bcmolt_group_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_group_members_update_data_set_default(bcmolt_group_members_update_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_group_members_update_data_validate(const bcmolt_group_members_update_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_group_complete_members_update_data_set_default(bcmolt_group_complete_members_update_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_group_complete_members_update_data_validate(const bcmolt_group_complete_members_update_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_group_auto_cfg_data_set_default(bcmolt_group_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_group_auto_cfg_data_validate(const bcmolt_group_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_host_log_key_set_default(bcmolt_host_log_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_host_log_key_validate(const bcmolt_host_log_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_host_log_cfg_data_set_default(bcmolt_host_log_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_host_log_cfg_data_validate(const bcmolt_host_log_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_host_log_multi_cfg_get_packed_length(const bcmolt_host_log_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_host_log_multi_cfg_pack(const bcmolt_host_log_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_host_log_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_host_log_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_host_log_file_key_set_default(bcmolt_host_log_file_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_host_log_file_key_validate(const bcmolt_host_log_file_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_host_log_file_cfg_data_set_default(bcmolt_host_log_file_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_host_log_file_cfg_data_validate(const bcmolt_host_log_file_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_host_log_file_multi_cfg_get_packed_length(const bcmolt_host_log_file_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_host_log_file_multi_cfg_pack(const bcmolt_host_log_file_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_host_log_file_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_host_log_file_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_inband_mgmt_channel_cfg_data_set_default(bcmolt_inband_mgmt_channel_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_inband_mgmt_channel_cfg_data_validate(const bcmolt_inband_mgmt_channel_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_inband_mgmt_channel_multi_cfg_get_packed_length(const bcmolt_inband_mgmt_channel_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_inband_mgmt_channel_multi_cfg_pack(const bcmolt_inband_mgmt_channel_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_inband_mgmt_channel_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_inband_mgmt_channel_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_inband_mgmt_channel_key_set_default(bcmolt_inband_mgmt_channel_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_inband_mgmt_channel_key_validate(const bcmolt_inband_mgmt_channel_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_key_set_default(bcmolt_internal_nni_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_key_validate(const bcmolt_internal_nni_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_cfg_data_set_default(bcmolt_internal_nni_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_cfg_data_validate(const bcmolt_internal_nni_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_internal_nni_multi_cfg_get_packed_length(const bcmolt_internal_nni_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_internal_nni_multi_cfg_pack(const bcmolt_internal_nni_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_internal_nni_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_internal_nni_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_status_changed_data_set_default(bcmolt_internal_nni_status_changed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_status_changed_data_validate(const bcmolt_internal_nni_status_changed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_nni_stats_data_set_default(bcmolt_internal_nni_nni_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_nni_stats_data_validate(const bcmolt_internal_nni_nni_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_internal_nni_multi_nni_stats_get_packed_length(const bcmolt_internal_nni_multi_nni_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_internal_nni_multi_nni_stats_pack(const bcmolt_internal_nni_multi_nni_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_internal_nni_multi_nni_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_internal_nni_multi_nni_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_enet_stats_data_set_default(bcmolt_internal_nni_enet_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_enet_stats_data_validate(const bcmolt_internal_nni_enet_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_internal_nni_multi_enet_stats_get_packed_length(const bcmolt_internal_nni_multi_enet_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_internal_nni_multi_enet_stats_pack(const bcmolt_internal_nni_multi_enet_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_internal_nni_multi_enet_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_internal_nni_multi_enet_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_packet_captured_data_set_default(bcmolt_internal_nni_packet_captured_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_packet_captured_data_validate(const bcmolt_internal_nni_packet_captured_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_send_eth_packet_data_set_default(bcmolt_internal_nni_send_eth_packet_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_send_eth_packet_data_validate(const bcmolt_internal_nni_send_eth_packet_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_nni_stats_cfg_data_set_default(bcmolt_internal_nni_nni_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_nni_stats_cfg_data_validate(const bcmolt_internal_nni_nni_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_nni_stats_alarm_raised_data_set_default(bcmolt_internal_nni_nni_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_nni_stats_alarm_raised_data_validate(const bcmolt_internal_nni_nni_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_nni_stats_alarm_cleared_data_set_default(bcmolt_internal_nni_nni_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_nni_stats_alarm_cleared_data_validate(const bcmolt_internal_nni_nni_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_enet_stats_cfg_data_set_default(bcmolt_internal_nni_enet_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_enet_stats_cfg_data_validate(const bcmolt_internal_nni_enet_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_enet_stats_alarm_raised_data_set_default(bcmolt_internal_nni_enet_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_enet_stats_alarm_raised_data_validate(const bcmolt_internal_nni_enet_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_enet_stats_alarm_cleared_data_set_default(bcmolt_internal_nni_enet_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_enet_stats_alarm_cleared_data_validate(const bcmolt_internal_nni_enet_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_internal_nni_auto_cfg_data_set_default(bcmolt_internal_nni_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_internal_nni_auto_cfg_data_validate(const bcmolt_internal_nni_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_key_set_default(bcmolt_itupon_alloc_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_key_validate(const bcmolt_itupon_alloc_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_cfg_data_set_default(bcmolt_itupon_alloc_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_cfg_data_validate(const bcmolt_itupon_alloc_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_itupon_alloc_multi_cfg_get_packed_length(const bcmolt_itupon_alloc_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_alloc_multi_cfg_pack(const bcmolt_itupon_alloc_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_alloc_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_itupon_alloc_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_configuration_completed_data_set_default(bcmolt_itupon_alloc_configuration_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_configuration_completed_data_validate(const bcmolt_itupon_alloc_configuration_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_get_stats_data_set_default(bcmolt_itupon_alloc_get_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_get_stats_data_validate(const bcmolt_itupon_alloc_get_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_get_alloc_stats_completed_data_set_default(bcmolt_itupon_alloc_get_alloc_stats_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_get_alloc_stats_completed_data_validate(const bcmolt_itupon_alloc_get_alloc_stats_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_set_state_data_set_default(bcmolt_itupon_alloc_set_state_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_set_state_data_validate(const bcmolt_itupon_alloc_set_state_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_stats_data_set_default(bcmolt_itupon_alloc_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_stats_data_validate(const bcmolt_itupon_alloc_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_itupon_alloc_multi_stats_get_packed_length(const bcmolt_itupon_alloc_multi_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_alloc_multi_stats_pack(const bcmolt_itupon_alloc_multi_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_alloc_multi_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_itupon_alloc_multi_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data_set_default(bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data_validate(const bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_itupon_alloc_multi_alloc_onu_accumulated_stats_get_packed_length(const bcmolt_itupon_alloc_multi_alloc_onu_accumulated_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_alloc_multi_alloc_onu_accumulated_stats_pack(const bcmolt_itupon_alloc_multi_alloc_onu_accumulated_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_alloc_multi_alloc_onu_accumulated_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_itupon_alloc_multi_alloc_onu_accumulated_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_latency_stats_data_set_default(bcmolt_itupon_alloc_latency_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_latency_stats_data_validate(const bcmolt_itupon_alloc_latency_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_itupon_alloc_multi_latency_stats_get_packed_length(const bcmolt_itupon_alloc_multi_latency_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_alloc_multi_latency_stats_pack(const bcmolt_itupon_alloc_multi_latency_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_alloc_multi_latency_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_itupon_alloc_multi_latency_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_stats_cfg_data_set_default(bcmolt_itupon_alloc_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_stats_cfg_data_validate(const bcmolt_itupon_alloc_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_stats_alarm_raised_data_set_default(bcmolt_itupon_alloc_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_stats_alarm_raised_data_validate(const bcmolt_itupon_alloc_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_stats_alarm_cleared_data_set_default(bcmolt_itupon_alloc_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_stats_alarm_cleared_data_validate(const bcmolt_itupon_alloc_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data_set_default(bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data_validate(const bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data_set_default(bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data_validate(const bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data_set_default(bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data_validate(const bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_latency_stats_cfg_data_set_default(bcmolt_itupon_alloc_latency_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_latency_stats_cfg_data_validate(const bcmolt_itupon_alloc_latency_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_latency_stats_alarm_raised_data_set_default(bcmolt_itupon_alloc_latency_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_latency_stats_alarm_raised_data_validate(const bcmolt_itupon_alloc_latency_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_latency_stats_alarm_cleared_data_set_default(bcmolt_itupon_alloc_latency_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_latency_stats_alarm_cleared_data_validate(const bcmolt_itupon_alloc_latency_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_alloc_auto_cfg_data_set_default(bcmolt_itupon_alloc_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_alloc_auto_cfg_data_validate(const bcmolt_itupon_alloc_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_gem_key_set_default(bcmolt_itupon_gem_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_gem_key_validate(const bcmolt_itupon_gem_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_gem_cfg_data_set_default(bcmolt_itupon_gem_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_gem_cfg_data_validate(const bcmolt_itupon_gem_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_itupon_gem_multi_cfg_get_packed_length(const bcmolt_itupon_gem_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_gem_multi_cfg_pack(const bcmolt_itupon_gem_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_gem_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_itupon_gem_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_gem_stats_data_set_default(bcmolt_itupon_gem_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_gem_stats_data_validate(const bcmolt_itupon_gem_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_itupon_gem_multi_stats_get_packed_length(const bcmolt_itupon_gem_multi_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_gem_multi_stats_pack(const bcmolt_itupon_gem_multi_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_itupon_gem_multi_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_itupon_gem_multi_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_gem_configuration_completed_data_set_default(bcmolt_itupon_gem_configuration_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_gem_configuration_completed_data_validate(const bcmolt_itupon_gem_configuration_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_gem_set_state_data_set_default(bcmolt_itupon_gem_set_state_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_gem_set_state_data_validate(const bcmolt_itupon_gem_set_state_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_gem_stats_cfg_data_set_default(bcmolt_itupon_gem_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_gem_stats_cfg_data_validate(const bcmolt_itupon_gem_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_gem_stats_alarm_raised_data_set_default(bcmolt_itupon_gem_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_gem_stats_alarm_raised_data_validate(const bcmolt_itupon_gem_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_gem_stats_alarm_cleared_data_set_default(bcmolt_itupon_gem_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_gem_stats_alarm_cleared_data_validate(const bcmolt_itupon_gem_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_itupon_gem_auto_cfg_data_set_default(bcmolt_itupon_gem_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_itupon_gem_auto_cfg_data_validate(const bcmolt_itupon_gem_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_l2_mac_table_key_set_default(bcmolt_l2_mac_table_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_l2_mac_table_key_validate(const bcmolt_l2_mac_table_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_l2_mac_table_cfg_data_set_default(bcmolt_l2_mac_table_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_l2_mac_table_cfg_data_validate(const bcmolt_l2_mac_table_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_l2_mac_table_multi_cfg_get_packed_length(const bcmolt_l2_mac_table_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_l2_mac_table_multi_cfg_pack(const bcmolt_l2_mac_table_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_l2_mac_table_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_l2_mac_table_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_l2_mac_table_dump_data_set_default(bcmolt_l2_mac_table_dump_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_l2_mac_table_dump_data_validate(const bcmolt_l2_mac_table_dump_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_l2_mac_table_dump_complete_data_set_default(bcmolt_l2_mac_table_dump_complete_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_l2_mac_table_dump_complete_data_validate(const bcmolt_l2_mac_table_dump_complete_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_l2_mac_table_network_events_data_set_default(bcmolt_l2_mac_table_network_events_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_l2_mac_table_network_events_data_validate(const bcmolt_l2_mac_table_network_events_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_l2_mac_table_pon_events_data_set_default(bcmolt_l2_mac_table_pon_events_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_l2_mac_table_pon_events_data_validate(const bcmolt_l2_mac_table_pon_events_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_l2_mac_table_auto_cfg_data_set_default(bcmolt_l2_mac_table_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_l2_mac_table_auto_cfg_data_validate(const bcmolt_l2_mac_table_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_key_set_default(bcmolt_lag_interface_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_key_validate(const bcmolt_lag_interface_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_cfg_data_set_default(bcmolt_lag_interface_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_cfg_data_validate(const bcmolt_lag_interface_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_lag_interface_multi_cfg_get_packed_length(const bcmolt_lag_interface_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_lag_interface_multi_cfg_pack(const bcmolt_lag_interface_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_lag_interface_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_lag_interface_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_stats_data_set_default(bcmolt_lag_interface_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_stats_data_validate(const bcmolt_lag_interface_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_lag_interface_multi_stats_get_packed_length(const bcmolt_lag_interface_multi_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_lag_interface_multi_stats_pack(const bcmolt_lag_interface_multi_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_lag_interface_multi_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_lag_interface_multi_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_members_update_data_set_default(bcmolt_lag_interface_members_update_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_members_update_data_validate(const bcmolt_lag_interface_members_update_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_complete_members_update_data_set_default(bcmolt_lag_interface_complete_members_update_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_complete_members_update_data_validate(const bcmolt_lag_interface_complete_members_update_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_state_update_data_set_default(bcmolt_lag_interface_state_update_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_state_update_data_validate(const bcmolt_lag_interface_state_update_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_state_updated_data_set_default(bcmolt_lag_interface_state_updated_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_state_updated_data_validate(const bcmolt_lag_interface_state_updated_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_lag_health_change_data_set_default(bcmolt_lag_interface_lag_health_change_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_lag_health_change_data_validate(const bcmolt_lag_interface_lag_health_change_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_stats_cfg_data_set_default(bcmolt_lag_interface_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_stats_cfg_data_validate(const bcmolt_lag_interface_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_stats_alarm_raised_data_set_default(bcmolt_lag_interface_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_stats_alarm_raised_data_validate(const bcmolt_lag_interface_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_stats_alarm_cleared_data_set_default(bcmolt_lag_interface_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_stats_alarm_cleared_data_validate(const bcmolt_lag_interface_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_lag_interface_auto_cfg_data_set_default(bcmolt_lag_interface_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_lag_interface_auto_cfg_data_validate(const bcmolt_lag_interface_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_log_key_set_default(bcmolt_log_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_log_key_validate(const bcmolt_log_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_log_cfg_data_set_default(bcmolt_log_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_log_cfg_data_validate(const bcmolt_log_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_log_multi_cfg_get_packed_length(const bcmolt_log_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_log_multi_cfg_pack(const bcmolt_log_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_log_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_log_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_log_file_key_set_default(bcmolt_log_file_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_log_file_key_validate(const bcmolt_log_file_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_log_file_cfg_data_set_default(bcmolt_log_file_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_log_file_cfg_data_validate(const bcmolt_log_file_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_log_file_multi_cfg_get_packed_length(const bcmolt_log_file_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_log_file_multi_cfg_pack(const bcmolt_log_file_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_log_file_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_log_file_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ngpon2_channel_key_set_default(bcmolt_ngpon2_channel_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ngpon2_channel_key_validate(const bcmolt_ngpon2_channel_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ngpon2_channel_cfg_data_set_default(bcmolt_ngpon2_channel_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ngpon2_channel_cfg_data_validate(const bcmolt_ngpon2_channel_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_ngpon2_channel_multi_cfg_get_packed_length(const bcmolt_ngpon2_channel_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_ngpon2_channel_multi_cfg_pack(const bcmolt_ngpon2_channel_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_ngpon2_channel_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_ngpon2_channel_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_key_set_default(bcmolt_nni_interface_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_key_validate(const bcmolt_nni_interface_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_state_change_data_set_default(bcmolt_nni_interface_state_change_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_state_change_data_validate(const bcmolt_nni_interface_state_change_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_cfg_data_set_default(bcmolt_nni_interface_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_cfg_data_validate(const bcmolt_nni_interface_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_nni_interface_multi_cfg_get_packed_length(const bcmolt_nni_interface_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_nni_interface_multi_cfg_pack(const bcmolt_nni_interface_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_nni_interface_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_nni_interface_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_set_nni_state_data_set_default(bcmolt_nni_interface_set_nni_state_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_set_nni_state_data_validate(const bcmolt_nni_interface_set_nni_state_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_stats_data_set_default(bcmolt_nni_interface_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_stats_data_validate(const bcmolt_nni_interface_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_nni_interface_multi_stats_get_packed_length(const bcmolt_nni_interface_multi_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_nni_interface_multi_stats_pack(const bcmolt_nni_interface_multi_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_nni_interface_multi_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_nni_interface_multi_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_link_state_change_data_set_default(bcmolt_nni_interface_link_state_change_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_link_state_change_data_validate(const bcmolt_nni_interface_link_state_change_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_fault_code_change_data_set_default(bcmolt_nni_interface_fault_code_change_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_fault_code_change_data_validate(const bcmolt_nni_interface_fault_code_change_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_stats_cfg_data_set_default(bcmolt_nni_interface_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_stats_cfg_data_validate(const bcmolt_nni_interface_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_stats_alarm_raised_data_set_default(bcmolt_nni_interface_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_stats_alarm_raised_data_validate(const bcmolt_nni_interface_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_stats_alarm_cleared_data_set_default(bcmolt_nni_interface_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_stats_alarm_cleared_data_validate(const bcmolt_nni_interface_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_nni_interface_auto_cfg_data_set_default(bcmolt_nni_interface_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_nni_interface_auto_cfg_data_validate(const bcmolt_nni_interface_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_olt_key_set_default(bcmolt_olt_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_olt_key_validate(const bcmolt_olt_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_olt_cfg_data_set_default(bcmolt_olt_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_olt_cfg_data_validate(const bcmolt_olt_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_olt_multi_cfg_get_packed_length(const bcmolt_olt_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_olt_multi_cfg_pack(const bcmolt_olt_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_olt_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_olt_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_olt_bal_failure_data_set_default(bcmolt_olt_bal_failure_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_olt_bal_failure_data_validate(const bcmolt_olt_bal_failure_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_olt_sw_error_data_set_default(bcmolt_olt_sw_error_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_olt_sw_error_data_validate(const bcmolt_olt_sw_error_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_olt_reset_data_set_default(bcmolt_olt_reset_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_olt_reset_data_validate(const bcmolt_olt_reset_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_olt_auto_cfg_data_set_default(bcmolt_olt_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_olt_auto_cfg_data_validate(const bcmolt_olt_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_key_set_default(bcmolt_onu_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_key_validate(const bcmolt_onu_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_cfg_data_set_default(bcmolt_onu_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_cfg_data_validate(const bcmolt_onu_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_onu_multi_cfg_get_packed_length(const bcmolt_onu_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_onu_multi_cfg_pack(const bcmolt_onu_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_onu_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_onu_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_itu_pon_stats_data_set_default(bcmolt_onu_itu_pon_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_itu_pon_stats_data_validate(const bcmolt_onu_itu_pon_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_onu_multi_itu_pon_stats_get_packed_length(const bcmolt_onu_multi_itu_pon_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_onu_multi_itu_pon_stats_pack(const bcmolt_onu_multi_itu_pon_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_onu_multi_itu_pon_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_onu_multi_itu_pon_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_set_onu_state_data_set_default(bcmolt_onu_set_onu_state_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_set_onu_state_data_validate(const bcmolt_onu_set_onu_state_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_request_registration_data_set_default(bcmolt_onu_request_registration_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_request_registration_data_validate(const bcmolt_onu_request_registration_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_change_power_levelling_data_set_default(bcmolt_onu_change_power_levelling_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_change_power_levelling_data_validate(const bcmolt_onu_change_power_levelling_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_adjust_tx_wavelength_data_set_default(bcmolt_onu_adjust_tx_wavelength_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_adjust_tx_wavelength_data_validate(const bcmolt_onu_adjust_tx_wavelength_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_secure_mutual_authentication_data_set_default(bcmolt_onu_secure_mutual_authentication_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_secure_mutual_authentication_data_validate(const bcmolt_onu_secure_mutual_authentication_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_tuning_out_data_set_default(bcmolt_onu_tuning_out_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_tuning_out_data_validate(const bcmolt_onu_tuning_out_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_xgpon_alarm_data_set_default(bcmolt_onu_xgpon_alarm_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_xgpon_alarm_data_validate(const bcmolt_onu_xgpon_alarm_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_gpon_alarm_data_set_default(bcmolt_onu_gpon_alarm_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_gpon_alarm_data_validate(const bcmolt_onu_gpon_alarm_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_dowi_data_set_default(bcmolt_onu_dowi_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_dowi_data_validate(const bcmolt_onu_dowi_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_sfi_data_set_default(bcmolt_onu_sfi_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_sfi_data_validate(const bcmolt_onu_sfi_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_sdi_data_set_default(bcmolt_onu_sdi_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_sdi_data_validate(const bcmolt_onu_sdi_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_dfi_data_set_default(bcmolt_onu_dfi_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_dfi_data_validate(const bcmolt_onu_dfi_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_pqsi_data_set_default(bcmolt_onu_pqsi_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_pqsi_data_validate(const bcmolt_onu_pqsi_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_sufi_data_set_default(bcmolt_onu_sufi_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_sufi_data_validate(const bcmolt_onu_sufi_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_tiwi_data_set_default(bcmolt_onu_tiwi_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_tiwi_data_validate(const bcmolt_onu_tiwi_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_looci_data_set_default(bcmolt_onu_looci_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_looci_data_validate(const bcmolt_onu_looci_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_loai_data_set_default(bcmolt_onu_loai_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_loai_data_validate(const bcmolt_onu_loai_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_dgi_data_set_default(bcmolt_onu_dgi_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_dgi_data_validate(const bcmolt_onu_dgi_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_pee_data_set_default(bcmolt_onu_pee_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_pee_data_validate(const bcmolt_onu_pee_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_pst_data_set_default(bcmolt_onu_pst_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_pst_data_validate(const bcmolt_onu_pst_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_ranging_completed_data_set_default(bcmolt_onu_ranging_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_ranging_completed_data_validate(const bcmolt_onu_ranging_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_onu_activation_completed_data_set_default(bcmolt_onu_onu_activation_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_onu_activation_completed_data_validate(const bcmolt_onu_onu_activation_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_onu_deactivation_completed_data_set_default(bcmolt_onu_onu_deactivation_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_onu_deactivation_completed_data_validate(const bcmolt_onu_onu_deactivation_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_onu_enable_completed_data_set_default(bcmolt_onu_onu_enable_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_onu_enable_completed_data_validate(const bcmolt_onu_onu_enable_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_onu_disable_completed_data_set_default(bcmolt_onu_onu_disable_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_onu_disable_completed_data_validate(const bcmolt_onu_onu_disable_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_rssi_measurement_completed_data_set_default(bcmolt_onu_rssi_measurement_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_rssi_measurement_completed_data_validate(const bcmolt_onu_rssi_measurement_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_invalid_dbru_report_data_set_default(bcmolt_onu_invalid_dbru_report_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_invalid_dbru_report_data_validate(const bcmolt_onu_invalid_dbru_report_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_key_exchange_completed_data_set_default(bcmolt_onu_key_exchange_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_key_exchange_completed_data_validate(const bcmolt_onu_key_exchange_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_key_exchange_key_mismatch_data_set_default(bcmolt_onu_key_exchange_key_mismatch_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_key_exchange_key_mismatch_data_validate(const bcmolt_onu_key_exchange_key_mismatch_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_loki_data_set_default(bcmolt_onu_loki_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_loki_data_validate(const bcmolt_onu_loki_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_memi_data_set_default(bcmolt_onu_memi_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_memi_data_validate(const bcmolt_onu_memi_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_omci_port_id_configuration_completed_data_set_default(bcmolt_onu_omci_port_id_configuration_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_omci_port_id_configuration_completed_data_validate(const bcmolt_onu_omci_port_id_configuration_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_ber_interval_configuration_completed_data_set_default(bcmolt_onu_ber_interval_configuration_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_ber_interval_configuration_completed_data_validate(const bcmolt_onu_ber_interval_configuration_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_err_data_set_default(bcmolt_onu_err_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_err_data_validate(const bcmolt_onu_err_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_password_authentication_completed_data_set_default(bcmolt_onu_password_authentication_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_password_authentication_completed_data_validate(const bcmolt_onu_password_authentication_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_key_exchange_unconsecutive_index_data_set_default(bcmolt_onu_key_exchange_unconsecutive_index_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_key_exchange_unconsecutive_index_data_validate(const bcmolt_onu_key_exchange_unconsecutive_index_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_key_exchange_decrypt_required_data_set_default(bcmolt_onu_key_exchange_decrypt_required_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_key_exchange_decrypt_required_data_validate(const bcmolt_onu_key_exchange_decrypt_required_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_onu_activation_standby_completed_data_set_default(bcmolt_onu_onu_activation_standby_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_onu_activation_standby_completed_data_validate(const bcmolt_onu_onu_activation_standby_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_power_management_state_change_data_set_default(bcmolt_onu_power_management_state_change_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_power_management_state_change_data_validate(const bcmolt_onu_power_management_state_change_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_possible_drift_data_set_default(bcmolt_onu_possible_drift_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_possible_drift_data_validate(const bcmolt_onu_possible_drift_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_registration_id_data_set_default(bcmolt_onu_registration_id_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_registration_id_data_validate(const bcmolt_onu_registration_id_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_power_level_report_data_set_default(bcmolt_onu_power_level_report_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_power_level_report_data_validate(const bcmolt_onu_power_level_report_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_power_consumption_report_data_set_default(bcmolt_onu_power_consumption_report_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_power_consumption_report_data_validate(const bcmolt_onu_power_consumption_report_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_secure_mutual_authentication_failure_data_set_default(bcmolt_onu_secure_mutual_authentication_failure_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_secure_mutual_authentication_failure_data_validate(const bcmolt_onu_secure_mutual_authentication_failure_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_onu_tuning_out_completed_data_set_default(bcmolt_onu_onu_tuning_out_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_onu_tuning_out_completed_data_validate(const bcmolt_onu_onu_tuning_out_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_onu_tuning_in_completed_data_set_default(bcmolt_onu_onu_tuning_in_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_onu_tuning_in_completed_data_validate(const bcmolt_onu_onu_tuning_in_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_tuning_response_data_set_default(bcmolt_onu_tuning_response_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_tuning_response_data_validate(const bcmolt_onu_tuning_response_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_ploam_packet_data_set_default(bcmolt_onu_ploam_packet_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_ploam_packet_data_validate(const bcmolt_onu_ploam_packet_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_cpu_packets_data_set_default(bcmolt_onu_cpu_packets_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_cpu_packets_data_validate(const bcmolt_onu_cpu_packets_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_cpu_packet_data_set_default(bcmolt_onu_cpu_packet_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_cpu_packet_data_validate(const bcmolt_onu_cpu_packet_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_omci_packet_data_set_default(bcmolt_onu_omci_packet_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_omci_packet_data_validate(const bcmolt_onu_omci_packet_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_rei_data_set_default(bcmolt_onu_rei_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_rei_data_validate(const bcmolt_onu_rei_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_state_change_data_set_default(bcmolt_onu_state_change_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_state_change_data_validate(const bcmolt_onu_state_change_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_range_value_changed_data_set_default(bcmolt_onu_range_value_changed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_range_value_changed_data_validate(const bcmolt_onu_range_value_changed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_xpon_unknown_ploam_data_set_default(bcmolt_onu_xpon_unknown_ploam_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_xpon_unknown_ploam_data_validate(const bcmolt_onu_xpon_unknown_ploam_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_trap_ploam_received_data_set_default(bcmolt_onu_trap_ploam_received_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_trap_ploam_received_data_validate(const bcmolt_onu_trap_ploam_received_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_itu_alloc_onu_accumulated_stats_data_set_default(bcmolt_onu_itu_alloc_onu_accumulated_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_itu_alloc_onu_accumulated_stats_data_validate(const bcmolt_onu_itu_alloc_onu_accumulated_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_onu_multi_itu_alloc_onu_accumulated_stats_get_packed_length(const bcmolt_onu_multi_itu_alloc_onu_accumulated_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_onu_multi_itu_alloc_onu_accumulated_stats_pack(const bcmolt_onu_multi_itu_alloc_onu_accumulated_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_onu_multi_itu_alloc_onu_accumulated_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_onu_multi_itu_alloc_onu_accumulated_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_itu_pon_stats_cfg_data_set_default(bcmolt_onu_itu_pon_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_itu_pon_stats_cfg_data_validate(const bcmolt_onu_itu_pon_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_itu_pon_stats_alarm_raised_data_set_default(bcmolt_onu_itu_pon_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_itu_pon_stats_alarm_raised_data_validate(const bcmolt_onu_itu_pon_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_itu_pon_stats_alarm_cleared_data_set_default(bcmolt_onu_itu_pon_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_itu_pon_stats_alarm_cleared_data_validate(const bcmolt_onu_itu_pon_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data_set_default(bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data_validate(const bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data_set_default(bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data_validate(const bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data_set_default(bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data_validate(const bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_onu_auto_cfg_data_set_default(bcmolt_onu_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_onu_auto_cfg_data_validate(const bcmolt_onu_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pbit_to_tc_key_set_default(bcmolt_pbit_to_tc_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pbit_to_tc_key_validate(const bcmolt_pbit_to_tc_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pbit_to_tc_cfg_data_set_default(bcmolt_pbit_to_tc_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pbit_to_tc_cfg_data_validate(const bcmolt_pbit_to_tc_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_pbit_to_tc_multi_cfg_get_packed_length(const bcmolt_pbit_to_tc_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_pbit_to_tc_multi_cfg_pack(const bcmolt_pbit_to_tc_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_pbit_to_tc_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_pbit_to_tc_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_policer_profile_key_set_default(bcmolt_policer_profile_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_policer_profile_key_validate(const bcmolt_policer_profile_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_policer_profile_cfg_data_set_default(bcmolt_policer_profile_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_policer_profile_cfg_data_validate(const bcmolt_policer_profile_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_policer_profile_multi_cfg_get_packed_length(const bcmolt_policer_profile_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_policer_profile_multi_cfg_pack(const bcmolt_policer_profile_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_policer_profile_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_policer_profile_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_key_set_default(bcmolt_pon_interface_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_key_validate(const bcmolt_pon_interface_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_cfg_data_set_default(bcmolt_pon_interface_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_cfg_data_validate(const bcmolt_pon_interface_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_pon_interface_multi_cfg_get_packed_length(const bcmolt_pon_interface_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_pon_interface_multi_cfg_pack(const bcmolt_pon_interface_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_pon_interface_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_pon_interface_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_itu_pon_stats_data_set_default(bcmolt_pon_interface_itu_pon_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_itu_pon_stats_data_validate(const bcmolt_pon_interface_itu_pon_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_pon_interface_multi_itu_pon_stats_get_packed_length(const bcmolt_pon_interface_multi_itu_pon_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_pon_interface_multi_itu_pon_stats_pack(const bcmolt_pon_interface_multi_itu_pon_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_pon_interface_multi_itu_pon_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_pon_interface_multi_itu_pon_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_ae_stats_data_set_default(bcmolt_pon_interface_ae_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_ae_stats_data_validate(const bcmolt_pon_interface_ae_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_pon_interface_multi_ae_stats_get_packed_length(const bcmolt_pon_interface_multi_ae_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_pon_interface_multi_ae_stats_pack(const bcmolt_pon_interface_multi_ae_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_pon_interface_multi_ae_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_pon_interface_multi_ae_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_set_pon_interface_state_data_set_default(bcmolt_pon_interface_set_pon_interface_state_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_set_pon_interface_state_data_validate(const bcmolt_pon_interface_set_pon_interface_state_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_set_onu_state_data_set_default(bcmolt_pon_interface_set_onu_state_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_set_onu_state_data_validate(const bcmolt_pon_interface_set_onu_state_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_disable_serial_number_data_set_default(bcmolt_pon_interface_disable_serial_number_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_disable_serial_number_data_validate(const bcmolt_pon_interface_disable_serial_number_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_run_special_bw_map_data_set_default(bcmolt_pon_interface_run_special_bw_map_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_run_special_bw_map_data_validate(const bcmolt_pon_interface_run_special_bw_map_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_start_onu_upgrade_data_set_default(bcmolt_pon_interface_start_onu_upgrade_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_start_onu_upgrade_data_validate(const bcmolt_pon_interface_start_onu_upgrade_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_set_default(bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_validate(const bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_set_default(bcmolt_pon_interface_protection_switching_apply_rerange_delta_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_validate(const bcmolt_pon_interface_protection_switching_apply_rerange_delta_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_cpu_packets_data_set_default(bcmolt_pon_interface_cpu_packets_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_cpu_packets_data_validate(const bcmolt_pon_interface_cpu_packets_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_broadcast_ploam_packet_data_set_default(bcmolt_pon_interface_broadcast_ploam_packet_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_broadcast_ploam_packet_data_validate(const bcmolt_pon_interface_broadcast_ploam_packet_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_state_change_completed_data_set_default(bcmolt_pon_interface_state_change_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_state_change_completed_data_validate(const bcmolt_pon_interface_state_change_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_tod_request_completed_data_set_default(bcmolt_pon_interface_tod_request_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_tod_request_completed_data_validate(const bcmolt_pon_interface_tod_request_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_los_data_set_default(bcmolt_pon_interface_los_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_los_data_validate(const bcmolt_pon_interface_los_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_protection_switching_traffic_resume_data_set_default(bcmolt_pon_interface_protection_switching_traffic_resume_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_protection_switching_traffic_resume_data_validate(const bcmolt_pon_interface_protection_switching_traffic_resume_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_protection_switching_onus_ranged_data_set_default(bcmolt_pon_interface_protection_switching_onus_ranged_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_protection_switching_onus_ranged_data_validate(const bcmolt_pon_interface_protection_switching_onus_ranged_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_protection_switching_switchover_completed_data_set_default(bcmolt_pon_interface_protection_switching_switchover_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_protection_switching_switchover_completed_data_validate(const bcmolt_pon_interface_protection_switching_switchover_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_set_default(bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_validate(const bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_onu_discovered_data_set_default(bcmolt_pon_interface_onu_discovered_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_onu_discovered_data_validate(const bcmolt_pon_interface_onu_discovered_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_cpu_packets_failure_data_set_default(bcmolt_pon_interface_cpu_packets_failure_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_cpu_packets_failure_data_validate(const bcmolt_pon_interface_cpu_packets_failure_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_activate_all_onus_completed_data_set_default(bcmolt_pon_interface_activate_all_onus_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_activate_all_onus_completed_data_validate(const bcmolt_pon_interface_activate_all_onus_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_onu_upgrade_complete_data_set_default(bcmolt_pon_interface_onu_upgrade_complete_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_onu_upgrade_complete_data_validate(const bcmolt_pon_interface_onu_upgrade_complete_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_mpcp_timestamp_changed_data_set_default(bcmolt_pon_interface_mpcp_timestamp_changed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_mpcp_timestamp_changed_data_validate(const bcmolt_pon_interface_mpcp_timestamp_changed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_switch_pon_type_data_set_default(bcmolt_pon_interface_switch_pon_type_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_switch_pon_type_data_validate(const bcmolt_pon_interface_switch_pon_type_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_switch_pon_type_completed_data_set_default(bcmolt_pon_interface_switch_pon_type_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_switch_pon_type_completed_data_validate(const bcmolt_pon_interface_switch_pon_type_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_rogue_detection_tool_data_set_default(bcmolt_pon_interface_rogue_detection_tool_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_rogue_detection_tool_data_validate(const bcmolt_pon_interface_rogue_detection_tool_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_rogue_detection_tool_done_data_set_default(bcmolt_pon_interface_rogue_detection_tool_done_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_rogue_detection_tool_done_data_validate(const bcmolt_pon_interface_rogue_detection_tool_done_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_onu_upgrade_activate_commit_data_set_default(bcmolt_pon_interface_onu_upgrade_activate_commit_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_onu_upgrade_activate_commit_data_validate(const bcmolt_pon_interface_onu_upgrade_activate_commit_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_itu_pon_stats_cfg_data_set_default(bcmolt_pon_interface_itu_pon_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_itu_pon_stats_cfg_data_validate(const bcmolt_pon_interface_itu_pon_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_set_default(bcmolt_pon_interface_itu_pon_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_validate(const bcmolt_pon_interface_itu_pon_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_set_default(bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_validate(const bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_ae_stats_cfg_data_set_default(bcmolt_pon_interface_ae_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_ae_stats_cfg_data_validate(const bcmolt_pon_interface_ae_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_ae_stats_alarm_raised_data_set_default(bcmolt_pon_interface_ae_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_ae_stats_alarm_raised_data_validate(const bcmolt_pon_interface_ae_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_ae_stats_alarm_cleared_data_set_default(bcmolt_pon_interface_ae_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_ae_stats_alarm_cleared_data_validate(const bcmolt_pon_interface_ae_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_pon_interface_auto_cfg_data_set_default(bcmolt_pon_interface_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_pon_interface_auto_cfg_data_validate(const bcmolt_pon_interface_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_protection_interface_key_set_default(bcmolt_protection_interface_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_protection_interface_key_validate(const bcmolt_protection_interface_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_protection_interface_cfg_data_set_default(bcmolt_protection_interface_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_protection_interface_cfg_data_validate(const bcmolt_protection_interface_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_protection_interface_multi_cfg_get_packed_length(const bcmolt_protection_interface_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_protection_interface_multi_cfg_pack(const bcmolt_protection_interface_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_protection_interface_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_protection_interface_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_protection_interface_protection_switch_completed_data_set_default(bcmolt_protection_interface_protection_switch_completed_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_protection_interface_protection_switch_completed_data_validate(const bcmolt_protection_interface_protection_switch_completed_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_protection_interface_auto_cfg_data_set_default(bcmolt_protection_interface_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_protection_interface_auto_cfg_data_validate(const bcmolt_protection_interface_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_software_error_key_set_default(bcmolt_software_error_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_software_error_key_validate(const bcmolt_software_error_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_software_error_cfg_data_set_default(bcmolt_software_error_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_software_error_cfg_data_validate(const bcmolt_software_error_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_software_error_multi_cfg_get_packed_length(const bcmolt_software_error_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_software_error_multi_cfg_pack(const bcmolt_software_error_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_software_error_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_software_error_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_switch_inni_key_set_default(bcmolt_switch_inni_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_switch_inni_key_validate(const bcmolt_switch_inni_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_switch_inni_cfg_data_set_default(bcmolt_switch_inni_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_switch_inni_cfg_data_validate(const bcmolt_switch_inni_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_switch_inni_multi_cfg_get_packed_length(const bcmolt_switch_inni_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_switch_inni_multi_cfg_pack(const bcmolt_switch_inni_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_switch_inni_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_switch_inni_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_switch_inni_stats_data_set_default(bcmolt_switch_inni_stats_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_switch_inni_stats_data_validate(const bcmolt_switch_inni_stats_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_switch_inni_multi_stats_get_packed_length(const bcmolt_switch_inni_multi_stats *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_switch_inni_multi_stats_pack(const bcmolt_switch_inni_multi_stats *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_switch_inni_multi_stats_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_switch_inni_multi_stats **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_switch_inni_link_state_change_data_set_default(bcmolt_switch_inni_link_state_change_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_switch_inni_link_state_change_data_validate(const bcmolt_switch_inni_link_state_change_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_switch_inni_stats_cfg_data_set_default(bcmolt_switch_inni_stats_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_switch_inni_stats_cfg_data_validate(const bcmolt_switch_inni_stats_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_switch_inni_stats_alarm_raised_data_set_default(bcmolt_switch_inni_stats_alarm_raised_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_switch_inni_stats_alarm_raised_data_validate(const bcmolt_switch_inni_stats_alarm_raised_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_switch_inni_stats_alarm_cleared_data_set_default(bcmolt_switch_inni_stats_alarm_cleared_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_switch_inni_stats_alarm_cleared_data_validate(const bcmolt_switch_inni_stats_alarm_cleared_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_switch_inni_auto_cfg_data_set_default(bcmolt_switch_inni_auto_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_switch_inni_auto_cfg_data_validate(const bcmolt_switch_inni_auto_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tc_to_queue_key_set_default(bcmolt_tc_to_queue_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tc_to_queue_key_validate(const bcmolt_tc_to_queue_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tc_to_queue_cfg_data_set_default(bcmolt_tc_to_queue_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tc_to_queue_cfg_data_validate(const bcmolt_tc_to_queue_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_tc_to_queue_multi_cfg_get_packed_length(const bcmolt_tc_to_queue_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_tc_to_queue_multi_cfg_pack(const bcmolt_tc_to_queue_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_tc_to_queue_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_tc_to_queue_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_qmp_key_set_default(bcmolt_tm_qmp_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_qmp_key_validate(const bcmolt_tm_qmp_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_qmp_cfg_data_set_default(bcmolt_tm_qmp_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_qmp_cfg_data_validate(const bcmolt_tm_qmp_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_tm_qmp_multi_cfg_get_packed_length(const bcmolt_tm_qmp_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_tm_qmp_multi_cfg_pack(const bcmolt_tm_qmp_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_tm_qmp_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_tm_qmp_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_queue_key_set_default(bcmolt_tm_queue_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_queue_key_validate(const bcmolt_tm_queue_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_queue_cfg_data_set_default(bcmolt_tm_queue_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_queue_cfg_data_validate(const bcmolt_tm_queue_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_tm_queue_multi_cfg_get_packed_length(const bcmolt_tm_queue_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_tm_queue_multi_cfg_pack(const bcmolt_tm_queue_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_tm_queue_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_tm_queue_multi_cfg **msg);

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_sched_key_set_default(bcmolt_tm_sched_key *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_sched_key_validate(const bcmolt_tm_sched_key *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_tm_sched_cfg_data_set_default(bcmolt_tm_sched_cfg_data *obj);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_tm_sched_cfg_data_validate(const bcmolt_tm_sched_cfg_data *obj, bcmos_errno *err, bcmolt_string *err_details);


/** Gets the number of bytes that a multi-object container would occupy on the wire.
 *
 * Does not include the common header (msg->hdr->hdr).
 *
 * \param msg Pointer to the structure.
 * \return The structure size in bytes.
 */
uint32_t bcmolt_tm_sched_multi_cfg_get_packed_length(const bcmolt_tm_sched_multi_cfg *msg);

/** Packs a multi-object container to bytes for transmission on the wire.
 *
 * Assumes that the common header (msg->hdr->hdr) has already been packed.
 *
 * \param msg Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * eturn Error encountered during the pack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_tm_sched_multi_cfg_pack(const bcmolt_tm_sched_multi_cfg *msg, bcmolt_buf *buf);

/** Unpacks a multi-object container from bytes as received on the wire.
 *
 * Assumes that the common header has already been unpacked.
 *
 * \param buf Pointer to the buffer to read from.
 * \param hdr The common header that has already been unpacked.
 * \param msg Pointer to the structure to unpack. This can be NULL, in which case the message will be dynamically allocated.
 * eturn Error encountered during the unpack (BCM_ERR_OK on success).
 */
bcmos_errno bcmolt_tm_sched_multi_cfg_unpack(bcmolt_buf *buf, const bcmolt_msg *hdr, bcmolt_tm_sched_multi_cfg **msg);



#endif
