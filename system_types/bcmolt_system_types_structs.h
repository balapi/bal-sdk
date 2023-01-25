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

#ifndef BCMOLT_SYSTEM_TYPES_STRUCTS_H_
#define BCMOLT_SYSTEM_TYPES_STRUCTS_H_

#include <bcmos_system.h>
#include <bcmolt_presence_mask.h>
#include "bcmolt_system_types_enums.h"
#include "bcmolt_system_types_typedefs.h"

/** \addtogroup object_model
 * @{
 */

/** IEEE Demo ONU LLID Support */
typedef struct
{
    bcmolt_presence_mask presence_mask;
    bcmolt_ieee_demo_onu_llid_rate plid; /**< PLID. */
    bcmolt_ieee_demo_onu_llid_rate mlid; /**< MLID. */
    bcmolt_ieee_demo_onu_llid_rate bcast_plid; /**< BCAST_PLID. */
    bcmolt_ieee_demo_onu_llid_rate bcast_mlid; /**< BCAST_MLID. */
} bcmolt_ieee_demo_onu_llid_support;

/* Constants associated with bcmolt_ieee_demo_onu_llid_support. */
#define BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_PRESENCE_MASK_ALL 0x000000000000000FULL
#define BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_PLID_DEFAULT BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G
#define BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_MLID_DEFAULT BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G
#define BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_BCAST_PLID_DEFAULT BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G
#define BCMOLT_IEEE_DEMO_ONU_LLID_SUPPORT_BCAST_MLID_DEFAULT BCMOLT_IEEE_DEMO_ONU_LLID_RATE_SPEED_10G



/** @} */

#endif
