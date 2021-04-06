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

#ifndef BCMOLT_SYSTEM_TYPES_TYPEDEFS_H_
#define BCMOLT_SYSTEM_TYPES_TYPEDEFS_H_

#include <bcmos_system.h>

/** \addtogroup object_model
 * @{
 */

/** bcmolt_alloc_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_alloc_id;
#define BCMOLT_ALLOC_ID_INVALID ((bcmolt_alloc_id)65535U)
#define BCMOLT_ALLOC_ID_MIN ((bcmolt_alloc_id)0)
#define BCMOLT_ALLOC_ID_MAX ((bcmolt_alloc_id)16383)

/** bcmolt_devid: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_devid;

/** bcmolt_flow_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_flow_id;
#define BCMOLT_FLOW_ID_MIN ((bcmolt_flow_id)0)
#define BCMOLT_FLOW_ID_MAX ((bcmolt_flow_id)65535U)

/** bcmolt_gem_port_id: Typed alias for a 32-bit unsigned integer. */
typedef uint32_t bcmolt_gem_port_id;
#define BCMOLT_GEM_PORT_ID_NEXT_FREE ((bcmolt_gem_port_id)65536UL)
#define BCMOLT_GEM_PORT_ID_INVALID ((bcmolt_gem_port_id)65535UL)
#define BCMOLT_GEM_PORT_ID_MIN ((bcmolt_gem_port_id)0)
#define BCMOLT_GEM_PORT_ID_MAX ((bcmolt_gem_port_id)65536UL)

/** bcmolt_interface: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_interface;
#define BCMOLT_INTERFACE_UNDEFINED ((bcmolt_interface)255)

/** bcmolt_iwf_flow_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_iwf_flow_id;
#define BCMOLT_IWF_FLOW_ID_MIN ((bcmolt_iwf_flow_id)0)
#define BCMOLT_IWF_FLOW_ID_MAX ((bcmolt_iwf_flow_id)8192)

/** bcmolt_ldid: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_ldid;
#define BCMOLT_LDID_UNDEFINED ((bcmolt_ldid)255)

/** bcmolt_loid: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_loid;
#define BCMOLT_LOID_UNDEFINED ((bcmolt_loid)255)

/** bcmolt_mac_table_idx_cam: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_mac_table_idx_cam;
#define BCMOLT_MAC_TABLE_IDX_CAM_NONE ((bcmolt_mac_table_idx_cam)255)
#define BCMOLT_MAC_TABLE_IDX_CAM_MIN ((bcmolt_mac_table_idx_cam)0)
#define BCMOLT_MAC_TABLE_IDX_CAM_MAX ((bcmolt_mac_table_idx_cam)63)

/** bcmolt_mac_table_idx_main: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_mac_table_idx_main;
#define BCMOLT_MAC_TABLE_IDX_MAIN_MIN ((bcmolt_mac_table_idx_main)0)
#define BCMOLT_MAC_TABLE_IDX_MAIN_MAX ((bcmolt_mac_table_idx_main)4096)

/** bcmolt_nni_id: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_nni_id;
#define BCMOLT_NNI_ID_INVALID ((bcmolt_nni_id)255)

/** bcmolt_odid: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_odid;
#define BCMOLT_ODID_UNDEFINED ((bcmolt_odid)255)

/** bcmolt_oltid: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_oltid;

/** bcmolt_onu_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_onu_id;
#define BCMOLT_ONU_ID_INVALID ((bcmolt_onu_id)65535U)
#define BCMOLT_ONU_ID_NEXT_FREE ((bcmolt_onu_id)65534U)
#define BCMOLT_ONU_ID_MIN ((bcmolt_onu_id)0)
#define BCMOLT_ONU_ID_MAX ((bcmolt_onu_id)65535U)

/** bcmolt_pon_ni: Typed alias for a 8-bit unsigned integer. */
typedef uint8_t bcmolt_pon_ni;
#define BCMOLT_PON_NI_INVALID ((bcmolt_pon_ni)255)
#define BCMOLT_PON_NI_ALL ((bcmolt_pon_ni)254)
#define BCMOLT_PON_NI_MIN ((bcmolt_pon_ni)0)
#define BCMOLT_PON_NI_MAX ((bcmolt_pon_ni)15)

/** bcmolt_vlan_id: Typed alias for a 16-bit unsigned integer. */
typedef uint16_t bcmolt_vlan_id;
#define BCMOLT_VLAN_ID_MAX ((bcmolt_vlan_id)4095)
#define BCMOLT_VLAN_ID_ANY ((bcmolt_vlan_id)65535U)
#define BCMOLT_VLAN_ID_MIN ((bcmolt_vlan_id)0)



/** @} */

#endif
