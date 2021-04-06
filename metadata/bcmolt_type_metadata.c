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

#include <bcmos_system.h>
#include "bcmolt_type_metadata.h"

int bcmolt_get_num_enum_vals(const bcmolt_enum_val *vals)
{
    const bcmolt_enum_val *v = vals;
    while (v && v->name)
    {
        ++v;
    }
    return (v - vals);
}

const bcmolt_type_descr type_descr_uint8_t =
{
    .name = "uint8",
    .base_type = BCMOLT_BASE_TYPE_ID_UNUM,
    .size = sizeof(uint8_t)
};

const bcmolt_type_descr type_descr_uint16_t =
{
    .name = "uint16",
    .base_type = BCMOLT_BASE_TYPE_ID_UNUM,
    .size = sizeof(uint16_t)
};

const bcmolt_type_descr type_descr_uint32_t =
{
    .name = "uint32",
    .base_type = BCMOLT_BASE_TYPE_ID_UNUM,
    .size = sizeof(uint32_t)
};

const bcmolt_type_descr type_descr_uint64_t =
{
    .name = "uint64",
    .base_type = BCMOLT_BASE_TYPE_ID_UNUM,
    .size = sizeof(uint64_t)
};

const bcmolt_type_descr type_descr_uint8_t_hex =
{
    .name = "uint8_hex",
    .base_type = BCMOLT_BASE_TYPE_ID_UNUM_HEX,
    .size = sizeof(uint8_t)
};

const bcmolt_type_descr type_descr_uint16_t_hex =
{
    .name = "uint16_hex",
    .base_type = BCMOLT_BASE_TYPE_ID_UNUM_HEX,
    .size = sizeof(uint16_t)
};

const bcmolt_type_descr type_descr_uint32_t_hex =
{
    .name = "uint32_hex",
    .base_type = BCMOLT_BASE_TYPE_ID_UNUM_HEX,
    .size = sizeof(uint32_t)
};

const bcmolt_type_descr type_descr_uint64_t_hex =
{
    .name = "uint64_hex",
    .base_type = BCMOLT_BASE_TYPE_ID_UNUM_HEX,
    .size = sizeof(uint64_t)
};

const bcmolt_type_descr type_descr_int8_t =
{
    .name = "int8",
    .base_type = BCMOLT_BASE_TYPE_ID_SNUM,
    .size = sizeof(int8_t)
};

const bcmolt_type_descr type_descr_int16_t =
{
    .name = "int16",
    .base_type = BCMOLT_BASE_TYPE_ID_SNUM,
    .size = sizeof(int16_t)
};

const bcmolt_type_descr type_descr_int32_t =
{
    .name = "int32",
    .base_type = BCMOLT_BASE_TYPE_ID_SNUM,
    .size = sizeof(int32_t)
};

const bcmolt_type_descr type_descr_int64_t =
{
    .name = "int64",
    .base_type = BCMOLT_BASE_TYPE_ID_SNUM,
    .size = sizeof(int64_t)
};

const bcmolt_type_descr type_descr_float =
{
    .name = "float",
    .base_type = BCMOLT_BASE_TYPE_ID_FLOAT,
    .size = sizeof(float)
};

const bcmolt_type_descr type_descr_double =
{
    .name = "double",
    .base_type = BCMOLT_BASE_TYPE_ID_FLOAT,
    .size = sizeof(double)
};

const bcmolt_type_descr type_descr_bcmos_mac_address =
{
    .name = "mac",
    .descr = "MAC address",
    .base_type = BCMOLT_BASE_TYPE_ID_MAC,
    .size = sizeof(bcmos_mac_address)
};

const bcmolt_type_descr type_descr_bcmos_ipv4_address =
{
    .name = "ipv4",
    .descr = "IPv4 address",
    .base_type = BCMOLT_BASE_TYPE_ID_IPV4,
    .size = sizeof(bcmos_ipv4_address)
};

const bcmolt_type_descr type_descr_bcmos_ipv6_address =
{
    .name = "ipv6",
    .descr = "IPv6 address",
    .base_type = BCMOLT_BASE_TYPE_ID_IPV6,
    .size = sizeof(bcmos_ipv6_address)
};

const bcmolt_type_descr type_descr_bcmos_bool =
{
    .name = "bool",
    .descr = "Boolean",
    .base_type = BCMOLT_BASE_TYPE_ID_BOOL,
    .size = sizeof(bcmos_bool)
};
