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
#include <bcmolt_string.h>
#include "bcmolt_system_types_struct_funcs.h"
#include "bcmolt_system_types_enum_funcs.h"

void bcmolt_ieee_demo_onu_llid_support_set_default(
    bcmolt_ieee_demo_onu_llid_support *p_obj)
{
    p_obj->plid = BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G;
    p_obj->mlid = BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G;
    p_obj->bcast_plid = BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G;
    p_obj->bcast_mlid = BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G;
}

bcmos_bool bcmolt_ieee_demo_onu_llid_support_pack(
    const bcmolt_ieee_demo_onu_llid_support *p_obj,
    bcmolt_buf *p_buf)
{
    if (!bcmolt_ieee_demo_onu_llid_rate_pack(p_obj->plid, p_buf))
    {
        return BCMOS_FALSE;
    }
    if (!bcmolt_ieee_demo_onu_llid_rate_pack(p_obj->mlid, p_buf))
    {
        return BCMOS_FALSE;
    }
    if (!bcmolt_ieee_demo_onu_llid_rate_pack(p_obj->bcast_plid, p_buf))
    {
        return BCMOS_FALSE;
    }
    if (!bcmolt_ieee_demo_onu_llid_rate_pack(p_obj->bcast_mlid, p_buf))
    {
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_ieee_demo_onu_llid_support_unpack(
    bcmolt_ieee_demo_onu_llid_support *p_obj,
    bcmolt_buf *p_buf,
    void **p_extra_mem)
{
    if (!bcmolt_ieee_demo_onu_llid_rate_unpack(&p_obj->plid, p_buf))
    {
        return BCMOS_FALSE;
    }
    if (!bcmolt_ieee_demo_onu_llid_rate_unpack(&p_obj->mlid, p_buf))
    {
        return BCMOS_FALSE;
    }
    if (!bcmolt_ieee_demo_onu_llid_rate_unpack(&p_obj->bcast_plid, p_buf))
    {
        return BCMOS_FALSE;
    }
    if (!bcmolt_ieee_demo_onu_llid_rate_unpack(&p_obj->bcast_mlid, p_buf))
    {
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

bcmos_bool bcmolt_ieee_demo_onu_llid_support_validate(
    const bcmolt_ieee_demo_onu_llid_support *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    switch (p_obj->plid)
    {
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_DISABLE:
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_25G:
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "plid: enum value %d is unexpected\n", (int)p_obj->plid);
        return BCMOS_FALSE;
    }
    switch (p_obj->mlid)
    {
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_DISABLE:
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_25G:
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "mlid: enum value %d is unexpected\n", (int)p_obj->mlid);
        return BCMOS_FALSE;
    }
    switch (p_obj->bcast_plid)
    {
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_DISABLE:
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_25G:
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "bcast_plid: enum value %d is unexpected\n", (int)p_obj->bcast_plid);
        return BCMOS_FALSE;
    }
    switch (p_obj->bcast_mlid)
    {
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_DISABLE:
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_25G:
    case BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "bcast_mlid: enum value %d is unexpected\n", (int)p_obj->bcast_mlid);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}


