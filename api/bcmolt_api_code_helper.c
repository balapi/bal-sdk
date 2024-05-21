/*
<:copyright-BRCM:2016-2024:Apache:standard
 
 Copyright (c) 2016-2024 Broadcom. All Rights Reserved
 
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
#include <bcmolt_bit_utils.h>
#include <bcmolt_api.h>
#include "bcmolt_api_code_helper.h"

#define OLT_REF "olt_id"
#define RC_REF "rc"
#define MSG_REF "msg"
#define DATA_REF "data"
#define KEY_REF "key"
#define LIST_MEM_REF "list_mem"
#define DYN_LIST_SIZE "APICLI_DYNAMIC_LIST_BUFFER_SIZE"

static bcmos_bool _api_code_need_list_mem(const bcmolt_msg *msg, const bcmolt_group_descr *group_descr)
{
    return (msg->type == BCMOLT_MSG_TYPE_GET) && (msg->group == BCMOLT_MGT_GROUP_CFG)
        && bcmolt_type_may_have_dynamic_array(group_descr->type, (void *)((long)msg + group_descr->data_offset));
}

static void bcmolt_api_code_write_upper(const bcmolt_metadata_writer *writer, const char *src)
{
    while (*src != '\0')
    {
        bcmolt_metadata_write(writer, "%c", (char)toupper((int)*src));
        ++src;
    }
}

static void _api_code_write_path(const bcmolt_metadata_writer *writer, const bcmolt_api_prop_path *path)
{
    if (path == NULL)
    {
        bcmolt_metadata_write(writer, "NULL");
        return;
    }

    for (uint32_t i = 0; i < path->curr_depth; ++i)
    {
        if (i != 0)
        {
            bcmolt_metadata_write(writer, ".");
        }
        switch (path->nodes[i].type)
        {
        case BCMOLT_API_PROP_NODE_TYPE_FIELD:
            bcmolt_metadata_write(writer, path->nodes[i].u.field->name);
            break;
        case BCMOLT_API_PROP_NODE_TYPE_UNION_FIELD:
            bcmolt_metadata_write(writer, "u.%s", path->nodes[i].u.field->name);
            break;
        case BCMOLT_API_PROP_NODE_TYPE_ARRAY_INDEX:
            bcmolt_metadata_write(writer, "arr[%u]", path->nodes[i].u.array_index);
            break;
        default:
            break;
        }
    }
}

typedef struct
{
    const bcmolt_metadata_writer *writer;
    bcmos_bool is_multi;
} api_code_context;

/* start get fields */
static void _get_fields_recurse(
    const bcmolt_type_descr *type,
    const void *data,
    bcmolt_api_prop_path *path,
    api_code_context *ctxt);

static void _get_fields_simple(const bcmolt_api_parse_simple *simple, void *context)
{
    api_code_context *ctxt = context;

    bcmolt_metadata_write_indented(
        ctxt->writer,
        1,
        "%s(%s" MSG_REF ", ",
        ctxt->is_multi ? "BCMOLT_MULTI_MSG_FIELD_GET" : "BCMOLT_MSG_FIELD_GET",
        ctxt->is_multi ? "" : "&");
    _api_code_write_path(ctxt->writer, simple->path);
    bcmolt_metadata_write(ctxt->writer, ");\n");
}

static void _get_fields_pm_check(
    const bcmolt_type_descr *type,
    void *mask,
    void *data,
    bcmolt_api_prop_path *path,
    api_code_context *ctxt)
{
    const bcmolt_presence_mask *pm = bcmolt_api_get_presence_mask_ptr(data, type);

    if ((pm == NULL) || (*pm == 0) || BITS_SET(*pm, bcmolt_api_get_presence_mask_all(type)))
    {
        _get_fields_simple(
            &(const bcmolt_api_parse_simple){ .type = type, .mask = mask, .data = data, .path = path },
            ctxt);
    }
    else
    {
        _get_fields_recurse(type, data, path, ctxt);
    }
}

static void _get_fields_field(const bcmolt_api_parse_field *field, void *context)
{
    api_code_context *ctxt = context;

    switch (field->descr->type->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_STRUCT:
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
        _get_fields_pm_check(field->descr->type, field->mask, field->data, field->path, ctxt);
        break;
    case BCMOLT_BASE_TYPE_ID_UNION:
        /* don't recurse into unions on gets - we don't have the selector value - just treat it as a simple type */
        _get_fields_simple(
            &(bcmolt_api_parse_simple){
                .type = field->descr->type,
                .mask = field->mask,
                .data = field->data,
                .path = field->path },
            ctxt);
        break;
    default:
        _get_fields_recurse(field->descr->type, field->data, field->path, ctxt);
        break;
    }
}

static void _get_fields_elem(const bcmolt_api_parse_elem *elem, void *context)
{
    api_code_context *ctxt = (api_code_context *)context;

    _get_fields_pm_check(elem->elem_type, elem->mask, elem->data, elem->path, ctxt);
}

static void _get_fields_recurse(
    const bcmolt_type_descr *type,
    const void *data,
    bcmolt_api_prop_path *path,
    api_code_context *ctxt)
{
    bcmolt_api_parse(data, type, BCMOS_FALSE, path, ctxt, _get_fields_field, _get_fields_elem, _get_fields_simple);
}

static void bcmolt_api_code_get_fields(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *type,
    const void *data,
    bcmos_bool is_multi)
{
    if (type != NULL)
    {
        bcmolt_api_prop_path path = {};
        api_code_context ctxt = { .writer = writer, .is_multi = is_multi };
        _get_fields_recurse(type, data, &path, &ctxt);
    }
}
/* end get fields */

/* start set fields */
static void _set_feilds_recurse(
    const bcmolt_type_descr *type,
    const void *data,
    bcmolt_api_prop_path *path,
    api_code_context *ctxt);

static void _set_fields_field(const bcmolt_api_parse_field *field, void *context)
{
    api_code_context *ctxt = context;

    switch (field->descr->type->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
        /* point API struct to anonymous stack aray if needed */
        if (!field->descr->type->x.arr_dyn.is_array_backend)
        {
            bcmolt_metadata_write_indented(ctxt->writer, 1, MSG_REF "." DATA_REF ".");
            _api_code_write_path(ctxt->writer, field->path);
            bcmolt_metadata_write(
                ctxt->writer,
                ".arr = (bcmolt_%s[%u]){ };\n",
                field->descr->type->x.arr_dyn.elem_type->name,
                bcmolt_api_get_list_len(field->descr->type, field->data));
        }

        bcmolt_metadata_write_indented(ctxt->writer, 1, MSG_REF"."DATA_REF".");
        _api_code_write_path(ctxt->writer, field->path);
        bcmolt_metadata_write(ctxt->writer, ".len = %u;\n", bcmolt_api_get_list_len(field->descr->type, field->data));
        break;
    default:
        break;
    }

    _set_feilds_recurse(field->descr->type, field->data, field->path, ctxt);
}

static void _set_fields_elem(
    const bcmolt_api_parse_elem*elem,
    void *context)
{
    api_code_context *ctxt = (api_code_context *)context;

    bcmolt_metadata_write_indented(ctxt->writer, 1, "(void)BCMOLT_ARRAY_ELEM_SET_PRESENT(&"MSG_REF"."DATA_REF".");
    /* we need the path of the elements owner */
    --elem->path->curr_depth;
    _api_code_write_path(ctxt->writer, elem->path);
    ++elem->path->curr_depth;
    bcmolt_metadata_write(ctxt->writer, ", %u);\n", elem->idx);

    _set_feilds_recurse(elem->elem_type, elem->data, elem->path, ctxt);
}

static void _set_fields_simple(const bcmolt_api_parse_simple *simple, void *context)
{
    api_code_context *ctxt = context;

    bcmolt_metadata_write_indented(
        ctxt->writer,
        1,
        "%s(%s" MSG_REF ", ",
        ctxt->is_multi ? "BCMOLT_MULTI_MSG_FILTER_SET" : "BCMOLT_MSG_FIELD_SET",
        ctxt->is_multi ? "" : "&");
    _api_code_write_path(ctxt->writer, simple->path);
    bcmolt_metadata_write(ctxt->writer, ", ");
    bcmolt_metadata_write_elem(
        ctxt->writer,
        simple->type,
        simple->data,
        "",
        BCMOLT_METADATA_WRITE_STYLE_C_INIT,
        0,
        "",
        "");
    bcmolt_metadata_write(ctxt->writer, ");\n");
}

static void _set_feilds_recurse(
    const bcmolt_type_descr *type,
    const void *data,
    bcmolt_api_prop_path *path,
    api_code_context *ctxt)
{
    bcmolt_api_parse(data, type, BCMOS_FALSE, path, ctxt, _set_fields_field, _set_fields_elem, _set_fields_simple);
}

static void bcmolt_api_code_set_fields(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *type,
    const void *data,
    bcmos_bool is_multi)
{
    if (type != NULL)
    {
        bcmolt_api_prop_path path = {};
        api_code_context ctxt = { .writer = writer, .is_multi = is_multi };
        _set_feilds_recurse(type, data, &path, &ctxt);
    }
}
/* end set fields */

static const char* bcmolt_api_code_get_stat_flags(const bcmolt_msg *msg)
{
    return ((msg->type & BCMOLT_MSG_TYPE_CLEAR) == 0) ? "BCMOLT_STAT_FLAGS_NONE" : "BCMOLT_STAT_FLAGS_CLEAR_ON_READ";
}

static const char* bcmolt_api_code_get_multi_flags(const bcmolt_msg *msg)
{
    switch (((const bcmolt_multi_msg *)msg)->filter_flags)
    {
    case BCMOLT_FILTER_FLAGS_NONE:
        return "BCMOLT_FILTER_FLAGS_NONE";
    case BCMOLT_FILTER_FLAGS_INVERT_SELECTION:
        return "BCMOLT_FILTER_FLAGS_INVERT_SELECTION";
    case BCMOLT_FILTER_FLAGS_DISABLE_FILTER:
        return "BCMOLT_FILTER_FLAGS_DISABLE_FILTER";
    default:
        return "<INVALID>";
    }
}

static void bcmolt_api_code_write_api_call(const bcmolt_metadata_writer *writer, const bcmolt_msg *msg)
{
    bcmolt_metadata_write(writer, "bcmolt_");
    if ((msg->type & BCMOLT_MSG_TYPE_MULTI) != 0)
    {
        bcmolt_metadata_write(writer, "multi_");
    }
    bcmolt_metadata_write(writer, "%s_", bcmolt_mgt_group_to_str(msg->group));
    if ((msg->type & BCMOLT_MSG_TYPE_GET) != 0)
    {
        bcmolt_metadata_write(writer, "get");
    }
    if ((msg->type & BCMOLT_MSG_TYPE_SET) != 0)
    {
        if (msg->group == BCMOLT_MGT_GROUP_OPER)
        {
            bcmolt_metadata_write(writer, "submit");
        }
        else
        {
            bcmolt_metadata_write(writer, "set");
        }
    }
    if ((msg->type & BCMOLT_MSG_TYPE_CLEAR) != 0)
    {
        if (msg->group == BCMOLT_MGT_GROUP_CFG)
        {
            bcmolt_metadata_write(writer, "clear");
        }
    }
}

bcmos_errno bcmolt_api_code_generate(const bcmolt_metadata_writer *writer, const bcmolt_msg *msg)
{
    bcmos_errno err;
    const bcmolt_obj_descr *obj_descr;
    const bcmolt_group_descr *key_descr;
    const bcmolt_group_descr *group_descr;
    const void *key;
    const void *data = NULL;
    const void *multi_filter = NULL;
    const void *multi_request = NULL;
    bcmos_bool need_list_mem = BCMOS_FALSE;
    bcmos_bool is_multi = ((msg->type & BCMOLT_MSG_TYPE_MULTI) != 0);

    err = bcmolt_api_obj_descr_get(msg->obj_type, &obj_descr);
    BCMOS_RETURN_IF_ERROR(err);
    err = bcmolt_api_group_descr_get(msg->obj_type, BCMOLT_MGT_GROUP_KEY, 0, &key_descr);
    BCMOS_RETURN_IF_ERROR(err);
    err = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group_descr);
    BCMOS_RETURN_IF_ERROR(err);

    /* init variables */
    bcmolt_metadata_write_indented(writer, 1, "{\n");
    bcmolt_metadata_write_indented(writer, 1, "bcmos_errno "RC_REF";\n");
    if (!is_multi)
    {
        key = (void *)((long)msg + group_descr->key_offset);
        data = (void *)((long)msg + group_descr->data_offset);
        bcmolt_metadata_write_indented(writer, 1, "bcmolt_%s_%s", obj_descr->name, group_descr->name);
        if (msg->group == BCMOLT_MGT_GROUP_STAT_CFG)
        {
            bcmolt_metadata_write(writer, "_cfg");
        }
        bcmolt_metadata_write(writer, " "MSG_REF";\n");
        need_list_mem = _api_code_need_list_mem(msg, group_descr);
    }
    else
    {
        key = (void *)((long)msg + group_descr->multi->key_offset);
        multi_filter = (void *)((long)msg + group_descr->multi->filter_offset);
        multi_request = (void *)((long)msg + group_descr->multi->request_offset);
        bcmolt_metadata_write_indented(
            writer,
            1,
            "bcmolt_%s_multi_%s *" MSG_REF ";\n",
            obj_descr->name,
            group_descr->name);
    }
    bcmolt_metadata_write_indented(writer, 1, "bcmolt_%s_key "KEY_REF" = ", obj_descr->name);
    bcmolt_metadata_write_elem(
        writer,
        key_descr->type,
        key,
        key_descr->name,
        BCMOLT_METADATA_WRITE_STYLE_C_INIT,
        0,
        "",
        "");
    bcmolt_metadata_write(writer, ";\n");

    if (need_list_mem)
    {
        bcmolt_metadata_write_indented(writer, 1, "uint8_t *"LIST_MEM_REF" = bcmos_calloc("DYN_LIST_SIZE");\n");
    }

    bcmolt_metadata_write(writer, "\n");

    if (is_multi)
    {
        bcmolt_metadata_write_indented(writer, 1, MSG_REF" = BCMOLT_MULTI_");
        bcmolt_api_code_write_upper(writer, bcmolt_mgt_group_to_str(msg->group));
        bcmolt_metadata_write(writer, "_ALLOC(%s, ", obj_descr->name);
        if (msg->group == BCMOLT_MGT_GROUP_STAT)
        {
            bcmolt_metadata_write(writer, "%s, ", group_descr->name);
        }
        bcmolt_metadata_write(writer, KEY_REF", %u);\n", ((const bcmolt_multi_msg *)msg)->max_responses);
        bcmolt_metadata_write_indented(writer, 1, "BUG_ON("MSG_REF" == NULL);\n\n");

        const bcmolt_group_descr *cfg_descr;
        err = bcmolt_api_group_descr_get(msg->obj_type, BCMOLT_MGT_GROUP_CFG, 0, &cfg_descr);
        BCMOS_RETURN_IF_ERROR(err);
        bcmolt_api_code_set_fields(writer, cfg_descr->type, multi_filter, BCMOS_TRUE);
        bcmolt_api_code_get_fields(writer, group_descr->type, multi_request, BCMOS_TRUE);
    }
    else
    {
        /* set properties */
        bcmolt_metadata_write_indented(writer, 1, "BCMOLT_");
        bcmolt_api_code_write_upper(writer, bcmolt_mgt_group_to_str(msg->group));
        bcmolt_metadata_write(writer, "_INIT(&"MSG_REF", %s", obj_descr->name);
        if ((msg->group == BCMOLT_MGT_GROUP_STAT)
            || (msg->group == BCMOLT_MGT_GROUP_STAT_CFG)
            || (msg->group == BCMOLT_MGT_GROUP_OPER))
        {
            bcmolt_metadata_write(writer, ", %s", group_descr->name);
        }
        bcmolt_metadata_write(writer, ", "KEY_REF");\n");

        if (need_list_mem)
        {
            bcmolt_metadata_write_indented(
                writer,
                1,
                "BCMOLT_CFG_LIST_BUF_SET(&" MSG_REF ", %s, " LIST_MEM_REF ", " DYN_LIST_SIZE ");\n",
                obj_descr->name);
        }

        if ((msg->type & BCMOLT_MSG_TYPE_GET) != 0)
        {
            bcmolt_api_code_get_fields(writer, group_descr->type, data, BCMOS_FALSE);
        }
        if ((msg->type & BCMOLT_MSG_TYPE_SET) != 0)
        {
            bcmolt_api_code_set_fields(writer, group_descr->type, data, BCMOS_FALSE);
        }
    }

    /* call API */
    bcmolt_metadata_write_indented(writer, 1, RC_REF" = ");
    bcmolt_api_code_write_api_call(writer, msg);
    bcmolt_metadata_write(writer, "("OLT_REF", &"MSG_REF"%shdr", is_multi ? "->" : ".");
    if (msg->group == BCMOLT_MGT_GROUP_STAT)
    {
        bcmolt_metadata_write(writer, ", %s", bcmolt_api_code_get_stat_flags(msg));
    }
    if (is_multi)
    {
        bcmolt_metadata_write(writer, ", %s", bcmolt_api_code_get_multi_flags(msg));
    }
    bcmolt_metadata_write(writer, ");\n");
    bcmolt_metadata_write_indented(writer, 1, "bcmos_printf(\"");
    bcmolt_api_code_write_api_call(writer, msg);
    bcmolt_metadata_write(writer, " returned %%s (%%d)\\n\", bcmos_strerror("RC_REF"), "RC_REF");\n");

    if (need_list_mem)
    {
        bcmolt_metadata_write_indented(writer, 1, "bcmos_free("LIST_MEM_REF");\n");
    }
    if (is_multi)
    {
        bcmolt_metadata_write_indented(writer, 1, "bcmolt_multi_msg_free(&"MSG_REF"->hdr.hdr);\n");
    }
    bcmolt_metadata_write_indented(writer, 1, "}\n");

    return BCM_ERR_OK;
}
