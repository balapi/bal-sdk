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

#include "bcmolt_metadata_utils.h"

char *bcmolt_enum_stringval_multi(char *str, uint32_t size, uint32_t bits, const bcmolt_enum_val *table)
{
    uint32_t event;
    uint32_t shift;
    uint32_t is_first = BCMOS_TRUE;
    uint32_t pos = 0;

    *str = 0;
    while ((shift = ffs(bits)))
    {
        const char *event_str;
        uint32_t n;

        shift--;
        event = 1 << shift;
        bits &= ~event;
        event_str = bcmolt_enum_stringval(table, event);

        n = snprintf(str + pos, size, "%s%s", is_first ? "" : "|", event_str);
        pos += n;
        size -= n;
        is_first = BCMOS_FALSE;
    }

    return str;
}

