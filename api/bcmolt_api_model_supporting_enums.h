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

#ifndef BCMOLT_API_MODEL_SUPPORTING_ENUMS_H_
#define BCMOLT_API_MODEL_SUPPORTING_ENUMS_H_

#include <bcmos_system.h>

/** \addtogroup object_model
 * @{
 */

/** access control forwarding action type. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_INVALID = 0, /**< this can not be set, just the init value of the field in object */
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_TRAP_TO_HOST = 1, /**< trap matching packets to host */
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_DROP = 2, /**< drop matching packets */
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_REDIRECT = 3, /**< redirect matching packet to a destination port */
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_NO_ACTION = 4, /**< no action applied to packet and is passed to the pipeline for further handling */
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_access_control_fwd_action_type;

/** action_cmd_id. */
typedef enum
{
    BCMOLT_ACTION_CMD_ID_NONE = 0,
    BCMOLT_ACTION_CMD_ID_ADD_OUTER_TAG = 0x0001, /**< Add outer tag. */
    BCMOLT_ACTION_CMD_ID_REMOVE_OUTER_TAG = 0x0002, /**< Remove outer tag. */
    BCMOLT_ACTION_CMD_ID_XLATE_OUTER_TAG = 0x0004, /**< Translate outer tag. */
    BCMOLT_ACTION_CMD_ID_ADD_INNER_TAG = 0x0010, /**< Add inner tag. */
    BCMOLT_ACTION_CMD_ID_REMOVE_INNER_TAG = 0x0020, /**< Remove inner tag. */
    BCMOLT_ACTION_CMD_ID_XLATE_INNER_TAG = 0x0040, /**< Translate inner tag. */
    BCMOLT_ACTION_CMD_ID_REMARK_OUTER_PBITS = 0x0100, /**< Remark outer pbits. */
    BCMOLT_ACTION_CMD_ID_REMARK_INNER_PBITS = 0x0200, /**< Remark inner pbits. */
} bcmolt_action_cmd_id;

/** ACL pkt modifier IDs. */
typedef enum
{
    BCMOLT_ACTION_CONTROL_PKT_MODIFIERS_NONE = 0,
    BCMOLT_ACTION_CONTROL_PKT_MODIFIERS_PUSH_TAG = 0x0001, /**< Push VLAN Id */
    BCMOLT_ACTION_CONTROL_PKT_MODIFIERS_POP_TAG = 0x0002, /**< Pop Outer Vlan Tag */
    BCMOLT_ACTION_CONTROL_PKT_MODIFIERS_MODIFY_OUTER_VID = 0x0004, /**< Modify Outer VID */
    BCMOLT_ACTION_CONTROL_PKT_MODIFIERS_MODIFY_INNER_VID = 0x0008, /**< Modify Inner VID */
    BCMOLT_ACTION_CONTROL_PKT_MODIFIERS_REMARK_OUTER_PBITS = 0x0010, /**< Remark Outer PBits */
    BCMOLT_ACTION_CONTROL_PKT_MODIFIERS_REMARK_INNER_PBITS = 0x0020, /**< Remark Inner PBits */
    BCMOLT_ACTION_CONTROL_PKT_MODIFIERS_REMARK_DSCP = 0x0040, /**< Remark DSCP */
    BCMOLT_ACTION_CONTROL_PKT_MODIFIERS_REWRITE_TTL = 0x0080, /**< Rewrite TTL */
} bcmolt_action_control_pkt_modifiers;

/** action_tag_format. */
typedef enum
{
    BCMOLT_ACTION_TAG_FORMAT__BEGIN = 0,
    BCMOLT_ACTION_TAG_FORMAT_DOT_1_Q = 0, /**< 802.1q. */
    BCMOLT_ACTION_TAG_FORMAT_Q_IN_Q = 1, /**< 802.1ad. */
    BCMOLT_ACTION_TAG_FORMAT__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_action_tag_format;

/** activation fail reason. */
typedef enum
{
    BCMOLT_ACTIVATION_FAIL_REASON__BEGIN = 0,
    BCMOLT_ACTIVATION_FAIL_REASON_NONE = 0, /**< None. */
    BCMOLT_ACTIVATION_FAIL_REASON_RANGING = 1, /**< Ranging. */
    BCMOLT_ACTIVATION_FAIL_REASON_PASSWORD_AUTHENTICATION = 2, /**< Password authentication. */
    BCMOLT_ACTIVATION_FAIL_REASON_LOS = 3, /**< LOS. */
    BCMOLT_ACTIVATION_FAIL_REASON_ONU_ALARM = 4, /**< ONU Alarm. */
    BCMOLT_ACTIVATION_FAIL_REASON_SWITCH_OVER = 5, /**< protection switch over. */
    BCMOLT_ACTIVATION_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_activation_fail_reason;

/** gem port/alloc/ flow activation state */
typedef enum
{
    BCMOLT_ACTIVATION_STATE__BEGIN = 0,
    BCMOLT_ACTIVATION_STATE_NOT_CONFIGURED = 0, /**< Not configured. */
    BCMOLT_ACTIVATION_STATE_INACTIVE = 1, /**< Inactive. */
    BCMOLT_ACTIVATION_STATE_PROCESSING = 2, /**< Processing. */
    BCMOLT_ACTIVATION_STATE_ACTIVE = 3, /**< Active. */
    BCMOLT_ACTIVATION_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_activation_state;

/** Currently active interface in protection interface pair (Primary or Secondary) */
typedef enum
{
    BCMOLT_ACTIVE_INTERFACE__BEGIN = 0,
    BCMOLT_ACTIVE_INTERFACE_UNASSIGNED = 0, /**< No Active Interface */
    BCMOLT_ACTIVE_INTERFACE_PRIMARY = 1, /**< Primary Interface is active in protection pair */
    BCMOLT_ACTIVE_INTERFACE_SECONDARY = 2, /**< Secondary Interface is active in protection pair */
    BCMOLT_ACTIVE_INTERFACE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_active_interface;

/** Additional BW eligibility. */
typedef enum
{
    BCMOLT_ADDITIONAL_BW_ELIGIBILITY__BEGIN = 0,
    BCMOLT_ADDITIONAL_BW_ELIGIBILITY_NONE = 0, /**< None. */
    BCMOLT_ADDITIONAL_BW_ELIGIBILITY_NON_ASSURED = 1, /**< Non Assured. */
    BCMOLT_ADDITIONAL_BW_ELIGIBILITY_BEST_EFFORT = 2, /**< Best Effort. */
    BCMOLT_ADDITIONAL_BW_ELIGIBILITY__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_additional_bw_eligibility;

/** Alloc operation. */
typedef enum
{
    BCMOLT_ALLOC_OPERATION__BEGIN = 0,
    BCMOLT_ALLOC_OPERATION_ACTIVATE = 0, /**< Activate. */
    BCMOLT_ALLOC_OPERATION_DEACTIVATE = 1, /**< Deactivate. */
    BCMOLT_ALLOC_OPERATION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_alloc_operation;

/** Alloc Type. */
typedef enum
{
    BCMOLT_ALLOC_TYPE__BEGIN = 0,
    BCMOLT_ALLOC_TYPE_NONE = 0, /**< None. */
    BCMOLT_ALLOC_TYPE_NSR = 1, /**< Non Status Report. */
    BCMOLT_ALLOC_TYPE_SR = 2, /**< Status Report. */
    BCMOLT_ALLOC_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_alloc_type;

/** deactivation reason. */
typedef enum
{
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON__BEGIN = 0,
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_NONE = 0, /**< none. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_DEACTIVATION = 1, /**< deactivation. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_ACK_TIMEOUT = 2, /**< ack timeout. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_SFI = 3, /**< sfi alarm. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_TIWI = 4, /**< tiwi. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_PASSWORD_AUTHENTICATION = 5, /**< password authentication. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_ONU_ALARM = 6, /**< onu alarm. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_LOS = 7, /**< los. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_LOKI = 8, /**< loki. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_RERANGE_FAILURE = 9, /**< re-range failure. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_FORCE_DEACTIVATION = 10, /**< force deactivation. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_automatic_onu_deactivation_reason;

/** BAL and/or Switch fail reason. */
typedef enum
{
    BCMOLT_BAL_FAIL_REASON__BEGIN = 1,
    BCMOLT_BAL_FAIL_REASON_SWITCH_TIMED_OUT = 1, /**< Switch timed out during initialization. */
    BCMOLT_BAL_FAIL_REASON_SWITCH_INTERNAL_ERROR = 2, /**< Switch internal error during initialization. */
    BCMOLT_BAL_FAIL_REASON_BAL_TIMED_OUT = 3, /**< BAL initialization timed out. */
    BCMOLT_BAL_FAIL_REASON_BAL_INTERNAL_ERROR = 4, /**< BAL internal error during initialization. */
    BCMOLT_BAL_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_bal_fail_reason;

/** The overall state of OLT Object instance */
typedef enum
{
    BCMOLT_BAL_STATE__BEGIN = 0,
    BCMOLT_BAL_STATE_BAL_STARTING = 0, /**< BAL initialization in progress */
    BCMOLT_BAL_STATE_SWITCH_FAILED = 1, /**< Switch device initialization failed */
    BCMOLT_BAL_STATE_SWITCH_READY = 2, /**< switch device initialized successfully */
    BCMOLT_BAL_STATE_BAL_FAILED = 3, /**< BAL initialization failed */
    BCMOLT_BAL_STATE_BAL_READY = 4, /**< BAL initialized successfully */
    BCMOLT_BAL_STATE_BAL_AND_SWITCH_READY = 5, /**< BAL and switch device both initialized successfully */
    BCMOLT_BAL_STATE_BAL_NOT_AVAILABLE = 6, /**< BAL Not Available. */
    BCMOLT_BAL_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_bal_state;

/** Type of burst profile - ranging or data */
typedef enum
{
    BCMOLT_BURST_PROFILE_TYPE__BEGIN = 0,
    BCMOLT_BURST_PROFILE_TYPE_RANGING = 0, /**< Ranging burst profile type */
    BCMOLT_BURST_PROFILE_TYPE_DATA = 1, /**< Data burst profile type */
    BCMOLT_BURST_PROFILE_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_burst_profile_type;

/** Calibration Record. */
typedef enum
{
    BCMOLT_CALIBRATION_RECORD__BEGIN = 0,
    BCMOLT_CALIBRATION_RECORD_UNSPECIFIED = 0, /**< Unspecified. */
    BCMOLT_CALIBRATION_RECORD_UNCALIBRATED = 1, /**< Uncalibrated. */
    BCMOLT_CALIBRATION_RECORD_LOOSE = 2, /**< Loose. */
    BCMOLT_CALIBRATION_RECORD_SUFFICIENT = 3, /**< Sufficient. */
    BCMOLT_CALIBRATION_RECORD__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_calibration_record;

/** CCM Event. */
typedef enum
{
    BCMOLT_CCM_EVENT__BEGIN = 0,
    BCMOLT_CCM_EVENT_UNASSIGNED = 0, /**< Unassigned event type */
    BCMOLT_CCM_EVENT_LOC_ON = 1, /**< CCM timeout */
    BCMOLT_CCM_EVENT_LOC_OFF = 2, /**< CCM recovery */
    BCMOLT_CCM_EVENT_RDI_SET = 3, /**< RDI Set received */
    BCMOLT_CCM_EVENT_RDI_RESET = 4, /**< RDI de-asserted received */
    BCMOLT_CCM_EVENT__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ccm_event;

/** CCM Interval. */
typedef enum
{
    BCMOLT_CCM_INTERVAL__BEGIN = 3,
    BCMOLT_CCM_INTERVAL_RATE_3_3MS = 3, /**< 3.3 MS */
    BCMOLT_CCM_INTERVAL_RATE_10_MS = 10, /**< 10 MS */
    BCMOLT_CCM_INTERVAL_RATE_100_MS = 100, /**< 100 MS */
    BCMOLT_CCM_INTERVAL_RATE_1_SEC = 1000, /**< 1 SECOND */
    BCMOLT_CCM_INTERVAL_RATE_10_SEC = 10000, /**< 10 SECONDS */
    BCMOLT_CCM_INTERVAL_RATE_60_SEC = 60000UL, /**< 1 MINUTE */
    BCMOLT_CCM_INTERVAL_RATE_600_SEC = 600000UL, /**< 10 MINUTES */
    BCMOLT_CCM_INTERVAL__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ccm_interval;

/** Chip Family. */
typedef enum
{
    BCMOLT_CHIP_FAMILY__BEGIN = 0,
    BCMOLT_CHIP_FAMILY_UNKNOWN = 0, /**< Unknown. */
    BCMOLT_CHIP_FAMILY_CHIP_FAMILY_6862_X = 1, /**< Maple */
    BCMOLT_CHIP_FAMILY_CHIP_FAMILY_6865_X = 2, /**< Aspen */
    BCMOLT_CHIP_FAMILY__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_chip_family;

/** Communication Mode AKA Management Mode */
typedef enum
{
    BCMOLT_COMM_MODE__BEGIN = 0,
    BCMOLT_COMM_MODE_PCIE = 0, /**< Out of Band PCIe Management Communication */
    BCMOLT_COMM_MODE_IN_BAND = 1, /**< In Band Management Communication */
    BCMOLT_COMM_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_comm_mode;

/** Object state: Not Configured or Configured */
typedef enum
{
    BCMOLT_CONFIG_STATE__BEGIN = 0,
    BCMOLT_CONFIG_STATE_NOT_CONFIGURED = 0, /**< Not Configured. */
    BCMOLT_CONFIG_STATE_CONFIGURED = 1, /**< Configured. */
    BCMOLT_CONFIG_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_config_state;

/** control state. */
typedef enum
{
    BCMOLT_CONTROL_STATE__BEGIN = 0,
    BCMOLT_CONTROL_STATE_DISABLE = 0, /**< Disabled. */
    BCMOLT_CONTROL_STATE_ENABLE = 1, /**< Enabled. */
    BCMOLT_CONTROL_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_control_state;

/** DBA implementation type */
typedef enum
{
    BCMOLT_DBA_IMPLEMENTATION_TYPE__BEGIN = 0,
    BCMOLT_DBA_IMPLEMENTATION_TYPE_INTERNAL = 0, /**< Internal DBA implementation */
    BCMOLT_DBA_IMPLEMENTATION_TYPE_EXTERNAL = 1, /**< External DBA implementation */
    BCMOLT_DBA_IMPLEMENTATION_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_dba_implementation_type;

/** dba mode. */
typedef enum
{
    BCMOLT_DBA_MODE__BEGIN = 0,
    BCMOLT_DBA_MODE_NORMAL = 0, /**< normal. */
    BCMOLT_DBA_MODE_EXTENDED = 1, /**< extended. */
    BCMOLT_DBA_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_dba_mode;

/** Test mode of DDR memory */
typedef enum
{
    BCMOLT_DDR_TEST_MODE__BEGIN = 0,
    BCMOLT_DDR_TEST_MODE_NO_TEST = 0, /**< Test is not needed */
    BCMOLT_DDR_TEST_MODE_ALL_DDRS = 1, /**< All DDRs should be tested */
    BCMOLT_DDR_TEST_MODE_CPU_DDR = 2, /**< Only CPU DDR should be tested */
    BCMOLT_DDR_TEST_MODE_RAS_DDRS = 3, /**< RAS DDRs should be tested */
    BCMOLT_DDR_TEST_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ddr_test_mode;

/** DDR Test Result. */
typedef enum
{
    BCMOLT_DDR_TEST_RESULT__BEGIN = 0,
    BCMOLT_DDR_TEST_RESULT_SUCCESS = 0, /**< Success. */
    BCMOLT_DDR_TEST_RESULT_PHY_INIT_ERROR = 1, /**< PHY Init Error. */
    BCMOLT_DDR_TEST_RESULT_DRAM_INIT_ERROR = 2, /**< DRAM Init Error. */
    BCMOLT_DDR_TEST_RESULT_SHMOO_ERROR = 3, /**< SHMOO Error. */
    BCMOLT_DDR_TEST_RESULT_EDIS_TEST_ERROR = 4, /**< EDIS Test Error. */
    BCMOLT_DDR_TEST_RESULT_MEM_TEST_ERROR = 5, /**< Mem Test Error. */
    BCMOLT_DDR_TEST_RESULT_NOT_TESTED = 127, /**< Not Tested. */
    BCMOLT_DDR_TEST_RESULT__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ddr_test_result;

/** DDR Test Status. */
typedef enum
{
    BCMOLT_DDR_TEST_STATUS__BEGIN = 0,
    BCMOLT_DDR_TEST_STATUS_COMPLETED = 0, /**< The DDR test ran to completion */
    BCMOLT_DDR_TEST_STATUS_CONNECTION_FAILED = 1, /**< The DDR test failed due to an issue loading the bootloader */
    BCMOLT_DDR_TEST_STATUS_TIMEOUT = 2, /**< The DDR test failed to complete within the expected time */
    BCMOLT_DDR_TEST_STATUS__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ddr_test_status;

/** deactivation fail reason. */
typedef enum
{
    BCMOLT_DEACTIVATION_FAIL_REASON__BEGIN = 0,
    BCMOLT_DEACTIVATION_FAIL_REASON_NONE = 0, /**< None. */
    BCMOLT_DEACTIVATION_FAIL_REASON_FAIL = 1, /**< general_fail. */
    BCMOLT_DEACTIVATION_FAIL_REASON_SWITCH_OVER = 2, /**< protection switch over. */
    BCMOLT_DEACTIVATION_FAIL_REASON_FORCE_DEACTIVATION = 3, /**< force deactivation. */
    BCMOLT_DEACTIVATION_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_deactivation_fail_reason;

/** Revision of the BCM68620 device. */
typedef enum
{
    BCMOLT_DEVICE_CHIP_REVISION__BEGIN = 160,
    BCMOLT_DEVICE_CHIP_REVISION_A0 = 160, /**< A0. */
    BCMOLT_DEVICE_CHIP_REVISION_A1 = 161, /**< A1. */
    BCMOLT_DEVICE_CHIP_REVISION_B0 = 176, /**< B0. */
    BCMOLT_DEVICE_CHIP_REVISION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_device_chip_revision;

/** Device disconnect reason. */
typedef enum
{
    BCMOLT_DEVICE_DISCONNECT_REASON__BEGIN = 0,
    BCMOLT_DEVICE_DISCONNECT_REASON_FAILED_TO_CONNECT = 0, /**< failed_to_connect. */
    BCMOLT_DEVICE_DISCONNECT_REASON_DISCONNECT_REQUEST = 1, /**< disconnect_request. */
    BCMOLT_DEVICE_DISCONNECT_REASON_RESET_REQUEST = 2, /**< reset_request. */
    BCMOLT_DEVICE_DISCONNECT_REASON_KA_FAILURE = 3, /**< ka_failure. */
    BCMOLT_DEVICE_DISCONNECT_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_device_disconnect_reason;

/** Device Image Type. */
typedef enum
{
    BCMOLT_DEVICE_IMAGE_TYPE__BEGIN = 0,
    BCMOLT_DEVICE_IMAGE_TYPE_BOOTLOADER = 0, /**< Bootloader. */
    BCMOLT_DEVICE_IMAGE_TYPE_APPLICATION = 1, /**< Application. */
    BCMOLT_DEVICE_IMAGE_TYPE_ITU_PON_ONU_FIRMWARE = 2, /**< ITU PON ONU firmware. */
    BCMOLT_DEVICE_IMAGE_TYPE_EPON_ONU_FIRMWARE = 3, /**< EPON ONU firmware. */
    BCMOLT_DEVICE_IMAGE_TYPE_DDR_PHY = 4, /**< Aspen DDR PHY image. */
    BCMOLT_DEVICE_IMAGE_TYPE_CFE = 5, /**< CFE. */
    BCMOLT_DEVICE_IMAGE_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_device_image_type;

/** Disable Serial Number Control. */
typedef enum
{
    BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL__BEGIN = 0,
    BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_UNICAST_DISABLE = 0, /**< Unicast Disable. */
    BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_UNICAST_ENABLE = 1, /**< Unicast Enable. */
    BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_BROADCAST_ENABLE = 2, /**< Broadcast Enable. */
    BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_BROADCAST_DISABLE = 3, /**< Broadcast Disable. */
    BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_DISABLE_DISCOVERY = 4, /**< Disable Discovery. */
    BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_disable_serial_number_control;

/** eth duplex mode. */
typedef enum
{
    BCMOLT_DUPLEX_MODE__BEGIN = 0,
    BCMOLT_DUPLEX_MODE_FULL = 0, /**< full duplex. */
    BCMOLT_DUPLEX_MODE_HALF = 1, /**< half duplex. */
    BCMOLT_DUPLEX_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_duplex_mode;

/** egress_qos_type. */
typedef enum
{
    BCMOLT_EGRESS_QOS_TYPE__BEGIN = 0,
    BCMOLT_EGRESS_QOS_TYPE_FIXED_QUEUE = 0, /**< fixed queue */
    BCMOLT_EGRESS_QOS_TYPE_TC_TO_QUEUE = 1, /**< fixed tc base */
    BCMOLT_EGRESS_QOS_TYPE_PBIT_TO_TC = 2, /**< pbit to tc based */
    BCMOLT_EGRESS_QOS_TYPE_NONE = 3, /**< No egress qos */
    BCMOLT_EGRESS_QOS_TYPE_PRIORITY_TO_QUEUE = 4, /**< priority_to_queue. */
    BCMOLT_EGRESS_QOS_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_egress_qos_type;

/** embedded image transfer status. */
typedef enum
{
    BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS__BEGIN = 0,
    BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS_NONE = 0, /**< No file.  Transfer has never started for this entry. */
    BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS_IN_PROGRESS = 1, /**< Transfer has started and not finished. */
    BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS_SUCCESS = 2, /**< Transfer has finished successfully. */
    BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS_FAILURE = 3, /**< Transfer failed.  Typically due to CRC error. */
    BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_embedded_image_transfer_status;

/** erps_control. */
typedef enum
{
    BCMOLT_ERPS_CONTROL__BEGIN = 0,
    BCMOLT_ERPS_CONTROL_UNASSIGNED = 0, /**< unassigned. */
    BCMOLT_ERPS_CONTROL_BLOCK_PORT_RX = 1, /**< Block Port Rx. */
    BCMOLT_ERPS_CONTROL_BLOCK_PORT_TX = 2, /**< Block Port Tx. */
    BCMOLT_ERPS_CONTROL_UNBLOCK_PORT_RX = 3, /**< UnBlock Port Rx. */
    BCMOLT_ERPS_CONTROL_UNBLOCK_PORT_TX = 4, /**< Unblock Port Tx. */
    BCMOLT_ERPS_CONTROL_FLUSH_PORT = 5, /**< Flush Port. */
    BCMOLT_ERPS_CONTROL__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_erps_control;

/** East, West and sub_ports */
typedef enum
{
    BCMOLT_ERPS_PORT__BEGIN = 2,
    BCMOLT_ERPS_PORT_WEST_PORT = 2, /**< ERPS West Port Interface. */
    BCMOLT_ERPS_PORT_SUB_PORT = 3, /**< ERPS Subtended OLT Port. */
    BCMOLT_ERPS_PORT__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_erps_port;

/** External IRQ. */
typedef enum
{
    BCMOLT_EXT_IRQ_EXT_IRQ0 = 0, /**< External IRQ 0. */
    BCMOLT_EXT_IRQ_EXT_IRQ1 = 1, /**< External IRQ 1. */
    BCMOLT_EXT_IRQ_EXT_IRQ2 = 2, /**< External IRQ 2. */
    BCMOLT_EXT_IRQ_EXT_IRQ3 = 3, /**< External IRQ 3. */
    BCMOLT_EXT_IRQ_EXT_IRQ4 = 4, /**< External IRQ 4. */
    BCMOLT_EXT_IRQ_EXT_IRQ5 = 5, /**< External IRQ 5. */
    BCMOLT_EXT_IRQ_UNCONFIGURED = 255, /**< Unconfigured external IRQ. */
} bcmolt_ext_irq;

/** External DBA options */
typedef enum
{
    BCMOLT_EXTERNAL_DBA_OPTIONS_NONE = 0,
    BCMOLT_EXTERNAL_DBA_OPTIONS_STATS_IND = 0x0001, /**< Send statistics indication after each DBA buffer swap event */
} bcmolt_external_dba_options;

/** flow interface type */
typedef enum
{
    BCMOLT_FLOW_INTERFACE_TYPE_PON = 10, /**< flow pon interface */
    BCMOLT_FLOW_INTERFACE_TYPE_NNI = 11, /**< flow network interface */
    BCMOLT_FLOW_INTERFACE_TYPE_HOST = 12, /**< flow host interface */
    BCMOLT_FLOW_INTERFACE_TYPE_ERPS = 13, /**< flow erps */
    BCMOLT_FLOW_INTERFACE_TYPE_PROTECTION = 14, /**< flow protection pair */
    BCMOLT_FLOW_INTERFACE_TYPE_LAG = 15, /**< flow lag interface */
    BCMOLT_FLOW_INTERFACE_TYPE_UNASSIGNED = 255, /**< flow invalid interface */
} bcmolt_flow_interface_type;

/** Flow State. */
typedef enum
{
    BCMOLT_FLOW_STATE__BEGIN = 0,
    BCMOLT_FLOW_STATE_NOT_CONFIGURED = 0, /**< not_configured. */
    BCMOLT_FLOW_STATE_DISABLE = 1, /**< disable. */
    BCMOLT_FLOW_STATE_ENABLE = 2, /**< enable. */
    BCMOLT_FLOW_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_flow_state;

/** Flow Type. */
typedef enum
{
    BCMOLT_FLOW_TYPE__BEGIN = 0,
    BCMOLT_FLOW_TYPE_UPSTREAM = 0, /**< Upstream flow */
    BCMOLT_FLOW_TYPE_DOWNSTREAM = 1, /**< Downstream Flow */
    BCMOLT_FLOW_TYPE_MULTICAST = 2, /**< Multicast Flow */
    BCMOLT_FLOW_TYPE_XCONNECT = 3, /**< Specific flow uses the Cross Connect construct in the switch. Used for ERPS nni to nni flows. */
    BCMOLT_FLOW_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_flow_type;

/** Frequency adjustment direction */
typedef enum
{
    BCMOLT_FREQUENCY_ADJUSTMENT_DIRECTION__BEGIN = 0,
    BCMOLT_FREQUENCY_ADJUSTMENT_DIRECTION_LOWER = 0, /**< Lower */
    BCMOLT_FREQUENCY_ADJUSTMENT_DIRECTION_HIGHER = 1, /**< Higher */
    BCMOLT_FREQUENCY_ADJUSTMENT_DIRECTION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_frequency_adjustment_direction;

/** GEM port ID direction. */
typedef enum
{
    BCMOLT_GEM_PORT_DIRECTION__BEGIN = 0,
    BCMOLT_GEM_PORT_DIRECTION_DOWNSTREAM = 0, /**< downstream port ID. */
    BCMOLT_GEM_PORT_DIRECTION_UPSTREAM = 1, /**< upstream port ID. */
    BCMOLT_GEM_PORT_DIRECTION_BIDIRECTIONAL = 2, /**< bidirectional port  ID. */
    BCMOLT_GEM_PORT_DIRECTION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_gem_port_direction;

/** GEM port operation. */
typedef enum
{
    BCMOLT_GEM_PORT_OPERATION__BEGIN = 0,
    BCMOLT_GEM_PORT_OPERATION_ACTIVATE = 0, /**< Activate. */
    BCMOLT_GEM_PORT_OPERATION_DEACTIVATE = 1, /**< Deactivate. */
    BCMOLT_GEM_PORT_OPERATION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_gem_port_operation;

/** GEM port type. */
typedef enum
{
    BCMOLT_GEM_PORT_TYPE__BEGIN = 0,
    BCMOLT_GEM_PORT_TYPE_UNICAST = 0, /**< unicast port ID. */
    BCMOLT_GEM_PORT_TYPE_MULTICAST = 1, /**< multicast port ID. */
    BCMOLT_GEM_PORT_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_gem_port_type;

/** GPIO pin number. */
typedef enum
{
    BCMOLT_GPIO_PIN_PIN0 = 0, /**< GPIO pin 0. */
    BCMOLT_GPIO_PIN_PIN1 = 1, /**< GPIO pin 1. */
    BCMOLT_GPIO_PIN_PIN2 = 2, /**< GPIO pin 2. */
    BCMOLT_GPIO_PIN_PIN3 = 3, /**< GPIO pin 3. */
    BCMOLT_GPIO_PIN_PIN4 = 4, /**< GPIO pin 4. */
    BCMOLT_GPIO_PIN_PIN5 = 5, /**< GPIO pin 5. */
    BCMOLT_GPIO_PIN_PIN6 = 6, /**< GPIO pin 6. */
    BCMOLT_GPIO_PIN_PIN7 = 7, /**< GPIO pin 7. */
    BCMOLT_GPIO_PIN_PIN8 = 8, /**< GPIO pin 8. */
    BCMOLT_GPIO_PIN_PIN9 = 9, /**< GPIO pin 9. */
    BCMOLT_GPIO_PIN_PIN10 = 10, /**< GPIO pin 10. */
    BCMOLT_GPIO_PIN_PIN11 = 11, /**< GPIO pin 11. */
    BCMOLT_GPIO_PIN_PIN12 = 12, /**< GPIO pin 12. */
    BCMOLT_GPIO_PIN_PIN13 = 13, /**< GPIO pin 13. */
    BCMOLT_GPIO_PIN_PIN14 = 14, /**< GPIO pin 14. */
    BCMOLT_GPIO_PIN_PIN15 = 15, /**< GPIO pin 15. */
    BCMOLT_GPIO_PIN_PIN16 = 16, /**< GPIO pin 16. */
    BCMOLT_GPIO_PIN_PIN17 = 17, /**< GPIO pin 17. */
    BCMOLT_GPIO_PIN_PIN18 = 18, /**< GPIO pin 18. */
    BCMOLT_GPIO_PIN_PIN19 = 19, /**< GPIO pin 19. */
    BCMOLT_GPIO_PIN_PIN20 = 20, /**< GPIO pin 20. */
    BCMOLT_GPIO_PIN_PIN21 = 21, /**< GPIO pin 21. */
    BCMOLT_GPIO_PIN_PIN22 = 22, /**< GPIO pin 22. */
    BCMOLT_GPIO_PIN_PIN23 = 23, /**< GPIO pin 23. */
    BCMOLT_GPIO_PIN_PIN24 = 24, /**< GPIO pin 24. */
    BCMOLT_GPIO_PIN_PIN25 = 25, /**< GPIO pin 25. */
    BCMOLT_GPIO_PIN_PIN26 = 26, /**< GPIO pin 26. */
    BCMOLT_GPIO_PIN_PIN27 = 27, /**< GPIO pin 27. */
    BCMOLT_GPIO_PIN_PIN28 = 28, /**< GPIO pin 28. */
    BCMOLT_GPIO_PIN_PIN29 = 29, /**< GPIO pin 29. */
    BCMOLT_GPIO_PIN_PIN30 = 30, /**< GPIO pin 30. */
    BCMOLT_GPIO_PIN_PIN31 = 31, /**< GPIO pin 31. */
    BCMOLT_GPIO_PIN_PIN32 = 32, /**< GPIO pin 32. */
    BCMOLT_GPIO_PIN_PIN33 = 33, /**< GPIO pin 33. */
    BCMOLT_GPIO_PIN_PIN34 = 34, /**< GPIO pin 34. */
    BCMOLT_GPIO_PIN_PIN35 = 35, /**< GPIO pin 35. */
    BCMOLT_GPIO_PIN_PIN36 = 36, /**< GPIO pin 36. */
    BCMOLT_GPIO_PIN_PIN37 = 37, /**< GPIO pin 37. */
    BCMOLT_GPIO_PIN_PIN38 = 38, /**< GPIO pin 38. */
    BCMOLT_GPIO_PIN_PIN39 = 39, /**< GPIO pin 39. */
    BCMOLT_GPIO_PIN_PIN40 = 40, /**< GPIO pin 40. */
    BCMOLT_GPIO_PIN_PIN41 = 41, /**< GPIO pin 41. */
    BCMOLT_GPIO_PIN_PIN42 = 42, /**< GPIO pin 42. */
    BCMOLT_GPIO_PIN_PIN43 = 43, /**< GPIO pin 43. */
    BCMOLT_GPIO_PIN_PIN44 = 44, /**< GPIO pin 44. */
    BCMOLT_GPIO_PIN_PIN45 = 45, /**< GPIO pin 45. */
    BCMOLT_GPIO_PIN_PIN46 = 46, /**< GPIO pin 46. */
    BCMOLT_GPIO_PIN_PIN47 = 47, /**< GPIO pin 47. */
    BCMOLT_GPIO_PIN_PIN48 = 48, /**< GPIO pin 48. */
    BCMOLT_GPIO_PIN_PIN49 = 49, /**< GPIO pin 49. */
    BCMOLT_GPIO_PIN_PIN50 = 50, /**< GPIO pin 50. */
    BCMOLT_GPIO_PIN_PIN51 = 51, /**< GPIO pin 51. */
    BCMOLT_GPIO_PIN_PIN52 = 52, /**< GPIO pin 52. */
    BCMOLT_GPIO_PIN_PIN53 = 53, /**< GPIO pin 53. */
    BCMOLT_GPIO_PIN_PIN54 = 54, /**< GPIO pin 54. */
    BCMOLT_GPIO_PIN_PIN55 = 55, /**< GPIO pin 55. */
    BCMOLT_GPIO_PIN_PIN56 = 56, /**< GPIO pin 56. */
    BCMOLT_GPIO_PIN_PIN57 = 57, /**< GPIO pin 57. */
    BCMOLT_GPIO_PIN_PIN58 = 58, /**< GPIO pin 58. */
    BCMOLT_GPIO_PIN_PIN59 = 59, /**< GPIO pin 59. */
    BCMOLT_GPIO_PIN_PIN60 = 60, /**< GPIO pin 60. */
    BCMOLT_GPIO_PIN_PIN61 = 61, /**< GPIO pin 61. */
    BCMOLT_GPIO_PIN_PIN62 = 62, /**< GPIO pin 62. */
    BCMOLT_GPIO_PIN_PIN63 = 63, /**< GPIO pin 63. */
    BCMOLT_GPIO_PIN_PIN64 = 64, /**< GPIO pin 64. */
    BCMOLT_GPIO_PIN_PIN65 = 65, /**< GPIO pin 65. */
    BCMOLT_GPIO_PIN_PIN66 = 66, /**< GPIO pin 66. */
    BCMOLT_GPIO_PIN_PIN67 = 67, /**< GPIO pin 67. */
    BCMOLT_GPIO_PIN_PIN68 = 68, /**< GPIO pin 68. */
    BCMOLT_GPIO_PIN_PIN69 = 69, /**< GPIO pin 69. */
    BCMOLT_GPIO_PIN_PIN70 = 70, /**< GPIO pin 70. */
    BCMOLT_GPIO_PIN_PIN71 = 71, /**< GPIO pin 71. */
    BCMOLT_GPIO_PIN_PIN72 = 72, /**< GPIO pin 72. */
    BCMOLT_GPIO_PIN_PIN73 = 73, /**< GPIO pin 73. */
    BCMOLT_GPIO_PIN_PIN74 = 74, /**< GPIO pin 74. */
    BCMOLT_GPIO_PIN_PIN75 = 75, /**< GPIO pin 75. */
    BCMOLT_GPIO_PIN_PIN76 = 76, /**< GPIO pin 76. */
    BCMOLT_GPIO_PIN_PIN77 = 77, /**< GPIO pin 77. */
    BCMOLT_GPIO_PIN_PIN78 = 78, /**< GPIO pin 78. */
    BCMOLT_GPIO_PIN_PIN79 = 79, /**< GPIO pin 79. */
    BCMOLT_GPIO_PIN_PIN80 = 80, /**< GPIO pin 80. */
    BCMOLT_GPIO_PIN_PIN81 = 81, /**< GPIO pin 81. */
    BCMOLT_GPIO_PIN_PIN82 = 82, /**< GPIO pin 82. */
    BCMOLT_GPIO_PIN_PIN83 = 83, /**< GPIO pin 83. */
    BCMOLT_GPIO_PIN_PIN84 = 84, /**< GPIO pin 84. */
    BCMOLT_GPIO_PIN_PIN85 = 85, /**< GPIO pin 85. */
    BCMOLT_GPIO_PIN_PIN86 = 86, /**< GPIO pin 86. */
    BCMOLT_GPIO_PIN_PIN87 = 87, /**< GPIO pin 87. */
    BCMOLT_GPIO_PIN_PIN88 = 88, /**< GPIO pin 88. */
    BCMOLT_GPIO_PIN_PIN89 = 89, /**< GPIO pin 89. */
    BCMOLT_GPIO_PIN_PIN90 = 90, /**< GPIO pin 90. */
    BCMOLT_GPIO_PIN_PIN91 = 91, /**< GPIO pin 91. */
    BCMOLT_GPIO_PIN_PIN92 = 92, /**< GPIO pin 92. */
    BCMOLT_GPIO_PIN_PIN93 = 93, /**< GPIO pin 93. */
    BCMOLT_GPIO_PIN_PIN94 = 94, /**< GPIO pin 94. */
    BCMOLT_GPIO_PIN_PIN95 = 95, /**< GPIO pin 95. */
    BCMOLT_GPIO_PIN_PIN96 = 96, /**< GPIO pin 96. */
    BCMOLT_GPIO_PIN_PIN97 = 97, /**< GPIO pin 97. */
    BCMOLT_GPIO_PIN_PIN98 = 98, /**< GPIO pin 98. */
    BCMOLT_GPIO_PIN_PIN99 = 99, /**< GPIO pin 99. */
    BCMOLT_GPIO_PIN_PIN100 = 100, /**< GPIO pin 100. */
    BCMOLT_GPIO_PIN_PIN101 = 101, /**< GPIO pin 101. */
    BCMOLT_GPIO_PIN_PIN102 = 102, /**< GPIO pin 102. */
    BCMOLT_GPIO_PIN_PIN103 = 103, /**< GPIO pin 103. */
    BCMOLT_GPIO_PIN_PIN104 = 104, /**< GPIO pin 104. */
    BCMOLT_GPIO_PIN_PIN105 = 105, /**< GPIO pin 105. */
    BCMOLT_GPIO_PIN_PIN106 = 106, /**< GPIO pin 106. */
    BCMOLT_GPIO_PIN_PIN107 = 107, /**< GPIO pin 107. */
    BCMOLT_GPIO_PIN_PIN108 = 108, /**< GPIO pin 108. */
    BCMOLT_GPIO_PIN_PIN109 = 109, /**< GPIO pin 109. */
    BCMOLT_GPIO_PIN_PIN110 = 110, /**< GPIO pin 110. */
    BCMOLT_GPIO_PIN_PIN111 = 111, /**< GPIO pin 111. */
    BCMOLT_GPIO_PIN_PIN112 = 112, /**< GPIO pin 112. */
    BCMOLT_GPIO_PIN_PIN113 = 113, /**< GPIO pin 113. */
    BCMOLT_GPIO_PIN_PIN114 = 114, /**< GPIO pin 114. */
    BCMOLT_GPIO_PIN_PIN115 = 115, /**< GPIO pin 115. */
    BCMOLT_GPIO_PIN_PIN116 = 116, /**< GPIO pin 116. */
    BCMOLT_GPIO_PIN_PIN117 = 117, /**< GPIO pin 117. */
    BCMOLT_GPIO_PIN_PIN118 = 118, /**< GPIO pin 118. */
    BCMOLT_GPIO_PIN_PIN119 = 119, /**< GPIO pin 119. */
    BCMOLT_GPIO_PIN_PIN120 = 120, /**< GPIO pin 120. */
    BCMOLT_GPIO_PIN_PIN121 = 121, /**< GPIO pin 121. */
    BCMOLT_GPIO_PIN_PIN122 = 122, /**< GPIO pin 122. */
    BCMOLT_GPIO_PIN_PIN123 = 123, /**< GPIO pin 123. */
    BCMOLT_GPIO_PIN_PIN124 = 124, /**< GPIO pin 124. */
    BCMOLT_GPIO_PIN_PIN125 = 125, /**< GPIO pin 125. */
    BCMOLT_GPIO_PIN_PIN126 = 126, /**< GPIO pin 126. */
    BCMOLT_GPIO_PIN_PIN127 = 127, /**< GPIO pin 127. */
    BCMOLT_GPIO_PIN_PIN128 = 128, /**< GPIO pin 128. */
    BCMOLT_GPIO_PIN_PIN129 = 129, /**< GPIO pin 129. */
    BCMOLT_GPIO_PIN_PIN130 = 130, /**< GPIO pin 130. */
    BCMOLT_GPIO_PIN_PIN131 = 131, /**< GPIO pin 131. */
    BCMOLT_GPIO_PIN_PIN132 = 132, /**< GPIO pin 132. */
    BCMOLT_GPIO_PIN_PIN133 = 133, /**< GPIO pin 133. */
    BCMOLT_GPIO_PIN_PIN134 = 134, /**< GPIO pin 134. */
    BCMOLT_GPIO_PIN_PIN135 = 135, /**< GPIO pin 135. */
    BCMOLT_GPIO_PIN_PIN136 = 136, /**< GPIO pin 136. */
    BCMOLT_GPIO_PIN_PIN137 = 137, /**< GPIO pin 137. */
    BCMOLT_GPIO_PIN_PIN138 = 138, /**< GPIO pin 138. */
    BCMOLT_GPIO_PIN_PIN139 = 139, /**< GPIO pin 139. */
    BCMOLT_GPIO_PIN_PIN140 = 140, /**< GPIO pin 140. */
    BCMOLT_GPIO_PIN_PIN141 = 141, /**< GPIO pin 141. */
    BCMOLT_GPIO_PIN_PIN142 = 142, /**< GPIO pin 142. */
    BCMOLT_GPIO_PIN_PIN143 = 143, /**< GPIO pin 143. */
    BCMOLT_GPIO_PIN_PIN144 = 144, /**< GPIO pin 144. */
    BCMOLT_GPIO_PIN_PIN145 = 145, /**< GPIO pin 145. */
    BCMOLT_GPIO_PIN_PIN146 = 146, /**< GPIO pin 146. */
    BCMOLT_GPIO_PIN_PIN147 = 147, /**< GPIO pin 147. */
    BCMOLT_GPIO_PIN_PIN148 = 148, /**< GPIO pin 148. */
    BCMOLT_GPIO_PIN_PIN149 = 149, /**< GPIO pin 149. */
    BCMOLT_GPIO_PIN_PIN150 = 150, /**< GPIO pin 150. */
    BCMOLT_GPIO_PIN_PIN151 = 151, /**< GPIO pin 151. */
    BCMOLT_GPIO_PIN_PIN152 = 152, /**< GPIO pin 152. */
    BCMOLT_GPIO_PIN_PIN153 = 153, /**< GPIO pin 153. */
    BCMOLT_GPIO_PIN_PIN154 = 154, /**< GPIO pin 154. */
    BCMOLT_GPIO_PIN_PIN155 = 155, /**< GPIO pin 155. */
    BCMOLT_GPIO_PIN_PIN156 = 156, /**< GPIO pin 156. */
    BCMOLT_GPIO_PIN_PIN157 = 157, /**< GPIO pin 157. */
    BCMOLT_GPIO_PIN_PIN158 = 158, /**< GPIO pin 158. */
    BCMOLT_GPIO_PIN_PIN159 = 159, /**< GPIO pin 159. */
    BCMOLT_GPIO_PIN_PIN160 = 160, /**< GPIO pin 160. */
    BCMOLT_GPIO_PIN_PIN161 = 161, /**< GPIO pin 161. */
    BCMOLT_GPIO_PIN_PIN162 = 162, /**< GPIO pin 162. */
    BCMOLT_GPIO_PIN_PIN163 = 163, /**< GPIO pin 163. */
    BCMOLT_GPIO_PIN_PIN164 = 164, /**< GPIO pin 164. */
    BCMOLT_GPIO_PIN_PIN165 = 165, /**< GPIO pin 165. */
    BCMOLT_GPIO_PIN_PIN166 = 166, /**< GPIO pin 166. */
    BCMOLT_GPIO_PIN_PIN167 = 167, /**< GPIO pin 167. */
    BCMOLT_GPIO_PIN_PIN168 = 168, /**< GPIO pin 168. */
    BCMOLT_GPIO_PIN_PIN169 = 169, /**< GPIO pin 169. */
    BCMOLT_GPIO_PIN_PIN170 = 170, /**< GPIO pin 170. */
    BCMOLT_GPIO_PIN_PIN171 = 171, /**< GPIO pin 171. */
    BCMOLT_GPIO_PIN_PIN172 = 172, /**< GPIO pin 172. */
    BCMOLT_GPIO_PIN_PIN173 = 173, /**< GPIO pin 173. */
    BCMOLT_GPIO_PIN_PIN174 = 174, /**< GPIO pin 174. */
    BCMOLT_GPIO_PIN_PIN175 = 175, /**< GPIO pin 175. */
    BCMOLT_GPIO_PIN_PIN176 = 176, /**< GPIO pin 176. */
    BCMOLT_GPIO_PIN_PIN177 = 177, /**< GPIO pin 177. */
    BCMOLT_GPIO_PIN_PIN178 = 178, /**< GPIO pin 178. */
    BCMOLT_GPIO_PIN_PIN179 = 179, /**< GPIO pin 179. */
    BCMOLT_GPIO_PIN_PIN180 = 180, /**< GPIO pin 180. */
    BCMOLT_GPIO_PIN_PIN181 = 181, /**< GPIO pin 181. */
    BCMOLT_GPIO_PIN_PIN182 = 182, /**< GPIO pin 182. */
    BCMOLT_GPIO_PIN_PIN183 = 183, /**< GPIO pin 183. */
    BCMOLT_GPIO_PIN_PIN184 = 184, /**< GPIO pin 184. */
    BCMOLT_GPIO_PIN_PIN185 = 185, /**< GPIO pin 185. */
    BCMOLT_GPIO_PIN_PIN186 = 186, /**< GPIO pin 186. */
    BCMOLT_GPIO_PIN_PIN187 = 187, /**< GPIO pin 187. */
    BCMOLT_GPIO_PIN_PIN188 = 188, /**< GPIO pin 188. */
    BCMOLT_GPIO_PIN_PIN189 = 189, /**< GPIO pin 189. */
    BCMOLT_GPIO_PIN_PIN190 = 190, /**< GPIO pin 190. */
    BCMOLT_GPIO_PIN_PIN191 = 191, /**< GPIO pin 191. */
    BCMOLT_GPIO_PIN_PIN192 = 192, /**< GPIO pin 192. */
    BCMOLT_GPIO_PIN_PIN193 = 193, /**< GPIO pin 193. */
    BCMOLT_GPIO_PIN_PIN194 = 194, /**< GPIO pin 194. */
    BCMOLT_GPIO_PIN_PIN195 = 195, /**< GPIO pin 195. */
    BCMOLT_GPIO_PIN_PIN196 = 196, /**< GPIO pin 196. */
    BCMOLT_GPIO_PIN_PIN197 = 197, /**< GPIO pin 197. */
    BCMOLT_GPIO_PIN_PIN198 = 198, /**< GPIO pin 198. */
    BCMOLT_GPIO_PIN_PIN199 = 199, /**< GPIO pin 199. */
    BCMOLT_GPIO_PIN_PIN200 = 200, /**< GPIO pin 200. */
    BCMOLT_GPIO_PIN_PIN201 = 201, /**< GPIO pin 201. */
    BCMOLT_GPIO_PIN_PIN202 = 202, /**< GPIO pin 202. */
    BCMOLT_GPIO_PIN_PIN203 = 203, /**< GPIO pin 203. */
    BCMOLT_GPIO_PIN_PIN204 = 204, /**< GPIO pin 204. */
    BCMOLT_GPIO_PIN_PIN205 = 205, /**< GPIO pin 205. */
    BCMOLT_GPIO_PIN_UNCONFIGURED = 255, /**< Unconfigured GPIO pin. */
} bcmolt_gpio_pin;

/** GPIO PIN Direction. */
typedef enum
{
    BCMOLT_GPIO_PIN_DIR__BEGIN = 0,
    BCMOLT_GPIO_PIN_DIR_INPUT = 0, /**< Input. */
    BCMOLT_GPIO_PIN_DIR_OUTPUT = 1, /**< Output. */
    BCMOLT_GPIO_PIN_DIR__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_gpio_pin_dir;

/** GPIO Polarity. */
typedef enum
{
    BCMOLT_GPIO_POLARITY__BEGIN = 0,
    BCMOLT_GPIO_POLARITY_ACTIVE_LOW = 0, /**< Active Low. */
    BCMOLT_GPIO_POLARITY_ACTIVE_HIGH = 1, /**< Active High. */
    BCMOLT_GPIO_POLARITY__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_gpio_polarity;

/** GPIO Value. */
typedef enum
{
    BCMOLT_GPIO_VALUE__BEGIN = 0,
    BCMOLT_GPIO_VALUE_CLEAR = 0, /**< Clear. */
    BCMOLT_GPIO_VALUE_SET = 1, /**< Set. */
    BCMOLT_GPIO_VALUE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_gpio_value;

/** Key exchange mode. */
typedef enum
{
    BCMOLT_GPON_KEY_EXCHANGE_MODE__BEGIN = 0,
    BCMOLT_GPON_KEY_EXCHANGE_MODE_NORMAL = 0, /**< Normal. */
    BCMOLT_GPON_KEY_EXCHANGE_MODE_ENHANCED = 1, /**< Enhanced. */
    BCMOLT_GPON_KEY_EXCHANGE_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_gpon_key_exchange_mode;

/** group_member_update_fail_reaso */
typedef enum
{
    BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON__BEGIN = 0,
    BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_NONE = 0, /**< none */
    BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_PARM = 1, /**< invalid  parameter */
    BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_INTERNAL = 2, /**< internal */
    BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_SW = 3, /**< fail in switch configuration */
    BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_MAC = 4, /**< fail in mac configuration */
    BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_SVC_PORT_MISS_MATCH = 5, /**< svc port id type miss match */
    BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_QOS = 6, /**< qos set invalid */
    BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_group_member_update_fail_reason;

/** group state */
typedef enum
{
    BCMOLT_GROUP_STATE__BEGIN = 0,
    BCMOLT_GROUP_STATE_NOT_CONFIGURED = 0, /**< not_configured */
    BCMOLT_GROUP_STATE_CONFIGURED = 1, /**< configured */
    BCMOLT_GROUP_STATE_ACTIVE = 2, /**< active */
    BCMOLT_GROUP_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_group_state;

/** type of a group */
typedef enum
{
    BCMOLT_GROUP_TYPE__BEGIN = 0,
    BCMOLT_GROUP_TYPE_NONE = 0, /**< type not set */
    BCMOLT_GROUP_TYPE_MULTICAST = 1, /**< multicast group */
    BCMOLT_GROUP_TYPE_N_TO_1 = 2, /**< N:1 Group */
    BCMOLT_GROUP_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_group_type;

/** Reasons why the connection between the host and the device failed */
typedef enum
{
    BCMOLT_HOST_CONNECTION_FAIL_REASON__BEGIN = 0,
    BCMOLT_HOST_CONNECTION_FAIL_REASON_TIMEOUT = 0, /**< The connection process has timed out. */
    BCMOLT_HOST_CONNECTION_FAIL_REASON_KEEPALIVE = 1, /**< Too much time has passed between keepalive messages from the device. */
    BCMOLT_HOST_CONNECTION_FAIL_REASON_SOFTWARE_VERSION_MISMATCH = 2, /**< The software version on the running device doesn't match the version in the host software.  Only the revision number is allowed to differ - major/minor/model must match. */
    BCMOLT_HOST_CONNECTION_FAIL_REASON_CONNECTION_PARAM_MISMATCH = 3, /**< Connection parameter (system mode or inni config) cannot be changed when reconnecting. */
    BCMOLT_HOST_CONNECTION_FAIL_REASON_RECONNECT_TIMEOUT = 4, /**< A running device didn't respond to the request to reconnect. */
    BCMOLT_HOST_CONNECTION_FAIL_REASON_INTERNAL_ERROR = 5, /**< An unspecified internal error occurred - check the log output for details. */
    BCMOLT_HOST_CONNECTION_FAIL_REASON_SYSTEM_MODE_NOT_SUPPORTED = 6, /**< The given system mode is not supported on this device. */
    BCMOLT_HOST_CONNECTION_FAIL_REASON_PARAMETER = 7, /**< One of the initial connection parameters was incorrect. */
    BCMOLT_HOST_CONNECTION_FAIL_REASON_DDR_TEST_FAIL = 8, /**< Initialization or memory test of one or more DDRs failed. */
    BCMOLT_HOST_CONNECTION_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_host_connection_fail_reason;

/** Host Log File ID. */
typedef enum
{
    BCMOLT_HOST_LOG_FILE_ID__BEGIN = 0,
    BCMOLT_HOST_LOG_FILE_ID_SRAM = 0, /**< SRAM. */
    BCMOLT_HOST_LOG_FILE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_host_log_file_id;

/** Image transfer status. */
typedef enum
{
    BCMOLT_IMAGE_TRANSFER_STATUS__BEGIN = 0,
    BCMOLT_IMAGE_TRANSFER_STATUS_SUCCESS = 0, /**< Success. */
    BCMOLT_IMAGE_TRANSFER_STATUS_MEMORY_ALLOCATION_FAILURE = 1, /**< Memory allocation failure. */
    BCMOLT_IMAGE_TRANSFER_STATUS_UNSUPPORTED_FILE_TYPE = 2, /**< Unsupported file type. */
    BCMOLT_IMAGE_TRANSFER_STATUS_CRC_ERROR = 3, /**< CRC checksum error. */
    BCMOLT_IMAGE_TRANSFER_STATUS_BLOCK_OUT_OF_SYNC = 4, /**< Block out of sync. */
    BCMOLT_IMAGE_TRANSFER_STATUS_INTERNAL_ERROR = 5, /**< Internal error. */
    BCMOLT_IMAGE_TRANSFER_STATUS_INVALID_STATE = 6, /**< Invalid state. */
    BCMOLT_IMAGE_TRANSFER_STATUS_PREMATURE_TERMINATION = 7, /**< Premature termination. */
    BCMOLT_IMAGE_TRANSFER_STATUS_ACK_TIMEOUT = 8, /**< ACK timeout. */
    BCMOLT_IMAGE_TRANSFER_STATUS__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_image_transfer_status;

/** Action on Inband Mgmt Vlan Tag. */
typedef enum
{
    BCMOLT_INBAND_MGMT_ACTION_TYPE__BEGIN = 0,
    BCMOLT_INBAND_MGMT_ACTION_TYPE_NONE = 0, /**< no action (transparent pass through for matching Vlan tag). */
    BCMOLT_INBAND_MGMT_ACTION_TYPE_REMOVE_ADD_OUTER_TAG = 1, /**< remove Vlan on downstream / conversely Add Vlan tag on Upstream. */
    BCMOLT_INBAND_MGMT_ACTION_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_inband_mgmt_action_type;

/** State of the inband management channel. */
typedef enum
{
    BCMOLT_INBAND_MGMT_STATE__BEGIN = 0,
    BCMOLT_INBAND_MGMT_STATE_NOT_CONFIGURED = 0, /**< not configured. */
    BCMOLT_INBAND_MGMT_STATE_CONFIGURED = 1, /**< configured. */
    BCMOLT_INBAND_MGMT_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_inband_mgmt_state;

/** Inject Type. */
typedef enum
{
    BCMOLT_INJECT_TYPE__BEGIN = 0,
    BCMOLT_INJECT_TYPE_INJECT_AT_EGRESS = 0, /**< Inject packet at Egress Port */
    BCMOLT_INJECT_TYPE_INJECT_AT_INGRESS = 1, /**< Inject packet at Ingress Port */
    BCMOLT_INJECT_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_inject_type;

/** The FEC mode that the INNI should use.  Options are:
  * 1.  mode default - use the default mode for the rate and physical layer
  * 2.  RS FEC (CL91/CL108)
  * 3.  FC FEC (CL74)
  * 4.  Use auto negotiation to select a mode. */
typedef enum
{
    BCMOLT_INNI_FEC_MODES__BEGIN = 0,
    BCMOLT_INNI_FEC_MODES_NONE = 0, /**< No FEC */
    BCMOLT_INNI_FEC_MODES_RS_FEC = 1, /**< Clause 91/108 FEC */
    BCMOLT_INNI_FEC_MODES_FC_FEC = 2, /**< CLause 74 FEC */
    BCMOLT_INNI_FEC_MODES_AUTO_NEGOTIATE = 3, /**< Select FEC using CL73 Auto Negotiation */
    BCMOLT_INNI_FEC_MODES__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_inni_fec_modes;

/** Availabke INNI Lanes. */
typedef enum
{
    BCMOLT_INNI_LANES__BEGIN = 0,
    BCMOLT_INNI_LANES_ALL = 0, /**< Standard redundancy:
    
    Lanes 0 and 1 of each Port Macro form one protecion Pair, and Lanes 2 and 3 form the other protection pair. */
    BCMOLT_INNI_LANES_EVEN = 1, /**< Even Port Redundancy:
    
    Lanes 0 and 2 of each Port Macro form the protecion Pair, and Lanes 1 and 3 are unused. */
    BCMOLT_INNI_LANES__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_inni_lanes;

/** Interface Operation. */
typedef enum
{
    BCMOLT_INTERFACE_OPERATION__BEGIN = 0,
    BCMOLT_INTERFACE_OPERATION_INACTIVE = 0, /**< Inactive. */
    BCMOLT_INTERFACE_OPERATION_ACTIVE_WORKING = 1, /**< Active Working. */
    BCMOLT_INTERFACE_OPERATION_ACTIVE_STANDBY = 2, /**< Active Standby. */
    BCMOLT_INTERFACE_OPERATION_DISABLE = 3, /**< Disable. */
    BCMOLT_INTERFACE_OPERATION_ENABLE = 4, /**< Enable. */
    BCMOLT_INTERFACE_OPERATION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_interface_operation;

/** Interface state. */
typedef enum
{
    BCMOLT_INTERFACE_STATE__BEGIN = 0,
    BCMOLT_INTERFACE_STATE_INACTIVE = 0, /**< Inactive. */
    BCMOLT_INTERFACE_STATE_PROCESSING = 1, /**< Processing. */
    BCMOLT_INTERFACE_STATE_ACTIVE_WORKING = 2, /**< Active Working. */
    BCMOLT_INTERFACE_STATE_ACTIVE_STANDBY = 3, /**< Active Standby. */
    BCMOLT_INTERFACE_STATE_DISABLED = 4, /**< Disabled. */
    BCMOLT_INTERFACE_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_interface_state;

/** Interface Type */
typedef enum
{
    BCMOLT_INTERFACE_TYPE__BEGIN = 0,
    BCMOLT_INTERFACE_TYPE_PON = 0, /**< ITU PON Access Interface */
    BCMOLT_INTERFACE_TYPE_NNI = 1, /**< NNI */
    BCMOLT_INTERFACE_TYPE_HOST = 2, /**< Host */
    BCMOLT_INTERFACE_TYPE_EPON_1_G = 3, /**< Epon 1G Access Interface */
    BCMOLT_INTERFACE_TYPE_EPON_10_G = 4, /**< Epon 10G Access Interface */
    BCMOLT_INTERFACE_TYPE_ERPS = 5, /**< ERPS Ring Interface */
    BCMOLT_INTERFACE_TYPE_LAG = 6, /**< NNI LAG group */
    BCMOLT_INTERFACE_TYPE_PROTECTION = 7, /**< PON, NNI or LAG 1 to 1 Redundancy Pair, subtype indicated in underlying protection_interface intf_ref fields */
    BCMOLT_INTERFACE_TYPE_UNASSIGNED = 8, /**< No Type Assigned */
    BCMOLT_INTERFACE_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_interface_type;

/** Internal NNI Redundancy. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_REDUNDANCY__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_REDUNDANCY_NONE = 0, /**< No Redundancy. */
    BCMOLT_INTERNAL_NNI_REDUNDANCY_MANUAL = 1, /**< Redundancy with Manual Switching. */
    BCMOLT_INTERNAL_NNI_REDUNDANCY_AUTOSWITCH = 2, /**< Automatically switch between primary/backup NNIs when Loss of Link is detected. */
    BCMOLT_INTERNAL_NNI_REDUNDANCY_GPIO = 3, /**< Switch based on a GPIO pin */
    BCMOLT_INTERNAL_NNI_REDUNDANCY__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_internal_nni_redundancy;

/** Interface Option flags */
typedef enum
{
    BCMOLT_INTF_OPT_NONE = 0,
    BCMOLT_INTF_OPT_ERPS_EXCLUDE_FROM_MC_GROUP = 0x01, /**< Exclude this ERPS Port from MC Flooding Group */
} bcmolt_intf_opt;

/** LAG hash field flags. */
typedef enum
{
    BCMOLT_LAG_HASH_FIELD_FLAGS_NONE = 0,
    BCMOLT_LAG_HASH_FIELD_FLAGS_DEST_MAC = 0x0001, /**< dest mac. */
    BCMOLT_LAG_HASH_FIELD_FLAGS_SRC_MAC = 0x0002, /**< src mac. */
    BCMOLT_LAG_HASH_FIELD_FLAGS_VLAN = 0x0004, /**< vlan. */
    BCMOLT_LAG_HASH_FIELD_FLAGS_ETHERTYPE = 0x0008, /**< ethertype. */
    BCMOLT_LAG_HASH_FIELD_FLAGS_DST_IP_V_4 = 0x0010, /**< IPV4 dest ip addr. */
    BCMOLT_LAG_HASH_FIELD_FLAGS_SRC_IP_V_4 = 0x0020, /**< IPV4 src ip addr. */
    BCMOLT_LAG_HASH_FIELD_FLAGS_IP_PROTO = 0x0040, /**< IP protocol. */
    BCMOLT_LAG_HASH_FIELD_FLAGS_DST_PORT = 0x0080, /**< L4 dest port. */
    BCMOLT_LAG_HASH_FIELD_FLAGS_SRC_PORT = 0x0100, /**< L4 src port. */
} bcmolt_lag_hash_field_flags;

/** LAG Hash Polynomial. */
typedef enum
{
    BCMOLT_LAG_HASH_POLYNOMIAL__BEGIN = 22,
    BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X8003 = 22, /**< crc 16 calculation with bits 16,2,1 xored. */
    BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X8101 = 25, /**< crc 16 calculation with bits 16,9,1 xored. */
    BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X84A1 = 26, /**< crc 16 calculation with bits 16,11,8,6,1 xored. */
    BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X9019 = 27, /**< crc 16 calculation with bits 16,13,4,3,1 xored. */
    BCMOLT_LAG_HASH_POLYNOMIAL__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_lag_hash_polynomial;

/** LAG health. */
typedef enum
{
    BCMOLT_LAG_HEALTH__BEGIN = 0,
    BCMOLT_LAG_HEALTH_DOWN = 0, /**< Down. */
    BCMOLT_LAG_HEALTH_DEGRADED = 1, /**< Degraded. */
    BCMOLT_LAG_HEALTH_UP = 2, /**< Up. */
    BCMOLT_LAG_HEALTH__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_lag_health;

/** group_member_update_fail_reaso */
typedef enum
{
    BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON__BEGIN = 0,
    BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_NONE = 0, /**< none */
    BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_PARM = 1, /**< invalid  parameter */
    BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_INTERNAL = 2, /**< internal */
    BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_SW = 3, /**< fail in switch configuration */
    BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_IN_USE = 4, /**< lag has use counts */
    BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_lag_member_update_fail_reason;

/** LAG PSC Mode. */
typedef enum
{
    BCMOLT_LAG_PSC_MODE__BEGIN = 0,
    BCMOLT_LAG_PSC_MODE_ROUND_ROBIN = 0, /**< Round Robin. */
    BCMOLT_LAG_PSC_MODE_SMOOTH_DIVISION = 1, /**< Smooth Division. */
    BCMOLT_LAG_PSC_MODE_MULTIPLICATION = 2, /**< Multiplication. */
    BCMOLT_LAG_PSC_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_lag_psc_mode;

/** the subtype of a lag interface */
typedef enum
{
    BCMOLT_LAG_SUBTYPE__BEGIN = 0,
    BCMOLT_LAG_SUBTYPE_UNASSIGNED = 0, /**< unassigned interface. */
    BCMOLT_LAG_SUBTYPE_NETWORK = 1, /**< network facing interface. */
    BCMOLT_LAG_SUBTYPE_ERPS_SUBPORT = 2, /**< erps subport interface. */
    BCMOLT_LAG_SUBTYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_lag_subtype;

/** Link Fault Code (Local or Remote Fault) */
typedef enum
{
    BCMOLT_LINK_FAULT_CODE_NONE = 0,
    BCMOLT_LINK_FAULT_CODE_LOCAL_FAULT = 0x1, /**< Local Fault detected. */
    BCMOLT_LINK_FAULT_CODE_REMOTE_FAULT = 0x2, /**< Remote Fault detected. */
} bcmolt_link_fault_code;

/** Current Link State (Link Up or Link Down) */
typedef enum
{
    BCMOLT_LINK_STATE__BEGIN = 0,
    BCMOLT_LINK_STATE_LINK_DOWN = 0, /**< Link Down */
    BCMOLT_LINK_STATE_LINK_UP = 1, /**< Link Up */
    BCMOLT_LINK_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_link_state;

/** Link type. */
typedef enum
{
    BCMOLT_LINK_TYPE__BEGIN = 0,
    BCMOLT_LINK_TYPE_UNSPECIFIED = 0, /**< Link type unspecified */
    BCMOLT_LINK_TYPE_B = 1, /**< Link type A is not supported, link type B is supported */
    BCMOLT_LINK_TYPE_A = 2, /**< Link type A is supported, link type B is not supported */
    BCMOLT_LINK_TYPE_A_AND_B = 3, /**< Both link types A and B are supported */
    BCMOLT_LINK_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_link_type;

/** loc_clear_threshold. */
typedef enum
{
    BCMOLT_LOC_CLEAR_THRESHOLD__BEGIN = 1,
    BCMOLT_LOC_CLEAR_THRESHOLD_CCM_INTERVAL = 1, /**< threshold = ccm_interval */
    BCMOLT_LOC_CLEAR_THRESHOLD_CCM_INTERVAL_TIMES_2 = 2, /**< threshold = ccm_interval * 2 */
    BCMOLT_LOC_CLEAR_THRESHOLD_CCM_INTERVAL_TIMES_3 = 3, /**< threshold = ccm_interval * 3 */
    BCMOLT_LOC_CLEAR_THRESHOLD__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_loc_clear_threshold;

/** Log File ID. */
typedef enum
{
    BCMOLT_LOG_FILE_ID__BEGIN = 0,
    BCMOLT_LOG_FILE_ID_SRAM = 0, /**< SRAM. */
    BCMOLT_LOG_FILE_ID_DDR = 1, /**< DDR. */
    BCMOLT_LOG_FILE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_log_file_id;

/** Log verbosity level */
typedef enum
{
    BCMOLT_LOG_LEVEL__BEGIN = 0,
    BCMOLT_LOG_LEVEL_NO_LOG = 0, /**< No log output at all */
    BCMOLT_LOG_LEVEL_FATAL = 1, /**< Fatal errors only */
    BCMOLT_LOG_LEVEL_ERROR = 2, /**< All errors */
    BCMOLT_LOG_LEVEL_WARNING = 3, /**< All warnings and errors */
    BCMOLT_LOG_LEVEL_INFO = 4, /**< Informational messages, warnings and errors */
    BCMOLT_LOG_LEVEL_DEBUG = 5, /**< All messages */
    BCMOLT_LOG_LEVEL__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_log_level;

/** log style. */
typedef enum
{
    BCMOLT_LOG_STYLE__BEGIN = 0,
    BCMOLT_LOG_STYLE_NORMAL = 0, /**< normal. */
    BCMOLT_LOG_STYLE_BOLD = 1, /**< bold. */
    BCMOLT_LOG_STYLE_UNDERLINE = 2, /**< underline. */
    BCMOLT_LOG_STYLE_BLINK = 3, /**< blink. */
    BCMOLT_LOG_STYLE_REVERSE_VIDEO = 4, /**< reverse video. */
    BCMOLT_LOG_STYLE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_log_style;

/** log type. */
typedef enum
{
    BCMOLT_LOG_TYPE__BEGIN = 0,
    BCMOLT_LOG_TYPE_NONE = 0, /**< dont show log */
    BCMOLT_LOG_TYPE_PRINT = 1, /**< print. */
    BCMOLT_LOG_TYPE_SAVE = 2, /**< save. */
    BCMOLT_LOG_TYPE_BOTH = 3, /**< both. */
    BCMOLT_LOG_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_log_type;

/** action to take on a mac table miss. */
typedef enum
{
    BCMOLT_MAC_TABLE_MISS_ACTION__BEGIN = 0,
    BCMOLT_MAC_TABLE_MISS_ACTION_FLOOD = 0, /**< flood the packet. */
    BCMOLT_MAC_TABLE_MISS_ACTION_DROP = 1, /**< drop the packet. */
    BCMOLT_MAC_TABLE_MISS_ACTION_ERPS_DEFAULT = 2, /**< ERPS default handling. */
    BCMOLT_MAC_TABLE_MISS_ACTION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_mac_table_miss_action;

/** MEG Id Format. */
typedef enum
{
    BCMOLT_MEG_FORMAT__BEGIN = 2,
    BCMOLT_MEG_FORMAT_IEEE_8021_AG_2 = 2, /**< 1-45  Character String */
    BCMOLT_MEG_FORMAT_IEEE_8021_AG_1 = 3, /**< 2 Byte Integer */
    BCMOLT_MEG_FORMAT_ICC = 32, /**< ITU carrier Code (ICC)  + Unique MEG ID code (UMC). */
    BCMOLT_MEG_FORMAT__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_meg_format;

/** MEG Level. */
typedef enum
{
    BCMOLT_MEG_LEVEL__BEGIN = 0,
    BCMOLT_MEG_LEVEL_LEVEL_0 = 0, /**< Level_0. */
    BCMOLT_MEG_LEVEL_LEVEL_1 = 1, /**< Level_1. */
    BCMOLT_MEG_LEVEL_LEVEL_2 = 2, /**< Level_2. */
    BCMOLT_MEG_LEVEL_LEVEL_3 = 3, /**< Level_3. */
    BCMOLT_MEG_LEVEL_LEVEL_4 = 4, /**< Level_4. */
    BCMOLT_MEG_LEVEL_LEVEL_5 = 5, /**< Level_5. */
    BCMOLT_MEG_LEVEL_LEVEL_6 = 6, /**< Level_6. */
    BCMOLT_MEG_LEVEL_LEVEL_7 = 7, /**< Level_7. */
    BCMOLT_MEG_LEVEL__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_meg_level;

/** members_update_command. */
typedef enum
{
    BCMOLT_MEMBERS_UPDATE_COMMAND__BEGIN = 0,
    BCMOLT_MEMBERS_UPDATE_COMMAND_ADD = 0, /**< add members */
    BCMOLT_MEMBERS_UPDATE_COMMAND_REMOVE = 1, /**< remove members */
    BCMOLT_MEMBERS_UPDATE_COMMAND_SET = 2, /**< set members */
    BCMOLT_MEMBERS_UPDATE_COMMAND__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_members_update_command;

/** mep type */
typedef enum
{
    BCMOLT_MEP_TYPE__BEGIN = 1,
    BCMOLT_MEP_TYPE_MEP = 1, /**< Local MEP = tx endpoint */
    BCMOLT_MEP_TYPE_RMEP = 2, /**< Remote MEP = rx endpoint */
    BCMOLT_MEP_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_mep_type;

/** MPCP discovery info. */
typedef enum
{
    BCMOLT_MPCP_DISCOVERY_INFO_NONE = 0,
    BCMOLT_MPCP_DISCOVERY_INFO_ONE_G_CAPABLE = 0x01, /**< 1G Capable. */
    BCMOLT_MPCP_DISCOVERY_INFO_TEN_G_CAPABLE = 0x02, /**< 10G Capable. */
    BCMOLT_MPCP_DISCOVERY_INFO_TWENTY_FIVE_G_CAPABLE = 0x04, /**< 25G Capable. */
    BCMOLT_MPCP_DISCOVERY_INFO_ONE_G_WINDOW = 0x10, /**< 1G window. */
    BCMOLT_MPCP_DISCOVERY_INFO_TEN_G_WINDOW = 0x20, /**< 10G window. */
    BCMOLT_MPCP_DISCOVERY_INFO_TWENTY_FIVE_G_WINDOW = 0x40, /**< 25G window. */
} bcmolt_mpcp_discovery_info;

/** NNI Connection. */
typedef enum
{
    BCMOLT_NNI_CONNECTION__BEGIN = 0,
    BCMOLT_NNI_CONNECTION_PRIMARY = 0, /**< Primary. */
    BCMOLT_NNI_CONNECTION_BACKUP = 1, /**< Backup. */
    BCMOLT_NNI_CONNECTION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_nni_connection;

/** Loopback Type. */
typedef enum
{
    BCMOLT_NNI_LOOPBACK_TYPE__BEGIN = 0,
    BCMOLT_NNI_LOOPBACK_TYPE_NONE = 0, /**< No Looback. */
    BCMOLT_NNI_LOOPBACK_TYPE_LINE = 1, /**< Incoming packets coming from the NNI interface to the PM and going back towards the NNI interface */
    BCMOLT_NNI_LOOPBACK_TYPE_REMOTE = 2, /**< Incoming packets coming from the PON (upstream) and going back to the PON (Downstream) */
    BCMOLT_NNI_LOOPBACK_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_nni_loopback_type;

/** NNI Protection Mode */
typedef enum
{
    BCMOLT_NNI_PROTECTION_MODE__BEGIN = 0,
    BCMOLT_NNI_PROTECTION_MODE_UNASSIGNED = 0, /**< Unused */
    BCMOLT_NNI_PROTECTION_MODE_ERPS = 1, /**< ERPS Ring Protection */
    BCMOLT_NNI_PROTECTION_MODE_NNI = 2, /**< NNI or LAG 1:1 Link Redundancy */
    BCMOLT_NNI_PROTECTION_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_nni_protection_mode;

/** the subtype of an nni interface */
typedef enum
{
    BCMOLT_NNI_SUBTYPE__BEGIN = 0,
    BCMOLT_NNI_SUBTYPE_NETWORK = 0, /**< network facing interface. */
    BCMOLT_NNI_SUBTYPE_ERPS_SUBPORT = 1, /**< erps subport interface. */
    BCMOLT_NNI_SUBTYPE_NIC = 2, /**< nic interface. */
    BCMOLT_NNI_SUBTYPE_LAG_MEMBER = 3, /**< lag member interface. */
    BCMOLT_NNI_SUBTYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_nni_subtype;

/** Number of frames per map. */
typedef enum
{
    BCMOLT_NUM_OF_FRAMES_PER_MAP__BEGIN = 0,
    BCMOLT_NUM_OF_FRAMES_PER_MAP_X_1 = 0, /**< 1 frame per map (125 us DBA cycle) */
    BCMOLT_NUM_OF_FRAMES_PER_MAP_X_2 = 1, /**< 2 frames per map (250 us DBA cycle) */
    BCMOLT_NUM_OF_FRAMES_PER_MAP_X_4 = 2, /**< 4 frames per map (500 us DBA cycle) */
    BCMOLT_NUM_OF_FRAMES_PER_MAP_X_8 = 3, /**< 8 frames per map (1000 us DBA cycle) */
    BCMOLT_NUM_OF_FRAMES_PER_MAP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_num_of_frames_per_map;

/** ODN Class. */
typedef enum
{
    BCMOLT_ODN_CLASS__BEGIN = 0,
    BCMOLT_ODN_CLASS_N1 = 0, /**< N1. */
    BCMOLT_ODN_CLASS_N2 = 1, /**< N2. */
    BCMOLT_ODN_CLASS_E1 = 3, /**< E1. */
    BCMOLT_ODN_CLASS_E2 = 4, /**< E2. */
    BCMOLT_ODN_CLASS__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_odn_class;

/** OMCI Device ID. */
typedef enum
{
    BCMOLT_OMCI_DEVICE_ID__BEGIN = 10,
    BCMOLT_OMCI_DEVICE_ID_BASELINE = 10, /**< Baseline. */
    BCMOLT_OMCI_DEVICE_ID_EXTENDED = 11, /**< Extended. */
    BCMOLT_OMCI_DEVICE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_omci_device_id;

/** OMCI Port ID operation. */
typedef enum
{
    BCMOLT_OMCI_PORT_ID_OPERATION__BEGIN = 0,
    BCMOLT_OMCI_PORT_ID_OPERATION_CONFIGURE = 0, /**< configure. */
    BCMOLT_OMCI_PORT_ID_OPERATION_REMOVE = 1, /**< remove. */
    BCMOLT_OMCI_PORT_ID_OPERATION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_omci_port_id_operation;

/** ONU operation. */
typedef enum
{
    BCMOLT_ONU_OPERATION__BEGIN = 0,
    BCMOLT_ONU_OPERATION_INACTIVE = 0, /**< Inactive. */
    BCMOLT_ONU_OPERATION_ACTIVE = 1, /**< Active. */
    BCMOLT_ONU_OPERATION_DISABLE = 2, /**< Disable. */
    BCMOLT_ONU_OPERATION_ENABLE = 3, /**< Enable. */
    BCMOLT_ONU_OPERATION_ACTIVE_STANDBY = 4, /**< Active Standby. */
    BCMOLT_ONU_OPERATION_AWAKE_FREE = 5, /**< Transitions the ONU to an active state with power management enabled. Allowed in inactive, disabled, and active states. */
    BCMOLT_ONU_OPERATION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_onu_operation;

/** ONU post discovery mode. */
typedef enum
{
    BCMOLT_ONU_POST_DISCOVERY_MODE__BEGIN = 0,
    BCMOLT_ONU_POST_DISCOVERY_MODE_NONE = 0, /**< Send an indication to the host, all the host to decide the next step. */
    BCMOLT_ONU_POST_DISCOVERY_MODE_ACTIVATE = 1, /**< Automatically activate if the service is known in the database. */
    BCMOLT_ONU_POST_DISCOVERY_MODE_DISABLE = 2, /**< Send an indication to the host, and disable the ONU. */
    BCMOLT_ONU_POST_DISCOVERY_MODE_PROVISION_AND_ACTIVATE = 3, /**< Automatically active upon discovery, applying default provisioning as necessary */
    BCMOLT_ONU_POST_DISCOVERY_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_onu_post_discovery_mode;

/** The upstream/downstream rates for this ONU */
typedef enum
{
    BCMOLT_ONU_RATE__BEGIN = 0,
    BCMOLT_ONU_RATE_RATE_10G_DS_10G_US = 0, /**< 10G Bidirectional ONU rate */
    BCMOLT_ONU_RATE_RATE_10G_DS_2P5G_US = 1, /**< 10G downstream, 2.5G Upstream ONU rate */
    BCMOLT_ONU_RATE_RATE_10G_DS_1G_US = 2, /**< 10G downstream, 1G Upstream ONU rate */
    BCMOLT_ONU_RATE_RATE_2P5G_DS_1P25G_US = 3, /**< 2.5G downstream, 1.25G Upstream ONU rate */
    BCMOLT_ONU_RATE_RATE_1G_DS_1G_US = 4, /**< 1G downstream, 1G Upstream ONU rate */
    BCMOLT_ONU_RATE_RATE_25G_DS_25G_US = 5, /**< 25G downstream, 25G upstream */
    BCMOLT_ONU_RATE_RATE_25G_DS_10G_US = 6, /**< 25G downstream, 10G upstream */
    BCMOLT_ONU_RATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_onu_rate;

/** ONU state. */
typedef enum
{
    BCMOLT_ONU_STATE__BEGIN = 0,
    BCMOLT_ONU_STATE_NOT_CONFIGURED = 0, /**< not_configured. */
    BCMOLT_ONU_STATE_INACTIVE = 1, /**< inactive. */
    BCMOLT_ONU_STATE_ACTIVE = 2, /**< active. */
    BCMOLT_ONU_STATE_ACTIVE_STANDBY = 3, /**< active standby. */
    BCMOLT_ONU_STATE_DISABLED = 4, /**< disabled. */
    BCMOLT_ONU_STATE_AWAKE_FREE = 5, /**< ONU is active, but power management is enabled. ONU is allowed to enter low power states at its own discretion. */
    BCMOLT_ONU_STATE_PROCESSING = 7, /**< processing. */
    BCMOLT_ONU_STATE_LOW_POWER_DOZE = 8, /**< ONU has entered the Doze low power state. */
    BCMOLT_ONU_STATE_LOW_POWER_SLEEP = 9, /**< ONU has entered the Sleep low power state. */
    BCMOLT_ONU_STATE_LOW_POWER_WATCH = 10, /**< ONU has entered the Watchful Sleep low power state. */
    BCMOLT_ONU_STATE_UNAWARE = 11, /**< ONU is added to data base but no bws is saved */
    BCMOLT_ONU_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_onu_state;

/** Modes for determining ONU range after the tuning-in process. */
typedef enum
{
    BCMOLT_ONU_TUNING_RANGE_MODE__BEGIN = 0,
    BCMOLT_ONU_TUNING_RANGE_MODE_RE_RANGE = 0, /**< During the tuning in process, the ONU range will be reset to 0 and then re-calculated. */
    BCMOLT_ONU_TUNING_RANGE_MODE_STATIC_RANGE = 1, /**< During the tuning in process, the ONU range will be set to the value "itu.xgpon.ngpon2.tuning_static_eqd" from the ONU object. This will be sent to the ONU using a Ranging_Time PLOAM targeting the active channel. */
    BCMOLT_ONU_TUNING_RANGE_MODE_PRE_PROVISIONED = 2, /**< During the tuning in process, no Ranging_Time PLOAM will be sent. This assumes the ONU already knows the correct EQD value and will start using it automatically (such as for type W protection if "partner_static_eqd" is set). */
    BCMOLT_ONU_TUNING_RANGE_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_onu_tuning_range_mode;

/** ONU Upgrade Status Code. */
typedef enum
{
    BCMOLT_ONU_UPGRADE_STATUS_CODE__BEGIN = 0,
    BCMOLT_ONU_UPGRADE_STATUS_CODE_TRANSFERRING_IMAGE = 0, /**< In the process of transferring the software image to the ONU. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_FINALIZING_TRANSFER = 1, /**< Sending the last packet / finalizing the software image transfer. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_ACTIVATING = 2, /**< Activating the ONU. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_SUCCESS = 3, /**< Upgrade succeeded. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_INTERNAL_ERROR = 4, /**< Internal error. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_ONU_RESPONSE_TIMEOUT = 5, /**< ONU did not respond to a message within the time specified by the "Write request timeout". */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_MESSAGE_SEND_FAILED = 6, /**< Failed to send an OAM/OMCI message to the ONU. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_SYNC_ERROR = 7, /**< Block number sync error. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_COMMIT_FAILED = 8, /**< Commit software command failed. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_PARSE_ERROR = 9, /**< Unable to parse the ONU response. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_TCI_MISMATCH = 10, /**< Transaction ID mismatch. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_GET_IMAGE_FAILED = 11, /**< Get Image Info command failed. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_ACTIVATION_FAILED = 12, /**< Activation software command failed. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_PROCESSING_ERROR = 20, /**< Command processing error.
    Possible causes:
    1) CRC mismatches the End Software Download OMCI message.
    2) Downloaded image format is not supported or invalid. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_NOT_SUPPORTED = 21, /**< Command not supported, or not applicable for End software download message. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_PARAMETER_ERROR = 22, /**< Parameter error, or not applicable for End software download message.
    Exception: Oren ONU returns this error for the CRC mismatch. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_UNKNOWN_MANAGED_ENTITY = 23, /**< Unknown managed entity. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_UNKNOWN_MANAGED_ENTITY_INSTANCE = 24, /**< Unknown managed entity instance. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_DEVICE_BUSY = 25, /**< Device busy. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_UNDEFINED = 30, /**< Unknown error, or one not covered elsewhere. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_NOT_FOUND = 31, /**< Read requested file that is not available. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_NO_ACCESS = 32, /**< Access permissions do not allow the requested read/write. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_FULL = 33, /**< Storage is full, and cannot hold the written file. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_ILLEGAL_OPERATION = 34, /**< Cannot perform requested operation in current state. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_UNKNOWN_ID = 35, /**< Requested file ID is not supported by this device. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_BAD_BLOCK = 36, /**< Block received in error. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_TIMEOUT = 37, /**< No block received before timer expiration. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_BUSY = 38, /**< Cannot perform requested action due to other activity. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_INCOMPATIBLE_FILE = 39, /**< Received file is incompatible with this device. File incompatibility is determined by the device vendor. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_CORRUPTED_FILE = 40, /**< File was received corrupted and is unusable by this device. File integrity is determined by the device vendor. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_ERROR_NOT_DEFINED = 50, /**< ONU returned ERROR PDU: Undefined error code. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_ERROR_ALLOC_EXCEEDED = 51, /**< ONU returned ERROR PDU: Disk full or allocation exceeded. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_ERROR_ILLEGAL_OP = 52, /**< ONU returned ERROR PDU: Illegal TFTP operation. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_ERROR_FILE_EXISTS = 53, /**< ONU returned ERROR PDU: Mirror file already exists. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_END_WRITING_NVS = 54, /**< ONU returned END RESPONSE PDU with error: Writing file to NVS */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_END_CRC_ERROR = 55, /**< ONU returned END RESPONSE PDU with error: CRC32 error */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_END_PARAMETER_ERROR = 56, /**< ONU returned END RESPONSE PDU with error: Parameter error */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_END_COMMAND_NOT_SUPPORTED = 57, /**< ONU returned END RESPONSE PDU with error: Command not supported */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_OK = 70, /**< BRCM OAM: OK. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_UNDEFINED = 71, /**< BRCM OAM: Undefined. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_NOT_FOUND = 72, /**< BRCM OAM: Not Found. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_NO_ACCESS = 73, /**< BRCM OAM: No Access. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_FULL = 74, /**< BRCM OAM: Full. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_ILLEGAL_OP = 75, /**< BRCM OAM: Illegal Op. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_UNKNOWN_ID = 76, /**< BRCM OAM: Unknown ID. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_BAD_BLOCK = 77, /**< BRCM OAM: Bad Block. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_TIMEOUT = 78, /**< BRCM OAM: Timeout. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_BUSY = 79, /**< BRCM OAM: Busy. */
    BCMOLT_ONU_UPGRADE_STATUS_CODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_onu_upgrade_status_code;

/** Packet Injection Error. */
typedef enum
{
    BCMOLT_PACKET_INJECTION_ERROR__BEGIN = 0,
    BCMOLT_PACKET_INJECTION_ERROR_GEM_PORT_NOT_ACTIVE = 0, /**< GEM Port Not Active. */
    BCMOLT_PACKET_INJECTION_ERROR__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_packet_injection_error;

/** packet type. */
typedef enum
{
    BCMOLT_PACKET_TYPE__BEGIN = 0,
    BCMOLT_PACKET_TYPE_ETH = 0, /**< ethernet. */
    BCMOLT_PACKET_TYPE_OMCI = 1, /**< OMCI. */
    BCMOLT_PACKET_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_packet_type;

/** Password authentication fail reason. */
typedef enum
{
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON__BEGIN = 0,
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_NONE = 0, /**< none. */
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_PASSWORD_INCONSISTENCY = 1, /**< Password inconsistency. */
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_PASSWORD_MISMATCH = 2, /**< Password mismatch. */
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_PASSWORD_AUTHENTICATION_TIMEOUT = 3, /**< Password authentication timeout. */
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_ONU_ALARM = 4, /**< onu alarm. */
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_LOS_EVENT = 5, /**< los event. */
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_DISABLE_EVENT = 6, /**< disable event. */
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_SWITCH_OVER = 7, /**< switch over event. */
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_FORCE_DEACTIVATION = 8, /**< force deactivation. */
    BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_password_authentication_fail_reason;

/** Packet tag type. */
typedef enum
{
    BCMOLT_PKT_TAG_TYPE_NONE = 0,
    BCMOLT_PKT_TAG_TYPE_UNTAGGED = 0x0001, /**< Untagged. */
    BCMOLT_PKT_TAG_TYPE_SINGLE_TAG = 0x0002, /**< Single tag. */
    BCMOLT_PKT_TAG_TYPE_DOUBLE_TAG = 0x0004, /**< Double tag. */
    BCMOLT_PKT_TAG_TYPE_TRIPLE_TAG = 0x0008, /**< Triple tag. */
} bcmolt_pkt_tag_type;

/** policer reference type. */
typedef enum
{
    BCMOLT_POLICER_REFERENCE_TYPE__BEGIN = 0,
    BCMOLT_POLICER_REFERENCE_TYPE_POLICER_PROFILE = 0, /**< policer profile. */
    BCMOLT_POLICER_REFERENCE_TYPE_HARDWARE_METER = 1, /**< hardware meter. */
    BCMOLT_POLICER_REFERENCE_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_policer_reference_type;

/** policer type. */
typedef enum
{
    BCMOLT_POLICER_TYPE__BEGIN = 0,
    BCMOLT_POLICER_TYPE_SR_TCM = 0, /**< magic number do not change */
    BCMOLT_POLICER_TYPE_TR_TCM_RFC4115 = 4, /**< magic number - do not change */
    BCMOLT_POLICER_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_policer_type;

/** PON NI ONU Upgrade Status Code */
typedef enum
{
    BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE__BEGIN = 0,
    BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_NOT_STARTED = 0, /**< No upgrade has been started yet on this PON NI. */
    BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_IN_PROGRESS = 1, /**< An upgrade operation is in progress. */
    BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_SUCCESS = 2, /**< The last ONU upgrade was successful and no upgrade is in progress. */
    BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_FAILURE = 3, /**< At least one ONU failed the last upgrade and no upgrade is in progress. */
    BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_ABORTED = 4, /**< The upgrade was aborted prematurely. */
    BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_pon_ni_onu_upgrade_status_code;

/** PON Protection Switching Options. */
typedef enum
{
    BCMOLT_PON_PROTECTION_SWITCHING_OPTIONS_NONE = 0,
    BCMOLT_PON_PROTECTION_SWITCHING_OPTIONS_SWIFT_POPUP = 0x0001, /**< If set, switchovers will utilize the Swift_POPUP and Ranging_Adjustment PLOAMs added in G.984 annex D. */
    BCMOLT_PON_PROTECTION_SWITCHING_OPTIONS_FAST_RANGING = 0x0002, /**< If set, ONU EQDs will not be calculated as part of a switchover.  Instead, each ONU's new EQD will be equal to its last EQD when the PON NI was in active-working state.  This provides a fast switchover, but can only be used if the trunk distance never changes. */
} bcmolt_pon_protection_switching_options;

/** Type of PON interface: GPON, XGPON, XGS, EPON, AE */
typedef enum
{
    BCMOLT_PON_TYPE__BEGIN = 0,
    BCMOLT_PON_TYPE_UNKNOWN = 0, /**< Unknown (not set) pon type */
    BCMOLT_PON_TYPE_GPON = 1, /**< GPON */
    BCMOLT_PON_TYPE_XGPON = 2, /**< XGPON */
    BCMOLT_PON_TYPE_XGS = 3, /**< XGS */
    BCMOLT_PON_TYPE_NGPON2_2P5G = 4, /**< NGPON2 with 2.5G upstream */
    BCMOLT_PON_TYPE_NGPON2_10G = 5, /**< NGPON2 with 10G upstream */
    BCMOLT_PON_TYPE_XGS_XGPON_TDMR = 6, /**< XGS and XGPON TDMR */
    BCMOLT_PON_TYPE_XGS_GPON_WDMA = 11, /**< XGS_GPON_WDMA. */
    BCMOLT_PON_TYPE_XGS_XGPON_TDMR_GPON_WDMA = 12, /**< XGS XGPON TDMR and GPON WDMA */
    BCMOLT_PON_TYPE_XGPON_GPON_WDMA = 20, /**< XGPON and GPON WDMA */
    BCMOLT_PON_TYPE_XGS_XGS_WDMA = 21, /**< XGS and XGS WDMA */
    BCMOLT_PON_TYPE_GPON_GPON_WDMA = 22, /**< GPON and GPON WDMA */
    BCMOLT_PON_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_pon_type;

/** port_update_command. */
typedef enum
{
    BCMOLT_PORT_COMMAND__BEGIN = 1,
    BCMOLT_PORT_COMMAND_ADD_PORT = 1, /**< add members */
    BCMOLT_PORT_COMMAND_REMOVE_PORT = 2, /**< remove members */
    BCMOLT_PORT_COMMAND__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_port_command;

/** power levelling control. */
typedef enum
{
    BCMOLT_POWER_LEVELLING_CONTROL__BEGIN = 0,
    BCMOLT_POWER_LEVELLING_CONTROL_DIRECT = 0, /**< Direct. */
    BCMOLT_POWER_LEVELLING_CONTROL_DECREASE = 1, /**< Decrease. */
    BCMOLT_POWER_LEVELLING_CONTROL_INCREASE = 2, /**< Increase. */
    BCMOLT_POWER_LEVELLING_CONTROL__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_power_levelling_control;

/** The reason that a power management state change occurred. */
typedef enum
{
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON__BEGIN = 0,
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_POWER_MANAGEMENT_ENABLED = 0, /**< Host requested power management enable. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_POWER_MANAGEMENT_DISABLED = 1, /**< Host requested power management disable. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_SLEEP_REQUEST_AWAKE = 2, /**< Received sleep request PLOAM from ONU. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_SLEEP_REQUEST_DOZE = 3, /**< Received sleep request PLOAM from ONU. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_SLEEP_REQUEST_SLEEP = 4, /**< Received sleep request PLOAM from ONU. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_SLEEP_REQUEST_WATCH = 5, /**< Received sleep request PLOAM from ONU. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_TERI_EXPIRED = 6, /**< Teri timer expired. It has been too long since we have received an upstream burst from an ONU in a low power state. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_TALERTED_EXPIRED = 7, /**< Talerted timer expired. It has been too long since the ONU was requested to wake up with no idication that it has complied. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_ALARM = 8, /**< A LOSi/LOFi/LOBi alarm has ben raised against the ONU. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_FORCE_DEACTIVATION = 9, /**< Force Deactivation. */
    BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_power_management_transition_reason;

/** PRBS checker mode. */
typedef enum
{
    BCMOLT_PRBS_CHECKER_MODE__BEGIN = 0,
    BCMOLT_PRBS_CHECKER_MODE_SELF_SYNC = 0, /**< Self-sync mode w/ hysteresis. PRBS seed register is continuously seeded with previous received bits.  This mode results in faster locking, but bit errors are counted multiple times (often by 3x). */
    BCMOLT_PRBS_CHECKER_MODE_INITIAL_SEED_MODE = 1, /**< Initial seed mode w/ hysteresis. PRBS seed registers is seeded with previous received bits only till PRBS lock is  acquired and then they run locally independently from the received data until the checker goes out of PRBS lock. */
    BCMOLT_PRBS_CHECKER_MODE_INITIAL_SEED_MODE_2 = 2, /**< Initial seed mode w/o hysteresis. Similar to mode 1 above except once locked it stays locked until PRBS is disabled. */
    BCMOLT_PRBS_CHECKER_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_prbs_checker_mode;

/** PRBS Lock State. */
typedef enum
{
    BCMOLT_PRBS_LOCK_STATE__BEGIN = 0,
    BCMOLT_PRBS_LOCK_STATE_UNLOCKED = 0, /**< PRBS Checker is out of LOCK state and state machine is searching for a LOCK */
    BCMOLT_PRBS_LOCK_STATE_LOCKED = 1, /**< PRBS Checker is in LOCKED state */
    BCMOLT_PRBS_LOCK_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_prbs_lock_state;

/** PRBS Polynomial. */
typedef enum
{
    BCMOLT_PRBS_POLYNOMIAL__BEGIN = 0,
    BCMOLT_PRBS_POLYNOMIAL_PRBS_7 = 0, /**< PRBS_7. */
    BCMOLT_PRBS_POLYNOMIAL_PRBS_9 = 1, /**< PRBS_9. */
    BCMOLT_PRBS_POLYNOMIAL_PRBS_11 = 2, /**< PRBS_11. Not Supported in 68650 */
    BCMOLT_PRBS_POLYNOMIAL_PRBS_15 = 3, /**< PRBS_15. */
    BCMOLT_PRBS_POLYNOMIAL_PRBS_23 = 4, /**< PRBS_23. */
    BCMOLT_PRBS_POLYNOMIAL_PRBS_31 = 5, /**< PRBS_31. */
    BCMOLT_PRBS_POLYNOMIAL_PRBS_58 = 6, /**< PRBS_58. Not Supported in 68650 */
    BCMOLT_PRBS_POLYNOMIAL__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_prbs_polynomial;

/** Status of PRBS test */
typedef enum
{
    BCMOLT_PRBS_TEST_STATUS_TYPE__BEGIN = 0,
    BCMOLT_PRBS_TEST_STATUS_TYPE_STATUS_NA = 0, /**< Status is N/A. */
    BCMOLT_PRBS_TEST_STATUS_TYPE_TEST_CONTINUE = 1, /**< Status Continue: it is possible to run the test again */
    BCMOLT_PRBS_TEST_STATUS_TYPE_TEST_DONE = 2, /**< Status Done: when reached maximal value of Error counts. */
    BCMOLT_PRBS_TEST_STATUS_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_prbs_test_status_type;

/** Ranging fail reason. */
typedef enum
{
    BCMOLT_RANGING_FAIL_REASON__BEGIN = 0,
    BCMOLT_RANGING_FAIL_REASON_NONE = 0, /**< none. */
    BCMOLT_RANGING_FAIL_REASON_RANGING_ACK_TIMEOUT = 1, /**< ranging ack timeout. */
    BCMOLT_RANGING_FAIL_REASON_PLOAM_DATA_MISMATCH = 2, /**< ploam data mismatch. */
    BCMOLT_RANGING_FAIL_REASON_PLOAM_TYPE_MISMATCH = 3, /**< ploam type mismatch. */
    BCMOLT_RANGING_FAIL_REASON_PLOAM_ONU_ID_MISMATCH = 4, /**< ploam onu id mismatch. */
    BCMOLT_RANGING_FAIL_REASON_DRIFT_EXCEEDED = 5, /**< drift exceeded. */
    BCMOLT_RANGING_FAIL_REASON_NO_PLOAM_RECEIVED = 6, /**< no ploam received. */
    BCMOLT_RANGING_FAIL_REASON_LOS = 7, /**< los. */
    BCMOLT_RANGING_FAIL_REASON_ALARMS = 8, /**< alarms. */
    BCMOLT_RANGING_FAIL_REASON_FORCE_DEACTIVATE = 9, /**< force deactivate. */
    BCMOLT_RANGING_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ranging_fail_reason;

/** Usage mode of RAS DDRs (no DDR is used, 1, 2 or 4 DDRs are used) */
typedef enum
{
    BCMOLT_RAS_DDR_USAGE_MODE__BEGIN = 0,
    BCMOLT_RAS_DDR_USAGE_MODE_NO_DDR = 0, /**< No DDR is used (applicable for all EPON system modes) */
    BCMOLT_RAS_DDR_USAGE_MODE_ONE_DDR = 1, /**< One DDR is used in the system (applicable for ITU PON system modes) */
    BCMOLT_RAS_DDR_USAGE_MODE_TWO_DDRS = 2, /**< Two DDRS are used in the system (applicable for ITU PON system modes) */
    BCMOLT_RAS_DDR_USAGE_MODE_FOUR_DDRS = 3, /**< Four DDRs are used in the system (applicable for ITU PON system modes) */
    BCMOLT_RAS_DDR_USAGE_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ras_ddr_usage_mode;

/** request registration fail reason. */
typedef enum
{
    BCMOLT_REQUEST_REGISTRATION_FAIL_REASON__BEGIN = 0,
    BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_NONE = 0, /**< None. */
    BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_REGISTRATION_PLOAM_TIMEOUT = 1, /**< registration ploam timeout. */
    BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_ONU_ALARM = 2, /**< onu alarm. */
    BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_DEACTIVATION = 3, /**< deactivation. */
    BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_DISABLE = 4, /**< disable. */
    BCMOLT_REQUEST_REGISTRATION_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_request_registration_fail_reason;

/** Options for the reset operation. */
typedef enum
{
    BCMOLT_RESET_MODE__BEGIN = 1,
    BCMOLT_RESET_MODE_HOST = 1, /**< Reset the host processor. */
    BCMOLT_RESET_MODE_ALL = 2, /**< Turn off all embedded devices' processor and reset the host processor. */
    BCMOLT_RESET_MODE_HOST_ISSU = 3, /**< Warm restart */
    BCMOLT_RESET_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_reset_mode;

/** Result. */
typedef enum
{
    BCMOLT_RESULT__BEGIN = 0,
    BCMOLT_RESULT_SUCCESS = 0, /**< Success. */
    BCMOLT_RESULT_FAIL = 1, /**< Fail. */
    BCMOLT_RESULT__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_result;

/** ERPS Ring Instance Id. */
typedef enum
{
    BCMOLT_RING_INSTANCE_INVALID = 65534U, /**< Invalid. */
    BCMOLT_RING_INSTANCE_UNASSIGNED = 65535U, /**< Unassigned. */
} bcmolt_ring_instance;

/** Ring Port. */
typedef enum
{
    BCMOLT_RING_PORT__BEGIN = 0,
    BCMOLT_RING_PORT_UNASSIGNED = 0, /**< No Ring Ports assigned yet */
    BCMOLT_RING_PORT_WEST = 1, /**< ERPSRing West Ring Port */
    BCMOLT_RING_PORT_EAST = 2, /**< ERPS Ring East Ring Port */
    BCMOLT_RING_PORT__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ring_port;

/** Ring Port State. */
typedef enum
{
    BCMOLT_RING_PORT_STATE__BEGIN = 0,
    BCMOLT_RING_PORT_STATE_UNASSIGNED = 0, /**< Unassigned. */
    BCMOLT_RING_PORT_STATE_BLOCKED = 1, /**< Blocked. */
    BCMOLT_RING_PORT_STATE_UNBLOCKED = 2, /**< Unblocked. */
    BCMOLT_RING_PORT_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ring_port_state;

/** RSSI measurement fail reason. */
typedef enum
{
    BCMOLT_RSSI_MEASUREMENT_FAIL_REASON__BEGIN = 0,
    BCMOLT_RSSI_MEASUREMENT_FAIL_REASON_NONE = 0, /**< None. */
    BCMOLT_RSSI_MEASUREMENT_FAIL_REASON_NO_DELIMITER = 1, /**< No delimiter. */
    BCMOLT_RSSI_MEASUREMENT_FAIL_REASON_NO_ACCESS = 2, /**< No access. */
    BCMOLT_RSSI_MEASUREMENT_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_rssi_measurement_fail_reason;

/** secure mutual authentication fail reason. */
typedef enum
{
    BCMOLT_SECURE_MUTUAL_AUTHENTICATION_FAIL_REASON__BEGIN = 0,
    BCMOLT_SECURE_MUTUAL_AUTHENTICATION_FAIL_REASON_TIMEOUT = 0, /**< secure mutual authentication timeout. */
    BCMOLT_SECURE_MUTUAL_AUTHENTICATION_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_secure_mutual_authentication_fail_reason;

/** sign. */
typedef enum
{
    BCMOLT_SIGN__BEGIN = 0,
    BCMOLT_SIGN_POSITIVE = 0, /**< Positive. */
    BCMOLT_SIGN_NEGATIVE = 1, /**< Negative. */
    BCMOLT_SIGN__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_sign;

/** All possible statistic alarm trigger conditions. */
typedef enum
{
    BCMOLT_STAT_CONDITION_TYPE__BEGIN = 0,
    BCMOLT_STAT_CONDITION_TYPE_NONE = 0, /**< The alarm is disabled. */
    BCMOLT_STAT_CONDITION_TYPE_RATE_THRESHOLD = 1, /**< The alarm is triggered if the stats delta value between samples crosses the configured threshold boundary. */
    BCMOLT_STAT_CONDITION_TYPE_RATE_RANGE = 2, /**< The alarm is triggered if the stats delta value between samples deviates from the configured range. */
    BCMOLT_STAT_CONDITION_TYPE_VALUE_THRESHOLD = 3, /**< The alarm is raised if the stats sample value becomes greater than this level.  The alarm is cleared when the host read the stats. */
    BCMOLT_STAT_CONDITION_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_stat_condition_type;

/** Status. */
typedef enum
{
    BCMOLT_STATUS__BEGIN = 0,
    BCMOLT_STATUS_OFF = 0, /**< Status is off. */
    BCMOLT_STATUS_ON = 1, /**< Status is on. */
    BCMOLT_STATUS_NO_CHANGE = 2, /**< Status should not be changed (valid for SET API calls only). */
    BCMOLT_STATUS__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_status;

/** Switch over type c onu state. */
typedef enum
{
    BCMOLT_SWITCH_OVER_TYPE_C_ONU_STATE__BEGIN = 0,
    BCMOLT_SWITCH_OVER_TYPE_C_ONU_STATE_ACTIVE = 0, /**< Active. */
    BCMOLT_SWITCH_OVER_TYPE_C_ONU_STATE_ACTIVE_STANDBY = 1, /**< Active standby. */
    BCMOLT_SWITCH_OVER_TYPE_C_ONU_STATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_switch_over_type_c_onu_state;

/** switch pon type fail reason. */
typedef enum
{
    BCMOLT_SWITCH_PON_TYPE_FAIL_REASON__BEGIN = 0,
    BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_NONE = 0, /**< None. */
    BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_INTERNAL_ERROR = 1, /**< Internal Error. */
    BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_ALREADY_RUNNING = 2, /**< Already running. */
    BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_BAD_PON_STATE = 3, /**< Bad PON state. */
    BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_BAD_DEV_STATE = 4, /**< Bad device state. */
    BCMOLT_SWITCH_PON_TYPE_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_switch_pon_type_fail_reason;

/** System working mode (GPON/EPON etc.) */
typedef enum
{
    BCMOLT_SYSTEM_MODE__BEGIN = 12,
    BCMOLT_SYSTEM_MODE_GPON__16_X = 12, /**< 16x GPON */
    BCMOLT_SYSTEM_MODE_XGPON__2_X = 13, /**< 2x XGPON */
    BCMOLT_SYSTEM_MODE_XGPON__8_X = 15, /**< 8x XGPON */
    BCMOLT_SYSTEM_MODE_XGS__2_X = 18, /**< 2x XGS-PON (10/10) */
    BCMOLT_SYSTEM_MODE_XGS__16_X = 19, /**< 16x XGS-PON (10/10) */
    BCMOLT_SYSTEM_MODE_XGS_XGPON__2_X_COEX_TDMA = 20, /**< 2x XGS and XGPON TDMA coexistence */
    BCMOLT_SYSTEM_MODE_NGPON2__2_X_10G = 21, /**< 2x NGPON2 (10/10) */
    BCMOLT_SYSTEM_MODE_XGS__8_X_GPON__8_X_WDMA = 38, /**< 8x XGS 8x GPON wdma */
    BCMOLT_SYSTEM_MODE_XGS__1_X = 70, /**< 1x XGS-PON (10/10) */
    BCMOLT_SYSTEM_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_system_mode;

/** TC layer protocol. */
typedef enum
{
    BCMOLT_TC_PROTOCOL__BEGIN = 0,
    BCMOLT_TC_PROTOCOL_TC_LAYER_PROTOCOL_G_987_P_3 = 0, /**< TC layer protocol G.987.3 */
    BCMOLT_TC_PROTOCOL_TC_LAYER_PROTOCOL_G_989_P_3 = 1, /**< TC layer protocol G.989.3 */
    BCMOLT_TC_PROTOCOL__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_tc_protocol;

/** tm_qmp_type. */
typedef enum
{
    BCMOLT_TM_QMP_TYPE__BEGIN = 0,
    BCMOLT_TM_QMP_TYPE_UNDEFINED = 0, /**< Undefined. */
    BCMOLT_TM_QMP_TYPE_PBITS = 1, /**< pbits. */
    BCMOLT_TM_QMP_TYPE_DSCP = 2, /**< dscp. */
    BCMOLT_TM_QMP_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_tm_qmp_type;

/** Traffic Direction */
typedef enum
{
    BCMOLT_TM_SCHED_DIR__BEGIN = 1,
    BCMOLT_TM_SCHED_DIR_US = 1, /**< Upstream */
    BCMOLT_TM_SCHED_DIR_DS = 2, /**< Downstream */
    BCMOLT_TM_SCHED_DIR__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_tm_sched_dir;

/** TM Scheduler Output Type */
typedef enum
{
    BCMOLT_TM_SCHED_OUTPUT_TYPE__BEGIN = 0,
    BCMOLT_TM_SCHED_OUTPUT_TYPE_UNDEFINED = 0, /**< Undefined */
    BCMOLT_TM_SCHED_OUTPUT_TYPE_INTERFACE = 1, /**< Interface */
    BCMOLT_TM_SCHED_OUTPUT_TYPE_TM_SCHED = 2, /**< Other tm scheduler */
    BCMOLT_TM_SCHED_OUTPUT_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_tm_sched_output_type;

/** TM Sched Param Type. */
typedef enum
{
    BCMOLT_TM_SCHED_PARAM_TYPE__BEGIN = 0,
    BCMOLT_TM_SCHED_PARAM_TYPE_UNDEFINED = 0, /**< Undefined. */
    BCMOLT_TM_SCHED_PARAM_TYPE_PRIORITY = 1, /**< Priority. */
    BCMOLT_TM_SCHED_PARAM_TYPE_WEIGHT = 2, /**< Weight. */
    BCMOLT_TM_SCHED_PARAM_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_tm_sched_param_type;

/** Scheduler Type */
typedef enum
{
    BCMOLT_TM_SCHED_TYPE__BEGIN = 0,
    BCMOLT_TM_SCHED_TYPE_UNDEFINED = 0, /**< Undefined */
    BCMOLT_TM_SCHED_TYPE_WFQ = 1, /**< Weighted Fair Queue (WFQ) */
    BCMOLT_TM_SCHED_TYPE_SP = 2, /**< Strict Priority */
    BCMOLT_TM_SCHED_TYPE_SP_WFQ = 3, /**< Hybrid SP + WFQ */
    BCMOLT_TM_SCHED_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_tm_sched_type;

/** tod calibration fail reason. */
typedef enum
{
    BCMOLT_TOD_CALIBRATION_FAIL_REASON__BEGIN = 0,
    BCMOLT_TOD_CALIBRATION_FAIL_REASON_NONE = 0, /**< none. */
    BCMOLT_TOD_CALIBRATION_FAIL_REASON_PPS_TIMEOUT = 1, /**< pps timeout. */
    BCMOLT_TOD_CALIBRATION_FAIL_REASON_UART_READ_FAIL = 2, /**< uart read fail. */
    BCMOLT_TOD_CALIBRATION_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_tod_calibration_fail_reason;

/** Traffic resume result. */
typedef enum
{
    BCMOLT_TRAFFIC_RESUME_RESULT__BEGIN = 0,
    BCMOLT_TRAFFIC_RESUME_RESULT_SUCCESS = 0, /**< Success. */
    BCMOLT_TRAFFIC_RESUME_RESULT_FAILURE = 1, /**< Failure. */
    BCMOLT_TRAFFIC_RESUME_RESULT_SUSPECTED_LOS = 2, /**< suspected_los. */
    BCMOLT_TRAFFIC_RESUME_RESULT__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_traffic_resume_result;

/** Traffic type. */
typedef enum
{
    BCMOLT_TRAFFIC_TYPE__BEGIN = 0,
    BCMOLT_TRAFFIC_TYPE_UNK_UNICAST = 0, /**< L2 Unicast where the DMAC is not found (DLF) */
    BCMOLT_TRAFFIC_TYPE_KNOWN_UNICAST = 1, /**< L2 Unicast (DMAC MSB=0) */
    BCMOLT_TRAFFIC_TYPE_MULTICAST = 2, /**< L2 Multicast  (DMAC MSB=0x01) */
    BCMOLT_TRAFFIC_TYPE_BROADCAST = 3, /**< L2 Broadcast (DMAC=FF:FF:FF:FF:FF) */
    BCMOLT_TRAFFIC_TYPE_UNK_MULTICAST = 4, /**< L2 Multicast where the DMAC is not found */
    BCMOLT_TRAFFIC_TYPE_ALL_TRAFFIC = 5, /**< Traffic of any type */
    BCMOLT_TRAFFIC_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_traffic_type;

/** Trivalent. */
typedef enum
{
    BCMOLT_TRIVALENT__BEGIN = 0,
    BCMOLT_TRIVALENT_FALSE = 0, /**< False. */
    BCMOLT_TRIVALENT_TRUE = 1, /**< True. */
    BCMOLT_TRIVALENT_NOT_APPLICABLE = 2, /**< Not Applicable. */
    BCMOLT_TRIVALENT__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_trivalent;

/** TRX type. */
typedef enum
{
    BCMOLT_TRX_TYPE__BEGIN = 0,
    BCMOLT_TRX_TYPE_SPS_43_48_H_HP_CDE_SD_2013 = 0, /**< SourcePhotonics - SPS-43-48H-HP-CDE-SD Reset is required BEFORE, TRX is Squelched. till 2013 rev. */
    BCMOLT_TRX_TYPE_SOG_4321_PSGB = 1, /**< Superxon B+ type */
    BCMOLT_TRX_TYPE_LTE_3680_M = 2, /**< LIGENT LTE3680M. */
    BCMOLT_TRX_TYPE_SOURCE_PHOTONICS = 3, /**< Source Photonics. */
    BCMOLT_TRX_TYPE_LTE_3680_P_TYPE_C_PLUS = 4, /**< LIGENT LTE3680P_TYPE_C_PLUS. */
    BCMOLT_TRX_TYPE_ANY = 5, /**< Any. */
    BCMOLT_TRX_TYPE_WTD_RTXM_167_526_CPLUS = 8, /**< WTD RTXM167 526 C+. */
    BCMOLT_TRX_TYPE_WTD_RTXM_167_522_BPLUS = 9, /**< WTD RTXM167 522 B+. */
    BCMOLT_TRX_TYPE_LTE_3680_P_BC = 10, /**< LIGENT HiSense LTE3680P-BC. */
    BCMOLT_TRX_TYPE_SOGQ_4321_PSGB_C_PLUS = 11, /**< Superxon C+ type */
    BCMOLT_TRX_TYPE_WTD_RTXM167_521 = 12, /**< WTD RTXM167_521. */
    BCMOLT_TRX_TYPE_LTE3678 = 13, /**< LTE3678. */
    BCMOLT_TRX_TYPE_LTH_5308 = 26, /**< XGS / GPON Combo Trx XFP */
    BCMOLT_TRX_TYPE_LTF_5308 = 27, /**< XGS / GPON Combo Trx SFP+ */
    BCMOLT_TRX_TYPE_LTF_5308_E = 28, /**< XGS / GPON Combo Trx SFP+ 22 pins */
    BCMOLT_TRX_TYPE_LTF_5306 = 29, /**< XGPON / GPON Combo Trx XFP */
    BCMOLT_TRX_TYPE_LTF_5308_B = 30, /**< Ligent LTF5308B. */
    BCMOLT_TRX_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_trx_type;

/** Tune in fail reason. */
typedef enum
{
    BCMOLT_TUNE_IN_FAIL_REASON__BEGIN = 0,
    BCMOLT_TUNE_IN_FAIL_REASON_NONE = 0, /**< none. */
    BCMOLT_TUNE_IN_FAIL_REASON_NO_TUNING_RESPONSE_PLOAM_RECEIVED = 1, /**< No tuning response ploam received. */
    BCMOLT_TUNE_IN_FAIL_REASON_ONU_ACTIVATION_FAILED = 2, /**< onu activation failed. */
    BCMOLT_TUNE_IN_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_tune_in_fail_reason;

/** Tune out fail reason. */
typedef enum
{
    BCMOLT_TUNE_OUT_FAIL_REASON__BEGIN = 0,
    BCMOLT_TUNE_OUT_FAIL_REASON_NONE = 0, /**< none. */
    BCMOLT_TUNE_OUT_FAIL_REASON_NACK_PLOAM_RECEIVED = 1, /**< NACK ploam received. */
    BCMOLT_TUNE_OUT_FAIL_REASON_NO_TUNING_RESPONSE_PLOAM_RECEIVED = 2, /**< no tuning response ploam received. */
    BCMOLT_TUNE_OUT_FAIL_REASON_TSOURCE_TIMEOUT = 3, /**< tsource timeout. */
    BCMOLT_TUNE_OUT_FAIL_REASON_ROLLBACK_REQUEST = 4, /**< rollback request. */
    BCMOLT_TUNE_OUT_FAIL_REASON_SWITCH_OVER = 5, /**< protection switch over. */
    BCMOLT_TUNE_OUT_FAIL_REASON_FORCE_DEACTIVATE = 6, /**< force deactivate. */
    BCMOLT_TUNE_OUT_FAIL_REASON__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_tune_out_fail_reason;

/** UART baud rate. */
typedef enum
{
    BCMOLT_UART_BAUDRATE__BEGIN = 0,
    BCMOLT_UART_BAUDRATE_UART_RATE_4800 = 0, /**< UART rate 4800. */
    BCMOLT_UART_BAUDRATE_UART_RATE_9600 = 1, /**< UART rate 9600. */
    BCMOLT_UART_BAUDRATE_UART_RATE_14400 = 2, /**< UART rate 14400. */
    BCMOLT_UART_BAUDRATE_UART_RATE_19200 = 3, /**< UART rate 19200. */
    BCMOLT_UART_BAUDRATE_UART_RATE_38400 = 4, /**< UART rate 38400. */
    BCMOLT_UART_BAUDRATE_UART_RATE_57600 = 5, /**< UART rate 57600. */
    BCMOLT_UART_BAUDRATE_UART_RATE_115200 = 6, /**< UART rate 115200. */
    BCMOLT_UART_BAUDRATE_UART_RATE_230400 = 7, /**< UART rate 230400. */
    BCMOLT_UART_BAUDRATE_UART_RATE_380400 = 8, /**< UART rate 380400. */
    BCMOLT_UART_BAUDRATE_UART_RATE_460800 = 9, /**< UART rate 460800. */
    BCMOLT_UART_BAUDRATE_UART_RATE_921600 = 10, /**< UART rate 921600. */
    BCMOLT_UART_BAUDRATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_uart_baudrate;

/** XGPON ni upstream line rate capabilities */
typedef enum
{
    BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES__BEGIN = 0,
    BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_2_P_5_G = 0, /**< 2.5G Upstream line rate capability */
    BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_10_G = 1, /**< 10G Upstream line rate capability */
    BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_1_G = 2, /**< 1G Upstream line rate capability */
    BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_DUAL_2_P_5_G_AND_10_G = 3, /**< dual 2.5G and 10G upstream line rate capability. */
    BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_upstream_line_rate_capabilities;

/** us_gem_port_destination. */
typedef enum
{
    BCMOLT_US_GEM_PORT_DESTINATION__BEGIN = 0,
    BCMOLT_US_GEM_PORT_DESTINATION_DATA = 0, /**< data. */
    BCMOLT_US_GEM_PORT_DESTINATION_CPU = 1, /**< cpu. */
    BCMOLT_US_GEM_PORT_DESTINATION_OMCI = 2, /**< omci. */
    BCMOLT_US_GEM_PORT_DESTINATION__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_us_gem_port_destination;

/** US operating wavelength bands. */
typedef enum
{
    BCMOLT_US_OPERATING_WAVELENGTH_BANDS__BEGIN = 0,
    BCMOLT_US_OPERATING_WAVELENGTH_BANDS_EXPANDED_SPECTRUM_WIDE_BAND = 0, /**< Expanded spectrum wide band option */
    BCMOLT_US_OPERATING_WAVELENGTH_BANDS_EXPANDED_SPECTRUM_REDUCED_BAND = 1, /**< Expanded spectrum reduced band option */
    BCMOLT_US_OPERATING_WAVELENGTH_BANDS_EXPANDED_SPECTRUM_NARROW_BAND = 2, /**< Expanded spectrum reduced band option */
    BCMOLT_US_OPERATING_WAVELENGTH_BANDS_SHARED_SPECTRUM_WIDE_BAND = 16, /**< Shared spectrum wide band option */
    BCMOLT_US_OPERATING_WAVELENGTH_BANDS_SHARED_SPECTRUM_REDUCED_BAND = 17, /**< Shared spectrum reduced band option */
    BCMOLT_US_OPERATING_WAVELENGTH_BANDS_SHARED_SPECTRUM_NARROW_BAND = 18, /**< Shared spectrum wide narrow option */
    BCMOLT_US_OPERATING_WAVELENGTH_BANDS__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_us_operating_wavelength_bands;

/** XGPON TRX type. */
typedef enum
{
    BCMOLT_XGPON_TRX_TYPE__BEGIN = 0,
    BCMOLT_XGPON_TRX_TYPE_LTH_7222_PC = 0, /**< Ligent LTH 7222-PC. */
    BCMOLT_XGPON_TRX_TYPE_WTD_RTXM266_702 = 2, /**< WTD_RTXM266_702. */
    BCMOLT_XGPON_TRX_TYPE_LTH_7222_BC_PLUS = 3, /**< SFP+ */
    BCMOLT_XGPON_TRX_TYPE_LTH_7226_PC = 4, /**< XGS */
    BCMOLT_XGPON_TRX_TYPE_LTH_5302_PC = 5, /**< 10G EPON for XGS mode */
    BCMOLT_XGPON_TRX_TYPE_LTW_627_X_PC = 8, /**< Supports NGPON2 TRx for various channels */
    BCMOLT_XGPON_TRX_TYPE_XPP_XE_R_3_CDFB = 9, /**< 10G EPON for XGS mode */
    BCMOLT_XGPON_TRX_TYPE_LTH_7226_A_PC_PLUS = 10, /**< for XGS XGPON coex TDMA mode */
    BCMOLT_XGPON_TRX_TYPE_D272RR_SSCB_DM = 11, /**< xgs muiti mode TRX */
    BCMOLT_XGPON_TRX_TYPE_LTH_5308 = 12, /**< XGS / GPON Combo TRx XFP */
    BCMOLT_XGPON_TRX_TYPE_LTF_5308 = 13, /**< XGS / GPON Combo TRx SFP+ */
    BCMOLT_XGPON_TRX_TYPE_LTF_7226_B = 14, /**< XGS, XGPON1, TDMA */
    BCMOLT_XGPON_TRX_TYPE_LTF_5308_E = 15, /**< XGS, XGPON1, TDMA 22 pins */
    BCMOLT_XGPON_TRX_TYPE_LTF_5306 = 16, /**< XGS / GPON Combo TRx SFP+ */
    BCMOLT_XGPON_TRX_TYPE_LTF_5308_B = 17, /**< XGS / GPON Combo TRx SFP+ */
    BCMOLT_XGPON_TRX_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_xgpon_trx_type;

/** Identifiers for all objects in the system. */
typedef enum
{
    BCMOLT_OBJ_ID__BEGIN = 1,
    BCMOLT_OBJ_ID_DEVICE = 1, /**< Device. */
    BCMOLT_OBJ_ID_FLOW = 4, /**< BAL Flow. */
    BCMOLT_OBJ_ID_GPIO = 5, /**< GPIO. */
    BCMOLT_OBJ_ID_GROUP = 6, /**< BAL Group. */
    BCMOLT_OBJ_ID_INTERNAL_NNI = 7, /**< Internal NNI. */
    BCMOLT_OBJ_ID_ITUPON_ALLOC = 8, /**< ITU PON Alloc. */
    BCMOLT_OBJ_ID_ITUPON_GEM = 9, /**< ITU PON GEM Port. */
    BCMOLT_OBJ_ID_LOG = 15, /**< Log. */
    BCMOLT_OBJ_ID_LOG_FILE = 16, /**< Log File. */
    BCMOLT_OBJ_ID_NGPON2_CHANNEL = 17, /**< Channel. */
    BCMOLT_OBJ_ID_NNI_INTERFACE = 18, /**< nni_interface. */
    BCMOLT_OBJ_ID_OLT = 19, /**< olt. */
    BCMOLT_OBJ_ID_ONU = 20, /**< ONU. */
    BCMOLT_OBJ_ID_PBIT_TO_TC = 21, /**< pbit_to_tc. */
    BCMOLT_OBJ_ID_PON_INTERFACE = 22, /**< pon interface. */
    BCMOLT_OBJ_ID_SOFTWARE_ERROR = 23, /**< Software Error. */
    BCMOLT_OBJ_ID_TC_TO_QUEUE = 24, /**< tc_to_queue. */
    BCMOLT_OBJ_ID_TM_QUEUE = 25, /**< tm_queue. */
    BCMOLT_OBJ_ID_TM_SCHED = 26, /**< tm_sched. */
    BCMOLT_OBJ_ID_INBAND_MGMT_CHANNEL = 31, /**< BAL Inband Management Channel. */
    BCMOLT_OBJ_ID_ERPS_INTERFACE = 33, /**< ERPS Interface. */
    BCMOLT_OBJ_ID_PROTECTION_INTERFACE = 34, /**< Protection Interface. */
    BCMOLT_OBJ_ID_TM_QMP = 35, /**< tm_qmp. */
    BCMOLT_OBJ_ID_ETH_OAM = 36, /**< Ethernet OAM. */
    BCMOLT_OBJ_ID_POLICER_PROFILE = 39, /**< policer (aka meter) profile. */
    BCMOLT_OBJ_ID_ACCESS_CONTROL = 40, /**< access control. */
    BCMOLT_OBJ_ID_SWITCH_INNI = 41, /**< switch inni. */
    BCMOLT_OBJ_ID_LAG_INTERFACE = 42, /**< LAG interface. */
    BCMOLT_OBJ_ID_BAL_SYSTEM = 43, /**< BAL System Globals. */
    BCMOLT_OBJ_ID_HOST_LOG_FILE = 44, /**< Host Log File. */
    BCMOLT_OBJ_ID_HOST_LOG = 45, /**< host log. */
    BCMOLT_OBJ_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_obj_id__begin BCMOLT_OBJ_ID__BEGIN
#define bcmolt_obj_id_device BCMOLT_OBJ_ID_DEVICE
#define bcmolt_obj_id_flow BCMOLT_OBJ_ID_FLOW
#define bcmolt_obj_id_gpio BCMOLT_OBJ_ID_GPIO
#define bcmolt_obj_id_group BCMOLT_OBJ_ID_GROUP
#define bcmolt_obj_id_internal_nni BCMOLT_OBJ_ID_INTERNAL_NNI
#define bcmolt_obj_id_itupon_alloc BCMOLT_OBJ_ID_ITUPON_ALLOC
#define bcmolt_obj_id_itupon_gem BCMOLT_OBJ_ID_ITUPON_GEM
#define bcmolt_obj_id_log BCMOLT_OBJ_ID_LOG
#define bcmolt_obj_id_log_file BCMOLT_OBJ_ID_LOG_FILE
#define bcmolt_obj_id_ngpon2_channel BCMOLT_OBJ_ID_NGPON2_CHANNEL
#define bcmolt_obj_id_nni_interface BCMOLT_OBJ_ID_NNI_INTERFACE
#define bcmolt_obj_id_olt BCMOLT_OBJ_ID_OLT
#define bcmolt_obj_id_onu BCMOLT_OBJ_ID_ONU
#define bcmolt_obj_id_pbit_to_tc BCMOLT_OBJ_ID_PBIT_TO_TC
#define bcmolt_obj_id_pon_interface BCMOLT_OBJ_ID_PON_INTERFACE
#define bcmolt_obj_id_software_error BCMOLT_OBJ_ID_SOFTWARE_ERROR
#define bcmolt_obj_id_tc_to_queue BCMOLT_OBJ_ID_TC_TO_QUEUE
#define bcmolt_obj_id_tm_queue BCMOLT_OBJ_ID_TM_QUEUE
#define bcmolt_obj_id_tm_sched BCMOLT_OBJ_ID_TM_SCHED
#define bcmolt_obj_id_inband_mgmt_channel BCMOLT_OBJ_ID_INBAND_MGMT_CHANNEL
#define bcmolt_obj_id_erps_interface BCMOLT_OBJ_ID_ERPS_INTERFACE
#define bcmolt_obj_id_protection_interface BCMOLT_OBJ_ID_PROTECTION_INTERFACE
#define bcmolt_obj_id_tm_qmp BCMOLT_OBJ_ID_TM_QMP
#define bcmolt_obj_id_eth_oam BCMOLT_OBJ_ID_ETH_OAM
#define bcmolt_obj_id_policer_profile BCMOLT_OBJ_ID_POLICER_PROFILE
#define bcmolt_obj_id_access_control BCMOLT_OBJ_ID_ACCESS_CONTROL
#define bcmolt_obj_id_switch_inni BCMOLT_OBJ_ID_SWITCH_INNI
#define bcmolt_obj_id_lag_interface BCMOLT_OBJ_ID_LAG_INTERFACE
#define bcmolt_obj_id_bal_system BCMOLT_OBJ_ID_BAL_SYSTEM
#define bcmolt_obj_id_host_log_file BCMOLT_OBJ_ID_HOST_LOG_FILE
#define bcmolt_obj_id_host_log BCMOLT_OBJ_ID_HOST_LOG
#define bcmolt_obj_id__num_of BCMOLT_OBJ_ID__NUM_OF
#define bcmolt_obj_id_all_properties 0xFFFF
#define bcmolt_obj_id_full_mask 0x3F9E87FF83F2

} bcmolt_obj_id;

/** Identifiers for all possible groups under all objects in the system. */
typedef enum
{
    BCMOLT_API_GROUP_ID__BEGIN = 0,
    BCMOLT_API_GROUP_ID_ACCESS_CONTROL_KEY = 0, /**< access control - key. */
    BCMOLT_API_GROUP_ID_ACCESS_CONTROL_CFG = 1, /**< access control - cfg. */
    BCMOLT_API_GROUP_ID_ACCESS_CONTROL_STATS = 2, /**< access control - stats. */
    BCMOLT_API_GROUP_ID_ACCESS_CONTROL_RECEIVE_ETH_PACKET = 3, /**< access control - receive_eth_packet. */
    BCMOLT_API_GROUP_ID_ACCESS_CONTROL_INTERFACES_UPDATE = 4, /**< access control - update interface reference. */
    BCMOLT_API_GROUP_ID_ACCESS_CONTROL_STATS_CFG = 5, /**< access control - Stats Configuration. */
    BCMOLT_API_GROUP_ID_ACCESS_CONTROL_STATS_ALARM_RAISED = 6, /**< access control - Stats Alarm Raised. */
    BCMOLT_API_GROUP_ID_ACCESS_CONTROL_STATS_ALARM_CLEARED = 7, /**< access control - Stats Alarm Cleared. */
    BCMOLT_API_GROUP_ID_ACCESS_CONTROL_AUTO_CFG = 8, /**< access control - Indication Configuration. */
    BCMOLT_API_GROUP_ID_BAL_SYSTEM_CFG = 9, /**< BAL System Globals - cfg. */
    BCMOLT_API_GROUP_ID_BAL_SYSTEM_KEY = 10, /**< BAL System Globals - key. */
    BCMOLT_API_GROUP_ID_DEVICE_KEY = 11, /**< Device - key. */
    BCMOLT_API_GROUP_ID_DEVICE_CFG = 12, /**< Device - cfg. */
    BCMOLT_API_GROUP_ID_DEVICE_CONNECT = 13, /**< Device - Connect. */
    BCMOLT_API_GROUP_ID_DEVICE_DISCONNECT = 14, /**< Device - Device Disconnect. */
    BCMOLT_API_GROUP_ID_DEVICE_RESET = 15, /**< Device - Device Reset. */
    BCMOLT_API_GROUP_ID_DEVICE_HOST_KEEP_ALIVE = 16, /**< Device - Host Keep Alive (Internal). */
    BCMOLT_API_GROUP_ID_DEVICE_SW_UPGRADE_ACTIVATE = 17, /**< Device - SW upgrade activate. */
    BCMOLT_API_GROUP_ID_DEVICE_SET_8021_AS_TOD_STRING = 18, /**< Device - Set ToD String for 802.1AS. */
    BCMOLT_API_GROUP_ID_DEVICE_IMAGE_TRANSFER_START = 19, /**< Device - Start Image Transfer Operation. */
    BCMOLT_API_GROUP_ID_DEVICE_IMAGE_TRANSFER_DATA = 20, /**< Device - Image Data Transfer Operation (Internal). */
    BCMOLT_API_GROUP_ID_DEVICE_RUN_DDR_TEST = 21, /**< Device - Run DDR Test. */
    BCMOLT_API_GROUP_ID_DEVICE_DEVICE_READY = 22, /**< Device - Device Ready. */
    BCMOLT_API_GROUP_ID_DEVICE_CONNECTION_ESTABLISHED = 23, /**< Device - Connection Established. */
    BCMOLT_API_GROUP_ID_DEVICE_DEVICE_KEEP_ALIVE = 24, /**< Device - Device Keep Alive. */
    BCMOLT_API_GROUP_ID_DEVICE_CONNECTION_FAILURE = 25, /**< Device - Connection Failure. */
    BCMOLT_API_GROUP_ID_DEVICE_CONNECTION_COMPLETE = 26, /**< Device - Connection Complete. */
    BCMOLT_API_GROUP_ID_DEVICE_DISCONNECTION_COMPLETE = 27, /**< Device - Disconnection Complete. */
    BCMOLT_API_GROUP_ID_DEVICE_SW_ERROR = 28, /**< Device - sw error. */
    BCMOLT_API_GROUP_ID_DEVICE_SW_EXCEPTION = 29, /**< Device - sw exception. */
    BCMOLT_API_GROUP_ID_DEVICE_IMAGE_TRANSFER_COMPLETE = 30, /**< Device - Image Transfer Complete. */
    BCMOLT_API_GROUP_ID_DEVICE_DDR_TEST_COMPLETE = 31, /**< Device - DDR Test Complete. */
    BCMOLT_API_GROUP_ID_DEVICE_SW_HEALTH_CHECK_FAILURE = 32, /**< Device - Software Health Check Failure. */
    BCMOLT_API_GROUP_ID_DEVICE_CHANGE_INNI_MUX = 33, /**< Device - Change_configuration_completed INNI mux. */
    BCMOLT_API_GROUP_ID_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED = 34, /**< Device - INNI mux configuration completed. */
    BCMOLT_API_GROUP_ID_DEVICE_TOD_CALIBRATION_DONE = 35, /**< Device - tod calibration done. */
    BCMOLT_API_GROUP_ID_DEVICE_AUTO_CFG = 36, /**< Device - Indication Configuration. */
    BCMOLT_API_GROUP_ID_ERPS_INTERFACE_KEY = 37, /**< ERPS Interface - key. */
    BCMOLT_API_GROUP_ID_ERPS_INTERFACE_CFG = 38, /**< ERPS Interface - cfg. */
    BCMOLT_API_GROUP_ID_ERPS_INTERFACE_SET_RING_PORT_CONTROL = 39, /**< ERPS Interface - Set Ring Port Control. */
    BCMOLT_API_GROUP_ID_ERPS_INTERFACE_RING_PORT_CONTROL = 40, /**< ERPS Interface - Ring Port Control. */
    BCMOLT_API_GROUP_ID_ERPS_INTERFACE_PORT_UPDATE = 41, /**< ERPS Interface - erps port update. */
    BCMOLT_API_GROUP_ID_ERPS_INTERFACE_PORT_UPDATE_COMPLETE = 42, /**< ERPS Interface - erps port update completed. */
    BCMOLT_API_GROUP_ID_ERPS_INTERFACE_AUTO_CFG = 43, /**< ERPS Interface - Indication Configuration. */
    BCMOLT_API_GROUP_ID_ETH_OAM_KEY = 44, /**< Ethernet OAM - key. */
    BCMOLT_API_GROUP_ID_ETH_OAM_CFG = 45, /**< Ethernet OAM - cfg. */
    BCMOLT_API_GROUP_ID_ETH_OAM_CCM_EVENT = 46, /**< Ethernet OAM - CFM CCM Event. */
    BCMOLT_API_GROUP_ID_ETH_OAM_STATS = 47, /**< Ethernet OAM - stats. */
    BCMOLT_API_GROUP_ID_ETH_OAM_SET_MEP_STATE = 48, /**< Ethernet OAM - Set MEP Control State. */
    BCMOLT_API_GROUP_ID_ETH_OAM_STATE_CHANGE = 49, /**< Ethernet OAM - State Change. */
    BCMOLT_API_GROUP_ID_ETH_OAM_STATS_CFG = 50, /**< Ethernet OAM - Stats Configuration. */
    BCMOLT_API_GROUP_ID_ETH_OAM_STATS_ALARM_RAISED = 51, /**< Ethernet OAM - Stats Alarm Raised. */
    BCMOLT_API_GROUP_ID_ETH_OAM_STATS_ALARM_CLEARED = 52, /**< Ethernet OAM - Stats Alarm Cleared. */
    BCMOLT_API_GROUP_ID_ETH_OAM_AUTO_CFG = 53, /**< Ethernet OAM - Indication Configuration. */
    BCMOLT_API_GROUP_ID_FLOW_CFG = 54, /**< BAL Flow - cfg. */
    BCMOLT_API_GROUP_ID_FLOW_KEY = 55, /**< BAL Flow - key. */
    BCMOLT_API_GROUP_ID_FLOW_STATS = 56, /**< BAL Flow - Statistics. */
    BCMOLT_API_GROUP_ID_FLOW_SEND_ETH_PACKET = 57, /**< BAL Flow - send_eth_packet. */
    BCMOLT_API_GROUP_ID_FLOW_STATS_CFG = 58, /**< BAL Flow - Statistics Configuration. */
    BCMOLT_API_GROUP_ID_FLOW_STATS_ALARM_RAISED = 59, /**< BAL Flow - Statistics Alarm Raised. */
    BCMOLT_API_GROUP_ID_FLOW_STATS_ALARM_CLEARED = 60, /**< BAL Flow - Statistics Alarm Cleared. */
    BCMOLT_API_GROUP_ID_FLOW_AUTO_CFG = 61, /**< BAL Flow - Indication Configuration. */
    BCMOLT_API_GROUP_ID_GPIO_KEY = 62, /**< GPIO - key. */
    BCMOLT_API_GROUP_ID_GPIO_CFG = 63, /**< GPIO - cfg. */
    BCMOLT_API_GROUP_ID_GROUP_CFG = 64, /**< BAL Group - cfg. */
    BCMOLT_API_GROUP_ID_GROUP_KEY = 65, /**< BAL Group - key. */
    BCMOLT_API_GROUP_ID_GROUP_MEMBERS_UPDATE = 66, /**< BAL Group - members_update. */
    BCMOLT_API_GROUP_ID_GROUP_COMPLETE_MEMBERS_UPDATE = 67, /**< BAL Group - complete_members_update. */
    BCMOLT_API_GROUP_ID_GROUP_AUTO_CFG = 68, /**< BAL Group - Indication Configuration. */
    BCMOLT_API_GROUP_ID_HOST_LOG_KEY = 69, /**< host log - key. */
    BCMOLT_API_GROUP_ID_HOST_LOG_CFG = 70, /**< host log - cfg. */
    BCMOLT_API_GROUP_ID_HOST_LOG_FILE_KEY = 71, /**< Host Log File - key. */
    BCMOLT_API_GROUP_ID_HOST_LOG_FILE_CFG = 72, /**< Host Log File - cfg. */
    BCMOLT_API_GROUP_ID_HOST_LOG_FILE_CLEAR = 73, /**< Host Log File - Clear. */
    BCMOLT_API_GROUP_ID_HOST_LOG_FILE_RESET_BUFFER_PTR = 74, /**< Host Log File - Reset Buffer Pointer. */
    BCMOLT_API_GROUP_ID_INBAND_MGMT_CHANNEL_CFG = 75, /**< BAL Inband Management Channel - cfg. */
    BCMOLT_API_GROUP_ID_INBAND_MGMT_CHANNEL_KEY = 76, /**< BAL Inband Management Channel - key. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_KEY = 77, /**< Internal NNI - key. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_CFG = 78, /**< Internal NNI - cfg. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_STATUS_CHANGED = 79, /**< Internal NNI - Status changed. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_NNI_STATS = 80, /**< Internal NNI - NNI and AE Counters (RMON). */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_ENET_STATS = 81, /**< Internal NNI - Ethernet Statistics. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_PACKET_CAPTURED = 82, /**< Internal NNI - Packet Captured. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_SEND_ETH_PACKET = 83, /**< Internal NNI - send_eth_packet. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_SWAP_COMPLETED = 84, /**< Internal NNI - intetrnal inni sawp completed. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_NNI_STATS_CFG = 85, /**< Internal NNI - NNI And AE Counters (RMON) Configuration. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_NNI_STATS_ALARM_RAISED = 86, /**< Internal NNI - NNI And AE Counters (RMON) Alarm Raised. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_NNI_STATS_ALARM_CLEARED = 87, /**< Internal NNI - NNI And AE Counters (RMON) Alarm Cleared. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_ENET_STATS_CFG = 88, /**< Internal NNI - Ethernet Statistics Configuration. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_ENET_STATS_ALARM_RAISED = 89, /**< Internal NNI - Ethernet Statistics Alarm Raised. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_ENET_STATS_ALARM_CLEARED = 90, /**< Internal NNI - Ethernet Statistics Alarm Cleared. */
    BCMOLT_API_GROUP_ID_INTERNAL_NNI_AUTO_CFG = 91, /**< Internal NNI - Indication Configuration. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_KEY = 92, /**< ITU PON Alloc - key. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_CFG = 93, /**< ITU PON Alloc - cfg. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_CONFIGURATION_COMPLETED = 94, /**< ITU PON Alloc - Configuration Completed. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_GET_STATS = 95, /**< ITU PON Alloc - Get alloc level statistics. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED = 96, /**< ITU PON Alloc - Get alloc level statistics completed. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_SET_STATE = 97, /**< ITU PON Alloc - Set state. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_STATS = 98, /**< ITU PON Alloc - Statistics. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_STATS_CFG = 99, /**< ITU PON Alloc - Statistics Configuration. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_STATS_ALARM_RAISED = 100, /**< ITU PON Alloc - Statistics Alarm Raised. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_STATS_ALARM_CLEARED = 101, /**< ITU PON Alloc - Statistics Alarm Cleared. */
    BCMOLT_API_GROUP_ID_ITUPON_ALLOC_AUTO_CFG = 102, /**< ITU PON Alloc - Indication Configuration. */
    BCMOLT_API_GROUP_ID_ITUPON_GEM_KEY = 103, /**< ITU PON GEM Port - key. */
    BCMOLT_API_GROUP_ID_ITUPON_GEM_CFG = 104, /**< ITU PON GEM Port - cfg. */
    BCMOLT_API_GROUP_ID_ITUPON_GEM_STATS = 105, /**< ITU PON GEM Port - Statistics. */
    BCMOLT_API_GROUP_ID_ITUPON_GEM_CONFIGURATION_COMPLETED = 106, /**< ITU PON GEM Port - Configuration Completed. */
    BCMOLT_API_GROUP_ID_ITUPON_GEM_SET_STATE = 107, /**< ITU PON GEM Port - Set state. */
    BCMOLT_API_GROUP_ID_ITUPON_GEM_STATS_CFG = 108, /**< ITU PON GEM Port - Statistics Configuration. */
    BCMOLT_API_GROUP_ID_ITUPON_GEM_STATS_ALARM_RAISED = 109, /**< ITU PON GEM Port - Statistics Alarm Raised. */
    BCMOLT_API_GROUP_ID_ITUPON_GEM_STATS_ALARM_CLEARED = 110, /**< ITU PON GEM Port - Statistics Alarm Cleared. */
    BCMOLT_API_GROUP_ID_ITUPON_GEM_AUTO_CFG = 111, /**< ITU PON GEM Port - Indication Configuration. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_KEY = 112, /**< LAG interface - key. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_CFG = 113, /**< LAG interface - cfg. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_STATS = 114, /**< LAG interface - LAG Interface Statistics. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_MEMBERS_UPDATE = 115, /**< LAG interface - members_update. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE = 116, /**< LAG interface - complete_members_update. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_STATE_UPDATE = 117, /**< LAG interface - state_update. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_STATE_UPDATED = 118, /**< LAG interface - interface state updated. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_LAG_HEALTH_CHANGE = 119, /**< LAG interface - LAG health change. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_STATS_CFG = 120, /**< LAG interface - LAG Interface Statistics Configuration. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_STATS_ALARM_RAISED = 121, /**< LAG interface - LAG Interface Statistics Alarm Raised. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_STATS_ALARM_CLEARED = 122, /**< LAG interface - LAG Interface Statistics Alarm Cleared. */
    BCMOLT_API_GROUP_ID_LAG_INTERFACE_AUTO_CFG = 123, /**< LAG interface - Indication Configuration. */
    BCMOLT_API_GROUP_ID_LOG_KEY = 124, /**< Log - key. */
    BCMOLT_API_GROUP_ID_LOG_CFG = 125, /**< Log - cfg. */
    BCMOLT_API_GROUP_ID_LOG_FILE_KEY = 126, /**< Log File - key. */
    BCMOLT_API_GROUP_ID_LOG_FILE_CFG = 127, /**< Log File - cfg. */
    BCMOLT_API_GROUP_ID_LOG_FILE_CLEAR = 128, /**< Log File - Clear. */
    BCMOLT_API_GROUP_ID_LOG_FILE_RESET_BUFFER_PTR = 129, /**< Log File - Reset Buffer Pointer. */
    BCMOLT_API_GROUP_ID_NGPON2_CHANNEL_KEY = 130, /**< Channel - key. */
    BCMOLT_API_GROUP_ID_NGPON2_CHANNEL_CFG = 131, /**< Channel - cfg. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_KEY = 132, /**< nni_interface - key. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_STATE_CHANGE = 133, /**< nni_interface - State Change. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_CFG = 134, /**< nni_interface - cfg. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_SET_NNI_STATE = 135, /**< nni_interface - set_nni_state. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_STATS = 136, /**< nni_interface - NNI Interface Statistics. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_LINK_STATE_CHANGE = 137, /**< nni_interface - link_state_change. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_STATS_CFG = 138, /**< nni_interface - NNI Interface Statistics Configuration. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_STATS_ALARM_RAISED = 139, /**< nni_interface - NNI Interface Statistics Alarm Raised. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_STATS_ALARM_CLEARED = 140, /**< nni_interface - NNI Interface Statistics Alarm Cleared. */
    BCMOLT_API_GROUP_ID_NNI_INTERFACE_AUTO_CFG = 141, /**< nni_interface - Indication Configuration. */
    BCMOLT_API_GROUP_ID_OLT_KEY = 142, /**< olt - key. */
    BCMOLT_API_GROUP_ID_OLT_CFG = 143, /**< olt - cfg. */
    BCMOLT_API_GROUP_ID_OLT_CONNECT = 144, /**< olt - connect. */
    BCMOLT_API_GROUP_ID_OLT_DISCONNECT = 145, /**< olt - disconnect. */
    BCMOLT_API_GROUP_ID_OLT_BAL_RESET = 146, /**< olt - Reset BAL and Switch. */
    BCMOLT_API_GROUP_ID_OLT_BAL_FAILURE = 147, /**< olt - BAL and/or Switch Failed. */
    BCMOLT_API_GROUP_ID_OLT_BAL_READY = 148, /**< olt - BAL and Switch Ready. */
    BCMOLT_API_GROUP_ID_OLT_SW_ERROR = 149, /**< olt - OLT Software error. */
    BCMOLT_API_GROUP_ID_OLT_RESET = 150, /**< olt - OLT Reset. */
    BCMOLT_API_GROUP_ID_OLT_AUTO_CFG = 151, /**< olt - Indication Configuration. */
    BCMOLT_API_GROUP_ID_ONU_KEY = 152, /**< ONU - key. */
    BCMOLT_API_GROUP_ID_ONU_CFG = 153, /**< ONU - cfg. */
    BCMOLT_API_GROUP_ID_ONU_ITU_PON_STATS = 154, /**< ONU - ITU PON Statistics. */
    BCMOLT_API_GROUP_ID_ONU_SET_ONU_STATE = 155, /**< ONU - Set ONU State. */
    BCMOLT_API_GROUP_ID_ONU_RSSI_MEASUREMENT = 156, /**< ONU - RSSI Measurement. */
    BCMOLT_API_GROUP_ID_ONU_REQUEST_REGISTRATION = 157, /**< ONU - Request registration. */
    BCMOLT_API_GROUP_ID_ONU_CHANGE_POWER_LEVELLING = 158, /**< ONU - Change power levelling. */
    BCMOLT_API_GROUP_ID_ONU_GET_POWER_LEVEL = 159, /**< ONU - Get power level. */
    BCMOLT_API_GROUP_ID_ONU_GET_POWER_CONSUMPTION = 160, /**< ONU - Get power consumption. */
    BCMOLT_API_GROUP_ID_ONU_ADJUST_TX_WAVELENGTH = 161, /**< ONU - Adjust Tx wavelength. */
    BCMOLT_API_GROUP_ID_ONU_SECURE_MUTUAL_AUTHENTICATION = 162, /**< ONU - Secure mutual authentication. */
    BCMOLT_API_GROUP_ID_ONU_TUNING_IN = 163, /**< ONU - ONU Tuning in. */
    BCMOLT_API_GROUP_ID_ONU_TUNING_OUT = 164, /**< ONU - ONU Tuning out. */
    BCMOLT_API_GROUP_ID_ONU_XGPON_ALARM = 165, /**< ONU - XGPON ONU Alarm. */
    BCMOLT_API_GROUP_ID_ONU_GPON_ALARM = 166, /**< ONU - GPON ONU Alarm. */
    BCMOLT_API_GROUP_ID_ONU_DOWI = 167, /**< ONU - Drift of Window of ONUi. */
    BCMOLT_API_GROUP_ID_ONU_SFI = 168, /**< ONU - Signal Fail of ONUi. */
    BCMOLT_API_GROUP_ID_ONU_SDI = 169, /**< ONU - Signal Degraded of ONUi. */
    BCMOLT_API_GROUP_ID_ONU_DFI = 170, /**< ONU - Receive Dying-Gasp of ONUi. */
    BCMOLT_API_GROUP_ID_ONU_PQSI = 171, /**< ONU - ploam queue status. */
    BCMOLT_API_GROUP_ID_ONU_SUFI = 172, /**< ONU - SUFi. */
    BCMOLT_API_GROUP_ID_ONU_TIWI = 173, /**< ONU - Transmission Interference Warning. */
    BCMOLT_API_GROUP_ID_ONU_LOOCI = 174, /**< ONU - LOOCi. */
    BCMOLT_API_GROUP_ID_ONU_LOAI = 175, /**< ONU - LOAi. */
    BCMOLT_API_GROUP_ID_ONU_DGI = 176, /**< ONU - Receive Dying-Gasp of ONUi. */
    BCMOLT_API_GROUP_ID_ONU_PEE = 177, /**< ONU - PEE. */
    BCMOLT_API_GROUP_ID_ONU_PST = 178, /**< ONU - PST. */
    BCMOLT_API_GROUP_ID_ONU_RANGING_COMPLETED = 179, /**< ONU - Ranging Completed. */
    BCMOLT_API_GROUP_ID_ONU_ONU_ACTIVATION_COMPLETED = 180, /**< ONU - ONU Activation Completed. */
    BCMOLT_API_GROUP_ID_ONU_ONU_DEACTIVATION_COMPLETED = 181, /**< ONU - ONU Deactivation Completed. */
    BCMOLT_API_GROUP_ID_ONU_ONU_ENABLE_COMPLETED = 182, /**< ONU - ONU Enable Completed. */
    BCMOLT_API_GROUP_ID_ONU_ONU_DISABLE_COMPLETED = 183, /**< ONU - ONU Disable Completed. */
    BCMOLT_API_GROUP_ID_ONU_RSSI_MEASUREMENT_COMPLETED = 184, /**< ONU - RSSI Measurement Completed. */
    BCMOLT_API_GROUP_ID_ONU_INVALID_DBRU_REPORT = 185, /**< ONU - Invalid DBRu Report. */
    BCMOLT_API_GROUP_ID_ONU_KEY_EXCHANGE_COMPLETED = 186, /**< ONU - Key Exchange Completed. */
    BCMOLT_API_GROUP_ID_ONU_KEY_EXCHANGE_KEY_REQUEST_TIMEOUT = 187, /**< ONU - Key Exchange Key Request Timeout. */
    BCMOLT_API_GROUP_ID_ONU_KEY_EXCHANGE_CYCLE_SKIPPED = 188, /**< ONU - Key Exchange Cycle Skipped. */
    BCMOLT_API_GROUP_ID_ONU_KEY_EXCHANGE_KEY_MISMATCH = 189, /**< ONU - Key Exchange Key Mismatch. */
    BCMOLT_API_GROUP_ID_ONU_OPTICAL_REFLECTION = 190, /**< ONU - Optical Reflection. */
    BCMOLT_API_GROUP_ID_ONU_LOKI = 191, /**< ONU - LOki. */
    BCMOLT_API_GROUP_ID_ONU_MEMI = 192, /**< ONU - MEMi. */
    BCMOLT_API_GROUP_ID_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED = 193, /**< ONU - OMCI PORT ID Configuration Completed. */
    BCMOLT_API_GROUP_ID_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED = 194, /**< ONU - BER Interval Configuration Completed. */
    BCMOLT_API_GROUP_ID_ONU_ERR = 195, /**< ONU - ERR. */
    BCMOLT_API_GROUP_ID_ONU_PASSWORD_AUTHENTICATION_COMPLETED = 196, /**< ONU - Password Authentication Completed. */
    BCMOLT_API_GROUP_ID_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX = 197, /**< ONU - Key Exchange Unconsecutive Index. */
    BCMOLT_API_GROUP_ID_ONU_KEY_EXCHANGE_DECRYPT_REQUIRED = 198, /**< ONU - Key Exchange Decrypt Required. */
    BCMOLT_API_GROUP_ID_ONU_ONU_ACTIVATION_STANDBY_COMPLETED = 199, /**< ONU - onu activation standby completed. */
    BCMOLT_API_GROUP_ID_ONU_POWER_MANAGEMENT_STATE_CHANGE = 200, /**< ONU - Power Management State Change. */
    BCMOLT_API_GROUP_ID_ONU_POSSIBLE_DRIFT = 201, /**< ONU - Possible Drift. */
    BCMOLT_API_GROUP_ID_ONU_REGISTRATION_ID = 202, /**< ONU - Registration ID. */
    BCMOLT_API_GROUP_ID_ONU_POWER_LEVEL_REPORT = 203, /**< ONU - Power level report. */
    BCMOLT_API_GROUP_ID_ONU_POWER_CONSUMPTION_REPORT = 204, /**< ONU - Power consumption report. */
    BCMOLT_API_GROUP_ID_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE = 205, /**< ONU - secure mutual authentication failure. */
    BCMOLT_API_GROUP_ID_ONU_ONU_TUNING_OUT_COMPLETED = 206, /**< ONU - ONU Tuning out completed. */
    BCMOLT_API_GROUP_ID_ONU_ONU_TUNING_IN_COMPLETED = 207, /**< ONU - ONU Tuning in completed. */
    BCMOLT_API_GROUP_ID_ONU_TUNING_RESPONSE = 208, /**< ONU - Tuning response. */
    BCMOLT_API_GROUP_ID_ONU_PLOAM_PACKET = 209, /**< ONU - PLOAM Packet. */
    BCMOLT_API_GROUP_ID_ONU_CPU_PACKETS = 210, /**< ONU - XGPON CPU packets. */
    BCMOLT_API_GROUP_ID_ONU_CPU_PACKET = 211, /**< ONU - XGPON CPU packet. */
    BCMOLT_API_GROUP_ID_ONU_OMCI_PACKET = 212, /**< ONU - XGPON OMCI packet. */
    BCMOLT_API_GROUP_ID_ONU_ONU_READY_FOR_DATA_GRANT = 213, /**< ONU - ONU is ready to be granted data accesses. */
    BCMOLT_API_GROUP_ID_ONU_REI = 214, /**< ONU - REI. */
    BCMOLT_API_GROUP_ID_ONU_FORCE_DEACTIVATION = 215, /**< ONU - Force deactivation. */
    BCMOLT_API_GROUP_ID_ONU_STATE_CHANGE = 216, /**< ONU - State Change. */
    BCMOLT_API_GROUP_ID_ONU_RANGE_VALUE_CHANGED = 217, /**< ONU - Range Value Changed. */
    BCMOLT_API_GROUP_ID_ONU_XPON_UNKNOWN_PLOAM = 218, /**< ONU - XPON Unknown ploam. */
    BCMOLT_API_GROUP_ID_ONU_TRAP_PLOAM_RECEIVED = 219, /**< ONU - trap ploam received. */
    BCMOLT_API_GROUP_ID_ONU_ITU_PON_STATS_CFG = 220, /**< ONU - ITU PON Statistics Configuration. */
    BCMOLT_API_GROUP_ID_ONU_ITU_PON_STATS_ALARM_RAISED = 221, /**< ONU - ITU PON Statistics Alarm Raised. */
    BCMOLT_API_GROUP_ID_ONU_ITU_PON_STATS_ALARM_CLEARED = 222, /**< ONU - ITU PON Statistics Alarm Cleared. */
    BCMOLT_API_GROUP_ID_ONU_AUTO_CFG = 223, /**< ONU - Indication Configuration. */
    BCMOLT_API_GROUP_ID_PBIT_TO_TC_KEY = 224, /**< pbit_to_tc - key. */
    BCMOLT_API_GROUP_ID_PBIT_TO_TC_CFG = 225, /**< pbit_to_tc - cfg. */
    BCMOLT_API_GROUP_ID_POLICER_PROFILE_KEY = 226, /**< policer (aka meter) profile - key. */
    BCMOLT_API_GROUP_ID_POLICER_PROFILE_CFG = 227, /**< policer (aka meter) profile - cfg. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_KEY = 228, /**< pon interface - key. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_CFG = 229, /**< pon interface - cfg. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ITU_PON_STATS = 230, /**< pon interface - ITU PON Statistics. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_AE_STATS = 231, /**< pon interface - Active Ethernet Interface Counters. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_SET_PON_INTERFACE_STATE = 232, /**< pon interface - Set PON Interface State. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_SET_ONU_STATE = 233, /**< pon interface - Set ONU State. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_RESET = 234, /**< pon interface - Reset. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_DISABLE_SERIAL_NUMBER = 235, /**< pon interface - Disable Serial Number. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_SINGLE_REQUEST_STANDBY_PON_MONITORING = 236, /**< pon interface - Single request standby PON Monitoring. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_RUN_SPECIAL_BW_MAP = 237, /**< pon interface - Run Special BW Map. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_TOD_REQUEST = 238, /**< pon interface - TOD request. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_START_ONU_UPGRADE = 239, /**< pon interface - Start ONU Firmware Upgrade. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ABORT_ONU_UPGRADE = 240, /**< pon interface - Abort ONU Firmware Upgrade. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE = 241, /**< pon interface - protection switching type c set multiple onu state. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA = 242, /**< pon interface - Protection switching apply re-range delta (IEEE). */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_CPU_PACKETS = 243, /**< pon interface - XGPON CPU packets. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_BROADCAST_PLOAM_PACKET = 244, /**< pon interface - Broadcast PLOAM Packet. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_STATE_CHANGE_COMPLETED = 245, /**< pon interface - State Change Completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_TOD_REQUEST_COMPLETED = 246, /**< pon interface - TOD request completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_LOS = 247, /**< pon interface - LOS. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_SERIAL_NUMBER_ACQUISITION_CYCLE_START = 248, /**< pon interface - Serial Number Acquisition Cycle Start. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_PROTECTION_SWITCHING_TRAFFIC_RESUME = 249, /**< pon interface - Protection Switching Traffic Resume. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_PROTECTION_SWITCHING_ONUS_RANGED = 250, /**< pon interface - Protection Switching ONUs Ranged. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_PROTECTION_SWITCHING_RERANGE_FAILURE = 251, /**< pon interface - Protection Switching Re-range failure  (IEEE). */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED = 252, /**< pon interface - Protection Switching Switchover Completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED = 253, /**< pon interface - Standby PON Monitoring Cycle Completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ONU_DISCOVERED = 254, /**< pon interface - ONU Discovered. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_CPU_PACKETS_FAILURE = 255, /**< pon interface - CPU Packets Failure. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_DEACTIVATE_ALL_ONUS_COMPLETED = 256, /**< pon interface - deactivate all onus completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_DISABLE_ALL_ONUS_COMPLETED = 257, /**< pon interface - disable all onus completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ACTIVATE_ALL_ONUS_COMPLETED = 258, /**< pon interface - activate all onus completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ENABLE_ALL_ONUS_COMPLETED = 259, /**< pon interface - enable all onus completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ONU_UPGRADE_COMPLETE = 260, /**< pon interface - ONU Upgrade Complete. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_IEEE_ROGUE_DETECTION_COMPLETED = 261, /**< pon interface - IEEE Rogue Detection Completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_MPCP_TIMESTAMP_CHANGED = 262, /**< pon interface - MPCP Timestamp Changed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_SWITCH_PON_TYPE = 263, /**< pon interface - Switch PON type. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED = 264, /**< pon interface - Switch PON type completed. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ROGUE_DETECTION_TOOL = 265, /**< pon interface - rogue detection tool. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE = 266, /**< pon interface - rogue detection tool done. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ONU_UPGRADE_ACTIVATE_COMMIT = 267, /**< pon interface - ONU Upgrade Activate Commit. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ITU_PON_STATS_CFG = 268, /**< pon interface - ITU PON Statistics Configuration. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ITU_PON_STATS_ALARM_RAISED = 269, /**< pon interface - ITU PON Statistics Alarm Raised. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_ITU_PON_STATS_ALARM_CLEARED = 270, /**< pon interface - ITU PON Statistics Alarm Cleared. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_AE_STATS_CFG = 271, /**< pon interface - Active Ethernet Interface Counters Configuration. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_AE_STATS_ALARM_RAISED = 272, /**< pon interface - Active Ethernet Interface Counters Alarm Raised. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_AE_STATS_ALARM_CLEARED = 273, /**< pon interface - Active Ethernet Interface Counters Alarm Cleared. */
    BCMOLT_API_GROUP_ID_PON_INTERFACE_AUTO_CFG = 274, /**< pon interface - Indication Configuration. */
    BCMOLT_API_GROUP_ID_PROTECTION_INTERFACE_KEY = 275, /**< Protection Interface - key. */
    BCMOLT_API_GROUP_ID_PROTECTION_INTERFACE_CFG = 276, /**< Protection Interface - cfg. */
    BCMOLT_API_GROUP_ID_PROTECTION_INTERFACE_PROTECTION_SWITCH = 277, /**< Protection Interface - Protection Switch. */
    BCMOLT_API_GROUP_ID_PROTECTION_INTERFACE_PROTECTION_SWITCH_COMPLETED = 278, /**< Protection Interface - Protection Switch Completed. */
    BCMOLT_API_GROUP_ID_PROTECTION_INTERFACE_AUTO_CFG = 279, /**< Protection Interface - Indication Configuration. */
    BCMOLT_API_GROUP_ID_SOFTWARE_ERROR_KEY = 280, /**< Software Error - key. */
    BCMOLT_API_GROUP_ID_SOFTWARE_ERROR_CFG = 281, /**< Software Error - cfg. */
    BCMOLT_API_GROUP_ID_SWITCH_INNI_KEY = 282, /**< switch inni - key. */
    BCMOLT_API_GROUP_ID_SWITCH_INNI_CFG = 283, /**< switch inni - cfg. */
    BCMOLT_API_GROUP_ID_SWITCH_INNI_STATS = 284, /**< switch inni - Switch INNI Interface Statistics. */
    BCMOLT_API_GROUP_ID_SWITCH_INNI_STATS_CFG = 285, /**< switch inni - Switch INNI Interface Statistics Configuration. */
    BCMOLT_API_GROUP_ID_SWITCH_INNI_STATS_ALARM_RAISED = 286, /**< switch inni - Switch INNI Interface Statistics Alarm Raised. */
    BCMOLT_API_GROUP_ID_SWITCH_INNI_STATS_ALARM_CLEARED = 287, /**< switch inni - Switch INNI Interface Statistics Alarm Cleared. */
    BCMOLT_API_GROUP_ID_SWITCH_INNI_AUTO_CFG = 288, /**< switch inni - Indication Configuration. */
    BCMOLT_API_GROUP_ID_TC_TO_QUEUE_KEY = 289, /**< tc_to_queue - key. */
    BCMOLT_API_GROUP_ID_TC_TO_QUEUE_CFG = 290, /**< tc_to_queue - cfg. */
    BCMOLT_API_GROUP_ID_TM_QMP_KEY = 291, /**< tm_qmp - key. */
    BCMOLT_API_GROUP_ID_TM_QMP_CFG = 292, /**< tm_qmp - cfg. */
    BCMOLT_API_GROUP_ID_TM_QUEUE_KEY = 293, /**< tm_queue - key. */
    BCMOLT_API_GROUP_ID_TM_QUEUE_CFG = 294, /**< tm_queue - cfg. */
    BCMOLT_API_GROUP_ID_TM_SCHED_KEY = 295, /**< tm_sched - key. */
    BCMOLT_API_GROUP_ID_TM_SCHED_CFG = 296, /**< tm_sched - cfg. */
    BCMOLT_API_GROUP_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_api_group_id;

/** List of all access_control groups of type stat. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ACCESS_CONTROL_STAT_SUBGROUP_STATS = 1, /**< stats. */
    BCMOLT_ACCESS_CONTROL_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_stat_subgroup__begin BCMOLT_ACCESS_CONTROL_STAT_SUBGROUP__BEGIN
#define bcmolt_access_control_stat_subgroup_all BCMOLT_ACCESS_CONTROL_STAT_SUBGROUP_ALL
#define bcmolt_access_control_stat_subgroup_stats BCMOLT_ACCESS_CONTROL_STAT_SUBGROUP_STATS
#define bcmolt_access_control_stat_subgroup__num_of BCMOLT_ACCESS_CONTROL_STAT_SUBGROUP__NUM_OF
#define bcmolt_access_control_stat_subgroup_all_properties 0xFFFF
#define bcmolt_access_control_stat_subgroup_full_mask 0x3

} bcmolt_access_control_stat_subgroup;

/** List of all access_control groups of type stat_cfg. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ACCESS_CONTROL_STAT_CFG_SUBGROUP_STATS_CFG = 1, /**< Stats Configuration. */
    BCMOLT_ACCESS_CONTROL_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_stat_cfg_subgroup__begin BCMOLT_ACCESS_CONTROL_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_access_control_stat_cfg_subgroup_all BCMOLT_ACCESS_CONTROL_STAT_CFG_SUBGROUP_ALL
#define bcmolt_access_control_stat_cfg_subgroup_stats_cfg BCMOLT_ACCESS_CONTROL_STAT_CFG_SUBGROUP_STATS_CFG
#define bcmolt_access_control_stat_cfg_subgroup__num_of BCMOLT_ACCESS_CONTROL_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_access_control_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_access_control_stat_cfg_subgroup_full_mask 0x3

} bcmolt_access_control_stat_cfg_subgroup;

/** List of all access_control groups of type auto. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP_RECEIVE_ETH_PACKET = 1, /**< receive_eth_packet. */
    BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP_STATS_ALARM_CLEARED = 2, /**< Stats Alarm Cleared. */
    BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP_STATS_ALARM_RAISED = 3, /**< Stats Alarm Raised. */
    BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_auto_subgroup__begin BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP__BEGIN
#define bcmolt_access_control_auto_subgroup_all BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP_ALL
#define bcmolt_access_control_auto_subgroup_receive_eth_packet BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP_RECEIVE_ETH_PACKET
#define bcmolt_access_control_auto_subgroup_stats_alarm_cleared BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP_STATS_ALARM_CLEARED
#define bcmolt_access_control_auto_subgroup_stats_alarm_raised BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP_STATS_ALARM_RAISED
#define bcmolt_access_control_auto_subgroup__num_of BCMOLT_ACCESS_CONTROL_AUTO_SUBGROUP__NUM_OF
#define bcmolt_access_control_auto_subgroup_all_properties 0xFFFF
#define bcmolt_access_control_auto_subgroup_full_mask 0xF

} bcmolt_access_control_auto_subgroup;

/** List of all access_control groups of type oper. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ACCESS_CONTROL_OPER_SUBGROUP_INTERFACES_UPDATE = 1, /**< update interface reference. */
    BCMOLT_ACCESS_CONTROL_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_oper_subgroup__begin BCMOLT_ACCESS_CONTROL_OPER_SUBGROUP__BEGIN
#define bcmolt_access_control_oper_subgroup_all BCMOLT_ACCESS_CONTROL_OPER_SUBGROUP_ALL
#define bcmolt_access_control_oper_subgroup_interfaces_update BCMOLT_ACCESS_CONTROL_OPER_SUBGROUP_INTERFACES_UPDATE
#define bcmolt_access_control_oper_subgroup__num_of BCMOLT_ACCESS_CONTROL_OPER_SUBGROUP__NUM_OF
#define bcmolt_access_control_oper_subgroup_all_properties 0xFFFF
#define bcmolt_access_control_oper_subgroup_full_mask 0x3

} bcmolt_access_control_oper_subgroup;

/** List of all device groups of type auto. */
typedef enum
{
    BCMOLT_DEVICE_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_DEVICE_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_COMPLETE = 1, /**< Connection Complete. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_ESTABLISHED = 2, /**< Connection Established. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_FAILURE = 3, /**< Connection Failure. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_DDR_TEST_COMPLETE = 4, /**< DDR Test Complete. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_DEVICE_KEEP_ALIVE = 5, /**< Device Keep Alive. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_DEVICE_READY = 6, /**< Device Ready. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_DISCONNECTION_COMPLETE = 7, /**< Disconnection Complete. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_IMAGE_TRANSFER_COMPLETE = 8, /**< Image Transfer Complete. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_INNI_MUX_CONFIGURATION_COMPLETED = 9, /**< INNI mux configuration completed. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_SW_ERROR = 10, /**< sw error. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_SW_EXCEPTION = 11, /**< sw exception. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_SW_HEALTH_CHECK_FAILURE = 12, /**< Software Health Check Failure. */
    BCMOLT_DEVICE_AUTO_SUBGROUP_TOD_CALIBRATION_DONE = 13, /**< tod calibration done. */
    BCMOLT_DEVICE_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_auto_subgroup__begin BCMOLT_DEVICE_AUTO_SUBGROUP__BEGIN
#define bcmolt_device_auto_subgroup_all BCMOLT_DEVICE_AUTO_SUBGROUP_ALL
#define bcmolt_device_auto_subgroup_connection_complete BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_COMPLETE
#define bcmolt_device_auto_subgroup_connection_established BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_ESTABLISHED
#define bcmolt_device_auto_subgroup_connection_failure BCMOLT_DEVICE_AUTO_SUBGROUP_CONNECTION_FAILURE
#define bcmolt_device_auto_subgroup_ddr_test_complete BCMOLT_DEVICE_AUTO_SUBGROUP_DDR_TEST_COMPLETE
#define bcmolt_device_auto_subgroup_device_keep_alive BCMOLT_DEVICE_AUTO_SUBGROUP_DEVICE_KEEP_ALIVE
#define bcmolt_device_auto_subgroup_device_ready BCMOLT_DEVICE_AUTO_SUBGROUP_DEVICE_READY
#define bcmolt_device_auto_subgroup_disconnection_complete BCMOLT_DEVICE_AUTO_SUBGROUP_DISCONNECTION_COMPLETE
#define bcmolt_device_auto_subgroup_image_transfer_complete BCMOLT_DEVICE_AUTO_SUBGROUP_IMAGE_TRANSFER_COMPLETE
#define bcmolt_device_auto_subgroup_inni_mux_configuration_completed BCMOLT_DEVICE_AUTO_SUBGROUP_INNI_MUX_CONFIGURATION_COMPLETED
#define bcmolt_device_auto_subgroup_sw_error BCMOLT_DEVICE_AUTO_SUBGROUP_SW_ERROR
#define bcmolt_device_auto_subgroup_sw_exception BCMOLT_DEVICE_AUTO_SUBGROUP_SW_EXCEPTION
#define bcmolt_device_auto_subgroup_sw_health_check_failure BCMOLT_DEVICE_AUTO_SUBGROUP_SW_HEALTH_CHECK_FAILURE
#define bcmolt_device_auto_subgroup_tod_calibration_done BCMOLT_DEVICE_AUTO_SUBGROUP_TOD_CALIBRATION_DONE
#define bcmolt_device_auto_subgroup__num_of BCMOLT_DEVICE_AUTO_SUBGROUP__NUM_OF
#define bcmolt_device_auto_subgroup_all_properties 0xFFFF
#define bcmolt_device_auto_subgroup_full_mask 0x3FFF

} bcmolt_device_auto_subgroup;

/** List of all device groups of type oper. */
typedef enum
{
    BCMOLT_DEVICE_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_DEVICE_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_DEVICE_OPER_SUBGROUP_CHANGE_INNI_MUX = 1, /**< Change_configuration_completed INNI mux. */
    BCMOLT_DEVICE_OPER_SUBGROUP_CONNECT = 2, /**< Connect. */
    BCMOLT_DEVICE_OPER_SUBGROUP_DISCONNECT = 3, /**< Device Disconnect. */
    BCMOLT_DEVICE_OPER_SUBGROUP_HOST_KEEP_ALIVE = 4, /**< Host Keep Alive (Internal). */
    BCMOLT_DEVICE_OPER_SUBGROUP_IMAGE_TRANSFER_DATA = 5, /**< Image Data Transfer Operation (Internal). */
    BCMOLT_DEVICE_OPER_SUBGROUP_IMAGE_TRANSFER_START = 6, /**< Start Image Transfer Operation. */
    BCMOLT_DEVICE_OPER_SUBGROUP_RESET = 7, /**< Device Reset. */
    BCMOLT_DEVICE_OPER_SUBGROUP_RUN_DDR_TEST = 8, /**< Run DDR Test. */
    BCMOLT_DEVICE_OPER_SUBGROUP_SET_8021_AS_TOD_STRING = 9, /**< Set ToD String for 802.1AS. */
    BCMOLT_DEVICE_OPER_SUBGROUP_SW_UPGRADE_ACTIVATE = 10, /**< SW upgrade activate. */
    BCMOLT_DEVICE_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_oper_subgroup__begin BCMOLT_DEVICE_OPER_SUBGROUP__BEGIN
#define bcmolt_device_oper_subgroup_all BCMOLT_DEVICE_OPER_SUBGROUP_ALL
#define bcmolt_device_oper_subgroup_change_inni_mux BCMOLT_DEVICE_OPER_SUBGROUP_CHANGE_INNI_MUX
#define bcmolt_device_oper_subgroup_connect BCMOLT_DEVICE_OPER_SUBGROUP_CONNECT
#define bcmolt_device_oper_subgroup_disconnect BCMOLT_DEVICE_OPER_SUBGROUP_DISCONNECT
#define bcmolt_device_oper_subgroup_host_keep_alive BCMOLT_DEVICE_OPER_SUBGROUP_HOST_KEEP_ALIVE
#define bcmolt_device_oper_subgroup_image_transfer_data BCMOLT_DEVICE_OPER_SUBGROUP_IMAGE_TRANSFER_DATA
#define bcmolt_device_oper_subgroup_image_transfer_start BCMOLT_DEVICE_OPER_SUBGROUP_IMAGE_TRANSFER_START
#define bcmolt_device_oper_subgroup_reset BCMOLT_DEVICE_OPER_SUBGROUP_RESET
#define bcmolt_device_oper_subgroup_run_ddr_test BCMOLT_DEVICE_OPER_SUBGROUP_RUN_DDR_TEST
#define bcmolt_device_oper_subgroup_set_8021_as_tod_string BCMOLT_DEVICE_OPER_SUBGROUP_SET_8021_AS_TOD_STRING
#define bcmolt_device_oper_subgroup_sw_upgrade_activate BCMOLT_DEVICE_OPER_SUBGROUP_SW_UPGRADE_ACTIVATE
#define bcmolt_device_oper_subgroup__num_of BCMOLT_DEVICE_OPER_SUBGROUP__NUM_OF
#define bcmolt_device_oper_subgroup_all_properties 0xFFFF
#define bcmolt_device_oper_subgroup_full_mask 0x7FF

} bcmolt_device_oper_subgroup;

/** List of all erps_interface groups of type auto. */
typedef enum
{
    BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP_PORT_UPDATE_COMPLETE = 1, /**< erps port update completed. */
    BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP_RING_PORT_CONTROL = 2, /**< Ring Port Control. */
    BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_interface_auto_subgroup__begin BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP__BEGIN
#define bcmolt_erps_interface_auto_subgroup_all BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP_ALL
#define bcmolt_erps_interface_auto_subgroup_port_update_complete BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP_PORT_UPDATE_COMPLETE
#define bcmolt_erps_interface_auto_subgroup_ring_port_control BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP_RING_PORT_CONTROL
#define bcmolt_erps_interface_auto_subgroup__num_of BCMOLT_ERPS_INTERFACE_AUTO_SUBGROUP__NUM_OF
#define bcmolt_erps_interface_auto_subgroup_all_properties 0xFFFF
#define bcmolt_erps_interface_auto_subgroup_full_mask 0x7

} bcmolt_erps_interface_auto_subgroup;

/** List of all erps_interface groups of type oper. */
typedef enum
{
    BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP_PORT_UPDATE = 1, /**< erps port update. */
    BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP_SET_RING_PORT_CONTROL = 2, /**< Set Ring Port Control. */
    BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_interface_oper_subgroup__begin BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP__BEGIN
#define bcmolt_erps_interface_oper_subgroup_all BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP_ALL
#define bcmolt_erps_interface_oper_subgroup_port_update BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP_PORT_UPDATE
#define bcmolt_erps_interface_oper_subgroup_set_ring_port_control BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP_SET_RING_PORT_CONTROL
#define bcmolt_erps_interface_oper_subgroup__num_of BCMOLT_ERPS_INTERFACE_OPER_SUBGROUP__NUM_OF
#define bcmolt_erps_interface_oper_subgroup_all_properties 0xFFFF
#define bcmolt_erps_interface_oper_subgroup_full_mask 0x7

} bcmolt_erps_interface_oper_subgroup;

/** List of all eth_oam groups of type stat. */
typedef enum
{
    BCMOLT_ETH_OAM_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_ETH_OAM_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ETH_OAM_STAT_SUBGROUP_STATS = 1, /**< stats. */
    BCMOLT_ETH_OAM_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_stat_subgroup__begin BCMOLT_ETH_OAM_STAT_SUBGROUP__BEGIN
#define bcmolt_eth_oam_stat_subgroup_all BCMOLT_ETH_OAM_STAT_SUBGROUP_ALL
#define bcmolt_eth_oam_stat_subgroup_stats BCMOLT_ETH_OAM_STAT_SUBGROUP_STATS
#define bcmolt_eth_oam_stat_subgroup__num_of BCMOLT_ETH_OAM_STAT_SUBGROUP__NUM_OF
#define bcmolt_eth_oam_stat_subgroup_all_properties 0xFFFF
#define bcmolt_eth_oam_stat_subgroup_full_mask 0x3

} bcmolt_eth_oam_stat_subgroup;

/** List of all eth_oam groups of type stat_cfg. */
typedef enum
{
    BCMOLT_ETH_OAM_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_ETH_OAM_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ETH_OAM_STAT_CFG_SUBGROUP_STATS_CFG = 1, /**< Stats Configuration. */
    BCMOLT_ETH_OAM_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_stat_cfg_subgroup__begin BCMOLT_ETH_OAM_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_eth_oam_stat_cfg_subgroup_all BCMOLT_ETH_OAM_STAT_CFG_SUBGROUP_ALL
#define bcmolt_eth_oam_stat_cfg_subgroup_stats_cfg BCMOLT_ETH_OAM_STAT_CFG_SUBGROUP_STATS_CFG
#define bcmolt_eth_oam_stat_cfg_subgroup__num_of BCMOLT_ETH_OAM_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_eth_oam_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_eth_oam_stat_cfg_subgroup_full_mask 0x3

} bcmolt_eth_oam_stat_cfg_subgroup;

/** List of all eth_oam groups of type auto. */
typedef enum
{
    BCMOLT_ETH_OAM_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_ETH_OAM_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ETH_OAM_AUTO_SUBGROUP_CCM_EVENT = 1, /**< CFM CCM Event. */
    BCMOLT_ETH_OAM_AUTO_SUBGROUP_STATE_CHANGE = 2, /**< State Change. */
    BCMOLT_ETH_OAM_AUTO_SUBGROUP_STATS_ALARM_CLEARED = 3, /**< Stats Alarm Cleared. */
    BCMOLT_ETH_OAM_AUTO_SUBGROUP_STATS_ALARM_RAISED = 4, /**< Stats Alarm Raised. */
    BCMOLT_ETH_OAM_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_auto_subgroup__begin BCMOLT_ETH_OAM_AUTO_SUBGROUP__BEGIN
#define bcmolt_eth_oam_auto_subgroup_all BCMOLT_ETH_OAM_AUTO_SUBGROUP_ALL
#define bcmolt_eth_oam_auto_subgroup_ccm_event BCMOLT_ETH_OAM_AUTO_SUBGROUP_CCM_EVENT
#define bcmolt_eth_oam_auto_subgroup_state_change BCMOLT_ETH_OAM_AUTO_SUBGROUP_STATE_CHANGE
#define bcmolt_eth_oam_auto_subgroup_stats_alarm_cleared BCMOLT_ETH_OAM_AUTO_SUBGROUP_STATS_ALARM_CLEARED
#define bcmolt_eth_oam_auto_subgroup_stats_alarm_raised BCMOLT_ETH_OAM_AUTO_SUBGROUP_STATS_ALARM_RAISED
#define bcmolt_eth_oam_auto_subgroup__num_of BCMOLT_ETH_OAM_AUTO_SUBGROUP__NUM_OF
#define bcmolt_eth_oam_auto_subgroup_all_properties 0xFFFF
#define bcmolt_eth_oam_auto_subgroup_full_mask 0x1F

} bcmolt_eth_oam_auto_subgroup;

/** List of all eth_oam groups of type oper. */
typedef enum
{
    BCMOLT_ETH_OAM_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_ETH_OAM_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ETH_OAM_OPER_SUBGROUP_SET_MEP_STATE = 1, /**< Set MEP Control State. */
    BCMOLT_ETH_OAM_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_oper_subgroup__begin BCMOLT_ETH_OAM_OPER_SUBGROUP__BEGIN
#define bcmolt_eth_oam_oper_subgroup_all BCMOLT_ETH_OAM_OPER_SUBGROUP_ALL
#define bcmolt_eth_oam_oper_subgroup_set_mep_state BCMOLT_ETH_OAM_OPER_SUBGROUP_SET_MEP_STATE
#define bcmolt_eth_oam_oper_subgroup__num_of BCMOLT_ETH_OAM_OPER_SUBGROUP__NUM_OF
#define bcmolt_eth_oam_oper_subgroup_all_properties 0xFFFF
#define bcmolt_eth_oam_oper_subgroup_full_mask 0x3

} bcmolt_eth_oam_oper_subgroup;

/** List of all flow groups of type stat. */
typedef enum
{
    BCMOLT_FLOW_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_FLOW_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_FLOW_STAT_SUBGROUP_STATS = 1, /**< Statistics. */
    BCMOLT_FLOW_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_stat_subgroup__begin BCMOLT_FLOW_STAT_SUBGROUP__BEGIN
#define bcmolt_flow_stat_subgroup_all BCMOLT_FLOW_STAT_SUBGROUP_ALL
#define bcmolt_flow_stat_subgroup_stats BCMOLT_FLOW_STAT_SUBGROUP_STATS
#define bcmolt_flow_stat_subgroup__num_of BCMOLT_FLOW_STAT_SUBGROUP__NUM_OF
#define bcmolt_flow_stat_subgroup_all_properties 0xFFFF
#define bcmolt_flow_stat_subgroup_full_mask 0x3

} bcmolt_flow_stat_subgroup;

/** List of all flow groups of type stat_cfg. */
typedef enum
{
    BCMOLT_FLOW_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_FLOW_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_FLOW_STAT_CFG_SUBGROUP_STATS_CFG = 1, /**< Statistics Configuration. */
    BCMOLT_FLOW_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_stat_cfg_subgroup__begin BCMOLT_FLOW_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_flow_stat_cfg_subgroup_all BCMOLT_FLOW_STAT_CFG_SUBGROUP_ALL
#define bcmolt_flow_stat_cfg_subgroup_stats_cfg BCMOLT_FLOW_STAT_CFG_SUBGROUP_STATS_CFG
#define bcmolt_flow_stat_cfg_subgroup__num_of BCMOLT_FLOW_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_flow_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_flow_stat_cfg_subgroup_full_mask 0x3

} bcmolt_flow_stat_cfg_subgroup;

/** List of all flow groups of type auto. */
typedef enum
{
    BCMOLT_FLOW_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_FLOW_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_FLOW_AUTO_SUBGROUP_STATS_ALARM_CLEARED = 1, /**< Statistics Alarm Cleared. */
    BCMOLT_FLOW_AUTO_SUBGROUP_STATS_ALARM_RAISED = 2, /**< Statistics Alarm Raised. */
    BCMOLT_FLOW_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_auto_subgroup__begin BCMOLT_FLOW_AUTO_SUBGROUP__BEGIN
#define bcmolt_flow_auto_subgroup_all BCMOLT_FLOW_AUTO_SUBGROUP_ALL
#define bcmolt_flow_auto_subgroup_stats_alarm_cleared BCMOLT_FLOW_AUTO_SUBGROUP_STATS_ALARM_CLEARED
#define bcmolt_flow_auto_subgroup_stats_alarm_raised BCMOLT_FLOW_AUTO_SUBGROUP_STATS_ALARM_RAISED
#define bcmolt_flow_auto_subgroup__num_of BCMOLT_FLOW_AUTO_SUBGROUP__NUM_OF
#define bcmolt_flow_auto_subgroup_all_properties 0xFFFF
#define bcmolt_flow_auto_subgroup_full_mask 0x7

} bcmolt_flow_auto_subgroup;

/** List of all flow groups of type oper. */
typedef enum
{
    BCMOLT_FLOW_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_FLOW_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_FLOW_OPER_SUBGROUP_SEND_ETH_PACKET = 1, /**< send_eth_packet. */
    BCMOLT_FLOW_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_oper_subgroup__begin BCMOLT_FLOW_OPER_SUBGROUP__BEGIN
#define bcmolt_flow_oper_subgroup_all BCMOLT_FLOW_OPER_SUBGROUP_ALL
#define bcmolt_flow_oper_subgroup_send_eth_packet BCMOLT_FLOW_OPER_SUBGROUP_SEND_ETH_PACKET
#define bcmolt_flow_oper_subgroup__num_of BCMOLT_FLOW_OPER_SUBGROUP__NUM_OF
#define bcmolt_flow_oper_subgroup_all_properties 0xFFFF
#define bcmolt_flow_oper_subgroup_full_mask 0x3

} bcmolt_flow_oper_subgroup;

/** List of all group groups of type auto. */
typedef enum
{
    BCMOLT_GROUP_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_GROUP_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_GROUP_AUTO_SUBGROUP_COMPLETE_MEMBERS_UPDATE = 1, /**< complete_members_update. */
    BCMOLT_GROUP_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_group_auto_subgroup__begin BCMOLT_GROUP_AUTO_SUBGROUP__BEGIN
#define bcmolt_group_auto_subgroup_all BCMOLT_GROUP_AUTO_SUBGROUP_ALL
#define bcmolt_group_auto_subgroup_complete_members_update BCMOLT_GROUP_AUTO_SUBGROUP_COMPLETE_MEMBERS_UPDATE
#define bcmolt_group_auto_subgroup__num_of BCMOLT_GROUP_AUTO_SUBGROUP__NUM_OF
#define bcmolt_group_auto_subgroup_all_properties 0xFFFF
#define bcmolt_group_auto_subgroup_full_mask 0x3

} bcmolt_group_auto_subgroup;

/** List of all group groups of type oper. */
typedef enum
{
    BCMOLT_GROUP_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_GROUP_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_GROUP_OPER_SUBGROUP_MEMBERS_UPDATE = 1, /**< members_update. */
    BCMOLT_GROUP_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_group_oper_subgroup__begin BCMOLT_GROUP_OPER_SUBGROUP__BEGIN
#define bcmolt_group_oper_subgroup_all BCMOLT_GROUP_OPER_SUBGROUP_ALL
#define bcmolt_group_oper_subgroup_members_update BCMOLT_GROUP_OPER_SUBGROUP_MEMBERS_UPDATE
#define bcmolt_group_oper_subgroup__num_of BCMOLT_GROUP_OPER_SUBGROUP__NUM_OF
#define bcmolt_group_oper_subgroup_all_properties 0xFFFF
#define bcmolt_group_oper_subgroup_full_mask 0x3

} bcmolt_group_oper_subgroup;

/** List of all host_log_file groups of type oper. */
typedef enum
{
    BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP_CLEAR = 1, /**< Clear. */
    BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP_RESET_BUFFER_PTR = 2, /**< Reset Buffer Pointer. */
    BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_host_log_file_oper_subgroup__begin BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP__BEGIN
#define bcmolt_host_log_file_oper_subgroup_all BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP_ALL
#define bcmolt_host_log_file_oper_subgroup_clear BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP_CLEAR
#define bcmolt_host_log_file_oper_subgroup_reset_buffer_ptr BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP_RESET_BUFFER_PTR
#define bcmolt_host_log_file_oper_subgroup__num_of BCMOLT_HOST_LOG_FILE_OPER_SUBGROUP__NUM_OF
#define bcmolt_host_log_file_oper_subgroup_all_properties 0xFFFF
#define bcmolt_host_log_file_oper_subgroup_full_mask 0x7

} bcmolt_host_log_file_oper_subgroup;

/** List of all internal_nni groups of type stat. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_INTERNAL_NNI_STAT_SUBGROUP_ENET_STATS = 1, /**< Ethernet Statistics. */
    BCMOLT_INTERNAL_NNI_STAT_SUBGROUP_NNI_STATS = 2, /**< NNI and AE Counters (RMON). */
    BCMOLT_INTERNAL_NNI_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_stat_subgroup__begin BCMOLT_INTERNAL_NNI_STAT_SUBGROUP__BEGIN
#define bcmolt_internal_nni_stat_subgroup_all BCMOLT_INTERNAL_NNI_STAT_SUBGROUP_ALL
#define bcmolt_internal_nni_stat_subgroup_enet_stats BCMOLT_INTERNAL_NNI_STAT_SUBGROUP_ENET_STATS
#define bcmolt_internal_nni_stat_subgroup_nni_stats BCMOLT_INTERNAL_NNI_STAT_SUBGROUP_NNI_STATS
#define bcmolt_internal_nni_stat_subgroup__num_of BCMOLT_INTERNAL_NNI_STAT_SUBGROUP__NUM_OF
#define bcmolt_internal_nni_stat_subgroup_all_properties 0xFFFF
#define bcmolt_internal_nni_stat_subgroup_full_mask 0x7

} bcmolt_internal_nni_stat_subgroup;

/** List of all internal_nni groups of type stat_cfg. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP_ENET_STATS_CFG = 1, /**< Ethernet Statistics Configuration. */
    BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP_NNI_STATS_CFG = 2, /**< NNI And AE Counters (RMON) Configuration. */
    BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_stat_cfg_subgroup__begin BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_internal_nni_stat_cfg_subgroup_all BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP_ALL
#define bcmolt_internal_nni_stat_cfg_subgroup_enet_stats_cfg BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP_ENET_STATS_CFG
#define bcmolt_internal_nni_stat_cfg_subgroup_nni_stats_cfg BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP_NNI_STATS_CFG
#define bcmolt_internal_nni_stat_cfg_subgroup__num_of BCMOLT_INTERNAL_NNI_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_internal_nni_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_internal_nni_stat_cfg_subgroup_full_mask 0x7

} bcmolt_internal_nni_stat_cfg_subgroup;

/** List of all internal_nni groups of type auto. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_ENET_STATS_ALARM_CLEARED = 1, /**< Ethernet Statistics Alarm Cleared. */
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_ENET_STATS_ALARM_RAISED = 2, /**< Ethernet Statistics Alarm Raised. */
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_NNI_STATS_ALARM_CLEARED = 3, /**< NNI And AE Counters (RMON) Alarm Cleared. */
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_NNI_STATS_ALARM_RAISED = 4, /**< NNI And AE Counters (RMON) Alarm Raised. */
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_PACKET_CAPTURED = 5, /**< Packet Captured. */
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_STATUS_CHANGED = 6, /**< Status changed. */
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_SWAP_COMPLETED = 7, /**< intetrnal inni sawp completed. */
    BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_auto_subgroup__begin BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP__BEGIN
#define bcmolt_internal_nni_auto_subgroup_all BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_ALL
#define bcmolt_internal_nni_auto_subgroup_enet_stats_alarm_cleared BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_ENET_STATS_ALARM_CLEARED
#define bcmolt_internal_nni_auto_subgroup_enet_stats_alarm_raised BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_ENET_STATS_ALARM_RAISED
#define bcmolt_internal_nni_auto_subgroup_nni_stats_alarm_cleared BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_NNI_STATS_ALARM_CLEARED
#define bcmolt_internal_nni_auto_subgroup_nni_stats_alarm_raised BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_NNI_STATS_ALARM_RAISED
#define bcmolt_internal_nni_auto_subgroup_packet_captured BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_PACKET_CAPTURED
#define bcmolt_internal_nni_auto_subgroup_status_changed BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_STATUS_CHANGED
#define bcmolt_internal_nni_auto_subgroup_swap_completed BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP_SWAP_COMPLETED
#define bcmolt_internal_nni_auto_subgroup__num_of BCMOLT_INTERNAL_NNI_AUTO_SUBGROUP__NUM_OF
#define bcmolt_internal_nni_auto_subgroup_all_properties 0xFFFF
#define bcmolt_internal_nni_auto_subgroup_full_mask 0xFF

} bcmolt_internal_nni_auto_subgroup;

/** List of all internal_nni groups of type oper. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_INTERNAL_NNI_OPER_SUBGROUP_SEND_ETH_PACKET = 1, /**< send_eth_packet. */
    BCMOLT_INTERNAL_NNI_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_oper_subgroup__begin BCMOLT_INTERNAL_NNI_OPER_SUBGROUP__BEGIN
#define bcmolt_internal_nni_oper_subgroup_all BCMOLT_INTERNAL_NNI_OPER_SUBGROUP_ALL
#define bcmolt_internal_nni_oper_subgroup_send_eth_packet BCMOLT_INTERNAL_NNI_OPER_SUBGROUP_SEND_ETH_PACKET
#define bcmolt_internal_nni_oper_subgroup__num_of BCMOLT_INTERNAL_NNI_OPER_SUBGROUP__NUM_OF
#define bcmolt_internal_nni_oper_subgroup_all_properties 0xFFFF
#define bcmolt_internal_nni_oper_subgroup_full_mask 0x3

} bcmolt_internal_nni_oper_subgroup;

/** List of all itupon_alloc groups of type stat. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ITUPON_ALLOC_STAT_SUBGROUP_STATS = 1, /**< Statistics. */
    BCMOLT_ITUPON_ALLOC_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_stat_subgroup__begin BCMOLT_ITUPON_ALLOC_STAT_SUBGROUP__BEGIN
#define bcmolt_itupon_alloc_stat_subgroup_all BCMOLT_ITUPON_ALLOC_STAT_SUBGROUP_ALL
#define bcmolt_itupon_alloc_stat_subgroup_stats BCMOLT_ITUPON_ALLOC_STAT_SUBGROUP_STATS
#define bcmolt_itupon_alloc_stat_subgroup__num_of BCMOLT_ITUPON_ALLOC_STAT_SUBGROUP__NUM_OF
#define bcmolt_itupon_alloc_stat_subgroup_all_properties 0xFFFF
#define bcmolt_itupon_alloc_stat_subgroup_full_mask 0x3

} bcmolt_itupon_alloc_stat_subgroup;

/** List of all itupon_alloc groups of type stat_cfg. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ITUPON_ALLOC_STAT_CFG_SUBGROUP_STATS_CFG = 1, /**< Statistics Configuration. */
    BCMOLT_ITUPON_ALLOC_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_stat_cfg_subgroup__begin BCMOLT_ITUPON_ALLOC_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_itupon_alloc_stat_cfg_subgroup_all BCMOLT_ITUPON_ALLOC_STAT_CFG_SUBGROUP_ALL
#define bcmolt_itupon_alloc_stat_cfg_subgroup_stats_cfg BCMOLT_ITUPON_ALLOC_STAT_CFG_SUBGROUP_STATS_CFG
#define bcmolt_itupon_alloc_stat_cfg_subgroup__num_of BCMOLT_ITUPON_ALLOC_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_itupon_alloc_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_itupon_alloc_stat_cfg_subgroup_full_mask 0x3

} bcmolt_itupon_alloc_stat_cfg_subgroup;

/** List of all itupon_alloc groups of type auto. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_CONFIGURATION_COMPLETED = 1, /**< Configuration Completed. */
    BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_GET_ALLOC_STATS_COMPLETED = 2, /**< Get alloc level statistics completed. */
    BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_STATS_ALARM_CLEARED = 3, /**< Statistics Alarm Cleared. */
    BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_STATS_ALARM_RAISED = 4, /**< Statistics Alarm Raised. */
    BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_auto_subgroup__begin BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP__BEGIN
#define bcmolt_itupon_alloc_auto_subgroup_all BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_ALL
#define bcmolt_itupon_alloc_auto_subgroup_configuration_completed BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_CONFIGURATION_COMPLETED
#define bcmolt_itupon_alloc_auto_subgroup_get_alloc_stats_completed BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_GET_ALLOC_STATS_COMPLETED
#define bcmolt_itupon_alloc_auto_subgroup_stats_alarm_cleared BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_STATS_ALARM_CLEARED
#define bcmolt_itupon_alloc_auto_subgroup_stats_alarm_raised BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP_STATS_ALARM_RAISED
#define bcmolt_itupon_alloc_auto_subgroup__num_of BCMOLT_ITUPON_ALLOC_AUTO_SUBGROUP__NUM_OF
#define bcmolt_itupon_alloc_auto_subgroup_all_properties 0xFFFF
#define bcmolt_itupon_alloc_auto_subgroup_full_mask 0x1F

} bcmolt_itupon_alloc_auto_subgroup;

/** List of all itupon_alloc groups of type oper. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP_GET_STATS = 1, /**< Get alloc level statistics. */
    BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP_SET_STATE = 2, /**< Set state. */
    BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_oper_subgroup__begin BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP__BEGIN
#define bcmolt_itupon_alloc_oper_subgroup_all BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP_ALL
#define bcmolt_itupon_alloc_oper_subgroup_get_stats BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP_GET_STATS
#define bcmolt_itupon_alloc_oper_subgroup_set_state BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP_SET_STATE
#define bcmolt_itupon_alloc_oper_subgroup__num_of BCMOLT_ITUPON_ALLOC_OPER_SUBGROUP__NUM_OF
#define bcmolt_itupon_alloc_oper_subgroup_all_properties 0xFFFF
#define bcmolt_itupon_alloc_oper_subgroup_full_mask 0x7

} bcmolt_itupon_alloc_oper_subgroup;

/** List of all itupon_gem groups of type stat. */
typedef enum
{
    BCMOLT_ITUPON_GEM_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_ITUPON_GEM_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ITUPON_GEM_STAT_SUBGROUP_STATS = 1, /**< Statistics. */
    BCMOLT_ITUPON_GEM_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_stat_subgroup__begin BCMOLT_ITUPON_GEM_STAT_SUBGROUP__BEGIN
#define bcmolt_itupon_gem_stat_subgroup_all BCMOLT_ITUPON_GEM_STAT_SUBGROUP_ALL
#define bcmolt_itupon_gem_stat_subgroup_stats BCMOLT_ITUPON_GEM_STAT_SUBGROUP_STATS
#define bcmolt_itupon_gem_stat_subgroup__num_of BCMOLT_ITUPON_GEM_STAT_SUBGROUP__NUM_OF
#define bcmolt_itupon_gem_stat_subgroup_all_properties 0xFFFF
#define bcmolt_itupon_gem_stat_subgroup_full_mask 0x3

} bcmolt_itupon_gem_stat_subgroup;

/** List of all itupon_gem groups of type stat_cfg. */
typedef enum
{
    BCMOLT_ITUPON_GEM_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_ITUPON_GEM_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ITUPON_GEM_STAT_CFG_SUBGROUP_STATS_CFG = 1, /**< Statistics Configuration. */
    BCMOLT_ITUPON_GEM_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_stat_cfg_subgroup__begin BCMOLT_ITUPON_GEM_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_itupon_gem_stat_cfg_subgroup_all BCMOLT_ITUPON_GEM_STAT_CFG_SUBGROUP_ALL
#define bcmolt_itupon_gem_stat_cfg_subgroup_stats_cfg BCMOLT_ITUPON_GEM_STAT_CFG_SUBGROUP_STATS_CFG
#define bcmolt_itupon_gem_stat_cfg_subgroup__num_of BCMOLT_ITUPON_GEM_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_itupon_gem_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_itupon_gem_stat_cfg_subgroup_full_mask 0x3

} bcmolt_itupon_gem_stat_cfg_subgroup;

/** List of all itupon_gem groups of type auto. */
typedef enum
{
    BCMOLT_ITUPON_GEM_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_ITUPON_GEM_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ITUPON_GEM_AUTO_SUBGROUP_CONFIGURATION_COMPLETED = 1, /**< Configuration Completed. */
    BCMOLT_ITUPON_GEM_AUTO_SUBGROUP_STATS_ALARM_CLEARED = 2, /**< Statistics Alarm Cleared. */
    BCMOLT_ITUPON_GEM_AUTO_SUBGROUP_STATS_ALARM_RAISED = 3, /**< Statistics Alarm Raised. */
    BCMOLT_ITUPON_GEM_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_auto_subgroup__begin BCMOLT_ITUPON_GEM_AUTO_SUBGROUP__BEGIN
#define bcmolt_itupon_gem_auto_subgroup_all BCMOLT_ITUPON_GEM_AUTO_SUBGROUP_ALL
#define bcmolt_itupon_gem_auto_subgroup_configuration_completed BCMOLT_ITUPON_GEM_AUTO_SUBGROUP_CONFIGURATION_COMPLETED
#define bcmolt_itupon_gem_auto_subgroup_stats_alarm_cleared BCMOLT_ITUPON_GEM_AUTO_SUBGROUP_STATS_ALARM_CLEARED
#define bcmolt_itupon_gem_auto_subgroup_stats_alarm_raised BCMOLT_ITUPON_GEM_AUTO_SUBGROUP_STATS_ALARM_RAISED
#define bcmolt_itupon_gem_auto_subgroup__num_of BCMOLT_ITUPON_GEM_AUTO_SUBGROUP__NUM_OF
#define bcmolt_itupon_gem_auto_subgroup_all_properties 0xFFFF
#define bcmolt_itupon_gem_auto_subgroup_full_mask 0xF

} bcmolt_itupon_gem_auto_subgroup;

/** List of all itupon_gem groups of type oper. */
typedef enum
{
    BCMOLT_ITUPON_GEM_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_ITUPON_GEM_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ITUPON_GEM_OPER_SUBGROUP_SET_STATE = 1, /**< Set state. */
    BCMOLT_ITUPON_GEM_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_oper_subgroup__begin BCMOLT_ITUPON_GEM_OPER_SUBGROUP__BEGIN
#define bcmolt_itupon_gem_oper_subgroup_all BCMOLT_ITUPON_GEM_OPER_SUBGROUP_ALL
#define bcmolt_itupon_gem_oper_subgroup_set_state BCMOLT_ITUPON_GEM_OPER_SUBGROUP_SET_STATE
#define bcmolt_itupon_gem_oper_subgroup__num_of BCMOLT_ITUPON_GEM_OPER_SUBGROUP__NUM_OF
#define bcmolt_itupon_gem_oper_subgroup_all_properties 0xFFFF
#define bcmolt_itupon_gem_oper_subgroup_full_mask 0x3

} bcmolt_itupon_gem_oper_subgroup;

/** List of all lag_interface groups of type stat. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_LAG_INTERFACE_STAT_SUBGROUP_STATS = 1, /**< LAG Interface Statistics. */
    BCMOLT_LAG_INTERFACE_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_stat_subgroup__begin BCMOLT_LAG_INTERFACE_STAT_SUBGROUP__BEGIN
#define bcmolt_lag_interface_stat_subgroup_all BCMOLT_LAG_INTERFACE_STAT_SUBGROUP_ALL
#define bcmolt_lag_interface_stat_subgroup_stats BCMOLT_LAG_INTERFACE_STAT_SUBGROUP_STATS
#define bcmolt_lag_interface_stat_subgroup__num_of BCMOLT_LAG_INTERFACE_STAT_SUBGROUP__NUM_OF
#define bcmolt_lag_interface_stat_subgroup_all_properties 0xFFFF
#define bcmolt_lag_interface_stat_subgroup_full_mask 0x3

} bcmolt_lag_interface_stat_subgroup;

/** List of all lag_interface groups of type stat_cfg. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_LAG_INTERFACE_STAT_CFG_SUBGROUP_STATS_CFG = 1, /**< LAG Interface Statistics Configuration. */
    BCMOLT_LAG_INTERFACE_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_stat_cfg_subgroup__begin BCMOLT_LAG_INTERFACE_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_lag_interface_stat_cfg_subgroup_all BCMOLT_LAG_INTERFACE_STAT_CFG_SUBGROUP_ALL
#define bcmolt_lag_interface_stat_cfg_subgroup_stats_cfg BCMOLT_LAG_INTERFACE_STAT_CFG_SUBGROUP_STATS_CFG
#define bcmolt_lag_interface_stat_cfg_subgroup__num_of BCMOLT_LAG_INTERFACE_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_lag_interface_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_lag_interface_stat_cfg_subgroup_full_mask 0x3

} bcmolt_lag_interface_stat_cfg_subgroup;

/** List of all lag_interface groups of type auto. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_COMPLETE_MEMBERS_UPDATE = 1, /**< complete_members_update. */
    BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_LAG_HEALTH_CHANGE = 2, /**< LAG health change. */
    BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_STATE_UPDATED = 3, /**< interface state updated. */
    BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_STATS_ALARM_CLEARED = 4, /**< LAG Interface Statistics Alarm Cleared. */
    BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_STATS_ALARM_RAISED = 5, /**< LAG Interface Statistics Alarm Raised. */
    BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_auto_subgroup__begin BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP__BEGIN
#define bcmolt_lag_interface_auto_subgroup_all BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_ALL
#define bcmolt_lag_interface_auto_subgroup_complete_members_update BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_COMPLETE_MEMBERS_UPDATE
#define bcmolt_lag_interface_auto_subgroup_lag_health_change BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_LAG_HEALTH_CHANGE
#define bcmolt_lag_interface_auto_subgroup_state_updated BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_STATE_UPDATED
#define bcmolt_lag_interface_auto_subgroup_stats_alarm_cleared BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_STATS_ALARM_CLEARED
#define bcmolt_lag_interface_auto_subgroup_stats_alarm_raised BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP_STATS_ALARM_RAISED
#define bcmolt_lag_interface_auto_subgroup__num_of BCMOLT_LAG_INTERFACE_AUTO_SUBGROUP__NUM_OF
#define bcmolt_lag_interface_auto_subgroup_all_properties 0xFFFF
#define bcmolt_lag_interface_auto_subgroup_full_mask 0x3F

} bcmolt_lag_interface_auto_subgroup;

/** List of all lag_interface groups of type oper. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_LAG_INTERFACE_OPER_SUBGROUP_MEMBERS_UPDATE = 1, /**< members_update. */
    BCMOLT_LAG_INTERFACE_OPER_SUBGROUP_STATE_UPDATE = 2, /**< state_update. */
    BCMOLT_LAG_INTERFACE_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_oper_subgroup__begin BCMOLT_LAG_INTERFACE_OPER_SUBGROUP__BEGIN
#define bcmolt_lag_interface_oper_subgroup_all BCMOLT_LAG_INTERFACE_OPER_SUBGROUP_ALL
#define bcmolt_lag_interface_oper_subgroup_members_update BCMOLT_LAG_INTERFACE_OPER_SUBGROUP_MEMBERS_UPDATE
#define bcmolt_lag_interface_oper_subgroup_state_update BCMOLT_LAG_INTERFACE_OPER_SUBGROUP_STATE_UPDATE
#define bcmolt_lag_interface_oper_subgroup__num_of BCMOLT_LAG_INTERFACE_OPER_SUBGROUP__NUM_OF
#define bcmolt_lag_interface_oper_subgroup_all_properties 0xFFFF
#define bcmolt_lag_interface_oper_subgroup_full_mask 0x7

} bcmolt_lag_interface_oper_subgroup;

/** List of all log_file groups of type oper. */
typedef enum
{
    BCMOLT_LOG_FILE_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_LOG_FILE_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_LOG_FILE_OPER_SUBGROUP_CLEAR = 1, /**< Clear. */
    BCMOLT_LOG_FILE_OPER_SUBGROUP_RESET_BUFFER_PTR = 2, /**< Reset Buffer Pointer. */
    BCMOLT_LOG_FILE_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_log_file_oper_subgroup__begin BCMOLT_LOG_FILE_OPER_SUBGROUP__BEGIN
#define bcmolt_log_file_oper_subgroup_all BCMOLT_LOG_FILE_OPER_SUBGROUP_ALL
#define bcmolt_log_file_oper_subgroup_clear BCMOLT_LOG_FILE_OPER_SUBGROUP_CLEAR
#define bcmolt_log_file_oper_subgroup_reset_buffer_ptr BCMOLT_LOG_FILE_OPER_SUBGROUP_RESET_BUFFER_PTR
#define bcmolt_log_file_oper_subgroup__num_of BCMOLT_LOG_FILE_OPER_SUBGROUP__NUM_OF
#define bcmolt_log_file_oper_subgroup_all_properties 0xFFFF
#define bcmolt_log_file_oper_subgroup_full_mask 0x7

} bcmolt_log_file_oper_subgroup;

/** List of all nni_interface groups of type stat. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_NNI_INTERFACE_STAT_SUBGROUP_STATS = 1, /**< NNI Interface Statistics. */
    BCMOLT_NNI_INTERFACE_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_stat_subgroup__begin BCMOLT_NNI_INTERFACE_STAT_SUBGROUP__BEGIN
#define bcmolt_nni_interface_stat_subgroup_all BCMOLT_NNI_INTERFACE_STAT_SUBGROUP_ALL
#define bcmolt_nni_interface_stat_subgroup_stats BCMOLT_NNI_INTERFACE_STAT_SUBGROUP_STATS
#define bcmolt_nni_interface_stat_subgroup__num_of BCMOLT_NNI_INTERFACE_STAT_SUBGROUP__NUM_OF
#define bcmolt_nni_interface_stat_subgroup_all_properties 0xFFFF
#define bcmolt_nni_interface_stat_subgroup_full_mask 0x3

} bcmolt_nni_interface_stat_subgroup;

/** List of all nni_interface groups of type stat_cfg. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_NNI_INTERFACE_STAT_CFG_SUBGROUP_STATS_CFG = 1, /**< NNI Interface Statistics Configuration. */
    BCMOLT_NNI_INTERFACE_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_stat_cfg_subgroup__begin BCMOLT_NNI_INTERFACE_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_nni_interface_stat_cfg_subgroup_all BCMOLT_NNI_INTERFACE_STAT_CFG_SUBGROUP_ALL
#define bcmolt_nni_interface_stat_cfg_subgroup_stats_cfg BCMOLT_NNI_INTERFACE_STAT_CFG_SUBGROUP_STATS_CFG
#define bcmolt_nni_interface_stat_cfg_subgroup__num_of BCMOLT_NNI_INTERFACE_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_nni_interface_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_nni_interface_stat_cfg_subgroup_full_mask 0x3

} bcmolt_nni_interface_stat_cfg_subgroup;

/** List of all nni_interface groups of type auto. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_LINK_STATE_CHANGE = 1, /**< link_state_change. */
    BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_STATE_CHANGE = 2, /**< State Change. */
    BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_STATS_ALARM_CLEARED = 3, /**< NNI Interface Statistics Alarm Cleared. */
    BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_STATS_ALARM_RAISED = 4, /**< NNI Interface Statistics Alarm Raised. */
    BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_auto_subgroup__begin BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP__BEGIN
#define bcmolt_nni_interface_auto_subgroup_all BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_ALL
#define bcmolt_nni_interface_auto_subgroup_link_state_change BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_LINK_STATE_CHANGE
#define bcmolt_nni_interface_auto_subgroup_state_change BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_STATE_CHANGE
#define bcmolt_nni_interface_auto_subgroup_stats_alarm_cleared BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_STATS_ALARM_CLEARED
#define bcmolt_nni_interface_auto_subgroup_stats_alarm_raised BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP_STATS_ALARM_RAISED
#define bcmolt_nni_interface_auto_subgroup__num_of BCMOLT_NNI_INTERFACE_AUTO_SUBGROUP__NUM_OF
#define bcmolt_nni_interface_auto_subgroup_all_properties 0xFFFF
#define bcmolt_nni_interface_auto_subgroup_full_mask 0x1F

} bcmolt_nni_interface_auto_subgroup;

/** List of all nni_interface groups of type oper. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_NNI_INTERFACE_OPER_SUBGROUP_SET_NNI_STATE = 1, /**< set_nni_state. */
    BCMOLT_NNI_INTERFACE_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_oper_subgroup__begin BCMOLT_NNI_INTERFACE_OPER_SUBGROUP__BEGIN
#define bcmolt_nni_interface_oper_subgroup_all BCMOLT_NNI_INTERFACE_OPER_SUBGROUP_ALL
#define bcmolt_nni_interface_oper_subgroup_set_nni_state BCMOLT_NNI_INTERFACE_OPER_SUBGROUP_SET_NNI_STATE
#define bcmolt_nni_interface_oper_subgroup__num_of BCMOLT_NNI_INTERFACE_OPER_SUBGROUP__NUM_OF
#define bcmolt_nni_interface_oper_subgroup_all_properties 0xFFFF
#define bcmolt_nni_interface_oper_subgroup_full_mask 0x3

} bcmolt_nni_interface_oper_subgroup;

/** List of all olt groups of type auto. */
typedef enum
{
    BCMOLT_OLT_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_OLT_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_OLT_AUTO_SUBGROUP_BAL_FAILURE = 1, /**< BAL and/or Switch Failed. */
    BCMOLT_OLT_AUTO_SUBGROUP_BAL_READY = 2, /**< BAL and Switch Ready. */
    BCMOLT_OLT_AUTO_SUBGROUP_SW_ERROR = 3, /**< OLT Software error. */
    BCMOLT_OLT_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_olt_auto_subgroup__begin BCMOLT_OLT_AUTO_SUBGROUP__BEGIN
#define bcmolt_olt_auto_subgroup_all BCMOLT_OLT_AUTO_SUBGROUP_ALL
#define bcmolt_olt_auto_subgroup_bal_failure BCMOLT_OLT_AUTO_SUBGROUP_BAL_FAILURE
#define bcmolt_olt_auto_subgroup_bal_ready BCMOLT_OLT_AUTO_SUBGROUP_BAL_READY
#define bcmolt_olt_auto_subgroup_sw_error BCMOLT_OLT_AUTO_SUBGROUP_SW_ERROR
#define bcmolt_olt_auto_subgroup__num_of BCMOLT_OLT_AUTO_SUBGROUP__NUM_OF
#define bcmolt_olt_auto_subgroup_all_properties 0xFFFF
#define bcmolt_olt_auto_subgroup_full_mask 0xF

} bcmolt_olt_auto_subgroup;

/** List of all olt groups of type oper. */
typedef enum
{
    BCMOLT_OLT_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_OLT_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_OLT_OPER_SUBGROUP_BAL_RESET = 1, /**< Reset BAL and Switch. */
    BCMOLT_OLT_OPER_SUBGROUP_CONNECT = 2, /**< connect. */
    BCMOLT_OLT_OPER_SUBGROUP_DISCONNECT = 3, /**< disconnect. */
    BCMOLT_OLT_OPER_SUBGROUP_RESET = 4, /**< OLT Reset. */
    BCMOLT_OLT_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_olt_oper_subgroup__begin BCMOLT_OLT_OPER_SUBGROUP__BEGIN
#define bcmolt_olt_oper_subgroup_all BCMOLT_OLT_OPER_SUBGROUP_ALL
#define bcmolt_olt_oper_subgroup_bal_reset BCMOLT_OLT_OPER_SUBGROUP_BAL_RESET
#define bcmolt_olt_oper_subgroup_connect BCMOLT_OLT_OPER_SUBGROUP_CONNECT
#define bcmolt_olt_oper_subgroup_disconnect BCMOLT_OLT_OPER_SUBGROUP_DISCONNECT
#define bcmolt_olt_oper_subgroup_reset BCMOLT_OLT_OPER_SUBGROUP_RESET
#define bcmolt_olt_oper_subgroup__num_of BCMOLT_OLT_OPER_SUBGROUP__NUM_OF
#define bcmolt_olt_oper_subgroup_all_properties 0xFFFF
#define bcmolt_olt_oper_subgroup_full_mask 0x1F

} bcmolt_olt_oper_subgroup;

/** List of all onu groups of type stat. */
typedef enum
{
    BCMOLT_ONU_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_ONU_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ONU_STAT_SUBGROUP_ITU_PON_STATS = 1, /**< ITU PON Statistics. */
    BCMOLT_ONU_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_stat_subgroup__begin BCMOLT_ONU_STAT_SUBGROUP__BEGIN
#define bcmolt_onu_stat_subgroup_all BCMOLT_ONU_STAT_SUBGROUP_ALL
#define bcmolt_onu_stat_subgroup_itu_pon_stats BCMOLT_ONU_STAT_SUBGROUP_ITU_PON_STATS
#define bcmolt_onu_stat_subgroup__num_of BCMOLT_ONU_STAT_SUBGROUP__NUM_OF
#define bcmolt_onu_stat_subgroup_all_properties 0xFFFF
#define bcmolt_onu_stat_subgroup_full_mask 0x3

} bcmolt_onu_stat_subgroup;

/** List of all onu groups of type stat_cfg. */
typedef enum
{
    BCMOLT_ONU_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_ONU_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ONU_STAT_CFG_SUBGROUP_ITU_PON_STATS_CFG = 1, /**< ITU PON Statistics Configuration. */
    BCMOLT_ONU_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_stat_cfg_subgroup__begin BCMOLT_ONU_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_onu_stat_cfg_subgroup_all BCMOLT_ONU_STAT_CFG_SUBGROUP_ALL
#define bcmolt_onu_stat_cfg_subgroup_itu_pon_stats_cfg BCMOLT_ONU_STAT_CFG_SUBGROUP_ITU_PON_STATS_CFG
#define bcmolt_onu_stat_cfg_subgroup__num_of BCMOLT_ONU_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_onu_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_onu_stat_cfg_subgroup_full_mask 0x3

} bcmolt_onu_stat_cfg_subgroup;

/** List of all onu groups of type auto. */
typedef enum
{
    BCMOLT_ONU_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_ONU_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ONU_AUTO_SUBGROUP_BER_INTERVAL_CONFIGURATION_COMPLETED = 1, /**< BER Interval Configuration Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_CPU_PACKET = 2, /**< XGPON CPU packet. */
    BCMOLT_ONU_AUTO_SUBGROUP_DFI = 3, /**< Receive Dying-Gasp of ONUi. */
    BCMOLT_ONU_AUTO_SUBGROUP_DGI = 4, /**< Receive Dying-Gasp of ONUi. */
    BCMOLT_ONU_AUTO_SUBGROUP_DOWI = 5, /**< Drift of Window of ONUi. */
    BCMOLT_ONU_AUTO_SUBGROUP_ERR = 6, /**< ERR. */
    BCMOLT_ONU_AUTO_SUBGROUP_GPON_ALARM = 7, /**< GPON ONU Alarm. */
    BCMOLT_ONU_AUTO_SUBGROUP_INVALID_DBRU_REPORT = 8, /**< Invalid DBRu Report. */
    BCMOLT_ONU_AUTO_SUBGROUP_ITU_PON_STATS_ALARM_CLEARED = 9, /**< ITU PON Statistics Alarm Cleared. */
    BCMOLT_ONU_AUTO_SUBGROUP_ITU_PON_STATS_ALARM_RAISED = 10, /**< ITU PON Statistics Alarm Raised. */
    BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_COMPLETED = 11, /**< Key Exchange Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_CYCLE_SKIPPED = 12, /**< Key Exchange Cycle Skipped. */
    BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_DECRYPT_REQUIRED = 13, /**< Key Exchange Decrypt Required. */
    BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_KEY_MISMATCH = 14, /**< Key Exchange Key Mismatch. */
    BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_KEY_REQUEST_TIMEOUT = 15, /**< Key Exchange Key Request Timeout. */
    BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_UNCONSECUTIVE_INDEX = 16, /**< Key Exchange Unconsecutive Index. */
    BCMOLT_ONU_AUTO_SUBGROUP_LOAI = 17, /**< LOAi. */
    BCMOLT_ONU_AUTO_SUBGROUP_LOKI = 18, /**< LOki. */
    BCMOLT_ONU_AUTO_SUBGROUP_LOOCI = 19, /**< LOOCi. */
    BCMOLT_ONU_AUTO_SUBGROUP_MEMI = 20, /**< MEMi. */
    BCMOLT_ONU_AUTO_SUBGROUP_OMCI_PACKET = 21, /**< XGPON OMCI packet. */
    BCMOLT_ONU_AUTO_SUBGROUP_OMCI_PORT_ID_CONFIGURATION_COMPLETED = 22, /**< OMCI PORT ID Configuration Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_ONU_ACTIVATION_COMPLETED = 23, /**< ONU Activation Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_ONU_ACTIVATION_STANDBY_COMPLETED = 24, /**< onu activation standby completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_ONU_DEACTIVATION_COMPLETED = 25, /**< ONU Deactivation Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_ONU_DISABLE_COMPLETED = 26, /**< ONU Disable Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_ONU_ENABLE_COMPLETED = 27, /**< ONU Enable Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_ONU_READY_FOR_DATA_GRANT = 28, /**< ONU is ready to be granted data accesses. */
    BCMOLT_ONU_AUTO_SUBGROUP_ONU_TUNING_IN_COMPLETED = 29, /**< ONU Tuning in completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_ONU_TUNING_OUT_COMPLETED = 30, /**< ONU Tuning out completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_OPTICAL_REFLECTION = 31, /**< Optical Reflection. */
    BCMOLT_ONU_AUTO_SUBGROUP_PASSWORD_AUTHENTICATION_COMPLETED = 32, /**< Password Authentication Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_PEE = 33, /**< PEE. */
    BCMOLT_ONU_AUTO_SUBGROUP_POSSIBLE_DRIFT = 34, /**< Possible Drift. */
    BCMOLT_ONU_AUTO_SUBGROUP_POWER_CONSUMPTION_REPORT = 35, /**< Power consumption report. */
    BCMOLT_ONU_AUTO_SUBGROUP_POWER_LEVEL_REPORT = 36, /**< Power level report. */
    BCMOLT_ONU_AUTO_SUBGROUP_POWER_MANAGEMENT_STATE_CHANGE = 37, /**< Power Management State Change. */
    BCMOLT_ONU_AUTO_SUBGROUP_PQSI = 38, /**< ploam queue status. */
    BCMOLT_ONU_AUTO_SUBGROUP_PST = 39, /**< PST. */
    BCMOLT_ONU_AUTO_SUBGROUP_RANGE_VALUE_CHANGED = 40, /**< Range Value Changed. */
    BCMOLT_ONU_AUTO_SUBGROUP_RANGING_COMPLETED = 41, /**< Ranging Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_REGISTRATION_ID = 42, /**< Registration ID. */
    BCMOLT_ONU_AUTO_SUBGROUP_REI = 43, /**< REI. */
    BCMOLT_ONU_AUTO_SUBGROUP_RSSI_MEASUREMENT_COMPLETED = 44, /**< RSSI Measurement Completed. */
    BCMOLT_ONU_AUTO_SUBGROUP_SDI = 45, /**< Signal Degraded of ONUi. */
    BCMOLT_ONU_AUTO_SUBGROUP_SECURE_MUTUAL_AUTHENTICATION_FAILURE = 46, /**< secure mutual authentication failure. */
    BCMOLT_ONU_AUTO_SUBGROUP_SFI = 47, /**< Signal Fail of ONUi. */
    BCMOLT_ONU_AUTO_SUBGROUP_STATE_CHANGE = 48, /**< State Change. */
    BCMOLT_ONU_AUTO_SUBGROUP_SUFI = 49, /**< SUFi. */
    BCMOLT_ONU_AUTO_SUBGROUP_TIWI = 50, /**< Transmission Interference Warning. */
    BCMOLT_ONU_AUTO_SUBGROUP_TRAP_PLOAM_RECEIVED = 51, /**< trap ploam received. */
    BCMOLT_ONU_AUTO_SUBGROUP_TUNING_RESPONSE = 52, /**< Tuning response. */
    BCMOLT_ONU_AUTO_SUBGROUP_XGPON_ALARM = 53, /**< XGPON ONU Alarm. */
    BCMOLT_ONU_AUTO_SUBGROUP_XPON_UNKNOWN_PLOAM = 54, /**< XPON Unknown ploam. */
    BCMOLT_ONU_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_auto_subgroup__begin BCMOLT_ONU_AUTO_SUBGROUP__BEGIN
#define bcmolt_onu_auto_subgroup_all BCMOLT_ONU_AUTO_SUBGROUP_ALL
#define bcmolt_onu_auto_subgroup_ber_interval_configuration_completed BCMOLT_ONU_AUTO_SUBGROUP_BER_INTERVAL_CONFIGURATION_COMPLETED
#define bcmolt_onu_auto_subgroup_cpu_packet BCMOLT_ONU_AUTO_SUBGROUP_CPU_PACKET
#define bcmolt_onu_auto_subgroup_dfi BCMOLT_ONU_AUTO_SUBGROUP_DFI
#define bcmolt_onu_auto_subgroup_dgi BCMOLT_ONU_AUTO_SUBGROUP_DGI
#define bcmolt_onu_auto_subgroup_dowi BCMOLT_ONU_AUTO_SUBGROUP_DOWI
#define bcmolt_onu_auto_subgroup_err BCMOLT_ONU_AUTO_SUBGROUP_ERR
#define bcmolt_onu_auto_subgroup_gpon_alarm BCMOLT_ONU_AUTO_SUBGROUP_GPON_ALARM
#define bcmolt_onu_auto_subgroup_invalid_dbru_report BCMOLT_ONU_AUTO_SUBGROUP_INVALID_DBRU_REPORT
#define bcmolt_onu_auto_subgroup_itu_pon_stats_alarm_cleared BCMOLT_ONU_AUTO_SUBGROUP_ITU_PON_STATS_ALARM_CLEARED
#define bcmolt_onu_auto_subgroup_itu_pon_stats_alarm_raised BCMOLT_ONU_AUTO_SUBGROUP_ITU_PON_STATS_ALARM_RAISED
#define bcmolt_onu_auto_subgroup_key_exchange_completed BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_COMPLETED
#define bcmolt_onu_auto_subgroup_key_exchange_cycle_skipped BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_CYCLE_SKIPPED
#define bcmolt_onu_auto_subgroup_key_exchange_decrypt_required BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_DECRYPT_REQUIRED
#define bcmolt_onu_auto_subgroup_key_exchange_key_mismatch BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_KEY_MISMATCH
#define bcmolt_onu_auto_subgroup_key_exchange_key_request_timeout BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_KEY_REQUEST_TIMEOUT
#define bcmolt_onu_auto_subgroup_key_exchange_unconsecutive_index BCMOLT_ONU_AUTO_SUBGROUP_KEY_EXCHANGE_UNCONSECUTIVE_INDEX
#define bcmolt_onu_auto_subgroup_loai BCMOLT_ONU_AUTO_SUBGROUP_LOAI
#define bcmolt_onu_auto_subgroup_loki BCMOLT_ONU_AUTO_SUBGROUP_LOKI
#define bcmolt_onu_auto_subgroup_looci BCMOLT_ONU_AUTO_SUBGROUP_LOOCI
#define bcmolt_onu_auto_subgroup_memi BCMOLT_ONU_AUTO_SUBGROUP_MEMI
#define bcmolt_onu_auto_subgroup_omci_packet BCMOLT_ONU_AUTO_SUBGROUP_OMCI_PACKET
#define bcmolt_onu_auto_subgroup_omci_port_id_configuration_completed BCMOLT_ONU_AUTO_SUBGROUP_OMCI_PORT_ID_CONFIGURATION_COMPLETED
#define bcmolt_onu_auto_subgroup_onu_activation_completed BCMOLT_ONU_AUTO_SUBGROUP_ONU_ACTIVATION_COMPLETED
#define bcmolt_onu_auto_subgroup_onu_activation_standby_completed BCMOLT_ONU_AUTO_SUBGROUP_ONU_ACTIVATION_STANDBY_COMPLETED
#define bcmolt_onu_auto_subgroup_onu_deactivation_completed BCMOLT_ONU_AUTO_SUBGROUP_ONU_DEACTIVATION_COMPLETED
#define bcmolt_onu_auto_subgroup_onu_disable_completed BCMOLT_ONU_AUTO_SUBGROUP_ONU_DISABLE_COMPLETED
#define bcmolt_onu_auto_subgroup_onu_enable_completed BCMOLT_ONU_AUTO_SUBGROUP_ONU_ENABLE_COMPLETED
#define bcmolt_onu_auto_subgroup_onu_ready_for_data_grant BCMOLT_ONU_AUTO_SUBGROUP_ONU_READY_FOR_DATA_GRANT
#define bcmolt_onu_auto_subgroup_onu_tuning_in_completed BCMOLT_ONU_AUTO_SUBGROUP_ONU_TUNING_IN_COMPLETED
#define bcmolt_onu_auto_subgroup_onu_tuning_out_completed BCMOLT_ONU_AUTO_SUBGROUP_ONU_TUNING_OUT_COMPLETED
#define bcmolt_onu_auto_subgroup_optical_reflection BCMOLT_ONU_AUTO_SUBGROUP_OPTICAL_REFLECTION
#define bcmolt_onu_auto_subgroup_password_authentication_completed BCMOLT_ONU_AUTO_SUBGROUP_PASSWORD_AUTHENTICATION_COMPLETED
#define bcmolt_onu_auto_subgroup_pee BCMOLT_ONU_AUTO_SUBGROUP_PEE
#define bcmolt_onu_auto_subgroup_possible_drift BCMOLT_ONU_AUTO_SUBGROUP_POSSIBLE_DRIFT
#define bcmolt_onu_auto_subgroup_power_consumption_report BCMOLT_ONU_AUTO_SUBGROUP_POWER_CONSUMPTION_REPORT
#define bcmolt_onu_auto_subgroup_power_level_report BCMOLT_ONU_AUTO_SUBGROUP_POWER_LEVEL_REPORT
#define bcmolt_onu_auto_subgroup_power_management_state_change BCMOLT_ONU_AUTO_SUBGROUP_POWER_MANAGEMENT_STATE_CHANGE
#define bcmolt_onu_auto_subgroup_pqsi BCMOLT_ONU_AUTO_SUBGROUP_PQSI
#define bcmolt_onu_auto_subgroup_pst BCMOLT_ONU_AUTO_SUBGROUP_PST
#define bcmolt_onu_auto_subgroup_range_value_changed BCMOLT_ONU_AUTO_SUBGROUP_RANGE_VALUE_CHANGED
#define bcmolt_onu_auto_subgroup_ranging_completed BCMOLT_ONU_AUTO_SUBGROUP_RANGING_COMPLETED
#define bcmolt_onu_auto_subgroup_registration_id BCMOLT_ONU_AUTO_SUBGROUP_REGISTRATION_ID
#define bcmolt_onu_auto_subgroup_rei BCMOLT_ONU_AUTO_SUBGROUP_REI
#define bcmolt_onu_auto_subgroup_rssi_measurement_completed BCMOLT_ONU_AUTO_SUBGROUP_RSSI_MEASUREMENT_COMPLETED
#define bcmolt_onu_auto_subgroup_sdi BCMOLT_ONU_AUTO_SUBGROUP_SDI
#define bcmolt_onu_auto_subgroup_secure_mutual_authentication_failure BCMOLT_ONU_AUTO_SUBGROUP_SECURE_MUTUAL_AUTHENTICATION_FAILURE
#define bcmolt_onu_auto_subgroup_sfi BCMOLT_ONU_AUTO_SUBGROUP_SFI
#define bcmolt_onu_auto_subgroup_state_change BCMOLT_ONU_AUTO_SUBGROUP_STATE_CHANGE
#define bcmolt_onu_auto_subgroup_sufi BCMOLT_ONU_AUTO_SUBGROUP_SUFI
#define bcmolt_onu_auto_subgroup_tiwi BCMOLT_ONU_AUTO_SUBGROUP_TIWI
#define bcmolt_onu_auto_subgroup_trap_ploam_received BCMOLT_ONU_AUTO_SUBGROUP_TRAP_PLOAM_RECEIVED
#define bcmolt_onu_auto_subgroup_tuning_response BCMOLT_ONU_AUTO_SUBGROUP_TUNING_RESPONSE
#define bcmolt_onu_auto_subgroup_xgpon_alarm BCMOLT_ONU_AUTO_SUBGROUP_XGPON_ALARM
#define bcmolt_onu_auto_subgroup_xpon_unknown_ploam BCMOLT_ONU_AUTO_SUBGROUP_XPON_UNKNOWN_PLOAM
#define bcmolt_onu_auto_subgroup__num_of BCMOLT_ONU_AUTO_SUBGROUP__NUM_OF
#define bcmolt_onu_auto_subgroup_all_properties 0xFFFF
#define bcmolt_onu_auto_subgroup_full_mask 0x7FFFFFFFFFFFFF

} bcmolt_onu_auto_subgroup;

/** List of all onu groups of type oper. */
typedef enum
{
    BCMOLT_ONU_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_ONU_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_ONU_OPER_SUBGROUP_ADJUST_TX_WAVELENGTH = 1, /**< Adjust Tx wavelength. */
    BCMOLT_ONU_OPER_SUBGROUP_CHANGE_POWER_LEVELLING = 2, /**< Change power levelling. */
    BCMOLT_ONU_OPER_SUBGROUP_CPU_PACKETS = 3, /**< XGPON CPU packets. */
    BCMOLT_ONU_OPER_SUBGROUP_FORCE_DEACTIVATION = 4, /**< Force deactivation. */
    BCMOLT_ONU_OPER_SUBGROUP_GET_POWER_CONSUMPTION = 5, /**< Get power consumption. */
    BCMOLT_ONU_OPER_SUBGROUP_GET_POWER_LEVEL = 6, /**< Get power level. */
    BCMOLT_ONU_OPER_SUBGROUP_PLOAM_PACKET = 7, /**< PLOAM Packet. */
    BCMOLT_ONU_OPER_SUBGROUP_REQUEST_REGISTRATION = 8, /**< Request registration. */
    BCMOLT_ONU_OPER_SUBGROUP_RSSI_MEASUREMENT = 9, /**< RSSI Measurement. */
    BCMOLT_ONU_OPER_SUBGROUP_SECURE_MUTUAL_AUTHENTICATION = 10, /**< Secure mutual authentication. */
    BCMOLT_ONU_OPER_SUBGROUP_SET_ONU_STATE = 11, /**< Set ONU State. */
    BCMOLT_ONU_OPER_SUBGROUP_TUNING_IN = 12, /**< ONU Tuning in. */
    BCMOLT_ONU_OPER_SUBGROUP_TUNING_OUT = 13, /**< ONU Tuning out. */
    BCMOLT_ONU_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_oper_subgroup__begin BCMOLT_ONU_OPER_SUBGROUP__BEGIN
#define bcmolt_onu_oper_subgroup_all BCMOLT_ONU_OPER_SUBGROUP_ALL
#define bcmolt_onu_oper_subgroup_adjust_tx_wavelength BCMOLT_ONU_OPER_SUBGROUP_ADJUST_TX_WAVELENGTH
#define bcmolt_onu_oper_subgroup_change_power_levelling BCMOLT_ONU_OPER_SUBGROUP_CHANGE_POWER_LEVELLING
#define bcmolt_onu_oper_subgroup_cpu_packets BCMOLT_ONU_OPER_SUBGROUP_CPU_PACKETS
#define bcmolt_onu_oper_subgroup_force_deactivation BCMOLT_ONU_OPER_SUBGROUP_FORCE_DEACTIVATION
#define bcmolt_onu_oper_subgroup_get_power_consumption BCMOLT_ONU_OPER_SUBGROUP_GET_POWER_CONSUMPTION
#define bcmolt_onu_oper_subgroup_get_power_level BCMOLT_ONU_OPER_SUBGROUP_GET_POWER_LEVEL
#define bcmolt_onu_oper_subgroup_ploam_packet BCMOLT_ONU_OPER_SUBGROUP_PLOAM_PACKET
#define bcmolt_onu_oper_subgroup_request_registration BCMOLT_ONU_OPER_SUBGROUP_REQUEST_REGISTRATION
#define bcmolt_onu_oper_subgroup_rssi_measurement BCMOLT_ONU_OPER_SUBGROUP_RSSI_MEASUREMENT
#define bcmolt_onu_oper_subgroup_secure_mutual_authentication BCMOLT_ONU_OPER_SUBGROUP_SECURE_MUTUAL_AUTHENTICATION
#define bcmolt_onu_oper_subgroup_set_onu_state BCMOLT_ONU_OPER_SUBGROUP_SET_ONU_STATE
#define bcmolt_onu_oper_subgroup_tuning_in BCMOLT_ONU_OPER_SUBGROUP_TUNING_IN
#define bcmolt_onu_oper_subgroup_tuning_out BCMOLT_ONU_OPER_SUBGROUP_TUNING_OUT
#define bcmolt_onu_oper_subgroup__num_of BCMOLT_ONU_OPER_SUBGROUP__NUM_OF
#define bcmolt_onu_oper_subgroup_all_properties 0xFFFF
#define bcmolt_onu_oper_subgroup_full_mask 0x3FFF

} bcmolt_onu_oper_subgroup;

/** List of all pon_interface groups of type stat. */
typedef enum
{
    BCMOLT_PON_INTERFACE_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_PON_INTERFACE_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_PON_INTERFACE_STAT_SUBGROUP_AE_STATS = 1, /**< Active Ethernet Interface Counters. */
    BCMOLT_PON_INTERFACE_STAT_SUBGROUP_ITU_PON_STATS = 2, /**< ITU PON Statistics. */
    BCMOLT_PON_INTERFACE_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_stat_subgroup__begin BCMOLT_PON_INTERFACE_STAT_SUBGROUP__BEGIN
#define bcmolt_pon_interface_stat_subgroup_all BCMOLT_PON_INTERFACE_STAT_SUBGROUP_ALL
#define bcmolt_pon_interface_stat_subgroup_ae_stats BCMOLT_PON_INTERFACE_STAT_SUBGROUP_AE_STATS
#define bcmolt_pon_interface_stat_subgroup_itu_pon_stats BCMOLT_PON_INTERFACE_STAT_SUBGROUP_ITU_PON_STATS
#define bcmolt_pon_interface_stat_subgroup__num_of BCMOLT_PON_INTERFACE_STAT_SUBGROUP__NUM_OF
#define bcmolt_pon_interface_stat_subgroup_all_properties 0xFFFF
#define bcmolt_pon_interface_stat_subgroup_full_mask 0x7

} bcmolt_pon_interface_stat_subgroup;

/** List of all pon_interface groups of type stat_cfg. */
typedef enum
{
    BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP_AE_STATS_CFG = 1, /**< Active Ethernet Interface Counters Configuration. */
    BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP_ITU_PON_STATS_CFG = 2, /**< ITU PON Statistics Configuration. */
    BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_stat_cfg_subgroup__begin BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_pon_interface_stat_cfg_subgroup_all BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP_ALL
#define bcmolt_pon_interface_stat_cfg_subgroup_ae_stats_cfg BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP_AE_STATS_CFG
#define bcmolt_pon_interface_stat_cfg_subgroup_itu_pon_stats_cfg BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP_ITU_PON_STATS_CFG
#define bcmolt_pon_interface_stat_cfg_subgroup__num_of BCMOLT_PON_INTERFACE_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_pon_interface_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_pon_interface_stat_cfg_subgroup_full_mask 0x7

} bcmolt_pon_interface_stat_cfg_subgroup;

/** List of all pon_interface groups of type auto. */
typedef enum
{
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ACTIVATE_ALL_ONUS_COMPLETED = 1, /**< activate all onus completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_AE_STATS_ALARM_CLEARED = 2, /**< Active Ethernet Interface Counters Alarm Cleared. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_AE_STATS_ALARM_RAISED = 3, /**< Active Ethernet Interface Counters Alarm Raised. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_CPU_PACKETS_FAILURE = 4, /**< CPU Packets Failure. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_DEACTIVATE_ALL_ONUS_COMPLETED = 5, /**< deactivate all onus completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_DISABLE_ALL_ONUS_COMPLETED = 6, /**< disable all onus completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ENABLE_ALL_ONUS_COMPLETED = 7, /**< enable all onus completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_IEEE_ROGUE_DETECTION_COMPLETED = 8, /**< IEEE Rogue Detection Completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ITU_PON_STATS_ALARM_CLEARED = 9, /**< ITU PON Statistics Alarm Cleared. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ITU_PON_STATS_ALARM_RAISED = 10, /**< ITU PON Statistics Alarm Raised. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_LOS = 11, /**< LOS. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_MPCP_TIMESTAMP_CHANGED = 12, /**< MPCP Timestamp Changed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ONU_DISCOVERED = 13, /**< ONU Discovered. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ONU_UPGRADE_COMPLETE = 14, /**< ONU Upgrade Complete. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCHING_ONUS_RANGED = 15, /**< Protection Switching ONUs Ranged. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCHING_RERANGE_FAILURE = 16, /**< Protection Switching Re-range failure  (IEEE). */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED = 17, /**< Protection Switching Switchover Completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCHING_TRAFFIC_RESUME = 18, /**< Protection Switching Traffic Resume. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ROGUE_DETECTION_TOOL_DONE = 19, /**< rogue detection tool done. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_SERIAL_NUMBER_ACQUISITION_CYCLE_START = 20, /**< Serial Number Acquisition Cycle Start. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_STANDBY_PON_MONITORING_CYCLE_COMPLETED = 21, /**< Standby PON Monitoring Cycle Completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_STATE_CHANGE_COMPLETED = 22, /**< State Change Completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_SWITCH_PON_TYPE_COMPLETED = 23, /**< Switch PON type completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_TOD_REQUEST_COMPLETED = 24, /**< TOD request completed. */
    BCMOLT_PON_INTERFACE_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_auto_subgroup__begin BCMOLT_PON_INTERFACE_AUTO_SUBGROUP__BEGIN
#define bcmolt_pon_interface_auto_subgroup_all BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ALL
#define bcmolt_pon_interface_auto_subgroup_activate_all_onus_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ACTIVATE_ALL_ONUS_COMPLETED
#define bcmolt_pon_interface_auto_subgroup_ae_stats_alarm_cleared BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_AE_STATS_ALARM_CLEARED
#define bcmolt_pon_interface_auto_subgroup_ae_stats_alarm_raised BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_AE_STATS_ALARM_RAISED
#define bcmolt_pon_interface_auto_subgroup_cpu_packets_failure BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_CPU_PACKETS_FAILURE
#define bcmolt_pon_interface_auto_subgroup_deactivate_all_onus_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_DEACTIVATE_ALL_ONUS_COMPLETED
#define bcmolt_pon_interface_auto_subgroup_disable_all_onus_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_DISABLE_ALL_ONUS_COMPLETED
#define bcmolt_pon_interface_auto_subgroup_enable_all_onus_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ENABLE_ALL_ONUS_COMPLETED
#define bcmolt_pon_interface_auto_subgroup_ieee_rogue_detection_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_IEEE_ROGUE_DETECTION_COMPLETED
#define bcmolt_pon_interface_auto_subgroup_itu_pon_stats_alarm_cleared BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ITU_PON_STATS_ALARM_CLEARED
#define bcmolt_pon_interface_auto_subgroup_itu_pon_stats_alarm_raised BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ITU_PON_STATS_ALARM_RAISED
#define bcmolt_pon_interface_auto_subgroup_los BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_LOS
#define bcmolt_pon_interface_auto_subgroup_mpcp_timestamp_changed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_MPCP_TIMESTAMP_CHANGED
#define bcmolt_pon_interface_auto_subgroup_onu_discovered BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ONU_DISCOVERED
#define bcmolt_pon_interface_auto_subgroup_onu_upgrade_complete BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ONU_UPGRADE_COMPLETE
#define bcmolt_pon_interface_auto_subgroup_protection_switching_onus_ranged BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCHING_ONUS_RANGED
#define bcmolt_pon_interface_auto_subgroup_protection_switching_rerange_failure BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCHING_RERANGE_FAILURE
#define bcmolt_pon_interface_auto_subgroup_protection_switching_switchover_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED
#define bcmolt_pon_interface_auto_subgroup_protection_switching_traffic_resume BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCHING_TRAFFIC_RESUME
#define bcmolt_pon_interface_auto_subgroup_rogue_detection_tool_done BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_ROGUE_DETECTION_TOOL_DONE
#define bcmolt_pon_interface_auto_subgroup_serial_number_acquisition_cycle_start BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_SERIAL_NUMBER_ACQUISITION_CYCLE_START
#define bcmolt_pon_interface_auto_subgroup_standby_pon_monitoring_cycle_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_STANDBY_PON_MONITORING_CYCLE_COMPLETED
#define bcmolt_pon_interface_auto_subgroup_state_change_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_STATE_CHANGE_COMPLETED
#define bcmolt_pon_interface_auto_subgroup_switch_pon_type_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_SWITCH_PON_TYPE_COMPLETED
#define bcmolt_pon_interface_auto_subgroup_tod_request_completed BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_TOD_REQUEST_COMPLETED
#define bcmolt_pon_interface_auto_subgroup__num_of BCMOLT_PON_INTERFACE_AUTO_SUBGROUP__NUM_OF
#define bcmolt_pon_interface_auto_subgroup_all_properties 0xFFFF
#define bcmolt_pon_interface_auto_subgroup_full_mask 0x1FFFFFF

} bcmolt_pon_interface_auto_subgroup;

/** List of all pon_interface groups of type oper. */
typedef enum
{
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_ABORT_ONU_UPGRADE = 1, /**< Abort ONU Firmware Upgrade. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_BROADCAST_PLOAM_PACKET = 2, /**< Broadcast PLOAM Packet. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_CPU_PACKETS = 3, /**< XGPON CPU packets. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_DISABLE_SERIAL_NUMBER = 4, /**< Disable Serial Number. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_ONU_UPGRADE_ACTIVATE_COMMIT = 5, /**< ONU Upgrade Activate Commit. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA = 6, /**< Protection switching apply re-range delta (IEEE). */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE = 7, /**< protection switching type c set multiple onu state. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_RESET = 8, /**< Reset. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_ROGUE_DETECTION_TOOL = 9, /**< rogue detection tool. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_RUN_SPECIAL_BW_MAP = 10, /**< Run Special BW Map. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_SET_ONU_STATE = 11, /**< Set ONU State. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_SET_PON_INTERFACE_STATE = 12, /**< Set PON Interface State. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_SINGLE_REQUEST_STANDBY_PON_MONITORING = 13, /**< Single request standby PON Monitoring. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_START_ONU_UPGRADE = 14, /**< Start ONU Firmware Upgrade. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_SWITCH_PON_TYPE = 15, /**< Switch PON type. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP_TOD_REQUEST = 16, /**< TOD request. */
    BCMOLT_PON_INTERFACE_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_oper_subgroup__begin BCMOLT_PON_INTERFACE_OPER_SUBGROUP__BEGIN
#define bcmolt_pon_interface_oper_subgroup_all BCMOLT_PON_INTERFACE_OPER_SUBGROUP_ALL
#define bcmolt_pon_interface_oper_subgroup_abort_onu_upgrade BCMOLT_PON_INTERFACE_OPER_SUBGROUP_ABORT_ONU_UPGRADE
#define bcmolt_pon_interface_oper_subgroup_broadcast_ploam_packet BCMOLT_PON_INTERFACE_OPER_SUBGROUP_BROADCAST_PLOAM_PACKET
#define bcmolt_pon_interface_oper_subgroup_cpu_packets BCMOLT_PON_INTERFACE_OPER_SUBGROUP_CPU_PACKETS
#define bcmolt_pon_interface_oper_subgroup_disable_serial_number BCMOLT_PON_INTERFACE_OPER_SUBGROUP_DISABLE_SERIAL_NUMBER
#define bcmolt_pon_interface_oper_subgroup_onu_upgrade_activate_commit BCMOLT_PON_INTERFACE_OPER_SUBGROUP_ONU_UPGRADE_ACTIVATE_COMMIT
#define bcmolt_pon_interface_oper_subgroup_protection_switching_apply_rerange_delta BCMOLT_PON_INTERFACE_OPER_SUBGROUP_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA
#define bcmolt_pon_interface_oper_subgroup_protection_switching_type_c_set_multiple_onu_state BCMOLT_PON_INTERFACE_OPER_SUBGROUP_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE
#define bcmolt_pon_interface_oper_subgroup_reset BCMOLT_PON_INTERFACE_OPER_SUBGROUP_RESET
#define bcmolt_pon_interface_oper_subgroup_rogue_detection_tool BCMOLT_PON_INTERFACE_OPER_SUBGROUP_ROGUE_DETECTION_TOOL
#define bcmolt_pon_interface_oper_subgroup_run_special_bw_map BCMOLT_PON_INTERFACE_OPER_SUBGROUP_RUN_SPECIAL_BW_MAP
#define bcmolt_pon_interface_oper_subgroup_set_onu_state BCMOLT_PON_INTERFACE_OPER_SUBGROUP_SET_ONU_STATE
#define bcmolt_pon_interface_oper_subgroup_set_pon_interface_state BCMOLT_PON_INTERFACE_OPER_SUBGROUP_SET_PON_INTERFACE_STATE
#define bcmolt_pon_interface_oper_subgroup_single_request_standby_pon_monitoring BCMOLT_PON_INTERFACE_OPER_SUBGROUP_SINGLE_REQUEST_STANDBY_PON_MONITORING
#define bcmolt_pon_interface_oper_subgroup_start_onu_upgrade BCMOLT_PON_INTERFACE_OPER_SUBGROUP_START_ONU_UPGRADE
#define bcmolt_pon_interface_oper_subgroup_switch_pon_type BCMOLT_PON_INTERFACE_OPER_SUBGROUP_SWITCH_PON_TYPE
#define bcmolt_pon_interface_oper_subgroup_tod_request BCMOLT_PON_INTERFACE_OPER_SUBGROUP_TOD_REQUEST
#define bcmolt_pon_interface_oper_subgroup__num_of BCMOLT_PON_INTERFACE_OPER_SUBGROUP__NUM_OF
#define bcmolt_pon_interface_oper_subgroup_all_properties 0xFFFF
#define bcmolt_pon_interface_oper_subgroup_full_mask 0x1FFFF

} bcmolt_pon_interface_oper_subgroup;

/** List of all protection_interface groups of type auto. */
typedef enum
{
    BCMOLT_PROTECTION_INTERFACE_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_PROTECTION_INTERFACE_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_PROTECTION_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCH_COMPLETED = 1, /**< Protection Switch Completed. */
    BCMOLT_PROTECTION_INTERFACE_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_protection_interface_auto_subgroup__begin BCMOLT_PROTECTION_INTERFACE_AUTO_SUBGROUP__BEGIN
#define bcmolt_protection_interface_auto_subgroup_all BCMOLT_PROTECTION_INTERFACE_AUTO_SUBGROUP_ALL
#define bcmolt_protection_interface_auto_subgroup_protection_switch_completed BCMOLT_PROTECTION_INTERFACE_AUTO_SUBGROUP_PROTECTION_SWITCH_COMPLETED
#define bcmolt_protection_interface_auto_subgroup__num_of BCMOLT_PROTECTION_INTERFACE_AUTO_SUBGROUP__NUM_OF
#define bcmolt_protection_interface_auto_subgroup_all_properties 0xFFFF
#define bcmolt_protection_interface_auto_subgroup_full_mask 0x3

} bcmolt_protection_interface_auto_subgroup;

/** List of all protection_interface groups of type oper. */
typedef enum
{
    BCMOLT_PROTECTION_INTERFACE_OPER_SUBGROUP__BEGIN = 0,
    BCMOLT_PROTECTION_INTERFACE_OPER_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_PROTECTION_INTERFACE_OPER_SUBGROUP_PROTECTION_SWITCH = 1, /**< Protection Switch. */
    BCMOLT_PROTECTION_INTERFACE_OPER_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_protection_interface_oper_subgroup__begin BCMOLT_PROTECTION_INTERFACE_OPER_SUBGROUP__BEGIN
#define bcmolt_protection_interface_oper_subgroup_all BCMOLT_PROTECTION_INTERFACE_OPER_SUBGROUP_ALL
#define bcmolt_protection_interface_oper_subgroup_protection_switch BCMOLT_PROTECTION_INTERFACE_OPER_SUBGROUP_PROTECTION_SWITCH
#define bcmolt_protection_interface_oper_subgroup__num_of BCMOLT_PROTECTION_INTERFACE_OPER_SUBGROUP__NUM_OF
#define bcmolt_protection_interface_oper_subgroup_all_properties 0xFFFF
#define bcmolt_protection_interface_oper_subgroup_full_mask 0x3

} bcmolt_protection_interface_oper_subgroup;

/** List of all switch_inni groups of type stat. */
typedef enum
{
    BCMOLT_SWITCH_INNI_STAT_SUBGROUP__BEGIN = 0,
    BCMOLT_SWITCH_INNI_STAT_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_SWITCH_INNI_STAT_SUBGROUP_STATS = 1, /**< Switch INNI Interface Statistics. */
    BCMOLT_SWITCH_INNI_STAT_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_stat_subgroup__begin BCMOLT_SWITCH_INNI_STAT_SUBGROUP__BEGIN
#define bcmolt_switch_inni_stat_subgroup_all BCMOLT_SWITCH_INNI_STAT_SUBGROUP_ALL
#define bcmolt_switch_inni_stat_subgroup_stats BCMOLT_SWITCH_INNI_STAT_SUBGROUP_STATS
#define bcmolt_switch_inni_stat_subgroup__num_of BCMOLT_SWITCH_INNI_STAT_SUBGROUP__NUM_OF
#define bcmolt_switch_inni_stat_subgroup_all_properties 0xFFFF
#define bcmolt_switch_inni_stat_subgroup_full_mask 0x3

} bcmolt_switch_inni_stat_subgroup;

/** List of all switch_inni groups of type stat_cfg. */
typedef enum
{
    BCMOLT_SWITCH_INNI_STAT_CFG_SUBGROUP__BEGIN = 0,
    BCMOLT_SWITCH_INNI_STAT_CFG_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_SWITCH_INNI_STAT_CFG_SUBGROUP_STATS_CFG = 1, /**< Switch INNI Interface Statistics Configuration. */
    BCMOLT_SWITCH_INNI_STAT_CFG_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_stat_cfg_subgroup__begin BCMOLT_SWITCH_INNI_STAT_CFG_SUBGROUP__BEGIN
#define bcmolt_switch_inni_stat_cfg_subgroup_all BCMOLT_SWITCH_INNI_STAT_CFG_SUBGROUP_ALL
#define bcmolt_switch_inni_stat_cfg_subgroup_stats_cfg BCMOLT_SWITCH_INNI_STAT_CFG_SUBGROUP_STATS_CFG
#define bcmolt_switch_inni_stat_cfg_subgroup__num_of BCMOLT_SWITCH_INNI_STAT_CFG_SUBGROUP__NUM_OF
#define bcmolt_switch_inni_stat_cfg_subgroup_all_properties 0xFFFF
#define bcmolt_switch_inni_stat_cfg_subgroup_full_mask 0x3

} bcmolt_switch_inni_stat_cfg_subgroup;

/** List of all switch_inni groups of type auto. */
typedef enum
{
    BCMOLT_SWITCH_INNI_AUTO_SUBGROUP__BEGIN = 0,
    BCMOLT_SWITCH_INNI_AUTO_SUBGROUP_ALL = 0, /**< Subscribe to all subgroups (reserved value). */
    BCMOLT_SWITCH_INNI_AUTO_SUBGROUP_STATS_ALARM_CLEARED = 1, /**< Switch INNI Interface Statistics Alarm Cleared. */
    BCMOLT_SWITCH_INNI_AUTO_SUBGROUP_STATS_ALARM_RAISED = 2, /**< Switch INNI Interface Statistics Alarm Raised. */
    BCMOLT_SWITCH_INNI_AUTO_SUBGROUP__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_auto_subgroup__begin BCMOLT_SWITCH_INNI_AUTO_SUBGROUP__BEGIN
#define bcmolt_switch_inni_auto_subgroup_all BCMOLT_SWITCH_INNI_AUTO_SUBGROUP_ALL
#define bcmolt_switch_inni_auto_subgroup_stats_alarm_cleared BCMOLT_SWITCH_INNI_AUTO_SUBGROUP_STATS_ALARM_CLEARED
#define bcmolt_switch_inni_auto_subgroup_stats_alarm_raised BCMOLT_SWITCH_INNI_AUTO_SUBGROUP_STATS_ALARM_RAISED
#define bcmolt_switch_inni_auto_subgroup__num_of BCMOLT_SWITCH_INNI_AUTO_SUBGROUP__NUM_OF
#define bcmolt_switch_inni_auto_subgroup_all_properties 0xFFFF
#define bcmolt_switch_inni_auto_subgroup_full_mask 0x7

} bcmolt_switch_inni_auto_subgroup;

/** Identifiers for all fields in a 'access_control_fwd_action'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID_ACTION = 0, /**< action. */
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID_REDIRECT_INTF_REF = 1, /**< redirect interface. */
    BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_fwd_action_id__begin BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID__BEGIN
#define bcmolt_access_control_fwd_action_id_action BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID_ACTION
#define bcmolt_access_control_fwd_action_id_redirect_intf_ref BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID_REDIRECT_INTF_REF
#define bcmolt_access_control_fwd_action_id__num_of BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID__NUM_OF
#define bcmolt_access_control_fwd_action_id_all_properties 0xFF
#define bcmolt_access_control_fwd_action_id_full_mask 0x3

} bcmolt_access_control_fwd_action_id;

/** Identifiers for all fields in a 'access_control_pkt_modifier'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_PKT_MODIFIER_BIT_MASK = 0, /**< Packet modifer Bit mask. */
    BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_O_VID = 1, /**< Push Outer VID or Modify Outer VID. */
    BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_I_VID = 2, /**< Modify Inner Vlan Id. */
    BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_O_PBITS = 3, /**< Remark Outer PBits. */
    BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_I_PBITS = 4, /**< Remark Inner PBits. */
    BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_DSCP = 5, /**< Remark DSCP value. */
    BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_TTL = 6, /**< Rewrite TTL value. */
    BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_pkt_modifier_id__begin BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID__BEGIN
#define bcmolt_access_control_pkt_modifier_id_pkt_modifier_bit_mask BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_PKT_MODIFIER_BIT_MASK
#define bcmolt_access_control_pkt_modifier_id_o_vid BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_O_VID
#define bcmolt_access_control_pkt_modifier_id_i_vid BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_I_VID
#define bcmolt_access_control_pkt_modifier_id_o_pbits BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_O_PBITS
#define bcmolt_access_control_pkt_modifier_id_i_pbits BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_I_PBITS
#define bcmolt_access_control_pkt_modifier_id_dscp BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_DSCP
#define bcmolt_access_control_pkt_modifier_id_ttl BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_TTL
#define bcmolt_access_control_pkt_modifier_id__num_of BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID__NUM_OF
#define bcmolt_access_control_pkt_modifier_id_all_properties 0xFF
#define bcmolt_access_control_pkt_modifier_id_full_mask 0x7F

} bcmolt_access_control_pkt_modifier_id;

/** Identifiers for all fields in a 'action'. */
typedef enum
{
    BCMOLT_ACTION_ID__BEGIN = 0,
    BCMOLT_ACTION_ID_CMDS_BITMASK = 0, /**< Commands bitmask. */
    BCMOLT_ACTION_ID_O_VID = 1, /**< Outer vid. */
    BCMOLT_ACTION_ID_O_PBITS = 2, /**< Outer pbits. */
    BCMOLT_ACTION_ID_I_VID = 3, /**< Inner vid. */
    BCMOLT_ACTION_ID_I_PBITS = 4, /**< Inner pbits. */
    BCMOLT_ACTION_ID_TAG_FORMAT = 5, /**< vlan tags format. */
    BCMOLT_ACTION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_action_id__begin BCMOLT_ACTION_ID__BEGIN
#define bcmolt_action_id_cmds_bitmask BCMOLT_ACTION_ID_CMDS_BITMASK
#define bcmolt_action_id_o_vid BCMOLT_ACTION_ID_O_VID
#define bcmolt_action_id_o_pbits BCMOLT_ACTION_ID_O_PBITS
#define bcmolt_action_id_i_vid BCMOLT_ACTION_ID_I_VID
#define bcmolt_action_id_i_pbits BCMOLT_ACTION_ID_I_PBITS
#define bcmolt_action_id_tag_format BCMOLT_ACTION_ID_TAG_FORMAT
#define bcmolt_action_id__num_of BCMOLT_ACTION_ID__NUM_OF
#define bcmolt_action_id_all_properties 0xFF
#define bcmolt_action_id_full_mask 0x3F

} bcmolt_action_id;

/** Identifiers for all fields in a 'aes_key'. */
typedef enum
{
    BCMOLT_AES_KEY_ID__BEGIN = 0,
    BCMOLT_AES_KEY_ID_BYTES = 0, /**< Bytes. */
    BCMOLT_AES_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_aes_key_id__begin BCMOLT_AES_KEY_ID__BEGIN
#define bcmolt_aes_key_id_bytes BCMOLT_AES_KEY_ID_BYTES
#define bcmolt_aes_key_id__num_of BCMOLT_AES_KEY_ID__NUM_OF
#define bcmolt_aes_key_id_all_properties 0xFF
#define bcmolt_aes_key_id_full_mask 0x1

} bcmolt_aes_key_id;

/** Identifiers for all fields in a 'automatic_onu_deactivation'. */
typedef enum
{
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID__BEGIN = 0,
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_LOS = 0, /**< LOS. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_ONU_ALARMS = 1, /**< ONU alarms. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_TIWI = 2, /**< Tiwi. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_ACK_TIMEOUT = 3, /**< ACK timeout. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_SFI = 4, /**< SFi. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_LOKI = 5, /**< Loki. */
    BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_automatic_onu_deactivation_id__begin BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID__BEGIN
#define bcmolt_automatic_onu_deactivation_id_los BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_LOS
#define bcmolt_automatic_onu_deactivation_id_onu_alarms BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_ONU_ALARMS
#define bcmolt_automatic_onu_deactivation_id_tiwi BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_TIWI
#define bcmolt_automatic_onu_deactivation_id_ack_timeout BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_ACK_TIMEOUT
#define bcmolt_automatic_onu_deactivation_id_sfi BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_SFI
#define bcmolt_automatic_onu_deactivation_id_loki BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_LOKI
#define bcmolt_automatic_onu_deactivation_id__num_of BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID__NUM_OF
#define bcmolt_automatic_onu_deactivation_id_all_properties 0xFF
#define bcmolt_automatic_onu_deactivation_id_full_mask 0x3F

} bcmolt_automatic_onu_deactivation_id;

/** Identifiers for all fields in a 'ber_monitor_params'. */
typedef enum
{
    BCMOLT_BER_MONITOR_PARAMS_ID__BEGIN = 0,
    BCMOLT_BER_MONITOR_PARAMS_ID_US_BER_INTERVAL = 0, /**< US BER interval in ms. */
    BCMOLT_BER_MONITOR_PARAMS_ID_SF_THRESHOLD = 1, /**< SF threshold. */
    BCMOLT_BER_MONITOR_PARAMS_ID_SD_THRESHOLD = 2, /**< SD threshold. */
    BCMOLT_BER_MONITOR_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ber_monitor_params_id__begin BCMOLT_BER_MONITOR_PARAMS_ID__BEGIN
#define bcmolt_ber_monitor_params_id_us_ber_interval BCMOLT_BER_MONITOR_PARAMS_ID_US_BER_INTERVAL
#define bcmolt_ber_monitor_params_id_sf_threshold BCMOLT_BER_MONITOR_PARAMS_ID_SF_THRESHOLD
#define bcmolt_ber_monitor_params_id_sd_threshold BCMOLT_BER_MONITOR_PARAMS_ID_SD_THRESHOLD
#define bcmolt_ber_monitor_params_id__num_of BCMOLT_BER_MONITOR_PARAMS_ID__NUM_OF
#define bcmolt_ber_monitor_params_id_all_properties 0xFF
#define bcmolt_ber_monitor_params_id_full_mask 0x7

} bcmolt_ber_monitor_params_id;

/** Identifiers for all fields in a 'cbr_rt_allocation_profile'. */
typedef enum
{
    BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID__BEGIN = 0,
    BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID_MA_7 = 0, /**< MA_7. */
    BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID_MA_3 = 1, /**< MA_3. */
    BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID_MA_1 = 2, /**< MA_1. */
    BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_cbr_rt_allocation_profile_id__begin BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID__BEGIN
#define bcmolt_cbr_rt_allocation_profile_id_ma_7 BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID_MA_7
#define bcmolt_cbr_rt_allocation_profile_id_ma_3 BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID_MA_3
#define bcmolt_cbr_rt_allocation_profile_id_ma_1 BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID_MA_1
#define bcmolt_cbr_rt_allocation_profile_id__num_of BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID__NUM_OF
#define bcmolt_cbr_rt_allocation_profile_id_all_properties 0xFF
#define bcmolt_cbr_rt_allocation_profile_id_full_mask 0x7

} bcmolt_cbr_rt_allocation_profile_id;

/** Identifiers for all fields in a 'channel_profile'. */
typedef enum
{
    BCMOLT_CHANNEL_PROFILE_ID__BEGIN = 0,
    BCMOLT_CHANNEL_PROFILE_ID_VERSION = 0, /**< Channel profile version. */
    BCMOLT_CHANNEL_PROFILE_ID_CHANNEL_INDEX = 1, /**< Channel profile index. */
    BCMOLT_CHANNEL_PROFILE_ID_DS_FREQUENCY_OFFSET = 2, /**< DS frequency offset. */
    BCMOLT_CHANNEL_PROFILE_ID_CHANNEL_PARTITION = 3, /**< Channel partition. */
    BCMOLT_CHANNEL_PROFILE_ID_UWLCH_ID = 4, /**< UWLCH ID. */
    BCMOLT_CHANNEL_PROFILE_ID_US_FREQUENCY = 5, /**< US frequency. */
    BCMOLT_CHANNEL_PROFILE_ID_US_RATE = 6, /**< US rate. */
    BCMOLT_CHANNEL_PROFILE_ID_DEFAULT_ONU_ATTENUATION = 7, /**< default ONU attenuation. */
    BCMOLT_CHANNEL_PROFILE_ID_RESPONSE_THRESHOLD = 8, /**< Response threshold. */
    BCMOLT_CHANNEL_PROFILE_ID_US_LINK_TYPE = 9, /**< US link type. */
    BCMOLT_CHANNEL_PROFILE_ID_IS_VALID = 10, /**< is valid. */
    BCMOLT_CHANNEL_PROFILE_ID_PON_ID = 11, /**< pon_id. */
    BCMOLT_CHANNEL_PROFILE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_channel_profile_id__begin BCMOLT_CHANNEL_PROFILE_ID__BEGIN
#define bcmolt_channel_profile_id_version BCMOLT_CHANNEL_PROFILE_ID_VERSION
#define bcmolt_channel_profile_id_channel_index BCMOLT_CHANNEL_PROFILE_ID_CHANNEL_INDEX
#define bcmolt_channel_profile_id_ds_frequency_offset BCMOLT_CHANNEL_PROFILE_ID_DS_FREQUENCY_OFFSET
#define bcmolt_channel_profile_id_channel_partition BCMOLT_CHANNEL_PROFILE_ID_CHANNEL_PARTITION
#define bcmolt_channel_profile_id_uwlch_id BCMOLT_CHANNEL_PROFILE_ID_UWLCH_ID
#define bcmolt_channel_profile_id_us_frequency BCMOLT_CHANNEL_PROFILE_ID_US_FREQUENCY
#define bcmolt_channel_profile_id_us_rate BCMOLT_CHANNEL_PROFILE_ID_US_RATE
#define bcmolt_channel_profile_id_default_onu_attenuation BCMOLT_CHANNEL_PROFILE_ID_DEFAULT_ONU_ATTENUATION
#define bcmolt_channel_profile_id_response_threshold BCMOLT_CHANNEL_PROFILE_ID_RESPONSE_THRESHOLD
#define bcmolt_channel_profile_id_us_link_type BCMOLT_CHANNEL_PROFILE_ID_US_LINK_TYPE
#define bcmolt_channel_profile_id_is_valid BCMOLT_CHANNEL_PROFILE_ID_IS_VALID
#define bcmolt_channel_profile_id_pon_id BCMOLT_CHANNEL_PROFILE_ID_PON_ID
#define bcmolt_channel_profile_id__num_of BCMOLT_CHANNEL_PROFILE_ID__NUM_OF
#define bcmolt_channel_profile_id_all_properties 0xFF
#define bcmolt_channel_profile_id_full_mask 0xFFF

} bcmolt_channel_profile_id;

/** Identifiers for all fields in a 'classifier'. */
typedef enum
{
    BCMOLT_CLASSIFIER_ID__BEGIN = 0,
    BCMOLT_CLASSIFIER_ID_CLASSIFIER_BITMAP = 0, /**< Classifier Bitmap. */
    BCMOLT_CLASSIFIER_ID_O_VID = 1, /**< Outer vid. */
    BCMOLT_CLASSIFIER_ID_I_VID = 2, /**< Inner vid. */
    BCMOLT_CLASSIFIER_ID_O_PBITS = 3, /**< Outer Pbits. */
    BCMOLT_CLASSIFIER_ID_I_PBITS = 4, /**< Inner Pbits. */
    BCMOLT_CLASSIFIER_ID_ETHER_TYPE = 5, /**< Ether type. */
    BCMOLT_CLASSIFIER_ID_DST_MAC = 6, /**< Destination mac. */
    BCMOLT_CLASSIFIER_ID_SRC_MAC = 7, /**< Source mac. */
    BCMOLT_CLASSIFIER_ID_IP_PROTO = 8, /**< IP Protocol. */
    BCMOLT_CLASSIFIER_ID_DST_IP = 9, /**< Destination IP address. */
    BCMOLT_CLASSIFIER_ID_DST_IP_MASK = 10, /**< Destination IP address mask. */
    BCMOLT_CLASSIFIER_ID_DST_PORT = 11, /**< Destination port. */
    BCMOLT_CLASSIFIER_ID_DST_PORT_RANGE = 12, /**< Destination port range. */
    BCMOLT_CLASSIFIER_ID_SRC_IP = 13, /**< Source IP address. */
    BCMOLT_CLASSIFIER_ID_SRC_IP_MASK = 14, /**< Source IP address mask. */
    BCMOLT_CLASSIFIER_ID_SRC_PORT = 15, /**< Source port. */
    BCMOLT_CLASSIFIER_ID_SRC_PORT_RANGE = 16, /**< Source port range. */
    BCMOLT_CLASSIFIER_ID_PKT_TAG_TYPE = 17, /**< Packet tag type. */
    BCMOLT_CLASSIFIER_ID_IP_V_6 = 18, /**< IPv6 related classifier. */
    BCMOLT_CLASSIFIER_ID_I2_VID = 19, /**< Second Inner vid. */
    BCMOLT_CLASSIFIER_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_classifier_id__begin BCMOLT_CLASSIFIER_ID__BEGIN
#define bcmolt_classifier_id_classifier_bitmap BCMOLT_CLASSIFIER_ID_CLASSIFIER_BITMAP
#define bcmolt_classifier_id_o_vid BCMOLT_CLASSIFIER_ID_O_VID
#define bcmolt_classifier_id_i_vid BCMOLT_CLASSIFIER_ID_I_VID
#define bcmolt_classifier_id_o_pbits BCMOLT_CLASSIFIER_ID_O_PBITS
#define bcmolt_classifier_id_i_pbits BCMOLT_CLASSIFIER_ID_I_PBITS
#define bcmolt_classifier_id_ether_type BCMOLT_CLASSIFIER_ID_ETHER_TYPE
#define bcmolt_classifier_id_dst_mac BCMOLT_CLASSIFIER_ID_DST_MAC
#define bcmolt_classifier_id_src_mac BCMOLT_CLASSIFIER_ID_SRC_MAC
#define bcmolt_classifier_id_ip_proto BCMOLT_CLASSIFIER_ID_IP_PROTO
#define bcmolt_classifier_id_dst_ip BCMOLT_CLASSIFIER_ID_DST_IP
#define bcmolt_classifier_id_dst_ip_mask BCMOLT_CLASSIFIER_ID_DST_IP_MASK
#define bcmolt_classifier_id_dst_port BCMOLT_CLASSIFIER_ID_DST_PORT
#define bcmolt_classifier_id_dst_port_range BCMOLT_CLASSIFIER_ID_DST_PORT_RANGE
#define bcmolt_classifier_id_src_ip BCMOLT_CLASSIFIER_ID_SRC_IP
#define bcmolt_classifier_id_src_ip_mask BCMOLT_CLASSIFIER_ID_SRC_IP_MASK
#define bcmolt_classifier_id_src_port BCMOLT_CLASSIFIER_ID_SRC_PORT
#define bcmolt_classifier_id_src_port_range BCMOLT_CLASSIFIER_ID_SRC_PORT_RANGE
#define bcmolt_classifier_id_pkt_tag_type BCMOLT_CLASSIFIER_ID_PKT_TAG_TYPE
#define bcmolt_classifier_id_ip_v_6 BCMOLT_CLASSIFIER_ID_IP_V_6
#define bcmolt_classifier_id_i2_vid BCMOLT_CLASSIFIER_ID_I2_VID
#define bcmolt_classifier_id__num_of BCMOLT_CLASSIFIER_ID__NUM_OF
#define bcmolt_classifier_id_all_properties 0xFF
#define bcmolt_classifier_id_full_mask 0xFFFFF

} bcmolt_classifier_id;

/** Identifiers for all fields in a 'classifier_ip_v_6'. */
typedef enum
{
    BCMOLT_CLASSIFIER_IP_V_6_ID__BEGIN = 0,
    BCMOLT_CLASSIFIER_IP_V_6_ID_CLASSIFIER_IP_V_6_BITMAP = 0, /**< classifier bitmap for ipv6. */
    BCMOLT_CLASSIFIER_IP_V_6_ID_MATCH_MLD_PKTS = 1, /**< match MLD packets. */
    BCMOLT_CLASSIFIER_IP_V_6_ID_DST_IP_V_6 = 2, /**< Destination IPv6 address. */
    BCMOLT_CLASSIFIER_IP_V_6_ID_DST_IP_V_6_MASK = 3, /**< Destination IPv6 address mask. */
    BCMOLT_CLASSIFIER_IP_V_6_ID_SRC_IP_V_6 = 4, /**< Source IPv6 Address. */
    BCMOLT_CLASSIFIER_IP_V_6_ID_SRC_IP_V_6_MASK = 5, /**< Source IPv6 Address mask. */
    BCMOLT_CLASSIFIER_IP_V_6_ID_IS_ONE_EXT_HDR = 6, /**< Protocol field in First Extension Header of IPv6. */
    BCMOLT_CLASSIFIER_IP_V_6_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_classifier_ip_v_6_id__begin BCMOLT_CLASSIFIER_IP_V_6_ID__BEGIN
#define bcmolt_classifier_ip_v_6_id_classifier_ip_v_6_bitmap BCMOLT_CLASSIFIER_IP_V_6_ID_CLASSIFIER_IP_V_6_BITMAP
#define bcmolt_classifier_ip_v_6_id_match_mld_pkts BCMOLT_CLASSIFIER_IP_V_6_ID_MATCH_MLD_PKTS
#define bcmolt_classifier_ip_v_6_id_dst_ip_v_6 BCMOLT_CLASSIFIER_IP_V_6_ID_DST_IP_V_6
#define bcmolt_classifier_ip_v_6_id_dst_ip_v_6_mask BCMOLT_CLASSIFIER_IP_V_6_ID_DST_IP_V_6_MASK
#define bcmolt_classifier_ip_v_6_id_src_ip_v_6 BCMOLT_CLASSIFIER_IP_V_6_ID_SRC_IP_V_6
#define bcmolt_classifier_ip_v_6_id_src_ip_v_6_mask BCMOLT_CLASSIFIER_IP_V_6_ID_SRC_IP_V_6_MASK
#define bcmolt_classifier_ip_v_6_id_is_one_ext_hdr BCMOLT_CLASSIFIER_IP_V_6_ID_IS_ONE_EXT_HDR
#define bcmolt_classifier_ip_v_6_id__num_of BCMOLT_CLASSIFIER_IP_V_6_ID__NUM_OF
#define bcmolt_classifier_ip_v_6_id_all_properties 0xFF
#define bcmolt_classifier_ip_v_6_id_full_mask 0x7F

} bcmolt_classifier_ip_v_6_id;

/** Identifiers for all fields in a 'ddr_test_completed'. */
typedef enum
{
    BCMOLT_DDR_TEST_COMPLETED_ID__BEGIN = 0,
    BCMOLT_DDR_TEST_COMPLETED_ID_STATUS = 0, /**< Status. */
    BCMOLT_DDR_TEST_COMPLETED_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ddr_test_completed_id__begin BCMOLT_DDR_TEST_COMPLETED_ID__BEGIN
#define bcmolt_ddr_test_completed_id_status BCMOLT_DDR_TEST_COMPLETED_ID_STATUS
#define bcmolt_ddr_test_completed_id__num_of BCMOLT_DDR_TEST_COMPLETED_ID__NUM_OF
#define bcmolt_ddr_test_completed_id_all_properties 0xFF
#define bcmolt_ddr_test_completed_id_full_mask 0x1

} bcmolt_ddr_test_completed_id;

/** Identifiers for all fields in a 'ddr_test_completed_default'. */
typedef enum
{
    BCMOLT_DDR_TEST_COMPLETED_DEFAULT_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ddr_test_completed_default_id__num_of BCMOLT_DDR_TEST_COMPLETED_DEFAULT_ID__NUM_OF
#define bcmolt_ddr_test_completed_default_id_all_properties 0xFF
#define bcmolt_ddr_test_completed_default_id_full_mask 0x0

} bcmolt_ddr_test_completed_default_id;

/** Identifiers for all fields in a 'ddr_test_completed_completed'. */
typedef enum
{
    BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID__BEGIN = 0,
    BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID_CPU_RESULT = 0, /**< CPU Result. */
    BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID_RAS_0_RESULT = 1, /**< RAS 0 Result. */
    BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID_RAS_1_RESULT = 2, /**< RAS 1 Result. */
    BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ddr_test_completed_completed_id__begin BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID__BEGIN
#define bcmolt_ddr_test_completed_completed_id_cpu_result BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID_CPU_RESULT
#define bcmolt_ddr_test_completed_completed_id_ras_0_result BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID_RAS_0_RESULT
#define bcmolt_ddr_test_completed_completed_id_ras_1_result BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID_RAS_1_RESULT
#define bcmolt_ddr_test_completed_completed_id__num_of BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID__NUM_OF
#define bcmolt_ddr_test_completed_completed_id_all_properties 0xFF
#define bcmolt_ddr_test_completed_completed_id_full_mask 0x7

} bcmolt_ddr_test_completed_completed_id;

/** Identifiers for all fields in a 'ddr_test_completed_connection_failed'. */
typedef enum
{
    BCMOLT_DDR_TEST_COMPLETED_CONNECTION_FAILED_ID__BEGIN = 0,
    BCMOLT_DDR_TEST_COMPLETED_CONNECTION_FAILED_ID_REASON = 0, /**< Connection fail reason. */
    BCMOLT_DDR_TEST_COMPLETED_CONNECTION_FAILED_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ddr_test_completed_connection_failed_id__begin BCMOLT_DDR_TEST_COMPLETED_CONNECTION_FAILED_ID__BEGIN
#define bcmolt_ddr_test_completed_connection_failed_id_reason BCMOLT_DDR_TEST_COMPLETED_CONNECTION_FAILED_ID_REASON
#define bcmolt_ddr_test_completed_connection_failed_id__num_of BCMOLT_DDR_TEST_COMPLETED_CONNECTION_FAILED_ID__NUM_OF
#define bcmolt_ddr_test_completed_connection_failed_id_all_properties 0xFF
#define bcmolt_ddr_test_completed_connection_failed_id_full_mask 0x1

} bcmolt_ddr_test_completed_connection_failed_id;

/** Identifiers for all fields in a 'debug_device_cfg'. */
typedef enum
{
    BCMOLT_DEBUG_DEVICE_CFG_ID__BEGIN = 0,
    BCMOLT_DEBUG_DEVICE_CFG_ID_USE_PREV_PON_SERDES_FIRMWARE = 0, /**< Use previous SGB SERDES firmware. */
    BCMOLT_DEBUG_DEVICE_CFG_ID_USE_PREV_NNI_SERDES_FIRMWARE = 1, /**< Use previous NNI SERDES firmware. */
    BCMOLT_DEBUG_DEVICE_CFG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_debug_device_cfg_id__begin BCMOLT_DEBUG_DEVICE_CFG_ID__BEGIN
#define bcmolt_debug_device_cfg_id_use_prev_pon_serdes_firmware BCMOLT_DEBUG_DEVICE_CFG_ID_USE_PREV_PON_SERDES_FIRMWARE
#define bcmolt_debug_device_cfg_id_use_prev_nni_serdes_firmware BCMOLT_DEBUG_DEVICE_CFG_ID_USE_PREV_NNI_SERDES_FIRMWARE
#define bcmolt_debug_device_cfg_id__num_of BCMOLT_DEBUG_DEVICE_CFG_ID__NUM_OF
#define bcmolt_debug_device_cfg_id_all_properties 0xFF
#define bcmolt_debug_device_cfg_id_full_mask 0x3

} bcmolt_debug_device_cfg_id;

/** Identifiers for all fields in a 'debug_flow_config'. */
typedef enum
{
    BCMOLT_DEBUG_FLOW_CONFIG_ID__BEGIN = 0,
    BCMOLT_DEBUG_FLOW_CONFIG_ID_UNTAGGED_FLOW = 0, /**< Untagged Flow. */
    BCMOLT_DEBUG_FLOW_CONFIG_ID_UNTAGGED_VID = 1, /**< Untagged VID. */
    BCMOLT_DEBUG_FLOW_CONFIG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_debug_flow_config_id__begin BCMOLT_DEBUG_FLOW_CONFIG_ID__BEGIN
#define bcmolt_debug_flow_config_id_untagged_flow BCMOLT_DEBUG_FLOW_CONFIG_ID_UNTAGGED_FLOW
#define bcmolt_debug_flow_config_id_untagged_vid BCMOLT_DEBUG_FLOW_CONFIG_ID_UNTAGGED_VID
#define bcmolt_debug_flow_config_id__num_of BCMOLT_DEBUG_FLOW_CONFIG_ID__NUM_OF
#define bcmolt_debug_flow_config_id_all_properties 0xFF
#define bcmolt_debug_flow_config_id_full_mask 0x3

} bcmolt_debug_flow_config_id;

/** Identifiers for all fields in a 'ds_frequency_offset'. */
typedef enum
{
    BCMOLT_DS_FREQUENCY_OFFSET_ID__BEGIN = 0,
    BCMOLT_DS_FREQUENCY_OFFSET_ID_SIGN = 0, /**< sign. */
    BCMOLT_DS_FREQUENCY_OFFSET_ID_VALUE = 1, /**< value. */
    BCMOLT_DS_FREQUENCY_OFFSET_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ds_frequency_offset_id__begin BCMOLT_DS_FREQUENCY_OFFSET_ID__BEGIN
#define bcmolt_ds_frequency_offset_id_sign BCMOLT_DS_FREQUENCY_OFFSET_ID_SIGN
#define bcmolt_ds_frequency_offset_id_value BCMOLT_DS_FREQUENCY_OFFSET_ID_VALUE
#define bcmolt_ds_frequency_offset_id__num_of BCMOLT_DS_FREQUENCY_OFFSET_ID__NUM_OF
#define bcmolt_ds_frequency_offset_id_all_properties 0xFF
#define bcmolt_ds_frequency_offset_id_full_mask 0x3

} bcmolt_ds_frequency_offset_id;

/** Identifiers for all fields in a 'egress_qos'. */
typedef enum
{
    BCMOLT_EGRESS_QOS_ID__BEGIN = 0,
    BCMOLT_EGRESS_QOS_ID_TYPE = 0, /**< egress qos type. */
    BCMOLT_EGRESS_QOS_ID_TM_SCHED = 1, /**< TM scheduler. */
    BCMOLT_EGRESS_QOS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_egress_qos_id__begin BCMOLT_EGRESS_QOS_ID__BEGIN
#define bcmolt_egress_qos_id_type BCMOLT_EGRESS_QOS_ID_TYPE
#define bcmolt_egress_qos_id_tm_sched BCMOLT_EGRESS_QOS_ID_TM_SCHED
#define bcmolt_egress_qos_id__num_of BCMOLT_EGRESS_QOS_ID__NUM_OF
#define bcmolt_egress_qos_id_all_properties 0xFF
#define bcmolt_egress_qos_id_full_mask 0x3

} bcmolt_egress_qos_id;

/** Identifiers for all fields in a 'egress_qos_fixed_queue'. */
typedef enum
{
    BCMOLT_EGRESS_QOS_FIXED_QUEUE_ID__BEGIN = 0,
    BCMOLT_EGRESS_QOS_FIXED_QUEUE_ID_QUEUE_ID = 0, /**< queue_id. */
    BCMOLT_EGRESS_QOS_FIXED_QUEUE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_egress_qos_fixed_queue_id__begin BCMOLT_EGRESS_QOS_FIXED_QUEUE_ID__BEGIN
#define bcmolt_egress_qos_fixed_queue_id_queue_id BCMOLT_EGRESS_QOS_FIXED_QUEUE_ID_QUEUE_ID
#define bcmolt_egress_qos_fixed_queue_id__num_of BCMOLT_EGRESS_QOS_FIXED_QUEUE_ID__NUM_OF
#define bcmolt_egress_qos_fixed_queue_id_all_properties 0xFF
#define bcmolt_egress_qos_fixed_queue_id_full_mask 0x1

} bcmolt_egress_qos_fixed_queue_id;

/** Identifiers for all fields in a 'egress_qos_tc_to_queue'. */
typedef enum
{
    BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID__BEGIN = 0,
    BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID_TC_ID = 0, /**< tc_id. */
    BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID_TC_TO_QUEUE_ID = 1, /**< tc_to_queue_id. */
    BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_egress_qos_tc_to_queue_id__begin BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID__BEGIN
#define bcmolt_egress_qos_tc_to_queue_id_tc_id BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID_TC_ID
#define bcmolt_egress_qos_tc_to_queue_id_tc_to_queue_id BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID_TC_TO_QUEUE_ID
#define bcmolt_egress_qos_tc_to_queue_id__num_of BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID__NUM_OF
#define bcmolt_egress_qos_tc_to_queue_id_all_properties 0xFF
#define bcmolt_egress_qos_tc_to_queue_id_full_mask 0x3

} bcmolt_egress_qos_tc_to_queue_id;

/** Identifiers for all fields in a 'egress_qos_pbit_to_tc'. */
typedef enum
{
    BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID__BEGIN = 0,
    BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID_PBIT_TO_TC_ID = 0, /**< pbit_to_tc_id. */
    BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID_TC_TO_QUEUE_ID = 1, /**< tc_to_queue_id. */
    BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_egress_qos_pbit_to_tc_id__begin BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID__BEGIN
#define bcmolt_egress_qos_pbit_to_tc_id_pbit_to_tc_id BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID_PBIT_TO_TC_ID
#define bcmolt_egress_qos_pbit_to_tc_id_tc_to_queue_id BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID_TC_TO_QUEUE_ID
#define bcmolt_egress_qos_pbit_to_tc_id__num_of BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID__NUM_OF
#define bcmolt_egress_qos_pbit_to_tc_id_all_properties 0xFF
#define bcmolt_egress_qos_pbit_to_tc_id_full_mask 0x3

} bcmolt_egress_qos_pbit_to_tc_id;

/** Identifiers for all fields in a 'egress_qos_priority_to_queue'. */
typedef enum
{
    BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID__BEGIN = 0,
    BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID_TM_QMP_ID = 0, /**< tm_qmp_id. */
    BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID_TM_Q_SET_ID = 1, /**< tm_q_set_id. */
    BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_egress_qos_priority_to_queue_id__begin BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID__BEGIN
#define bcmolt_egress_qos_priority_to_queue_id_tm_qmp_id BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID_TM_QMP_ID
#define bcmolt_egress_qos_priority_to_queue_id_tm_q_set_id BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID_TM_Q_SET_ID
#define bcmolt_egress_qos_priority_to_queue_id__num_of BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID__NUM_OF
#define bcmolt_egress_qos_priority_to_queue_id_all_properties 0xFF
#define bcmolt_egress_qos_priority_to_queue_id_full_mask 0x3

} bcmolt_egress_qos_priority_to_queue_id;

/** Identifiers for all fields in a 'egress_qos_none'. */
typedef enum
{
    BCMOLT_EGRESS_QOS_NONE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_egress_qos_none_id__num_of BCMOLT_EGRESS_QOS_NONE_ID__NUM_OF
#define bcmolt_egress_qos_none_id_all_properties 0xFF
#define bcmolt_egress_qos_none_id_full_mask 0x0

} bcmolt_egress_qos_none_id;

/** Identifiers for all fields in a 'embedded_image_entry'. */
typedef enum
{
    BCMOLT_EMBEDDED_IMAGE_ENTRY_ID__BEGIN = 0,
    BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_IMAGE_TYPE = 0, /**< Image Type. */
    BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_IMAGE_SIZE = 1, /**< Image size. */
    BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_CRC32 = 2, /**< CRC32. */
    BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_STATUS = 3, /**< Status. */
    BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_IMAGE_NAME = 4, /**< Image name. */
    BCMOLT_EMBEDDED_IMAGE_ENTRY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_embedded_image_entry_id__begin BCMOLT_EMBEDDED_IMAGE_ENTRY_ID__BEGIN
#define bcmolt_embedded_image_entry_id_image_type BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_IMAGE_TYPE
#define bcmolt_embedded_image_entry_id_image_size BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_IMAGE_SIZE
#define bcmolt_embedded_image_entry_id_crc32 BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_CRC32
#define bcmolt_embedded_image_entry_id_status BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_STATUS
#define bcmolt_embedded_image_entry_id_image_name BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_IMAGE_NAME
#define bcmolt_embedded_image_entry_id__num_of BCMOLT_EMBEDDED_IMAGE_ENTRY_ID__NUM_OF
#define bcmolt_embedded_image_entry_id_all_properties 0xFF
#define bcmolt_embedded_image_entry_id_full_mask 0x1F

} bcmolt_embedded_image_entry_id;

/** Identifiers for all fields in a 'erps_intf_ref'. */
typedef enum
{
    BCMOLT_ERPS_INTF_REF_ID__BEGIN = 0,
    BCMOLT_ERPS_INTF_REF_ID_INTF_ID = 0, /**< intf_id. */
    BCMOLT_ERPS_INTF_REF_ID_INTF_TYPE = 1, /**< intf_type. */
    BCMOLT_ERPS_INTF_REF_ID_PORT_TYPE = 2, /**< port_type. */
    BCMOLT_ERPS_INTF_REF_ID_INTF_OPT = 3, /**< intf_opt. */
    BCMOLT_ERPS_INTF_REF_ID_SUB_PORT_IDX = 4, /**< sub_port_index. */
    BCMOLT_ERPS_INTF_REF_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_intf_ref_id__begin BCMOLT_ERPS_INTF_REF_ID__BEGIN
#define bcmolt_erps_intf_ref_id_intf_id BCMOLT_ERPS_INTF_REF_ID_INTF_ID
#define bcmolt_erps_intf_ref_id_intf_type BCMOLT_ERPS_INTF_REF_ID_INTF_TYPE
#define bcmolt_erps_intf_ref_id_port_type BCMOLT_ERPS_INTF_REF_ID_PORT_TYPE
#define bcmolt_erps_intf_ref_id_intf_opt BCMOLT_ERPS_INTF_REF_ID_INTF_OPT
#define bcmolt_erps_intf_ref_id_sub_port_idx BCMOLT_ERPS_INTF_REF_ID_SUB_PORT_IDX
#define bcmolt_erps_intf_ref_id__num_of BCMOLT_ERPS_INTF_REF_ID__NUM_OF
#define bcmolt_erps_intf_ref_id_all_properties 0xFF
#define bcmolt_erps_intf_ref_id_full_mask 0x1F

} bcmolt_erps_intf_ref_id;

/** Identifiers for all fields in a 'extended_dba_priority_adjustment'. */
typedef enum
{
    BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID__BEGIN = 0,
    BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID_CONTROL = 0, /**< control. */
    BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID_SLOTS = 1, /**< slots. */
    BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_extended_dba_priority_adjustment_id__begin BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID__BEGIN
#define bcmolt_extended_dba_priority_adjustment_id_control BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID_CONTROL
#define bcmolt_extended_dba_priority_adjustment_id_slots BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID_SLOTS
#define bcmolt_extended_dba_priority_adjustment_id__num_of BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID__NUM_OF
#define bcmolt_extended_dba_priority_adjustment_id_all_properties 0xFF
#define bcmolt_extended_dba_priority_adjustment_id_full_mask 0x3

} bcmolt_extended_dba_priority_adjustment_id;

/** Identifiers for all fields in a 'firmware_sw_version'. */
typedef enum
{
    BCMOLT_FIRMWARE_SW_VERSION_ID__BEGIN = 0,
    BCMOLT_FIRMWARE_SW_VERSION_ID_MAJOR = 0, /**< Major. */
    BCMOLT_FIRMWARE_SW_VERSION_ID_MINOR = 1, /**< Minor. */
    BCMOLT_FIRMWARE_SW_VERSION_ID_REVISION = 2, /**< Revision. */
    BCMOLT_FIRMWARE_SW_VERSION_ID_MODEL = 3, /**< Model. */
    BCMOLT_FIRMWARE_SW_VERSION_ID_BUILD_TIME = 4, /**< Firmware SW build time. */
    BCMOLT_FIRMWARE_SW_VERSION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_firmware_sw_version_id__begin BCMOLT_FIRMWARE_SW_VERSION_ID__BEGIN
#define bcmolt_firmware_sw_version_id_major BCMOLT_FIRMWARE_SW_VERSION_ID_MAJOR
#define bcmolt_firmware_sw_version_id_minor BCMOLT_FIRMWARE_SW_VERSION_ID_MINOR
#define bcmolt_firmware_sw_version_id_revision BCMOLT_FIRMWARE_SW_VERSION_ID_REVISION
#define bcmolt_firmware_sw_version_id_model BCMOLT_FIRMWARE_SW_VERSION_ID_MODEL
#define bcmolt_firmware_sw_version_id_build_time BCMOLT_FIRMWARE_SW_VERSION_ID_BUILD_TIME
#define bcmolt_firmware_sw_version_id__num_of BCMOLT_FIRMWARE_SW_VERSION_ID__NUM_OF
#define bcmolt_firmware_sw_version_id_all_properties 0xFF
#define bcmolt_firmware_sw_version_id_full_mask 0x1F

} bcmolt_firmware_sw_version_id;

/** Identifiers for all fields in a 'flow_intf_ref'. */
typedef enum
{
    BCMOLT_FLOW_INTF_REF_ID__BEGIN = 0,
    BCMOLT_FLOW_INTF_REF_ID_INTF_TYPE = 0, /**< intf_type. */
    BCMOLT_FLOW_INTF_REF_ID_INTF_ID = 1, /**< intf_id. */
    BCMOLT_FLOW_INTF_REF_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_intf_ref_id__begin BCMOLT_FLOW_INTF_REF_ID__BEGIN
#define bcmolt_flow_intf_ref_id_intf_type BCMOLT_FLOW_INTF_REF_ID_INTF_TYPE
#define bcmolt_flow_intf_ref_id_intf_id BCMOLT_FLOW_INTF_REF_ID_INTF_ID
#define bcmolt_flow_intf_ref_id__num_of BCMOLT_FLOW_INTF_REF_ID__NUM_OF
#define bcmolt_flow_intf_ref_id_all_properties 0xFF
#define bcmolt_flow_intf_ref_id_full_mask 0x3

} bcmolt_flow_intf_ref_id;

/** Identifiers for all fields in a 'gem_port_configuration'. */
typedef enum
{
    BCMOLT_GEM_PORT_CONFIGURATION_ID__BEGIN = 0,
    BCMOLT_GEM_PORT_CONFIGURATION_ID_DIRECTION = 0, /**< GEM port ID direction. */
    BCMOLT_GEM_PORT_CONFIGURATION_ID_TYPE = 1, /**< GEM port type. */
    BCMOLT_GEM_PORT_CONFIGURATION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_gem_port_configuration_id__begin BCMOLT_GEM_PORT_CONFIGURATION_ID__BEGIN
#define bcmolt_gem_port_configuration_id_direction BCMOLT_GEM_PORT_CONFIGURATION_ID_DIRECTION
#define bcmolt_gem_port_configuration_id_type BCMOLT_GEM_PORT_CONFIGURATION_ID_TYPE
#define bcmolt_gem_port_configuration_id__num_of BCMOLT_GEM_PORT_CONFIGURATION_ID__NUM_OF
#define bcmolt_gem_port_configuration_id_all_properties 0xFF
#define bcmolt_gem_port_configuration_id_full_mask 0x3

} bcmolt_gem_port_configuration_id;

/** Identifiers for all fields in a 'gpon_onu_alarm_state'. */
typedef enum
{
    BCMOLT_GPON_ONU_ALARM_STATE_ID__BEGIN = 0,
    BCMOLT_GPON_ONU_ALARM_STATE_ID_LOSI = 0, /**< Loss of signal. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_LOFI = 1, /**< Loss of frame. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_LOAMI = 2, /**< Loss of PLOAM. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_DGI = 3, /**< Dying Gasp. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_TIWI = 4, /**< Transmission interference Alarm. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_DOWI = 5, /**< Drift of Window. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_SUFI = 6, /**< Start UP Failure. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_SFI = 7, /**< Signal Fail. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_SDI = 8, /**< Signal Degraded. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_DFI = 9, /**< Deactivation Failure. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_LOAI = 10, /**< Loss of ack. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID_LOKI = 11, /**< loss of key. */
    BCMOLT_GPON_ONU_ALARM_STATE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_gpon_onu_alarm_state_id__begin BCMOLT_GPON_ONU_ALARM_STATE_ID__BEGIN
#define bcmolt_gpon_onu_alarm_state_id_losi BCMOLT_GPON_ONU_ALARM_STATE_ID_LOSI
#define bcmolt_gpon_onu_alarm_state_id_lofi BCMOLT_GPON_ONU_ALARM_STATE_ID_LOFI
#define bcmolt_gpon_onu_alarm_state_id_loami BCMOLT_GPON_ONU_ALARM_STATE_ID_LOAMI
#define bcmolt_gpon_onu_alarm_state_id_dgi BCMOLT_GPON_ONU_ALARM_STATE_ID_DGI
#define bcmolt_gpon_onu_alarm_state_id_tiwi BCMOLT_GPON_ONU_ALARM_STATE_ID_TIWI
#define bcmolt_gpon_onu_alarm_state_id_dowi BCMOLT_GPON_ONU_ALARM_STATE_ID_DOWI
#define bcmolt_gpon_onu_alarm_state_id_sufi BCMOLT_GPON_ONU_ALARM_STATE_ID_SUFI
#define bcmolt_gpon_onu_alarm_state_id_sfi BCMOLT_GPON_ONU_ALARM_STATE_ID_SFI
#define bcmolt_gpon_onu_alarm_state_id_sdi BCMOLT_GPON_ONU_ALARM_STATE_ID_SDI
#define bcmolt_gpon_onu_alarm_state_id_dfi BCMOLT_GPON_ONU_ALARM_STATE_ID_DFI
#define bcmolt_gpon_onu_alarm_state_id_loai BCMOLT_GPON_ONU_ALARM_STATE_ID_LOAI
#define bcmolt_gpon_onu_alarm_state_id_loki BCMOLT_GPON_ONU_ALARM_STATE_ID_LOKI
#define bcmolt_gpon_onu_alarm_state_id__num_of BCMOLT_GPON_ONU_ALARM_STATE_ID__NUM_OF
#define bcmolt_gpon_onu_alarm_state_id_all_properties 0xFF
#define bcmolt_gpon_onu_alarm_state_id_full_mask 0xFFF

} bcmolt_gpon_onu_alarm_state_id;

/** Identifiers for all fields in a 'gpon_onu_alarms'. */
typedef enum
{
    BCMOLT_GPON_ONU_ALARMS_ID__BEGIN = 0,
    BCMOLT_GPON_ONU_ALARMS_ID_LOSI = 0, /**< LOSi. */
    BCMOLT_GPON_ONU_ALARMS_ID_LOFI = 1, /**< LOFi. */
    BCMOLT_GPON_ONU_ALARMS_ID_LOAMI = 2, /**< LOAMi. */
    BCMOLT_GPON_ONU_ALARMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_gpon_onu_alarms_id__begin BCMOLT_GPON_ONU_ALARMS_ID__BEGIN
#define bcmolt_gpon_onu_alarms_id_losi BCMOLT_GPON_ONU_ALARMS_ID_LOSI
#define bcmolt_gpon_onu_alarms_id_lofi BCMOLT_GPON_ONU_ALARMS_ID_LOFI
#define bcmolt_gpon_onu_alarms_id_loami BCMOLT_GPON_ONU_ALARMS_ID_LOAMI
#define bcmolt_gpon_onu_alarms_id__num_of BCMOLT_GPON_ONU_ALARMS_ID__NUM_OF
#define bcmolt_gpon_onu_alarms_id_all_properties 0xFF
#define bcmolt_gpon_onu_alarms_id_full_mask 0x7

} bcmolt_gpon_onu_alarms_id;

/** Identifiers for all fields in a 'gpon_onu_alarms_thresholds'. */
typedef enum
{
    BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID__BEGIN = 0,
    BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID_LOSI = 0, /**< LOSi. */
    BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID_LOFI = 1, /**< LOFi. */
    BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID_LOAMI = 2, /**< LOAMi. */
    BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_gpon_onu_alarms_thresholds_id__begin BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID__BEGIN
#define bcmolt_gpon_onu_alarms_thresholds_id_losi BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID_LOSI
#define bcmolt_gpon_onu_alarms_thresholds_id_lofi BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID_LOFI
#define bcmolt_gpon_onu_alarms_thresholds_id_loami BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID_LOAMI
#define bcmolt_gpon_onu_alarms_thresholds_id__num_of BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID__NUM_OF
#define bcmolt_gpon_onu_alarms_thresholds_id_all_properties 0xFF
#define bcmolt_gpon_onu_alarms_thresholds_id_full_mask 0x7

} bcmolt_gpon_onu_alarms_thresholds_id;

/** Identifiers for all fields in a 'gpon_onu_params'. */
typedef enum
{
    BCMOLT_GPON_ONU_PARAMS_ID__BEGIN = 0,
    BCMOLT_GPON_ONU_PARAMS_ID_PASSWORD = 0, /**< password. */
    BCMOLT_GPON_ONU_PARAMS_ID_US_FEC = 1, /**< US FEC. */
    BCMOLT_GPON_ONU_PARAMS_ID_OMCI_PORT_ID = 2, /**< OMCI port ID. */
    BCMOLT_GPON_ONU_PARAMS_ID_DS_BER_REPORTING_INTERVAL = 3, /**< DS BER reporting interval in ms. */
    BCMOLT_GPON_ONU_PARAMS_ID_ALARM_STATE = 4, /**< alarm state. */
    BCMOLT_GPON_ONU_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_gpon_onu_params_id__begin BCMOLT_GPON_ONU_PARAMS_ID__BEGIN
#define bcmolt_gpon_onu_params_id_password BCMOLT_GPON_ONU_PARAMS_ID_PASSWORD
#define bcmolt_gpon_onu_params_id_us_fec BCMOLT_GPON_ONU_PARAMS_ID_US_FEC
#define bcmolt_gpon_onu_params_id_omci_port_id BCMOLT_GPON_ONU_PARAMS_ID_OMCI_PORT_ID
#define bcmolt_gpon_onu_params_id_ds_ber_reporting_interval BCMOLT_GPON_ONU_PARAMS_ID_DS_BER_REPORTING_INTERVAL
#define bcmolt_gpon_onu_params_id_alarm_state BCMOLT_GPON_ONU_PARAMS_ID_ALARM_STATE
#define bcmolt_gpon_onu_params_id__num_of BCMOLT_GPON_ONU_PARAMS_ID__NUM_OF
#define bcmolt_gpon_onu_params_id_all_properties 0xFF
#define bcmolt_gpon_onu_params_id_full_mask 0x1F

} bcmolt_gpon_onu_params_id;

/** Identifiers for all fields in a 'gpon_pon_params'. */
typedef enum
{
    BCMOLT_GPON_PON_PARAMS_ID__BEGIN = 0,
    BCMOLT_GPON_PON_PARAMS_ID_ONU_ALARMS_THRESHOLDS = 0, /**< ONU alarms thresholds. */
    BCMOLT_GPON_PON_PARAMS_ID_PREASSIGNED_EQUALIZATION_DELAY = 1, /**< Pre-assigned Equalization Delay [bits]. */
    BCMOLT_GPON_PON_PARAMS_ID_POWER_LEVEL = 2, /**< Power level. */
    BCMOLT_GPON_PON_PARAMS_ID_BIP32_INDICATION_CONTROL = 3, /**< bip32 indication control. */
    BCMOLT_GPON_PON_PARAMS_ID_DS_BER_REPORTING_INTERVAL = 4, /**< DS BER reporting interval in ms. */
    BCMOLT_GPON_PON_PARAMS_ID_SR_REPORTING_BLOCK_SIZE = 5, /**< SR reporting block size in bytes. */
    BCMOLT_GPON_PON_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_gpon_pon_params_id__begin BCMOLT_GPON_PON_PARAMS_ID__BEGIN
#define bcmolt_gpon_pon_params_id_onu_alarms_thresholds BCMOLT_GPON_PON_PARAMS_ID_ONU_ALARMS_THRESHOLDS
#define bcmolt_gpon_pon_params_id_preassigned_equalization_delay BCMOLT_GPON_PON_PARAMS_ID_PREASSIGNED_EQUALIZATION_DELAY
#define bcmolt_gpon_pon_params_id_power_level BCMOLT_GPON_PON_PARAMS_ID_POWER_LEVEL
#define bcmolt_gpon_pon_params_id_bip32_indication_control BCMOLT_GPON_PON_PARAMS_ID_BIP32_INDICATION_CONTROL
#define bcmolt_gpon_pon_params_id_ds_ber_reporting_interval BCMOLT_GPON_PON_PARAMS_ID_DS_BER_REPORTING_INTERVAL
#define bcmolt_gpon_pon_params_id_sr_reporting_block_size BCMOLT_GPON_PON_PARAMS_ID_SR_REPORTING_BLOCK_SIZE
#define bcmolt_gpon_pon_params_id__num_of BCMOLT_GPON_PON_PARAMS_ID__NUM_OF
#define bcmolt_gpon_pon_params_id_all_properties 0xFF
#define bcmolt_gpon_pon_params_id_full_mask 0x3F

} bcmolt_gpon_pon_params_id;

/** Identifiers for all fields in a 'gpon_trx'. */
typedef enum
{
    BCMOLT_GPON_TRX_ID__BEGIN = 0,
    BCMOLT_GPON_TRX_ID_TRANSCEIVER_TYPE = 0, /**< transceiver type. */
    BCMOLT_GPON_TRX_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_gpon_trx_id__begin BCMOLT_GPON_TRX_ID__BEGIN
#define bcmolt_gpon_trx_id_transceiver_type BCMOLT_GPON_TRX_ID_TRANSCEIVER_TYPE
#define bcmolt_gpon_trx_id__num_of BCMOLT_GPON_TRX_ID__NUM_OF
#define bcmolt_gpon_trx_id_all_properties 0xFF
#define bcmolt_gpon_trx_id_full_mask 0x1

} bcmolt_gpon_trx_id;

/** Identifiers for all fields in a 'group_member_info'. */
typedef enum
{
    BCMOLT_GROUP_MEMBER_INFO_ID__BEGIN = 0,
    BCMOLT_GROUP_MEMBER_INFO_ID_INTF = 0, /**< Egress Pon Interface. */
    BCMOLT_GROUP_MEMBER_INFO_ID_SVC_PORT_ID = 1, /**< Service Port ID. */
    BCMOLT_GROUP_MEMBER_INFO_ID_EGRESS_QOS = 3, /**< Egress qos. */
    BCMOLT_GROUP_MEMBER_INFO_ID_SVC_PORT_IS_WC = 4, /**< Wildcard Service Port. */
    BCMOLT_GROUP_MEMBER_INFO_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_group_member_info_id__begin BCMOLT_GROUP_MEMBER_INFO_ID__BEGIN
#define bcmolt_group_member_info_id_intf BCMOLT_GROUP_MEMBER_INFO_ID_INTF
#define bcmolt_group_member_info_id_svc_port_id BCMOLT_GROUP_MEMBER_INFO_ID_SVC_PORT_ID
#define bcmolt_group_member_info_id_egress_qos BCMOLT_GROUP_MEMBER_INFO_ID_EGRESS_QOS
#define bcmolt_group_member_info_id_svc_port_is_wc BCMOLT_GROUP_MEMBER_INFO_ID_SVC_PORT_IS_WC
#define bcmolt_group_member_info_id__num_of BCMOLT_GROUP_MEMBER_INFO_ID__NUM_OF
#define bcmolt_group_member_info_id_all_properties 0xFF
#define bcmolt_group_member_info_id_full_mask 0x1B

} bcmolt_group_member_info_id;

/** Identifiers for all fields in a 'group_members_update_command'. */
typedef enum
{
    BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID__BEGIN = 0,
    BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID_COMMAND = 0, /**< command. */
    BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID_MEMBERS = 1, /**< members. */
    BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_group_members_update_command_id__begin BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID__BEGIN
#define bcmolt_group_members_update_command_id_command BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID_COMMAND
#define bcmolt_group_members_update_command_id_members BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID_MEMBERS
#define bcmolt_group_members_update_command_id__num_of BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID__NUM_OF
#define bcmolt_group_members_update_command_id_all_properties 0xFF
#define bcmolt_group_members_update_command_id_full_mask 0x3

} bcmolt_group_members_update_command_id;

/** Identifiers for all fields in a 'host_port_params'. */
typedef enum
{
    BCMOLT_HOST_PORT_PARAMS_ID__BEGIN = 0,
    BCMOLT_HOST_PORT_PARAMS_ID_PIR_KBPS = 0, /**< pir_kbps. */
    BCMOLT_HOST_PORT_PARAMS_ID_QUEUE_SIZE_KBYTES = 1, /**< queue size kbytes. */
    BCMOLT_HOST_PORT_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_host_port_params_id__begin BCMOLT_HOST_PORT_PARAMS_ID__BEGIN
#define bcmolt_host_port_params_id_pir_kbps BCMOLT_HOST_PORT_PARAMS_ID_PIR_KBPS
#define bcmolt_host_port_params_id_queue_size_kbytes BCMOLT_HOST_PORT_PARAMS_ID_QUEUE_SIZE_KBYTES
#define bcmolt_host_port_params_id__num_of BCMOLT_HOST_PORT_PARAMS_ID__NUM_OF
#define bcmolt_host_port_params_id_all_properties 0xFF
#define bcmolt_host_port_params_id_full_mask 0x3

} bcmolt_host_port_params_id;

/** Identifiers for all fields in a 'host_sw_version'. */
typedef enum
{
    BCMOLT_HOST_SW_VERSION_ID__BEGIN = 0,
    BCMOLT_HOST_SW_VERSION_ID_MAJOR = 0, /**< Major. */
    BCMOLT_HOST_SW_VERSION_ID_MINOR = 1, /**< Minor. */
    BCMOLT_HOST_SW_VERSION_ID_REVISION = 2, /**< Revision. */
    BCMOLT_HOST_SW_VERSION_ID_BUILD_TIME = 4, /**< Host SW build time. */
    BCMOLT_HOST_SW_VERSION_ID_MODEL = 5, /**< Model Revision. */
    BCMOLT_HOST_SW_VERSION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_host_sw_version_id__begin BCMOLT_HOST_SW_VERSION_ID__BEGIN
#define bcmolt_host_sw_version_id_major BCMOLT_HOST_SW_VERSION_ID_MAJOR
#define bcmolt_host_sw_version_id_minor BCMOLT_HOST_SW_VERSION_ID_MINOR
#define bcmolt_host_sw_version_id_revision BCMOLT_HOST_SW_VERSION_ID_REVISION
#define bcmolt_host_sw_version_id_build_time BCMOLT_HOST_SW_VERSION_ID_BUILD_TIME
#define bcmolt_host_sw_version_id_model BCMOLT_HOST_SW_VERSION_ID_MODEL
#define bcmolt_host_sw_version_id__num_of BCMOLT_HOST_SW_VERSION_ID__NUM_OF
#define bcmolt_host_sw_version_id_all_properties 0xFF
#define bcmolt_host_sw_version_id_full_mask 0x37

} bcmolt_host_sw_version_id;

/** Identifiers for all fields in a 'hw_pon_id'. */
typedef enum
{
    BCMOLT_HW_PON_ID_ID__BEGIN = 0,
    BCMOLT_HW_PON_ID_ID_PON_ID_1 = 0, /**< pon id 1. */
    BCMOLT_HW_PON_ID_ID_PON_ID_2 = 1, /**< pon id 2. */
    BCMOLT_HW_PON_ID_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_hw_pon_id_id__begin BCMOLT_HW_PON_ID_ID__BEGIN
#define bcmolt_hw_pon_id_id_pon_id_1 BCMOLT_HW_PON_ID_ID_PON_ID_1
#define bcmolt_hw_pon_id_id_pon_id_2 BCMOLT_HW_PON_ID_ID_PON_ID_2
#define bcmolt_hw_pon_id_id__num_of BCMOLT_HW_PON_ID_ID__NUM_OF
#define bcmolt_hw_pon_id_id_all_properties 0xFF
#define bcmolt_hw_pon_id_id_full_mask 0x3

} bcmolt_hw_pon_id_id;

/** Identifiers for all fields in a 'ieee_8021_as_tod'. */
typedef enum
{
    BCMOLT_IEEE_8021_AS_TOD_ID__BEGIN = 0,
    BCMOLT_IEEE_8021_AS_TOD_ID_TOD_FORMAT = 0, /**< 802.1AS ToD Format. */
    BCMOLT_IEEE_8021_AS_TOD_ID_CLOCK_TRANSPORT_SAMPLE_DELAY = 1, /**< Clock Transport Sample Delay. */
    BCMOLT_IEEE_8021_AS_TOD_ID_TOD_READ_DELAY_MS = 2, /**< ToD Read Delay (ms). */
    BCMOLT_IEEE_8021_AS_TOD_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ieee_8021_as_tod_id__begin BCMOLT_IEEE_8021_AS_TOD_ID__BEGIN
#define bcmolt_ieee_8021_as_tod_id_tod_format BCMOLT_IEEE_8021_AS_TOD_ID_TOD_FORMAT
#define bcmolt_ieee_8021_as_tod_id_clock_transport_sample_delay BCMOLT_IEEE_8021_AS_TOD_ID_CLOCK_TRANSPORT_SAMPLE_DELAY
#define bcmolt_ieee_8021_as_tod_id_tod_read_delay_ms BCMOLT_IEEE_8021_AS_TOD_ID_TOD_READ_DELAY_MS
#define bcmolt_ieee_8021_as_tod_id__num_of BCMOLT_IEEE_8021_AS_TOD_ID__NUM_OF
#define bcmolt_ieee_8021_as_tod_id_all_properties 0xFF
#define bcmolt_ieee_8021_as_tod_id_full_mask 0x7

} bcmolt_ieee_8021_as_tod_id;

/** Identifiers for all fields in a 'inband_config_data'. */
typedef enum
{
    BCMOLT_INBAND_CONFIG_DATA_ID__BEGIN = 0,
    BCMOLT_INBAND_CONFIG_DATA_ID_CONTROL = 0, /**< Control. */
    BCMOLT_INBAND_CONFIG_DATA_ID_IP_ADDRESS = 1, /**< IP Address. */
    BCMOLT_INBAND_CONFIG_DATA_ID_UDP_PORT = 2, /**< UDP port. */
    BCMOLT_INBAND_CONFIG_DATA_ID_NET_MASK = 3, /**< Net Mask. */
    BCMOLT_INBAND_CONFIG_DATA_ID_GW_ADDRESS = 4, /**< Gateway Address. */
    BCMOLT_INBAND_CONFIG_DATA_ID_VLAN_TAG = 5, /**< VLAN tag. */
    BCMOLT_INBAND_CONFIG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_inband_config_data_id__begin BCMOLT_INBAND_CONFIG_DATA_ID__BEGIN
#define bcmolt_inband_config_data_id_control BCMOLT_INBAND_CONFIG_DATA_ID_CONTROL
#define bcmolt_inband_config_data_id_ip_address BCMOLT_INBAND_CONFIG_DATA_ID_IP_ADDRESS
#define bcmolt_inband_config_data_id_udp_port BCMOLT_INBAND_CONFIG_DATA_ID_UDP_PORT
#define bcmolt_inband_config_data_id_net_mask BCMOLT_INBAND_CONFIG_DATA_ID_NET_MASK
#define bcmolt_inband_config_data_id_gw_address BCMOLT_INBAND_CONFIG_DATA_ID_GW_ADDRESS
#define bcmolt_inband_config_data_id_vlan_tag BCMOLT_INBAND_CONFIG_DATA_ID_VLAN_TAG
#define bcmolt_inband_config_data_id__num_of BCMOLT_INBAND_CONFIG_DATA_ID__NUM_OF
#define bcmolt_inband_config_data_id_all_properties 0xFF
#define bcmolt_inband_config_data_id_full_mask 0x3F

} bcmolt_inband_config_data_id;

/** Identifiers for all fields in a 'inband_conn_data'. */
typedef enum
{
    BCMOLT_INBAND_CONN_DATA_ID__BEGIN = 0,
    BCMOLT_INBAND_CONN_DATA_ID_DEVICE_IP_ADDRESS = 0, /**< Device IP Address. */
    BCMOLT_INBAND_CONN_DATA_ID_DEVICE_UDP_PORT = 1, /**< Device UDP port. */
    BCMOLT_INBAND_CONN_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_inband_conn_data_id__begin BCMOLT_INBAND_CONN_DATA_ID__BEGIN
#define bcmolt_inband_conn_data_id_device_ip_address BCMOLT_INBAND_CONN_DATA_ID_DEVICE_IP_ADDRESS
#define bcmolt_inband_conn_data_id_device_udp_port BCMOLT_INBAND_CONN_DATA_ID_DEVICE_UDP_PORT
#define bcmolt_inband_conn_data_id__num_of BCMOLT_INBAND_CONN_DATA_ID__NUM_OF
#define bcmolt_inband_conn_data_id_all_properties 0xFF
#define bcmolt_inband_conn_data_id_full_mask 0x3

} bcmolt_inband_conn_data_id;

/** Identifiers for all fields in a 'indication_shaping'. */
typedef enum
{
    BCMOLT_INDICATION_SHAPING_ID__BEGIN = 0,
    BCMOLT_INDICATION_SHAPING_ID_ENABLED = 0, /**< Enabled. */
    BCMOLT_INDICATION_SHAPING_ID_MAX_RATE = 1, /**< Max Rate. */
    BCMOLT_INDICATION_SHAPING_ID_MAX_BURST = 2, /**< Max Burst. */
    BCMOLT_INDICATION_SHAPING_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_indication_shaping_id__begin BCMOLT_INDICATION_SHAPING_ID__BEGIN
#define bcmolt_indication_shaping_id_enabled BCMOLT_INDICATION_SHAPING_ID_ENABLED
#define bcmolt_indication_shaping_id_max_rate BCMOLT_INDICATION_SHAPING_ID_MAX_RATE
#define bcmolt_indication_shaping_id_max_burst BCMOLT_INDICATION_SHAPING_ID_MAX_BURST
#define bcmolt_indication_shaping_id__num_of BCMOLT_INDICATION_SHAPING_ID__NUM_OF
#define bcmolt_indication_shaping_id_all_properties 0xFF
#define bcmolt_indication_shaping_id_full_mask 0x7

} bcmolt_indication_shaping_id;

/** Identifiers for all fields in a 'inni_config'. */
typedef enum
{
    BCMOLT_INNI_CONFIG_ID__BEGIN = 0,
    BCMOLT_INNI_CONFIG_ID_MODE = 0, /**< INNI Mode. */
    BCMOLT_INNI_CONFIG_ID_MUX = 1, /**< INNI Multiplexing. */
    BCMOLT_INNI_CONFIG_ID_CL73_AN = 2, /**< CL73 AN. */
    BCMOLT_INNI_CONFIG_ID_LINK_TRAINING = 3, /**< Link Training. */
    BCMOLT_INNI_CONFIG_ID_INNI_FEC = 4, /**< INNI_FEC. */
    BCMOLT_INNI_CONFIG_ID_AVAILABLE_LANES = 5, /**< INNI Lanes. */
    BCMOLT_INNI_CONFIG_ID_PS_GPIO = 6, /**< Protecion Switch GPIO. */
    BCMOLT_INNI_CONFIG_ID_GPIO_POLARITY = 7, /**< gpio_polarity. */
    BCMOLT_INNI_CONFIG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_inni_config_id__begin BCMOLT_INNI_CONFIG_ID__BEGIN
#define bcmolt_inni_config_id_mode BCMOLT_INNI_CONFIG_ID_MODE
#define bcmolt_inni_config_id_mux BCMOLT_INNI_CONFIG_ID_MUX
#define bcmolt_inni_config_id_cl73_an BCMOLT_INNI_CONFIG_ID_CL73_AN
#define bcmolt_inni_config_id_link_training BCMOLT_INNI_CONFIG_ID_LINK_TRAINING
#define bcmolt_inni_config_id_inni_fec BCMOLT_INNI_CONFIG_ID_INNI_FEC
#define bcmolt_inni_config_id_available_lanes BCMOLT_INNI_CONFIG_ID_AVAILABLE_LANES
#define bcmolt_inni_config_id_ps_gpio BCMOLT_INNI_CONFIG_ID_PS_GPIO
#define bcmolt_inni_config_id_gpio_polarity BCMOLT_INNI_CONFIG_ID_GPIO_POLARITY
#define bcmolt_inni_config_id__num_of BCMOLT_INNI_CONFIG_ID__NUM_OF
#define bcmolt_inni_config_id_all_properties 0xFF
#define bcmolt_inni_config_id_full_mask 0xFF

} bcmolt_inni_config_id;

/** Identifiers for all fields in a 'intf_ref'. */
typedef enum
{
    BCMOLT_INTF_REF_ID__BEGIN = 0,
    BCMOLT_INTF_REF_ID_INTF_TYPE = 0, /**< intf_type. */
    BCMOLT_INTF_REF_ID_INTF_ID = 1, /**< intf_id. */
    BCMOLT_INTF_REF_ID_INTF_OPT = 2, /**< intf_opt. */
    BCMOLT_INTF_REF_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_intf_ref_id__begin BCMOLT_INTF_REF_ID__BEGIN
#define bcmolt_intf_ref_id_intf_type BCMOLT_INTF_REF_ID_INTF_TYPE
#define bcmolt_intf_ref_id_intf_id BCMOLT_INTF_REF_ID_INTF_ID
#define bcmolt_intf_ref_id_intf_opt BCMOLT_INTF_REF_ID_INTF_OPT
#define bcmolt_intf_ref_id__num_of BCMOLT_INTF_REF_ID__NUM_OF
#define bcmolt_intf_ref_id_all_properties 0xFF
#define bcmolt_intf_ref_id_full_mask 0x7

} bcmolt_intf_ref_id;

/** Identifiers for all fields in a 'itu_onu_params'. */
typedef enum
{
    BCMOLT_ITU_ONU_PARAMS_ID__BEGIN = 0,
    BCMOLT_ITU_ONU_PARAMS_ID_SERIAL_NUMBER = 0, /**< serial number. */
    BCMOLT_ITU_ONU_PARAMS_ID_RANGING_TIME = 1, /**< ranging time. */
    BCMOLT_ITU_ONU_PARAMS_ID_ENCRYPTION_KEY = 2, /**< current encryption key. */
    BCMOLT_ITU_ONU_PARAMS_ID_AUTO_LEARNING = 3, /**< automatic learning of password/registration ID. */
    BCMOLT_ITU_ONU_PARAMS_ID_DISABLED_AFTER_DISCOVERY = 5, /**< Disabled after Discovery. */
    BCMOLT_ITU_ONU_PARAMS_ID_AUTOMATIC_ONU_DEACTIVATION_REASON = 6, /**< automatic ONU deactivation reason. */
    BCMOLT_ITU_ONU_PARAMS_ID_PS_TYPE_C = 7, /**< ONU PS type C. */
    BCMOLT_ITU_ONU_PARAMS_ID_GPON = 8, /**< GPON ONU Parameters. */
    BCMOLT_ITU_ONU_PARAMS_ID_XGPON = 11, /**< XGPON, NGPON2, XGS-PON ONU Parameters. */
    BCMOLT_ITU_ONU_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itu_onu_params_id__begin BCMOLT_ITU_ONU_PARAMS_ID__BEGIN
#define bcmolt_itu_onu_params_id_serial_number BCMOLT_ITU_ONU_PARAMS_ID_SERIAL_NUMBER
#define bcmolt_itu_onu_params_id_ranging_time BCMOLT_ITU_ONU_PARAMS_ID_RANGING_TIME
#define bcmolt_itu_onu_params_id_encryption_key BCMOLT_ITU_ONU_PARAMS_ID_ENCRYPTION_KEY
#define bcmolt_itu_onu_params_id_auto_learning BCMOLT_ITU_ONU_PARAMS_ID_AUTO_LEARNING
#define bcmolt_itu_onu_params_id_disabled_after_discovery BCMOLT_ITU_ONU_PARAMS_ID_DISABLED_AFTER_DISCOVERY
#define bcmolt_itu_onu_params_id_automatic_onu_deactivation_reason BCMOLT_ITU_ONU_PARAMS_ID_AUTOMATIC_ONU_DEACTIVATION_REASON
#define bcmolt_itu_onu_params_id_ps_type_c BCMOLT_ITU_ONU_PARAMS_ID_PS_TYPE_C
#define bcmolt_itu_onu_params_id_gpon BCMOLT_ITU_ONU_PARAMS_ID_GPON
#define bcmolt_itu_onu_params_id_xgpon BCMOLT_ITU_ONU_PARAMS_ID_XGPON
#define bcmolt_itu_onu_params_id__num_of BCMOLT_ITU_ONU_PARAMS_ID__NUM_OF
#define bcmolt_itu_onu_params_id_all_properties 0xFF
#define bcmolt_itu_onu_params_id_full_mask 0x9EF

} bcmolt_itu_onu_params_id;

/** Identifiers for all fields in a 'itu_pon_params'. */
typedef enum
{
    BCMOLT_ITU_PON_PARAMS_ID__BEGIN = 0,
    BCMOLT_ITU_PON_PARAMS_ID_AVAILABLE_BANDWIDTH = 0, /**< Available Bandwidth. */
    BCMOLT_ITU_PON_PARAMS_ID_RANGING_WINDOW_SIZE = 1, /**< Ranging window size. */
    BCMOLT_ITU_PON_PARAMS_ID_EQD_CYCLES_NUMBER = 2, /**< EqD measurement cycles number. */
    BCMOLT_ITU_PON_PARAMS_ID_DRIFT_CONTROL = 3, /**< drift control. */
    BCMOLT_ITU_PON_PARAMS_ID_LOS_ALARM_THRESHOLD = 4, /**< los alarm threshold. */
    BCMOLT_ITU_PON_PARAMS_ID_BER_MONITOR = 5, /**< BER monitoring params. */
    BCMOLT_ITU_PON_PARAMS_ID_ACK_TIMEOUT = 6, /**< ACK timeout. */
    BCMOLT_ITU_PON_PARAMS_ID_ONU_ACTIVATION = 7, /**< ONU Activation. */
    BCMOLT_ITU_PON_PARAMS_ID_KEY_EXCHANGE = 8, /**< key exchange. */
    BCMOLT_ITU_PON_PARAMS_ID_MIN_DATA_ALLOC_ID = 9, /**< Minimum data alloc id. */
    BCMOLT_ITU_PON_PARAMS_ID_CBR_RT_ALLOCATION_PROFILE = 10, /**< CBR RT Allocation profile. */
    BCMOLT_ITU_PON_PARAMS_ID_CBR_NRT_ALLOCATION_PROFILE = 11, /**< CBR-nrt allocation profile. */
    BCMOLT_ITU_PON_PARAMS_ID_POWER_MANAGEMENT = 12, /**< Power Management. */
    BCMOLT_ITU_PON_PARAMS_ID_PERIODIC_STANDBY_PON_MONITORING = 13, /**< Periodic standby PON monitoring. */
    BCMOLT_ITU_PON_PARAMS_ID_PRBS_CHECKER = 14, /**< PRBS Checker. */
    BCMOLT_ITU_PON_PARAMS_ID_PRBS_GENERATOR = 15, /**< PRBS Generator. */
    BCMOLT_ITU_PON_PARAMS_ID_PRBS_STATUS = 16, /**< PRBS status. */
    BCMOLT_ITU_PON_PARAMS_ID_DBA_MODE = 17, /**< DBA mode. */
    BCMOLT_ITU_PON_PARAMS_ID_PROTECTION_SWITCHING = 19, /**< Protection switching. */
    BCMOLT_ITU_PON_PARAMS_ID_AUTOMATIC_ONU_DEACTIVATION = 21, /**< Automatic ONU deactivation. */
    BCMOLT_ITU_PON_PARAMS_ID_US_BANDWIDTH_LIMIT = 22, /**< US bandwidth Limit. */
    BCMOLT_ITU_PON_PARAMS_ID_ONU_UPGRADE_PARAMS = 23, /**< ONU upgrade params. */
    BCMOLT_ITU_PON_PARAMS_ID_ONU_UPGRADE_STATUS = 24, /**< ONU upgrade status. */
    BCMOLT_ITU_PON_PARAMS_ID_DS_FEC_MODE = 25, /**< DS FEC mode. */
    BCMOLT_ITU_PON_PARAMS_ID_XGPON = 27, /**< XGPON, NGPON2, XGS PON Parameters. */
    BCMOLT_ITU_PON_PARAMS_ID_GPON = 29, /**< GPON Parameters. */
    BCMOLT_ITU_PON_PARAMS_ID_BW_ELIGIBILITY_CLASS_STATS = 31, /**< BW Eligibility Class Statistics. */
    BCMOLT_ITU_PON_PARAMS_ID_DBA = 32, /**< DBA. */
    BCMOLT_ITU_PON_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itu_pon_params_id__begin BCMOLT_ITU_PON_PARAMS_ID__BEGIN
#define bcmolt_itu_pon_params_id_available_bandwidth BCMOLT_ITU_PON_PARAMS_ID_AVAILABLE_BANDWIDTH
#define bcmolt_itu_pon_params_id_ranging_window_size BCMOLT_ITU_PON_PARAMS_ID_RANGING_WINDOW_SIZE
#define bcmolt_itu_pon_params_id_eqd_cycles_number BCMOLT_ITU_PON_PARAMS_ID_EQD_CYCLES_NUMBER
#define bcmolt_itu_pon_params_id_drift_control BCMOLT_ITU_PON_PARAMS_ID_DRIFT_CONTROL
#define bcmolt_itu_pon_params_id_los_alarm_threshold BCMOLT_ITU_PON_PARAMS_ID_LOS_ALARM_THRESHOLD
#define bcmolt_itu_pon_params_id_ber_monitor BCMOLT_ITU_PON_PARAMS_ID_BER_MONITOR
#define bcmolt_itu_pon_params_id_ack_timeout BCMOLT_ITU_PON_PARAMS_ID_ACK_TIMEOUT
#define bcmolt_itu_pon_params_id_onu_activation BCMOLT_ITU_PON_PARAMS_ID_ONU_ACTIVATION
#define bcmolt_itu_pon_params_id_key_exchange BCMOLT_ITU_PON_PARAMS_ID_KEY_EXCHANGE
#define bcmolt_itu_pon_params_id_min_data_alloc_id BCMOLT_ITU_PON_PARAMS_ID_MIN_DATA_ALLOC_ID
#define bcmolt_itu_pon_params_id_cbr_rt_allocation_profile BCMOLT_ITU_PON_PARAMS_ID_CBR_RT_ALLOCATION_PROFILE
#define bcmolt_itu_pon_params_id_cbr_nrt_allocation_profile BCMOLT_ITU_PON_PARAMS_ID_CBR_NRT_ALLOCATION_PROFILE
#define bcmolt_itu_pon_params_id_power_management BCMOLT_ITU_PON_PARAMS_ID_POWER_MANAGEMENT
#define bcmolt_itu_pon_params_id_periodic_standby_pon_monitoring BCMOLT_ITU_PON_PARAMS_ID_PERIODIC_STANDBY_PON_MONITORING
#define bcmolt_itu_pon_params_id_prbs_checker BCMOLT_ITU_PON_PARAMS_ID_PRBS_CHECKER
#define bcmolt_itu_pon_params_id_prbs_generator BCMOLT_ITU_PON_PARAMS_ID_PRBS_GENERATOR
#define bcmolt_itu_pon_params_id_prbs_status BCMOLT_ITU_PON_PARAMS_ID_PRBS_STATUS
#define bcmolt_itu_pon_params_id_dba_mode BCMOLT_ITU_PON_PARAMS_ID_DBA_MODE
#define bcmolt_itu_pon_params_id_protection_switching BCMOLT_ITU_PON_PARAMS_ID_PROTECTION_SWITCHING
#define bcmolt_itu_pon_params_id_automatic_onu_deactivation BCMOLT_ITU_PON_PARAMS_ID_AUTOMATIC_ONU_DEACTIVATION
#define bcmolt_itu_pon_params_id_us_bandwidth_limit BCMOLT_ITU_PON_PARAMS_ID_US_BANDWIDTH_LIMIT
#define bcmolt_itu_pon_params_id_onu_upgrade_params BCMOLT_ITU_PON_PARAMS_ID_ONU_UPGRADE_PARAMS
#define bcmolt_itu_pon_params_id_onu_upgrade_status BCMOLT_ITU_PON_PARAMS_ID_ONU_UPGRADE_STATUS
#define bcmolt_itu_pon_params_id_ds_fec_mode BCMOLT_ITU_PON_PARAMS_ID_DS_FEC_MODE
#define bcmolt_itu_pon_params_id_xgpon BCMOLT_ITU_PON_PARAMS_ID_XGPON
#define bcmolt_itu_pon_params_id_gpon BCMOLT_ITU_PON_PARAMS_ID_GPON
#define bcmolt_itu_pon_params_id_bw_eligibility_class_stats BCMOLT_ITU_PON_PARAMS_ID_BW_ELIGIBILITY_CLASS_STATS
#define bcmolt_itu_pon_params_id_dba BCMOLT_ITU_PON_PARAMS_ID_DBA
#define bcmolt_itu_pon_params_id__num_of BCMOLT_ITU_PON_PARAMS_ID__NUM_OF
#define bcmolt_itu_pon_params_id_all_properties 0xFF
#define bcmolt_itu_pon_params_id_full_mask 0x1ABEBFFFF

} bcmolt_itu_pon_params_id;

/** Identifiers for all fields in a 'itu_tod'. */
typedef enum
{
    BCMOLT_ITU_TOD_ID__BEGIN = 0,
    BCMOLT_ITU_TOD_ID_TOD_ENABLE = 0, /**< ToD enable. */
    BCMOLT_ITU_TOD_ID_TOD_GPIO_PIN = 1, /**< ToD GPIO pin. */
    BCMOLT_ITU_TOD_ID_CONNECTED_INTERNALLY = 2, /**< Connected Internally. */
    BCMOLT_ITU_TOD_ID_TOD_STRING_LENGTH = 3, /**< ToD string length. */
    BCMOLT_ITU_TOD_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itu_tod_id__begin BCMOLT_ITU_TOD_ID__BEGIN
#define bcmolt_itu_tod_id_tod_enable BCMOLT_ITU_TOD_ID_TOD_ENABLE
#define bcmolt_itu_tod_id_tod_gpio_pin BCMOLT_ITU_TOD_ID_TOD_GPIO_PIN
#define bcmolt_itu_tod_id_connected_internally BCMOLT_ITU_TOD_ID_CONNECTED_INTERNALLY
#define bcmolt_itu_tod_id_tod_string_length BCMOLT_ITU_TOD_ID_TOD_STRING_LENGTH
#define bcmolt_itu_tod_id__num_of BCMOLT_ITU_TOD_ID__NUM_OF
#define bcmolt_itu_tod_id_all_properties 0xFF
#define bcmolt_itu_tod_id_full_mask 0xF

} bcmolt_itu_tod_id;

/** Identifiers for all fields in a 'ituonu_upgrade_params'. */
typedef enum
{
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID__BEGIN = 0,
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID_RESPONSE_TIMEOUT_MS = 0, /**< Response timeout in milliseconds. */
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID_MAX_RETRY_COUNT = 1, /**< Maximum retry count. */
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID_OMCI_FORMAT = 2, /**< OMCI format. */
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID_WINDOW_SIZE = 3, /**< Window size. */
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID_ACTIVATE_COMMIT = 4, /**< Activate & commit. */
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID_DELAY_FOR_COMMIT_MS = 5, /**< Delay for commit. */
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID_MAX_ACTIVATION_ATTEMPTS = 6, /**< Max activation attempts. */
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID_END_SWDL_DELAY_MS = 7, /**< End SWDL delay in milliseconds. */
    BCMOLT_ITUONU_UPGRADE_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ituonu_upgrade_params_id__begin BCMOLT_ITUONU_UPGRADE_PARAMS_ID__BEGIN
#define bcmolt_ituonu_upgrade_params_id_response_timeout_ms BCMOLT_ITUONU_UPGRADE_PARAMS_ID_RESPONSE_TIMEOUT_MS
#define bcmolt_ituonu_upgrade_params_id_max_retry_count BCMOLT_ITUONU_UPGRADE_PARAMS_ID_MAX_RETRY_COUNT
#define bcmolt_ituonu_upgrade_params_id_omci_format BCMOLT_ITUONU_UPGRADE_PARAMS_ID_OMCI_FORMAT
#define bcmolt_ituonu_upgrade_params_id_window_size BCMOLT_ITUONU_UPGRADE_PARAMS_ID_WINDOW_SIZE
#define bcmolt_ituonu_upgrade_params_id_activate_commit BCMOLT_ITUONU_UPGRADE_PARAMS_ID_ACTIVATE_COMMIT
#define bcmolt_ituonu_upgrade_params_id_delay_for_commit_ms BCMOLT_ITUONU_UPGRADE_PARAMS_ID_DELAY_FOR_COMMIT_MS
#define bcmolt_ituonu_upgrade_params_id_max_activation_attempts BCMOLT_ITUONU_UPGRADE_PARAMS_ID_MAX_ACTIVATION_ATTEMPTS
#define bcmolt_ituonu_upgrade_params_id_end_swdl_delay_ms BCMOLT_ITUONU_UPGRADE_PARAMS_ID_END_SWDL_DELAY_MS
#define bcmolt_ituonu_upgrade_params_id__num_of BCMOLT_ITUONU_UPGRADE_PARAMS_ID__NUM_OF
#define bcmolt_ituonu_upgrade_params_id_all_properties 0xFF
#define bcmolt_ituonu_upgrade_params_id_full_mask 0xFF

} bcmolt_ituonu_upgrade_params_id;

/** Identifiers for all fields in a 'itupon_dba'. */
typedef enum
{
    BCMOLT_ITUPON_DBA_ID__BEGIN = 0,
    BCMOLT_ITUPON_DBA_ID_IMPLEMENTATION_TYPE = 0, /**< DBA Implementation type. */
    BCMOLT_ITUPON_DBA_ID_NUM_OF_FRAMES_PER_MAP = 1, /**< Number of frames per map. */
    BCMOLT_ITUPON_DBA_ID_EXTERNAL_DBA_OPTIONS = 2, /**< External DBA options. */
    BCMOLT_ITUPON_DBA_ID_EXTENDED_DBA_PRIORITY_ADJUSTMENT = 3, /**< Extended DBA priority adjustment. */
    BCMOLT_ITUPON_DBA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_dba_id__begin BCMOLT_ITUPON_DBA_ID__BEGIN
#define bcmolt_itupon_dba_id_implementation_type BCMOLT_ITUPON_DBA_ID_IMPLEMENTATION_TYPE
#define bcmolt_itupon_dba_id_num_of_frames_per_map BCMOLT_ITUPON_DBA_ID_NUM_OF_FRAMES_PER_MAP
#define bcmolt_itupon_dba_id_external_dba_options BCMOLT_ITUPON_DBA_ID_EXTERNAL_DBA_OPTIONS
#define bcmolt_itupon_dba_id_extended_dba_priority_adjustment BCMOLT_ITUPON_DBA_ID_EXTENDED_DBA_PRIORITY_ADJUSTMENT
#define bcmolt_itupon_dba_id__num_of BCMOLT_ITUPON_DBA_ID__NUM_OF
#define bcmolt_itupon_dba_id_all_properties 0xFF
#define bcmolt_itupon_dba_id_full_mask 0xF

} bcmolt_itupon_dba_id;

/** Identifiers for all fields in a 'itupon_onu_aes_key'. */
typedef enum
{
    BCMOLT_ITUPON_ONU_AES_KEY_ID__BEGIN = 0,
    BCMOLT_ITUPON_ONU_AES_KEY_ID_ENCRYPTION_KEY = 0, /**< encryption key. */
    BCMOLT_ITUPON_ONU_AES_KEY_ID_KEY_INDEX = 1, /**< key index. */
    BCMOLT_ITUPON_ONU_AES_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_onu_aes_key_id__begin BCMOLT_ITUPON_ONU_AES_KEY_ID__BEGIN
#define bcmolt_itupon_onu_aes_key_id_encryption_key BCMOLT_ITUPON_ONU_AES_KEY_ID_ENCRYPTION_KEY
#define bcmolt_itupon_onu_aes_key_id_key_index BCMOLT_ITUPON_ONU_AES_KEY_ID_KEY_INDEX
#define bcmolt_itupon_onu_aes_key_id__num_of BCMOLT_ITUPON_ONU_AES_KEY_ID__NUM_OF
#define bcmolt_itupon_onu_aes_key_id_all_properties 0xFF
#define bcmolt_itupon_onu_aes_key_id_full_mask 0x3

} bcmolt_itupon_onu_aes_key_id;

/** Identifiers for all fields in a 'itupon_onu_eqd'. */
typedef enum
{
    BCMOLT_ITUPON_ONU_EQD_ID__BEGIN = 0,
    BCMOLT_ITUPON_ONU_EQD_ID_ONU_ID = 0, /**< ONU ID. */
    BCMOLT_ITUPON_ONU_EQD_ID_EQD = 1, /**< EQD. */
    BCMOLT_ITUPON_ONU_EQD_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_onu_eqd_id__begin BCMOLT_ITUPON_ONU_EQD_ID__BEGIN
#define bcmolt_itupon_onu_eqd_id_onu_id BCMOLT_ITUPON_ONU_EQD_ID_ONU_ID
#define bcmolt_itupon_onu_eqd_id_eqd BCMOLT_ITUPON_ONU_EQD_ID_EQD
#define bcmolt_itupon_onu_eqd_id__num_of BCMOLT_ITUPON_ONU_EQD_ID__NUM_OF
#define bcmolt_itupon_onu_eqd_id_all_properties 0xFF
#define bcmolt_itupon_onu_eqd_id_full_mask 0x3

} bcmolt_itupon_onu_eqd_id;

/** Identifiers for all fields in a 'itupon_protection_switching'. */
typedef enum
{
    BCMOLT_ITUPON_PROTECTION_SWITCHING_ID__BEGIN = 0,
    BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_TIMEOUT = 0, /**< Timeout. */
    BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_GPIO_PIN = 1, /**< GPIO pin. */
    BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_PS_C_WAIT_BEFORE_DEACTIVATION_TIMEOUT = 2, /**< protection switching type c wait before deactivation timeout. */
    BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_OPTIONS = 3, /**< Options. */
    BCMOLT_ITUPON_PROTECTION_SWITCHING_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_protection_switching_id__begin BCMOLT_ITUPON_PROTECTION_SWITCHING_ID__BEGIN
#define bcmolt_itupon_protection_switching_id_timeout BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_TIMEOUT
#define bcmolt_itupon_protection_switching_id_gpio_pin BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_GPIO_PIN
#define bcmolt_itupon_protection_switching_id_ps_c_wait_before_deactivation_timeout BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_PS_C_WAIT_BEFORE_DEACTIVATION_TIMEOUT
#define bcmolt_itupon_protection_switching_id_options BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_OPTIONS
#define bcmolt_itupon_protection_switching_id__num_of BCMOLT_ITUPON_PROTECTION_SWITCHING_ID__NUM_OF
#define bcmolt_itupon_protection_switching_id_all_properties 0xFF
#define bcmolt_itupon_protection_switching_id_full_mask 0xF

} bcmolt_itupon_protection_switching_id;

/** Identifiers for all fields in a 'key_exchange'. */
typedef enum
{
    BCMOLT_KEY_EXCHANGE_ID__BEGIN = 0,
    BCMOLT_KEY_EXCHANGE_ID_INTERVAL = 0, /**< interval in ms. */
    BCMOLT_KEY_EXCHANGE_ID_CONTROL = 1, /**< control. */
    BCMOLT_KEY_EXCHANGE_ID_ENCRYPTED_PORTS_ONLY = 2, /**< Encrypted ports only. */
    BCMOLT_KEY_EXCHANGE_ID_GPON_MODE = 3, /**< GPON Mode. */
    BCMOLT_KEY_EXCHANGE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_key_exchange_id__begin BCMOLT_KEY_EXCHANGE_ID__BEGIN
#define bcmolt_key_exchange_id_interval BCMOLT_KEY_EXCHANGE_ID_INTERVAL
#define bcmolt_key_exchange_id_control BCMOLT_KEY_EXCHANGE_ID_CONTROL
#define bcmolt_key_exchange_id_encrypted_ports_only BCMOLT_KEY_EXCHANGE_ID_ENCRYPTED_PORTS_ONLY
#define bcmolt_key_exchange_id_gpon_mode BCMOLT_KEY_EXCHANGE_ID_GPON_MODE
#define bcmolt_key_exchange_id__num_of BCMOLT_KEY_EXCHANGE_ID__NUM_OF
#define bcmolt_key_exchange_id_all_properties 0xFF
#define bcmolt_key_exchange_id_full_mask 0xF

} bcmolt_key_exchange_id;

/** Identifiers for all fields in a 'lag_global_parms'. */
typedef enum
{
    BCMOLT_LAG_GLOBAL_PARMS_ID__BEGIN = 0,
    BCMOLT_LAG_GLOBAL_PARMS_ID_POLYNOMIAL = 0, /**< LAG Polynomial Values. */
    BCMOLT_LAG_GLOBAL_PARMS_ID_HASH_FIELD = 1, /**< LAG Hash Fields. */
    BCMOLT_LAG_GLOBAL_PARMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_global_parms_id__begin BCMOLT_LAG_GLOBAL_PARMS_ID__BEGIN
#define bcmolt_lag_global_parms_id_polynomial BCMOLT_LAG_GLOBAL_PARMS_ID_POLYNOMIAL
#define bcmolt_lag_global_parms_id_hash_field BCMOLT_LAG_GLOBAL_PARMS_ID_HASH_FIELD
#define bcmolt_lag_global_parms_id__num_of BCMOLT_LAG_GLOBAL_PARMS_ID__NUM_OF
#define bcmolt_lag_global_parms_id_all_properties 0xFF
#define bcmolt_lag_global_parms_id_full_mask 0x3

} bcmolt_lag_global_parms_id;

/** Identifiers for all fields in a 'lag_interface_members_update_command'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID_COMMAND = 0, /**< command. */
    BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID_NNI_IDS = 1, /**< nni_ids. */
    BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_members_update_command_id__begin BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID__BEGIN
#define bcmolt_lag_interface_members_update_command_id_command BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID_COMMAND
#define bcmolt_lag_interface_members_update_command_id_nni_ids BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID_NNI_IDS
#define bcmolt_lag_interface_members_update_command_id__num_of BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID__NUM_OF
#define bcmolt_lag_interface_members_update_command_id_all_properties 0xFF
#define bcmolt_lag_interface_members_update_command_id_full_mask 0x3

} bcmolt_lag_interface_members_update_command_id;

/** Identifiers for all fields in a 'layer_4_port_range'. */
typedef enum
{
    BCMOLT_LAYER_4_PORT_RANGE_ID__BEGIN = 0,
    BCMOLT_LAYER_4_PORT_RANGE_ID_MIN = 0, /**< port range min value. */
    BCMOLT_LAYER_4_PORT_RANGE_ID_MAX = 1, /**< port range max value. */
    BCMOLT_LAYER_4_PORT_RANGE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_layer_4_port_range_id__begin BCMOLT_LAYER_4_PORT_RANGE_ID__BEGIN
#define bcmolt_layer_4_port_range_id_min BCMOLT_LAYER_4_PORT_RANGE_ID_MIN
#define bcmolt_layer_4_port_range_id_max BCMOLT_LAYER_4_PORT_RANGE_ID_MAX
#define bcmolt_layer_4_port_range_id__num_of BCMOLT_LAYER_4_PORT_RANGE_ID__NUM_OF
#define bcmolt_layer_4_port_range_id_all_properties 0xFF
#define bcmolt_layer_4_port_range_id_full_mask 0x3

} bcmolt_layer_4_port_range_id;

/** Identifiers for all fields in a 'local_mep'. */
typedef enum
{
    BCMOLT_LOCAL_MEP_ID__BEGIN = 0,
    BCMOLT_LOCAL_MEP_ID_ID = 0, /**< id. */
    BCMOLT_LOCAL_MEP_ID_INTERVAL = 3, /**< CCM Interval. */
    BCMOLT_LOCAL_MEP_ID_STATE = 6, /**< state. */
    BCMOLT_LOCAL_MEP_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_local_mep_id__begin BCMOLT_LOCAL_MEP_ID__BEGIN
#define bcmolt_local_mep_id_id BCMOLT_LOCAL_MEP_ID_ID
#define bcmolt_local_mep_id_interval BCMOLT_LOCAL_MEP_ID_INTERVAL
#define bcmolt_local_mep_id_state BCMOLT_LOCAL_MEP_ID_STATE
#define bcmolt_local_mep_id__num_of BCMOLT_LOCAL_MEP_ID__NUM_OF
#define bcmolt_local_mep_id_all_properties 0xFF
#define bcmolt_local_mep_id_full_mask 0x49

} bcmolt_local_mep_id;

/** Identifiers for all fields in a 'log_level_msg_count'. */
typedef enum
{
    BCMOLT_LOG_LEVEL_MSG_COUNT_ID__BEGIN = 0,
    BCMOLT_LOG_LEVEL_MSG_COUNT_ID_NO_LOG = 0, /**< No Log. */
    BCMOLT_LOG_LEVEL_MSG_COUNT_ID_FATAL = 1, /**< Fatal. */
    BCMOLT_LOG_LEVEL_MSG_COUNT_ID_ERROR = 2, /**< Error. */
    BCMOLT_LOG_LEVEL_MSG_COUNT_ID_WARNING = 3, /**< Warning. */
    BCMOLT_LOG_LEVEL_MSG_COUNT_ID_INFO = 4, /**< Info. */
    BCMOLT_LOG_LEVEL_MSG_COUNT_ID_DEBUG = 5, /**< Debug. */
    BCMOLT_LOG_LEVEL_MSG_COUNT_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_log_level_msg_count_id__begin BCMOLT_LOG_LEVEL_MSG_COUNT_ID__BEGIN
#define bcmolt_log_level_msg_count_id_no_log BCMOLT_LOG_LEVEL_MSG_COUNT_ID_NO_LOG
#define bcmolt_log_level_msg_count_id_fatal BCMOLT_LOG_LEVEL_MSG_COUNT_ID_FATAL
#define bcmolt_log_level_msg_count_id_error BCMOLT_LOG_LEVEL_MSG_COUNT_ID_ERROR
#define bcmolt_log_level_msg_count_id_warning BCMOLT_LOG_LEVEL_MSG_COUNT_ID_WARNING
#define bcmolt_log_level_msg_count_id_info BCMOLT_LOG_LEVEL_MSG_COUNT_ID_INFO
#define bcmolt_log_level_msg_count_id_debug BCMOLT_LOG_LEVEL_MSG_COUNT_ID_DEBUG
#define bcmolt_log_level_msg_count_id__num_of BCMOLT_LOG_LEVEL_MSG_COUNT_ID__NUM_OF
#define bcmolt_log_level_msg_count_id_all_properties 0xFF
#define bcmolt_log_level_msg_count_id_full_mask 0x3F

} bcmolt_log_level_msg_count_id;

/** Identifiers for all fields in a 'log_level_per_file'. */
typedef enum
{
    BCMOLT_LOG_LEVEL_PER_FILE_ID__BEGIN = 0,
    BCMOLT_LOG_LEVEL_PER_FILE_ID_PRINT = 0, /**< Print. */
    BCMOLT_LOG_LEVEL_PER_FILE_ID_SAVE = 1, /**< Save. */
    BCMOLT_LOG_LEVEL_PER_FILE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_log_level_per_file_id__begin BCMOLT_LOG_LEVEL_PER_FILE_ID__BEGIN
#define bcmolt_log_level_per_file_id_print BCMOLT_LOG_LEVEL_PER_FILE_ID_PRINT
#define bcmolt_log_level_per_file_id_save BCMOLT_LOG_LEVEL_PER_FILE_ID_SAVE
#define bcmolt_log_level_per_file_id__num_of BCMOLT_LOG_LEVEL_PER_FILE_ID__NUM_OF
#define bcmolt_log_level_per_file_id_all_properties 0xFF
#define bcmolt_log_level_per_file_id_full_mask 0x3

} bcmolt_log_level_per_file_id;

/** Identifiers for all fields in a 'meg_cfg'. */
typedef enum
{
    BCMOLT_MEG_CFG_ID__BEGIN = 0,
    BCMOLT_MEG_CFG_ID_NAME = 0, /**< MEG Name. */
    BCMOLT_MEG_CFG_ID_FORMAT = 1, /**< MEG Id Format. */
    BCMOLT_MEG_CFG_ID_LEVEL = 2, /**< Meg Level. */
    BCMOLT_MEG_CFG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_meg_cfg_id__begin BCMOLT_MEG_CFG_ID__BEGIN
#define bcmolt_meg_cfg_id_name BCMOLT_MEG_CFG_ID_NAME
#define bcmolt_meg_cfg_id_format BCMOLT_MEG_CFG_ID_FORMAT
#define bcmolt_meg_cfg_id_level BCMOLT_MEG_CFG_ID_LEVEL
#define bcmolt_meg_cfg_id__num_of BCMOLT_MEG_CFG_ID__NUM_OF
#define bcmolt_meg_cfg_id_all_properties 0xFF
#define bcmolt_meg_cfg_id_full_mask 0x7

} bcmolt_meg_cfg_id;

/** Identifiers for all fields in a 'ngpon2_onu_params'. */
typedef enum
{
    BCMOLT_NGPON2_ONU_PARAMS_ID__BEGIN = 0,
    BCMOLT_NGPON2_ONU_PARAMS_ID_CALIBRATION_RECORD = 0, /**< Calibration record. */
    BCMOLT_NGPON2_ONU_PARAMS_ID_US_LINE_RATE = 1, /**< US line rate. */
    BCMOLT_NGPON2_ONU_PARAMS_ID_TUNING_GRANULARITY = 2, /**< Tuning granularity. */
    BCMOLT_NGPON2_ONU_PARAMS_ID_STEP_TUNING_TIME = 3, /**< Step tuning time. */
    BCMOLT_NGPON2_ONU_PARAMS_ID_POWER_LEVELLING_CAPABILITIES = 4, /**< Power levelling capabilities. */
    BCMOLT_NGPON2_ONU_PARAMS_ID_TUNING_STATIC_EQD = 5, /**< Tuning Static EQD. */
    BCMOLT_NGPON2_ONU_PARAMS_ID_PS_TYPE_W = 6, /**< PS type W. */
    BCMOLT_NGPON2_ONU_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ngpon2_onu_params_id__begin BCMOLT_NGPON2_ONU_PARAMS_ID__BEGIN
#define bcmolt_ngpon2_onu_params_id_calibration_record BCMOLT_NGPON2_ONU_PARAMS_ID_CALIBRATION_RECORD
#define bcmolt_ngpon2_onu_params_id_us_line_rate BCMOLT_NGPON2_ONU_PARAMS_ID_US_LINE_RATE
#define bcmolt_ngpon2_onu_params_id_tuning_granularity BCMOLT_NGPON2_ONU_PARAMS_ID_TUNING_GRANULARITY
#define bcmolt_ngpon2_onu_params_id_step_tuning_time BCMOLT_NGPON2_ONU_PARAMS_ID_STEP_TUNING_TIME
#define bcmolt_ngpon2_onu_params_id_power_levelling_capabilities BCMOLT_NGPON2_ONU_PARAMS_ID_POWER_LEVELLING_CAPABILITIES
#define bcmolt_ngpon2_onu_params_id_tuning_static_eqd BCMOLT_NGPON2_ONU_PARAMS_ID_TUNING_STATIC_EQD
#define bcmolt_ngpon2_onu_params_id_ps_type_w BCMOLT_NGPON2_ONU_PARAMS_ID_PS_TYPE_W
#define bcmolt_ngpon2_onu_params_id__num_of BCMOLT_NGPON2_ONU_PARAMS_ID__NUM_OF
#define bcmolt_ngpon2_onu_params_id_all_properties 0xFF
#define bcmolt_ngpon2_onu_params_id_full_mask 0x7F

} bcmolt_ngpon2_onu_params_id;

/** Identifiers for all fields in a 'ngpon2_pon_params'. */
typedef enum
{
    BCMOLT_NGPON2_PON_PARAMS_ID__BEGIN = 0,
    BCMOLT_NGPON2_PON_PARAMS_ID_NGPON2_AMD1 = 0, /**< Enable NGPON2 Amendment 1 support on PON. */
    BCMOLT_NGPON2_PON_PARAMS_ID_ONU_TUNING = 1, /**< onu tuning. */
    BCMOLT_NGPON2_PON_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ngpon2_pon_params_id__begin BCMOLT_NGPON2_PON_PARAMS_ID__BEGIN
#define bcmolt_ngpon2_pon_params_id_ngpon2_amd1 BCMOLT_NGPON2_PON_PARAMS_ID_NGPON2_AMD1
#define bcmolt_ngpon2_pon_params_id_onu_tuning BCMOLT_NGPON2_PON_PARAMS_ID_ONU_TUNING
#define bcmolt_ngpon2_pon_params_id__num_of BCMOLT_NGPON2_PON_PARAMS_ID__NUM_OF
#define bcmolt_ngpon2_pon_params_id_all_properties 0xFF
#define bcmolt_ngpon2_pon_params_id_full_mask 0x3

} bcmolt_ngpon2_pon_params_id;

/** Identifiers for all fields in a 'nni_link_status'. */
typedef enum
{
    BCMOLT_NNI_LINK_STATUS_ID__BEGIN = 0,
    BCMOLT_NNI_LINK_STATUS_ID_LINK_STATUS = 0, /**< Link Status. */
    BCMOLT_NNI_LINK_STATUS_ID_SIGNAL_DETECTED = 1, /**< Signal Detected. */
    BCMOLT_NNI_LINK_STATUS_ID_PMD_LOCKED = 2, /**< PMD locked. */
    BCMOLT_NNI_LINK_STATUS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_link_status_id__begin BCMOLT_NNI_LINK_STATUS_ID__BEGIN
#define bcmolt_nni_link_status_id_link_status BCMOLT_NNI_LINK_STATUS_ID_LINK_STATUS
#define bcmolt_nni_link_status_id_signal_detected BCMOLT_NNI_LINK_STATUS_ID_SIGNAL_DETECTED
#define bcmolt_nni_link_status_id_pmd_locked BCMOLT_NNI_LINK_STATUS_ID_PMD_LOCKED
#define bcmolt_nni_link_status_id__num_of BCMOLT_NNI_LINK_STATUS_ID__NUM_OF
#define bcmolt_nni_link_status_id_all_properties 0xFF
#define bcmolt_nni_link_status_id_full_mask 0x7

} bcmolt_nni_link_status_id;

/** Identifiers for all fields in a 'onu_activation'. */
typedef enum
{
    BCMOLT_ONU_ACTIVATION_ID__BEGIN = 0,
    BCMOLT_ONU_ACTIVATION_ID_KEY_EXCHANGE = 0, /**< Key exchange. */
    BCMOLT_ONU_ACTIVATION_ID_AUTHENTICATION = 1, /**< Authentication. */
    BCMOLT_ONU_ACTIVATION_ID_FAIL_DUE_TO_AUTHENTICATION_FAILURE = 2, /**< Fail due to password/registration authentication failure. */
    BCMOLT_ONU_ACTIVATION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_activation_id__begin BCMOLT_ONU_ACTIVATION_ID__BEGIN
#define bcmolt_onu_activation_id_key_exchange BCMOLT_ONU_ACTIVATION_ID_KEY_EXCHANGE
#define bcmolt_onu_activation_id_authentication BCMOLT_ONU_ACTIVATION_ID_AUTHENTICATION
#define bcmolt_onu_activation_id_fail_due_to_authentication_failure BCMOLT_ONU_ACTIVATION_ID_FAIL_DUE_TO_AUTHENTICATION_FAILURE
#define bcmolt_onu_activation_id__num_of BCMOLT_ONU_ACTIVATION_ID__NUM_OF
#define bcmolt_onu_activation_id_all_properties 0xFF
#define bcmolt_onu_activation_id_full_mask 0x7

} bcmolt_onu_activation_id;

/** Identifiers for all fields in a 'onu_power_management_configuration'. */
typedef enum
{
    BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID__BEGIN = 0,
    BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_ILOWPOWER = 0, /**< Ilowpower. */
    BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_IAWARE = 1, /**< Iaware. */
    BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_ITRANSINIT = 2, /**< Itransinit. */
    BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_ITXINIT = 3, /**< Itxinit. */
    BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_IRXOFF = 4, /**< Irxoff. */
    BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_power_management_configuration_id__begin BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID__BEGIN
#define bcmolt_onu_power_management_configuration_id_ilowpower BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_ILOWPOWER
#define bcmolt_onu_power_management_configuration_id_iaware BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_IAWARE
#define bcmolt_onu_power_management_configuration_id_itransinit BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_ITRANSINIT
#define bcmolt_onu_power_management_configuration_id_itxinit BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_ITXINIT
#define bcmolt_onu_power_management_configuration_id_irxoff BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_IRXOFF
#define bcmolt_onu_power_management_configuration_id__num_of BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID__NUM_OF
#define bcmolt_onu_power_management_configuration_id_all_properties 0xFF
#define bcmolt_onu_power_management_configuration_id_full_mask 0x1F

} bcmolt_onu_power_management_configuration_id;

/** Identifiers for all fields in a 'onu_ps_type_w'. */
typedef enum
{
    BCMOLT_ONU_PS_TYPE_W_ID__BEGIN = 0,
    BCMOLT_ONU_PS_TYPE_W_ID_CONTROL = 0, /**< Control. */
    BCMOLT_ONU_PS_TYPE_W_ID_PARTNER_PON_ID = 1, /**< Partner PON ID. */
    BCMOLT_ONU_PS_TYPE_W_ID_PARTNER_STATIC_EQD = 2, /**< Partner Static EQD. */
    BCMOLT_ONU_PS_TYPE_W_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_ps_type_w_id__begin BCMOLT_ONU_PS_TYPE_W_ID__BEGIN
#define bcmolt_onu_ps_type_w_id_control BCMOLT_ONU_PS_TYPE_W_ID_CONTROL
#define bcmolt_onu_ps_type_w_id_partner_pon_id BCMOLT_ONU_PS_TYPE_W_ID_PARTNER_PON_ID
#define bcmolt_onu_ps_type_w_id_partner_static_eqd BCMOLT_ONU_PS_TYPE_W_ID_PARTNER_STATIC_EQD
#define bcmolt_onu_ps_type_w_id__num_of BCMOLT_ONU_PS_TYPE_W_ID__NUM_OF
#define bcmolt_onu_ps_type_w_id_all_properties 0xFF
#define bcmolt_onu_ps_type_w_id_full_mask 0x7

} bcmolt_onu_ps_type_w_id;

/** Identifiers for all fields in a 'onu_tuning_configuration'. */
typedef enum
{
    BCMOLT_ONU_TUNING_CONFIGURATION_ID__BEGIN = 0,
    BCMOLT_ONU_TUNING_CONFIGURATION_ID_TSOURCE = 0, /**< tsource. */
    BCMOLT_ONU_TUNING_CONFIGURATION_ID_TTARGET = 1, /**< ttarget. */
    BCMOLT_ONU_TUNING_CONFIGURATION_ID_REQUEST_REGISTRATION_REQUIRED = 2, /**< request registration required. */
    BCMOLT_ONU_TUNING_CONFIGURATION_ID_RANGE_MODE = 3, /**< range mode. */
    BCMOLT_ONU_TUNING_CONFIGURATION_ID_RETRY_INTERVAL = 4, /**< retry interval. */
    BCMOLT_ONU_TUNING_CONFIGURATION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_tuning_configuration_id__begin BCMOLT_ONU_TUNING_CONFIGURATION_ID__BEGIN
#define bcmolt_onu_tuning_configuration_id_tsource BCMOLT_ONU_TUNING_CONFIGURATION_ID_TSOURCE
#define bcmolt_onu_tuning_configuration_id_ttarget BCMOLT_ONU_TUNING_CONFIGURATION_ID_TTARGET
#define bcmolt_onu_tuning_configuration_id_request_registration_required BCMOLT_ONU_TUNING_CONFIGURATION_ID_REQUEST_REGISTRATION_REQUIRED
#define bcmolt_onu_tuning_configuration_id_range_mode BCMOLT_ONU_TUNING_CONFIGURATION_ID_RANGE_MODE
#define bcmolt_onu_tuning_configuration_id_retry_interval BCMOLT_ONU_TUNING_CONFIGURATION_ID_RETRY_INTERVAL
#define bcmolt_onu_tuning_configuration_id__num_of BCMOLT_ONU_TUNING_CONFIGURATION_ID__NUM_OF
#define bcmolt_onu_tuning_configuration_id_all_properties 0xFF
#define bcmolt_onu_tuning_configuration_id_full_mask 0x1F

} bcmolt_onu_tuning_configuration_id;

/** Identifiers for all fields in a 'onu_upgrade_status'. */
typedef enum
{
    BCMOLT_ONU_UPGRADE_STATUS_ID__BEGIN = 0,
    BCMOLT_ONU_UPGRADE_STATUS_ID_ONU_ID = 0, /**< ONU ID. */
    BCMOLT_ONU_UPGRADE_STATUS_ID_BYTES_TRANSMITTED = 1, /**< Bytes transmitted. */
    BCMOLT_ONU_UPGRADE_STATUS_ID_STATUS = 2, /**< Status. */
    BCMOLT_ONU_UPGRADE_STATUS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_upgrade_status_id__begin BCMOLT_ONU_UPGRADE_STATUS_ID__BEGIN
#define bcmolt_onu_upgrade_status_id_onu_id BCMOLT_ONU_UPGRADE_STATUS_ID_ONU_ID
#define bcmolt_onu_upgrade_status_id_bytes_transmitted BCMOLT_ONU_UPGRADE_STATUS_ID_BYTES_TRANSMITTED
#define bcmolt_onu_upgrade_status_id_status BCMOLT_ONU_UPGRADE_STATUS_ID_STATUS
#define bcmolt_onu_upgrade_status_id__num_of BCMOLT_ONU_UPGRADE_STATUS_ID__NUM_OF
#define bcmolt_onu_upgrade_status_id_all_properties 0xFF
#define bcmolt_onu_upgrade_status_id_full_mask 0x7

} bcmolt_onu_upgrade_status_id;

/** Identifiers for all fields in a 'operation_control'. */
typedef enum
{
    BCMOLT_OPERATION_CONTROL_ID__BEGIN = 0,
    BCMOLT_OPERATION_CONTROL_ID_RE = 0, /**< RE flag. */
    BCMOLT_OPERATION_CONTROL_ID_ODN_CLASS = 1, /**< ODN Class. */
    BCMOLT_OPERATION_CONTROL_ID_DS_FEC_MODE = 2, /**< DS FEC mode. */
    BCMOLT_OPERATION_CONTROL_ID_PROTOCOL = 3, /**< Protocol. */
    BCMOLT_OPERATION_CONTROL_ID_DS_LINK_TYPE = 4, /**< DS link type. */
    BCMOLT_OPERATION_CONTROL_ID_PON_ID = 5, /**< PON ID. */
    BCMOLT_OPERATION_CONTROL_ID_C = 6, /**< C. */
    BCMOLT_OPERATION_CONTROL_ID_TOL = 7, /**< TOL. */
    BCMOLT_OPERATION_CONTROL_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_operation_control_id__begin BCMOLT_OPERATION_CONTROL_ID__BEGIN
#define bcmolt_operation_control_id_re BCMOLT_OPERATION_CONTROL_ID_RE
#define bcmolt_operation_control_id_odn_class BCMOLT_OPERATION_CONTROL_ID_ODN_CLASS
#define bcmolt_operation_control_id_ds_fec_mode BCMOLT_OPERATION_CONTROL_ID_DS_FEC_MODE
#define bcmolt_operation_control_id_protocol BCMOLT_OPERATION_CONTROL_ID_PROTOCOL
#define bcmolt_operation_control_id_ds_link_type BCMOLT_OPERATION_CONTROL_ID_DS_LINK_TYPE
#define bcmolt_operation_control_id_pon_id BCMOLT_OPERATION_CONTROL_ID_PON_ID
#define bcmolt_operation_control_id_c BCMOLT_OPERATION_CONTROL_ID_C
#define bcmolt_operation_control_id_tol BCMOLT_OPERATION_CONTROL_ID_TOL
#define bcmolt_operation_control_id__num_of BCMOLT_OPERATION_CONTROL_ID__NUM_OF
#define bcmolt_operation_control_id_all_properties 0xFF
#define bcmolt_operation_control_id_full_mask 0xFF

} bcmolt_operation_control_id;

/** Identifiers for all fields in a 'pcie_conn_data'. */
typedef enum
{
    BCMOLT_PCIE_CONN_DATA_ID__BEGIN = 0,
    BCMOLT_PCIE_CONN_DATA_ID_HOST_DMA_RX_QUEUE_SIZE = 0, /**< RX queue size of the host DMA. */
    BCMOLT_PCIE_CONN_DATA_ID_HOST_DMA_TX_QUEUE_SIZE = 1, /**< TX queue size of the host DMA. */
    BCMOLT_PCIE_CONN_DATA_ID_MTU = 2, /**< MTU. */
    BCMOLT_PCIE_CONN_DATA_ID_AVS_CONTROL = 3, /**< AVS Control. */
    BCMOLT_PCIE_CONN_DATA_ID_DEBUG_TRACE = 4, /**< Debug trace. */
    BCMOLT_PCIE_CONN_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pcie_conn_data_id__begin BCMOLT_PCIE_CONN_DATA_ID__BEGIN
#define bcmolt_pcie_conn_data_id_host_dma_rx_queue_size BCMOLT_PCIE_CONN_DATA_ID_HOST_DMA_RX_QUEUE_SIZE
#define bcmolt_pcie_conn_data_id_host_dma_tx_queue_size BCMOLT_PCIE_CONN_DATA_ID_HOST_DMA_TX_QUEUE_SIZE
#define bcmolt_pcie_conn_data_id_mtu BCMOLT_PCIE_CONN_DATA_ID_MTU
#define bcmolt_pcie_conn_data_id_avs_control BCMOLT_PCIE_CONN_DATA_ID_AVS_CONTROL
#define bcmolt_pcie_conn_data_id_debug_trace BCMOLT_PCIE_CONN_DATA_ID_DEBUG_TRACE
#define bcmolt_pcie_conn_data_id__num_of BCMOLT_PCIE_CONN_DATA_ID__NUM_OF
#define bcmolt_pcie_conn_data_id_all_properties 0xFF
#define bcmolt_pcie_conn_data_id_full_mask 0x1F

} bcmolt_pcie_conn_data_id;

/** Identifiers for all fields in a 'periodic_ploams'. */
typedef enum
{
    BCMOLT_PERIODIC_PLOAMS_ID__BEGIN = 0,
    BCMOLT_PERIODIC_PLOAMS_ID_CONTROL = 0, /**< Control. */
    BCMOLT_PERIODIC_PLOAMS_ID_INTERVAL_MS = 1, /**< Interval. */
    BCMOLT_PERIODIC_PLOAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_periodic_ploams_id__begin BCMOLT_PERIODIC_PLOAMS_ID__BEGIN
#define bcmolt_periodic_ploams_id_control BCMOLT_PERIODIC_PLOAMS_ID_CONTROL
#define bcmolt_periodic_ploams_id_interval_ms BCMOLT_PERIODIC_PLOAMS_ID_INTERVAL_MS
#define bcmolt_periodic_ploams_id__num_of BCMOLT_PERIODIC_PLOAMS_ID__NUM_OF
#define bcmolt_periodic_ploams_id_all_properties 0xFF
#define bcmolt_periodic_ploams_id_full_mask 0x3

} bcmolt_periodic_ploams_id;

/** Identifiers for all fields in a 'periodic_standby_pon_monitoring'. */
typedef enum
{
    BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID__BEGIN = 0,
    BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID_INTERVAL = 0, /**< interval in ms. */
    BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID_CONTROL = 1, /**< control. */
    BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_periodic_standby_pon_monitoring_id__begin BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID__BEGIN
#define bcmolt_periodic_standby_pon_monitoring_id_interval BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID_INTERVAL
#define bcmolt_periodic_standby_pon_monitoring_id_control BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID_CONTROL
#define bcmolt_periodic_standby_pon_monitoring_id__num_of BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID__NUM_OF
#define bcmolt_periodic_standby_pon_monitoring_id_all_properties 0xFF
#define bcmolt_periodic_standby_pon_monitoring_id_full_mask 0x3

} bcmolt_periodic_standby_pon_monitoring_id;

/** Identifiers for all fields in a 'ploam_filter'. */
typedef enum
{
    BCMOLT_PLOAM_FILTER_ID__BEGIN = 0,
    BCMOLT_PLOAM_FILTER_ID_PLOAM_ID = 0, /**< ploam id. */
    BCMOLT_PLOAM_FILTER_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ploam_filter_id__begin BCMOLT_PLOAM_FILTER_ID__BEGIN
#define bcmolt_ploam_filter_id_ploam_id BCMOLT_PLOAM_FILTER_ID_PLOAM_ID
#define bcmolt_ploam_filter_id__num_of BCMOLT_PLOAM_FILTER_ID__NUM_OF
#define bcmolt_ploam_filter_id_all_properties 0xFF
#define bcmolt_ploam_filter_id_full_mask 0x1

} bcmolt_ploam_filter_id;

/** Identifiers for all fields in a 'ploam_retransmission'. */
typedef enum
{
    BCMOLT_PLOAM_RETRANSMISSION_ID__BEGIN = 0,
    BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_RANGING_TIME = 0, /**< retransmission ranging time. */
    BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_ASSIGN_ALLOC_ID = 1, /**< retransmission assign alloc id. */
    BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_KEY_CONTROL = 2, /**< retransmission key control. */
    BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_REQUEST_REGISTRATION = 3, /**< retransmission request registration. */
    BCMOLT_PLOAM_RETRANSMISSION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ploam_retransmission_id__begin BCMOLT_PLOAM_RETRANSMISSION_ID__BEGIN
#define bcmolt_ploam_retransmission_id_retrans_ranging_time BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_RANGING_TIME
#define bcmolt_ploam_retransmission_id_retrans_assign_alloc_id BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_ASSIGN_ALLOC_ID
#define bcmolt_ploam_retransmission_id_retrans_key_control BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_KEY_CONTROL
#define bcmolt_ploam_retransmission_id_retrans_request_registration BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_REQUEST_REGISTRATION
#define bcmolt_ploam_retransmission_id__num_of BCMOLT_PLOAM_RETRANSMISSION_ID__NUM_OF
#define bcmolt_ploam_retransmission_id_all_properties 0xFF
#define bcmolt_ploam_retransmission_id_full_mask 0xF

} bcmolt_ploam_retransmission_id;

/** Identifiers for all fields in a 'policer_action'. */
typedef enum
{
    BCMOLT_POLICER_ACTION_ID__BEGIN = 1,
    BCMOLT_POLICER_ACTION_ID_STATE = 1, /**< state. */
    BCMOLT_POLICER_ACTION_ID_POLICER_REF = 2, /**< policer ref. */
    BCMOLT_POLICER_ACTION_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_policer_action_id__begin BCMOLT_POLICER_ACTION_ID__BEGIN
#define bcmolt_policer_action_id_state BCMOLT_POLICER_ACTION_ID_STATE
#define bcmolt_policer_action_id_policer_ref BCMOLT_POLICER_ACTION_ID_POLICER_REF
#define bcmolt_policer_action_id__num_of BCMOLT_POLICER_ACTION_ID__NUM_OF
#define bcmolt_policer_action_id_all_properties 0xFF
#define bcmolt_policer_action_id_full_mask 0x6

} bcmolt_policer_action_id;

/** Identifiers for all fields in a 'policer_ref'. */
typedef enum
{
    BCMOLT_POLICER_REF_ID__BEGIN = 0,
    BCMOLT_POLICER_REF_ID_TYPE = 0, /**< type. */
    BCMOLT_POLICER_REF_ID_ID = 1, /**< id. */
    BCMOLT_POLICER_REF_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_policer_ref_id__begin BCMOLT_POLICER_REF_ID__BEGIN
#define bcmolt_policer_ref_id_type BCMOLT_POLICER_REF_ID_TYPE
#define bcmolt_policer_ref_id_id BCMOLT_POLICER_REF_ID_ID
#define bcmolt_policer_ref_id__num_of BCMOLT_POLICER_REF_ID__NUM_OF
#define bcmolt_policer_ref_id_all_properties 0xFF
#define bcmolt_policer_ref_id_full_mask 0x3

} bcmolt_policer_ref_id;

/** Identifiers for all fields in a 'pon_alloc_sla'. */
typedef enum
{
    BCMOLT_PON_ALLOC_SLA_ID__BEGIN = 0,
    BCMOLT_PON_ALLOC_SLA_ID_CBR_RT_BW = 0, /**< CBR RT BW in bytes per second. */
    BCMOLT_PON_ALLOC_SLA_ID_CBR_NRT_BW = 1, /**< CBR NRT BW in bytes per second. */
    BCMOLT_PON_ALLOC_SLA_ID_GUARANTEED_BW = 2, /**< Guaranteed BW in bytes per second. */
    BCMOLT_PON_ALLOC_SLA_ID_MAXIMUM_BW = 3, /**< Maximum BW in bytes per second. */
    BCMOLT_PON_ALLOC_SLA_ID_ADDITIONAL_BW_ELIGIBILITY = 4, /**< Additional BW eligibility. */
    BCMOLT_PON_ALLOC_SLA_ID_CBR_RT_COMPENSATION = 5, /**< CBR-rt compensation. */
    BCMOLT_PON_ALLOC_SLA_ID_CBR_RT_AP_INDEX = 6, /**< CBR-rt allocation profile index. */
    BCMOLT_PON_ALLOC_SLA_ID_CBR_NRT_AP_INDEX = 7, /**< CBR-nrt allocation profile index. */
    BCMOLT_PON_ALLOC_SLA_ID_ALLOC_TYPE = 8, /**< Alloc Type. */
    BCMOLT_PON_ALLOC_SLA_ID_WEIGHT = 9, /**< Weight. */
    BCMOLT_PON_ALLOC_SLA_ID_PRIORITY = 10, /**< Priority. */
    BCMOLT_PON_ALLOC_SLA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_alloc_sla_id__begin BCMOLT_PON_ALLOC_SLA_ID__BEGIN
#define bcmolt_pon_alloc_sla_id_cbr_rt_bw BCMOLT_PON_ALLOC_SLA_ID_CBR_RT_BW
#define bcmolt_pon_alloc_sla_id_cbr_nrt_bw BCMOLT_PON_ALLOC_SLA_ID_CBR_NRT_BW
#define bcmolt_pon_alloc_sla_id_guaranteed_bw BCMOLT_PON_ALLOC_SLA_ID_GUARANTEED_BW
#define bcmolt_pon_alloc_sla_id_maximum_bw BCMOLT_PON_ALLOC_SLA_ID_MAXIMUM_BW
#define bcmolt_pon_alloc_sla_id_additional_bw_eligibility BCMOLT_PON_ALLOC_SLA_ID_ADDITIONAL_BW_ELIGIBILITY
#define bcmolt_pon_alloc_sla_id_cbr_rt_compensation BCMOLT_PON_ALLOC_SLA_ID_CBR_RT_COMPENSATION
#define bcmolt_pon_alloc_sla_id_cbr_rt_ap_index BCMOLT_PON_ALLOC_SLA_ID_CBR_RT_AP_INDEX
#define bcmolt_pon_alloc_sla_id_cbr_nrt_ap_index BCMOLT_PON_ALLOC_SLA_ID_CBR_NRT_AP_INDEX
#define bcmolt_pon_alloc_sla_id_alloc_type BCMOLT_PON_ALLOC_SLA_ID_ALLOC_TYPE
#define bcmolt_pon_alloc_sla_id_weight BCMOLT_PON_ALLOC_SLA_ID_WEIGHT
#define bcmolt_pon_alloc_sla_id_priority BCMOLT_PON_ALLOC_SLA_ID_PRIORITY
#define bcmolt_pon_alloc_sla_id__num_of BCMOLT_PON_ALLOC_SLA_ID__NUM_OF
#define bcmolt_pon_alloc_sla_id_all_properties 0xFF
#define bcmolt_pon_alloc_sla_id_full_mask 0x7FF

} bcmolt_pon_alloc_sla_id;

/** Identifiers for all fields in a 'pon_available_bandwidth'. */
typedef enum
{
    BCMOLT_PON_AVAILABLE_BANDWIDTH_ID__BEGIN = 0,
    BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_CBR_BW = 0, /**< CBR BW. */
    BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_TOTAL_BW = 1, /**< Total BW. */
    BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_NEXT_ONU_TOTAL_BW = 2, /**< Next ONU Total BW. */
    BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_GROUP_TOTAL_BW = 3, /**< Group Total BW. */
    BCMOLT_PON_AVAILABLE_BANDWIDTH_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_available_bandwidth_id__begin BCMOLT_PON_AVAILABLE_BANDWIDTH_ID__BEGIN
#define bcmolt_pon_available_bandwidth_id_cbr_bw BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_CBR_BW
#define bcmolt_pon_available_bandwidth_id_total_bw BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_TOTAL_BW
#define bcmolt_pon_available_bandwidth_id_next_onu_total_bw BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_NEXT_ONU_TOTAL_BW
#define bcmolt_pon_available_bandwidth_id_group_total_bw BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_GROUP_TOTAL_BW
#define bcmolt_pon_available_bandwidth_id__num_of BCMOLT_PON_AVAILABLE_BANDWIDTH_ID__NUM_OF
#define bcmolt_pon_available_bandwidth_id_all_properties 0xFF
#define bcmolt_pon_available_bandwidth_id_full_mask 0xF

} bcmolt_pon_available_bandwidth_id;

/** Identifiers for all fields in a 'pon_distance'. */
typedef enum
{
    BCMOLT_PON_DISTANCE_ID__BEGIN = 0,
    BCMOLT_PON_DISTANCE_ID_MAX_LOG_DISTANCE = 0, /**< Maximum logical distance in km. */
    BCMOLT_PON_DISTANCE_ID_MAX_DIFF_REACH = 1, /**< Maximum differential reach in km. */
    BCMOLT_PON_DISTANCE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_distance_id__begin BCMOLT_PON_DISTANCE_ID__BEGIN
#define bcmolt_pon_distance_id_max_log_distance BCMOLT_PON_DISTANCE_ID_MAX_LOG_DISTANCE
#define bcmolt_pon_distance_id_max_diff_reach BCMOLT_PON_DISTANCE_ID_MAX_DIFF_REACH
#define bcmolt_pon_distance_id__num_of BCMOLT_PON_DISTANCE_ID__NUM_OF
#define bcmolt_pon_distance_id_all_properties 0xFF
#define bcmolt_pon_distance_id_full_mask 0x3

} bcmolt_pon_distance_id;

/** Identifiers for all fields in a 'pon_drift_control'. */
typedef enum
{
    BCMOLT_PON_DRIFT_CONTROL_ID__BEGIN = 0,
    BCMOLT_PON_DRIFT_CONTROL_ID_DRIFT_INTERVAL = 0, /**< Drift interval in ms. */
    BCMOLT_PON_DRIFT_CONTROL_ID_DRIFT_LIMIT = 1, /**< Drift limit. */
    BCMOLT_PON_DRIFT_CONTROL_ID_TRANSMISSION_CONTROL_LIMIT = 2, /**< Transmission control limit. */
    BCMOLT_PON_DRIFT_CONTROL_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_drift_control_id__begin BCMOLT_PON_DRIFT_CONTROL_ID__BEGIN
#define bcmolt_pon_drift_control_id_drift_interval BCMOLT_PON_DRIFT_CONTROL_ID_DRIFT_INTERVAL
#define bcmolt_pon_drift_control_id_drift_limit BCMOLT_PON_DRIFT_CONTROL_ID_DRIFT_LIMIT
#define bcmolt_pon_drift_control_id_transmission_control_limit BCMOLT_PON_DRIFT_CONTROL_ID_TRANSMISSION_CONTROL_LIMIT
#define bcmolt_pon_drift_control_id__num_of BCMOLT_PON_DRIFT_CONTROL_ID__NUM_OF
#define bcmolt_pon_drift_control_id_all_properties 0xFF
#define bcmolt_pon_drift_control_id_full_mask 0x7

} bcmolt_pon_drift_control_id;

/** Identifiers for all fields in a 'pon_id'. */
typedef enum
{
    BCMOLT_PON_ID_ID__BEGIN = 0,
    BCMOLT_PON_ID_ID_ADMINISTRATIVE_LABEL = 0, /**< Administrative label. */
    BCMOLT_PON_ID_ID_DWLCH_ID = 1, /**< DWLCH ID. */
    BCMOLT_PON_ID_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_id_id__begin BCMOLT_PON_ID_ID__BEGIN
#define bcmolt_pon_id_id_administrative_label BCMOLT_PON_ID_ID_ADMINISTRATIVE_LABEL
#define bcmolt_pon_id_id_dwlch_id BCMOLT_PON_ID_ID_DWLCH_ID
#define bcmolt_pon_id_id__num_of BCMOLT_PON_ID_ID__NUM_OF
#define bcmolt_pon_id_id_all_properties 0xFF
#define bcmolt_pon_id_id_full_mask 0x3

} bcmolt_pon_id_id;

/** Identifiers for all fields in a 'pon_onu_upgrade_status'. */
typedef enum
{
    BCMOLT_PON_ONU_UPGRADE_STATUS_ID__BEGIN = 0,
    BCMOLT_PON_ONU_UPGRADE_STATUS_ID_OVERALL_STATUS = 0, /**< Overall status. */
    BCMOLT_PON_ONU_UPGRADE_STATUS_ID_FILE_SIZE_IN_BYTES = 1, /**< File size in bytes. */
    BCMOLT_PON_ONU_UPGRADE_STATUS_ID_ONU_STATUS = 2, /**< ONU status. */
    BCMOLT_PON_ONU_UPGRADE_STATUS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_onu_upgrade_status_id__begin BCMOLT_PON_ONU_UPGRADE_STATUS_ID__BEGIN
#define bcmolt_pon_onu_upgrade_status_id_overall_status BCMOLT_PON_ONU_UPGRADE_STATUS_ID_OVERALL_STATUS
#define bcmolt_pon_onu_upgrade_status_id_file_size_in_bytes BCMOLT_PON_ONU_UPGRADE_STATUS_ID_FILE_SIZE_IN_BYTES
#define bcmolt_pon_onu_upgrade_status_id_onu_status BCMOLT_PON_ONU_UPGRADE_STATUS_ID_ONU_STATUS
#define bcmolt_pon_onu_upgrade_status_id__num_of BCMOLT_PON_ONU_UPGRADE_STATUS_ID__NUM_OF
#define bcmolt_pon_onu_upgrade_status_id_all_properties 0xFF
#define bcmolt_pon_onu_upgrade_status_id_full_mask 0x7

} bcmolt_pon_onu_upgrade_status_id;

/** Identifiers for all fields in a 'pon_power_level'. */
typedef enum
{
    BCMOLT_PON_POWER_LEVEL_ID__BEGIN = 0,
    BCMOLT_PON_POWER_LEVEL_ID_PLS_MAXIMUM_ALLOCATION_SIZE = 0, /**< PLS maximum allocation size in bytes. */
    BCMOLT_PON_POWER_LEVEL_ID_MODE = 1, /**< mode. */
    BCMOLT_PON_POWER_LEVEL_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_power_level_id__begin BCMOLT_PON_POWER_LEVEL_ID__BEGIN
#define bcmolt_pon_power_level_id_pls_maximum_allocation_size BCMOLT_PON_POWER_LEVEL_ID_PLS_MAXIMUM_ALLOCATION_SIZE
#define bcmolt_pon_power_level_id_mode BCMOLT_PON_POWER_LEVEL_ID_MODE
#define bcmolt_pon_power_level_id__num_of BCMOLT_PON_POWER_LEVEL_ID__NUM_OF
#define bcmolt_pon_power_level_id_all_properties 0xFF
#define bcmolt_pon_power_level_id_full_mask 0x3

} bcmolt_pon_power_level_id;

/** Identifiers for all fields in a 'power_consumption_channel_report'. */
typedef enum
{
    BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID__BEGIN = 0,
    BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID_DS_WAVELENGTH_CHANNEL_ID = 0, /**< DS wavelength channel ID. */
    BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID_US_WAVELENGTH_CHANNEL_ID = 1, /**< US wavelength channel id. */
    BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID_POWER_CONSUMPTION = 2, /**< Power consumption. */
    BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_power_consumption_channel_report_id__begin BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID__BEGIN
#define bcmolt_power_consumption_channel_report_id_ds_wavelength_channel_id BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID_DS_WAVELENGTH_CHANNEL_ID
#define bcmolt_power_consumption_channel_report_id_us_wavelength_channel_id BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID_US_WAVELENGTH_CHANNEL_ID
#define bcmolt_power_consumption_channel_report_id_power_consumption BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID_POWER_CONSUMPTION
#define bcmolt_power_consumption_channel_report_id__num_of BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID__NUM_OF
#define bcmolt_power_consumption_channel_report_id_all_properties 0xFF
#define bcmolt_power_consumption_channel_report_id_full_mask 0x7

} bcmolt_power_consumption_channel_report_id;

/** Identifiers for all fields in a 'prbs_checker_config'. */
typedef enum
{
    BCMOLT_PRBS_CHECKER_CONFIG_ID__BEGIN = 0,
    BCMOLT_PRBS_CHECKER_CONFIG_ID_POLYNOM = 0, /**< polynom. */
    BCMOLT_PRBS_CHECKER_CONFIG_ID_MODE = 1, /**< mode. */
    BCMOLT_PRBS_CHECKER_CONFIG_ID_DATA_INVERT = 2, /**< data invert. */
    BCMOLT_PRBS_CHECKER_CONFIG_ID_CONTROL = 3, /**< control. */
    BCMOLT_PRBS_CHECKER_CONFIG_ID_IS_TDMR_XGS = 4, /**< either XGS(1) or XGPON(0) will be test. */
    BCMOLT_PRBS_CHECKER_CONFIG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_prbs_checker_config_id__begin BCMOLT_PRBS_CHECKER_CONFIG_ID__BEGIN
#define bcmolt_prbs_checker_config_id_polynom BCMOLT_PRBS_CHECKER_CONFIG_ID_POLYNOM
#define bcmolt_prbs_checker_config_id_mode BCMOLT_PRBS_CHECKER_CONFIG_ID_MODE
#define bcmolt_prbs_checker_config_id_data_invert BCMOLT_PRBS_CHECKER_CONFIG_ID_DATA_INVERT
#define bcmolt_prbs_checker_config_id_control BCMOLT_PRBS_CHECKER_CONFIG_ID_CONTROL
#define bcmolt_prbs_checker_config_id_is_tdmr_xgs BCMOLT_PRBS_CHECKER_CONFIG_ID_IS_TDMR_XGS
#define bcmolt_prbs_checker_config_id__num_of BCMOLT_PRBS_CHECKER_CONFIG_ID__NUM_OF
#define bcmolt_prbs_checker_config_id_all_properties 0xFF
#define bcmolt_prbs_checker_config_id_full_mask 0x1F

} bcmolt_prbs_checker_config_id;

/** Identifiers for all fields in a 'prbs_generator_config'. */
typedef enum
{
    BCMOLT_PRBS_GENERATOR_CONFIG_ID__BEGIN = 0,
    BCMOLT_PRBS_GENERATOR_CONFIG_ID_POLYNOM = 0, /**< polynom. */
    BCMOLT_PRBS_GENERATOR_CONFIG_ID_ERROR_INSERT = 1, /**< error insert. */
    BCMOLT_PRBS_GENERATOR_CONFIG_ID_INVERT = 2, /**< invert. */
    BCMOLT_PRBS_GENERATOR_CONFIG_ID_CONTROL = 3, /**< control. */
    BCMOLT_PRBS_GENERATOR_CONFIG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_prbs_generator_config_id__begin BCMOLT_PRBS_GENERATOR_CONFIG_ID__BEGIN
#define bcmolt_prbs_generator_config_id_polynom BCMOLT_PRBS_GENERATOR_CONFIG_ID_POLYNOM
#define bcmolt_prbs_generator_config_id_error_insert BCMOLT_PRBS_GENERATOR_CONFIG_ID_ERROR_INSERT
#define bcmolt_prbs_generator_config_id_invert BCMOLT_PRBS_GENERATOR_CONFIG_ID_INVERT
#define bcmolt_prbs_generator_config_id_control BCMOLT_PRBS_GENERATOR_CONFIG_ID_CONTROL
#define bcmolt_prbs_generator_config_id__num_of BCMOLT_PRBS_GENERATOR_CONFIG_ID__NUM_OF
#define bcmolt_prbs_generator_config_id_all_properties 0xFF
#define bcmolt_prbs_generator_config_id_full_mask 0xF

} bcmolt_prbs_generator_config_id;

/** Identifiers for all fields in a 'prbs_status'. */
typedef enum
{
    BCMOLT_PRBS_STATUS_ID__BEGIN = 0,
    BCMOLT_PRBS_STATUS_ID_LOCK_STATE = 0, /**< Lock State. */
    BCMOLT_PRBS_STATUS_ID_ERROR_COUNTS = 1, /**< Error Counts. */
    BCMOLT_PRBS_STATUS_ID_LOSS_SYNC = 2, /**< Loss Sync. */
    BCMOLT_PRBS_STATUS_ID_BER = 3, /**< Bit Error rate. */
    BCMOLT_PRBS_STATUS_ID_TEST_STATUS = 4, /**< Test Run Status (Continue/Done  when reached maximal value of Error counts). */
    BCMOLT_PRBS_STATUS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_prbs_status_id__begin BCMOLT_PRBS_STATUS_ID__BEGIN
#define bcmolt_prbs_status_id_lock_state BCMOLT_PRBS_STATUS_ID_LOCK_STATE
#define bcmolt_prbs_status_id_error_counts BCMOLT_PRBS_STATUS_ID_ERROR_COUNTS
#define bcmolt_prbs_status_id_loss_sync BCMOLT_PRBS_STATUS_ID_LOSS_SYNC
#define bcmolt_prbs_status_id_ber BCMOLT_PRBS_STATUS_ID_BER
#define bcmolt_prbs_status_id_test_status BCMOLT_PRBS_STATUS_ID_TEST_STATUS
#define bcmolt_prbs_status_id__num_of BCMOLT_PRBS_STATUS_ID__NUM_OF
#define bcmolt_prbs_status_id_all_properties 0xFF
#define bcmolt_prbs_status_id_full_mask 0x1F

} bcmolt_prbs_status_id;

/** Identifiers for all fields in a 'protection_type'. */
typedef enum
{
    BCMOLT_PROTECTION_TYPE_ID__BEGIN = 0,
    BCMOLT_PROTECTION_TYPE_ID_MODE = 0, /**< Mode. */
    BCMOLT_PROTECTION_TYPE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_protection_type_id__begin BCMOLT_PROTECTION_TYPE_ID__BEGIN
#define bcmolt_protection_type_id_mode BCMOLT_PROTECTION_TYPE_ID_MODE
#define bcmolt_protection_type_id__num_of BCMOLT_PROTECTION_TYPE_ID__NUM_OF
#define bcmolt_protection_type_id_all_properties 0xFF
#define bcmolt_protection_type_id_full_mask 0x1

} bcmolt_protection_type_id;

/** Identifiers for all fields in a 'remote_mep'. */
typedef enum
{
    BCMOLT_REMOTE_MEP_ID__BEGIN = 0,
    BCMOLT_REMOTE_MEP_ID_ID = 0, /**< id. */
    BCMOLT_REMOTE_MEP_ID_LOC_CLEAR_THRESHOLD = 5, /**< loc clear threshold. */
    BCMOLT_REMOTE_MEP_ID_STATE = 6, /**< state. */
    BCMOLT_REMOTE_MEP_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_remote_mep_id__begin BCMOLT_REMOTE_MEP_ID__BEGIN
#define bcmolt_remote_mep_id_id BCMOLT_REMOTE_MEP_ID_ID
#define bcmolt_remote_mep_id_loc_clear_threshold BCMOLT_REMOTE_MEP_ID_LOC_CLEAR_THRESHOLD
#define bcmolt_remote_mep_id_state BCMOLT_REMOTE_MEP_ID_STATE
#define bcmolt_remote_mep_id__num_of BCMOLT_REMOTE_MEP_ID__NUM_OF
#define bcmolt_remote_mep_id_all_properties 0xFF
#define bcmolt_remote_mep_id_full_mask 0x61

} bcmolt_remote_mep_id;

/** Identifiers for all fields in a 'request_registration_status'. */
typedef enum
{
    BCMOLT_REQUEST_REGISTRATION_STATUS_ID__BEGIN = 0,
    BCMOLT_REQUEST_REGISTRATION_STATUS_ID_REQUEST_REGISTRATION_STATE = 0, /**< request registration state. */
    BCMOLT_REQUEST_REGISTRATION_STATUS_ID_SMA_FLAG = 1, /**< sma flag. */
    BCMOLT_REQUEST_REGISTRATION_STATUS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_request_registration_status_id__begin BCMOLT_REQUEST_REGISTRATION_STATUS_ID__BEGIN
#define bcmolt_request_registration_status_id_request_registration_state BCMOLT_REQUEST_REGISTRATION_STATUS_ID_REQUEST_REGISTRATION_STATE
#define bcmolt_request_registration_status_id_sma_flag BCMOLT_REQUEST_REGISTRATION_STATUS_ID_SMA_FLAG
#define bcmolt_request_registration_status_id__num_of BCMOLT_REQUEST_REGISTRATION_STATUS_ID__NUM_OF
#define bcmolt_request_registration_status_id_all_properties 0xFF
#define bcmolt_request_registration_status_id_full_mask 0x3

} bcmolt_request_registration_status_id;

/** Identifiers for all fields in a 'rssi_measurement_result'. */
typedef enum
{
    BCMOLT_RSSI_MEASUREMENT_RESULT_ID__BEGIN = 0,
    BCMOLT_RSSI_MEASUREMENT_RESULT_ID_RSSI_DONE = 0, /**< rssi measurement done. */
    BCMOLT_RSSI_MEASUREMENT_RESULT_ID_ERROR = 1, /**< error. */
    BCMOLT_RSSI_MEASUREMENT_RESULT_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_rssi_measurement_result_id__begin BCMOLT_RSSI_MEASUREMENT_RESULT_ID__BEGIN
#define bcmolt_rssi_measurement_result_id_rssi_done BCMOLT_RSSI_MEASUREMENT_RESULT_ID_RSSI_DONE
#define bcmolt_rssi_measurement_result_id_error BCMOLT_RSSI_MEASUREMENT_RESULT_ID_ERROR
#define bcmolt_rssi_measurement_result_id__num_of BCMOLT_RSSI_MEASUREMENT_RESULT_ID__NUM_OF
#define bcmolt_rssi_measurement_result_id_all_properties 0xFF
#define bcmolt_rssi_measurement_result_id_full_mask 0x3

} bcmolt_rssi_measurement_result_id;

/** Identifiers for all fields in a 'serial_number'. */
typedef enum
{
    BCMOLT_SERIAL_NUMBER_ID__BEGIN = 0,
    BCMOLT_SERIAL_NUMBER_ID_VENDOR_ID = 0, /**< vendor id. */
    BCMOLT_SERIAL_NUMBER_ID_VENDOR_SPECIFIC = 1, /**< vendor specific. */
    BCMOLT_SERIAL_NUMBER_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_serial_number_id__begin BCMOLT_SERIAL_NUMBER_ID__BEGIN
#define bcmolt_serial_number_id_vendor_id BCMOLT_SERIAL_NUMBER_ID_VENDOR_ID
#define bcmolt_serial_number_id_vendor_specific BCMOLT_SERIAL_NUMBER_ID_VENDOR_SPECIFIC
#define bcmolt_serial_number_id__num_of BCMOLT_SERIAL_NUMBER_ID__NUM_OF
#define bcmolt_serial_number_id_all_properties 0xFF
#define bcmolt_serial_number_id_full_mask 0x3

} bcmolt_serial_number_id;

/** Identifiers for all fields in a 'service_discovery'. */
typedef enum
{
    BCMOLT_SERVICE_DISCOVERY_ID__BEGIN = 0,
    BCMOLT_SERVICE_DISCOVERY_ID_INTERVAL = 0, /**< interval in ms. */
    BCMOLT_SERVICE_DISCOVERY_ID_CONTROL = 1, /**< control. */
    BCMOLT_SERVICE_DISCOVERY_ID_ONU_POST_DISCOVERY_MODE = 2, /**< ONU post discovery mode. */
    BCMOLT_SERVICE_DISCOVERY_ID_BURST_PROFILE = 3, /**< burst profile. */
    BCMOLT_SERVICE_DISCOVERY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_service_discovery_id__begin BCMOLT_SERVICE_DISCOVERY_ID__BEGIN
#define bcmolt_service_discovery_id_interval BCMOLT_SERVICE_DISCOVERY_ID_INTERVAL
#define bcmolt_service_discovery_id_control BCMOLT_SERVICE_DISCOVERY_ID_CONTROL
#define bcmolt_service_discovery_id_onu_post_discovery_mode BCMOLT_SERVICE_DISCOVERY_ID_ONU_POST_DISCOVERY_MODE
#define bcmolt_service_discovery_id_burst_profile BCMOLT_SERVICE_DISCOVERY_ID_BURST_PROFILE
#define bcmolt_service_discovery_id__num_of BCMOLT_SERVICE_DISCOVERY_ID__NUM_OF
#define bcmolt_service_discovery_id_all_properties 0xFF
#define bcmolt_service_discovery_id_full_mask 0xF

} bcmolt_service_discovery_id;

/** Identifiers for all fields in a 'stat_alarm_config'. */
typedef enum
{
    BCMOLT_STAT_ALARM_CONFIG_ID__BEGIN = 0,
    BCMOLT_STAT_ALARM_CONFIG_ID_TRIGGER = 0, /**< Trigger. */
    BCMOLT_STAT_ALARM_CONFIG_ID_SOAK = 1, /**< Soak. */
    BCMOLT_STAT_ALARM_CONFIG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_stat_alarm_config_id__begin BCMOLT_STAT_ALARM_CONFIG_ID__BEGIN
#define bcmolt_stat_alarm_config_id_trigger BCMOLT_STAT_ALARM_CONFIG_ID_TRIGGER
#define bcmolt_stat_alarm_config_id_soak BCMOLT_STAT_ALARM_CONFIG_ID_SOAK
#define bcmolt_stat_alarm_config_id__num_of BCMOLT_STAT_ALARM_CONFIG_ID__NUM_OF
#define bcmolt_stat_alarm_config_id_all_properties 0xFF
#define bcmolt_stat_alarm_config_id_full_mask 0x3

} bcmolt_stat_alarm_config_id;

/** Identifiers for all fields in a 'stat_alarm_soak_config'. */
typedef enum
{
    BCMOLT_STAT_ALARM_SOAK_CONFIG_ID__BEGIN = 0,
    BCMOLT_STAT_ALARM_SOAK_CONFIG_ID_ACTIVE_SOAK_TIME = 0, /**< Active Soak Time in seconds. */
    BCMOLT_STAT_ALARM_SOAK_CONFIG_ID_CLEAR_SOAK_TIME = 1, /**< Clear Soak Time in seconds. */
    BCMOLT_STAT_ALARM_SOAK_CONFIG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_stat_alarm_soak_config_id__begin BCMOLT_STAT_ALARM_SOAK_CONFIG_ID__BEGIN
#define bcmolt_stat_alarm_soak_config_id_active_soak_time BCMOLT_STAT_ALARM_SOAK_CONFIG_ID_ACTIVE_SOAK_TIME
#define bcmolt_stat_alarm_soak_config_id_clear_soak_time BCMOLT_STAT_ALARM_SOAK_CONFIG_ID_CLEAR_SOAK_TIME
#define bcmolt_stat_alarm_soak_config_id__num_of BCMOLT_STAT_ALARM_SOAK_CONFIG_ID__NUM_OF
#define bcmolt_stat_alarm_soak_config_id_all_properties 0xFF
#define bcmolt_stat_alarm_soak_config_id_full_mask 0x3

} bcmolt_stat_alarm_soak_config_id;

/** Identifiers for all fields in a 'stat_alarm_trigger_config'. */
typedef enum
{
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_ID__BEGIN = 0,
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_ID_TYPE = 0, /**< type. */
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_stat_alarm_trigger_config_id__begin BCMOLT_STAT_ALARM_TRIGGER_CONFIG_ID__BEGIN
#define bcmolt_stat_alarm_trigger_config_id_type BCMOLT_STAT_ALARM_TRIGGER_CONFIG_ID_TYPE
#define bcmolt_stat_alarm_trigger_config_id__num_of BCMOLT_STAT_ALARM_TRIGGER_CONFIG_ID__NUM_OF
#define bcmolt_stat_alarm_trigger_config_id_all_properties 0xFF
#define bcmolt_stat_alarm_trigger_config_id_full_mask 0x1

} bcmolt_stat_alarm_trigger_config_id;

/** Identifiers for all fields in a 'stat_alarm_trigger_config_rate_threshold'. */
typedef enum
{
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID__BEGIN = 0,
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID_RISING = 0, /**< Rising Threshold. */
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID_FALLING = 1, /**< Falling Threshold. */
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_stat_alarm_trigger_config_rate_threshold_id__begin BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID__BEGIN
#define bcmolt_stat_alarm_trigger_config_rate_threshold_id_rising BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID_RISING
#define bcmolt_stat_alarm_trigger_config_rate_threshold_id_falling BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID_FALLING
#define bcmolt_stat_alarm_trigger_config_rate_threshold_id__num_of BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID__NUM_OF
#define bcmolt_stat_alarm_trigger_config_rate_threshold_id_all_properties 0xFF
#define bcmolt_stat_alarm_trigger_config_rate_threshold_id_full_mask 0x3

} bcmolt_stat_alarm_trigger_config_rate_threshold_id;

/** Identifiers for all fields in a 'stat_alarm_trigger_config_rate_range'. */
typedef enum
{
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID__BEGIN = 0,
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID_UPPER = 0, /**< Range Upper Bound. */
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID_LOWER = 1, /**< Range Lower Bound. */
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_stat_alarm_trigger_config_rate_range_id__begin BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID__BEGIN
#define bcmolt_stat_alarm_trigger_config_rate_range_id_upper BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID_UPPER
#define bcmolt_stat_alarm_trigger_config_rate_range_id_lower BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID_LOWER
#define bcmolt_stat_alarm_trigger_config_rate_range_id__num_of BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID__NUM_OF
#define bcmolt_stat_alarm_trigger_config_rate_range_id_all_properties 0xFF
#define bcmolt_stat_alarm_trigger_config_rate_range_id_full_mask 0x3

} bcmolt_stat_alarm_trigger_config_rate_range_id;

/** Identifiers for all fields in a 'stat_alarm_trigger_config_value_threshold'. */
typedef enum
{
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_VALUE_THRESHOLD_ID__BEGIN = 0,
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_VALUE_THRESHOLD_ID_LIMIT = 0, /**< Limit. */
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_VALUE_THRESHOLD_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_stat_alarm_trigger_config_value_threshold_id__begin BCMOLT_STAT_ALARM_TRIGGER_CONFIG_VALUE_THRESHOLD_ID__BEGIN
#define bcmolt_stat_alarm_trigger_config_value_threshold_id_limit BCMOLT_STAT_ALARM_TRIGGER_CONFIG_VALUE_THRESHOLD_ID_LIMIT
#define bcmolt_stat_alarm_trigger_config_value_threshold_id__num_of BCMOLT_STAT_ALARM_TRIGGER_CONFIG_VALUE_THRESHOLD_ID__NUM_OF
#define bcmolt_stat_alarm_trigger_config_value_threshold_id_all_properties 0xFF
#define bcmolt_stat_alarm_trigger_config_value_threshold_id_full_mask 0x1

} bcmolt_stat_alarm_trigger_config_value_threshold_id;

/** Identifiers for all fields in a 'stat_alarm_trigger_config_none'. */
typedef enum
{
    BCMOLT_STAT_ALARM_TRIGGER_CONFIG_NONE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_stat_alarm_trigger_config_none_id__num_of BCMOLT_STAT_ALARM_TRIGGER_CONFIG_NONE_ID__NUM_OF
#define bcmolt_stat_alarm_trigger_config_none_id_all_properties 0xFF
#define bcmolt_stat_alarm_trigger_config_none_id_full_mask 0x0

} bcmolt_stat_alarm_trigger_config_none_id;

/** Identifiers for all fields in a 'sw_error'. */
typedef enum
{
    BCMOLT_SW_ERROR_ID__BEGIN = 0,
    BCMOLT_SW_ERROR_ID_FIRST_ERROR_TIME_US = 0, /**< First Error Time (us). */
    BCMOLT_SW_ERROR_ID_LAST_ERROR_TIME_US = 1, /**< Last Error Time (us). */
    BCMOLT_SW_ERROR_ID_LINE_NUMBER = 2, /**< Line Number. */
    BCMOLT_SW_ERROR_ID_ERROR_COUNTER = 3, /**< Error Counter. */
    BCMOLT_SW_ERROR_ID_INSTANCE = 4, /**< Instance. */
    BCMOLT_SW_ERROR_ID_FILENAME = 5, /**< Filename. */
    BCMOLT_SW_ERROR_ID_TASK_NAME = 6, /**< Task Name. */
    BCMOLT_SW_ERROR_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_sw_error_id__begin BCMOLT_SW_ERROR_ID__BEGIN
#define bcmolt_sw_error_id_first_error_time_us BCMOLT_SW_ERROR_ID_FIRST_ERROR_TIME_US
#define bcmolt_sw_error_id_last_error_time_us BCMOLT_SW_ERROR_ID_LAST_ERROR_TIME_US
#define bcmolt_sw_error_id_line_number BCMOLT_SW_ERROR_ID_LINE_NUMBER
#define bcmolt_sw_error_id_error_counter BCMOLT_SW_ERROR_ID_ERROR_COUNTER
#define bcmolt_sw_error_id_instance BCMOLT_SW_ERROR_ID_INSTANCE
#define bcmolt_sw_error_id_filename BCMOLT_SW_ERROR_ID_FILENAME
#define bcmolt_sw_error_id_task_name BCMOLT_SW_ERROR_ID_TASK_NAME
#define bcmolt_sw_error_id__num_of BCMOLT_SW_ERROR_ID__NUM_OF
#define bcmolt_sw_error_id_all_properties 0xFF
#define bcmolt_sw_error_id_full_mask 0x7F

} bcmolt_sw_error_id;

/** Identifiers for all fields in a 'system_profile'. */
typedef enum
{
    BCMOLT_SYSTEM_PROFILE_ID__BEGIN = 0,
    BCMOLT_SYSTEM_PROFILE_ID_NG_2_SYS_ID = 0, /**< NG2SYS ID. */
    BCMOLT_SYSTEM_PROFILE_ID_VERSION = 1, /**< System profile version. */
    BCMOLT_SYSTEM_PROFILE_ID_CHANNEL_SPACING = 2, /**< Channel spacing. */
    BCMOLT_SYSTEM_PROFILE_ID_US_OPERATING_WAVELENGTH_BANDS = 3, /**< Upstream operating wavelength bands. */
    BCMOLT_SYSTEM_PROFILE_ID_US_MSE = 4, /**< Upstream MSE. */
    BCMOLT_SYSTEM_PROFILE_ID_LOOSE_CALIBRATION_BOUND = 5, /**< Loose calibration bound. */
    BCMOLT_SYSTEM_PROFILE_ID_FSR = 6, /**< FSR. */
    BCMOLT_SYSTEM_PROFILE_ID_TWDM_CHANNEL_COUNT = 7, /**< TWDM channel count. */
    BCMOLT_SYSTEM_PROFILE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_system_profile_id__begin BCMOLT_SYSTEM_PROFILE_ID__BEGIN
#define bcmolt_system_profile_id_ng_2_sys_id BCMOLT_SYSTEM_PROFILE_ID_NG_2_SYS_ID
#define bcmolt_system_profile_id_version BCMOLT_SYSTEM_PROFILE_ID_VERSION
#define bcmolt_system_profile_id_channel_spacing BCMOLT_SYSTEM_PROFILE_ID_CHANNEL_SPACING
#define bcmolt_system_profile_id_us_operating_wavelength_bands BCMOLT_SYSTEM_PROFILE_ID_US_OPERATING_WAVELENGTH_BANDS
#define bcmolt_system_profile_id_us_mse BCMOLT_SYSTEM_PROFILE_ID_US_MSE
#define bcmolt_system_profile_id_loose_calibration_bound BCMOLT_SYSTEM_PROFILE_ID_LOOSE_CALIBRATION_BOUND
#define bcmolt_system_profile_id_fsr BCMOLT_SYSTEM_PROFILE_ID_FSR
#define bcmolt_system_profile_id_twdm_channel_count BCMOLT_SYSTEM_PROFILE_ID_TWDM_CHANNEL_COUNT
#define bcmolt_system_profile_id__num_of BCMOLT_SYSTEM_PROFILE_ID__NUM_OF
#define bcmolt_system_profile_id_all_properties 0xFF
#define bcmolt_system_profile_id_full_mask 0xFF

} bcmolt_system_profile_id;

/** Identifiers for all fields in a 'tm_queue_ref'. */
typedef enum
{
    BCMOLT_TM_QUEUE_REF_ID__BEGIN = 0,
    BCMOLT_TM_QUEUE_REF_ID_SCHED_ID = 0, /**< Scheduler ID. */
    BCMOLT_TM_QUEUE_REF_ID_QUEUE_ID = 1, /**< Queue ID. */
    BCMOLT_TM_QUEUE_REF_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_queue_ref_id__begin BCMOLT_TM_QUEUE_REF_ID__BEGIN
#define bcmolt_tm_queue_ref_id_sched_id BCMOLT_TM_QUEUE_REF_ID_SCHED_ID
#define bcmolt_tm_queue_ref_id_queue_id BCMOLT_TM_QUEUE_REF_ID_QUEUE_ID
#define bcmolt_tm_queue_ref_id__num_of BCMOLT_TM_QUEUE_REF_ID__NUM_OF
#define bcmolt_tm_queue_ref_id_all_properties 0xFF
#define bcmolt_tm_queue_ref_id_full_mask 0x3

} bcmolt_tm_queue_ref_id;

/** Identifiers for all fields in a 'tm_sched_attachment_point'. */
typedef enum
{
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_ID__BEGIN = 0,
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_ID_TYPE = 0, /**< type. */
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_sched_attachment_point_id__begin BCMOLT_TM_SCHED_ATTACHMENT_POINT_ID__BEGIN
#define bcmolt_tm_sched_attachment_point_id_type BCMOLT_TM_SCHED_ATTACHMENT_POINT_ID_TYPE
#define bcmolt_tm_sched_attachment_point_id__num_of BCMOLT_TM_SCHED_ATTACHMENT_POINT_ID__NUM_OF
#define bcmolt_tm_sched_attachment_point_id_all_properties 0xFF
#define bcmolt_tm_sched_attachment_point_id_full_mask 0x1

} bcmolt_tm_sched_attachment_point_id;

/** Identifiers for all fields in a 'tm_sched_attachment_point_interface'. */
typedef enum
{
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_INTERFACE_ID__BEGIN = 0,
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_INTERFACE_ID_INTERFACE_REF = 0, /**< interface_ref. */
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_INTERFACE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_sched_attachment_point_interface_id__begin BCMOLT_TM_SCHED_ATTACHMENT_POINT_INTERFACE_ID__BEGIN
#define bcmolt_tm_sched_attachment_point_interface_id_interface_ref BCMOLT_TM_SCHED_ATTACHMENT_POINT_INTERFACE_ID_INTERFACE_REF
#define bcmolt_tm_sched_attachment_point_interface_id__num_of BCMOLT_TM_SCHED_ATTACHMENT_POINT_INTERFACE_ID__NUM_OF
#define bcmolt_tm_sched_attachment_point_interface_id_all_properties 0xFF
#define bcmolt_tm_sched_attachment_point_interface_id_full_mask 0x1

} bcmolt_tm_sched_attachment_point_interface_id;

/** Identifiers for all fields in a 'tm_sched_attachment_point_tm_sched'. */
typedef enum
{
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID__BEGIN = 0,
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID_TM_SCHED_ID = 0, /**< parent tm sched id. */
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID_TM_SCHED_PARAM = 1, /**< TM Sched Param. */
    BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_sched_attachment_point_tm_sched_id__begin BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID__BEGIN
#define bcmolt_tm_sched_attachment_point_tm_sched_id_tm_sched_id BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID_TM_SCHED_ID
#define bcmolt_tm_sched_attachment_point_tm_sched_id_tm_sched_param BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID_TM_SCHED_PARAM
#define bcmolt_tm_sched_attachment_point_tm_sched_id__num_of BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID__NUM_OF
#define bcmolt_tm_sched_attachment_point_tm_sched_id_all_properties 0xFF
#define bcmolt_tm_sched_attachment_point_tm_sched_id_full_mask 0x3

} bcmolt_tm_sched_attachment_point_tm_sched_id;

/** Identifiers for all fields in a 'tm_sched_param'. */
typedef enum
{
    BCMOLT_TM_SCHED_PARAM_ID__BEGIN = 0,
    BCMOLT_TM_SCHED_PARAM_ID_TYPE = 0, /**< Type. */
    BCMOLT_TM_SCHED_PARAM_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_sched_param_id__begin BCMOLT_TM_SCHED_PARAM_ID__BEGIN
#define bcmolt_tm_sched_param_id_type BCMOLT_TM_SCHED_PARAM_ID_TYPE
#define bcmolt_tm_sched_param_id__num_of BCMOLT_TM_SCHED_PARAM_ID__NUM_OF
#define bcmolt_tm_sched_param_id_all_properties 0xFF
#define bcmolt_tm_sched_param_id_full_mask 0x1

} bcmolt_tm_sched_param_id;

/** Identifiers for all fields in a 'tm_sched_param_priority'. */
typedef enum
{
    BCMOLT_TM_SCHED_PARAM_PRIORITY_ID__BEGIN = 2,
    BCMOLT_TM_SCHED_PARAM_PRIORITY_ID_PRIORITY = 2, /**< priority. */
    BCMOLT_TM_SCHED_PARAM_PRIORITY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_sched_param_priority_id__begin BCMOLT_TM_SCHED_PARAM_PRIORITY_ID__BEGIN
#define bcmolt_tm_sched_param_priority_id_priority BCMOLT_TM_SCHED_PARAM_PRIORITY_ID_PRIORITY
#define bcmolt_tm_sched_param_priority_id__num_of BCMOLT_TM_SCHED_PARAM_PRIORITY_ID__NUM_OF
#define bcmolt_tm_sched_param_priority_id_all_properties 0xFF
#define bcmolt_tm_sched_param_priority_id_full_mask 0x4

} bcmolt_tm_sched_param_priority_id;

/** Identifiers for all fields in a 'tm_sched_param_weight'. */
typedef enum
{
    BCMOLT_TM_SCHED_PARAM_WEIGHT_ID__BEGIN = 1,
    BCMOLT_TM_SCHED_PARAM_WEIGHT_ID_WEIGHT = 1, /**< weight. */
    BCMOLT_TM_SCHED_PARAM_WEIGHT_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_sched_param_weight_id__begin BCMOLT_TM_SCHED_PARAM_WEIGHT_ID__BEGIN
#define bcmolt_tm_sched_param_weight_id_weight BCMOLT_TM_SCHED_PARAM_WEIGHT_ID_WEIGHT
#define bcmolt_tm_sched_param_weight_id__num_of BCMOLT_TM_SCHED_PARAM_WEIGHT_ID__NUM_OF
#define bcmolt_tm_sched_param_weight_id_all_properties 0xFF
#define bcmolt_tm_sched_param_weight_id_full_mask 0x2

} bcmolt_tm_sched_param_weight_id;

/** Identifiers for all fields in a 'tm_sched_ref'. */
typedef enum
{
    BCMOLT_TM_SCHED_REF_ID__BEGIN = 1,
    BCMOLT_TM_SCHED_REF_ID_ID = 1, /**< sched_id. */
    BCMOLT_TM_SCHED_REF_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_sched_ref_id__begin BCMOLT_TM_SCHED_REF_ID__BEGIN
#define bcmolt_tm_sched_ref_id_id BCMOLT_TM_SCHED_REF_ID_ID
#define bcmolt_tm_sched_ref_id__num_of BCMOLT_TM_SCHED_REF_ID__NUM_OF
#define bcmolt_tm_sched_ref_id_all_properties 0xFF
#define bcmolt_tm_sched_ref_id_full_mask 0x2

} bcmolt_tm_sched_ref_id;

/** Identifiers for all fields in a 'tm_shaping'. */
typedef enum
{
    BCMOLT_TM_SHAPING_ID__BEGIN = 0,
    BCMOLT_TM_SHAPING_ID_CIR = 0, /**< CIR. */
    BCMOLT_TM_SHAPING_ID_PIR = 1, /**< PIR. */
    BCMOLT_TM_SHAPING_ID_BURST = 2, /**< burst. */
    BCMOLT_TM_SHAPING_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_shaping_id__begin BCMOLT_TM_SHAPING_ID__BEGIN
#define bcmolt_tm_shaping_id_cir BCMOLT_TM_SHAPING_ID_CIR
#define bcmolt_tm_shaping_id_pir BCMOLT_TM_SHAPING_ID_PIR
#define bcmolt_tm_shaping_id_burst BCMOLT_TM_SHAPING_ID_BURST
#define bcmolt_tm_shaping_id__num_of BCMOLT_TM_SHAPING_ID__NUM_OF
#define bcmolt_tm_shaping_id_all_properties 0xFF
#define bcmolt_tm_shaping_id_full_mask 0x7

} bcmolt_tm_shaping_id;

/** Identifiers for all fields in a 'topology'. */
typedef enum
{
    BCMOLT_TOPOLOGY_ID__BEGIN = 0,
    BCMOLT_TOPOLOGY_ID_NUM_SWITCH_PORTS = 0, /**< Number of nni ports on switch device. */
    BCMOLT_TOPOLOGY_ID_TOPOLOGY_MAPS = 1, /**< Topology mappings. */
    BCMOLT_TOPOLOGY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_topology_id__begin BCMOLT_TOPOLOGY_ID__BEGIN
#define bcmolt_topology_id_num_switch_ports BCMOLT_TOPOLOGY_ID_NUM_SWITCH_PORTS
#define bcmolt_topology_id_topology_maps BCMOLT_TOPOLOGY_ID_TOPOLOGY_MAPS
#define bcmolt_topology_id__num_of BCMOLT_TOPOLOGY_ID__NUM_OF
#define bcmolt_topology_id_all_properties 0xFF
#define bcmolt_topology_id_full_mask 0x3

} bcmolt_topology_id;

/** Identifiers for all fields in a 'topology_map'. */
typedef enum
{
    BCMOLT_TOPOLOGY_MAP_ID__BEGIN = 1,
    BCMOLT_TOPOLOGY_MAP_ID_LOCAL_DEVICE_ID = 1, /**< Local MAC device Id in OLT line card. */
    BCMOLT_TOPOLOGY_MAP_ID_OLT_DEVICE_ID = 2, /**< MAC device Id in scope of OLT Instance. */
    BCMOLT_TOPOLOGY_MAP_ID_PHYSICAL_IF_ID = 3, /**< physical PON interface Id on MAC device. */
    BCMOLT_TOPOLOGY_MAP_ID_USER_STRING = 4, /**< User specified string in config line. */
    BCMOLT_TOPOLOGY_MAP_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_topology_map_id__begin BCMOLT_TOPOLOGY_MAP_ID__BEGIN
#define bcmolt_topology_map_id_local_device_id BCMOLT_TOPOLOGY_MAP_ID_LOCAL_DEVICE_ID
#define bcmolt_topology_map_id_olt_device_id BCMOLT_TOPOLOGY_MAP_ID_OLT_DEVICE_ID
#define bcmolt_topology_map_id_physical_if_id BCMOLT_TOPOLOGY_MAP_ID_PHYSICAL_IF_ID
#define bcmolt_topology_map_id_user_string BCMOLT_TOPOLOGY_MAP_ID_USER_STRING
#define bcmolt_topology_map_id__num_of BCMOLT_TOPOLOGY_MAP_ID__NUM_OF
#define bcmolt_topology_map_id_all_properties 0xFF
#define bcmolt_topology_map_id_full_mask 0x1E

} bcmolt_topology_map_id;

/** Identifiers for all fields in a 'trap_config'. */
typedef enum
{
    BCMOLT_TRAP_CONFIG_ID__BEGIN = 0,
    BCMOLT_TRAP_CONFIG_ID_TPID = 0, /**< TPID. */
    BCMOLT_TRAP_CONFIG_ID_VLAN_ID = 1, /**< VLAN ID. */
    BCMOLT_TRAP_CONFIG_ID_VLAN_MASK = 2, /**< VLAN Mask. */
    BCMOLT_TRAP_CONFIG_ID_CFI = 3, /**< cfi. */
    BCMOLT_TRAP_CONFIG_ID_PBITS = 4, /**< pbits. */
    BCMOLT_TRAP_CONFIG_ID_ENABLE = 7, /**< Enable. */
    BCMOLT_TRAP_CONFIG_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_trap_config_id__begin BCMOLT_TRAP_CONFIG_ID__BEGIN
#define bcmolt_trap_config_id_tpid BCMOLT_TRAP_CONFIG_ID_TPID
#define bcmolt_trap_config_id_vlan_id BCMOLT_TRAP_CONFIG_ID_VLAN_ID
#define bcmolt_trap_config_id_vlan_mask BCMOLT_TRAP_CONFIG_ID_VLAN_MASK
#define bcmolt_trap_config_id_cfi BCMOLT_TRAP_CONFIG_ID_CFI
#define bcmolt_trap_config_id_pbits BCMOLT_TRAP_CONFIG_ID_PBITS
#define bcmolt_trap_config_id_enable BCMOLT_TRAP_CONFIG_ID_ENABLE
#define bcmolt_trap_config_id__num_of BCMOLT_TRAP_CONFIG_ID__NUM_OF
#define bcmolt_trap_config_id_all_properties 0xFF
#define bcmolt_trap_config_id_full_mask 0x9F

} bcmolt_trap_config_id;

/** Identifiers for all fields in a 'xgpon_burst_profile'. */
typedef enum
{
    BCMOLT_XGPON_BURST_PROFILE_ID__BEGIN = 0,
    BCMOLT_XGPON_BURST_PROFILE_ID_PROFILE_VERSION = 0, /**< profile version. */
    BCMOLT_XGPON_BURST_PROFILE_ID_TYPE = 1, /**< Type. */
    BCMOLT_XGPON_BURST_PROFILE_ID_IS_FEC_ON = 2, /**< is fec on. */
    BCMOLT_XGPON_BURST_PROFILE_ID_DELIMITER_SIZE_IN_BYTES = 3, /**< delimiter size in bytes. */
    BCMOLT_XGPON_BURST_PROFILE_ID_DELIMITER_PATTERN_HIGH = 4, /**< delimiter pattern high. */
    BCMOLT_XGPON_BURST_PROFILE_ID_DELIMITER_PATTERN_LOW = 5, /**< delimiter pattern low. */
    BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_LENGTH_IN_BYTES = 6, /**< preamble length in bytes. */
    BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_REPEATS_COUNT = 7, /**< preamble repeats count. */
    BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_PATTERN_HIGH = 8, /**< preamble pattern high. */
    BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_PATTERN_LOW = 9, /**< preamble pattern low. */
    BCMOLT_XGPON_BURST_PROFILE_ID_PON_TAG = 10, /**< PON tag. */
    BCMOLT_XGPON_BURST_PROFILE_ID_NUM_OF_GUARD_BYTES = 11, /**< number of guard bytes. */
    BCMOLT_XGPON_BURST_PROFILE_ID_IS_PROFILE_VALID = 12, /**< is profile valid. */
    BCMOLT_XGPON_BURST_PROFILE_ID_BURST_OVERHEAD_SIZE_IN_WORDS = 13, /**< burst overhead size in words. */
    BCMOLT_XGPON_BURST_PROFILE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_burst_profile_id__begin BCMOLT_XGPON_BURST_PROFILE_ID__BEGIN
#define bcmolt_xgpon_burst_profile_id_profile_version BCMOLT_XGPON_BURST_PROFILE_ID_PROFILE_VERSION
#define bcmolt_xgpon_burst_profile_id_type BCMOLT_XGPON_BURST_PROFILE_ID_TYPE
#define bcmolt_xgpon_burst_profile_id_is_fec_on BCMOLT_XGPON_BURST_PROFILE_ID_IS_FEC_ON
#define bcmolt_xgpon_burst_profile_id_delimiter_size_in_bytes BCMOLT_XGPON_BURST_PROFILE_ID_DELIMITER_SIZE_IN_BYTES
#define bcmolt_xgpon_burst_profile_id_delimiter_pattern_high BCMOLT_XGPON_BURST_PROFILE_ID_DELIMITER_PATTERN_HIGH
#define bcmolt_xgpon_burst_profile_id_delimiter_pattern_low BCMOLT_XGPON_BURST_PROFILE_ID_DELIMITER_PATTERN_LOW
#define bcmolt_xgpon_burst_profile_id_preamble_length_in_bytes BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_LENGTH_IN_BYTES
#define bcmolt_xgpon_burst_profile_id_preamble_repeats_count BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_REPEATS_COUNT
#define bcmolt_xgpon_burst_profile_id_preamble_pattern_high BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_PATTERN_HIGH
#define bcmolt_xgpon_burst_profile_id_preamble_pattern_low BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_PATTERN_LOW
#define bcmolt_xgpon_burst_profile_id_pon_tag BCMOLT_XGPON_BURST_PROFILE_ID_PON_TAG
#define bcmolt_xgpon_burst_profile_id_num_of_guard_bytes BCMOLT_XGPON_BURST_PROFILE_ID_NUM_OF_GUARD_BYTES
#define bcmolt_xgpon_burst_profile_id_is_profile_valid BCMOLT_XGPON_BURST_PROFILE_ID_IS_PROFILE_VALID
#define bcmolt_xgpon_burst_profile_id_burst_overhead_size_in_words BCMOLT_XGPON_BURST_PROFILE_ID_BURST_OVERHEAD_SIZE_IN_WORDS
#define bcmolt_xgpon_burst_profile_id__num_of BCMOLT_XGPON_BURST_PROFILE_ID__NUM_OF
#define bcmolt_xgpon_burst_profile_id_all_properties 0xFF
#define bcmolt_xgpon_burst_profile_id_full_mask 0x3FFF

} bcmolt_xgpon_burst_profile_id;

/** Identifiers for all fields in a 'xgpon_multicast_key'. */
typedef enum
{
    BCMOLT_XGPON_MULTICAST_KEY_ID__BEGIN = 0,
    BCMOLT_XGPON_MULTICAST_KEY_ID_KEY = 0, /**< encryption key array. */
    BCMOLT_XGPON_MULTICAST_KEY_ID_KEY_INDEX = 1, /**< key index. */
    BCMOLT_XGPON_MULTICAST_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_multicast_key_id__begin BCMOLT_XGPON_MULTICAST_KEY_ID__BEGIN
#define bcmolt_xgpon_multicast_key_id_key BCMOLT_XGPON_MULTICAST_KEY_ID_KEY
#define bcmolt_xgpon_multicast_key_id_key_index BCMOLT_XGPON_MULTICAST_KEY_ID_KEY_INDEX
#define bcmolt_xgpon_multicast_key_id__num_of BCMOLT_XGPON_MULTICAST_KEY_ID__NUM_OF
#define bcmolt_xgpon_multicast_key_id_all_properties 0xFF
#define bcmolt_xgpon_multicast_key_id_full_mask 0x3

} bcmolt_xgpon_multicast_key_id;

/** Identifiers for all fields in a 'xgpon_onu_alarm_indication_control'. */
typedef enum
{
    BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID__BEGIN = 0,
    BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID_LOAI = 0, /**< loss of ack indication control. */
    BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID_LOKI = 1, /**< loss of key indicayion control. */
    BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_onu_alarm_indication_control_id__begin BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID__BEGIN
#define bcmolt_xgpon_onu_alarm_indication_control_id_loai BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID_LOAI
#define bcmolt_xgpon_onu_alarm_indication_control_id_loki BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID_LOKI
#define bcmolt_xgpon_onu_alarm_indication_control_id__num_of BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID__NUM_OF
#define bcmolt_xgpon_onu_alarm_indication_control_id_all_properties 0xFF
#define bcmolt_xgpon_onu_alarm_indication_control_id_full_mask 0x3

} bcmolt_xgpon_onu_alarm_indication_control_id;

/** Identifiers for all fields in a 'xgpon_onu_alarm_state'. */
typedef enum
{
    BCMOLT_XGPON_ONU_ALARM_STATE_ID__BEGIN = 0,
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOSI = 0, /**< Loss of signal. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOBI = 1, /**< Loss of burst. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOPCI = 2, /**< Loss of PLOAM channel. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOPCI_MIC_ERROR = 3, /**< Mic error on ploam channel. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOOCI = 4, /**< Loss of OMCI channel. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_TIWI = 5, /**< Transmission interference Alarm. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_DOWI = 6, /**< Drift of Window. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_SUFI = 7, /**< Start UP Failure. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_SFI = 8, /**< Signal Fail. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_SDI = 9, /**< Signal Degraded. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_DFI = 10, /**< Deactivation Failure. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_DGI = 11, /**< Dying gasp. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_PQSI = 12, /**< Ploam queue status. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOAI = 13, /**< Loss of ack. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOKI = 14, /**< loss of key. */
    BCMOLT_XGPON_ONU_ALARM_STATE_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_onu_alarm_state_id__begin BCMOLT_XGPON_ONU_ALARM_STATE_ID__BEGIN
#define bcmolt_xgpon_onu_alarm_state_id_losi BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOSI
#define bcmolt_xgpon_onu_alarm_state_id_lobi BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOBI
#define bcmolt_xgpon_onu_alarm_state_id_lopci BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOPCI
#define bcmolt_xgpon_onu_alarm_state_id_lopci_mic_error BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOPCI_MIC_ERROR
#define bcmolt_xgpon_onu_alarm_state_id_looci BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOOCI
#define bcmolt_xgpon_onu_alarm_state_id_tiwi BCMOLT_XGPON_ONU_ALARM_STATE_ID_TIWI
#define bcmolt_xgpon_onu_alarm_state_id_dowi BCMOLT_XGPON_ONU_ALARM_STATE_ID_DOWI
#define bcmolt_xgpon_onu_alarm_state_id_sufi BCMOLT_XGPON_ONU_ALARM_STATE_ID_SUFI
#define bcmolt_xgpon_onu_alarm_state_id_sfi BCMOLT_XGPON_ONU_ALARM_STATE_ID_SFI
#define bcmolt_xgpon_onu_alarm_state_id_sdi BCMOLT_XGPON_ONU_ALARM_STATE_ID_SDI
#define bcmolt_xgpon_onu_alarm_state_id_dfi BCMOLT_XGPON_ONU_ALARM_STATE_ID_DFI
#define bcmolt_xgpon_onu_alarm_state_id_dgi BCMOLT_XGPON_ONU_ALARM_STATE_ID_DGI
#define bcmolt_xgpon_onu_alarm_state_id_pqsi BCMOLT_XGPON_ONU_ALARM_STATE_ID_PQSI
#define bcmolt_xgpon_onu_alarm_state_id_loai BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOAI
#define bcmolt_xgpon_onu_alarm_state_id_loki BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOKI
#define bcmolt_xgpon_onu_alarm_state_id__num_of BCMOLT_XGPON_ONU_ALARM_STATE_ID__NUM_OF
#define bcmolt_xgpon_onu_alarm_state_id_all_properties 0xFF
#define bcmolt_xgpon_onu_alarm_state_id_full_mask 0x7FFF

} bcmolt_xgpon_onu_alarm_state_id;

/** Identifiers for all fields in a 'xgpon_onu_alarms'. */
typedef enum
{
    BCMOLT_XGPON_ONU_ALARMS_ID__BEGIN = 0,
    BCMOLT_XGPON_ONU_ALARMS_ID_LOSI = 0, /**< LOSi. */
    BCMOLT_XGPON_ONU_ALARMS_ID_LOBI = 1, /**< LOBi. */
    BCMOLT_XGPON_ONU_ALARMS_ID_LOPCI_MISS = 2, /**< LOPCi miss. */
    BCMOLT_XGPON_ONU_ALARMS_ID_LOPCI_MIC_ERROR = 3, /**< LOPCi mic error. */
    BCMOLT_XGPON_ONU_ALARMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_onu_alarms_id__begin BCMOLT_XGPON_ONU_ALARMS_ID__BEGIN
#define bcmolt_xgpon_onu_alarms_id_losi BCMOLT_XGPON_ONU_ALARMS_ID_LOSI
#define bcmolt_xgpon_onu_alarms_id_lobi BCMOLT_XGPON_ONU_ALARMS_ID_LOBI
#define bcmolt_xgpon_onu_alarms_id_lopci_miss BCMOLT_XGPON_ONU_ALARMS_ID_LOPCI_MISS
#define bcmolt_xgpon_onu_alarms_id_lopci_mic_error BCMOLT_XGPON_ONU_ALARMS_ID_LOPCI_MIC_ERROR
#define bcmolt_xgpon_onu_alarms_id__num_of BCMOLT_XGPON_ONU_ALARMS_ID__NUM_OF
#define bcmolt_xgpon_onu_alarms_id_all_properties 0xFF
#define bcmolt_xgpon_onu_alarms_id_full_mask 0xF

} bcmolt_xgpon_onu_alarms_id;

/** Identifiers for all fields in a 'xgpon_onu_alarms_thresholds'. */
typedef enum
{
    BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID__BEGIN = 0,
    BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOSI = 0, /**< LOSi. */
    BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOBI = 1, /**< LOBi. */
    BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOOCI = 2, /**< LOOCi. */
    BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOPCI = 3, /**< LOPCi. */
    BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_onu_alarms_thresholds_id__begin BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID__BEGIN
#define bcmolt_xgpon_onu_alarms_thresholds_id_losi BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOSI
#define bcmolt_xgpon_onu_alarms_thresholds_id_lobi BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOBI
#define bcmolt_xgpon_onu_alarms_thresholds_id_looci BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOOCI
#define bcmolt_xgpon_onu_alarms_thresholds_id_lopci BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOPCI
#define bcmolt_xgpon_onu_alarms_thresholds_id__num_of BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID__NUM_OF
#define bcmolt_xgpon_onu_alarms_thresholds_id_all_properties 0xFF
#define bcmolt_xgpon_onu_alarms_thresholds_id_full_mask 0xF

} bcmolt_xgpon_onu_alarms_thresholds_id;

/** Identifiers for all fields in a 'xgpon_onu_params'. */
typedef enum
{
    BCMOLT_XGPON_ONU_PARAMS_ID__BEGIN = 0,
    BCMOLT_XGPON_ONU_PARAMS_ID_ALARM_STATE = 0, /**< alarm state. */
    BCMOLT_XGPON_ONU_PARAMS_ID_REGISTRATION_ID = 1, /**< registration id. */
    BCMOLT_XGPON_ONU_PARAMS_ID_NGPON2 = 2, /**< NGPON2 params. */
    BCMOLT_XGPON_ONU_PARAMS_ID_REGISTRATION_ENCRYPTION_KEYS = 3, /**< registration encryption keys. */
    BCMOLT_XGPON_ONU_PARAMS_ID_REQUEST_REGISTRATION_STATUS = 4, /**< Request registration status. */
    BCMOLT_XGPON_ONU_PARAMS_ID_RANGING_BURST_PROFILE = 5, /**< ranging burst profile. */
    BCMOLT_XGPON_ONU_PARAMS_ID_DATA_BURST_PROFILE = 6, /**< data burst profile. */
    BCMOLT_XGPON_ONU_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_onu_params_id__begin BCMOLT_XGPON_ONU_PARAMS_ID__BEGIN
#define bcmolt_xgpon_onu_params_id_alarm_state BCMOLT_XGPON_ONU_PARAMS_ID_ALARM_STATE
#define bcmolt_xgpon_onu_params_id_registration_id BCMOLT_XGPON_ONU_PARAMS_ID_REGISTRATION_ID
#define bcmolt_xgpon_onu_params_id_ngpon2 BCMOLT_XGPON_ONU_PARAMS_ID_NGPON2
#define bcmolt_xgpon_onu_params_id_registration_encryption_keys BCMOLT_XGPON_ONU_PARAMS_ID_REGISTRATION_ENCRYPTION_KEYS
#define bcmolt_xgpon_onu_params_id_request_registration_status BCMOLT_XGPON_ONU_PARAMS_ID_REQUEST_REGISTRATION_STATUS
#define bcmolt_xgpon_onu_params_id_ranging_burst_profile BCMOLT_XGPON_ONU_PARAMS_ID_RANGING_BURST_PROFILE
#define bcmolt_xgpon_onu_params_id_data_burst_profile BCMOLT_XGPON_ONU_PARAMS_ID_DATA_BURST_PROFILE
#define bcmolt_xgpon_onu_params_id__num_of BCMOLT_XGPON_ONU_PARAMS_ID__NUM_OF
#define bcmolt_xgpon_onu_params_id_all_properties 0xFF
#define bcmolt_xgpon_onu_params_id_full_mask 0x7F

} bcmolt_xgpon_onu_params_id;

/** Identifiers for all fields in a 'xgpon_onu_registration_keys'. */
typedef enum
{
    BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID__BEGIN = 0,
    BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_PLOAM_IK = 0, /**< ploam ik. */
    BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_OMCI_IK = 1, /**< omci ik. */
    BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_OMCI_K1 = 2, /**< omci k1. */
    BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_OMCI_K2 = 3, /**< omci k2. */
    BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_KEK = 4, /**< kek. */
    BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_onu_registration_keys_id__begin BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID__BEGIN
#define bcmolt_xgpon_onu_registration_keys_id_ploam_ik BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_PLOAM_IK
#define bcmolt_xgpon_onu_registration_keys_id_omci_ik BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_OMCI_IK
#define bcmolt_xgpon_onu_registration_keys_id_omci_k1 BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_OMCI_K1
#define bcmolt_xgpon_onu_registration_keys_id_omci_k2 BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_OMCI_K2
#define bcmolt_xgpon_onu_registration_keys_id_kek BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_KEK
#define bcmolt_xgpon_onu_registration_keys_id__num_of BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID__NUM_OF
#define bcmolt_xgpon_onu_registration_keys_id_all_properties 0xFF
#define bcmolt_xgpon_onu_registration_keys_id_full_mask 0x1F

} bcmolt_xgpon_onu_registration_keys_id;

/** Identifiers for all fields in a 'xgpon_pon_params'. */
typedef enum
{
    BCMOLT_XGPON_PON_PARAMS_ID__BEGIN = 0,
    BCMOLT_XGPON_PON_PARAMS_ID_HW_PON_ID = 0, /**< HW pon id. */
    BCMOLT_XGPON_PON_PARAMS_ID_ONU_ALARMS_THRESHOLDS = 1, /**< ONU alarms thresholds. */
    BCMOLT_XGPON_PON_PARAMS_ID_ALARM_INDICATION_CONTROL = 2, /**< alarm indication control. */
    BCMOLT_XGPON_PON_PARAMS_ID_MULTICAST_KEY = 3, /**< multicast key. */
    BCMOLT_XGPON_PON_PARAMS_ID_MIN_DATA_GEM_PORT_ID = 4, /**< Minimum data port id. */
    BCMOLT_XGPON_PON_PARAMS_ID_NGPON2 = 5, /**< NGPON params. */
    BCMOLT_XGPON_PON_PARAMS_ID_TDMA_2_5_G_DISCOVERY = 6, /**< TDMA 2.5 g discovery. */
    BCMOLT_XGPON_PON_PARAMS_ID_TDMA_10_G_DISCOVERY = 7, /**< TDMA 10 g discovery. */
    BCMOLT_XGPON_PON_PARAMS_ID_PLOAM_RETRANSMISSION = 8, /**< XGPON PLOAM retransmission. */
    BCMOLT_XGPON_PON_PARAMS_ID_TDMA_NUMBER_OF_2_5_G_ACTIVE_ONUS = 9, /**< TDMA number of 2.5Gbps active onus. */
    BCMOLT_XGPON_PON_PARAMS_ID_TDMA_NUMBER_OF_10_G_ACTIVE_ONUS = 10, /**< TDMA number of 10Gbps active onus. */
    BCMOLT_XGPON_PON_PARAMS_ID_OPERATION_CONTROL = 11, /**< operation control. */
    BCMOLT_XGPON_PON_PARAMS_ID_PERIODIC_PLOAMS = 12, /**< XGPON Periodic PLOAM Control. */
    BCMOLT_XGPON_PON_PARAMS_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_pon_params_id__begin BCMOLT_XGPON_PON_PARAMS_ID__BEGIN
#define bcmolt_xgpon_pon_params_id_hw_pon_id BCMOLT_XGPON_PON_PARAMS_ID_HW_PON_ID
#define bcmolt_xgpon_pon_params_id_onu_alarms_thresholds BCMOLT_XGPON_PON_PARAMS_ID_ONU_ALARMS_THRESHOLDS
#define bcmolt_xgpon_pon_params_id_alarm_indication_control BCMOLT_XGPON_PON_PARAMS_ID_ALARM_INDICATION_CONTROL
#define bcmolt_xgpon_pon_params_id_multicast_key BCMOLT_XGPON_PON_PARAMS_ID_MULTICAST_KEY
#define bcmolt_xgpon_pon_params_id_min_data_gem_port_id BCMOLT_XGPON_PON_PARAMS_ID_MIN_DATA_GEM_PORT_ID
#define bcmolt_xgpon_pon_params_id_ngpon2 BCMOLT_XGPON_PON_PARAMS_ID_NGPON2
#define bcmolt_xgpon_pon_params_id_tdma_2_5_g_discovery BCMOLT_XGPON_PON_PARAMS_ID_TDMA_2_5_G_DISCOVERY
#define bcmolt_xgpon_pon_params_id_tdma_10_g_discovery BCMOLT_XGPON_PON_PARAMS_ID_TDMA_10_G_DISCOVERY
#define bcmolt_xgpon_pon_params_id_ploam_retransmission BCMOLT_XGPON_PON_PARAMS_ID_PLOAM_RETRANSMISSION
#define bcmolt_xgpon_pon_params_id_tdma_number_of_2_5_g_active_onus BCMOLT_XGPON_PON_PARAMS_ID_TDMA_NUMBER_OF_2_5_G_ACTIVE_ONUS
#define bcmolt_xgpon_pon_params_id_tdma_number_of_10_g_active_onus BCMOLT_XGPON_PON_PARAMS_ID_TDMA_NUMBER_OF_10_G_ACTIVE_ONUS
#define bcmolt_xgpon_pon_params_id_operation_control BCMOLT_XGPON_PON_PARAMS_ID_OPERATION_CONTROL
#define bcmolt_xgpon_pon_params_id_periodic_ploams BCMOLT_XGPON_PON_PARAMS_ID_PERIODIC_PLOAMS
#define bcmolt_xgpon_pon_params_id__num_of BCMOLT_XGPON_PON_PARAMS_ID__NUM_OF
#define bcmolt_xgpon_pon_params_id_all_properties 0xFF
#define bcmolt_xgpon_pon_params_id_full_mask 0x1FFF

} bcmolt_xgpon_pon_params_id;

/** Identifiers for all fields in a 'xgpon_trx'. */
typedef enum
{
    BCMOLT_XGPON_TRX_ID__BEGIN = 0,
    BCMOLT_XGPON_TRX_ID_BURST_PROFILE = 0, /**< burst profile. */
    BCMOLT_XGPON_TRX_ID_TRANSCEIVER_TYPE = 2, /**< trx type. */
    BCMOLT_XGPON_TRX_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_xgpon_trx_id__begin BCMOLT_XGPON_TRX_ID__BEGIN
#define bcmolt_xgpon_trx_id_burst_profile BCMOLT_XGPON_TRX_ID_BURST_PROFILE
#define bcmolt_xgpon_trx_id_transceiver_type BCMOLT_XGPON_TRX_ID_TRANSCEIVER_TYPE
#define bcmolt_xgpon_trx_id__num_of BCMOLT_XGPON_TRX_ID__NUM_OF
#define bcmolt_xgpon_trx_id_all_properties 0xFF
#define bcmolt_xgpon_trx_id_full_mask 0x5

} bcmolt_xgpon_trx_id;

/** Identifiers for all fields in a 'access_control_key'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_KEY_ID__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_KEY_ID_ID = 0, /**< ACL ID. */
    BCMOLT_ACCESS_CONTROL_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_key_id__begin BCMOLT_ACCESS_CONTROL_KEY_ID__BEGIN
#define bcmolt_access_control_key_id_id BCMOLT_ACCESS_CONTROL_KEY_ID_ID
#define bcmolt_access_control_key_id__num_of BCMOLT_ACCESS_CONTROL_KEY_ID__NUM_OF
#define bcmolt_access_control_key_id_all_properties 0xFF
#define bcmolt_access_control_key_id_full_mask 0x1

} bcmolt_access_control_key_id;

/** Identifiers for all fields in a 'access_control_cfg_data'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID__BEGIN = 4,
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_CLASSIFIER = 4, /**< Classifier. */
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_PRIORITY = 5, /**< Priority. */
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_FORWARDING_ACTION = 6, /**< Packet forwarding Action. */
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_STATE = 9, /**< State. */
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_COOKIE = 11, /**< Cookie. */
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_INTERFACE_REFS = 12, /**< list of associated interfaces. */
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_STATISTICS_CONTROL = 14, /**< statistics control. */
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_MODIFIER_ACTION = 15, /**< Packet modifier action. */
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_POLICER_ACTION = 16, /**< policer action. */
    BCMOLT_ACCESS_CONTROL_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_cfg_data_id__begin BCMOLT_ACCESS_CONTROL_CFG_DATA_ID__BEGIN
#define bcmolt_access_control_cfg_data_id_classifier BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_CLASSIFIER
#define bcmolt_access_control_cfg_data_id_priority BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_PRIORITY
#define bcmolt_access_control_cfg_data_id_forwarding_action BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_FORWARDING_ACTION
#define bcmolt_access_control_cfg_data_id_state BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_STATE
#define bcmolt_access_control_cfg_data_id_cookie BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_COOKIE
#define bcmolt_access_control_cfg_data_id_interface_refs BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_INTERFACE_REFS
#define bcmolt_access_control_cfg_data_id_statistics_control BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_STATISTICS_CONTROL
#define bcmolt_access_control_cfg_data_id_modifier_action BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_MODIFIER_ACTION
#define bcmolt_access_control_cfg_data_id_policer_action BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_POLICER_ACTION
#define bcmolt_access_control_cfg_data_id__num_of BCMOLT_ACCESS_CONTROL_CFG_DATA_ID__NUM_OF
#define bcmolt_access_control_cfg_data_id_all_properties 0xFF
#define bcmolt_access_control_cfg_data_id_full_mask 0x1DA70

} bcmolt_access_control_cfg_data_id;

/** Identifiers for all fields in a 'access_control_stats_data'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_PACKETS = 0, /**< packets processed (ACL). */
    BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_BYTES = 1, /**< bytes processed (ACL). */
    BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_PASSED_UKMB = 2, /**< policer_packets_passed_ukmb. */
    BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_PASSED_UKMB = 3, /**< policer_bytes passed_ukmb. */
    BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_DROPPED_UKMB = 4, /**< policer_packets_dropped_ukmb. */
    BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_DROPPED_UKMB = 5, /**< policer_bytes dropped_ukmb. */
    BCMOLT_ACCESS_CONTROL_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_stats_data_id__begin BCMOLT_ACCESS_CONTROL_STATS_DATA_ID__BEGIN
#define bcmolt_access_control_stats_data_id_packets BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_PACKETS
#define bcmolt_access_control_stats_data_id_bytes BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_BYTES
#define bcmolt_access_control_stats_data_id_policer_packets_passed_ukmb BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_PASSED_UKMB
#define bcmolt_access_control_stats_data_id_policer_bytes_passed_ukmb BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_PASSED_UKMB
#define bcmolt_access_control_stats_data_id_policer_packets_dropped_ukmb BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_DROPPED_UKMB
#define bcmolt_access_control_stats_data_id_policer_bytes_dropped_ukmb BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_DROPPED_UKMB
#define bcmolt_access_control_stats_data_id__num_of BCMOLT_ACCESS_CONTROL_STATS_DATA_ID__NUM_OF
#define bcmolt_access_control_stats_data_id_all_properties 0xFF
#define bcmolt_access_control_stats_data_id_full_mask 0x3F

} bcmolt_access_control_stats_data_id;

/** Identifiers for all fields in a 'access_control_receive_eth_packet_data'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID__BEGIN = 1,
    BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_INTERFACE_REF = 1, /**< Interface Ref. */
    BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_BUFFER = 2, /**< Buffer. */
    BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_SVC_PORT_ID = 3, /**< GEM or LLID. */
    BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_receive_eth_packet_data_id__begin BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID__BEGIN
#define bcmolt_access_control_receive_eth_packet_data_id_interface_ref BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_INTERFACE_REF
#define bcmolt_access_control_receive_eth_packet_data_id_buffer BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_BUFFER
#define bcmolt_access_control_receive_eth_packet_data_id_svc_port_id BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_SVC_PORT_ID
#define bcmolt_access_control_receive_eth_packet_data_id__num_of BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID__NUM_OF
#define bcmolt_access_control_receive_eth_packet_data_id_all_properties 0xFF
#define bcmolt_access_control_receive_eth_packet_data_id_full_mask 0xE

} bcmolt_access_control_receive_eth_packet_data_id;

/** Identifiers for all fields in a 'access_control_interfaces_update_data'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID_INTERFACE_REF_LIST = 0, /**< interface reference. */
    BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID_COMMAND = 1, /**< command. */
    BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_interfaces_update_data_id__begin BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID__BEGIN
#define bcmolt_access_control_interfaces_update_data_id_interface_ref_list BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID_INTERFACE_REF_LIST
#define bcmolt_access_control_interfaces_update_data_id_command BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID_COMMAND
#define bcmolt_access_control_interfaces_update_data_id__num_of BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID__NUM_OF
#define bcmolt_access_control_interfaces_update_data_id_all_properties 0xFF
#define bcmolt_access_control_interfaces_update_data_id_full_mask 0x3

} bcmolt_access_control_interfaces_update_data_id;

/** Identifiers for all fields in a 'access_control_stats_cfg_data'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_PACKETS = 0, /**< packets processed (ACL). */
    BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_BYTES = 1, /**< bytes processed (ACL). */
    BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_PACKETS_PASSED_UKMB = 2, /**< policer_packets_passed_ukmb. */
    BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_BYTES_PASSED_UKMB = 3, /**< policer_bytes passed_ukmb. */
    BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_PACKETS_DROPPED_UKMB = 4, /**< policer_packets_dropped_ukmb. */
    BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_BYTES_DROPPED_UKMB = 5, /**< policer_bytes dropped_ukmb. */
    BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_stats_cfg_data_id__begin BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_access_control_stats_cfg_data_id_packets BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_PACKETS
#define bcmolt_access_control_stats_cfg_data_id_bytes BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_BYTES
#define bcmolt_access_control_stats_cfg_data_id_policer_packets_passed_ukmb BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_PACKETS_PASSED_UKMB
#define bcmolt_access_control_stats_cfg_data_id_policer_bytes_passed_ukmb BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_BYTES_PASSED_UKMB
#define bcmolt_access_control_stats_cfg_data_id_policer_packets_dropped_ukmb BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_PACKETS_DROPPED_UKMB
#define bcmolt_access_control_stats_cfg_data_id_policer_bytes_dropped_ukmb BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_BYTES_DROPPED_UKMB
#define bcmolt_access_control_stats_cfg_data_id__num_of BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_access_control_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_access_control_stats_cfg_data_id_full_mask 0x3F

} bcmolt_access_control_stats_cfg_data_id;

/** Identifiers for all fields in a 'access_control_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ACCESS_CONTROL_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_stats_alarm_raised_data_id__begin BCMOLT_ACCESS_CONTROL_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_access_control_stats_alarm_raised_data_id_stat BCMOLT_ACCESS_CONTROL_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_access_control_stats_alarm_raised_data_id__num_of BCMOLT_ACCESS_CONTROL_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_access_control_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_access_control_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_access_control_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'access_control_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ACCESS_CONTROL_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_stats_alarm_cleared_data_id__begin BCMOLT_ACCESS_CONTROL_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_access_control_stats_alarm_cleared_data_id_stat BCMOLT_ACCESS_CONTROL_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_access_control_stats_alarm_cleared_data_id__num_of BCMOLT_ACCESS_CONTROL_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_access_control_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_access_control_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_access_control_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'access_control_auto_cfg_data'. */
typedef enum
{
    BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID_RECEIVE_ETH_PACKET = 0, /**< receive_eth_packet. */
    BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED = 1, /**< Stats Alarm Cleared. */
    BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED = 2, /**< Stats Alarm Raised. */
    BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_access_control_auto_cfg_data_id__begin BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_access_control_auto_cfg_data_id_receive_eth_packet BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID_RECEIVE_ETH_PACKET
#define bcmolt_access_control_auto_cfg_data_id_stats_alarm_cleared BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED
#define bcmolt_access_control_auto_cfg_data_id_stats_alarm_raised BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED
#define bcmolt_access_control_auto_cfg_data_id__num_of BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_access_control_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_access_control_auto_cfg_data_id_full_mask 0x7

} bcmolt_access_control_auto_cfg_data_id;

/** Identifiers for all fields in a 'bal_system_cfg_data'. */
typedef enum
{
    BCMOLT_BAL_SYSTEM_CFG_DATA_ID__BEGIN = 4,
    BCMOLT_BAL_SYSTEM_CFG_DATA_ID_LAG_PARMS = 4, /**< LAG Global Params. */
    BCMOLT_BAL_SYSTEM_CFG_DATA_ID_CONFIG_STATE = 5, /**< Configuration State. */
    BCMOLT_BAL_SYSTEM_CFG_DATA_ID_HOST_PORT = 6, /**< host port. */
    BCMOLT_BAL_SYSTEM_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_bal_system_cfg_data_id__begin BCMOLT_BAL_SYSTEM_CFG_DATA_ID__BEGIN
#define bcmolt_bal_system_cfg_data_id_lag_parms BCMOLT_BAL_SYSTEM_CFG_DATA_ID_LAG_PARMS
#define bcmolt_bal_system_cfg_data_id_config_state BCMOLT_BAL_SYSTEM_CFG_DATA_ID_CONFIG_STATE
#define bcmolt_bal_system_cfg_data_id_host_port BCMOLT_BAL_SYSTEM_CFG_DATA_ID_HOST_PORT
#define bcmolt_bal_system_cfg_data_id__num_of BCMOLT_BAL_SYSTEM_CFG_DATA_ID__NUM_OF
#define bcmolt_bal_system_cfg_data_id_all_properties 0xFF
#define bcmolt_bal_system_cfg_data_id_full_mask 0x70

} bcmolt_bal_system_cfg_data_id;

/** Identifiers for all fields in a 'bal_system_key'. */
typedef enum
{
    BCMOLT_BAL_SYSTEM_KEY_ID__BEGIN = 0,
    BCMOLT_BAL_SYSTEM_KEY_ID_ID = 0, /**< id. */
    BCMOLT_BAL_SYSTEM_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_bal_system_key_id__begin BCMOLT_BAL_SYSTEM_KEY_ID__BEGIN
#define bcmolt_bal_system_key_id_id BCMOLT_BAL_SYSTEM_KEY_ID_ID
#define bcmolt_bal_system_key_id__num_of BCMOLT_BAL_SYSTEM_KEY_ID__NUM_OF
#define bcmolt_bal_system_key_id_all_properties 0xFF
#define bcmolt_bal_system_key_id_full_mask 0x1

} bcmolt_bal_system_key_id;

/** Identifiers for all fields in a 'device_key'. */
typedef enum
{
    BCMOLT_DEVICE_KEY_ID__BEGIN = 0,
    BCMOLT_DEVICE_KEY_ID_DEVICE_ID = 0, /**< Device ID. */
    BCMOLT_DEVICE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_key_id__begin BCMOLT_DEVICE_KEY_ID__BEGIN
#define bcmolt_device_key_id_device_id BCMOLT_DEVICE_KEY_ID_DEVICE_ID
#define bcmolt_device_key_id__num_of BCMOLT_DEVICE_KEY_ID__NUM_OF
#define bcmolt_device_key_id_all_properties 0xFF
#define bcmolt_device_key_id_full_mask 0x1

} bcmolt_device_key_id;

/** Identifiers for all fields in a 'device_cfg_data'. */
typedef enum
{
    BCMOLT_DEVICE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_CFG_DATA_ID_SYSTEM_MODE = 0, /**< system_mode. */
    BCMOLT_DEVICE_CFG_DATA_ID_KEEPALIVE_INTERVAL = 1, /**< Device Keepalive Interval. */
    BCMOLT_DEVICE_CFG_DATA_ID_KEEPALIVE_TOLERANCE = 2, /**< Device Keepalive tolerance. */
    BCMOLT_DEVICE_CFG_DATA_ID_FIRMWARE_SW_VERSION = 3, /**< Firmware SW Version. */
    BCMOLT_DEVICE_CFG_DATA_ID_CHIP_REVISION = 4, /**< Chip Revision. */
    BCMOLT_DEVICE_CFG_DATA_ID_CHIP_VOLTAGE = 5, /**< chip voltage. */
    BCMOLT_DEVICE_CFG_DATA_ID_CHIP_TEMPERATURE = 6, /**< chip temperature. */
    BCMOLT_DEVICE_CFG_DATA_ID_DEBUG = 7, /**< debug parameters. */
    BCMOLT_DEVICE_CFG_DATA_ID_PROTECTION_SWITCHING_EXT_IRQ = 9, /**< Protection Switching External IRQ. */
    BCMOLT_DEVICE_CFG_DATA_ID_INDICATION_SHAPING = 10, /**< Indication Shaping. */
    BCMOLT_DEVICE_CFG_DATA_ID_TOD_UART_BAUDRATE = 11, /**< UART baudrate. */
    BCMOLT_DEVICE_CFG_DATA_ID_ITU_TOD = 12, /**< ITU ToD. */
    BCMOLT_DEVICE_CFG_DATA_ID_IEEE_8021_AS_TOD = 13, /**< IEEE 802.1 AS ToD. */
    BCMOLT_DEVICE_CFG_DATA_ID_EMBEDDED_IMAGE_LIST = 16, /**< Embedded image list. */
    BCMOLT_DEVICE_CFG_DATA_ID_WD_ENABLE = 17, /**< In-band watchdog enable. */
    BCMOLT_DEVICE_CFG_DATA_ID_WD_IP_TRAFFIC_TIMEOUT = 18, /**< In-band watchdog IP traffic timeout interval. */
    BCMOLT_DEVICE_CFG_DATA_ID_COMM_MODE = 19, /**< Communication Mode. */
    BCMOLT_DEVICE_CFG_DATA_ID_PCIE_CONN_DATA = 20, /**< PCIe Connection Data. */
    BCMOLT_DEVICE_CFG_DATA_ID_CHIP_ID = 21, /**< Chip Id. */
    BCMOLT_DEVICE_CFG_DATA_ID_LOGGER_ENABLE = 27, /**< Logger Enable. */
    BCMOLT_DEVICE_CFG_DATA_ID_INNI_CONFIG = 28, /**< INNI Configuration. */
    BCMOLT_DEVICE_CFG_DATA_ID_CHIP_FAMILY = 29, /**< Chip Family. */
    BCMOLT_DEVICE_CFG_DATA_ID_RAS_DDR_MODE = 30, /**< RAS DDR Mode. */
    BCMOLT_DEVICE_CFG_DATA_ID_ITU_MULTIPON_DBA_ENABLE = 31, /**< Enable Multi-PON DBA feature in ITU modes. */
    BCMOLT_DEVICE_CFG_DATA_ID_ITU_ENABLE_INNI_MUX = 32, /**< Enable INNI mux configuration. */
    BCMOLT_DEVICE_CFG_DATA_ID_ITU_LOW_LATENCY_DBA_ENABLE = 33, /**< Enable low latency DBA feature in ITU modes. */
    BCMOLT_DEVICE_CFG_DATA_ID_TRAP_GPON_PLOAM = 34, /**< trap gpon ploam. */
    BCMOLT_DEVICE_CFG_DATA_ID_TRAP_XGPON_PLOAM = 35, /**< trap xgpon ploam. */
    BCMOLT_DEVICE_CFG_DATA_ID_DEBUG_UART_PORT_SWAP = 36, /**< Swap UART ports 0 and 1. */
    BCMOLT_DEVICE_CFG_DATA_ID_INBAND_CONN_DATA = 37, /**< In-Band Connection Data. */
    BCMOLT_DEVICE_CFG_DATA_ID_INBAND_INTERNAL_NNI = 38, /**< In-Band Internal NNI. */
    BCMOLT_DEVICE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_cfg_data_id__begin BCMOLT_DEVICE_CFG_DATA_ID__BEGIN
#define bcmolt_device_cfg_data_id_system_mode BCMOLT_DEVICE_CFG_DATA_ID_SYSTEM_MODE
#define bcmolt_device_cfg_data_id_keepalive_interval BCMOLT_DEVICE_CFG_DATA_ID_KEEPALIVE_INTERVAL
#define bcmolt_device_cfg_data_id_keepalive_tolerance BCMOLT_DEVICE_CFG_DATA_ID_KEEPALIVE_TOLERANCE
#define bcmolt_device_cfg_data_id_firmware_sw_version BCMOLT_DEVICE_CFG_DATA_ID_FIRMWARE_SW_VERSION
#define bcmolt_device_cfg_data_id_chip_revision BCMOLT_DEVICE_CFG_DATA_ID_CHIP_REVISION
#define bcmolt_device_cfg_data_id_chip_voltage BCMOLT_DEVICE_CFG_DATA_ID_CHIP_VOLTAGE
#define bcmolt_device_cfg_data_id_chip_temperature BCMOLT_DEVICE_CFG_DATA_ID_CHIP_TEMPERATURE
#define bcmolt_device_cfg_data_id_debug BCMOLT_DEVICE_CFG_DATA_ID_DEBUG
#define bcmolt_device_cfg_data_id_protection_switching_ext_irq BCMOLT_DEVICE_CFG_DATA_ID_PROTECTION_SWITCHING_EXT_IRQ
#define bcmolt_device_cfg_data_id_indication_shaping BCMOLT_DEVICE_CFG_DATA_ID_INDICATION_SHAPING
#define bcmolt_device_cfg_data_id_tod_uart_baudrate BCMOLT_DEVICE_CFG_DATA_ID_TOD_UART_BAUDRATE
#define bcmolt_device_cfg_data_id_itu_tod BCMOLT_DEVICE_CFG_DATA_ID_ITU_TOD
#define bcmolt_device_cfg_data_id_ieee_8021_as_tod BCMOLT_DEVICE_CFG_DATA_ID_IEEE_8021_AS_TOD
#define bcmolt_device_cfg_data_id_embedded_image_list BCMOLT_DEVICE_CFG_DATA_ID_EMBEDDED_IMAGE_LIST
#define bcmolt_device_cfg_data_id_wd_enable BCMOLT_DEVICE_CFG_DATA_ID_WD_ENABLE
#define bcmolt_device_cfg_data_id_wd_ip_traffic_timeout BCMOLT_DEVICE_CFG_DATA_ID_WD_IP_TRAFFIC_TIMEOUT
#define bcmolt_device_cfg_data_id_comm_mode BCMOLT_DEVICE_CFG_DATA_ID_COMM_MODE
#define bcmolt_device_cfg_data_id_pcie_conn_data BCMOLT_DEVICE_CFG_DATA_ID_PCIE_CONN_DATA
#define bcmolt_device_cfg_data_id_chip_id BCMOLT_DEVICE_CFG_DATA_ID_CHIP_ID
#define bcmolt_device_cfg_data_id_logger_enable BCMOLT_DEVICE_CFG_DATA_ID_LOGGER_ENABLE
#define bcmolt_device_cfg_data_id_inni_config BCMOLT_DEVICE_CFG_DATA_ID_INNI_CONFIG
#define bcmolt_device_cfg_data_id_chip_family BCMOLT_DEVICE_CFG_DATA_ID_CHIP_FAMILY
#define bcmolt_device_cfg_data_id_ras_ddr_mode BCMOLT_DEVICE_CFG_DATA_ID_RAS_DDR_MODE
#define bcmolt_device_cfg_data_id_itu_multipon_dba_enable BCMOLT_DEVICE_CFG_DATA_ID_ITU_MULTIPON_DBA_ENABLE
#define bcmolt_device_cfg_data_id_itu_enable_inni_mux BCMOLT_DEVICE_CFG_DATA_ID_ITU_ENABLE_INNI_MUX
#define bcmolt_device_cfg_data_id_itu_low_latency_dba_enable BCMOLT_DEVICE_CFG_DATA_ID_ITU_LOW_LATENCY_DBA_ENABLE
#define bcmolt_device_cfg_data_id_trap_gpon_ploam BCMOLT_DEVICE_CFG_DATA_ID_TRAP_GPON_PLOAM
#define bcmolt_device_cfg_data_id_trap_xgpon_ploam BCMOLT_DEVICE_CFG_DATA_ID_TRAP_XGPON_PLOAM
#define bcmolt_device_cfg_data_id_debug_uart_port_swap BCMOLT_DEVICE_CFG_DATA_ID_DEBUG_UART_PORT_SWAP
#define bcmolt_device_cfg_data_id_inband_conn_data BCMOLT_DEVICE_CFG_DATA_ID_INBAND_CONN_DATA
#define bcmolt_device_cfg_data_id_inband_internal_nni BCMOLT_DEVICE_CFG_DATA_ID_INBAND_INTERNAL_NNI
#define bcmolt_device_cfg_data_id__num_of BCMOLT_DEVICE_CFG_DATA_ID__NUM_OF
#define bcmolt_device_cfg_data_id_all_properties 0xFF
#define bcmolt_device_cfg_data_id_full_mask 0x7FF83F3EFF

} bcmolt_device_cfg_data_id;

/** Identifiers for all fields in a 'device_connect_data'. */
typedef enum
{
    BCMOLT_DEVICE_CONNECT_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_CONNECT_DATA_ID_SYSTEM_MODE = 0, /**< System Mode. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_COMM_MODE = 1, /**< Communication Mode. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_PCIE_CONN_DATA = 2, /**< PCIe Connection Data. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_INBAND_CONN_DATA = 3, /**< In-Band Connection Data. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_INNI_CONFIG = 5, /**< INNI Configuration. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_RAS_DDR_MODE = 6, /**< RAS DDR mode. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_ITU_MULTIPON_DBA_ENABLE = 7, /**< Enable Multi-PON DBA feature in ITU modes. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_DDR_TEST_MODE = 8, /**< DDR test mode. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_ITU_CHANGE_INNI_MUX_ENABLE = 9, /**< Enable changing INNI mux. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_ITU_LOW_LATENCY_DBA_ENABLE = 10, /**< Enable low latency DBA feature in ITU modes. */
    BCMOLT_DEVICE_CONNECT_DATA_ID_DEBUG_UART_PORT_SWAP = 11, /**< Swap usage of UART 0 and 1. */
    BCMOLT_DEVICE_CONNECT_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_connect_data_id__begin BCMOLT_DEVICE_CONNECT_DATA_ID__BEGIN
#define bcmolt_device_connect_data_id_system_mode BCMOLT_DEVICE_CONNECT_DATA_ID_SYSTEM_MODE
#define bcmolt_device_connect_data_id_comm_mode BCMOLT_DEVICE_CONNECT_DATA_ID_COMM_MODE
#define bcmolt_device_connect_data_id_pcie_conn_data BCMOLT_DEVICE_CONNECT_DATA_ID_PCIE_CONN_DATA
#define bcmolt_device_connect_data_id_inband_conn_data BCMOLT_DEVICE_CONNECT_DATA_ID_INBAND_CONN_DATA
#define bcmolt_device_connect_data_id_inni_config BCMOLT_DEVICE_CONNECT_DATA_ID_INNI_CONFIG
#define bcmolt_device_connect_data_id_ras_ddr_mode BCMOLT_DEVICE_CONNECT_DATA_ID_RAS_DDR_MODE
#define bcmolt_device_connect_data_id_itu_multipon_dba_enable BCMOLT_DEVICE_CONNECT_DATA_ID_ITU_MULTIPON_DBA_ENABLE
#define bcmolt_device_connect_data_id_ddr_test_mode BCMOLT_DEVICE_CONNECT_DATA_ID_DDR_TEST_MODE
#define bcmolt_device_connect_data_id_itu_change_inni_mux_enable BCMOLT_DEVICE_CONNECT_DATA_ID_ITU_CHANGE_INNI_MUX_ENABLE
#define bcmolt_device_connect_data_id_itu_low_latency_dba_enable BCMOLT_DEVICE_CONNECT_DATA_ID_ITU_LOW_LATENCY_DBA_ENABLE
#define bcmolt_device_connect_data_id_debug_uart_port_swap BCMOLT_DEVICE_CONNECT_DATA_ID_DEBUG_UART_PORT_SWAP
#define bcmolt_device_connect_data_id__num_of BCMOLT_DEVICE_CONNECT_DATA_ID__NUM_OF
#define bcmolt_device_connect_data_id_all_properties 0xFF
#define bcmolt_device_connect_data_id_full_mask 0xFEF

} bcmolt_device_connect_data_id;

/** Identifiers for all fields in a 'device_host_keep_alive_data'. */
typedef enum
{
    BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID_SEQUENCE_NUMBER = 0, /**< sequence number. */
    BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID_TIME_STAMP = 1, /**< time stamp. */
    BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_host_keep_alive_data_id__begin BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID__BEGIN
#define bcmolt_device_host_keep_alive_data_id_sequence_number BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID_SEQUENCE_NUMBER
#define bcmolt_device_host_keep_alive_data_id_time_stamp BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID_TIME_STAMP
#define bcmolt_device_host_keep_alive_data_id__num_of BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID__NUM_OF
#define bcmolt_device_host_keep_alive_data_id_all_properties 0xFF
#define bcmolt_device_host_keep_alive_data_id_full_mask 0x3

} bcmolt_device_host_keep_alive_data_id;

/** Identifiers for all fields in a 'device_set_8021_as_tod_string_data'. */
typedef enum
{
    BCMOLT_DEVICE_SET_8021_AS_TOD_STRING_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_SET_8021_AS_TOD_STRING_DATA_ID_TOD_STRING = 0, /**< ToD String. */
    BCMOLT_DEVICE_SET_8021_AS_TOD_STRING_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_set_8021_as_tod_string_data_id__begin BCMOLT_DEVICE_SET_8021_AS_TOD_STRING_DATA_ID__BEGIN
#define bcmolt_device_set_8021_as_tod_string_data_id_tod_string BCMOLT_DEVICE_SET_8021_AS_TOD_STRING_DATA_ID_TOD_STRING
#define bcmolt_device_set_8021_as_tod_string_data_id__num_of BCMOLT_DEVICE_SET_8021_AS_TOD_STRING_DATA_ID__NUM_OF
#define bcmolt_device_set_8021_as_tod_string_data_id_all_properties 0xFF
#define bcmolt_device_set_8021_as_tod_string_data_id_full_mask 0x1

} bcmolt_device_set_8021_as_tod_string_data_id;

/** Identifiers for all fields in a 'device_image_transfer_start_data'. */
typedef enum
{
    BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_IMAGE_TYPE = 0, /**< Image type. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_IMAGE_SIZE = 1, /**< Image Size. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_CRC32 = 2, /**< CRC32. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_IMAGE_NAME = 3, /**< Image name. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_image_transfer_start_data_id__begin BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID__BEGIN
#define bcmolt_device_image_transfer_start_data_id_image_type BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_IMAGE_TYPE
#define bcmolt_device_image_transfer_start_data_id_image_size BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_IMAGE_SIZE
#define bcmolt_device_image_transfer_start_data_id_crc32 BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_CRC32
#define bcmolt_device_image_transfer_start_data_id_image_name BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_IMAGE_NAME
#define bcmolt_device_image_transfer_start_data_id__num_of BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID__NUM_OF
#define bcmolt_device_image_transfer_start_data_id_all_properties 0xFF
#define bcmolt_device_image_transfer_start_data_id_full_mask 0xF

} bcmolt_device_image_transfer_start_data_id;

/** Identifiers for all fields in a 'device_image_transfer_data_data'. */
typedef enum
{
    BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID_BLOCK_NUMBER = 0, /**< Block number. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID_MORE_DATA = 1, /**< More Data. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID_DATA = 2, /**< Data. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_image_transfer_data_data_id__begin BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID__BEGIN
#define bcmolt_device_image_transfer_data_data_id_block_number BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID_BLOCK_NUMBER
#define bcmolt_device_image_transfer_data_data_id_more_data BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID_MORE_DATA
#define bcmolt_device_image_transfer_data_data_id_data BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID_DATA
#define bcmolt_device_image_transfer_data_data_id__num_of BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID__NUM_OF
#define bcmolt_device_image_transfer_data_data_id_all_properties 0xFF
#define bcmolt_device_image_transfer_data_data_id_full_mask 0x7

} bcmolt_device_image_transfer_data_data_id;

/** Identifiers for all fields in a 'device_run_ddr_test_data'. */
typedef enum
{
    BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID_CPU = 0, /**< CPU. */
    BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID_RAS_0 = 1, /**< RAS 0. */
    BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID_RAS_1 = 2, /**< RAS 1. */
    BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_run_ddr_test_data_id__begin BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID__BEGIN
#define bcmolt_device_run_ddr_test_data_id_cpu BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID_CPU
#define bcmolt_device_run_ddr_test_data_id_ras_0 BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID_RAS_0
#define bcmolt_device_run_ddr_test_data_id_ras_1 BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID_RAS_1
#define bcmolt_device_run_ddr_test_data_id__num_of BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID__NUM_OF
#define bcmolt_device_run_ddr_test_data_id_all_properties 0xFF
#define bcmolt_device_run_ddr_test_data_id_full_mask 0x7

} bcmolt_device_run_ddr_test_data_id;

/** Identifiers for all fields in a 'device_device_ready_data'. */
typedef enum
{
    BCMOLT_DEVICE_DEVICE_READY_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_DEVICE_READY_DATA_ID_FIRMWARE_SW_VERSION = 0, /**< Software Version. */
    BCMOLT_DEVICE_DEVICE_READY_DATA_ID_SYSTEM_MODE = 1, /**< System Mode. */
    BCMOLT_DEVICE_DEVICE_READY_DATA_ID_KEEPALIVE_INTERVAL = 2, /**< Device keepalive interval. */
    BCMOLT_DEVICE_DEVICE_READY_DATA_ID_KEEPALIVE_TOLERANCE = 3, /**< Device keepalive tolerance. */
    BCMOLT_DEVICE_DEVICE_READY_DATA_ID_STANDALONE = 4, /**< Standalone. */
    BCMOLT_DEVICE_DEVICE_READY_DATA_ID_CHIP_FAMILY = 5, /**< Chip Family. */
    BCMOLT_DEVICE_DEVICE_READY_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_device_ready_data_id__begin BCMOLT_DEVICE_DEVICE_READY_DATA_ID__BEGIN
#define bcmolt_device_device_ready_data_id_firmware_sw_version BCMOLT_DEVICE_DEVICE_READY_DATA_ID_FIRMWARE_SW_VERSION
#define bcmolt_device_device_ready_data_id_system_mode BCMOLT_DEVICE_DEVICE_READY_DATA_ID_SYSTEM_MODE
#define bcmolt_device_device_ready_data_id_keepalive_interval BCMOLT_DEVICE_DEVICE_READY_DATA_ID_KEEPALIVE_INTERVAL
#define bcmolt_device_device_ready_data_id_keepalive_tolerance BCMOLT_DEVICE_DEVICE_READY_DATA_ID_KEEPALIVE_TOLERANCE
#define bcmolt_device_device_ready_data_id_standalone BCMOLT_DEVICE_DEVICE_READY_DATA_ID_STANDALONE
#define bcmolt_device_device_ready_data_id_chip_family BCMOLT_DEVICE_DEVICE_READY_DATA_ID_CHIP_FAMILY
#define bcmolt_device_device_ready_data_id__num_of BCMOLT_DEVICE_DEVICE_READY_DATA_ID__NUM_OF
#define bcmolt_device_device_ready_data_id_all_properties 0xFF
#define bcmolt_device_device_ready_data_id_full_mask 0x3F

} bcmolt_device_device_ready_data_id;

/** Identifiers for all fields in a 'device_device_keep_alive_data'. */
typedef enum
{
    BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_SEQUENCE_NUMBER = 0, /**< sequence number. */
    BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_TIME_STAMP = 1, /**< time stamp. */
    BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_KEEPALIVE_INTERVAL = 2, /**< Keepalive Interval. */
    BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_KEEPALIVE_TOLERANCE = 3, /**< Keepalive Tolerance. */
    BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_device_keep_alive_data_id__begin BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID__BEGIN
#define bcmolt_device_device_keep_alive_data_id_sequence_number BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_SEQUENCE_NUMBER
#define bcmolt_device_device_keep_alive_data_id_time_stamp BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_TIME_STAMP
#define bcmolt_device_device_keep_alive_data_id_keepalive_interval BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_KEEPALIVE_INTERVAL
#define bcmolt_device_device_keep_alive_data_id_keepalive_tolerance BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_KEEPALIVE_TOLERANCE
#define bcmolt_device_device_keep_alive_data_id__num_of BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID__NUM_OF
#define bcmolt_device_device_keep_alive_data_id_all_properties 0xFF
#define bcmolt_device_device_keep_alive_data_id_full_mask 0xF

} bcmolt_device_device_keep_alive_data_id;

/** Identifiers for all fields in a 'device_connection_failure_data'. */
typedef enum
{
    BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID_REASON = 0, /**< Connection fail reason. */
    BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID_DEVICE_IN_RESET = 1, /**< Device In Reset. */
    BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID_ERROR_TEXT = 2, /**< Error Text. */
    BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_connection_failure_data_id__begin BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID__BEGIN
#define bcmolt_device_connection_failure_data_id_reason BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID_REASON
#define bcmolt_device_connection_failure_data_id_device_in_reset BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID_DEVICE_IN_RESET
#define bcmolt_device_connection_failure_data_id_error_text BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID_ERROR_TEXT
#define bcmolt_device_connection_failure_data_id__num_of BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID__NUM_OF
#define bcmolt_device_connection_failure_data_id_all_properties 0xFF
#define bcmolt_device_connection_failure_data_id_full_mask 0x7

} bcmolt_device_connection_failure_data_id;

/** Identifiers for all fields in a 'device_connection_complete_data'. */
typedef enum
{
    BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID_STANDALONE = 0, /**< Standalone. */
    BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID_SYSTEM_MODE = 1, /**< System Mode. */
    BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_connection_complete_data_id__begin BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID__BEGIN
#define bcmolt_device_connection_complete_data_id_standalone BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID_STANDALONE
#define bcmolt_device_connection_complete_data_id_system_mode BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID_SYSTEM_MODE
#define bcmolt_device_connection_complete_data_id__num_of BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID__NUM_OF
#define bcmolt_device_connection_complete_data_id_all_properties 0xFF
#define bcmolt_device_connection_complete_data_id_full_mask 0x3

} bcmolt_device_connection_complete_data_id;

/** Identifiers for all fields in a 'device_disconnection_complete_data'. */
typedef enum
{
    BCMOLT_DEVICE_DISCONNECTION_COMPLETE_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_DISCONNECTION_COMPLETE_DATA_ID_REASON = 0, /**< disconnect reason. */
    BCMOLT_DEVICE_DISCONNECTION_COMPLETE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_disconnection_complete_data_id__begin BCMOLT_DEVICE_DISCONNECTION_COMPLETE_DATA_ID__BEGIN
#define bcmolt_device_disconnection_complete_data_id_reason BCMOLT_DEVICE_DISCONNECTION_COMPLETE_DATA_ID_REASON
#define bcmolt_device_disconnection_complete_data_id__num_of BCMOLT_DEVICE_DISCONNECTION_COMPLETE_DATA_ID__NUM_OF
#define bcmolt_device_disconnection_complete_data_id_all_properties 0xFF
#define bcmolt_device_disconnection_complete_data_id_full_mask 0x1

} bcmolt_device_disconnection_complete_data_id;

/** Identifiers for all fields in a 'device_sw_error_data'. */
typedef enum
{
    BCMOLT_DEVICE_SW_ERROR_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_SW_ERROR_DATA_ID_TASK_NAME = 0, /**< task name. */
    BCMOLT_DEVICE_SW_ERROR_DATA_ID_FILE_NAME = 1, /**< file name. */
    BCMOLT_DEVICE_SW_ERROR_DATA_ID_LINE_NUMBER = 2, /**< line number. */
    BCMOLT_DEVICE_SW_ERROR_DATA_ID_PON_NI = 3, /**< pon_ni. */
    BCMOLT_DEVICE_SW_ERROR_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_sw_error_data_id__begin BCMOLT_DEVICE_SW_ERROR_DATA_ID__BEGIN
#define bcmolt_device_sw_error_data_id_task_name BCMOLT_DEVICE_SW_ERROR_DATA_ID_TASK_NAME
#define bcmolt_device_sw_error_data_id_file_name BCMOLT_DEVICE_SW_ERROR_DATA_ID_FILE_NAME
#define bcmolt_device_sw_error_data_id_line_number BCMOLT_DEVICE_SW_ERROR_DATA_ID_LINE_NUMBER
#define bcmolt_device_sw_error_data_id_pon_ni BCMOLT_DEVICE_SW_ERROR_DATA_ID_PON_NI
#define bcmolt_device_sw_error_data_id__num_of BCMOLT_DEVICE_SW_ERROR_DATA_ID__NUM_OF
#define bcmolt_device_sw_error_data_id_all_properties 0xFF
#define bcmolt_device_sw_error_data_id_full_mask 0xF

} bcmolt_device_sw_error_data_id;

/** Identifiers for all fields in a 'device_sw_exception_data'. */
typedef enum
{
    BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID_CPU_ID = 0, /**< CPU ID. */
    BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID_TEXT = 1, /**< text. */
    BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_sw_exception_data_id__begin BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID__BEGIN
#define bcmolt_device_sw_exception_data_id_cpu_id BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID_CPU_ID
#define bcmolt_device_sw_exception_data_id_text BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID_TEXT
#define bcmolt_device_sw_exception_data_id__num_of BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID__NUM_OF
#define bcmolt_device_sw_exception_data_id_all_properties 0xFF
#define bcmolt_device_sw_exception_data_id_full_mask 0x3

} bcmolt_device_sw_exception_data_id;

/** Identifiers for all fields in a 'device_image_transfer_complete_data'. */
typedef enum
{
    BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID_IMAGE_TYPE = 0, /**< Image type. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID_BLOCK_NUMBER = 1, /**< Block number. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID_STATUS = 2, /**< Status. */
    BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_image_transfer_complete_data_id__begin BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID__BEGIN
#define bcmolt_device_image_transfer_complete_data_id_image_type BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID_IMAGE_TYPE
#define bcmolt_device_image_transfer_complete_data_id_block_number BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID_BLOCK_NUMBER
#define bcmolt_device_image_transfer_complete_data_id_status BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID_STATUS
#define bcmolt_device_image_transfer_complete_data_id__num_of BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID__NUM_OF
#define bcmolt_device_image_transfer_complete_data_id_all_properties 0xFF
#define bcmolt_device_image_transfer_complete_data_id_full_mask 0x7

} bcmolt_device_image_transfer_complete_data_id;

/** Identifiers for all fields in a 'device_ddr_test_complete_data'. */
typedef enum
{
    BCMOLT_DEVICE_DDR_TEST_COMPLETE_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_DDR_TEST_COMPLETE_DATA_ID_DDR_TEST = 0, /**< DDR Test. */
    BCMOLT_DEVICE_DDR_TEST_COMPLETE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_ddr_test_complete_data_id__begin BCMOLT_DEVICE_DDR_TEST_COMPLETE_DATA_ID__BEGIN
#define bcmolt_device_ddr_test_complete_data_id_ddr_test BCMOLT_DEVICE_DDR_TEST_COMPLETE_DATA_ID_DDR_TEST
#define bcmolt_device_ddr_test_complete_data_id__num_of BCMOLT_DEVICE_DDR_TEST_COMPLETE_DATA_ID__NUM_OF
#define bcmolt_device_ddr_test_complete_data_id_all_properties 0xFF
#define bcmolt_device_ddr_test_complete_data_id_full_mask 0x1

} bcmolt_device_ddr_test_complete_data_id;

/** Identifiers for all fields in a 'device_sw_health_check_failure_data'. */
typedef enum
{
    BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID_MODULE_NAME = 0, /**< module name. */
    BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID_MODULE_ID = 1, /**< module id. */
    BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID_STATUS = 2, /**< status. */
    BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_sw_health_check_failure_data_id__begin BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID__BEGIN
#define bcmolt_device_sw_health_check_failure_data_id_module_name BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID_MODULE_NAME
#define bcmolt_device_sw_health_check_failure_data_id_module_id BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID_MODULE_ID
#define bcmolt_device_sw_health_check_failure_data_id_status BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID_STATUS
#define bcmolt_device_sw_health_check_failure_data_id__num_of BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID__NUM_OF
#define bcmolt_device_sw_health_check_failure_data_id_all_properties 0xFF
#define bcmolt_device_sw_health_check_failure_data_id_full_mask 0x7

} bcmolt_device_sw_health_check_failure_data_id;

/** Identifiers for all fields in a 'device_change_inni_mux_data'. */
typedef enum
{
    BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID_MUX = 0, /**< mux. */
    BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID_NNI_CONNECTION = 1, /**< nni_connection. */
    BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_change_inni_mux_data_id__begin BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID__BEGIN
#define bcmolt_device_change_inni_mux_data_id_mux BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID_MUX
#define bcmolt_device_change_inni_mux_data_id_nni_connection BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID_NNI_CONNECTION
#define bcmolt_device_change_inni_mux_data_id__num_of BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID__NUM_OF
#define bcmolt_device_change_inni_mux_data_id_all_properties 0xFF
#define bcmolt_device_change_inni_mux_data_id_full_mask 0x3

} bcmolt_device_change_inni_mux_data_id;

/** Identifiers for all fields in a 'device_inni_mux_configuration_completed_data'. */
typedef enum
{
    BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID_NEW_MUX = 0, /**< new_mux. */
    BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID_STATUS = 1, /**< status. */
    BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_inni_mux_configuration_completed_data_id__begin BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID__BEGIN
#define bcmolt_device_inni_mux_configuration_completed_data_id_new_mux BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID_NEW_MUX
#define bcmolt_device_inni_mux_configuration_completed_data_id_status BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID_STATUS
#define bcmolt_device_inni_mux_configuration_completed_data_id__num_of BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_device_inni_mux_configuration_completed_data_id_all_properties 0xFF
#define bcmolt_device_inni_mux_configuration_completed_data_id_full_mask 0x3

} bcmolt_device_inni_mux_configuration_completed_data_id;

/** Identifiers for all fields in a 'device_tod_calibration_done_data'. */
typedef enum
{
    BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID_RESULT = 0, /**< result. */
    BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID_PON_NI = 1, /**< pon_ni. */
    BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID_FAIL_REASON = 2, /**< fail reason. */
    BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_tod_calibration_done_data_id__begin BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID__BEGIN
#define bcmolt_device_tod_calibration_done_data_id_result BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID_RESULT
#define bcmolt_device_tod_calibration_done_data_id_pon_ni BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID_PON_NI
#define bcmolt_device_tod_calibration_done_data_id_fail_reason BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID_FAIL_REASON
#define bcmolt_device_tod_calibration_done_data_id__num_of BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID__NUM_OF
#define bcmolt_device_tod_calibration_done_data_id_all_properties 0xFF
#define bcmolt_device_tod_calibration_done_data_id_full_mask 0x7

} bcmolt_device_tod_calibration_done_data_id;

/** Identifiers for all fields in a 'device_auto_cfg_data'. */
typedef enum
{
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_CONNECTION_COMPLETE = 0, /**< Connection Complete. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_CONNECTION_ESTABLISHED = 1, /**< Connection Established. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_CONNECTION_FAILURE = 2, /**< Connection Failure. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DDR_TEST_COMPLETE = 3, /**< DDR Test Complete. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DEVICE_KEEP_ALIVE = 4, /**< Device Keep Alive. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DEVICE_READY = 5, /**< Device Ready. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DISCONNECTION_COMPLETE = 6, /**< Disconnection Complete. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_IMAGE_TRANSFER_COMPLETE = 7, /**< Image Transfer Complete. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_INNI_MUX_CONFIGURATION_COMPLETED = 8, /**< INNI mux configuration completed. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_SW_ERROR = 9, /**< sw error. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_SW_EXCEPTION = 10, /**< sw exception. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_SW_HEALTH_CHECK_FAILURE = 11, /**< Software Health Check Failure. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID_TOD_CALIBRATION_DONE = 12, /**< tod calibration done. */
    BCMOLT_DEVICE_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_device_auto_cfg_data_id__begin BCMOLT_DEVICE_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_device_auto_cfg_data_id_connection_complete BCMOLT_DEVICE_AUTO_CFG_DATA_ID_CONNECTION_COMPLETE
#define bcmolt_device_auto_cfg_data_id_connection_established BCMOLT_DEVICE_AUTO_CFG_DATA_ID_CONNECTION_ESTABLISHED
#define bcmolt_device_auto_cfg_data_id_connection_failure BCMOLT_DEVICE_AUTO_CFG_DATA_ID_CONNECTION_FAILURE
#define bcmolt_device_auto_cfg_data_id_ddr_test_complete BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DDR_TEST_COMPLETE
#define bcmolt_device_auto_cfg_data_id_device_keep_alive BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DEVICE_KEEP_ALIVE
#define bcmolt_device_auto_cfg_data_id_device_ready BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DEVICE_READY
#define bcmolt_device_auto_cfg_data_id_disconnection_complete BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DISCONNECTION_COMPLETE
#define bcmolt_device_auto_cfg_data_id_image_transfer_complete BCMOLT_DEVICE_AUTO_CFG_DATA_ID_IMAGE_TRANSFER_COMPLETE
#define bcmolt_device_auto_cfg_data_id_inni_mux_configuration_completed BCMOLT_DEVICE_AUTO_CFG_DATA_ID_INNI_MUX_CONFIGURATION_COMPLETED
#define bcmolt_device_auto_cfg_data_id_sw_error BCMOLT_DEVICE_AUTO_CFG_DATA_ID_SW_ERROR
#define bcmolt_device_auto_cfg_data_id_sw_exception BCMOLT_DEVICE_AUTO_CFG_DATA_ID_SW_EXCEPTION
#define bcmolt_device_auto_cfg_data_id_sw_health_check_failure BCMOLT_DEVICE_AUTO_CFG_DATA_ID_SW_HEALTH_CHECK_FAILURE
#define bcmolt_device_auto_cfg_data_id_tod_calibration_done BCMOLT_DEVICE_AUTO_CFG_DATA_ID_TOD_CALIBRATION_DONE
#define bcmolt_device_auto_cfg_data_id__num_of BCMOLT_DEVICE_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_device_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_device_auto_cfg_data_id_full_mask 0x1FFF

} bcmolt_device_auto_cfg_data_id;

/** Identifiers for all fields in a 'erps_interface_key'. */
typedef enum
{
    BCMOLT_ERPS_INTERFACE_KEY_ID__BEGIN = 0,
    BCMOLT_ERPS_INTERFACE_KEY_ID_ID = 0, /**< ID. */
    BCMOLT_ERPS_INTERFACE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_interface_key_id__begin BCMOLT_ERPS_INTERFACE_KEY_ID__BEGIN
#define bcmolt_erps_interface_key_id_id BCMOLT_ERPS_INTERFACE_KEY_ID_ID
#define bcmolt_erps_interface_key_id__num_of BCMOLT_ERPS_INTERFACE_KEY_ID__NUM_OF
#define bcmolt_erps_interface_key_id_all_properties 0xFF
#define bcmolt_erps_interface_key_id_full_mask 0x1

} bcmolt_erps_interface_key_id;

/** Identifiers for all fields in a 'erps_interface_cfg_data'. */
typedef enum
{
    BCMOLT_ERPS_INTERFACE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_EAST_PORT = 0, /**< East Port. */
    BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_WEST_PORT = 1, /**< West Port. */
    BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_CONTROL_VLAN_ID = 2, /**< Control VLAN Id. */
    BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_EAST_PORT_STATE = 9, /**< East Port State. */
    BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_WEST_PORT_STATE = 10, /**< West Port State. */
    BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_STATE = 11, /**< state. */
    BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_SUB_PORT_LIST = 13, /**< List of Sub_Ports. */
    BCMOLT_ERPS_INTERFACE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_interface_cfg_data_id__begin BCMOLT_ERPS_INTERFACE_CFG_DATA_ID__BEGIN
#define bcmolt_erps_interface_cfg_data_id_east_port BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_EAST_PORT
#define bcmolt_erps_interface_cfg_data_id_west_port BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_WEST_PORT
#define bcmolt_erps_interface_cfg_data_id_control_vlan_id BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_CONTROL_VLAN_ID
#define bcmolt_erps_interface_cfg_data_id_east_port_state BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_EAST_PORT_STATE
#define bcmolt_erps_interface_cfg_data_id_west_port_state BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_WEST_PORT_STATE
#define bcmolt_erps_interface_cfg_data_id_state BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_STATE
#define bcmolt_erps_interface_cfg_data_id_sub_port_list BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_SUB_PORT_LIST
#define bcmolt_erps_interface_cfg_data_id__num_of BCMOLT_ERPS_INTERFACE_CFG_DATA_ID__NUM_OF
#define bcmolt_erps_interface_cfg_data_id_all_properties 0xFF
#define bcmolt_erps_interface_cfg_data_id_full_mask 0x2E07

} bcmolt_erps_interface_cfg_data_id;

/** Identifiers for all fields in a 'erps_interface_set_ring_port_control_data'. */
typedef enum
{
    BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID__BEGIN = 0,
    BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID_COMMAND = 0, /**< command. */
    BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID_PORT = 1, /**< port. */
    BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_interface_set_ring_port_control_data_id__begin BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID__BEGIN
#define bcmolt_erps_interface_set_ring_port_control_data_id_command BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID_COMMAND
#define bcmolt_erps_interface_set_ring_port_control_data_id_port BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID_PORT
#define bcmolt_erps_interface_set_ring_port_control_data_id__num_of BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID__NUM_OF
#define bcmolt_erps_interface_set_ring_port_control_data_id_all_properties 0xFF
#define bcmolt_erps_interface_set_ring_port_control_data_id_full_mask 0x3

} bcmolt_erps_interface_set_ring_port_control_data_id;

/** Identifiers for all fields in a 'erps_interface_ring_port_control_data'. */
typedef enum
{
    BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID__BEGIN = 0,
    BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_PORT_ID = 0, /**< port id. */
    BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_COMMAND = 1, /**< command. */
    BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_PORT_STATE = 2, /**< Port State. */
    BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_RESULT = 3, /**< Result. */
    BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_interface_ring_port_control_data_id__begin BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID__BEGIN
#define bcmolt_erps_interface_ring_port_control_data_id_port_id BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_PORT_ID
#define bcmolt_erps_interface_ring_port_control_data_id_command BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_COMMAND
#define bcmolt_erps_interface_ring_port_control_data_id_port_state BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_PORT_STATE
#define bcmolt_erps_interface_ring_port_control_data_id_result BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_RESULT
#define bcmolt_erps_interface_ring_port_control_data_id__num_of BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID__NUM_OF
#define bcmolt_erps_interface_ring_port_control_data_id_all_properties 0xFF
#define bcmolt_erps_interface_ring_port_control_data_id_full_mask 0xF

} bcmolt_erps_interface_ring_port_control_data_id;

/** Identifiers for all fields in a 'erps_interface_port_update_data'. */
typedef enum
{
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID__BEGIN = 0,
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID_COMMAND = 0, /**< Update an ERPS port. */
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID_INTF_REF = 2, /**< Port interface Reference. */
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID_PORT = 3, /**< Port to add or remove. */
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_interface_port_update_data_id__begin BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID__BEGIN
#define bcmolt_erps_interface_port_update_data_id_command BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID_COMMAND
#define bcmolt_erps_interface_port_update_data_id_intf_ref BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID_INTF_REF
#define bcmolt_erps_interface_port_update_data_id_port BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID_PORT
#define bcmolt_erps_interface_port_update_data_id__num_of BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID__NUM_OF
#define bcmolt_erps_interface_port_update_data_id_all_properties 0xFF
#define bcmolt_erps_interface_port_update_data_id_full_mask 0xD

} bcmolt_erps_interface_port_update_data_id;

/** Identifiers for all fields in a 'erps_interface_port_update_complete_data'. */
typedef enum
{
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID__BEGIN = 0,
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_COMMAND = 0, /**< Command just executed. */
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_INTF_REF = 1, /**< Modified Port. */
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_RESULT = 2, /**< Result of command pass/fail. */
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_PORT = 3, /**< ERPS Port just updated. */
    BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_interface_port_update_complete_data_id__begin BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID__BEGIN
#define bcmolt_erps_interface_port_update_complete_data_id_command BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_COMMAND
#define bcmolt_erps_interface_port_update_complete_data_id_intf_ref BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_INTF_REF
#define bcmolt_erps_interface_port_update_complete_data_id_result BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_RESULT
#define bcmolt_erps_interface_port_update_complete_data_id_port BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_PORT
#define bcmolt_erps_interface_port_update_complete_data_id__num_of BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID__NUM_OF
#define bcmolt_erps_interface_port_update_complete_data_id_all_properties 0xFF
#define bcmolt_erps_interface_port_update_complete_data_id_full_mask 0xF

} bcmolt_erps_interface_port_update_complete_data_id;

/** Identifiers for all fields in a 'erps_interface_auto_cfg_data'. */
typedef enum
{
    BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID_PORT_UPDATE_COMPLETE = 0, /**< erps port update completed. */
    BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID_RING_PORT_CONTROL = 1, /**< Ring Port Control. */
    BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_erps_interface_auto_cfg_data_id__begin BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_erps_interface_auto_cfg_data_id_port_update_complete BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID_PORT_UPDATE_COMPLETE
#define bcmolt_erps_interface_auto_cfg_data_id_ring_port_control BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID_RING_PORT_CONTROL
#define bcmolt_erps_interface_auto_cfg_data_id__num_of BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_erps_interface_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_erps_interface_auto_cfg_data_id_full_mask 0x3

} bcmolt_erps_interface_auto_cfg_data_id;

/** Identifiers for all fields in a 'eth_oam_key'. */
typedef enum
{
    BCMOLT_ETH_OAM_KEY_ID__BEGIN = 0,
    BCMOLT_ETH_OAM_KEY_ID_ID = 0, /**< id. */
    BCMOLT_ETH_OAM_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_key_id__begin BCMOLT_ETH_OAM_KEY_ID__BEGIN
#define bcmolt_eth_oam_key_id_id BCMOLT_ETH_OAM_KEY_ID_ID
#define bcmolt_eth_oam_key_id__num_of BCMOLT_ETH_OAM_KEY_ID__NUM_OF
#define bcmolt_eth_oam_key_id_all_properties 0xFF
#define bcmolt_eth_oam_key_id_full_mask 0x1

} bcmolt_eth_oam_key_id;

/** Identifiers for all fields in a 'eth_oam_cfg_data'. */
typedef enum
{
    BCMOLT_ETH_OAM_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ETH_OAM_CFG_DATA_ID_INTF_REF = 0, /**< Network Interface Reference. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_LOCAL_MEP = 1, /**< Local MEP. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_REMOTE_MEP = 2, /**< Remote MEP. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_STATE = 5, /**< Config State. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_SOURCE_MAC = 8, /**< Source MAC. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_DEST_MAC = 9, /**< Destination Mac. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_PKT_TAG_TYPE = 10, /**< Tag Count. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_O_VID = 11, /**< Outer Tag. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_O_PBITS = 12, /**< Outer PBits. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_O_TPID = 13, /**< Outer TPID. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_I_VID = 14, /**< Inner Tag. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_I_PBITS = 15, /**< Inner PBits. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_I_TPID = 16, /**< Inner TPID. */
    BCMOLT_ETH_OAM_CFG_DATA_ID_MEG = 17, /**< MEG Config. */
    BCMOLT_ETH_OAM_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_cfg_data_id__begin BCMOLT_ETH_OAM_CFG_DATA_ID__BEGIN
#define bcmolt_eth_oam_cfg_data_id_intf_ref BCMOLT_ETH_OAM_CFG_DATA_ID_INTF_REF
#define bcmolt_eth_oam_cfg_data_id_local_mep BCMOLT_ETH_OAM_CFG_DATA_ID_LOCAL_MEP
#define bcmolt_eth_oam_cfg_data_id_remote_mep BCMOLT_ETH_OAM_CFG_DATA_ID_REMOTE_MEP
#define bcmolt_eth_oam_cfg_data_id_state BCMOLT_ETH_OAM_CFG_DATA_ID_STATE
#define bcmolt_eth_oam_cfg_data_id_source_mac BCMOLT_ETH_OAM_CFG_DATA_ID_SOURCE_MAC
#define bcmolt_eth_oam_cfg_data_id_dest_mac BCMOLT_ETH_OAM_CFG_DATA_ID_DEST_MAC
#define bcmolt_eth_oam_cfg_data_id_pkt_tag_type BCMOLT_ETH_OAM_CFG_DATA_ID_PKT_TAG_TYPE
#define bcmolt_eth_oam_cfg_data_id_o_vid BCMOLT_ETH_OAM_CFG_DATA_ID_O_VID
#define bcmolt_eth_oam_cfg_data_id_o_pbits BCMOLT_ETH_OAM_CFG_DATA_ID_O_PBITS
#define bcmolt_eth_oam_cfg_data_id_o_tpid BCMOLT_ETH_OAM_CFG_DATA_ID_O_TPID
#define bcmolt_eth_oam_cfg_data_id_i_vid BCMOLT_ETH_OAM_CFG_DATA_ID_I_VID
#define bcmolt_eth_oam_cfg_data_id_i_pbits BCMOLT_ETH_OAM_CFG_DATA_ID_I_PBITS
#define bcmolt_eth_oam_cfg_data_id_i_tpid BCMOLT_ETH_OAM_CFG_DATA_ID_I_TPID
#define bcmolt_eth_oam_cfg_data_id_meg BCMOLT_ETH_OAM_CFG_DATA_ID_MEG
#define bcmolt_eth_oam_cfg_data_id__num_of BCMOLT_ETH_OAM_CFG_DATA_ID__NUM_OF
#define bcmolt_eth_oam_cfg_data_id_all_properties 0xFF
#define bcmolt_eth_oam_cfg_data_id_full_mask 0x3FF27

} bcmolt_eth_oam_cfg_data_id;

/** Identifiers for all fields in a 'eth_oam_ccm_event_data'. */
typedef enum
{
    BCMOLT_ETH_OAM_CCM_EVENT_DATA_ID__BEGIN = 1,
    BCMOLT_ETH_OAM_CCM_EVENT_DATA_ID_EVENT = 1, /**< CCM event. */
    BCMOLT_ETH_OAM_CCM_EVENT_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_ccm_event_data_id__begin BCMOLT_ETH_OAM_CCM_EVENT_DATA_ID__BEGIN
#define bcmolt_eth_oam_ccm_event_data_id_event BCMOLT_ETH_OAM_CCM_EVENT_DATA_ID_EVENT
#define bcmolt_eth_oam_ccm_event_data_id__num_of BCMOLT_ETH_OAM_CCM_EVENT_DATA_ID__NUM_OF
#define bcmolt_eth_oam_ccm_event_data_id_all_properties 0xFF
#define bcmolt_eth_oam_ccm_event_data_id_full_mask 0x2

} bcmolt_eth_oam_ccm_event_data_id;

/** Identifiers for all fields in a 'eth_oam_stats_data'. */
typedef enum
{
    BCMOLT_ETH_OAM_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_TX_COUNT = 0, /**< CCM Tx Count. */
    BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_RX_COUNT = 1, /**< CCM Rx Count. */
    BCMOLT_ETH_OAM_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_stats_data_id__begin BCMOLT_ETH_OAM_STATS_DATA_ID__BEGIN
#define bcmolt_eth_oam_stats_data_id_ccm_tx_count BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_TX_COUNT
#define bcmolt_eth_oam_stats_data_id_ccm_rx_count BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_RX_COUNT
#define bcmolt_eth_oam_stats_data_id__num_of BCMOLT_ETH_OAM_STATS_DATA_ID__NUM_OF
#define bcmolt_eth_oam_stats_data_id_all_properties 0xFF
#define bcmolt_eth_oam_stats_data_id_full_mask 0x3

} bcmolt_eth_oam_stats_data_id;

/** Identifiers for all fields in a 'eth_oam_set_mep_state_data'. */
typedef enum
{
    BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID__BEGIN = 0,
    BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID_TYPE = 0, /**< MEP Type. */
    BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID_STATE = 1, /**< MEP Control State. */
    BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_set_mep_state_data_id__begin BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID__BEGIN
#define bcmolt_eth_oam_set_mep_state_data_id_type BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID_TYPE
#define bcmolt_eth_oam_set_mep_state_data_id_state BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID_STATE
#define bcmolt_eth_oam_set_mep_state_data_id__num_of BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID__NUM_OF
#define bcmolt_eth_oam_set_mep_state_data_id_all_properties 0xFF
#define bcmolt_eth_oam_set_mep_state_data_id_full_mask 0x3

} bcmolt_eth_oam_set_mep_state_data_id;

/** Identifiers for all fields in a 'eth_oam_state_change_data'. */
typedef enum
{
    BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID__BEGIN = 0,
    BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID_RESULT = 0, /**< Command Result. */
    BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID_OLD_STATE = 1, /**< Old State. */
    BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID_NEW_STATE = 2, /**< New State. */
    BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_state_change_data_id__begin BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID__BEGIN
#define bcmolt_eth_oam_state_change_data_id_result BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID_RESULT
#define bcmolt_eth_oam_state_change_data_id_old_state BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID_OLD_STATE
#define bcmolt_eth_oam_state_change_data_id_new_state BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID_NEW_STATE
#define bcmolt_eth_oam_state_change_data_id__num_of BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID__NUM_OF
#define bcmolt_eth_oam_state_change_data_id_all_properties 0xFF
#define bcmolt_eth_oam_state_change_data_id_full_mask 0x7

} bcmolt_eth_oam_state_change_data_id;

/** Identifiers for all fields in a 'eth_oam_stats_cfg_data'. */
typedef enum
{
    BCMOLT_ETH_OAM_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ETH_OAM_STATS_CFG_DATA_ID_CCM_TX_COUNT = 0, /**< CCM Tx Count. */
    BCMOLT_ETH_OAM_STATS_CFG_DATA_ID_CCM_RX_COUNT = 1, /**< CCM Rx Count. */
    BCMOLT_ETH_OAM_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_stats_cfg_data_id__begin BCMOLT_ETH_OAM_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_eth_oam_stats_cfg_data_id_ccm_tx_count BCMOLT_ETH_OAM_STATS_CFG_DATA_ID_CCM_TX_COUNT
#define bcmolt_eth_oam_stats_cfg_data_id_ccm_rx_count BCMOLT_ETH_OAM_STATS_CFG_DATA_ID_CCM_RX_COUNT
#define bcmolt_eth_oam_stats_cfg_data_id__num_of BCMOLT_ETH_OAM_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_eth_oam_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_eth_oam_stats_cfg_data_id_full_mask 0x3

} bcmolt_eth_oam_stats_cfg_data_id;

/** Identifiers for all fields in a 'eth_oam_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_ETH_OAM_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_ETH_OAM_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ETH_OAM_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_stats_alarm_raised_data_id__begin BCMOLT_ETH_OAM_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_eth_oam_stats_alarm_raised_data_id_stat BCMOLT_ETH_OAM_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_eth_oam_stats_alarm_raised_data_id__num_of BCMOLT_ETH_OAM_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_eth_oam_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_eth_oam_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_eth_oam_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'eth_oam_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_ETH_OAM_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_ETH_OAM_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ETH_OAM_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_stats_alarm_cleared_data_id__begin BCMOLT_ETH_OAM_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_eth_oam_stats_alarm_cleared_data_id_stat BCMOLT_ETH_OAM_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_eth_oam_stats_alarm_cleared_data_id__num_of BCMOLT_ETH_OAM_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_eth_oam_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_eth_oam_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_eth_oam_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'eth_oam_auto_cfg_data'. */
typedef enum
{
    BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_CCM_EVENT = 0, /**< CFM CCM Event. */
    BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_STATE_CHANGE = 1, /**< State Change. */
    BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED = 2, /**< Stats Alarm Cleared. */
    BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED = 3, /**< Stats Alarm Raised. */
    BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_eth_oam_auto_cfg_data_id__begin BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_eth_oam_auto_cfg_data_id_ccm_event BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_CCM_EVENT
#define bcmolt_eth_oam_auto_cfg_data_id_state_change BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_STATE_CHANGE
#define bcmolt_eth_oam_auto_cfg_data_id_stats_alarm_cleared BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED
#define bcmolt_eth_oam_auto_cfg_data_id_stats_alarm_raised BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED
#define bcmolt_eth_oam_auto_cfg_data_id__num_of BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_eth_oam_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_eth_oam_auto_cfg_data_id_full_mask 0xF

} bcmolt_eth_oam_auto_cfg_data_id;

/** Identifiers for all fields in a 'flow_cfg_data'. */
typedef enum
{
    BCMOLT_FLOW_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_FLOW_CFG_DATA_ID_INGRESS_INTF = 0, /**< Ingress interface. */
    BCMOLT_FLOW_CFG_DATA_ID_EGRESS_INTF = 1, /**< Egress interface. */
    BCMOLT_FLOW_CFG_DATA_ID_ONU_ID = 2, /**< ONU ID. */
    BCMOLT_FLOW_CFG_DATA_ID_SVC_PORT_ID = 3, /**< Service Port ID. */
    BCMOLT_FLOW_CFG_DATA_ID_CLASSIFIER = 4, /**< Classifier. */
    BCMOLT_FLOW_CFG_DATA_ID_PRIORITY = 5, /**< Priority. */
    BCMOLT_FLOW_CFG_DATA_ID_ACTION = 6, /**< Action. */
    BCMOLT_FLOW_CFG_DATA_ID_GROUP_ID = 7, /**< Group ID. */
    BCMOLT_FLOW_CFG_DATA_ID_EGRESS_QOS = 8, /**< Egress qos. */
    BCMOLT_FLOW_CFG_DATA_ID_STATE = 9, /**< Flow State. */
    BCMOLT_FLOW_CFG_DATA_ID_LOCAL_SWITCHING = 10, /**< Local Switching. */
    BCMOLT_FLOW_CFG_DATA_ID_COOKIE = 11, /**< Cookie. */
    BCMOLT_FLOW_CFG_DATA_ID_STATISTICS = 12, /**< statistics control. */
    BCMOLT_FLOW_CFG_DATA_ID_MAC_TABLE_MISS_ACTION = 13, /**< action on mac table miss. */
    BCMOLT_FLOW_CFG_DATA_ID_POLICER_PROFILE = 14, /**< policer profile. */
    BCMOLT_FLOW_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_cfg_data_id__begin BCMOLT_FLOW_CFG_DATA_ID__BEGIN
#define bcmolt_flow_cfg_data_id_ingress_intf BCMOLT_FLOW_CFG_DATA_ID_INGRESS_INTF
#define bcmolt_flow_cfg_data_id_egress_intf BCMOLT_FLOW_CFG_DATA_ID_EGRESS_INTF
#define bcmolt_flow_cfg_data_id_onu_id BCMOLT_FLOW_CFG_DATA_ID_ONU_ID
#define bcmolt_flow_cfg_data_id_svc_port_id BCMOLT_FLOW_CFG_DATA_ID_SVC_PORT_ID
#define bcmolt_flow_cfg_data_id_classifier BCMOLT_FLOW_CFG_DATA_ID_CLASSIFIER
#define bcmolt_flow_cfg_data_id_priority BCMOLT_FLOW_CFG_DATA_ID_PRIORITY
#define bcmolt_flow_cfg_data_id_action BCMOLT_FLOW_CFG_DATA_ID_ACTION
#define bcmolt_flow_cfg_data_id_group_id BCMOLT_FLOW_CFG_DATA_ID_GROUP_ID
#define bcmolt_flow_cfg_data_id_egress_qos BCMOLT_FLOW_CFG_DATA_ID_EGRESS_QOS
#define bcmolt_flow_cfg_data_id_state BCMOLT_FLOW_CFG_DATA_ID_STATE
#define bcmolt_flow_cfg_data_id_local_switching BCMOLT_FLOW_CFG_DATA_ID_LOCAL_SWITCHING
#define bcmolt_flow_cfg_data_id_cookie BCMOLT_FLOW_CFG_DATA_ID_COOKIE
#define bcmolt_flow_cfg_data_id_statistics BCMOLT_FLOW_CFG_DATA_ID_STATISTICS
#define bcmolt_flow_cfg_data_id_mac_table_miss_action BCMOLT_FLOW_CFG_DATA_ID_MAC_TABLE_MISS_ACTION
#define bcmolt_flow_cfg_data_id_policer_profile BCMOLT_FLOW_CFG_DATA_ID_POLICER_PROFILE
#define bcmolt_flow_cfg_data_id__num_of BCMOLT_FLOW_CFG_DATA_ID__NUM_OF
#define bcmolt_flow_cfg_data_id_all_properties 0xFF
#define bcmolt_flow_cfg_data_id_full_mask 0x7FFF

} bcmolt_flow_cfg_data_id;

/** Identifiers for all fields in a 'flow_key'. */
typedef enum
{
    BCMOLT_FLOW_KEY_ID__BEGIN = 0,
    BCMOLT_FLOW_KEY_ID_FLOW_ID = 0, /**< Flow ID. */
    BCMOLT_FLOW_KEY_ID_FLOW_TYPE = 1, /**< Flow type. */
    BCMOLT_FLOW_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_key_id__begin BCMOLT_FLOW_KEY_ID__BEGIN
#define bcmolt_flow_key_id_flow_id BCMOLT_FLOW_KEY_ID_FLOW_ID
#define bcmolt_flow_key_id_flow_type BCMOLT_FLOW_KEY_ID_FLOW_TYPE
#define bcmolt_flow_key_id__num_of BCMOLT_FLOW_KEY_ID__NUM_OF
#define bcmolt_flow_key_id_all_properties 0xFF
#define bcmolt_flow_key_id_full_mask 0x3

} bcmolt_flow_key_id;

/** Identifiers for all fields in a 'flow_stats_data'. */
typedef enum
{
    BCMOLT_FLOW_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_FLOW_STATS_DATA_ID_RX_PACKETS = 0, /**< Received packets. */
    BCMOLT_FLOW_STATS_DATA_ID_RX_BYTES = 1, /**< Received bytes. */
    BCMOLT_FLOW_STATS_DATA_ID_TX_PACKETS = 2, /**< Transmitted packets. */
    BCMOLT_FLOW_STATS_DATA_ID_TX_BYTES = 3, /**< Transmitted bytes. */
    BCMOLT_FLOW_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_stats_data_id__begin BCMOLT_FLOW_STATS_DATA_ID__BEGIN
#define bcmolt_flow_stats_data_id_rx_packets BCMOLT_FLOW_STATS_DATA_ID_RX_PACKETS
#define bcmolt_flow_stats_data_id_rx_bytes BCMOLT_FLOW_STATS_DATA_ID_RX_BYTES
#define bcmolt_flow_stats_data_id_tx_packets BCMOLT_FLOW_STATS_DATA_ID_TX_PACKETS
#define bcmolt_flow_stats_data_id_tx_bytes BCMOLT_FLOW_STATS_DATA_ID_TX_BYTES
#define bcmolt_flow_stats_data_id__num_of BCMOLT_FLOW_STATS_DATA_ID__NUM_OF
#define bcmolt_flow_stats_data_id_all_properties 0xFF
#define bcmolt_flow_stats_data_id_full_mask 0xF

} bcmolt_flow_stats_data_id;

/** Identifiers for all fields in a 'flow_send_eth_packet_data'. */
typedef enum
{
    BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID__BEGIN = 0,
    BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_BUFFER = 0, /**< buffer. */
    BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_INJECT_TYPE = 1, /**< Inject Type. */
    BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_INGRESS_INTF = 2, /**< Ingress Interface. */
    BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_SVC_PORT_ID = 3, /**< Service Port Id. */
    BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_send_eth_packet_data_id__begin BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID__BEGIN
#define bcmolt_flow_send_eth_packet_data_id_buffer BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_BUFFER
#define bcmolt_flow_send_eth_packet_data_id_inject_type BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_INJECT_TYPE
#define bcmolt_flow_send_eth_packet_data_id_ingress_intf BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_INGRESS_INTF
#define bcmolt_flow_send_eth_packet_data_id_svc_port_id BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_SVC_PORT_ID
#define bcmolt_flow_send_eth_packet_data_id__num_of BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID__NUM_OF
#define bcmolt_flow_send_eth_packet_data_id_all_properties 0xFF
#define bcmolt_flow_send_eth_packet_data_id_full_mask 0xF

} bcmolt_flow_send_eth_packet_data_id;

/** Identifiers for all fields in a 'flow_stats_cfg_data'. */
typedef enum
{
    BCMOLT_FLOW_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_FLOW_STATS_CFG_DATA_ID_RX_PACKETS = 0, /**< Received packets. */
    BCMOLT_FLOW_STATS_CFG_DATA_ID_RX_BYTES = 1, /**< Received bytes. */
    BCMOLT_FLOW_STATS_CFG_DATA_ID_TX_PACKETS = 2, /**< Transmitted packets. */
    BCMOLT_FLOW_STATS_CFG_DATA_ID_TX_BYTES = 3, /**< Transmitted bytes. */
    BCMOLT_FLOW_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_stats_cfg_data_id__begin BCMOLT_FLOW_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_flow_stats_cfg_data_id_rx_packets BCMOLT_FLOW_STATS_CFG_DATA_ID_RX_PACKETS
#define bcmolt_flow_stats_cfg_data_id_rx_bytes BCMOLT_FLOW_STATS_CFG_DATA_ID_RX_BYTES
#define bcmolt_flow_stats_cfg_data_id_tx_packets BCMOLT_FLOW_STATS_CFG_DATA_ID_TX_PACKETS
#define bcmolt_flow_stats_cfg_data_id_tx_bytes BCMOLT_FLOW_STATS_CFG_DATA_ID_TX_BYTES
#define bcmolt_flow_stats_cfg_data_id__num_of BCMOLT_FLOW_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_flow_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_flow_stats_cfg_data_id_full_mask 0xF

} bcmolt_flow_stats_cfg_data_id;

/** Identifiers for all fields in a 'flow_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_FLOW_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_FLOW_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_FLOW_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_stats_alarm_raised_data_id__begin BCMOLT_FLOW_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_flow_stats_alarm_raised_data_id_stat BCMOLT_FLOW_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_flow_stats_alarm_raised_data_id__num_of BCMOLT_FLOW_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_flow_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_flow_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_flow_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'flow_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_FLOW_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_FLOW_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_FLOW_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_stats_alarm_cleared_data_id__begin BCMOLT_FLOW_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_flow_stats_alarm_cleared_data_id_stat BCMOLT_FLOW_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_flow_stats_alarm_cleared_data_id__num_of BCMOLT_FLOW_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_flow_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_flow_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_flow_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'flow_auto_cfg_data'. */
typedef enum
{
    BCMOLT_FLOW_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_FLOW_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED = 0, /**< Statistics Alarm Cleared. */
    BCMOLT_FLOW_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED = 1, /**< Statistics Alarm Raised. */
    BCMOLT_FLOW_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_flow_auto_cfg_data_id__begin BCMOLT_FLOW_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_flow_auto_cfg_data_id_stats_alarm_cleared BCMOLT_FLOW_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED
#define bcmolt_flow_auto_cfg_data_id_stats_alarm_raised BCMOLT_FLOW_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED
#define bcmolt_flow_auto_cfg_data_id__num_of BCMOLT_FLOW_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_flow_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_flow_auto_cfg_data_id_full_mask 0x3

} bcmolt_flow_auto_cfg_data_id;

/** Identifiers for all fields in a 'gpio_key'. */
typedef enum
{
    BCMOLT_GPIO_KEY_ID__BEGIN = 0,
    BCMOLT_GPIO_KEY_ID_DEVICE_ID = 0, /**< Device ID. */
    BCMOLT_GPIO_KEY_ID_GPIO_ID = 1, /**< GPIO ID. */
    BCMOLT_GPIO_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_gpio_key_id__begin BCMOLT_GPIO_KEY_ID__BEGIN
#define bcmolt_gpio_key_id_device_id BCMOLT_GPIO_KEY_ID_DEVICE_ID
#define bcmolt_gpio_key_id_gpio_id BCMOLT_GPIO_KEY_ID_GPIO_ID
#define bcmolt_gpio_key_id__num_of BCMOLT_GPIO_KEY_ID__NUM_OF
#define bcmolt_gpio_key_id_all_properties 0xFF
#define bcmolt_gpio_key_id_full_mask 0x3

} bcmolt_gpio_key_id;

/** Identifiers for all fields in a 'gpio_cfg_data'. */
typedef enum
{
    BCMOLT_GPIO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_GPIO_CFG_DATA_ID_DIRECTION = 0, /**< Direction. */
    BCMOLT_GPIO_CFG_DATA_ID_VALUE = 1, /**< Value. */
    BCMOLT_GPIO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_gpio_cfg_data_id__begin BCMOLT_GPIO_CFG_DATA_ID__BEGIN
#define bcmolt_gpio_cfg_data_id_direction BCMOLT_GPIO_CFG_DATA_ID_DIRECTION
#define bcmolt_gpio_cfg_data_id_value BCMOLT_GPIO_CFG_DATA_ID_VALUE
#define bcmolt_gpio_cfg_data_id__num_of BCMOLT_GPIO_CFG_DATA_ID__NUM_OF
#define bcmolt_gpio_cfg_data_id_all_properties 0xFF
#define bcmolt_gpio_cfg_data_id_full_mask 0x3

} bcmolt_gpio_cfg_data_id;

/** Identifiers for all fields in a 'group_cfg_data'. */
typedef enum
{
    BCMOLT_GROUP_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_GROUP_CFG_DATA_ID_MEMBERS = 0, /**< Member. */
    BCMOLT_GROUP_CFG_DATA_ID_COOKIE = 1, /**< Application cookie. */
    BCMOLT_GROUP_CFG_DATA_ID_TYPE = 2, /**< Type of the group. */
    BCMOLT_GROUP_CFG_DATA_ID_STATE = 3, /**< group state. */
    BCMOLT_GROUP_CFG_DATA_ID_ACTION = 4, /**< Action. */
    BCMOLT_GROUP_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_group_cfg_data_id__begin BCMOLT_GROUP_CFG_DATA_ID__BEGIN
#define bcmolt_group_cfg_data_id_members BCMOLT_GROUP_CFG_DATA_ID_MEMBERS
#define bcmolt_group_cfg_data_id_cookie BCMOLT_GROUP_CFG_DATA_ID_COOKIE
#define bcmolt_group_cfg_data_id_type BCMOLT_GROUP_CFG_DATA_ID_TYPE
#define bcmolt_group_cfg_data_id_state BCMOLT_GROUP_CFG_DATA_ID_STATE
#define bcmolt_group_cfg_data_id_action BCMOLT_GROUP_CFG_DATA_ID_ACTION
#define bcmolt_group_cfg_data_id__num_of BCMOLT_GROUP_CFG_DATA_ID__NUM_OF
#define bcmolt_group_cfg_data_id_all_properties 0xFF
#define bcmolt_group_cfg_data_id_full_mask 0x1F

} bcmolt_group_cfg_data_id;

/** Identifiers for all fields in a 'group_key'. */
typedef enum
{
    BCMOLT_GROUP_KEY_ID__BEGIN = 0,
    BCMOLT_GROUP_KEY_ID_ID = 0, /**< Group ID. */
    BCMOLT_GROUP_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_group_key_id__begin BCMOLT_GROUP_KEY_ID__BEGIN
#define bcmolt_group_key_id_id BCMOLT_GROUP_KEY_ID_ID
#define bcmolt_group_key_id__num_of BCMOLT_GROUP_KEY_ID__NUM_OF
#define bcmolt_group_key_id_all_properties 0xFF
#define bcmolt_group_key_id_full_mask 0x1

} bcmolt_group_key_id;

/** Identifiers for all fields in a 'group_members_update_data'. */
typedef enum
{
    BCMOLT_GROUP_MEMBERS_UPDATE_DATA_ID__BEGIN = 0,
    BCMOLT_GROUP_MEMBERS_UPDATE_DATA_ID_MEMBERS_CMD = 0, /**< members_cmd. */
    BCMOLT_GROUP_MEMBERS_UPDATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_group_members_update_data_id__begin BCMOLT_GROUP_MEMBERS_UPDATE_DATA_ID__BEGIN
#define bcmolt_group_members_update_data_id_members_cmd BCMOLT_GROUP_MEMBERS_UPDATE_DATA_ID_MEMBERS_CMD
#define bcmolt_group_members_update_data_id__num_of BCMOLT_GROUP_MEMBERS_UPDATE_DATA_ID__NUM_OF
#define bcmolt_group_members_update_data_id_all_properties 0xFF
#define bcmolt_group_members_update_data_id_full_mask 0x1

} bcmolt_group_members_update_data_id;

/** Identifiers for all fields in a 'group_complete_members_update_data'. */
typedef enum
{
    BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID__BEGIN = 0,
    BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID_RESULT = 0, /**< result. */
    BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_group_complete_members_update_data_id__begin BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID__BEGIN
#define bcmolt_group_complete_members_update_data_id_result BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID_RESULT
#define bcmolt_group_complete_members_update_data_id_fail_reason BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID_FAIL_REASON
#define bcmolt_group_complete_members_update_data_id__num_of BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID__NUM_OF
#define bcmolt_group_complete_members_update_data_id_all_properties 0xFF
#define bcmolt_group_complete_members_update_data_id_full_mask 0x3

} bcmolt_group_complete_members_update_data_id;

/** Identifiers for all fields in a 'group_auto_cfg_data'. */
typedef enum
{
    BCMOLT_GROUP_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_GROUP_AUTO_CFG_DATA_ID_COMPLETE_MEMBERS_UPDATE = 0, /**< complete_members_update. */
    BCMOLT_GROUP_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_group_auto_cfg_data_id__begin BCMOLT_GROUP_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_group_auto_cfg_data_id_complete_members_update BCMOLT_GROUP_AUTO_CFG_DATA_ID_COMPLETE_MEMBERS_UPDATE
#define bcmolt_group_auto_cfg_data_id__num_of BCMOLT_GROUP_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_group_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_group_auto_cfg_data_id_full_mask 0x1

} bcmolt_group_auto_cfg_data_id;

/** Identifiers for all fields in a 'host_log_key'. */
typedef enum
{
    BCMOLT_HOST_LOG_KEY_ID__BEGIN = 1,
    BCMOLT_HOST_LOG_KEY_ID_NAME = 1, /**< name. */
    BCMOLT_HOST_LOG_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_host_log_key_id__begin BCMOLT_HOST_LOG_KEY_ID__BEGIN
#define bcmolt_host_log_key_id_name BCMOLT_HOST_LOG_KEY_ID_NAME
#define bcmolt_host_log_key_id__num_of BCMOLT_HOST_LOG_KEY_ID__NUM_OF
#define bcmolt_host_log_key_id_all_properties 0xFF
#define bcmolt_host_log_key_id_full_mask 0x2

} bcmolt_host_log_key_id;

/** Identifiers for all fields in a 'host_log_cfg_data'. */
typedef enum
{
    BCMOLT_HOST_LOG_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_HOST_LOG_CFG_DATA_ID_TYPE = 0, /**< Type. */
    BCMOLT_HOST_LOG_CFG_DATA_ID_STYLE = 1, /**< Style. */
    BCMOLT_HOST_LOG_CFG_DATA_ID_LEVEL = 2, /**< Level. */
    BCMOLT_HOST_LOG_CFG_DATA_ID_MSG_COUNT = 3, /**< Message Count. */
    BCMOLT_HOST_LOG_CFG_DATA_ID_LOST_MSG_COUNT = 4, /**< Lost Message Count. */
    BCMOLT_HOST_LOG_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_host_log_cfg_data_id__begin BCMOLT_HOST_LOG_CFG_DATA_ID__BEGIN
#define bcmolt_host_log_cfg_data_id_type BCMOLT_HOST_LOG_CFG_DATA_ID_TYPE
#define bcmolt_host_log_cfg_data_id_style BCMOLT_HOST_LOG_CFG_DATA_ID_STYLE
#define bcmolt_host_log_cfg_data_id_level BCMOLT_HOST_LOG_CFG_DATA_ID_LEVEL
#define bcmolt_host_log_cfg_data_id_msg_count BCMOLT_HOST_LOG_CFG_DATA_ID_MSG_COUNT
#define bcmolt_host_log_cfg_data_id_lost_msg_count BCMOLT_HOST_LOG_CFG_DATA_ID_LOST_MSG_COUNT
#define bcmolt_host_log_cfg_data_id__num_of BCMOLT_HOST_LOG_CFG_DATA_ID__NUM_OF
#define bcmolt_host_log_cfg_data_id_all_properties 0xFF
#define bcmolt_host_log_cfg_data_id_full_mask 0x1F

} bcmolt_host_log_cfg_data_id;

/** Identifiers for all fields in a 'host_log_file_key'. */
typedef enum
{
    BCMOLT_HOST_LOG_FILE_KEY_ID__BEGIN = 1,
    BCMOLT_HOST_LOG_FILE_KEY_ID_FILE_ID = 1, /**< File ID. */
    BCMOLT_HOST_LOG_FILE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_host_log_file_key_id__begin BCMOLT_HOST_LOG_FILE_KEY_ID__BEGIN
#define bcmolt_host_log_file_key_id_file_id BCMOLT_HOST_LOG_FILE_KEY_ID_FILE_ID
#define bcmolt_host_log_file_key_id__num_of BCMOLT_HOST_LOG_FILE_KEY_ID__NUM_OF
#define bcmolt_host_log_file_key_id_all_properties 0xFF
#define bcmolt_host_log_file_key_id_full_mask 0x2

} bcmolt_host_log_file_key_id;

/** Identifiers for all fields in a 'host_log_file_cfg_data'. */
typedef enum
{
    BCMOLT_HOST_LOG_FILE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_WRAP_AROUND = 0, /**< Wrap Around. */
    BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_CLEAR_AFTER_READ = 1, /**< Clear After Read. */
    BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_MSG_COUNT = 2, /**< Message Count. */
    BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_MSGS_READ = 3, /**< Messages Read. */
    BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_MSGS_REMAINING = 4, /**< Messages Remaining. */
    BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_BUFFER = 5, /**< Buffer. */
    BCMOLT_HOST_LOG_FILE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_host_log_file_cfg_data_id__begin BCMOLT_HOST_LOG_FILE_CFG_DATA_ID__BEGIN
#define bcmolt_host_log_file_cfg_data_id_wrap_around BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_WRAP_AROUND
#define bcmolt_host_log_file_cfg_data_id_clear_after_read BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_CLEAR_AFTER_READ
#define bcmolt_host_log_file_cfg_data_id_msg_count BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_MSG_COUNT
#define bcmolt_host_log_file_cfg_data_id_msgs_read BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_MSGS_READ
#define bcmolt_host_log_file_cfg_data_id_msgs_remaining BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_MSGS_REMAINING
#define bcmolt_host_log_file_cfg_data_id_buffer BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_BUFFER
#define bcmolt_host_log_file_cfg_data_id__num_of BCMOLT_HOST_LOG_FILE_CFG_DATA_ID__NUM_OF
#define bcmolt_host_log_file_cfg_data_id_all_properties 0xFF
#define bcmolt_host_log_file_cfg_data_id_full_mask 0x3F

} bcmolt_host_log_file_cfg_data_id;

/** Identifiers for all fields in a 'inband_mgmt_channel_cfg_data'. */
typedef enum
{
    BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_NNI_INTF = 0, /**< NNI Interface Reference. */
    BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_NIC_INTF_ID = 1, /**< NIC facing logical interface Id. */
    BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_VLAN_ID = 2, /**< vlan Id classification for this inband mgmt channel. */
    BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_NIC_CARD_MAC = 3, /**< NIC card MAC address. */
    BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_ACTION = 4, /**< Inband Mgmt Action. */
    BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_STATE = 5, /**< Inband Mgmt State. */
    BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_POLICER_PROFILE = 6, /**< policer_profile. */
    BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_inband_mgmt_channel_cfg_data_id__begin BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID__BEGIN
#define bcmolt_inband_mgmt_channel_cfg_data_id_nni_intf BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_NNI_INTF
#define bcmolt_inband_mgmt_channel_cfg_data_id_nic_intf_id BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_NIC_INTF_ID
#define bcmolt_inband_mgmt_channel_cfg_data_id_vlan_id BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_VLAN_ID
#define bcmolt_inband_mgmt_channel_cfg_data_id_nic_card_mac BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_NIC_CARD_MAC
#define bcmolt_inband_mgmt_channel_cfg_data_id_action BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_ACTION
#define bcmolt_inband_mgmt_channel_cfg_data_id_state BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_STATE
#define bcmolt_inband_mgmt_channel_cfg_data_id_policer_profile BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_POLICER_PROFILE
#define bcmolt_inband_mgmt_channel_cfg_data_id__num_of BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID__NUM_OF
#define bcmolt_inband_mgmt_channel_cfg_data_id_all_properties 0xFF
#define bcmolt_inband_mgmt_channel_cfg_data_id_full_mask 0x7F

} bcmolt_inband_mgmt_channel_cfg_data_id;

/** Identifiers for all fields in a 'inband_mgmt_channel_key'. */
typedef enum
{
    BCMOLT_INBAND_MGMT_CHANNEL_KEY_ID__BEGIN = 0,
    BCMOLT_INBAND_MGMT_CHANNEL_KEY_ID_ID = 0, /**< Inband Mgmt instance Id. */
    BCMOLT_INBAND_MGMT_CHANNEL_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_inband_mgmt_channel_key_id__begin BCMOLT_INBAND_MGMT_CHANNEL_KEY_ID__BEGIN
#define bcmolt_inband_mgmt_channel_key_id_id BCMOLT_INBAND_MGMT_CHANNEL_KEY_ID_ID
#define bcmolt_inband_mgmt_channel_key_id__num_of BCMOLT_INBAND_MGMT_CHANNEL_KEY_ID__NUM_OF
#define bcmolt_inband_mgmt_channel_key_id_all_properties 0xFF
#define bcmolt_inband_mgmt_channel_key_id_full_mask 0x1

} bcmolt_inband_mgmt_channel_key_id;

/** Identifiers for all fields in a 'internal_nni_key'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_KEY_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_KEY_ID_PON_NI = 0, /**< PON NI. */
    BCMOLT_INTERNAL_NNI_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_key_id__begin BCMOLT_INTERNAL_NNI_KEY_ID__BEGIN
#define bcmolt_internal_nni_key_id_pon_ni BCMOLT_INTERNAL_NNI_KEY_ID_PON_NI
#define bcmolt_internal_nni_key_id__num_of BCMOLT_INTERNAL_NNI_KEY_ID__NUM_OF
#define bcmolt_internal_nni_key_id_all_properties 0xFF
#define bcmolt_internal_nni_key_id_full_mask 0x1

} bcmolt_internal_nni_key_id;

/** Identifiers for all fields in a 'internal_nni_cfg_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID__BEGIN = 1,
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_MAC_ADDRESS = 1, /**< Mac Address. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_ACTIVE_NNI = 2, /**< Active NNI. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_STATUS = 3, /**< NNI Status. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_BACKUP_STATUS = 4, /**< NNI Backup Status. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_LOOPBACK_TYPE = 5, /**< Loopback Type. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_STATUS_POLLING_INTERVAL_MS = 7, /**< NNI Status Polling Interval (ms). */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_REDUNDANCY = 8, /**< NNI Redundancy. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_FLOW_CONTROL = 9, /**< Flow Control. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_INBAND_MGMT = 10, /**< Inband Management. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_TRAP_CONFIG = 11, /**< Trap Config. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_OVERSUBSCRIPTION = 12, /**< Oversubscription. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_PRBS_GENERATOR = 13, /**< PRBS Generator. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_PRBS_CHECKER = 14, /**< PRBS Checker. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_PRBS_STATUS = 15, /**< PRBS Status. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID_NNI_SWAP_DELAY_US = 16, /**< Delay for traffic during NNI swap in us. */
    BCMOLT_INTERNAL_NNI_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_cfg_data_id__begin BCMOLT_INTERNAL_NNI_CFG_DATA_ID__BEGIN
#define bcmolt_internal_nni_cfg_data_id_mac_address BCMOLT_INTERNAL_NNI_CFG_DATA_ID_MAC_ADDRESS
#define bcmolt_internal_nni_cfg_data_id_active_nni BCMOLT_INTERNAL_NNI_CFG_DATA_ID_ACTIVE_NNI
#define bcmolt_internal_nni_cfg_data_id_status BCMOLT_INTERNAL_NNI_CFG_DATA_ID_STATUS
#define bcmolt_internal_nni_cfg_data_id_backup_status BCMOLT_INTERNAL_NNI_CFG_DATA_ID_BACKUP_STATUS
#define bcmolt_internal_nni_cfg_data_id_loopback_type BCMOLT_INTERNAL_NNI_CFG_DATA_ID_LOOPBACK_TYPE
#define bcmolt_internal_nni_cfg_data_id_status_polling_interval_ms BCMOLT_INTERNAL_NNI_CFG_DATA_ID_STATUS_POLLING_INTERVAL_MS
#define bcmolt_internal_nni_cfg_data_id_redundancy BCMOLT_INTERNAL_NNI_CFG_DATA_ID_REDUNDANCY
#define bcmolt_internal_nni_cfg_data_id_flow_control BCMOLT_INTERNAL_NNI_CFG_DATA_ID_FLOW_CONTROL
#define bcmolt_internal_nni_cfg_data_id_inband_mgmt BCMOLT_INTERNAL_NNI_CFG_DATA_ID_INBAND_MGMT
#define bcmolt_internal_nni_cfg_data_id_trap_config BCMOLT_INTERNAL_NNI_CFG_DATA_ID_TRAP_CONFIG
#define bcmolt_internal_nni_cfg_data_id_oversubscription BCMOLT_INTERNAL_NNI_CFG_DATA_ID_OVERSUBSCRIPTION
#define bcmolt_internal_nni_cfg_data_id_prbs_generator BCMOLT_INTERNAL_NNI_CFG_DATA_ID_PRBS_GENERATOR
#define bcmolt_internal_nni_cfg_data_id_prbs_checker BCMOLT_INTERNAL_NNI_CFG_DATA_ID_PRBS_CHECKER
#define bcmolt_internal_nni_cfg_data_id_prbs_status BCMOLT_INTERNAL_NNI_CFG_DATA_ID_PRBS_STATUS
#define bcmolt_internal_nni_cfg_data_id_nni_swap_delay_us BCMOLT_INTERNAL_NNI_CFG_DATA_ID_NNI_SWAP_DELAY_US
#define bcmolt_internal_nni_cfg_data_id__num_of BCMOLT_INTERNAL_NNI_CFG_DATA_ID__NUM_OF
#define bcmolt_internal_nni_cfg_data_id_all_properties 0xFF
#define bcmolt_internal_nni_cfg_data_id_full_mask 0x1FFBE

} bcmolt_internal_nni_cfg_data_id;

/** Identifiers for all fields in a 'internal_nni_status_changed_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_NEW_STATUS = 0, /**< New NNI Link Status. */
    BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_LINK = 1, /**< Link. */
    BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_PREVIOUS_ACTIVE = 2, /**< Previous Active. */
    BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_NEW_ACTIVE = 3, /**< New Active. */
    BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_status_changed_data_id__begin BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID__BEGIN
#define bcmolt_internal_nni_status_changed_data_id_new_status BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_NEW_STATUS
#define bcmolt_internal_nni_status_changed_data_id_link BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_LINK
#define bcmolt_internal_nni_status_changed_data_id_previous_active BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_PREVIOUS_ACTIVE
#define bcmolt_internal_nni_status_changed_data_id_new_active BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_NEW_ACTIVE
#define bcmolt_internal_nni_status_changed_data_id__num_of BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID__NUM_OF
#define bcmolt_internal_nni_status_changed_data_id_all_properties 0xFF
#define bcmolt_internal_nni_status_changed_data_id_full_mask 0xF

} bcmolt_internal_nni_status_changed_data_id;

/** Identifiers for all fields in a 'internal_nni_nni_stats_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_GOOD_FRAMES = 0, /**< RX Good Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CONTROL_FRAMES = 1, /**< RX Control Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PAUSE_FRAMES = 2, /**< RX Pause Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PFC_FRAMES = 3, /**< RX PFC Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_OPCODE = 4, /**< RX Unsupported Opcode Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_DA = 5, /**< RX Unsupported DA Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_ALIGNMENT_ERRORS = 6, /**< RX Alignment Errors. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_LENGTH_OUT_OF_RANGE = 7, /**< RX Length Out of Range. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CODE_ERRORS = 8, /**< RX Code Errors. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_JABBER_FRAMES = 9, /**< RX Jabber Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_MTU_CHECK_ERRORS = 10, /**< RX MTU Check Errors. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PROMISCUOUS_FRAMES = 11, /**< RX Promiscuous Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_VLAN_FRAMES = 12, /**< RX VLAN Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_DOUBLE_VLAN_FRAMES = 13, /**< RX Double VLAN Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_TRUNCATED_FRAMES = 14, /**< RX Truncated Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNDERSIZE_FRAMES = 15, /**< RX Undersized Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_FRAGMENTED_FRAMES = 16, /**< RX Fragmented Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_GOOD_FRAMES = 17, /**< TX Good Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PAUSE_FRAMES = 18, /**< TX Pause Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PFC_FRAMES = 19, /**< TX PFC Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_JABBER_FRAMES = 20, /**< TX Jabber Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_CONTROL_FRAMES = 21, /**< TX Control Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_OVERSIZE_FRAMES = 22, /**< TX Oversize Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_FRAGMENTED_FRAMES = 23, /**< TX Fragmented Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_ERROR_FRAMES = 24, /**< TX Error Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_VLAN_FRAMES = 25, /**< TX VLAN Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_DOUBLE_VLAN_FRAMES = 26, /**< TX Double VLAN Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_RUNT_FRAMES = 27, /**< TX Runt Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_UNDERRUN_FRAMES = 28, /**< TX Underrun Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_nni_stats_data_id__begin BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID__BEGIN
#define bcmolt_internal_nni_nni_stats_data_id_rx_good_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_GOOD_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_control_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CONTROL_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_pause_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PAUSE_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_pfc_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PFC_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_unsupported_opcode BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_OPCODE
#define bcmolt_internal_nni_nni_stats_data_id_rx_unsupported_da BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_DA
#define bcmolt_internal_nni_nni_stats_data_id_rx_alignment_errors BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_ALIGNMENT_ERRORS
#define bcmolt_internal_nni_nni_stats_data_id_rx_length_out_of_range BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_LENGTH_OUT_OF_RANGE
#define bcmolt_internal_nni_nni_stats_data_id_rx_code_errors BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CODE_ERRORS
#define bcmolt_internal_nni_nni_stats_data_id_rx_jabber_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_JABBER_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_mtu_check_errors BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_MTU_CHECK_ERRORS
#define bcmolt_internal_nni_nni_stats_data_id_rx_promiscuous_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PROMISCUOUS_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_vlan_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_VLAN_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_double_vlan_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_DOUBLE_VLAN_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_truncated_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_TRUNCATED_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_undersize_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNDERSIZE_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_rx_fragmented_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_FRAGMENTED_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_good_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_GOOD_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_pause_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PAUSE_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_pfc_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PFC_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_jabber_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_JABBER_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_control_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_CONTROL_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_oversize_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_OVERSIZE_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_fragmented_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_FRAGMENTED_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_error_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_ERROR_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_vlan_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_VLAN_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_double_vlan_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_DOUBLE_VLAN_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_runt_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_RUNT_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id_tx_underrun_frames BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_UNDERRUN_FRAMES
#define bcmolt_internal_nni_nni_stats_data_id__num_of BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID__NUM_OF
#define bcmolt_internal_nni_nni_stats_data_id_all_properties 0xFF
#define bcmolt_internal_nni_nni_stats_data_id_full_mask 0x1FFFFFFF

} bcmolt_internal_nni_nni_stats_data_id;

/** Identifiers for all fields in a 'internal_nni_enet_stats_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BYTES = 0, /**< RX Bytes. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES = 1, /**< RX Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_64 = 2, /**< RX 64 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_65_127 = 3, /**< RX 65-127 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_128_255 = 4, /**< RX 128-255 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_256_511 = 5, /**< RX 256-511 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_512_1023 = 6, /**< RX 512-1023 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1024_1518 = 7, /**< RX 1024-1518 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1519_2047 = 8, /**< RX 1519-2047 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_2048_4095 = 9, /**< RX 2048_4095 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_4096_9216 = 10, /**< RX 4096-9216 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_9217_16383 = 11, /**< RX 9217-16383 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BROADCAST_FRAMES = 12, /**< RX Broadcast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_DATA_BYTES = 13, /**< RX Data Bytes. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_MULTICAST_FRAMES = 14, /**< RX Mulitcast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_UNICAST_FRAMES = 15, /**< RX Unicast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_ABORT_FRAMES = 16, /**< RX Abort Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FCS_ERROR = 17, /**< RX FCS Error. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_OVERSIZE_ERROR = 18, /**< RX Oversize Error. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_RUNT_ERROR = 19, /**< RX Runt Error. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BYTES = 20, /**< TX Bytes. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES = 21, /**< TX Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_64 = 22, /**< TX 64 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_65_127 = 23, /**< TX 65-127 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_128_255 = 24, /**< TX 128-255 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_256_511 = 25, /**< TX 256-511 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_512_1023 = 26, /**< TX 512-1023 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1024_1518 = 27, /**< TX 1024-1518 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1519_2047 = 28, /**< TX 1519-2047 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_2048_4095 = 29, /**< TX 2048_4095 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_4096_9216 = 30, /**< TX 4096-9216 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_9217_16383 = 31, /**< TX 9217-16383 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BROADCAST_FRAMES = 32, /**< TX Broadcast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_DATA_BYTES = 33, /**< TX Data Bytes. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_MULTICAST_FRAMES = 34, /**< TX Mulitcast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_UNICAST_FRAMES = 35, /**< TX Unicast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_ABORT_FRAMES = 36, /**< TX Abort Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FCS_ERROR = 37, /**< TX FCS Error. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_enet_stats_data_id__begin BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID__BEGIN
#define bcmolt_internal_nni_enet_stats_data_id_rx_bytes BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BYTES
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_64 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_64
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_65_127 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_65_127
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_128_255 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_128_255
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_256_511 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_256_511
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_512_1023 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_1024_1518 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_1519_2047 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_2048_4095 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_4096_9216 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_internal_nni_enet_stats_data_id_rx_frames_9217_16383 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_internal_nni_enet_stats_data_id_rx_broadcast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BROADCAST_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_rx_data_bytes BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_DATA_BYTES
#define bcmolt_internal_nni_enet_stats_data_id_rx_multicast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_MULTICAST_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_rx_unicast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_UNICAST_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_rx_abort_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_ABORT_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_rx_fcs_error BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FCS_ERROR
#define bcmolt_internal_nni_enet_stats_data_id_rx_oversize_error BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_OVERSIZE_ERROR
#define bcmolt_internal_nni_enet_stats_data_id_rx_runt_error BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_RUNT_ERROR
#define bcmolt_internal_nni_enet_stats_data_id_tx_bytes BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BYTES
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_64 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_64
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_65_127 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_65_127
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_128_255 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_128_255
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_256_511 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_256_511
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_512_1023 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_1024_1518 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_1519_2047 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_2048_4095 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_4096_9216 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_internal_nni_enet_stats_data_id_tx_frames_9217_16383 BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_internal_nni_enet_stats_data_id_tx_broadcast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BROADCAST_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_tx_data_bytes BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_DATA_BYTES
#define bcmolt_internal_nni_enet_stats_data_id_tx_multicast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_MULTICAST_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_tx_unicast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_UNICAST_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_tx_abort_frames BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_ABORT_FRAMES
#define bcmolt_internal_nni_enet_stats_data_id_tx_fcs_error BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FCS_ERROR
#define bcmolt_internal_nni_enet_stats_data_id__num_of BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID__NUM_OF
#define bcmolt_internal_nni_enet_stats_data_id_all_properties 0xFF
#define bcmolt_internal_nni_enet_stats_data_id_full_mask 0x3FFFFFFFFF

} bcmolt_internal_nni_enet_stats_data_id;

/** Identifiers for all fields in a 'internal_nni_packet_captured_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID__BEGIN = 1,
    BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID_PACKET_SIZE = 1, /**< packet_size. */
    BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID_BUFFER = 2, /**< buffer. */
    BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_packet_captured_data_id__begin BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID__BEGIN
#define bcmolt_internal_nni_packet_captured_data_id_packet_size BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID_PACKET_SIZE
#define bcmolt_internal_nni_packet_captured_data_id_buffer BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID_BUFFER
#define bcmolt_internal_nni_packet_captured_data_id__num_of BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID__NUM_OF
#define bcmolt_internal_nni_packet_captured_data_id_all_properties 0xFF
#define bcmolt_internal_nni_packet_captured_data_id_full_mask 0x6

} bcmolt_internal_nni_packet_captured_data_id;

/** Identifiers for all fields in a 'internal_nni_send_eth_packet_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_SEND_ETH_PACKET_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_SEND_ETH_PACKET_DATA_ID_BUFFER = 0, /**< buffer. */
    BCMOLT_INTERNAL_NNI_SEND_ETH_PACKET_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_send_eth_packet_data_id__begin BCMOLT_INTERNAL_NNI_SEND_ETH_PACKET_DATA_ID__BEGIN
#define bcmolt_internal_nni_send_eth_packet_data_id_buffer BCMOLT_INTERNAL_NNI_SEND_ETH_PACKET_DATA_ID_BUFFER
#define bcmolt_internal_nni_send_eth_packet_data_id__num_of BCMOLT_INTERNAL_NNI_SEND_ETH_PACKET_DATA_ID__NUM_OF
#define bcmolt_internal_nni_send_eth_packet_data_id_all_properties 0xFF
#define bcmolt_internal_nni_send_eth_packet_data_id_full_mask 0x1

} bcmolt_internal_nni_send_eth_packet_data_id;

/** Identifiers for all fields in a 'internal_nni_nni_stats_cfg_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_GOOD_FRAMES = 0, /**< RX Good Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_CONTROL_FRAMES = 1, /**< RX Control Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_PAUSE_FRAMES = 2, /**< RX Pause Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_PFC_FRAMES = 3, /**< RX PFC Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_UNSUPPORTED_OPCODE = 4, /**< RX Unsupported Opcode Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_UNSUPPORTED_DA = 5, /**< RX Unsupported DA Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_ALIGNMENT_ERRORS = 6, /**< RX Alignment Errors. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_LENGTH_OUT_OF_RANGE = 7, /**< RX Length Out of Range. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_CODE_ERRORS = 8, /**< RX Code Errors. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_JABBER_FRAMES = 9, /**< RX Jabber Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_MTU_CHECK_ERRORS = 10, /**< RX MTU Check Errors. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_PROMISCUOUS_FRAMES = 11, /**< RX Promiscuous Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_VLAN_FRAMES = 12, /**< RX VLAN Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_DOUBLE_VLAN_FRAMES = 13, /**< RX Double VLAN Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_TRUNCATED_FRAMES = 14, /**< RX Truncated Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_UNDERSIZE_FRAMES = 15, /**< RX Undersized Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_FRAGMENTED_FRAMES = 16, /**< RX Fragmented Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_GOOD_FRAMES = 17, /**< TX Good Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_PAUSE_FRAMES = 18, /**< TX Pause Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_PFC_FRAMES = 19, /**< TX PFC Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_JABBER_FRAMES = 20, /**< TX Jabber Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_CONTROL_FRAMES = 21, /**< TX Control Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_OVERSIZE_FRAMES = 22, /**< TX Oversize Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_FRAGMENTED_FRAMES = 23, /**< TX Fragmented Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_ERROR_FRAMES = 24, /**< TX Error Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_VLAN_FRAMES = 25, /**< TX VLAN Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_DOUBLE_VLAN_FRAMES = 26, /**< TX Double VLAN Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_RUNT_FRAMES = 27, /**< TX Runt Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_UNDERRUN_FRAMES = 28, /**< TX Underrun Frames. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_nni_stats_cfg_data_id__begin BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_good_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_GOOD_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_control_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_CONTROL_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_pause_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_PAUSE_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_pfc_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_PFC_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_unsupported_opcode BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_UNSUPPORTED_OPCODE
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_unsupported_da BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_UNSUPPORTED_DA
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_alignment_errors BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_ALIGNMENT_ERRORS
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_length_out_of_range BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_LENGTH_OUT_OF_RANGE
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_code_errors BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_CODE_ERRORS
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_jabber_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_JABBER_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_mtu_check_errors BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_MTU_CHECK_ERRORS
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_promiscuous_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_PROMISCUOUS_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_vlan_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_VLAN_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_double_vlan_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_DOUBLE_VLAN_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_truncated_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_TRUNCATED_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_undersize_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_UNDERSIZE_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_rx_fragmented_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_FRAGMENTED_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_good_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_GOOD_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_pause_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_PAUSE_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_pfc_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_PFC_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_jabber_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_JABBER_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_control_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_CONTROL_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_oversize_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_OVERSIZE_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_fragmented_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_FRAGMENTED_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_error_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_ERROR_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_vlan_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_VLAN_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_double_vlan_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_DOUBLE_VLAN_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_runt_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_RUNT_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id_tx_underrun_frames BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_UNDERRUN_FRAMES
#define bcmolt_internal_nni_nni_stats_cfg_data_id__num_of BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_internal_nni_nni_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_internal_nni_nni_stats_cfg_data_id_full_mask 0x1FFFFFFF

} bcmolt_internal_nni_nni_stats_cfg_data_id;

/** Identifiers for all fields in a 'internal_nni_nni_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_nni_stats_alarm_raised_data_id__begin BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_internal_nni_nni_stats_alarm_raised_data_id_stat BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_internal_nni_nni_stats_alarm_raised_data_id__num_of BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_internal_nni_nni_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_internal_nni_nni_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_internal_nni_nni_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'internal_nni_nni_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_nni_stats_alarm_cleared_data_id__begin BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_internal_nni_nni_stats_alarm_cleared_data_id_stat BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_internal_nni_nni_stats_alarm_cleared_data_id__num_of BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_internal_nni_nni_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_internal_nni_nni_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_internal_nni_nni_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'internal_nni_enet_stats_cfg_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_BYTES = 0, /**< RX Bytes. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES = 1, /**< RX Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_64 = 2, /**< RX 64 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_65_127 = 3, /**< RX 65-127 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_128_255 = 4, /**< RX 128-255 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_256_511 = 5, /**< RX 256-511 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_512_1023 = 6, /**< RX 512-1023 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518 = 7, /**< RX 1024-1518 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047 = 8, /**< RX 1519-2047 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095 = 9, /**< RX 2048_4095 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216 = 10, /**< RX 4096-9216 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383 = 11, /**< RX 9217-16383 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_BROADCAST_FRAMES = 12, /**< RX Broadcast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_DATA_BYTES = 13, /**< RX Data Bytes. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_MULTICAST_FRAMES = 14, /**< RX Mulitcast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_UNICAST_FRAMES = 15, /**< RX Unicast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_ABORT_FRAMES = 16, /**< RX Abort Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FCS_ERROR = 17, /**< RX FCS Error. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_OVERSIZE_ERROR = 18, /**< RX Oversize Error. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_RUNT_ERROR = 19, /**< RX Runt Error. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_BYTES = 20, /**< TX Bytes. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES = 21, /**< TX Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_64 = 22, /**< TX 64 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_65_127 = 23, /**< TX 65-127 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_128_255 = 24, /**< TX 128-255 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_256_511 = 25, /**< TX 256-511 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_512_1023 = 26, /**< TX 512-1023 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518 = 27, /**< TX 1024-1518 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047 = 28, /**< TX 1519-2047 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095 = 29, /**< TX 2048_4095 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216 = 30, /**< TX 4096-9216 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383 = 31, /**< TX 9217-16383 Byte Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_BROADCAST_FRAMES = 32, /**< TX Broadcast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_DATA_BYTES = 33, /**< TX Data Bytes. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_MULTICAST_FRAMES = 34, /**< TX Mulitcast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_UNICAST_FRAMES = 35, /**< TX Unicast Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_ABORT_FRAMES = 36, /**< TX Abort Frames. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FCS_ERROR = 37, /**< TX FCS Error. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_enet_stats_cfg_data_id__begin BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_bytes BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_BYTES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_64 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_64
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_65_127 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_65_127
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_128_255 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_128_255
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_256_511 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_256_511
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_512_1023 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_1024_1518 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_1519_2047 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_2048_4095 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_4096_9216 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_frames_9217_16383 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_broadcast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_BROADCAST_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_data_bytes BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_DATA_BYTES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_multicast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_MULTICAST_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_unicast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_UNICAST_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_abort_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_ABORT_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_fcs_error BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FCS_ERROR
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_oversize_error BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_OVERSIZE_ERROR
#define bcmolt_internal_nni_enet_stats_cfg_data_id_rx_runt_error BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_RUNT_ERROR
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_bytes BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_BYTES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_64 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_64
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_65_127 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_65_127
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_128_255 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_128_255
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_256_511 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_256_511
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_512_1023 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_1024_1518 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_1519_2047 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_2048_4095 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_4096_9216 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_frames_9217_16383 BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_broadcast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_BROADCAST_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_data_bytes BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_DATA_BYTES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_multicast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_MULTICAST_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_unicast_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_UNICAST_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_abort_frames BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_ABORT_FRAMES
#define bcmolt_internal_nni_enet_stats_cfg_data_id_tx_fcs_error BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FCS_ERROR
#define bcmolt_internal_nni_enet_stats_cfg_data_id__num_of BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_internal_nni_enet_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_internal_nni_enet_stats_cfg_data_id_full_mask 0x3FFFFFFFFF

} bcmolt_internal_nni_enet_stats_cfg_data_id;

/** Identifiers for all fields in a 'internal_nni_enet_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_enet_stats_alarm_raised_data_id__begin BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_internal_nni_enet_stats_alarm_raised_data_id_stat BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_internal_nni_enet_stats_alarm_raised_data_id__num_of BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_internal_nni_enet_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_internal_nni_enet_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_internal_nni_enet_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'internal_nni_enet_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_enet_stats_alarm_cleared_data_id__begin BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_internal_nni_enet_stats_alarm_cleared_data_id_stat BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_internal_nni_enet_stats_alarm_cleared_data_id__num_of BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_internal_nni_enet_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_internal_nni_enet_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_internal_nni_enet_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'internal_nni_auto_cfg_data'. */
typedef enum
{
    BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_ENET_STATS_ALARM_CLEARED = 0, /**< Ethernet Statistics Alarm Cleared. */
    BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_ENET_STATS_ALARM_RAISED = 1, /**< Ethernet Statistics Alarm Raised. */
    BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_NNI_STATS_ALARM_CLEARED = 2, /**< NNI And AE Counters (RMON) Alarm Cleared. */
    BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_NNI_STATS_ALARM_RAISED = 3, /**< NNI And AE Counters (RMON) Alarm Raised. */
    BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_PACKET_CAPTURED = 4, /**< Packet Captured. */
    BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_STATUS_CHANGED = 5, /**< Status changed. */
    BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_SWAP_COMPLETED = 6, /**< intetrnal inni sawp completed. */
    BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_internal_nni_auto_cfg_data_id__begin BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_internal_nni_auto_cfg_data_id_enet_stats_alarm_cleared BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_ENET_STATS_ALARM_CLEARED
#define bcmolt_internal_nni_auto_cfg_data_id_enet_stats_alarm_raised BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_ENET_STATS_ALARM_RAISED
#define bcmolt_internal_nni_auto_cfg_data_id_nni_stats_alarm_cleared BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_NNI_STATS_ALARM_CLEARED
#define bcmolt_internal_nni_auto_cfg_data_id_nni_stats_alarm_raised BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_NNI_STATS_ALARM_RAISED
#define bcmolt_internal_nni_auto_cfg_data_id_packet_captured BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_PACKET_CAPTURED
#define bcmolt_internal_nni_auto_cfg_data_id_status_changed BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_STATUS_CHANGED
#define bcmolt_internal_nni_auto_cfg_data_id_swap_completed BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_SWAP_COMPLETED
#define bcmolt_internal_nni_auto_cfg_data_id__num_of BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_internal_nni_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_internal_nni_auto_cfg_data_id_full_mask 0x7F

} bcmolt_internal_nni_auto_cfg_data_id;

/** Identifiers for all fields in a 'itupon_alloc_key'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_KEY_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_KEY_ID_PON_NI = 0, /**< PON network interface. */
    BCMOLT_ITUPON_ALLOC_KEY_ID_ALLOC_ID = 1, /**< Alloc ID. */
    BCMOLT_ITUPON_ALLOC_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_key_id__begin BCMOLT_ITUPON_ALLOC_KEY_ID__BEGIN
#define bcmolt_itupon_alloc_key_id_pon_ni BCMOLT_ITUPON_ALLOC_KEY_ID_PON_NI
#define bcmolt_itupon_alloc_key_id_alloc_id BCMOLT_ITUPON_ALLOC_KEY_ID_ALLOC_ID
#define bcmolt_itupon_alloc_key_id__num_of BCMOLT_ITUPON_ALLOC_KEY_ID__NUM_OF
#define bcmolt_itupon_alloc_key_id_all_properties 0xFF
#define bcmolt_itupon_alloc_key_id_full_mask 0x3

} bcmolt_itupon_alloc_key_id;

/** Identifiers for all fields in a 'itupon_alloc_cfg_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_STATE = 0, /**< state. */
    BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_SLA = 1, /**< sla. */
    BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_ONU_ID = 2, /**< onu_id. */
    BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_COLLECT_STATS = 3, /**< Enable statistics collection on the alloc id. */
    BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_ONU_TCONT_MAX_QUEUE_SIZE = 4, /**< The maximum size of the TCONT queue for this alloc ID in the ONU, in bytes. */
    BCMOLT_ITUPON_ALLOC_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_cfg_data_id__begin BCMOLT_ITUPON_ALLOC_CFG_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_cfg_data_id_state BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_STATE
#define bcmolt_itupon_alloc_cfg_data_id_sla BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_SLA
#define bcmolt_itupon_alloc_cfg_data_id_onu_id BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_ONU_ID
#define bcmolt_itupon_alloc_cfg_data_id_collect_stats BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_COLLECT_STATS
#define bcmolt_itupon_alloc_cfg_data_id_onu_tcont_max_queue_size BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_ONU_TCONT_MAX_QUEUE_SIZE
#define bcmolt_itupon_alloc_cfg_data_id__num_of BCMOLT_ITUPON_ALLOC_CFG_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_cfg_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_cfg_data_id_full_mask 0x1F

} bcmolt_itupon_alloc_cfg_data_id;

/** Identifiers for all fields in a 'itupon_alloc_configuration_completed_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID_STATUS = 0, /**< status. */
    BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID_NEW_STATE = 1, /**< new state. */
    BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_configuration_completed_data_id__begin BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_configuration_completed_data_id_status BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID_STATUS
#define bcmolt_itupon_alloc_configuration_completed_data_id_new_state BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID_NEW_STATE
#define bcmolt_itupon_alloc_configuration_completed_data_id__num_of BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_configuration_completed_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_configuration_completed_data_id_full_mask 0x3

} bcmolt_itupon_alloc_configuration_completed_data_id;

/** Identifiers for all fields in a 'itupon_alloc_get_stats_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_ID_NUM_OF_CYCLES = 0, /**< Number of cycles. */
    BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_get_stats_data_id__begin BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_get_stats_data_id_num_of_cycles BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_ID_NUM_OF_CYCLES
#define bcmolt_itupon_alloc_get_stats_data_id__num_of BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_get_stats_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_get_stats_data_id_full_mask 0x1

} bcmolt_itupon_alloc_get_stats_data_id;

/** Identifiers for all fields in a 'itupon_alloc_get_alloc_stats_completed_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_STATUS = 0, /**< status. */
    BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_AVERAGE_NSR_USED = 1, /**< Average NSR used words. */
    BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_AVERAGE_NSR_ALLOCATED = 2, /**< Average NSR allocated words. */
    BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_AVERAGE_SR_REPORT = 3, /**< Average SR report. */
    BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_get_alloc_stats_completed_data_id__begin BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_get_alloc_stats_completed_data_id_status BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_STATUS
#define bcmolt_itupon_alloc_get_alloc_stats_completed_data_id_average_nsr_used BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_AVERAGE_NSR_USED
#define bcmolt_itupon_alloc_get_alloc_stats_completed_data_id_average_nsr_allocated BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_AVERAGE_NSR_ALLOCATED
#define bcmolt_itupon_alloc_get_alloc_stats_completed_data_id_average_sr_report BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_AVERAGE_SR_REPORT
#define bcmolt_itupon_alloc_get_alloc_stats_completed_data_id__num_of BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_get_alloc_stats_completed_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_get_alloc_stats_completed_data_id_full_mask 0xF

} bcmolt_itupon_alloc_get_alloc_stats_completed_data_id;

/** Identifiers for all fields in a 'itupon_alloc_set_state_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_SET_STATE_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_SET_STATE_DATA_ID_STATE = 0, /**< State. */
    BCMOLT_ITUPON_ALLOC_SET_STATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_set_state_data_id__begin BCMOLT_ITUPON_ALLOC_SET_STATE_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_set_state_data_id_state BCMOLT_ITUPON_ALLOC_SET_STATE_DATA_ID_STATE
#define bcmolt_itupon_alloc_set_state_data_id__num_of BCMOLT_ITUPON_ALLOC_SET_STATE_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_set_state_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_set_state_data_id_full_mask 0x1

} bcmolt_itupon_alloc_set_state_data_id;

/** Identifiers for all fields in a 'itupon_alloc_stats_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_STATS_DATA_ID_RX_BYTES = 0, /**< Received Bytes. */
    BCMOLT_ITUPON_ALLOC_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_stats_data_id__begin BCMOLT_ITUPON_ALLOC_STATS_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_stats_data_id_rx_bytes BCMOLT_ITUPON_ALLOC_STATS_DATA_ID_RX_BYTES
#define bcmolt_itupon_alloc_stats_data_id__num_of BCMOLT_ITUPON_ALLOC_STATS_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_stats_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_stats_data_id_full_mask 0x1

} bcmolt_itupon_alloc_stats_data_id;

/** Identifiers for all fields in a 'itupon_alloc_stats_cfg_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_STATS_CFG_DATA_ID_RX_BYTES = 0, /**< Received Bytes. */
    BCMOLT_ITUPON_ALLOC_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_stats_cfg_data_id__begin BCMOLT_ITUPON_ALLOC_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_stats_cfg_data_id_rx_bytes BCMOLT_ITUPON_ALLOC_STATS_CFG_DATA_ID_RX_BYTES
#define bcmolt_itupon_alloc_stats_cfg_data_id__num_of BCMOLT_ITUPON_ALLOC_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_stats_cfg_data_id_full_mask 0x1

} bcmolt_itupon_alloc_stats_cfg_data_id;

/** Identifiers for all fields in a 'itupon_alloc_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ITUPON_ALLOC_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_stats_alarm_raised_data_id__begin BCMOLT_ITUPON_ALLOC_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_stats_alarm_raised_data_id_stat BCMOLT_ITUPON_ALLOC_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_itupon_alloc_stats_alarm_raised_data_id__num_of BCMOLT_ITUPON_ALLOC_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_itupon_alloc_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'itupon_alloc_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ITUPON_ALLOC_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_stats_alarm_cleared_data_id__begin BCMOLT_ITUPON_ALLOC_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_stats_alarm_cleared_data_id_stat BCMOLT_ITUPON_ALLOC_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_itupon_alloc_stats_alarm_cleared_data_id__num_of BCMOLT_ITUPON_ALLOC_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_itupon_alloc_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'itupon_alloc_auto_cfg_data'. */
typedef enum
{
    BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_CONFIGURATION_COMPLETED = 0, /**< Configuration Completed. */
    BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_GET_ALLOC_STATS_COMPLETED = 1, /**< Get alloc level statistics completed. */
    BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED = 2, /**< Statistics Alarm Cleared. */
    BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED = 3, /**< Statistics Alarm Raised. */
    BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_alloc_auto_cfg_data_id__begin BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_itupon_alloc_auto_cfg_data_id_configuration_completed BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_CONFIGURATION_COMPLETED
#define bcmolt_itupon_alloc_auto_cfg_data_id_get_alloc_stats_completed BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_GET_ALLOC_STATS_COMPLETED
#define bcmolt_itupon_alloc_auto_cfg_data_id_stats_alarm_cleared BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED
#define bcmolt_itupon_alloc_auto_cfg_data_id_stats_alarm_raised BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED
#define bcmolt_itupon_alloc_auto_cfg_data_id__num_of BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_itupon_alloc_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_itupon_alloc_auto_cfg_data_id_full_mask 0xF

} bcmolt_itupon_alloc_auto_cfg_data_id;

/** Identifiers for all fields in a 'itupon_gem_key'. */
typedef enum
{
    BCMOLT_ITUPON_GEM_KEY_ID__BEGIN = 0,
    BCMOLT_ITUPON_GEM_KEY_ID_PON_NI = 0, /**< PON network interface. */
    BCMOLT_ITUPON_GEM_KEY_ID_GEM_PORT_ID = 1, /**< GEM Port ID. */
    BCMOLT_ITUPON_GEM_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_key_id__begin BCMOLT_ITUPON_GEM_KEY_ID__BEGIN
#define bcmolt_itupon_gem_key_id_pon_ni BCMOLT_ITUPON_GEM_KEY_ID_PON_NI
#define bcmolt_itupon_gem_key_id_gem_port_id BCMOLT_ITUPON_GEM_KEY_ID_GEM_PORT_ID
#define bcmolt_itupon_gem_key_id__num_of BCMOLT_ITUPON_GEM_KEY_ID__NUM_OF
#define bcmolt_itupon_gem_key_id_all_properties 0xFF
#define bcmolt_itupon_gem_key_id_full_mask 0x3

} bcmolt_itupon_gem_key_id;

/** Identifiers for all fields in a 'itupon_gem_cfg_data'. */
typedef enum
{
    BCMOLT_ITUPON_GEM_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_GEM_CFG_DATA_ID_CONFIGURATION = 0, /**< Configuration. */
    BCMOLT_ITUPON_GEM_CFG_DATA_ID_ONU_ID = 1, /**< ONU ID. */
    BCMOLT_ITUPON_GEM_CFG_DATA_ID_STATE = 2, /**< state. */
    BCMOLT_ITUPON_GEM_CFG_DATA_ID_ENCRYPTION_MODE = 3, /**< encryption mode. */
    BCMOLT_ITUPON_GEM_CFG_DATA_ID_UPSTREAM_DESTINATION_QUEUE = 4, /**< Upstream destination queue. */
    BCMOLT_ITUPON_GEM_CFG_DATA_ID_CONTROL = 5, /**< control. */
    BCMOLT_ITUPON_GEM_CFG_DATA_ID_MAC_TABLE_ENTRY_LIMIT = 6, /**< MAC table entry limit. */
    BCMOLT_ITUPON_GEM_CFG_DATA_ID_DEBUG_FLOW_CONFIG = 7, /**< debug flow config. */
    BCMOLT_ITUPON_GEM_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_cfg_data_id__begin BCMOLT_ITUPON_GEM_CFG_DATA_ID__BEGIN
#define bcmolt_itupon_gem_cfg_data_id_configuration BCMOLT_ITUPON_GEM_CFG_DATA_ID_CONFIGURATION
#define bcmolt_itupon_gem_cfg_data_id_onu_id BCMOLT_ITUPON_GEM_CFG_DATA_ID_ONU_ID
#define bcmolt_itupon_gem_cfg_data_id_state BCMOLT_ITUPON_GEM_CFG_DATA_ID_STATE
#define bcmolt_itupon_gem_cfg_data_id_encryption_mode BCMOLT_ITUPON_GEM_CFG_DATA_ID_ENCRYPTION_MODE
#define bcmolt_itupon_gem_cfg_data_id_upstream_destination_queue BCMOLT_ITUPON_GEM_CFG_DATA_ID_UPSTREAM_DESTINATION_QUEUE
#define bcmolt_itupon_gem_cfg_data_id_control BCMOLT_ITUPON_GEM_CFG_DATA_ID_CONTROL
#define bcmolt_itupon_gem_cfg_data_id_mac_table_entry_limit BCMOLT_ITUPON_GEM_CFG_DATA_ID_MAC_TABLE_ENTRY_LIMIT
#define bcmolt_itupon_gem_cfg_data_id_debug_flow_config BCMOLT_ITUPON_GEM_CFG_DATA_ID_DEBUG_FLOW_CONFIG
#define bcmolt_itupon_gem_cfg_data_id__num_of BCMOLT_ITUPON_GEM_CFG_DATA_ID__NUM_OF
#define bcmolt_itupon_gem_cfg_data_id_all_properties 0xFF
#define bcmolt_itupon_gem_cfg_data_id_full_mask 0xFF

} bcmolt_itupon_gem_cfg_data_id;

/** Identifiers for all fields in a 'itupon_gem_stats_data'. */
typedef enum
{
    BCMOLT_ITUPON_GEM_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_PACKETS = 0, /**< Received GEM frames. */
    BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_BYTES = 1, /**< Received bytes. */
    BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_PACKETS = 2, /**< Transmitted GEM frames. */
    BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_BYTES = 3, /**< Transmitted bytes. */
    BCMOLT_ITUPON_GEM_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_stats_data_id__begin BCMOLT_ITUPON_GEM_STATS_DATA_ID__BEGIN
#define bcmolt_itupon_gem_stats_data_id_rx_packets BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_PACKETS
#define bcmolt_itupon_gem_stats_data_id_rx_bytes BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_BYTES
#define bcmolt_itupon_gem_stats_data_id_tx_packets BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_PACKETS
#define bcmolt_itupon_gem_stats_data_id_tx_bytes BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_BYTES
#define bcmolt_itupon_gem_stats_data_id__num_of BCMOLT_ITUPON_GEM_STATS_DATA_ID__NUM_OF
#define bcmolt_itupon_gem_stats_data_id_all_properties 0xFF
#define bcmolt_itupon_gem_stats_data_id_full_mask 0xF

} bcmolt_itupon_gem_stats_data_id;

/** Identifiers for all fields in a 'itupon_gem_configuration_completed_data'. */
typedef enum
{
    BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID_STATUS = 0, /**< status. */
    BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID_NEW_STATE = 1, /**< new state. */
    BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_configuration_completed_data_id__begin BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID__BEGIN
#define bcmolt_itupon_gem_configuration_completed_data_id_status BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID_STATUS
#define bcmolt_itupon_gem_configuration_completed_data_id_new_state BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID_NEW_STATE
#define bcmolt_itupon_gem_configuration_completed_data_id__num_of BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_itupon_gem_configuration_completed_data_id_all_properties 0xFF
#define bcmolt_itupon_gem_configuration_completed_data_id_full_mask 0x3

} bcmolt_itupon_gem_configuration_completed_data_id;

/** Identifiers for all fields in a 'itupon_gem_set_state_data'. */
typedef enum
{
    BCMOLT_ITUPON_GEM_SET_STATE_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_GEM_SET_STATE_DATA_ID_STATE = 0, /**< State. */
    BCMOLT_ITUPON_GEM_SET_STATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_set_state_data_id__begin BCMOLT_ITUPON_GEM_SET_STATE_DATA_ID__BEGIN
#define bcmolt_itupon_gem_set_state_data_id_state BCMOLT_ITUPON_GEM_SET_STATE_DATA_ID_STATE
#define bcmolt_itupon_gem_set_state_data_id__num_of BCMOLT_ITUPON_GEM_SET_STATE_DATA_ID__NUM_OF
#define bcmolt_itupon_gem_set_state_data_id_all_properties 0xFF
#define bcmolt_itupon_gem_set_state_data_id_full_mask 0x1

} bcmolt_itupon_gem_set_state_data_id;

/** Identifiers for all fields in a 'itupon_gem_stats_cfg_data'. */
typedef enum
{
    BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_RX_PACKETS = 0, /**< Received GEM frames. */
    BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_RX_BYTES = 1, /**< Received bytes. */
    BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_TX_PACKETS = 2, /**< Transmitted GEM frames. */
    BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_TX_BYTES = 3, /**< Transmitted bytes. */
    BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_stats_cfg_data_id__begin BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_itupon_gem_stats_cfg_data_id_rx_packets BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_RX_PACKETS
#define bcmolt_itupon_gem_stats_cfg_data_id_rx_bytes BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_RX_BYTES
#define bcmolt_itupon_gem_stats_cfg_data_id_tx_packets BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_TX_PACKETS
#define bcmolt_itupon_gem_stats_cfg_data_id_tx_bytes BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_TX_BYTES
#define bcmolt_itupon_gem_stats_cfg_data_id__num_of BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_itupon_gem_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_itupon_gem_stats_cfg_data_id_full_mask 0xF

} bcmolt_itupon_gem_stats_cfg_data_id;

/** Identifiers for all fields in a 'itupon_gem_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_ITUPON_GEM_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_GEM_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ITUPON_GEM_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_stats_alarm_raised_data_id__begin BCMOLT_ITUPON_GEM_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_itupon_gem_stats_alarm_raised_data_id_stat BCMOLT_ITUPON_GEM_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_itupon_gem_stats_alarm_raised_data_id__num_of BCMOLT_ITUPON_GEM_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_itupon_gem_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_itupon_gem_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_itupon_gem_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'itupon_gem_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_ITUPON_GEM_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_GEM_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ITUPON_GEM_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_stats_alarm_cleared_data_id__begin BCMOLT_ITUPON_GEM_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_itupon_gem_stats_alarm_cleared_data_id_stat BCMOLT_ITUPON_GEM_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_itupon_gem_stats_alarm_cleared_data_id__num_of BCMOLT_ITUPON_GEM_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_itupon_gem_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_itupon_gem_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_itupon_gem_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'itupon_gem_auto_cfg_data'. */
typedef enum
{
    BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID_CONFIGURATION_COMPLETED = 0, /**< Configuration Completed. */
    BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED = 1, /**< Statistics Alarm Cleared. */
    BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED = 2, /**< Statistics Alarm Raised. */
    BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_itupon_gem_auto_cfg_data_id__begin BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_itupon_gem_auto_cfg_data_id_configuration_completed BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID_CONFIGURATION_COMPLETED
#define bcmolt_itupon_gem_auto_cfg_data_id_stats_alarm_cleared BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED
#define bcmolt_itupon_gem_auto_cfg_data_id_stats_alarm_raised BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED
#define bcmolt_itupon_gem_auto_cfg_data_id__num_of BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_itupon_gem_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_itupon_gem_auto_cfg_data_id_full_mask 0x7

} bcmolt_itupon_gem_auto_cfg_data_id;

/** Identifiers for all fields in a 'lag_interface_key'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_KEY_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_KEY_ID_ID = 0, /**< id. */
    BCMOLT_LAG_INTERFACE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_key_id__begin BCMOLT_LAG_INTERFACE_KEY_ID__BEGIN
#define bcmolt_lag_interface_key_id_id BCMOLT_LAG_INTERFACE_KEY_ID_ID
#define bcmolt_lag_interface_key_id__num_of BCMOLT_LAG_INTERFACE_KEY_ID__NUM_OF
#define bcmolt_lag_interface_key_id_all_properties 0xFF
#define bcmolt_lag_interface_key_id_full_mask 0x1

} bcmolt_lag_interface_key_id;

/** Identifiers for all fields in a 'lag_interface_cfg_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_CONFIG_STATE = 0, /**< config_state. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_PSC_MODE = 1, /**< PSC mode. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_STATE = 4, /**< state. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_NNI_IDS = 5, /**< nni ids. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_MEMBER_STATUS = 7, /**< member status. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_MEMBER_COUNT = 9, /**< member_count. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_MEMBER_UP_COUNT = 10, /**< member_up_count. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_PROTECTION_TYPE = 11, /**< Protect Interface Type. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_LAG_HEALTH = 12, /**< lag_health. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID_SUB_TYPE = 13, /**< lag interface subtype. */
    BCMOLT_LAG_INTERFACE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_cfg_data_id__begin BCMOLT_LAG_INTERFACE_CFG_DATA_ID__BEGIN
#define bcmolt_lag_interface_cfg_data_id_config_state BCMOLT_LAG_INTERFACE_CFG_DATA_ID_CONFIG_STATE
#define bcmolt_lag_interface_cfg_data_id_psc_mode BCMOLT_LAG_INTERFACE_CFG_DATA_ID_PSC_MODE
#define bcmolt_lag_interface_cfg_data_id_state BCMOLT_LAG_INTERFACE_CFG_DATA_ID_STATE
#define bcmolt_lag_interface_cfg_data_id_nni_ids BCMOLT_LAG_INTERFACE_CFG_DATA_ID_NNI_IDS
#define bcmolt_lag_interface_cfg_data_id_member_status BCMOLT_LAG_INTERFACE_CFG_DATA_ID_MEMBER_STATUS
#define bcmolt_lag_interface_cfg_data_id_member_count BCMOLT_LAG_INTERFACE_CFG_DATA_ID_MEMBER_COUNT
#define bcmolt_lag_interface_cfg_data_id_member_up_count BCMOLT_LAG_INTERFACE_CFG_DATA_ID_MEMBER_UP_COUNT
#define bcmolt_lag_interface_cfg_data_id_protection_type BCMOLT_LAG_INTERFACE_CFG_DATA_ID_PROTECTION_TYPE
#define bcmolt_lag_interface_cfg_data_id_lag_health BCMOLT_LAG_INTERFACE_CFG_DATA_ID_LAG_HEALTH
#define bcmolt_lag_interface_cfg_data_id_sub_type BCMOLT_LAG_INTERFACE_CFG_DATA_ID_SUB_TYPE
#define bcmolt_lag_interface_cfg_data_id__num_of BCMOLT_LAG_INTERFACE_CFG_DATA_ID__NUM_OF
#define bcmolt_lag_interface_cfg_data_id_all_properties 0xFF
#define bcmolt_lag_interface_cfg_data_id_full_mask 0x3EB3

} bcmolt_lag_interface_cfg_data_id;

/** Identifiers for all fields in a 'lag_interface_stats_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BYTES = 0, /**< received bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_PACKETS = 1, /**< received  packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS = 2, /**< received  unicast packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS = 3, /**< received  multicast packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS = 4, /**< received  broadcast packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS = 5, /**< received error packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UNKNOWN_PROTOS = 6, /**< received unknown proto packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BYTES = 7, /**< transmitted bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_PACKETS = 8, /**< transmitted packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS = 9, /**< transmitted unicast packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS = 10, /**< transmitted multicast packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS = 11, /**< transmitted broadcast packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS = 12, /**< transmitted error packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_64 = 13, /**< rx 64 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127 = 14, /**< rx 65-127 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255 = 15, /**< rx 128-255 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511 = 16, /**< rx 256-511 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023 = 17, /**< rx 512-1023 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518 = 18, /**< rx 1024-1518 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047 = 19, /**< rx 1519-2047 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095 = 20, /**< rx 2048-4095 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216 = 21, /**< rx 4096-9216 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383 = 22, /**< rx 9217-16383 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_64 = 23, /**< tx 64 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127 = 24, /**< tx 65-127 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255 = 25, /**< tx 128-255 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511 = 26, /**< tx 256-511 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023 = 27, /**< tx 512-1023 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518 = 28, /**< tx 1024-1518 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047 = 29, /**< tx 1519-2047 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095 = 30, /**< tx 2048-4095 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216 = 31, /**< tx 4096-9216 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383 = 32, /**< tx 9217-16383 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS = 33, /**< rx fcs error packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS = 34, /**< rx undersize packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS = 35, /**< rx oversize packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS = 36, /**< tx undersize packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS = 37, /**< tx oversize packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS = 38, /**< tx jabber packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS = 39, /**< rx jabber packets. */
    BCMOLT_LAG_INTERFACE_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_stats_data_id__begin BCMOLT_LAG_INTERFACE_STATS_DATA_ID__BEGIN
#define bcmolt_lag_interface_stats_data_id_rx_bytes BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BYTES
#define bcmolt_lag_interface_stats_data_id_rx_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_PACKETS
#define bcmolt_lag_interface_stats_data_id_rx_ucast_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS
#define bcmolt_lag_interface_stats_data_id_rx_mcast_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS
#define bcmolt_lag_interface_stats_data_id_rx_bcast_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS
#define bcmolt_lag_interface_stats_data_id_rx_error_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS
#define bcmolt_lag_interface_stats_data_id_rx_unknown_protos BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UNKNOWN_PROTOS
#define bcmolt_lag_interface_stats_data_id_tx_bytes BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BYTES
#define bcmolt_lag_interface_stats_data_id_tx_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_PACKETS
#define bcmolt_lag_interface_stats_data_id_tx_ucast_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS
#define bcmolt_lag_interface_stats_data_id_tx_mcast_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS
#define bcmolt_lag_interface_stats_data_id_tx_bcast_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS
#define bcmolt_lag_interface_stats_data_id_tx_error_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS
#define bcmolt_lag_interface_stats_data_id_rx_frames_64 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_64
#define bcmolt_lag_interface_stats_data_id_rx_frames_65_127 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127
#define bcmolt_lag_interface_stats_data_id_rx_frames_128_255 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255
#define bcmolt_lag_interface_stats_data_id_rx_frames_256_511 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511
#define bcmolt_lag_interface_stats_data_id_rx_frames_512_1023 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_lag_interface_stats_data_id_rx_frames_1024_1518 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_lag_interface_stats_data_id_rx_frames_1519_2047 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_lag_interface_stats_data_id_rx_frames_2048_4095 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_lag_interface_stats_data_id_rx_frames_4096_9216 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_lag_interface_stats_data_id_rx_frames_9217_16383 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_lag_interface_stats_data_id_tx_frames_64 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_64
#define bcmolt_lag_interface_stats_data_id_tx_frames_65_127 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127
#define bcmolt_lag_interface_stats_data_id_tx_frames_128_255 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255
#define bcmolt_lag_interface_stats_data_id_tx_frames_256_511 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511
#define bcmolt_lag_interface_stats_data_id_tx_frames_512_1023 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_lag_interface_stats_data_id_tx_frames_1024_1518 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_lag_interface_stats_data_id_tx_frames_1519_2047 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_lag_interface_stats_data_id_tx_frames_2048_4095 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_lag_interface_stats_data_id_tx_frames_4096_9216 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_lag_interface_stats_data_id_tx_frames_9217_16383 BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_lag_interface_stats_data_id_rx_fcs_error_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS
#define bcmolt_lag_interface_stats_data_id_rx_undersize_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS
#define bcmolt_lag_interface_stats_data_id_rx_oversize_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS
#define bcmolt_lag_interface_stats_data_id_tx_undersize_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS
#define bcmolt_lag_interface_stats_data_id_tx_oversize_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS
#define bcmolt_lag_interface_stats_data_id_tx_jabber_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS
#define bcmolt_lag_interface_stats_data_id_rx_jabber_packets BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS
#define bcmolt_lag_interface_stats_data_id__num_of BCMOLT_LAG_INTERFACE_STATS_DATA_ID__NUM_OF
#define bcmolt_lag_interface_stats_data_id_all_properties 0xFF
#define bcmolt_lag_interface_stats_data_id_full_mask 0xFFFFFFFFFF

} bcmolt_lag_interface_stats_data_id;

/** Identifiers for all fields in a 'lag_interface_members_update_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_DATA_ID_MEMBERS_CMD = 0, /**< members_cmd. */
    BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_members_update_data_id__begin BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_DATA_ID__BEGIN
#define bcmolt_lag_interface_members_update_data_id_members_cmd BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_DATA_ID_MEMBERS_CMD
#define bcmolt_lag_interface_members_update_data_id__num_of BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_DATA_ID__NUM_OF
#define bcmolt_lag_interface_members_update_data_id_all_properties 0xFF
#define bcmolt_lag_interface_members_update_data_id_full_mask 0x1

} bcmolt_lag_interface_members_update_data_id;

/** Identifiers for all fields in a 'lag_interface_complete_members_update_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID_RESULT = 0, /**< result. */
    BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_complete_members_update_data_id__begin BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID__BEGIN
#define bcmolt_lag_interface_complete_members_update_data_id_result BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID_RESULT
#define bcmolt_lag_interface_complete_members_update_data_id_fail_reason BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID_FAIL_REASON
#define bcmolt_lag_interface_complete_members_update_data_id__num_of BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID__NUM_OF
#define bcmolt_lag_interface_complete_members_update_data_id_all_properties 0xFF
#define bcmolt_lag_interface_complete_members_update_data_id_full_mask 0x3

} bcmolt_lag_interface_complete_members_update_data_id;

/** Identifiers for all fields in a 'lag_interface_state_update_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_STATE_UPDATE_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_STATE_UPDATE_DATA_ID_LAG_STATE = 0, /**< lag_state. */
    BCMOLT_LAG_INTERFACE_STATE_UPDATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_state_update_data_id__begin BCMOLT_LAG_INTERFACE_STATE_UPDATE_DATA_ID__BEGIN
#define bcmolt_lag_interface_state_update_data_id_lag_state BCMOLT_LAG_INTERFACE_STATE_UPDATE_DATA_ID_LAG_STATE
#define bcmolt_lag_interface_state_update_data_id__num_of BCMOLT_LAG_INTERFACE_STATE_UPDATE_DATA_ID__NUM_OF
#define bcmolt_lag_interface_state_update_data_id_all_properties 0xFF
#define bcmolt_lag_interface_state_update_data_id_full_mask 0x1

} bcmolt_lag_interface_state_update_data_id;

/** Identifiers for all fields in a 'lag_interface_state_updated_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID_NEW_STATE = 0, /**< new_state. */
    BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID_OLD_STATE = 1, /**< old state. */
    BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID_FAULT_CODE = 2, /**< fault_code. */
    BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_state_updated_data_id__begin BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID__BEGIN
#define bcmolt_lag_interface_state_updated_data_id_new_state BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID_NEW_STATE
#define bcmolt_lag_interface_state_updated_data_id_old_state BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID_OLD_STATE
#define bcmolt_lag_interface_state_updated_data_id_fault_code BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID_FAULT_CODE
#define bcmolt_lag_interface_state_updated_data_id__num_of BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID__NUM_OF
#define bcmolt_lag_interface_state_updated_data_id_all_properties 0xFF
#define bcmolt_lag_interface_state_updated_data_id_full_mask 0x7

} bcmolt_lag_interface_state_updated_data_id;

/** Identifiers for all fields in a 'lag_interface_lag_health_change_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID_NEW_STATE = 0, /**< new_state. */
    BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID_OLD_STATE = 1, /**< old state. */
    BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_lag_health_change_data_id__begin BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID__BEGIN
#define bcmolt_lag_interface_lag_health_change_data_id_new_state BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID_NEW_STATE
#define bcmolt_lag_interface_lag_health_change_data_id_old_state BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID_OLD_STATE
#define bcmolt_lag_interface_lag_health_change_data_id__num_of BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID__NUM_OF
#define bcmolt_lag_interface_lag_health_change_data_id_all_properties 0xFF
#define bcmolt_lag_interface_lag_health_change_data_id_full_mask 0x3

} bcmolt_lag_interface_lag_health_change_data_id;

/** Identifiers for all fields in a 'lag_interface_stats_cfg_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_BYTES = 0, /**< received bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_PACKETS = 1, /**< received  packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_UCAST_PACKETS = 2, /**< received  unicast packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_MCAST_PACKETS = 3, /**< received  multicast packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_BCAST_PACKETS = 4, /**< received  broadcast packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_ERROR_PACKETS = 5, /**< received error packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_UNKNOWN_PROTOS = 6, /**< received unknown proto packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_BYTES = 7, /**< transmitted bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_PACKETS = 8, /**< transmitted packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_UCAST_PACKETS = 9, /**< transmitted unicast packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_MCAST_PACKETS = 10, /**< transmitted multicast packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_BCAST_PACKETS = 11, /**< transmitted broadcast packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_ERROR_PACKETS = 12, /**< transmitted error packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_64 = 13, /**< rx 64 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_65_127 = 14, /**< rx 65-127 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_128_255 = 15, /**< rx 128-255 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_256_511 = 16, /**< rx 256-511 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_512_1023 = 17, /**< rx 512-1023 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518 = 18, /**< rx 1024-1518 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047 = 19, /**< rx 1519-2047 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095 = 20, /**< rx 2048-4095 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216 = 21, /**< rx 4096-9216 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383 = 22, /**< rx 9217-16383 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_64 = 23, /**< tx 64 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_65_127 = 24, /**< tx 65-127 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_128_255 = 25, /**< tx 128-255 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_256_511 = 26, /**< tx 256-511 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_512_1023 = 27, /**< tx 512-1023 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518 = 28, /**< tx 1024-1518 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047 = 29, /**< tx 1519-2047 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095 = 30, /**< tx 2048-4095 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216 = 31, /**< tx 4096-9216 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383 = 32, /**< tx 9217-16383 Bytes. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FCS_ERROR_PACKETS = 33, /**< rx fcs error packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_UNDERSIZE_PACKETS = 34, /**< rx undersize packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_OVERSIZE_PACKETS = 35, /**< rx oversize packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_UNDERSIZE_PACKETS = 36, /**< tx undersize packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_OVERSIZE_PACKETS = 37, /**< tx oversize packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_JABBER_PACKETS = 38, /**< tx jabber packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_JABBER_PACKETS = 39, /**< rx jabber packets. */
    BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_stats_cfg_data_id__begin BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_lag_interface_stats_cfg_data_id_rx_bytes BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_BYTES
#define bcmolt_lag_interface_stats_cfg_data_id_rx_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_rx_ucast_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_UCAST_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_rx_mcast_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_MCAST_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_rx_bcast_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_BCAST_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_rx_error_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_ERROR_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_rx_unknown_protos BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_UNKNOWN_PROTOS
#define bcmolt_lag_interface_stats_cfg_data_id_tx_bytes BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_BYTES
#define bcmolt_lag_interface_stats_cfg_data_id_tx_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_tx_ucast_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_UCAST_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_tx_mcast_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_MCAST_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_tx_bcast_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_BCAST_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_tx_error_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_ERROR_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_64 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_64
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_65_127 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_65_127
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_128_255 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_128_255
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_256_511 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_256_511
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_512_1023 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_1024_1518 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_1519_2047 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_2048_4095 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_4096_9216 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_lag_interface_stats_cfg_data_id_rx_frames_9217_16383 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_64 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_64
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_65_127 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_65_127
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_128_255 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_128_255
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_256_511 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_256_511
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_512_1023 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_1024_1518 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_1519_2047 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_2048_4095 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_4096_9216 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_lag_interface_stats_cfg_data_id_tx_frames_9217_16383 BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_lag_interface_stats_cfg_data_id_rx_fcs_error_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FCS_ERROR_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_rx_undersize_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_UNDERSIZE_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_rx_oversize_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_OVERSIZE_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_tx_undersize_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_UNDERSIZE_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_tx_oversize_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_OVERSIZE_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_tx_jabber_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_JABBER_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id_rx_jabber_packets BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_JABBER_PACKETS
#define bcmolt_lag_interface_stats_cfg_data_id__num_of BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_lag_interface_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_lag_interface_stats_cfg_data_id_full_mask 0xFFFFFFFFFF

} bcmolt_lag_interface_stats_cfg_data_id;

/** Identifiers for all fields in a 'lag_interface_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_LAG_INTERFACE_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_stats_alarm_raised_data_id__begin BCMOLT_LAG_INTERFACE_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_lag_interface_stats_alarm_raised_data_id_stat BCMOLT_LAG_INTERFACE_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_lag_interface_stats_alarm_raised_data_id__num_of BCMOLT_LAG_INTERFACE_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_lag_interface_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_lag_interface_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_lag_interface_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'lag_interface_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_LAG_INTERFACE_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_stats_alarm_cleared_data_id__begin BCMOLT_LAG_INTERFACE_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_lag_interface_stats_alarm_cleared_data_id_stat BCMOLT_LAG_INTERFACE_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_lag_interface_stats_alarm_cleared_data_id__num_of BCMOLT_LAG_INTERFACE_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_lag_interface_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_lag_interface_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_lag_interface_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'lag_interface_auto_cfg_data'. */
typedef enum
{
    BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_COMPLETE_MEMBERS_UPDATE = 0, /**< complete_members_update. */
    BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_LAG_HEALTH_CHANGE = 1, /**< LAG health change. */
    BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_STATE_UPDATED = 2, /**< interface state updated. */
    BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED = 3, /**< LAG Interface Statistics Alarm Cleared. */
    BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED = 4, /**< LAG Interface Statistics Alarm Raised. */
    BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_lag_interface_auto_cfg_data_id__begin BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_lag_interface_auto_cfg_data_id_complete_members_update BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_COMPLETE_MEMBERS_UPDATE
#define bcmolt_lag_interface_auto_cfg_data_id_lag_health_change BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_LAG_HEALTH_CHANGE
#define bcmolt_lag_interface_auto_cfg_data_id_state_updated BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_STATE_UPDATED
#define bcmolt_lag_interface_auto_cfg_data_id_stats_alarm_cleared BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED
#define bcmolt_lag_interface_auto_cfg_data_id_stats_alarm_raised BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED
#define bcmolt_lag_interface_auto_cfg_data_id__num_of BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_lag_interface_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_lag_interface_auto_cfg_data_id_full_mask 0x1F

} bcmolt_lag_interface_auto_cfg_data_id;

/** Identifiers for all fields in a 'log_key'. */
typedef enum
{
    BCMOLT_LOG_KEY_ID__BEGIN = 0,
    BCMOLT_LOG_KEY_ID_DEVICE_ID = 0, /**< Device ID. */
    BCMOLT_LOG_KEY_ID_NAME = 1, /**< name. */
    BCMOLT_LOG_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_log_key_id__begin BCMOLT_LOG_KEY_ID__BEGIN
#define bcmolt_log_key_id_device_id BCMOLT_LOG_KEY_ID_DEVICE_ID
#define bcmolt_log_key_id_name BCMOLT_LOG_KEY_ID_NAME
#define bcmolt_log_key_id__num_of BCMOLT_LOG_KEY_ID__NUM_OF
#define bcmolt_log_key_id_all_properties 0xFF
#define bcmolt_log_key_id_full_mask 0x3

} bcmolt_log_key_id;

/** Identifiers for all fields in a 'log_cfg_data'. */
typedef enum
{
    BCMOLT_LOG_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_LOG_CFG_DATA_ID_TYPE = 0, /**< Type. */
    BCMOLT_LOG_CFG_DATA_ID_STYLE = 1, /**< Style. */
    BCMOLT_LOG_CFG_DATA_ID_LEVEL = 2, /**< Level. */
    BCMOLT_LOG_CFG_DATA_ID_MSG_COUNT = 3, /**< Message Count. */
    BCMOLT_LOG_CFG_DATA_ID_LOST_MSG_COUNT = 4, /**< Lost Message Count. */
    BCMOLT_LOG_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_log_cfg_data_id__begin BCMOLT_LOG_CFG_DATA_ID__BEGIN
#define bcmolt_log_cfg_data_id_type BCMOLT_LOG_CFG_DATA_ID_TYPE
#define bcmolt_log_cfg_data_id_style BCMOLT_LOG_CFG_DATA_ID_STYLE
#define bcmolt_log_cfg_data_id_level BCMOLT_LOG_CFG_DATA_ID_LEVEL
#define bcmolt_log_cfg_data_id_msg_count BCMOLT_LOG_CFG_DATA_ID_MSG_COUNT
#define bcmolt_log_cfg_data_id_lost_msg_count BCMOLT_LOG_CFG_DATA_ID_LOST_MSG_COUNT
#define bcmolt_log_cfg_data_id__num_of BCMOLT_LOG_CFG_DATA_ID__NUM_OF
#define bcmolt_log_cfg_data_id_all_properties 0xFF
#define bcmolt_log_cfg_data_id_full_mask 0x1F

} bcmolt_log_cfg_data_id;

/** Identifiers for all fields in a 'log_file_key'. */
typedef enum
{
    BCMOLT_LOG_FILE_KEY_ID__BEGIN = 0,
    BCMOLT_LOG_FILE_KEY_ID_DEVICE_ID = 0, /**< Device ID. */
    BCMOLT_LOG_FILE_KEY_ID_FILE_ID = 1, /**< File ID. */
    BCMOLT_LOG_FILE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_log_file_key_id__begin BCMOLT_LOG_FILE_KEY_ID__BEGIN
#define bcmolt_log_file_key_id_device_id BCMOLT_LOG_FILE_KEY_ID_DEVICE_ID
#define bcmolt_log_file_key_id_file_id BCMOLT_LOG_FILE_KEY_ID_FILE_ID
#define bcmolt_log_file_key_id__num_of BCMOLT_LOG_FILE_KEY_ID__NUM_OF
#define bcmolt_log_file_key_id_all_properties 0xFF
#define bcmolt_log_file_key_id_full_mask 0x3

} bcmolt_log_file_key_id;

/** Identifiers for all fields in a 'log_file_cfg_data'. */
typedef enum
{
    BCMOLT_LOG_FILE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_LOG_FILE_CFG_DATA_ID_WRAP_AROUND = 0, /**< Wrap Around. */
    BCMOLT_LOG_FILE_CFG_DATA_ID_CLEAR_AFTER_READ = 1, /**< Clear After Read. */
    BCMOLT_LOG_FILE_CFG_DATA_ID_MSG_COUNT = 2, /**< Message Count. */
    BCMOLT_LOG_FILE_CFG_DATA_ID_MSGS_READ = 3, /**< Messages Read. */
    BCMOLT_LOG_FILE_CFG_DATA_ID_MSGS_REMAINING = 4, /**< Messages Remaining. */
    BCMOLT_LOG_FILE_CFG_DATA_ID_BUFFER = 5, /**< Buffer. */
    BCMOLT_LOG_FILE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_log_file_cfg_data_id__begin BCMOLT_LOG_FILE_CFG_DATA_ID__BEGIN
#define bcmolt_log_file_cfg_data_id_wrap_around BCMOLT_LOG_FILE_CFG_DATA_ID_WRAP_AROUND
#define bcmolt_log_file_cfg_data_id_clear_after_read BCMOLT_LOG_FILE_CFG_DATA_ID_CLEAR_AFTER_READ
#define bcmolt_log_file_cfg_data_id_msg_count BCMOLT_LOG_FILE_CFG_DATA_ID_MSG_COUNT
#define bcmolt_log_file_cfg_data_id_msgs_read BCMOLT_LOG_FILE_CFG_DATA_ID_MSGS_READ
#define bcmolt_log_file_cfg_data_id_msgs_remaining BCMOLT_LOG_FILE_CFG_DATA_ID_MSGS_REMAINING
#define bcmolt_log_file_cfg_data_id_buffer BCMOLT_LOG_FILE_CFG_DATA_ID_BUFFER
#define bcmolt_log_file_cfg_data_id__num_of BCMOLT_LOG_FILE_CFG_DATA_ID__NUM_OF
#define bcmolt_log_file_cfg_data_id_all_properties 0xFF
#define bcmolt_log_file_cfg_data_id_full_mask 0x3F

} bcmolt_log_file_cfg_data_id;

/** Identifiers for all fields in a 'ngpon2_channel_key'. */
typedef enum
{
    BCMOLT_NGPON2_CHANNEL_KEY_ID__BEGIN = 0,
    BCMOLT_NGPON2_CHANNEL_KEY_ID_PON_NI = 0, /**< PON network interface. */
    BCMOLT_NGPON2_CHANNEL_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ngpon2_channel_key_id__begin BCMOLT_NGPON2_CHANNEL_KEY_ID__BEGIN
#define bcmolt_ngpon2_channel_key_id_pon_ni BCMOLT_NGPON2_CHANNEL_KEY_ID_PON_NI
#define bcmolt_ngpon2_channel_key_id__num_of BCMOLT_NGPON2_CHANNEL_KEY_ID__NUM_OF
#define bcmolt_ngpon2_channel_key_id_all_properties 0xFF
#define bcmolt_ngpon2_channel_key_id_full_mask 0x1

} bcmolt_ngpon2_channel_key_id;

/** Identifiers for all fields in a 'ngpon2_channel_cfg_data'. */
typedef enum
{
    BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID_SYSTEM_PROFILE = 0, /**< System profile. */
    BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID_CHANNEL_PROFILE = 1, /**< Channel profile. */
    BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ngpon2_channel_cfg_data_id__begin BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID__BEGIN
#define bcmolt_ngpon2_channel_cfg_data_id_system_profile BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID_SYSTEM_PROFILE
#define bcmolt_ngpon2_channel_cfg_data_id_channel_profile BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID_CHANNEL_PROFILE
#define bcmolt_ngpon2_channel_cfg_data_id__num_of BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID__NUM_OF
#define bcmolt_ngpon2_channel_cfg_data_id_all_properties 0xFF
#define bcmolt_ngpon2_channel_cfg_data_id_full_mask 0x3

} bcmolt_ngpon2_channel_cfg_data_id;

/** Identifiers for all fields in a 'nni_interface_key'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_KEY_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_KEY_ID_ID = 0, /**< id. */
    BCMOLT_NNI_INTERFACE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_key_id__begin BCMOLT_NNI_INTERFACE_KEY_ID__BEGIN
#define bcmolt_nni_interface_key_id_id BCMOLT_NNI_INTERFACE_KEY_ID_ID
#define bcmolt_nni_interface_key_id__num_of BCMOLT_NNI_INTERFACE_KEY_ID__NUM_OF
#define bcmolt_nni_interface_key_id_all_properties 0xFF
#define bcmolt_nni_interface_key_id_full_mask 0x1

} bcmolt_nni_interface_key_id;

/** Identifiers for all fields in a 'nni_interface_state_change_data'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID_RESULT = 0, /**< Result. */
    BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID_OLD_STATE = 1, /**< Old State. */
    BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID_NEW_STATE = 2, /**< New State. */
    BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_state_change_data_id__begin BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID__BEGIN
#define bcmolt_nni_interface_state_change_data_id_result BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID_RESULT
#define bcmolt_nni_interface_state_change_data_id_old_state BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID_OLD_STATE
#define bcmolt_nni_interface_state_change_data_id_new_state BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID_NEW_STATE
#define bcmolt_nni_interface_state_change_data_id__num_of BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID__NUM_OF
#define bcmolt_nni_interface_state_change_data_id_all_properties 0xFF
#define bcmolt_nni_interface_state_change_data_id_full_mask 0x7

} bcmolt_nni_interface_state_change_data_id;

/** Identifiers for all fields in a 'nni_interface_cfg_data'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_CONFIG_STATE = 0, /**< config_state. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_STATE = 1, /**< state. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_LINK_STATE = 3, /**< Link State. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_LINK_FAULT_CODE = 4, /**< Link Fault Code. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_PROTECTION_TYPE = 5, /**< Protect Type. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_DESCRIPTION = 6, /**< Description. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_MTU = 8, /**< eth mtu. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_SPEED = 9, /**< eth speed. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_DUPLEX = 10, /**< eth duplex mode. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_AUTO_NEGOTIATE = 11, /**< eth auto negotiation mode. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID_SUB_TYPE = 12, /**< nni interface subtype. */
    BCMOLT_NNI_INTERFACE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_cfg_data_id__begin BCMOLT_NNI_INTERFACE_CFG_DATA_ID__BEGIN
#define bcmolt_nni_interface_cfg_data_id_config_state BCMOLT_NNI_INTERFACE_CFG_DATA_ID_CONFIG_STATE
#define bcmolt_nni_interface_cfg_data_id_state BCMOLT_NNI_INTERFACE_CFG_DATA_ID_STATE
#define bcmolt_nni_interface_cfg_data_id_link_state BCMOLT_NNI_INTERFACE_CFG_DATA_ID_LINK_STATE
#define bcmolt_nni_interface_cfg_data_id_link_fault_code BCMOLT_NNI_INTERFACE_CFG_DATA_ID_LINK_FAULT_CODE
#define bcmolt_nni_interface_cfg_data_id_protection_type BCMOLT_NNI_INTERFACE_CFG_DATA_ID_PROTECTION_TYPE
#define bcmolt_nni_interface_cfg_data_id_description BCMOLT_NNI_INTERFACE_CFG_DATA_ID_DESCRIPTION
#define bcmolt_nni_interface_cfg_data_id_mtu BCMOLT_NNI_INTERFACE_CFG_DATA_ID_MTU
#define bcmolt_nni_interface_cfg_data_id_speed BCMOLT_NNI_INTERFACE_CFG_DATA_ID_SPEED
#define bcmolt_nni_interface_cfg_data_id_duplex BCMOLT_NNI_INTERFACE_CFG_DATA_ID_DUPLEX
#define bcmolt_nni_interface_cfg_data_id_auto_negotiate BCMOLT_NNI_INTERFACE_CFG_DATA_ID_AUTO_NEGOTIATE
#define bcmolt_nni_interface_cfg_data_id_sub_type BCMOLT_NNI_INTERFACE_CFG_DATA_ID_SUB_TYPE
#define bcmolt_nni_interface_cfg_data_id__num_of BCMOLT_NNI_INTERFACE_CFG_DATA_ID__NUM_OF
#define bcmolt_nni_interface_cfg_data_id_all_properties 0xFF
#define bcmolt_nni_interface_cfg_data_id_full_mask 0x1F7B

} bcmolt_nni_interface_cfg_data_id;

/** Identifiers for all fields in a 'nni_interface_set_nni_state_data'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_SET_NNI_STATE_DATA_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_SET_NNI_STATE_DATA_ID_NNI_STATE = 0, /**< nni_state. */
    BCMOLT_NNI_INTERFACE_SET_NNI_STATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_set_nni_state_data_id__begin BCMOLT_NNI_INTERFACE_SET_NNI_STATE_DATA_ID__BEGIN
#define bcmolt_nni_interface_set_nni_state_data_id_nni_state BCMOLT_NNI_INTERFACE_SET_NNI_STATE_DATA_ID_NNI_STATE
#define bcmolt_nni_interface_set_nni_state_data_id__num_of BCMOLT_NNI_INTERFACE_SET_NNI_STATE_DATA_ID__NUM_OF
#define bcmolt_nni_interface_set_nni_state_data_id_all_properties 0xFF
#define bcmolt_nni_interface_set_nni_state_data_id_full_mask 0x1

} bcmolt_nni_interface_set_nni_state_data_id;

/** Identifiers for all fields in a 'nni_interface_stats_data'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BYTES = 0, /**< received bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_PACKETS = 1, /**< received  packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS = 2, /**< received  unicast packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS = 3, /**< received  multicast packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS = 4, /**< received  broadcast packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS = 5, /**< received error packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UNKNOWN_PROTOS = 6, /**< received unknown proto packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BYTES = 7, /**< transmitted bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_PACKETS = 8, /**< transmitted packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS = 9, /**< transmitted unicast packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS = 10, /**< transmitted multicast packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS = 11, /**< transmitted broadcast packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS = 12, /**< transmitted error packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_64 = 13, /**< rx 64 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127 = 14, /**< rx 65-127 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255 = 15, /**< rx 128-255 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511 = 16, /**< rx 256-511 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023 = 17, /**< rx 512-1023 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518 = 18, /**< rx 1024-1518 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047 = 19, /**< rx 1519-2047 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095 = 20, /**< rx 2048-4095 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216 = 21, /**< rx 4096-9216 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383 = 22, /**< rx 9217-16383 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_64 = 23, /**< tx 64 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127 = 24, /**< tx 65-127 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255 = 25, /**< tx 128-255 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511 = 26, /**< tx 256-511 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023 = 27, /**< tx 512-1023 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518 = 28, /**< tx 1024-1518 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047 = 29, /**< tx 1519-2047 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095 = 30, /**< tx 2048-4095 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216 = 31, /**< tx 4096-9216 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383 = 32, /**< tx 9217-16383 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS = 33, /**< rx fcs error packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS = 34, /**< rx undersize packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS = 35, /**< rx oversize packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS = 36, /**< tx undersize packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS = 37, /**< tx oversize packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS = 38, /**< tx jabber packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS = 39, /**< rx jabber packets. */
    BCMOLT_NNI_INTERFACE_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_stats_data_id__begin BCMOLT_NNI_INTERFACE_STATS_DATA_ID__BEGIN
#define bcmolt_nni_interface_stats_data_id_rx_bytes BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BYTES
#define bcmolt_nni_interface_stats_data_id_rx_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_PACKETS
#define bcmolt_nni_interface_stats_data_id_rx_ucast_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS
#define bcmolt_nni_interface_stats_data_id_rx_mcast_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS
#define bcmolt_nni_interface_stats_data_id_rx_bcast_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS
#define bcmolt_nni_interface_stats_data_id_rx_error_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS
#define bcmolt_nni_interface_stats_data_id_rx_unknown_protos BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UNKNOWN_PROTOS
#define bcmolt_nni_interface_stats_data_id_tx_bytes BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BYTES
#define bcmolt_nni_interface_stats_data_id_tx_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_PACKETS
#define bcmolt_nni_interface_stats_data_id_tx_ucast_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS
#define bcmolt_nni_interface_stats_data_id_tx_mcast_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS
#define bcmolt_nni_interface_stats_data_id_tx_bcast_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS
#define bcmolt_nni_interface_stats_data_id_tx_error_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS
#define bcmolt_nni_interface_stats_data_id_rx_frames_64 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_64
#define bcmolt_nni_interface_stats_data_id_rx_frames_65_127 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127
#define bcmolt_nni_interface_stats_data_id_rx_frames_128_255 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255
#define bcmolt_nni_interface_stats_data_id_rx_frames_256_511 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511
#define bcmolt_nni_interface_stats_data_id_rx_frames_512_1023 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_nni_interface_stats_data_id_rx_frames_1024_1518 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_nni_interface_stats_data_id_rx_frames_1519_2047 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_nni_interface_stats_data_id_rx_frames_2048_4095 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_nni_interface_stats_data_id_rx_frames_4096_9216 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_nni_interface_stats_data_id_rx_frames_9217_16383 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_nni_interface_stats_data_id_tx_frames_64 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_64
#define bcmolt_nni_interface_stats_data_id_tx_frames_65_127 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127
#define bcmolt_nni_interface_stats_data_id_tx_frames_128_255 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255
#define bcmolt_nni_interface_stats_data_id_tx_frames_256_511 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511
#define bcmolt_nni_interface_stats_data_id_tx_frames_512_1023 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_nni_interface_stats_data_id_tx_frames_1024_1518 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_nni_interface_stats_data_id_tx_frames_1519_2047 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_nni_interface_stats_data_id_tx_frames_2048_4095 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_nni_interface_stats_data_id_tx_frames_4096_9216 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_nni_interface_stats_data_id_tx_frames_9217_16383 BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_nni_interface_stats_data_id_rx_fcs_error_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS
#define bcmolt_nni_interface_stats_data_id_rx_undersize_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS
#define bcmolt_nni_interface_stats_data_id_rx_oversize_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS
#define bcmolt_nni_interface_stats_data_id_tx_undersize_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS
#define bcmolt_nni_interface_stats_data_id_tx_oversize_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS
#define bcmolt_nni_interface_stats_data_id_tx_jabber_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS
#define bcmolt_nni_interface_stats_data_id_rx_jabber_packets BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS
#define bcmolt_nni_interface_stats_data_id__num_of BCMOLT_NNI_INTERFACE_STATS_DATA_ID__NUM_OF
#define bcmolt_nni_interface_stats_data_id_all_properties 0xFF
#define bcmolt_nni_interface_stats_data_id_full_mask 0xFFFFFFFFFF

} bcmolt_nni_interface_stats_data_id;

/** Identifiers for all fields in a 'nni_interface_link_state_change_data'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID_OLD_STATE = 0, /**< old_state. */
    BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID_NEW_STATE = 1, /**< new_state. */
    BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID_FAULT_CODE = 2, /**< fault_code. */
    BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_link_state_change_data_id__begin BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID__BEGIN
#define bcmolt_nni_interface_link_state_change_data_id_old_state BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID_OLD_STATE
#define bcmolt_nni_interface_link_state_change_data_id_new_state BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID_NEW_STATE
#define bcmolt_nni_interface_link_state_change_data_id_fault_code BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID_FAULT_CODE
#define bcmolt_nni_interface_link_state_change_data_id__num_of BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID__NUM_OF
#define bcmolt_nni_interface_link_state_change_data_id_all_properties 0xFF
#define bcmolt_nni_interface_link_state_change_data_id_full_mask 0x7

} bcmolt_nni_interface_link_state_change_data_id;

/** Identifiers for all fields in a 'nni_interface_stats_cfg_data'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_BYTES = 0, /**< received bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_PACKETS = 1, /**< received  packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_UCAST_PACKETS = 2, /**< received  unicast packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_MCAST_PACKETS = 3, /**< received  multicast packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_BCAST_PACKETS = 4, /**< received  broadcast packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_ERROR_PACKETS = 5, /**< received error packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_UNKNOWN_PROTOS = 6, /**< received unknown proto packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_BYTES = 7, /**< transmitted bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_PACKETS = 8, /**< transmitted packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_UCAST_PACKETS = 9, /**< transmitted unicast packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_MCAST_PACKETS = 10, /**< transmitted multicast packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_BCAST_PACKETS = 11, /**< transmitted broadcast packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_ERROR_PACKETS = 12, /**< transmitted error packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_64 = 13, /**< rx 64 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_65_127 = 14, /**< rx 65-127 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_128_255 = 15, /**< rx 128-255 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_256_511 = 16, /**< rx 256-511 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_512_1023 = 17, /**< rx 512-1023 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518 = 18, /**< rx 1024-1518 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047 = 19, /**< rx 1519-2047 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095 = 20, /**< rx 2048-4095 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216 = 21, /**< rx 4096-9216 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383 = 22, /**< rx 9217-16383 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_64 = 23, /**< tx 64 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_65_127 = 24, /**< tx 65-127 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_128_255 = 25, /**< tx 128-255 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_256_511 = 26, /**< tx 256-511 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_512_1023 = 27, /**< tx 512-1023 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518 = 28, /**< tx 1024-1518 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047 = 29, /**< tx 1519-2047 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095 = 30, /**< tx 2048-4095 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216 = 31, /**< tx 4096-9216 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383 = 32, /**< tx 9217-16383 Bytes. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FCS_ERROR_PACKETS = 33, /**< rx fcs error packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_UNDERSIZE_PACKETS = 34, /**< rx undersize packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_OVERSIZE_PACKETS = 35, /**< rx oversize packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_UNDERSIZE_PACKETS = 36, /**< tx undersize packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_OVERSIZE_PACKETS = 37, /**< tx oversize packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_JABBER_PACKETS = 38, /**< tx jabber packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_JABBER_PACKETS = 39, /**< rx jabber packets. */
    BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_stats_cfg_data_id__begin BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_nni_interface_stats_cfg_data_id_rx_bytes BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_BYTES
#define bcmolt_nni_interface_stats_cfg_data_id_rx_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_rx_ucast_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_UCAST_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_rx_mcast_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_MCAST_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_rx_bcast_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_BCAST_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_rx_error_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_ERROR_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_rx_unknown_protos BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_UNKNOWN_PROTOS
#define bcmolt_nni_interface_stats_cfg_data_id_tx_bytes BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_BYTES
#define bcmolt_nni_interface_stats_cfg_data_id_tx_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_tx_ucast_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_UCAST_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_tx_mcast_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_MCAST_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_tx_bcast_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_BCAST_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_tx_error_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_ERROR_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_64 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_64
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_65_127 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_65_127
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_128_255 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_128_255
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_256_511 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_256_511
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_512_1023 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_1024_1518 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_1519_2047 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_2048_4095 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_4096_9216 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_nni_interface_stats_cfg_data_id_rx_frames_9217_16383 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_64 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_64
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_65_127 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_65_127
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_128_255 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_128_255
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_256_511 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_256_511
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_512_1023 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_1024_1518 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_1519_2047 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_2048_4095 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_4096_9216 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_nni_interface_stats_cfg_data_id_tx_frames_9217_16383 BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_nni_interface_stats_cfg_data_id_rx_fcs_error_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FCS_ERROR_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_rx_undersize_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_UNDERSIZE_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_rx_oversize_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_OVERSIZE_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_tx_undersize_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_UNDERSIZE_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_tx_oversize_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_OVERSIZE_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_tx_jabber_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_JABBER_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id_rx_jabber_packets BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_JABBER_PACKETS
#define bcmolt_nni_interface_stats_cfg_data_id__num_of BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_nni_interface_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_nni_interface_stats_cfg_data_id_full_mask 0xFFFFFFFFFF

} bcmolt_nni_interface_stats_cfg_data_id;

/** Identifiers for all fields in a 'nni_interface_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_NNI_INTERFACE_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_stats_alarm_raised_data_id__begin BCMOLT_NNI_INTERFACE_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_nni_interface_stats_alarm_raised_data_id_stat BCMOLT_NNI_INTERFACE_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_nni_interface_stats_alarm_raised_data_id__num_of BCMOLT_NNI_INTERFACE_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_nni_interface_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_nni_interface_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_nni_interface_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'nni_interface_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_NNI_INTERFACE_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_stats_alarm_cleared_data_id__begin BCMOLT_NNI_INTERFACE_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_nni_interface_stats_alarm_cleared_data_id_stat BCMOLT_NNI_INTERFACE_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_nni_interface_stats_alarm_cleared_data_id__num_of BCMOLT_NNI_INTERFACE_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_nni_interface_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_nni_interface_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_nni_interface_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'nni_interface_auto_cfg_data'. */
typedef enum
{
    BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_LINK_STATE_CHANGE = 0, /**< link_state_change. */
    BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_STATE_CHANGE = 1, /**< State Change. */
    BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED = 2, /**< NNI Interface Statistics Alarm Cleared. */
    BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED = 3, /**< NNI Interface Statistics Alarm Raised. */
    BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_nni_interface_auto_cfg_data_id__begin BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_nni_interface_auto_cfg_data_id_link_state_change BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_LINK_STATE_CHANGE
#define bcmolt_nni_interface_auto_cfg_data_id_state_change BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_STATE_CHANGE
#define bcmolt_nni_interface_auto_cfg_data_id_stats_alarm_cleared BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED
#define bcmolt_nni_interface_auto_cfg_data_id_stats_alarm_raised BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED
#define bcmolt_nni_interface_auto_cfg_data_id__num_of BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_nni_interface_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_nni_interface_auto_cfg_data_id_full_mask 0xF

} bcmolt_nni_interface_auto_cfg_data_id;

/** Identifiers for all fields in a 'olt_key'. */
typedef enum
{
    BCMOLT_OLT_KEY_ID__BEGIN = 0,
    BCMOLT_OLT_KEY_ID_RESERVED = 0, /**< Reserved. */
    BCMOLT_OLT_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_olt_key_id__begin BCMOLT_OLT_KEY_ID__BEGIN
#define bcmolt_olt_key_id_reserved BCMOLT_OLT_KEY_ID_RESERVED
#define bcmolt_olt_key_id__num_of BCMOLT_OLT_KEY_ID__NUM_OF
#define bcmolt_olt_key_id_all_properties 0xFF
#define bcmolt_olt_key_id_full_mask 0x1

} bcmolt_olt_key_id;

/** Identifiers for all fields in a 'olt_cfg_data'. */
typedef enum
{
    BCMOLT_OLT_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_OLT_CFG_DATA_ID_TOPOLOGY = 0, /**< topology. */
    BCMOLT_OLT_CFG_DATA_ID_BAL_STATE = 1, /**< BAL and Switch device state. */
    BCMOLT_OLT_CFG_DATA_ID_HOST_SW_VERSION = 2, /**< Host Software Version. */
    BCMOLT_OLT_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_olt_cfg_data_id__begin BCMOLT_OLT_CFG_DATA_ID__BEGIN
#define bcmolt_olt_cfg_data_id_topology BCMOLT_OLT_CFG_DATA_ID_TOPOLOGY
#define bcmolt_olt_cfg_data_id_bal_state BCMOLT_OLT_CFG_DATA_ID_BAL_STATE
#define bcmolt_olt_cfg_data_id_host_sw_version BCMOLT_OLT_CFG_DATA_ID_HOST_SW_VERSION
#define bcmolt_olt_cfg_data_id__num_of BCMOLT_OLT_CFG_DATA_ID__NUM_OF
#define bcmolt_olt_cfg_data_id_all_properties 0xFF
#define bcmolt_olt_cfg_data_id_full_mask 0x7

} bcmolt_olt_cfg_data_id;

/** Identifiers for all fields in a 'olt_bal_failure_data'. */
typedef enum
{
    BCMOLT_OLT_BAL_FAILURE_DATA_ID__BEGIN = 0,
    BCMOLT_OLT_BAL_FAILURE_DATA_ID_REASON = 0, /**< Fail reason. */
    BCMOLT_OLT_BAL_FAILURE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_olt_bal_failure_data_id__begin BCMOLT_OLT_BAL_FAILURE_DATA_ID__BEGIN
#define bcmolt_olt_bal_failure_data_id_reason BCMOLT_OLT_BAL_FAILURE_DATA_ID_REASON
#define bcmolt_olt_bal_failure_data_id__num_of BCMOLT_OLT_BAL_FAILURE_DATA_ID__NUM_OF
#define bcmolt_olt_bal_failure_data_id_all_properties 0xFF
#define bcmolt_olt_bal_failure_data_id_full_mask 0x1

} bcmolt_olt_bal_failure_data_id;

/** Identifiers for all fields in a 'olt_sw_error_data'. */
typedef enum
{
    BCMOLT_OLT_SW_ERROR_DATA_ID__BEGIN = 0,
    BCMOLT_OLT_SW_ERROR_DATA_ID_TASK_NAME = 0, /**< Task Name. */
    BCMOLT_OLT_SW_ERROR_DATA_ID_FILE_NAME = 1, /**< File Name. */
    BCMOLT_OLT_SW_ERROR_DATA_ID_LINE_NUMBER = 2, /**< Line Number. */
    BCMOLT_OLT_SW_ERROR_DATA_ID_ERROR_STRING = 3, /**< User error string. */
    BCMOLT_OLT_SW_ERROR_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_olt_sw_error_data_id__begin BCMOLT_OLT_SW_ERROR_DATA_ID__BEGIN
#define bcmolt_olt_sw_error_data_id_task_name BCMOLT_OLT_SW_ERROR_DATA_ID_TASK_NAME
#define bcmolt_olt_sw_error_data_id_file_name BCMOLT_OLT_SW_ERROR_DATA_ID_FILE_NAME
#define bcmolt_olt_sw_error_data_id_line_number BCMOLT_OLT_SW_ERROR_DATA_ID_LINE_NUMBER
#define bcmolt_olt_sw_error_data_id_error_string BCMOLT_OLT_SW_ERROR_DATA_ID_ERROR_STRING
#define bcmolt_olt_sw_error_data_id__num_of BCMOLT_OLT_SW_ERROR_DATA_ID__NUM_OF
#define bcmolt_olt_sw_error_data_id_all_properties 0xFF
#define bcmolt_olt_sw_error_data_id_full_mask 0xF

} bcmolt_olt_sw_error_data_id;

/** Identifiers for all fields in a 'olt_reset_data'. */
typedef enum
{
    BCMOLT_OLT_RESET_DATA_ID__BEGIN = 0,
    BCMOLT_OLT_RESET_DATA_ID_MODE = 0, /**< Reset Mode. */
    BCMOLT_OLT_RESET_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_olt_reset_data_id__begin BCMOLT_OLT_RESET_DATA_ID__BEGIN
#define bcmolt_olt_reset_data_id_mode BCMOLT_OLT_RESET_DATA_ID_MODE
#define bcmolt_olt_reset_data_id__num_of BCMOLT_OLT_RESET_DATA_ID__NUM_OF
#define bcmolt_olt_reset_data_id_all_properties 0xFF
#define bcmolt_olt_reset_data_id_full_mask 0x1

} bcmolt_olt_reset_data_id;

/** Identifiers for all fields in a 'olt_auto_cfg_data'. */
typedef enum
{
    BCMOLT_OLT_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_OLT_AUTO_CFG_DATA_ID_BAL_FAILURE = 0, /**< BAL and/or Switch Failed. */
    BCMOLT_OLT_AUTO_CFG_DATA_ID_BAL_READY = 1, /**< BAL and Switch Ready. */
    BCMOLT_OLT_AUTO_CFG_DATA_ID_SW_ERROR = 2, /**< OLT Software error. */
    BCMOLT_OLT_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_olt_auto_cfg_data_id__begin BCMOLT_OLT_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_olt_auto_cfg_data_id_bal_failure BCMOLT_OLT_AUTO_CFG_DATA_ID_BAL_FAILURE
#define bcmolt_olt_auto_cfg_data_id_bal_ready BCMOLT_OLT_AUTO_CFG_DATA_ID_BAL_READY
#define bcmolt_olt_auto_cfg_data_id_sw_error BCMOLT_OLT_AUTO_CFG_DATA_ID_SW_ERROR
#define bcmolt_olt_auto_cfg_data_id__num_of BCMOLT_OLT_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_olt_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_olt_auto_cfg_data_id_full_mask 0x7

} bcmolt_olt_auto_cfg_data_id;

/** Identifiers for all fields in a 'onu_key'. */
typedef enum
{
    BCMOLT_ONU_KEY_ID__BEGIN = 0,
    BCMOLT_ONU_KEY_ID_PON_NI = 0, /**< PON network interface. */
    BCMOLT_ONU_KEY_ID_ONU_ID = 1, /**< onu id. */
    BCMOLT_ONU_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_key_id__begin BCMOLT_ONU_KEY_ID__BEGIN
#define bcmolt_onu_key_id_pon_ni BCMOLT_ONU_KEY_ID_PON_NI
#define bcmolt_onu_key_id_onu_id BCMOLT_ONU_KEY_ID_ONU_ID
#define bcmolt_onu_key_id__num_of BCMOLT_ONU_KEY_ID__NUM_OF
#define bcmolt_onu_key_id_all_properties 0xFF
#define bcmolt_onu_key_id_full_mask 0x3

} bcmolt_onu_key_id;

/** Identifiers for all fields in a 'onu_cfg_data'. */
typedef enum
{
    BCMOLT_ONU_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_CFG_DATA_ID_ONU_STATE = 0, /**< onu state. */
    BCMOLT_ONU_CFG_DATA_ID_ONU_OLD_STATE = 1, /**< onu old state. */
    BCMOLT_ONU_CFG_DATA_ID_ONU_RATE = 2, /**< ONU rate. */
    BCMOLT_ONU_CFG_DATA_ID_ITU = 3, /**< ITU ONU Parameters (GPON, XGPON1, NGPON2, XGS PON). */
    BCMOLT_ONU_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_cfg_data_id__begin BCMOLT_ONU_CFG_DATA_ID__BEGIN
#define bcmolt_onu_cfg_data_id_onu_state BCMOLT_ONU_CFG_DATA_ID_ONU_STATE
#define bcmolt_onu_cfg_data_id_onu_old_state BCMOLT_ONU_CFG_DATA_ID_ONU_OLD_STATE
#define bcmolt_onu_cfg_data_id_onu_rate BCMOLT_ONU_CFG_DATA_ID_ONU_RATE
#define bcmolt_onu_cfg_data_id_itu BCMOLT_ONU_CFG_DATA_ID_ITU
#define bcmolt_onu_cfg_data_id__num_of BCMOLT_ONU_CFG_DATA_ID__NUM_OF
#define bcmolt_onu_cfg_data_id_all_properties 0xFF
#define bcmolt_onu_cfg_data_id_full_mask 0xF

} bcmolt_onu_cfg_data_id;

/** Identifiers for all fields in a 'onu_itu_pon_stats_data'. */
typedef enum
{
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_POSITIVE_DRIFT = 0, /**< positive drift. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_NEGATIVE_DRIFT = 1, /**< negative drift. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_DELIMITER_MISS_DETECTION = 2, /**< delimiter miss detection. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_ERRORS = 3, /**< bip errors. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_UNITS = 4, /**< Received units (In GPON units are bits, in other system modes units are Bytes) protected by BIP. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_SYMBOLS = 5, /**< fec corrected symbols  (Not relevant in GPON system modes). */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_CORRECTED = 6, /**< fec corrected codewords. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTABLE = 7, /**< fec uncorrectable codewords. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS = 8, /**< fec total codewords. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_UNITS = 9, /**< fec corrected units (In GPON units are bits in other system modes, units are Bytes). */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_KEY_ERRORS = 10, /**< xgem key error. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_LOSS = 11, /**< xgem loss. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR = 12, /**< mic error ploam. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE = 13, /**< non idle ploam. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI = 14, /**< Received OMCI packets. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR = 15, /**< Received OMCI packets with CRC errors. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_BYTES = 16, /**< rx bytes. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PACKETS = 17, /**< rx packets. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_BYTES = 18, /**< tx bytes. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_PACKETS = 19, /**< tx packets. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BER_REPORTED = 20, /**< ber reported. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_LCDG_ERRORS = 21, /**< LCDG errors. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RDI_ERRORS = 22, /**< RDI errors. */
    BCMOLT_ONU_ITU_PON_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_itu_pon_stats_data_id__begin BCMOLT_ONU_ITU_PON_STATS_DATA_ID__BEGIN
#define bcmolt_onu_itu_pon_stats_data_id_positive_drift BCMOLT_ONU_ITU_PON_STATS_DATA_ID_POSITIVE_DRIFT
#define bcmolt_onu_itu_pon_stats_data_id_negative_drift BCMOLT_ONU_ITU_PON_STATS_DATA_ID_NEGATIVE_DRIFT
#define bcmolt_onu_itu_pon_stats_data_id_delimiter_miss_detection BCMOLT_ONU_ITU_PON_STATS_DATA_ID_DELIMITER_MISS_DETECTION
#define bcmolt_onu_itu_pon_stats_data_id_bip_errors BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_ERRORS
#define bcmolt_onu_itu_pon_stats_data_id_bip_units BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_UNITS
#define bcmolt_onu_itu_pon_stats_data_id_fec_corrected_symbols BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_SYMBOLS
#define bcmolt_onu_itu_pon_stats_data_id_fec_codewords_corrected BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_CORRECTED
#define bcmolt_onu_itu_pon_stats_data_id_fec_codewords_uncorrectable BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTABLE
#define bcmolt_onu_itu_pon_stats_data_id_fec_codewords BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS
#define bcmolt_onu_itu_pon_stats_data_id_fec_corrected_units BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_UNITS
#define bcmolt_onu_itu_pon_stats_data_id_xgem_key_errors BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_KEY_ERRORS
#define bcmolt_onu_itu_pon_stats_data_id_xgem_loss BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_LOSS
#define bcmolt_onu_itu_pon_stats_data_id_rx_ploams_error BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR
#define bcmolt_onu_itu_pon_stats_data_id_rx_ploams_non_idle BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE
#define bcmolt_onu_itu_pon_stats_data_id_rx_omci BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI
#define bcmolt_onu_itu_pon_stats_data_id_rx_omci_packets_crc_error BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR
#define bcmolt_onu_itu_pon_stats_data_id_rx_bytes BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_BYTES
#define bcmolt_onu_itu_pon_stats_data_id_rx_packets BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PACKETS
#define bcmolt_onu_itu_pon_stats_data_id_tx_bytes BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_BYTES
#define bcmolt_onu_itu_pon_stats_data_id_tx_packets BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_PACKETS
#define bcmolt_onu_itu_pon_stats_data_id_ber_reported BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BER_REPORTED
#define bcmolt_onu_itu_pon_stats_data_id_lcdg_errors BCMOLT_ONU_ITU_PON_STATS_DATA_ID_LCDG_ERRORS
#define bcmolt_onu_itu_pon_stats_data_id_rdi_errors BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RDI_ERRORS
#define bcmolt_onu_itu_pon_stats_data_id__num_of BCMOLT_ONU_ITU_PON_STATS_DATA_ID__NUM_OF
#define bcmolt_onu_itu_pon_stats_data_id_all_properties 0xFF
#define bcmolt_onu_itu_pon_stats_data_id_full_mask 0x7FFFFF

} bcmolt_onu_itu_pon_stats_data_id;

/** Identifiers for all fields in a 'onu_set_onu_state_data'. */
typedef enum
{
    BCMOLT_ONU_SET_ONU_STATE_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_SET_ONU_STATE_DATA_ID_ONU_STATE = 0, /**< ONU state. */
    BCMOLT_ONU_SET_ONU_STATE_DATA_ID_MEASURE_RSSI = 1, /**< Enable RSSI measurement during activation. */
    BCMOLT_ONU_SET_ONU_STATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_set_onu_state_data_id__begin BCMOLT_ONU_SET_ONU_STATE_DATA_ID__BEGIN
#define bcmolt_onu_set_onu_state_data_id_onu_state BCMOLT_ONU_SET_ONU_STATE_DATA_ID_ONU_STATE
#define bcmolt_onu_set_onu_state_data_id_measure_rssi BCMOLT_ONU_SET_ONU_STATE_DATA_ID_MEASURE_RSSI
#define bcmolt_onu_set_onu_state_data_id__num_of BCMOLT_ONU_SET_ONU_STATE_DATA_ID__NUM_OF
#define bcmolt_onu_set_onu_state_data_id_all_properties 0xFF
#define bcmolt_onu_set_onu_state_data_id_full_mask 0x3

} bcmolt_onu_set_onu_state_data_id;

/** Identifiers for all fields in a 'onu_request_registration_data'. */
typedef enum
{
    BCMOLT_ONU_REQUEST_REGISTRATION_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_REQUEST_REGISTRATION_DATA_ID_SMA_FLAG = 0, /**< SMA flag. */
    BCMOLT_ONU_REQUEST_REGISTRATION_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_request_registration_data_id__begin BCMOLT_ONU_REQUEST_REGISTRATION_DATA_ID__BEGIN
#define bcmolt_onu_request_registration_data_id_sma_flag BCMOLT_ONU_REQUEST_REGISTRATION_DATA_ID_SMA_FLAG
#define bcmolt_onu_request_registration_data_id__num_of BCMOLT_ONU_REQUEST_REGISTRATION_DATA_ID__NUM_OF
#define bcmolt_onu_request_registration_data_id_all_properties 0xFF
#define bcmolt_onu_request_registration_data_id_full_mask 0x1

} bcmolt_onu_request_registration_data_id;

/** Identifiers for all fields in a 'onu_change_power_levelling_data'. */
typedef enum
{
    BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID_CONTROL = 0, /**< control. */
    BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID_ATTENUATION = 1, /**< Attenuation. */
    BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_change_power_levelling_data_id__begin BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID__BEGIN
#define bcmolt_onu_change_power_levelling_data_id_control BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID_CONTROL
#define bcmolt_onu_change_power_levelling_data_id_attenuation BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID_ATTENUATION
#define bcmolt_onu_change_power_levelling_data_id__num_of BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID__NUM_OF
#define bcmolt_onu_change_power_levelling_data_id_all_properties 0xFF
#define bcmolt_onu_change_power_levelling_data_id_full_mask 0x3

} bcmolt_onu_change_power_levelling_data_id;

/** Identifiers for all fields in a 'onu_adjust_tx_wavelength_data'. */
typedef enum
{
    BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID_FREQUENCY_ADJUSTMENT_DIRECTION = 0, /**< Frequency adjustment direction. */
    BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID_FREQUENCY_ADJUSTMENT_SIZE = 1, /**< Frequency adjustment size. */
    BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_adjust_tx_wavelength_data_id__begin BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID__BEGIN
#define bcmolt_onu_adjust_tx_wavelength_data_id_frequency_adjustment_direction BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID_FREQUENCY_ADJUSTMENT_DIRECTION
#define bcmolt_onu_adjust_tx_wavelength_data_id_frequency_adjustment_size BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID_FREQUENCY_ADJUSTMENT_SIZE
#define bcmolt_onu_adjust_tx_wavelength_data_id__num_of BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID__NUM_OF
#define bcmolt_onu_adjust_tx_wavelength_data_id_all_properties 0xFF
#define bcmolt_onu_adjust_tx_wavelength_data_id_full_mask 0x3

} bcmolt_onu_adjust_tx_wavelength_data_id;

/** Identifiers for all fields in a 'onu_secure_mutual_authentication_data'. */
typedef enum
{
    BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID_MASTER_KEY = 0, /**< master key. */
    BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID_BUFFER = 1, /**< OMCI data buffer. */
    BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID_MIC = 2, /**< mic. */
    BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_secure_mutual_authentication_data_id__begin BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID__BEGIN
#define bcmolt_onu_secure_mutual_authentication_data_id_master_key BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID_MASTER_KEY
#define bcmolt_onu_secure_mutual_authentication_data_id_buffer BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID_BUFFER
#define bcmolt_onu_secure_mutual_authentication_data_id_mic BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID_MIC
#define bcmolt_onu_secure_mutual_authentication_data_id__num_of BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID__NUM_OF
#define bcmolt_onu_secure_mutual_authentication_data_id_all_properties 0xFF
#define bcmolt_onu_secure_mutual_authentication_data_id_full_mask 0x7

} bcmolt_onu_secure_mutual_authentication_data_id;

/** Identifiers for all fields in a 'onu_tuning_out_data'. */
typedef enum
{
    BCMOLT_ONU_TUNING_OUT_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_TUNING_OUT_DATA_ID_TARGET_DS_PON_ID = 0, /**< target ds pon id. */
    BCMOLT_ONU_TUNING_OUT_DATA_ID_TARGET_US_PON_ID = 1, /**< target us pon id. */
    BCMOLT_ONU_TUNING_OUT_DATA_ID_TIME_TO_SWITCH = 2, /**< time to switch. */
    BCMOLT_ONU_TUNING_OUT_DATA_ID_ROLLBACK = 3, /**< rollback. */
    BCMOLT_ONU_TUNING_OUT_DATA_ID_STATUS = 4, /**< status. */
    BCMOLT_ONU_TUNING_OUT_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_tuning_out_data_id__begin BCMOLT_ONU_TUNING_OUT_DATA_ID__BEGIN
#define bcmolt_onu_tuning_out_data_id_target_ds_pon_id BCMOLT_ONU_TUNING_OUT_DATA_ID_TARGET_DS_PON_ID
#define bcmolt_onu_tuning_out_data_id_target_us_pon_id BCMOLT_ONU_TUNING_OUT_DATA_ID_TARGET_US_PON_ID
#define bcmolt_onu_tuning_out_data_id_time_to_switch BCMOLT_ONU_TUNING_OUT_DATA_ID_TIME_TO_SWITCH
#define bcmolt_onu_tuning_out_data_id_rollback BCMOLT_ONU_TUNING_OUT_DATA_ID_ROLLBACK
#define bcmolt_onu_tuning_out_data_id_status BCMOLT_ONU_TUNING_OUT_DATA_ID_STATUS
#define bcmolt_onu_tuning_out_data_id__num_of BCMOLT_ONU_TUNING_OUT_DATA_ID__NUM_OF
#define bcmolt_onu_tuning_out_data_id_all_properties 0xFF
#define bcmolt_onu_tuning_out_data_id_full_mask 0x1F

} bcmolt_onu_tuning_out_data_id;

/** Identifiers for all fields in a 'onu_xgpon_alarm_data'. */
typedef enum
{
    BCMOLT_ONU_XGPON_ALARM_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_XGPON_ALARM_DATA_ID_XGPON_ONU_ALARM = 0, /**< xgpon onu alarm. */
    BCMOLT_ONU_XGPON_ALARM_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_xgpon_alarm_data_id__begin BCMOLT_ONU_XGPON_ALARM_DATA_ID__BEGIN
#define bcmolt_onu_xgpon_alarm_data_id_xgpon_onu_alarm BCMOLT_ONU_XGPON_ALARM_DATA_ID_XGPON_ONU_ALARM
#define bcmolt_onu_xgpon_alarm_data_id__num_of BCMOLT_ONU_XGPON_ALARM_DATA_ID__NUM_OF
#define bcmolt_onu_xgpon_alarm_data_id_all_properties 0xFF
#define bcmolt_onu_xgpon_alarm_data_id_full_mask 0x1

} bcmolt_onu_xgpon_alarm_data_id;

/** Identifiers for all fields in a 'onu_gpon_alarm_data'. */
typedef enum
{
    BCMOLT_ONU_GPON_ALARM_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_GPON_ALARM_DATA_ID_GPON_ONU_ALARM = 0, /**< gpon onu alarm. */
    BCMOLT_ONU_GPON_ALARM_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_gpon_alarm_data_id__begin BCMOLT_ONU_GPON_ALARM_DATA_ID__BEGIN
#define bcmolt_onu_gpon_alarm_data_id_gpon_onu_alarm BCMOLT_ONU_GPON_ALARM_DATA_ID_GPON_ONU_ALARM
#define bcmolt_onu_gpon_alarm_data_id__num_of BCMOLT_ONU_GPON_ALARM_DATA_ID__NUM_OF
#define bcmolt_onu_gpon_alarm_data_id_all_properties 0xFF
#define bcmolt_onu_gpon_alarm_data_id_full_mask 0x1

} bcmolt_onu_gpon_alarm_data_id;

/** Identifiers for all fields in a 'onu_dowi_data'. */
typedef enum
{
    BCMOLT_ONU_DOWI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_DOWI_DATA_ID_ALARM_STATUS = 0, /**< Alarm status. */
    BCMOLT_ONU_DOWI_DATA_ID_DRIFT_VALUE = 1, /**< Drift value. */
    BCMOLT_ONU_DOWI_DATA_ID_NEW_EQD = 2, /**< New EQD. */
    BCMOLT_ONU_DOWI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_dowi_data_id__begin BCMOLT_ONU_DOWI_DATA_ID__BEGIN
#define bcmolt_onu_dowi_data_id_alarm_status BCMOLT_ONU_DOWI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_dowi_data_id_drift_value BCMOLT_ONU_DOWI_DATA_ID_DRIFT_VALUE
#define bcmolt_onu_dowi_data_id_new_eqd BCMOLT_ONU_DOWI_DATA_ID_NEW_EQD
#define bcmolt_onu_dowi_data_id__num_of BCMOLT_ONU_DOWI_DATA_ID__NUM_OF
#define bcmolt_onu_dowi_data_id_all_properties 0xFF
#define bcmolt_onu_dowi_data_id_full_mask 0x7

} bcmolt_onu_dowi_data_id;

/** Identifiers for all fields in a 'onu_sfi_data'. */
typedef enum
{
    BCMOLT_ONU_SFI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_SFI_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_SFI_DATA_ID_BER = 1, /**< BER. */
    BCMOLT_ONU_SFI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_sfi_data_id__begin BCMOLT_ONU_SFI_DATA_ID__BEGIN
#define bcmolt_onu_sfi_data_id_alarm_status BCMOLT_ONU_SFI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_sfi_data_id_ber BCMOLT_ONU_SFI_DATA_ID_BER
#define bcmolt_onu_sfi_data_id__num_of BCMOLT_ONU_SFI_DATA_ID__NUM_OF
#define bcmolt_onu_sfi_data_id_all_properties 0xFF
#define bcmolt_onu_sfi_data_id_full_mask 0x3

} bcmolt_onu_sfi_data_id;

/** Identifiers for all fields in a 'onu_sdi_data'. */
typedef enum
{
    BCMOLT_ONU_SDI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_SDI_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_SDI_DATA_ID_BER = 1, /**< BER. */
    BCMOLT_ONU_SDI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_sdi_data_id__begin BCMOLT_ONU_SDI_DATA_ID__BEGIN
#define bcmolt_onu_sdi_data_id_alarm_status BCMOLT_ONU_SDI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_sdi_data_id_ber BCMOLT_ONU_SDI_DATA_ID_BER
#define bcmolt_onu_sdi_data_id__num_of BCMOLT_ONU_SDI_DATA_ID__NUM_OF
#define bcmolt_onu_sdi_data_id_all_properties 0xFF
#define bcmolt_onu_sdi_data_id_full_mask 0x3

} bcmolt_onu_sdi_data_id;

/** Identifiers for all fields in a 'onu_dfi_data'. */
typedef enum
{
    BCMOLT_ONU_DFI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_DFI_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_DFI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_dfi_data_id__begin BCMOLT_ONU_DFI_DATA_ID__BEGIN
#define bcmolt_onu_dfi_data_id_alarm_status BCMOLT_ONU_DFI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_dfi_data_id__num_of BCMOLT_ONU_DFI_DATA_ID__NUM_OF
#define bcmolt_onu_dfi_data_id_all_properties 0xFF
#define bcmolt_onu_dfi_data_id_full_mask 0x1

} bcmolt_onu_dfi_data_id;

/** Identifiers for all fields in a 'onu_pqsi_data'. */
typedef enum
{
    BCMOLT_ONU_PQSI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_PQSI_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_PQSI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_pqsi_data_id__begin BCMOLT_ONU_PQSI_DATA_ID__BEGIN
#define bcmolt_onu_pqsi_data_id_alarm_status BCMOLT_ONU_PQSI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_pqsi_data_id__num_of BCMOLT_ONU_PQSI_DATA_ID__NUM_OF
#define bcmolt_onu_pqsi_data_id_all_properties 0xFF
#define bcmolt_onu_pqsi_data_id_full_mask 0x1

} bcmolt_onu_pqsi_data_id;

/** Identifiers for all fields in a 'onu_sufi_data'. */
typedef enum
{
    BCMOLT_ONU_SUFI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_SUFI_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_SUFI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_sufi_data_id__begin BCMOLT_ONU_SUFI_DATA_ID__BEGIN
#define bcmolt_onu_sufi_data_id_alarm_status BCMOLT_ONU_SUFI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_sufi_data_id__num_of BCMOLT_ONU_SUFI_DATA_ID__NUM_OF
#define bcmolt_onu_sufi_data_id_all_properties 0xFF
#define bcmolt_onu_sufi_data_id_full_mask 0x1

} bcmolt_onu_sufi_data_id;

/** Identifiers for all fields in a 'onu_tiwi_data'. */
typedef enum
{
    BCMOLT_ONU_TIWI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_TIWI_DATA_ID_ALARM_STATUS = 0, /**< Alarm status. */
    BCMOLT_ONU_TIWI_DATA_ID_DRIFT_VALUE = 1, /**< Drift value. */
    BCMOLT_ONU_TIWI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_tiwi_data_id__begin BCMOLT_ONU_TIWI_DATA_ID__BEGIN
#define bcmolt_onu_tiwi_data_id_alarm_status BCMOLT_ONU_TIWI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_tiwi_data_id_drift_value BCMOLT_ONU_TIWI_DATA_ID_DRIFT_VALUE
#define bcmolt_onu_tiwi_data_id__num_of BCMOLT_ONU_TIWI_DATA_ID__NUM_OF
#define bcmolt_onu_tiwi_data_id_all_properties 0xFF
#define bcmolt_onu_tiwi_data_id_full_mask 0x3

} bcmolt_onu_tiwi_data_id;

/** Identifiers for all fields in a 'onu_looci_data'. */
typedef enum
{
    BCMOLT_ONU_LOOCI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_LOOCI_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_LOOCI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_looci_data_id__begin BCMOLT_ONU_LOOCI_DATA_ID__BEGIN
#define bcmolt_onu_looci_data_id_alarm_status BCMOLT_ONU_LOOCI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_looci_data_id__num_of BCMOLT_ONU_LOOCI_DATA_ID__NUM_OF
#define bcmolt_onu_looci_data_id_all_properties 0xFF
#define bcmolt_onu_looci_data_id_full_mask 0x1

} bcmolt_onu_looci_data_id;

/** Identifiers for all fields in a 'onu_loai_data'. */
typedef enum
{
    BCMOLT_ONU_LOAI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_LOAI_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_LOAI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_loai_data_id__begin BCMOLT_ONU_LOAI_DATA_ID__BEGIN
#define bcmolt_onu_loai_data_id_alarm_status BCMOLT_ONU_LOAI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_loai_data_id__num_of BCMOLT_ONU_LOAI_DATA_ID__NUM_OF
#define bcmolt_onu_loai_data_id_all_properties 0xFF
#define bcmolt_onu_loai_data_id_full_mask 0x1

} bcmolt_onu_loai_data_id;

/** Identifiers for all fields in a 'onu_dgi_data'. */
typedef enum
{
    BCMOLT_ONU_DGI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_DGI_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_DGI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_dgi_data_id__begin BCMOLT_ONU_DGI_DATA_ID__BEGIN
#define bcmolt_onu_dgi_data_id_alarm_status BCMOLT_ONU_DGI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_dgi_data_id__num_of BCMOLT_ONU_DGI_DATA_ID__NUM_OF
#define bcmolt_onu_dgi_data_id_all_properties 0xFF
#define bcmolt_onu_dgi_data_id_full_mask 0x1

} bcmolt_onu_dgi_data_id;

/** Identifiers for all fields in a 'onu_pee_data'. */
typedef enum
{
    BCMOLT_ONU_PEE_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_PEE_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_PEE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_pee_data_id__begin BCMOLT_ONU_PEE_DATA_ID__BEGIN
#define bcmolt_onu_pee_data_id_alarm_status BCMOLT_ONU_PEE_DATA_ID_ALARM_STATUS
#define bcmolt_onu_pee_data_id__num_of BCMOLT_ONU_PEE_DATA_ID__NUM_OF
#define bcmolt_onu_pee_data_id_all_properties 0xFF
#define bcmolt_onu_pee_data_id_full_mask 0x1

} bcmolt_onu_pee_data_id;

/** Identifiers for all fields in a 'onu_pst_data'. */
typedef enum
{
    BCMOLT_ONU_PST_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_PST_DATA_ID_LINK_NUMBER = 0, /**< link number. */
    BCMOLT_ONU_PST_DATA_ID_K1 = 1, /**< K1. */
    BCMOLT_ONU_PST_DATA_ID_K2 = 2, /**< K2. */
    BCMOLT_ONU_PST_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_pst_data_id__begin BCMOLT_ONU_PST_DATA_ID__BEGIN
#define bcmolt_onu_pst_data_id_link_number BCMOLT_ONU_PST_DATA_ID_LINK_NUMBER
#define bcmolt_onu_pst_data_id_k1 BCMOLT_ONU_PST_DATA_ID_K1
#define bcmolt_onu_pst_data_id_k2 BCMOLT_ONU_PST_DATA_ID_K2
#define bcmolt_onu_pst_data_id__num_of BCMOLT_ONU_PST_DATA_ID__NUM_OF
#define bcmolt_onu_pst_data_id_all_properties 0xFF
#define bcmolt_onu_pst_data_id_full_mask 0x7

} bcmolt_onu_pst_data_id;

/** Identifiers for all fields in a 'onu_ranging_completed_data'. */
typedef enum
{
    BCMOLT_ONU_RANGING_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_STATUS = 0, /**< status. */
    BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_EQD = 2, /**< EQD. */
    BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_NUMBER_OF_PLOAMS = 3, /**< number of ploams. */
    BCMOLT_ONU_RANGING_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_ranging_completed_data_id__begin BCMOLT_ONU_RANGING_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_ranging_completed_data_id_status BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_STATUS
#define bcmolt_onu_ranging_completed_data_id_fail_reason BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_FAIL_REASON
#define bcmolt_onu_ranging_completed_data_id_eqd BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_EQD
#define bcmolt_onu_ranging_completed_data_id_number_of_ploams BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_NUMBER_OF_PLOAMS
#define bcmolt_onu_ranging_completed_data_id__num_of BCMOLT_ONU_RANGING_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_ranging_completed_data_id_all_properties 0xFF
#define bcmolt_onu_ranging_completed_data_id_full_mask 0xF

} bcmolt_onu_ranging_completed_data_id;

/** Identifiers for all fields in a 'onu_onu_activation_completed_data'. */
typedef enum
{
    BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_STATUS = 0, /**< status. */
    BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_REGISTRATION_ID = 2, /**< registration id. */
    BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_REGISTRATION_ENCRYPTION_KEYS = 3, /**< registration encryption keys. */
    BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_RSSI_MEASUREMENT = 4, /**< rssi measurement. */
    BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_onu_activation_completed_data_id__begin BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_onu_activation_completed_data_id_status BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_STATUS
#define bcmolt_onu_onu_activation_completed_data_id_fail_reason BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_FAIL_REASON
#define bcmolt_onu_onu_activation_completed_data_id_registration_id BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_REGISTRATION_ID
#define bcmolt_onu_onu_activation_completed_data_id_registration_encryption_keys BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_REGISTRATION_ENCRYPTION_KEYS
#define bcmolt_onu_onu_activation_completed_data_id_rssi_measurement BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_RSSI_MEASUREMENT
#define bcmolt_onu_onu_activation_completed_data_id__num_of BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_onu_activation_completed_data_id_all_properties 0xFF
#define bcmolt_onu_onu_activation_completed_data_id_full_mask 0x1F

} bcmolt_onu_onu_activation_completed_data_id;

/** Identifiers for all fields in a 'onu_onu_deactivation_completed_data'. */
typedef enum
{
    BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID_STATUS = 0, /**< Status. */
    BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_onu_deactivation_completed_data_id__begin BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_onu_deactivation_completed_data_id_status BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID_STATUS
#define bcmolt_onu_onu_deactivation_completed_data_id_fail_reason BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID_FAIL_REASON
#define bcmolt_onu_onu_deactivation_completed_data_id__num_of BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_onu_deactivation_completed_data_id_all_properties 0xFF
#define bcmolt_onu_onu_deactivation_completed_data_id_full_mask 0x3

} bcmolt_onu_onu_deactivation_completed_data_id;

/** Identifiers for all fields in a 'onu_onu_enable_completed_data'. */
typedef enum
{
    BCMOLT_ONU_ONU_ENABLE_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ONU_ENABLE_COMPLETED_DATA_ID_SERIAL_NUMBER = 0, /**< serial number. */
    BCMOLT_ONU_ONU_ENABLE_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_onu_enable_completed_data_id__begin BCMOLT_ONU_ONU_ENABLE_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_onu_enable_completed_data_id_serial_number BCMOLT_ONU_ONU_ENABLE_COMPLETED_DATA_ID_SERIAL_NUMBER
#define bcmolt_onu_onu_enable_completed_data_id__num_of BCMOLT_ONU_ONU_ENABLE_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_onu_enable_completed_data_id_all_properties 0xFF
#define bcmolt_onu_onu_enable_completed_data_id_full_mask 0x1

} bcmolt_onu_onu_enable_completed_data_id;

/** Identifiers for all fields in a 'onu_onu_disable_completed_data'. */
typedef enum
{
    BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID_SERIAL_NUMBER = 0, /**< serial number. */
    BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID_STATUS = 2, /**< status. */
    BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_onu_disable_completed_data_id__begin BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_onu_disable_completed_data_id_serial_number BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID_SERIAL_NUMBER
#define bcmolt_onu_onu_disable_completed_data_id_fail_reason BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID_FAIL_REASON
#define bcmolt_onu_onu_disable_completed_data_id_status BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID_STATUS
#define bcmolt_onu_onu_disable_completed_data_id__num_of BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_onu_disable_completed_data_id_all_properties 0xFF
#define bcmolt_onu_onu_disable_completed_data_id_full_mask 0x7

} bcmolt_onu_onu_disable_completed_data_id;

/** Identifiers for all fields in a 'onu_rssi_measurement_completed_data'. */
typedef enum
{
    BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID_STATUS = 0, /**< status. */
    BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_rssi_measurement_completed_data_id__begin BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_rssi_measurement_completed_data_id_status BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID_STATUS
#define bcmolt_onu_rssi_measurement_completed_data_id_fail_reason BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID_FAIL_REASON
#define bcmolt_onu_rssi_measurement_completed_data_id__num_of BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_rssi_measurement_completed_data_id_all_properties 0xFF
#define bcmolt_onu_rssi_measurement_completed_data_id_full_mask 0x3

} bcmolt_onu_rssi_measurement_completed_data_id;

/** Identifiers for all fields in a 'onu_invalid_dbru_report_data'. */
typedef enum
{
    BCMOLT_ONU_INVALID_DBRU_REPORT_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_INVALID_DBRU_REPORT_DATA_ID_ALLOC_ID = 0, /**< Alloc-ID. */
    BCMOLT_ONU_INVALID_DBRU_REPORT_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_invalid_dbru_report_data_id__begin BCMOLT_ONU_INVALID_DBRU_REPORT_DATA_ID__BEGIN
#define bcmolt_onu_invalid_dbru_report_data_id_alloc_id BCMOLT_ONU_INVALID_DBRU_REPORT_DATA_ID_ALLOC_ID
#define bcmolt_onu_invalid_dbru_report_data_id__num_of BCMOLT_ONU_INVALID_DBRU_REPORT_DATA_ID__NUM_OF
#define bcmolt_onu_invalid_dbru_report_data_id_all_properties 0xFF
#define bcmolt_onu_invalid_dbru_report_data_id_full_mask 0x1

} bcmolt_onu_invalid_dbru_report_data_id;

/** Identifiers for all fields in a 'onu_key_exchange_completed_data'. */
typedef enum
{
    BCMOLT_ONU_KEY_EXCHANGE_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_KEY_EXCHANGE_COMPLETED_DATA_ID_NEW_KEY = 0, /**< new key. */
    BCMOLT_ONU_KEY_EXCHANGE_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_key_exchange_completed_data_id__begin BCMOLT_ONU_KEY_EXCHANGE_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_key_exchange_completed_data_id_new_key BCMOLT_ONU_KEY_EXCHANGE_COMPLETED_DATA_ID_NEW_KEY
#define bcmolt_onu_key_exchange_completed_data_id__num_of BCMOLT_ONU_KEY_EXCHANGE_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_key_exchange_completed_data_id_all_properties 0xFF
#define bcmolt_onu_key_exchange_completed_data_id_full_mask 0x1

} bcmolt_onu_key_exchange_completed_data_id;

/** Identifiers for all fields in a 'onu_key_exchange_key_mismatch_data'. */
typedef enum
{
    BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID_EXPECTED_KEY = 0, /**< expected key. */
    BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID_RECEIVED_KEY = 1, /**< received key. */
    BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_key_exchange_key_mismatch_data_id__begin BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID__BEGIN
#define bcmolt_onu_key_exchange_key_mismatch_data_id_expected_key BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID_EXPECTED_KEY
#define bcmolt_onu_key_exchange_key_mismatch_data_id_received_key BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID_RECEIVED_KEY
#define bcmolt_onu_key_exchange_key_mismatch_data_id__num_of BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID__NUM_OF
#define bcmolt_onu_key_exchange_key_mismatch_data_id_all_properties 0xFF
#define bcmolt_onu_key_exchange_key_mismatch_data_id_full_mask 0x3

} bcmolt_onu_key_exchange_key_mismatch_data_id;

/** Identifiers for all fields in a 'onu_loki_data'. */
typedef enum
{
    BCMOLT_ONU_LOKI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_LOKI_DATA_ID_ALARM_STATUS = 0, /**< alarm status. */
    BCMOLT_ONU_LOKI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_loki_data_id__begin BCMOLT_ONU_LOKI_DATA_ID__BEGIN
#define bcmolt_onu_loki_data_id_alarm_status BCMOLT_ONU_LOKI_DATA_ID_ALARM_STATUS
#define bcmolt_onu_loki_data_id__num_of BCMOLT_ONU_LOKI_DATA_ID__NUM_OF
#define bcmolt_onu_loki_data_id_all_properties 0xFF
#define bcmolt_onu_loki_data_id_full_mask 0x1

} bcmolt_onu_loki_data_id;

/** Identifiers for all fields in a 'onu_memi_data'. */
typedef enum
{
    BCMOLT_ONU_MEMI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_MEMI_DATA_ID_PLOAM_BUFFER = 0, /**< PLOAM buffer. */
    BCMOLT_ONU_MEMI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_memi_data_id__begin BCMOLT_ONU_MEMI_DATA_ID__BEGIN
#define bcmolt_onu_memi_data_id_ploam_buffer BCMOLT_ONU_MEMI_DATA_ID_PLOAM_BUFFER
#define bcmolt_onu_memi_data_id__num_of BCMOLT_ONU_MEMI_DATA_ID__NUM_OF
#define bcmolt_onu_memi_data_id_all_properties 0xFF
#define bcmolt_onu_memi_data_id_full_mask 0x1

} bcmolt_onu_memi_data_id;

/** Identifiers for all fields in a 'onu_omci_port_id_configuration_completed_data'. */
typedef enum
{
    BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID_GEM_PORT = 0, /**< GEM Port ID. */
    BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID_STATUS = 1, /**< status. */
    BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID_OPERATION = 2, /**< Operation. */
    BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_omci_port_id_configuration_completed_data_id__begin BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_omci_port_id_configuration_completed_data_id_gem_port BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID_GEM_PORT
#define bcmolt_onu_omci_port_id_configuration_completed_data_id_status BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID_STATUS
#define bcmolt_onu_omci_port_id_configuration_completed_data_id_operation BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID_OPERATION
#define bcmolt_onu_omci_port_id_configuration_completed_data_id__num_of BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_omci_port_id_configuration_completed_data_id_all_properties 0xFF
#define bcmolt_onu_omci_port_id_configuration_completed_data_id_full_mask 0x7

} bcmolt_onu_omci_port_id_configuration_completed_data_id;

/** Identifiers for all fields in a 'onu_ber_interval_configuration_completed_data'. */
typedef enum
{
    BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID_BER_INTERVAL = 0, /**< BER interval in ms. */
    BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID_RESULT = 1, /**< Result. */
    BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_ber_interval_configuration_completed_data_id__begin BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_ber_interval_configuration_completed_data_id_ber_interval BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID_BER_INTERVAL
#define bcmolt_onu_ber_interval_configuration_completed_data_id_result BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID_RESULT
#define bcmolt_onu_ber_interval_configuration_completed_data_id__num_of BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_ber_interval_configuration_completed_data_id_all_properties 0xFF
#define bcmolt_onu_ber_interval_configuration_completed_data_id_full_mask 0x3

} bcmolt_onu_ber_interval_configuration_completed_data_id;

/** Identifiers for all fields in a 'onu_err_data'. */
typedef enum
{
    BCMOLT_ONU_ERR_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ERR_DATA_ID_BIP8_ERRORS = 0, /**< BIP8 errors. */
    BCMOLT_ONU_ERR_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_err_data_id__begin BCMOLT_ONU_ERR_DATA_ID__BEGIN
#define bcmolt_onu_err_data_id_bip8_errors BCMOLT_ONU_ERR_DATA_ID_BIP8_ERRORS
#define bcmolt_onu_err_data_id__num_of BCMOLT_ONU_ERR_DATA_ID__NUM_OF
#define bcmolt_onu_err_data_id_all_properties 0xFF
#define bcmolt_onu_err_data_id_full_mask 0x1

} bcmolt_onu_err_data_id;

/** Identifiers for all fields in a 'onu_password_authentication_completed_data'. */
typedef enum
{
    BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID_STATUS = 0, /**< status. */
    BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID_PASSWORD = 2, /**< password. */
    BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_password_authentication_completed_data_id__begin BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_password_authentication_completed_data_id_status BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID_STATUS
#define bcmolt_onu_password_authentication_completed_data_id_fail_reason BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID_FAIL_REASON
#define bcmolt_onu_password_authentication_completed_data_id_password BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID_PASSWORD
#define bcmolt_onu_password_authentication_completed_data_id__num_of BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_password_authentication_completed_data_id_all_properties 0xFF
#define bcmolt_onu_password_authentication_completed_data_id_full_mask 0x7

} bcmolt_onu_password_authentication_completed_data_id;

/** Identifiers for all fields in a 'onu_key_exchange_unconsecutive_index_data'. */
typedef enum
{
    BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID_EXPECTED_INDEX = 0, /**< expected index. */
    BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID_ACTUAL_INDEX = 1, /**< actual index. */
    BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_key_exchange_unconsecutive_index_data_id__begin BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID__BEGIN
#define bcmolt_onu_key_exchange_unconsecutive_index_data_id_expected_index BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID_EXPECTED_INDEX
#define bcmolt_onu_key_exchange_unconsecutive_index_data_id_actual_index BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID_ACTUAL_INDEX
#define bcmolt_onu_key_exchange_unconsecutive_index_data_id__num_of BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID__NUM_OF
#define bcmolt_onu_key_exchange_unconsecutive_index_data_id_all_properties 0xFF
#define bcmolt_onu_key_exchange_unconsecutive_index_data_id_full_mask 0x3

} bcmolt_onu_key_exchange_unconsecutive_index_data_id;

/** Identifiers for all fields in a 'onu_key_exchange_decrypt_required_data'. */
typedef enum
{
    BCMOLT_ONU_KEY_EXCHANGE_DECRYPT_REQUIRED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_KEY_EXCHANGE_DECRYPT_REQUIRED_DATA_ID_NEW_KEY = 0, /**< new key. */
    BCMOLT_ONU_KEY_EXCHANGE_DECRYPT_REQUIRED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_key_exchange_decrypt_required_data_id__begin BCMOLT_ONU_KEY_EXCHANGE_DECRYPT_REQUIRED_DATA_ID__BEGIN
#define bcmolt_onu_key_exchange_decrypt_required_data_id_new_key BCMOLT_ONU_KEY_EXCHANGE_DECRYPT_REQUIRED_DATA_ID_NEW_KEY
#define bcmolt_onu_key_exchange_decrypt_required_data_id__num_of BCMOLT_ONU_KEY_EXCHANGE_DECRYPT_REQUIRED_DATA_ID__NUM_OF
#define bcmolt_onu_key_exchange_decrypt_required_data_id_all_properties 0xFF
#define bcmolt_onu_key_exchange_decrypt_required_data_id_full_mask 0x1

} bcmolt_onu_key_exchange_decrypt_required_data_id;

/** Identifiers for all fields in a 'onu_onu_activation_standby_completed_data'. */
typedef enum
{
    BCMOLT_ONU_ONU_ACTIVATION_STANDBY_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ONU_ACTIVATION_STANDBY_COMPLETED_DATA_ID_RESULT = 0, /**< result. */
    BCMOLT_ONU_ONU_ACTIVATION_STANDBY_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_onu_activation_standby_completed_data_id__begin BCMOLT_ONU_ONU_ACTIVATION_STANDBY_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_onu_activation_standby_completed_data_id_result BCMOLT_ONU_ONU_ACTIVATION_STANDBY_COMPLETED_DATA_ID_RESULT
#define bcmolt_onu_onu_activation_standby_completed_data_id__num_of BCMOLT_ONU_ONU_ACTIVATION_STANDBY_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_onu_activation_standby_completed_data_id_all_properties 0xFF
#define bcmolt_onu_onu_activation_standby_completed_data_id_full_mask 0x1

} bcmolt_onu_onu_activation_standby_completed_data_id;

/** Identifiers for all fields in a 'onu_power_management_state_change_data'. */
typedef enum
{
    BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID_OLD_STATE = 0, /**< Old State. */
    BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID_NEW_STATE = 1, /**< New State. */
    BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID_REASON = 2, /**< Reason. */
    BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_power_management_state_change_data_id__begin BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID__BEGIN
#define bcmolt_onu_power_management_state_change_data_id_old_state BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID_OLD_STATE
#define bcmolt_onu_power_management_state_change_data_id_new_state BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID_NEW_STATE
#define bcmolt_onu_power_management_state_change_data_id_reason BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID_REASON
#define bcmolt_onu_power_management_state_change_data_id__num_of BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID__NUM_OF
#define bcmolt_onu_power_management_state_change_data_id_all_properties 0xFF
#define bcmolt_onu_power_management_state_change_data_id_full_mask 0x7

} bcmolt_onu_power_management_state_change_data_id;

/** Identifiers for all fields in a 'onu_possible_drift_data'. */
typedef enum
{
    BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID_ALARM_STATUS = 0, /**< Alarm Status. */
    BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID_ESTIMATED_DRIFT = 1, /**< Estimated Drift. */
    BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_possible_drift_data_id__begin BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID__BEGIN
#define bcmolt_onu_possible_drift_data_id_alarm_status BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID_ALARM_STATUS
#define bcmolt_onu_possible_drift_data_id_estimated_drift BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID_ESTIMATED_DRIFT
#define bcmolt_onu_possible_drift_data_id__num_of BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID__NUM_OF
#define bcmolt_onu_possible_drift_data_id_all_properties 0xFF
#define bcmolt_onu_possible_drift_data_id_full_mask 0x3

} bcmolt_onu_possible_drift_data_id;

/** Identifiers for all fields in a 'onu_registration_id_data'. */
typedef enum
{
    BCMOLT_ONU_REGISTRATION_ID_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_REGISTRATION_ID_DATA_ID_REGISTRATION_ID = 0, /**< Registration ID. */
    BCMOLT_ONU_REGISTRATION_ID_DATA_ID_REQUEST_REGISTRATION_STATUS = 1, /**< request registration status. */
    BCMOLT_ONU_REGISTRATION_ID_DATA_ID_REQUEST_REGISTRATION_FAIL_REASON = 2, /**< request registration fail reason. */
    BCMOLT_ONU_REGISTRATION_ID_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_registration_id_data_id__begin BCMOLT_ONU_REGISTRATION_ID_DATA_ID__BEGIN
#define bcmolt_onu_registration_id_data_id_registration_id BCMOLT_ONU_REGISTRATION_ID_DATA_ID_REGISTRATION_ID
#define bcmolt_onu_registration_id_data_id_request_registration_status BCMOLT_ONU_REGISTRATION_ID_DATA_ID_REQUEST_REGISTRATION_STATUS
#define bcmolt_onu_registration_id_data_id_request_registration_fail_reason BCMOLT_ONU_REGISTRATION_ID_DATA_ID_REQUEST_REGISTRATION_FAIL_REASON
#define bcmolt_onu_registration_id_data_id__num_of BCMOLT_ONU_REGISTRATION_ID_DATA_ID__NUM_OF
#define bcmolt_onu_registration_id_data_id_all_properties 0xFF
#define bcmolt_onu_registration_id_data_id_full_mask 0x7

} bcmolt_onu_registration_id_data_id;

/** Identifiers for all fields in a 'onu_power_level_report_data'. */
typedef enum
{
    BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID_ATTENUATION = 0, /**< Attenuation. */
    BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID_POWER_LEVELLING_CAPABILITY = 1, /**< Power levelling capability. */
    BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_power_level_report_data_id__begin BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID__BEGIN
#define bcmolt_onu_power_level_report_data_id_attenuation BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID_ATTENUATION
#define bcmolt_onu_power_level_report_data_id_power_levelling_capability BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID_POWER_LEVELLING_CAPABILITY
#define bcmolt_onu_power_level_report_data_id__num_of BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID__NUM_OF
#define bcmolt_onu_power_level_report_data_id_all_properties 0xFF
#define bcmolt_onu_power_level_report_data_id_full_mask 0x3

} bcmolt_onu_power_level_report_data_id;

/** Identifiers for all fields in a 'onu_power_consumption_report_data'. */
typedef enum
{
    BCMOLT_ONU_POWER_CONSUMPTION_REPORT_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_POWER_CONSUMPTION_REPORT_DATA_ID_POWER_CONSUMPTION_REPORT = 0, /**< power consumption report. */
    BCMOLT_ONU_POWER_CONSUMPTION_REPORT_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_power_consumption_report_data_id__begin BCMOLT_ONU_POWER_CONSUMPTION_REPORT_DATA_ID__BEGIN
#define bcmolt_onu_power_consumption_report_data_id_power_consumption_report BCMOLT_ONU_POWER_CONSUMPTION_REPORT_DATA_ID_POWER_CONSUMPTION_REPORT
#define bcmolt_onu_power_consumption_report_data_id__num_of BCMOLT_ONU_POWER_CONSUMPTION_REPORT_DATA_ID__NUM_OF
#define bcmolt_onu_power_consumption_report_data_id_all_properties 0xFF
#define bcmolt_onu_power_consumption_report_data_id_full_mask 0x1

} bcmolt_onu_power_consumption_report_data_id;

/** Identifiers for all fields in a 'onu_secure_mutual_authentication_failure_data'. */
typedef enum
{
    BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID_STATUS = 0, /**< status. */
    BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID_FAIL_REASON = 1, /**< secure mutual authentication fail reason. */
    BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_secure_mutual_authentication_failure_data_id__begin BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID__BEGIN
#define bcmolt_onu_secure_mutual_authentication_failure_data_id_status BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID_STATUS
#define bcmolt_onu_secure_mutual_authentication_failure_data_id_fail_reason BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID_FAIL_REASON
#define bcmolt_onu_secure_mutual_authentication_failure_data_id__num_of BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID__NUM_OF
#define bcmolt_onu_secure_mutual_authentication_failure_data_id_all_properties 0xFF
#define bcmolt_onu_secure_mutual_authentication_failure_data_id_full_mask 0x3

} bcmolt_onu_secure_mutual_authentication_failure_data_id;

/** Identifiers for all fields in a 'onu_onu_tuning_out_completed_data'. */
typedef enum
{
    BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID_RESULT = 0, /**< result. */
    BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_onu_tuning_out_completed_data_id__begin BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_onu_tuning_out_completed_data_id_result BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID_RESULT
#define bcmolt_onu_onu_tuning_out_completed_data_id_fail_reason BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID_FAIL_REASON
#define bcmolt_onu_onu_tuning_out_completed_data_id__num_of BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_onu_tuning_out_completed_data_id_all_properties 0xFF
#define bcmolt_onu_onu_tuning_out_completed_data_id_full_mask 0x3

} bcmolt_onu_onu_tuning_out_completed_data_id;

/** Identifiers for all fields in a 'onu_onu_tuning_in_completed_data'. */
typedef enum
{
    BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID_RESULT = 0, /**< result. */
    BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID_FAIL_REASON = 1, /**< fail reason. */
    BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_onu_tuning_in_completed_data_id__begin BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID__BEGIN
#define bcmolt_onu_onu_tuning_in_completed_data_id_result BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID_RESULT
#define bcmolt_onu_onu_tuning_in_completed_data_id_fail_reason BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID_FAIL_REASON
#define bcmolt_onu_onu_tuning_in_completed_data_id__num_of BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_onu_onu_tuning_in_completed_data_id_all_properties 0xFF
#define bcmolt_onu_onu_tuning_in_completed_data_id_full_mask 0x3

} bcmolt_onu_onu_tuning_in_completed_data_id;

/** Identifiers for all fields in a 'onu_tuning_response_data'. */
typedef enum
{
    BCMOLT_ONU_TUNING_RESPONSE_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_TUNING_RESPONSE_DATA_ID_ACK = 0, /**< ack. */
    BCMOLT_ONU_TUNING_RESPONSE_DATA_ID_RESULT = 1, /**< result. */
    BCMOLT_ONU_TUNING_RESPONSE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_tuning_response_data_id__begin BCMOLT_ONU_TUNING_RESPONSE_DATA_ID__BEGIN
#define bcmolt_onu_tuning_response_data_id_ack BCMOLT_ONU_TUNING_RESPONSE_DATA_ID_ACK
#define bcmolt_onu_tuning_response_data_id_result BCMOLT_ONU_TUNING_RESPONSE_DATA_ID_RESULT
#define bcmolt_onu_tuning_response_data_id__num_of BCMOLT_ONU_TUNING_RESPONSE_DATA_ID__NUM_OF
#define bcmolt_onu_tuning_response_data_id_all_properties 0xFF
#define bcmolt_onu_tuning_response_data_id_full_mask 0x3

} bcmolt_onu_tuning_response_data_id;

/** Identifiers for all fields in a 'onu_ploam_packet_data'. */
typedef enum
{
    BCMOLT_ONU_PLOAM_PACKET_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_PLOAM_PACKET_DATA_ID_DEFAULT_KEY = 0, /**< default key. */
    BCMOLT_ONU_PLOAM_PACKET_DATA_ID_PLOAM = 1, /**< ploam. */
    BCMOLT_ONU_PLOAM_PACKET_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_ploam_packet_data_id__begin BCMOLT_ONU_PLOAM_PACKET_DATA_ID__BEGIN
#define bcmolt_onu_ploam_packet_data_id_default_key BCMOLT_ONU_PLOAM_PACKET_DATA_ID_DEFAULT_KEY
#define bcmolt_onu_ploam_packet_data_id_ploam BCMOLT_ONU_PLOAM_PACKET_DATA_ID_PLOAM
#define bcmolt_onu_ploam_packet_data_id__num_of BCMOLT_ONU_PLOAM_PACKET_DATA_ID__NUM_OF
#define bcmolt_onu_ploam_packet_data_id_all_properties 0xFF
#define bcmolt_onu_ploam_packet_data_id_full_mask 0x3

} bcmolt_onu_ploam_packet_data_id;

/** Identifiers for all fields in a 'onu_cpu_packets_data'. */
typedef enum
{
    BCMOLT_ONU_CPU_PACKETS_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_CPU_PACKETS_DATA_ID_PACKET_TYPE = 0, /**< packet type. */
    BCMOLT_ONU_CPU_PACKETS_DATA_ID_CALC_CRC = 1, /**< calc crc. */
    BCMOLT_ONU_CPU_PACKETS_DATA_ID_NUMBER_OF_PACKETS = 2, /**< number of packets. */
    BCMOLT_ONU_CPU_PACKETS_DATA_ID_PACKET_SIZE = 3, /**< Single packet size. */
    BCMOLT_ONU_CPU_PACKETS_DATA_ID_BUFFER = 4, /**< buffer. */
    BCMOLT_ONU_CPU_PACKETS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_cpu_packets_data_id__begin BCMOLT_ONU_CPU_PACKETS_DATA_ID__BEGIN
#define bcmolt_onu_cpu_packets_data_id_packet_type BCMOLT_ONU_CPU_PACKETS_DATA_ID_PACKET_TYPE
#define bcmolt_onu_cpu_packets_data_id_calc_crc BCMOLT_ONU_CPU_PACKETS_DATA_ID_CALC_CRC
#define bcmolt_onu_cpu_packets_data_id_number_of_packets BCMOLT_ONU_CPU_PACKETS_DATA_ID_NUMBER_OF_PACKETS
#define bcmolt_onu_cpu_packets_data_id_packet_size BCMOLT_ONU_CPU_PACKETS_DATA_ID_PACKET_SIZE
#define bcmolt_onu_cpu_packets_data_id_buffer BCMOLT_ONU_CPU_PACKETS_DATA_ID_BUFFER
#define bcmolt_onu_cpu_packets_data_id__num_of BCMOLT_ONU_CPU_PACKETS_DATA_ID__NUM_OF
#define bcmolt_onu_cpu_packets_data_id_all_properties 0xFF
#define bcmolt_onu_cpu_packets_data_id_full_mask 0x1F

} bcmolt_onu_cpu_packets_data_id;

/** Identifiers for all fields in a 'onu_cpu_packet_data'. */
typedef enum
{
    BCMOLT_ONU_CPU_PACKET_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_CPU_PACKET_DATA_ID_PORT_ID = 0, /**< port id. */
    BCMOLT_ONU_CPU_PACKET_DATA_ID_CRC_OK = 1, /**< crc ok. */
    BCMOLT_ONU_CPU_PACKET_DATA_ID_PACKET_SIZE = 2, /**< packet size. */
    BCMOLT_ONU_CPU_PACKET_DATA_ID_BUFFER = 3, /**< buffer. */
    BCMOLT_ONU_CPU_PACKET_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_cpu_packet_data_id__begin BCMOLT_ONU_CPU_PACKET_DATA_ID__BEGIN
#define bcmolt_onu_cpu_packet_data_id_port_id BCMOLT_ONU_CPU_PACKET_DATA_ID_PORT_ID
#define bcmolt_onu_cpu_packet_data_id_crc_ok BCMOLT_ONU_CPU_PACKET_DATA_ID_CRC_OK
#define bcmolt_onu_cpu_packet_data_id_packet_size BCMOLT_ONU_CPU_PACKET_DATA_ID_PACKET_SIZE
#define bcmolt_onu_cpu_packet_data_id_buffer BCMOLT_ONU_CPU_PACKET_DATA_ID_BUFFER
#define bcmolt_onu_cpu_packet_data_id__num_of BCMOLT_ONU_CPU_PACKET_DATA_ID__NUM_OF
#define bcmolt_onu_cpu_packet_data_id_all_properties 0xFF
#define bcmolt_onu_cpu_packet_data_id_full_mask 0xF

} bcmolt_onu_cpu_packet_data_id;

/** Identifiers for all fields in a 'onu_omci_packet_data'. */
typedef enum
{
    BCMOLT_ONU_OMCI_PACKET_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_OMCI_PACKET_DATA_ID_PORT_ID = 0, /**< port id. */
    BCMOLT_ONU_OMCI_PACKET_DATA_ID_CRC_OK = 1, /**< crc ok. */
    BCMOLT_ONU_OMCI_PACKET_DATA_ID_PACKET_SIZE = 2, /**< packet size. */
    BCMOLT_ONU_OMCI_PACKET_DATA_ID_BUFFER = 3, /**< buffer. */
    BCMOLT_ONU_OMCI_PACKET_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_omci_packet_data_id__begin BCMOLT_ONU_OMCI_PACKET_DATA_ID__BEGIN
#define bcmolt_onu_omci_packet_data_id_port_id BCMOLT_ONU_OMCI_PACKET_DATA_ID_PORT_ID
#define bcmolt_onu_omci_packet_data_id_crc_ok BCMOLT_ONU_OMCI_PACKET_DATA_ID_CRC_OK
#define bcmolt_onu_omci_packet_data_id_packet_size BCMOLT_ONU_OMCI_PACKET_DATA_ID_PACKET_SIZE
#define bcmolt_onu_omci_packet_data_id_buffer BCMOLT_ONU_OMCI_PACKET_DATA_ID_BUFFER
#define bcmolt_onu_omci_packet_data_id__num_of BCMOLT_ONU_OMCI_PACKET_DATA_ID__NUM_OF
#define bcmolt_onu_omci_packet_data_id_all_properties 0xFF
#define bcmolt_onu_omci_packet_data_id_full_mask 0xF

} bcmolt_onu_omci_packet_data_id;

/** Identifiers for all fields in a 'onu_rei_data'. */
typedef enum
{
    BCMOLT_ONU_REI_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_REI_DATA_ID_BIP8_ERRORS = 0, /**< BIP8 errors. */
    BCMOLT_ONU_REI_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_rei_data_id__begin BCMOLT_ONU_REI_DATA_ID__BEGIN
#define bcmolt_onu_rei_data_id_bip8_errors BCMOLT_ONU_REI_DATA_ID_BIP8_ERRORS
#define bcmolt_onu_rei_data_id__num_of BCMOLT_ONU_REI_DATA_ID__NUM_OF
#define bcmolt_onu_rei_data_id_all_properties 0xFF
#define bcmolt_onu_rei_data_id_full_mask 0x1

} bcmolt_onu_rei_data_id;

/** Identifiers for all fields in a 'onu_state_change_data'. */
typedef enum
{
    BCMOLT_ONU_STATE_CHANGE_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_STATE_CHANGE_DATA_ID_NEW_ONU_STATE = 0, /**< New ONU state. */
    BCMOLT_ONU_STATE_CHANGE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_state_change_data_id__begin BCMOLT_ONU_STATE_CHANGE_DATA_ID__BEGIN
#define bcmolt_onu_state_change_data_id_new_onu_state BCMOLT_ONU_STATE_CHANGE_DATA_ID_NEW_ONU_STATE
#define bcmolt_onu_state_change_data_id__num_of BCMOLT_ONU_STATE_CHANGE_DATA_ID__NUM_OF
#define bcmolt_onu_state_change_data_id_all_properties 0xFF
#define bcmolt_onu_state_change_data_id_full_mask 0x1

} bcmolt_onu_state_change_data_id;

/** Identifiers for all fields in a 'onu_range_value_changed_data'. */
typedef enum
{
    BCMOLT_ONU_RANGE_VALUE_CHANGED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_RANGE_VALUE_CHANGED_DATA_ID_RANGE_VALUE_TQ = 0, /**< Range value in time quanta. */
    BCMOLT_ONU_RANGE_VALUE_CHANGED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_range_value_changed_data_id__begin BCMOLT_ONU_RANGE_VALUE_CHANGED_DATA_ID__BEGIN
#define bcmolt_onu_range_value_changed_data_id_range_value_tq BCMOLT_ONU_RANGE_VALUE_CHANGED_DATA_ID_RANGE_VALUE_TQ
#define bcmolt_onu_range_value_changed_data_id__num_of BCMOLT_ONU_RANGE_VALUE_CHANGED_DATA_ID__NUM_OF
#define bcmolt_onu_range_value_changed_data_id_all_properties 0xFF
#define bcmolt_onu_range_value_changed_data_id_full_mask 0x1

} bcmolt_onu_range_value_changed_data_id;

/** Identifiers for all fields in a 'onu_xpon_unknown_ploam_data'. */
typedef enum
{
    BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_ID_PLOAM_BUFFER = 0, /**< PLOAM buffer. */
    BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_xpon_unknown_ploam_data_id__begin BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_ID__BEGIN
#define bcmolt_onu_xpon_unknown_ploam_data_id_ploam_buffer BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_ID_PLOAM_BUFFER
#define bcmolt_onu_xpon_unknown_ploam_data_id__num_of BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_ID__NUM_OF
#define bcmolt_onu_xpon_unknown_ploam_data_id_all_properties 0xFF
#define bcmolt_onu_xpon_unknown_ploam_data_id_full_mask 0x1

} bcmolt_onu_xpon_unknown_ploam_data_id;

/** Identifiers for all fields in a 'onu_trap_ploam_received_data'. */
typedef enum
{
    BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID_MESSAGE_ID = 0, /**< message id. */
    BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID_ONU_ID = 1, /**< onu_id. */
    BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID_DATA = 2, /**< data. */
    BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_trap_ploam_received_data_id__begin BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID__BEGIN
#define bcmolt_onu_trap_ploam_received_data_id_message_id BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID_MESSAGE_ID
#define bcmolt_onu_trap_ploam_received_data_id_onu_id BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID_ONU_ID
#define bcmolt_onu_trap_ploam_received_data_id_data BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID_DATA
#define bcmolt_onu_trap_ploam_received_data_id__num_of BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID__NUM_OF
#define bcmolt_onu_trap_ploam_received_data_id_all_properties 0xFF
#define bcmolt_onu_trap_ploam_received_data_id_full_mask 0x7

} bcmolt_onu_trap_ploam_received_data_id;

/** Identifiers for all fields in a 'onu_itu_pon_stats_cfg_data'. */
typedef enum
{
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_POSITIVE_DRIFT = 0, /**< positive drift. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_NEGATIVE_DRIFT = 1, /**< negative drift. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_DELIMITER_MISS_DETECTION = 2, /**< delimiter miss detection. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_BIP_ERRORS = 3, /**< bip errors. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_BIP_UNITS = 4, /**< Received units (In GPON units are bits, in other system modes units are Bytes) protected by BIP. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CORRECTED_SYMBOLS = 5, /**< fec corrected symbols  (Not relevant in GPON system modes). */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS_CORRECTED = 6, /**< fec corrected codewords. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS_UNCORRECTABLE = 7, /**< fec uncorrectable codewords. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS = 8, /**< fec total codewords. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CORRECTED_UNITS = 9, /**< fec corrected units (In GPON units are bits in other system modes, units are Bytes). */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_XGEM_KEY_ERRORS = 10, /**< xgem key error. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_XGEM_LOSS = 11, /**< xgem loss. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_ERROR = 12, /**< mic error ploam. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_NON_IDLE = 13, /**< non idle ploam. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI = 14, /**< Received OMCI packets. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR = 15, /**< Received OMCI packets with CRC errors. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_BYTES = 16, /**< rx bytes. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_PACKETS = 17, /**< rx packets. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_TX_BYTES = 18, /**< tx bytes. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_TX_PACKETS = 19, /**< tx packets. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_BER_REPORTED = 20, /**< ber reported. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_LCDG_ERRORS = 21, /**< LCDG errors. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RDI_ERRORS = 22, /**< RDI errors. */
    BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_itu_pon_stats_cfg_data_id__begin BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_onu_itu_pon_stats_cfg_data_id_positive_drift BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_POSITIVE_DRIFT
#define bcmolt_onu_itu_pon_stats_cfg_data_id_negative_drift BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_NEGATIVE_DRIFT
#define bcmolt_onu_itu_pon_stats_cfg_data_id_delimiter_miss_detection BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_DELIMITER_MISS_DETECTION
#define bcmolt_onu_itu_pon_stats_cfg_data_id_bip_errors BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_BIP_ERRORS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_bip_units BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_BIP_UNITS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_fec_corrected_symbols BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CORRECTED_SYMBOLS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_fec_codewords_corrected BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS_CORRECTED
#define bcmolt_onu_itu_pon_stats_cfg_data_id_fec_codewords_uncorrectable BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS_UNCORRECTABLE
#define bcmolt_onu_itu_pon_stats_cfg_data_id_fec_codewords BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_fec_corrected_units BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CORRECTED_UNITS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_xgem_key_errors BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_XGEM_KEY_ERRORS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_xgem_loss BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_XGEM_LOSS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_rx_ploams_error BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_ERROR
#define bcmolt_onu_itu_pon_stats_cfg_data_id_rx_ploams_non_idle BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_NON_IDLE
#define bcmolt_onu_itu_pon_stats_cfg_data_id_rx_omci BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI
#define bcmolt_onu_itu_pon_stats_cfg_data_id_rx_omci_packets_crc_error BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR
#define bcmolt_onu_itu_pon_stats_cfg_data_id_rx_bytes BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_BYTES
#define bcmolt_onu_itu_pon_stats_cfg_data_id_rx_packets BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_PACKETS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_tx_bytes BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_TX_BYTES
#define bcmolt_onu_itu_pon_stats_cfg_data_id_tx_packets BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_TX_PACKETS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_ber_reported BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_BER_REPORTED
#define bcmolt_onu_itu_pon_stats_cfg_data_id_lcdg_errors BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_LCDG_ERRORS
#define bcmolt_onu_itu_pon_stats_cfg_data_id_rdi_errors BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RDI_ERRORS
#define bcmolt_onu_itu_pon_stats_cfg_data_id__num_of BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_onu_itu_pon_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_onu_itu_pon_stats_cfg_data_id_full_mask 0x7FFFFF

} bcmolt_onu_itu_pon_stats_cfg_data_id;

/** Identifiers for all fields in a 'onu_itu_pon_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_ONU_ITU_PON_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ITU_PON_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ONU_ITU_PON_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_itu_pon_stats_alarm_raised_data_id__begin BCMOLT_ONU_ITU_PON_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_onu_itu_pon_stats_alarm_raised_data_id_stat BCMOLT_ONU_ITU_PON_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_onu_itu_pon_stats_alarm_raised_data_id__num_of BCMOLT_ONU_ITU_PON_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_onu_itu_pon_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_onu_itu_pon_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_onu_itu_pon_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'onu_itu_pon_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_ONU_ITU_PON_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_ITU_PON_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_ONU_ITU_PON_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_itu_pon_stats_alarm_cleared_data_id__begin BCMOLT_ONU_ITU_PON_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_onu_itu_pon_stats_alarm_cleared_data_id_stat BCMOLT_ONU_ITU_PON_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_onu_itu_pon_stats_alarm_cleared_data_id__num_of BCMOLT_ONU_ITU_PON_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_onu_itu_pon_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_onu_itu_pon_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_onu_itu_pon_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'onu_auto_cfg_data'. */
typedef enum
{
    BCMOLT_ONU_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_ONU_AUTO_CFG_DATA_ID_BER_INTERVAL_CONFIGURATION_COMPLETED = 0, /**< BER Interval Configuration Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_CPU_PACKET = 1, /**< XGPON CPU packet. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_DFI = 2, /**< Receive Dying-Gasp of ONUi. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_DGI = 3, /**< Receive Dying-Gasp of ONUi. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_DOWI = 4, /**< Drift of Window of ONUi. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ERR = 5, /**< ERR. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_GPON_ALARM = 6, /**< GPON ONU Alarm. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_INVALID_DBRU_REPORT = 7, /**< Invalid DBRu Report. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_CLEARED = 8, /**< ITU PON Statistics Alarm Cleared. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_RAISED = 9, /**< ITU PON Statistics Alarm Raised. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_COMPLETED = 10, /**< Key Exchange Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_CYCLE_SKIPPED = 11, /**< Key Exchange Cycle Skipped. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_DECRYPT_REQUIRED = 12, /**< Key Exchange Decrypt Required. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_KEY_MISMATCH = 13, /**< Key Exchange Key Mismatch. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_KEY_REQUEST_TIMEOUT = 14, /**< Key Exchange Key Request Timeout. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_UNCONSECUTIVE_INDEX = 15, /**< Key Exchange Unconsecutive Index. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_LOAI = 16, /**< LOAi. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_LOKI = 17, /**< LOki. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_LOOCI = 18, /**< LOOCi. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_MEMI = 19, /**< MEMi. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_OMCI_PACKET = 20, /**< XGPON OMCI packet. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_OMCI_PORT_ID_CONFIGURATION_COMPLETED = 21, /**< OMCI PORT ID Configuration Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_ACTIVATION_COMPLETED = 22, /**< ONU Activation Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_ACTIVATION_STANDBY_COMPLETED = 23, /**< onu activation standby completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_DEACTIVATION_COMPLETED = 24, /**< ONU Deactivation Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_DISABLE_COMPLETED = 25, /**< ONU Disable Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_ENABLE_COMPLETED = 26, /**< ONU Enable Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_READY_FOR_DATA_GRANT = 27, /**< ONU is ready to be granted data accesses. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_TUNING_IN_COMPLETED = 28, /**< ONU Tuning in completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_TUNING_OUT_COMPLETED = 29, /**< ONU Tuning out completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_OPTICAL_REFLECTION = 30, /**< Optical Reflection. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_PASSWORD_AUTHENTICATION_COMPLETED = 31, /**< Password Authentication Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_PEE = 32, /**< PEE. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_POSSIBLE_DRIFT = 33, /**< Possible Drift. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_POWER_CONSUMPTION_REPORT = 34, /**< Power consumption report. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_POWER_LEVEL_REPORT = 35, /**< Power level report. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_POWER_MANAGEMENT_STATE_CHANGE = 36, /**< Power Management State Change. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_PQSI = 37, /**< ploam queue status. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_PST = 38, /**< PST. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_RANGE_VALUE_CHANGED = 39, /**< Range Value Changed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_RANGING_COMPLETED = 40, /**< Ranging Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_REGISTRATION_ID = 41, /**< Registration ID. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_REI = 42, /**< REI. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_RSSI_MEASUREMENT_COMPLETED = 43, /**< RSSI Measurement Completed. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_SDI = 44, /**< Signal Degraded of ONUi. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_SECURE_MUTUAL_AUTHENTICATION_FAILURE = 45, /**< secure mutual authentication failure. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_SFI = 46, /**< Signal Fail of ONUi. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_STATE_CHANGE = 47, /**< State Change. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_SUFI = 48, /**< SUFi. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_TIWI = 49, /**< Transmission Interference Warning. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_TRAP_PLOAM_RECEIVED = 50, /**< trap ploam received. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_TUNING_RESPONSE = 51, /**< Tuning response. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_XGPON_ALARM = 52, /**< XGPON ONU Alarm. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID_XPON_UNKNOWN_PLOAM = 53, /**< XPON Unknown ploam. */
    BCMOLT_ONU_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_onu_auto_cfg_data_id__begin BCMOLT_ONU_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_onu_auto_cfg_data_id_ber_interval_configuration_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_BER_INTERVAL_CONFIGURATION_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_cpu_packet BCMOLT_ONU_AUTO_CFG_DATA_ID_CPU_PACKET
#define bcmolt_onu_auto_cfg_data_id_dfi BCMOLT_ONU_AUTO_CFG_DATA_ID_DFI
#define bcmolt_onu_auto_cfg_data_id_dgi BCMOLT_ONU_AUTO_CFG_DATA_ID_DGI
#define bcmolt_onu_auto_cfg_data_id_dowi BCMOLT_ONU_AUTO_CFG_DATA_ID_DOWI
#define bcmolt_onu_auto_cfg_data_id_err BCMOLT_ONU_AUTO_CFG_DATA_ID_ERR
#define bcmolt_onu_auto_cfg_data_id_gpon_alarm BCMOLT_ONU_AUTO_CFG_DATA_ID_GPON_ALARM
#define bcmolt_onu_auto_cfg_data_id_invalid_dbru_report BCMOLT_ONU_AUTO_CFG_DATA_ID_INVALID_DBRU_REPORT
#define bcmolt_onu_auto_cfg_data_id_itu_pon_stats_alarm_cleared BCMOLT_ONU_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_CLEARED
#define bcmolt_onu_auto_cfg_data_id_itu_pon_stats_alarm_raised BCMOLT_ONU_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_RAISED
#define bcmolt_onu_auto_cfg_data_id_key_exchange_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_key_exchange_cycle_skipped BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_CYCLE_SKIPPED
#define bcmolt_onu_auto_cfg_data_id_key_exchange_decrypt_required BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_DECRYPT_REQUIRED
#define bcmolt_onu_auto_cfg_data_id_key_exchange_key_mismatch BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_KEY_MISMATCH
#define bcmolt_onu_auto_cfg_data_id_key_exchange_key_request_timeout BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_KEY_REQUEST_TIMEOUT
#define bcmolt_onu_auto_cfg_data_id_key_exchange_unconsecutive_index BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_UNCONSECUTIVE_INDEX
#define bcmolt_onu_auto_cfg_data_id_loai BCMOLT_ONU_AUTO_CFG_DATA_ID_LOAI
#define bcmolt_onu_auto_cfg_data_id_loki BCMOLT_ONU_AUTO_CFG_DATA_ID_LOKI
#define bcmolt_onu_auto_cfg_data_id_looci BCMOLT_ONU_AUTO_CFG_DATA_ID_LOOCI
#define bcmolt_onu_auto_cfg_data_id_memi BCMOLT_ONU_AUTO_CFG_DATA_ID_MEMI
#define bcmolt_onu_auto_cfg_data_id_omci_packet BCMOLT_ONU_AUTO_CFG_DATA_ID_OMCI_PACKET
#define bcmolt_onu_auto_cfg_data_id_omci_port_id_configuration_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_OMCI_PORT_ID_CONFIGURATION_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_onu_activation_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_ACTIVATION_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_onu_activation_standby_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_ACTIVATION_STANDBY_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_onu_deactivation_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_DEACTIVATION_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_onu_disable_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_DISABLE_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_onu_enable_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_ENABLE_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_onu_ready_for_data_grant BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_READY_FOR_DATA_GRANT
#define bcmolt_onu_auto_cfg_data_id_onu_tuning_in_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_TUNING_IN_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_onu_tuning_out_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_TUNING_OUT_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_optical_reflection BCMOLT_ONU_AUTO_CFG_DATA_ID_OPTICAL_REFLECTION
#define bcmolt_onu_auto_cfg_data_id_password_authentication_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_PASSWORD_AUTHENTICATION_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_pee BCMOLT_ONU_AUTO_CFG_DATA_ID_PEE
#define bcmolt_onu_auto_cfg_data_id_possible_drift BCMOLT_ONU_AUTO_CFG_DATA_ID_POSSIBLE_DRIFT
#define bcmolt_onu_auto_cfg_data_id_power_consumption_report BCMOLT_ONU_AUTO_CFG_DATA_ID_POWER_CONSUMPTION_REPORT
#define bcmolt_onu_auto_cfg_data_id_power_level_report BCMOLT_ONU_AUTO_CFG_DATA_ID_POWER_LEVEL_REPORT
#define bcmolt_onu_auto_cfg_data_id_power_management_state_change BCMOLT_ONU_AUTO_CFG_DATA_ID_POWER_MANAGEMENT_STATE_CHANGE
#define bcmolt_onu_auto_cfg_data_id_pqsi BCMOLT_ONU_AUTO_CFG_DATA_ID_PQSI
#define bcmolt_onu_auto_cfg_data_id_pst BCMOLT_ONU_AUTO_CFG_DATA_ID_PST
#define bcmolt_onu_auto_cfg_data_id_range_value_changed BCMOLT_ONU_AUTO_CFG_DATA_ID_RANGE_VALUE_CHANGED
#define bcmolt_onu_auto_cfg_data_id_ranging_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_RANGING_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_registration_id BCMOLT_ONU_AUTO_CFG_DATA_ID_REGISTRATION_ID
#define bcmolt_onu_auto_cfg_data_id_rei BCMOLT_ONU_AUTO_CFG_DATA_ID_REI
#define bcmolt_onu_auto_cfg_data_id_rssi_measurement_completed BCMOLT_ONU_AUTO_CFG_DATA_ID_RSSI_MEASUREMENT_COMPLETED
#define bcmolt_onu_auto_cfg_data_id_sdi BCMOLT_ONU_AUTO_CFG_DATA_ID_SDI
#define bcmolt_onu_auto_cfg_data_id_secure_mutual_authentication_failure BCMOLT_ONU_AUTO_CFG_DATA_ID_SECURE_MUTUAL_AUTHENTICATION_FAILURE
#define bcmolt_onu_auto_cfg_data_id_sfi BCMOLT_ONU_AUTO_CFG_DATA_ID_SFI
#define bcmolt_onu_auto_cfg_data_id_state_change BCMOLT_ONU_AUTO_CFG_DATA_ID_STATE_CHANGE
#define bcmolt_onu_auto_cfg_data_id_sufi BCMOLT_ONU_AUTO_CFG_DATA_ID_SUFI
#define bcmolt_onu_auto_cfg_data_id_tiwi BCMOLT_ONU_AUTO_CFG_DATA_ID_TIWI
#define bcmolt_onu_auto_cfg_data_id_trap_ploam_received BCMOLT_ONU_AUTO_CFG_DATA_ID_TRAP_PLOAM_RECEIVED
#define bcmolt_onu_auto_cfg_data_id_tuning_response BCMOLT_ONU_AUTO_CFG_DATA_ID_TUNING_RESPONSE
#define bcmolt_onu_auto_cfg_data_id_xgpon_alarm BCMOLT_ONU_AUTO_CFG_DATA_ID_XGPON_ALARM
#define bcmolt_onu_auto_cfg_data_id_xpon_unknown_ploam BCMOLT_ONU_AUTO_CFG_DATA_ID_XPON_UNKNOWN_PLOAM
#define bcmolt_onu_auto_cfg_data_id__num_of BCMOLT_ONU_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_onu_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_onu_auto_cfg_data_id_full_mask 0x3FFFFFFFFFFFFF

} bcmolt_onu_auto_cfg_data_id;

/** Identifiers for all fields in a 'pbit_to_tc_key'. */
typedef enum
{
    BCMOLT_PBIT_TO_TC_KEY_ID__BEGIN = 0,
    BCMOLT_PBIT_TO_TC_KEY_ID_ID = 0, /**< id. */
    BCMOLT_PBIT_TO_TC_KEY_ID_DIR = 1, /**< dir. */
    BCMOLT_PBIT_TO_TC_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pbit_to_tc_key_id__begin BCMOLT_PBIT_TO_TC_KEY_ID__BEGIN
#define bcmolt_pbit_to_tc_key_id_id BCMOLT_PBIT_TO_TC_KEY_ID_ID
#define bcmolt_pbit_to_tc_key_id_dir BCMOLT_PBIT_TO_TC_KEY_ID_DIR
#define bcmolt_pbit_to_tc_key_id__num_of BCMOLT_PBIT_TO_TC_KEY_ID__NUM_OF
#define bcmolt_pbit_to_tc_key_id_all_properties 0xFF
#define bcmolt_pbit_to_tc_key_id_full_mask 0x3

} bcmolt_pbit_to_tc_key_id;

/** Identifiers for all fields in a 'pbit_to_tc_cfg_data'. */
typedef enum
{
    BCMOLT_PBIT_TO_TC_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_PBIT_TO_TC_CFG_DATA_ID_TC = 0, /**< tc. */
    BCMOLT_PBIT_TO_TC_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pbit_to_tc_cfg_data_id__begin BCMOLT_PBIT_TO_TC_CFG_DATA_ID__BEGIN
#define bcmolt_pbit_to_tc_cfg_data_id_tc BCMOLT_PBIT_TO_TC_CFG_DATA_ID_TC
#define bcmolt_pbit_to_tc_cfg_data_id__num_of BCMOLT_PBIT_TO_TC_CFG_DATA_ID__NUM_OF
#define bcmolt_pbit_to_tc_cfg_data_id_all_properties 0xFF
#define bcmolt_pbit_to_tc_cfg_data_id_full_mask 0x1

} bcmolt_pbit_to_tc_cfg_data_id;

/** Identifiers for all fields in a 'policer_profile_key'. */
typedef enum
{
    BCMOLT_POLICER_PROFILE_KEY_ID__BEGIN = 0,
    BCMOLT_POLICER_PROFILE_KEY_ID_ID = 0, /**< id. */
    BCMOLT_POLICER_PROFILE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_policer_profile_key_id__begin BCMOLT_POLICER_PROFILE_KEY_ID__BEGIN
#define bcmolt_policer_profile_key_id_id BCMOLT_POLICER_PROFILE_KEY_ID_ID
#define bcmolt_policer_profile_key_id__num_of BCMOLT_POLICER_PROFILE_KEY_ID__NUM_OF
#define bcmolt_policer_profile_key_id_all_properties 0xFF
#define bcmolt_policer_profile_key_id_full_mask 0x1

} bcmolt_policer_profile_key_id;

/** Identifiers for all fields in a 'policer_profile_cfg_data'. */
typedef enum
{
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID_STATE = 0, /**< Config State. */
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID_TYPE = 1, /**< type. */
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID_TRAFFIC_TYPE = 3, /**< traffic_type. */
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID_CIR_KBPS = 4, /**< cir kbps. */
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID_EIR_KBPS = 5, /**< eir kbps. */
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID_CBS_KB = 6, /**< cbs kb. */
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID_EBS_KB = 7, /**< ebs kb. */
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID_COLOR_AWARENESS = 8, /**< color awareness. */
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID_COLOR_MARKING = 9, /**< color marking. */
    BCMOLT_POLICER_PROFILE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_policer_profile_cfg_data_id__begin BCMOLT_POLICER_PROFILE_CFG_DATA_ID__BEGIN
#define bcmolt_policer_profile_cfg_data_id_state BCMOLT_POLICER_PROFILE_CFG_DATA_ID_STATE
#define bcmolt_policer_profile_cfg_data_id_type BCMOLT_POLICER_PROFILE_CFG_DATA_ID_TYPE
#define bcmolt_policer_profile_cfg_data_id_traffic_type BCMOLT_POLICER_PROFILE_CFG_DATA_ID_TRAFFIC_TYPE
#define bcmolt_policer_profile_cfg_data_id_cir_kbps BCMOLT_POLICER_PROFILE_CFG_DATA_ID_CIR_KBPS
#define bcmolt_policer_profile_cfg_data_id_eir_kbps BCMOLT_POLICER_PROFILE_CFG_DATA_ID_EIR_KBPS
#define bcmolt_policer_profile_cfg_data_id_cbs_kb BCMOLT_POLICER_PROFILE_CFG_DATA_ID_CBS_KB
#define bcmolt_policer_profile_cfg_data_id_ebs_kb BCMOLT_POLICER_PROFILE_CFG_DATA_ID_EBS_KB
#define bcmolt_policer_profile_cfg_data_id_color_awareness BCMOLT_POLICER_PROFILE_CFG_DATA_ID_COLOR_AWARENESS
#define bcmolt_policer_profile_cfg_data_id_color_marking BCMOLT_POLICER_PROFILE_CFG_DATA_ID_COLOR_MARKING
#define bcmolt_policer_profile_cfg_data_id__num_of BCMOLT_POLICER_PROFILE_CFG_DATA_ID__NUM_OF
#define bcmolt_policer_profile_cfg_data_id_all_properties 0xFF
#define bcmolt_policer_profile_cfg_data_id_full_mask 0x3FB

} bcmolt_policer_profile_cfg_data_id;

/** Identifiers for all fields in a 'pon_interface_key'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_KEY_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_KEY_ID_PON_NI = 0, /**< pon_ni. */
    BCMOLT_PON_INTERFACE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_key_id__begin BCMOLT_PON_INTERFACE_KEY_ID__BEGIN
#define bcmolt_pon_interface_key_id_pon_ni BCMOLT_PON_INTERFACE_KEY_ID_PON_NI
#define bcmolt_pon_interface_key_id__num_of BCMOLT_PON_INTERFACE_KEY_ID__NUM_OF
#define bcmolt_pon_interface_key_id_all_properties 0xFF
#define bcmolt_pon_interface_key_id_full_mask 0x1

} bcmolt_pon_interface_key_id;

/** Identifiers for all fields in a 'pon_interface_cfg_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_STATE = 0, /**< state. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_PON_TYPE = 1, /**< PON type. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_LOS_STATUS = 2, /**< LOS status. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_LOS_INITIAL_VALUE = 3, /**< los initialization value. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_DISCOVERY = 4, /**< PON service discovery control. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_ITU = 5, /**< ITU PON Attributes. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_PON_DISTANCE = 8, /**< PON distance. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_NUMBER_OF_ACTIVE_ONUS = 9, /**< number of active onus. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_NUMBER_OF_ACTIVE_STANDBY_ONUS = 10, /**< number of active standby onus. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_GPON_TRX = 11, /**< gpon transceiver. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_XGPON_TRX = 12, /**< xgpon transceiver. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_XGS_NGPON2_TRX = 13, /**< xgs_ngpon2 transceiver params. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID_LOS_WAIT_TIMEOUT = 14, /**< los wait timeout. */
    BCMOLT_PON_INTERFACE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_cfg_data_id__begin BCMOLT_PON_INTERFACE_CFG_DATA_ID__BEGIN
#define bcmolt_pon_interface_cfg_data_id_state BCMOLT_PON_INTERFACE_CFG_DATA_ID_STATE
#define bcmolt_pon_interface_cfg_data_id_pon_type BCMOLT_PON_INTERFACE_CFG_DATA_ID_PON_TYPE
#define bcmolt_pon_interface_cfg_data_id_los_status BCMOLT_PON_INTERFACE_CFG_DATA_ID_LOS_STATUS
#define bcmolt_pon_interface_cfg_data_id_los_initial_value BCMOLT_PON_INTERFACE_CFG_DATA_ID_LOS_INITIAL_VALUE
#define bcmolt_pon_interface_cfg_data_id_discovery BCMOLT_PON_INTERFACE_CFG_DATA_ID_DISCOVERY
#define bcmolt_pon_interface_cfg_data_id_itu BCMOLT_PON_INTERFACE_CFG_DATA_ID_ITU
#define bcmolt_pon_interface_cfg_data_id_pon_distance BCMOLT_PON_INTERFACE_CFG_DATA_ID_PON_DISTANCE
#define bcmolt_pon_interface_cfg_data_id_number_of_active_onus BCMOLT_PON_INTERFACE_CFG_DATA_ID_NUMBER_OF_ACTIVE_ONUS
#define bcmolt_pon_interface_cfg_data_id_number_of_active_standby_onus BCMOLT_PON_INTERFACE_CFG_DATA_ID_NUMBER_OF_ACTIVE_STANDBY_ONUS
#define bcmolt_pon_interface_cfg_data_id_gpon_trx BCMOLT_PON_INTERFACE_CFG_DATA_ID_GPON_TRX
#define bcmolt_pon_interface_cfg_data_id_xgpon_trx BCMOLT_PON_INTERFACE_CFG_DATA_ID_XGPON_TRX
#define bcmolt_pon_interface_cfg_data_id_xgs_ngpon2_trx BCMOLT_PON_INTERFACE_CFG_DATA_ID_XGS_NGPON2_TRX
#define bcmolt_pon_interface_cfg_data_id_los_wait_timeout BCMOLT_PON_INTERFACE_CFG_DATA_ID_LOS_WAIT_TIMEOUT
#define bcmolt_pon_interface_cfg_data_id__num_of BCMOLT_PON_INTERFACE_CFG_DATA_ID__NUM_OF
#define bcmolt_pon_interface_cfg_data_id_all_properties 0xFF
#define bcmolt_pon_interface_cfg_data_id_full_mask 0x7F3F

} bcmolt_pon_interface_cfg_data_id;

/** Identifiers for all fields in a 'pon_interface_itu_pon_stats_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS = 0, /**< Receive FEC codewords. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_UNITS = 1, /**< Received units (bits in GPON / bytes in XGPON) protected by bip. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_ERRORS = 2, /**< Received bip errors. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM = 3, /**< Received valid GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_DROPPED = 4, /**< Received dropped GEM ID frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_IDLE = 5, /**< Received idle GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_CORRECTED = 6, /**< Received corrected GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CRC_ERROR = 7, /**< Received packets with CRC error. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_FRAGMENT_ERROR = 8, /**< Received fragment errors. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS_DROPPED = 9, /**< Global dropped packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_SHORT = 10, /**< Received packets dropped due to length too short. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_LONG = 11, /**< Received packet dropped due to length too long. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_KEY_ERROR = 12, /**< Received key errors. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU_OMCI_PACKETS_DROPPED = 13, /**< Received packets dropped due to illegal length. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PLOAMS = 14, /**< Transmitted Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_DROPPED = 15, /**< Received dropped Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_VALID = 16, /**< Received valid allocations. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_INVALID = 17, /**< Received invalid allocations. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_DISABLED = 18, /**< Received disabled allocations. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS = 19, /**< Received Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE = 20, /**< Received non idle Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR = 21, /**< Received error Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU = 22, /**< Received CPU packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI = 23, /**< Received OMCI packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR = 24, /**< Received OMCI packets with CRC errors. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PACKETS = 25, /**< Transmitted packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_GEM = 26, /**< Transmitted GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_CPU = 27, /**< Transmitted CPU packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_OMCI = 28, /**< Transmitted OMCI packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_ILLEGAL_LENGTH = 29, /**< Transmit packets dropped due to illegal length. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TPID_MISS = 30, /**< Transmit packets dropped due to TPID miss. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_VID_MISS = 31, /**< Transmit packets droped due to VID miss. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_HEADERS = 32, /**< Received valid XGTC headers. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_CORRECTED = 33, /**< Received corrected XGTC headers. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_UNCORRECTED = 34, /**< Received uncorrected XGTC headers. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTED = 35, /**< Received uncorrected FEC codewords. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_ILLEGAL = 36, /**< Received illegal GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TOTAL = 37, /**< Total transmit packets droped. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS = 38, /**< Received packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_itu_pon_stats_data_id__begin BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID__BEGIN
#define bcmolt_pon_interface_itu_pon_stats_data_id_fec_codewords BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS
#define bcmolt_pon_interface_itu_pon_stats_data_id_bip_units BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_UNITS
#define bcmolt_pon_interface_itu_pon_stats_data_id_bip_errors BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_ERRORS
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_gem BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_gem_dropped BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_DROPPED
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_gem_idle BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_IDLE
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_gem_corrected BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_CORRECTED
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_crc_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CRC_ERROR
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_fragment_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_FRAGMENT_ERROR
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_packets_dropped BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS_DROPPED
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_dropped_too_short BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_SHORT
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_dropped_too_long BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_LONG
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_key_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_KEY_ERROR
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_cpu_omci_packets_dropped BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU_OMCI_PACKETS_DROPPED
#define bcmolt_pon_interface_itu_pon_stats_data_id_tx_ploams BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PLOAMS
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_ploams_dropped BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_DROPPED
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_allocations_valid BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_VALID
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_allocations_invalid BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_INVALID
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_allocations_disabled BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_DISABLED
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_ploams BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_ploams_non_idle BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_ploams_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_cpu BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_omci BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_omci_packets_crc_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR
#define bcmolt_pon_interface_itu_pon_stats_data_id_tx_packets BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PACKETS
#define bcmolt_pon_interface_itu_pon_stats_data_id_tx_gem BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_GEM
#define bcmolt_pon_interface_itu_pon_stats_data_id_tx_cpu BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_CPU
#define bcmolt_pon_interface_itu_pon_stats_data_id_tx_omci BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_OMCI
#define bcmolt_pon_interface_itu_pon_stats_data_id_tx_dropped_illegal_length BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_ILLEGAL_LENGTH
#define bcmolt_pon_interface_itu_pon_stats_data_id_tx_dropped_tpid_miss BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TPID_MISS
#define bcmolt_pon_interface_itu_pon_stats_data_id_tx_dropped_vid_miss BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_VID_MISS
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_xgtc_headers BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_HEADERS
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_xgtc_corrected BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_CORRECTED
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_xgtc_uncorrected BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_UNCORRECTED
#define bcmolt_pon_interface_itu_pon_stats_data_id_fec_codewords_uncorrected BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTED
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_gem_illegal BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_ILLEGAL
#define bcmolt_pon_interface_itu_pon_stats_data_id_tx_dropped_total BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TOTAL
#define bcmolt_pon_interface_itu_pon_stats_data_id_rx_packets BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS
#define bcmolt_pon_interface_itu_pon_stats_data_id__num_of BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID__NUM_OF
#define bcmolt_pon_interface_itu_pon_stats_data_id_all_properties 0xFF
#define bcmolt_pon_interface_itu_pon_stats_data_id_full_mask 0x7FFFFFFFFF

} bcmolt_pon_interface_itu_pon_stats_data_id;

/** Identifiers for all fields in a 'pon_interface_ae_stats_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BYTES = 0, /**< RX Bytes. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES = 1, /**< RX Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_64 = 2, /**< RX 64 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_65_127 = 3, /**< RX 65-127 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_128_255 = 4, /**< RX 128-255 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_256_511 = 5, /**< RX 256-511 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_512_1023 = 6, /**< RX 512-1023 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1024_1518 = 7, /**< RX 1024-1518 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1519_2047 = 8, /**< RX 1519-2047 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_2048_4095 = 9, /**< RX 2048_4095 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_4096_9216 = 10, /**< RX 4096-9216 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_9217_16383 = 11, /**< RX 9217-16383 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BROADCAST_FRAMES = 12, /**< RX Broadcast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_DATA_BYTES = 13, /**< RX Data Bytes. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_MULTICAST_FRAMES = 14, /**< RX Mulitcast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_UNICAST_FRAMES = 15, /**< RX Unicast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_ABORT_FRAMES = 16, /**< RX Abort Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FCS_ERROR = 17, /**< RX FCS Error. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_OVERSIZE_ERROR = 18, /**< RX Oversize Error. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_RUNT_ERROR = 19, /**< RX Runt Error. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BYTES = 20, /**< TX Bytes. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES = 21, /**< TX Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_64 = 22, /**< TX 64 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_65_127 = 23, /**< TX 65-127 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_128_255 = 24, /**< TX 128-255 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_256_511 = 25, /**< TX 256-511 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_512_1023 = 26, /**< TX 512-1023 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1024_1518 = 27, /**< TX 1024-1518 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1519_2047 = 28, /**< TX 1519-2047 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_2048_4095 = 29, /**< TX 2048_4095 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_4096_9216 = 30, /**< TX 4096-9216 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_9217_16383 = 31, /**< TX 9217-16383 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BROADCAST_FRAMES = 32, /**< TX Broadcast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_DATA_BYTES = 33, /**< TX Data Bytes. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_MULTICAST_FRAMES = 34, /**< TX Mulitcast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_UNICAST_FRAMES = 35, /**< TX Unicast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_ABORT_FRAMES = 36, /**< TX Abort Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_ae_stats_data_id__begin BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID__BEGIN
#define bcmolt_pon_interface_ae_stats_data_id_rx_bytes BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BYTES
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_64 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_64
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_65_127 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_65_127
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_128_255 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_128_255
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_256_511 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_256_511
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_512_1023 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_1024_1518 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_1519_2047 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_2048_4095 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_4096_9216 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_pon_interface_ae_stats_data_id_rx_frames_9217_16383 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_pon_interface_ae_stats_data_id_rx_broadcast_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BROADCAST_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id_rx_data_bytes BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_DATA_BYTES
#define bcmolt_pon_interface_ae_stats_data_id_rx_multicast_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_MULTICAST_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id_rx_unicast_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_UNICAST_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id_rx_abort_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_ABORT_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id_rx_fcs_error BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FCS_ERROR
#define bcmolt_pon_interface_ae_stats_data_id_rx_oversize_error BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_OVERSIZE_ERROR
#define bcmolt_pon_interface_ae_stats_data_id_rx_runt_error BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_RUNT_ERROR
#define bcmolt_pon_interface_ae_stats_data_id_tx_bytes BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BYTES
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_64 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_64
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_65_127 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_65_127
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_128_255 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_128_255
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_256_511 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_256_511
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_512_1023 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_1024_1518 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_1519_2047 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_2048_4095 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_4096_9216 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_pon_interface_ae_stats_data_id_tx_frames_9217_16383 BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_pon_interface_ae_stats_data_id_tx_broadcast_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BROADCAST_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id_tx_data_bytes BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_DATA_BYTES
#define bcmolt_pon_interface_ae_stats_data_id_tx_multicast_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_MULTICAST_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id_tx_unicast_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_UNICAST_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id_tx_abort_frames BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_ABORT_FRAMES
#define bcmolt_pon_interface_ae_stats_data_id__num_of BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID__NUM_OF
#define bcmolt_pon_interface_ae_stats_data_id_all_properties 0xFF
#define bcmolt_pon_interface_ae_stats_data_id_full_mask 0x1FFFFFFFFF

} bcmolt_pon_interface_ae_stats_data_id;

/** Identifiers for all fields in a 'pon_interface_set_pon_interface_state_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_SET_PON_INTERFACE_STATE_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_SET_PON_INTERFACE_STATE_DATA_ID_OPERATION = 0, /**< PON interface operation. */
    BCMOLT_PON_INTERFACE_SET_PON_INTERFACE_STATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_set_pon_interface_state_data_id__begin BCMOLT_PON_INTERFACE_SET_PON_INTERFACE_STATE_DATA_ID__BEGIN
#define bcmolt_pon_interface_set_pon_interface_state_data_id_operation BCMOLT_PON_INTERFACE_SET_PON_INTERFACE_STATE_DATA_ID_OPERATION
#define bcmolt_pon_interface_set_pon_interface_state_data_id__num_of BCMOLT_PON_INTERFACE_SET_PON_INTERFACE_STATE_DATA_ID__NUM_OF
#define bcmolt_pon_interface_set_pon_interface_state_data_id_all_properties 0xFF
#define bcmolt_pon_interface_set_pon_interface_state_data_id_full_mask 0x1

} bcmolt_pon_interface_set_pon_interface_state_data_id;

/** Identifiers for all fields in a 'pon_interface_set_onu_state_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_SET_ONU_STATE_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_SET_ONU_STATE_DATA_ID_ONU_STATE = 0, /**< ONU state. */
    BCMOLT_PON_INTERFACE_SET_ONU_STATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_set_onu_state_data_id__begin BCMOLT_PON_INTERFACE_SET_ONU_STATE_DATA_ID__BEGIN
#define bcmolt_pon_interface_set_onu_state_data_id_onu_state BCMOLT_PON_INTERFACE_SET_ONU_STATE_DATA_ID_ONU_STATE
#define bcmolt_pon_interface_set_onu_state_data_id__num_of BCMOLT_PON_INTERFACE_SET_ONU_STATE_DATA_ID__NUM_OF
#define bcmolt_pon_interface_set_onu_state_data_id_all_properties 0xFF
#define bcmolt_pon_interface_set_onu_state_data_id_full_mask 0x1

} bcmolt_pon_interface_set_onu_state_data_id;

/** Identifiers for all fields in a 'pon_interface_disable_serial_number_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID_CONTROL = 0, /**< control. */
    BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID_SERIAL_NUMBER = 1, /**< serial number. */
    BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_disable_serial_number_data_id__begin BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID__BEGIN
#define bcmolt_pon_interface_disable_serial_number_data_id_control BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID_CONTROL
#define bcmolt_pon_interface_disable_serial_number_data_id_serial_number BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID_SERIAL_NUMBER
#define bcmolt_pon_interface_disable_serial_number_data_id__num_of BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID__NUM_OF
#define bcmolt_pon_interface_disable_serial_number_data_id_all_properties 0xFF
#define bcmolt_pon_interface_disable_serial_number_data_id_full_mask 0x3

} bcmolt_pon_interface_disable_serial_number_data_id;

/** Identifiers for all fields in a 'pon_interface_run_special_bw_map_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID_NUMBER_OF_CYCLE = 0, /**< number of cycle. */
    BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID_ALLOCATION_NUMBER = 1, /**< allocation number. */
    BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID_BW_MAP_ARRAY = 2, /**< bw map array. */
    BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_run_special_bw_map_data_id__begin BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID__BEGIN
#define bcmolt_pon_interface_run_special_bw_map_data_id_number_of_cycle BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID_NUMBER_OF_CYCLE
#define bcmolt_pon_interface_run_special_bw_map_data_id_allocation_number BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID_ALLOCATION_NUMBER
#define bcmolt_pon_interface_run_special_bw_map_data_id_bw_map_array BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID_BW_MAP_ARRAY
#define bcmolt_pon_interface_run_special_bw_map_data_id__num_of BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID__NUM_OF
#define bcmolt_pon_interface_run_special_bw_map_data_id_all_properties 0xFF
#define bcmolt_pon_interface_run_special_bw_map_data_id_full_mask 0x7

} bcmolt_pon_interface_run_special_bw_map_data_id;

/** Identifiers for all fields in a 'pon_interface_start_onu_upgrade_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_START_ONU_UPGRADE_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_START_ONU_UPGRADE_DATA_ID_LIST_OF_ONU_IDS = 0, /**< List of ONU IDs. */
    BCMOLT_PON_INTERFACE_START_ONU_UPGRADE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_start_onu_upgrade_data_id__begin BCMOLT_PON_INTERFACE_START_ONU_UPGRADE_DATA_ID__BEGIN
#define bcmolt_pon_interface_start_onu_upgrade_data_id_list_of_onu_ids BCMOLT_PON_INTERFACE_START_ONU_UPGRADE_DATA_ID_LIST_OF_ONU_IDS
#define bcmolt_pon_interface_start_onu_upgrade_data_id__num_of BCMOLT_PON_INTERFACE_START_ONU_UPGRADE_DATA_ID__NUM_OF
#define bcmolt_pon_interface_start_onu_upgrade_data_id_all_properties 0xFF
#define bcmolt_pon_interface_start_onu_upgrade_data_id_full_mask 0x1

} bcmolt_pon_interface_start_onu_upgrade_data_id;

/** Identifiers for all fields in a
  * 'pon_interface_protection_switching_type_c_set_multiple_onu_state_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID_ONU_STATE = 0, /**< onu state. */
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID_ONU_LIST = 1, /**< onu list. */
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_id__begin BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID__BEGIN
#define bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_id_onu_state BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID_ONU_STATE
#define bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_id_onu_list BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID_ONU_LIST
#define bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_id__num_of BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID__NUM_OF
#define bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_id_all_properties 0xFF
#define bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_id_full_mask 0x3

} bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_id;

/** Identifiers for all fields in a 'pon_interface_protection_switching_apply_rerange_delta_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA_DATA_ID_RERANGE_DELTA = 0, /**< Re-range delta. */
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_id__begin BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA_DATA_ID__BEGIN
#define bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_id_rerange_delta BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA_DATA_ID_RERANGE_DELTA
#define bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_id__num_of BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA_DATA_ID__NUM_OF
#define bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_id_all_properties 0xFF
#define bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_id_full_mask 0x1

} bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_id;

/** Identifiers for all fields in a 'pon_interface_cpu_packets_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_PACKET_TYPE = 0, /**< packet type. */
    BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_CALC_CRC = 1, /**< calc crc. */
    BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_GEM_PORT_LIST = 2, /**< gem port list. */
    BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_BUFFER = 3, /**< buffer. */
    BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_cpu_packets_data_id__begin BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID__BEGIN
#define bcmolt_pon_interface_cpu_packets_data_id_packet_type BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_PACKET_TYPE
#define bcmolt_pon_interface_cpu_packets_data_id_calc_crc BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_CALC_CRC
#define bcmolt_pon_interface_cpu_packets_data_id_gem_port_list BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_GEM_PORT_LIST
#define bcmolt_pon_interface_cpu_packets_data_id_buffer BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_BUFFER
#define bcmolt_pon_interface_cpu_packets_data_id__num_of BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID__NUM_OF
#define bcmolt_pon_interface_cpu_packets_data_id_all_properties 0xFF
#define bcmolt_pon_interface_cpu_packets_data_id_full_mask 0xF

} bcmolt_pon_interface_cpu_packets_data_id;

/** Identifiers for all fields in a 'pon_interface_broadcast_ploam_packet_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_ID_PLOAM = 0, /**< ploam. */
    BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_broadcast_ploam_packet_data_id__begin BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_ID__BEGIN
#define bcmolt_pon_interface_broadcast_ploam_packet_data_id_ploam BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_ID_PLOAM
#define bcmolt_pon_interface_broadcast_ploam_packet_data_id__num_of BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_ID__NUM_OF
#define bcmolt_pon_interface_broadcast_ploam_packet_data_id_all_properties 0xFF
#define bcmolt_pon_interface_broadcast_ploam_packet_data_id_full_mask 0x1

} bcmolt_pon_interface_broadcast_ploam_packet_data_id;

/** Identifiers for all fields in a 'pon_interface_state_change_completed_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID_RESULT = 0, /**< Result. */
    BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID_PREVIOUS_STATE = 1, /**< Previous state. */
    BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID_NEW_STATE = 2, /**< new state. */
    BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_state_change_completed_data_id__begin BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID__BEGIN
#define bcmolt_pon_interface_state_change_completed_data_id_result BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID_RESULT
#define bcmolt_pon_interface_state_change_completed_data_id_previous_state BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID_PREVIOUS_STATE
#define bcmolt_pon_interface_state_change_completed_data_id_new_state BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID_NEW_STATE
#define bcmolt_pon_interface_state_change_completed_data_id__num_of BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_state_change_completed_data_id_all_properties 0xFF
#define bcmolt_pon_interface_state_change_completed_data_id_full_mask 0x7

} bcmolt_pon_interface_state_change_completed_data_id;

/** Identifiers for all fields in a 'pon_interface_tod_request_completed_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_TOD_STRING = 0, /**< tod_string. */
    BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_SFC = 1, /**< sfc. */
    BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_RTC_OFFSET_SEC = 2, /**< rtc_offset_sec. */
    BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_RTC_OFFSET_NSEC = 3, /**< rtc_offset_nsec. */
    BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_STATUS = 4, /**< status. */
    BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_tod_request_completed_data_id__begin BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID__BEGIN
#define bcmolt_pon_interface_tod_request_completed_data_id_tod_string BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_TOD_STRING
#define bcmolt_pon_interface_tod_request_completed_data_id_sfc BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_SFC
#define bcmolt_pon_interface_tod_request_completed_data_id_rtc_offset_sec BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_RTC_OFFSET_SEC
#define bcmolt_pon_interface_tod_request_completed_data_id_rtc_offset_nsec BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_RTC_OFFSET_NSEC
#define bcmolt_pon_interface_tod_request_completed_data_id_status BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_STATUS
#define bcmolt_pon_interface_tod_request_completed_data_id__num_of BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_tod_request_completed_data_id_all_properties 0xFF
#define bcmolt_pon_interface_tod_request_completed_data_id_full_mask 0x1F

} bcmolt_pon_interface_tod_request_completed_data_id;

/** Identifiers for all fields in a 'pon_interface_los_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_LOS_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_LOS_DATA_ID_STATUS = 0, /**< status. */
    BCMOLT_PON_INTERFACE_LOS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_los_data_id__begin BCMOLT_PON_INTERFACE_LOS_DATA_ID__BEGIN
#define bcmolt_pon_interface_los_data_id_status BCMOLT_PON_INTERFACE_LOS_DATA_ID_STATUS
#define bcmolt_pon_interface_los_data_id__num_of BCMOLT_PON_INTERFACE_LOS_DATA_ID__NUM_OF
#define bcmolt_pon_interface_los_data_id_all_properties 0xFF
#define bcmolt_pon_interface_los_data_id_full_mask 0x1

} bcmolt_pon_interface_los_data_id;

/** Identifiers for all fields in a 'pon_interface_protection_switching_traffic_resume_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TRAFFIC_RESUME_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TRAFFIC_RESUME_DATA_ID_RESULT = 0, /**< Result. */
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TRAFFIC_RESUME_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_protection_switching_traffic_resume_data_id__begin BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TRAFFIC_RESUME_DATA_ID__BEGIN
#define bcmolt_pon_interface_protection_switching_traffic_resume_data_id_result BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TRAFFIC_RESUME_DATA_ID_RESULT
#define bcmolt_pon_interface_protection_switching_traffic_resume_data_id__num_of BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TRAFFIC_RESUME_DATA_ID__NUM_OF
#define bcmolt_pon_interface_protection_switching_traffic_resume_data_id_all_properties 0xFF
#define bcmolt_pon_interface_protection_switching_traffic_resume_data_id_full_mask 0x1

} bcmolt_pon_interface_protection_switching_traffic_resume_data_id;

/** Identifiers for all fields in a 'pon_interface_protection_switching_onus_ranged_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_ONUS_RANGED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_ONUS_RANGED_DATA_ID_ONUS = 0, /**< ONUs. */
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_ONUS_RANGED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_protection_switching_onus_ranged_data_id__begin BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_ONUS_RANGED_DATA_ID__BEGIN
#define bcmolt_pon_interface_protection_switching_onus_ranged_data_id_onus BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_ONUS_RANGED_DATA_ID_ONUS
#define bcmolt_pon_interface_protection_switching_onus_ranged_data_id__num_of BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_ONUS_RANGED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_protection_switching_onus_ranged_data_id_all_properties 0xFF
#define bcmolt_pon_interface_protection_switching_onus_ranged_data_id_full_mask 0x1

} bcmolt_pon_interface_protection_switching_onus_ranged_data_id;

/** Identifiers for all fields in a 'pon_interface_protection_switching_switchover_completed_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED_DATA_ID_RESULT = 0, /**< Result. */
    BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_protection_switching_switchover_completed_data_id__begin BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED_DATA_ID__BEGIN
#define bcmolt_pon_interface_protection_switching_switchover_completed_data_id_result BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED_DATA_ID_RESULT
#define bcmolt_pon_interface_protection_switching_switchover_completed_data_id__num_of BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_protection_switching_switchover_completed_data_id_all_properties 0xFF
#define bcmolt_pon_interface_protection_switching_switchover_completed_data_id_full_mask 0x1

} bcmolt_pon_interface_protection_switching_switchover_completed_data_id;

/** Identifiers for all fields in a 'pon_interface_standby_pon_monitoring_cycle_completed_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID_NUMBER_OF_DETECTED_DELIMITER = 0, /**< number of detected delimiter. */
    BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID_ENERGY_DETECT_SIGNAL = 1, /**< energy detect signal. */
    BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_id__begin BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID__BEGIN
#define bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_id_number_of_detected_delimiter BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID_NUMBER_OF_DETECTED_DELIMITER
#define bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_id_energy_detect_signal BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID_ENERGY_DETECT_SIGNAL
#define bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_id__num_of BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_id_all_properties 0xFF
#define bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_id_full_mask 0x3

} bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_id;

/** Identifiers for all fields in a 'pon_interface_onu_discovered_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_SERIAL_NUMBER = 0, /**< serial number. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_RANGING_TIME = 1, /**< ranging time. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_ONU_ID = 2, /**< onu_id. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_UPSTREAM_LINE_RATE_CAPABILITIES = 3, /**< upstream line rate capabilities. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_CURRENT_DOWNSTREAM_PON_ID = 4, /**< current downstream pon id. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_CURRENT_UPSTREAM_PON_ID = 5, /**< current upstream pon id. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_CALIBRATION_RECORD = 6, /**< calibration record. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_TUNING_GRANULARITY = 7, /**< tuning granularity. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_STEP_TUNING_TIME = 8, /**< step tuning time. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_ATTENUATION = 9, /**< attenuetion. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_POWER_LEVELLING_CAPABILITIES = 10, /**< power levelling capabilities. */
    BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_onu_discovered_data_id__begin BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID__BEGIN
#define bcmolt_pon_interface_onu_discovered_data_id_serial_number BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_SERIAL_NUMBER
#define bcmolt_pon_interface_onu_discovered_data_id_ranging_time BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_RANGING_TIME
#define bcmolt_pon_interface_onu_discovered_data_id_onu_id BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_ONU_ID
#define bcmolt_pon_interface_onu_discovered_data_id_upstream_line_rate_capabilities BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_UPSTREAM_LINE_RATE_CAPABILITIES
#define bcmolt_pon_interface_onu_discovered_data_id_current_downstream_pon_id BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_CURRENT_DOWNSTREAM_PON_ID
#define bcmolt_pon_interface_onu_discovered_data_id_current_upstream_pon_id BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_CURRENT_UPSTREAM_PON_ID
#define bcmolt_pon_interface_onu_discovered_data_id_calibration_record BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_CALIBRATION_RECORD
#define bcmolt_pon_interface_onu_discovered_data_id_tuning_granularity BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_TUNING_GRANULARITY
#define bcmolt_pon_interface_onu_discovered_data_id_step_tuning_time BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_STEP_TUNING_TIME
#define bcmolt_pon_interface_onu_discovered_data_id_attenuation BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_ATTENUATION
#define bcmolt_pon_interface_onu_discovered_data_id_power_levelling_capabilities BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_POWER_LEVELLING_CAPABILITIES
#define bcmolt_pon_interface_onu_discovered_data_id__num_of BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_onu_discovered_data_id_all_properties 0xFF
#define bcmolt_pon_interface_onu_discovered_data_id_full_mask 0x7FF

} bcmolt_pon_interface_onu_discovered_data_id;

/** Identifiers for all fields in a 'pon_interface_cpu_packets_failure_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID_ERROR = 0, /**< Error. */
    BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID_GEM_PORT_ID = 1, /**< GEM Port ID. */
    BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_cpu_packets_failure_data_id__begin BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID__BEGIN
#define bcmolt_pon_interface_cpu_packets_failure_data_id_error BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID_ERROR
#define bcmolt_pon_interface_cpu_packets_failure_data_id_gem_port_id BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID_GEM_PORT_ID
#define bcmolt_pon_interface_cpu_packets_failure_data_id__num_of BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID__NUM_OF
#define bcmolt_pon_interface_cpu_packets_failure_data_id_all_properties 0xFF
#define bcmolt_pon_interface_cpu_packets_failure_data_id_full_mask 0x3

} bcmolt_pon_interface_cpu_packets_failure_data_id;

/** Identifiers for all fields in a 'pon_interface_onu_upgrade_complete_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID_OVERALL_STATUS = 0, /**< Overall status. */
    BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID_FILE_SIZE_IN_BYTES = 1, /**< File size in bytes. */
    BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID_ONU_STATUS = 2, /**< ONU status. */
    BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_onu_upgrade_complete_data_id__begin BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID__BEGIN
#define bcmolt_pon_interface_onu_upgrade_complete_data_id_overall_status BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID_OVERALL_STATUS
#define bcmolt_pon_interface_onu_upgrade_complete_data_id_file_size_in_bytes BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID_FILE_SIZE_IN_BYTES
#define bcmolt_pon_interface_onu_upgrade_complete_data_id_onu_status BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID_ONU_STATUS
#define bcmolt_pon_interface_onu_upgrade_complete_data_id__num_of BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID__NUM_OF
#define bcmolt_pon_interface_onu_upgrade_complete_data_id_all_properties 0xFF
#define bcmolt_pon_interface_onu_upgrade_complete_data_id_full_mask 0x7

} bcmolt_pon_interface_onu_upgrade_complete_data_id;

/** Identifiers for all fields in a 'pon_interface_mpcp_timestamp_changed_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_MPCP_TIMESTAMP_CHANGED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_MPCP_TIMESTAMP_CHANGED_DATA_ID_MPCP_TIMESTAMP = 0, /**< MPCP Timestamp. */
    BCMOLT_PON_INTERFACE_MPCP_TIMESTAMP_CHANGED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_mpcp_timestamp_changed_data_id__begin BCMOLT_PON_INTERFACE_MPCP_TIMESTAMP_CHANGED_DATA_ID__BEGIN
#define bcmolt_pon_interface_mpcp_timestamp_changed_data_id_mpcp_timestamp BCMOLT_PON_INTERFACE_MPCP_TIMESTAMP_CHANGED_DATA_ID_MPCP_TIMESTAMP
#define bcmolt_pon_interface_mpcp_timestamp_changed_data_id__num_of BCMOLT_PON_INTERFACE_MPCP_TIMESTAMP_CHANGED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_mpcp_timestamp_changed_data_id_all_properties 0xFF
#define bcmolt_pon_interface_mpcp_timestamp_changed_data_id_full_mask 0x1

} bcmolt_pon_interface_mpcp_timestamp_changed_data_id;

/** Identifiers for all fields in a 'pon_interface_switch_pon_type_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_DATA_ID_NEW_PON_TYPE = 0, /**< Requested PON type. */
    BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_switch_pon_type_data_id__begin BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_DATA_ID__BEGIN
#define bcmolt_pon_interface_switch_pon_type_data_id_new_pon_type BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_DATA_ID_NEW_PON_TYPE
#define bcmolt_pon_interface_switch_pon_type_data_id__num_of BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_DATA_ID__NUM_OF
#define bcmolt_pon_interface_switch_pon_type_data_id_all_properties 0xFF
#define bcmolt_pon_interface_switch_pon_type_data_id_full_mask 0x1

} bcmolt_pon_interface_switch_pon_type_data_id;

/** Identifiers for all fields in a 'pon_interface_switch_pon_type_completed_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_RESULT = 0, /**< Result of the operation. */
    BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_FAIL_REASON = 1, /**< Failure reason. */
    BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_NEW_TYPE = 2, /**< The new PON type that is set by the switch_pon_type operation. In case of failure it is the same as the old type.. */
    BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_OLD_TYPE = 3, /**< The PON type before the switch PON type operation. */
    BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_switch_pon_type_completed_data_id__begin BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID__BEGIN
#define bcmolt_pon_interface_switch_pon_type_completed_data_id_result BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_RESULT
#define bcmolt_pon_interface_switch_pon_type_completed_data_id_fail_reason BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_FAIL_REASON
#define bcmolt_pon_interface_switch_pon_type_completed_data_id_new_type BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_NEW_TYPE
#define bcmolt_pon_interface_switch_pon_type_completed_data_id_old_type BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_OLD_TYPE
#define bcmolt_pon_interface_switch_pon_type_completed_data_id__num_of BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_switch_pon_type_completed_data_id_all_properties 0xFF
#define bcmolt_pon_interface_switch_pon_type_completed_data_id_full_mask 0xF

} bcmolt_pon_interface_switch_pon_type_completed_data_id;

/** Identifiers for all fields in a 'pon_interface_rogue_detection_tool_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID_START_OFFSET = 0, /**< start offSet. */
    BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID_USE_ONU_ID = 1, /**< use onu id. */
    BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID_ONU_ID = 2, /**< onu id. */
    BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_rogue_detection_tool_data_id__begin BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID__BEGIN
#define bcmolt_pon_interface_rogue_detection_tool_data_id_start_offset BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID_START_OFFSET
#define bcmolt_pon_interface_rogue_detection_tool_data_id_use_onu_id BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID_USE_ONU_ID
#define bcmolt_pon_interface_rogue_detection_tool_data_id_onu_id BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID_ONU_ID
#define bcmolt_pon_interface_rogue_detection_tool_data_id__num_of BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID__NUM_OF
#define bcmolt_pon_interface_rogue_detection_tool_data_id_all_properties 0xFF
#define bcmolt_pon_interface_rogue_detection_tool_data_id_full_mask 0x7

} bcmolt_pon_interface_rogue_detection_tool_data_id;

/** Identifiers for all fields in a 'pon_interface_rogue_detection_tool_done_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID_RESULT = 0, /**< result. */
    BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID_OUTPUT = 1, /**< output. */
    BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_rogue_detection_tool_done_data_id__begin BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID__BEGIN
#define bcmolt_pon_interface_rogue_detection_tool_done_data_id_result BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID_RESULT
#define bcmolt_pon_interface_rogue_detection_tool_done_data_id_output BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID_OUTPUT
#define bcmolt_pon_interface_rogue_detection_tool_done_data_id__num_of BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID__NUM_OF
#define bcmolt_pon_interface_rogue_detection_tool_done_data_id_all_properties 0xFF
#define bcmolt_pon_interface_rogue_detection_tool_done_data_id_full_mask 0x3

} bcmolt_pon_interface_rogue_detection_tool_done_data_id;

/** Identifiers for all fields in a 'pon_interface_onu_upgrade_activate_commit_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_ONU_UPGRADE_ACTIVATE_COMMIT_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_ONU_UPGRADE_ACTIVATE_COMMIT_DATA_ID_LIST_OF_ONU_IDS = 0, /**< List of ONU IDs. */
    BCMOLT_PON_INTERFACE_ONU_UPGRADE_ACTIVATE_COMMIT_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_onu_upgrade_activate_commit_data_id__begin BCMOLT_PON_INTERFACE_ONU_UPGRADE_ACTIVATE_COMMIT_DATA_ID__BEGIN
#define bcmolt_pon_interface_onu_upgrade_activate_commit_data_id_list_of_onu_ids BCMOLT_PON_INTERFACE_ONU_UPGRADE_ACTIVATE_COMMIT_DATA_ID_LIST_OF_ONU_IDS
#define bcmolt_pon_interface_onu_upgrade_activate_commit_data_id__num_of BCMOLT_PON_INTERFACE_ONU_UPGRADE_ACTIVATE_COMMIT_DATA_ID__NUM_OF
#define bcmolt_pon_interface_onu_upgrade_activate_commit_data_id_all_properties 0xFF
#define bcmolt_pon_interface_onu_upgrade_activate_commit_data_id_full_mask 0x1

} bcmolt_pon_interface_onu_upgrade_activate_commit_data_id;

/** Identifiers for all fields in a 'pon_interface_itu_pon_stats_cfg_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS = 0, /**< Receive FEC codewords. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_BIP_UNITS = 1, /**< Received units (bits in GPON / bytes in XGPON) protected by bip. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_BIP_ERRORS = 2, /**< Received bip errors. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM = 3, /**< Received valid GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_DROPPED = 4, /**< Received dropped GEM ID frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_IDLE = 5, /**< Received idle GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_CORRECTED = 6, /**< Received corrected GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_CRC_ERROR = 7, /**< Received packets with CRC error. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_FRAGMENT_ERROR = 8, /**< Received fragment errors. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PACKETS_DROPPED = 9, /**< Global dropped packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_DROPPED_TOO_SHORT = 10, /**< Received packets dropped due to length too short. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_DROPPED_TOO_LONG = 11, /**< Received packet dropped due to length too long. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_KEY_ERROR = 12, /**< Received key errors. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_CPU_OMCI_PACKETS_DROPPED = 13, /**< Received packets dropped due to illegal length. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_PLOAMS = 14, /**< Transmitted Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_DROPPED = 15, /**< Received dropped Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_ALLOCATIONS_VALID = 16, /**< Received valid allocations. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_ALLOCATIONS_INVALID = 17, /**< Received invalid allocations. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_ALLOCATIONS_DISABLED = 18, /**< Received disabled allocations. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS = 19, /**< Received Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_NON_IDLE = 20, /**< Received non idle Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_ERROR = 21, /**< Received error Ploams. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_CPU = 22, /**< Received CPU packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI = 23, /**< Received OMCI packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR = 24, /**< Received OMCI packets with CRC errors. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_PACKETS = 25, /**< Transmitted packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_GEM = 26, /**< Transmitted GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_CPU = 27, /**< Transmitted CPU packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_OMCI = 28, /**< Transmitted OMCI packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_ILLEGAL_LENGTH = 29, /**< Transmit packets dropped due to illegal length. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_TPID_MISS = 30, /**< Transmit packets dropped due to TPID miss. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_VID_MISS = 31, /**< Transmit packets droped due to VID miss. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_XGTC_HEADERS = 32, /**< Received valid XGTC headers. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_XGTC_CORRECTED = 33, /**< Received corrected XGTC headers. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_XGTC_UNCORRECTED = 34, /**< Received uncorrected XGTC headers. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS_UNCORRECTED = 35, /**< Received uncorrected FEC codewords. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_ILLEGAL = 36, /**< Received illegal GEM frames. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_TOTAL = 37, /**< Total transmit packets droped. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PACKETS = 38, /**< Received packets. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id__begin BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_fec_codewords BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_bip_units BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_BIP_UNITS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_bip_errors BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_BIP_ERRORS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_gem BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_gem_dropped BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_DROPPED
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_gem_idle BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_IDLE
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_gem_corrected BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_CORRECTED
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_crc_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_CRC_ERROR
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_fragment_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_FRAGMENT_ERROR
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_packets_dropped BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PACKETS_DROPPED
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_dropped_too_short BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_DROPPED_TOO_SHORT
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_dropped_too_long BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_DROPPED_TOO_LONG
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_key_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_KEY_ERROR
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_cpu_omci_packets_dropped BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_CPU_OMCI_PACKETS_DROPPED
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_tx_ploams BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_PLOAMS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_ploams_dropped BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_DROPPED
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_allocations_valid BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_ALLOCATIONS_VALID
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_allocations_invalid BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_ALLOCATIONS_INVALID
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_allocations_disabled BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_ALLOCATIONS_DISABLED
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_ploams BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_ploams_non_idle BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_NON_IDLE
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_ploams_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_ERROR
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_cpu BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_CPU
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_omci BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_omci_packets_crc_error BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_tx_packets BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_PACKETS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_tx_gem BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_GEM
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_tx_cpu BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_CPU
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_tx_omci BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_OMCI
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_tx_dropped_illegal_length BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_ILLEGAL_LENGTH
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_tx_dropped_tpid_miss BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_TPID_MISS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_tx_dropped_vid_miss BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_VID_MISS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_xgtc_headers BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_XGTC_HEADERS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_xgtc_corrected BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_XGTC_CORRECTED
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_xgtc_uncorrected BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_XGTC_UNCORRECTED
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_fec_codewords_uncorrected BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS_UNCORRECTED
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_gem_illegal BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_ILLEGAL
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_tx_dropped_total BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_TOTAL
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_rx_packets BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PACKETS
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id__num_of BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_pon_interface_itu_pon_stats_cfg_data_id_full_mask 0x7FFFFFFFFF

} bcmolt_pon_interface_itu_pon_stats_cfg_data_id;

/** Identifiers for all fields in a 'pon_interface_itu_pon_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_id__begin BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_id_stat BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_id__num_of BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'pon_interface_itu_pon_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_id__begin BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_id_stat BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_id__num_of BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'pon_interface_ae_stats_cfg_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_BYTES = 0, /**< RX Bytes. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES = 1, /**< RX Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_64 = 2, /**< RX 64 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_65_127 = 3, /**< RX 65-127 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_128_255 = 4, /**< RX 128-255 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_256_511 = 5, /**< RX 256-511 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_512_1023 = 6, /**< RX 512-1023 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518 = 7, /**< RX 1024-1518 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047 = 8, /**< RX 1519-2047 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095 = 9, /**< RX 2048_4095 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216 = 10, /**< RX 4096-9216 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383 = 11, /**< RX 9217-16383 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_BROADCAST_FRAMES = 12, /**< RX Broadcast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_DATA_BYTES = 13, /**< RX Data Bytes. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_MULTICAST_FRAMES = 14, /**< RX Mulitcast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_UNICAST_FRAMES = 15, /**< RX Unicast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_ABORT_FRAMES = 16, /**< RX Abort Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FCS_ERROR = 17, /**< RX FCS Error. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_OVERSIZE_ERROR = 18, /**< RX Oversize Error. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_RUNT_ERROR = 19, /**< RX Runt Error. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_BYTES = 20, /**< TX Bytes. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES = 21, /**< TX Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_64 = 22, /**< TX 64 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_65_127 = 23, /**< TX 65-127 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_128_255 = 24, /**< TX 128-255 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_256_511 = 25, /**< TX 256-511 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_512_1023 = 26, /**< TX 512-1023 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518 = 27, /**< TX 1024-1518 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047 = 28, /**< TX 1519-2047 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095 = 29, /**< TX 2048_4095 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216 = 30, /**< TX 4096-9216 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383 = 31, /**< TX 9217-16383 Byte Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_BROADCAST_FRAMES = 32, /**< TX Broadcast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_DATA_BYTES = 33, /**< TX Data Bytes. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_MULTICAST_FRAMES = 34, /**< TX Mulitcast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_UNICAST_FRAMES = 35, /**< TX Unicast Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_ABORT_FRAMES = 36, /**< TX Abort Frames. */
    BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_ae_stats_cfg_data_id__begin BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_bytes BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_BYTES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_64 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_64
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_65_127 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_65_127
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_128_255 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_128_255
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_256_511 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_256_511
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_512_1023 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_1024_1518 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_1519_2047 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_2048_4095 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_4096_9216 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_frames_9217_16383 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_broadcast_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_BROADCAST_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_data_bytes BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_DATA_BYTES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_multicast_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_MULTICAST_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_unicast_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_UNICAST_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_abort_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_ABORT_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_fcs_error BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FCS_ERROR
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_oversize_error BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_OVERSIZE_ERROR
#define bcmolt_pon_interface_ae_stats_cfg_data_id_rx_runt_error BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_RUNT_ERROR
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_bytes BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_BYTES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_64 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_64
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_65_127 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_65_127
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_128_255 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_128_255
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_256_511 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_256_511
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_512_1023 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_1024_1518 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_1519_2047 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_2048_4095 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_4096_9216 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_frames_9217_16383 BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_broadcast_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_BROADCAST_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_data_bytes BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_DATA_BYTES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_multicast_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_MULTICAST_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_unicast_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_UNICAST_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id_tx_abort_frames BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_ABORT_FRAMES
#define bcmolt_pon_interface_ae_stats_cfg_data_id__num_of BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_pon_interface_ae_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_pon_interface_ae_stats_cfg_data_id_full_mask 0x1FFFFFFFFF

} bcmolt_pon_interface_ae_stats_cfg_data_id;

/** Identifiers for all fields in a 'pon_interface_ae_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_AE_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_AE_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_PON_INTERFACE_AE_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_ae_stats_alarm_raised_data_id__begin BCMOLT_PON_INTERFACE_AE_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_pon_interface_ae_stats_alarm_raised_data_id_stat BCMOLT_PON_INTERFACE_AE_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_pon_interface_ae_stats_alarm_raised_data_id__num_of BCMOLT_PON_INTERFACE_AE_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_ae_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_pon_interface_ae_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_pon_interface_ae_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'pon_interface_ae_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_AE_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_AE_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_PON_INTERFACE_AE_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_ae_stats_alarm_cleared_data_id__begin BCMOLT_PON_INTERFACE_AE_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_pon_interface_ae_stats_alarm_cleared_data_id_stat BCMOLT_PON_INTERFACE_AE_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_pon_interface_ae_stats_alarm_cleared_data_id__num_of BCMOLT_PON_INTERFACE_AE_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_pon_interface_ae_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_pon_interface_ae_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_pon_interface_ae_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'pon_interface_auto_cfg_data'. */
typedef enum
{
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ACTIVATE_ALL_ONUS_COMPLETED = 0, /**< activate all onus completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_AE_STATS_ALARM_CLEARED = 1, /**< Active Ethernet Interface Counters Alarm Cleared. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_AE_STATS_ALARM_RAISED = 2, /**< Active Ethernet Interface Counters Alarm Raised. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_CPU_PACKETS_FAILURE = 3, /**< CPU Packets Failure. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_DEACTIVATE_ALL_ONUS_COMPLETED = 4, /**< deactivate all onus completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_DISABLE_ALL_ONUS_COMPLETED = 5, /**< disable all onus completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ENABLE_ALL_ONUS_COMPLETED = 6, /**< enable all onus completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_IEEE_ROGUE_DETECTION_COMPLETED = 7, /**< IEEE Rogue Detection Completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_CLEARED = 8, /**< ITU PON Statistics Alarm Cleared. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_RAISED = 9, /**< ITU PON Statistics Alarm Raised. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_LOS = 10, /**< LOS. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_MPCP_TIMESTAMP_CHANGED = 11, /**< MPCP Timestamp Changed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ONU_DISCOVERED = 12, /**< ONU Discovered. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ONU_UPGRADE_COMPLETE = 13, /**< ONU Upgrade Complete. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_ONUS_RANGED = 14, /**< Protection Switching ONUs Ranged. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_RERANGE_FAILURE = 15, /**< Protection Switching Re-range failure  (IEEE). */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED = 16, /**< Protection Switching Switchover Completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_TRAFFIC_RESUME = 17, /**< Protection Switching Traffic Resume. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ROGUE_DETECTION_TOOL_DONE = 18, /**< rogue detection tool done. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_SERIAL_NUMBER_ACQUISITION_CYCLE_START = 19, /**< Serial Number Acquisition Cycle Start. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_STANDBY_PON_MONITORING_CYCLE_COMPLETED = 20, /**< Standby PON Monitoring Cycle Completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_STATE_CHANGE_COMPLETED = 21, /**< State Change Completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_SWITCH_PON_TYPE_COMPLETED = 22, /**< Switch PON type completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_TOD_REQUEST_COMPLETED = 23, /**< TOD request completed. */
    BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_pon_interface_auto_cfg_data_id__begin BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_pon_interface_auto_cfg_data_id_activate_all_onus_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ACTIVATE_ALL_ONUS_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id_ae_stats_alarm_cleared BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_AE_STATS_ALARM_CLEARED
#define bcmolt_pon_interface_auto_cfg_data_id_ae_stats_alarm_raised BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_AE_STATS_ALARM_RAISED
#define bcmolt_pon_interface_auto_cfg_data_id_cpu_packets_failure BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_CPU_PACKETS_FAILURE
#define bcmolt_pon_interface_auto_cfg_data_id_deactivate_all_onus_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_DEACTIVATE_ALL_ONUS_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id_disable_all_onus_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_DISABLE_ALL_ONUS_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id_enable_all_onus_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ENABLE_ALL_ONUS_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id_ieee_rogue_detection_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_IEEE_ROGUE_DETECTION_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id_itu_pon_stats_alarm_cleared BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_CLEARED
#define bcmolt_pon_interface_auto_cfg_data_id_itu_pon_stats_alarm_raised BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_RAISED
#define bcmolt_pon_interface_auto_cfg_data_id_los BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_LOS
#define bcmolt_pon_interface_auto_cfg_data_id_mpcp_timestamp_changed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_MPCP_TIMESTAMP_CHANGED
#define bcmolt_pon_interface_auto_cfg_data_id_onu_discovered BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ONU_DISCOVERED
#define bcmolt_pon_interface_auto_cfg_data_id_onu_upgrade_complete BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ONU_UPGRADE_COMPLETE
#define bcmolt_pon_interface_auto_cfg_data_id_protection_switching_onus_ranged BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_ONUS_RANGED
#define bcmolt_pon_interface_auto_cfg_data_id_protection_switching_rerange_failure BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_RERANGE_FAILURE
#define bcmolt_pon_interface_auto_cfg_data_id_protection_switching_switchover_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id_protection_switching_traffic_resume BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_TRAFFIC_RESUME
#define bcmolt_pon_interface_auto_cfg_data_id_rogue_detection_tool_done BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ROGUE_DETECTION_TOOL_DONE
#define bcmolt_pon_interface_auto_cfg_data_id_serial_number_acquisition_cycle_start BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_SERIAL_NUMBER_ACQUISITION_CYCLE_START
#define bcmolt_pon_interface_auto_cfg_data_id_standby_pon_monitoring_cycle_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_STANDBY_PON_MONITORING_CYCLE_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id_state_change_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_STATE_CHANGE_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id_switch_pon_type_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_SWITCH_PON_TYPE_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id_tod_request_completed BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_TOD_REQUEST_COMPLETED
#define bcmolt_pon_interface_auto_cfg_data_id__num_of BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_pon_interface_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_pon_interface_auto_cfg_data_id_full_mask 0xFFFFFF

} bcmolt_pon_interface_auto_cfg_data_id;

/** Identifiers for all fields in a 'protection_interface_key'. */
typedef enum
{
    BCMOLT_PROTECTION_INTERFACE_KEY_ID__BEGIN = 0,
    BCMOLT_PROTECTION_INTERFACE_KEY_ID_ID = 0, /**< Id. */
    BCMOLT_PROTECTION_INTERFACE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_protection_interface_key_id__begin BCMOLT_PROTECTION_INTERFACE_KEY_ID__BEGIN
#define bcmolt_protection_interface_key_id_id BCMOLT_PROTECTION_INTERFACE_KEY_ID_ID
#define bcmolt_protection_interface_key_id__num_of BCMOLT_PROTECTION_INTERFACE_KEY_ID__NUM_OF
#define bcmolt_protection_interface_key_id_all_properties 0xFF
#define bcmolt_protection_interface_key_id_full_mask 0x1

} bcmolt_protection_interface_key_id;

/** Identifiers for all fields in a 'protection_interface_cfg_data'. */
typedef enum
{
    BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_STATE = 0, /**< State. */
    BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_PRIMARY_INTERFACE = 1, /**< Primary Interface. */
    BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_SECONDARY_INTERFACE = 2, /**< Secondary Interface. */
    BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_ACTIVE_INTERFACE = 3, /**< Active Interface. */
    BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_protection_interface_cfg_data_id__begin BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID__BEGIN
#define bcmolt_protection_interface_cfg_data_id_state BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_STATE
#define bcmolt_protection_interface_cfg_data_id_primary_interface BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_PRIMARY_INTERFACE
#define bcmolt_protection_interface_cfg_data_id_secondary_interface BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_SECONDARY_INTERFACE
#define bcmolt_protection_interface_cfg_data_id_active_interface BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_ACTIVE_INTERFACE
#define bcmolt_protection_interface_cfg_data_id__num_of BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID__NUM_OF
#define bcmolt_protection_interface_cfg_data_id_all_properties 0xFF
#define bcmolt_protection_interface_cfg_data_id_full_mask 0xF

} bcmolt_protection_interface_cfg_data_id;

/** Identifiers for all fields in a 'protection_interface_protection_switch_completed_data'. */
typedef enum
{
    BCMOLT_PROTECTION_INTERFACE_PROTECTION_SWITCH_COMPLETED_DATA_ID__BEGIN = 0,
    BCMOLT_PROTECTION_INTERFACE_PROTECTION_SWITCH_COMPLETED_DATA_ID_ACTIVE_INTERFACE = 0, /**< Active Interface. */
    BCMOLT_PROTECTION_INTERFACE_PROTECTION_SWITCH_COMPLETED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_protection_interface_protection_switch_completed_data_id__begin BCMOLT_PROTECTION_INTERFACE_PROTECTION_SWITCH_COMPLETED_DATA_ID__BEGIN
#define bcmolt_protection_interface_protection_switch_completed_data_id_active_interface BCMOLT_PROTECTION_INTERFACE_PROTECTION_SWITCH_COMPLETED_DATA_ID_ACTIVE_INTERFACE
#define bcmolt_protection_interface_protection_switch_completed_data_id__num_of BCMOLT_PROTECTION_INTERFACE_PROTECTION_SWITCH_COMPLETED_DATA_ID__NUM_OF
#define bcmolt_protection_interface_protection_switch_completed_data_id_all_properties 0xFF
#define bcmolt_protection_interface_protection_switch_completed_data_id_full_mask 0x1

} bcmolt_protection_interface_protection_switch_completed_data_id;

/** Identifiers for all fields in a 'protection_interface_auto_cfg_data'. */
typedef enum
{
    BCMOLT_PROTECTION_INTERFACE_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_PROTECTION_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCH_COMPLETED = 0, /**< Protection Switch Completed. */
    BCMOLT_PROTECTION_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_protection_interface_auto_cfg_data_id__begin BCMOLT_PROTECTION_INTERFACE_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_protection_interface_auto_cfg_data_id_protection_switch_completed BCMOLT_PROTECTION_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCH_COMPLETED
#define bcmolt_protection_interface_auto_cfg_data_id__num_of BCMOLT_PROTECTION_INTERFACE_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_protection_interface_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_protection_interface_auto_cfg_data_id_full_mask 0x1

} bcmolt_protection_interface_auto_cfg_data_id;

/** Identifiers for all fields in a 'software_error_key'. */
typedef enum
{
    BCMOLT_SOFTWARE_ERROR_KEY_ID__BEGIN = 0,
    BCMOLT_SOFTWARE_ERROR_KEY_ID_DEVICE_ID = 0, /**< Device ID. */
    BCMOLT_SOFTWARE_ERROR_KEY_ID_IDX = 1, /**< Index. */
    BCMOLT_SOFTWARE_ERROR_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_software_error_key_id__begin BCMOLT_SOFTWARE_ERROR_KEY_ID__BEGIN
#define bcmolt_software_error_key_id_device_id BCMOLT_SOFTWARE_ERROR_KEY_ID_DEVICE_ID
#define bcmolt_software_error_key_id_idx BCMOLT_SOFTWARE_ERROR_KEY_ID_IDX
#define bcmolt_software_error_key_id__num_of BCMOLT_SOFTWARE_ERROR_KEY_ID__NUM_OF
#define bcmolt_software_error_key_id_all_properties 0xFF
#define bcmolt_software_error_key_id_full_mask 0x3

} bcmolt_software_error_key_id;

/** Identifiers for all fields in a 'software_error_cfg_data'. */
typedef enum
{
    BCMOLT_SOFTWARE_ERROR_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_SOFTWARE_ERROR_CFG_DATA_ID_ENTRY = 0, /**< Entry. */
    BCMOLT_SOFTWARE_ERROR_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_software_error_cfg_data_id__begin BCMOLT_SOFTWARE_ERROR_CFG_DATA_ID__BEGIN
#define bcmolt_software_error_cfg_data_id_entry BCMOLT_SOFTWARE_ERROR_CFG_DATA_ID_ENTRY
#define bcmolt_software_error_cfg_data_id__num_of BCMOLT_SOFTWARE_ERROR_CFG_DATA_ID__NUM_OF
#define bcmolt_software_error_cfg_data_id_all_properties 0xFF
#define bcmolt_software_error_cfg_data_id_full_mask 0x1

} bcmolt_software_error_cfg_data_id;

/** Identifiers for all fields in a 'switch_inni_key'. */
typedef enum
{
    BCMOLT_SWITCH_INNI_KEY_ID__BEGIN = 0,
    BCMOLT_SWITCH_INNI_KEY_ID_ID = 0, /**< id. */
    BCMOLT_SWITCH_INNI_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_key_id__begin BCMOLT_SWITCH_INNI_KEY_ID__BEGIN
#define bcmolt_switch_inni_key_id_id BCMOLT_SWITCH_INNI_KEY_ID_ID
#define bcmolt_switch_inni_key_id__num_of BCMOLT_SWITCH_INNI_KEY_ID__NUM_OF
#define bcmolt_switch_inni_key_id_all_properties 0xFF
#define bcmolt_switch_inni_key_id_full_mask 0x1

} bcmolt_switch_inni_key_id;

/** Identifiers for all fields in a 'switch_inni_cfg_data'. */
typedef enum
{
    BCMOLT_SWITCH_INNI_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_SWITCH_INNI_CFG_DATA_ID_CONFIG_STATE = 0, /**< config state. */
    BCMOLT_SWITCH_INNI_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_cfg_data_id__begin BCMOLT_SWITCH_INNI_CFG_DATA_ID__BEGIN
#define bcmolt_switch_inni_cfg_data_id_config_state BCMOLT_SWITCH_INNI_CFG_DATA_ID_CONFIG_STATE
#define bcmolt_switch_inni_cfg_data_id__num_of BCMOLT_SWITCH_INNI_CFG_DATA_ID__NUM_OF
#define bcmolt_switch_inni_cfg_data_id_all_properties 0xFF
#define bcmolt_switch_inni_cfg_data_id_full_mask 0x1

} bcmolt_switch_inni_cfg_data_id;

/** Identifiers for all fields in a 'switch_inni_stats_data'. */
typedef enum
{
    BCMOLT_SWITCH_INNI_STATS_DATA_ID__BEGIN = 0,
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BYTES = 0, /**< received bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_PACKETS = 1, /**< received  packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UCAST_PACKETS = 2, /**< received  unicast packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_MCAST_PACKETS = 3, /**< received  multicast packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BCAST_PACKETS = 4, /**< received  broadcast packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_ERROR_PACKETS = 5, /**< received error packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UNKNOWN_PROTOS = 6, /**< received unknown proto packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BYTES = 7, /**< transmitted bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_PACKETS = 8, /**< transmitted packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UCAST_PACKETS = 9, /**< transmitted unicast packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_MCAST_PACKETS = 10, /**< transmitted multicast packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BCAST_PACKETS = 11, /**< transmitted broadcast packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_ERROR_PACKETS = 12, /**< transmitted error packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_64 = 13, /**< rx 64 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_65_127 = 14, /**< rx 65-127 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_128_255 = 15, /**< rx 128-255 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_256_511 = 16, /**< rx 256-511 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_512_1023 = 17, /**< rx 512-1023 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1024_1518 = 18, /**< rx 1024-1518 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1519_2047 = 19, /**< rx 1519-2047 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_2048_4095 = 20, /**< rx 2048-4095 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_4096_9216 = 21, /**< rx 4096-9216 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_9217_16383 = 22, /**< rx 9217-16383 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_64 = 23, /**< tx 64 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_65_127 = 24, /**< tx 65-127 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_128_255 = 25, /**< tx 128-255 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_256_511 = 26, /**< tx 256-511 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_512_1023 = 27, /**< tx 512-1023 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1024_1518 = 28, /**< tx 1024-1518 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1519_2047 = 29, /**< tx 1519-2047 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_2048_4095 = 30, /**< tx 2048-4095 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_4096_9216 = 31, /**< tx 4096-9216 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_9217_16383 = 32, /**< tx 9217-16383 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FCS_ERROR_PACKETS = 33, /**< rx fcs error packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UNDERSIZE_PACKETS = 34, /**< rx undersize packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_OVERSIZE_PACKETS = 35, /**< rx oversize packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UNDERSIZE_PACKETS = 36, /**< tx undersize packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_OVERSIZE_PACKETS = 37, /**< tx oversize packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_JABBER_PACKETS = 38, /**< rx jabber packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_JABBER_PACKETS = 39, /**< tx jabber packets. */
    BCMOLT_SWITCH_INNI_STATS_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_stats_data_id__begin BCMOLT_SWITCH_INNI_STATS_DATA_ID__BEGIN
#define bcmolt_switch_inni_stats_data_id_rx_bytes BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BYTES
#define bcmolt_switch_inni_stats_data_id_rx_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_PACKETS
#define bcmolt_switch_inni_stats_data_id_rx_ucast_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UCAST_PACKETS
#define bcmolt_switch_inni_stats_data_id_rx_mcast_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_MCAST_PACKETS
#define bcmolt_switch_inni_stats_data_id_rx_bcast_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BCAST_PACKETS
#define bcmolt_switch_inni_stats_data_id_rx_error_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_ERROR_PACKETS
#define bcmolt_switch_inni_stats_data_id_rx_unknown_protos BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UNKNOWN_PROTOS
#define bcmolt_switch_inni_stats_data_id_tx_bytes BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BYTES
#define bcmolt_switch_inni_stats_data_id_tx_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_PACKETS
#define bcmolt_switch_inni_stats_data_id_tx_ucast_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UCAST_PACKETS
#define bcmolt_switch_inni_stats_data_id_tx_mcast_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_MCAST_PACKETS
#define bcmolt_switch_inni_stats_data_id_tx_bcast_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BCAST_PACKETS
#define bcmolt_switch_inni_stats_data_id_tx_error_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_ERROR_PACKETS
#define bcmolt_switch_inni_stats_data_id_rx_frames_64 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_64
#define bcmolt_switch_inni_stats_data_id_rx_frames_65_127 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_65_127
#define bcmolt_switch_inni_stats_data_id_rx_frames_128_255 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_128_255
#define bcmolt_switch_inni_stats_data_id_rx_frames_256_511 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_256_511
#define bcmolt_switch_inni_stats_data_id_rx_frames_512_1023 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_switch_inni_stats_data_id_rx_frames_1024_1518 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_switch_inni_stats_data_id_rx_frames_1519_2047 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_switch_inni_stats_data_id_rx_frames_2048_4095 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_switch_inni_stats_data_id_rx_frames_4096_9216 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_switch_inni_stats_data_id_rx_frames_9217_16383 BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_switch_inni_stats_data_id_tx_frames_64 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_64
#define bcmolt_switch_inni_stats_data_id_tx_frames_65_127 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_65_127
#define bcmolt_switch_inni_stats_data_id_tx_frames_128_255 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_128_255
#define bcmolt_switch_inni_stats_data_id_tx_frames_256_511 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_256_511
#define bcmolt_switch_inni_stats_data_id_tx_frames_512_1023 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_switch_inni_stats_data_id_tx_frames_1024_1518 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_switch_inni_stats_data_id_tx_frames_1519_2047 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_switch_inni_stats_data_id_tx_frames_2048_4095 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_switch_inni_stats_data_id_tx_frames_4096_9216 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_switch_inni_stats_data_id_tx_frames_9217_16383 BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_switch_inni_stats_data_id_rx_fcs_error_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FCS_ERROR_PACKETS
#define bcmolt_switch_inni_stats_data_id_rx_undersize_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UNDERSIZE_PACKETS
#define bcmolt_switch_inni_stats_data_id_rx_oversize_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_OVERSIZE_PACKETS
#define bcmolt_switch_inni_stats_data_id_tx_undersize_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UNDERSIZE_PACKETS
#define bcmolt_switch_inni_stats_data_id_tx_oversize_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_OVERSIZE_PACKETS
#define bcmolt_switch_inni_stats_data_id_rx_jabber_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_JABBER_PACKETS
#define bcmolt_switch_inni_stats_data_id_tx_jabber_packets BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_JABBER_PACKETS
#define bcmolt_switch_inni_stats_data_id__num_of BCMOLT_SWITCH_INNI_STATS_DATA_ID__NUM_OF
#define bcmolt_switch_inni_stats_data_id_all_properties 0xFF
#define bcmolt_switch_inni_stats_data_id_full_mask 0xFFFFFFFFFF

} bcmolt_switch_inni_stats_data_id;

/** Identifiers for all fields in a 'switch_inni_stats_cfg_data'. */
typedef enum
{
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_BYTES = 0, /**< received bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_PACKETS = 1, /**< received  packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_UCAST_PACKETS = 2, /**< received  unicast packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_MCAST_PACKETS = 3, /**< received  multicast packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_BCAST_PACKETS = 4, /**< received  broadcast packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_ERROR_PACKETS = 5, /**< received error packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_UNKNOWN_PROTOS = 6, /**< received unknown proto packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_BYTES = 7, /**< transmitted bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_PACKETS = 8, /**< transmitted packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_UCAST_PACKETS = 9, /**< transmitted unicast packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_MCAST_PACKETS = 10, /**< transmitted multicast packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_BCAST_PACKETS = 11, /**< transmitted broadcast packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_ERROR_PACKETS = 12, /**< transmitted error packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_64 = 13, /**< rx 64 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_65_127 = 14, /**< rx 65-127 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_128_255 = 15, /**< rx 128-255 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_256_511 = 16, /**< rx 256-511 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_512_1023 = 17, /**< rx 512-1023 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518 = 18, /**< rx 1024-1518 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047 = 19, /**< rx 1519-2047 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095 = 20, /**< rx 2048-4095 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216 = 21, /**< rx 4096-9216 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383 = 22, /**< rx 9217-16383 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_64 = 23, /**< tx 64 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_65_127 = 24, /**< tx 65-127 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_128_255 = 25, /**< tx 128-255 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_256_511 = 26, /**< tx 256-511 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_512_1023 = 27, /**< tx 512-1023 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518 = 28, /**< tx 1024-1518 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047 = 29, /**< tx 1519-2047 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095 = 30, /**< tx 2048-4095 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216 = 31, /**< tx 4096-9216 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383 = 32, /**< tx 9217-16383 Bytes. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FCS_ERROR_PACKETS = 33, /**< rx fcs error packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_UNDERSIZE_PACKETS = 34, /**< rx undersize packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_OVERSIZE_PACKETS = 35, /**< rx oversize packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_UNDERSIZE_PACKETS = 36, /**< tx undersize packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_OVERSIZE_PACKETS = 37, /**< tx oversize packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_JABBER_PACKETS = 38, /**< rx jabber packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_JABBER_PACKETS = 39, /**< tx jabber packets. */
    BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_stats_cfg_data_id__begin BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID__BEGIN
#define bcmolt_switch_inni_stats_cfg_data_id_rx_bytes BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_BYTES
#define bcmolt_switch_inni_stats_cfg_data_id_rx_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_rx_ucast_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_UCAST_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_rx_mcast_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_MCAST_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_rx_bcast_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_BCAST_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_rx_error_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_ERROR_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_rx_unknown_protos BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_UNKNOWN_PROTOS
#define bcmolt_switch_inni_stats_cfg_data_id_tx_bytes BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_BYTES
#define bcmolt_switch_inni_stats_cfg_data_id_tx_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_tx_ucast_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_UCAST_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_tx_mcast_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_MCAST_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_tx_bcast_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_BCAST_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_tx_error_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_ERROR_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_64 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_64
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_65_127 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_65_127
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_128_255 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_128_255
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_256_511 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_256_511
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_512_1023 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_512_1023
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_1024_1518 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_1519_2047 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_2048_4095 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_4096_9216 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216
#define bcmolt_switch_inni_stats_cfg_data_id_rx_frames_9217_16383 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_64 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_64
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_65_127 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_65_127
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_128_255 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_128_255
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_256_511 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_256_511
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_512_1023 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_512_1023
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_1024_1518 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_1519_2047 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_2048_4095 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_4096_9216 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216
#define bcmolt_switch_inni_stats_cfg_data_id_tx_frames_9217_16383 BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383
#define bcmolt_switch_inni_stats_cfg_data_id_rx_fcs_error_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FCS_ERROR_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_rx_undersize_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_UNDERSIZE_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_rx_oversize_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_OVERSIZE_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_tx_undersize_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_UNDERSIZE_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_tx_oversize_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_OVERSIZE_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_rx_jabber_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_JABBER_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id_tx_jabber_packets BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_JABBER_PACKETS
#define bcmolt_switch_inni_stats_cfg_data_id__num_of BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID__NUM_OF
#define bcmolt_switch_inni_stats_cfg_data_id_all_properties 0xFF
#define bcmolt_switch_inni_stats_cfg_data_id_full_mask 0xFFFFFFFFFF

} bcmolt_switch_inni_stats_cfg_data_id;

/** Identifiers for all fields in a 'switch_inni_stats_alarm_raised_data'. */
typedef enum
{
    BCMOLT_SWITCH_INNI_STATS_ALARM_RAISED_DATA_ID__BEGIN = 0,
    BCMOLT_SWITCH_INNI_STATS_ALARM_RAISED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_SWITCH_INNI_STATS_ALARM_RAISED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_stats_alarm_raised_data_id__begin BCMOLT_SWITCH_INNI_STATS_ALARM_RAISED_DATA_ID__BEGIN
#define bcmolt_switch_inni_stats_alarm_raised_data_id_stat BCMOLT_SWITCH_INNI_STATS_ALARM_RAISED_DATA_ID_STAT
#define bcmolt_switch_inni_stats_alarm_raised_data_id__num_of BCMOLT_SWITCH_INNI_STATS_ALARM_RAISED_DATA_ID__NUM_OF
#define bcmolt_switch_inni_stats_alarm_raised_data_id_all_properties 0xFF
#define bcmolt_switch_inni_stats_alarm_raised_data_id_full_mask 0x1

} bcmolt_switch_inni_stats_alarm_raised_data_id;

/** Identifiers for all fields in a 'switch_inni_stats_alarm_cleared_data'. */
typedef enum
{
    BCMOLT_SWITCH_INNI_STATS_ALARM_CLEARED_DATA_ID__BEGIN = 0,
    BCMOLT_SWITCH_INNI_STATS_ALARM_CLEARED_DATA_ID_STAT = 0, /**< Statistic ID. */
    BCMOLT_SWITCH_INNI_STATS_ALARM_CLEARED_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_stats_alarm_cleared_data_id__begin BCMOLT_SWITCH_INNI_STATS_ALARM_CLEARED_DATA_ID__BEGIN
#define bcmolt_switch_inni_stats_alarm_cleared_data_id_stat BCMOLT_SWITCH_INNI_STATS_ALARM_CLEARED_DATA_ID_STAT
#define bcmolt_switch_inni_stats_alarm_cleared_data_id__num_of BCMOLT_SWITCH_INNI_STATS_ALARM_CLEARED_DATA_ID__NUM_OF
#define bcmolt_switch_inni_stats_alarm_cleared_data_id_all_properties 0xFF
#define bcmolt_switch_inni_stats_alarm_cleared_data_id_full_mask 0x1

} bcmolt_switch_inni_stats_alarm_cleared_data_id;

/** Identifiers for all fields in a 'switch_inni_auto_cfg_data'. */
typedef enum
{
    BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED = 0, /**< Switch INNI Interface Statistics Alarm Cleared. */
    BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED = 1, /**< Switch INNI Interface Statistics Alarm Raised. */
    BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_switch_inni_auto_cfg_data_id__begin BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID__BEGIN
#define bcmolt_switch_inni_auto_cfg_data_id_stats_alarm_cleared BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED
#define bcmolt_switch_inni_auto_cfg_data_id_stats_alarm_raised BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED
#define bcmolt_switch_inni_auto_cfg_data_id__num_of BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID__NUM_OF
#define bcmolt_switch_inni_auto_cfg_data_id_all_properties 0xFF
#define bcmolt_switch_inni_auto_cfg_data_id_full_mask 0x3

} bcmolt_switch_inni_auto_cfg_data_id;

/** Identifiers for all fields in a 'tc_to_queue_key'. */
typedef enum
{
    BCMOLT_TC_TO_QUEUE_KEY_ID__BEGIN = 0,
    BCMOLT_TC_TO_QUEUE_KEY_ID_ID = 0, /**< id. */
    BCMOLT_TC_TO_QUEUE_KEY_ID_DIR = 1, /**< dir. */
    BCMOLT_TC_TO_QUEUE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tc_to_queue_key_id__begin BCMOLT_TC_TO_QUEUE_KEY_ID__BEGIN
#define bcmolt_tc_to_queue_key_id_id BCMOLT_TC_TO_QUEUE_KEY_ID_ID
#define bcmolt_tc_to_queue_key_id_dir BCMOLT_TC_TO_QUEUE_KEY_ID_DIR
#define bcmolt_tc_to_queue_key_id__num_of BCMOLT_TC_TO_QUEUE_KEY_ID__NUM_OF
#define bcmolt_tc_to_queue_key_id_all_properties 0xFF
#define bcmolt_tc_to_queue_key_id_full_mask 0x3

} bcmolt_tc_to_queue_key_id;

/** Identifiers for all fields in a 'tc_to_queue_cfg_data'. */
typedef enum
{
    BCMOLT_TC_TO_QUEUE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_TC_TO_QUEUE_CFG_DATA_ID_QUEUE = 0, /**< queue. */
    BCMOLT_TC_TO_QUEUE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tc_to_queue_cfg_data_id__begin BCMOLT_TC_TO_QUEUE_CFG_DATA_ID__BEGIN
#define bcmolt_tc_to_queue_cfg_data_id_queue BCMOLT_TC_TO_QUEUE_CFG_DATA_ID_QUEUE
#define bcmolt_tc_to_queue_cfg_data_id__num_of BCMOLT_TC_TO_QUEUE_CFG_DATA_ID__NUM_OF
#define bcmolt_tc_to_queue_cfg_data_id_all_properties 0xFF
#define bcmolt_tc_to_queue_cfg_data_id_full_mask 0x1

} bcmolt_tc_to_queue_cfg_data_id;

/** Identifiers for all fields in a 'tm_qmp_key'. */
typedef enum
{
    BCMOLT_TM_QMP_KEY_ID__BEGIN = 0,
    BCMOLT_TM_QMP_KEY_ID_ID = 0, /**< id. */
    BCMOLT_TM_QMP_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_qmp_key_id__begin BCMOLT_TM_QMP_KEY_ID__BEGIN
#define bcmolt_tm_qmp_key_id_id BCMOLT_TM_QMP_KEY_ID_ID
#define bcmolt_tm_qmp_key_id__num_of BCMOLT_TM_QMP_KEY_ID__NUM_OF
#define bcmolt_tm_qmp_key_id_all_properties 0xFF
#define bcmolt_tm_qmp_key_id_full_mask 0x1

} bcmolt_tm_qmp_key_id;

/** Identifiers for all fields in a 'tm_qmp_cfg_data'. */
typedef enum
{
    BCMOLT_TM_QMP_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_TM_QMP_CFG_DATA_ID_TYPE = 0, /**< type. */
    BCMOLT_TM_QMP_CFG_DATA_ID_PBITS_TO_TMQ_ID = 1, /**< pbits_to_tmq_id. */
    BCMOLT_TM_QMP_CFG_DATA_ID_REF_COUNT = 2, /**< ref_count. */
    BCMOLT_TM_QMP_CFG_DATA_ID_STATE = 3, /**< state. */
    BCMOLT_TM_QMP_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_qmp_cfg_data_id__begin BCMOLT_TM_QMP_CFG_DATA_ID__BEGIN
#define bcmolt_tm_qmp_cfg_data_id_type BCMOLT_TM_QMP_CFG_DATA_ID_TYPE
#define bcmolt_tm_qmp_cfg_data_id_pbits_to_tmq_id BCMOLT_TM_QMP_CFG_DATA_ID_PBITS_TO_TMQ_ID
#define bcmolt_tm_qmp_cfg_data_id_ref_count BCMOLT_TM_QMP_CFG_DATA_ID_REF_COUNT
#define bcmolt_tm_qmp_cfg_data_id_state BCMOLT_TM_QMP_CFG_DATA_ID_STATE
#define bcmolt_tm_qmp_cfg_data_id__num_of BCMOLT_TM_QMP_CFG_DATA_ID__NUM_OF
#define bcmolt_tm_qmp_cfg_data_id_all_properties 0xFF
#define bcmolt_tm_qmp_cfg_data_id_full_mask 0xF

} bcmolt_tm_qmp_cfg_data_id;

/** Identifiers for all fields in a 'tm_queue_key'. */
typedef enum
{
    BCMOLT_TM_QUEUE_KEY_ID__BEGIN = 0,
    BCMOLT_TM_QUEUE_KEY_ID_SCHED_ID = 0, /**< sched_id. */
    BCMOLT_TM_QUEUE_KEY_ID_TM_Q_SET_ID = 1, /**< tm_q_set_id. */
    BCMOLT_TM_QUEUE_KEY_ID_ID = 2, /**< id. */
    BCMOLT_TM_QUEUE_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_queue_key_id__begin BCMOLT_TM_QUEUE_KEY_ID__BEGIN
#define bcmolt_tm_queue_key_id_sched_id BCMOLT_TM_QUEUE_KEY_ID_SCHED_ID
#define bcmolt_tm_queue_key_id_tm_q_set_id BCMOLT_TM_QUEUE_KEY_ID_TM_Q_SET_ID
#define bcmolt_tm_queue_key_id_id BCMOLT_TM_QUEUE_KEY_ID_ID
#define bcmolt_tm_queue_key_id__num_of BCMOLT_TM_QUEUE_KEY_ID__NUM_OF
#define bcmolt_tm_queue_key_id_all_properties 0xFF
#define bcmolt_tm_queue_key_id_full_mask 0x7

} bcmolt_tm_queue_key_id;

/** Identifiers for all fields in a 'tm_queue_cfg_data'. */
typedef enum
{
    BCMOLT_TM_QUEUE_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_TM_QUEUE_CFG_DATA_ID_STATE = 0, /**< State. */
    BCMOLT_TM_QUEUE_CFG_DATA_ID_TM_SCHED_PARAM = 1, /**< TM Sched Param. */
    BCMOLT_TM_QUEUE_CFG_DATA_ID_RATE = 3, /**< rate. */
    BCMOLT_TM_QUEUE_CFG_DATA_ID_REF_COUNT = 4, /**< ref_count. */
    BCMOLT_TM_QUEUE_CFG_DATA_ID_CONTROL_STATE = 5, /**< control state. */
    BCMOLT_TM_QUEUE_CFG_DATA_ID_CIR_ATTACHMENT_POINT = 6, /**< TM sched and priority line where CIR queue is attached. */
    BCMOLT_TM_QUEUE_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_queue_cfg_data_id__begin BCMOLT_TM_QUEUE_CFG_DATA_ID__BEGIN
#define bcmolt_tm_queue_cfg_data_id_state BCMOLT_TM_QUEUE_CFG_DATA_ID_STATE
#define bcmolt_tm_queue_cfg_data_id_tm_sched_param BCMOLT_TM_QUEUE_CFG_DATA_ID_TM_SCHED_PARAM
#define bcmolt_tm_queue_cfg_data_id_rate BCMOLT_TM_QUEUE_CFG_DATA_ID_RATE
#define bcmolt_tm_queue_cfg_data_id_ref_count BCMOLT_TM_QUEUE_CFG_DATA_ID_REF_COUNT
#define bcmolt_tm_queue_cfg_data_id_control_state BCMOLT_TM_QUEUE_CFG_DATA_ID_CONTROL_STATE
#define bcmolt_tm_queue_cfg_data_id_cir_attachment_point BCMOLT_TM_QUEUE_CFG_DATA_ID_CIR_ATTACHMENT_POINT
#define bcmolt_tm_queue_cfg_data_id__num_of BCMOLT_TM_QUEUE_CFG_DATA_ID__NUM_OF
#define bcmolt_tm_queue_cfg_data_id_all_properties 0xFF
#define bcmolt_tm_queue_cfg_data_id_full_mask 0x7B

} bcmolt_tm_queue_cfg_data_id;

/** Identifiers for all fields in a 'tm_sched_key'. */
typedef enum
{
    BCMOLT_TM_SCHED_KEY_ID__BEGIN = 0,
    BCMOLT_TM_SCHED_KEY_ID_ID = 0, /**< id. */
    BCMOLT_TM_SCHED_KEY_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_sched_key_id__begin BCMOLT_TM_SCHED_KEY_ID__BEGIN
#define bcmolt_tm_sched_key_id_id BCMOLT_TM_SCHED_KEY_ID_ID
#define bcmolt_tm_sched_key_id__num_of BCMOLT_TM_SCHED_KEY_ID__NUM_OF
#define bcmolt_tm_sched_key_id_all_properties 0xFF
#define bcmolt_tm_sched_key_id_full_mask 0x1

} bcmolt_tm_sched_key_id;

/** Identifiers for all fields in a 'tm_sched_cfg_data'. */
typedef enum
{
    BCMOLT_TM_SCHED_CFG_DATA_ID__BEGIN = 0,
    BCMOLT_TM_SCHED_CFG_DATA_ID_ATTACHMENT_POINT = 0, /**< attachment_point. */
    BCMOLT_TM_SCHED_CFG_DATA_ID_SCHED_TYPE = 1, /**< type. */
    BCMOLT_TM_SCHED_CFG_DATA_ID_NUM_PRIORITIES = 2, /**< num_priorities. */
    BCMOLT_TM_SCHED_CFG_DATA_ID_RATE = 3, /**< rate. */
    BCMOLT_TM_SCHED_CFG_DATA_ID_STATE = 5, /**< state. */
    BCMOLT_TM_SCHED_CFG_DATA_ID_CIR_ATTACHMENT_POINT = 6, /**< TM sched and priority line where CIR queue can be attached. */
    BCMOLT_TM_SCHED_CFG_DATA_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_tm_sched_cfg_data_id__begin BCMOLT_TM_SCHED_CFG_DATA_ID__BEGIN
#define bcmolt_tm_sched_cfg_data_id_attachment_point BCMOLT_TM_SCHED_CFG_DATA_ID_ATTACHMENT_POINT
#define bcmolt_tm_sched_cfg_data_id_sched_type BCMOLT_TM_SCHED_CFG_DATA_ID_SCHED_TYPE
#define bcmolt_tm_sched_cfg_data_id_num_priorities BCMOLT_TM_SCHED_CFG_DATA_ID_NUM_PRIORITIES
#define bcmolt_tm_sched_cfg_data_id_rate BCMOLT_TM_SCHED_CFG_DATA_ID_RATE
#define bcmolt_tm_sched_cfg_data_id_state BCMOLT_TM_SCHED_CFG_DATA_ID_STATE
#define bcmolt_tm_sched_cfg_data_id_cir_attachment_point BCMOLT_TM_SCHED_CFG_DATA_ID_CIR_ATTACHMENT_POINT
#define bcmolt_tm_sched_cfg_data_id__num_of BCMOLT_TM_SCHED_CFG_DATA_ID__NUM_OF
#define bcmolt_tm_sched_cfg_data_id_all_properties 0xFF
#define bcmolt_tm_sched_cfg_data_id_full_mask 0x6F

} bcmolt_tm_sched_cfg_data_id;



/** @} */

#endif
