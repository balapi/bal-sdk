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

/* bcmolt_presence_mask.h:
 * Definitions/utilities related to presence masks.
 */

#ifndef BCMOLT_PRESENCE_MASK_H_
#define BCMOLT_PRESENCE_MASK_H_

#include <bcmos_system.h>

/** Bitmask of fields that are present in a message/struct/array. */
typedef uint64_t bcmolt_presence_mask;

/** Presence mask indicating all fields present. For structures/arrays, 0 also means all fields present. */
#define BCMOLT_PRESENCE_MASK_ALL ((bcmolt_presence_mask)0xFFFFFFFFFFFFFFFF)

#endif
