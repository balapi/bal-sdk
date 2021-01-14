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

#ifndef BCMOLT_MSG_PACK_H_
#define BCMOLT_MSG_PACK_H_

#include <bcmos_system.h>
#include <bcmolt_buf.h>
#include "bcmolt_api_model.h"
#include "bcmolt_msg.h"

/** Gets the number of bytes a message would occupy when packed.
 *
 * \param this The message to scan.
 * \return The size in bytes if > 0, or an error as defined in bcmos_errno.
 */
int32_t bcmolt_msg_get_packed_length(bcmolt_msg *obj);

/** Packs a message to a byte stream.
 *
 * \param this The message to pack.
 * \param buf The stream to pack into.
 * \return An error code or BCM_ERR_OK for success.
 */
bcmos_errno bcmolt_msg_pack(bcmolt_msg *obj, bcmolt_buf *buf);

/** Unpacks a message from a byte stream.
 *
 * This unpacks the message from the packed form into the struct following the "unpacked" pointer.  There are several
 * special cases:
 *
 * if *unpacked == NULL:
 *   *unpacked will be allocated dynamically via bcmos_msg_alloc, in a contiguous block of memory with the struct
 *   itself followed by the memory required for all variable-sized lists.
 *
 * if (*unpacked)->list_buf != NULL:
 *   When a variable-length list is encountered in the input stream, and the array field we're unpacking into is NULL,
 *   memory will be allocated starting from (*unpacked)->list_buf.  If multiple such lists exist, they will share this
 *   buffer.  If the (*unpacked)->list_buf_size is not large enough, this will return BCM_ERR_INSUFFICIENT_LIST_MEM.
 *
 * \param buf           The stream to unpack from.
 * \param unpacked      A pointer to the message to unpack.
 * \return An error as defined in bcmos_errno.
 */
bcmos_errno bcmolt_msg_unpack(bcmolt_buf *buf, bcmolt_msg **unpacked);

/** Packs a group (managment group + subgroup pair) to a buffer using its persistent group ID.
 *
 * \param[in] buf The buffer to pack the data into.
 * \param[in] obj The ID of the object that has the group.
 * \param[in] group The top-level group type.
 * \param[in] subgroup The subgroup index under the object/group.
 * \return BCMOS_TRUE if the pack was successful, BCMOS_FALSE otherwise.
 */
bcmos_bool bcmolt_msg_group_id_pack(bcmolt_buf *buf, bcmolt_obj_id obj, bcmolt_mgt_group group, uint16_t subgroup);

/** Unpacks a group (managment group + subgroup pair) from a buffer using its persistent group ID.
 *
 * \param[in] buf The buffer to unpack the data from.
 * \param[in] obj The ID of the object that has the group.
 * \param[out] group The top-level group type.
 * \param[out] subgroup The subgroup index under the object/group.
 * \return BCMOS_TRUE if the unpack was successful, BCMOS_FALSE otherwise.
 */
bcmos_bool bcmolt_msg_group_id_unpack(bcmolt_buf *buf, bcmolt_obj_id obj, bcmolt_mgt_group *group, uint16_t *subgroup);

/** Get the length of the header portion of a message.
 *
 * \param msg The message to scan.
 * \return The size in bytes if > 0, or an error as defined in bcmos_errno.
 */
int32_t bcmolt_msg_hdr_get_packed_length(const bcmolt_msg *msg);

/** Pack a message header to a byte stream.
 *
 * \param this The message to pack.
 * \param buf The stream to pack into.
 * \return An error code or BCM_ERR_OK for success.
 */
bcmos_errno bcmolt_msg_hdr_pack(const bcmolt_msg *msg, bcmolt_buf *buf);

/** Unpack a message header from a byte stream.
 *
 * \param buf           The stream to unpack from.
 * \param unpacked      A pointer to the message to unpack.
 * \return An error as defined in bcmos_errno.
 */
bcmos_errno bcmolt_msg_hdr_unpack(bcmolt_msg *msg, bcmolt_buf *buf);

#endif /* BCMOLT_MSG_PACK_H_ */
