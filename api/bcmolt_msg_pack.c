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
#include <bcmolt_buf.h>
#include "bcmolt_api_model.h"
#include "bcmolt_api_metadata.h"
#include "bcmolt_serializer.h"
#include "bcmolt_msg.h"
#include "bcmolt_msg_pack.h"

#define MSG_FIELD_PTR(msg, offset) (void *)((long)msg + (offset))
#define MAX_KEY_SIZE_BYTES 128
#define DONT_SERIALIZE ((bcmolt_serializer_flag)-1)

/* The serialized format for API IDs is as follows:
 * - If the ID number is less than 0x80, the ID is serialized as a single byte with its raw value.
 * - Otherwise, the low 7 bits of the first byte are a count of how many bytes are to follow.
 *   Currently the only supported value is 0x82 meaning "2 bytes of data".
 */
static inline uint8_t bcmolt_meta_id_get_packed_length(bcmolt_meta_id id)
{
    return id < 0x80 ? 1 : 3;
}

static bcmos_bool bcmolt_meta_id_pack(bcmolt_buf *buf, bcmolt_meta_id id)
{
    if (id < 0x80)
    {
        return bcmolt_buf_write_u8(buf, id);
    }
    else
    {
        return bcmolt_buf_write_u8(buf, 0x82) && bcmolt_buf_write_u16(buf, id);
    }
}

static bcmos_bool bcmolt_meta_id_unpack(bcmolt_buf *buf, bcmolt_meta_id *id)
{
    uint8_t first_byte = 0;
    if (!bcmolt_buf_read_u8(buf, &first_byte))
    {
        return BCMOS_FALSE;
    }
    if (first_byte < 0x80)
    {
        *id = first_byte;
        return BCMOS_TRUE;
    }
    BCMOS_CHECK_RETURN(first_byte != 0x82, BCM_ERR_NOT_SUPPORTED, BCMOS_FALSE);
    return bcmolt_buf_read_u16(buf, id);
}

static bcmolt_serializer_flag bcmolt_get_data_serialization_flags(const bcmolt_msg *msg)
{
    switch (msg->group)
    {
        case BCMOLT_MGT_GROUP_CFG:
        case BCMOLT_MGT_GROUP_STAT:
        case BCMOLT_MGT_GROUP_STAT_CFG:
        case BCMOLT_MGT_GROUP_AUTO_CFG:
            if ((msg->type & BCMOLT_MSG_TYPE_GET))
            {
                /* Get message requests should only pack the TLV types, not the data. */
                return msg->dir == BCMOLT_MSG_DIR_REQUEST
                    ? BCMOLT_SERIALIZER_FLAG_SKIP_DATA
                    : BCMOLT_SERIALIZER_FLAG_NONE;
            }
            else if ((msg->type & BCMOLT_MSG_TYPE_SET))
            {
                return msg->dir == BCMOLT_MSG_DIR_REQUEST ? BCMOLT_SERIALIZER_FLAG_NONE : DONT_SERIALIZE;
            }
            else
            {
                return DONT_SERIALIZE;
            }

        case BCMOLT_MGT_GROUP_OPER:
            return msg->dir == BCMOLT_MSG_DIR_REQUEST ? BCMOLT_SERIALIZER_FLAG_NONE : DONT_SERIALIZE;

        default:
            return BCMOLT_SERIALIZER_FLAG_NONE;
    }
}

static bcmos_bool bcmolt_get_group_info(
    const bcmolt_msg *msg,
    const bcmolt_group_descr **group,
    const bcmolt_group_descr **key)
{
    bcmolt_api_group_id group_id;
    bcmos_errno err;

    err = bcmolt_api_group_id_combine(msg->obj_type, msg->group, msg->subgroup, &group_id);
    if (err != BCM_ERR_OK)
    {
        return BCMOS_FALSE;
    }

    err = bcmolt_api_group_descr_get_by_global_id(group_id, group);
    if (err != BCM_ERR_OK)
    {
        return BCMOS_FALSE;
    }

    err = bcmolt_api_group_id_combine(msg->obj_type, BCMOLT_MGT_GROUP_KEY, 0, &group_id);
    if (err != BCM_ERR_OK)
    {
        return BCMOS_FALSE;
    }

    err = bcmolt_api_group_descr_get_by_global_id(group_id, key);
    if (err != BCM_ERR_OK)
    {
        return BCMOS_FALSE;
    }

    return BCMOS_TRUE;
}

static void bcmolt_msg_err_text_buf_init(bcmolt_buf *buf, bcmolt_msg *msg)
{
    /* Skip the last character to make sure the string is NULL terminated. */
    bcmolt_buf_init(buf, sizeof(msg->err_text) - 1, (uint8_t *)msg->err_text);
}

static int32_t bcmolt_msg_get_packed_length_single(
    bcmolt_msg *msg,
    const bcmolt_group_descr *group,
    const bcmolt_group_descr *key)
{
    bcmos_errno err;
    uint32_t len;
    int32_t ret;
    bcmolt_serializer_flag flags;
    bcmolt_buf err_buf;

    bcmolt_msg_err_text_buf_init(&err_buf, msg);

    err = bcmolt_type_get_serialized_length(
        key->type,
        BCMOLT_SERIALIZER_FLAG_NONE,
        MSG_FIELD_PTR(msg, group->key_offset),
        &len,
        &err_buf);
    if (err != BCM_ERR_OK)
    {
        return err;
    }
    ret = len;

    flags = bcmolt_get_data_serialization_flags(msg);
    if (flags != DONT_SERIALIZE)
    {
        if (group->type == NULL)
        {
            ret += 2; /* terminator TLV */
        }
        else
        {
            err = bcmolt_type_get_serialized_length(
                group->type,
                flags,
                MSG_FIELD_PTR(msg, group->data_offset), &len, &err_buf);
            if (err != BCM_ERR_OK)
            {
                return err;
            }
            ret += len;
        }
    }

    return ret;
}

static int32_t bcmolt_msg_get_packed_length_multi(
    bcmolt_multi_msg *msg,
    const bcmolt_group_descr *group,
    const bcmolt_group_descr *key)
{
    bcmos_errno err;
    uint32_t len;
    bcmos_bool *more;
    int32_t ret;
    bcmolt_buf err_buf;

    BCMOS_TRACE_CHECK_RETURN(group->multi == NULL, BCM_ERR_INTERNAL, "multi group descr missing\n");
    bcmolt_msg_err_text_buf_init(&err_buf, &msg->hdr);

    ret = 3; /* num_responses|max_respones (2) + more (1) */
    err = bcmolt_type_get_serialized_length(
        key->type,
        BCMOLT_SERIALIZER_FLAG_NONE,
        MSG_FIELD_PTR(msg, group->multi->key_offset),
        &len,
        &err_buf);
    if (err != BCM_ERR_OK)
    {
        return err;
    }
    ret += len;

    more = MSG_FIELD_PTR(msg, group->multi->more_offset);
    if (*more)
    {
        err = bcmolt_type_get_serialized_length(
            key->type,
            BCMOLT_SERIALIZER_FLAG_NONE,
            MSG_FIELD_PTR(msg, group->multi->next_key_offset),
            &len,
            &err_buf);
        if (err != BCM_ERR_OK)
        {
            return err;
        }
        ret += len;
    }

    if (msg->hdr.dir == BCMOLT_MSG_DIR_REQUEST)
    {
        ret += 8; /* filter_flags */
        if ((msg->filter_flags & BCMOLT_FILTER_FLAGS_DISABLE_FILTER) == 0)
        {
            const bcmolt_group_descr *cfg_group;
            err = bcmolt_api_group_descr_get(msg->hdr.obj_type, BCMOLT_MGT_GROUP_CFG, 0, &cfg_group);
            if (err != BCM_ERR_OK)
            {
                bcmolt_strncpy(msg->hdr.err_text, "API group lookup failed", sizeof(msg->hdr.err_text));
                return err;
            }
            if (cfg_group != NULL)
            {
                err = bcmolt_type_get_serialized_length(
                    cfg_group->type,
                    BCMOLT_SERIALIZER_FLAG_NONE,
                    MSG_FIELD_PTR(msg, group->multi->filter_offset),
                    &len,
                    &err_buf);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
                ret += len;
            }
        }
        err = bcmolt_type_get_serialized_length(
            group->type,
            BCMOLT_SERIALIZER_FLAG_NONE,
            MSG_FIELD_PTR(msg, group->multi->request_offset),
            &len,
            &err_buf);
        if (err != BCM_ERR_OK)
        {
            return err;
        }
        ret += len;
    }
    else
    {
        uint16_t i;
        uint16_t *num_responses = MSG_FIELD_PTR(msg, group->multi->num_responses_offset);
        uint8_t **responses = MSG_FIELD_PTR(msg, group->multi->responses_offset);
        for (i = 0; i < *num_responses; i++)
        {
            void *response_i = *responses + (i * group->container_size);
            ret += bcmolt_msg_get_packed_length((bcmolt_msg *)response_i);
        }
    }

    return ret;
}

int32_t bcmolt_msg_get_packed_length(bcmolt_msg *msg)
{
    const bcmolt_group_descr *group;
    const bcmolt_group_descr *key;
    int32_t hdr_len;
    int32_t body_len;

    if (!bcmolt_get_group_info(msg, &group, &key))
    {
        return (int32_t)BCM_ERR_MSG_ERROR;
    }

    hdr_len = bcmolt_msg_hdr_get_packed_length(msg);
    if (hdr_len < 0)
    {
        return hdr_len;
    }

    body_len = (msg->type & BCMOLT_MSG_TYPE_MULTI) == 0
        ? bcmolt_msg_get_packed_length_single(msg, group, key)
        : bcmolt_msg_get_packed_length_multi((bcmolt_multi_msg *)msg, group, key);
    if (body_len < 0)
    {
        return body_len;
    }

    return hdr_len + body_len;
}

static bcmos_errno bcmolt_msg_pack_single(
    bcmolt_msg *msg,
    bcmolt_buf *buf,
    const bcmolt_group_descr *group,
    const bcmolt_group_descr *key)
{
    bcmolt_serializer_flag flags;
    bcmos_errno err;
    bcmolt_buf err_buf;

    bcmolt_msg_err_text_buf_init(&err_buf, msg);

    err = bcmolt_type_serialize(
        key->type,
        BCMOLT_SERIALIZER_FLAG_NONE,
        MSG_FIELD_PTR(msg, group->key_offset),
        buf,
        &err_buf);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    flags = bcmolt_get_data_serialization_flags(msg);
    if (flags != DONT_SERIALIZE)
    {
        if (group->type == NULL)
        {
            /* pack terminator alone */
            if (!bcmolt_buf_write_u16(buf, BCMOLT_SERIALIZER_TERMINATOR_TLV_ID))
            {
                bcmolt_strncpy(msg->err_text, "buffer write failed", sizeof(msg->err_text));
                return BCM_ERR_OVERFLOW;
            }
        }
        else
        {
            err = bcmolt_type_serialize(group->type, flags, MSG_FIELD_PTR(msg, group->data_offset), buf, &err_buf);
            if (err != BCM_ERR_OK)
            {
                return err;
            }
        }
    }

    return BCM_ERR_OK;
}

static bcmos_errno bcmolt_msg_pack_multi(
    bcmolt_multi_msg *msg,
    bcmolt_buf *buf,
    const bcmolt_group_descr *group,
    const bcmolt_group_descr *key)
{
    bcmos_errno err;
    bcmos_bool *more;
    bcmolt_buf err_buf;

    BCMOS_TRACE_CHECK_RETURN(group->multi == NULL, BCM_ERR_INTERNAL, "multi group descr missing\n");
    bcmolt_msg_err_text_buf_init(&err_buf, &msg->hdr);

    if (msg->hdr.dir == BCMOLT_MSG_DIR_REQUEST)
    {
        if (!bcmolt_buf_write_u16(buf, msg->max_responses))
        {
            bcmolt_strncpy(msg->hdr.err_text, "buffer write failed", sizeof(msg->hdr.err_text));
            return BCM_ERR_OVERFLOW;
        }
    }
    else
    {
        uint16_t *num_responses = MSG_FIELD_PTR(msg, group->multi->num_responses_offset);
        if (!bcmolt_buf_write_u16(buf, *num_responses))
        {
            bcmolt_strncpy(msg->hdr.err_text, "buffer write failed", sizeof(msg->hdr.err_text));
            return BCM_ERR_OVERFLOW;
        }
    }

    err = bcmolt_type_serialize(
        key->type,
        BCMOLT_SERIALIZER_FLAG_NONE,
        MSG_FIELD_PTR(msg, group->multi->key_offset),
        buf,
        &err_buf);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    more = MSG_FIELD_PTR(msg, group->multi->more_offset);
    if (!bcmolt_buf_write_bool(buf, *more))
    {
        bcmolt_strncpy(msg->hdr.err_text, "buffer write failed", sizeof(msg->hdr.err_text));
        return BCM_ERR_OVERFLOW;
    }

    if (*more)
    {
        err = bcmolt_type_serialize(
            key->type,
            BCMOLT_SERIALIZER_FLAG_NONE,
            MSG_FIELD_PTR(msg, group->multi->next_key_offset),
            buf,
            &err_buf);
        if (err != BCM_ERR_OK)
        {
            return err;
        }
    }

    if (msg->hdr.dir == BCMOLT_MSG_DIR_REQUEST)
    {
        if (!bcmolt_buf_write_u64(buf, (uint64_t)msg->filter_flags))
        {
            bcmolt_strncpy(msg->hdr.err_text, "buffer write failed", sizeof(msg->hdr.err_text));
            return BCM_ERR_OVERFLOW;
        }
        if ((msg->filter_flags & BCMOLT_FILTER_FLAGS_DISABLE_FILTER) == 0)
        {
            const bcmolt_group_descr *cfg_group;
            err = bcmolt_api_group_descr_get(msg->hdr.obj_type, BCMOLT_MGT_GROUP_CFG, 0, &cfg_group);
            if (err != BCM_ERR_OK)
            {
                bcmolt_strncpy(msg->hdr.err_text, "API group lookup failed", sizeof(msg->hdr.err_text));
                return err;
            }
            if (cfg_group != NULL)
            {
                err = bcmolt_type_serialize(
                    cfg_group->type,
                    BCMOLT_SERIALIZER_FLAG_NONE,
                    MSG_FIELD_PTR(msg, group->multi->filter_offset),
                    buf,
                    &err_buf);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
            }
        }
        err = bcmolt_type_serialize(
            group->type,
            BCMOLT_SERIALIZER_FLAG_NONE,
            MSG_FIELD_PTR(msg, group->multi->request_offset),
            buf,
            &err_buf);
        if (err != BCM_ERR_OK)
        {
            return err;
        }
    }
    else
    {
        uint16_t i;
        uint16_t *num_responses = MSG_FIELD_PTR(msg, group->multi->num_responses_offset);
        uint8_t **responses = MSG_FIELD_PTR(msg, group->multi->responses_offset);
        for (i = 0; i < *num_responses; i++)
        {
            void *response_i = *responses + (i * group->container_size);
            err = bcmolt_msg_pack((bcmolt_msg *)response_i, buf);
            if (err != BCM_ERR_OK)
            {
                return err;
            }
        }
    }

    return BCM_ERR_OK;
}

bcmos_errno bcmolt_msg_pack(bcmolt_msg *msg, bcmolt_buf *buf)
{
    bcmos_errno err;
    const bcmolt_group_descr *group;
    const bcmolt_group_descr *key;

    if (!bcmolt_get_group_info(msg, &group, &key))
    {
        return BCM_ERR_MSG_ERROR;
    }

    err = bcmolt_msg_hdr_pack(msg, buf);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    return (msg->type & BCMOLT_MSG_TYPE_MULTI) == 0
        ? bcmolt_msg_pack_single(msg, buf, group, key)
        : bcmolt_msg_pack_multi((bcmolt_multi_msg *)msg, buf, group, key);
}

/* Scan the input buffer to determine how much memory will be required to unpack variable-sized lists */
static bcmos_errno bcmolt_msg_list_mem_scan(
    bcmolt_buf *buf,
    bcmolt_msg *hdr,
    const bcmolt_group_descr *group,
    const bcmolt_group_descr *key,
    uint32_t *size)
{
    uint32_t pos_before_scan = bcmolt_buf_get_used(buf);
    bcmos_errno err;
    bcmolt_serializer_flag flags;
    bcmolt_buf err_buf;

    bcmolt_msg_err_text_buf_init(&err_buf, hdr);

    err = bcmolt_type_extra_mem_scan(key->type, BCMOLT_SERIALIZER_FLAG_NONE, buf, size, &err_buf);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    flags = bcmolt_get_data_serialization_flags(hdr);
    if (flags != DONT_SERIALIZE && group->type != NULL)
    {
        err = bcmolt_type_extra_mem_scan(group->type, flags, buf, size, &err_buf);
        if (err != BCM_ERR_OK)
        {
            return err;
        }
    }

    if (!bcmolt_buf_rewind(buf, bcmolt_buf_get_used(buf) - pos_before_scan))
    {
        bcmolt_strncpy(hdr->err_text, "buffer rewind failed", sizeof(hdr->err_text));
        return BCM_ERR_OVERFLOW;
    }

    return BCM_ERR_OK;
}

static bcmos_errno bcmolt_msg_unpack_single(
    bcmolt_msg *hdr,
    bcmolt_buf *buf,
    bcmolt_msg **unpacked,
    const bcmolt_group_descr *group,
    const bcmolt_group_descr *key)
{
    bcmos_errno err;
    bcmos_bool did_malloc = BCMOS_FALSE;
    uint8_t *key_ptr;
    void *list_mem = NULL;
    bcmolt_buf list_mem_buf;
    bcmolt_buf *list_mem_buf_ptr = NULL;
    bcmolt_serializer_flag flags;
    bcmolt_buf err_buf;

    bcmolt_msg_err_text_buf_init(&err_buf, hdr);

    if (*unpacked == NULL)
    {
        uint32_t size = group->container_size;
        err = bcmolt_msg_list_mem_scan(buf, hdr, group, key, &size);
        if (err != BCM_ERR_OK)
        {
            return err;
        }
        if (size < sizeof(bcmolt_msg))
        {
            /* It appears that buf contains some garbage and bcmolt_msg_list_mem_scan got confused */
            return BCM_ERR_OVERFLOW;
        }

        *unpacked = bcmolt_msg_alloc(size);
        if (*unpacked == NULL)
        {
            return BCM_ERR_NOMEM;
        }

        list_mem = (uint8_t *)(*unpacked) + group->container_size;
        bcmolt_buf_init(&list_mem_buf, size - group->container_size, list_mem);
        list_mem_buf_ptr = &list_mem_buf;
        did_malloc = BCMOS_TRUE;
    }
    else
    {
        if ((*unpacked)->list_buf != NULL)
        {
            uint32_t size = 0;
            err = bcmolt_msg_list_mem_scan(buf, hdr, group, key, &size);
            if (err != BCM_ERR_OK)
            {
                return err;
            }
            if (size > (*unpacked)->list_buf_size)
            {
                return BCM_ERR_INSUFFICIENT_LIST_MEM;
            }
            list_mem = (*unpacked)->list_buf;
            bcmolt_buf_init(&list_mem_buf, size, list_mem);
            list_mem_buf_ptr = &list_mem_buf;
        }
    }

    **unpacked = *hdr;

    key_ptr = (uint8_t *)(*unpacked) + group->key_offset;
    err = bcmolt_type_deserialize(key->type, BCMOLT_SERIALIZER_FLAG_NONE, key_ptr, buf, list_mem_buf_ptr, &err_buf);
    if (err != BCM_ERR_OK)
    {
        if (did_malloc)
        {
            bcmolt_msg_free(*unpacked);
        }
        return err;
    }

    flags = bcmolt_get_data_serialization_flags(hdr);
    if (flags != DONT_SERIALIZE && group->type != NULL)
    {
        uint8_t *data_ptr = (uint8_t *)(*unpacked) + group->data_offset;
        err = bcmolt_type_deserialize(group->type, flags, data_ptr, buf, list_mem_buf_ptr, &err_buf);
        if (err != BCM_ERR_OK)
        {
            if (did_malloc)
            {
                bcmolt_msg_free(*unpacked);
            }
            return err;
        }
    }

    return BCM_ERR_OK;
}

static bcmos_errno bcmolt_msg_unpack_multi(
    bcmolt_msg *hdr,
    bcmolt_buf *buf,
    bcmolt_msg **unpacked,
    const bcmolt_group_descr *group,
    const bcmolt_group_descr *key)
{
    bcmos_errno err;
    bcmos_bool did_malloc = BCMOS_FALSE;
    bcmolt_multi_msg *multi;
    uint8_t key_buf[MAX_KEY_SIZE_BYTES] = {};
    uint16_t num_responses;
    bcmos_bool *more;
    bcmolt_buf err_buf;

    BCMOS_TRACE_CHECK_RETURN(group->multi == NULL, BCM_ERR_INTERNAL, "multi group descr missing\n");
    bcmolt_msg_err_text_buf_init(&err_buf, hdr);

    if (!bcmolt_buf_read_u16(buf, &num_responses))
    {
        return BCM_ERR_OVERFLOW;
    }

    BCMOS_TRACE_CHECK_RETURN(
        key->type->size > MAX_KEY_SIZE_BYTES,
        BCM_ERR_INTERNAL,
        "key is too big, obj=%u\n",
        hdr->obj_type);

    err = bcmolt_type_deserialize(key->type, BCMOLT_SERIALIZER_FLAG_NONE, key_buf, buf, NULL, &err_buf);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    if (*unpacked == NULL)
    {
        multi = bcmolt_multi_msg_alloc(hdr->obj_type, hdr->group, hdr->subgroup, key_buf, num_responses);
        if (multi == NULL)
        {
            bcmolt_strncpy(hdr->err_text, "multi-part message memory allocation failed", sizeof(hdr->err_text));
            return BCM_ERR_NOMEM;
        }
        *unpacked = &multi->hdr;
        did_malloc = BCMOS_TRUE;
    }
    else
    {
        multi = (bcmolt_multi_msg *)*unpacked;
        memcpy(MSG_FIELD_PTR(multi, group->multi->key_offset), key_buf, key->type->size);
        BCMOS_TRACE_CHECK_RETURN(
            num_responses > multi->max_responses,
            BCM_ERR_TOO_MANY,
            "number of responses (%u) exceeds max responses (%u)\n",
            num_responses,
            multi->max_responses);
    }

    multi->hdr = *hdr;

    if (multi->hdr.dir == BCMOLT_MSG_DIR_REQUEST)
    {
        multi->max_responses = num_responses;
    }
    else
    {
        *(uint16_t *)MSG_FIELD_PTR(multi, group->multi->num_responses_offset) = num_responses;
    }

    more = MSG_FIELD_PTR(multi, group->multi->more_offset);
    if (!bcmolt_buf_read_bool(buf, more))
    {
        bcmolt_strncpy(hdr->err_text, "buffer read failed", sizeof(hdr->err_text));
        err = BCM_ERR_OVERFLOW;
        goto done;
    }
    if (*more)
    {
        err = bcmolt_type_deserialize(
            key->type,
            BCMOLT_SERIALIZER_FLAG_NONE,
            MSG_FIELD_PTR(multi, group->multi->next_key_offset),
            buf,
            NULL,
            &err_buf);
        if (err != BCM_ERR_OK)
        {
            goto done;
        }
    }

    if (multi->hdr.dir == BCMOLT_MSG_DIR_REQUEST)
    {
        uint64_t flags;
        if (!bcmolt_buf_read_u64(buf, &flags))
        {
            bcmolt_strncpy(hdr->err_text, "buffer read failed", sizeof(hdr->err_text));
            err = BCM_ERR_OVERFLOW;
            goto done;
        }
        multi->filter_flags = (bcmolt_filter_flags)flags;
        if ((multi->filter_flags & BCMOLT_FILTER_FLAGS_DISABLE_FILTER) == 0)
        {
            const bcmolt_group_descr *cfg_group;
            err = bcmolt_api_group_descr_get(multi->hdr.obj_type, BCMOLT_MGT_GROUP_CFG, 0, &cfg_group);
            if (err != BCM_ERR_OK)
            {
                bcmolt_strncpy(hdr->err_text, "API group lookup failed", sizeof(hdr->err_text));
                goto done;
            }
            if (cfg_group != NULL)
            {
                void *filter = MSG_FIELD_PTR(multi, group->multi->filter_offset);
                err = bcmolt_type_deserialize(
                    cfg_group->type,
                    BCMOLT_SERIALIZER_FLAG_NONE,
                    filter,
                    buf,
                    NULL,
                    &err_buf);
                if (err != BCM_ERR_OK)
                {
                    goto done;
                }
            }
        }
        err = bcmolt_type_deserialize(
            group->type,
            BCMOLT_SERIALIZER_FLAG_NONE,
            MSG_FIELD_PTR(multi, group->multi->request_offset),
            buf,
            NULL,
            &err_buf);
        if (err != BCM_ERR_OK)
        {
            goto done;
        }
    }
    else
    {
        uint16_t i;
        uint8_t **responses = MSG_FIELD_PTR(multi, group->multi->responses_offset);
        for (i = 0; i < num_responses; i++)
        {
            void *response_i = *responses + (i * group->container_size);
            err = bcmolt_msg_unpack(buf, (bcmolt_msg **)&response_i);
            if (err != BCM_ERR_OK)
            {
                goto done;
            }
        }
    }

done:
    if (err != BCM_ERR_OK && did_malloc)
    {
        bcmolt_msg_free(*unpacked);
    }
    return err;
}

bcmos_errno bcmolt_msg_unpack(bcmolt_buf *buf, bcmolt_msg **unpacked)
{
    bcmolt_msg hdr = {};
    bcmos_errno err;
    const bcmolt_group_descr *group;
    const bcmolt_group_descr *key;

    err = bcmolt_msg_hdr_unpack(&hdr, buf);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    if (!bcmolt_get_group_info(&hdr, &group, &key))
    {
        return BCM_ERR_MSG_ERROR;
    }

    err = (hdr.type & BCMOLT_MSG_TYPE_MULTI) == 0
        ? bcmolt_msg_unpack_single(&hdr, buf, unpacked, group, key)
        : bcmolt_msg_unpack_multi(&hdr, buf, unpacked, group, key);

    /* If there was an error unpacking, make sure to copy the error string to the target message. */
    if (err != BCM_ERR_OK && *unpacked != NULL)
    {
        (*unpacked)->err = hdr.err;
        memcpy((*unpacked)->err_text, hdr.err_text, sizeof(hdr.err_text));
    }

    return err;
}

int32_t bcmolt_msg_hdr_get_packed_length(const bcmolt_msg *msg)
{
    bcmos_errno err;
    bcmolt_api_group_id global_group_id;
    const bcmolt_group_descr *group_descr;

    err = bcmolt_api_group_id_combine(msg->obj_type, msg->group, msg->subgroup, &global_group_id);
    if (err != BCM_ERR_OK)
    {
        return BCMOS_FALSE;
    }

    err = bcmolt_api_group_descr_get_by_global_id(global_group_id, &group_descr);
    if (err != BCM_ERR_OK)
    {
        return BCMOS_FALSE;
    }

    return 5
        + bcmolt_meta_id_get_packed_length(group_descr->obj_id)
        + bcmolt_meta_id_get_packed_length(group_descr->id)
        + (msg->err ? strlen(msg->err_text) + 2 : 0);
}

bcmos_errno bcmolt_msg_hdr_pack(const bcmolt_msg *msg, bcmolt_buf *buf)
{
    bcmos_bool ret;

    ret =        bcmolt_meta_id_pack(buf, (bcmolt_meta_id)msg->obj_type);
    ret = ret && bcmolt_msg_group_id_pack(buf, msg->obj_type, msg->group, msg->subgroup);
    ret = ret && bcmolt_buf_write_u8(buf, (uint8_t)msg->type);
    ret = ret && bcmolt_buf_write_u8(buf, (uint8_t)msg->dir);
    ret = ret && bcmolt_buf_write_u8(buf, (uint8_t)msg->loid);
    ret = ret && bcmolt_buf_write_s16(buf, (int16_t)msg->err);
    if (msg->err)
    {
        uint16_t len = strlen(msg->err_text);
        ret = ret && bcmolt_buf_write_u16(buf, len);
        ret = ret && bcmolt_buf_write(buf, msg->err_text, len);
    }

    return ret ? BCM_ERR_OK : BCM_ERR_OVERFLOW;
}

bcmos_errno bcmolt_msg_hdr_unpack(bcmolt_msg *msg, bcmolt_buf *buf)
{
    bcmolt_meta_id obj_type;
    bcmolt_mgt_group mgt_group;
    uint16_t subgroup;
    uint8_t type;
    uint8_t dir;
    uint8_t loid;
    int16_t err = 0;
    bcmos_bool ret;

    ret =        bcmolt_meta_id_unpack(buf, &obj_type);
    ret = ret && bcmolt_msg_group_id_unpack(buf, (bcmolt_obj_id)obj_type, &mgt_group, &subgroup);
    ret = ret && bcmolt_buf_read_u8(buf, &type);
    ret = ret && bcmolt_buf_read_u8(buf, &dir);
    ret = ret && bcmolt_buf_read_u8(buf, &loid);
    ret = ret && bcmolt_buf_read_s16(buf, &err);
    if (err)
    {
        uint16_t len = 0;
        ret = ret && bcmolt_buf_read_u16(buf, &len);
        if (len >= sizeof(msg->err_text))
            len = sizeof(msg->err_text) - 1;
        ret = ret && bcmolt_buf_read(buf, msg->err_text, len);
        msg->err_text[len] = 0;
    }
    else
    {
        msg->err_text[0] = 0;
    }

    if (ret)
    {
        msg->obj_type = (bcmolt_obj_id)obj_type;
        msg->group = mgt_group;
        msg->subgroup = subgroup;
        msg->type = (bcmolt_msg_type)type;
        msg->dir = (bcmolt_msg_dir)dir;
        msg->loid = loid;
        msg->err = (bcmos_errno)err;
    }

    return ret ? BCM_ERR_OK : BCM_ERR_OVERFLOW;
}

bcmos_bool bcmolt_msg_group_id_pack(bcmolt_buf *buf, bcmolt_obj_id obj, bcmolt_mgt_group group, uint16_t subgroup)
{
    bcmos_errno err;
    bcmolt_api_group_id global_group_id;
    const bcmolt_group_descr *group_descr;

    err = bcmolt_api_group_id_combine(obj, group, subgroup, &global_group_id);
    if (err != BCM_ERR_OK)
    {
        return BCMOS_FALSE;
    }

    err = bcmolt_api_group_descr_get_by_global_id(global_group_id, &group_descr);
    if (err != BCM_ERR_OK)
    {
        return BCMOS_FALSE;
    }

    return bcmolt_meta_id_pack(buf, group_descr->id);
}

bcmos_bool bcmolt_msg_group_id_unpack(bcmolt_buf *buf, bcmolt_obj_id obj, bcmolt_mgt_group *group, uint16_t *subgroup)
{
    bcmos_errno err;
    const bcmolt_group_descr *group_descr;
    bcmolt_meta_id group_id;

    if (!bcmolt_meta_id_unpack(buf, &group_id))
    {
        return BCMOS_FALSE;
    }

    err = bcmolt_api_group_descr_get_by_group_id(obj, group_id, &group_descr);
    if (err != BCM_ERR_OK)
    {
        return BCMOS_FALSE;
    }

    *group = group_descr->mgt_group;
    *subgroup = group_descr->subgroup_idx;
    return BCMOS_TRUE;
}
