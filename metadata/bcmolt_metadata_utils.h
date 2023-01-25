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
#ifndef BCMOLT_METADATA_UTILS_H_
#define BCMOLT_METADATA_UTILS_H_

/* bcmolt_metadata_utils.h
 * Utility functions for metadata module.
 */

#include <bcmos_system.h>
#include "bcmolt_set_metadata.h"
#include "bcmolt_type_metadata.h"

/* Build a human readable string from multiple bit values (e.g. "buffer_swap|quiet_window"). */
char *bcmolt_enum_stringval_multi(char *str, uint32_t size, uint32_t bits, const bcmolt_enum_val *table);

#endif /* BCMOLT_METADATA_UTILS_H_ */
