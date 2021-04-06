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

#ifndef BCMOLT_SYSTEM_TYPES_STRUCT_FUNCS_H_
#define BCMOLT_SYSTEM_TYPES_STRUCT_FUNCS_H_

#include <bcmos_system.h>
#include <bcmolt_buf.h>
#include <bcmolt_string.h>
#include "bcmolt_system_types_structs.h"

/** Initializes a structure to default values.
 *
 * \param obj Pointer to the structure to initialize.
 */
void bcmolt_ieee_demo_onu_llid_support_set_default(bcmolt_ieee_demo_onu_llid_support *obj);

/** Packs a structure to bytes for transmission on the wire.
 *
 * \param obj Pointer to the structure to pack.
 * \param buf Pointer to the buffer to write to.
 * \return TRUE if the pack was successful, FALSE otherwise.
 */
bcmos_bool bcmolt_ieee_demo_onu_llid_support_pack(const bcmolt_ieee_demo_onu_llid_support *obj, bcmolt_buf *buf);

/** Unpacks a structure from bytes as received on the wire.
 *
 * \param obj Pointer to the structure to unpack.
 * \param buf Pointer to the buffer to read from.
 * \param extra_mem Pointer to the first location in memory to use to store pointer fields that are
 *        NULL. Setting obj to NULL will cause an error when a NULL pointer is encountered.
 * \return TRUE if the unpack was successful, FALSE otherwise.
 */
bcmos_bool bcmolt_ieee_demo_onu_llid_support_unpack(bcmolt_ieee_demo_onu_llid_support *obj, bcmolt_buf *buf, void **extra_mem);

/** Checks if any field in the structure is set incorrectly (e.g. out of bounds).
 *
 * \param obj Pointer to the structure to validate.
 * \param err Filled in with the error (if validation fails).
 * \param err_details Filled in with a description of the error (if validation fails).
 * \return TRUE on success, FALSE on failure.
 */
bcmos_bool bcmolt_ieee_demo_onu_llid_support_validate(const bcmolt_ieee_demo_onu_llid_support *obj, bcmos_errno *err, bcmolt_string *err_details);




#endif
