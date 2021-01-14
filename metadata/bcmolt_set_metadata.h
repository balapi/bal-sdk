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

/* bcmolt_set_metadata.h:
 * Helper types/functions for collective sets of metadata (e.g. an entire collection of API objects).
 */

#ifndef BCMOLT_SET_METADATA_H_
#define BCMOLT_SET_METADATA_H_

#include <bcmos_system.h>
#include "bcmolt_type_metadata.h"
#include "bcmolt_buf.h"
#include "bcmolt_presence_mask.h"

/* Unless specified in the XML model, dynamic arrays will have this max size (in bytes, will divide by element size). */
#define DEFAULT_DYN_ARR_MAX_SIZE 2048

typedef struct
{
    uint16_t obj_id_count;
    uint32_t global_id_count;
    uint16_t max_subgroup_count;
    uint16_t tag_count;

    /* Array of object descriptor pointers, indexed by object ID. */
    const bcmolt_obj_descr **lookup_obj_by_id;

    /* Pointer to a function that will retrieve a group descriptor, based on object and group ID. */
    const bcmolt_group_descr *(*find_group_descr)(bcmolt_meta_id obj, bcmolt_meta_id group);

    /* Array of group descriptor pointers, indexed by global group ID. */
    const bcmolt_group_descr **lookup_group_by_global_id;

    /* Array of group descriptor pointers, indexed by:
       - [0]: object ID
       - [1]: group type
       - [2]: subgroup index.
       This is a 3D array, but you can't put a 3D array with unknown bounds in a C struct. */
    const bcmolt_group_descr **lookup_group_by_subgroup_idx;

    /* Flat array of tag descriptor pointers. */
    const bcmolt_tag_descr *tags;
} bcmolt_metadata_set;

/* All APIs return
 * BCM_ERR_OK - ok
 * BCM_ERR_NOENT - if id is in range, but doesn't correspond to any value (a hole)
 * BCM_ERR_RANGE - id is out of range
 */

/** Get object descriptor. */
bcmos_errno bcmolt_obj_descr_get(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj_id,
    const bcmolt_obj_descr **descr);

/** Get object subgroup descriptor (e.g. cfg or a single operation), using subgroup index. */
bcmos_errno bcmolt_group_descr_get(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj_id,
    bcmolt_mgt_group mgt_group,
    uint16_t subgroup_idx,
    const bcmolt_group_descr **descr);

/** Get object subgroup descriptor using persistent group ID. */
bcmos_errno bcmolt_group_descr_get_by_group_id(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj_id,
    bcmolt_meta_id group_id,
    const bcmolt_group_descr **descr);

/** Get object subgroup descriptor using global group ID. */
bcmos_errno bcmolt_group_descr_get_by_global_id(
    const bcmolt_metadata_set *set,
    uint32_t global_id,
    const bcmolt_group_descr **descr);

/** Get subgroup count for object group. */
uint16_t bcmolt_group_count_get(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj_id,
    bcmolt_mgt_group mgt_group);

/** Converts a global group ID into a specific object type, group and subgroup.
 *
 * \param group_id The global group ID.
 * \param obj The object type that corresponds to the group ID.
 * \param group The group type that corresponds to the group ID.
 * \param subgroup The subgroup index that corresponds to the group ID.
 * \return An error code or BCM_ERR_OK for success.
 */
bcmos_errno bcmolt_group_id_split(
    const bcmolt_metadata_set *set,
    uint32_t group_id,
    bcmolt_meta_id *obj,
    bcmolt_mgt_group *group,
    uint16_t *subgroup);

/** Converts a specific object type, group and subgroup into a global group ID.
 *
 * \param obj The object type that corresponds to the group ID.
 * \param group The group type that corresponds to the group ID.
 * \param subgroup The subgroup index that corresponds to the group ID.
 * \param group_id The global group ID.
 * \return An error code or BCM_ERR_OK for success.
 */
bcmos_errno bcmolt_group_id_combine(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj,
    bcmolt_mgt_group group,
    uint16_t subgroup,
    uint32_t *group_id);

/** Get tag descriptor. */
bcmos_errno bcmolt_tag_descr_get(const bcmolt_metadata_set *set, uint32_t tag_id, const bcmolt_tag_descr **descr);

#endif
