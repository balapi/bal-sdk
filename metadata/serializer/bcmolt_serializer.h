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

/* bcmolt_serializer.h:
 * Generic utility to serialize/deserialize data in a TLV-style format
 */

#ifndef BCMOLT_SERIALIZER_H
#define BCMOLT_SERIALIZER_H

#include <bcmos_system.h>
#include "bcmolt_buf.h"
#include "bcmolt_type_metadata.h"

#define BCMOLT_SERIALIZER_TERMINATOR_TLV_ID 0xFFFF

/** Serializer option flags. */
typedef enum
{
    BCMOLT_SERIALIZER_FLAG_NONE = 0,

    /** Don't serialize field data (e.g. for GET request).
     * Note that this still serializes all types/lengths (0) for the entire element tree recursively. */
    BCMOLT_SERIALIZER_FLAG_SKIP_DATA = 1 << 0,

    /** Don't serialize the data portion of var-length arrays (not even the elements' presence masks). */
    BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA = 1 << 1,

    /** Like BCMOLT_SERIALIZER_FLAG_SKIP_DATA, but also skip any embedded presence masks (for internal use). */
    BCMOLT_SERIALIZER_FLAG_SKIP_DATA_ENTIRELY = 1 << 2,
} bcmolt_serializer_flag;

/** Get the number of bytes that a given type would occupy if serialized.
 *
 * \param[in]  type   Type that will be serialized.
 * \param[in]  flags  Flags to control the serialization process.
 * \param[in]  data   Pointer to the data itself.
 * \param[out] length Packed size.
 * \return            Query operation result.
 */
bcmos_errno bcmolt_type_get_serialized_length(
    const bcmolt_type_descr *type,
    bcmolt_serializer_flag flags,
    const void *data,
    uint32_t *length);

/** Packs a given type into a byte stream using a TLV-style format.
 *
 * \param[in]  type  Type that will be serialized.
 * \param[in]  flags Flags to control the serialization process.
 * \param[in]  data  Pointer to the data itself.
 * \param[in]  buf   Buffer to pack into.
 * \return           Pack operation result.
 */
bcmos_errno bcmolt_type_serialize(
    const bcmolt_type_descr *type,
    bcmolt_serializer_flag flags,
    const void *data,
    bcmolt_buf *buf);

/** Scans past serialized piece of data and collects memory requirements requirements above and beyond sizeof().
 *
 * \param[in]  type  Type that will be serialized.
 * \param[in]  flags Flags to control the serialization process.
 * \param[in]  buf   Buffer that contains the serialized data.
 * \param[out] size  Number of additional storage bytes required.
 * \return           Query operation result.
 */
bcmos_errno bcmolt_type_extra_mem_scan(
    const bcmolt_type_descr *type,
    bcmolt_serializer_flag flags,
    bcmolt_buf *buf,
    uint32_t *size);

/** Unpacks a given type from a byte stream using a TLV-style format.
 *
 * \param[in] type      Type that will be deserialized.
 * \param[in] flags     Flags to control the serialization process.
 * \param[in] data      Pointer to the data itself.
 * \param[in] buf       Buffer to unpack from.
 * \param[in] extra_mem Buffer to use for allocating pointer fields that are NULL.
 * \return              Unpack operation result.
 */
bcmos_errno bcmolt_type_deserialize(
    const bcmolt_type_descr *type,
    bcmolt_serializer_flag flags,
    void *data,
    bcmolt_buf *buf,
    bcmolt_buf *extra_mem);

/** Initialize the serializer service (should be called at init time). */
void bcmolt_serializer_init(void);

#endif
