/*
<:copyright-BRCM:2016-2020:Apache:standard

 Copyright (c) 2016-2020 Broadcom. All Rights Reserved

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
#include "bcmolt_msg.h"
#include "bcmolt_api_metadata.h"
#include "bcmolt_msg_pack.h"

static bcmos_bool msg_pool_is_initialized = BCMOS_FALSE;
static bcmos_byte_pool msg_pool;

static void *bcmolt_msg_alloc_mem(uint32_t size)
{
    if (msg_pool_is_initialized)
    {
        void *ptr = bcmos_byte_pool_alloc(&msg_pool, size);
        if (ptr != NULL)
            memset(ptr, 0, size);
        return ptr;
    }
    else
    {
        return bcmos_calloc(size);
    }
}

bcmolt_msg *bcmolt_msg_alloc(uint32_t size)
{
    return bcmolt_msg_alloc_mem(size);
}

static void bcmolt_msg_free_mem(void *mem)
{
    if (msg_pool_is_initialized)
    {
        bcmos_byte_pool_free(mem);
    }
    else
    {
        bcmos_free(mem);
    }
}

bcmolt_multi_msg *bcmolt_multi_msg_alloc(
    bcmolt_obj_id obj_id,
    bcmolt_mgt_group group,
    uint16_t subgroup,
    const void *key,
    uint16_t max_responses)
{
    uint16_t i;
    bcmolt_multi_msg *ret;
    const bcmolt_group_descr *group_descr;
    void **responses_arr_ptr;
    bcmolt_msg *response_ptr;
    uint32_t size;
    bcmos_errno err;

    if (group != BCMOLT_MGT_GROUP_CFG && group != BCMOLT_MGT_GROUP_STAT)
    {
        BCMOS_TRACE_ERR("group must be BCMOLT_MGT_GROUP_CFG or BCMOLT_MGT_GROUP_STAT\n");
        return NULL;
    }

    /* Calculate full size of multi-msg */
    err = bcmolt_api_group_descr_get(obj_id, group, subgroup, &group_descr);
    if (err != BCM_ERR_OK || group_descr->multi == NULL)
    {
        BCMOS_TRACE_ERR("invalid group/subgroup: %u/%u\n", group, subgroup);
        return NULL;
    }

    /* Size includes the container structure plus room for all of the responses. */
    size = group_descr->multi->container_size + (max_responses * group_descr->container_size);
    ret = bcmolt_msg_alloc_mem(size);
    if (ret == NULL)
    {
        return NULL;
    }

    /* Initialize the top-level header. */
    ret->hdr.obj_type = obj_id;
    ret->hdr.type = BCMOLT_MSG_TYPE_GET_MULTI;
    ret->hdr.group = group;
    ret->hdr.subgroup = subgroup;
    ret->max_responses = max_responses;

    /* Copy in the key. */
    memcpy((void *)((long)ret + group_descr->multi->key_offset), key, group_descr->key_size);

    /* Set the responses pointer value to the next location after the container structure. */
    response_ptr = (bcmolt_msg *)((long)ret + group_descr->multi->container_size);
    responses_arr_ptr = (void **)((long)ret + group_descr->multi->responses_offset);
    *responses_arr_ptr = response_ptr;

    /* Initialize all of the response headers. */
    for (i = 0; i < max_responses; ++i)
    {
        memset(response_ptr, 0, sizeof(*response_ptr));
        response_ptr->type = BCMOLT_MSG_TYPE_GET;
        response_ptr->dir = BCMOLT_MSG_DIR_RESPONSE;
        response_ptr->obj_type = obj_id;
        response_ptr->group = group;
        response_ptr->subgroup = subgroup;
        response_ptr->loid = BCMOLT_LOID_UNDEFINED;
        response_ptr = (bcmolt_msg *)((long)response_ptr + group_descr->container_size);
    }

    return ret;
}

void bcmolt_msg_free(bcmolt_msg *msg)
{
    bcmolt_msg_free_mem(msg);
}

void bcmolt_multi_msg_free(bcmolt_multi_msg *msg)
{
    bcmolt_msg_free_mem(msg);
}

bcmos_errno bcmolt_msg_clone(bcmolt_msg **dest, bcmolt_msg *src)
{
    bcmos_errno err;
    int32_t packed_len;
    uint8_t *mem;
    bcmolt_buf buf;

    if (src == NULL || dest == NULL)
    {
        return BCM_ERR_PARM;
    }

    packed_len = bcmolt_msg_get_packed_length(src);
    if (packed_len < 0)
    {
        return (bcmos_errno) packed_len;
    }

    mem = bcmolt_msg_alloc_mem((uint32_t)packed_len);
    if (mem == NULL)
    {
        return BCM_ERR_NOMEM;
    }

    bcmolt_buf_init(&buf, (uint32_t)packed_len, mem);
    err = bcmolt_msg_pack(src, &buf);
    if (err != BCM_ERR_OK)
    {
        bcmolt_msg_free_mem(mem);
        return err;
    }

    buf.curr = buf.start;
    err = bcmolt_msg_unpack(&buf, dest);
    bcmolt_msg_free_mem(mem);
    return err;
}

void bcmolt_msg_mem_pool_set(const bcmos_byte_pool_parm *parms)
{
    if (msg_pool_is_initialized)
    {
        bcmos_byte_pool_destroy(&msg_pool);
    }
    if (parms == NULL)
    {
        msg_pool_is_initialized = BCMOS_FALSE;
    }
    else
    {
        bcmos_byte_pool_create(&msg_pool, parms);
        msg_pool_is_initialized = BCMOS_TRUE;
    }
}
