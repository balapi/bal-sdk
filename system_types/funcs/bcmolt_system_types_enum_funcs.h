/*
<:copyright-BRCM:2018-2020:Apache:standard

 Copyright (c) 2018-2020 Broadcom. All Rights Reserved

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

:>
*/

#ifndef BCMOLT_SYSTEM_TYPES_ENUM_FUNCS_H_
#define BCMOLT_SYSTEM_TYPES_ENUM_FUNCS_H_

#include <bcmos_system.h>
#include <bcmolt_buf.h>
#include "bcmolt_system_types_enums.h"

/** Packs an enumeration to bytes for transmission on the wire.
  *
  * \param obj The enumeration to pack.
  * \param buf Pointer to the buffer to write to.
  * \return Whether or not the pack was successful.
  */
bcmos_bool bcmolt_conn_type_pack(
    bcmolt_conn_type obj,
    bcmolt_buf *buf);

/** Unpacks an enumeration from bytes as received on the wire.
  *
  * \param obj Pointer to the enumeration to unpack.
  * \param buf Pointer to the buffer to read from.
  * \return Whether or not the unpack was successful.
  */
bcmos_bool bcmolt_conn_type_unpack(
    bcmolt_conn_type *obj,
    bcmolt_buf *buf);

/** Packs an enumeration to bytes for transmission on the wire.
  *
  * \param obj The enumeration to pack.
  * \param buf Pointer to the buffer to write to.
  * \return Whether or not the pack was successful.
  */
bcmos_bool bcmolt_conn_type_mask_pack(
    bcmolt_conn_type_mask obj,
    bcmolt_buf *buf);

/** Unpacks an enumeration from bytes as received on the wire.
  *
  * \param obj Pointer to the enumeration to unpack.
  * \param buf Pointer to the buffer to read from.
  * \return Whether or not the unpack was successful.
  */
bcmos_bool bcmolt_conn_type_mask_unpack(
    bcmolt_conn_type_mask *obj,
    bcmolt_buf *buf);

/** Packs an enumeration to bytes for transmission on the wire.
  *
  * \param obj The enumeration to pack.
  * \param buf Pointer to the buffer to write to.
  * \return Whether or not the pack was successful.
  */
bcmos_bool bcmolt_energy_detect_source_pack(
    bcmolt_energy_detect_source obj,
    bcmolt_buf *buf);

/** Unpacks an enumeration from bytes as received on the wire.
  *
  * \param obj Pointer to the enumeration to unpack.
  * \param buf Pointer to the buffer to read from.
  * \return Whether or not the unpack was successful.
  */
bcmos_bool bcmolt_energy_detect_source_unpack(
    bcmolt_energy_detect_source *obj,
    bcmolt_buf *buf);

/** Packs an enumeration to bytes for transmission on the wire.
  *
  * \param obj The enumeration to pack.
  * \param buf Pointer to the buffer to write to.
  * \return Whether or not the pack was successful.
  */
bcmos_bool bcmolt_epon_link_rate_pack(
    bcmolt_epon_link_rate obj,
    bcmolt_buf *buf);

/** Unpacks an enumeration from bytes as received on the wire.
  *
  * \param obj Pointer to the enumeration to unpack.
  * \param buf Pointer to the buffer to read from.
  * \return Whether or not the unpack was successful.
  */
bcmos_bool bcmolt_epon_link_rate_unpack(
    bcmolt_epon_link_rate *obj,
    bcmolt_buf *buf);

/** Packs an enumeration to bytes for transmission on the wire.
  *
  * \param obj The enumeration to pack.
  * \param buf Pointer to the buffer to write to.
  * \return Whether or not the pack was successful.
  */
bcmos_bool bcmolt_flow_control_mode_pack(
    bcmolt_flow_control_mode obj,
    bcmolt_buf *buf);

/** Unpacks an enumeration from bytes as received on the wire.
  *
  * \param obj Pointer to the enumeration to unpack.
  * \param buf Pointer to the buffer to read from.
  * \return Whether or not the unpack was successful.
  */
bcmos_bool bcmolt_flow_control_mode_unpack(
    bcmolt_flow_control_mode *obj,
    bcmolt_buf *buf);

/** Packs an enumeration to bytes for transmission on the wire.
  *
  * \param obj The enumeration to pack.
  * \param buf Pointer to the buffer to write to.
  * \return Whether or not the pack was successful.
  */
bcmos_bool bcmolt_ieee_demo_onu_llid_rate_pack(
    bcmolt_ieee_demo_onu_llid_rate obj,
    bcmolt_buf *buf);

/** Unpacks an enumeration from bytes as received on the wire.
  *
  * \param obj Pointer to the enumeration to unpack.
  * \param buf Pointer to the buffer to read from.
  * \return Whether or not the unpack was successful.
  */
bcmos_bool bcmolt_ieee_demo_onu_llid_rate_unpack(
    bcmolt_ieee_demo_onu_llid_rate *obj,
    bcmolt_buf *buf);

/** Packs an enumeration to bytes for transmission on the wire.
  *
  * \param obj The enumeration to pack.
  * \param buf Pointer to the buffer to write to.
  * \return Whether or not the pack was successful.
  */
bcmos_bool bcmolt_ieee_demo_onu_loopback_mode_pack(
    bcmolt_ieee_demo_onu_loopback_mode obj,
    bcmolt_buf *buf);

/** Unpacks an enumeration from bytes as received on the wire.
  *
  * \param obj Pointer to the enumeration to unpack.
  * \param buf Pointer to the buffer to read from.
  * \return Whether or not the unpack was successful.
  */
bcmos_bool bcmolt_ieee_demo_onu_loopback_mode_unpack(
    bcmolt_ieee_demo_onu_loopback_mode *obj,
    bcmolt_buf *buf);

/** Packs an enumeration to bytes for transmission on the wire.
  *
  * \param obj The enumeration to pack.
  * \param buf Pointer to the buffer to write to.
  * \return Whether or not the pack was successful.
  */
bcmos_bool bcmolt_inni_mode_pack(
    bcmolt_inni_mode obj,
    bcmolt_buf *buf);

/** Unpacks an enumeration from bytes as received on the wire.
  *
  * \param obj Pointer to the enumeration to unpack.
  * \param buf Pointer to the buffer to read from.
  * \return Whether or not the unpack was successful.
  */
bcmos_bool bcmolt_inni_mode_unpack(
    bcmolt_inni_mode *obj,
    bcmolt_buf *buf);

/** Packs an enumeration to bytes for transmission on the wire.
  *
  * \param obj The enumeration to pack.
  * \param buf Pointer to the buffer to write to.
  * \return Whether or not the pack was successful.
  */
bcmos_bool bcmolt_inni_mux_pack(
    bcmolt_inni_mux obj,
    bcmolt_buf *buf);

/** Unpacks an enumeration from bytes as received on the wire.
  *
  * \param obj Pointer to the enumeration to unpack.
  * \param buf Pointer to the buffer to read from.
  * \return Whether or not the unpack was successful.
  */
bcmos_bool bcmolt_inni_mux_unpack(
    bcmolt_inni_mux *obj,
    bcmolt_buf *buf);



#endif
