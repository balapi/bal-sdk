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

#ifndef BCMOLT_API_H_
#define BCMOLT_API_H_

#include <bcmos_system.h>
#include <bcmolt_api_model.h>
#include <bcmolt_api_metadata.h>
#include <bcmolt_api_utils.h>
#include <bcmolt_api_macros.h>
#include <bcmolt_api_internals.h>

/** \defgroup api BCM6862x, BCM6865x Host API
 *
 * Data Types and functions that should be used for BCM6862x device management.
 * @{
 */


/** \defgroup api_func API Functions
 * @{
 */

/*
 * API
 */

/** Initialize API layer
 * \returns error code
 */
bcmos_errno bcmolt_api_init(void);

/** Set Configuration
 *
 * \param[in]   olt     OLT ID
 * \param[in]   cfg     Configuration structure
 * \returns error code
 */
bcmos_errno bcmolt_cfg_set(bcmolt_oltid olt, bcmolt_cfg *cfg);

/** Get Configuration
 *
 * \param[in]   olt     OLT ID
 * \param[in]   cfg     Configuration structure
 * \returns error code
 * The error code can indicate local or remote failure
 */
bcmos_errno bcmolt_cfg_get(bcmolt_oltid olt, bcmolt_cfg *cfg);

/** Clear Configuration
 *
 * \param[in]   olt     OLT ID
 * \param[in]   cfg     Configuration structure
 * \returns error code
 * The error code can indicate local or remote failure
 */
bcmos_errno bcmolt_cfg_clear(bcmolt_oltid olt, bcmolt_cfg *cfg);

/** Get Statistics
 *
 * \param[in]   olt     OLT ID
 * \param[in]   stat    Statistics structure
 * \param[in]   flags   Statistics flags
 * \returns error code
 * The error code can indicate local or remote failure
 */
bcmos_errno bcmolt_stat_get(bcmolt_oltid olt, bcmolt_stat *stat, bcmolt_stat_flags flags);

/** Get Statistics Configuration
 *
 * \param[in]   olt     OLT ID
 * \param[in]   cfg     Statistics configuration structure
 * \returns error code
 * The error code can indicate local or remote failure
 */
bcmos_errno bcmolt_stat_cfg_get(bcmolt_oltid olt, bcmolt_stat_cfg *cfg);

/** Set Statistics Configuration
 *
 * \param[in]   olt     OLT ID
 * \param[in]   cfg     Statistics configuration structure
 * \returns error code
 * The error code can indicate local or remote failure
 */
bcmos_errno bcmolt_stat_cfg_set(bcmolt_oltid olt, bcmolt_stat_cfg *cfg);

/** Submit Operation
 *
 * \param[in]   olt     OLT ID
 * \param[in]   oper    Operation
 * \returns error code
 */
bcmos_errno bcmolt_oper_submit(bcmolt_oltid olt, bcmolt_oper *oper);

/** Receive callback registration parameters */
typedef struct bcmolt_rx_cfg
{
    bcmolt_obj_id obj_type;     /**< Object type. Can be \ref BCMOLT_OBJECT_ANY */
    f_bcmolt_msg_handler rx_cb; /**< Receive callback. Must be != NULL */
    bcmolt_auto_flags flags;    /**< Dispatch flags. Receive callback function can be called
                                     in the context of rx task or application task,
                                     depending on the flags */
    bcmos_module_id module;     /**< Target module ID.
                                     Relevant only if flags == BCMOLT_AUTO_FLAGS_DISPATCH */
    uint32_t pon_ni_mask;       /**< Bitmask of pon_ni interfaces the registration applies to.
                                     0=all interfaces. Each interface is identified by (1 << pon_ni) bit */
    uint16_t subgroup;          /**< If set, registration is performed for specific object's subgroup */
} bcmolt_rx_cfg;

/** Register Autonomous Indication Message Handler.
 *
 * Multiple subscribers can be registered for the same obj_type.
 *
 * \param[in]   olt     OLT ID
 * \param[in]   rx_cfg  Receive handler configuration
 * \returns error code
 */
bcmos_errno bcmolt_ind_subscribe(bcmolt_oltid olt, bcmolt_rx_cfg *rx_cfg);

/** Un-register Autonomous Indication Message Handler registered by
 * bcmolt_ind_subscribe().
 * Note that this function honors rx_cfg->subgroup. For unregistering
 * callback registered by bcmolt_ind_subscribe(), set .subgroup=BCMOLT_SUBGROUP_ANY.
 *
 * \param[in]   olt     OLT ID
 * \param[in]   rx_cfg  Receive handler configuration
 * \returns error code
 */
bcmos_errno bcmolt_ind_unsubscribe(bcmolt_oltid olt, bcmolt_rx_cfg *rx_cfg);

/** \defgroup multi_api_func Multi-object API Functions
 * @{
 */

/** Get configuration of multiple objects
 *
 * \param[in]   olt             OLT ID
 * \param[in]   cfg             Configuration structure
 * \param[in]   filter_flags    Optional filtering flags
 * \returns error code
 * The error code can indicate local or remote failure
 */
bcmos_errno bcmolt_multi_cfg_get(
    bcmolt_oltid olt,
    bcmolt_multi_cfg *cfg,
    bcmolt_filter_flags filter_flags);

/** Get statistics of multiple objects
 *
 * \param[in]   olt             OLT ID
 * \param[in]   stat            Statistics structure
 * \param[in]   flags           Statistics flags
 * \param[in]   filter_flags    Optional filtering flags
 * \returns error code
 * The error code can indicate local or remote failure
 */
bcmos_errno bcmolt_multi_stat_get(
    bcmolt_oltid olt,
    bcmolt_multi_stat *stat,
    bcmolt_stat_flags stat_flags,
    bcmolt_filter_flags filter_flags);

/** @} */

/** @} */

/** @} */

#endif /* BCMOLT_API_H_ */
