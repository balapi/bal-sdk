/*
<:copyright-BRCM:2016-2020:Apache:standard

 Copyright (c) 2016-2020 Broadcom. All Rights Reserved

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
#include "bcmolt_mgt_group.h"

const char *bcmolt_mgt_group_to_str(bcmolt_mgt_group group)
{
    static const char *str_table[BCMOLT_MGT_GROUP__NUM_OF] =
    {
        [BCMOLT_MGT_GROUP_KEY]      = "key",
        [BCMOLT_MGT_GROUP_CFG]      = "cfg",
        [BCMOLT_MGT_GROUP_STAT]     = "stat",
        [BCMOLT_MGT_GROUP_STAT_CFG] = "stat_cfg",
        [BCMOLT_MGT_GROUP_AUTO]     = "auto",
        [BCMOLT_MGT_GROUP_AUTO_CFG] = "auto_cfg",
        [BCMOLT_MGT_GROUP_OPER]     = "oper",
    };
    return (group >= BCMOLT_MGT_GROUP__NUM_OF) ? "<unknown>" : str_table[group];
}
