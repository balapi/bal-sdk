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

#ifndef BCMOLT_SYSTEM_TYPES_ENUMS_H_
#define BCMOLT_SYSTEM_TYPES_ENUMS_H_

#include <bcmos_system.h>

/** \addtogroup object_model
 * @{
 */

/** Host-Device Connection Type. */
typedef enum
{
    BCMOLT_CONN_TYPE__BEGIN = 0,
    BCMOLT_CONN_TYPE_MUX = 0, /**< Conection between MAC device and Device Control Daemon */
    BCMOLT_CONN_TYPE_APP = 1, /**< Connection initiated by an application */
    BCMOLT_CONN_TYPE_FAST = 2, /**< Fast API connection */
    BCMOLT_CONN_TYPE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_conn_type;

/** 1<<bcmolt_conn_type */
typedef enum
{
    BCMOLT_CONN_TYPE_MASK__BEGIN = 1,
    BCMOLT_CONN_TYPE_MASK_MUX = 1, /**< Conection between MAC device and Device Control Daemon */
    BCMOLT_CONN_TYPE_MASK_APP = 2, /**< Connection initiated by an application */
    BCMOLT_CONN_TYPE_MASK_FAST = 4, /**< Fast API Connection */
    BCMOLT_CONN_TYPE_MASK__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_conn_type_mask;

/** energy detect source. */
typedef enum
{
    BCMOLT_ENERGY_DETECT_SOURCE__BEGIN = 0,
    BCMOLT_ENERGY_DETECT_SOURCE_INTERNAL = 0, /**< internal. */
    BCMOLT_ENERGY_DETECT_SOURCE_TRX = 1, /**< TRX. */
    BCMOLT_ENERGY_DETECT_SOURCE_BCDR = 2, /**< BCDR. */
    BCMOLT_ENERGY_DETECT_SOURCE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_energy_detect_source;

/** EPON link rate. */
typedef enum
{
    BCMOLT_EPON_LINK_RATE__BEGIN = 0,
    BCMOLT_EPON_LINK_RATE_TEN_TEN = 0, /**< 10/10. */
    BCMOLT_EPON_LINK_RATE_TEN_ONE = 1, /**< 10/1. */
    BCMOLT_EPON_LINK_RATE_ONE_ONE = 2, /**< 1/1. */
    BCMOLT_EPON_LINK_RATE_TWENTY_FIVE_TWENTY_FIVE = 3, /**< 25/25. */
    BCMOLT_EPON_LINK_RATE_TWENTY_FIVE_TEN = 4, /**< 25/10. */
    BCMOLT_EPON_LINK_RATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_epon_link_rate;

/** EPON flow control mode. */
typedef enum
{
    BCMOLT_FLOW_CONTROL_MODE__BEGIN = 0,
    BCMOLT_FLOW_CONTROL_MODE_FLOW_CONTROL_NONE = 0, /**< No flow control of any kind. */
    BCMOLT_FLOW_CONTROL_MODE_PAUSE = 1, /**< Pause type flow control */
    BCMOLT_FLOW_CONTROL_MODE_PFC = 2, /**< PFC type flow control */
    BCMOLT_FLOW_CONTROL_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_flow_control_mode;

/** IEEE Demo ONU LLID Speed. */
typedef enum
{
    BCMOLT_IEEE_DEMO_ONU_LLID_RATE__BEGIN = 0,
    BCMOLT_IEEE_DEMO_ONU_LLID_RATE_DISABLE = 0, /**< LLID is disabled (add support for additional ULID). */
    BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_25G = 1, /**< LLID is enabled at 25G rate. */
    BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G = 2, /**< LLID is enabled at 10G rate. */
    BCMOLT_IEEE_DEMO_ONU_LLID_RATE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ieee_demo_onu_llid_rate;

/** IEEE Demo ONU Loopback Mode. */
typedef enum
{
    BCMOLT_IEEE_DEMO_ONU_LOOPBACK_MODE__BEGIN = 0,
    BCMOLT_IEEE_DEMO_ONU_LOOPBACK_MODE_NONE = 0, /**< No loopback */
    BCMOLT_IEEE_DEMO_ONU_LOOPBACK_MODE_MPRS = 1, /**< MPRS loopback in both directions */
    BCMOLT_IEEE_DEMO_ONU_LOOPBACK_MODE_DOWNSTREAM_PCS = 2, /**< PCS loopback downstream, MPRS upstream */
    BCMOLT_IEEE_DEMO_ONU_LOOPBACK_MODE_UPSTREAM_PCS = 3, /**< PCS loopback upstrea, MPRS downstream */
    BCMOLT_IEEE_DEMO_ONU_LOOPBACK_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_ieee_demo_onu_loopback_mode;

/** INNI mode for the system */
typedef enum
{
    BCMOLT_INNI_MODE__BEGIN = 0,
    BCMOLT_INNI_MODE_ALL_1_G = 0, /**< INNI ports set to 1Gbps. */
    BCMOLT_INNI_MODE_ALL_2_P_5_G = 1, /**< INNI ports set to 2.5Gbps. */
    BCMOLT_INNI_MODE_ALL_10_G_XFI = 2, /**< INNI ports set to 10Gbps (XFI). */
    BCMOLT_INNI_MODE_ALL_10_G_KR = 3, /**< INNI ports set to 10Gbps (KR). */
    BCMOLT_INNI_MODE_ALL_10_G_SFI = 4, /**< INNI ports set to 10Gbps (SFI). */
    BCMOLT_INNI_MODE_ALL_12_P_5_G = 5, /**< INNI ports set to 12.5Gbps. */
    BCMOLT_INNI_MODE_ALL_25_G_XFI = 6, /**< INNI ports set to 25Gbps (XFI). */
    BCMOLT_INNI_MODE_ALL_25_G_KR = 7, /**< INNI ports set to 25Gbps (KR). */
    BCMOLT_INNI_MODE_HALF_10_G_HALF_2_P_5_G = 8, /**< INNI ports, first half 10Gbps and second half 2.5Gbps. */
    BCMOLT_INNI_MODE_ALL_25_G_CR = 9, /**< INNI ports set to 25Gbps (CR). */
    BCMOLT_INNI_MODE__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_inni_mode;

/** Indicate type of multiplexing on INNI */
typedef enum
{
    BCMOLT_INNI_MUX__BEGIN = 0,
    BCMOLT_INNI_MUX_NONE = 0, /**< No Multiplexing. */
    BCMOLT_INNI_MUX_FOUR_TO_ONE = 1, /**< 4:1 Multiplexing. */
    BCMOLT_INNI_MUX_TWO_TO_ONE = 2, /**< 2:1 Multiplexing. */
    BCMOLT_INNI_MUX_FOUR_TO_ONE_IN_VLAN = 3, /**< 4:1 pon tag in vlan */
    BCMOLT_INNI_MUX_TWO_TO_ONE_IN_VLAN = 4, /**< 2:1 pon tag in vlan */
    BCMOLT_INNI_MUX__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */
} bcmolt_inni_mux;

/** Identifiers for all fields in a 'ieee_demo_onu_llid_support'. */
typedef enum
{
    BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID__BEGIN = 0,
    BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID_PLID = 0, /**< PLID. */
    BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID_MLID = 1, /**< MLID. */
    BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID_BCAST_PLID = 2, /**< BCAST_PLID. */
    BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID_BCAST_MLID = 3, /**< BCAST_MLID. */
    BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID__NUM_OF, /**< Constant to use for sizing arrays - note that enum may have holes. */

    /* Lower-case versions for macro support. */
#define bcmolt_ieee_demo_onu_llid_support_id__begin BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID__BEGIN
#define bcmolt_ieee_demo_onu_llid_support_id_plid BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID_PLID
#define bcmolt_ieee_demo_onu_llid_support_id_mlid BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID_MLID
#define bcmolt_ieee_demo_onu_llid_support_id_bcast_plid BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID_BCAST_PLID
#define bcmolt_ieee_demo_onu_llid_support_id_bcast_mlid BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID_BCAST_MLID
#define bcmolt_ieee_demo_onu_llid_support_id__num_of BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_ID__NUM_OF
#define bcmolt_ieee_demo_onu_llid_support_id_all_properties 0xFF
#define bcmolt_ieee_demo_onu_llid_support_id_full_mask 0xF

} bcmolt_ieee_demo_onu_llid_support_id;



/** @} */

#endif
