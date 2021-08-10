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

#ifndef BCMOLT_API_MODEL_SUPPORTING_STRUCTS_H_
#define BCMOLT_API_MODEL_SUPPORTING_STRUCTS_H_

#include <bcmos_system.h>
#include <bcmolt_system_types.h>
#include "bcmolt_msg.h"
#include "bcmolt_api_model_supporting_enums.h"
#include "bcmolt_api_model_supporting_typedefs.h"

/** \addtogroup object_model
 * @{
 */

/** interface reference */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_interface_type intf_type; /**< interface type - user must configure type */
    bcmolt_interface_id intf_id; /**< interface id - user must configure an interface id */
    bcmolt_intf_opt intf_opt; /**< Interface Option Flags */
} bcmolt_intf_ref;

/* Constants associated with bcmolt_intf_ref. */
#define BCMOLT_INTF_REF_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_INTF_REF_INTF_TYPE_DEFAULT BCMOLT_INTERFACE_TYPE_UNASSIGNED
#define BCMOLT_INTF_REF_INTF_ID_DEFAULT (bcmolt_interface_id)255
#define BCMOLT_INTF_REF_INTF_OPT_DEFAULT (bcmolt_intf_opt)0U

/** access control fowarding action */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_access_control_fwd_action_type action; /**< action. */
    bcmolt_intf_ref redirect_intf_ref; /**< redirect interface. */
} bcmolt_access_control_fwd_action;

/* Constants associated with bcmolt_access_control_fwd_action. */
#define BCMOLT_ACCESS_CONTROL_FWD_ACTION_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Pkt header modifier associated with an ACL */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_action_control_pkt_modifiers pkt_modifier_bit_mask; /**< Packet header modifier bit mask */
    uint16_t o_vid; /**< used to push a New Outer Vlan TAg or modify a Vlan ID */
    uint16_t i_vid; /**< New Inner VID for Modify */
    uint8_t o_pbits; /**< Remark Outer PBits */
    uint8_t i_pbits; /**< Remark Inner PBits */
    uint8_t dscp; /**< Remark DSCP */
    uint8_t ttl; /**< Rewrite TTL value */
} bcmolt_access_control_pkt_modifier;

/* Constants associated with bcmolt_access_control_pkt_modifier. */
#define BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_PRESENCE_MASK_ALL 0x000000000000007FULL
#define BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_PKT_MODIFIER_BIT_MASK_DEFAULT (bcmolt_action_control_pkt_modifiers)0UL

/** action */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_action_cmd_id cmds_bitmask; /**< Commands bitmask. */
    uint16_t o_vid; /**< Outer vid. */
    uint8_t o_pbits; /**< Outer pbits. */
    uint16_t i_vid; /**< Inner vid. */
    uint8_t i_pbits; /**< Inner pbits. */
    bcmolt_action_tag_format tag_format; /**< vlan tags format. */
} bcmolt_action;

/* Constants associated with bcmolt_action. */
#define BCMOLT_ACTION_PRESENCE_MASK_ALL 0x000000000000003FULL
#define BCMOLT_ACTION_CMDS_BITMASK_DEFAULT (bcmolt_action_cmd_id)0UL
#define BCMOLT_ACTION_O_VID_MAX 4094U
#define BCMOLT_ACTION_O_PBITS_MAX 7
#define BCMOLT_ACTION_I_VID_MAX 4094U
#define BCMOLT_ACTION_I_PBITS_MAX 7
#define BCMOLT_ACTION_TAG_FORMAT_DEFAULT BCMOLT_ACTION_TAG_FORMAT_DOT_1_Q

/** Fixed-length binary string of 16 bytes */
typedef struct
{
    uint8_t arr[16]; /**< Binary string contents. */
} bcmolt_bin_str_16;

/** 128-bit AES key used for ONU authentication. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str_16 bytes; /**< Bytes that comprise the key. */
} bcmolt_aes_key;

/* Constants associated with bcmolt_aes_key. */
#define BCMOLT_AES_KEY_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_AES_KEY_BYTES_MAX_LENGTH 16
#define BCMOLT_AES_KEY_BYTES_LENGTH 16

/** Fixed-Length list: 2x aes_key */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_aes_key arr[2]; /**< Array. */
} bcmolt_arr_aes_key_2;

/** Fixed-Length list: 8x calibration_record */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_calibration_record arr[8]; /**< Array. */
} bcmolt_arr_calibration_record_8;

/** DS frequency offset */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_sign sign; /**< sign. */
    uint8_t value; /**< value. */
} bcmolt_ds_frequency_offset;

/* Constants associated with bcmolt_ds_frequency_offset. */
#define BCMOLT_DS_FREQUENCY_OFFSET_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Identifies the TWDM channel termination within a certain domain */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t administrative_label; /**< MSB 28 bit of the PON ID */
    uint8_t dwlch_id; /**< LSB 4 bits of the PON ID */
} bcmolt_pon_id;

/* Constants associated with bcmolt_pon_id. */
#define BCMOLT_PON_ID_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_PON_ID_ADMINISTRATIVE_LABEL_MIN 0UL
#define BCMOLT_PON_ID_ADMINISTRATIVE_LABEL_MAX 4294967280UL
#define BCMOLT_PON_ID_DWLCH_ID_MIN 0
#define BCMOLT_PON_ID_DWLCH_ID_MAX 7

/** Channel Profile */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t version; /**< Channel profile version */
    uint8_t channel_index; /**< Channel profile index */
    bcmolt_ds_frequency_offset ds_frequency_offset; /**< The difference between the actual OLT CT Tx frequency and the nominal central frequency for the given DWLCH ID, expressed in units of 0.1GHz */
    uint8_t channel_partition; /**< Channel partition */
    uint8_t uwlch_id; /**< The assigned upstream wavelength channel ID */
    uint32_t us_frequency; /**< The nominal central frequency of the upstream wavelength channel or a root frequency of the cyclic set of central frequencies forming an upstream wavelength channel, indicates the value in units of 0.1 GHz. */
    bcmolt_upstream_line_rate_capabilities us_rate; /**< US rate. */
    uint8_t default_onu_attenuation; /**< The default ONU attenuation level in steps of 3dB */
    uint8_t response_threshold; /**< Threshold represent the maximum number of Ploams the ONU can transmit at non-zero attenuation level while attempting to establish communication with OLT CT */
    bcmolt_link_type us_link_type; /**< US link type. */
    bcmos_bool is_valid; /**< is valid. */
    bcmolt_pon_id pon_id; /**< pon_id. */
} bcmolt_channel_profile;

/* Constants associated with bcmolt_channel_profile. */
#define BCMOLT_CHANNEL_PROFILE_PRESENCE_MASK_ALL 0x0000000000000FFFULL
#define BCMOLT_CHANNEL_PROFILE_VERSION_DEFAULT 0
#define BCMOLT_CHANNEL_PROFILE_VERSION_MIN 0
#define BCMOLT_CHANNEL_PROFILE_VERSION_MAX 15
#define BCMOLT_CHANNEL_PROFILE_CHANNEL_INDEX_DEFAULT 0
#define BCMOLT_CHANNEL_PROFILE_CHANNEL_INDEX_MIN 0
#define BCMOLT_CHANNEL_PROFILE_CHANNEL_INDEX_MAX 15
#define BCMOLT_CHANNEL_PROFILE_CHANNEL_PARTITION_DEFAULT 0
#define BCMOLT_CHANNEL_PROFILE_CHANNEL_PARTITION_MIN 0
#define BCMOLT_CHANNEL_PROFILE_CHANNEL_PARTITION_MAX 15
#define BCMOLT_CHANNEL_PROFILE_UWLCH_ID_MIN 0
#define BCMOLT_CHANNEL_PROFILE_UWLCH_ID_MAX 15
#define BCMOLT_CHANNEL_PROFILE_DEFAULT_ONU_ATTENUATION_DEFAULT 0
#define BCMOLT_CHANNEL_PROFILE_DEFAULT_ONU_ATTENUATION_MIN 0
#define BCMOLT_CHANNEL_PROFILE_DEFAULT_ONU_ATTENUATION_MAX 7
#define BCMOLT_CHANNEL_PROFILE_RESPONSE_THRESHOLD_DEFAULT 0
#define BCMOLT_CHANNEL_PROFILE_IS_VALID_DEFAULT BCMOS_TRUE

/** Fixed-Length list: 8x channel_profile */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_channel_profile arr[8]; /**< Array. */
} bcmolt_arr_channel_profile_8;

/** Fixed-Length list: 16x intf_ref */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_intf_ref arr[16]; /**< Array. */
} bcmolt_arr_intf_ref_16;

/** Fixed-Length list: 8x link_state */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_link_state arr[8]; /**< Array. */
} bcmolt_arr_link_state_8;

/** Fixed-Length list: 8x nni_id */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_nni_id arr[8]; /**< Array. */
} bcmolt_arr_nni_id_8;

/** policer reference structure */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_policer_reference_type type; /**< type. */
    uint16_t id; /**< id. */
} bcmolt_policer_ref;

/* Constants associated with bcmolt_policer_ref. */
#define BCMOLT_POLICER_REF_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_POLICER_REF_TYPE_DEFAULT BCMOLT_POLICER_REFERENCE_TYPE_POLICER_PROFILE
#define BCMOLT_POLICER_REF_ID_DEFAULT 65535U

/** Fixed-Length list: 4x policer_ref */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_policer_ref arr[4]; /**< Array. */
} bcmolt_arr_policer_ref_4;

/** Power consumption report per channel */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t ds_wavelength_channel_id; /**< Downstream wavelength channel ID */
    uint8_t us_wavelength_channel_id; /**< Upstream wavelength channel ID */
    uint16_t power_consumption; /**< Power consumption */
} bcmolt_power_consumption_channel_report;

/* Constants associated with bcmolt_power_consumption_channel_report. */
#define BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Fixed-Length list: 8x power_consumption_channel_report */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_power_consumption_channel_report arr[8]; /**< Array. */
} bcmolt_arr_power_consumption_channel_report_8;

/** Queue Reference */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_tm_sched_id sched_id; /**< Scheduler (tm_sched) ID */
    bcmolt_tm_queue_id queue_id; /**< Queue ID */
} bcmolt_tm_queue_ref;

/* Constants associated with bcmolt_tm_queue_ref. */
#define BCMOLT_TM_QUEUE_REF_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_TM_QUEUE_REF_SCHED_ID_DEFAULT (bcmolt_tm_sched_id)65535U
#define BCMOLT_TM_QUEUE_REF_QUEUE_ID_DEFAULT (bcmolt_tm_queue_id)65535U

/** Fixed-Length list: 8x tm_queue_ref */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_tm_queue_ref arr[8]; /**< Array. */
} bcmolt_arr_tm_queue_ref_8;

/** Fixed-Length list: 2x U16 */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    uint16_t arr[2]; /**< Array. */
} bcmolt_arr_u16_2;

/** Fixed-Length list: 4x U64 */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    uint64_t arr[4]; /**< Array. */
} bcmolt_arr_u64_4;

/** Fixed-Length list: 20x U8 */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    uint8_t arr[20]; /**< Array. */
} bcmolt_arr_u8_20;

/** Fixed-Length list: 8x U8 */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    uint8_t arr[8]; /**< Array. */
} bcmolt_arr_u8_8;

/** XGPON burst profile */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t profile_version; /**< profile version. */
    bcmolt_burst_profile_type type; /**< Type. */
    bcmos_bool is_fec_on; /**< is fec on. */
    uint8_t delimiter_size_in_bytes; /**< delimiter size in bytes. */
    uint32_t delimiter_pattern_high; /**< delimiter pattern high. */
    uint32_t delimiter_pattern_low; /**< delimiter pattern low. */
    uint8_t preamble_length_in_bytes; /**< preamble length in bytes. */
    uint8_t preamble_repeats_count; /**< preamble repeats count. */
    uint32_t preamble_pattern_high; /**< preamble pattern high. */
    uint32_t preamble_pattern_low; /**< preamble pattern low. */
    uint64_t pon_tag; /**< PON tag. */
    uint32_t num_of_guard_bytes; /**< number of guard bytes. */
    bcmos_bool is_profile_valid; /**< is profile valid. */
    uint32_t burst_overhead_size_in_words; /**< Burst overhead size in 4-byte words (word size is 4 bytes regardless of upstream data rate). */
} bcmolt_xgpon_burst_profile;

/* Constants associated with bcmolt_xgpon_burst_profile. */
#define BCMOLT_XGPON_BURST_PROFILE_PRESENCE_MASK_ALL 0x0000000000003FFFULL
#define BCMOLT_XGPON_BURST_PROFILE_PROFILE_VERSION_DEFAULT 0x0
#define BCMOLT_XGPON_BURST_PROFILE_TYPE_DEFAULT BCMOLT_BURST_PROFILE_TYPE_RANGING
#define BCMOLT_XGPON_BURST_PROFILE_IS_FEC_ON_DEFAULT BCMOS_FALSE
#define BCMOLT_XGPON_BURST_PROFILE_DELIMITER_SIZE_IN_BYTES_DEFAULT 0
#define BCMOLT_XGPON_BURST_PROFILE_DELIMITER_SIZE_IN_BYTES_MIN 0
#define BCMOLT_XGPON_BURST_PROFILE_DELIMITER_SIZE_IN_BYTES_MAX 8
#define BCMOLT_XGPON_BURST_PROFILE_DELIMITER_PATTERN_HIGH_DEFAULT 0x0UL
#define BCMOLT_XGPON_BURST_PROFILE_DELIMITER_PATTERN_LOW_DEFAULT 0x8UL
#define BCMOLT_XGPON_BURST_PROFILE_PREAMBLE_LENGTH_IN_BYTES_DEFAULT 8
#define BCMOLT_XGPON_BURST_PROFILE_PREAMBLE_LENGTH_IN_BYTES_MIN 1
#define BCMOLT_XGPON_BURST_PROFILE_PREAMBLE_LENGTH_IN_BYTES_MAX 8
#define BCMOLT_XGPON_BURST_PROFILE_PREAMBLE_REPEATS_COUNT_DEFAULT 0
#define BCMOLT_XGPON_BURST_PROFILE_PREAMBLE_REPEATS_COUNT_MIN 0
#define BCMOLT_XGPON_BURST_PROFILE_PREAMBLE_REPEATS_COUNT_MAX 255
#define BCMOLT_XGPON_BURST_PROFILE_PREAMBLE_PATTERN_HIGH_DEFAULT 0x0UL
#define BCMOLT_XGPON_BURST_PROFILE_PREAMBLE_PATTERN_LOW_DEFAULT 0x0UL
#define BCMOLT_XGPON_BURST_PROFILE_PON_TAG_DEFAULT 0ULL
#define BCMOLT_XGPON_BURST_PROFILE_NUM_OF_GUARD_BYTES_DEFAULT 0UL
#define BCMOLT_XGPON_BURST_PROFILE_IS_PROFILE_VALID_DEFAULT BCMOS_FALSE
#define BCMOLT_XGPON_BURST_PROFILE_BURST_OVERHEAD_SIZE_IN_WORDS_DEFAULT 0UL

/** Fixed-Length list: 4x xgpon_burst_profile */
typedef struct
{
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_xgpon_burst_profile arr[4]; /**< Array. */
} bcmolt_arr_xgpon_burst_profile_4;

/** Automatic ONU deactivation */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool los; /**< Auto deactivate ONU due to LOS */
    bcmos_bool onu_alarms; /**< Auto deactivate ONU due to ONU alarms */
    bcmos_bool tiwi; /**< Auto deactivate ONU due to TIWi alarm */
    bcmos_bool ack_timeout; /**< Auto deactivate ONU due to Ack timeout */
    bcmos_bool sfi; /**< Auto deactivate ONU due to SFi alarm */
    bcmos_bool loki; /**< Auto deactivate ONU due to Loki alarm */
} bcmolt_automatic_onu_deactivation;

/* Constants associated with bcmolt_automatic_onu_deactivation. */
#define BCMOLT_AUTOMATIC_ONU_DEACTIVATION_PRESENCE_MASK_ALL 0x000000000000003FULL

/** BER monitoring parameters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t us_ber_interval; /**< Interval in milliseconds for upstream BER monitoring (0 = disabled). */
    uint8_t sf_threshold; /**< Signal fail alarm is raised when BER raises to 10^-x, where x is this number. */
    uint8_t sd_threshold; /**< Signal degrade alarm is raised when BER raises to 10^-x, where x is this number. */
} bcmolt_ber_monitor_params;

/* Constants associated with bcmolt_ber_monitor_params. */
#define BCMOLT_BER_MONITOR_PARAMS_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_BER_MONITOR_PARAMS_US_BER_INTERVAL_DEFAULT 5000UL
#define BCMOLT_BER_MONITOR_PARAMS_US_BER_INTERVAL_MIN 0UL
#define BCMOLT_BER_MONITOR_PARAMS_US_BER_INTERVAL_MAX 60000UL
#define BCMOLT_BER_MONITOR_PARAMS_SF_THRESHOLD_DEFAULT 3
#define BCMOLT_BER_MONITOR_PARAMS_SF_THRESHOLD_MIN 3
#define BCMOLT_BER_MONITOR_PARAMS_SF_THRESHOLD_MAX 8
#define BCMOLT_BER_MONITOR_PARAMS_SD_THRESHOLD_DEFAULT 5
#define BCMOLT_BER_MONITOR_PARAMS_SD_THRESHOLD_MIN 4
#define BCMOLT_BER_MONITOR_PARAMS_SD_THRESHOLD_MAX 9

/** Variable-length binary string */
typedef struct
{
    uint32_t len; /**< Number of bytes in the binary string. */
    uint8_t *arr; /**< Binary string contents. */
} bcmolt_bin_str;

/** Fixed-length binary string of 10 bytes */
typedef struct
{
    uint8_t arr[10]; /**< Binary string contents. */
} bcmolt_bin_str_10;

/** Fixed-length binary string of 13 bytes */
typedef struct
{
    uint8_t arr[13]; /**< Binary string contents. */
} bcmolt_bin_str_13;

/** Fixed-length binary string of 36 bytes */
typedef struct
{
    uint8_t arr[36]; /**< Binary string contents. */
} bcmolt_bin_str_36;

/** Fixed-length binary string of 4 bytes */
typedef struct
{
    uint8_t arr[4]; /**< Binary string contents. */
} bcmolt_bin_str_4;

/** Fixed-length binary string of 40 bytes */
typedef struct
{
    uint8_t arr[40]; /**< Binary string contents. */
} bcmolt_bin_str_40;

/** Fixed-length binary string of 48 bytes */
typedef struct
{
    uint8_t arr[48]; /**< Binary string contents. */
} bcmolt_bin_str_48;

/** Fixed-length binary string of 8 bytes */
typedef struct
{
    uint8_t arr[8]; /**< Binary string contents. */
} bcmolt_bin_str_8;

/** CBR RT Allocation profile */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint16_t ma_7; /**< CBA maximum allocation size for frame gap 7 */
    uint16_t ma_3; /**< CBA maximum allocation size for frame gap 3 */
    uint16_t ma_1; /**< CBA maximum allocation size for frame gap 1 */
} bcmolt_cbr_rt_allocation_profile;

/* Constants associated with bcmolt_cbr_rt_allocation_profile. */
#define BCMOLT_CBR_RT_ALLOCATION_PROFILE_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_CBR_RT_ALLOCATION_PROFILE_MA_7_DEFAULT 64U
#define BCMOLT_CBR_RT_ALLOCATION_PROFILE_MA_3_DEFAULT 256U
#define BCMOLT_CBR_RT_ALLOCATION_PROFILE_MA_1_DEFAULT 512U

/** udp or tcp port range */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint16_t min; /**< port range min value. */
    uint16_t max; /**< port range max value. */
} bcmolt_layer_4_port_range;

/* Constants associated with bcmolt_layer_4_port_range. */
#define BCMOLT_LAYER_4_PORT_RANGE_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** classifier with IPv6 parameters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t classifier_ip_v_6_bitmap; /**< classifier ipv6 bitmap */
    bcmos_bool match_mld_pkts; /**< whether to match MLD packets or not */
    bcmos_ipv6_address dst_ip_v_6; /**< destination IPv6 address to match for access control */
    bcmos_ipv6_address dst_ip_v_6_mask; /**< mask to match packet for access control  (not subnet mask) */
    bcmos_ipv6_address src_ip_v_6; /**< source IPv6 address to match for access control */
    bcmos_ipv6_address src_ip_v_6_mask; /**< destination IPv6 address mask to match for access control (not subnet mask) */
    bcmos_bool is_one_ext_hdr; /**< If True, Protocol field is in First Ext Hdr; otherwise it is in Next Hdr of IPv6 pkt */
} bcmolt_classifier_ip_v_6;

/* Constants associated with bcmolt_classifier_ip_v_6. */
#define BCMOLT_CLASSIFIER_IP_V_6_PRESENCE_MASK_ALL 0x000000000000007FULL
#define BCMOLT_CLASSIFIER_IP_V_6_CLASSIFIER_IP_V_6_BITMAP_DEFAULT 0ULL
#define BCMOLT_CLASSIFIER_IP_V_6_MATCH_MLD_PKTS_DEFAULT BCMOS_FALSE
#define BCMOLT_CLASSIFIER_IP_V_6_IS_ONE_EXT_HDR_DEFAULT BCMOS_FALSE

/** classifier */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t classifier_bitmap; /**< Bitmap of classifier fields which are in use. */
    uint16_t o_vid; /**< Outer VID of the packet to be classified */
    uint16_t i_vid; /**< Inner VID of the packet to be classified */
    uint8_t o_pbits; /**< Outer PBITS of the packet to be classified */
    uint8_t i_pbits; /**< Inner PBITS of the packet to be classified */
    uint16_t ether_type; /**< Ethertype of the packet to be classified */
    bcmos_mac_address dst_mac; /**< Destination MAC address of the packet to be classified */
    bcmos_mac_address src_mac; /**< Source MAC address of the packet to be classified */
    uint8_t ip_proto; /**< IP protocol of the packet to be classified */
    bcmos_ipv4_address dst_ip; /**< Destination IP address of the packet to be classified */
    bcmos_ipv4_address dst_ip_mask; /**< Destination IP address bitmask */
    uint16_t dst_port; /**< Destination tcp or udp port of the packet to be classified */
    bcmolt_layer_4_port_range dst_port_range; /**< Destination tcp or udp port range */
    bcmos_ipv4_address src_ip; /**< Source IP address of the packet to be classified */
    bcmos_ipv4_address src_ip_mask; /**< Source IP address bitmask */
    uint16_t src_port; /**< Source tcp or udp port of the packet to be classified */
    bcmolt_layer_4_port_range src_port_range; /**< Source tcp or udp port range */
    bcmolt_pkt_tag_type pkt_tag_type; /**< The tag type of the ingress packets */
    bcmolt_classifier_ip_v_6 ip_v_6; /**< IPv6 classification parameters for access control */
    uint16_t i2_vid; /**< Second Inner vid of a 3 tags packet */
} bcmolt_classifier;

/* Constants associated with bcmolt_classifier. */
#define BCMOLT_CLASSIFIER_PRESENCE_MASK_ALL 0x00000000000FFFFFULL
#define BCMOLT_CLASSIFIER_CLASSIFIER_BITMAP_DEFAULT 0ULL
#define BCMOLT_CLASSIFIER_O_VID_MAX 4094U
#define BCMOLT_CLASSIFIER_I_VID_MAX 4094U
#define BCMOLT_CLASSIFIER_O_PBITS_MAX 7
#define BCMOLT_CLASSIFIER_I_PBITS_MAX 7
#define BCMOLT_CLASSIFIER_I2_VID_MAX 4094U

/** Results of the DDR test */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_ddr_test_status status; /**< Outcome of the DDR test */
    union
    {
        struct
        {
            bcmolt_presence_mask presence_mask;
        } def;
        struct
        {
            bcmolt_presence_mask presence_mask;
            bcmolt_ddr_test_result cpu_result; /**< CPU Result. */
            bcmolt_ddr_test_result ras_0_result; /**< RAS 0 Result. */
            bcmolt_ddr_test_result ras_1_result; /**< RAS 1 Result. */
        } completed;
        struct
        {
            bcmolt_presence_mask presence_mask;
            bcmolt_host_connection_fail_reason reason; /**< Connection fail reason. */
        } connection_failed;
    } u;
} bcmolt_ddr_test_completed;

/* Constants associated with bcmolt_ddr_test_completed. */
#define BCMOLT_DDR_TEST_COMPLETED_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_DDR_TEST_COMPLETED_DEFAULT_PRESENCE_MASK_ALL 0x0000000000000000ULL
#define BCMOLT_DDR_TEST_COMPLETED_COMPLETED_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_DDR_TEST_COMPLETED_CONNECTION_FAILED_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** Debug parameters for device configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool use_prev_pon_serdes_firmware; /**< This is a fallback option if there are issues with the new firmware */
    bcmos_bool use_prev_nni_serdes_firmware; /**< This is a fallback option if there are issues with the new firmware */
} bcmolt_debug_device_cfg;

/* Constants associated with bcmolt_debug_device_cfg. */
#define BCMOLT_DEBUG_DEVICE_CFG_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_DEBUG_DEVICE_CFG_USE_PREV_PON_SERDES_FIRMWARE_DEFAULT BCMOS_FALSE
#define BCMOLT_DEBUG_DEVICE_CFG_USE_PREV_NNI_SERDES_FIRMWARE_DEFAULT BCMOS_FALSE

/** needed only for maple . */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_control_state untagged_flow; /**< If enabled, this GEM port will expect upstream traffic to be untagged and downstream traffic to use a custom VLAN tag. */
    bcmolt_vlan_id untagged_vid; /**< The VLAN ID to use when adding MAC table entries for untagged traffic. */
} bcmolt_debug_flow_config;

/* Constants associated with bcmolt_debug_flow_config. */
#define BCMOLT_DEBUG_FLOW_CONFIG_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_DEBUG_FLOW_CONFIG_UNTAGGED_FLOW_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_DEBUG_FLOW_CONFIG_UNTAGGED_VID_MIN (bcmolt_vlan_id)0U
#define BCMOLT_DEBUG_FLOW_CONFIG_UNTAGGED_VID_MAX (bcmolt_vlan_id)4095U

/** A reference to a tm_sched object instance */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_tm_sched_id id; /**< Parent scheduler id */
} bcmolt_tm_sched_ref;

/* Constants associated with bcmolt_tm_sched_ref. */
#define BCMOLT_TM_SCHED_REF_PRESENCE_MASK_ALL 0x0000000000000002ULL
#define BCMOLT_TM_SCHED_REF_ID_DEFAULT (bcmolt_tm_sched_id)65535U

/** egress qos */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_egress_qos_type type; /**< egress qos type. */
    bcmolt_tm_sched_ref tm_sched; /**< TM scheduler. */
    union
    {
        struct
        {
            bcmolt_presence_mask presence_mask;
            bcmolt_tm_queue_id queue_id; /**< queue_id for tm_queue key */
        } fixed_queue;
        struct
        {
            bcmolt_presence_mask presence_mask;
            uint8_t tc_id; /**< tc_id */
            uint16_t tc_to_queue_id; /**< tc_to_queue object id */
        } tc_to_queue;
        struct
        {
            bcmolt_presence_mask presence_mask;
            uint16_t pbit_to_tc_id; /**< pbit_to_tc object id */
            uint16_t tc_to_queue_id; /**< tc_to_queue object id */
        } pbit_to_tc;
        struct
        {
            bcmolt_presence_mask presence_mask;
            bcmolt_tm_qmp_id tm_qmp_id; /**< tm_qmp_id */
            bcmolt_tm_queue_set_id tm_q_set_id; /**< tm_queue_set_id */
        } priority_to_queue;
        struct
        {
            bcmolt_presence_mask presence_mask;
        } none;
    } u;
} bcmolt_egress_qos;

/* Constants associated with bcmolt_egress_qos. */
#define BCMOLT_EGRESS_QOS_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_EGRESS_QOS_TYPE_DEFAULT BCMOLT_EGRESS_QOS_TYPE_NONE
#define BCMOLT_EGRESS_QOS_FIXED_QUEUE_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_EGRESS_QOS_FIXED_QUEUE_QUEUE_ID_DEFAULT (bcmolt_tm_queue_id)65535U
#define BCMOLT_EGRESS_QOS_TC_TO_QUEUE_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_EGRESS_QOS_TC_TO_QUEUE_TC_ID_MIN 0
#define BCMOLT_EGRESS_QOS_TC_TO_QUEUE_TC_ID_MAX 7
#define BCMOLT_EGRESS_QOS_PBIT_TO_TC_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_TM_QMP_ID_DEFAULT (bcmolt_tm_qmp_id)15
#define BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_TM_Q_SET_ID_DEFAULT (bcmolt_tm_queue_set_id)32768U
#define BCMOLT_EGRESS_QOS_NONE_PRESENCE_MASK_ALL 0x0000000000000000ULL

/** ASCII string with max length 64 */
typedef struct
{
    char str[64]; /**< String. */
} bcmolt_str_64;

/** Embedded image entry */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_device_image_type image_type; /**< Type of the embedded file image. */
    uint32_t image_size; /**< Size of the embedded file image.  Unit is bytes. */
    uint32_t crc32; /**< CRC 32 checksum of entire file image data. */
    bcmolt_embedded_image_transfer_status status; /**< Image transfer status. */
    bcmolt_str_64 image_name; /**< Name of the file image.  Null-terminated string.  This is required for the DPoE ONU only.  DPoE requires the write request OAM contains the name of the file. */
} bcmolt_embedded_image_entry;

/* Constants associated with bcmolt_embedded_image_entry. */
#define BCMOLT_EMBEDDED_IMAGE_ENTRY_PRESENCE_MASK_ALL 0x000000000000001FULL

/** Variable-length list of embedded_image_entry */
typedef struct
{
    uint8_t len; /**< List length. */
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_embedded_image_entry *arr; /**< List contents. */
} bcmolt_embedded_image_entry_list_u8_max_4;

/** Holds the ERPS intf_ref and port_type */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_interface_id intf_id; /**< intf_id. */
    bcmolt_interface_type intf_type; /**< intf_type. */
    bcmolt_erps_port port_type; /**< port_type. */
    bcmolt_intf_opt intf_opt; /**< intf_opt. */
    uint8_t sub_port_idx; /**< sub_port_index. */
} bcmolt_erps_intf_ref;

/* Constants associated with bcmolt_erps_intf_ref. */
#define BCMOLT_ERPS_INTF_REF_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_ERPS_INTF_REF_INTF_ID_DEFAULT (bcmolt_interface_id)255
#define BCMOLT_ERPS_INTF_REF_INTF_TYPE_DEFAULT BCMOLT_INTERFACE_TYPE_UNASSIGNED
#define BCMOLT_ERPS_INTF_REF_SUB_PORT_IDX_DEFAULT 255

/** Extended DBA priority adjustment */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_control_state control; /**< Enable/disable Extended DBA priority adjustment mechanism */
    bcmolt_arr_u8_20 slots; /**< Slots for manually configuring the identity of the promoted priority in each cycle out of a 20 cycles period */
} bcmolt_extended_dba_priority_adjustment;

/* Constants associated with bcmolt_extended_dba_priority_adjustment. */
#define BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_SLOTS_LENGTH 20

/** ASCII string with max length 32 */
typedef struct
{
    char str[32]; /**< String. */
} bcmolt_str_32;

/** Firmware SW Version */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t major; /**< Major. */
    uint8_t minor; /**< Minor. */
    uint8_t revision; /**< Revision. */
    uint32_t model; /**< Model. */
    bcmolt_str_32 build_time; /**< Firmware SW build time */
} bcmolt_firmware_sw_version;

/* Constants associated with bcmolt_firmware_sw_version. */
#define BCMOLT_FIRMWARE_SW_VERSION_PRESENCE_MASK_ALL 0x000000000000001FULL

/** flow interface reference */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_flow_interface_type intf_type; /**< flow interface type */
    bcmolt_interface_id intf_id; /**< flow interface id */
} bcmolt_flow_intf_ref;

/* Constants associated with bcmolt_flow_intf_ref. */
#define BCMOLT_FLOW_INTF_REF_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_FLOW_INTF_REF_INTF_TYPE_DEFAULT BCMOLT_FLOW_INTERFACE_TYPE_UNASSIGNED
#define BCMOLT_FLOW_INTF_REF_INTF_ID_DEFAULT (bcmolt_interface_id)255

/** GEM port configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_gem_port_direction direction; /**< GEM port direction */
    bcmolt_gem_port_type type; /**< GEM port type */
} bcmolt_gem_port_configuration;

/* Constants associated with bcmolt_gem_port_configuration. */
#define BCMOLT_GEM_PORT_CONFIGURATION_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Variable-length list of gem_port_id */
typedef struct
{
    uint8_t len; /**< List length. */
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_gem_port_id *arr; /**< List contents. */
} bcmolt_gem_port_id_list_u8_max_16;

/** GPON ONU alarm status */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status losi; /**< Loss of signal. */
    bcmolt_status lofi; /**< Loss of frame. */
    bcmolt_status loami; /**< Loss of PLOAM. */
    bcmolt_status dgi; /**< Dying Gasp. */
    bcmolt_status tiwi; /**< Transmission interference Alarm. */
    bcmolt_status dowi; /**< Drift of Window. */
    bcmolt_status sufi; /**< Start UP Failure. */
    bcmolt_status sfi; /**< Signal Fail. */
    bcmolt_status sdi; /**< Signal Degraded. */
    bcmolt_status dfi; /**< Deactivation Failure. */
    bcmolt_status loai; /**< Loss of ack. */
    bcmolt_status loki; /**< loss of key. */
} bcmolt_gpon_onu_alarm_state;

/* Constants associated with bcmolt_gpon_onu_alarm_state. */
#define BCMOLT_GPON_ONU_ALARM_STATE_PRESENCE_MASK_ALL 0x0000000000000FFFULL
#define BCMOLT_GPON_ONU_ALARM_STATE_LOSI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_LOFI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_LOAMI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_DGI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_TIWI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_DOWI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_SUFI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_SFI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_SDI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_DFI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_LOAI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_GPON_ONU_ALARM_STATE_LOKI_DEFAULT BCMOLT_STATUS_OFF

/** GPON ONU alarms */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status losi; /**< LOSi. */
    bcmolt_status lofi; /**< LOFi. */
    bcmolt_status loami; /**< LOAMi. */
} bcmolt_gpon_onu_alarms;

/* Constants associated with bcmolt_gpon_onu_alarms. */
#define BCMOLT_GPON_ONU_ALARMS_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** GPON ONU alarms thresholds */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t losi; /**< Threshold for asserting LOSi alarm */
    uint8_t lofi; /**< Threshold for asserting LOFi alarm */
    uint8_t loami; /**< Threshold for asserting LOAMi alarm */
} bcmolt_gpon_onu_alarms_thresholds;

/* Constants associated with bcmolt_gpon_onu_alarms_thresholds. */
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_LOSI_DEFAULT 4
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_LOSI_MIN 1
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_LOSI_MAX 15
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_LOFI_DEFAULT 4
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_LOFI_MIN 1
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_LOFI_MAX 15
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_LOAMI_DEFAULT 3
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_LOAMI_MIN 1
#define BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_LOAMI_MAX 15

/** GPON ONU Parameters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str_10 password; /**< ONU password */
    bcmos_bool us_fec; /**< Enable\Disable US FEC for ONU */
    bcmolt_gem_port_id omci_port_id; /**< OMCI port ID */
    bcmolt_ber_interval ds_ber_reporting_interval; /**< DS BER reporting interval */
    bcmolt_gpon_onu_alarm_state alarm_state; /**< State of all ONU alarms.  This is normally read-only and can only be written when the PON is in active-standby mode to keep the ONU in sync. */
} bcmolt_gpon_onu_params;

/* Constants associated with bcmolt_gpon_onu_params. */
#define BCMOLT_GPON_ONU_PARAMS_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_GPON_ONU_PARAMS_PASSWORD_MAX_LENGTH 10
#define BCMOLT_GPON_ONU_PARAMS_PASSWORD_LENGTH 10
#define BCMOLT_GPON_ONU_PARAMS_US_FEC_DEFAULT BCMOS_FALSE
#define BCMOLT_GPON_ONU_PARAMS_OMCI_PORT_ID_DEFAULT (bcmolt_gem_port_id)65535UL
#define BCMOLT_GPON_ONU_PARAMS_DS_BER_REPORTING_INTERVAL_DEFAULT (bcmolt_ber_interval)0UL
#define BCMOLT_GPON_ONU_PARAMS_DS_BER_REPORTING_INTERVAL_MAX (bcmolt_ber_interval)536870911UL

/** PON Power Level */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t pls_maximum_allocation_size; /**< Max allocation size for PLS transmission */
    uint8_t mode; /**< ONU default power level mode */
} bcmolt_pon_power_level;

/* Constants associated with bcmolt_pon_power_level. */
#define BCMOLT_PON_POWER_LEVEL_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_PON_POWER_LEVEL_PLS_MAXIMUM_ALLOCATION_SIZE_DEFAULT 120UL
#define BCMOLT_PON_POWER_LEVEL_MODE_DEFAULT 0

/** GPON Interface Parameters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_gpon_onu_alarms_thresholds onu_alarms_thresholds; /**< ONU alarms thresholds configuration */
    uint32_t preassigned_equalization_delay; /**< ONU pre-assigned equalization delay */
    bcmolt_pon_power_level power_level; /**< ONU power level configuration */
    bcmolt_control_state bip32_indication_control; /**< Option to disable the bip32 indication when the value is zero */
    bcmolt_ber_interval ds_ber_reporting_interval; /**< DS BER reporting interval */
    uint8_t sr_reporting_block_size; /**< ONU status report block size in bytes */
} bcmolt_gpon_pon_params;

/* Constants associated with bcmolt_gpon_pon_params. */
#define BCMOLT_GPON_PON_PARAMS_PRESENCE_MASK_ALL 0x000000000000003FULL
#define BCMOLT_GPON_PON_PARAMS_PREASSIGNED_EQUALIZATION_DELAY_DEFAULT 0UL
#define BCMOLT_GPON_PON_PARAMS_PREASSIGNED_EQUALIZATION_DELAY_MIN 0UL
#define BCMOLT_GPON_PON_PARAMS_PREASSIGNED_EQUALIZATION_DELAY_MAX 16776960UL
#define BCMOLT_GPON_PON_PARAMS_BIP32_INDICATION_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_ENABLE
#define BCMOLT_GPON_PON_PARAMS_DS_BER_REPORTING_INTERVAL_DEFAULT (bcmolt_ber_interval)5000UL
#define BCMOLT_GPON_PON_PARAMS_DS_BER_REPORTING_INTERVAL_MAX (bcmolt_ber_interval)536870911UL
#define BCMOLT_GPON_PON_PARAMS_SR_REPORTING_BLOCK_SIZE_DEFAULT 48

/** gpon trx */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_trx_type transceiver_type; /**< transceiver type. */
} bcmolt_gpon_trx;

/* Constants associated with bcmolt_gpon_trx. */
#define BCMOLT_GPON_TRX_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_GPON_TRX_TRANSCEIVER_TYPE_DEFAULT BCMOLT_TRX_TYPE_LTE_3680_M

/** Group Member Info */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_intf_ref intf; /**< Egress interface for this member */
    bcmolt_service_port_id svc_port_id; /**< The multicast "GEM" for this member */
    bcmolt_egress_qos egress_qos; /**< Egress queue for this member */
} bcmolt_group_member_info;

/* Constants associated with bcmolt_group_member_info. */
#define BCMOLT_GROUP_MEMBER_INFO_PRESENCE_MASK_ALL 0x000000000000000BULL

/** Variable-length list of group_member_info */
typedef struct
{
    uint8_t len; /**< List length. */
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_group_member_info *arr; /**< List contents. */
} bcmolt_group_member_info_list_u8;

/** group_members_update_command used to add/remove/set members of a group */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_members_update_command command; /**< command. */
    bcmolt_group_member_info_list_u8 members; /**< members. */
} bcmolt_group_members_update_command;

/* Constants associated with bcmolt_group_members_update_command. */
#define BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Host SW Version */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t major; /**< Major. */
    uint8_t minor; /**< Minor. */
    uint8_t revision; /**< Revision. */
    uint16_t model; /**< Model Revision. */
    bcmolt_str_64 build_time; /**< Host SW build time. */
} bcmolt_host_sw_version;

/* Constants associated with bcmolt_host_sw_version. */
#define BCMOLT_HOST_SW_VERSION_PRESENCE_MASK_ALL 0x0000000000000037ULL

/** HW PON ID */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t pon_id_1; /**< LSB 32 bits of PON ID. */
    uint32_t pon_id_2; /**< MSB 19 bits of PON ID. */
} bcmolt_hw_pon_id;

/* Constants associated with bcmolt_hw_pon_id. */
#define BCMOLT_HW_PON_ID_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_HW_PON_ID_PON_ID_1_DEFAULT 0UL
#define BCMOLT_HW_PON_ID_PON_ID_2_DEFAULT 0UL

/** ASCII string with max length 256 */
typedef struct
{
    char str[256]; /**< String. */
} bcmolt_str_256;

/** IEEE 802.1 AS ToD */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_str_256 tod_format; /**< The format of the 802.1AS ToD string.
    
    All ASCII characters will be matched literally except:
    
    - %d - Matches the day of the month as a decimal number (1-31). Leading zeroes optional.
    - %H - Matches the hour as a decimal number using a 24-hour clock (0-23). Leading zeroes optional, but cannot exceed two characters.
    - %m - Matches the month as a decimal number (1-12). Leading zeroes optional.
    - %M - Matches the minute as a decimal number (0-59). Leading zeroes optional, but cannot exceed two characters.
    - %S - Matches the second as a decimal number (0-59). Leading zeroes optional, but cannot exceed two characters.
    - %Y - Matches the year as a decimal number using the Gregorian Calendar. Leading zeroes optional.
    - %% - Matches a literal '%'.
    
    Maximum 256 characters.
    
    Example:
    If the date 2011-12-21 15:23:52 is encoded as "$UTC,152352,21,12,2011*42", then the ToD format string would be "$UTC,%H%M%S,%d,%m,%Y". */
    uint32_t clock_transport_sample_delay; /**< The time (in TQ) that it takes from when a pulse is generated at the external source to when we sample it. */
    uint32_t tod_read_delay_ms; /**< The delay (in ms) to wait after receving a pulse before reading the ToD. */
} bcmolt_ieee_8021_as_tod;

/* Constants associated with bcmolt_ieee_8021_as_tod. */
#define BCMOLT_IEEE_8021_AS_TOD_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_IEEE_8021_AS_TOD_CLOCK_TRANSPORT_SAMPLE_DELAY_DEFAULT 0UL
#define BCMOLT_IEEE_8021_AS_TOD_TOD_READ_DELAY_MS_DEFAULT 0UL
#define BCMOLT_IEEE_8021_AS_TOD_TOD_READ_DELAY_MS_MIN 0UL
#define BCMOLT_IEEE_8021_AS_TOD_TOD_READ_DELAY_MS_MAX 1000UL

/** Configuration for the inband management channel for an NNI port. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_control_state control; /**< Whether or not to enable an inband management channel on this port. */
    bcmos_ipv4_address ip_address; /**< The IP Address of this port. */
    uint16_t udp_port; /**< The UDP port number of this port. */
    bcmos_ipv4_address net_mask; /**< The netmask for this port. */
    bcmos_ipv4_address gw_address; /**< The gateway address for this port. */
    uint32_t vlan_tag; /**< VLAN tag of inband management traffic (including TPID). */
} bcmolt_inband_config_data;

/* Constants associated with bcmolt_inband_config_data. */
#define BCMOLT_INBAND_CONFIG_DATA_PRESENCE_MASK_ALL 0x000000000000003FULL
#define BCMOLT_INBAND_CONFIG_DATA_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_INBAND_CONFIG_DATA_VLAN_TAG_DEFAULT 0x81000001UL

/** Data need to connect via inband. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_ipv4_address device_ip_address; /**< The IP Address of the device, this parameter is mandatory. */
    uint16_t device_udp_port; /**< The UDP port of the Device, this parameter is mandatory. */
} bcmolt_inband_conn_data;

/* Constants associated with bcmolt_inband_conn_data. */
#define BCMOLT_INBAND_CONN_DATA_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Rate limiting / shaping for the indication channel. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool enabled; /**< Whether or not the device will limit the rate of indications sent to the host. */
    uint32_t max_rate; /**< Maximum number of indications per second to be generated by the device. */
    uint32_t max_burst; /**< Maximum number of indications that are allowed to be sent back-to-back. */
} bcmolt_indication_shaping;

/* Constants associated with bcmolt_indication_shaping. */
#define BCMOLT_INDICATION_SHAPING_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_INDICATION_SHAPING_ENABLED_DEFAULT BCMOS_FALSE
#define BCMOLT_INDICATION_SHAPING_MAX_RATE_DEFAULT 1000UL
#define BCMOLT_INDICATION_SHAPING_MAX_RATE_MIN 1UL
#define BCMOLT_INDICATION_SHAPING_MAX_RATE_MAX 10000UL
#define BCMOLT_INDICATION_SHAPING_MAX_BURST_DEFAULT 100UL
#define BCMOLT_INDICATION_SHAPING_MAX_BURST_MIN 1UL
#define BCMOLT_INDICATION_SHAPING_MAX_BURST_MAX 10000UL

/** INNI configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_inni_mode mode; /**< INNI mode */
    bcmolt_inni_mux mux; /**< INNI multiplexing */
    bcmolt_control_state cl73_an; /**< CL73 AN. */
    bcmolt_control_state link_training; /**< Link Training. */
    bcmolt_inni_fec_modes inni_fec; /**< The FEC mode desired for this INNI port.
    1.  None - no FEC
    2.  FC FEC - FEC as defined in IEEE 802.3 Clause 74
    3.  RS FEC - FEC as defined in IEEE 802.3 Clause 91 (10G) and Clause 108 (25G).
    4.  Auto negotiation - allow the link partnets to auto negotiate the FEC mode. */
    bcmolt_inni_lanes available_lanes; /**< The lane protection scheme use with INNI redundancy.   The options are 1.) None,  2.) All Lanes, and 3.) Even Lanes only. */
    bcmolt_gpio_pin ps_gpio; /**< GPIO assigned to drive active/standby status when the Internal NNI GPIO protection is enabled. */
    bcmolt_gpio_polarity gpio_polarity; /**< Polarity of the GPIO pin.
    
    active_low asserts that the GPIO active (value 0) should drive the primary internal NNI active.
    
    active_high asserts that the GPIO active (value 1) should drive the primary internal NNI active. */
} bcmolt_inni_config;

/* Constants associated with bcmolt_inni_config. */
#define BCMOLT_INNI_CONFIG_PRESENCE_MASK_ALL 0x00000000000000FFULL
#define BCMOLT_INNI_CONFIG_CL73_AN_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_INNI_CONFIG_LINK_TRAINING_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_INNI_CONFIG_INNI_FEC_DEFAULT BCMOLT_INNI_FEC_MODES_NONE
#define BCMOLT_INNI_CONFIG_AVAILABLE_LANES_DEFAULT BCMOLT_INNI_LANES_ALL
#define BCMOLT_INNI_CONFIG_PS_GPIO_DEFAULT BCMOLT_GPIO_PIN_UNCONFIGURED
#define BCMOLT_INNI_CONFIG_GPIO_POLARITY_DEFAULT BCMOLT_GPIO_POLARITY_ACTIVE_LOW

/** Variable-length list of intf_ref */
typedef struct
{
    uint8_t len; /**< List length. */
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_intf_ref *arr; /**< List contents. */
} bcmolt_intf_ref_list_u8;

/** serial number */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_bin_str_4 vendor_id; /**< vendor id. */
    bcmolt_bin_str_4 vendor_specific; /**< vendor specific. */
} bcmolt_serial_number;

/* Constants associated with bcmolt_serial_number. */
#define BCMOLT_SERIAL_NUMBER_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_SERIAL_NUMBER_VENDOR_ID_MAX_LENGTH 4
#define BCMOLT_SERIAL_NUMBER_VENDOR_ID_LENGTH 4
#define BCMOLT_SERIAL_NUMBER_VENDOR_SPECIFIC_MAX_LENGTH 4
#define BCMOLT_SERIAL_NUMBER_VENDOR_SPECIFIC_LENGTH 4

/** ITUPON ONU AES KEY */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_aes_key encryption_key; /**< encryption key. */
    uint8_t key_index; /**< Key index. 0 for GPON */
} bcmolt_itupon_onu_aes_key;

/* Constants associated with bcmolt_itupon_onu_aes_key. */
#define BCMOLT_ITUPON_ONU_AES_KEY_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** XGPON ONU alarm status */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status losi; /**< Loss of signal. */
    bcmolt_status lobi; /**< Loss of burst. */
    bcmolt_status lopci; /**< Loss of PLOAM channel. */
    bcmolt_status lopci_mic_error; /**< Mic error on ploam channel. */
    bcmolt_status looci; /**< Loss of OMCI channel. */
    bcmolt_status tiwi; /**< Transmission interference Alarm. */
    bcmolt_status dowi; /**< Drift of Window. */
    bcmolt_status sufi; /**< Start UP Failure. */
    bcmolt_status sfi; /**< Signal Fail. */
    bcmolt_status sdi; /**< Signal Degraded. */
    bcmolt_status dfi; /**< Deactivation Failure. */
    bcmolt_status dgi; /**< Dying gasp. */
    bcmolt_status pqsi; /**< Ploam queue status. */
    bcmolt_status loai; /**< Loss of ack. */
    bcmolt_status loki; /**< loss of key. */
} bcmolt_xgpon_onu_alarm_state;

/* Constants associated with bcmolt_xgpon_onu_alarm_state. */
#define BCMOLT_XGPON_ONU_ALARM_STATE_PRESENCE_MASK_ALL 0x0000000000007FFFULL
#define BCMOLT_XGPON_ONU_ALARM_STATE_LOSI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_LOBI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_LOPCI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_LOPCI_MIC_ERROR_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_LOOCI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_TIWI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_DOWI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_SUFI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_SFI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_SDI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_DFI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_DGI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_PQSI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_LOAI_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_XGPON_ONU_ALARM_STATE_LOKI_DEFAULT BCMOLT_STATUS_OFF

/** ngpon2 ONU params */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_arr_calibration_record_8 calibration_record; /**< Calibration record. */
    bcmolt_upstream_line_rate_capabilities us_line_rate; /**< US line rate. */
    uint8_t tuning_granularity; /**< The tuning granularity of the ONU transmitted expressed in units of 1GHz. Value of 0 indicates that the ONU does not support fine tuning/dithering */
    uint8_t step_tuning_time; /**< The value of the tuning time for a single granularity step, expressed in units of PHY frames. */
    uint8_t power_levelling_capabilities; /**< Power levelling capabilities. */
} bcmolt_ngpon2_onu_params;

/* Constants associated with bcmolt_ngpon2_onu_params. */
#define BCMOLT_NGPON2_ONU_PARAMS_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_NGPON2_ONU_PARAMS_CALIBRATION_RECORD_LENGTH 8

/** XGPON ONU registration keys */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_aes_key ploam_ik; /**< ploam ik. */
    bcmolt_aes_key omci_ik; /**< omci ik. */
    bcmolt_aes_key omci_k1; /**< omci k1. */
    bcmolt_aes_key omci_k2; /**< omci k2. */
    bcmolt_aes_key kek; /**< kek. */
} bcmolt_xgpon_onu_registration_keys;

/* Constants associated with bcmolt_xgpon_onu_registration_keys. */
#define BCMOLT_XGPON_ONU_REGISTRATION_KEYS_PRESENCE_MASK_ALL 0x000000000000001FULL

/** request registration status */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_control_state request_registration_state; /**< request registration state. */
    bcmos_bool sma_flag; /**< is request registration is part of sma process */
} bcmolt_request_registration_status;

/* Constants associated with bcmolt_request_registration_status. */
#define BCMOLT_REQUEST_REGISTRATION_STATUS_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_REQUEST_REGISTRATION_STATUS_REQUEST_REGISTRATION_STATE_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_REQUEST_REGISTRATION_STATUS_SMA_FLAG_DEFAULT BCMOS_FALSE

/** XGPON, NGPON2, XGS-PON ONU Parameters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_xgpon_onu_alarm_state alarm_state; /**< State of all ONU alarms.  This is normally read-only and can only be written when the PON is in active-standby mode to keep the ONU in sync. */
    bcmolt_bin_str_36 registration_id; /**< ONU registration ID */
    bcmolt_ngpon2_onu_params ngpon2; /**< NGPON2  parameters */
    bcmolt_xgpon_onu_registration_keys registration_encryption_keys; /**< AES encryption keys learned during ONU registration.  This is normally read-only and can only be written when the PON is in active-standby mode to keep the ONU in sync. */
    bcmolt_request_registration_status request_registration_status; /**< This value indicate that the onu is in the middle of request registration process */
    bcmolt_burst_profile_index ranging_burst_profile; /**< Burst profile index for ranging allocations */
    bcmolt_burst_profile_index data_burst_profile; /**< Burst profile index for data allocations */
} bcmolt_xgpon_onu_params;

/* Constants associated with bcmolt_xgpon_onu_params. */
#define BCMOLT_XGPON_ONU_PARAMS_PRESENCE_MASK_ALL 0x000000000000007FULL
#define BCMOLT_XGPON_ONU_PARAMS_REGISTRATION_ID_MAX_LENGTH 36
#define BCMOLT_XGPON_ONU_PARAMS_REGISTRATION_ID_LENGTH 36
#define BCMOLT_XGPON_ONU_PARAMS_RANGING_BURST_PROFILE_MIN (bcmolt_burst_profile_index)0
#define BCMOLT_XGPON_ONU_PARAMS_RANGING_BURST_PROFILE_MAX (bcmolt_burst_profile_index)3
#define BCMOLT_XGPON_ONU_PARAMS_DATA_BURST_PROFILE_MIN (bcmolt_burst_profile_index)0
#define BCMOLT_XGPON_ONU_PARAMS_DATA_BURST_PROFILE_MAX (bcmolt_burst_profile_index)3

/** ITU ONU Parameters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_serial_number serial_number; /**< ONU serial number */
    uint32_t ranging_time; /**< ONU ranging time.  This is normally read-only and can only be written when the PON is in active-standby mode to keep the ONU in sync. */
    bcmolt_itupon_onu_aes_key encryption_key; /**< Current AES encryption key.  This is normally read-only and can only be written when the PON is in active-standby mode to keep the ONU in sync. */
    bcmos_bool auto_learning; /**< Automatic learning of password (GPON) or registration ID (XGPON) */
    bcmolt_status disabled_after_discovery; /**< This ONU was disabled after SN discovery */
    bcmolt_automatic_onu_deactivation_reason automatic_onu_deactivation_reason; /**< automatic ONU deactivation reason. */
    bcmos_bool ps_type_c; /**< The ONU has a PS switching type C backup. */
    bcmolt_gpon_onu_params gpon; /**< GPON ONU Parameters. */
    bcmolt_xgpon_onu_params xgpon; /**< XGPON, NGPON2, XGS-PON ONU Parameters. */
} bcmolt_itu_onu_params;

/* Constants associated with bcmolt_itu_onu_params. */
#define BCMOLT_ITU_ONU_PARAMS_PRESENCE_MASK_ALL 0x00000000000009EFULL
#define BCMOLT_ITU_ONU_PARAMS_RANGING_TIME_DEFAULT 0UL
#define BCMOLT_ITU_ONU_PARAMS_DISABLED_AFTER_DISCOVERY_DEFAULT BCMOLT_STATUS_OFF
#define BCMOLT_ITU_ONU_PARAMS_AUTOMATIC_ONU_DEACTIVATION_REASON_DEFAULT BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_NONE
#define BCMOLT_ITU_ONU_PARAMS_PS_TYPE_C_DEFAULT BCMOS_FALSE

/** PON available bandwidth */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t cbr_bw; /**< Total BW available for CBR-rt (CBR real-time) traffic. In all modes except TDMA this is expressed in bytes/sec. In TDMA, it is expressed as blocks/sec in XGS or words/secin XGPON. */
    uint32_t total_bw; /**< Total BW available for guaranteed traffic. In all modes except TDMA this is expressed in bytes/sec. In TDMA, it is expressed as blocks/sec in XGS or words/sec in XGPON. */
    uint32_t group_total_bw; /**< Total BW available for guaranteed traffic for the entire PON group. In all modes, this is expressed in bytes/sec. */
    uint32_t next_onu_total_bw; /**< Total BW available for guaranteed traffic after new ONU is added. In all modes except TDMA this is expressed in bytes/sec. In TDMA, it is expressed as blocks/sec in XGS or words/sec in XGPON. */
} bcmolt_pon_available_bandwidth;

/* Constants associated with bcmolt_pon_available_bandwidth. */
#define BCMOLT_PON_AVAILABLE_BANDWIDTH_PRESENCE_MASK_ALL 0x000000000000000FULL

/** PON Drift Control */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t drift_interval; /**< Interval in milliseconds for ONU transmission drift monitoring (0 = disabled). */
    uint8_t drift_limit; /**< DOWi threshold in bits */
    uint8_t transmission_control_limit; /**< TIWi threshold in bits */
} bcmolt_pon_drift_control;

/* Constants associated with bcmolt_pon_drift_control. */
#define BCMOLT_PON_DRIFT_CONTROL_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_PON_DRIFT_CONTROL_DRIFT_INTERVAL_DEFAULT 1000UL
#define BCMOLT_PON_DRIFT_CONTROL_DRIFT_INTERVAL_MIN 0UL
#define BCMOLT_PON_DRIFT_CONTROL_DRIFT_INTERVAL_MAX 60000UL
#define BCMOLT_PON_DRIFT_CONTROL_DRIFT_LIMIT_DEFAULT 8
#define BCMOLT_PON_DRIFT_CONTROL_DRIFT_LIMIT_MIN 1
#define BCMOLT_PON_DRIFT_CONTROL_DRIFT_LIMIT_MAX 32
#define BCMOLT_PON_DRIFT_CONTROL_TRANSMISSION_CONTROL_LIMIT_DEFAULT 16
#define BCMOLT_PON_DRIFT_CONTROL_TRANSMISSION_CONTROL_LIMIT_MIN 1
#define BCMOLT_PON_DRIFT_CONTROL_TRANSMISSION_CONTROL_LIMIT_MAX 64

/** ITU PON ONU Activation Control */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_control_state key_exchange; /**< Perform single key exchange during activation. */
    bcmolt_control_state authentication; /**< Perform authentication during activation */
    bcmolt_control_state fail_due_to_authentication_failure; /**< Deactivate ONU due to password/registration authentication failure */
} bcmolt_onu_activation;

/* Constants associated with bcmolt_onu_activation. */
#define BCMOLT_ONU_ACTIVATION_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_ONU_ACTIVATION_KEY_EXCHANGE_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_ONU_ACTIVATION_AUTHENTICATION_DEFAULT BCMOLT_CONTROL_STATE_ENABLE
#define BCMOLT_ONU_ACTIVATION_FAIL_DUE_TO_AUTHENTICATION_FAILURE_DEFAULT BCMOLT_CONTROL_STATE_ENABLE

/** ITU-PON Key Exchange */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t interval; /**< Key Exchange process interval in milliseconds */
    bcmolt_control_state control; /**< Enable\disable periodic process of Key Exchange for active ONUs */
    bcmolt_control_state encrypted_ports_only; /**< Perform key exchange only to ONUs with GEM ports that have downstream encryption enabled */
    bcmolt_gpon_key_exchange_mode gpon_mode; /**< Key exchange mode */
} bcmolt_key_exchange;

/* Constants associated with bcmolt_key_exchange. */
#define BCMOLT_KEY_EXCHANGE_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_KEY_EXCHANGE_INTERVAL_DEFAULT 10000UL
#define BCMOLT_KEY_EXCHANGE_INTERVAL_MIN 1000UL
#define BCMOLT_KEY_EXCHANGE_INTERVAL_MAX 3600000UL
#define BCMOLT_KEY_EXCHANGE_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_KEY_EXCHANGE_ENCRYPTED_PORTS_ONLY_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_KEY_EXCHANGE_GPON_MODE_DEFAULT BCMOLT_GPON_KEY_EXCHANGE_MODE_NORMAL

/** Configuration parameters for the ONU power management feature. These should match the parameters
  * sent to the ONU via OMCI. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t ilowpower; /**< The maximum amount of time any ONU on this NI may spend in a low power state in units of 125us. */
    uint32_t iaware; /**< The minimum amount of time every ONU on his NI must spend in an aware state in units of 125us. */
    uint16_t itransinit; /**< The maximum amount of time required by any ONU on this NI to power up its transmitter only from a low power state in units of 125us. */
    uint16_t itxinit; /**< The maximum amount of time required by any ONU on this NI to power up its transceiver (transmitter + receiver) from a low power state in units of 125us. */
    uint32_t irxoff; /**< The maximum amount of time any ONU on this NI may spend with its receiver disabled in units of 125us. */
} bcmolt_onu_power_management_configuration;

/* Constants associated with bcmolt_onu_power_management_configuration. */
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ILOWPOWER_DEFAULT 1600UL
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ILOWPOWER_MIN 8UL
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ILOWPOWER_MAX 480000UL
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_IAWARE_DEFAULT 160UL
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_IAWARE_MIN 8UL
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_IAWARE_MAX 480000UL
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ITRANSINIT_DEFAULT 80U
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ITRANSINIT_MIN 0U
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ITRANSINIT_MAX 8000U
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ITXINIT_DEFAULT 80U
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ITXINIT_MIN 0U
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ITXINIT_MAX 8000U
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_IRXOFF_DEFAULT 1600UL
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_IRXOFF_MIN 8UL
#define BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_IRXOFF_MAX 480000UL

/** Periodic Standby PON monitoring */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t interval; /**< interval in ms. */
    bcmolt_control_state control; /**< control. */
} bcmolt_periodic_standby_pon_monitoring;

/* Constants associated with bcmolt_periodic_standby_pon_monitoring. */
#define BCMOLT_PERIODIC_STANDBY_PON_MONITORING_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_PERIODIC_STANDBY_PON_MONITORING_INTERVAL_DEFAULT 5000UL
#define BCMOLT_PERIODIC_STANDBY_PON_MONITORING_INTERVAL_MIN 1000UL
#define BCMOLT_PERIODIC_STANDBY_PON_MONITORING_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_DISABLE

/** PRBS checker config */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_prbs_polynomial polynom; /**< PRBS polynom type */
    bcmolt_prbs_checker_mode mode; /**< PRBS LOCK state machine. */
    bcmos_bool data_invert; /**< Invert or no invert for received PRBS data */
    bcmolt_control_state control; /**< Enable\Disable the US PRBS checker */
    bcmos_bool is_tdmr_xgs; /**< Optional field for TDMR mode allow choosing XGS/XGPON mode for PRBS testing */
} bcmolt_prbs_checker_config;

/* Constants associated with bcmolt_prbs_checker_config. */
#define BCMOLT_PRBS_CHECKER_CONFIG_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_PRBS_CHECKER_CONFIG_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_PRBS_CHECKER_CONFIG_IS_TDMR_XGS_DEFAULT BCMOS_TRUE

/** PRBS Generator config */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_prbs_polynomial polynom; /**< PRBS polynom type */
    bcmos_bool error_insert; /**< 0 to 1 transition on this signal will insert single bit error in the MSB bit of the data bus. */
    bcmos_bool invert; /**< Invert or no invert for transmitted PRBS data */
    bcmolt_control_state control; /**< Enable\Disable the DS PRBS generator */
} bcmolt_prbs_generator_config;

/* Constants associated with bcmolt_prbs_generator_config. */
#define BCMOLT_PRBS_GENERATOR_CONFIG_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_PRBS_GENERATOR_CONFIG_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_DISABLE

/** That state of the PRBS test, lock state, and error counters. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_prbs_lock_state lock_state; /**< The state of the PRBS lock */
    uint32_t error_counts; /**< The bit errors observed during the PRBS test.  This field is clear on read. */
    bcmos_bool loss_sync; /**< The state of the PRBS loss sync. N/A in 68620 */
    double ber; /**< The bit error ratio. N/A in 68620 */
    bcmolt_prbs_test_status_type test_status; /**< Test Run Status: Continue - can run test once more, Done - when reached maximal value of Error counts. N/A in 68620 */
} bcmolt_prbs_status;

/* Constants associated with bcmolt_prbs_status. */
#define BCMOLT_PRBS_STATUS_PRESENCE_MASK_ALL 0x000000000000001FULL

/** ITU PON protection switching configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint16_t timeout; /**< LOS switch over timeout in milliseconds */
    bcmolt_gpio_pin gpio_pin; /**< GPIO pin for input/output signal */
    uint16_t ps_c_wait_before_deactivation_timeout; /**< PS type C timeout in milliseconds */
    bcmolt_pon_protection_switching_options options; /**< Options to control the protection switching process */
} bcmolt_itupon_protection_switching;

/* Constants associated with bcmolt_itupon_protection_switching. */
#define BCMOLT_ITUPON_PROTECTION_SWITCHING_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_ITUPON_PROTECTION_SWITCHING_TIMEOUT_DEFAULT 100U
#define BCMOLT_ITUPON_PROTECTION_SWITCHING_TIMEOUT_MIN 0U
#define BCMOLT_ITUPON_PROTECTION_SWITCHING_TIMEOUT_MAX 65535U
#define BCMOLT_ITUPON_PROTECTION_SWITCHING_GPIO_PIN_DEFAULT BCMOLT_GPIO_PIN_UNCONFIGURED
#define BCMOLT_ITUPON_PROTECTION_SWITCHING_PS_C_WAIT_BEFORE_DEACTIVATION_TIMEOUT_DEFAULT 1000U
#define BCMOLT_ITUPON_PROTECTION_SWITCHING_OPTIONS_DEFAULT (bcmolt_pon_protection_switching_options)0UL

/** ITU PON ONU upgrade params */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t response_timeout_ms; /**< The length of time that the OLT will wait for the ONU to respond. */
    uint8_t max_retry_count; /**< The number of retries.
    The OLT will retry the OMCI messages to the ONU up to the number specified by this parameter. */
    bcmolt_omci_device_id omci_format; /**< Baseline (0x0A) or Extended (0x0B).
    The baseline messages have 48-byte fixed length PDUs, while the extended messages have variable length PDUs. */
    uint16_t window_size; /**< Number of sections per window.
    Refer to G.988-2012, I.3.2.1. */
    bcmos_bool activate_commit; /**< Automatically activate the new image and commit. */
    uint32_t delay_for_commit_ms; /**< Delay time before COMMIT command.  Unit is milliseconds. */
    uint8_t max_activation_attempts; /**< Maximum number of re-attempts to activate the ONU. */
    uint32_t end_swdl_delay_ms; /**< The length of time to wait after sending the last data block but before sending the END_SWDL message. */
} bcmolt_ituonu_upgrade_params;

/* Constants associated with bcmolt_ituonu_upgrade_params. */
#define BCMOLT_ITUONU_UPGRADE_PARAMS_PRESENCE_MASK_ALL 0x00000000000000FFULL
#define BCMOLT_ITUONU_UPGRADE_PARAMS_RESPONSE_TIMEOUT_MS_DEFAULT 1000UL
#define BCMOLT_ITUONU_UPGRADE_PARAMS_RESPONSE_TIMEOUT_MS_MIN 50UL
#define BCMOLT_ITUONU_UPGRADE_PARAMS_RESPONSE_TIMEOUT_MS_MAX 1000000UL
#define BCMOLT_ITUONU_UPGRADE_PARAMS_MAX_RETRY_COUNT_DEFAULT 23
#define BCMOLT_ITUONU_UPGRADE_PARAMS_OMCI_FORMAT_DEFAULT BCMOLT_OMCI_DEVICE_ID_BASELINE
#define BCMOLT_ITUONU_UPGRADE_PARAMS_WINDOW_SIZE_DEFAULT 32U
#define BCMOLT_ITUONU_UPGRADE_PARAMS_WINDOW_SIZE_MIN 1U
#define BCMOLT_ITUONU_UPGRADE_PARAMS_WINDOW_SIZE_MAX 256U
#define BCMOLT_ITUONU_UPGRADE_PARAMS_ACTIVATE_COMMIT_DEFAULT BCMOS_FALSE
#define BCMOLT_ITUONU_UPGRADE_PARAMS_DELAY_FOR_COMMIT_MS_DEFAULT 45000UL
#define BCMOLT_ITUONU_UPGRADE_PARAMS_DELAY_FOR_COMMIT_MS_MIN 0UL
#define BCMOLT_ITUONU_UPGRADE_PARAMS_DELAY_FOR_COMMIT_MS_MAX 1000000UL
#define BCMOLT_ITUONU_UPGRADE_PARAMS_MAX_ACTIVATION_ATTEMPTS_DEFAULT 23
#define BCMOLT_ITUONU_UPGRADE_PARAMS_END_SWDL_DELAY_MS_DEFAULT 30000UL
#define BCMOLT_ITUONU_UPGRADE_PARAMS_END_SWDL_DELAY_MS_MIN 0UL
#define BCMOLT_ITUONU_UPGRADE_PARAMS_END_SWDL_DELAY_MS_MAX 1000000UL

/** ONU Upgrade Status */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_id onu_id; /**< ONU ID. */
    uint32_t bytes_transmitted; /**< Number of bytes transmitted so far. */
    bcmolt_onu_upgrade_status_code status; /**< Upgrade status. */
} bcmolt_onu_upgrade_status;

/* Constants associated with bcmolt_onu_upgrade_status. */
#define BCMOLT_ONU_UPGRADE_STATUS_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Variable-length list of onu_upgrade_status */
typedef struct
{
    uint32_t len; /**< List length. */
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_onu_upgrade_status *arr; /**< List contents. */
} bcmolt_onu_upgrade_status_list_u32_max_128;

/** PON NI ONU upgrade status */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_pon_ni_onu_upgrade_status_code overall_status; /**< Overall status of the ONU upgrade. */
    uint32_t file_size_in_bytes; /**< Total size of the file to send in bytes. */
    bcmolt_onu_upgrade_status_list_u32_max_128 onu_status; /**< Status for each ONU that is part of the upgrade process. */
} bcmolt_pon_onu_upgrade_status;

/* Constants associated with bcmolt_pon_onu_upgrade_status. */
#define BCMOLT_PON_ONU_UPGRADE_STATUS_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_PON_ONU_UPGRADE_STATUS_ONU_STATUS_MAX_LENGTH 128

/** XGPON ONU alarms thresholds */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t losi; /**< Threshold for asserting LOSi alarm. */
    uint8_t lobi; /**< Threshold for asserting LOBi alarm. */
    uint8_t looci; /**< Threshold for asserting LOOCi alarm. */
    uint8_t lopci; /**< Threshold for asserting LOPCi alarm. */
} bcmolt_xgpon_onu_alarms_thresholds;

/* Constants associated with bcmolt_xgpon_onu_alarms_thresholds. */
#define BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_LOSI_DEFAULT 4
#define BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_LOBI_DEFAULT 4
#define BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_LOOCI_DEFAULT 3
#define BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_LOPCI_DEFAULT 3

/** xgpon onu alarm indication control */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_control_state loai; /**< loss of ack indication control. */
    bcmolt_control_state loki; /**< loss of key indicayion control. */
} bcmolt_xgpon_onu_alarm_indication_control;

/* Constants associated with bcmolt_xgpon_onu_alarm_indication_control. */
#define BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_LOAI_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_LOKI_DEFAULT BCMOLT_CONTROL_STATE_DISABLE

/** XGPON Multicast key */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_arr_aes_key_2 key; /**< AES encryption key array for multicsat XGEM port IDs */
    uint8_t key_index; /**< AES encryption key index. 0 - no encryption key. */
} bcmolt_xgpon_multicast_key;

/* Constants associated with bcmolt_xgpon_multicast_key. */
#define BCMOLT_XGPON_MULTICAST_KEY_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_XGPON_MULTICAST_KEY_KEY_LENGTH 2
#define BCMOLT_XGPON_MULTICAST_KEY_KEY_INDEX_DEFAULT 0
#define BCMOLT_XGPON_MULTICAST_KEY_KEY_INDEX_MIN 0
#define BCMOLT_XGPON_MULTICAST_KEY_KEY_INDEX_MAX 2

/** onu tuning configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t tsource; /**< Tsource timer in msec */
    uint32_t ttarget; /**< Ttarget timer in msec */
    bcmos_bool request_registration_required; /**< is request registration part of the tuning in process */
} bcmolt_onu_tuning_configuration;

/* Constants associated with bcmolt_onu_tuning_configuration. */
#define BCMOLT_ONU_TUNING_CONFIGURATION_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_ONU_TUNING_CONFIGURATION_TSOURCE_DEFAULT 1000UL
#define BCMOLT_ONU_TUNING_CONFIGURATION_TTARGET_DEFAULT 1000UL
#define BCMOLT_ONU_TUNING_CONFIGURATION_REQUEST_REGISTRATION_REQUIRED_DEFAULT BCMOS_TRUE

/** ngpon2 pon params */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_control_state ngpon2_amd1; /**< Enable or disable support of Amendment 1 of G.989.3 on this PON */
    bcmolt_onu_tuning_configuration onu_tuning; /**< onu tuning. */
} bcmolt_ngpon2_pon_params;

/* Constants associated with bcmolt_ngpon2_pon_params. */
#define BCMOLT_NGPON2_PON_PARAMS_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_NGPON2_PON_PARAMS_NGPON2_AMD1_DEFAULT BCMOLT_CONTROL_STATE_DISABLE

/** XGPON PLOAM retransmission  */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t retrans_ranging_time; /**< Number of Ranging Time ploam retransmissions in case of ACK timeout */
    uint8_t retrans_assign_alloc_id; /**< Number of Assign Alloc ID ploam retransmissions in case of ACK timeout */
    uint8_t retrans_key_control; /**< Number of Key Control ploam retransmissions in case of ACK timeout */
    uint8_t retrans_request_registration; /**< Number of Request Registration ploam retransmissions in case of ACK timeout */
} bcmolt_ploam_retransmission;

/* Constants associated with bcmolt_ploam_retransmission. */
#define BCMOLT_PLOAM_RETRANSMISSION_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_PLOAM_RETRANSMISSION_RETRANS_RANGING_TIME_DEFAULT 0
#define BCMOLT_PLOAM_RETRANSMISSION_RETRANS_ASSIGN_ALLOC_ID_DEFAULT 0
#define BCMOLT_PLOAM_RETRANSMISSION_RETRANS_KEY_CONTROL_DEFAULT 0
#define BCMOLT_PLOAM_RETRANSMISSION_RETRANS_REQUEST_REGISTRATION_DEFAULT 0

/** Operation Control */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t re; /**< Indicates whether the Transmit Optical Level (TOL) contains the launch power of the OTL (RE=0) or of a reach extender (RE=1) */
    bcmolt_odn_class odn_class; /**< Identifies the nominal optical parameters of the transceiver according to the ODN Optical Path Loss (OPL) */
    bcmolt_control_state ds_fec_mode; /**< Enable/Disable the downstream FEC. Default is Enable. Attribute can be set only when PON NI state is Inactive. */
    bcmolt_tc_protocol protocol; /**< When system mode is NGPON2, this parameter Indicate the TC layer protocol: ITU-T G.989.3 or ITU-T G.987.3 */
    bcmolt_link_type ds_link_type; /**< Optical link type (Unspecified, A, B, Both) */
    bcmolt_pon_id pon_id; /**< Identifies the TWDM channel termination within a certain domain */
    uint8_t c; /**< Transmit optical level (TOL) reference point indicator: S/R-CG or S/R-CP */
    uint16_t tol; /**< Transmit Optical Level. An indication of the current OLT CT transceiver channel launch power into the ODN */
} bcmolt_operation_control;

/* Constants associated with bcmolt_operation_control. */
#define BCMOLT_OPERATION_CONTROL_PRESENCE_MASK_ALL 0x00000000000000FFULL
#define BCMOLT_OPERATION_CONTROL_RE_DEFAULT 0
#define BCMOLT_OPERATION_CONTROL_RE_MIN 0
#define BCMOLT_OPERATION_CONTROL_RE_MAX 1
#define BCMOLT_OPERATION_CONTROL_DS_FEC_MODE_DEFAULT BCMOLT_CONTROL_STATE_ENABLE
#define BCMOLT_OPERATION_CONTROL_PROTOCOL_DEFAULT BCMOLT_TC_PROTOCOL_TC_LAYER_PROTOCOL_G_989_P_3
#define BCMOLT_OPERATION_CONTROL_C_DEFAULT 0
#define BCMOLT_OPERATION_CONTROL_C_MIN 0
#define BCMOLT_OPERATION_CONTROL_C_MAX 1
#define BCMOLT_OPERATION_CONTROL_TOL_MAX 511U

/** Periodic profile PLOAM interval and control. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_control_state control; /**< Enable/Disable periodic profile PLOAM transmission. */
    uint32_t interval_ms; /**< Periodic PLOAM interval in milliseconds */
} bcmolt_periodic_ploams;

/* Constants associated with bcmolt_periodic_ploams. */
#define BCMOLT_PERIODIC_PLOAMS_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_PERIODIC_PLOAMS_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_PERIODIC_PLOAMS_INTERVAL_MS_DEFAULT 5000UL
#define BCMOLT_PERIODIC_PLOAMS_INTERVAL_MS_MIN 500UL
#define BCMOLT_PERIODIC_PLOAMS_INTERVAL_MS_MAX 10000UL

/** XGPON/NGPON2/XGS PON Configuration Parameters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_hw_pon_id hw_pon_id; /**< 51 bit PON identifier. This attribute is part of the downstream physical synchronization block (PSBd) */
    bcmolt_xgpon_onu_alarms_thresholds onu_alarms_thresholds; /**< ONU alarms thresholds configuration */
    bcmolt_xgpon_onu_alarm_indication_control alarm_indication_control; /**< alarm indication control. */
    bcmolt_xgpon_multicast_key multicast_key; /**< Multicast XGEM ports encryption control */
    bcmolt_gem_port_id min_data_gem_port_id; /**< Min data XGEM port ID value */
    bcmolt_ngpon2_pon_params ngpon2; /**< NGPON2 params */
    bcmolt_control_state tdma_2_5_g_discovery; /**< TDMA 2.5 G discovery */
    bcmolt_control_state tdma_10_g_discovery; /**< TDMA 10G discovery */
    bcmolt_ploam_retransmission ploam_retransmission; /**< xgpon ploam retransmission */
    uint16_t tdma_number_of_2_5_g_active_onus; /**< TDMA number of 2.5Gbps active onus */
    uint16_t tdma_number_of_10_g_active_onus; /**< TDMA number of 10Gbps active onus */
    bcmolt_operation_control operation_control; /**< operation control */
    bcmolt_periodic_ploams periodic_ploams; /**< Periodic profile PLOAM control. */
} bcmolt_xgpon_pon_params;

/* Constants associated with bcmolt_xgpon_pon_params. */
#define BCMOLT_XGPON_PON_PARAMS_PRESENCE_MASK_ALL 0x0000000000001FFFULL
#define BCMOLT_XGPON_PON_PARAMS_MIN_DATA_GEM_PORT_ID_DEFAULT (bcmolt_gem_port_id)1024UL
#define BCMOLT_XGPON_PON_PARAMS_MIN_DATA_GEM_PORT_ID_MIN (bcmolt_gem_port_id)1021UL
#define BCMOLT_XGPON_PON_PARAMS_MIN_DATA_GEM_PORT_ID_MAX (bcmolt_gem_port_id)57599UL
#define BCMOLT_XGPON_PON_PARAMS_TDMA_2_5_G_DISCOVERY_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_XGPON_PON_PARAMS_TDMA_10_G_DISCOVERY_DEFAULT BCMOLT_CONTROL_STATE_DISABLE

/** DBA */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_extended_dba_priority_adjustment extended_dba_priority_adjustment; /**< Extended DBA priority adjustment, to prevent starvation of low priorities */
} bcmolt_itupon_dba;

/* Constants associated with bcmolt_itupon_dba. */
#define BCMOLT_ITUPON_DBA_PRESENCE_MASK_ALL 0x0000000000000001ULL

/** ITU PON Attributes */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_pon_available_bandwidth available_bandwidth; /**< PON available bandwidth parameters */
    uint32_t ranging_window_size; /**< Ranging window size in BW units (4-byte words for 2.5G upstream, 16-byte blocks for 10G upstream) */
    uint32_t eqd_cycles_number; /**< How many ranging windows are opened during a single ONU activation process */
    bcmolt_pon_drift_control drift_control; /**< Drift control process configuration */
    uint8_t los_alarm_threshold; /**< LOS alarm threshold */
    bcmolt_ber_monitor_params ber_monitor; /**< BER monitor process configuration */
    uint32_t ack_timeout; /**< ACK timeout in ms */
    bcmolt_onu_activation onu_activation; /**< ONU activation control parameters */
    bcmolt_key_exchange key_exchange; /**< Key Exchange process configuration */
    bcmolt_alloc_id min_data_alloc_id; /**< Min data Alloc ID value */
    bcmolt_cbr_rt_allocation_profile cbr_rt_allocation_profile; /**< CBR Real Time allocation profile */
    bcmolt_arr_u16_2 cbr_nrt_allocation_profile; /**< CBR non Real Time allocation profile */
    bcmolt_onu_power_management_configuration power_management; /**< ONU power management control */
    bcmolt_periodic_standby_pon_monitoring periodic_standby_pon_monitoring; /**< Periodic Standby PON monitoring */
    bcmolt_prbs_checker_config prbs_checker; /**< US PRBS checker configuration */
    bcmolt_prbs_generator_config prbs_generator; /**< DS PRBS generator configuration */
    bcmolt_prbs_status prbs_status; /**< Result of US PRBS checker */
    bcmolt_dba_mode dba_mode; /**< DBA mode */
    bcmolt_itupon_protection_switching protection_switching; /**< Protection switching control */
    bcmolt_automatic_onu_deactivation automatic_onu_deactivation; /**< Option to disable the automatic deactivation of ONUs due to alarms */
    uint32_t us_bandwidth_limit; /**< Total PON upstream bandwidth limit in bytes per second. */
    bcmolt_ituonu_upgrade_params onu_upgrade_params; /**< ONU upgrade params. */
    bcmolt_pon_onu_upgrade_status onu_upgrade_status; /**< ONU upgrade status. */
    bcmolt_control_state ds_fec_mode; /**< DS FEC mode. */
    bcmolt_xgpon_pon_params xgpon; /**< XGPON, NGPON2, XGS PON Parameters */
    bcmolt_gpon_pon_params gpon; /**< GPON Parameters */
    bcmos_bool bw_eligibility_class_stats; /**< BW Eligibility Class Statistics */
    bcmolt_itupon_dba dba; /**< DBA */
} bcmolt_itu_pon_params;

/* Constants associated with bcmolt_itu_pon_params. */
#define BCMOLT_ITU_PON_PARAMS_PRESENCE_MASK_ALL 0x00000001ABEBFFFFULL
#define BCMOLT_ITU_PON_PARAMS_EQD_CYCLES_NUMBER_DEFAULT 2UL
#define BCMOLT_ITU_PON_PARAMS_EQD_CYCLES_NUMBER_MIN 0UL
#define BCMOLT_ITU_PON_PARAMS_EQD_CYCLES_NUMBER_MAX 255UL
#define BCMOLT_ITU_PON_PARAMS_LOS_ALARM_THRESHOLD_DEFAULT 4
#define BCMOLT_ITU_PON_PARAMS_ACK_TIMEOUT_DEFAULT 2000UL
#define BCMOLT_ITU_PON_PARAMS_MIN_DATA_ALLOC_ID_DEFAULT (bcmolt_alloc_id)1024U
#define BCMOLT_ITU_PON_PARAMS_MIN_DATA_ALLOC_ID_MIN (bcmolt_alloc_id)256U
#define BCMOLT_ITU_PON_PARAMS_MIN_DATA_ALLOC_ID_MAX (bcmolt_alloc_id)14591U
#define BCMOLT_ITU_PON_PARAMS_CBR_NRT_ALLOCATION_PROFILE_LENGTH 2
#define BCMOLT_ITU_PON_PARAMS_DBA_MODE_DEFAULT BCMOLT_DBA_MODE_NORMAL
#define BCMOLT_ITU_PON_PARAMS_US_BANDWIDTH_LIMIT_DEFAULT 311040000UL
#define BCMOLT_ITU_PON_PARAMS_DS_FEC_MODE_DEFAULT BCMOLT_CONTROL_STATE_ENABLE

/** ITU ToD */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_control_state tod_enable; /**< ToD control state */
    bcmolt_gpio_pin tod_gpio_pin; /**< ToD GIO pin */
    bcmos_bool connected_internally; /**< ToD Internal */
    uint8_t tod_string_length; /**< ToD string length */
} bcmolt_itu_tod;

/* Constants associated with bcmolt_itu_tod. */
#define BCMOLT_ITU_TOD_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_ITU_TOD_TOD_ENABLE_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_ITU_TOD_TOD_GPIO_PIN_DEFAULT BCMOLT_GPIO_PIN_UNCONFIGURED
#define BCMOLT_ITU_TOD_CONNECTED_INTERNALLY_DEFAULT BCMOS_FALSE
#define BCMOLT_ITU_TOD_TOD_STRING_LENGTH_DEFAULT 16
#define BCMOLT_ITU_TOD_TOD_STRING_LENGTH_MAX 64

/** ITU PON ONU EQD */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_onu_id onu_id; /**< ONU ID. */
    uint32_t eqd; /**< EQD. */
} bcmolt_itupon_onu_eqd;

/* Constants associated with bcmolt_itupon_onu_eqd. */
#define BCMOLT_ITUPON_ONU_EQD_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Variable-length list of itupon_onu_eqd */
typedef struct
{
    uint32_t len; /**< List length. */
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_itupon_onu_eqd *arr; /**< List contents. */
} bcmolt_itupon_onu_eqd_list_u32;

/** System Wide LAG Configuration Parameters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_lag_hash_polynomial polynomial; /**< LAG Polynomial Values. */
    bcmolt_lag_hash_field_flags hash_field; /**< LAG Hash Fields. */
} bcmolt_lag_global_parms;

/* Constants associated with bcmolt_lag_global_parms. */
#define BCMOLT_LAG_GLOBAL_PARMS_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_LAG_GLOBAL_PARMS_POLYNOMIAL_DEFAULT BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X8003
#define BCMOLT_LAG_GLOBAL_PARMS_HASH_FIELD_DEFAULT (bcmolt_lag_hash_field_flags)7UL

/** lag_interface_members_update_command used to add/remove/set members of a lag_interface */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_members_update_command command; /**< command. */
    bcmolt_arr_nni_id_8 nni_ids; /**< nni_ids. */
} bcmolt_lag_interface_members_update_command;

/* Constants associated with bcmolt_lag_interface_members_update_command. */
#define BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_NNI_IDS_LENGTH 8

/** Local Maintenace Endpoint Identifier for MEG */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_mep_id id; /**< endpoint id */
    bcmolt_ccm_interval interval; /**< tx ccm rate in msec. LOC if no rx ccm in 3.5 ccm_intervals. */
    bcmolt_control_state state; /**< local mep enable disable */
} bcmolt_local_mep;

/* Constants associated with bcmolt_local_mep. */
#define BCMOLT_LOCAL_MEP_PRESENCE_MASK_ALL 0x0000000000000049ULL
#define BCMOLT_LOCAL_MEP_ID_DEFAULT (bcmolt_mep_id)65535U
#define BCMOLT_LOCAL_MEP_INTERVAL_DEFAULT BCMOLT_CCM_INTERVAL_RATE_100_MS
#define BCMOLT_LOCAL_MEP_STATE_DEFAULT BCMOLT_CONTROL_STATE_DISABLE

/** Number of messages per log level */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t no_log; /**< Number of messages at the no_log level */
    uint32_t fatal; /**< Number of messages at the fatal level */
    uint32_t error; /**< Number of messages at the error level */
    uint32_t warning; /**< Number of messages at the warning level */
    uint32_t info; /**< Number of messages at the info level */
    uint32_t debug; /**< Number of messages at the debug level */
} bcmolt_log_level_msg_count;

/* Constants associated with bcmolt_log_level_msg_count. */
#define BCMOLT_LOG_LEVEL_MSG_COUNT_PRESENCE_MASK_ALL 0x000000000000003FULL

/** Log levels for different files */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_log_level print; /**< Log level for printing to the UART */
    bcmolt_log_level save; /**< Log level for saving to RAM */
} bcmolt_log_level_per_file;

/* Constants associated with bcmolt_log_level_per_file. */
#define BCMOLT_LOG_LEVEL_PER_FILE_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** ASCII string with max length 48 */
typedef struct
{
    char str[48]; /**< String. */
} bcmolt_str_48;

/** Maint Group Config */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_str_48 name; /**< MEG Name. */
    bcmolt_meg_format format; /**< MEG Id Format. */
    bcmolt_meg_level level; /**< Meg Level. */
} bcmolt_meg_cfg;

/* Constants associated with bcmolt_meg_cfg. */
#define BCMOLT_MEG_CFG_PRESENCE_MASK_ALL 0x0000000000000007ULL
#define BCMOLT_MEG_CFG_FORMAT_DEFAULT BCMOLT_MEG_FORMAT_ICC
#define BCMOLT_MEG_CFG_LEVEL_DEFAULT BCMOLT_MEG_LEVEL_LEVEL_2

/** NNI Link Status */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_trivalent link_status; /**< The local and remote partners are abled and ready to transmit/receive traffic. */
    bcmolt_trivalent signal_detected; /**< Serdes controller has detected energy on the line.  debugging purpose. */
    bcmolt_trivalent pmd_locked; /**< Indicates PMD locked.  debugging purpose.  If this is true, but the links status is not, that means the transceiver is not enabled. */
} bcmolt_nni_link_status;

/* Constants associated with bcmolt_nni_link_status. */
#define BCMOLT_NNI_LINK_STATUS_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** Variable-length list of onu_id */
typedef struct
{
    uint32_t len; /**< List length. */
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_onu_id *arr; /**< List contents. */
} bcmolt_onu_id_list_u32;

/** Data that is used when setting up a PCIe connection. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint16_t host_dma_rx_queue_size; /**< RX queue size of the host DMA. */
    uint16_t host_dma_tx_queue_size; /**< TX queue size of the host DMA. */
    bcmolt_mtu mtu; /**< Maximum Transmission Unit. */
    bcmos_bool avs_control; /**< AVS Control. */
    bcmos_bool debug_trace; /**< Enable PCIE debug trace. Packets transmitted and received over PCIE DMA interface are dumped on both host and device sides */
} bcmolt_pcie_conn_data;

/* Constants associated with bcmolt_pcie_conn_data. */
#define BCMOLT_PCIE_CONN_DATA_PRESENCE_MASK_ALL 0x000000000000001FULL
#define BCMOLT_PCIE_CONN_DATA_HOST_DMA_RX_QUEUE_SIZE_DEFAULT 128U
#define BCMOLT_PCIE_CONN_DATA_HOST_DMA_TX_QUEUE_SIZE_DEFAULT 128U
#define BCMOLT_PCIE_CONN_DATA_MTU_DEFAULT (bcmolt_mtu)4096UL
#define BCMOLT_PCIE_CONN_DATA_MTU_MIN (bcmolt_mtu)4096UL
#define BCMOLT_PCIE_CONN_DATA_MTU_MAX (bcmolt_mtu)16384UL
#define BCMOLT_PCIE_CONN_DATA_AVS_CONTROL_DEFAULT BCMOS_FALSE
#define BCMOLT_PCIE_CONN_DATA_DEBUG_TRACE_DEFAULT BCMOS_FALSE

/** policer profiles for policers of this ACL */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_config_state state; /**< if configured, this is a policer acl */
    bcmolt_arr_policer_ref_4 policer_ref; /**< policers for each traffic type */
} bcmolt_policer_action;

/* Constants associated with bcmolt_policer_action. */
#define BCMOLT_POLICER_ACTION_PRESENCE_MASK_ALL 0x0000000000000006ULL
#define BCMOLT_POLICER_ACTION_STATE_DEFAULT BCMOLT_CONFIG_STATE_NOT_CONFIGURED
#define BCMOLT_POLICER_ACTION_POLICER_REF_LENGTH 4

/** PON Alloc SLA */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t cbr_rt_bw; /**< CBR Real Time Bandwidth which require shaping of the bandwidth allocations in a fine granularity. */
    uint32_t cbr_nrt_bw; /**< Fixed Bandwidth with no critical requirement of shaping */
    uint32_t guaranteed_bw; /**< Dynamic bandwidth which the OLT is committed to allocate upon demand */
    uint32_t maximum_bw; /**< Maximum allocated bandwidth allowed for this alloc ID */
    bcmolt_additional_bw_eligibility additional_bw_eligibility; /**< Alloc ID additional BW eligibility */
    bcmos_bool cbr_rt_compensation; /**< Set to True for AllocID with CBR RT Bandwidth that requires compensation for skipped allocations during quiet window */
    uint8_t cbr_rt_ap_index; /**< Allocation Profile index for CBR RT Bandwidth */
    uint8_t cbr_nrt_ap_index; /**< Allocation Profile index for CBR non-RT Bandwidth */
    bcmolt_alloc_type alloc_type; /**< Type of the alloc ID */
    uint8_t weight; /**< Alloc ID Weight used in case of Extended DBA mode */
    uint8_t priority; /**< Alloc ID Priority used in case of Extended DBA mode */
} bcmolt_pon_alloc_sla;

/* Constants associated with bcmolt_pon_alloc_sla. */
#define BCMOLT_PON_ALLOC_SLA_PRESENCE_MASK_ALL 0x00000000000007FFULL
#define BCMOLT_PON_ALLOC_SLA_CBR_RT_BW_DEFAULT 0UL
#define BCMOLT_PON_ALLOC_SLA_CBR_NRT_BW_DEFAULT 0UL
#define BCMOLT_PON_ALLOC_SLA_GUARANTEED_BW_DEFAULT 0UL
#define BCMOLT_PON_ALLOC_SLA_MAXIMUM_BW_DEFAULT 0UL
#define BCMOLT_PON_ALLOC_SLA_ADDITIONAL_BW_ELIGIBILITY_DEFAULT BCMOLT_ADDITIONAL_BW_ELIGIBILITY_NONE
#define BCMOLT_PON_ALLOC_SLA_CBR_RT_COMPENSATION_DEFAULT BCMOS_FALSE
#define BCMOLT_PON_ALLOC_SLA_CBR_RT_AP_INDEX_DEFAULT 0
#define BCMOLT_PON_ALLOC_SLA_CBR_RT_AP_INDEX_MIN 0
#define BCMOLT_PON_ALLOC_SLA_CBR_RT_AP_INDEX_MAX 0
#define BCMOLT_PON_ALLOC_SLA_CBR_NRT_AP_INDEX_DEFAULT 0
#define BCMOLT_PON_ALLOC_SLA_CBR_NRT_AP_INDEX_MIN 0
#define BCMOLT_PON_ALLOC_SLA_CBR_NRT_AP_INDEX_MAX 1
#define BCMOLT_PON_ALLOC_SLA_WEIGHT_DEFAULT 0
#define BCMOLT_PON_ALLOC_SLA_WEIGHT_MIN 0
#define BCMOLT_PON_ALLOC_SLA_WEIGHT_MAX 100
#define BCMOLT_PON_ALLOC_SLA_PRIORITY_DEFAULT 0
#define BCMOLT_PON_ALLOC_SLA_PRIORITY_MIN 0
#define BCMOLT_PON_ALLOC_SLA_PRIORITY_MAX 7

/** PON Distance */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t max_log_distance; /**< Max logical distance of an ONU on the PON */
    uint32_t max_diff_reach; /**< Max distance between the closest and farthest ONU */
} bcmolt_pon_distance;

/* Constants associated with bcmolt_pon_distance. */
#define BCMOLT_PON_DISTANCE_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_PON_DISTANCE_MAX_LOG_DISTANCE_DEFAULT 20UL
#define BCMOLT_PON_DISTANCE_MAX_LOG_DISTANCE_MIN 1UL
#define BCMOLT_PON_DISTANCE_MAX_LOG_DISTANCE_MAX 100UL
#define BCMOLT_PON_DISTANCE_MAX_DIFF_REACH_DEFAULT 20UL
#define BCMOLT_PON_DISTANCE_MAX_DIFF_REACH_MIN 1UL
#define BCMOLT_PON_DISTANCE_MAX_DIFF_REACH_MAX 60UL

/** Protection Type */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_nni_protection_mode mode; /**< Provisioned protection mode on this nni interface. */
} bcmolt_protection_type;

/* Constants associated with bcmolt_protection_type. */
#define BCMOLT_PROTECTION_TYPE_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_PROTECTION_TYPE_MODE_DEFAULT BCMOLT_NNI_PROTECTION_MODE_UNASSIGNED

/** Local Maintenace Endpoint Identifier for MEG */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_mep_id id; /**< endpoint id */
    bcmolt_loc_clear_threshold loc_clear_threshold; /**< Number of CCMs Rx'd before LOC de-asserted. */
    bcmolt_control_state state; /**< remote mep enable disable */
} bcmolt_remote_mep;

/* Constants associated with bcmolt_remote_mep. */
#define BCMOLT_REMOTE_MEP_PRESENCE_MASK_ALL 0x0000000000000061ULL
#define BCMOLT_REMOTE_MEP_ID_DEFAULT (bcmolt_mep_id)65535U
#define BCMOLT_REMOTE_MEP_LOC_CLEAR_THRESHOLD_DEFAULT BCMOLT_LOC_CLEAR_THRESHOLD_CCM_INTERVAL_TIMES_2
#define BCMOLT_REMOTE_MEP_STATE_DEFAULT BCMOLT_CONTROL_STATE_ENABLE

/** rssi in activation measurement result */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmos_bool rssi_done; /**< rssi measurement done */
    bcmos_bool error; /**< rssi measurement error */
} bcmolt_rssi_measurement_result;

/* Constants associated with bcmolt_rssi_measurement_result. */
#define BCMOLT_RSSI_MEASUREMENT_RESULT_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** PON Service Discovery Control */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t interval; /**< Discovery process interval in milliseconds */
    bcmolt_control_state control; /**< Discovery process control */
    bcmolt_onu_post_discovery_mode onu_post_discovery_mode; /**< Automatic operation following ONU discovery */
    bcmolt_burst_profile_index burst_profile; /**< Burst profile index to use during SN acquisition window */
} bcmolt_service_discovery;

/* Constants associated with bcmolt_service_discovery. */
#define BCMOLT_SERVICE_DISCOVERY_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_SERVICE_DISCOVERY_INTERVAL_DEFAULT 1000UL
#define BCMOLT_SERVICE_DISCOVERY_INTERVAL_MIN 1000UL
#define BCMOLT_SERVICE_DISCOVERY_INTERVAL_MAX 2147483UL
#define BCMOLT_SERVICE_DISCOVERY_CONTROL_DEFAULT BCMOLT_CONTROL_STATE_DISABLE
#define BCMOLT_SERVICE_DISCOVERY_ONU_POST_DISCOVERY_MODE_DEFAULT BCMOLT_ONU_POST_DISCOVERY_MODE_NONE
#define BCMOLT_SERVICE_DISCOVERY_BURST_PROFILE_DEFAULT (bcmolt_burst_profile_index)0
#define BCMOLT_SERVICE_DISCOVERY_BURST_PROFILE_MIN (bcmolt_burst_profile_index)0
#define BCMOLT_SERVICE_DISCOVERY_BURST_PROFILE_MAX (bcmolt_burst_profile_index)3

/** Statistic alarm trigger configuration. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_condition_type type; /**< Type of condition to trigger the alarm. */
    union
    {
        struct
        {
            bcmolt_presence_mask presence_mask;
            uint64_t rising; /**< The alarm is raised if the stats delta value per second becomes greater than this threshold level. */
            uint64_t falling; /**< The alarm is cleared if the stats delta value per second becomes less than this threshold level. */
        } rate_threshold;
        struct
        {
            bcmolt_presence_mask presence_mask;
            uint64_t upper; /**< The alarm is raised if the stats delta value per second becomes greater than this upper level. */
            uint64_t lower; /**< The alarm is raised if the stats delta value per second becomes less than this lower level. */
        } rate_range;
        struct
        {
            bcmolt_presence_mask presence_mask;
            uint64_t limit; /**< The alarm is raised if the stats sample value becomes greater than this level.  The alarm is cleared when the host clears the stats. */
        } value_threshold;
        struct
        {
            bcmolt_presence_mask presence_mask;
        } none;
    } u;
} bcmolt_stat_alarm_trigger_config;

/* Constants associated with bcmolt_stat_alarm_trigger_config. */
#define BCMOLT_STAT_ALARM_TRIGGER_CONFIG_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_PRESENCE_MASK_ALL 0x0000000000000003ULL
#define BCMOLT_STAT_ALARM_TRIGGER_CONFIG_VALUE_THRESHOLD_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_STAT_ALARM_TRIGGER_CONFIG_NONE_PRESENCE_MASK_ALL 0x0000000000000000ULL

/** Statistics alarm soaking configuration */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t active_soak_time; /**< If the alarm condition is raised and stays in the raised state for at least this amount of time (unit=seconds), the alarm indication is sent to the host.
    The OLT delays the alarm indication no less than this delay period. It can be delayed more than this period because of the statistics sampling interval. */
    uint32_t clear_soak_time; /**< After the alarm is raised, if it is cleared and stays in the cleared state for at least this amount of time (unit=seconds), the alarm indication is sent to the host.
    The OLT delays the alarm indication no less than this delay period.  It can be delayed more than this period because of the statistics sampling interval. */
} bcmolt_stat_alarm_soak_config;

/* Constants associated with bcmolt_stat_alarm_soak_config. */
#define BCMOLT_STAT_ALARM_SOAK_CONFIG_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Statistic alarm configuration. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_stat_alarm_trigger_config trigger; /**< Statistics alarm trigger configuration. */
    bcmolt_stat_alarm_soak_config soak; /**< Statistics alarm soaking configuration */
} bcmolt_stat_alarm_config;

/* Constants associated with bcmolt_stat_alarm_config. */
#define BCMOLT_STAT_ALARM_CONFIG_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** ASCII string with max length 100 */
typedef struct
{
    char str[100]; /**< String. */
} bcmolt_str_100;

/** ASCII string with max length 16 */
typedef struct
{
    char str[16]; /**< String. */
} bcmolt_str_16;

/** ASCII string with max length 2000 */
typedef struct
{
    char str[2000]; /**< String. */
} bcmolt_str_2000;

/** ASCII string with max length 2048 */
typedef struct
{
    char str[2048]; /**< String. */
} bcmolt_str_2048;

/** SW Error */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint64_t first_error_time_us; /**< Timestamp (in us) when his error first occurred */
    uint64_t last_error_time_us; /**< Timestamp (in us) when his error last occurred */
    uint32_t line_number; /**< Line Number. */
    uint32_t error_counter; /**< The number of times this error has occurred */
    uint32_t instance; /**< Instance. */
    bcmolt_str_64 filename; /**< Filename. */
    bcmolt_str_64 task_name; /**< Task Name. */
} bcmolt_sw_error;

/* Constants associated with bcmolt_sw_error. */
#define BCMOLT_SW_ERROR_PRESENCE_MASK_ALL 0x000000000000007FULL

/** System profile */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t ng_2_sys_id; /**< 20-bit identifier of the NGPON2 system */
    uint8_t version; /**< System profile version. */
    uint8_t channel_spacing; /**< An integer indicating the channel spacing in units of 1GHz */
    bcmolt_us_operating_wavelength_bands us_operating_wavelength_bands; /**< Upstream operating wavelength bands */
    uint8_t us_mse; /**< Upstream Maximum Spectral Excursion (MSE) represented as an unsigned integer indicating the value in units of 1GHz */
    uint8_t loose_calibration_bound; /**< Spectral excursion bound below which a TWDM ONU can be considered as loosely calibrated, in units of 1GHz. A value of 0 means use upstream MSE. */
    uint16_t fsr; /**< If a cyclic WM is used in the upstream, Free Spectral Range indicates the value in units of 0.1 GHz */
    uint8_t twdm_channel_count; /**< The number of Channel_Profile PLOAM messages with distinct Channel Profile indices that an ONU can expect to receive while listening to this downstream wavelength channel */
} bcmolt_system_profile;

/* Constants associated with bcmolt_system_profile. */
#define BCMOLT_SYSTEM_PROFILE_PRESENCE_MASK_ALL 0x00000000000000FFULL
#define BCMOLT_SYSTEM_PROFILE_NG_2_SYS_ID_MIN 0UL
#define BCMOLT_SYSTEM_PROFILE_NG_2_SYS_ID_MAX 1048575UL
#define BCMOLT_SYSTEM_PROFILE_VERSION_DEFAULT 0
#define BCMOLT_SYSTEM_PROFILE_VERSION_MIN 0
#define BCMOLT_SYSTEM_PROFILE_VERSION_MAX 15
#define BCMOLT_SYSTEM_PROFILE_CHANNEL_SPACING_DEFAULT 100
#define BCMOLT_SYSTEM_PROFILE_CHANNEL_SPACING_MIN 50
#define BCMOLT_SYSTEM_PROFILE_CHANNEL_SPACING_MAX 200
#define BCMOLT_SYSTEM_PROFILE_US_MSE_DEFAULT 20
#define BCMOLT_SYSTEM_PROFILE_US_MSE_MIN 12
#define BCMOLT_SYSTEM_PROFILE_US_MSE_MAX 25
#define BCMOLT_SYSTEM_PROFILE_LOOSE_CALIBRATION_BOUND_DEFAULT 0
#define BCMOLT_SYSTEM_PROFILE_FSR_DEFAULT 0U
#define BCMOLT_SYSTEM_PROFILE_TWDM_CHANNEL_COUNT_DEFAULT 8
#define BCMOLT_SYSTEM_PROFILE_TWDM_CHANNEL_COUNT_MIN 0
#define BCMOLT_SYSTEM_PROFILE_TWDM_CHANNEL_COUNT_MAX 15

/** TM Sched Param */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_tm_sched_param_type type; /**< Type. */
    union
    {
        struct
        {
            bcmolt_presence_mask presence_mask;
            bcmolt_tm_priority priority; /**< priority. */
        } priority;
        struct
        {
            bcmolt_presence_mask presence_mask;
            bcmolt_tm_weight weight; /**< weight. */
        } weight;
    } u;
} bcmolt_tm_sched_param;

/* Constants associated with bcmolt_tm_sched_param. */
#define BCMOLT_TM_SCHED_PARAM_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_TM_SCHED_PARAM_TYPE_DEFAULT BCMOLT_TM_SCHED_PARAM_TYPE_UNDEFINED
#define BCMOLT_TM_SCHED_PARAM_PRIORITY_PRESENCE_MASK_ALL 0x0000000000000004ULL
#define BCMOLT_TM_SCHED_PARAM_WEIGHT_PRESENCE_MASK_ALL 0x0000000000000002ULL
#define BCMOLT_TM_SCHED_PARAM_WEIGHT_WEIGHT_MIN (bcmolt_tm_weight)1
#define BCMOLT_TM_SCHED_PARAM_WEIGHT_WEIGHT_MAX (bcmolt_tm_weight)63

/** TM Scheduler Attachment Point (Output) */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_tm_sched_output_type type; /**< Output type */
    union
    {
        struct
        {
            bcmolt_presence_mask presence_mask;
            bcmolt_intf_ref interface_ref; /**< interface reference */
        } interface;
        struct
        {
            bcmolt_presence_mask presence_mask;
            uint32_t tm_sched_id; /**< Output tm sched id */
            bcmolt_tm_sched_param tm_sched_param; /**< TM Sched Param. */
        } tm_sched;
    } u;
} bcmolt_tm_sched_attachment_point;

/* Constants associated with bcmolt_tm_sched_attachment_point. */
#define BCMOLT_TM_SCHED_ATTACHMENT_POINT_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_TM_SCHED_ATTACHMENT_POINT_INTERFACE_PRESENCE_MASK_ALL 0x0000000000000001ULL
#define BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** Shaping Parameters */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint32_t cir; /**< Committed Information Rate (kbps) */
    uint32_t pir; /**< Peak Information Rate (kbps) */
    uint32_t burst; /**< Max Burst Bytes at Peak Bit Rate */
} bcmolt_tm_shaping;

/* Constants associated with bcmolt_tm_shaping. */
#define BCMOLT_TM_SHAPING_PRESENCE_MASK_ALL 0x0000000000000007ULL

/** The maps a logical intf to mac device+physical intf and other user specified configs for that line */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_ldid local_device_id; /**< Local MAC device Id in OLT line card */
    bcmolt_odid olt_device_id; /**< This device ID is what user would use for MAC device Ids in Aspen APIs */
    bcmolt_interface_id physical_if_id; /**< physical PON interface Id on the MAC device */
    bcmolt_str_16 user_string; /**< user specified string in topology config line */
} bcmolt_topology_map;

/* Constants associated with bcmolt_topology_map. */
#define BCMOLT_TOPOLOGY_MAP_PRESENCE_MASK_ALL 0x000000000000001EULL

/** Variable-length list of topology_map */
typedef struct
{
    uint32_t len; /**< List length. */
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    bcmolt_topology_map *arr; /**< List contents. */
} bcmolt_topology_map_list_u32;

/** system topology */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint8_t num_switch_ports; /**< The number of nni ports on switch device associated with the OLT */
    bcmolt_topology_map_list_u32 topology_maps; /**< Variable list of mappings between logical intf to mac device and physical intf along with other user specified configs */
} bcmolt_topology;

/* Constants associated with bcmolt_topology. */
#define BCMOLT_TOPOLOGY_PRESENCE_MASK_ALL 0x0000000000000003ULL

/** The attribute enables a feature where packets matching a certain pattern are trapped to the host
  * via an indication mechanism. */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    uint16_t tpid; /**< The TPID to match for trapped packets. */
    bcmolt_vlan_id vlan_id; /**< The VLAN to match */
    bcmolt_vlan_id vlan_mask; /**< Optional VLAN mask. */
    uint8_t cfi; /**< CFI to match. */
    uint8_t pbits; /**< Priority Bits to match. */
    bcmos_bool enable; /**< Enable the packet trapping to host.. */
} bcmolt_trap_config;

/* Constants associated with bcmolt_trap_config. */
#define BCMOLT_TRAP_CONFIG_PRESENCE_MASK_ALL 0x000000000000009FULL
#define BCMOLT_TRAP_CONFIG_VLAN_MASK_DEFAULT (bcmolt_vlan_id)65535U
#define BCMOLT_TRAP_CONFIG_VLAN_MASK_MIN (bcmolt_vlan_id)0U

/** Variable-length list of U64 */
typedef struct
{
    uint32_t len; /**< List length. */
    bcmolt_presence_mask arr_index_mask; /**< Bitmask of present array element indices. */
    uint64_t *arr; /**< List contents. */
} bcmolt_u64_list_u32_hex;

/** XGPON ONU alarms */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_status losi; /**< LOSi. */
    bcmolt_status lobi; /**< LOBi. */
    bcmolt_status lopci_miss; /**< LOPCi miss. */
    bcmolt_status lopci_mic_error; /**< LOPCi mic error. */
} bcmolt_xgpon_onu_alarms;

/* Constants associated with bcmolt_xgpon_onu_alarms. */
#define BCMOLT_XGPON_ONU_ALARMS_PRESENCE_MASK_ALL 0x000000000000000FULL

/** xgpon trx */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_arr_xgpon_burst_profile_4 burst_profile; /**< burst profile. */
    bcmolt_xgpon_trx_type transceiver_type; /**< trx type. */
} bcmolt_xgpon_trx;

/* Constants associated with bcmolt_xgpon_trx. */
#define BCMOLT_XGPON_TRX_PRESENCE_MASK_ALL 0x0000000000000005ULL
#define BCMOLT_XGPON_TRX_BURST_PROFILE_LENGTH 4
#define BCMOLT_XGPON_TRX_TRANSCEIVER_TYPE_DEFAULT BCMOLT_XGPON_TRX_TYPE_LTH_7222_PC



/** @} */

#endif
