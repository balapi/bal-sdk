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

#ifndef BCMTR_HEADER_H_
#define BCMTR_HEADER_H_

#include <bcmos_system.h>
#include <bcmolt_buf.h>
#include <bcmolt_msg_pack.h>
#include <bcmolt_api_metadata.h>

/** Endianess of numbers written to the transport buffer.
 * Currently bcmolt_buf service doesn't support setting
 * endianness dynamically. Transport buffer direction must be the same
 * as selected at compile time in bcmolt_buf.h
 */
#define BCMTR_BUF_ENDIAN        BCMOLT_BUF_ENDIAN_FIXED

#define BCMTR_ENDIAN_CPU_TO_BUF_U32(n) BCMOLT_BUF_ENDIAN_CPU_TO_BUF(U32, n)
#define BCMTR_ENDIAN_BUF_TO_CPU_U32(n) BCMOLT_BUF_ENDIAN_BUF_TO_CPU(U32, n)

/** Max number of channels per device */
#define BCMTR_MAX_CHANNELS   32


/** Transport header.
 * Inserted in each packet transmitted on the line
 */
typedef struct bcmtr_hdr
{
    bcmolt_msg_dir dir;         /**< Message direction: request/response */
    bcmolt_obj_id obj;          /**< Object id */
    bcmolt_msg_type msg_type;   /**< Message type */
    bcmos_bool more_fragments;  /**< TRUE=more fragments to follow */
    bcmos_bool auto_reg_unreg;  /**< TRUE=message is auto (un)registration */
    bcmos_bool keep_alive;      /**< TRUE=keep-alive message */
    uint8_t device;             /**< Device ID */
    uint8_t instance;           /**< Message instance */
    uint16_t group_id;          /**< Group ID */
    uint16_t corr_tag;          /**< correlation tag */
    union
    {
        uint16_t frag_number;       /**< Fragment number */
        uint16_t conn_id;           /**< Connection id */
    };
} bcmtr_hdr;

/** Autonomous mask update message */
typedef struct bcmtr_reg_unreg_msg
{
    bcmtr_hdr hdr;
    /* Mask of which indications are subscribed (one bit per indication subgroup index).
     * Note that this is NOT sent on the line for compatibility - see bcmtr_reg_unreg_msg_pack(). */
    bcmolt_presence_mask auto_mask;
} bcmtr_reg_unreg_msg;

#define BCMTR_HDR_SIZE              12
#define BCMTR_REG_UNREG_MSG_SIZE    (BCMTR_HDR_SIZE + (2 * 64) + 2) /* max size = ID for 64 indications + terminator */

/* Shifts and widths of transport header fields */
/* word 0 */
#define BCMTR_HDR_DIR_S         31
#define BCMTR_HDR_DIR_W         1
#define BCMTR_HDR_REG_UNREG_S   30
#define BCMTR_HDR_REG_UNREG_W   1
/* Bit 29 is unused */
#define BCMTR_HDR_KEEP_ALIVE_S  28
#define BCMTR_HDR_KEEP_ALIVE_W  1
#define BCMTR_HDR_MSG_TYPE_S    24
#define BCMTR_HDR_MSG_TYPE_W    4
#define BCMTR_HDR_INSTANCE_S    18
#define BCMTR_HDR_INSTANCE_W    6
#define BCMTR_HDR_OBJ_S         2
#define BCMTR_HDR_OBJ_W         16
/* Bits [1:0] are unused */
/* word 1 */
#define BCMTR_HDR_CORR_TAG_S    16
#define BCMTR_HDR_CORR_TAG_W    16
#define BCMTR_HDR_MORE_FRAGS_S  15
#define BCMTR_HDR_MORE_FRAGS_W  1
#define BCMTR_HDR_FRAG_S        4
#define BCMTR_HDR_FRAG_W        11
#define BCMTR_HDR_FRAG_M        ((1 << BCMTR_HDR_FRAG_W) - 1)
#define BCMTR_HDR_DEVICE_S      0
#define BCMTR_HDR_DEVICE_W      4
/* word 2 */
/* Bits [31:16] are unused */
#define BCMTR_HDR_GROUP_S       0
#define BCMTR_HDR_GROUP_W       16

/* Pack transport header
 *
 * \param[in]   hdr             Unpacked transport header
 * \param[out]  packed_hdr      Packed header
 */
static inline void bcmtr_header_pack(const bcmtr_hdr *hdr, uint8_t *packed_hdr)
{
    uint32_t w[3];

    w[0] = (hdr->dir           << BCMTR_HDR_DIR_S)        |
        (hdr->auto_reg_unreg   << BCMTR_HDR_REG_UNREG_S)  |
        (hdr->keep_alive       << BCMTR_HDR_KEEP_ALIVE_S) |
        (hdr->msg_type         << BCMTR_HDR_MSG_TYPE_S)   |
        (hdr->instance         << BCMTR_HDR_INSTANCE_S)   |
        (hdr->obj              << BCMTR_HDR_OBJ_S);
    w[1] = (hdr->corr_tag << BCMTR_HDR_CORR_TAG_S)        |
        (hdr->more_fragments   << BCMTR_HDR_MORE_FRAGS_S) |
        ((hdr->frag_number & BCMTR_HDR_FRAG_M) << BCMTR_HDR_FRAG_S) |
        hdr->device;
    w[2] = (hdr->group_id << BCMTR_HDR_GROUP_S);

    w[0] = BCMTR_ENDIAN_CPU_TO_BUF_U32(w[0]);
    w[1] = BCMTR_ENDIAN_CPU_TO_BUF_U32(w[1]);
    w[2] = BCMTR_ENDIAN_CPU_TO_BUF_U32(w[2]);

    memcpy(packed_hdr, w, BCMTR_HDR_SIZE);
}

/* Unpack transport header
 *
 * \param[in]   packed_hdr      Packed header
 * \param[out]  hdr             Unpacked transport header
 * Buffer current pointer is incremented by the header side.
 */
static inline void bcmtr_header_unpack(const uint8_t *packed_hdr, bcmtr_hdr *hdr)
{
    uint32_t w[3];

    memcpy(w, packed_hdr, BCMTR_HDR_SIZE);

    w[0] = BCMTR_ENDIAN_BUF_TO_CPU_U32(w[0]);
    w[1] = BCMTR_ENDIAN_BUF_TO_CPU_U32(w[1]);
    w[2] = BCMTR_ENDIAN_BUF_TO_CPU_U32(w[2]);

    hdr->dir              = (bcmolt_msg_dir)BCM_FIELD_GET(w[0], BCMTR_HDR_DIR);
    hdr->msg_type         = (bcmolt_msg_type)BCM_FIELD_GET(w[0], BCMTR_HDR_MSG_TYPE);
    hdr->instance         = BCM_FIELD_GET(w[0], BCMTR_HDR_INSTANCE);
    hdr->obj              = (bcmolt_obj_id)BCM_FIELD_GET(w[0], BCMTR_HDR_OBJ);
    hdr->auto_reg_unreg   = BCM_FIELD_GET(w[0], BCMTR_HDR_REG_UNREG);
    hdr->keep_alive       = BCM_FIELD_GET(w[0], BCMTR_HDR_KEEP_ALIVE);
    hdr->corr_tag         = BCM_FIELD_GET(w[1], BCMTR_HDR_CORR_TAG);
    hdr->more_fragments   = BCM_FIELD_GET(w[1], BCMTR_HDR_MORE_FRAGS);
    hdr->frag_number      = BCM_FIELD_GET(w[1], BCMTR_HDR_FRAG);
    hdr->device           = BCM_FIELD_GET(w[1], BCMTR_HDR_DEVICE);
    hdr->group_id         = BCM_FIELD_GET(w[2], BCMTR_HDR_GROUP);
}

/* Fill transport header
 */
static inline void bcmtr_header_fill(const bcmolt_msg *msg, bcmtr_hdr *hdr)
{
    bcmolt_interface interface_id = 0;
    bcmos_bool has_interface;
    bcmos_errno err;
    const bcmolt_group_descr *group_descr;

    bcmolt_devif_get(msg, NULL, NULL, &has_interface, &interface_id);
    err = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group_descr);
    BCMOS_TRACE_RETURN_VOID_ON_ERROR(err);

    hdr->dir = msg->dir;
    hdr->more_fragments = BCMOS_FALSE;
    hdr->auto_reg_unreg = hdr->keep_alive = 0;
    hdr->msg_type = msg->type;
    hdr->obj = msg->obj_type;
    hdr->group_id = group_descr->id;
    hdr->instance = interface_id;
    hdr->corr_tag = msg->corr_tag;
    hdr->frag_number = 0;
    hdr->device = msg->device;
}

/* Pack auto registration mask update message
 *
 * \param[in]   msg             Unpacked message
 * \param[out]  packed_msg      Packed message
 */
static inline void bcmtr_reg_unreg_msg_pack(const bcmtr_reg_unreg_msg *msg, uint8_t *packed_msg)
{
    uint16_t *ind_id_ptr = (uint16_t *)(void *)(packed_msg + BCMTR_HDR_SIZE);
    const bcmolt_group_descr *group_descr;
    uint8_t i;

    memset(packed_msg, 0, BCMTR_REG_UNREG_MSG_SIZE);
    bcmtr_header_pack(&msg->hdr, packed_msg);

    /* Pack the group ID of each indication, followed by 0xFFFF. */
    for (i = 0; i < 64; ++i)
    {
        if ((msg->auto_mask & (1ULL << i)) != 0
            && bcmolt_api_group_descr_get(msg->hdr.obj, BCMOLT_MGT_GROUP_AUTO, i, &group_descr) == BCM_ERR_OK)
        {
            *ind_id_ptr = BCMOS_ENDIAN_CPU_TO_BIG_U16(group_descr->id);
            ind_id_ptr++;
        }
    }
    *ind_id_ptr = 0xFFFF;
}

/* Unpack auto registration mask update message
 *
 * \param[in]   packed_msg      Packed message
 * \param[out]  msg             Unpacked message
 */
static inline void bcmtr_reg_unreg_msg_unpack(const uint8_t *packed_msg, bcmtr_reg_unreg_msg *msg)
{
    const uint16_t *ind_id_ptr = (const uint16_t *)(const void *)(packed_msg + BCMTR_HDR_SIZE);
    const bcmolt_group_descr *group_descr;

    bcmtr_header_unpack(packed_msg, &msg->hdr);

    /* Unpack the group ID of each indication, followed by 0xFFFF. */
    msg->auto_mask = 0;
    while (*ind_id_ptr != 0xFFFF)
    {
        uint16_t ind_id = BCMOS_ENDIAN_BIG_TO_CPU_U16(*ind_id_ptr);
        if (bcmolt_api_group_descr_get_by_group_id(msg->hdr.obj, ind_id, &group_descr) == BCM_ERR_OK)
        {
            msg->auto_mask |= 1ULL << group_descr->subgroup_idx;
        }
        ind_id_ptr++;
    }
}

#endif /* BCMTR_HEADER_H_ */
