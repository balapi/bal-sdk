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

/* system_types_common.h: commonly used platform agnostic data types */

#ifndef SYSTEM_TYPES_COMMON_H_
#define SYSTEM_TYPES_COMMON_H_

#include <bcmos_system.h>

/** Indication message type mask - high bits indicate message types that will be forwarded to the host.
 *
 * Bit positions correspond to the xxx_auto_id enum from the object model (e.g. bcmolt_gpon_ni_auto_id).
 */
typedef uint64_t ind_msg_mask;

typedef enum
{
    BCMOLT_PON_STD_TYPE_INVALID,
    BCMOLT_PON_STD_TYPE_ITU,    /* GPON, XGPON-1, XGS-PON, NGPON-2 */
    BCMOLT_PON_STD_TYPE_EPON,   /* 1G/2G/10G EPON */
    BCMOLT_PON_STD_TYPE_EPON_ONU,
    BCMOLT_PON_STD_TYPE_AE,     /* Active Ethernet */
    BCMOLT_PON_STD_TYPE_AE_ONU,

    BCMOLT_PON_STD_TYPE_COUNT,
    BCMOLT_PON_STD_TYPE_ANY = BCMOLT_PON_STD_TYPE_COUNT,
    BCMOLT_PON_STD_TYPE_NONE
} bcmolt_pon_std_type;

#endif
