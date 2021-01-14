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

/*
 * API translation service
 * Translates
 * - global OLT id : OLT id on a line card
 * - global device id : device id on line card : device id on OLT
 * - PON interface on OLT : PON interface on MAC device
 */

#ifndef BCMOLT_API_TRANSLATION_H_
#define BCMOLT_API_TRANSLATION_H_

#include <bcmos_system.h>
#include <bcmolt_system_types_typedefs.h>
#include <bcmolt_api_model_api_structs.h>
#include <bcmolt_api_topology.h>
#include <bcmolt_msg.h>

/* Initialize translation layer */
bcmos_errno bcmolt_api_translate_init(void);

/* Cleanup translation layer */
void bcmolt_api_translate_exit(void);

/**
 * @brief Initialize translation layer for an OLT
 * @param[in]       olt:                Global OLT id
 * @param[in]       loid:               OLT id on a line card
 * @param[in/out]  *ldid_to_gdid_array: Device on a line card to global device id mapping array.
 *                                      some devices might already be mapped by other OLTs
 * @param[in]      *topo:
 * @return error code
 */
bcmos_errno bcmolt_api_translate_olt_init(bcmolt_oltid olt, bcmolt_loid loid,
    bcmolt_gdid *ldid_to_gdid_array, const bcmolt_topology *topo);

/* Cleanup translation layer for an OLT */
void bcmolt_api_translate_olt_exit(bcmolt_oltid olt);

/* Translate request key, make RPC using transport layer and translate response */
bcmos_errno bcmolt_api_translate_and_call(bcmolt_oltid olt, bcmolt_msg *msg);

#endif /* BCMOLT_API_TRANSLATION_H_ */
