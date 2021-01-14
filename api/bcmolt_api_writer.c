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

#include <bcmos_system.h>
#include <bcmolt_msg.h>
#include <bcmolt_string.h>
#include <bcmolt_metadata_writer.h>
#include "bcmolt_api_metadata.h"
#include "bcmolt_api_writer.h"

static void writer_write(const bcmolt_metadata_writer *writer, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    writer->write_cb(writer->user_data, format, ap);
    va_end(ap);
}

/* Write object data */
static bcmos_errno write_data(
    const bcmolt_metadata_writer *writer,
    const bcmolt_msg *msg,
    const void *data,
    uint32_t data_size,
    uint32_t style)
{
    bcmos_errno rc;
    const bcmolt_group_descr *group;

    rc = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group);
    if (rc != BCM_ERR_OK)
    {
        return rc;
    }

    return bcmolt_metadata_write_elem(writer, group->type, data,
        (style & BCMOLT_METADATA_WRITE_STYLE_CLI_INPUT) ? NULL : "data",
        style, 0, "",
        (style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED) ? "\n" : " ");
}

/* Write object key */
static bcmos_errno write_key(
    const bcmolt_metadata_writer *writer,
    const bcmolt_msg *msg,
    const void *key,
    uint32_t key_size,
    uint32_t style)
{
    bcmos_errno rc;
    const bcmolt_group_descr *group;

    rc = bcmolt_api_group_descr_get(msg->obj_type, BCMOLT_MGT_GROUP_KEY, 0, &group);
    if (rc != BCM_ERR_OK)
    {
        return rc;
    }

    return bcmolt_metadata_write_elem(writer, group->type, key,
        (style & BCMOLT_METADATA_WRITE_STYLE_CLI_INPUT) ? NULL : "key",
        style, 0, "",
        (style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED) ? "\n" : " ");
}

/* Write message set returned by multi-object GET */
static bcmos_errno write_multi_msg(
    const bcmolt_metadata_writer *writer,
    const bcmolt_multi_msg *msg,
    const bcmolt_group_descr *group,
    uint32_t style)
{
    bcmos_bool *more_ptr = (bcmos_bool *)((long)msg + group->multi->more_offset);
    uint8_t *next_key_ptr = (uint8_t *)((long)msg + group->multi->next_key_offset);

    writer_write(writer, "more: %s\n", *more_ptr ? "yes" : "no");
    if (*more_ptr)
    {
        writer_write(writer, "next ");
        write_key(writer, &msg->hdr, next_key_ptr, group->key_size, style);
    }

    if (msg->hdr.dir == BCMOLT_MSG_DIR_RESPONSE)
    {
        uint16_t *num_responses_ptr = (uint16_t *)((long)msg + group->multi->num_responses_offset);
        bcmolt_msg **responses_arr_ptr = (bcmolt_msg **)((long)msg + group->multi->responses_offset);
        bcmos_errno rc;
        uint16_t i;

        writer_write(writer, "number of objects returned: %d\n", *num_responses_ptr);
        for (i = 0; i < *num_responses_ptr; i++)
        {
            bcmolt_msg *response_ptr = (bcmolt_msg *)((long)*responses_arr_ptr + (group->container_size * i));
            const void *response_key_ptr = (uint8_t *)response_ptr + group->key_offset;
            const void *response_data_ptr = (uint8_t *)response_ptr + group->data_offset;

            writer_write(writer, "object %d:\n", i);

            rc = write_key(writer, response_ptr, response_key_ptr, group->key_size, style);
            if (rc != BCM_ERR_OK)
            {
                return rc;
            }

            rc = write_data(writer, response_ptr, response_data_ptr, group->data_size, style);
            if (rc != BCM_ERR_OK)
            {
                return rc;
            }
        }
    }

    return BCM_ERR_OK;
}

static bcmos_errno write_cli_command(const bcmolt_metadata_writer *writer, const bcmolt_msg *msg)
{
    bcmos_errno err = BCM_ERR_OK;
    writer_write(writer, "/api/");
    switch(msg->group)
    {
        case BCMOLT_MGT_GROUP_CFG:
            if (msg->type & BCMOLT_MSG_TYPE_MULTI)
                writer_write(writer, "multiget ");
            else if (msg->type & BCMOLT_MSG_TYPE_CLEAR)
                writer_write(writer, "clear ");
            else if (msg->type & BCMOLT_MSG_TYPE_GET)
                writer_write(writer, "get ");
            else
                writer_write(writer, "set ");
            break;

        case BCMOLT_MGT_GROUP_STAT:
            if (msg->type & BCMOLT_MSG_TYPE_MULTI)
                writer_write(writer, "multistat ");
            else
                writer_write(writer, "stat ");
            break;

        case BCMOLT_MGT_GROUP_STAT_CFG:
            if (msg->type & BCMOLT_MSG_TYPE_GET)
                writer_write(writer, "saget ");
            else
                writer_write(writer, "saset ");
            break;

        case BCMOLT_MGT_GROUP_OPER:
            writer_write(writer, "oper ");
            break;

        default:
            writer_write(writer, "*unexpected* ");
            err = BCM_ERR_PARSE;
            break;
    }
    return err;
}

bcmos_errno bcmolt_api_write_msg(const bcmolt_metadata_writer *writer, const bcmolt_msg *msg, uint32_t style)
{
    bcmos_errno rc;
    const bcmolt_obj_descr *obj;
    const bcmolt_group_descr *group;
    const void *key = NULL;
    const void *data = NULL;

    rc = bcmolt_api_obj_descr_get(msg->obj_type, &obj);
    if (rc)
    {
        goto dump_error;
    }

    if (style & BCMOLT_METADATA_WRITE_STYLE_CLI_INPUT)
    {
        if (msg->dir != BCMOLT_MSG_DIR_REQUEST)
            goto dump_error;
        write_cli_command(writer, msg);
        if (msg->group == BCMOLT_MGT_GROUP_STAT)
            writer_write(writer, "clear=%s ", (msg->type & BCMOLT_MSG_TYPE_CLEAR) ? "yes" : "no");
        if ((msg->type & BCMOLT_MSG_TYPE_MULTI) != 0)
        {
            const bcmolt_multi_msg *mmsg = (const bcmolt_multi_msg *)msg;
            writer_write(writer, "max_msgs=%u filter_invert=%s ",
                mmsg->max_responses,
                (mmsg->filter_flags & BCMOLT_FILTER_FLAGS_INVERT_SELECTION) ? "yes" : "no");
        }
        writer_write(writer, "object=%s ", obj->name);
    }
    else
    {
        if (style & BCMOLT_METADATA_WRITE_STYLE_VERBOSE)
            writer_write(writer, "object: ");

        if (obj->name)
            writer_write(writer, "%s", obj->name);
    }

    rc = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group);
    if (rc)
    {
        goto dump_error;
    }

    if ((style & BCMOLT_METADATA_WRITE_STYLE_CLI_INPUT) &&
        (msg->group == BCMOLT_MGT_GROUP_OPER || msg->group == BCMOLT_MGT_GROUP_STAT))
    {
        writer_write(writer, "sub=%s ", group->name);
    }

    if (style & BCMOLT_METADATA_WRITE_STYLE_VERBOSE && obj->descr)
    {
        writer_write(writer, "- %s", obj->descr);
        writer_write(writer, style & BCMOLT_METADATA_WRITE_STYLE_SPACE_SEPARATED ? " " : "\n");
    }

    if (style & BCMOLT_METADATA_WRITE_STYLE_VERBOSE)
    {
        writer_write(writer, (msg->type & BCMOLT_MSG_TYPE_GET) != 0 ? "get" : "set");
        if ((msg->type & BCMOLT_MSG_TYPE_CLEAR) != 0)
        {
            writer_write(writer, ",clear");
        }
        if ((msg->type & BCMOLT_MSG_TYPE_MULTI) != 0)
        {
            writer_write(writer, ",multi");
        }
        writer_write(writer, " %s ", bcmolt_mgt_group_to_str(msg->group));

        if (msg->group != BCMOLT_MGT_GROUP_CFG && msg->group != BCMOLT_MGT_GROUP_AUTO_CFG)
            writer_write(writer, "subgroup: %s-%s ", group->name, group->descr ? group->descr : "");

        writer_write(writer, "loid: %u ", msg->loid);

        if (msg->dir == BCMOLT_MSG_DIR_REQUEST)
        {
            writer_write(writer, "request");
        }
        else
        {
            writer_write(writer, "response: %s %s", bcmos_strerror(msg->err), msg->err_text);
        }

        writer_write(writer, style & BCMOLT_METADATA_WRITE_STYLE_SPACE_SEPARATED ? " " : "\n");
    }
    else if (!(style & BCMOLT_METADATA_WRITE_STYLE_CLI_INPUT))
    {
        if (msg->group != BCMOLT_MGT_GROUP_CFG && msg->group != BCMOLT_MGT_GROUP_AUTO_CFG)
            writer_write(writer, ".%s ", group->name);
    }

    if ((msg->type & BCMOLT_MSG_TYPE_MULTI) != 0 && !(style & BCMOLT_METADATA_WRITE_STYLE_CLI_INPUT))
    {
        rc = write_multi_msg(writer, (const bcmolt_multi_msg *)msg, group, style);
        if (rc)
        {
            goto dump_error;
        }
    }
    else
    {
        if ((msg->group != BCMOLT_MGT_GROUP_AUTO_CFG) && group->key_size)
        {
            key = (const void *)((long)msg + group->key_offset);
            rc = write_key(writer, msg, key, group->key_size, style);
            if (rc)
            {
                goto dump_error;
            }
        }
        if (group->data_size &&
            (((msg->dir == BCMOLT_MSG_DIR_REQUEST) && (msg->type & BCMOLT_MSG_TYPE_SET))  ||
            ((msg->dir == BCMOLT_MSG_DIR_RESPONSE) && (msg->type & BCMOLT_MSG_TYPE_GET)) ||
            (msg->group == BCMOLT_MGT_GROUP_AUTO)
            )
           )
        {
            data = (const void *)((long)msg + group->data_offset);
            rc = write_data(writer, msg, data, group->data_size, style);
            if (rc)
            {
                goto dump_error;
            }
        }
    }

    /* For LINE_SEPARATED \n is already printed */
    if (!(style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED))
    {
        writer_write(writer, "\n");
    }

    return BCM_ERR_OK;

dump_error:
    writer_write(writer, "\n*** object print error %s (%d)\n", bcmos_strerror(rc), rc);
    return rc;
}
