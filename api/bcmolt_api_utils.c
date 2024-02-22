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

#include <bcmolt_type_metadata.h>
#include <bcmolt_math.h>
#include "bcmolt_api_macros.h"
#include "bcmolt_api_metadata.h"
#include "bcmolt_api_utils.h"
#include "bcmolt_api_writer.h"

#if 0
#define BCMOLT_API_UTILS_DEBUG
#endif

#ifdef BCMOLT_API_UTILS_DEBUG
#define BCMOLT_API_UTILS_PRINTF(fmt, args...) fprintf(stdout, fmt, ## args)
#else
#define BCMOLT_API_UTILS_PRINTF(fmt, args...) \
    do \
    { \
    } while (0)
#endif

/* Check if the given type is a list that contains a raw pointer (no pre-allocated memory). */
static bcmos_bool _is_raw_pointer_list(const bcmolt_type_descr *type)
{
    switch (type->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
        return !type->x.arr_dyn.is_array_backend;
    case BCMOLT_BASE_TYPE_ID_BINARY_DYN:
        return BCMOS_TRUE;
    default:
        return BCMOS_FALSE;
    }
}

static uint8_t *bcmolt_array_elem_data_get(const bcmolt_type_descr *type, void *arr_ptr, uint32_t i)
{
    if (arr_ptr == NULL)
    {
        return NULL;
    }

    if (_is_raw_pointer_list(type))
    {
        void *arr_data_ptr = (uint8_t *)arr_ptr + type->x.arr_dyn.data_offset;
        return *(uint8_t **)arr_data_ptr + (i * type->x.arr_dyn.elem_type->size);
    }
    else
    {
        return (uint8_t *)arr_ptr + type->x.arr_fixed.data_offset + (i * type->x.arr_fixed.elem_type->size);
    }
}

static const uint8_t *bcmolt_array_elem_data_get_const(const bcmolt_type_descr *type, const void *arr_ptr, uint32_t i)
{
    if (_is_raw_pointer_list(type))
    {
        const void *arr_data_ptr = (const uint8_t *)arr_ptr + type->x.arr_dyn.data_offset;
        return *(uint8_t * const *)arr_data_ptr + (i * type->x.arr_dyn.elem_type->size);
    }
    else
    {
        return (const uint8_t *)arr_ptr + type->x.arr_fixed.data_offset + (i * type->x.arr_fixed.elem_type->size);
    }
}

static bcmos_bool bcmolt_type_has_explicit_dynamic_array(const bcmolt_type_descr *type, const void *data);

static void _has_dyn_arr_field(const bcmolt_api_parse_field *field, void *context)
{
    bcmos_bool *has_dyn_arr = context;

    if (_is_raw_pointer_list(field->descr->type))
    {
        *has_dyn_arr = !field->is_implicit;
    }
    else
    {
        *has_dyn_arr = bcmolt_type_has_explicit_dynamic_array(field->descr->type, field->data);
    }
}

static void _has_dyn_arr_elem(const bcmolt_api_parse_elem *elem, void *context)
{
    bcmos_bool *has_dyn_arr = context;

    *has_dyn_arr = bcmolt_type_has_explicit_dynamic_array(elem->elem_type, elem->data);
}

/* Check if the given type contains (at any depth) any dynamically-sized arrays for which the presence mask bit is
 * SPECIFICALLY set (the overall PM is not all 0s). */
static bcmos_bool bcmolt_type_has_explicit_dynamic_array(const bcmolt_type_descr *type, const void *data)
{
    bcmos_bool has_dyn_arr = BCMOS_FALSE;
    bcmolt_api_parse(data, type, BCMOS_FALSE, NULL, &has_dyn_arr, _has_dyn_arr_field, _has_dyn_arr_elem, NULL);
    return has_dyn_arr;
}

static void _may_have_dyn_arr_field(const bcmolt_api_parse_field *field, void *context)
{
    bcmos_bool *has_dyn_arr = context;

    if (_is_raw_pointer_list(field->descr->type))
    {
        *has_dyn_arr = BCMOS_TRUE;
    }
    else
    {
        *has_dyn_arr = bcmolt_type_may_have_dynamic_array(field->descr->type, field->data);
    }
}

static void _may_have_dyn_arr_elem(const bcmolt_api_parse_elem *elem, void *context)
{
    bcmos_bool *has_dyn_arr = context;

    *has_dyn_arr = bcmolt_type_may_have_dynamic_array(elem->elem_type, elem->data);
}

/* Check if the given type could potentially contain (at any depth) any dynamically-sized arrays */
bcmos_bool bcmolt_type_may_have_dynamic_array(const bcmolt_type_descr *type, const void *data)
{
    bcmos_bool has_dyn_arr = BCMOS_FALSE;
    bcmolt_api_parse(data, type, BCMOS_TRUE, NULL, &has_dyn_arr, _may_have_dyn_arr_field, _may_have_dyn_arr_elem, NULL);
    return has_dyn_arr;
}

static bcmos_errno bcmolt_api_validate_multi_api(bcmolt_multi_msg *msg)
{
    bcmos_errno err;
    bcmolt_api_group_id req_group_id;
    bcmolt_api_group_id filter_group_id;
    const bcmolt_group_descr *req_group;
    const bcmolt_group_descr *filter_group = NULL;

    err = bcmolt_api_group_id_combine(msg->hdr.obj_type, msg->hdr.group, msg->hdr.subgroup, &req_group_id);
    BCMOS_RETURN_IF_ERROR(err);

    err = bcmolt_api_group_descr_get_by_global_id(req_group_id, &req_group);
    BCMOS_RETURN_IF_ERROR(err);

    if (bcmolt_api_group_id_combine(msg->hdr.obj_type, BCMOLT_MGT_GROUP_CFG, 0, &filter_group_id) == BCM_ERR_OK)
    {
        err = bcmolt_api_group_descr_get_by_global_id(filter_group_id, &filter_group);
        BCMOS_RETURN_IF_ERROR(err);
    }

    if (bcmolt_type_has_explicit_dynamic_array(req_group->type, (void *)((long)msg + req_group->multi->request_offset))
        || (filter_group != NULL
            && bcmolt_type_has_explicit_dynamic_array(
                filter_group->type,
                (void *)((long)msg + req_group->multi->filter_offset))))
    {
        return BCMOLT_MSG_ERR(
            &msg->hdr,
            DEV_LOG_INVALID_ID,
            BCM_ERR_PARM,
            "Dynamically-sized arrays are not allowed in multi-object API requests");
    }

    return BCM_ERR_OK;
}

static void bcmolt_api_path_add_field(bcmolt_api_prop_path *path, const bcmolt_field_descr *field)
{
    if ((path != NULL) && (path->curr_depth < BCMOLT_API_MAX_PATH_DEPTH))
    {
        path->nodes[path->curr_depth].type = BCMOLT_API_PROP_NODE_TYPE_FIELD;
        path->nodes[path->curr_depth].u.field = field;
        ++path->curr_depth;
    }
}

static void bcmolt_api_path_add_idx(bcmolt_api_prop_path *path, uint16_t array_index)
{
    if ((path != NULL) && (path->curr_depth < BCMOLT_API_MAX_PATH_DEPTH))
    {
        path->nodes[path->curr_depth].type = BCMOLT_API_PROP_NODE_TYPE_ARRAY_INDEX;
        path->nodes[path->curr_depth].u.array_index = array_index;
        ++path->curr_depth;
    }
}

static void bcmolt_api_path_add_union(bcmolt_api_prop_path *path, const bcmolt_field_descr *field)
{
    if ((path != NULL) && (path->curr_depth < BCMOLT_API_MAX_PATH_DEPTH))
    {
        path->nodes[path->curr_depth].type = BCMOLT_API_PROP_NODE_TYPE_UNION_FIELD;
        path->nodes[path->curr_depth].u.field = field;
        ++path->curr_depth;
    }
}

static bcmolt_api_prop_node *bcmolt_api_path_pop(bcmolt_api_prop_path *path)
{
    if ((path != NULL) && (path->curr_depth > 0))
    {
        --path->curr_depth;
        return &path->nodes[path->curr_depth];
    }
    return NULL;
}

static void bcmolt_api_parse_separate_mask(
    const void *mask,
    const void *data,
    const bcmolt_type_descr *type_descr,
    bcmos_bool expand_unions,
    bcmolt_api_prop_path *path,
    void *context,
    f_per_field field_cb,
    f_per_elem elem_cb,
    f_per_simple simple_cb)
{
    uint32_t i;
    bcmolt_presence_mask pm;
    const bcmolt_field_descr *field;
    int64_t array_len;

    switch (type_descr->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_STRUCT:
        /* process struct fields */
        pm = bcmolt_api_get_presence_mask(mask, type_descr);
        for (i = 0; i < type_descr->x.s.num_fields; i++)
        {
            field = &type_descr->x.s.fields[i];
            if (bcmolt_field_is_set(pm, field->id))
            {
                if (field_cb != NULL)
                {
                    bcmolt_api_path_add_field(path, field);
                    field_cb
                        (&(bcmolt_api_parse_field){
                            .parent_type = type_descr,
                            .parent_data = (void *)(long)data,
                            .descr = field,
                            .mask = (mask == NULL) ? NULL : (void *)((long)mask + field->offset),
                            .data = (data == NULL) ? NULL : (void *)((long)data + field->offset),
                            .is_implicit = pm == 0,
                            .in_union = BCMOS_FALSE,
                            .path = path },
                        context);
                    (void)bcmolt_api_path_pop(path);
                }
            }
        }
        break;
    case BCMOLT_BASE_TYPE_ID_UNION:
        /* process common fields */
        pm = bcmolt_api_get_presence_mask(mask, type_descr);
        for (i = 0; i < type_descr->x.u.num_common_fields; i++)
        {
            /* copy the common fields */
            field = &type_descr->x.u.common_fields[i];
            if (bcmolt_field_is_set(pm, field->id))
            {
                if (field_cb != NULL)
                {
                    bcmolt_api_path_add_field(path, field);
                    field_cb(
                        &(bcmolt_api_parse_field){
                            .parent_type = type_descr,
                            .parent_data = (void *)(long)data,
                            .descr = field,
                            .mask = (mask == NULL) ? NULL : (void *)((long)mask + field->offset),
                            .data = (data == NULL) ? NULL : (void *)((long)data + field->offset),
                            .is_implicit = pm == 0,
                            .in_union = BCMOS_FALSE,
                            .path = path },
                        context);
                    (void)bcmolt_api_path_pop(path);
                }
            }
        }
        /* process union fields */
        field = &type_descr->x.u.common_fields[type_descr->x.u.classifier_idx];
        if (bcmolt_field_is_set(pm, field->id))
        {
            int num_union_vals = bcmolt_get_num_enum_vals(field->type->x.e.vals);
            if (!expand_unions)
            {
                int64_t selector_val;
                if ((data != NULL)
                    && (BCM_ERR_OK
                        == bcmolt_read_snum(field->type->size, (void *)((long)data + field->offset), &selector_val)))
                {
                    if ((unsigned)selector_val < num_union_vals)
                    {
                        field = &type_descr->x.u.union_fields[selector_val];
                        if (field->name != NULL)
                        {
                            if (field_cb != NULL)
                            {
                                bcmolt_api_path_add_union(path, field);
                                field_cb(
                                    &(bcmolt_api_parse_field){
                                        .parent_type = type_descr,
                                        .parent_data = (void *)(long)data,
                                        .descr = field,
                                        .mask = (mask == NULL) ? NULL : (void *)((long)mask + field->offset),
                                        .data = (void *)((long)data + field->offset),
                                        .is_implicit = pm == 0,
                                        .in_union = BCMOS_TRUE,
                                        .path = path },
                                    context);
                                (void)bcmolt_api_path_pop(path);
                            }
                        }
                    }
                }
                else
                {
                    BCMOS_TRACE_ERR("bcmolt_read_snum() failed \n");
                }
            }
            else
            {
                for (i = 0; i < num_union_vals; ++i)
                {
                    field = &type_descr->x.u.union_fields[i];
                    if (field->name != NULL)
                    {
                        if (field_cb != NULL)
                        {
                            bcmolt_api_path_add_union(path, field);
                            field_cb(
                                &(bcmolt_api_parse_field){
                                    .parent_type = type_descr,
                                    .parent_data = (void *)(long)data,
                                    .descr = field,
                                    .mask = NULL,
                                    .data = NULL,
                                    .is_implicit = pm == 0,
                                    .in_union = BCMOS_TRUE,
                                    .path = path },
                                context);
                            (void)bcmolt_api_path_pop(path);
                        }
                    }
                }
            }
        }
        break;
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
        /* process fixed array elements */
        pm = bcmolt_api_get_presence_mask(mask, type_descr);
        for (i = 0; i < type_descr->x.arr_fixed.size; i++)
        {
            if (bcmolt_array_elem_is_present(pm, i))
            {
                if (elem_cb != NULL)
                {
                    bcmolt_api_path_add_idx(path, i);
                    elem_cb(
                        &(bcmolt_api_parse_elem){
                            .list_type = type_descr,
                            .list_data = (void *)(long)data,
                            .elem_type = type_descr->x.arr_fixed.elem_type,
                            .mask = bcmolt_array_elem_data_get(type_descr, (void *)(long)mask, i),
                            .data = bcmolt_array_elem_data_get(type_descr, (void *)(long)data, i),
                            .idx = i,
                            .path = path },
                        context);
                    (void)bcmolt_api_path_pop(path);
                }
            }
        }
        break;
    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
        /* process dynamic array elements */
        if ((data != NULL) && (BCM_ERR_OK == bcmolt_read_snum(type_descr->x.arr_dyn.len_type->size, data, &array_len)))
        {
            pm = bcmolt_api_get_presence_mask(mask, type_descr);
            for (i = 0; i < array_len; i++)
            {
                if (bcmolt_array_elem_is_present(pm, i))
                {
                    if (elem_cb != NULL)
                    {
                        bcmolt_api_path_add_idx(path, i);
                        elem_cb(
                            &(bcmolt_api_parse_elem){
                                .list_type = type_descr,
                                .list_data = (void *)(long)data,
                                .elem_type = type_descr->x.arr_fixed.elem_type,
                                .mask = bcmolt_array_elem_data_get(type_descr, (void *)(long)mask, i),
                                .data = bcmolt_array_elem_data_get(type_descr, (void *)(long)data, i),
                                .idx = i,
                                .path = path },
                            context);
                        (void)bcmolt_api_path_pop(path);
                    }
                }
            }
        }
        else
        {
            BCMOS_TRACE_ERR("bcmolt_read_snum() failed \n");
        }
        break;
    default:
        if (simple_cb != NULL)
        {
            simple_cb(
                &(bcmolt_api_parse_simple){
                    .type = type_descr,
                    .mask = (void *)(long)mask,
                    .data = (void *)(long)data,
                    .path = path },
                context);
        }
        break;
    }
}

void bcmolt_api_parse(
    const void *data,
    const bcmolt_type_descr *type_descr,
    bcmos_bool expand_unions,
    bcmolt_api_prop_path *path,
    void *context,
    f_per_field field_cb,
    f_per_elem elem_cb,
    f_per_simple simple_cb)
{
    bcmolt_api_parse_separate_mask(data, data, type_descr, expand_unions, path, context, field_cb, elem_cb, simple_cb);
}

uint32_t bcmolt_api_get_list_len(const bcmolt_type_descr *type_descr, const void *data)
{
    int64_t array_len;

    switch (type_descr->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_STRING:
        return type_descr->size;
    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
        if (BCM_ERR_OK
            == bcmolt_read_snum(
                type_descr->x.arr_dyn.len_type->size,
                (void *)((long)data + type_descr->x.arr_dyn.len_offset),
                &array_len))
        {
            return (uint32_t)array_len;
        }
        return 0;
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
        return type_descr->x.arr_fixed.size;
    case BCMOLT_BASE_TYPE_ID_BINARY_DYN:
        if (BCM_ERR_OK
            == bcmolt_read_snum(
                sizeof(((bcmolt_bin_str *)0)->len),
                (void *)((long)data + type_descr->x.binary_dyn.len_offset),
                &array_len))
        {
            return array_len;
        }
        return 0;
    case BCMOLT_BASE_TYPE_ID_BINARY_FIXED:
        return type_descr->x.binary_fixed.len;
    default:
        return 1;
    }
}

bcmos_errno bcmolt_api_validate_for_api_call(bcmolt_msg *msg)
{
    /* Check if a set request has a nonzero number of parameters and a presence mask of 0 (which we don't support). */
    if ((msg->type & BCMOLT_MSG_TYPE_SET) != 0 && msg->dir == BCMOLT_MSG_DIR_REQUEST)
    {
        const bcmolt_group_descr *group;
        bcmos_errno err = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group);
        if (err != BCM_ERR_OK)
        {
            msg->dir = BCMOLT_MSG_DIR_RESPONSE;
            return err;
        }

        if (group->type != NULL) /* no data struct = no parameters */
        {
            bcmolt_presence_mask *presence_mask =
                (void *)((uint8_t *)msg + group->data_offset + group->type->mask_offset);
            if (*presence_mask == 0)
            {
                msg->dir = BCMOLT_MSG_DIR_RESPONSE;
                return BCMOLT_MSG_ERR(msg, DEV_LOG_INVALID_ID, BCM_ERR_PARM, "At least one parameter must be set");
            }
        }
    }

    if ((msg->type & BCMOLT_MSG_TYPE_MULTI) != 0 && msg->dir == BCMOLT_MSG_DIR_REQUEST)
    {
        /* Multi-object requests have special validation requirements. */
        bcmos_errno err = bcmolt_api_validate_multi_api((bcmolt_multi_msg *)msg);
        if (err != BCM_ERR_OK)
        {
            msg->dir = BCMOLT_MSG_DIR_RESPONSE;
            return err;
        }
    }

    return BCM_ERR_OK;
}

static bcmos_bool _bcmolt_api_prop_tree_is_set(
    const bcmolt_api_prop_tree *tree,
    uint32_t prop,
    const bcmolt_api_prop_tree **prop_match)
{
    const bcmolt_api_prop_tree *iter;

    *prop_match = NULL;

    if (!tree)
        return BCMOS_TRUE;

    for (iter = tree; iter->prop != BCMOLT_PROP_TERMINATE; iter++)
    {
        if (iter->prop == prop)
        {
            *prop_match = iter;
            return BCMOS_TRUE;
        }
    }

    return BCMOS_FALSE;
}

const bcmolt_presence_mask *bcmolt_api_get_presence_mask_ptr(const uint8_t *data, const bcmolt_type_descr *type_descr)
{
    const void *fdata;

    if (data == NULL || type_descr->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
        return NULL;

    fdata = data + type_descr->mask_offset;
    return (const bcmolt_presence_mask *)fdata;
}

bcmolt_presence_mask bcmolt_api_get_presence_mask(const uint8_t *data, const bcmolt_type_descr *type_descr)
{
    const bcmolt_presence_mask *presence_mask_ptr = bcmolt_api_get_presence_mask_ptr(data, type_descr);

    /* If the structure doesn't have presence mask field (although most should have), assume all fields are set.
     * (data == NULL) is used internally to mean "ignore all presence masks". */
    if (presence_mask_ptr == NULL)
        return BCMOLT_PRESENCE_MASK_ALL;

    return *presence_mask_ptr;
}

bcmolt_presence_mask bcmolt_api_get_presence_mask_all(const bcmolt_type_descr *type_descr)
{
    bcmolt_presence_mask presence_mask_all = 0;
    uint32_t i;

    switch (type_descr->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_STRUCT:
        for (i = 0; i < type_descr->x.s.num_fields; i++)
            presence_mask_all |= 1ULL << type_descr->x.s.fields[i].id;
        break;
    case BCMOLT_BASE_TYPE_ID_UNION:
        for (i = 0; i < type_descr->x.u.num_common_fields; i++)
            presence_mask_all |= 1ULL << type_descr->x.u.common_fields[i].id;
        break;
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
        for (i = 0; i < type_descr->x.arr_fixed.size; i++)
            presence_mask_all |= 1ULL << i;
        break;
    default:
        break;
    }

    return presence_mask_all;
}

static void bcmolt_api_zero_presence_mask(uint8_t *data, const bcmolt_type_descr *type_descr)
{
    void *fdata = data + type_descr->mask_offset;
    *(bcmolt_presence_mask *)fdata = 0;
}

static void bcmolt_api_set_presence_mask_bit(uint8_t *data, const bcmolt_type_descr *type_descr, uint8_t field_id)
{
    void *fdata = data + type_descr->mask_offset;
    *(bcmolt_presence_mask *)fdata |= (1ULL << field_id);
}

static void bcmolt_api_clear_presence_mask_bit(uint8_t *data, const bcmolt_type_descr *type_descr, uint8_t field_id)
{
    void *fdata = data + type_descr->mask_offset;
    *(bcmolt_presence_mask *)fdata &= ~(1ULL << field_id);
}

bcmos_errno bcmolt_api_prop_iter_2nd_level(
    const uint8_t *data,
    const bcmolt_type_descr *type_descr,
    const bcmolt_api_prop_tree *tree,
    bcmolt_api_prop_iter_cb cb,
    void *context,
    bcmolt_api_prop_path *path,
    uint32_t curr_depth)
{
    bcmolt_presence_mask presence_mask;
    uint32_t i;
    int next_prop;
    bcmos_errno rc;
#ifdef BCMOLT_API_UTILS_DEBUG
    char path_str[BCMOLT_API_MAX_TYPE_DESCR_PATH_STR];
#endif

    presence_mask = bcmolt_api_get_presence_mask(data, type_descr);

    while ((next_prop = ffsll((uint64_t)presence_mask)))
    {
        /* Initialize to NULL to avoid compiler warning about uninitialized variable. */
        const bcmolt_field_descr *field_descr = NULL;
        const bcmolt_api_prop_tree *prop_match;

        next_prop--;

        for (i = 0; i < type_descr->x.s.num_fields; i++)
        {
            field_descr = &type_descr->x.s.fields[i];
            if (field_descr->id == next_prop)
                break;
        }
        BUG_ON(i == type_descr->x.s.num_fields);

        BCMOLT_API_UTILS_PRINTF(
            "\tScanning '%s%s'",
            bcmolt_string_indent(path_str, sizeof(path_str), curr_depth + 1),
            field_descr->name);

        path->nodes[curr_depth].type = BCMOLT_API_PROP_NODE_TYPE_FIELD;
        path->nodes[curr_depth].u.field = field_descr;
        /* If 'tree' is NULL and _bcmolt_api_prop_tree_is_set() returns true, then prop_match would become NULL. */
        if (_bcmolt_api_prop_tree_is_set(tree, next_prop, &prop_match))
        {
            if (field_descr->type->base_type != BCMOLT_BASE_TYPE_ID_STRUCT
                || (prop_match && (!prop_match->sub_tree || prop_match->data)))
            {
                /* Node is a leaf. */
                path->curr_depth = curr_depth + 1;
                rc = cb(field_descr, data + field_descr->offset, prop_match, context, path);
                BCMOLT_API_UTILS_PRINTF(" --> match (callback returned %d)\n", rc);
                if (rc != BCM_ERR_OK)
                    return rc;
            }
            else
                BCMOLT_API_UTILS_PRINTF("\n");

            if (field_descr->type->base_type == BCMOLT_BASE_TYPE_ID_STRUCT && (!prop_match || prop_match->sub_tree))
            {
                if (!prop_match)
                {
                    /* Node is a not a leaf and 'tree' is NULL (implying the callback should be called for each level). */
                    path->curr_depth = curr_depth + 1;
                    rc = cb(field_descr, data + field_descr->offset, prop_match, context, path);
                    BCMOLT_API_UTILS_PRINTF(" --> match (callback returned %d)\n", rc);
                    if (rc != BCM_ERR_OK)
                        return rc;
                }

                /* Node is not a leaf. */
                rc = bcmolt_api_prop_iter_2nd_level(
                    data + field_descr->offset,
                    field_descr->type,
                    prop_match ? prop_match->sub_tree : NULL,
                    cb,
                    context,
                    path,
                    curr_depth + 1);
                if (rc != BCM_ERR_OK)
                    return rc;
            }
        }
        else
        {
            path->curr_depth = curr_depth + 1;
            rc = cb(field_descr, data + field_descr->offset, prop_match, context, path); /* 'prop_match' would be NULL. */
            if (rc != BCM_ERR_OK)
            {
                BCMOLT_API_UTILS_PRINTF("\n");
                return rc; /* Stop the recursion */
            }
            BCMOLT_API_UTILS_PRINTF("\n");
        }

        presence_mask &= ~(1ULL << next_prop);
    }

    return BCM_ERR_OK;
}

bcmos_errno bcmolt_api_prop_iter_func(
    const bcmolt_msg *msg,
    const bcmolt_api_prop_tree *tree,
    bcmolt_api_prop_iter_cb cb,
    void *context,
    const char *func,
    int line)
{
    bcmos_errno rc;
    const bcmolt_group_descr *group_descr;
    const uint8_t *msg_data;
    bcmolt_api_prop_path path = {};

    rc = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group_descr);
    if (rc != BCM_ERR_OK)
        return rc;
    msg_data = (const uint8_t *)msg + group_descr->data_offset;

    BCMOLT_API_UTILS_PRINTF("bcmolt_api_prop_iter() called from %s:%d\n", func, line);
    return bcmolt_api_prop_iter_2nd_level(msg_data, group_descr->type, tree, cb, context, &path, 0);
}

static bcmos_errno bcmolt_api_prop_tree_is_set_cb(
    const bcmolt_field_descr *field_descr,
    const uint8_t *field_data,
    const bcmolt_api_prop_tree *node,
    void *context,
    const bcmolt_api_prop_path *path)
{
    bcmolt_api_prop_path *_path = context;

    if (node)
    {
        /* Match -> stop the recursion. */
        if (_path != NULL)
        {
            *_path = *path;
        }
        return BCM_ERR_ALREADY;
    }

    /* Continue the recursion. */
    return BCM_ERR_OK;
}

bcmos_bool bcmolt_api_prop_tree_is_set(
    const bcmolt_msg *msg,
    const bcmolt_api_prop_tree *tree,
    bcmolt_api_prop_path *path)
{
    bcmos_errno rc;

    if (path != NULL)
    {
        memset(path, 0, sizeof(*path));
    }
    rc = bcmolt_api_prop_iter(msg, tree, bcmolt_api_prop_tree_is_set_cb, (void *)path);

    return rc == BCM_ERR_OK ? BCMOS_FALSE : BCMOS_TRUE;
}

typedef struct
{
    const uint8_t *msg_data; /* pointer to the data portion of the API msg being traversed */
    const uint8_t *to_compare; /* pointer to the data for comparison - MUST match the type of message*/
    bcmolt_api_prop_path *path; /* OUT: path to the parameter that didn't match (if any) */
} bcmolt_api_prop_tree_compare_context;

static bcmos_errno bcmolt_api_tree_compare_cb(
    const bcmolt_field_descr *field_descr,
    const uint8_t *field_data,
    const bcmolt_api_prop_tree *node,
    void *context,
    const bcmolt_api_prop_path *path)
{
    bcmolt_api_prop_tree_compare_context *compare_ctxt = context;

    if (node)
    {
        /* this data was included and is unsupported - ensure it matches defaults */
        uint32_t byte_offset = field_data - compare_ctxt->msg_data;
        if (!bcmolt_api_check_field_equality_generic(
            field_descr->type,
            field_data,
            compare_ctxt->to_compare + byte_offset))
        {
            *(compare_ctxt->path) = *path;
            return BCM_ERR_MISMATCH;
        }
    }

    return BCM_ERR_OK;
}

bcmos_bool bcmolt_api_prop_tree_compare(
    const bcmolt_msg *msg,
    const bcmolt_api_prop_tree *tree,
    const void *msg_data,
    const void *to_compare,
    bcmolt_api_prop_path *path)
{
    bcmos_errno rc;
    bcmolt_api_prop_tree_compare_context tree_context =
    {
        .msg_data = msg_data,
        .to_compare = to_compare,
        .path = path
    };

    rc = bcmolt_api_prop_iter(msg, tree, bcmolt_api_tree_compare_cb, &tree_context);

    return rc == BCM_ERR_OK ? BCMOS_TRUE : BCMOS_FALSE;
}

typedef struct
{
    const uint8_t *prop_ptr;
    bcmos_bool force_presence_mask_all;
    bcmos_bool is_prop_set;
    bcmolt_api_prop_path *prop_path;
} bcmolt_api_is_prop_set_ctxt;

static void _prop_is_set_recurse(
    const uint8_t *data,
    const bcmolt_type_descr *type_descr,
    bcmolt_api_prop_path *parser_path,
    bcmolt_api_is_prop_set_ctxt *ctxt);

static void _is_prop_set_prop(
    const uint8_t *data,
    const bcmolt_type_descr *type_descr,
    bcmolt_api_prop_path *path,
    void *context)
{
    bcmolt_api_is_prop_set_ctxt *ctxt = context;

    if (data == ctxt->prop_ptr) /* Match -> stop the recursion. */
    {
        ctxt->is_prop_set = BCMOS_TRUE;
        if (ctxt->prop_path != NULL)
        {
            *ctxt->prop_path = *path;
        }
    }
    else
    {
        _prop_is_set_recurse(data, type_descr, path, ctxt);
    }
}

static void _is_prop_set_field(const bcmolt_api_parse_field *field, void *context)
{
    _is_prop_set_prop(field->data, field->descr->type, field->path, context);
}

static void _is_prop_set_elem(const bcmolt_api_parse_elem *elem, void *context)
{
    _is_prop_set_prop(elem->data, elem->elem_type, elem->path, context);
}

static void _prop_is_set_recurse(
    const uint8_t *data,
    const bcmolt_type_descr *type_descr,
    bcmolt_api_prop_path *parser_path,
    bcmolt_api_is_prop_set_ctxt *ctxt)
{
    bcmolt_api_parse_separate_mask(
        ctxt->force_presence_mask_all ? NULL : data,
        data,
        type_descr,
        BCMOS_FALSE,
        parser_path,
        ctxt,
        _is_prop_set_field,
        _is_prop_set_elem,
        NULL);
}

/* Return BCMOS_TRUE if the recursion found that the requested property is present. */
static bcmos_bool _prop_is_set(
    const uint8_t *data,
    const bcmolt_type_descr *type_descr,
    const uint8_t *prop_ptr,
    bcmolt_api_prop_path *path,
    bcmos_bool force_presence_mask_all)
{
    bcmolt_api_is_prop_set_ctxt ctxt =
    {
        .prop_ptr = prop_ptr,
        .force_presence_mask_all = force_presence_mask_all,
        .is_prop_set = BCMOS_FALSE,
        .prop_path = path
    };
    bcmolt_api_prop_path parser_path = {};
    _prop_is_set_recurse(data, type_descr, &parser_path, &ctxt);
    return ctxt.is_prop_set;
}

bcmos_bool bcmolt_api_prop_is_set(const bcmolt_msg *msg, const void *prop_ptr, bcmolt_api_prop_path *path)
{
    bcmos_errno rc;
    bcmos_bool is_set;
    const bcmolt_group_descr *group_descr;
    const uint8_t *msg_data;

    if (path != NULL)
    {
        memset(path, 0, sizeof(*path));
    }

    rc = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group_descr);
    if (rc != BCM_ERR_OK)
        return BCMOS_FALSE;
    msg_data = (const uint8_t *)msg + group_descr->data_offset;

    is_set = _prop_is_set(msg_data, group_descr->type, prop_ptr, path, BCMOS_FALSE);
    if (!is_set)
    {
        /* If the property isn't found in 'msg', at least retrieve its exact path (used for error messages). */
        _prop_is_set(msg_data, group_descr->type, prop_ptr, path, BCMOS_TRUE);
    }

    return is_set;
}

static void bcmolt_api_prop_presence_modify(bcmolt_msg *msg, const void *prop_ptr, bcmos_bool set_present)
{
    bcmos_errno rc;
    const bcmolt_group_descr *group_descr;
    uint8_t *data;
    bcmolt_api_prop_path path = {};

    rc = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group_descr);
    BCMOS_TRACE_RETURN_VOID_ON_ERROR(rc);

    if ((msg->type & BCMOLT_MSG_TYPE_MULTI) == 0)
    {
        data = (uint8_t *)msg + group_descr->data_offset;
    }
    else
    {
        BUG_ON(group_descr->multi == NULL);
        uint32_t prop_offset = (const uint8_t *)prop_ptr - (uint8_t *)msg;
        uint32_t data_offset;
        if (prop_offset > MAX(group_descr->multi->filter_offset, group_descr->multi->request_offset))
        {
            data_offset = MAX(group_descr->multi->filter_offset, group_descr->multi->request_offset);
        }
        else
        {
            data_offset = MIN(group_descr->multi->filter_offset, group_descr->multi->request_offset);
        }
        data = (uint8_t *)msg + data_offset;
        if ((msg->group == BCMOLT_MGT_GROUP_STAT) && (data_offset == group_descr->multi->filter_offset))
        {
            /* multi stat filter is cfg not stat */
            rc = bcmolt_api_group_descr_get(msg->obj_type, BCMOLT_MGT_GROUP_CFG, 0, &group_descr);
            BCMOS_TRACE_RETURN_VOID_ON_ERROR(rc);
        }
    }

    /* Call _prop_is_set() just to fill in the full path. */
    _prop_is_set(data, group_descr->type, prop_ptr, &path, BCMOS_TRUE);

    bcmolt_api_prop_presence_modify_by_path(&path, group_descr->type, data, set_present);
}

void bcmolt_api_prop_presence_modify_by_path(const bcmolt_api_prop_path *path, const bcmolt_type_descr *type_descr, uint8_t *data, bcmos_bool set_present)
{
    uint32_t i;

    for (i = 0; i < path->curr_depth; i++)
    {
        uint16_t id = 0;
        const bcmolt_type_descr *parent_type_descr = type_descr;
        uint8_t *parent_data = data;

        switch (path->nodes[i].type)
        {
        case BCMOLT_API_PROP_NODE_TYPE_FIELD:
        case BCMOLT_API_PROP_NODE_TYPE_UNION_FIELD:
            id = path->nodes[i].u.field->id;
            data += path->nodes[i].u.field->offset;
            type_descr = path->nodes[i].u.field->type;
            break;
        case BCMOLT_API_PROP_NODE_TYPE_ARRAY_INDEX:
            id = path->nodes[i].u.array_index;
            data = bcmolt_array_elem_data_get(type_descr, data, id);
            type_descr = type_descr->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN
                ? type_descr->x.arr_dyn.elem_type
                : type_descr->x.arr_fixed.elem_type;
            break;
        default:
            BUG();
            break;
        }

        BCMOS_TRACE_CHECK_RETURN_VOID(id > 255, BCM_ERR_NOT_SUPPORTED, "Field IDs > 255 are not currently supported");
        if (set_present)
        {
            bcmolt_api_set_presence_mask_bit(parent_data, parent_type_descr, (uint8_t)id);
        }
        else
        {
            if (i == path->curr_depth - 1) /* only clear the lowest-level presence mask */
            {
                bcmolt_api_clear_presence_mask_bit(parent_data, parent_type_descr, (uint8_t)id);
            }
        }
    }
}

void bcmolt_api_set_prop_present(bcmolt_msg *msg, const void *prop_ptr)
{
    bcmolt_api_prop_presence_modify(msg, prop_ptr, BCMOS_TRUE);
}

void bcmolt_api_clear_prop_presence(bcmolt_msg *msg, const void *prop_ptr)
{
    bcmolt_api_prop_presence_modify(msg, prop_ptr, BCMOS_FALSE);
}

char *bcmolt_api_prop_get_path_str(const bcmolt_api_prop_path *path, char *path_str, uint32_t max_path_str_len)
{
    uint32_t i;
    int len = 0;
    char *s = path_str;

    for (i = 0; i < path->curr_depth; i++)
    {
        switch (path->nodes[i].type)
        {
        case BCMOLT_API_PROP_NODE_TYPE_FIELD:
        case BCMOLT_API_PROP_NODE_TYPE_UNION_FIELD:
            len = snprintf(s, max_path_str_len - len, "%s%s", i ? "." : "", path->nodes[i].u.field->name);
            break;
        case BCMOLT_API_PROP_NODE_TYPE_ARRAY_INDEX:
            len = snprintf(s, max_path_str_len - len, "[%u]", path->nodes[i].u.array_index);
            break;
        default:
            len = -1;
            break;
        }
        if (len < 0)
            return NULL;
        s += len;
    }

    return path_str;
}

bcmos_errno bcmolt_msg_err(
    bcmolt_msg *msg,
    dev_log_id log_id,
    bcmos_errno err,
    const bcmolt_api_prop_path *path,
    const char *fmt,
    ...)
{
    char path_str[BCMOLT_API_MAX_TYPE_DESCR_PATH_STR];
    int offset = 0;

    msg->err = err;
    msg->err_text[0] = 0;

    if (path != NULL)
    {
        (void)bcmolt_api_prop_get_path_str(path, path_str, sizeof(path_str));
        offset = snprintf(msg->err_text, sizeof(msg->err_text), "%s: ", path_str);
    }
    if (fmt)
    {
        va_list args;

        va_start(args, fmt);
        offset += vsnprintf(msg->err_text + offset, sizeof(msg->err_text) - offset, fmt, args);
        va_end(args);
        snprintf(msg->err_text + offset, sizeof(msg->err_text) - offset, "\n");

        /* Make sure, if truncated, the last character is null */
        msg->err_text[(sizeof(msg->err_text) - 1)] = '\0';

#ifdef ENABLE_LOG
        if (log_id && log_id != DEV_LOG_INVALID_ID)
        {
            bcm_dev_log_log(log_id, DEV_LOG_LEVEL_ERROR, BCM_LOG_FLAG_CALLER_FMT, "%s", msg->err_text);
        }
#endif
    }

    return err;
}

typedef struct
{
    bcmolt_api_pm_copy_mode mode;
    void *dest;
} bcmolt_api_copy_field_ctxt;

static void _api_copy_field(const bcmolt_api_parse_field *field, void *context)
{
    bcmolt_api_copy_field_ctxt *ctxt = context;

    bcmolt_api_pm_copy_mode field_mode = ctxt->mode;
    if (ctxt->mode == BCMOLT_API_PM_COPY_MODE_DEST && field->in_union)
    {
        /* When using the dest mask (e.g. in a GET resquest handler), asking for the classifier field of a union
         * means "get me everything inside this union". However, when packing the request, the packer doesn't
         * know the classifier value, so it can't properly fill out the sub-presence masks. We need to reset all
         * of the sub-presence masks to 0, meaning "get all". */
        field_mode = BCMOLT_API_PM_COPY_MODE_IGNORE;
    }

    /* Structs & unions should be copied field-by-field */
    bcmolt_api_copy_field_generic(
        field->descr->type,
        (uint8_t *)ctxt->dest + field->descr->offset,
        field->data,
        field_mode);
}

static void _api_copy_elem(const bcmolt_api_parse_elem *elem, void *context)
{
    bcmolt_api_copy_field_ctxt *ctxt = context;

    /* Fixed-length arrays should be copied element-by-element */
    bcmolt_api_copy_field_generic(
        elem->elem_type,
        bcmolt_array_elem_data_get(elem->list_type, ctxt->dest, elem->idx),
        elem->data,
        ctxt->mode);
}

static void _api_copy_simple(const bcmolt_api_parse_simple *simple, void *context)
{
    bcmolt_api_copy_field_ctxt *ctxt = context;

    /* The field is simple - just copy it directly. */
    memcpy(ctxt->dest, simple->data, simple->type->size);
}

void bcmolt_api_copy_field_generic(
    const bcmolt_type_descr *type,
    void *dest,
    const void *src,
    bcmolt_api_pm_copy_mode mode)
{
    const void *pm_base;

    if (_is_raw_pointer_list(type))
    {
        /* Dynamic arrays can't be copied gracefully since it requires dynamic memory allocation. So, simply memcpy. */
        memcpy(dest, src, type->size);
        return;
    }

    switch (mode)
    {
    case BCMOLT_API_PM_COPY_MODE_SRC:
        pm_base = src;
        break;
    case BCMOLT_API_PM_COPY_MODE_DEST:
        pm_base = dest;
        break;
    default:
        pm_base = NULL;
        if (type->mask_offset != BCMOLT_TYPE_DESCR_NO_MASK)
        {
            /* If we don't know the right presence mask to use, always copy all fields. Push a presence mask of 0
             * into the destination struct to indicate all fields are valid. */
            bcmolt_api_zero_presence_mask(dest, type);
        }
        break;
    }

    bcmolt_api_copy_field_ctxt ctxt = { .mode = mode, .dest = dest };
    bcmolt_api_parse_separate_mask(
        pm_base,
        src,
        type,
        BCMOS_FALSE,
        NULL,
        &ctxt,
        _api_copy_field,
        _api_copy_elem,
        _api_copy_simple);
}

typedef struct
{
    const void *other;
    bcmos_bool match;
} bcmolt_api_check_field_equality_ctxt;

static void _check_equal_field(const bcmolt_api_parse_field *field, void *context)
{
    bcmolt_api_check_field_equality_ctxt *ctxt = context;

    /* Structs & unions should be compared field-by-field */
    ctxt->match = ctxt->match
        && bcmolt_api_check_field_equality_generic(
            field->descr->type,
            field->data,
            (const uint8_t *)ctxt->other + field->descr->offset);
}

static void _check_equal_elem(const bcmolt_api_parse_elem *elem, void *context)
{
    bcmolt_api_check_field_equality_ctxt *ctxt = context;

    /* Arrays should be compared element-by-element */
    ctxt->match = ctxt->match
        && bcmolt_api_check_field_equality_generic(
            elem->elem_type,
            elem->data,
            bcmolt_array_elem_data_get_const(elem->list_type, ctxt->other, elem->idx));
}

static void _check_equal_simple(const bcmolt_api_parse_simple *simple, void *context)
{
    bcmolt_api_check_field_equality_ctxt *ctxt = context;

    /* The field is simple - test for equality with memcmp */
    ctxt->match = ctxt->match && memcmp(simple->data, ctxt->other, simple->type->size) == 0;
}

bcmos_bool bcmolt_api_check_field_equality_generic(const bcmolt_type_descr *type, const void *a, const void *b)
{
    /* When comparing dynamically-sized arrays, we first need to check the size field. */
    if (type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN)
    {
        int64_t a_len = 0;
        int64_t b_len = 0;

        bcmolt_read_snum(type->x.arr_dyn.len_type->size, a, &a_len);
        bcmolt_read_snum(type->x.arr_dyn.len_type->size, b, &b_len);

        if (a_len != b_len)
        {
            return BCMOS_FALSE;
        }
    }

    bcmolt_api_check_field_equality_ctxt ctxt = { .other = b, .match = BCMOS_TRUE };
    bcmolt_api_parse(a, type, BCMOS_FALSE, NULL, &ctxt, _check_equal_field, _check_equal_elem, _check_equal_simple);
    return ctxt.match;
}

static void _copy_multiget_field(const bcmolt_api_parse_field *field, void *context)
{
    if (_is_raw_pointer_list(field->descr->type))
    {
        BCMOLT_API_UTILS_PRINTF("Dynamically-sized arrays are not supported for multi-get\n");
        bcmolt_api_clear_presence_mask_bit(field->parent_data, field->parent_type, field->descr->id);
    }
    else
    {
        bcmolt_api_set_presence_mask_bit(field->parent_data, field->parent_type, field->descr->id);
        bcmolt_api_copy_multiget_presence_mask(field->descr->type, field->data, field->mask);
    }
}

static void _copy_multiget_elem(const bcmolt_api_parse_elem *elem, void *context)
{
    bcmolt_api_set_presence_mask_bit(elem->list_data, elem->list_type, elem->idx);
    bcmolt_api_copy_multiget_presence_mask(elem->elem_type, elem->data, elem->mask);
}

void bcmolt_api_copy_multiget_presence_mask(const bcmolt_type_descr *type, void *dest, const void *src)
{
    bcmolt_api_parse_separate_mask(
        src,
        dest,
        type,
        BCMOS_FALSE,
        NULL,
        NULL,
        _copy_multiget_field,
        _copy_multiget_elem,
        NULL);
}

#ifdef ENABLE_LOG
/* Buffer to accommodate the output of the API writer, before we apply the loop that breaks into separate logger lines
 * in every '\n' */
#define BCMOLT_API_MSG_LOG_REC_SIZE 8192

/* maximum number of tasks that can use the API/logger integration simultaneously */
#define BCMOLT_API_MSG_LOG_NUM_BLKS 16

/* string that denotes that this entry is not complete - there is more data to come */
#define BCMOLT_API_MSG_LOG_CONT_STR "..."

/* number of characters reserved at the end of each log entry (continuation string + newline) */
typedef struct
{
    dev_log_id log_id;
    const bcmolt_msg *msg;
    char *buf;
    uint32_t used;
} bcmolt_api_msg_log_rec;

static bcmos_blk_pool bcmolt_api_msg_log_blk_pool;

static inline uint32_t bcmolt_api_msg_log_buf_remaining(const bcmolt_api_msg_log_rec *rec)
{
    return BCMOLT_API_MSG_LOG_REC_SIZE - rec->used;
}

static void bcmolt_api_msg_log_flush(bcmolt_api_msg_log_rec *rec, bcmos_bool is_truncation)
{
    char *s;
    char *new_line;
    char *end_pos;
    char *trim_pos;
    char log_str[MAX_DEV_LOG_STRING_NET_SIZE];
    bcmos_bool is_first = BCMOS_TRUE;

    s = rec->buf;
    while (*s)
    {
        end_pos = s + strlen(s);
        new_line = strchr(s, '\n');
        if (!new_line)
            new_line = end_pos;

        /* Find what comes first:
         * 1. Natural end of string ('\0')
         * 2. New line ('\n')
         * 3. Maximum Size of logger string */
        trim_pos = MIN3(end_pos, new_line, s + MAX_DEV_LOG_STRING_NET_SIZE - 2 * strlen(BCMOLT_API_MSG_LOG_CONT_STR));
        strncpy(log_str, s, trim_pos - s);
        log_str[trim_pos - s] = '\0';
        if (trim_pos == end_pos)
        {
            /* This is the last line, because we found the natural end of string first. */
            bcm_dev_log_log(
                rec->log_id,
                DEV_LOG_LEVEL_INFO,
                BCM_LOG_FLAG_CALLER_FMT,
                "%s%s\n",
                is_first ? "" : BCMOLT_API_MSG_LOG_CONT_STR,
                log_str);
            break;
        }

        /* Calculate the position of the next line. */
        if (trim_pos == new_line)
        {
            /* The string got trimmed as a result of '\n'. Continue from the character that follows. */
            s = trim_pos + 1;
        }
        else
        {
            /* The string got trimmed as a result of insufficient place in a logger string. */
            s = trim_pos;
        }

        /* Not the last line:
         * 1. If this is not the first line (continuation line), then add "..." as a prefix.
         * 1. If the next line is not empty, then add "..." as a suffix. */
        bcm_dev_log_log(
            rec->log_id,
            DEV_LOG_LEVEL_INFO,
            BCM_LOG_FLAG_CALLER_FMT,
            "%s%s%s\n",
            is_first ? "" : BCMOLT_API_MSG_LOG_CONT_STR,
            log_str,
            *s ? BCMOLT_API_MSG_LOG_CONT_STR : "");

        is_first = BCMOS_FALSE;
    }

    if (is_truncation)
        bcm_dev_log_log(rec->log_id, DEV_LOG_LEVEL_WARNING, BCM_LOG_FLAG_CALLER_FMT, "<logger string got truncated>\n");

    rec->used = 0;
}

#ifdef BCM_SUBSYSTEM_EMBEDDED
extern const char *last_format;
#endif
static void bcmolt_api_msg_log_write_cb(void *user_data, const char *format, va_list ap)
{
    int ret;
    bcmolt_api_msg_log_rec *rec = user_data;

#ifdef BCM_SUBSYSTEM_EMBEDDED
    last_format = format;
#endif
    ret = vsnprintf(rec->buf + rec->used, bcmolt_api_msg_log_buf_remaining(rec), format, ap);

    if (ret < 0 || ret >= bcmolt_api_msg_log_buf_remaining(rec))
        bcmolt_api_msg_log_flush(rec, BCMOS_TRUE);
    else
        rec->used += ret;
}

bcmos_errno bcmolt_api_msg_log(dev_log_id log_id, bcmolt_msg *msg)
{
    bcmos_errno err = BCM_ERR_OK;
    bcmolt_api_msg_log_rec rec = { .log_id = log_id, .msg = msg, .used = 0 };
    bcmolt_metadata_writer writer = { .write_cb = bcmolt_api_msg_log_write_cb, .user_data = &rec };

    rec.buf = bcmos_blk_pool_alloc(&bcmolt_api_msg_log_blk_pool);
    if (!rec.buf)
    {
        err = BCM_ERR_NOMEM;
        goto exit;
    }

    bcmolt_api_write_msg(&writer, msg, BCMOLT_METADATA_WRITE_STYLE_SPACE_SEPARATED);
    bcmolt_api_msg_log_flush(&rec, BCMOS_FALSE);

exit:
    if (rec.buf)
        bcmos_blk_pool_free(rec.buf);
    if (err != BCM_ERR_OK)
        BCM_LOG(ERROR, log_id, "API message log error: %s (%d)\n", bcmos_strerror(err), err);
    return err;
}
#endif

static uint32_t bcmolt_api_apply_tags(uint32_t cur_tags, uint32_t new_tags)
{
    /* The PROPRIETARY tag is the only tag that doesn't override the inherited tags. */
#ifdef BCMOLT_CONFIG_MODE_PROPRIETARY
    if (new_tags == BCMOLT_TAG_PROPRIETARY)
    {
        return cur_tags | BCMOLT_TAG_PROPRIETARY;
    }
#endif
    return new_tags == 0 ? cur_tags : new_tags;
}

bcmolt_tag bcmolt_api_get_field_tags(
    const bcmolt_msg *msg,
    const bcmolt_api_prop_path *path,
    const bcmolt_field_descr *field)
{
    const bcmolt_api_prop_node *node;
    const bcmolt_obj_descr *obj;
    const bcmolt_group_descr *group;
    uint32_t tags;

    if (bcmolt_api_obj_descr_get(msg->obj_type, &obj) != BCM_ERR_OK
        || bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group) != BCM_ERR_OK)
    {
        return BCMOLT_TAG__NONE;
    }

    tags = bcmolt_api_apply_tags(obj->tags, group->tags);
    for (node = &path->nodes[0]; node->type != BCMOLT_API_PROP_NODE_TYPE_INVALID; node++)
    {
        if ((node->type == BCMOLT_API_PROP_NODE_TYPE_FIELD) || (node->type == BCMOLT_API_PROP_NODE_TYPE_UNION_FIELD))
        {
            tags = bcmolt_api_apply_tags(tags, node->u.field->tags);
        }
    }
    tags = bcmolt_api_apply_tags(tags, field->tags);
    return (bcmolt_tag)tags;
}

bcmos_errno bcmolt_api_utils_init(void)
{
#ifdef ENABLE_LOG
    bcmos_blk_pool_parm blk_pool_parm =
    {
        .name = "api_msg_log",
        .blk_size = BCMOLT_API_MSG_LOG_REC_SIZE,
        .num_blks = BCMOLT_API_MSG_LOG_NUM_BLKS,
    };

    return bcmos_blk_pool_create(&bcmolt_api_msg_log_blk_pool, &blk_pool_parm);
#else
    return BCM_ERR_OK;
#endif
}
