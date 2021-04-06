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

#include <bcmos_system.h>
#include "bcmolt_type_metadata.h"
#include "bcmolt_set_metadata.h"

bcmos_errno bcmolt_obj_descr_get(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj_id,
    const bcmolt_obj_descr **descr)
{
    if (obj_id >= set->obj_id_count)
    {
        return BCM_ERR_RANGE;
    }

    *descr = set->lookup_obj_by_id[obj_id];
    return (*descr == NULL) ? BCM_ERR_NOENT : BCM_ERR_OK;
}

bcmos_errno bcmolt_group_descr_get(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj_id,
    bcmolt_mgt_group mgt_group,
    uint16_t subgroup_idx,
    const bcmolt_group_descr **descr)
{
    if (obj_id >= set->obj_id_count || mgt_group >= BCMOLT_MGT_GROUP__NUM_OF || subgroup_idx >= set->max_subgroup_count)
    {
        return BCM_ERR_RANGE;
    }

    /* Manually calculate the 3D array offset (since C won't let us use a 3D array of unknown dimensions). */
    uint16_t idx = (obj_id * BCMOLT_MGT_GROUP__NUM_OF * set->max_subgroup_count)
        + (mgt_group * set->max_subgroup_count)
        + subgroup_idx;

    *descr = set->lookup_group_by_subgroup_idx[idx];
    return (*descr == NULL) ? BCM_ERR_NOENT : BCM_ERR_OK;
}

bcmos_errno bcmolt_group_descr_get_by_group_id(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj_id,
    bcmolt_meta_id group_id,
    const bcmolt_group_descr **descr)
{
    *descr = set->find_group_descr(obj_id, group_id);
    return (*descr == NULL) ? BCM_ERR_NOENT : BCM_ERR_OK;
}

bcmos_errno bcmolt_group_descr_get_by_global_id(
    const bcmolt_metadata_set *set,
    uint32_t global_id,
    const bcmolt_group_descr **descr)
{
    if (global_id >= set->global_id_count)
    {
        return BCM_ERR_RANGE;
    }

    *descr = set->lookup_group_by_global_id[global_id];
    return BCM_ERR_OK;
}

uint16_t bcmolt_group_count_get(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj_id,
    bcmolt_mgt_group mgt_group)
{
    const bcmolt_obj_descr *obj_descr;
    uint16_t subgroup_count = 0;
    int i;

    if (bcmolt_obj_descr_get(set, obj_id, &obj_descr) != BCM_ERR_OK)
    {
        return 0;
    }

    for (i = 0; i < obj_descr->num_groups; i++)
    {
        if (obj_descr->groups[i]->mgt_group == mgt_group)
        {
            ++subgroup_count;
        }
    }
    return subgroup_count;
}

bcmos_errno bcmolt_group_id_split(
    const bcmolt_metadata_set *set,
    uint32_t group_id,
    bcmolt_meta_id *obj,
    bcmolt_mgt_group *group,
    uint16_t *subgroup)
{
    bcmos_errno err;
    const bcmolt_group_descr *descr;

    err = bcmolt_group_descr_get_by_global_id(set, group_id, &descr);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    *obj = descr->obj_id;
    *group = descr->mgt_group;
    *subgroup = descr->subgroup_idx;
    return BCM_ERR_OK;
}

bcmos_errno bcmolt_group_id_combine(
    const bcmolt_metadata_set *set,
    bcmolt_meta_id obj,
    bcmolt_mgt_group group,
    uint16_t subgroup,
    uint32_t *group_id)
{
    bcmos_errno err;
    const bcmolt_group_descr *descr;

    err = bcmolt_group_descr_get(set, obj, group, subgroup, &descr);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    *group_id = descr->global_id;
    return BCM_ERR_OK;
}

bcmos_errno bcmolt_tag_descr_get(const bcmolt_metadata_set *set, uint32_t tag_id, const bcmolt_tag_descr **descr)
{
    uint16_t i;
    bcmos_bool is_in_range = BCMOS_FALSE;

    for (i = 0; i < set->tag_count; i++)
    {
        is_in_range = is_in_range || (tag_id <= set->tags[i].id);
        if (tag_id == set->tags[i].id)
        {
            *descr = &set->tags[i];
            return BCM_ERR_OK;
        }
    }

    return is_in_range ? BCM_ERR_NOENT : BCM_ERR_RANGE;
}
