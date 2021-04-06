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

#ifndef BCMOLT_API_MODEL_INTERNAL_H_
#define BCMOLT_API_MODEL_INTERNAL_H_

#include <bcmos_system.h>
#include <bcm_dev_log.h>

/* Internal macro: Check if a given bit is set in a structure presence mask */
#define _BCMOLT_FIELD_MASK_BIT_IS_SET(_mask, _field_id) \
    ((_mask == 0) || ((_mask & (uint64_t)(1ULL << _field_id))) ? BCMOS_TRUE : BCMOS_FALSE)

/* Internal macro: Set a given bit in a structure presence mask */
#define _BCMOLT_FIELD_MASK_BIT_SET(_mask, _field_id) \
    do {                                             \
        _mask |= (uint64_t)(1ULL << _field_id);      \
    } while(0)

/* Internal macro: Check if a given bit is set in an array index mask */
/* Note: array indices >63 cannot be covered by the index mask and are assumed to always be set. */
#define _BCMOLT_ARRAY_MASK_BIT_IS_SET(_mask, _idx) \
    ((_idx > 63) || (_mask == 0) || ((_mask & (1ULL << _idx)) ? BCMOS_TRUE : BCMOS_FALSE))

/* Internal macro: Check if a given bit is set in a group property mask */
#define _BCMOLT_PROPERTY_MASK_BIT_IS_SET(_mask, _prop_id) \
    ((_mask & (1ULL << (uint64_t)_prop_id)) ? BCMOS_TRUE : BCMOS_FALSE)

/* Internal macro: Log that an unknown field ID was enountered during unpack */
#define _BCMOLT_LOG_UNKNOWN_FIELD_ID(_type_name, _presence_mask, _unsupported_mask) \
    BCM_LOG(ERROR, \
        bcmolt_api_model_log_id_get(), \
        "%s: unsupported field ID %d\n", \
        _type_name, \
        ffsll((_presence_mask) & (_unsupported_mask)) - 1)

dev_log_id bcmolt_api_model_log_id_get(void);
void bcmolt_api_model_init(void);

#endif
