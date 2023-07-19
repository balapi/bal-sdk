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

#ifndef BCMOLT_API_MODEL_API_STRUCTS_H_
#define BCMOLT_API_MODEL_API_STRUCTS_H_

#include <bcmos_system.h>
#include <bcmolt_system_types.h>
#include "bcmolt_msg.h"
#include "bcmolt_api_model_supporting_structs.h"
#include "bcmolt_api_model_supporting_enums.h"
#include "bcmolt_api_model_supporting_typedefs.h"

/** \addtogroup object_model
 * @{
 */

/** access control: key */
typedef struct
{
    bcmolt_access_control_id id; /**< The ID of the ACL object instance being referenced */
} bcmolt_access_control_key;

/* Constants associated with bcmolt_access_control_key. */
#define BCMOLT_ACCESS_CONTROL_KEY_ID_MIN (bcmolt_access_control_id)0U

/** access control: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_classifier classifier; /**< The classifier for this access control instance */
    uint16_t priority; /**< Priority for this access control instance
    Higher value has precedence over lower value. */
    bcmolt_access_control_fwd_action forwarding_action; /**< The action associated with this access control instance */
    bcmolt_access_control_pkt_modifier modifier_action; /**< config for modifying packet headers for vlan tags, dscp etc */
    bcmolt_config_state state; /**< State. */
    bcmolt_control_state statistics_control; /**< statistics control. */
    bcmolt_cookie cookie; /**< Opaque application cookie associated with this access control instance */
    bcmolt_intf_ref_list_u8 interface_refs; /**< list of associated interfaces. */
    bcmolt_policer_action policer_action; /**< policer action. */
    bcmolt_mirror_action mirror_action; /**< mirror ingress pkts action. */
    bcmolt_stage stage; /**< stage (ingress or egress) where the access control instance is configured */
} bcmolt_access_control_cfg_data;

/* Constants associated with bcmolt_access_control_cfg_data. */
#define BCMOLT_ACCESS_CONTROL_CFG_DATA_PRESENCE_MASK_ALL 0x000000000007DA70ULL
#define BCMOLT_ACCESS_CONTROL_CFG_DATA_PRIORITY_DEFAULT 0U
#define BCMOLT_ACCESS_CONTROL_CFG_DATA_PRIORITY_MIN 0U
#define BCMOLT_ACCESS_CONTROL_CFG_DATA_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED
#define BCMOLT_ACCESS_CONTROL_CFG_DATA_STAGE_DEFAULT BCMOLT_STAGE_INGRESS

/** Transport message definition for "cfg" group of "access_control" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key. */
    bcmolt_access_control_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_access_control_cfg;

/** Multi-object message definition for "cfg" group of "access_control" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key (can include wildcards). */
    bcmolt_access_control_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_access_control_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_access_control_cfg *responses; /**< Responses to the last API call. */

    bcmolt_access_control_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_access_control_multi_cfg;

/** access control: stats */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t packets; /**< pkts processed */
    uint64_t bytes; /**< bytes processed */
    bcmolt_arr_u64_4 policer_packets_passed_ukmb; /**< passed pkts on policer by traffic type - uu,ku,mc,bc */
    bcmolt_arr_u64_4 policer_packets_dropped_ukmb; /**< dropped pkts on policer by traffic type - uu,ku,mc,bc */
    bcmolt_arr_u64_4 policer_bytes_passed_ukmb; /**< passed bytes on policer by traffic type - uu,ku,mc,bc */
    bcmolt_arr_u64_4 policer_bytes_dropped_ukmb; /**< dropped bytes on policer by traffic type - uu,ku,mc,bc */
} bcmolt_access_control_stats_data;

/* Constants associated with bcmolt_access_control_stats_data. */
#define BCMOLT_ACCESS_CONTROL_STATS_DATA_PRESENCE_MASK_ALL 0x000000000000003FULL
#define BCMOLT_ACCESS_CONTROL_STATS_DATA_POLICER_PACKETS_PASSED_UKMB_LENGTH 4
#define BCMOLT_ACCESS_CONTROL_STATS_DATA_POLICER_PACKETS_DROPPED_UKMB_LENGTH 4
#define BCMOLT_ACCESS_CONTROL_STATS_DATA_POLICER_BYTES_PASSED_UKMB_LENGTH 4
#define BCMOLT_ACCESS_CONTROL_STATS_DATA_POLICER_BYTES_DROPPED_UKMB_LENGTH 4

/** Transport message definition for "stats" group of "access_control" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key. */
    bcmolt_access_control_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_access_control_stats;

/** Multi-object message definition for "stats" group of "access_control" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key (can include wildcards). */
    bcmolt_access_control_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_access_control_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_access_control_stats *responses; /**< Responses to the last API call. */

    bcmolt_access_control_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_access_control_multi_stats;

/** access control: receive_eth_packet */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_intf_ref interface_ref; /**< Interface Reference */
    bcmolt_service_port_id svc_port_id; /**< GEM or LLID of received packet */
    uint8_t lag_member_nni_id; /**< LAG member NNI Interface Id */
    bcmolt_bin_str buffer; /**< Buffer. */
} bcmolt_access_control_receive_eth_packet_data;

/* Constants associated with bcmolt_access_control_receive_eth_packet_data. */
#define BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_PRESENCE_MASK_ALL 0x000000000000001EULL

/** Transport message definition for "receive_eth_packet" group of "access_control" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key. */
    bcmolt_access_control_receive_eth_packet_data data; /**< All properties that must be set by the user. */
} bcmolt_access_control_receive_eth_packet;

/** access control: update interface reference */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_members_update_command command; /**< command. */
    bcmolt_intf_ref_list_u8 interface_ref_list; /**< intf list could be Ingress or Egress ports depending on stage acc ctrl instance is configured for */
} bcmolt_access_control_interfaces_update_data;

/* Constants associated with bcmolt_access_control_interfaces_update_data. */
#define BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "interfaces_update" group of "access_control" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key. */
    bcmolt_access_control_interfaces_update_data data; /**< All properties that must be set by the user. */
} bcmolt_access_control_interfaces_update;

/** access control: Stats Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config packets; /**< pkts processed */
    bcmolt_stat_alarm_config bytes; /**< bytes processed */
    bcmolt_stat_alarm_config policer_packets_passed_ukmb; /**< passed pkts on policer by traffic type - uu,ku,mc,bc */
    bcmolt_stat_alarm_config policer_packets_dropped_ukmb; /**< dropped pkts on policer by traffic type - uu,ku,mc,bc */
    bcmolt_stat_alarm_config policer_bytes_passed_ukmb; /**< passed bytes on policer by traffic type - uu,ku,mc,bc */
    bcmolt_stat_alarm_config policer_bytes_dropped_ukmb; /**< dropped bytes on policer by traffic type - uu,ku,mc,bc */
} bcmolt_access_control_stats_cfg_data;

/* Constants associated with bcmolt_access_control_stats_cfg_data. */
#define BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000003FULL

/** Transport message definition for "stats_cfg" group of "access_control" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key. */
    bcmolt_access_control_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_access_control_stats_cfg;

/** access control: Stats Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_access_control_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_access_control_stats_alarm_raised_data;

/* Constants associated with bcmolt_access_control_stats_alarm_raised_data. */
#define BCMOLT_ACCESS_CONTROL_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_raised" group of "access_control" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key. */
    bcmolt_access_control_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_access_control_stats_alarm_raised;

/** access control: Stats Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_access_control_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_access_control_stats_alarm_cleared_data;

/* Constants associated with bcmolt_access_control_stats_alarm_cleared_data. */
#define BCMOLT_ACCESS_CONTROL_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_cleared" group of "access_control" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key. */
    bcmolt_access_control_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_access_control_stats_alarm_cleared;

/** access control: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool receive_eth_packet; /**< If true, indications of type "receive_eth_packet" will be generated. */
    bcmos_bool stats_alarm_cleared; /**< If true, indications of type "stats_alarm_cleared" will be generated. */
    bcmos_bool stats_alarm_raised; /**< If true, indications of type "stats_alarm_raised" will be generated. */
} bcmolt_access_control_auto_cfg_data;

/* Constants associated with bcmolt_access_control_auto_cfg_data. */
#define BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "auto_cfg" group of "access_control" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_access_control_key key; /**< Object key. */
    bcmolt_access_control_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_access_control_auto_cfg;

/** BAL System Globals: key */
typedef struct
{
    bcmolt_bal_system_id id; /**< id. */
} bcmolt_bal_system_key;

/* Constants associated with bcmolt_bal_system_key. */
#define BCMOLT_BAL_SYSTEM_KEY_ID_DEFAULT (bcmolt_bal_system_id)0

/** BAL System Globals: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state config_state; /**< Configuration State. */
    bcmolt_lag_global_parms lag_parms; /**< LAG Global Params. */
    bcmolt_host_port_params host_port; /**< host port. */
} bcmolt_bal_system_cfg_data;

/* Constants associated with bcmolt_bal_system_cfg_data. */
#define BCMOLT_BAL_SYSTEM_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000070ULL
#define BCMOLT_BAL_SYSTEM_CFG_DATA_CONFIG_STATE_DEFAULT BCMOLT_CONFIG_STATE_CONFIGURED

/** Transport message definition for "cfg" group of "bal_system" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_bal_system_key key; /**< Object key. */
    bcmolt_bal_system_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_bal_system_cfg;

/** Multi-object message definition for "cfg" group of "bal_system" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_bal_system_key key; /**< Object key (can include wildcards). */
    bcmolt_bal_system_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_bal_system_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_bal_system_cfg *responses; /**< Responses to the last API call. */

    bcmolt_bal_system_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_bal_system_multi_cfg;

/** Device: key */
typedef struct
{
    bcmolt_ldid device_id; /**< Device ID */
} bcmolt_device_key;

/** Device: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_system_mode system_mode; /**< System mode - this must be set by the host when initially provisioning the system.  Setting this also sets the "nni_speed" property, unless it is overridden. */
    uint32_t keepalive_interval; /**< Keepalive Interval in Seconds  (0 = Disable) */
    uint32_t keepalive_tolerance; /**< How many keepalive messages can be lost before triggering a disconnect sequence */
    bcmolt_firmware_sw_version firmware_sw_version; /**< Firmware SW Version */
    bcmolt_chip_family chip_family; /**< Chip family */
    uint32_t chip_id; /**< Chip Id */
    bcmolt_device_chip_revision chip_revision; /**< Revision of the BCM68620 device. */
    uint32_t chip_voltage; /**< Chip voltage in mV */
    int32_t chip_temperature; /**< Current die temperature. */
    bcmolt_debug_device_cfg debug; /**< Device configuration debug parameters */
    bcmolt_ext_irq protection_switching_ext_irq; /**< Supported in BCM6862X only. The selected external IRQ for protection switching */
    bcmolt_indication_shaping indication_shaping; /**< Shaping / rate limiting for the indication channel. */
    bcmolt_uart_baudrate tod_uart_baudrate; /**< UART baud rate */
    bcmolt_itu_tod itu_tod; /**< ITU ToD configuration */
    bcmolt_ieee_8021_as_tod ieee_8021_as_tod; /**< 802.1AS (IEEE) ToD configuration */
    bcmolt_embedded_image_entry_list_u8_max_4 embedded_image_list; /**< List of all file images stored in the OLT. */
    bcmos_bool wd_enable; /**< In PCIe out of band management, this field is ignored.
    For in-band systems, the default is for the watchdog to be enabled.
    When enabled the Maple watchdog is patted periodically. */
    uint16_t wd_ip_traffic_timeout; /**< The units are seconds.
    
    The watchdog checks for IP traffic periodically.
    
    The watchdog IP traffic check default period is 5 minutes (300 seconds).
    
    The watchdog  IP traffic check period minimum has to be greater than the product
    of ka interval and (ka tolerance + 1).
    
    The minimum value of ka interval and ka tolerance is 0. In that case the minimum
    comm check period minimum is 5 seconds.
    
    If no IP traffic is received within the configured period. The watchdog will reset the Maple chip. */
    bcmolt_comm_mode comm_mode; /**< The communication mode being used. */
    bcmolt_pcie_conn_data pcie_conn_data; /**< Mirror of the PCIe connection parameters supplied in the initial connect operation. */
    bcmos_bool itu_multipon_dba_enable; /**< Enable Multi-PON DBA feature in ITU modes */
    bcmos_bool itu_low_latency_dba_enable; /**< Enable low latency DBA feature in ITU modes */
    bcmos_bool logger_enable; /**< Set to false to disable all logging in the system */
    bcmolt_inni_config inni_config; /**< INNI configuration */
    bcmolt_ras_ddr_usage_mode ras_ddr_mode; /**< RAS DDR Mode. */
    bcmos_bool itu_enable_inni_mux; /**< Enable INNI mux configuration on the fly */
    bcmolt_arr_ploam_filter_5 trap_gpon_ploam; /**< Trap gpon ploams according to ploam id */
    bcmolt_arr_ploam_filter_5 trap_xgpon_ploam; /**< Trap xgpon ploams according to ploam id */
    bcmos_bool debug_uart_port_swap; /**< If set to false (the default value) UART0 is used for logs/cli, UART1 for TOD. If set to true UART0 is used for TOD, UART1 for logs/cli. */
    bcmolt_inband_conn_data inband_conn_data; /**< Mirror of the in-band connection parameters supplied in the initial connect operation. */
    bcmolt_pon_ni inband_internal_nni; /**< Port number of the internal NNI port that is configured for in-band communication. */
} bcmolt_device_cfg_data;

/* Constants associated with bcmolt_device_cfg_data. */
#define BCMOLT_DEVICE_CFG_DATA_PRESENCE_MASK_ALL 0x0000007FF83F3EFFULL
#define BCMOLT_DEVICE_CFG_DATA_KEEPALIVE_INTERVAL_DEFAULT 5UL
#define BCMOLT_DEVICE_CFG_DATA_KEEPALIVE_INTERVAL_MAX 15UL
#define BCMOLT_DEVICE_CFG_DATA_KEEPALIVE_TOLERANCE_DEFAULT 3UL
#define BCMOLT_DEVICE_CFG_DATA_KEEPALIVE_TOLERANCE_MAX 5UL
#define BCMOLT_DEVICE_CFG_DATA_CHIP_FAMILY_DEFAULT BCMOLT_CHIP_FAMILY_UNKNOWN
#define BCMOLT_DEVICE_CFG_DATA_PROTECTION_SWITCHING_EXT_IRQ_DEFAULT BCMOLT_EXT_IRQ_UNCONFIGURED
#define BCMOLT_DEVICE_CFG_DATA_TOD_UART_BAUDRATE_DEFAULT BCMOLT_UART_BAUDRATE_UART_RATE_9600
#define BCMOLT_DEVICE_CFG_DATA_EMBEDDED_IMAGE_LIST_MIN_LENGTH 0
#define BCMOLT_DEVICE_CFG_DATA_EMBEDDED_IMAGE_LIST_MAX_LENGTH 4
#define BCMOLT_DEVICE_CFG_DATA_WD_ENABLE_DEFAULT BCMOS_TRUE
#define BCMOLT_DEVICE_CFG_DATA_WD_IP_TRAFFIC_TIMEOUT_DEFAULT 300U
#define BCMOLT_DEVICE_CFG_DATA_WD_IP_TRAFFIC_TIMEOUT_MIN 5U
#define BCMOLT_DEVICE_CFG_DATA_WD_IP_TRAFFIC_TIMEOUT_MAX 65535U
#define BCMOLT_DEVICE_CFG_DATA_ITU_MULTIPON_DBA_ENABLE_DEFAULT BCMOS_FALSE
#define BCMOLT_DEVICE_CFG_DATA_ITU_LOW_LATENCY_DBA_ENABLE_DEFAULT BCMOS_FALSE
#define BCMOLT_DEVICE_CFG_DATA_LOGGER_ENABLE_DEFAULT BCMOS_TRUE
#define BCMOLT_DEVICE_CFG_DATA_ITU_ENABLE_INNI_MUX_DEFAULT BCMOS_FALSE
#define BCMOLT_DEVICE_CFG_DATA_TRAP_GPON_PLOAM_LENGTH 5
#define BCMOLT_DEVICE_CFG_DATA_TRAP_XGPON_PLOAM_LENGTH 5
#define BCMOLT_DEVICE_CFG_DATA_DEBUG_UART_PORT_SWAP_DEFAULT BCMOS_FALSE
#define BCMOLT_DEVICE_CFG_DATA_INBAND_INTERNAL_NNI_DEFAULT (bcmolt_pon_ni)255

/** Transport message definition for "cfg" group of "device" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_device_cfg;

/** Multi-object message definition for "cfg" group of "device" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key (can include wildcards). */
    bcmolt_device_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_device_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_device_cfg *responses; /**< Responses to the last API call. */

    bcmolt_device_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_device_multi_cfg;

/** Device: Connect */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_system_mode system_mode; /**< System Mode. */
    bcmolt_comm_mode comm_mode; /**< Communication Mode. AKA Management Mode */
    bcmolt_pcie_conn_data pcie_conn_data; /**< If PCIe communications mode is selected, these parameters may be set. */
    bcmolt_inband_conn_data inband_conn_data; /**< If InBand Communication mode is selected, these parameters must be set. */
    bcmos_bool itu_multipon_dba_enable; /**< Enable Multi-PON DBA feature in ITU modes */
    bcmolt_inni_config inni_config; /**< INNI configuration */
    bcmolt_ras_ddr_usage_mode ras_ddr_mode; /**< If ITU PON system is used, this parameter states RAS DDR usage mode. For EPON system modes should be set to no_ddr value. */
    bcmolt_ddr_test_mode ddr_test_mode; /**< DDR test mode */
    bcmos_bool itu_change_inni_mux_enable; /**< Enable changing INNI mux on the fly */
    bcmos_bool itu_low_latency_dba_enable; /**< Enable low latency DBA feature in ITU modes */
    bcmos_bool debug_uart_port_swap; /**< Optional paramter. Default value is false. Set to true to use UART1 for logs/CLI, UART0 for TOD */
} bcmolt_device_connect_data;

/* Constants associated with bcmolt_device_connect_data. */
#define BCMOLT_DEVICE_CONNECT_DATA_PRESENCE_MASK_ALL 0x0000000000000FEFULL
#define BCMOLT_DEVICE_CONNECT_DATA_COMM_MODE_DEFAULT BCMOLT_COMM_MODE_PCIE
#define BCMOLT_DEVICE_CONNECT_DATA_ITU_MULTIPON_DBA_ENABLE_DEFAULT BCMOS_FALSE
#define BCMOLT_DEVICE_CONNECT_DATA_RAS_DDR_MODE_DEFAULT BCMOLT_RAS_DDR_USAGE_MODE_FOUR_DDRS
#define BCMOLT_DEVICE_CONNECT_DATA_DDR_TEST_MODE_DEFAULT BCMOLT_DDR_TEST_MODE_NO_TEST
#define BCMOLT_DEVICE_CONNECT_DATA_ITU_CHANGE_INNI_MUX_ENABLE_DEFAULT BCMOS_FALSE
#define BCMOLT_DEVICE_CONNECT_DATA_ITU_LOW_LATENCY_DBA_ENABLE_DEFAULT BCMOS_FALSE
#define BCMOLT_DEVICE_CONNECT_DATA_DEBUG_UART_PORT_SWAP_DEFAULT BCMOS_FALSE

/** Transport message definition for "connect" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_connect_data data; /**< All properties that must be set by the user. */
} bcmolt_device_connect;

/** Transport message definition for "disconnect" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
} bcmolt_device_disconnect;

/** Transport message definition for "reset" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
} bcmolt_device_reset;

/** Device: Host Keep Alive (Internal) */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t sequence_number; /**< sequence number */
    uint32_t time_stamp; /**< time stamp */
} bcmolt_device_host_keep_alive_data;

/* Constants associated with bcmolt_device_host_keep_alive_data. */
#define BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "host_keep_alive" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_host_keep_alive_data data; /**< All properties that must be set by the user. */
} bcmolt_device_host_keep_alive;

/** Transport message definition for "sw_upgrade_activate" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
} bcmolt_device_sw_upgrade_activate;

/** Device: Set ToD String for 802.1AS */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_str_256 tod_string; /**< The current ToD string to be used for clock transport (EPON only) */
} bcmolt_device_set_8021_as_tod_string_data;

/* Constants associated with bcmolt_device_set_8021_as_tod_string_data. */
#define BCMOLT_DEVICE_SET_8021_AS_TOD_STRING_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "set_8021_as_tod_string" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_set_8021_as_tod_string_data data; /**< All properties that must be set by the user. */
} bcmolt_device_set_8021_as_tod_string;

/** Device: Start Image Transfer Operation */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_device_image_type image_type; /**< File type. */
    uint32_t image_size; /**< Size of the file image. Ignored for RRQ operation */
    uint32_t crc32; /**< CRC32 checksum of the entire file image */
    bcmolt_str_64 image_name; /**< Name of the file image. Null-terminated string. This is required for the DPoE ONU only.  DPoE requires the write request OAM contains the name of the file */
} bcmolt_device_image_transfer_start_data;

/* Constants associated with bcmolt_device_image_transfer_start_data. */
#define BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "image_transfer_start" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_image_transfer_start_data data; /**< All properties that must be set by the user. */
} bcmolt_device_image_transfer_start;

/** Device: Image Data Transfer Operation (Internal) */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t block_number; /**< Block number. */
    bcmos_bool more_data; /**< Specifies that there are more data to come */
    bcmolt_bin_str data; /**< Data. */
} bcmolt_device_image_transfer_data_data;

/* Constants associated with bcmolt_device_image_transfer_data_data. */
#define BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "image_transfer_data" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_image_transfer_data_data data; /**< All properties that must be set by the user. */
} bcmolt_device_image_transfer_data;

/** Device: Run DDR Test */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool cpu; /**< Whether or not to test the CPU DDR */
    bcmos_bool ras_0; /**< Whether or not to test RAS 0 DDR */
    bcmos_bool ras_1; /**< Whether or not to test RAS 1 DDR */
} bcmolt_device_run_ddr_test_data;

/* Constants associated with bcmolt_device_run_ddr_test_data. */
#define BCMOLT_DEVICE_RUN_DDR_TEST_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "run_ddr_test" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_run_ddr_test_data data; /**< All properties that must be set by the user. */
} bcmolt_device_run_ddr_test;

/** Device: Device Ready */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_firmware_sw_version firmware_sw_version; /**< Software Version. */
    bcmolt_system_mode system_mode; /**< System Mode. */
    uint32_t keepalive_interval; /**< Keepalive Interval in Seconds (0 = Disable) */
    uint32_t keepalive_tolerance; /**< How many keepalive messages can be lost before triggering a disconnect sequence */
    bcmos_bool standalone; /**< Standalone. */
    bcmolt_chip_family chip_family; /**< Chip Family. */
} bcmolt_device_device_ready_data;

/* Constants associated with bcmolt_device_device_ready_data. */
#define BCMOLT_DEVICE_DEVICE_READY_DATA_PRESENCE_MASK_ALL 0x000000000000003FULL
#define BCMOLT_DEVICE_DEVICE_READY_DATA_KEEPALIVE_INTERVAL_DEFAULT 5UL
#define BCMOLT_DEVICE_DEVICE_READY_DATA_KEEPALIVE_INTERVAL_MAX 15UL
#define BCMOLT_DEVICE_DEVICE_READY_DATA_KEEPALIVE_TOLERANCE_DEFAULT 3UL

/** Transport message definition for "device_ready" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_device_ready_data data; /**< All properties that must be set by the user. */
} bcmolt_device_device_ready;

/** Transport message definition for "connection_established" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
} bcmolt_device_connection_established;

/** Device: Device Keep Alive */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t sequence_number; /**< sequence number */
    uint32_t time_stamp; /**< time stamp */
    uint32_t keepalive_interval; /**< Keepalive Interval. */
    uint32_t keepalive_tolerance; /**< Keepalive Tolerance. */
} bcmolt_device_device_keep_alive_data;

/* Constants associated with bcmolt_device_device_keep_alive_data. */
#define BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "device_keep_alive" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_device_keep_alive_data data; /**< All properties that must be set by the user. */
} bcmolt_device_device_keep_alive;

/** Device: Connection Failure */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_host_connection_fail_reason reason; /**< Connection fail reason. */
    bcmos_bool device_in_reset; /**< Whether or not the device was left in reset */
    bcmolt_str_256 error_text; /**< Error string associated with the failure response. */
} bcmolt_device_connection_failure_data;

/* Constants associated with bcmolt_device_connection_failure_data. */
#define BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "connection_failure" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_connection_failure_data data; /**< All properties that must be set by the user. */
} bcmolt_device_connection_failure;

/** Device: Connection Complete */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool standalone; /**< If true, the device was previously running in standalone mode before this connection was established. If false, the device was booted from reset with new firmware, etc. */
    bcmolt_system_mode system_mode; /**< System Mode. */
} bcmolt_device_connection_complete_data;

/* Constants associated with bcmolt_device_connection_complete_data. */
#define BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "connection_complete" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_connection_complete_data data; /**< All properties that must be set by the user. */
} bcmolt_device_connection_complete;

/** Device: Disconnection Complete */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_device_disconnect_reason reason; /**< Device disconnect reason */
} bcmolt_device_disconnection_complete_data;

/* Constants associated with bcmolt_device_disconnection_complete_data. */
#define BCMOLT_DEVICE_DISCONNECTION_COMPLETE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "disconnection_complete" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_disconnection_complete_data data; /**< All properties that must be set by the user. */
} bcmolt_device_disconnection_complete;

/** Device: sw error */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_str_100 task_name; /**< task name. */
    bcmolt_str_100 file_name; /**< file name. */
    uint32_t line_number; /**< line number. */
    uint8_t pon_ni; /**< pon_ni. */
} bcmolt_device_sw_error_data;

/* Constants associated with bcmolt_device_sw_error_data. */
#define BCMOLT_DEVICE_SW_ERROR_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "sw_error" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_sw_error_data data; /**< All properties that must be set by the user. */
} bcmolt_device_sw_error;

/** Device: sw exception */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t cpu_id; /**< CPU ID. */
    bcmolt_str_2000 text; /**< text. */
} bcmolt_device_sw_exception_data;

/* Constants associated with bcmolt_device_sw_exception_data. */
#define BCMOLT_DEVICE_SW_EXCEPTION_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "sw_exception" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_sw_exception_data data; /**< All properties that must be set by the user. */
} bcmolt_device_sw_exception;

/** Device: Image Transfer Complete */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_device_image_type image_type; /**< Image type. */
    uint32_t block_number; /**< Block number. */
    bcmolt_image_transfer_status status; /**< Image transfer status. */
} bcmolt_device_image_transfer_complete_data;

/* Constants associated with bcmolt_device_image_transfer_complete_data. */
#define BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "image_transfer_complete" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_image_transfer_complete_data data; /**< All properties that must be set by the user. */
} bcmolt_device_image_transfer_complete;

/** Device: DDR Test Complete */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_ddr_test_completed ddr_test; /**< Results of the DDR Test */
} bcmolt_device_ddr_test_complete_data;

/* Constants associated with bcmolt_device_ddr_test_complete_data. */
#define BCMOLT_DEVICE_DDR_TEST_COMPLETE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "ddr_test_complete" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_ddr_test_complete_data data; /**< All properties that must be set by the user. */
} bcmolt_device_ddr_test_complete;

/** Device: Software Health Check Failure */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_str_100 module_name; /**< Name of the unresponsive module. */
    uint16_t module_id; /**< The module ID of the unresponsive module. */
    bcmolt_status status; /**< status. */
} bcmolt_device_sw_health_check_failure_data;

/* Constants associated with bcmolt_device_sw_health_check_failure_data. */
#define BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_STATUS_DEFAULT BCMOLT_STATUS_OFF

/** Transport message definition for "sw_health_check_failure" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_sw_health_check_failure_data data; /**< All properties that must be set by the user. */
} bcmolt_device_sw_health_check_failure;

/** Device: Change_configuration_completed INNI mux */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_inni_mux mux; /**< mux. */
    bcmolt_nni_connection nni_connection; /**< nni_connection. */
} bcmolt_device_change_inni_mux_data;

/* Constants associated with bcmolt_device_change_inni_mux_data. */
#define BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "change_inni_mux" group of "device" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_change_inni_mux_data data; /**< All properties that must be set by the user. */
} bcmolt_device_change_inni_mux;

/** Device: INNI mux configuration completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_inni_mux new_mux; /**< new_mux. */
    bcmolt_result status; /**< status. */
} bcmolt_device_inni_mux_configuration_completed_data;

/* Constants associated with bcmolt_device_inni_mux_configuration_completed_data. */
#define BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "inni_mux_configuration_completed" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_inni_mux_configuration_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_device_inni_mux_configuration_completed;

/** Device: tod calibration done */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t pon_ni; /**< pon_ni. */
    bcmolt_result result; /**< result. */
    bcmolt_tod_calibration_fail_reason fail_reason; /**< fail reason. */
} bcmolt_device_tod_calibration_done_data;

/* Constants associated with bcmolt_device_tod_calibration_done_data. */
#define BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "tod_calibration_done" group of "device" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_tod_calibration_done_data data; /**< All properties that must be set by the user. */
} bcmolt_device_tod_calibration_done;

/** Device: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool connection_complete; /**< If true, indications of type "connection_complete" will be generated. */
    bcmos_bool connection_established; /**< If true, indications of type "connection_established" will be generated. */
    bcmos_bool connection_failure; /**< If true, indications of type "connection_failure" will be generated. */
    bcmos_bool ddr_test_complete; /**< If true, indications of type "ddr_test_complete" will be generated. */
    bcmos_bool device_keep_alive; /**< If true, indications of type "device_keep_alive" will be generated. */
    bcmos_bool device_ready; /**< If true, indications of type "device_ready" will be generated. */
    bcmos_bool disconnection_complete; /**< If true, indications of type "disconnection_complete" will be generated. */
    bcmos_bool image_transfer_complete; /**< If true, indications of type "image_transfer_complete" will be generated. */
    bcmos_bool inni_mux_configuration_completed; /**< If true, indications of type "inni_mux_configuration_completed" will be generated. */
    bcmos_bool sw_error; /**< If true, indications of type "sw_error" will be generated. */
    bcmos_bool sw_exception; /**< If true, indications of type "sw_exception" will be generated. */
    bcmos_bool sw_health_check_failure; /**< If true, indications of type "sw_health_check_failure" will be generated. */
    bcmos_bool tod_calibration_done; /**< If true, indications of type "tod_calibration_done" will be generated. */
} bcmolt_device_auto_cfg_data;

/* Constants associated with bcmolt_device_auto_cfg_data. */
#define BCMOLT_DEVICE_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000001FFFULL

/** Transport message definition for "auto_cfg" group of "device" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_device_key key; /**< Object key. */
    bcmolt_device_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_device_auto_cfg;

/** ERPS Interface: key */
typedef struct
{
    bcmolt_erps_id id; /**< ID. */
} bcmolt_erps_interface_key;

/** ERPS Interface: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state state; /**< state. */
    bcmolt_intf_ref east_port; /**< NNI or LAG interface Reference */
    bcmolt_intf_ref west_port; /**< NNI or LAG interface Reference and Id */
    bcmolt_vlan_id control_vlan_id; /**< Optional VLAN ID that carrys ERPS R-APS packets on the ring. */
    bcmolt_ring_port_state east_port_state; /**< The current state of the east port. For details about the blocked state see the east port detailed state. */
    bcmolt_ring_port_state west_port_state; /**< The current state of the west port. For details about the blocked state see the west port detailed state. */
    bcmolt_arr_intf_ref_16 sub_port_list; /**< List of provisioned sub_ports on this erps interface */
    bcmolt_ring_port_detailed_state east_port_detailed_state; /**< The current state of both tx and rx for the east port. */
    bcmolt_ring_port_detailed_state west_port_detailed_state; /**< The current state of both tx and rx for the west port. */
} bcmolt_erps_interface_cfg_data;

/* Constants associated with bcmolt_erps_interface_cfg_data. */
#define BCMOLT_ERPS_INTERFACE_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000EE07ULL
#define BCMOLT_ERPS_INTERFACE_CFG_DATA_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED
#define BCMOLT_ERPS_INTERFACE_CFG_DATA_CONTROL_VLAN_ID_DEFAULT (bcmolt_vlan_id)65535U
#define BCMOLT_ERPS_INTERFACE_CFG_DATA_CONTROL_VLAN_ID_MAX (bcmolt_vlan_id)4094U
#define BCMOLT_ERPS_INTERFACE_CFG_DATA_SUB_PORT_LIST_LENGTH 16

/** Transport message definition for "cfg" group of "erps_interface" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_erps_interface_key key; /**< Object key. */
    bcmolt_erps_interface_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_erps_interface_cfg;

/** Multi-object message definition for "cfg" group of "erps_interface" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_erps_interface_key key; /**< Object key (can include wildcards). */
    bcmolt_erps_interface_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_erps_interface_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_erps_interface_cfg *responses; /**< Responses to the last API call. */

    bcmolt_erps_interface_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_erps_interface_multi_cfg;

/** ERPS Interface: Set Ring Port Control */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_erps_control command; /**< command. */
    bcmolt_ring_port port; /**< port. */
} bcmolt_erps_interface_set_ring_port_control_data;

/* Constants associated with bcmolt_erps_interface_set_ring_port_control_data. */
#define BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "set_ring_port_control" group of "erps_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_erps_interface_key key; /**< Object key. */
    bcmolt_erps_interface_set_ring_port_control_data data; /**< All properties that must be set by the user. */
} bcmolt_erps_interface_set_ring_port_control;

/** ERPS Interface: Ring Port Control */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_ring_port port_id; /**< port id. */
    bcmolt_erps_control command; /**< Reflects current state of the requested Port */
    bcmolt_ring_port_state port_state; /**< The resulting state of the port after the command. For details on the blocked state see the detailed port state. */
    bcmolt_result result; /**< Result of operation, success or fail. If fail then the ind.hdr.hdr.err will contain the return code.
    The return code is of type bcmos_errno. */
    bcmolt_ring_port_detailed_state port_detailed_state; /**< The resulting state for both tx and rx of the port after the command. */
} bcmolt_erps_interface_ring_port_control_data;

/* Constants associated with bcmolt_erps_interface_ring_port_control_data. */
#define BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL

/** Transport message definition for "ring_port_control" group of "erps_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_erps_interface_key key; /**< Object key. */
    bcmolt_erps_interface_ring_port_control_data data; /**< All properties that must be set by the user. */
} bcmolt_erps_interface_ring_port_control;

/** ERPS Interface: set erps interface option  */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_ring_port port; /**< Port to be modified. */
    bcmolt_intf_opt intf_opt; /**< Port interface Option. */
} bcmolt_erps_interface_set_intf_opt_data;

/* Constants associated with bcmolt_erps_interface_set_intf_opt_data. */
#define BCMOLT_ERPS_INTERFACE_SET_INTF_OPT_DATA_PRESENCE_MASK_ALL 0x000000000000000CULL

/** Transport message definition for "set_intf_opt" group of "erps_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_erps_interface_key key; /**< Object key. */
    bcmolt_erps_interface_set_intf_opt_data data; /**< All properties that must be set by the user. */
} bcmolt_erps_interface_set_intf_opt;

/** ERPS Interface: erps port update */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_port_command command; /**< Update an ERPS port. */
    bcmolt_erps_port port; /**< Port to add or remove. */
    bcmolt_intf_ref intf_ref; /**< Port interface Reference. */
} bcmolt_erps_interface_port_update_data;

/* Constants associated with bcmolt_erps_interface_port_update_data. */
#define BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_PRESENCE_MASK_ALL 0x000000000000000DULL

/** Transport message definition for "port_update" group of "erps_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_erps_interface_key key; /**< Object key. */
    bcmolt_erps_interface_port_update_data data; /**< All properties that must be set by the user. */
} bcmolt_erps_interface_port_update;

/** ERPS Interface: erps port intf_opt modify completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_ring_port port; /**< ERPS Port just updated. */
    bcmolt_result result; /**< Result of command pass/fail. */
} bcmolt_erps_interface_set_intf_opt_complete_data;

/* Constants associated with bcmolt_erps_interface_set_intf_opt_complete_data. */
#define BCMOLT_ERPS_INTERFACE_SET_INTF_OPT_COMPLETE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "set_intf_opt_complete" group of "erps_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_erps_interface_key key; /**< Object key. */
    bcmolt_erps_interface_set_intf_opt_complete_data data; /**< All properties that must be set by the user. */
} bcmolt_erps_interface_set_intf_opt_complete;

/** ERPS Interface: erps port update completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_port_command command; /**< Command just executed. */
    bcmolt_erps_port port; /**< ERPS Port just updated. */
    bcmolt_intf_ref intf_ref; /**< Modified Port. */
    bcmolt_result result; /**< Result of command pass/fail. */
} bcmolt_erps_interface_port_update_complete_data;

/* Constants associated with bcmolt_erps_interface_port_update_complete_data. */
#define BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "port_update_complete" group of "erps_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_erps_interface_key key; /**< Object key. */
    bcmolt_erps_interface_port_update_complete_data data; /**< All properties that must be set by the user. */
} bcmolt_erps_interface_port_update_complete;

/** ERPS Interface: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool port_update_complete; /**< If true, indications of type "port_update_complete" will be generated. */
    bcmos_bool ring_port_control; /**< If true, indications of type "ring_port_control" will be generated. */
    bcmos_bool set_intf_opt_complete; /**< If true, indications of type "set_intf_opt_complete" will be generated. */
} bcmolt_erps_interface_auto_cfg_data;

/* Constants associated with bcmolt_erps_interface_auto_cfg_data. */
#define BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "auto_cfg" group of "erps_interface" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_erps_interface_key key; /**< Object key. */
    bcmolt_erps_interface_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_erps_interface_auto_cfg;

/** Ethernet OAM: key */
typedef struct
{
    bcmolt_eth_oam_id id; /**< id. */
} bcmolt_eth_oam_key;

/* Constants associated with bcmolt_eth_oam_key. */
#define BCMOLT_ETH_OAM_KEY_ID_DEFAULT (bcmolt_eth_oam_id)0
#define BCMOLT_ETH_OAM_KEY_ID_MIN (bcmolt_eth_oam_id)0
#define BCMOLT_ETH_OAM_KEY_ID_MAX (bcmolt_eth_oam_id)127

/** Ethernet OAM: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state state; /**< Config State. */
    bcmolt_intf_ref intf_ref; /**< NNI port # */
    bcmolt_local_mep local_mep; /**< Tx MEP config */
    bcmolt_remote_mep remote_mep; /**< Rx MEP config */
    bcmolt_meg_cfg meg; /**< Maintenance Entity Group config */
    bcmos_mac_address source_mac; /**< Source Mac - for Tx CCMs */
    bcmos_mac_address dest_mac; /**< Dest Mac - for Rx and Tx CCMs. */
    bcmolt_pkt_tag_type pkt_tag_type; /**< Number of vlan tags in packet, double or single tagged. */
    bcmolt_vlan_id o_vid; /**< Outer VLAN ID. */
    uint8_t o_pbits; /**< Outer VLAN Pbits. */
    uint16_t o_tpid; /**< Outer VLAN TPID. */
    bcmolt_vlan_id i_vid; /**< Inner VLAN ID, only if pkt_tag_type is double. */
    uint8_t i_pbits; /**< Inner VLAN Pbits, only if pkt_tag_type is double. */
    uint16_t i_tpid; /**< Inner VLAN TPID, only if pkt_tag_type is double. */
} bcmolt_eth_oam_cfg_data;

/* Constants associated with bcmolt_eth_oam_cfg_data. */
#define BCMOLT_ETH_OAM_CFG_DATA_PRESENCE_MASK_ALL 0x000000000003FF27ULL
#define BCMOLT_ETH_OAM_CFG_DATA_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED
#define BCMOLT_ETH_OAM_CFG_DATA_PKT_TAG_TYPE_DEFAULT BCMOLT_PKT_TAG_TYPE_SINGLE_TAG
#define BCMOLT_ETH_OAM_CFG_DATA_O_VID_DEFAULT (bcmolt_vlan_id)0U
#define BCMOLT_ETH_OAM_CFG_DATA_O_VID_MAX (bcmolt_vlan_id)4094U
#define BCMOLT_ETH_OAM_CFG_DATA_O_PBITS_DEFAULT 7
#define BCMOLT_ETH_OAM_CFG_DATA_O_PBITS_MIN 0
#define BCMOLT_ETH_OAM_CFG_DATA_O_PBITS_MAX 7
#define BCMOLT_ETH_OAM_CFG_DATA_O_TPID_DEFAULT 0x8100
#define BCMOLT_ETH_OAM_CFG_DATA_I_VID_DEFAULT (bcmolt_vlan_id)0U
#define BCMOLT_ETH_OAM_CFG_DATA_I_VID_MAX (bcmolt_vlan_id)4094U
#define BCMOLT_ETH_OAM_CFG_DATA_I_PBITS_DEFAULT 0
#define BCMOLT_ETH_OAM_CFG_DATA_I_PBITS_MIN 0
#define BCMOLT_ETH_OAM_CFG_DATA_I_PBITS_MAX 7
#define BCMOLT_ETH_OAM_CFG_DATA_I_TPID_DEFAULT 0U

/** Transport message definition for "cfg" group of "eth_oam" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key. */
    bcmolt_eth_oam_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_eth_oam_cfg;

/** Multi-object message definition for "cfg" group of "eth_oam" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key (can include wildcards). */
    bcmolt_eth_oam_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_eth_oam_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_eth_oam_cfg *responses; /**< Responses to the last API call. */

    bcmolt_eth_oam_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_eth_oam_multi_cfg;

/** Ethernet OAM: CFM CCM Event */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_ccm_event event; /**< Received CCM Event */
} bcmolt_eth_oam_ccm_event_data;

/* Constants associated with bcmolt_eth_oam_ccm_event_data. */
#define BCMOLT_ETH_OAM_CCM_EVENT_DATA_PRESENCE_MASK_ALL 0x0000000000000002ULL

/** Transport message definition for "ccm_event" group of "eth_oam" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key. */
    bcmolt_eth_oam_ccm_event_data data; /**< All properties that must be set by the user. */
} bcmolt_eth_oam_ccm_event;

/** Ethernet OAM: stats */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t ccm_tx_count; /**< CCM Tx Count. */
    uint64_t ccm_rx_count; /**< CCM Rx Count. */
} bcmolt_eth_oam_stats_data;

/* Constants associated with bcmolt_eth_oam_stats_data. */
#define BCMOLT_ETH_OAM_STATS_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "stats" group of "eth_oam" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key. */
    bcmolt_eth_oam_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_eth_oam_stats;

/** Multi-object message definition for "stats" group of "eth_oam" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key (can include wildcards). */
    bcmolt_eth_oam_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_eth_oam_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_eth_oam_stats *responses; /**< Responses to the last API call. */

    bcmolt_eth_oam_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_eth_oam_multi_stats;

/** Ethernet OAM: Set MEP Control State */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_mep_type type; /**< MEP Type. */
    bcmolt_control_state state; /**< MEP Control State. */
} bcmolt_eth_oam_set_mep_state_data;

/* Constants associated with bcmolt_eth_oam_set_mep_state_data. */
#define BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_TYPE_DEFAULT BCMOLT_MEP_TYPE_MEP
#define BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_STATE_DEFAULT BCMOLT_CONTROL_STATE_ENABLE

/** Transport message definition for "set_mep_state" group of "eth_oam" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key. */
    bcmolt_eth_oam_set_mep_state_data data; /**< All properties that must be set by the user. */
} bcmolt_eth_oam_set_mep_state;

/** Ethernet OAM: State Change */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< Command Result. */
    bcmolt_control_state old_state; /**< Old State. */
    bcmolt_control_state new_state; /**< New State. */
} bcmolt_eth_oam_state_change_data;

/* Constants associated with bcmolt_eth_oam_state_change_data. */
#define BCMOLT_ETH_OAM_STATE_CHANGE_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "state_change" group of "eth_oam" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key. */
    bcmolt_eth_oam_state_change_data data; /**< All properties that must be set by the user. */
} bcmolt_eth_oam_state_change;

/** Ethernet OAM: Stats Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config ccm_tx_count; /**< CCM Tx Count. */
    bcmolt_stat_alarm_config ccm_rx_count; /**< CCM Rx Count. */
} bcmolt_eth_oam_stats_cfg_data;

/* Constants associated with bcmolt_eth_oam_stats_cfg_data. */
#define BCMOLT_ETH_OAM_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "stats_cfg" group of "eth_oam" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key. */
    bcmolt_eth_oam_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_eth_oam_stats_cfg;

/** Ethernet OAM: Stats Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_eth_oam_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_eth_oam_stats_alarm_raised_data;

/* Constants associated with bcmolt_eth_oam_stats_alarm_raised_data. */
#define BCMOLT_ETH_OAM_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_raised" group of "eth_oam" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key. */
    bcmolt_eth_oam_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_eth_oam_stats_alarm_raised;

/** Ethernet OAM: Stats Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_eth_oam_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_eth_oam_stats_alarm_cleared_data;

/* Constants associated with bcmolt_eth_oam_stats_alarm_cleared_data. */
#define BCMOLT_ETH_OAM_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_cleared" group of "eth_oam" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key. */
    bcmolt_eth_oam_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_eth_oam_stats_alarm_cleared;

/** Ethernet OAM: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool ccm_event; /**< If true, indications of type "ccm_event" will be generated. */
    bcmos_bool state_change; /**< If true, indications of type "state_change" will be generated. */
    bcmos_bool stats_alarm_cleared; /**< If true, indications of type "stats_alarm_cleared" will be generated. */
    bcmos_bool stats_alarm_raised; /**< If true, indications of type "stats_alarm_raised" will be generated. */
} bcmolt_eth_oam_auto_cfg_data;

/* Constants associated with bcmolt_eth_oam_auto_cfg_data. */
#define BCMOLT_ETH_OAM_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "auto_cfg" group of "eth_oam" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_eth_oam_key key; /**< Object key. */
    bcmolt_eth_oam_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_eth_oam_auto_cfg;

/** BAL Flow: key */
typedef struct
{
    bcmolt_flow_id flow_id; /**< The ID of the flow object instance being referenced */
    bcmolt_flow_type flow_type; /**< The type of the flow, Upstream, Downstream, Broadcast or Multicast */
} bcmolt_flow_key;

/* Constants associated with bcmolt_flow_key. */
#define BCMOLT_FLOW_KEY_FLOW_ID_MIN (bcmolt_flow_id)0U

/** BAL Flow: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_intf_ref ingress_intf; /**< The ingress tip of the flow */
    bcmolt_intf_ref egress_intf; /**< The engress tip of the flow */
    bcmolt_onu_id onu_id; /**< The ID of the ONU assigned to this flow */
    bcmolt_service_port_id svc_port_id; /**< The ID of the service port (for GPON/XGPON - GEM ID) */
    bcmolt_classifier classifier; /**< The classifier for this flow */
    uint16_t priority; /**< Priority for this flow in case of multiple match.
    Higher value precednece over lower value. */
    bcmolt_action action; /**< The action associated with the flow */
    bcmolt_group_id group_id; /**< RW - The multicast group associated with this flow, valid for type MULTICAST only */
    bcmolt_egress_qos egress_qos; /**< Egress qos. */
    bcmolt_flow_state state; /**< Flow State. */
    bcmolt_control_state local_switching; /**< Utilize Pon to Pon local switching (US Flows Only), enable=Allow / disable=Do not allow (default). */
    bcmolt_control_state statistics; /**< enable/disable flow statistics */
    bcmolt_cookie cookie; /**< Opaque application cookie associated with the flow (not interpreted by Maple) */
    bcmolt_mac_table_miss_action mac_table_miss_action; /**< Action to take a mac table miss */
    bcmolt_policer_profile_id policer_profile; /**< policer profile for flow if any */
    bcmolt_um_fwrd_state um_forwarding; /**< um forwarding. */
    bcmolt_arr_src_binding_info_16 src_bindings; /**< source bindings for a flow */
} bcmolt_flow_cfg_data;

/* Constants associated with bcmolt_flow_cfg_data. */
#define BCMOLT_FLOW_CFG_DATA_PRESENCE_MASK_ALL 0x000000000001FFFFULL
#define BCMOLT_FLOW_CFG_DATA_ONU_ID_DEFAULT (bcmolt_onu_id)65535U
#define BCMOLT_FLOW_CFG_DATA_SVC_PORT_ID_DEFAULT (bcmolt_service_port_id)65535UL
#define BCMOLT_FLOW_CFG_DATA_PRIORITY_DEFAULT 10U
#define BCMOLT_FLOW_CFG_DATA_PRIORITY_MIN 0U
#define BCMOLT_FLOW_CFG_DATA_PRIORITY_MAX 65535U
#define BCMOLT_FLOW_CFG_DATA_GROUP_ID_DEFAULT (bcmolt_group_id)65535U
#define BCMOLT_FLOW_CFG_DATA_STATE_DEFAULT BCMOLT_FLOW_STATE_NOT_CONFIGURED
#define BCMOLT_FLOW_CFG_DATA_LOCAL_SWITCHING_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_FLOW_CFG_DATA_STATISTICS_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_FLOW_CFG_DATA_MAC_TABLE_MISS_ACTION_DEFAULT BCMOLT_MAC_TABLE_MISS_ACTION_FLOOD
#define BCMOLT_FLOW_CFG_DATA_POLICER_PROFILE_DEFAULT (bcmolt_policer_profile_id)65535U
#define BCMOLT_FLOW_CFG_DATA_UM_FORWARDING_DEFAULT BCMOLT_UM_FWRD_STATE_DISABLE
#define BCMOLT_FLOW_CFG_DATA_SRC_BINDINGS_LENGTH 16

/** Transport message definition for "cfg" group of "flow" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key. */
    bcmolt_flow_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_flow_cfg;

/** Multi-object message definition for "cfg" group of "flow" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key (can include wildcards). */
    bcmolt_flow_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_flow_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_flow_cfg *responses; /**< Responses to the last API call. */

    bcmolt_flow_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_flow_multi_cfg;

/** BAL Flow: Statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t rx_packets; /**< Received packets. */
    uint64_t rx_bytes; /**< Received bytes. */
    uint64_t tx_packets; /**< Transmitted packets. */
    uint64_t tx_bytes; /**< Transmitted bytes. */
} bcmolt_flow_stats_data;

/* Constants associated with bcmolt_flow_stats_data. */
#define BCMOLT_FLOW_STATS_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "stats" group of "flow" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key. */
    bcmolt_flow_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_flow_stats;

/** Multi-object message definition for "stats" group of "flow" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key (can include wildcards). */
    bcmolt_flow_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_flow_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_flow_stats *responses; /**< Responses to the last API call. */

    bcmolt_flow_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_flow_multi_stats;

/** BAL Flow: send_eth_packet */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str buffer; /**< Buffer containing frame to be sent (includes L2 header) */
    bcmolt_inject_type inject_type; /**< Location to inject frame (Egress Port or Ingress Port). */
    bcmolt_intf_ref ingress_intf; /**< Ingress Interface. Used with inject_type==ingress for Flow with Ingress==Host. */
    bcmolt_service_port_id svc_port_id; /**< Service Port Id. Used with inject_type==ingress for Flow with Ingress==Host. */
} bcmolt_flow_send_eth_packet_data;

/* Constants associated with bcmolt_flow_send_eth_packet_data. */
#define BCMOLT_FLOW_SEND_ETH_PACKET_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_FLOW_SEND_ETH_PACKET_DATA_INJECT_TYPE_DEFAULT BCMOLT_INJECT_TYPE_INJECT_AT_EGRESS
#define BCMOLT_FLOW_SEND_ETH_PACKET_DATA_SVC_PORT_ID_DEFAULT (bcmolt_service_port_id)65535UL

/** Transport message definition for "send_eth_packet" group of "flow" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key. */
    bcmolt_flow_send_eth_packet_data data; /**< All properties that must be set by the user. */
} bcmolt_flow_send_eth_packet;

/** BAL Flow: source binding update */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_binding_command command; /**< binding command */
    bcmolt_src_binding_info src_binding; /**< source binding parameters */
} bcmolt_flow_src_binding_update_data;

/* Constants associated with bcmolt_flow_src_binding_update_data. */
#define BCMOLT_FLOW_SRC_BINDING_UPDATE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "src_binding_update" group of "flow" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key. */
    bcmolt_flow_src_binding_update_data data; /**< All properties that must be set by the user. */
} bcmolt_flow_src_binding_update;

/** BAL Flow: Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config rx_packets; /**< Received packets. */
    bcmolt_stat_alarm_config rx_bytes; /**< Received bytes. */
    bcmolt_stat_alarm_config tx_packets; /**< Transmitted packets. */
    bcmolt_stat_alarm_config tx_bytes; /**< Transmitted bytes. */
} bcmolt_flow_stats_cfg_data;

/* Constants associated with bcmolt_flow_stats_cfg_data. */
#define BCMOLT_FLOW_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "stats_cfg" group of "flow" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key. */
    bcmolt_flow_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_flow_stats_cfg;

/** BAL Flow: Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_flow_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_flow_stats_alarm_raised_data;

/* Constants associated with bcmolt_flow_stats_alarm_raised_data. */
#define BCMOLT_FLOW_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_raised" group of "flow" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key. */
    bcmolt_flow_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_flow_stats_alarm_raised;

/** BAL Flow: Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_flow_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_flow_stats_alarm_cleared_data;

/* Constants associated with bcmolt_flow_stats_alarm_cleared_data. */
#define BCMOLT_FLOW_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_cleared" group of "flow" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key. */
    bcmolt_flow_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_flow_stats_alarm_cleared;

/** BAL Flow: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool stats_alarm_cleared; /**< If true, indications of type "stats_alarm_cleared" will be generated. */
    bcmos_bool stats_alarm_raised; /**< If true, indications of type "stats_alarm_raised" will be generated. */
} bcmolt_flow_auto_cfg_data;

/* Constants associated with bcmolt_flow_auto_cfg_data. */
#define BCMOLT_FLOW_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "auto_cfg" group of "flow" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_flow_key key; /**< Object key. */
    bcmolt_flow_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_flow_auto_cfg;

/** GPIO: key */
typedef struct
{
    bcmolt_ldid device_id; /**< Device ID */
    bcmolt_gpio_pin gpio_id; /**< GPIO ID. */
} bcmolt_gpio_key;

/** GPIO: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_gpio_pin_dir direction; /**< GPIO PIN direction (input or output) */
    bcmolt_gpio_value value; /**< Value to write. */
} bcmolt_gpio_cfg_data;

/* Constants associated with bcmolt_gpio_cfg_data. */
#define BCMOLT_GPIO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "cfg" group of "gpio" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_gpio_key key; /**< Object key. */
    bcmolt_gpio_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_gpio_cfg;

/** Multi-object message definition for "cfg" group of "gpio" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_gpio_key key; /**< Object key (can include wildcards). */
    bcmolt_gpio_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_gpio_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_gpio_cfg *responses; /**< Responses to the last API call. */

    bcmolt_gpio_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_gpio_multi_cfg;

/** BAL Group: key */
typedef struct
{
    bcmolt_group_id id; /**< The ID of the group object instance being referenced */
} bcmolt_group_key;

/** BAL Group: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_group_member_info_list_u8 members; /**< The list of members associated with this group, updated using operations */
    bcmolt_cookie cookie; /**< Application cookie */
    bcmolt_group_type type; /**< Configured Group Type is Mulicast or Nto1 */
    bcmolt_group_state state; /**< group state. */
    bcmolt_action action; /**< allowed vlan actions */
} bcmolt_group_cfg_data;

/* Constants associated with bcmolt_group_cfg_data. */
#define BCMOLT_GROUP_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_GROUP_CFG_DATA_TYPE_DEFAULT BCMOLT_GROUP_TYPE_NONE
#define BCMOLT_GROUP_CFG_DATA_STATE_DEFAULT BCMOLT_GROUP_STATE_NOT_CONFIGURED

/** Transport message definition for "cfg" group of "group" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_group_key key; /**< Object key. */
    bcmolt_group_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_group_cfg;

/** Multi-object message definition for "cfg" group of "group" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_group_key key; /**< Object key (can include wildcards). */
    bcmolt_group_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_group_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_group_cfg *responses; /**< Responses to the last API call. */

    bcmolt_group_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_group_multi_cfg;

/** BAL Group: members_update */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_group_members_update_command members_cmd; /**< members_cmd. */
} bcmolt_group_members_update_data;

/* Constants associated with bcmolt_group_members_update_data. */
#define BCMOLT_GROUP_MEMBERS_UPDATE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "members_update" group of "group" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_group_key key; /**< Object key. */
    bcmolt_group_members_update_data data; /**< All properties that must be set by the user. */
} bcmolt_group_members_update;

/** BAL Group: complete_members_update */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< result. */
    bcmolt_group_member_update_fail_reason fail_reason; /**< fail reason. */
} bcmolt_group_complete_members_update_data;

/* Constants associated with bcmolt_group_complete_members_update_data. */
#define BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "complete_members_update" group of "group" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_group_key key; /**< Object key. */
    bcmolt_group_complete_members_update_data data; /**< All properties that must be set by the user. */
} bcmolt_group_complete_members_update;

/** BAL Group: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool complete_members_update; /**< If true, indications of type "complete_members_update" will be generated. */
} bcmolt_group_auto_cfg_data;

/* Constants associated with bcmolt_group_auto_cfg_data. */
#define BCMOLT_GROUP_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "auto_cfg" group of "group" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_group_key key; /**< Object key. */
    bcmolt_group_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_group_auto_cfg;

/** host log: key */
typedef struct
{
    bcmolt_str_100 name; /**< Log name */
} bcmolt_host_log_key;

/** host log: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_log_type type; /**< Log type */
    bcmolt_log_style style; /**< Log style */
    bcmolt_log_level_per_file level; /**< Log levels for each file */
    bcmolt_log_level_msg_count msg_count; /**< Number of messages per log level */
    uint32_t lost_msg_count; /**< Number of messages lost/dropped */
} bcmolt_host_log_cfg_data;

/* Constants associated with bcmolt_host_log_cfg_data. */
#define BCMOLT_HOST_LOG_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL

/** Transport message definition for "cfg" group of "host_log" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_host_log_key key; /**< Object key. */
    bcmolt_host_log_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_host_log_cfg;

/** Multi-object message definition for "cfg" group of "host_log" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_host_log_key key; /**< Object key (can include wildcards). */
    bcmolt_host_log_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_host_log_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_host_log_cfg *responses; /**< Responses to the last API call. */

    bcmolt_host_log_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_host_log_multi_cfg;

/** Host Log File: key */
typedef struct
{
    bcmolt_host_log_file_id file_id; /**< The log file to access (only SRAM is supported) */
} bcmolt_host_log_file_key;

/** Host Log File: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool wrap_around; /**< Log file wrap-around option. TRUE=wrap around when full. FALSE=stop when full */
    bcmos_bool clear_after_read; /**< Clear log after last record has been read */
    uint32_t msg_count; /**< Number of messages currently in the log */
    uint32_t msgs_read; /**< Number of messages already read */
    uint32_t msgs_remaining; /**< Number of unread messages remaining in the log file */
    bcmolt_str_2048 buffer; /**< Contains a section of the log buffer, one message per line. Reading this field causes it to move to the next section. */
} bcmolt_host_log_file_cfg_data;

/* Constants associated with bcmolt_host_log_file_cfg_data. */
#define BCMOLT_HOST_LOG_FILE_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000003FULL
#define BCMOLT_HOST_LOG_FILE_CFG_DATA_WRAP_AROUND_DEFAULT BCMOS_TRUE
#define BCMOLT_HOST_LOG_FILE_CFG_DATA_CLEAR_AFTER_READ_DEFAULT BCMOS_FALSE

/** Transport message definition for "cfg" group of "host_log_file" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_host_log_file_key key; /**< Object key. */
    bcmolt_host_log_file_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_host_log_file_cfg;

/** Multi-object message definition for "cfg" group of "host_log_file" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_host_log_file_key key; /**< Object key (can include wildcards). */
    bcmolt_host_log_file_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_host_log_file_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_host_log_file_cfg *responses; /**< Responses to the last API call. */

    bcmolt_host_log_file_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_host_log_file_multi_cfg;

/** Transport message definition for "clear" group of "host_log_file" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_host_log_file_key key; /**< Object key. */
} bcmolt_host_log_file_clear;

/** Transport message definition for "reset_buffer_ptr" group of "host_log_file" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_host_log_file_key key; /**< Object key. */
} bcmolt_host_log_file_reset_buffer_ptr;

/** BAL Inband Management Channel: key */
typedef struct
{
    bcmolt_inband_mgmt_instance_id id; /**< The ID of the inband management flow object */
} bcmolt_inband_mgmt_channel_key;

/* Constants associated with bcmolt_inband_mgmt_channel_key. */
#define BCMOLT_INBAND_MGMT_CHANNEL_KEY_ID_MIN (bcmolt_inband_mgmt_instance_id)0
#define BCMOLT_INBAND_MGMT_CHANNEL_KEY_ID_MAX (bcmolt_inband_mgmt_instance_id)255

/** BAL Inband Management Channel: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_intf_ref nni_intf; /**< The NNI interface Id */
    bcmolt_policer_profile_id policer_profile; /**< policer_profile. */
    bcmolt_interface_id nic_intf_id; /**< The logical port from Topology file, facing the NIC card on host */
    uint16_t vlan_id; /**< The classifier for this inband mgmt flow. Vid is always an Outer Vid */
    bcmos_mac_address nic_card_mac; /**< NIC card MAC address. */
    bcmolt_inband_mgmt_action_type action; /**< The action associated with the inband flow */
    bcmolt_inband_mgmt_state state; /**< Inband Mgmt State. */
} bcmolt_inband_mgmt_channel_cfg_data;

/* Constants associated with bcmolt_inband_mgmt_channel_cfg_data. */
#define BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000007FULL
#define BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_POLICER_PROFILE_DEFAULT (bcmolt_policer_profile_id)65535U
#define BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_VLAN_ID_MIN 1U
#define BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_VLAN_ID_MAX 4094U
#define BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_STATE_DEFAULT BCMOLT_INBAND_MGMT_STATE_NOT_CONFIGURED

/** Transport message definition for "cfg" group of "inband_mgmt_channel" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_inband_mgmt_channel_key key; /**< Object key. */
    bcmolt_inband_mgmt_channel_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_inband_mgmt_channel_cfg;

/** Multi-object message definition for "cfg" group of "inband_mgmt_channel" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_inband_mgmt_channel_key key; /**< Object key (can include wildcards). */
    bcmolt_inband_mgmt_channel_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_inband_mgmt_channel_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_inband_mgmt_channel_cfg *responses; /**< Responses to the last API call. */

    bcmolt_inband_mgmt_channel_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_inband_mgmt_channel_multi_cfg;

/** Internal NNI: key */
typedef struct
{
    bcmolt_interface pon_ni; /**< Interface Id */
} bcmolt_internal_nni_key;

/** Internal NNI: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_mac_address mac_address; /**< Mac address to be used for this NNI. */
    bcmolt_nni_connection active_nni; /**< Which NNI is currently active. */
    bcmolt_nni_link_status status; /**< NNI status */
    bcmolt_nni_link_status backup_status; /**< Status of the backup NNI. */
    bcmolt_nni_loopback_type loopback_type; /**< Loopback direction, line, remote or none */
    uint32_t status_polling_interval_ms; /**< How often to check the status of the primary and backup NNIs (units: ms). Zero (0) disables status polling. */
    bcmolt_internal_nni_redundancy redundancy; /**< Should firmware automatically switch between primary/backup NNIs when Loss of Link is detected? */
    bcmolt_control_state flow_control; /**< NNI Flow control. */
    bcmolt_inband_config_data inband_mgmt; /**< Inband management configuration. */
    bcmolt_trap_config trap_config; /**< Rules for packet trapping on this interface */
    bcmos_bool oversubscription; /**< If true, this INNI is potentially oversubscribed and has enabled additonal buffering to mitigate traffic loss. */
    bcmolt_prbs_generator_config prbs_generator; /**< PRBS Generator. */
    bcmolt_prbs_checker_config prbs_checker; /**< PRBS Checker. */
    bcmolt_prbs_status prbs_status; /**< PRBS Status. */
    uint32_t nni_swap_delay_us; /**< It is used in NNI redundancy swap */
    bcmolt_flow_control_mode flow_control_mode; /**< Flow control mode in use on this internal_nni:  PFC or PAUSE */
} bcmolt_internal_nni_cfg_data;

/* Constants associated with bcmolt_internal_nni_cfg_data. */
#define BCMOLT_INTERNAL_NNI_CFG_DATA_PRESENCE_MASK_ALL 0x000000000003FFBEULL
#define BCMOLT_INTERNAL_NNI_CFG_DATA_ACTIVE_NNI_DEFAULT BCMOLT_NNI_CONNECTION_PRIMARY
#define BCMOLT_INTERNAL_NNI_CFG_DATA_LOOPBACK_TYPE_DEFAULT BCMOLT_NNI_LOOPBACK_TYPE_NONE
#define BCMOLT_INTERNAL_NNI_CFG_DATA_STATUS_POLLING_INTERVAL_MS_DEFAULT 50UL
#define BCMOLT_INTERNAL_NNI_CFG_DATA_STATUS_POLLING_INTERVAL_MS_MIN 0UL
#define BCMOLT_INTERNAL_NNI_CFG_DATA_STATUS_POLLING_INTERVAL_MS_MAX 2000000UL
#define BCMOLT_INTERNAL_NNI_CFG_DATA_REDUNDANCY_DEFAULT BCMOLT_INTERNAL_NNI_REDUNDANCY_NONE
#define BCMOLT_INTERNAL_NNI_CFG_DATA_FLOW_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_ENABLE
#define BCMOLT_INTERNAL_NNI_CFG_DATA_OVERSUBSCRIPTION_DEFAULT BCMOS_FALSE
#define BCMOLT_INTERNAL_NNI_CFG_DATA_NNI_SWAP_DELAY_US_DEFAULT 320UL
#define BCMOLT_INTERNAL_NNI_CFG_DATA_NNI_SWAP_DELAY_US_MIN 0UL
#define BCMOLT_INTERNAL_NNI_CFG_DATA_NNI_SWAP_DELAY_US_MAX 300000UL

/** Transport message definition for "cfg" group of "internal_nni" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_cfg;

/** Multi-object message definition for "cfg" group of "internal_nni" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key (can include wildcards). */
    bcmolt_internal_nni_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_internal_nni_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_internal_nni_cfg *responses; /**< Responses to the last API call. */

    bcmolt_internal_nni_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_internal_nni_multi_cfg;

/** Internal NNI: Status changed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status new_status; /**< New NNI Link Status */
    bcmolt_nni_connection link; /**< Which NNI this indication pertains to. */
    bcmolt_nni_connection previous_active; /**< Which NNI was active before this status change. */
    bcmolt_nni_connection new_active; /**< Which NNI is now active after this status change. */
} bcmolt_internal_nni_status_changed_data;

/* Constants associated with bcmolt_internal_nni_status_changed_data. */
#define BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "status_changed" group of "internal_nni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_status_changed_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_status_changed;

/** Internal NNI: NNI and AE Counters (RMON) */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t rx_good_frames; /**< The number of received good frames on this NNI. */
    uint64_t rx_control_frames; /**< The number of received control frames on this NNI. */
    uint64_t rx_pause_frames; /**< The number of received pause frames on this NNI. */
    uint64_t rx_pfc_frames; /**< The number of received PFC frames on this NNI. */
    uint64_t rx_unsupported_opcode; /**< The number of received Unsupported Opcode frames on this NNI. */
    uint64_t rx_unsupported_da; /**< The number of received unsupported DA frames on this NNI. */
    uint64_t rx_alignment_errors; /**< The number of received alignment errors on this NNI. */
    uint64_t rx_length_out_of_range; /**< The number of received length out of range errors on this NNI. */
    uint64_t rx_code_errors; /**< The number of received code errors on this NNI. */
    uint64_t rx_jabber_frames; /**< The number of received jabber frames on this NNI. these are oversized frames that also contain an invalid CRC, code error, or IEEE length check error. */
    uint64_t rx_mtu_check_errors; /**< The number of received MTU Check Errors on this NNI. */
    uint64_t rx_promiscuous_frames; /**< The number of received frames on this NNI that are not control packets and have a DA that is not matching with the RX SA. */
    uint64_t rx_vlan_frames; /**< The number of received VLAN tagged frames on this NNI (with TPID 8100). This counts both single and double tagged frames. */
    uint64_t rx_double_vlan_frames; /**< The number of received double VLAN tagged frames on this NNI (with TPID 8100). */
    uint64_t rx_truncated_frames; /**< The number of received truncated frames on this NNI. This is likely due to RX FIFO Full. */
    uint64_t rx_undersize_frames; /**< The number of received undersized frames on this NNI. */
    uint64_t rx_fragmented_frames; /**< The number of received fragmented frames on this NNI. */
    uint64_t tx_good_frames; /**< The number of transmitted good frames on this NNI. */
    uint64_t tx_pause_frames; /**< The number of transmitted pause frames on this NNI. */
    uint64_t tx_pfc_frames; /**< The number of transmitted PFC frames on this NNI. */
    uint64_t tx_jabber_frames; /**< The number of transmitted jabber frames on this NNI. These are oversized frames that also contain an invalid FCS. */
    uint64_t tx_control_frames; /**< The number of transmitted control frames on this NNI. */
    uint64_t tx_oversize_frames; /**< The number of transmitted oversized frames on this NNI. */
    uint64_t tx_fragmented_frames; /**< The number of transmitted fragmented frames on this NNI. */
    uint64_t tx_error_frames; /**< The number of transmitted errored frames on this NNI. */
    uint64_t tx_vlan_frames; /**< The number of transmitted VLAN tagged frames on this NNI (with TPID 8100). This counts both single and double tagged frames. */
    uint64_t tx_double_vlan_frames; /**< The number of transmitted double VLAN tagged frames on this NNI (with TPID 8100). */
    uint64_t tx_runt_frames; /**< The number of transmitted runt frames on this NNI. */
    uint64_t tx_underrun_frames; /**< The number of transmitted underrun frames on this NNI. Thus happens when a frame encounters a MAC underrun (Tx Sync FIFO runs out of data before the end of packet). */
} bcmolt_internal_nni_nni_stats_data;

/* Constants associated with bcmolt_internal_nni_nni_stats_data. */
#define BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_PRESENCE_MASK_ALL 0x000000001FFFFFFFULL

/** Transport message definition for "nni_stats" group of "internal_nni" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_nni_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_nni_stats;

/** Multi-object message definition for "nni_stats" group of "internal_nni" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key (can include wildcards). */
    bcmolt_internal_nni_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_internal_nni_nni_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_internal_nni_nni_stats *responses; /**< Responses to the last API call. */

    bcmolt_internal_nni_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_internal_nni_multi_nni_stats;

/** Internal NNI: Ethernet Statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t rx_bytes; /**< The number of bytes received. */
    uint64_t rx_frames; /**< The number of frames received. */
    uint64_t rx_frames_64; /**< The number of 64 byte frames received. */
    uint64_t rx_frames_65_127; /**< The number of 65 to 127 byte frames received. */
    uint64_t rx_frames_128_255; /**< The number of 128 to 255 byte frames received. */
    uint64_t rx_frames_256_511; /**< The number of 256 to 511 byte frames received. */
    uint64_t rx_frames_512_1023; /**< The number of 512 to 1023 byte frames received. */
    uint64_t rx_frames_1024_1518; /**< The number of 1024 to 1518 byte frames received. */
    uint64_t rx_frames_1519_2047; /**< The number of 1519 to 2047 byte frames received. */
    uint64_t rx_frames_2048_4095; /**< The number of 2048 to 4095 byte frames received. */
    uint64_t rx_frames_4096_9216; /**< The number of 4096 to 9216 byte frames received. */
    uint64_t rx_frames_9217_16383; /**< The number of 9217 to 16383 byte frames received. */
    uint64_t rx_broadcast_frames; /**< The number of broadcast frames received. */
    uint64_t rx_data_bytes; /**< The number of data bytes received. */
    uint64_t rx_multicast_frames; /**< The number of multicast frames received. */
    uint64_t rx_unicast_frames; /**< The number of unicast frames received. */
    uint64_t rx_abort_frames; /**< The number of abort frames received. */
    uint64_t rx_fcs_error; /**< The number of bad FCS errors received. */
    uint64_t rx_oversize_error; /**< The number of oversize errors received. */
    uint64_t rx_runt_error; /**< The number of runt errors received. */
    uint64_t tx_bytes; /**< The number of bytes transmitted. */
    uint64_t tx_frames; /**< The number of frames transmitted. */
    uint64_t tx_frames_64; /**< The number of 64 byte frames transmitted. */
    uint64_t tx_frames_65_127; /**< The number of 65 to 127 byte frames transmitted. */
    uint64_t tx_frames_128_255; /**< The number of 128 to 255 byte frames transmitted. */
    uint64_t tx_frames_256_511; /**< The number of 256 to 511 byte frames transmitted. */
    uint64_t tx_frames_512_1023; /**< The number of 512 to 1023 byte frames transmitted. */
    uint64_t tx_frames_1024_1518; /**< The number of 1024 to 1518 byte frames transmitted. */
    uint64_t tx_frames_1519_2047; /**< The number of 1519 to 2047 byte frames transmitted. */
    uint64_t tx_frames_2048_4095; /**< The number of 2048 to 4095 byte frames transmitted. */
    uint64_t tx_frames_4096_9216; /**< The number of 4096 to 9216 byte frames transmitted. */
    uint64_t tx_frames_9217_16383; /**< The number of 9217 to 16383 byte frames transmitted. */
    uint64_t tx_broadcast_frames; /**< The number of broadcast frames transmitted. */
    uint64_t tx_data_bytes; /**< The number of data bytes transmitted. */
    uint64_t tx_multicast_frames; /**< The number of multicast frames transmitted. */
    uint64_t tx_unicast_frames; /**< The number of unicast frames transmitted. */
    uint64_t tx_abort_frames; /**< The number of abort frames transmitted. */
    uint64_t tx_fcs_error; /**< The number of transmitted FCS errors on this NNI. */
} bcmolt_internal_nni_enet_stats_data;

/* Constants associated with bcmolt_internal_nni_enet_stats_data. */
#define BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_PRESENCE_MASK_ALL 0x0000003FFFFFFFFFULL

/** Transport message definition for "enet_stats" group of "internal_nni" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_enet_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_enet_stats;

/** Multi-object message definition for "enet_stats" group of "internal_nni" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key (can include wildcards). */
    bcmolt_internal_nni_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_internal_nni_enet_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_internal_nni_enet_stats *responses; /**< Responses to the last API call. */

    bcmolt_internal_nni_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_internal_nni_multi_enet_stats;

/** Internal NNI: Packet Captured */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t packet_size; /**< The size of the packet trapped. */
    bcmolt_bin_str buffer; /**< The actual packet contents */
} bcmolt_internal_nni_packet_captured_data;

/* Constants associated with bcmolt_internal_nni_packet_captured_data. */
#define BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_PRESENCE_MASK_ALL 0x0000000000000006ULL

/** Transport message definition for "packet_captured" group of "internal_nni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_packet_captured_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_packet_captured;

/** Internal NNI: send_eth_packet */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str buffer; /**< buffer. */
} bcmolt_internal_nni_send_eth_packet_data;

/* Constants associated with bcmolt_internal_nni_send_eth_packet_data. */
#define BCMOLT_INTERNAL_NNI_SEND_ETH_PACKET_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "send_eth_packet" group of "internal_nni" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_send_eth_packet_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_send_eth_packet;

/** Transport message definition for "swap_completed" group of "internal_nni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
} bcmolt_internal_nni_swap_completed;

/** Internal NNI: NNI And AE Counters (RMON) Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config rx_good_frames; /**< The number of received good frames on this NNI. */
    bcmolt_stat_alarm_config rx_control_frames; /**< The number of received control frames on this NNI. */
    bcmolt_stat_alarm_config rx_pause_frames; /**< The number of received pause frames on this NNI. */
    bcmolt_stat_alarm_config rx_pfc_frames; /**< The number of received PFC frames on this NNI. */
    bcmolt_stat_alarm_config rx_unsupported_opcode; /**< The number of received Unsupported Opcode frames on this NNI. */
    bcmolt_stat_alarm_config rx_unsupported_da; /**< The number of received unsupported DA frames on this NNI. */
    bcmolt_stat_alarm_config rx_alignment_errors; /**< The number of received alignment errors on this NNI. */
    bcmolt_stat_alarm_config rx_length_out_of_range; /**< The number of received length out of range errors on this NNI. */
    bcmolt_stat_alarm_config rx_code_errors; /**< The number of received code errors on this NNI. */
    bcmolt_stat_alarm_config rx_jabber_frames; /**< The number of received jabber frames on this NNI. these are oversized frames that also contain an invalid CRC, code error, or IEEE length check error. */
    bcmolt_stat_alarm_config rx_mtu_check_errors; /**< The number of received MTU Check Errors on this NNI. */
    bcmolt_stat_alarm_config rx_promiscuous_frames; /**< The number of received frames on this NNI that are not control packets and have a DA that is not matching with the RX SA. */
    bcmolt_stat_alarm_config rx_vlan_frames; /**< The number of received VLAN tagged frames on this NNI (with TPID 8100). This counts both single and double tagged frames. */
    bcmolt_stat_alarm_config rx_double_vlan_frames; /**< The number of received double VLAN tagged frames on this NNI (with TPID 8100). */
    bcmolt_stat_alarm_config rx_truncated_frames; /**< The number of received truncated frames on this NNI. This is likely due to RX FIFO Full. */
    bcmolt_stat_alarm_config rx_undersize_frames; /**< The number of received undersized frames on this NNI. */
    bcmolt_stat_alarm_config rx_fragmented_frames; /**< The number of received fragmented frames on this NNI. */
    bcmolt_stat_alarm_config tx_good_frames; /**< The number of transmitted good frames on this NNI. */
    bcmolt_stat_alarm_config tx_pause_frames; /**< The number of transmitted pause frames on this NNI. */
    bcmolt_stat_alarm_config tx_pfc_frames; /**< The number of transmitted PFC frames on this NNI. */
    bcmolt_stat_alarm_config tx_jabber_frames; /**< The number of transmitted jabber frames on this NNI. These are oversized frames that also contain an invalid FCS. */
    bcmolt_stat_alarm_config tx_control_frames; /**< The number of transmitted control frames on this NNI. */
    bcmolt_stat_alarm_config tx_oversize_frames; /**< The number of transmitted oversized frames on this NNI. */
    bcmolt_stat_alarm_config tx_fragmented_frames; /**< The number of transmitted fragmented frames on this NNI. */
    bcmolt_stat_alarm_config tx_error_frames; /**< The number of transmitted errored frames on this NNI. */
    bcmolt_stat_alarm_config tx_vlan_frames; /**< The number of transmitted VLAN tagged frames on this NNI (with TPID 8100). This counts both single and double tagged frames. */
    bcmolt_stat_alarm_config tx_double_vlan_frames; /**< The number of transmitted double VLAN tagged frames on this NNI (with TPID 8100). */
    bcmolt_stat_alarm_config tx_runt_frames; /**< The number of transmitted runt frames on this NNI. */
    bcmolt_stat_alarm_config tx_underrun_frames; /**< The number of transmitted underrun frames on this NNI. Thus happens when a frame encounters a MAC underrun (Tx Sync FIFO runs out of data before the end of packet). */
} bcmolt_internal_nni_nni_stats_cfg_data;

/* Constants associated with bcmolt_internal_nni_nni_stats_cfg_data. */
#define BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x000000001FFFFFFFULL

/** Transport message definition for "nni_stats_cfg" group of "internal_nni" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_nni_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_nni_stats_cfg;

/** Internal NNI: NNI And AE Counters (RMON) Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_internal_nni_nni_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_internal_nni_nni_stats_alarm_raised_data;

/* Constants associated with bcmolt_internal_nni_nni_stats_alarm_raised_data. */
#define BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "nni_stats_alarm_raised" group of "internal_nni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_nni_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_nni_stats_alarm_raised;

/** Internal NNI: NNI And AE Counters (RMON) Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_internal_nni_nni_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_internal_nni_nni_stats_alarm_cleared_data;

/* Constants associated with bcmolt_internal_nni_nni_stats_alarm_cleared_data. */
#define BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "nni_stats_alarm_cleared" group of "internal_nni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_nni_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_nni_stats_alarm_cleared;

/** Internal NNI: Ethernet Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config rx_bytes; /**< The number of bytes received. */
    bcmolt_stat_alarm_config rx_frames; /**< The number of frames received. */
    bcmolt_stat_alarm_config rx_frames_64; /**< The number of 64 byte frames received. */
    bcmolt_stat_alarm_config rx_frames_65_127; /**< The number of 65 to 127 byte frames received. */
    bcmolt_stat_alarm_config rx_frames_128_255; /**< The number of 128 to 255 byte frames received. */
    bcmolt_stat_alarm_config rx_frames_256_511; /**< The number of 256 to 511 byte frames received. */
    bcmolt_stat_alarm_config rx_frames_512_1023; /**< The number of 512 to 1023 byte frames received. */
    bcmolt_stat_alarm_config rx_frames_1024_1518; /**< The number of 1024 to 1518 byte frames received. */
    bcmolt_stat_alarm_config rx_frames_1519_2047; /**< The number of 1519 to 2047 byte frames received. */
    bcmolt_stat_alarm_config rx_frames_2048_4095; /**< The number of 2048 to 4095 byte frames received. */
    bcmolt_stat_alarm_config rx_frames_4096_9216; /**< The number of 4096 to 9216 byte frames received. */
    bcmolt_stat_alarm_config rx_frames_9217_16383; /**< The number of 9217 to 16383 byte frames received. */
    bcmolt_stat_alarm_config rx_broadcast_frames; /**< The number of broadcast frames received. */
    bcmolt_stat_alarm_config rx_data_bytes; /**< The number of data bytes received. */
    bcmolt_stat_alarm_config rx_multicast_frames; /**< The number of multicast frames received. */
    bcmolt_stat_alarm_config rx_unicast_frames; /**< The number of unicast frames received. */
    bcmolt_stat_alarm_config rx_abort_frames; /**< The number of abort frames received. */
    bcmolt_stat_alarm_config rx_fcs_error; /**< The number of bad FCS errors received. */
    bcmolt_stat_alarm_config rx_oversize_error; /**< The number of oversize errors received. */
    bcmolt_stat_alarm_config rx_runt_error; /**< The number of runt errors received. */
    bcmolt_stat_alarm_config tx_bytes; /**< The number of bytes transmitted. */
    bcmolt_stat_alarm_config tx_frames; /**< The number of frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_64; /**< The number of 64 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_65_127; /**< The number of 65 to 127 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_128_255; /**< The number of 128 to 255 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_256_511; /**< The number of 256 to 511 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_512_1023; /**< The number of 512 to 1023 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_1024_1518; /**< The number of 1024 to 1518 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_1519_2047; /**< The number of 1519 to 2047 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_2048_4095; /**< The number of 2048 to 4095 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_4096_9216; /**< The number of 4096 to 9216 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_frames_9217_16383; /**< The number of 9217 to 16383 byte frames transmitted. */
    bcmolt_stat_alarm_config tx_broadcast_frames; /**< The number of broadcast frames transmitted. */
    bcmolt_stat_alarm_config tx_data_bytes; /**< The number of data bytes transmitted. */
    bcmolt_stat_alarm_config tx_multicast_frames; /**< The number of multicast frames transmitted. */
    bcmolt_stat_alarm_config tx_unicast_frames; /**< The number of unicast frames transmitted. */
    bcmolt_stat_alarm_config tx_abort_frames; /**< The number of abort frames transmitted. */
    bcmolt_stat_alarm_config tx_fcs_error; /**< The number of transmitted FCS errors on this NNI. */
} bcmolt_internal_nni_enet_stats_cfg_data;

/* Constants associated with bcmolt_internal_nni_enet_stats_cfg_data. */
#define BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x0000003FFFFFFFFFULL

/** Transport message definition for "enet_stats_cfg" group of "internal_nni" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_enet_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_enet_stats_cfg;

/** Internal NNI: Ethernet Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_internal_nni_enet_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_internal_nni_enet_stats_alarm_raised_data;

/* Constants associated with bcmolt_internal_nni_enet_stats_alarm_raised_data. */
#define BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "enet_stats_alarm_raised" group of "internal_nni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_enet_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_enet_stats_alarm_raised;

/** Internal NNI: Ethernet Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_internal_nni_enet_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_internal_nni_enet_stats_alarm_cleared_data;

/* Constants associated with bcmolt_internal_nni_enet_stats_alarm_cleared_data. */
#define BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "enet_stats_alarm_cleared" group of "internal_nni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_enet_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_enet_stats_alarm_cleared;

/** Internal NNI: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool enet_stats_alarm_cleared; /**< If true, indications of type "enet_stats_alarm_cleared" will be generated. */
    bcmos_bool enet_stats_alarm_raised; /**< If true, indications of type "enet_stats_alarm_raised" will be generated. */
    bcmos_bool nni_stats_alarm_cleared; /**< If true, indications of type "nni_stats_alarm_cleared" will be generated. */
    bcmos_bool nni_stats_alarm_raised; /**< If true, indications of type "nni_stats_alarm_raised" will be generated. */
    bcmos_bool packet_captured; /**< If true, indications of type "packet_captured" will be generated. */
    bcmos_bool status_changed; /**< If true, indications of type "status_changed" will be generated. */
    bcmos_bool swap_completed; /**< If true, indications of type "swap_completed" will be generated. */
} bcmolt_internal_nni_auto_cfg_data;

/* Constants associated with bcmolt_internal_nni_auto_cfg_data. */
#define BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000007FULL

/** Transport message definition for "auto_cfg" group of "internal_nni" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_internal_nni_key key; /**< Object key. */
    bcmolt_internal_nni_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_internal_nni_auto_cfg;

/** ITU PON Alloc: key */
typedef struct
{
    bcmolt_interface pon_ni; /**< PON network interface. */
    bcmolt_alloc_id alloc_id; /**< Alloc ID. */
} bcmolt_itupon_alloc_key;

/** ITU PON Alloc: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_activation_state state; /**< Current Alloc ID state */
    bcmolt_pon_alloc_sla sla; /**< Alloc ID SLA */
    bcmolt_onu_id onu_id; /**< ONU ID the alloc ID is assigned to */
    bcmos_bool collect_stats; /**< Enable statistics collection for this alloc ID */
    uint32_t onu_tcont_max_queue_size; /**< For better DBA performance, this is the maximum size of the TCONT queue for this alloc ID in the ONU, in bytes. If 0, it means unconfigured. */
    bcmos_bool latency_sensitive; /**< Is the alloc latency sensitive ? This parameter is relevant only for SR allocs. Setting this flag to true may improve the latency of this alloc, but in the cost of slightly compromising other allocs (in congestion only) */
    bcmos_bool enable_latency_stats; /**< Enable latency statistics */
} bcmolt_itupon_alloc_cfg_data;

/* Constants associated with bcmolt_itupon_alloc_cfg_data. */
#define BCMOLT_ITUPON_ALLOC_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000007FULL
#define BCMOLT_ITUPON_ALLOC_CFG_DATA_STATE_DEFAULT BCMOLT_ACTIVATION_STATE_NOT_CONFIGURED
#define BCMOLT_ITUPON_ALLOC_CFG_DATA_ONU_TCONT_MAX_QUEUE_SIZE_DEFAULT 0UL
#define BCMOLT_ITUPON_ALLOC_CFG_DATA_ONU_TCONT_MAX_QUEUE_SIZE_MIN 0UL
#define BCMOLT_ITUPON_ALLOC_CFG_DATA_ONU_TCONT_MAX_QUEUE_SIZE_MAX 16777215UL
#define BCMOLT_ITUPON_ALLOC_CFG_DATA_LATENCY_SENSITIVE_DEFAULT BCMOS_FALSE
#define BCMOLT_ITUPON_ALLOC_CFG_DATA_ENABLE_LATENCY_STATS_DEFAULT BCMOS_FALSE

/** Transport message definition for "cfg" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_cfg;

/** Multi-object message definition for "cfg" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key (can include wildcards). */
    bcmolt_itupon_alloc_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_itupon_alloc_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_itupon_alloc_cfg *responses; /**< Responses to the last API call. */

    bcmolt_itupon_alloc_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_itupon_alloc_multi_cfg;

/** ITU PON Alloc: Configuration Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result status; /**< status. */
    bcmolt_activation_state new_state; /**< new state. */
} bcmolt_itupon_alloc_configuration_completed_data;

/* Constants associated with bcmolt_itupon_alloc_configuration_completed_data. */
#define BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "configuration_completed" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_configuration_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_configuration_completed;

/** ITU PON Alloc: Get alloc level statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t num_of_cycles; /**< The number of cycles to run statistics collection */
} bcmolt_itupon_alloc_get_stats_data;

/* Constants associated with bcmolt_itupon_alloc_get_stats_data. */
#define BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_NUM_OF_CYCLES_DEFAULT 1UL
#define BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_NUM_OF_CYCLES_MIN 1UL
#define BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_NUM_OF_CYCLES_MAX 10000UL

/** Transport message definition for "get_stats" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_get_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_get_stats;

/** ITU PON Alloc: Get alloc level statistics completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result status; /**< status. */
    uint32_t average_nsr_used; /**< Average NSR used words. */
    uint32_t average_nsr_allocated; /**< Average NSR allocated words. */
    uint32_t average_sr_report; /**< Average SR report. */
} bcmolt_itupon_alloc_get_alloc_stats_completed_data;

/* Constants associated with bcmolt_itupon_alloc_get_alloc_stats_completed_data. */
#define BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "get_alloc_stats_completed" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_get_alloc_stats_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_get_alloc_stats_completed;

/** ITU PON Alloc: Set state */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_alloc_operation state; /**< State. */
} bcmolt_itupon_alloc_set_state_data;

/* Constants associated with bcmolt_itupon_alloc_set_state_data. */
#define BCMOLT_ITUPON_ALLOC_SET_STATE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "set_state" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_set_state_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_set_state;

/** ITU PON Alloc: Statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t rx_bytes; /**< Number of alloc ID received bytes. */
} bcmolt_itupon_alloc_stats_data;

/* Constants associated with bcmolt_itupon_alloc_stats_data. */
#define BCMOLT_ITUPON_ALLOC_STATS_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_stats;

/** Multi-object message definition for "stats" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key (can include wildcards). */
    bcmolt_itupon_alloc_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_itupon_alloc_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_itupon_alloc_stats *responses; /**< Responses to the last API call. */

    bcmolt_itupon_alloc_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_itupon_alloc_multi_stats;

/** ITU PON Alloc: Accumulated statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t tm_used; /**< tm used. */
    uint64_t tm_allocated; /**< tm allocated. */
    uint64_t bufocc; /**< Buffer occupancy. */
} bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data;

/* Constants associated with bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data. */
#define BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "alloc_onu_accumulated_stats" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_alloc_onu_accumulated_stats;

/** Multi-object message definition for "alloc_onu_accumulated_stats" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key (can include wildcards). */
    bcmolt_itupon_alloc_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats *responses; /**< Responses to the last API call. */

    bcmolt_itupon_alloc_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_itupon_alloc_multi_alloc_onu_accumulated_stats;

/** ITU PON Alloc: latency statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t onu_tcont_max_queue_size; /**< ONU TCONT maximum queue size. */
    uint64_t allocation_busy; /**< allocation busy. */
    uint64_t latency_bucket_0_100_usec; /**< latency distribution bucket 0-0.1 ms. */
    uint64_t latency_bucket_100_200_usec; /**< latency distribution bucket 0.1-0.2 ms. */
    uint64_t latency_bucket_200_300_usec; /**< latency distribution bucket 0.2-0.3 ms. */
    uint64_t latency_bucket_300_400_usec; /**< latency distribution bucket 0.3-0.4 ms. */
    uint64_t latency_bucket_400_600_usec; /**< latency distribution bucket 0.4-0.6 ms. */
    uint64_t latency_bucket_600_800_usec; /**< latency distribution bucket 0.6-0.8 ms. */
    uint64_t latency_bucket_800_1000_usec; /**< latency distribution bucket 0.8-1 ms. */
    uint64_t latency_bucket_1_3_msec; /**< latency distribution bucket 1-3 ms. */
    uint64_t latency_bucket_3_5_msec; /**< latency distribution bucket 3-5 ms. */
    uint64_t latency_bucket_5_10_msec; /**< latency distribution bucket 5-10 ms. */
    uint64_t latency_bucket_more_than_10_msec; /**< latency distribution bucket more then 10ms. */
} bcmolt_itupon_alloc_latency_stats_data;

/* Constants associated with bcmolt_itupon_alloc_latency_stats_data. */
#define BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_PRESENCE_MASK_ALL 0x0000000000001FFFULL

/** Transport message definition for "latency_stats" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_latency_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_latency_stats;

/** Multi-object message definition for "latency_stats" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key (can include wildcards). */
    bcmolt_itupon_alloc_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_itupon_alloc_latency_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_itupon_alloc_latency_stats *responses; /**< Responses to the last API call. */

    bcmolt_itupon_alloc_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_itupon_alloc_multi_latency_stats;

/** ITU PON Alloc: Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config rx_bytes; /**< Number of alloc ID received bytes. */
} bcmolt_itupon_alloc_stats_cfg_data;

/* Constants associated with bcmolt_itupon_alloc_stats_cfg_data. */
#define BCMOLT_ITUPON_ALLOC_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_cfg" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_stats_cfg;

/** ITU PON Alloc: Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_alloc_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_itupon_alloc_stats_alarm_raised_data;

/* Constants associated with bcmolt_itupon_alloc_stats_alarm_raised_data. */
#define BCMOLT_ITUPON_ALLOC_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_raised" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_stats_alarm_raised;

/** ITU PON Alloc: Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_alloc_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_itupon_alloc_stats_alarm_cleared_data;

/* Constants associated with bcmolt_itupon_alloc_stats_alarm_cleared_data. */
#define BCMOLT_ITUPON_ALLOC_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_cleared" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_stats_alarm_cleared;

/** ITU PON Alloc: Accumulated Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config tm_used; /**< tm used. */
    bcmolt_stat_alarm_config tm_allocated; /**< tm allocated. */
    bcmolt_stat_alarm_config bufocc; /**< Buffer occupancy. */
} bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data;

/* Constants associated with bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data. */
#define BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "alloc_onu_accumulated_stats_cfg" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg;

/** ITU PON Alloc: Accumulated Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data;

/* Constants associated with bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data. */
#define BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "alloc_onu_accumulated_stats_alarm_raised" group of "itupon_alloc"
  * object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised;

/** ITU PON Alloc: Accumulated Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data;

/* Constants associated with bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data. */
#define BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "alloc_onu_accumulated_stats_alarm_cleared" group of
  * "itupon_alloc" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared;

/** ITU PON Alloc: Latency Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config onu_tcont_max_queue_size; /**< ONU TCONT maximum queue size. */
    bcmolt_stat_alarm_config allocation_busy; /**< allocation busy. */
    bcmolt_stat_alarm_config latency_bucket_0_100_usec; /**< latency distribution bucket 0-0.1 ms. */
    bcmolt_stat_alarm_config latency_bucket_100_200_usec; /**< latency distribution bucket 0.1-0.2 ms. */
    bcmolt_stat_alarm_config latency_bucket_200_300_usec; /**< latency distribution bucket 0.2-0.3 ms. */
    bcmolt_stat_alarm_config latency_bucket_300_400_usec; /**< latency distribution bucket 0.3-0.4 ms. */
    bcmolt_stat_alarm_config latency_bucket_400_600_usec; /**< latency distribution bucket 0.4-0.6 ms. */
    bcmolt_stat_alarm_config latency_bucket_600_800_usec; /**< latency distribution bucket 0.6-0.8 ms. */
    bcmolt_stat_alarm_config latency_bucket_800_1000_usec; /**< latency distribution bucket 0.8-1 ms. */
    bcmolt_stat_alarm_config latency_bucket_1_3_msec; /**< latency distribution bucket 1-3 ms. */
    bcmolt_stat_alarm_config latency_bucket_3_5_msec; /**< latency distribution bucket 3-5 ms. */
    bcmolt_stat_alarm_config latency_bucket_5_10_msec; /**< latency distribution bucket 5-10 ms. */
    bcmolt_stat_alarm_config latency_bucket_more_than_10_msec; /**< latency distribution bucket more then 10ms. */
} bcmolt_itupon_alloc_latency_stats_cfg_data;

/* Constants associated with bcmolt_itupon_alloc_latency_stats_cfg_data. */
#define BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000001FFFULL

/** Transport message definition for "latency_stats_cfg" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_latency_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_latency_stats_cfg;

/** ITU PON Alloc: Latency Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_alloc_latency_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_itupon_alloc_latency_stats_alarm_raised_data;

/* Constants associated with bcmolt_itupon_alloc_latency_stats_alarm_raised_data. */
#define BCMOLT_ITUPON_ALLOC_LATENCY_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "latency_stats_alarm_raised" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_latency_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_latency_stats_alarm_raised;

/** ITU PON Alloc: Latency Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_alloc_latency_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_itupon_alloc_latency_stats_alarm_cleared_data;

/* Constants associated with bcmolt_itupon_alloc_latency_stats_alarm_cleared_data. */
#define BCMOLT_ITUPON_ALLOC_LATENCY_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "latency_stats_alarm_cleared" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_latency_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_latency_stats_alarm_cleared;

/** ITU PON Alloc: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool alloc_onu_accumulated_stats_alarm_cleared; /**< If true, indications of type "alloc_onu_accumulated_stats_alarm_cleared" will be generated. */
    bcmos_bool alloc_onu_accumulated_stats_alarm_raised; /**< If true, indications of type "alloc_onu_accumulated_stats_alarm_raised" will be generated. */
    bcmos_bool configuration_completed; /**< If true, indications of type "configuration_completed" will be generated. */
    bcmos_bool get_alloc_stats_completed; /**< If true, indications of type "get_alloc_stats_completed" will be generated. */
    bcmos_bool latency_stats_alarm_cleared; /**< If true, indications of type "latency_stats_alarm_cleared" will be generated. */
    bcmos_bool latency_stats_alarm_raised; /**< If true, indications of type "latency_stats_alarm_raised" will be generated. */
    bcmos_bool stats_alarm_cleared; /**< If true, indications of type "stats_alarm_cleared" will be generated. */
    bcmos_bool stats_alarm_raised; /**< If true, indications of type "stats_alarm_raised" will be generated. */
} bcmolt_itupon_alloc_auto_cfg_data;

/* Constants associated with bcmolt_itupon_alloc_auto_cfg_data. */
#define BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x00000000000000FFULL

/** Transport message definition for "auto_cfg" group of "itupon_alloc" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_itupon_alloc_key key; /**< Object key. */
    bcmolt_itupon_alloc_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_alloc_auto_cfg;

/** ITU PON GEM Port: key */
typedef struct
{
    bcmolt_interface pon_ni; /**< PON network interface. */
    bcmolt_gem_port_id gem_port_id; /**< GEM Port ID. */
} bcmolt_itupon_gem_key;

/** ITU PON GEM Port: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_gem_port_configuration configuration; /**< GEM port configuration parameters */
    bcmolt_onu_id onu_id; /**< ONU ID this GEM port is assigned to */
    bcmolt_activation_state state; /**< Current GEM port state */
    bcmolt_control_state encryption_mode; /**< Enable/Disable the encryption mode of the GEM Port */
    bcmolt_us_gem_port_destination upstream_destination_queue; /**< The destination queue of the packets arriving on this GEM Port on the upstream direction */
    bcmolt_control_state control; /**< Enable/Disable the GEM Port ID in the OLT */
    uint16_t mac_table_entry_limit; /**< The maximum number of MAC table entries allowed for this GEM port (0 = no limit). */
    bcmolt_debug_flow_config debug_flow_config; /**< debug flow config to support mac only learning */
} bcmolt_itupon_gem_cfg_data;

/* Constants associated with bcmolt_itupon_gem_cfg_data. */
#define BCMOLT_ITUPON_GEM_CFG_DATA_PRESENCE_MASK_ALL 0x00000000000000FFULL
#define BCMOLT_ITUPON_GEM_CFG_DATA_STATE_DEFAULT BCMOLT_ACTIVATION_STATE_NOT_CONFIGURED
#define BCMOLT_ITUPON_GEM_CFG_DATA_MAC_TABLE_ENTRY_LIMIT_DEFAULT 0U
#define BCMOLT_ITUPON_GEM_CFG_DATA_MAC_TABLE_ENTRY_LIMIT_MIN 0U
#define BCMOLT_ITUPON_GEM_CFG_DATA_MAC_TABLE_ENTRY_LIMIT_MAX 128U

/** Transport message definition for "cfg" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key. */
    bcmolt_itupon_gem_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_gem_cfg;

/** Multi-object message definition for "cfg" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key (can include wildcards). */
    bcmolt_itupon_gem_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_itupon_gem_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_itupon_gem_cfg *responses; /**< Responses to the last API call. */

    bcmolt_itupon_gem_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_itupon_gem_multi_cfg;

/** ITU PON GEM Port: Statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t rx_packets; /**< Received GEM frames. */
    uint64_t rx_bytes; /**< Received bytes. */
    uint64_t tx_packets; /**< Transmitted GEM frames. */
    uint64_t tx_bytes; /**< Transmitted bytes. */
} bcmolt_itupon_gem_stats_data;

/* Constants associated with bcmolt_itupon_gem_stats_data. */
#define BCMOLT_ITUPON_GEM_STATS_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "stats" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key. */
    bcmolt_itupon_gem_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_gem_stats;

/** Multi-object message definition for "stats" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key (can include wildcards). */
    bcmolt_itupon_gem_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_itupon_gem_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_itupon_gem_stats *responses; /**< Responses to the last API call. */

    bcmolt_itupon_gem_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_itupon_gem_multi_stats;

/** ITU PON GEM Port: Configuration Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result status; /**< status. */
    bcmolt_activation_state new_state; /**< new state. */
} bcmolt_itupon_gem_configuration_completed_data;

/* Constants associated with bcmolt_itupon_gem_configuration_completed_data. */
#define BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "configuration_completed" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key. */
    bcmolt_itupon_gem_configuration_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_gem_configuration_completed;

/** ITU PON GEM Port: Set state */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_gem_port_operation state; /**< State. */
} bcmolt_itupon_gem_set_state_data;

/* Constants associated with bcmolt_itupon_gem_set_state_data. */
#define BCMOLT_ITUPON_GEM_SET_STATE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "set_state" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key. */
    bcmolt_itupon_gem_set_state_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_gem_set_state;

/** ITU PON GEM Port: Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config rx_packets; /**< Received GEM frames. */
    bcmolt_stat_alarm_config rx_bytes; /**< Received bytes. */
    bcmolt_stat_alarm_config tx_packets; /**< Transmitted GEM frames. */
    bcmolt_stat_alarm_config tx_bytes; /**< Transmitted bytes. */
} bcmolt_itupon_gem_stats_cfg_data;

/* Constants associated with bcmolt_itupon_gem_stats_cfg_data. */
#define BCMOLT_ITUPON_GEM_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "stats_cfg" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key. */
    bcmolt_itupon_gem_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_gem_stats_cfg;

/** ITU PON GEM Port: Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_gem_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_itupon_gem_stats_alarm_raised_data;

/* Constants associated with bcmolt_itupon_gem_stats_alarm_raised_data. */
#define BCMOLT_ITUPON_GEM_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_raised" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key. */
    bcmolt_itupon_gem_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_gem_stats_alarm_raised;

/** ITU PON GEM Port: Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_gem_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_itupon_gem_stats_alarm_cleared_data;

/* Constants associated with bcmolt_itupon_gem_stats_alarm_cleared_data. */
#define BCMOLT_ITUPON_GEM_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_cleared" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key. */
    bcmolt_itupon_gem_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_gem_stats_alarm_cleared;

/** ITU PON GEM Port: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool configuration_completed; /**< If true, indications of type "configuration_completed" will be generated. */
    bcmos_bool stats_alarm_cleared; /**< If true, indications of type "stats_alarm_cleared" will be generated. */
    bcmos_bool stats_alarm_raised; /**< If true, indications of type "stats_alarm_raised" will be generated. */
} bcmolt_itupon_gem_auto_cfg_data;

/* Constants associated with bcmolt_itupon_gem_auto_cfg_data. */
#define BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "auto_cfg" group of "itupon_gem" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_itupon_gem_key key; /**< Object key. */
    bcmolt_itupon_gem_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_itupon_gem_auto_cfg;

/** l2 mac table: key */
typedef struct
{
    bcmolt_l2_mac_table_id id; /**< id. */
} bcmolt_l2_mac_table_key;

/* Constants associated with bcmolt_l2_mac_table_key. */
#define BCMOLT_L2_MAC_TABLE_KEY_ID_DEFAULT (bcmolt_l2_mac_table_id)0
#define BCMOLT_L2_MAC_TABLE_KEY_ID_MIN (bcmolt_l2_mac_table_id)0
#define BCMOLT_L2_MAC_TABLE_KEY_ID_MAX (bcmolt_l2_mac_table_id)0

/** l2 mac table: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state state; /**< state. */
    bcmolt_l2_mact_dump_status dump_status; /**< dump status. */
    bcmolt_l2_mact_dump_status last_dump_result; /**< last dump_result. */
    bcmolt_l2_event_report_control report_event; /**< report learning events. */
} bcmolt_l2_mac_table_cfg_data;

/* Constants associated with bcmolt_l2_mac_table_cfg_data. */
#define BCMOLT_L2_MAC_TABLE_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_L2_MAC_TABLE_CFG_DATA_STATE_DEFAULT BCMOLT_CONFIG_STATE_CONFIGURED
#define BCMOLT_L2_MAC_TABLE_CFG_DATA_DUMP_STATUS_DEFAULT BCMOLT_L2_MACT_DUMP_STATUS_NOT_STARTED
#define BCMOLT_L2_MAC_TABLE_CFG_DATA_LAST_DUMP_RESULT_DEFAULT BCMOLT_L2_MACT_DUMP_STATUS_NOT_STARTED
#define BCMOLT_L2_MAC_TABLE_CFG_DATA_REPORT_EVENT_DEFAULT (bcmolt_l2_event_report_control)0U

/** Transport message definition for "cfg" group of "l2_mac_table" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_l2_mac_table_key key; /**< Object key. */
    bcmolt_l2_mac_table_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_l2_mac_table_cfg;

/** Multi-object message definition for "cfg" group of "l2_mac_table" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_l2_mac_table_key key; /**< Object key (can include wildcards). */
    bcmolt_l2_mac_table_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_l2_mac_table_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_l2_mac_table_cfg *responses; /**< Responses to the last API call. */

    bcmolt_l2_mac_table_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_l2_mac_table_multi_cfg;

/** l2 mac table: l2 mact dump */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_str_128 file_name; /**< file name. */
    bcmolt_l2_dump_mode mode; /**< dump mode. */
    bcmolt_l2_dump_filters filters; /**< dump filters. */
    bcmolt_control_state report_as_indication; /**< report as indication. */
    uint16_t max_entry_per_indication; /**< max number of entries per dump indication. */
} bcmolt_l2_mac_table_dump_data;

/* Constants associated with bcmolt_l2_mac_table_dump_data. */
#define BCMOLT_L2_MAC_TABLE_DUMP_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_L2_MAC_TABLE_DUMP_DATA_MODE_DEFAULT BCMOLT_L2_DUMP_MODE_DYNAMIC
#define BCMOLT_L2_MAC_TABLE_DUMP_DATA_REPORT_AS_INDICATION_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_L2_MAC_TABLE_DUMP_DATA_MAX_ENTRY_PER_INDICATION_DEFAULT 512U

/** Transport message definition for "dump" group of "l2_mac_table" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_l2_mac_table_key key; /**< Object key. */
    bcmolt_l2_mac_table_dump_data data; /**< All properties that must be set by the user. */
} bcmolt_l2_mac_table_dump;

/** l2 mac table: l2 mact dump completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_str_128 file_name; /**< file name. */
    bcmolt_l2_mact_dump_status result; /**< result. */
} bcmolt_l2_mac_table_dump_complete_data;

/* Constants associated with bcmolt_l2_mac_table_dump_complete_data. */
#define BCMOLT_L2_MAC_TABLE_DUMP_COMPLETE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "dump_complete" group of "l2_mac_table" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_l2_mac_table_key key; /**< Object key. */
    bcmolt_l2_mac_table_dump_complete_data data; /**< All properties that must be set by the user. */
} bcmolt_l2_mac_table_dump_complete;

/** Transport message definition for "dump_abort" group of "l2_mac_table" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_l2_mac_table_key key; /**< Object key. */
} bcmolt_l2_mac_table_dump_abort;

/** l2 mac table: network l2 events */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_l2_mact_entry_list_u32 entries; /**< entries. */
} bcmolt_l2_mac_table_network_events_data;

/* Constants associated with bcmolt_l2_mac_table_network_events_data. */
#define BCMOLT_L2_MAC_TABLE_NETWORK_EVENTS_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "network_events" group of "l2_mac_table" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_l2_mac_table_key key; /**< Object key. */
    bcmolt_l2_mac_table_network_events_data data; /**< All properties that must be set by the user. */
} bcmolt_l2_mac_table_network_events;

/** l2 mac table: pon l2 events */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_l2_mact_entry_list_u32 entries; /**< entries. */
} bcmolt_l2_mac_table_pon_events_data;

/* Constants associated with bcmolt_l2_mac_table_pon_events_data. */
#define BCMOLT_L2_MAC_TABLE_PON_EVENTS_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "pon_events" group of "l2_mac_table" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_l2_mac_table_key key; /**< Object key. */
    bcmolt_l2_mac_table_pon_events_data data; /**< All properties that must be set by the user. */
} bcmolt_l2_mac_table_pon_events;

/** l2 mac table: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool dump_complete; /**< If true, indications of type "dump_complete" will be generated. */
    bcmos_bool network_events; /**< If true, indications of type "network_events" will be generated. */
    bcmos_bool pon_events; /**< If true, indications of type "pon_events" will be generated. */
} bcmolt_l2_mac_table_auto_cfg_data;

/* Constants associated with bcmolt_l2_mac_table_auto_cfg_data. */
#define BCMOLT_L2_MAC_TABLE_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "auto_cfg" group of "l2_mac_table" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_l2_mac_table_key key; /**< Object key. */
    bcmolt_l2_mac_table_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_l2_mac_table_auto_cfg;

/** LAG interface: key */
typedef struct
{
    bcmolt_lag_interface_id id; /**< Lag Interface Id */
} bcmolt_lag_interface_key;

/* Constants associated with bcmolt_lag_interface_key. */
#define BCMOLT_LAG_INTERFACE_KEY_ID_MIN (bcmolt_lag_interface_id)0U
#define BCMOLT_LAG_INTERFACE_KEY_ID_MAX (bcmolt_lag_interface_id)31U

/** LAG interface: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state config_state; /**< provisioned or not */
    bcmolt_lag_psc_mode psc_mode; /**< port select criteria */
    bcmolt_interface_state state; /**< lag admin enable/disable */
    bcmolt_protection_type protection_type; /**< Provisioned protection type referencing this LAG interface. */
    bcmolt_arr_nni_id_8 nni_ids; /**< list of member ports */
    bcmolt_arr_link_state_8 member_status; /**< link status of members */
    uint8_t member_count; /**< num of members */
    uint8_t member_up_count; /**< num of link up members */
    bcmolt_lag_health lag_health; /**< health of lag */
    bcmolt_lag_subtype sub_type; /**< lag interface subtype */
} bcmolt_lag_interface_cfg_data;

/* Constants associated with bcmolt_lag_interface_cfg_data. */
#define BCMOLT_LAG_INTERFACE_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000003EB3ULL
#define BCMOLT_LAG_INTERFACE_CFG_DATA_CONFIG_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED
#define BCMOLT_LAG_INTERFACE_CFG_DATA_PSC_MODE_DEFAULT BCMOLT_LAG_PSC_MODE_SMOOTH_DIVISION
#define BCMOLT_LAG_INTERFACE_CFG_DATA_STATE_DEFAULT BCMOLT_INTERFACE_STATE_ACTIVE_WORKING
#define BCMOLT_LAG_INTERFACE_CFG_DATA_NNI_IDS_LENGTH 8
#define BCMOLT_LAG_INTERFACE_CFG_DATA_MEMBER_STATUS_LENGTH 8
#define BCMOLT_LAG_INTERFACE_CFG_DATA_MEMBER_COUNT_DEFAULT 0
#define BCMOLT_LAG_INTERFACE_CFG_DATA_MEMBER_UP_COUNT_DEFAULT 0
#define BCMOLT_LAG_INTERFACE_CFG_DATA_LAG_HEALTH_DEFAULT BCMOLT_LAG_HEALTH_DOWN

/** Transport message definition for "cfg" group of "lag_interface" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_cfg;

/** Multi-object message definition for "cfg" group of "lag_interface" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key (can include wildcards). */
    bcmolt_lag_interface_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_lag_interface_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_lag_interface_cfg *responses; /**< Responses to the last API call. */

    bcmolt_lag_interface_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_lag_interface_multi_cfg;

/** LAG interface: LAG Interface Statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t rx_bytes; /**< RFC 2233 */
    uint64_t rx_packets; /**< RFC 1213 ucast + none-ucast */
    uint64_t rx_ucast_packets; /**< RFC 2233 */
    uint64_t rx_mcast_packets; /**< EFC 2233 */
    uint64_t rx_bcast_packets; /**< RFC 2233 */
    uint64_t rx_error_packets; /**< RFC 1213 */
    uint64_t rx_fcs_error_packets; /**< RFC 2665 */
    uint64_t rx_undersize_packets; /**< Broadcom-Specific */
    uint64_t rx_oversize_packets; /**< Rx component of RFC 2665 snmpEtherStatsOversizePkts */
    uint64_t rx_jabber_packets; /**< RFC 1757 (EtherStat) */
    uint64_t tx_bytes; /**< RFC 2233 */
    uint64_t tx_packets; /**< RFC 1213 ucast + none-ucast */
    uint64_t tx_ucast_packets; /**< RFC 2233 */
    uint64_t tx_mcast_packets; /**< RFC 2233 */
    uint64_t tx_bcast_packets; /**< RFC 2233 */
    uint64_t tx_error_packets; /**< RFC 1213 */
    uint64_t tx_undersize_packets; /**< Broadcom-Specific */
    uint64_t tx_oversize_packets; /**< Tx component of RFC 2665 snmpEtherStatsOversizePkts */
    uint64_t tx_jabber_packets; /**< RFC 1757 (EtherStat) */
    uint64_t rx_frames_64; /**< Broadcom-Specific */
    uint64_t rx_frames_65_127; /**< Broadcom-Specific */
    uint64_t rx_frames_128_255; /**< Broadcom-Specific */
    uint64_t rx_frames_256_511; /**< Broadcom-Specific */
    uint64_t rx_frames_512_1023; /**< Broadcom-Specific */
    uint64_t rx_frames_1024_1518; /**< Broadcom-Specific */
    uint64_t rx_frames_1519_2047; /**< Broadcom-Specific */
    uint64_t rx_frames_2048_4095; /**< Broadcom-Specific */
    uint64_t rx_frames_4096_9216; /**< Broadcom-Specific */
    uint64_t rx_frames_9217_16383; /**< Broadcom-Specific */
    uint64_t tx_frames_64; /**< Broadcom-Specific */
    uint64_t tx_frames_65_127; /**< Broadcom-Specific */
    uint64_t tx_frames_128_255; /**< Broadcom-Specific */
    uint64_t tx_frames_256_511; /**< Broadcom-Specific */
    uint64_t tx_frames_512_1023; /**< Broadcom-Specific */
    uint64_t tx_frames_1024_1518; /**< Broadcom-Specific */
    uint64_t tx_frames_1519_2047; /**< Broadcom-Specific */
    uint64_t tx_frames_2048_4095; /**< Broadcom-Specific */
    uint64_t tx_frames_4096_9216; /**< Broadcom-Specific */
    uint64_t tx_frames_9217_16383; /**< Broadcom-Specific */
} bcmolt_lag_interface_stats_data;

/* Constants associated with bcmolt_lag_interface_stats_data. */
#define BCMOLT_LAG_INTERFACE_STATS_DATA_PRESENCE_MASK_ALL 0x000000FFFFFFFFBFULL

/** Transport message definition for "stats" group of "lag_interface" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_stats;

/** Multi-object message definition for "stats" group of "lag_interface" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key (can include wildcards). */
    bcmolt_lag_interface_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_lag_interface_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_lag_interface_stats *responses; /**< Responses to the last API call. */

    bcmolt_lag_interface_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_lag_interface_multi_stats;

/** LAG interface: members_update */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_lag_interface_members_update_command members_cmd; /**< members_cmd. */
} bcmolt_lag_interface_members_update_data;

/* Constants associated with bcmolt_lag_interface_members_update_data. */
#define BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "members_update" group of "lag_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_members_update_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_members_update;

/** LAG interface: complete_members_update */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< result. */
    bcmolt_lag_member_update_fail_reason fail_reason; /**< fail reason. */
} bcmolt_lag_interface_complete_members_update_data;

/* Constants associated with bcmolt_lag_interface_complete_members_update_data. */
#define BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "complete_members_update" group of "lag_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_complete_members_update_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_complete_members_update;

/** LAG interface: state_update */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_interface_operation lag_state; /**< lag_state. */
} bcmolt_lag_interface_state_update_data;

/* Constants associated with bcmolt_lag_interface_state_update_data. */
#define BCMOLT_LAG_INTERFACE_STATE_UPDATE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_LAG_INTERFACE_STATE_UPDATE_DATA_LAG_STATE_DEFAULT BCMOLT_INTERFACE_OPERATION_ACTIVE_WORKING

/** Transport message definition for "state_update" group of "lag_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_state_update_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_state_update;

/** LAG interface: interface state updated */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_interface_state new_state; /**< current interface state */
    bcmolt_interface_state old_state; /**< previous interface state */
    bcmolt_link_fault_code fault_code; /**< fault_code. */
} bcmolt_lag_interface_state_updated_data;

/* Constants associated with bcmolt_lag_interface_state_updated_data. */
#define BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "state_updated" group of "lag_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_state_updated_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_state_updated;

/** LAG interface: LAG health change */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_lag_health new_state; /**< LAG health */
    bcmolt_lag_health old_state; /**< old state. */
} bcmolt_lag_interface_lag_health_change_data;

/* Constants associated with bcmolt_lag_interface_lag_health_change_data. */
#define BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "lag_health_change" group of "lag_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_lag_health_change_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_lag_health_change;

/** LAG interface: LAG Interface Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config rx_bytes; /**< RFC 2233 */
    bcmolt_stat_alarm_config rx_packets; /**< RFC 1213 ucast + none-ucast */
    bcmolt_stat_alarm_config rx_ucast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config rx_mcast_packets; /**< EFC 2233 */
    bcmolt_stat_alarm_config rx_bcast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config rx_error_packets; /**< RFC 1213 */
    bcmolt_stat_alarm_config rx_fcs_error_packets; /**< RFC 2665 */
    bcmolt_stat_alarm_config rx_undersize_packets; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_oversize_packets; /**< Rx component of RFC 2665 snmpEtherStatsOversizePkts */
    bcmolt_stat_alarm_config rx_jabber_packets; /**< RFC 1757 (EtherStat) */
    bcmolt_stat_alarm_config tx_bytes; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_packets; /**< RFC 1213 ucast + none-ucast */
    bcmolt_stat_alarm_config tx_ucast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_mcast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_bcast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_error_packets; /**< RFC 1213 */
    bcmolt_stat_alarm_config tx_undersize_packets; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_oversize_packets; /**< Tx component of RFC 2665 snmpEtherStatsOversizePkts */
    bcmolt_stat_alarm_config tx_jabber_packets; /**< RFC 1757 (EtherStat) */
    bcmolt_stat_alarm_config rx_frames_64; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_65_127; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_128_255; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_256_511; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_512_1023; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_1024_1518; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_1519_2047; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_2048_4095; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_4096_9216; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_9217_16383; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_64; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_65_127; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_128_255; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_256_511; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_512_1023; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_1024_1518; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_1519_2047; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_2048_4095; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_4096_9216; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_9217_16383; /**< Broadcom-Specific */
} bcmolt_lag_interface_stats_cfg_data;

/* Constants associated with bcmolt_lag_interface_stats_cfg_data. */
#define BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x000000FFFFFFFFBFULL

/** Transport message definition for "stats_cfg" group of "lag_interface" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_stats_cfg;

/** LAG interface: LAG Interface Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_lag_interface_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_lag_interface_stats_alarm_raised_data;

/* Constants associated with bcmolt_lag_interface_stats_alarm_raised_data. */
#define BCMOLT_LAG_INTERFACE_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_raised" group of "lag_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_stats_alarm_raised;

/** LAG interface: LAG Interface Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_lag_interface_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_lag_interface_stats_alarm_cleared_data;

/* Constants associated with bcmolt_lag_interface_stats_alarm_cleared_data. */
#define BCMOLT_LAG_INTERFACE_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_cleared" group of "lag_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_stats_alarm_cleared;

/** LAG interface: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool complete_members_update; /**< If true, indications of type "complete_members_update" will be generated. */
    bcmos_bool lag_health_change; /**< If true, indications of type "lag_health_change" will be generated. */
    bcmos_bool state_updated; /**< If true, indications of type "state_updated" will be generated. */
    bcmos_bool stats_alarm_cleared; /**< If true, indications of type "stats_alarm_cleared" will be generated. */
    bcmos_bool stats_alarm_raised; /**< If true, indications of type "stats_alarm_raised" will be generated. */
} bcmolt_lag_interface_auto_cfg_data;

/* Constants associated with bcmolt_lag_interface_auto_cfg_data. */
#define BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL

/** Transport message definition for "auto_cfg" group of "lag_interface" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_lag_interface_key key; /**< Object key. */
    bcmolt_lag_interface_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_lag_interface_auto_cfg;

/** Log: key */
typedef struct
{
    bcmolt_ldid device_id; /**< Device ID */
    bcmolt_str_100 name; /**< Log name */
} bcmolt_log_key;

/** Log: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_log_type type; /**< Log type */
    bcmolt_log_style style; /**< Log style */
    bcmolt_log_level_per_file level; /**< Log levels for each file */
    bcmolt_log_level_msg_count msg_count; /**< Number of messages per log level */
    uint32_t lost_msg_count; /**< Number of messages lost/dropped */
} bcmolt_log_cfg_data;

/* Constants associated with bcmolt_log_cfg_data. */
#define BCMOLT_LOG_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL

/** Transport message definition for "cfg" group of "log" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_log_key key; /**< Object key. */
    bcmolt_log_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_log_cfg;

/** Multi-object message definition for "cfg" group of "log" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_log_key key; /**< Object key (can include wildcards). */
    bcmolt_log_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_log_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_log_cfg *responses; /**< Responses to the last API call. */

    bcmolt_log_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_log_multi_cfg;

/** Log File: key */
typedef struct
{
    bcmolt_ldid device_id; /**< Device ID */
    bcmolt_log_file_id file_id; /**< Which log file to access */
} bcmolt_log_file_key;

/** Log File: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool wrap_around; /**< Log file wrap-around option. TRUE=wrap around when full. FALSE=stop when full */
    bcmos_bool clear_after_read; /**< Clear log after last record has been read */
    uint32_t msg_count; /**< Number of messages currently in the log */
    uint32_t msgs_read; /**< Number of messages already read */
    uint32_t msgs_remaining; /**< Number of unread messages remaining in the log file */
    bcmolt_str_2048 buffer; /**< Contains a section of the log buffer, one message per line. Reading this field causes it to move to the next section. */
} bcmolt_log_file_cfg_data;

/* Constants associated with bcmolt_log_file_cfg_data. */
#define BCMOLT_LOG_FILE_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000003FULL
#define BCMOLT_LOG_FILE_CFG_DATA_WRAP_AROUND_DEFAULT BCMOS_TRUE
#define BCMOLT_LOG_FILE_CFG_DATA_CLEAR_AFTER_READ_DEFAULT BCMOS_FALSE

/** Transport message definition for "cfg" group of "log_file" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_log_file_key key; /**< Object key. */
    bcmolt_log_file_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_log_file_cfg;

/** Multi-object message definition for "cfg" group of "log_file" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_log_file_key key; /**< Object key (can include wildcards). */
    bcmolt_log_file_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_log_file_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_log_file_cfg *responses; /**< Responses to the last API call. */

    bcmolt_log_file_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_log_file_multi_cfg;

/** Transport message definition for "clear" group of "log_file" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_log_file_key key; /**< Object key. */
} bcmolt_log_file_clear;

/** Transport message definition for "reset_buffer_ptr" group of "log_file" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_log_file_key key; /**< Object key. */
} bcmolt_log_file_reset_buffer_ptr;

/** Channel: key */
typedef struct
{
    bcmolt_interface pon_ni; /**< PON network interface. */
} bcmolt_ngpon2_channel_key;

/** Channel: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_system_profile system_profile; /**< System profile. */
    bcmolt_arr_channel_profile_8 channel_profile; /**< Channel profile. */
} bcmolt_ngpon2_channel_cfg_data;

/* Constants associated with bcmolt_ngpon2_channel_cfg_data. */
#define BCMOLT_NGPON2_CHANNEL_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_NGPON2_CHANNEL_CFG_DATA_CHANNEL_PROFILE_LENGTH 8

/** Transport message definition for "cfg" group of "ngpon2_channel" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_ngpon2_channel_key key; /**< Object key. */
    bcmolt_ngpon2_channel_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_ngpon2_channel_cfg;

/** Multi-object message definition for "cfg" group of "ngpon2_channel" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_ngpon2_channel_key key; /**< Object key (can include wildcards). */
    bcmolt_ngpon2_channel_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_ngpon2_channel_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_ngpon2_channel_cfg *responses; /**< Responses to the last API call. */

    bcmolt_ngpon2_channel_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_ngpon2_channel_multi_cfg;

/** nni_interface: key */
typedef struct
{
    bcmolt_nni_id id; /**< id */
} bcmolt_nni_interface_key;

/* Constants associated with bcmolt_nni_interface_key. */
#define BCMOLT_NNI_INTERFACE_KEY_ID_DEFAULT (bcmolt_nni_id)255

/** nni_interface: State Change */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< State Change Request result (Success / Failure). */
    bcmolt_interface_state old_state; /**< Previous Interface state. */
    bcmolt_interface_state new_state; /**< New Interface state. */
} bcmolt_nni_interface_state_change_data;

/* Constants associated with bcmolt_nni_interface_state_change_data. */
#define BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "state_change" group of "nni_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_state_change_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_state_change;

/** nni_interface: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state config_state; /**< config_state. */
    bcmolt_interface_state state; /**< state. */
    bcmolt_protection_type protection_type; /**< Provisioned protection type on this NNI interface */
    bcmolt_link_state link_state; /**< Current Link State (Link Up or Link Down) */
    bcmolt_link_fault_code link_fault_code; /**< Link Fault Code (Local or Remote Fault) */
    bcmolt_str_48 description; /**< Descriptive string */
    uint32_t mtu; /**< max frame size in bytes (including ethernet header and CRC) */
    uint32_t speed; /**< ethernet speed in Mbps */
    bcmolt_duplex_mode duplex; /**< ethernet duplex mode */
    bcmolt_control_state auto_negotiate; /**< ethernet auto negotiation mode */
    bcmolt_nni_subtype sub_type; /**< nni interface subtype */
} bcmolt_nni_interface_cfg_data;

/* Constants associated with bcmolt_nni_interface_cfg_data. */
#define BCMOLT_NNI_INTERFACE_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000001F7BULL
#define BCMOLT_NNI_INTERFACE_CFG_DATA_CONFIG_STATE_DEFAULT BCMOLT_CONFIG_STATE_CONFIGURED
#define BCMOLT_NNI_INTERFACE_CFG_DATA_MTU_DEFAULT 9600UL
#define BCMOLT_NNI_INTERFACE_CFG_DATA_MTU_MIN 261UL
#define BCMOLT_NNI_INTERFACE_CFG_DATA_MTU_MAX 9600UL

/** Transport message definition for "cfg" group of "nni_interface" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_cfg;

/** Multi-object message definition for "cfg" group of "nni_interface" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key (can include wildcards). */
    bcmolt_nni_interface_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_nni_interface_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_nni_interface_cfg *responses; /**< Responses to the last API call. */

    bcmolt_nni_interface_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_nni_interface_multi_cfg;

/** nni_interface: set_nni_state */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_interface_operation nni_state; /**< nni_state. */
} bcmolt_nni_interface_set_nni_state_data;

/* Constants associated with bcmolt_nni_interface_set_nni_state_data. */
#define BCMOLT_NNI_INTERFACE_SET_NNI_STATE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "set_nni_state" group of "nni_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_set_nni_state_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_set_nni_state;

/** nni_interface: NNI Interface Statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t rx_bytes; /**< RFC 2233 */
    uint64_t rx_packets; /**< RFC 1213 ucast + none-ucast */
    uint64_t rx_ucast_packets; /**< RFC 2233 */
    uint64_t rx_mcast_packets; /**< EFC 2233 */
    uint64_t rx_bcast_packets; /**< RFC 2233 */
    uint64_t rx_error_packets; /**< RFC 1213 */
    uint64_t rx_fcs_error_packets; /**< RFC 2665 */
    uint64_t rx_undersize_packets; /**< Broadcom-Specific */
    uint64_t rx_oversize_packets; /**< Rx component of RFC 2665 snmpEtherStatsOversizePkts */
    uint64_t rx_jabber_packets; /**< RFC 1757 (EtherStat) */
    uint64_t tx_bytes; /**< RFC 2233 */
    uint64_t tx_packets; /**< RFC 1213 ucast + none-ucast */
    uint64_t tx_ucast_packets; /**< RFC 2233 */
    uint64_t tx_mcast_packets; /**< RFC 2233 */
    uint64_t tx_bcast_packets; /**< RFC 2233 */
    uint64_t tx_error_packets; /**< RFC 1213 */
    uint64_t tx_undersize_packets; /**< Broadcom-Specific */
    uint64_t tx_oversize_packets; /**< Tx component of RFC 2665 snmpEtherStatsOversizePkts */
    uint64_t tx_jabber_packets; /**< RFC 1757 (EtherStat) */
    uint64_t rx_frames_64; /**< Broadcom-Specific */
    uint64_t rx_frames_65_127; /**< Broadcom-Specific */
    uint64_t rx_frames_128_255; /**< Broadcom-Specific */
    uint64_t rx_frames_256_511; /**< Broadcom-Specific */
    uint64_t rx_frames_512_1023; /**< Broadcom-Specific */
    uint64_t rx_frames_1024_1518; /**< Broadcom-Specific */
    uint64_t rx_frames_1519_2047; /**< Broadcom-Specific */
    uint64_t rx_frames_2048_4095; /**< Broadcom-Specific */
    uint64_t rx_frames_4096_9216; /**< Broadcom-Specific */
    uint64_t rx_frames_9217_16383; /**< Broadcom-Specific */
    uint64_t tx_frames_64; /**< Broadcom-Specific */
    uint64_t tx_frames_65_127; /**< Broadcom-Specific */
    uint64_t tx_frames_128_255; /**< Broadcom-Specific */
    uint64_t tx_frames_256_511; /**< Broadcom-Specific */
    uint64_t tx_frames_512_1023; /**< Broadcom-Specific */
    uint64_t tx_frames_1024_1518; /**< Broadcom-Specific */
    uint64_t tx_frames_1519_2047; /**< Broadcom-Specific */
    uint64_t tx_frames_2048_4095; /**< Broadcom-Specific */
    uint64_t tx_frames_4096_9216; /**< Broadcom-Specific */
    uint64_t tx_frames_9217_16383; /**< Broadcom-Specific */
} bcmolt_nni_interface_stats_data;

/* Constants associated with bcmolt_nni_interface_stats_data. */
#define BCMOLT_NNI_INTERFACE_STATS_DATA_PRESENCE_MASK_ALL 0x000000FFFFFFFFBFULL

/** Transport message definition for "stats" group of "nni_interface" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_stats;

/** Multi-object message definition for "stats" group of "nni_interface" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key (can include wildcards). */
    bcmolt_nni_interface_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_nni_interface_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_nni_interface_stats *responses; /**< Responses to the last API call. */

    bcmolt_nni_interface_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_nni_interface_multi_stats;

/** nni_interface: link_state_change */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_link_state old_state; /**< old_state. */
    bcmolt_link_state new_state; /**< new_state. */
} bcmolt_nni_interface_link_state_change_data;

/* Constants associated with bcmolt_nni_interface_link_state_change_data. */
#define BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "link_state_change" group of "nni_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_link_state_change_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_link_state_change;

/** nni_interface: fault_code_change */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_link_fault_code old_fault_code; /**< old_fault_code. */
    bcmolt_link_fault_code new_fault_code; /**< new_fault_code. */
} bcmolt_nni_interface_fault_code_change_data;

/* Constants associated with bcmolt_nni_interface_fault_code_change_data. */
#define BCMOLT_NNI_INTERFACE_FAULT_CODE_CHANGE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "fault_code_change" group of "nni_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_fault_code_change_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_fault_code_change;

/** nni_interface: NNI Interface Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config rx_bytes; /**< RFC 2233 */
    bcmolt_stat_alarm_config rx_packets; /**< RFC 1213 ucast + none-ucast */
    bcmolt_stat_alarm_config rx_ucast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config rx_mcast_packets; /**< EFC 2233 */
    bcmolt_stat_alarm_config rx_bcast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config rx_error_packets; /**< RFC 1213 */
    bcmolt_stat_alarm_config rx_fcs_error_packets; /**< RFC 2665 */
    bcmolt_stat_alarm_config rx_undersize_packets; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_oversize_packets; /**< Rx component of RFC 2665 snmpEtherStatsOversizePkts */
    bcmolt_stat_alarm_config rx_jabber_packets; /**< RFC 1757 (EtherStat) */
    bcmolt_stat_alarm_config tx_bytes; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_packets; /**< RFC 1213 ucast + none-ucast */
    bcmolt_stat_alarm_config tx_ucast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_mcast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_bcast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_error_packets; /**< RFC 1213 */
    bcmolt_stat_alarm_config tx_undersize_packets; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_oversize_packets; /**< Tx component of RFC 2665 snmpEtherStatsOversizePkts */
    bcmolt_stat_alarm_config tx_jabber_packets; /**< RFC 1757 (EtherStat) */
    bcmolt_stat_alarm_config rx_frames_64; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_65_127; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_128_255; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_256_511; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_512_1023; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_1024_1518; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_1519_2047; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_2048_4095; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_4096_9216; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_9217_16383; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_64; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_65_127; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_128_255; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_256_511; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_512_1023; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_1024_1518; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_1519_2047; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_2048_4095; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_4096_9216; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_9217_16383; /**< Broadcom-Specific */
} bcmolt_nni_interface_stats_cfg_data;

/* Constants associated with bcmolt_nni_interface_stats_cfg_data. */
#define BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x000000FFFFFFFFBFULL

/** Transport message definition for "stats_cfg" group of "nni_interface" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_stats_cfg;

/** nni_interface: NNI Interface Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_nni_interface_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_nni_interface_stats_alarm_raised_data;

/* Constants associated with bcmolt_nni_interface_stats_alarm_raised_data. */
#define BCMOLT_NNI_INTERFACE_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_raised" group of "nni_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_stats_alarm_raised;

/** nni_interface: NNI Interface Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_nni_interface_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_nni_interface_stats_alarm_cleared_data;

/* Constants associated with bcmolt_nni_interface_stats_alarm_cleared_data. */
#define BCMOLT_NNI_INTERFACE_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_cleared" group of "nni_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_stats_alarm_cleared;

/** nni_interface: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool fault_code_change; /**< If true, indications of type "fault_code_change" will be generated. */
    bcmos_bool link_state_change; /**< If true, indications of type "link_state_change" will be generated. */
    bcmos_bool state_change; /**< If true, indications of type "state_change" will be generated. */
    bcmos_bool stats_alarm_cleared; /**< If true, indications of type "stats_alarm_cleared" will be generated. */
    bcmos_bool stats_alarm_raised; /**< If true, indications of type "stats_alarm_raised" will be generated. */
} bcmolt_nni_interface_auto_cfg_data;

/* Constants associated with bcmolt_nni_interface_auto_cfg_data. */
#define BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL

/** Transport message definition for "auto_cfg" group of "nni_interface" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_nni_interface_key key; /**< Object key. */
    bcmolt_nni_interface_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_nni_interface_auto_cfg;

/** olt: key */
typedef struct
{
    uint8_t reserved; /**< Reserved (set to 0) */
} bcmolt_olt_key;

/* Constants associated with bcmolt_olt_key. */
#define BCMOLT_OLT_KEY_RESERVED_DEFAULT 0

/** olt: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_topology topology; /**< Topology as configured in Topology.ini */
    bcmolt_bal_state bal_state; /**< BAL and Switch device state */
    bcmolt_host_sw_version host_sw_version; /**< Host Software version */
} bcmolt_olt_cfg_data;

/* Constants associated with bcmolt_olt_cfg_data. */
#define BCMOLT_OLT_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "cfg" group of "olt" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key. */
    bcmolt_olt_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_olt_cfg;

/** Multi-object message definition for "cfg" group of "olt" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key (can include wildcards). */
    bcmolt_olt_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_olt_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_olt_cfg *responses; /**< Responses to the last API call. */

    bcmolt_olt_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_olt_multi_cfg;

/** Transport message definition for "connect" group of "olt" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key. */
} bcmolt_olt_connect;

/** Transport message definition for "disconnect" group of "olt" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key. */
} bcmolt_olt_disconnect;

/** Transport message definition for "bal_reset" group of "olt" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key. */
} bcmolt_olt_bal_reset;

/** olt: BAL and/or Switch Failed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bal_fail_reason reason; /**< Disconnect reason */
} bcmolt_olt_bal_failure_data;

/* Constants associated with bcmolt_olt_bal_failure_data. */
#define BCMOLT_OLT_BAL_FAILURE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "bal_failure" group of "olt" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key. */
    bcmolt_olt_bal_failure_data data; /**< All properties that must be set by the user. */
} bcmolt_olt_bal_failure;

/** Transport message definition for "bal_ready" group of "olt" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key. */
} bcmolt_olt_bal_ready;

/** olt: OLT Software error */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_str_100 task_name; /**< Task Name. */
    bcmolt_str_100 file_name; /**< File Name. */
    uint32_t line_number; /**< Line Number. */
    bcmolt_str_256 error_string; /**< User error string. */
    bcmolt_sw_error_severity severity; /**< Severity. */
} bcmolt_olt_sw_error_data;

/* Constants associated with bcmolt_olt_sw_error_data. */
#define BCMOLT_OLT_SW_ERROR_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL

/** Transport message definition for "sw_error" group of "olt" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key. */
    bcmolt_olt_sw_error_data data; /**< All properties that must be set by the user. */
} bcmolt_olt_sw_error;

/** olt: OLT Reset */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_reset_mode mode; /**< Reset Mode. */
} bcmolt_olt_reset_data;

/* Constants associated with bcmolt_olt_reset_data. */
#define BCMOLT_OLT_RESET_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "reset" group of "olt" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key. */
    bcmolt_olt_reset_data data; /**< All properties that must be set by the user. */
} bcmolt_olt_reset;

/** olt: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool bal_failure; /**< If true, indications of type "bal_failure" will be generated. */
    bcmos_bool bal_ready; /**< If true, indications of type "bal_ready" will be generated. */
    bcmos_bool sw_error; /**< If true, indications of type "sw_error" will be generated. */
} bcmolt_olt_auto_cfg_data;

/* Constants associated with bcmolt_olt_auto_cfg_data. */
#define BCMOLT_OLT_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "auto_cfg" group of "olt" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_olt_key key; /**< Object key. */
    bcmolt_olt_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_olt_auto_cfg;

/** ONU: key */
typedef struct
{
    bcmolt_interface pon_ni; /**< PON network interface. */
    bcmolt_onu_id onu_id; /**< onu id. */
} bcmolt_onu_key;

/** ONU: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_state onu_state; /**< Current ONU state */
    bcmolt_onu_state onu_old_state; /**< onu old state. */
    bcmolt_onu_rate onu_rate; /**< ONU rate. */
    bcmolt_itu_onu_params itu; /**< ITU ONU Parameters (GPON, XGPON1, NGPON2, XGS PON). */
} bcmolt_onu_cfg_data;

/* Constants associated with bcmolt_onu_cfg_data. */
#define BCMOLT_ONU_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_ONU_CFG_DATA_ONU_STATE_DEFAULT BCMOLT_ONU_STATE_NOT_CONFIGURED
#define BCMOLT_ONU_CFG_DATA_ONU_OLD_STATE_DEFAULT BCMOLT_ONU_STATE_NOT_CONFIGURED

/** Transport message definition for "cfg" group of "onu" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_cfg;

/** Multi-object message definition for "cfg" group of "onu" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key (can include wildcards). */
    bcmolt_onu_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_onu_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_onu_cfg *responses; /**< Responses to the last API call. */

    bcmolt_onu_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_onu_multi_cfg;

/** ONU: ITU PON Statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t positive_drift; /**< positive drift. */
    uint64_t negative_drift; /**< negative drift. */
    uint64_t delimiter_miss_detection; /**< unreceived bursts */
    uint64_t bip_errors; /**< bip errors. */
    uint64_t bip_units; /**< Number of 4-byte words xgpon or bytes gpon received (word size is 4 bytes regardless of upstream data rate). */
    uint64_t fec_corrected_symbols; /**< fec corrected symbols  (Not relevant in GPON system modes). */
    uint64_t fec_codewords_corrected; /**< fec corrected codewords. */
    uint64_t fec_codewords_uncorrectable; /**< fec uncorrectable codewords. */
    uint64_t fec_codewords; /**< fec total codewords. */
    uint64_t fec_corrected_units; /**< fec corrected units (In GPON units are bits in other system modes, units are Bytes). */
    uint64_t xgem_key_errors; /**< xgem key error. */
    uint64_t xgem_loss; /**< xgem loss. */
    uint64_t rx_ploams_error; /**< mic error ploam. */
    uint64_t rx_ploams_non_idle; /**< non idle ploam. */
    uint64_t rx_omci; /**< Received OMCI packets. */
    uint64_t rx_omci_packets_crc_error; /**< Received OMCI packets with CRC errors. */
    uint64_t rx_bytes; /**< rx bytes. */
    uint64_t rx_packets; /**< rx packets. */
    uint64_t tx_bytes; /**< tx bytes. */
    uint64_t tx_packets; /**< tx packets. */
    uint64_t ber_reported; /**< gpon only */
    uint64_t lcdg_errors; /**< LCDG errors. */
    uint64_t rdi_errors; /**< RDI errors. */
} bcmolt_onu_itu_pon_stats_data;

/* Constants associated with bcmolt_onu_itu_pon_stats_data. */
#define BCMOLT_ONU_ITU_PON_STATS_DATA_PRESENCE_MASK_ALL 0x00000000007FFFFFULL

/** Transport message definition for "itu_pon_stats" group of "onu" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_itu_pon_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_itu_pon_stats;

/** Multi-object message definition for "itu_pon_stats" group of "onu" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key (can include wildcards). */
    bcmolt_onu_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_onu_itu_pon_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_onu_itu_pon_stats *responses; /**< Responses to the last API call. */

    bcmolt_onu_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_onu_multi_itu_pon_stats;

/** ONU: Set ONU State */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_operation onu_state; /**< ONU state. */
    bcmos_bool measure_rssi; /**< Enable RSSI measurement during activation. */
} bcmolt_onu_set_onu_state_data;

/* Constants associated with bcmolt_onu_set_onu_state_data. */
#define BCMOLT_ONU_SET_ONU_STATE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_ONU_SET_ONU_STATE_DATA_MEASURE_RSSI_DEFAULT BCMOS_FALSE

/** Transport message definition for "set_onu_state" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_set_onu_state_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_set_onu_state;

/** Transport message definition for "rssi_measurement" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
} bcmolt_onu_rssi_measurement;

/** ONU: Request registration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool sma_flag; /**< Is the request registration process is part of the SMA process */
} bcmolt_onu_request_registration_data;

/* Constants associated with bcmolt_onu_request_registration_data. */
#define BCMOLT_ONU_REQUEST_REGISTRATION_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_ONU_REQUEST_REGISTRATION_DATA_SMA_FLAG_DEFAULT BCMOS_FALSE

/** Transport message definition for "request_registration" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_request_registration_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_request_registration;

/** ONU: Change power levelling */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_power_levelling_control control; /**< control. */
    uint8_t attenuation; /**< The requested attenuation in steps of 3dB as part of power levelling instruction */
} bcmolt_onu_change_power_levelling_data;

/* Constants associated with bcmolt_onu_change_power_levelling_data. */
#define BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "change_power_levelling" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_change_power_levelling_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_change_power_levelling;

/** Transport message definition for "get_power_level" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
} bcmolt_onu_get_power_level;

/** Transport message definition for "get_power_consumption" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
} bcmolt_onu_get_power_consumption;

/** ONU: Adjust Tx wavelength */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_frequency_adjustment_direction frequency_adjustment_direction; /**< Frequency adjustment direction. */
    uint8_t frequency_adjustment_size; /**< The size of the frequency adjustment in units of 0.1GHz */
} bcmolt_onu_adjust_tx_wavelength_data;

/* Constants associated with bcmolt_onu_adjust_tx_wavelength_data. */
#define BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "adjust_tx_wavelength" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_adjust_tx_wavelength_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_adjust_tx_wavelength;

/** ONU: Secure mutual authentication */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_aes_key master_key; /**< master key. */
    bcmolt_bin_str buffer; /**< OMCI data buffer. */
    uint32_t mic; /**< mic. */
} bcmolt_onu_secure_mutual_authentication_data;

/* Constants associated with bcmolt_onu_secure_mutual_authentication_data. */
#define BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "secure_mutual_authentication" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_secure_mutual_authentication_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_secure_mutual_authentication;

/** Transport message definition for "tuning_in" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
} bcmolt_onu_tuning_in;

/** ONU: ONU Tuning out */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_pon_id target_ds_pon_id; /**< target ds pon id. */
    bcmolt_pon_id target_us_pon_id; /**< target us pon id. */
    uint32_t time_to_switch; /**< Time to switch in ms */
    bcmos_bool rollback; /**< rollback. */
    bcmolt_status status; /**< on- to start tuning out off- to stop tuning out */
} bcmolt_onu_tuning_out_data;

/* Constants associated with bcmolt_onu_tuning_out_data. */
#define BCMOLT_ONU_TUNING_OUT_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_ONU_TUNING_OUT_DATA_TIME_TO_SWITCH_MIN 500UL
#define BCMOLT_ONU_TUNING_OUT_DATA_ROLLBACK_DEFAULT BCMOS_FALSE

/** Transport message definition for "tuning_out" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_tuning_out_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_tuning_out;

/** ONU: XGPON ONU Alarm */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_xgpon_onu_alarms xgpon_onu_alarm; /**< xgpon onu alarm. */
} bcmolt_onu_xgpon_alarm_data;

/* Constants associated with bcmolt_onu_xgpon_alarm_data. */
#define BCMOLT_ONU_XGPON_ALARM_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "xgpon_alarm" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_xgpon_alarm_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_xgpon_alarm;

/** ONU: GPON ONU Alarm */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_gpon_onu_alarms gpon_onu_alarm; /**< gpon onu alarm. */
} bcmolt_onu_gpon_alarm_data;

/* Constants associated with bcmolt_onu_gpon_alarm_data. */
#define BCMOLT_ONU_GPON_ALARM_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "gpon_alarm" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_gpon_alarm_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_gpon_alarm;

/** ONU: Drift of Window of ONUi */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< Alarm status. */
    int32_t drift_value; /**< Calculated amount of drift (positive + negative as a signed value). */
    uint32_t new_eqd; /**< New EQD after drift is corrected (only valid if status is 'on'). */
} bcmolt_onu_dowi_data;

/* Constants associated with bcmolt_onu_dowi_data. */
#define BCMOLT_ONU_DOWI_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "dowi" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_dowi_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_dowi;

/** ONU: Signal Fail of ONUi */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
    uint32_t ber; /**< Inverse bit error rate (e.g. if this number is 1000, the BER is 1/1000). */
} bcmolt_onu_sfi_data;

/* Constants associated with bcmolt_onu_sfi_data. */
#define BCMOLT_ONU_SFI_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "sfi" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_sfi_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_sfi;

/** ONU: Signal Degraded of ONUi */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
    uint32_t ber; /**< Inverse bit error rate (e.g. if this number is 1000, the BER is 1/1000). */
} bcmolt_onu_sdi_data;

/* Constants associated with bcmolt_onu_sdi_data. */
#define BCMOLT_ONU_SDI_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "sdi" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_sdi_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_sdi;

/** ONU: Receive Dying-Gasp of ONUi */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
} bcmolt_onu_dfi_data;

/* Constants associated with bcmolt_onu_dfi_data. */
#define BCMOLT_ONU_DFI_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "dfi" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_dfi_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_dfi;

/** ONU: ploam queue status */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
} bcmolt_onu_pqsi_data;

/* Constants associated with bcmolt_onu_pqsi_data. */
#define BCMOLT_ONU_PQSI_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "pqsi" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_pqsi_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_pqsi;

/** ONU: SUFi */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
} bcmolt_onu_sufi_data;

/* Constants associated with bcmolt_onu_sufi_data. */
#define BCMOLT_ONU_SUFI_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "sufi" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_sufi_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_sufi;

/** ONU: Transmission Interference Warning */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< Alarm status. */
    int32_t drift_value; /**< Calculated amount of drift (positive + negative as a signed value). */
} bcmolt_onu_tiwi_data;

/* Constants associated with bcmolt_onu_tiwi_data. */
#define BCMOLT_ONU_TIWI_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "tiwi" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_tiwi_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_tiwi;

/** ONU: LOOCi */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
} bcmolt_onu_looci_data;

/* Constants associated with bcmolt_onu_looci_data. */
#define BCMOLT_ONU_LOOCI_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "looci" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_looci_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_looci;

/** ONU: LOAi */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
} bcmolt_onu_loai_data;

/* Constants associated with bcmolt_onu_loai_data. */
#define BCMOLT_ONU_LOAI_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "loai" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_loai_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_loai;

/** ONU: Receive Dying-Gasp of ONUi */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
} bcmolt_onu_dgi_data;

/* Constants associated with bcmolt_onu_dgi_data. */
#define BCMOLT_ONU_DGI_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "dgi" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_dgi_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_dgi;

/** ONU: PEE */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
} bcmolt_onu_pee_data;

/* Constants associated with bcmolt_onu_pee_data. */
#define BCMOLT_ONU_PEE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "pee" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_pee_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_pee;

/** ONU: PST */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t link_number; /**< link number. */
    uint8_t k1; /**< K1. */
    uint8_t k2; /**< K2. */
} bcmolt_onu_pst_data;

/* Constants associated with bcmolt_onu_pst_data. */
#define BCMOLT_ONU_PST_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "pst" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_pst_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_pst;

/** ONU: Ranging Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result status; /**< status. */
    bcmolt_ranging_fail_reason fail_reason; /**< fail reason. */
    uint32_t eqd; /**< EQD. */
    uint8_t number_of_ploams; /**< number of ploams. */
} bcmolt_onu_ranging_completed_data;

/* Constants associated with bcmolt_onu_ranging_completed_data. */
#define BCMOLT_ONU_RANGING_COMPLETED_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "ranging_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_ranging_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_ranging_completed;

/** ONU: ONU Activation Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result status; /**< status. */
    bcmolt_activation_fail_reason fail_reason; /**< fail reason. */
    bcmolt_bin_str_36 registration_id; /**< registration id. */
    bcmolt_xgpon_onu_registration_keys registration_encryption_keys; /**< registration encryption keys. */
    bcmolt_rssi_measurement_result rssi_measurement; /**< rssi measurement. */
} bcmolt_onu_onu_activation_completed_data;

/* Constants associated with bcmolt_onu_onu_activation_completed_data. */
#define BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_REGISTRATION_ID_MAX_LENGTH 36
#define BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_REGISTRATION_ID_LENGTH 36

/** Transport message definition for "onu_activation_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_onu_activation_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_onu_activation_completed;

/** ONU: ONU Deactivation Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result status; /**< Status. */
    bcmolt_deactivation_fail_reason fail_reason; /**< fail reason. */
} bcmolt_onu_onu_deactivation_completed_data;

/* Constants associated with bcmolt_onu_onu_deactivation_completed_data. */
#define BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "onu_deactivation_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_onu_deactivation_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_onu_deactivation_completed;

/** ONU: ONU Enable Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_serial_number serial_number; /**< serial number. */
} bcmolt_onu_onu_enable_completed_data;

/* Constants associated with bcmolt_onu_onu_enable_completed_data. */
#define BCMOLT_ONU_ONU_ENABLE_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "onu_enable_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_onu_enable_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_onu_enable_completed;

/** ONU: ONU Disable Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_serial_number serial_number; /**< serial number. */
    bcmolt_deactivation_fail_reason fail_reason; /**< fail reason. */
    bcmolt_result status; /**< status. */
} bcmolt_onu_onu_disable_completed_data;

/* Constants associated with bcmolt_onu_onu_disable_completed_data. */
#define BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "onu_disable_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_onu_disable_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_onu_disable_completed;

/** ONU: RSSI Measurement Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result status; /**< status. */
    bcmolt_rssi_measurement_fail_reason fail_reason; /**< fail reason. */
} bcmolt_onu_rssi_measurement_completed_data;

/* Constants associated with bcmolt_onu_rssi_measurement_completed_data. */
#define BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "rssi_measurement_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_rssi_measurement_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_rssi_measurement_completed;

/** ONU: Invalid DBRu Report */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_alloc_id alloc_id; /**< Alloc-ID. */
} bcmolt_onu_invalid_dbru_report_data;

/* Constants associated with bcmolt_onu_invalid_dbru_report_data. */
#define BCMOLT_ONU_INVALID_DBRU_REPORT_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "invalid_dbru_report" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_invalid_dbru_report_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_invalid_dbru_report;

/** ONU: Key Exchange Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_onu_aes_key new_key; /**< new key. */
} bcmolt_onu_key_exchange_completed_data;

/* Constants associated with bcmolt_onu_key_exchange_completed_data. */
#define BCMOLT_ONU_KEY_EXCHANGE_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "key_exchange_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_key_exchange_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_key_exchange_completed;

/** Transport message definition for "key_exchange_key_request_timeout" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
} bcmolt_onu_key_exchange_key_request_timeout;

/** Transport message definition for "key_exchange_cycle_skipped" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
} bcmolt_onu_key_exchange_cycle_skipped;

/** ONU: Key Exchange Key Mismatch */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_aes_key expected_key; /**< expected key. */
    bcmolt_aes_key received_key; /**< received key. */
} bcmolt_onu_key_exchange_key_mismatch_data;

/* Constants associated with bcmolt_onu_key_exchange_key_mismatch_data. */
#define BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "key_exchange_key_mismatch" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_key_exchange_key_mismatch_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_key_exchange_key_mismatch;

/** Transport message definition for "optical_reflection" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
} bcmolt_onu_optical_reflection;

/** ONU: LOki */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< alarm status. */
} bcmolt_onu_loki_data;

/* Constants associated with bcmolt_onu_loki_data. */
#define BCMOLT_ONU_LOKI_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "loki" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_loki_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_loki;

/** ONU: MEMi */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str_13 ploam_buffer; /**< PLOAM buffer. */
} bcmolt_onu_memi_data;

/* Constants associated with bcmolt_onu_memi_data. */
#define BCMOLT_ONU_MEMI_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_ONU_MEMI_DATA_PLOAM_BUFFER_MAX_LENGTH 13
#define BCMOLT_ONU_MEMI_DATA_PLOAM_BUFFER_LENGTH 13

/** Transport message definition for "memi" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_memi_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_memi;

/** ONU: OMCI PORT ID Configuration Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_gem_port_id gem_port; /**< GEM Port ID. */
    bcmolt_result status; /**< status. */
    bcmolt_omci_port_id_operation operation; /**< Operation. */
} bcmolt_onu_omci_port_id_configuration_completed_data;

/* Constants associated with bcmolt_onu_omci_port_id_configuration_completed_data. */
#define BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "omci_port_id_configuration_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_omci_port_id_configuration_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_omci_port_id_configuration_completed;

/** ONU: BER Interval Configuration Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_ber_interval ber_interval; /**< BER interval in ms. */
    bcmolt_result result; /**< Result. */
} bcmolt_onu_ber_interval_configuration_completed_data;

/* Constants associated with bcmolt_onu_ber_interval_configuration_completed_data. */
#define BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_BER_INTERVAL_DEFAULT (bcmolt_ber_interval)0UL

/** Transport message definition for "ber_interval_configuration_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_ber_interval_configuration_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_ber_interval_configuration_completed;

/** ONU: ERR */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t bip8_errors; /**< BIP8 errors. */
} bcmolt_onu_err_data;

/* Constants associated with bcmolt_onu_err_data. */
#define BCMOLT_ONU_ERR_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "err" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_err_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_err;

/** ONU: Password Authentication Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result status; /**< status. */
    bcmolt_password_authentication_fail_reason fail_reason; /**< fail reason. */
    bcmolt_bin_str_10 password; /**< password. */
} bcmolt_onu_password_authentication_completed_data;

/* Constants associated with bcmolt_onu_password_authentication_completed_data. */
#define BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_PASSWORD_MAX_LENGTH 10
#define BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_PASSWORD_LENGTH 10

/** Transport message definition for "password_authentication_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_password_authentication_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_password_authentication_completed;

/** ONU: Key Exchange Unconsecutive Index */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t expected_index; /**< expected index. */
    uint32_t actual_index; /**< actual index. */
} bcmolt_onu_key_exchange_unconsecutive_index_data;

/* Constants associated with bcmolt_onu_key_exchange_unconsecutive_index_data. */
#define BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "key_exchange_unconsecutive_index" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_key_exchange_unconsecutive_index_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_key_exchange_unconsecutive_index;

/** ONU: Key Exchange Decrypt Required */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_aes_key new_key; /**< new key. */
} bcmolt_onu_key_exchange_decrypt_required_data;

/* Constants associated with bcmolt_onu_key_exchange_decrypt_required_data. */
#define BCMOLT_ONU_KEY_EXCHANGE_DECRYPT_REQUIRED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "key_exchange_decrypt_required" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_key_exchange_decrypt_required_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_key_exchange_decrypt_required;

/** ONU: onu activation standby completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< result. */
} bcmolt_onu_onu_activation_standby_completed_data;

/* Constants associated with bcmolt_onu_onu_activation_standby_completed_data. */
#define BCMOLT_ONU_ONU_ACTIVATION_STANDBY_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "onu_activation_standby_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_onu_activation_standby_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_onu_activation_standby_completed;

/** ONU: Power Management State Change */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_state old_state; /**< The state the ONU was previously in. */
    bcmolt_onu_state new_state; /**< The state the ONU is currently in. */
    bcmolt_power_management_transition_reason reason; /**< The reason for the state change. */
} bcmolt_onu_power_management_state_change_data;

/* Constants associated with bcmolt_onu_power_management_state_change_data. */
#define BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "power_management_state_change" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_power_management_state_change_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_power_management_state_change;

/** ONU: Possible Drift */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status alarm_status; /**< On: estimated drift has exceeded the configured threshold. */
    int32_t estimated_drift; /**< If status is on, the estimated drift value, otherwise zero (0). */
} bcmolt_onu_possible_drift_data;

/* Constants associated with bcmolt_onu_possible_drift_data. */
#define BCMOLT_ONU_POSSIBLE_DRIFT_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "possible_drift" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_possible_drift_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_possible_drift;

/** ONU: Registration ID */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str_36 registration_id; /**< Registration ID. */
    bcmolt_result request_registration_status; /**< request registration status. */
    bcmolt_request_registration_fail_reason request_registration_fail_reason; /**< request registration fail reason. */
} bcmolt_onu_registration_id_data;

/* Constants associated with bcmolt_onu_registration_id_data. */
#define BCMOLT_ONU_REGISTRATION_ID_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_ONU_REGISTRATION_ID_DATA_REGISTRATION_ID_MAX_LENGTH 36
#define BCMOLT_ONU_REGISTRATION_ID_DATA_REGISTRATION_ID_LENGTH 36

/** Transport message definition for "registration_id" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_registration_id_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_registration_id;

/** ONU: Power level report */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t attenuation; /**< Attenuation. */
    uint8_t power_levelling_capability; /**< Power levelling capability. */
} bcmolt_onu_power_level_report_data;

/* Constants associated with bcmolt_onu_power_level_report_data. */
#define BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "power_level_report" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_power_level_report_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_power_level_report;

/** ONU: Power consumption report */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_arr_power_consumption_channel_report_8 power_consumption_report; /**< power consumption report. */
} bcmolt_onu_power_consumption_report_data;

/* Constants associated with bcmolt_onu_power_consumption_report_data. */
#define BCMOLT_ONU_POWER_CONSUMPTION_REPORT_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_ONU_POWER_CONSUMPTION_REPORT_DATA_POWER_CONSUMPTION_REPORT_LENGTH 8

/** Transport message definition for "power_consumption_report" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_power_consumption_report_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_power_consumption_report;

/** ONU: secure mutual authentication failure */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result status; /**< status. */
    bcmolt_secure_mutual_authentication_fail_reason fail_reason; /**< secure mutual authentication fail reason. */
} bcmolt_onu_secure_mutual_authentication_failure_data;

/* Constants associated with bcmolt_onu_secure_mutual_authentication_failure_data. */
#define BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "secure_mutual_authentication_failure" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_secure_mutual_authentication_failure_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_secure_mutual_authentication_failure;

/** ONU: ONU Tuning out completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< result. */
    bcmolt_tune_out_fail_reason fail_reason; /**< fail reason. */
} bcmolt_onu_onu_tuning_out_completed_data;

/* Constants associated with bcmolt_onu_onu_tuning_out_completed_data. */
#define BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "onu_tuning_out_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_onu_tuning_out_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_onu_tuning_out_completed;

/** ONU: ONU Tuning in completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< result. */
    bcmolt_tune_in_fail_reason fail_reason; /**< fail reason. */
} bcmolt_onu_onu_tuning_in_completed_data;

/* Constants associated with bcmolt_onu_onu_tuning_in_completed_data. */
#define BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "onu_tuning_in_completed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_onu_tuning_in_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_onu_tuning_in_completed;

/** ONU: Tuning response */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool ack; /**< is tuning response received with ack or nack */
    bcmolt_result result; /**< result. */
} bcmolt_onu_tuning_response_data;

/* Constants associated with bcmolt_onu_tuning_response_data. */
#define BCMOLT_ONU_TUNING_RESPONSE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "tuning_response" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_tuning_response_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_tuning_response;

/** ONU: PLOAM Packet */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool default_key; /**< default key. */
    bcmolt_bin_str_40 ploam; /**< ploam. */
} bcmolt_onu_ploam_packet_data;

/* Constants associated with bcmolt_onu_ploam_packet_data. */
#define BCMOLT_ONU_PLOAM_PACKET_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_ONU_PLOAM_PACKET_DATA_DEFAULT_KEY_DEFAULT BCMOS_FALSE
#define BCMOLT_ONU_PLOAM_PACKET_DATA_PLOAM_MAX_LENGTH 40
#define BCMOLT_ONU_PLOAM_PACKET_DATA_PLOAM_LENGTH 40

/** Transport message definition for "ploam_packet" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_ploam_packet_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_ploam_packet;

/** ONU: XGPON CPU packets */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_packet_type packet_type; /**< packet type. */
    bcmos_bool calc_crc; /**< calc crc. */
    uint8_t number_of_packets; /**< number of packets. */
    uint16_t packet_size; /**< Single packet size. */
    bcmolt_bin_str buffer; /**< buffer. */
} bcmolt_onu_cpu_packets_data;

/* Constants associated with bcmolt_onu_cpu_packets_data. */
#define BCMOLT_ONU_CPU_PACKETS_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_ONU_CPU_PACKETS_DATA_NUMBER_OF_PACKETS_MAX 32
#define BCMOLT_ONU_CPU_PACKETS_DATA_PACKET_SIZE_MAX 2000U

/** Transport message definition for "cpu_packets" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_cpu_packets_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_cpu_packets;

/** ONU: XGPON CPU packet */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint16_t port_id; /**< port id. */
    bcmos_bool crc_ok; /**< crc ok. */
    uint32_t packet_size; /**< packet size. */
    bcmolt_bin_str buffer; /**< buffer. */
} bcmolt_onu_cpu_packet_data;

/* Constants associated with bcmolt_onu_cpu_packet_data. */
#define BCMOLT_ONU_CPU_PACKET_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "cpu_packet" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_cpu_packet_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_cpu_packet;

/** ONU: XGPON OMCI packet */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint16_t port_id; /**< port id. */
    bcmos_bool crc_ok; /**< crc ok. */
    uint32_t packet_size; /**< packet size. */
    bcmolt_bin_str buffer; /**< buffer. */
} bcmolt_onu_omci_packet_data;

/* Constants associated with bcmolt_onu_omci_packet_data. */
#define BCMOLT_ONU_OMCI_PACKET_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "omci_packet" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_omci_packet_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_omci_packet;

/** Transport message definition for "onu_ready_for_data_grant" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
} bcmolt_onu_onu_ready_for_data_grant;

/** ONU: REI */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t bip8_errors; /**< BIP8 errors. */
} bcmolt_onu_rei_data;

/* Constants associated with bcmolt_onu_rei_data. */
#define BCMOLT_ONU_REI_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "rei" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_rei_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_rei;

/** Transport message definition for "force_deactivation" group of "onu" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
} bcmolt_onu_force_deactivation;

/** ONU: State Change */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_operation new_onu_state; /**< New ONU state. */
} bcmolt_onu_state_change_data;

/* Constants associated with bcmolt_onu_state_change_data. */
#define BCMOLT_ONU_STATE_CHANGE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "state_change" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_state_change_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_state_change;

/** ONU: Range Value Changed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_time_quanta range_value_tq; /**< New range value. */
} bcmolt_onu_range_value_changed_data;

/* Constants associated with bcmolt_onu_range_value_changed_data. */
#define BCMOLT_ONU_RANGE_VALUE_CHANGED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "range_value_changed" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_range_value_changed_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_range_value_changed;

/** ONU: XPON Unknown ploam */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str_48 ploam_buffer; /**< PLOAM buffer. */
} bcmolt_onu_xpon_unknown_ploam_data;

/* Constants associated with bcmolt_onu_xpon_unknown_ploam_data. */
#define BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_PLOAM_BUFFER_MAX_LENGTH 48
#define BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_PLOAM_BUFFER_LENGTH 48

/** Transport message definition for "xpon_unknown_ploam" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_xpon_unknown_ploam_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_xpon_unknown_ploam;

/** ONU: trap ploam received */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t message_id; /**< message id. */
    uint16_t onu_id; /**< onu_id. */
    bcmolt_u8_list_u8_hex data; /**< data. */
} bcmolt_onu_trap_ploam_received_data;

/* Constants associated with bcmolt_onu_trap_ploam_received_data. */
#define BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "trap_ploam_received" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_trap_ploam_received_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_trap_ploam_received;

/** ONU: Accumulated statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t tm_used; /**< tm used. */
    uint64_t tm_allocated; /**< tm allocated. */
    uint64_t bufocc; /**< Buffer occupancy. */
} bcmolt_onu_itu_alloc_onu_accumulated_stats_data;

/* Constants associated with bcmolt_onu_itu_alloc_onu_accumulated_stats_data. */
#define BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "itu_alloc_onu_accumulated_stats" group of "onu" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_itu_alloc_onu_accumulated_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_itu_alloc_onu_accumulated_stats;

/** Multi-object message definition for "itu_alloc_onu_accumulated_stats" group of "onu" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key (can include wildcards). */
    bcmolt_onu_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_onu_itu_alloc_onu_accumulated_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_onu_itu_alloc_onu_accumulated_stats *responses; /**< Responses to the last API call. */

    bcmolt_onu_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_onu_multi_itu_alloc_onu_accumulated_stats;

/** ONU: ITU PON Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config positive_drift; /**< positive drift. */
    bcmolt_stat_alarm_config negative_drift; /**< negative drift. */
    bcmolt_stat_alarm_config delimiter_miss_detection; /**< unreceived bursts */
    bcmolt_stat_alarm_config bip_errors; /**< bip errors. */
    bcmolt_stat_alarm_config bip_units; /**< Number of 4-byte words xgpon or bytes gpon received (word size is 4 bytes regardless of upstream data rate). */
    bcmolt_stat_alarm_config fec_corrected_symbols; /**< fec corrected symbols  (Not relevant in GPON system modes). */
    bcmolt_stat_alarm_config fec_codewords_corrected; /**< fec corrected codewords. */
    bcmolt_stat_alarm_config fec_codewords_uncorrectable; /**< fec uncorrectable codewords. */
    bcmolt_stat_alarm_config fec_codewords; /**< fec total codewords. */
    bcmolt_stat_alarm_config fec_corrected_units; /**< fec corrected units (In GPON units are bits in other system modes, units are Bytes). */
    bcmolt_stat_alarm_config xgem_key_errors; /**< xgem key error. */
    bcmolt_stat_alarm_config xgem_loss; /**< xgem loss. */
    bcmolt_stat_alarm_config rx_ploams_error; /**< mic error ploam. */
    bcmolt_stat_alarm_config rx_ploams_non_idle; /**< non idle ploam. */
    bcmolt_stat_alarm_config rx_omci; /**< Received OMCI packets. */
    bcmolt_stat_alarm_config rx_omci_packets_crc_error; /**< Received OMCI packets with CRC errors. */
    bcmolt_stat_alarm_config rx_bytes; /**< rx bytes. */
    bcmolt_stat_alarm_config rx_packets; /**< rx packets. */
    bcmolt_stat_alarm_config tx_bytes; /**< tx bytes. */
    bcmolt_stat_alarm_config tx_packets; /**< tx packets. */
    bcmolt_stat_alarm_config ber_reported; /**< gpon only */
    bcmolt_stat_alarm_config lcdg_errors; /**< LCDG errors. */
    bcmolt_stat_alarm_config rdi_errors; /**< RDI errors. */
} bcmolt_onu_itu_pon_stats_cfg_data;

/* Constants associated with bcmolt_onu_itu_pon_stats_cfg_data. */
#define BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x00000000007FFFFFULL

/** Transport message definition for "itu_pon_stats_cfg" group of "onu" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_itu_pon_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_itu_pon_stats_cfg;

/** ONU: ITU PON Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_itu_pon_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_onu_itu_pon_stats_alarm_raised_data;

/* Constants associated with bcmolt_onu_itu_pon_stats_alarm_raised_data. */
#define BCMOLT_ONU_ITU_PON_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "itu_pon_stats_alarm_raised" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_itu_pon_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_itu_pon_stats_alarm_raised;

/** ONU: ITU PON Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_itu_pon_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_onu_itu_pon_stats_alarm_cleared_data;

/* Constants associated with bcmolt_onu_itu_pon_stats_alarm_cleared_data. */
#define BCMOLT_ONU_ITU_PON_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "itu_pon_stats_alarm_cleared" group of "onu" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_itu_pon_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_itu_pon_stats_alarm_cleared;

/** ONU: Accumulated Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config tm_used; /**< tm used. */
    bcmolt_stat_alarm_config tm_allocated; /**< tm allocated. */
    bcmolt_stat_alarm_config bufocc; /**< Buffer occupancy. */
} bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data;

/* Constants associated with bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data. */
#define BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "itu_alloc_onu_accumulated_stats_cfg" group of "onu" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg;

/** ONU: Accumulated Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_itu_alloc_onu_accumulated_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data;

/* Constants associated with bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data. */
#define BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "itu_alloc_onu_accumulated_stats_alarm_raised" group of "onu"
  * object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised;

/** ONU: Accumulated Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_itu_alloc_onu_accumulated_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data;

/* Constants associated with bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data. */
#define BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "itu_alloc_onu_accumulated_stats_alarm_cleared" group of "onu"
  * object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared;

/** ONU: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool ber_interval_configuration_completed; /**< If true, indications of type "ber_interval_configuration_completed" will be generated. */
    bcmos_bool cpu_packet; /**< If true, indications of type "cpu_packet" will be generated. */
    bcmos_bool dfi; /**< If true, indications of type "dfi" will be generated. */
    bcmos_bool dgi; /**< If true, indications of type "dgi" will be generated. */
    bcmos_bool dowi; /**< If true, indications of type "dowi" will be generated. */
    bcmos_bool err; /**< If true, indications of type "err" will be generated. */
    bcmos_bool gpon_alarm; /**< If true, indications of type "gpon_alarm" will be generated. */
    bcmos_bool invalid_dbru_report; /**< If true, indications of type "invalid_dbru_report" will be generated. */
    bcmos_bool itu_alloc_onu_accumulated_stats_alarm_cleared; /**< If true, indications of type "itu_alloc_onu_accumulated_stats_alarm_cleared" will be generated. */
    bcmos_bool itu_alloc_onu_accumulated_stats_alarm_raised; /**< If true, indications of type "itu_alloc_onu_accumulated_stats_alarm_raised" will be generated. */
    bcmos_bool itu_pon_stats_alarm_cleared; /**< If true, indications of type "itu_pon_stats_alarm_cleared" will be generated. */
    bcmos_bool itu_pon_stats_alarm_raised; /**< If true, indications of type "itu_pon_stats_alarm_raised" will be generated. */
    bcmos_bool key_exchange_completed; /**< If true, indications of type "key_exchange_completed" will be generated. */
    bcmos_bool key_exchange_cycle_skipped; /**< If true, indications of type "key_exchange_cycle_skipped" will be generated. */
    bcmos_bool key_exchange_decrypt_required; /**< If true, indications of type "key_exchange_decrypt_required" will be generated. */
    bcmos_bool key_exchange_key_mismatch; /**< If true, indications of type "key_exchange_key_mismatch" will be generated. */
    bcmos_bool key_exchange_key_request_timeout; /**< If true, indications of type "key_exchange_key_request_timeout" will be generated. */
    bcmos_bool key_exchange_unconsecutive_index; /**< If true, indications of type "key_exchange_unconsecutive_index" will be generated. */
    bcmos_bool loai; /**< If true, indications of type "loai" will be generated. */
    bcmos_bool loki; /**< If true, indications of type "loki" will be generated. */
    bcmos_bool looci; /**< If true, indications of type "looci" will be generated. */
    bcmos_bool memi; /**< If true, indications of type "memi" will be generated. */
    bcmos_bool omci_packet; /**< If true, indications of type "omci_packet" will be generated. */
    bcmos_bool omci_port_id_configuration_completed; /**< If true, indications of type "omci_port_id_configuration_completed" will be generated. */
    bcmos_bool onu_activation_completed; /**< If true, indications of type "onu_activation_completed" will be generated. */
    bcmos_bool onu_activation_standby_completed; /**< If true, indications of type "onu_activation_standby_completed" will be generated. */
    bcmos_bool onu_deactivation_completed; /**< If true, indications of type "onu_deactivation_completed" will be generated. */
    bcmos_bool onu_disable_completed; /**< If true, indications of type "onu_disable_completed" will be generated. */
    bcmos_bool onu_enable_completed; /**< If true, indications of type "onu_enable_completed" will be generated. */
    bcmos_bool onu_ready_for_data_grant; /**< If true, indications of type "onu_ready_for_data_grant" will be generated. */
    bcmos_bool onu_tuning_in_completed; /**< If true, indications of type "onu_tuning_in_completed" will be generated. */
    bcmos_bool onu_tuning_out_completed; /**< If true, indications of type "onu_tuning_out_completed" will be generated. */
    bcmos_bool optical_reflection; /**< If true, indications of type "optical_reflection" will be generated. */
    bcmos_bool password_authentication_completed; /**< If true, indications of type "password_authentication_completed" will be generated. */
    bcmos_bool pee; /**< If true, indications of type "pee" will be generated. */
    bcmos_bool possible_drift; /**< If true, indications of type "possible_drift" will be generated. */
    bcmos_bool power_consumption_report; /**< If true, indications of type "power_consumption_report" will be generated. */
    bcmos_bool power_level_report; /**< If true, indications of type "power_level_report" will be generated. */
    bcmos_bool power_management_state_change; /**< If true, indications of type "power_management_state_change" will be generated. */
    bcmos_bool pqsi; /**< If true, indications of type "pqsi" will be generated. */
    bcmos_bool pst; /**< If true, indications of type "pst" will be generated. */
    bcmos_bool range_value_changed; /**< If true, indications of type "range_value_changed" will be generated. */
    bcmos_bool ranging_completed; /**< If true, indications of type "ranging_completed" will be generated. */
    bcmos_bool registration_id; /**< If true, indications of type "registration_id" will be generated. */
    bcmos_bool rei; /**< If true, indications of type "rei" will be generated. */
    bcmos_bool rssi_measurement_completed; /**< If true, indications of type "rssi_measurement_completed" will be generated. */
    bcmos_bool sdi; /**< If true, indications of type "sdi" will be generated. */
    bcmos_bool secure_mutual_authentication_failure; /**< If true, indications of type "secure_mutual_authentication_failure" will be generated. */
    bcmos_bool sfi; /**< If true, indications of type "sfi" will be generated. */
    bcmos_bool state_change; /**< If true, indications of type "state_change" will be generated. */
    bcmos_bool sufi; /**< If true, indications of type "sufi" will be generated. */
    bcmos_bool tiwi; /**< If true, indications of type "tiwi" will be generated. */
    bcmos_bool trap_ploam_received; /**< If true, indications of type "trap_ploam_received" will be generated. */
    bcmos_bool tuning_response; /**< If true, indications of type "tuning_response" will be generated. */
    bcmos_bool xgpon_alarm; /**< If true, indications of type "xgpon_alarm" will be generated. */
    bcmos_bool xpon_unknown_ploam; /**< If true, indications of type "xpon_unknown_ploam" will be generated. */
} bcmolt_onu_auto_cfg_data;

/* Constants associated with bcmolt_onu_auto_cfg_data. */
#define BCMOLT_ONU_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x00FFFFFFFFFFFFFFULL

/** Transport message definition for "auto_cfg" group of "onu" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_onu_key key; /**< Object key. */
    bcmolt_onu_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_onu_auto_cfg;

/** pbit_to_tc: key */
typedef struct
{
    uint16_t id; /**< id */
    bcmolt_tm_sched_dir dir; /**< dir. */
} bcmolt_pbit_to_tc_key;

/* Constants associated with bcmolt_pbit_to_tc_key. */
#define BCMOLT_PBIT_TO_TC_KEY_ID_MIN 1U
#define BCMOLT_PBIT_TO_TC_KEY_ID_MAX 4096U

/** pbit_to_tc: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str_8 tc; /**< tc (0..7) set for a pbit 0..7 */
} bcmolt_pbit_to_tc_cfg_data;

/* Constants associated with bcmolt_pbit_to_tc_cfg_data. */
#define BCMOLT_PBIT_TO_TC_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_PBIT_TO_TC_CFG_DATA_TC_MAX_LENGTH 8
#define BCMOLT_PBIT_TO_TC_CFG_DATA_TC_LENGTH 8

/** Transport message definition for "cfg" group of "pbit_to_tc" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_pbit_to_tc_key key; /**< Object key. */
    bcmolt_pbit_to_tc_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_pbit_to_tc_cfg;

/** Multi-object message definition for "cfg" group of "pbit_to_tc" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_pbit_to_tc_key key; /**< Object key (can include wildcards). */
    bcmolt_pbit_to_tc_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_pbit_to_tc_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_pbit_to_tc_cfg *responses; /**< Responses to the last API call. */

    bcmolt_pbit_to_tc_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_pbit_to_tc_multi_cfg;

/** policer (aka meter) profile: key */
typedef struct
{
    bcmolt_policer_profile_id id; /**< id. */
} bcmolt_policer_profile_key;

/** policer (aka meter) profile: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state state; /**< not_configured => entry not used */
    bcmolt_policer_type type; /**< meter type - single rate, two color, etc. */
    bcmolt_traffic_type traffic_type; /**< type of traffic (Unk Uni, Broadcast, etc.) to police */
    uint32_t cir_kbps; /**< commited rate in kbps */
    uint32_t eir_kbps; /**< excess rate in kbps */
    uint32_t cbs_kb; /**< committed burst in kb */
    uint32_t ebs_kb; /**< excess burst in kb */
    bcmos_bool color_awareness; /**< enable color reading from input packet. method is spec'd in input tm_cmp for port */
    bcmos_bool color_marking; /**< enable color marking to outgoing packet. method is spec'd in output tm_cmp for port */
} bcmolt_policer_profile_cfg_data;

/* Constants associated with bcmolt_policer_profile_cfg_data. */
#define BCMOLT_POLICER_PROFILE_CFG_DATA_PRESENCE_MASK_ALL 0x00000000000003FBULL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED
#define BCMOLT_POLICER_PROFILE_CFG_DATA_TYPE_DEFAULT BCMOLT_POLICER_TYPE_SR_TCM
#define BCMOLT_POLICER_PROFILE_CFG_DATA_TRAFFIC_TYPE_DEFAULT BCMOLT_TRAFFIC_TYPE_BROADCAST
#define BCMOLT_POLICER_PROFILE_CFG_DATA_CIR_KBPS_DEFAULT 100UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_CIR_KBPS_MIN 0UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_CIR_KBPS_MAX 100000000UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_EIR_KBPS_DEFAULT 50UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_EIR_KBPS_MIN 0UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_EIR_KBPS_MAX 100000000UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_CBS_KB_DEFAULT 64UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_CBS_KB_MIN 1UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_CBS_KB_MAX 33292UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_EBS_KB_DEFAULT 32UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_EBS_KB_MIN 1UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_EBS_KB_MAX 33292UL
#define BCMOLT_POLICER_PROFILE_CFG_DATA_COLOR_AWARENESS_DEFAULT BCMOS_FALSE
#define BCMOLT_POLICER_PROFILE_CFG_DATA_COLOR_MARKING_DEFAULT BCMOS_FALSE

/** Transport message definition for "cfg" group of "policer_profile" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_policer_profile_key key; /**< Object key. */
    bcmolt_policer_profile_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_policer_profile_cfg;

/** Multi-object message definition for "cfg" group of "policer_profile" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_policer_profile_key key; /**< Object key (can include wildcards). */
    bcmolt_policer_profile_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_policer_profile_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_policer_profile_cfg *responses; /**< Responses to the last API call. */

    bcmolt_policer_profile_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_policer_profile_multi_cfg;

/** pon interface: key */
typedef struct
{
    bcmolt_interface pon_ni; /**< Interface Id */
} bcmolt_pon_interface_key;

/** pon interface: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_interface_state state; /**< Interface state */
    bcmolt_pon_type pon_type; /**< PON type: GPON, XGPON, XGS, EPON ... */
    bcmolt_status los_status; /**< LoS Status */
    bcmolt_status los_initial_value; /**< LOS initial value following PON activation */
    bcmolt_service_discovery discovery; /**< Serial Number process configuration */
    bcmolt_itu_pon_params itu; /**< ITU PON Attributes */
    bcmolt_pon_distance pon_distance; /**< PON distance */
    uint16_t number_of_active_onus; /**< Number of active ONUs on the PON */
    uint16_t number_of_active_standby_onus; /**< Number of active standby ONUs on the PON */
    bcmolt_gpon_trx gpon_trx; /**< gpon transceiver parameters */
    bcmolt_xgpon_trx xgpon_trx; /**< xgpon transceiver parameters */
    bcmolt_xgpon_trx xgs_ngpon2_trx; /**< xgs or ngpon2 transceiver params */
    uint32_t los_wait_timeout; /**< los wait timeout in ms */
} bcmolt_pon_interface_cfg_data;

/* Constants associated with bcmolt_pon_interface_cfg_data. */
#define BCMOLT_PON_INTERFACE_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000007F3FULL
#define BCMOLT_PON_INTERFACE_CFG_DATA_STATE_DEFAULT BCMOLT_INTERFACE_STATE_INACTIVE
#define BCMOLT_PON_INTERFACE_CFG_DATA_LOS_INITIAL_VALUE_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_PON_INTERFACE_CFG_DATA_LOS_WAIT_TIMEOUT_DEFAULT 10UL
#define BCMOLT_PON_INTERFACE_CFG_DATA_LOS_WAIT_TIMEOUT_MAX 1000UL

/** Transport message definition for "cfg" group of "pon_interface" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_cfg;

/** Multi-object message definition for "cfg" group of "pon_interface" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key (can include wildcards). */
    bcmolt_pon_interface_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_pon_interface_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_pon_interface_cfg *responses; /**< Responses to the last API call. */

    bcmolt_pon_interface_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_pon_interface_multi_cfg;

/** pon interface: ITU PON Statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t fec_codewords; /**< Receive FEC codewords. */
    uint64_t bip_units; /**< Received units (bits in GPON / bytes in XGPON) protected by bip. */
    uint64_t bip_errors; /**< Received bip errors. */
    uint64_t rx_gem; /**< Received valid GEM frames. */
    uint64_t rx_gem_dropped; /**< Received dropped GEM ID frames. */
    uint64_t rx_gem_idle; /**< Received idle GEM frames. */
    uint64_t rx_gem_corrected; /**< Received corrected GEM frames. */
    uint64_t rx_crc_error; /**< Received packets with CRC error. */
    uint64_t rx_fragment_error; /**< Received fragment errors. */
    uint64_t rx_packets_dropped; /**< Global dropped packets. */
    uint64_t rx_dropped_too_short; /**< Received packets dropped due to length too short. */
    uint64_t rx_dropped_too_long; /**< Received packet dropped due to length too long. */
    uint64_t rx_key_error; /**< Received key errors. */
    uint8_t rx_cpu_omci_packets_dropped; /**< Received packets dropped due to illegal length. */
    uint64_t tx_ploams; /**< Transmitted Ploams. */
    uint64_t rx_ploams_dropped; /**< Received dropped Ploams. */
    uint64_t rx_allocations_valid; /**< Received valid allocations. */
    uint64_t rx_allocations_invalid; /**< Received invalid allocations. */
    uint64_t rx_allocations_disabled; /**< Received disabled allocations. */
    uint64_t rx_ploams; /**< Received Ploams. */
    uint64_t rx_ploams_non_idle; /**< Received non idle Ploams. */
    uint64_t rx_ploams_error; /**< Received error Ploams. */
    uint64_t rx_cpu; /**< Received CPU packets. */
    uint64_t rx_omci; /**< Received OMCI packets. */
    uint64_t rx_omci_packets_crc_error; /**< Received OMCI packets with CRC errors. */
    uint64_t tx_packets; /**< Transmitted packets. */
    uint64_t tx_gem; /**< Transmitted GEM frames. */
    uint64_t tx_cpu; /**< Transmitted CPU packets. */
    uint64_t tx_omci; /**< Transmitted OMCI packets. */
    uint64_t tx_dropped_illegal_length; /**< Transmit packets dropped due to illegal length. */
    uint64_t tx_dropped_tpid_miss; /**< Transmit packets dropped due to TPID miss. */
    uint64_t tx_dropped_vid_miss; /**< Transmit packets droped due to VID miss. */
    uint64_t tx_dropped_total; /**< Total transmit packets droped. */
    uint64_t rx_xgtc_headers; /**< Received valid XGTC headers. */
    uint64_t rx_xgtc_corrected; /**< Received corrected XGTC headers. */
    uint64_t rx_xgtc_uncorrected; /**< Received uncorrected XGTC headers. */
    uint64_t fec_codewords_uncorrected; /**< Received uncorrected FEC codewords. */
    uint64_t rx_gem_illegal; /**< Received illegal GEM frames. */
    uint64_t rx_packets; /**< Received packets. */
    uint64_t tx_bytes; /**< Transmitted bytes. */
    uint64_t rx_bytes; /**< Received bytes. */
} bcmolt_pon_interface_itu_pon_stats_data;

/* Constants associated with bcmolt_pon_interface_itu_pon_stats_data. */
#define BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_PRESENCE_MASK_ALL 0x000001FFFFFFFFFFULL

/** Transport message definition for "itu_pon_stats" group of "pon_interface" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_itu_pon_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_itu_pon_stats;

/** Multi-object message definition for "itu_pon_stats" group of "pon_interface" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key (can include wildcards). */
    bcmolt_pon_interface_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_pon_interface_itu_pon_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_pon_interface_itu_pon_stats *responses; /**< Responses to the last API call. */

    bcmolt_pon_interface_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_pon_interface_multi_itu_pon_stats;

/** pon interface: Active Ethernet Interface Counters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t rx_bytes; /**< The number of bytes received on this interface. */
    uint64_t rx_frames; /**< The number of frames received on this interface. */
    uint64_t rx_frames_64; /**< The number of 64 byte frames received on this interface. */
    uint64_t rx_frames_65_127; /**< The number of 65 to 127 byte frames received on this interface. */
    uint64_t rx_frames_128_255; /**< The number of 128 to 255 byte frames received on this interface. */
    uint64_t rx_frames_256_511; /**< The number of 256 to 511 byte frames received on this interface. */
    uint64_t rx_frames_512_1023; /**< The number of 512 to 1023 byte frames received on this interface. */
    uint64_t rx_frames_1024_1518; /**< The number of 1024 to 1518 byte frames received on this interface. */
    uint64_t rx_frames_1519_2047; /**< The number of 1519 to 2047 byte frames received on this interface. */
    uint64_t rx_frames_2048_4095; /**< The number of 2048 to 4095 byte frames received on this interface. */
    uint64_t rx_frames_4096_9216; /**< The number of 4096 to 9216 byte frames received on this interface. */
    uint64_t rx_frames_9217_16383; /**< The number of 9217 to 16383 byte frames received on this interface. */
    uint64_t rx_broadcast_frames; /**< The number of broadcast frames received on this interface. */
    uint64_t rx_data_bytes; /**< The number of data bytes received on this interface. */
    uint64_t rx_multicast_frames; /**< The number of multicast frames received on this interface. */
    uint64_t rx_unicast_frames; /**< The number of unicast frames received on this interface. */
    uint64_t rx_abort_frames; /**< The number of abort frames received on this interface. */
    uint64_t rx_fcs_error; /**< The number of bad FCS errors received on this interface. */
    uint64_t rx_oversize_error; /**< The number of oversize errors received on this interface. */
    uint64_t rx_runt_error; /**< The number of runt errors received on this interface. */
    uint64_t tx_bytes; /**< The number of bytes transmitted on this interface. */
    uint64_t tx_frames; /**< The number of frames transmitted on this interface. */
    uint64_t tx_frames_64; /**< The number of 64 byte frames transmitted on this interface. */
    uint64_t tx_frames_65_127; /**< The number of 65 to 127 byte frames transmitted on this interface. */
    uint64_t tx_frames_128_255; /**< The number of 128 to 255 byte frames transmitted on this interface. */
    uint64_t tx_frames_256_511; /**< The number of 256 to 511 byte frames transmitted on this interface. */
    uint64_t tx_frames_512_1023; /**< The number of 512 to 1023 byte frames transmitted on this interface. */
    uint64_t tx_frames_1024_1518; /**< The number of 1024 to 1518 byte frames transmitted on this interface. */
    uint64_t tx_frames_1519_2047; /**< The number of 1519 to 2047 byte frames transmitted on this interface. */
    uint64_t tx_frames_2048_4095; /**< The number of 2048 to 4095 byte frames transmitted on this interface. */
    uint64_t tx_frames_4096_9216; /**< The number of 4096 to 9216 byte frames transmitted on this interface. */
    uint64_t tx_frames_9217_16383; /**< The number of 9217 to 16383 byte frames transmitted on this interface. */
    uint64_t tx_broadcast_frames; /**< The number of broadcast frames transmitted on this interface. */
    uint64_t tx_data_bytes; /**< The number of data bytes transmitted on this interface. */
    uint64_t tx_multicast_frames; /**< The number of multicast frames transmitted on this interface. */
    uint64_t tx_unicast_frames; /**< The number of unicast frames transmitted on this interface. */
    uint64_t tx_abort_frames; /**< Number of abort frames transmitted on this interface. */
} bcmolt_pon_interface_ae_stats_data;

/* Constants associated with bcmolt_pon_interface_ae_stats_data. */
#define BCMOLT_PON_INTERFACE_AE_STATS_DATA_PRESENCE_MASK_ALL 0x0000001FFFFFFFFFULL

/** Transport message definition for "ae_stats" group of "pon_interface" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_ae_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_ae_stats;

/** Multi-object message definition for "ae_stats" group of "pon_interface" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key (can include wildcards). */
    bcmolt_pon_interface_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_pon_interface_ae_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_pon_interface_ae_stats *responses; /**< Responses to the last API call. */

    bcmolt_pon_interface_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_pon_interface_multi_ae_stats;

/** pon interface: Set PON Interface State */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_interface_operation operation; /**< PON interface operation. */
} bcmolt_pon_interface_set_pon_interface_state_data;

/* Constants associated with bcmolt_pon_interface_set_pon_interface_state_data. */
#define BCMOLT_PON_INTERFACE_SET_PON_INTERFACE_STATE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "set_pon_interface_state" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_set_pon_interface_state_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_set_pon_interface_state;

/** pon interface: Set ONU State */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_operation onu_state; /**< New operation state of all ONUs.  The default operation may be configured by the XGPON NI configuration object : xgpon_ni.cfg.sn_acquisition. */
} bcmolt_pon_interface_set_onu_state_data;

/* Constants associated with bcmolt_pon_interface_set_onu_state_data. */
#define BCMOLT_PON_INTERFACE_SET_ONU_STATE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "set_onu_state" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_set_onu_state_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_set_onu_state;

/** Transport message definition for "reset" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_reset;

/** pon interface: Disable Serial Number */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_disable_serial_number_control control; /**< control. */
    bcmolt_serial_number serial_number; /**< serial number. */
} bcmolt_pon_interface_disable_serial_number_data;

/* Constants associated with bcmolt_pon_interface_disable_serial_number_data. */
#define BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "disable_serial_number" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_disable_serial_number_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_disable_serial_number;

/** Transport message definition for "single_request_standby_pon_monitoring" group of "pon_interface"
  * object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_single_request_standby_pon_monitoring;

/** pon interface: Run Special BW Map */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t number_of_cycle; /**< number of cycle. */
    uint8_t allocation_number; /**< allocation number. */
    uint8_t bw_map_array; /**< bw map array. */
} bcmolt_pon_interface_run_special_bw_map_data;

/* Constants associated with bcmolt_pon_interface_run_special_bw_map_data. */
#define BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "run_special_bw_map" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_run_special_bw_map_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_run_special_bw_map;

/** Transport message definition for "tod_request" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_tod_request;

/** pon interface: Start ONU Firmware Upgrade */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_id_list_u32 list_of_onu_ids; /**< List of ONU IDs to upgrade the firmware. */
} bcmolt_pon_interface_start_onu_upgrade_data;

/* Constants associated with bcmolt_pon_interface_start_onu_upgrade_data. */
#define BCMOLT_PON_INTERFACE_START_ONU_UPGRADE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "start_onu_upgrade" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_start_onu_upgrade_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_start_onu_upgrade;

/** Transport message definition for "abort_onu_upgrade" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_abort_onu_upgrade;

/** pon interface: protection switching type c set multiple onu state */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_switch_over_type_c_onu_state onu_state; /**< onu state. */
    bcmolt_onu_id_list_u32 onu_list; /**< onu list. */
} bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data;

/* Constants associated with bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data. */
#define BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "protection_switching_type_c_set_multiple_onu_state" group of
  * "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state;

/** pon interface: Protection switching apply re-range delta (IEEE) */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t rerange_delta; /**< Re-range delta. */
} bcmolt_pon_interface_protection_switching_apply_rerange_delta_data;

/* Constants associated with bcmolt_pon_interface_protection_switching_apply_rerange_delta_data. */
#define BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "protection_switching_apply_rerange_delta" group of
  * "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_protection_switching_apply_rerange_delta_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_protection_switching_apply_rerange_delta;

/** pon interface: XGPON CPU packets */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_packet_type packet_type; /**< packet type. */
    bcmos_bool calc_crc; /**< calc crc. */
    bcmolt_gem_port_id_list_u8_max_16 gem_port_list; /**< gem port list. */
    bcmolt_bin_str buffer; /**< buffer. */
} bcmolt_pon_interface_cpu_packets_data;

/* Constants associated with bcmolt_pon_interface_cpu_packets_data. */
#define BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_GEM_PORT_LIST_MIN_LENGTH 0
#define BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_GEM_PORT_LIST_MAX_LENGTH 16

/** Transport message definition for "cpu_packets" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_cpu_packets_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_cpu_packets;

/** pon interface: Broadcast PLOAM Packet */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str_40 ploam; /**< ploam. */
} bcmolt_pon_interface_broadcast_ploam_packet_data;

/* Constants associated with bcmolt_pon_interface_broadcast_ploam_packet_data. */
#define BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_PLOAM_MAX_LENGTH 40
#define BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_PLOAM_LENGTH 40

/** Transport message definition for "broadcast_ploam_packet" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_broadcast_ploam_packet_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_broadcast_ploam_packet;

/** pon interface: State Change Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< Result. */
    bcmolt_interface_state previous_state; /**< Previous state. */
    bcmolt_interface_state new_state; /**< new state. */
} bcmolt_pon_interface_state_change_completed_data;

/* Constants associated with bcmolt_pon_interface_state_change_completed_data. */
#define BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "state_change_completed" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_state_change_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_state_change_completed;

/** pon interface: TOD request completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_str_64 tod_string; /**< tod_string. */
    uint64_t sfc; /**< sfc. */
    uint64_t rtc_offset_sec; /**< rtc_offset_sec. */
    uint32_t rtc_offset_nsec; /**< rtc_offset_nsec. */
    bcmolt_result status; /**< status. */
} bcmolt_pon_interface_tod_request_completed_data;

/* Constants associated with bcmolt_pon_interface_tod_request_completed_data. */
#define BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL

/** Transport message definition for "tod_request_completed" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_tod_request_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_tod_request_completed;

/** pon interface: LOS */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status status; /**< status. */
} bcmolt_pon_interface_los_data;

/* Constants associated with bcmolt_pon_interface_los_data. */
#define BCMOLT_PON_INTERFACE_LOS_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "los" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_los_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_los;

/** Transport message definition for "serial_number_acquisition_cycle_start" group of "pon_interface"
  * object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_serial_number_acquisition_cycle_start;

/** pon interface: Protection Switching Traffic Resume */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_traffic_resume_result result; /**< Result. */
} bcmolt_pon_interface_protection_switching_traffic_resume_data;

/* Constants associated with bcmolt_pon_interface_protection_switching_traffic_resume_data. */
#define BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TRAFFIC_RESUME_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "protection_switching_traffic_resume" group of "pon_interface"
  * object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_protection_switching_traffic_resume_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_protection_switching_traffic_resume;

/** pon interface: Protection Switching ONUs Ranged */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_itupon_onu_eqd_list_u32 onus; /**< ONUs. */
} bcmolt_pon_interface_protection_switching_onus_ranged_data;

/* Constants associated with bcmolt_pon_interface_protection_switching_onus_ranged_data. */
#define BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_ONUS_RANGED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "protection_switching_onus_ranged" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_protection_switching_onus_ranged_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_protection_switching_onus_ranged;

/** Transport message definition for "protection_switching_rerange_failure" group of "pon_interface"
  * object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_protection_switching_rerange_failure;

/** pon interface: Protection Switching Switchover Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< Result. */
} bcmolt_pon_interface_protection_switching_switchover_completed_data;

/* Constants associated with bcmolt_pon_interface_protection_switching_switchover_completed_data. */
#define BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "protection_switching_switchover_completed" group of
  * "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_protection_switching_switchover_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_protection_switching_switchover_completed;

/** pon interface: Standby PON Monitoring Cycle Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t number_of_detected_delimiter; /**< number of detected delimiter. */
    bcmolt_status energy_detect_signal; /**< energy detect signal. */
} bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data;

/* Constants associated with bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data. */
#define BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "standby_pon_monitoring_cycle_completed" group of "pon_interface"
  * object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_standby_pon_monitoring_cycle_completed;

/** pon interface: ONU Discovered */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_serial_number serial_number; /**< serial number. */
    uint32_t ranging_time; /**< ranging time. */
    bcmolt_onu_id onu_id; /**< onu_id. */
    bcmolt_upstream_line_rate_capabilities upstream_line_rate_capabilities; /**< Upstream line rate capabilities */
    uint8_t current_downstream_pon_id; /**< The PON-ID received by the ONU in its current downstream wavelength channel */
    uint8_t current_upstream_pon_id; /**< The PON-ID of the Channel Profile containing the descriptor of the upstream wavelength channel in which the ONU is transmitting */
    bcmolt_arr_calibration_record_8 calibration_record; /**< Calibration record */
    uint8_t tuning_granularity; /**< The tuning granularity of the ONU transmitted expressed in units of 1Ghz. Value of 0 indicates that the ONU does not support fine tuning / dithering */
    uint8_t step_tuning_time; /**< The value of the tuning time for a single granularity step, expressed in unit of PHY frames. The value 0 indicates that the ONU does not support fine tuning / dithering */
    uint8_t attenuation; /**< The ONU attenuation in steps of 3dB at the time of the message transmission as part of the power levelling report. Value of 0 represents un-attenuated transmission */
    uint8_t power_levelling_capabilities; /**< The ONU supports attenuation level in step of 3dB */
} bcmolt_pon_interface_onu_discovered_data;

/* Constants associated with bcmolt_pon_interface_onu_discovered_data. */
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_PRESENCE_MASK_ALL 0x00000000000007FFULL
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_CALIBRATION_RECORD_LENGTH 8
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_TUNING_GRANULARITY_DEFAULT 0
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_STEP_TUNING_TIME_DEFAULT 0
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_STEP_TUNING_TIME_MIN 0
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_STEP_TUNING_TIME_MAX 255
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ATTENUATION_DEFAULT 0
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ATTENUATION_MIN 0
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ATTENUATION_MAX 7
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_POWER_LEVELLING_CAPABILITIES_DEFAULT 0
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_POWER_LEVELLING_CAPABILITIES_MIN 0
#define BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_POWER_LEVELLING_CAPABILITIES_MAX 127

/** Transport message definition for "onu_discovered" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_onu_discovered_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_onu_discovered;

/** pon interface: CPU Packets Failure */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_packet_injection_error error; /**< The error that was encountered. */
    bcmolt_gem_port_id gem_port_id; /**< The GEM port that caused the error. */
} bcmolt_pon_interface_cpu_packets_failure_data;

/* Constants associated with bcmolt_pon_interface_cpu_packets_failure_data. */
#define BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "cpu_packets_failure" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_cpu_packets_failure_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_cpu_packets_failure;

/** Transport message definition for "deactivate_all_onus_completed" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_deactivate_all_onus_completed;

/** Transport message definition for "disable_all_onus_completed" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_disable_all_onus_completed;

/** pon interface: activate all onus completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< result. */
} bcmolt_pon_interface_activate_all_onus_completed_data;

/* Constants associated with bcmolt_pon_interface_activate_all_onus_completed_data. */
#define BCMOLT_PON_INTERFACE_ACTIVATE_ALL_ONUS_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "activate_all_onus_completed" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_activate_all_onus_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_activate_all_onus_completed;

/** Transport message definition for "enable_all_onus_completed" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_enable_all_onus_completed;

/** pon interface: ONU Upgrade Complete */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_pon_ni_onu_upgrade_status_code overall_status; /**< Overall status of the ONU upgrade (success or failure). */
    uint32_t file_size_in_bytes; /**< Total size of the file to send in bytes. */
    bcmolt_onu_upgrade_status_list_u32_max_128 onu_status; /**< Status for each ONU that is part of the upgrade process. */
} bcmolt_pon_interface_onu_upgrade_complete_data;

/* Constants associated with bcmolt_pon_interface_onu_upgrade_complete_data. */
#define BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ONU_STATUS_MAX_LENGTH 128

/** Transport message definition for "onu_upgrade_complete" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_onu_upgrade_complete_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_onu_upgrade_complete;

/** Transport message definition for "ieee_rogue_detection_completed" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
} bcmolt_pon_interface_ieee_rogue_detection_completed;

/** pon interface: MPCP Timestamp Changed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t mpcp_timestamp; /**< The MPCP time at which the pulse was received. */
} bcmolt_pon_interface_mpcp_timestamp_changed_data;

/* Constants associated with bcmolt_pon_interface_mpcp_timestamp_changed_data. */
#define BCMOLT_PON_INTERFACE_MPCP_TIMESTAMP_CHANGED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "mpcp_timestamp_changed" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_mpcp_timestamp_changed_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_mpcp_timestamp_changed;

/** pon interface: Switch PON type */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_pon_type new_pon_type; /**< The PON type requested by switch_pon_type operation */
} bcmolt_pon_interface_switch_pon_type_data;

/* Constants associated with bcmolt_pon_interface_switch_pon_type_data. */
#define BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "switch_pon_type" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_switch_pon_type_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_switch_pon_type;

/** pon interface: Switch PON type completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< Result of the operation. */
    bcmolt_switch_pon_type_fail_reason fail_reason; /**< Failure reason. */
    bcmolt_pon_type new_type; /**< The new PON type that is set by the switch_pon_type operation. In case of failure it is the same as the old type.. */
    bcmolt_pon_type old_type; /**< The PON type before the switch PON type operation. */
} bcmolt_pon_interface_switch_pon_type_completed_data;

/* Constants associated with bcmolt_pon_interface_switch_pon_type_completed_data. */
#define BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL

/** Transport message definition for "switch_pon_type_completed" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_switch_pon_type_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_switch_pon_type_completed;

/** pon interface: rogue detection tool */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint16_t start_offset; /**< counted in 622/644 clock cycles */
    uint8_t use_onu_id; /**< collect data for specific onu = 1, always collect data = 0 */
    uint8_t onu_id; /**< onu id */
} bcmolt_pon_interface_rogue_detection_tool_data;

/* Constants associated with bcmolt_pon_interface_rogue_detection_tool_data. */
#define BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "rogue_detection_tool" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_rogue_detection_tool_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_rogue_detection_tool;

/** pon interface: rogue detection tool done */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_result result; /**< result. */
    bcmolt_u64_list_u32_hex output; /**< output. */
} bcmolt_pon_interface_rogue_detection_tool_done_data;

/* Constants associated with bcmolt_pon_interface_rogue_detection_tool_done_data. */
#define BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "rogue_detection_tool_done" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_rogue_detection_tool_done_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_rogue_detection_tool_done;

/** pon interface: ONU Upgrade Activate Commit */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_id_list_u32 list_of_onu_ids; /**< List of ONU IDs to upgrade the firmware. */
} bcmolt_pon_interface_onu_upgrade_activate_commit_data;

/* Constants associated with bcmolt_pon_interface_onu_upgrade_activate_commit_data. */
#define BCMOLT_PON_INTERFACE_ONU_UPGRADE_ACTIVATE_COMMIT_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "onu_upgrade_activate_commit" group of "pon_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_onu_upgrade_activate_commit_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_onu_upgrade_activate_commit;

/** pon interface: ITU PON Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config fec_codewords; /**< Receive FEC codewords. */
    bcmolt_stat_alarm_config bip_units; /**< Received units (bits in GPON / bytes in XGPON) protected by bip. */
    bcmolt_stat_alarm_config bip_errors; /**< Received bip errors. */
    bcmolt_stat_alarm_config rx_gem; /**< Received valid GEM frames. */
    bcmolt_stat_alarm_config rx_gem_dropped; /**< Received dropped GEM ID frames. */
    bcmolt_stat_alarm_config rx_gem_idle; /**< Received idle GEM frames. */
    bcmolt_stat_alarm_config rx_gem_corrected; /**< Received corrected GEM frames. */
    bcmolt_stat_alarm_config rx_crc_error; /**< Received packets with CRC error. */
    bcmolt_stat_alarm_config rx_fragment_error; /**< Received fragment errors. */
    bcmolt_stat_alarm_config rx_packets_dropped; /**< Global dropped packets. */
    bcmolt_stat_alarm_config rx_dropped_too_short; /**< Received packets dropped due to length too short. */
    bcmolt_stat_alarm_config rx_dropped_too_long; /**< Received packet dropped due to length too long. */
    bcmolt_stat_alarm_config rx_key_error; /**< Received key errors. */
    bcmolt_stat_alarm_config rx_cpu_omci_packets_dropped; /**< Received packets dropped due to illegal length. */
    bcmolt_stat_alarm_config tx_ploams; /**< Transmitted Ploams. */
    bcmolt_stat_alarm_config rx_ploams_dropped; /**< Received dropped Ploams. */
    bcmolt_stat_alarm_config rx_allocations_valid; /**< Received valid allocations. */
    bcmolt_stat_alarm_config rx_allocations_invalid; /**< Received invalid allocations. */
    bcmolt_stat_alarm_config rx_allocations_disabled; /**< Received disabled allocations. */
    bcmolt_stat_alarm_config rx_ploams; /**< Received Ploams. */
    bcmolt_stat_alarm_config rx_ploams_non_idle; /**< Received non idle Ploams. */
    bcmolt_stat_alarm_config rx_ploams_error; /**< Received error Ploams. */
    bcmolt_stat_alarm_config rx_cpu; /**< Received CPU packets. */
    bcmolt_stat_alarm_config rx_omci; /**< Received OMCI packets. */
    bcmolt_stat_alarm_config rx_omci_packets_crc_error; /**< Received OMCI packets with CRC errors. */
    bcmolt_stat_alarm_config tx_packets; /**< Transmitted packets. */
    bcmolt_stat_alarm_config tx_gem; /**< Transmitted GEM frames. */
    bcmolt_stat_alarm_config tx_cpu; /**< Transmitted CPU packets. */
    bcmolt_stat_alarm_config tx_omci; /**< Transmitted OMCI packets. */
    bcmolt_stat_alarm_config tx_dropped_illegal_length; /**< Transmit packets dropped due to illegal length. */
    bcmolt_stat_alarm_config tx_dropped_tpid_miss; /**< Transmit packets dropped due to TPID miss. */
    bcmolt_stat_alarm_config tx_dropped_vid_miss; /**< Transmit packets droped due to VID miss. */
    bcmolt_stat_alarm_config tx_dropped_total; /**< Total transmit packets droped. */
    bcmolt_stat_alarm_config rx_xgtc_headers; /**< Received valid XGTC headers. */
    bcmolt_stat_alarm_config rx_xgtc_corrected; /**< Received corrected XGTC headers. */
    bcmolt_stat_alarm_config rx_xgtc_uncorrected; /**< Received uncorrected XGTC headers. */
    bcmolt_stat_alarm_config fec_codewords_uncorrected; /**< Received uncorrected FEC codewords. */
    bcmolt_stat_alarm_config rx_gem_illegal; /**< Received illegal GEM frames. */
    bcmolt_stat_alarm_config rx_packets; /**< Received packets. */
    bcmolt_stat_alarm_config tx_bytes; /**< Transmitted bytes. */
    bcmolt_stat_alarm_config rx_bytes; /**< Received bytes. */
} bcmolt_pon_interface_itu_pon_stats_cfg_data;

/* Constants associated with bcmolt_pon_interface_itu_pon_stats_cfg_data. */
#define BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x000001FFFFFFFFFFULL

/** Transport message definition for "itu_pon_stats_cfg" group of "pon_interface" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_itu_pon_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_itu_pon_stats_cfg;

/** pon interface: ITU PON Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_pon_interface_itu_pon_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_pon_interface_itu_pon_stats_alarm_raised_data;

/* Constants associated with bcmolt_pon_interface_itu_pon_stats_alarm_raised_data. */
#define BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "itu_pon_stats_alarm_raised" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_itu_pon_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_itu_pon_stats_alarm_raised;

/** pon interface: ITU PON Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_pon_interface_itu_pon_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data;

/* Constants associated with bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data. */
#define BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "itu_pon_stats_alarm_cleared" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_itu_pon_stats_alarm_cleared;

/** pon interface: Active Ethernet Interface Counters Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config rx_bytes; /**< The number of bytes received on this interface. */
    bcmolt_stat_alarm_config rx_frames; /**< The number of frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_64; /**< The number of 64 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_65_127; /**< The number of 65 to 127 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_128_255; /**< The number of 128 to 255 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_256_511; /**< The number of 256 to 511 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_512_1023; /**< The number of 512 to 1023 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_1024_1518; /**< The number of 1024 to 1518 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_1519_2047; /**< The number of 1519 to 2047 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_2048_4095; /**< The number of 2048 to 4095 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_4096_9216; /**< The number of 4096 to 9216 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_frames_9217_16383; /**< The number of 9217 to 16383 byte frames received on this interface. */
    bcmolt_stat_alarm_config rx_broadcast_frames; /**< The number of broadcast frames received on this interface. */
    bcmolt_stat_alarm_config rx_data_bytes; /**< The number of data bytes received on this interface. */
    bcmolt_stat_alarm_config rx_multicast_frames; /**< The number of multicast frames received on this interface. */
    bcmolt_stat_alarm_config rx_unicast_frames; /**< The number of unicast frames received on this interface. */
    bcmolt_stat_alarm_config rx_abort_frames; /**< The number of abort frames received on this interface. */
    bcmolt_stat_alarm_config rx_fcs_error; /**< The number of bad FCS errors received on this interface. */
    bcmolt_stat_alarm_config rx_oversize_error; /**< The number of oversize errors received on this interface. */
    bcmolt_stat_alarm_config rx_runt_error; /**< The number of runt errors received on this interface. */
    bcmolt_stat_alarm_config tx_bytes; /**< The number of bytes transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames; /**< The number of frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_64; /**< The number of 64 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_65_127; /**< The number of 65 to 127 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_128_255; /**< The number of 128 to 255 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_256_511; /**< The number of 256 to 511 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_512_1023; /**< The number of 512 to 1023 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_1024_1518; /**< The number of 1024 to 1518 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_1519_2047; /**< The number of 1519 to 2047 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_2048_4095; /**< The number of 2048 to 4095 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_4096_9216; /**< The number of 4096 to 9216 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_frames_9217_16383; /**< The number of 9217 to 16383 byte frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_broadcast_frames; /**< The number of broadcast frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_data_bytes; /**< The number of data bytes transmitted on this interface. */
    bcmolt_stat_alarm_config tx_multicast_frames; /**< The number of multicast frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_unicast_frames; /**< The number of unicast frames transmitted on this interface. */
    bcmolt_stat_alarm_config tx_abort_frames; /**< Number of abort frames transmitted on this interface. */
} bcmolt_pon_interface_ae_stats_cfg_data;

/* Constants associated with bcmolt_pon_interface_ae_stats_cfg_data. */
#define BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x0000001FFFFFFFFFULL

/** Transport message definition for "ae_stats_cfg" group of "pon_interface" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_ae_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_ae_stats_cfg;

/** pon interface: Active Ethernet Interface Counters Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_pon_interface_ae_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_pon_interface_ae_stats_alarm_raised_data;

/* Constants associated with bcmolt_pon_interface_ae_stats_alarm_raised_data. */
#define BCMOLT_PON_INTERFACE_AE_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "ae_stats_alarm_raised" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_ae_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_ae_stats_alarm_raised;

/** pon interface: Active Ethernet Interface Counters Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_pon_interface_ae_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_pon_interface_ae_stats_alarm_cleared_data;

/* Constants associated with bcmolt_pon_interface_ae_stats_alarm_cleared_data. */
#define BCMOLT_PON_INTERFACE_AE_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "ae_stats_alarm_cleared" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_ae_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_ae_stats_alarm_cleared;

/** pon interface: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool activate_all_onus_completed; /**< If true, indications of type "activate_all_onus_completed" will be generated. */
    bcmos_bool ae_stats_alarm_cleared; /**< If true, indications of type "ae_stats_alarm_cleared" will be generated. */
    bcmos_bool ae_stats_alarm_raised; /**< If true, indications of type "ae_stats_alarm_raised" will be generated. */
    bcmos_bool cpu_packets_failure; /**< If true, indications of type "cpu_packets_failure" will be generated. */
    bcmos_bool deactivate_all_onus_completed; /**< If true, indications of type "deactivate_all_onus_completed" will be generated. */
    bcmos_bool disable_all_onus_completed; /**< If true, indications of type "disable_all_onus_completed" will be generated. */
    bcmos_bool enable_all_onus_completed; /**< If true, indications of type "enable_all_onus_completed" will be generated. */
    bcmos_bool ieee_rogue_detection_completed; /**< If true, indications of type "ieee_rogue_detection_completed" will be generated. */
    bcmos_bool itu_pon_stats_alarm_cleared; /**< If true, indications of type "itu_pon_stats_alarm_cleared" will be generated. */
    bcmos_bool itu_pon_stats_alarm_raised; /**< If true, indications of type "itu_pon_stats_alarm_raised" will be generated. */
    bcmos_bool los; /**< If true, indications of type "los" will be generated. */
    bcmos_bool mpcp_timestamp_changed; /**< If true, indications of type "mpcp_timestamp_changed" will be generated. */
    bcmos_bool onu_discovered; /**< If true, indications of type "onu_discovered" will be generated. */
    bcmos_bool onu_upgrade_complete; /**< If true, indications of type "onu_upgrade_complete" will be generated. */
    bcmos_bool protection_switching_onus_ranged; /**< If true, indications of type "protection_switching_onus_ranged" will be generated. */
    bcmos_bool protection_switching_rerange_failure; /**< If true, indications of type "protection_switching_rerange_failure" will be generated. */
    bcmos_bool protection_switching_switchover_completed; /**< If true, indications of type "protection_switching_switchover_completed" will be generated. */
    bcmos_bool protection_switching_traffic_resume; /**< If true, indications of type "protection_switching_traffic_resume" will be generated. */
    bcmos_bool rogue_detection_tool_done; /**< If true, indications of type "rogue_detection_tool_done" will be generated. */
    bcmos_bool serial_number_acquisition_cycle_start; /**< If true, indications of type "serial_number_acquisition_cycle_start" will be generated. */
    bcmos_bool standby_pon_monitoring_cycle_completed; /**< If true, indications of type "standby_pon_monitoring_cycle_completed" will be generated. */
    bcmos_bool state_change_completed; /**< If true, indications of type "state_change_completed" will be generated. */
    bcmos_bool switch_pon_type_completed; /**< If true, indications of type "switch_pon_type_completed" will be generated. */
    bcmos_bool tod_request_completed; /**< If true, indications of type "tod_request_completed" will be generated. */
} bcmolt_pon_interface_auto_cfg_data;

/* Constants associated with bcmolt_pon_interface_auto_cfg_data. */
#define BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000FFFFFFULL

/** Transport message definition for "auto_cfg" group of "pon_interface" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_pon_interface_key key; /**< Object key. */
    bcmolt_pon_interface_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_pon_interface_auto_cfg;

/** Protection Interface: key */
typedef struct
{
    bcmolt_protection_interface_id id; /**< Id used to represent virtual Protection Interface Objects */
} bcmolt_protection_interface_key;

/* Constants associated with bcmolt_protection_interface_key. */
#define BCMOLT_PROTECTION_INTERFACE_KEY_ID_MIN (bcmolt_protection_interface_id)0U
#define BCMOLT_PROTECTION_INTERFACE_KEY_ID_MAX (bcmolt_protection_interface_id)63U

/** Protection Interface: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state state; /**< Not Configured or Configured */
    bcmolt_intf_ref primary_interface; /**< Primary Interface Reference with type */
    bcmolt_intf_ref secondary_interface; /**< Secondary Interface Reference with type */
    bcmolt_active_interface active_interface; /**< Currently active interface in protection interface pair (Primary or Secondary) */
} bcmolt_protection_interface_cfg_data;

/* Constants associated with bcmolt_protection_interface_cfg_data. */
#define BCMOLT_PROTECTION_INTERFACE_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_PROTECTION_INTERFACE_CFG_DATA_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED
#define BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ACTIVE_INTERFACE_DEFAULT BCMOLT_ACTIVE_INTERFACE_UNASSIGNED

/** Transport message definition for "cfg" group of "protection_interface" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_protection_interface_key key; /**< Object key. */
    bcmolt_protection_interface_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_protection_interface_cfg;

/** Multi-object message definition for "cfg" group of "protection_interface" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_protection_interface_key key; /**< Object key (can include wildcards). */
    bcmolt_protection_interface_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_protection_interface_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_protection_interface_cfg *responses; /**< Responses to the last API call. */

    bcmolt_protection_interface_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_protection_interface_multi_cfg;

/** Transport message definition for "protection_switch" group of "protection_interface" object. */
typedef struct
{
    bcmolt_oper hdr; /**< Transport header. */
    bcmolt_protection_interface_key key; /**< Object key. */
} bcmolt_protection_interface_protection_switch;

/** Protection Interface: Protection Switch Completed */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_active_interface active_interface; /**< Newly active Interface (Primary or Secondary) */
} bcmolt_protection_interface_protection_switch_completed_data;

/* Constants associated with bcmolt_protection_interface_protection_switch_completed_data. */
#define BCMOLT_PROTECTION_INTERFACE_PROTECTION_SWITCH_COMPLETED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "protection_switch_completed" group of "protection_interface"
  * object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_protection_interface_key key; /**< Object key. */
    bcmolt_protection_interface_protection_switch_completed_data data; /**< All properties that must be set by the user. */
} bcmolt_protection_interface_protection_switch_completed;

/** Protection Interface: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool protection_switch_completed; /**< If true, indications of type "protection_switch_completed" will be generated. */
} bcmolt_protection_interface_auto_cfg_data;

/* Constants associated with bcmolt_protection_interface_auto_cfg_data. */
#define BCMOLT_PROTECTION_INTERFACE_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "auto_cfg" group of "protection_interface" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_protection_interface_key key; /**< Object key. */
    bcmolt_protection_interface_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_protection_interface_auto_cfg;

/** Software Error: key */
typedef struct
{
    bcmolt_ldid device_id; /**< Device ID */
    uint32_t idx; /**< SW error table index */
} bcmolt_software_error_key;

/** Software Error: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_sw_error entry; /**< Entry. */
} bcmolt_software_error_cfg_data;

/* Constants associated with bcmolt_software_error_cfg_data. */
#define BCMOLT_SOFTWARE_ERROR_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "cfg" group of "software_error" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_software_error_key key; /**< Object key. */
    bcmolt_software_error_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_software_error_cfg;

/** Multi-object message definition for "cfg" group of "software_error" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_software_error_key key; /**< Object key (can include wildcards). */
    bcmolt_software_error_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_software_error_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_software_error_cfg *responses; /**< Responses to the last API call. */

    bcmolt_software_error_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_software_error_multi_cfg;

/** switch inni: key */
typedef struct
{
    bcmolt_switch_inni_id id; /**< id. */
} bcmolt_switch_inni_key;

/* Constants associated with bcmolt_switch_inni_key. */
#define BCMOLT_SWITCH_INNI_KEY_ID_DEFAULT (bcmolt_switch_inni_id)0
#define BCMOLT_SWITCH_INNI_KEY_ID_MIN (bcmolt_switch_inni_id)0
#define BCMOLT_SWITCH_INNI_KEY_ID_MAX (bcmolt_switch_inni_id)127

/** switch inni: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state config_state; /**< config state. */
    bcmolt_link_state link_state; /**< Current Link State (Link Up or Link Down) */
} bcmolt_switch_inni_cfg_data;

/* Constants associated with bcmolt_switch_inni_cfg_data. */
#define BCMOLT_SWITCH_INNI_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_SWITCH_INNI_CFG_DATA_CONFIG_STATE_DEFAULT BCMOLT_CONFIG_STATE_CONFIGURED

/** Transport message definition for "cfg" group of "switch_inni" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_switch_inni_key key; /**< Object key. */
    bcmolt_switch_inni_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_switch_inni_cfg;

/** Multi-object message definition for "cfg" group of "switch_inni" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_switch_inni_key key; /**< Object key (can include wildcards). */
    bcmolt_switch_inni_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_switch_inni_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_switch_inni_cfg *responses; /**< Responses to the last API call. */

    bcmolt_switch_inni_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_switch_inni_multi_cfg;

/** switch inni: Switch INNI Interface Statistics */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t rx_bytes; /**< RFC 2233 */
    uint64_t rx_packets; /**< RFC 1213 ucast + none-ucast */
    uint64_t rx_ucast_packets; /**< RFC 2233 */
    uint64_t rx_mcast_packets; /**< EFC 2233 */
    uint64_t rx_bcast_packets; /**< RFC 2233 */
    uint64_t rx_error_packets; /**< RFC 1213 */
    uint64_t rx_fcs_error_packets; /**< RFC 2665 */
    uint64_t rx_undersize_packets; /**< Broadcom-Specific */
    uint64_t rx_oversize_packets; /**< Rx component of RFC 2665 snmpEtherStatsOversizePkts */
    uint64_t rx_jabber_packets; /**< RFC 1757 (EtherStat) */
    uint64_t tx_bytes; /**< RFC 2233 */
    uint64_t tx_packets; /**< RFC 1213 ucast + none-ucast */
    uint64_t tx_ucast_packets; /**< RFC 2233 */
    uint64_t tx_mcast_packets; /**< RFC 2233 */
    uint64_t tx_bcast_packets; /**< RFC 2233 */
    uint64_t tx_error_packets; /**< RFC 1213 */
    uint64_t tx_undersize_packets; /**< Broadcom-Specific */
    uint64_t tx_oversize_packets; /**< Tx component of RFC 2665 snmpEtherStatsOversizePkts */
    uint64_t tx_jabber_packets; /**< RFC 1757 (EtherStat) */
    uint64_t rx_frames_64; /**< Broadcom-Specific */
    uint64_t rx_frames_65_127; /**< Broadcom-Specific */
    uint64_t rx_frames_128_255; /**< Broadcom-Specific */
    uint64_t rx_frames_256_511; /**< Broadcom-Specific */
    uint64_t rx_frames_512_1023; /**< Broadcom-Specific */
    uint64_t rx_frames_1024_1518; /**< Broadcom-Specific */
    uint64_t rx_frames_1519_2047; /**< Broadcom-Specific */
    uint64_t rx_frames_2048_4095; /**< Broadcom-Specific */
    uint64_t rx_frames_4096_9216; /**< Broadcom-Specific */
    uint64_t rx_frames_9217_16383; /**< Broadcom-Specific */
    uint64_t tx_frames_64; /**< Broadcom-Specific */
    uint64_t tx_frames_65_127; /**< Broadcom-Specific */
    uint64_t tx_frames_128_255; /**< Broadcom-Specific */
    uint64_t tx_frames_256_511; /**< Broadcom-Specific */
    uint64_t tx_frames_512_1023; /**< Broadcom-Specific */
    uint64_t tx_frames_1024_1518; /**< Broadcom-Specific */
    uint64_t tx_frames_1519_2047; /**< Broadcom-Specific */
    uint64_t tx_frames_2048_4095; /**< Broadcom-Specific */
    uint64_t tx_frames_4096_9216; /**< Broadcom-Specific */
    uint64_t tx_frames_9217_16383; /**< Broadcom-Specific */
} bcmolt_switch_inni_stats_data;

/* Constants associated with bcmolt_switch_inni_stats_data. */
#define BCMOLT_SWITCH_INNI_STATS_DATA_PRESENCE_MASK_ALL 0x000000FFFFFFFFBFULL

/** Transport message definition for "stats" group of "switch_inni" object. */
typedef struct
{
    bcmolt_stat hdr; /**< Transport header. */
    bcmolt_switch_inni_key key; /**< Object key. */
    bcmolt_switch_inni_stats_data data; /**< All properties that must be set by the user. */
} bcmolt_switch_inni_stats;

/** Multi-object message definition for "stats" group of "switch_inni" object. */
typedef struct
{
    bcmolt_multi_stat hdr; /**< Transport header. */
    bcmolt_switch_inni_key key; /**< Object key (can include wildcards). */
    bcmolt_switch_inni_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_switch_inni_stats_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_switch_inni_stats *responses; /**< Responses to the last API call. */

    bcmolt_switch_inni_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_switch_inni_multi_stats;

/** switch inni: link_state_change */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_link_state old_state; /**< old_state. */
    bcmolt_link_state new_state; /**< new_state. */
} bcmolt_switch_inni_link_state_change_data;

/* Constants associated with bcmolt_switch_inni_link_state_change_data. */
#define BCMOLT_SWITCH_INNI_LINK_STATE_CHANGE_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Transport message definition for "link_state_change" group of "switch_inni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_switch_inni_key key; /**< Object key. */
    bcmolt_switch_inni_link_state_change_data data; /**< All properties that must be set by the user. */
} bcmolt_switch_inni_link_state_change;

/** switch inni: Switch INNI Interface Statistics Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_config rx_bytes; /**< RFC 2233 */
    bcmolt_stat_alarm_config rx_packets; /**< RFC 1213 ucast + none-ucast */
    bcmolt_stat_alarm_config rx_ucast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config rx_mcast_packets; /**< EFC 2233 */
    bcmolt_stat_alarm_config rx_bcast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config rx_error_packets; /**< RFC 1213 */
    bcmolt_stat_alarm_config rx_fcs_error_packets; /**< RFC 2665 */
    bcmolt_stat_alarm_config rx_undersize_packets; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_oversize_packets; /**< Rx component of RFC 2665 snmpEtherStatsOversizePkts */
    bcmolt_stat_alarm_config rx_jabber_packets; /**< RFC 1757 (EtherStat) */
    bcmolt_stat_alarm_config tx_bytes; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_packets; /**< RFC 1213 ucast + none-ucast */
    bcmolt_stat_alarm_config tx_ucast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_mcast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_bcast_packets; /**< RFC 2233 */
    bcmolt_stat_alarm_config tx_error_packets; /**< RFC 1213 */
    bcmolt_stat_alarm_config tx_undersize_packets; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_oversize_packets; /**< Tx component of RFC 2665 snmpEtherStatsOversizePkts */
    bcmolt_stat_alarm_config tx_jabber_packets; /**< RFC 1757 (EtherStat) */
    bcmolt_stat_alarm_config rx_frames_64; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_65_127; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_128_255; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_256_511; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_512_1023; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_1024_1518; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_1519_2047; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_2048_4095; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_4096_9216; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config rx_frames_9217_16383; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_64; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_65_127; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_128_255; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_256_511; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_512_1023; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_1024_1518; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_1519_2047; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_2048_4095; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_4096_9216; /**< Broadcom-Specific */
    bcmolt_stat_alarm_config tx_frames_9217_16383; /**< Broadcom-Specific */
} bcmolt_switch_inni_stats_cfg_data;

/* Constants associated with bcmolt_switch_inni_stats_cfg_data. */
#define BCMOLT_SWITCH_INNI_STATS_CFG_DATA_PRESENCE_MASK_ALL 0x000000FFFFFFFFBFULL

/** Transport message definition for "stats_cfg" group of "switch_inni" object. */
typedef struct
{
    bcmolt_stat_cfg hdr; /**< Transport header. */
    bcmolt_switch_inni_key key; /**< Object key. */
    bcmolt_switch_inni_stats_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_switch_inni_stats_cfg;

/** switch inni: Switch INNI Interface Statistics Alarm Raised */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_switch_inni_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_switch_inni_stats_alarm_raised_data;

/* Constants associated with bcmolt_switch_inni_stats_alarm_raised_data. */
#define BCMOLT_SWITCH_INNI_STATS_ALARM_RAISED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_raised" group of "switch_inni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_switch_inni_key key; /**< Object key. */
    bcmolt_switch_inni_stats_alarm_raised_data data; /**< All properties that must be set by the user. */
} bcmolt_switch_inni_stats_alarm_raised;

/** switch inni: Switch INNI Interface Statistics Alarm Cleared */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_switch_inni_stats_data_id stat; /**< Statistic identifier. */
} bcmolt_switch_inni_stats_alarm_cleared_data;

/* Constants associated with bcmolt_switch_inni_stats_alarm_cleared_data. */
#define BCMOLT_SWITCH_INNI_STATS_ALARM_CLEARED_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Transport message definition for "stats_alarm_cleared" group of "switch_inni" object. */
typedef struct
{
    bcmolt_auto hdr; /**< Transport header. */
    bcmolt_switch_inni_key key; /**< Object key. */
    bcmolt_switch_inni_stats_alarm_cleared_data data; /**< All properties that must be set by the user. */
} bcmolt_switch_inni_stats_alarm_cleared;

/** switch inni: Indication Configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool link_state_change; /**< If true, indications of type "link_state_change" will be generated. */
    bcmos_bool stats_alarm_cleared; /**< If true, indications of type "stats_alarm_cleared" will be generated. */
    bcmos_bool stats_alarm_raised; /**< If true, indications of type "stats_alarm_raised" will be generated. */
} bcmolt_switch_inni_auto_cfg_data;

/* Constants associated with bcmolt_switch_inni_auto_cfg_data. */
#define BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Transport message definition for "auto_cfg" group of "switch_inni" object. */
typedef struct
{
    bcmolt_auto_cfg hdr; /**< Transport header. */
    bcmolt_switch_inni_key key; /**< Object key. */
    bcmolt_switch_inni_auto_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_switch_inni_auto_cfg;

/** tc_to_queue: key */
typedef struct
{
    uint16_t id; /**< id. */
    bcmolt_tm_sched_dir dir; /**< dir. */
} bcmolt_tc_to_queue_key;

/* Constants associated with bcmolt_tc_to_queue_key. */
#define BCMOLT_TC_TO_QUEUE_KEY_ID_MIN 1U
#define BCMOLT_TC_TO_QUEUE_KEY_ID_MAX 4096U

/** tc_to_queue: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_arr_tm_queue_ref_8 queue; /**< queue ref for each tc 0..7 */
} bcmolt_tc_to_queue_cfg_data;

/* Constants associated with bcmolt_tc_to_queue_cfg_data. */
#define BCMOLT_TC_TO_QUEUE_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_TC_TO_QUEUE_CFG_DATA_QUEUE_LENGTH 8

/** Transport message definition for "cfg" group of "tc_to_queue" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_tc_to_queue_key key; /**< Object key. */
    bcmolt_tc_to_queue_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_tc_to_queue_cfg;

/** Multi-object message definition for "cfg" group of "tc_to_queue" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_tc_to_queue_key key; /**< Object key (can include wildcards). */
    bcmolt_tc_to_queue_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_tc_to_queue_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_tc_to_queue_cfg *responses; /**< Responses to the last API call. */

    bcmolt_tc_to_queue_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_tc_to_queue_multi_cfg;

/** tm_qmp: key */
typedef struct
{
    bcmolt_tm_qmp_id id; /**< id. */
} bcmolt_tm_qmp_key;

/* Constants associated with bcmolt_tm_qmp_key. */
#define BCMOLT_TM_QMP_KEY_ID_DEFAULT (bcmolt_tm_qmp_id)255

/** tm_qmp: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_tm_qmp_type type; /**< type. */
    bcmolt_arr_u8_8 pbits_to_tmq_id; /**< pbits_to_tmq_id. */
    bcmolt_config_state state; /**< state. */
} bcmolt_tm_qmp_cfg_data;

/* Constants associated with bcmolt_tm_qmp_cfg_data. */
#define BCMOLT_TM_QMP_CFG_DATA_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_TM_QMP_CFG_DATA_TYPE_DEFAULT BCMOLT_TM_QMP_TYPE_UNDEFINED
#define BCMOLT_TM_QMP_CFG_DATA_PBITS_TO_TMQ_ID_LENGTH 8
#define BCMOLT_TM_QMP_CFG_DATA_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED

/** Transport message definition for "cfg" group of "tm_qmp" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_tm_qmp_key key; /**< Object key. */
    bcmolt_tm_qmp_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_tm_qmp_cfg;

/** Multi-object message definition for "cfg" group of "tm_qmp" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_tm_qmp_key key; /**< Object key (can include wildcards). */
    bcmolt_tm_qmp_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_tm_qmp_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_tm_qmp_cfg *responses; /**< Responses to the last API call. */

    bcmolt_tm_qmp_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_tm_qmp_multi_cfg;

/** tm_queue: key */
typedef struct
{
    bcmolt_tm_sched_id sched_id; /**< Scheduler that owns the queue */
    bcmolt_tm_queue_set_id tm_q_set_id; /**< TM Queue Set Id */
    bcmolt_tm_queue_id id; /**< Queue id */
} bcmolt_tm_queue_key;

/* Constants associated with bcmolt_tm_queue_key. */
#define BCMOLT_TM_QUEUE_KEY_SCHED_ID_DEFAULT (bcmolt_tm_sched_id)65535U
#define BCMOLT_TM_QUEUE_KEY_TM_Q_SET_ID_DEFAULT (bcmolt_tm_queue_set_id)32768U
#define BCMOLT_TM_QUEUE_KEY_ID_DEFAULT (bcmolt_tm_queue_id)65535U

/** tm_queue: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state state; /**< State. */
    bcmolt_tm_sched_param tm_sched_param; /**< Scheduling priority */
    bcmolt_tm_shaping rate; /**< Rate shaping parameters */
    bcmolt_control_state control_state; /**< enable or disable state of the TM queue */
    bcmolt_tm_sched_attachment_point cir_attachment_point; /**< TM sched and priority line where CIR queue is attached. */
} bcmolt_tm_queue_cfg_data;

/* Constants associated with bcmolt_tm_queue_cfg_data. */
#define BCMOLT_TM_QUEUE_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000003BULL
#define BCMOLT_TM_QUEUE_CFG_DATA_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED
#define BCMOLT_TM_QUEUE_CFG_DATA_CONTROL_STATE_DEFAULT BCMOLT_CONTROL_STATE_ENABLE

/** Transport message definition for "cfg" group of "tm_queue" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_tm_queue_key key; /**< Object key. */
    bcmolt_tm_queue_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_tm_queue_cfg;

/** Multi-object message definition for "cfg" group of "tm_queue" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_tm_queue_key key; /**< Object key (can include wildcards). */
    bcmolt_tm_queue_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_tm_queue_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_tm_queue_cfg *responses; /**< Responses to the last API call. */

    bcmolt_tm_queue_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_tm_queue_multi_cfg;

/** tm_sched: key */
typedef struct
{
    bcmolt_tm_sched_id id; /**< ID */
} bcmolt_tm_sched_key;

/** tm_sched: cfg */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_tm_sched_attachment_point attachment_point; /**< The output of the tm_sched object instance */
    bcmolt_tm_sched_type sched_type; /**< Scheduler type */
    uint8_t num_priorities; /**< Max number of strict priority scheduling elements.
    Note for SP_WFQ, max 9 priorities [0-8] will be allowed */
    bcmolt_tm_shaping rate; /**< Rate shaping parameters */
    bcmolt_config_state state; /**< Current state of object. (Not Configured or Active) */
    bcmolt_tm_sched_attachment_point cir_attachment_point; /**< TM sched and priority line where CIR queue can be attached. */
} bcmolt_tm_sched_cfg_data;

/* Constants associated with bcmolt_tm_sched_cfg_data. */
#define BCMOLT_TM_SCHED_CFG_DATA_PRESENCE_MASK_ALL 0x000000000000006FULL
#define BCMOLT_TM_SCHED_CFG_DATA_NUM_PRIORITIES_MAX 9
#define BCMOLT_TM_SCHED_CFG_DATA_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED

/** Transport message definition for "cfg" group of "tm_sched" object. */
typedef struct
{
    bcmolt_cfg hdr; /**< Transport header. */
    bcmolt_tm_sched_key key; /**< Object key. */
    bcmolt_tm_sched_cfg_data data; /**< All properties that must be set by the user. */
} bcmolt_tm_sched_cfg;

/** Multi-object message definition for "cfg" group of "tm_sched" object. */
typedef struct
{
    bcmolt_multi_cfg hdr; /**< Transport header. */
    bcmolt_tm_sched_key key; /**< Object key (can include wildcards). */
    bcmolt_tm_sched_cfg_data filter; /**< Only include responses that match these values. */
    bcmolt_tm_sched_cfg_data request; /**< Responses will include all present fields. */

    bcmos_bool more; /**< BCMOS_TRUE if not all responses were retreived by the last API call. */
    uint16_t num_responses; /**< Number of responses to the last API call. */
    bcmolt_tm_sched_cfg *responses; /**< Responses to the last API call. */

    bcmolt_tm_sched_key next_key; /**< Key iterator (do not set manually). */
} bcmolt_tm_sched_multi_cfg;



/** @} */

#endif
