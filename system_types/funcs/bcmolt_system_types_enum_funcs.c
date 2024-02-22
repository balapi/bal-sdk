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

#include <bcmos_system.h>
#include <bcmolt_buf.h>
#include "bcmolt_system_types_enum_funcs.h"

bcmos_bool bcmolt_conn_type_pack(
    bcmolt_conn_type obj,
    bcmolt_buf *p_buf)
{
    return bcmolt_buf_write_u8(p_buf, (uint8_t)obj);
}

bcmos_bool bcmolt_conn_type_unpack(
    bcmolt_conn_type *p_obj,
    bcmolt_buf *p_buf)
{
    uint8_t num_val;
    if (!bcmolt_buf_read_u8(p_buf, &num_val))
    {
        return BCMOS_FALSE;
    }
    *p_obj = (bcmolt_conn_type)num_val;
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_conn_type_mask_pack(
    bcmolt_conn_type_mask obj,
    bcmolt_buf *p_buf)
{
    return bcmolt_buf_write_u8(p_buf, (uint8_t)obj);
}

bcmos_bool bcmolt_conn_type_mask_unpack(
    bcmolt_conn_type_mask *p_obj,
    bcmolt_buf *p_buf)
{
    uint8_t num_val;
    if (!bcmolt_buf_read_u8(p_buf, &num_val))
    {
        return BCMOS_FALSE;
    }
    *p_obj = (bcmolt_conn_type_mask)num_val;
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_energy_detect_source_pack(
    bcmolt_energy_detect_source obj,
    bcmolt_buf *p_buf)
{
    return bcmolt_buf_write_u8(p_buf, (uint8_t)obj);
}

bcmos_bool bcmolt_energy_detect_source_unpack(
    bcmolt_energy_detect_source *p_obj,
    bcmolt_buf *p_buf)
{
    uint8_t num_val;
    if (!bcmolt_buf_read_u8(p_buf, &num_val))
    {
        return BCMOS_FALSE;
    }
    *p_obj = (bcmolt_energy_detect_source)num_val;
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_epon_link_rate_pack(
    bcmolt_epon_link_rate obj,
    bcmolt_buf *p_buf)
{
    return bcmolt_buf_write_u16(p_buf, (uint16_t)obj);
}

bcmos_bool bcmolt_epon_link_rate_unpack(
    bcmolt_epon_link_rate *p_obj,
    bcmolt_buf *p_buf)
{
    uint16_t num_val;
    if (!bcmolt_buf_read_u16(p_buf, &num_val))
    {
        return BCMOS_FALSE;
    }
    *p_obj = (bcmolt_epon_link_rate)num_val;
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_flow_control_mode_pack(
    bcmolt_flow_control_mode obj,
    bcmolt_buf *p_buf)
{
    return bcmolt_buf_write_u16(p_buf, (uint16_t)obj);
}

bcmos_bool bcmolt_flow_control_mode_unpack(
    bcmolt_flow_control_mode *p_obj,
    bcmolt_buf *p_buf)
{
    uint16_t num_val;
    if (!bcmolt_buf_read_u16(p_buf, &num_val))
    {
        return BCMOS_FALSE;
    }
    *p_obj = (bcmolt_flow_control_mode)num_val;
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_ieee_demo_onu_llid_rate_pack(
    bcmolt_ieee_demo_onu_llid_rate obj,
    bcmolt_buf *p_buf)
{
    return bcmolt_buf_write_u8(p_buf, (uint8_t)obj);
}

bcmos_bool bcmolt_ieee_demo_onu_llid_rate_unpack(
    bcmolt_ieee_demo_onu_llid_rate *p_obj,
    bcmolt_buf *p_buf)
{
    uint8_t num_val;
    if (!bcmolt_buf_read_u8(p_buf, &num_val))
    {
        return BCMOS_FALSE;
    }
    *p_obj = (bcmolt_ieee_demo_onu_llid_rate)num_val;
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_ieee_demo_onu_loopback_mode_pack(
    bcmolt_ieee_demo_onu_loopback_mode obj,
    bcmolt_buf *p_buf)
{
    return bcmolt_buf_write_u8(p_buf, (uint8_t)obj);
}

bcmos_bool bcmolt_ieee_demo_onu_loopback_mode_unpack(
    bcmolt_ieee_demo_onu_loopback_mode *p_obj,
    bcmolt_buf *p_buf)
{
    uint8_t num_val;
    if (!bcmolt_buf_read_u8(p_buf, &num_val))
    {
        return BCMOS_FALSE;
    }
    *p_obj = (bcmolt_ieee_demo_onu_loopback_mode)num_val;
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_inni_mode_pack(
    bcmolt_inni_mode obj,
    bcmolt_buf *p_buf)
{
    return bcmolt_buf_write_u8(p_buf, (uint8_t)obj);
}

bcmos_bool bcmolt_inni_mode_unpack(
    bcmolt_inni_mode *p_obj,
    bcmolt_buf *p_buf)
{
    uint8_t num_val;
    if (!bcmolt_buf_read_u8(p_buf, &num_val))
    {
        return BCMOS_FALSE;
    }
    *p_obj = (bcmolt_inni_mode)num_val;
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_inni_mux_pack(
    bcmolt_inni_mux obj,
    bcmolt_buf *p_buf)
{
    return bcmolt_buf_write_u8(p_buf, (uint8_t)obj);
}

bcmos_bool bcmolt_inni_mux_unpack(
    bcmolt_inni_mux *p_obj,
    bcmolt_buf *p_buf)
{
    uint8_t num_val;
    if (!bcmolt_buf_read_u8(p_buf, &num_val))
    {
        return BCMOS_FALSE;
    }
    *p_obj = (bcmolt_inni_mux)num_val;
    return BCMOS_TRUE;
}


