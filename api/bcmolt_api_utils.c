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

/* Helper macro for parsing API structs */
#define BCMOLT_API_PARSE_FIELD(_pm_base, _data, _type_desc, _per_field, _per_elem, _per_simple) \
    do \
    { \
        uint32_t i; \
        bcmolt_presence_mask mask; \
        const bcmolt_field_descr *field; \
        int num_union_vals = 0; \
        \
        switch ((_type_desc)->base_type) \
        { \
        case BCMOLT_BASE_TYPE_ID_STRUCT: \
            /* process struct fields */ \
            mask = bcmolt_api_get_presence_mask((_pm_base), (_type_desc)); \
            for (i = 0; i < (_type_desc)->x.s.num_fields; i++) \
            { \
                field = &(_type_desc)->x.s.fields[i]; \
                if ((mask == 0) || ((mask & (1ULL << field->id)) != 0)) \
                { \
                    _per_field \
                } \
            } \
            break; \
        case BCMOLT_BASE_TYPE_ID_UNION: \
            /* process common fields */ \
            mask = bcmolt_api_get_presence_mask((_pm_base), (_type_desc)); \
            for (i = 0; i < (_type_desc)->x.u.num_common_fields; i++) \
            { \
                /* copy the common fields */ \
                field = &(_type_desc)->x.u.common_fields[i]; \
                if ((mask == 0) || ((mask & (1ULL << field->id)) != 0)) \
                { \
                    _per_field \
                } \
            } \
            /* process union fields */ \
            field = &(_type_desc)->x.u.common_fields[(_type_desc)->x.u.classifier_idx]; \
            if ((mask == 0) || ((mask & (1ULL << field->id)) != 0)) \
            { \
                int64_t selector_val; \
                if (BCM_ERR_OK == bcmolt_read_snum( \
                    field->type->size, \
                    (void *)((long)(_data) + field->offset), \
                    &selector_val)) \
                { \
                    num_union_vals = bcmolt_get_num_enum_vals(field->type->x.e.vals); \
                    if ((unsigned)selector_val < num_union_vals) \
                    { \
                        field = &(_type_desc)->x.u.union_fields[selector_val]; \
                        if (field->name != NULL) \
                        { \
                            _per_field \
                        } \
                    } \
                } \
                else \
                { \
                    BCMOS_TRACE_ERR("bcmolt_read_snum() failed \n"); \
                } \
            } \
            break; \
        case BCMOLT_BASE_TYPE_ID_ARR_FIXED: \
            /* process fixed array elements */ \
            mask = bcmolt_api_get_presence_mask((_pm_base), (_type_desc)); \
            for (i = 0; i < (_type_desc)->x.arr_fixed.size; i++) \
            { \
                if ((mask == 0) || i >= 64 || ((mask & (1ULL << i)) != 0)) \
                { \
                    const bcmolt_type_descr *elem_type = (_type_desc)->x.arr_fixed.elem_type; \
                    _per_elem \
                } \
            } \
            break; \
        case BCMOLT_BASE_TYPE_ID_ARR_DYN: \
        { \
            int64_t array_len; \
            /* process dynamic array elements */ \
            if (BCM_ERR_OK == bcmolt_read_snum((_type_desc)->x.arr_dyn.len_type->size, (_data), &array_len)) \
            { \
                mask = bcmolt_api_get_presence_mask((_pm_base), (_type_desc)); \
                for (i = 0; i < array_len; i++) \
                { \
                    if ((mask == 0) || i >= 64 || ((mask & (1ULL << i)) != 0)) \
                    { \
                        const bcmolt_type_descr *elem_type = (_type_desc)->x.arr_dyn.elem_type; \
                        _per_elem \
                    } \
                } \
            } \
            else \
            { \
                BCMOS_TRACE_ERR("bcmolt_read_snum() failed \n"); \
            } \
            break; \
        } \
        default: \
            _per_simple \
            break; \
        } \
    } while (0)

static uint8_t *bcmolt_array_elem_data_get(const bcmolt_type_descr *type, void *arr_ptr, uint32_t i)
{
    if (type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN)
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
    if (type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN)
    {
        const void *arr_data_ptr = (const uint8_t *)arr_ptr + type->x.arr_dyn.data_offset;
        return *(uint8_t * const *)arr_data_ptr + (i * type->x.arr_dyn.elem_type->size);
    }
    else
    {
        return (const uint8_t *)arr_ptr + type->x.arr_fixed.data_offset + (i * type->x.arr_fixed.elem_type->size);
    }
}

// Check if the given type contains (at any depth) any dynamically-sized arrays for which the presence mask bit is
// SPECIFICALLY set (the overall PM is not all 0s).
static bcmos_bool bcmolt_type_has_explicit_dynamic_array(const bcmolt_type_descr *type, const void *data)
{
    BCMOLT_API_PARSE_FIELD(data, data, type,
        if ((mask != 0) && ((field->type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN)
            || (field->type->base_type == BCMOLT_BASE_TYPE_ID_BINARY_DYN)))
        {
            return BCMOS_TRUE;
        }
        if (bcmolt_type_has_explicit_dynamic_array(field->type, (const uint8_t *)data + field->offset))
        {
            return BCMOS_TRUE;
        }
        ,
        if (bcmolt_type_has_explicit_dynamic_array(elem_type, bcmolt_array_elem_data_get_const(type, data, i)))
        {
            return BCMOS_TRUE;
        }
        ,
        );
    return BCMOS_FALSE;
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
                return BCMOLT_MSG_ERR(
                    msg,
                    DEV_LOG_INVALID_ID,
                    BCM_ERR_PARM,
                    "At least one parameter must be set");
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

static bcmos_bool _bcmolt_api_prop_tree_is_set(const bcmolt_api_prop_tree *tree, uint32_t prop, const bcmolt_api_prop_tree **prop_match)
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

    for (i = 0; i < type_descr->x.s.num_fields; i++)
        presence_mask_all |= 1ULL << type_descr->x.s.fields[i].id;

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

static bcmos_errno bcmolt_api_prop_iter_2nd_level(
    const bcmolt_msg *msg,
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
        const bcmolt_field_descr *field_descr = NULL; /* Initialize to NULL to avoid compiler warning about uninitialized variable. */
        const bcmolt_api_prop_tree *prop_match;

        next_prop--;

        for (i = 0; i < type_descr->x.s.num_fields; i++)
        {
            field_descr = &type_descr->x.s.fields[i];
            if (field_descr->id == next_prop)
                break;
        }
        BUG_ON(i == type_descr->x.s.num_fields);

        BCMOLT_API_UTILS_PRINTF("\tScanning '%s%s'", bcmolt_string_indent(path_str, sizeof(path_str), curr_depth + 1), field_descr->name);

        path->nodes[curr_depth].type = BCMOLT_API_PROP_NODE_TYPE_FIELD;
        path->nodes[curr_depth].u.field = field_descr;
        /* If 'tree' is NULL and _bcmolt_api_prop_tree_is_set() returns true, then prop_match would become NULL. */
        if (_bcmolt_api_prop_tree_is_set(tree, next_prop, &prop_match))
        {
            if (field_descr->type->base_type != BCMOLT_BASE_TYPE_ID_STRUCT || (prop_match && (!prop_match->sub_tree || prop_match->data)))
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
                rc = bcmolt_api_prop_iter_2nd_level(msg, data + field_descr->offset, field_descr->type, prop_match ? prop_match->sub_tree : NULL, cb, context, path, curr_depth + 1);
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

bcmos_errno bcmolt_api_prop_iter_func(const bcmolt_msg *msg, const bcmolt_api_prop_tree *tree, bcmolt_api_prop_iter_cb cb, void *context, const char *func, int line)
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
    return bcmolt_api_prop_iter_2nd_level(msg, msg_data, group_descr->type, tree, cb, context, &path, 0);
}

static bcmos_errno bcmolt_api_prop_tree_is_set_cb(const bcmolt_field_descr *field_descr, const uint8_t *field_data, const bcmolt_api_prop_tree *node, void *context,
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

bcmos_bool bcmolt_api_prop_tree_is_set(const bcmolt_msg *msg, const bcmolt_api_prop_tree *tree, bcmolt_api_prop_path *path)
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

/* Return BCMOS_TRUE if the recursion found that the requested property is present. */
static bcmos_bool _prop_is_set(
    const uint8_t *data,
    const bcmolt_type_descr *type_descr,
    const uint8_t *prop_ptr,
    bcmolt_api_prop_path *path,
    bcmos_bool force_presence_mask_all)
{
    const uint8_t *elem_data;

    if (path != NULL)
    {
        path->curr_depth++;
    }

    /* The first argument (pm_base) can be NULL to cause presence mask to become "all" in all levels. */
    BCMOLT_API_PARSE_FIELD(force_presence_mask_all ? NULL : data, data, type_descr,
        /* Recursively check the offset of every field in every struct/union */
        if (path != NULL)
        {
            path->nodes[path->curr_depth - 1].type = BCMOLT_API_PROP_NODE_TYPE_FIELD;
            path->nodes[path->curr_depth - 1].u.field = field;
        }

        if (data + field->offset == prop_ptr) /* Match -> stop the recursion. */
        {
            return BCMOS_TRUE;
        }

        if (_prop_is_set(data + field->offset, field->type, prop_ptr, path, force_presence_mask_all))
        {
            return BCMOS_TRUE;
        }
        ,
        /* Recursively check the offset of every index in the array */
        if (path != NULL)
        {
            path->nodes[path->curr_depth - 1].type = BCMOLT_API_PROP_NODE_TYPE_ARRAY_INDEX;
            path->nodes[path->curr_depth - 1].u.array_index = i;
        }

        elem_data = bcmolt_array_elem_data_get_const(type_descr, data, i);
        if (elem_data == prop_ptr)
        {
            return BCMOS_TRUE;
        }

        if (_prop_is_set(elem_data, elem_type, prop_ptr, path, force_presence_mask_all))
        {
            return BCMOS_TRUE;
        }
        ,
        /* Nothing to do for simple values */
        );

    if (path != NULL)
    {
        path->nodes[path->curr_depth - 1].type = BCMOLT_API_PROP_NODE_TYPE_INVALID;
        path->curr_depth--;
    }

    return BCMOS_FALSE;
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
    uint32_t i;
    const bcmolt_group_descr *group_descr;
    const bcmolt_type_descr *type_descr;
    uint8_t *data;
    bcmolt_api_prop_path path = {};

    rc = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group_descr);
    BCMOS_RETURN_ON_ERROR(rc);
    data = (uint8_t *)msg + group_descr->data_offset;

    /* Call _prop_is_set() just to fill in the full path. */
    _prop_is_set(data, group_descr->type, prop_ptr, &path, BCMOS_TRUE);

    type_descr = group_descr->type;
    for (i = 0; i < path.curr_depth; i++)
    {
        uint16_t id = 0;
        const bcmolt_type_descr *parent_type_descr = type_descr;
        uint8_t *parent_data = data;

        switch (path.nodes[i].type)
        {
        case BCMOLT_API_PROP_NODE_TYPE_FIELD:
            id = path.nodes[i].u.field->id;
            data += path.nodes[i].u.field->offset;
            type_descr = path.nodes[i].u.field->type;
            break;
        case BCMOLT_API_PROP_NODE_TYPE_ARRAY_INDEX:
            id = path.nodes[i].u.array_index;
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
            if (i == path.curr_depth - 1) /* only clear the lowest-level presence mask */
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

void bcmolt_api_copy_field_generic(
    const bcmolt_type_descr *type,
    void *dest,
    const void *src,
    bcmolt_api_pm_copy_mode mode)
{
    const void *pm_base;

    if (type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN)
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

    BCMOLT_API_PARSE_FIELD(pm_base, src, type,
        bcmolt_api_pm_copy_mode field_mode = mode;
        if (mode == BCMOLT_API_PM_COPY_MODE_DEST && num_union_vals > 0)
        {
            /* When using the dest mask (e.g. in a GET resquest handler), asking for the classifier field of a union
             * means "get me everything inside this union". However, when packing the request, the packer doesn't
             * know the classifier value, so it can't properly fill out the sub-presence masks. We need to reset all
             * of the sub-presence masks to 0, meaning "get all". */
            field_mode = BCMOLT_API_PM_COPY_MODE_IGNORE;
        }

        /* Structs & unions should be copied field-by-field */
        bcmolt_api_copy_field_generic(
            field->type,
            (uint8_t *)dest + field->offset,
            (const uint8_t *)src + field->offset,
            field_mode);
        ,
        /* Fixed-length arrays should be copied element-by-element */
        bcmolt_api_copy_field_generic(
            elem_type,
            bcmolt_array_elem_data_get(type, dest, i),
            bcmolt_array_elem_data_get_const(type, src, i),
            mode);
        ,
        /* The field is simple - just copy it directly. */
        memcpy(dest, src, type->size);
        );
}

bcmos_bool bcmolt_api_check_field_equality_generic(const bcmolt_type_descr *type, const void *a, const void *b)
{
    bcmos_bool match = BCMOS_TRUE;

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

    BCMOLT_API_PARSE_FIELD(a, a, type,
        /* Structs & unions should be compared field-by-field */
        match = match && bcmolt_api_check_field_equality_generic(
            field->type,
            (const uint8_t *)a + field->offset,
            (const uint8_t *)b + field->offset);
        ,
        /* Arrays should be compared element-by-element */
        match = match && bcmolt_api_check_field_equality_generic(
            elem_type,
            bcmolt_array_elem_data_get_const(type, a, i),
            bcmolt_array_elem_data_get_const(type, b, i));
        ,
        /* The field is simple - test for equality with memcmp */
        match = match && memcmp(a, b, type->size) == 0;
        );

    return match;
}

void bcmolt_api_copy_multiget_presence_mask(const bcmolt_type_descr *type, void *dest, const void *src)
{
    BCMOLT_API_PARSE_FIELD(src, dest, type,

        if (field->type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN
            || field->type->base_type == BCMOLT_BASE_TYPE_ID_BINARY_DYN)
        {
            BCMOLT_API_UTILS_PRINTF("Dynamically-sized arrays are not supported for multi-get\n");
            bcmolt_api_clear_presence_mask_bit(dest, type, field->id);
        }
        else
        {
            bcmolt_api_set_presence_mask_bit(dest, type, field->id);
            bcmolt_api_copy_multiget_presence_mask(
                field->type,
                (uint8_t *)dest + field->offset,
                (const uint8_t *)src + field->offset);
        }
        ,

        bcmolt_api_set_presence_mask_bit(dest, type, i);
        bcmolt_api_copy_multiget_presence_mask(
            elem_type,
            bcmolt_array_elem_data_get(type, dest, i),
            bcmolt_array_elem_data_get_const(type, src, i));
        ,

        /* The field is simple, there's no presence mask, do nothing */
        );
}

#ifdef ENABLE_LOG
/* Buffer to accommodate the output of the API writer, before we apply the loop that breaks into separate logger lines in every '\n' */
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
            bcm_dev_log_log(rec->log_id, DEV_LOG_LEVEL_INFO, BCM_LOG_FLAG_CALLER_FMT, "%s%s\n", is_first ? "" : BCMOLT_API_MSG_LOG_CONT_STR, log_str);
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
        bcm_dev_log_log(rec->log_id, DEV_LOG_LEVEL_INFO, BCM_LOG_FLAG_CALLER_FMT, "%s%s%s\n",
            is_first ? "" : BCMOLT_API_MSG_LOG_CONT_STR, log_str, *s ? BCMOLT_API_MSG_LOG_CONT_STR : "");

        is_first = BCMOS_FALSE;
    }

    if (is_truncation)
        bcm_dev_log_log(rec->log_id, DEV_LOG_LEVEL_WARNING, BCM_LOG_FLAG_CALLER_FMT, "<logger string got truncated>\n");

    rec->used = 0;
}


#ifdef BCM_SUBSYSTEM_EMBEDDED
extern const char * last_format;
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
        if (node->type == BCMOLT_API_PROP_NODE_TYPE_FIELD)
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
