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

/* bcmolt_serializer.c:
 * Generic utility to serialize/deserialize data in a TLV-style format
 */

#include <bcmos_system.h>
#include <bcmolt_math.h>
#include <bcm_dev_log.h>
#include "bcmolt_buf.h"
#include "bcmolt_type_metadata.h"
#include "bcmolt_serializer.h"

#ifdef ENABLE_LOG
static dev_log_id serializer_log_id = DEV_LOG_INVALID_ID;
#endif

#define BOOL_TO_ERR(ok) (ok ? BCM_ERR_OK : BCM_ERR_OVERFLOW)

static inline uint8_t _read_u8(const void *data, uint16_t offset)
{
    const uint8_t *ptr = (const uint8_t *)data + offset;
    return *ptr;
}

static inline uint16_t _read_u16(const void *data, uint16_t offset)
{
    const void *ptr = (const uint8_t *)data + offset;
    return *(const uint16_t *)ptr;
}

static inline uint32_t _read_u32(const void *data, uint16_t offset)
{
    const void *ptr = (const uint8_t *)data + offset;
    return *(const uint32_t *)ptr;
}

static inline uint64_t _read_u64(const void *data, uint16_t offset)
{
    const void *ptr = (const uint8_t *)data + offset;
    return *(const uint64_t *)ptr;
}

static inline uint64_t _read_unum(const void *data, uint16_t offset, uint8_t width)
{
    switch (width)
    {
    case 1:
        return _read_u8(data, offset);
    case 2:
        return _read_u16(data, offset);
    case 4:
        return _read_u32(data, offset);
    case 8:
        return _read_u64(data, offset);
    default:
        BCMOS_TRACE_ERR("Unexpected number width: %u\n", width);
        return 0;
    }
}

static inline void _write_u8(void *data, uint16_t offset, uint8_t val)
{
    uint8_t *ptr = (uint8_t *)data + offset;
    *ptr = val;
}

static inline void _write_u16(void *data, uint16_t offset, uint16_t val)
{
    void *ptr = (uint8_t *)data + offset;
    *(uint16_t *)ptr = val;
}

static inline void _write_u32(void *data, uint16_t offset, uint32_t val)
{
    void *ptr = (uint8_t *)data + offset;
    *(uint32_t *)ptr = val;
}

static inline void _write_u64(void *data, uint16_t offset, uint64_t val)
{
    void *ptr = (uint8_t *)data + offset;
    *(uint64_t *)ptr = val;
}

static inline void _write_unum(void *data, uint16_t offset, uint8_t width, uint64_t val)
{
    switch (width)
    {
    case 1:
        _write_u8(data, offset, (uint8_t)val);
        break;
    case 2:
        _write_u16(data, offset, (uint16_t)val);
        break;
    case 4:
        _write_u32(data, offset, (uint32_t)val);
        break;
    case 8:
        _write_u64(data, offset, (uint64_t)val);
        break;
    default:
        BCMOS_TRACE_ERR("Unexpected number width: %u\n", width);
        break;
    }
}

/* Copy a number from one buffer to another and one datatype size to another. */
static void _copy_number(uint8_t *dest, uint8_t dest_num_size, const uint8_t *src, uint8_t src_num_size)
{
    if (src_num_size < dest_num_size)
    {
        /* Copy into the larger number, adding padding. */
#if (BCM_CPU_ENDIAN == BCMOS_ENDIAN_BIG)
        memset(dest, 0, dest_num_size - src_num_size); /* big endian - padding at start */
        memcpy(dest + (dest_num_size - src_num_size), src, src_num_size);
#else
        memcpy(dest, src, src_num_size);
        memset(dest + src_num_size, 0, dest_num_size - src_num_size); /* little endian - padding at end */
#endif
    }
    else if (src_num_size > dest_num_size)
    {
        /* Copy into the smaller number, potentially truncating. */
#if (BCM_CPU_ENDIAN == BCMOS_ENDIAN_BIG)
        memcpy(dest, src + (src_num_size - dest_num_size), dest_num_size);
#else
        memcpy(dest, src, dest_num_size);
#endif
    }
    else // src_num_size == dest_num_size
    {
        memcpy(dest, src, dest_num_size);
    }
}

static inline void *_read_dyn_array_ptr(void *data, uint16_t offset)
{
    void *array_ptr = (uint8_t *)data + offset;
    return *(void **)array_ptr;
}

static inline const void *_read_dyn_array_ptr_const(const void *data, uint16_t offset)
{
    const void *array_ptr = (const uint8_t *)data + offset;
    return *(void * const *)array_ptr;
}

static inline void _write_dyn_array_ptr(void *data, uint16_t offset, void *new_ptr)
{
    void *array_ptr = (uint8_t *)data + offset;
    *(void **)array_ptr = new_ptr;
}

static inline bcmos_bool _presence_mask_has_bit(const bcmolt_type_descr *type, const void *data, uint16_t bit)
{
    const void *mask = (const uint8_t *)data + type->mask_offset;
    return (*(const uint64_t *)mask == 0) || (*(const uint64_t *)mask & (1ULL << bit)) != 0;
}

static inline void _clear_presence_mask(const bcmolt_type_descr *type, void *data)
{
    void *mask = (uint8_t *)data + type->mask_offset;
    *(uint64_t *)mask = 0;
}

static inline void _set_presence_mask_bit(const bcmolt_type_descr *type, void *data, uint16_t bit)
{
    void *mask = (uint8_t *)data + type->mask_offset;
    *(uint64_t *)mask |= (1ULL << bit);
}

static const bcmolt_field_descr *_find_classified_substruct_for_val(const bcmolt_type_descr *type, uint64_t val)
{
    uint16_t i;
    const bcmolt_field_descr *classifier_field = &type->x.u.common_fields[type->x.u.classifier_idx];
    for (i = 0; classifier_field->type->x.e.vals[i].name != NULL; i++)
    {
        if (classifier_field->type->x.e.vals[i].val == val)
        {
            return &type->x.u.union_fields[i];
        }
    }
    return &type->x.u.union_fields[i]; /* default is at the end of the list */
}

static const bcmolt_field_descr *_find_classified_substruct(const bcmolt_type_descr *type, const void *data)
{
    const bcmolt_field_descr *classifier_field = &type->x.u.common_fields[type->x.u.classifier_idx];
    uint64_t classifier_val = _read_unum(
        data,
        classifier_field->offset,
        classifier_field->type->size);
    return _find_classified_substruct_for_val(type, classifier_val);
}

static bcmos_errno _get_field_serialized_length(
    const bcmolt_field_descr *field,
    bcmolt_serializer_flag flags,
    const void *data,
    uint32_t *length)
{
    uint32_t field_len = 0;
    const void *field_ptr = (const uint8_t *)data + field->offset;
    bcmos_errno err = bcmolt_type_get_serialized_length(field->type, flags, field_ptr, &field_len);
    if (err == BCM_ERR_OK)
    {
        *length += 4 + field_len; /* 2 bytes of ID, 2 bytes of length */
    }
    return err;
}

static bcmos_bool _is_nested_type(bcmolt_base_type_id type)
{
    switch (type)
    {
    case BCMOLT_BASE_TYPE_ID_STRUCT:
    case BCMOLT_BASE_TYPE_ID_UNION:
    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
        return BCMOS_TRUE;
    default:
        return BCMOS_FALSE;
    }
}

static bcmos_bool _should_skip_data(const bcmolt_type_descr *type, bcmolt_serializer_flag flags)
{
    if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DATA_ENTIRELY) != 0)
    {
        return BCMOS_TRUE;
    }

    if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DATA) != 0 && !_is_nested_type(type->base_type))
    {
        return BCMOS_TRUE;
    }

    return BCMOS_FALSE;
}

bcmos_errno bcmolt_type_get_serialized_length(
    const bcmolt_type_descr *type,
    bcmolt_serializer_flag flags,
    const void *data,
    uint32_t *length)
{
    bcmos_errno err;
    BCM_LOG(DEBUG, serializer_log_id, "Get serialized length for type: %s\n", type->name);

    if (_should_skip_data(type, flags))
    {
        *length = 0;
        return BCM_ERR_OK;
    }

    switch (type->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_SNUM:
    case BCMOLT_BASE_TYPE_ID_UNUM:
    case BCMOLT_BASE_TYPE_ID_UNUM_HEX:
    case BCMOLT_BASE_TYPE_ID_FLOAT:
    case BCMOLT_BASE_TYPE_ID_STRING:
        *length = type->size;
        return BCM_ERR_OK;

    case BCMOLT_BASE_TYPE_ID_BOOL:
        *length = 1;
        return BCM_ERR_OK;

    case BCMOLT_BASE_TYPE_ID_IPV4:
        *length = 4;
        return BCM_ERR_OK;

    case BCMOLT_BASE_TYPE_ID_IPV6:
        *length = 16;
        return BCM_ERR_OK;

    case BCMOLT_BASE_TYPE_ID_MAC:
        *length = 6;
        return BCM_ERR_OK;

    case BCMOLT_BASE_TYPE_ID_ENUM:
    case BCMOLT_BASE_TYPE_ID_ENUM_MASK:
        *length = type->x.e.base_type->size;
        return BCM_ERR_OK;

    case BCMOLT_BASE_TYPE_ID_BINARY_DYN:
        *length = 4;
        if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA) == 0)
        {
            *length += _read_u32(data, type->x.binary_dyn.len_offset);
        }
        return BCM_ERR_OK;

    case BCMOLT_BASE_TYPE_ID_BINARY_FIXED:
        *length = type->x.binary_fixed.len;
        return BCM_ERR_OK;

    case BCMOLT_BASE_TYPE_ID_STRUCT:
    {
        uint16_t i;
        if (type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
        {
            *length = 0;
            for (i = 0; i < type->x.s.num_fields; i++)
            {
                const void *field_ptr = (const uint8_t *)data + type->x.s.fields[i].offset;
                uint32_t field_length;
                err = bcmolt_type_get_serialized_length(type->x.s.fields[i].type, flags, field_ptr, &field_length);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
                *length += field_length;
            }
        }
        else
        {
            *length = 2; /* terminator */
            for (i = 0; i < type->x.s.num_fields; i++)
            {
                if (_presence_mask_has_bit(type, data, type->x.s.fields[i].id))
                {
                    err = _get_field_serialized_length(&type->x.s.fields[i], flags, data, length);
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                }
            }
        }
        return BCM_ERR_OK;
    }

    case BCMOLT_BASE_TYPE_ID_UNION:
    {
        uint16_t i;
        *length = 2; /* terminator */

        BCMOS_TRACE_CHECK_RETURN(
            type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK,
            BCM_ERR_INTERNAL,
            "Error: unions with no presence mask are not supported.\n");

        for (i = 0; i < type->x.u.num_common_fields; i++)
        {
            if (_presence_mask_has_bit(type, data, type->x.u.common_fields[i].id))
            {
                err = _get_field_serialized_length(&type->x.u.common_fields[i], flags, data, length);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
                if (type->x.u.classifier_idx == i)
                {
                    const bcmolt_field_descr *substruct = _find_classified_substruct(type, data);
                    if (substruct->type == NULL)
                    {
                        *length += 2; /* terminator */
                    }
                    else
                    {
                        uint32_t field_len = 0;
                        const void *substruct_ptr = (const uint8_t *)data + substruct->offset;
                        err = bcmolt_type_get_serialized_length(substruct->type, flags, substruct_ptr, &field_len);
                        if (err != BCM_ERR_OK)
                        {
                            return err;
                        }
                        *length += field_len;
                    }
                }
            }
        }

        return BCM_ERR_OK;
    }

    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
    {
        const bcmolt_type_descr *elem_type;
        const void *arr_data;
        uint64_t arr_len;
        uint16_t i;
        uint32_t elem_len = 0;

        if (type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN)
        {
            elem_type = type->x.arr_dyn.elem_type;
            arr_data = _read_dyn_array_ptr_const(data, type->x.arr_dyn.data_offset);
            arr_len = _read_unum(data, type->x.arr_dyn.len_offset, type->x.arr_dyn.len_type->size);
            *length = type->x.arr_dyn.len_type->size;

            if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA) != 0)
            {
                flags |= BCMOLT_SERIALIZER_FLAG_SKIP_DATA_ENTIRELY; /* skip the data part of the element TLVs */
            }
        }
        else
        {
            elem_type = type->x.arr_fixed.elem_type;
            arr_data = (const uint8_t *)data + type->x.arr_fixed.data_offset;
            arr_len = type->x.arr_fixed.size;
            *length = 0;
        }
        *length += 2; /* terminator */

        if (type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
        {
            for (i = 0; i < arr_len; i++)
            {
                const void *elem_ptr = (const uint8_t *)arr_data + (i * elem_type->size);
                err = bcmolt_type_get_serialized_length(elem_type, flags, elem_ptr, length);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
            }
        }
        else
        {
            for (i = 0; i < arr_len; i++)
            {
                if (_presence_mask_has_bit(type, data, i))
                {
                    const void *elem_ptr = (const uint8_t *)arr_data + (i * elem_type->size);
                    err = bcmolt_type_get_serialized_length(elem_type, flags, elem_ptr, &elem_len);
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                    *length += 4 + elem_len; /* 2 bytes of index, 2 bytes of length */
                }
            }
        }
        return BCM_ERR_OK;
    }

    default:
        return BCM_ERR_NOT_SUPPORTED;
    }
}

static bcmos_errno _serialize_tlv(
    const bcmolt_type_descr *type,
    bcmolt_serializer_flag flags,
    const void *data,
    uint16_t id,
    bcmolt_buf *buf)
{
    uint32_t len = 0;
    bcmos_errno err = bcmolt_type_get_serialized_length(type, flags, data, &len);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    BCM_LOG(DEBUG, serializer_log_id, "Writing TLV with ID=%u len=%u\n", id, len);

    /* Pack ID (16 bits for future compatibility) */
    if (!bcmolt_buf_write_u16(buf, id))
    {
        return BCM_ERR_OVERFLOW;
    }

    /* Pack length (16 bits, unless it's >= 0xFFFF, in which case we use 0xFFFF to mean "32 bits follow") */
    if (len >= 0xFFFF)
    {
        if (!bcmolt_buf_write_u16(buf, 0xFFFF) || !bcmolt_buf_write_u32(buf, len))
        {
            return BCM_ERR_OVERFLOW;
        }
    }
    else
    {
        if (!bcmolt_buf_write_u16(buf, (uint16_t)len))
        {
            return BCM_ERR_OVERFLOW;
        }
    }

    /* Pack the TLV data itself */
    return bcmolt_type_serialize(type, flags, data, buf);
}

static bcmos_errno _serialize_terminator_tlv(bcmolt_buf *buf)
{
    return BOOL_TO_ERR(bcmolt_buf_write_u16(buf, BCMOLT_SERIALIZER_TERMINATOR_TLV_ID));
}

static bcmos_errno _serialize_field(
    const bcmolt_field_descr *field,
    bcmolt_serializer_flag flags,
    const void *data,
    bcmolt_buf *buf)
{
    return _serialize_tlv(field->type, flags, (const uint8_t *)data + field->offset, field->id, buf);
}

bcmos_errno bcmolt_type_serialize(
    const bcmolt_type_descr *type,
    bcmolt_serializer_flag flags,
    const void *data,
    bcmolt_buf *buf)
{
    bcmos_errno err;
    BCM_LOG(DEBUG, serializer_log_id, "Serialize type: %s\n", type->name);

    if (_should_skip_data(type, flags))
    {
        return BCM_ERR_OK;
    }

    switch (type->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_SNUM:
        switch (type->size)
        {
        case 1:
            return BOOL_TO_ERR(bcmolt_buf_write_s8(buf, *(const int8_t *)data));
        case 2:
            return BOOL_TO_ERR(bcmolt_buf_write_s16(buf, *(const int16_t *)data));
        case 4:
            return BOOL_TO_ERR(bcmolt_buf_write_s32(buf, *(const int32_t *)data));
        case 8:
            return BOOL_TO_ERR(bcmolt_buf_write_s64(buf, *(const int64_t *)data));
        default:
            return BCM_ERR_NOT_SUPPORTED;
        }

    case BCMOLT_BASE_TYPE_ID_UNUM:
    case BCMOLT_BASE_TYPE_ID_UNUM_HEX:
        switch (type->size)
        {
        case 1:
            return BOOL_TO_ERR(bcmolt_buf_write_u8(buf, *(const uint8_t *)data));
        case 2:
            return BOOL_TO_ERR(bcmolt_buf_write_u16(buf, *(const uint16_t *)data));
        case 3:
            return BOOL_TO_ERR(bcmolt_buf_write_u24(buf, *(const uint24_t *)data));
        case 4:
            return BOOL_TO_ERR(bcmolt_buf_write_u32(buf, *(const uint32_t *)data));
        case 8:
            return BOOL_TO_ERR(bcmolt_buf_write_u64(buf, *(const uint64_t *)data));
        default:
            return BCM_ERR_NOT_SUPPORTED;
        }

    case BCMOLT_BASE_TYPE_ID_FLOAT:
        switch (type->size)
        {
        case 4:
            return BOOL_TO_ERR(bcmolt_buf_write_float(buf, *(const float *)data));
        case 8:
            return BOOL_TO_ERR(bcmolt_buf_write_double(buf, *(const double *)data));
        default:
            return BCM_ERR_NOT_SUPPORTED;
        }

    case BCMOLT_BASE_TYPE_ID_STRING:
        return BOOL_TO_ERR(bcmolt_buf_write(buf, (const uint8_t *)data, type->size));

    case BCMOLT_BASE_TYPE_ID_BOOL:
        return BOOL_TO_ERR(bcmolt_buf_write_bool(buf, *(const bcmos_bool *)data));

    case BCMOLT_BASE_TYPE_ID_IPV4:
        return BOOL_TO_ERR(bcmolt_buf_write_ipv4_address(buf, *(const bcmos_ipv4_address *)data));

    case BCMOLT_BASE_TYPE_ID_IPV6:
        return BOOL_TO_ERR(bcmolt_buf_write_ipv6_address(buf, *(const bcmos_ipv6_address *)data));

    case BCMOLT_BASE_TYPE_ID_MAC:
        return BOOL_TO_ERR(bcmolt_buf_write_mac_address(buf, *(const bcmos_mac_address *)data));

    case BCMOLT_BASE_TYPE_ID_ENUM:
    case BCMOLT_BASE_TYPE_ID_ENUM_MASK:
    {
        /* The compiler may have allocated a different size for the enum compared to the base type (larger for padding
         * or smaller if enums are packed). Convert the enum into a number, then serialize that number. */
        uint8_t scratch[8] = {};
        _copy_number(scratch, type->x.e.base_type->size, data, type->size);
        return bcmolt_type_serialize(type->x.e.base_type, flags, scratch, buf);
    }

    case BCMOLT_BASE_TYPE_ID_BINARY_DYN:
    {
        uint32_t string_len = _read_u32(data, type->x.binary_dyn.len_offset);
        if (!bcmolt_buf_write_u32(buf, string_len))
        {
            return BCM_ERR_OVERFLOW;
        }
        if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA) == 0)
        {
            const void *string_data = _read_dyn_array_ptr_const(data, type->x.binary_dyn.data_offset);
            BCMOS_TRACE_CHECK_RETURN(
                string_len != 0 && string_data == NULL,
                BCM_ERR_NOMEM,
                "Error: array field is NULL. You must allocate memory for this pointer before packing.\n");
            if (!bcmolt_buf_write(buf, string_data, string_len))
            {
                return BCM_ERR_OVERFLOW;
            }
        }
        return BCM_ERR_OK;
    }

    case BCMOLT_BASE_TYPE_ID_BINARY_FIXED:
    {
        const void *string_data = (const uint8_t *)data + type->x.binary_fixed.data_offset;
        return BOOL_TO_ERR(bcmolt_buf_write(buf, string_data, type->x.binary_fixed.len));
    }

    case BCMOLT_BASE_TYPE_ID_STRUCT:
    {
        uint16_t i;

        if (type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
        {
            for (i = 0; i < type->x.s.num_fields; i++)
            {
                const bcmolt_field_descr *field = &type->x.s.fields[i];
                err = bcmolt_type_serialize(field->type, flags, (const uint8_t *)data + field->offset, buf);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
            }
            return BCM_ERR_OK;
        }
        else
        {
            for (i = 0; i < type->x.s.num_fields; i++)
            {
                if (_presence_mask_has_bit(type, data, type->x.s.fields[i].id))
                {
                    err = _serialize_field(&type->x.s.fields[i], flags, data, buf);
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                }
            }
            return _serialize_terminator_tlv(buf);
        }
    }

    case BCMOLT_BASE_TYPE_ID_UNION:
    {
        uint16_t i;

        BCMOS_TRACE_CHECK_RETURN(
            type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK,
            BCM_ERR_INTERNAL,
            "Error: unions with no presence mask are not supported.\n");

        for (i = 0; i < type->x.u.num_common_fields; i++)
        {
            if (_presence_mask_has_bit(type, data, type->x.u.common_fields[i].id))
            {
                err = _serialize_field(&type->x.u.common_fields[i], flags, data, buf);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
                if (type->x.u.classifier_idx == i)
                {
                    const bcmolt_field_descr *substruct = _find_classified_substruct(type, data);
                    if (substruct->type == NULL)
                    {
                        err = _serialize_terminator_tlv(buf);
                    }
                    else
                    {
                        const void *substruct_ptr = (const uint8_t *)data + substruct->offset;
                        err = bcmolt_type_serialize(substruct->type, flags, substruct_ptr, buf);
                    }
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                }
            }
        }

        return _serialize_terminator_tlv(buf);
    }

    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
    {
        const bcmolt_type_descr *elem_type;
        uint64_t arr_len;
        const void *arr_data;
        uint16_t i;

        if (type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN)
        {
            const void *arr_len_ptr = (const uint8_t *)data + type->x.arr_dyn.len_offset;
            elem_type = type->x.arr_dyn.elem_type;
            arr_len = _read_unum(data, type->x.arr_dyn.len_offset, type->x.arr_dyn.len_type->size);

            /* Pack the array length (only for dynamically-sized arrays) */
            err = bcmolt_type_serialize(type->x.arr_dyn.len_type, BCMOLT_SERIALIZER_FLAG_NONE, arr_len_ptr, buf);
            if (err != BCM_ERR_OK)
            {
                return err;
            }

            arr_data = _read_dyn_array_ptr_const(data, type->x.arr_dyn.data_offset);
            BCMOS_TRACE_CHECK_RETURN(
                arr_len != 0 && arr_data == NULL,
                BCM_ERR_NOMEM,
                "Error: array field is NULL. You must allocate memory for this pointer before packing.\n");

            if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA) != 0)
            {
                flags |= BCMOLT_SERIALIZER_FLAG_SKIP_DATA_ENTIRELY; /* skip the data part of the element TLVs */
            }
        }
        else
        {
            elem_type = type->x.arr_fixed.elem_type;
            arr_len = type->x.arr_fixed.size;
            arr_data = (const uint8_t *)data + type->x.arr_fixed.data_offset;
        }

        if (type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
        {
            for (i = 0; i < arr_len; i++)
            {
                const void *elem_ptr = (const uint8_t *)arr_data + (i * elem_type->size);
                err = bcmolt_type_serialize(elem_type, flags, elem_ptr, buf);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
            }
            return BCM_ERR_OK;
        }
        else
        {
            for (i = 0; i < arr_len; i++)
            {
                if (_presence_mask_has_bit(type, data, i))
                {
                    const void *elem_ptr = (const uint8_t *)arr_data + (i * elem_type->size);

                    /* Pack the element as a TLV (ID = array index) */
                    err = _serialize_tlv(elem_type, flags, elem_ptr, i, buf);
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                }
            }
            return _serialize_terminator_tlv(buf);
        }
    }

    default:
        return BCM_ERR_NOT_SUPPORTED;
    }
}

static const bcmolt_field_descr *_find_field_by_id(uint16_t num_fields, const bcmolt_field_descr *fields, uint16_t id)
{
    uint16_t i;
    for (i = 0; i < num_fields; i++)
    {
        if (fields[i].id == id)
        {
            return &fields[i];
        }
    }
    return NULL;
}

static bcmos_errno _deserialize_tlv(bcmolt_buf *buf, uint16_t *id, bcmolt_buf *field_buf)
{
    uint16_t len;

    if (!bcmolt_buf_read_u16(buf, id))
    {
        return BCM_ERR_OVERFLOW;
    }

    if (*id == BCMOLT_SERIALIZER_TERMINATOR_TLV_ID)
    {
        return BCM_ERR_NO_MORE;
    }

    if (!bcmolt_buf_read_u16(buf, &len))
    {
        return BCM_ERR_OVERFLOW;
    }

    BCM_LOG(DEBUG, serializer_log_id, "Reading TLV with ID=%u len=%u\n", *id, len);

    /* The field buffer is a copy of the parent buffer with its length limited to the TLV length. */
    *field_buf = *buf;
    bcmolt_buf_set_length(field_buf, bcmolt_buf_get_used(buf) + len);

    /* Advance the parent buffer past the field buffer. */
    if (!bcmolt_buf_skip(buf, len))
    {
        return BCM_ERR_OVERFLOW;
    }

    return BCM_ERR_OK;
}

bcmos_errno bcmolt_type_extra_mem_scan(
    const bcmolt_type_descr *type,
    bcmolt_serializer_flag flags,
    bcmolt_buf *buf,
    uint32_t *size)
{
    bcmos_errno err;
    BCM_LOG(DEBUG, serializer_log_id, "Extra mem scan for type: %s\n", type->name);

    if (_should_skip_data(type, flags))
    {
        return BCM_ERR_OK;
    }

    switch (type->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_SNUM:
    case BCMOLT_BASE_TYPE_ID_UNUM:
    case BCMOLT_BASE_TYPE_ID_UNUM_HEX:
    case BCMOLT_BASE_TYPE_ID_FLOAT:
    case BCMOLT_BASE_TYPE_ID_STRING:
        return BOOL_TO_ERR(bcmolt_buf_skip(buf, type->size));

    case BCMOLT_BASE_TYPE_ID_BOOL:
        return BOOL_TO_ERR(bcmolt_buf_skip(buf, 1));

    case BCMOLT_BASE_TYPE_ID_IPV4:
        return BOOL_TO_ERR(bcmolt_buf_skip(buf, 4));

    case BCMOLT_BASE_TYPE_ID_IPV6:
        return BOOL_TO_ERR(bcmolt_buf_skip(buf, 16));

    case BCMOLT_BASE_TYPE_ID_MAC:
        return BOOL_TO_ERR(bcmolt_buf_skip(buf, 6));

    case BCMOLT_BASE_TYPE_ID_ENUM:
    case BCMOLT_BASE_TYPE_ID_ENUM_MASK:
        return bcmolt_type_extra_mem_scan(type->x.e.base_type, flags, buf, size);

    case BCMOLT_BASE_TYPE_ID_BINARY_DYN:
    {
        uint32_t string_len = 0;
        if (!bcmolt_buf_read_u32(buf, &string_len))
        {
            return BCM_ERR_OVERFLOW;
        }
        if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA) == 0)
        {
            *size += BCMOS_ROUND_TO_WORD(string_len);
            if (!bcmolt_buf_skip(buf, string_len))
            {
                return BCM_ERR_OVERFLOW;
            }
        }
        return BCM_ERR_OK;
    }

    case BCMOLT_BASE_TYPE_ID_BINARY_FIXED:
        return BOOL_TO_ERR(bcmolt_buf_skip(buf, type->x.binary_fixed.len));

    case BCMOLT_BASE_TYPE_ID_STRUCT:
    {
        const bcmolt_field_descr *field;

        if (type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
        {
            uint16_t i;
            for (i = 0; i < type->x.s.num_fields; ++i)
            {
                err = bcmolt_type_extra_mem_scan(type->x.s.fields[i].type, flags, buf, size);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
            }
        }
        else
        {
            uint16_t id;
            bcmolt_buf field_buf;
            while (bcmolt_buf_get_remaining_size(buf) > 0)
            {
                err = _deserialize_tlv(buf, &id, &field_buf);
                if (err != BCM_ERR_OK)
                {
                    return err == BCM_ERR_NO_MORE ? BCM_ERR_OK : err;
                }

                field = _find_field_by_id(type->x.s.num_fields, type->x.s.fields, id);
                if (field == NULL)
                {
                    BCM_LOG(INFO, serializer_log_id, "Unknown field discarded, ID=%u\n", id);
                }
                else
                {
                    err = bcmolt_type_extra_mem_scan(field->type, flags, &field_buf, size);
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                }
            }
        }
        return BCM_ERR_OK;
    }

    case BCMOLT_BASE_TYPE_ID_UNION:
    {
        uint16_t id;
        bcmolt_buf field_buf;
        const bcmolt_field_descr *field;

        BCMOS_TRACE_CHECK_RETURN(
            type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK,
            BCM_ERR_INTERNAL,
            "Error: unions with no presence mask are not supported.\n");

        while (bcmolt_buf_get_remaining_size(buf) > 0)
        {
            err = _deserialize_tlv(buf, &id, &field_buf);
            if (err != BCM_ERR_OK)
            {
                return err == BCM_ERR_NO_MORE ? BCM_ERR_OK : err;
            }

            field = _find_field_by_id(type->x.u.num_common_fields, type->x.u.common_fields, id);
            if (field == NULL)
            {
                BCM_LOG(INFO, serializer_log_id, "Unknown field discarded, ID=%u\n", id);
            }
            else if (type->x.u.common_fields[type->x.u.classifier_idx].id == id)
            {
                /* We need to deserialize the classifier field, since the classified data will follow */
                const bcmolt_type_descr *classifier_type = type->x.u.common_fields[type->x.u.classifier_idx].type;
                uint64_t classifier_val = 0;
                const bcmolt_field_descr *substruct;

                /* Unpack the classifier itself into a local variable so we can check it */
                err = bcmolt_type_deserialize(classifier_type, flags, &classifier_val, &field_buf, NULL);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
                classifier_val = _read_unum(&classifier_val, 0, classifier_type->size);

                /* Unpack the corresponding classified substructure */
                substruct = _find_classified_substruct_for_val(type, classifier_val);
                if (substruct->type != NULL)
                {
                    err = bcmolt_type_extra_mem_scan(substruct->type, flags, buf, size);
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                }
            }
            else
            {
                err = bcmolt_type_extra_mem_scan(field->type, flags, &field_buf, size);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
            }
        }
        return BCM_ERR_OK;
    }

    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
    {
        const bcmolt_type_descr *elem_type;
        uint64_t arr_len;
        uint16_t idx;

        if (type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN)
        {
            elem_type = type->x.arr_dyn.elem_type;

            /* Unpack the array length (only for dynamically-sized arrays) */
            err = bcmolt_type_deserialize(type->x.arr_dyn.len_type, BCMOLT_SERIALIZER_FLAG_NONE, &arr_len, buf, NULL);
            if (err != BCM_ERR_OK)
            {
                return err;
            }
            arr_len = _read_unum(&arr_len, 0, type->x.arr_dyn.len_type->size);

            if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA) != 0)
            {
                flags |= BCMOLT_SERIALIZER_FLAG_SKIP_DATA_ENTIRELY; /* skip the data part of the element TLVs */
            }
            else
            {
                /* Allocate space for the dynamic array itself */
                *size += BCMOS_ROUND_TO_WORD(elem_type->size * arr_len);
            }
        }
        else
        {
            elem_type = type->x.arr_fixed.elem_type;
            arr_len = type->x.arr_fixed.size;
        }

        if (type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
        {
            for (idx = 0; idx < arr_len; idx++)
            {
                err = bcmolt_type_extra_mem_scan(elem_type, flags, buf, size);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
            }
        }
        else
        {
            bcmolt_buf elem_buf;
            while (bcmolt_buf_get_remaining_size(buf) > 0)
            {
                err = _deserialize_tlv(buf, &idx, &elem_buf);
                if (err != BCM_ERR_OK)
                {
                    return err == BCM_ERR_NO_MORE ? BCM_ERR_OK : err;
                }

                if (idx >= arr_len)
                {
                    BCM_LOG(WARNING, serializer_log_id, "Out-of-bounds array element discarded, idx=%u\n", idx);
                }
                else
                {
                    err = bcmolt_type_extra_mem_scan(elem_type, flags, &elem_buf, size);
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                }
            }
        }
        return BCM_ERR_OK;
    }

    default:
        return BCM_ERR_NOT_SUPPORTED;
    }
}

bcmos_errno bcmolt_type_deserialize(
    const bcmolt_type_descr *type,
    bcmolt_serializer_flag flags,
    void *data,
    bcmolt_buf *buf,
    bcmolt_buf *extra_mem)
{
    bcmos_errno err;
    BCM_LOG(DEBUG, serializer_log_id, "Deserialize type: %s\n", type->name);

    if (_should_skip_data(type, flags))
    {
        return BCM_ERR_OK;
    }

    switch (type->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_SNUM:
        switch (type->size)
        {
        case 1:
            return BOOL_TO_ERR(bcmolt_buf_read_s8(buf, (int8_t *)data));
        case 2:
            return BOOL_TO_ERR(bcmolt_buf_read_s16(buf, (int16_t *)data));
        case 4:
            return BOOL_TO_ERR(bcmolt_buf_read_s32(buf, (int32_t *)data));
        case 8:
            return BOOL_TO_ERR(bcmolt_buf_read_s64(buf, (int64_t *)data));
        default:
            return BCM_ERR_NOT_SUPPORTED;
        }

    case BCMOLT_BASE_TYPE_ID_UNUM:
    case BCMOLT_BASE_TYPE_ID_UNUM_HEX:
        switch (type->size)
        {
        case 1:
            return BOOL_TO_ERR(bcmolt_buf_read_u8(buf, (uint8_t *)data));
        case 2:
            return BOOL_TO_ERR(bcmolt_buf_read_u16(buf, (uint16_t *)data));
        case 3:
            return BOOL_TO_ERR(bcmolt_buf_read_u24(buf, (uint24_t *)data));
        case 4:
            return BOOL_TO_ERR(bcmolt_buf_read_u32(buf, (uint32_t *)data));
        case 8:
            return BOOL_TO_ERR(bcmolt_buf_read_u64(buf, (uint64_t *)data));
        default:
            return BCM_ERR_NOT_SUPPORTED;
        }

    case BCMOLT_BASE_TYPE_ID_FLOAT:
        switch (type->size)
        {
        case 4:
            return BOOL_TO_ERR(bcmolt_buf_read_float(buf, (float *)data));
        case 8:
            return BOOL_TO_ERR(bcmolt_buf_read_double(buf, (double *)data));
        default:
            return BCM_ERR_NOT_SUPPORTED;
        }

    case BCMOLT_BASE_TYPE_ID_STRING:
        return BOOL_TO_ERR(bcmolt_buf_read(buf, (uint8_t *)data, type->size));

    case BCMOLT_BASE_TYPE_ID_BOOL:
        return BOOL_TO_ERR(bcmolt_buf_read_bool(buf, (bcmos_bool *)data));

    case BCMOLT_BASE_TYPE_ID_IPV4:
        return BOOL_TO_ERR(bcmolt_buf_read_ipv4_address(buf, (bcmos_ipv4_address *)data));

    case BCMOLT_BASE_TYPE_ID_IPV6:
        return BOOL_TO_ERR(bcmolt_buf_read_ipv6_address(buf, (bcmos_ipv6_address *)data));

    case BCMOLT_BASE_TYPE_ID_MAC:
        return BOOL_TO_ERR(bcmolt_buf_read_mac_address(buf, (bcmos_mac_address *)data));

    case BCMOLT_BASE_TYPE_ID_ENUM:
    case BCMOLT_BASE_TYPE_ID_ENUM_MASK:
    {
        /* The compiler may have allocated a different size for the enum compared to the base type (larger for padding
         * or smaller if enums are packed). Deserialize to a scratchpad, then copy the value to the target. */
        uint8_t scratch[8] = {};
        err = bcmolt_type_deserialize(type->x.e.base_type, flags, scratch, buf, extra_mem);
        if (err == BCM_ERR_OK)
        {
            _copy_number(data, type->size, scratch, type->x.e.base_type->size);
        }
        return err;
    }

    case BCMOLT_BASE_TYPE_ID_BINARY_DYN:
    {
        void *arr_data = _read_dyn_array_ptr(data, type->x.binary_dyn.data_offset);
        uint32_t old_len = _read_u32(data, type->x.binary_dyn.len_offset);
        uint32_t arr_len = 0;

        if (!bcmolt_buf_read_u32(buf, &arr_len))
        {
            return BCM_ERR_OVERFLOW;
        }

        if (arr_len == 0 || (flags & BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA) != 0)
        {
            /* Nothing else to do (no data to deserialize) */
        }
        else if (arr_data == NULL)
        {
            uint32_t bytes_to_alloc;

            BCMOS_TRACE_CHECK_RETURN(
                extra_mem == NULL,
                BCM_ERR_NOMEM,
                "Error: array field is NULL. You must allocate memory for this pointer before unpacking.\n");

            bytes_to_alloc = BCMOS_ROUND_TO_WORD(arr_len);
            arr_data = bcmolt_buf_snap_get(extra_mem);
            if (!bcmolt_buf_skip(extra_mem, bytes_to_alloc))
            {
                return BCM_ERR_NOMEM;
            }
            _write_dyn_array_ptr(data, type->x.binary_dyn.data_offset, arr_data);
        }
        else
        {
            if (arr_len > old_len)
            {
                BCM_LOG(
                    ERROR,
                    serializer_log_id,
                    "Dynamic binary string size %u not large enough (%u required)\n",
                    old_len,
                    arr_len);
                return BCM_ERR_NOMEM;
            }
        }

        _write_u32(data, type->x.binary_dyn.len_offset, arr_len);
        if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA) == 0)
        {
            if (!bcmolt_buf_read(buf, arr_data, arr_len))
            {
                return BCM_ERR_OVERFLOW;
            }
        }
        return BCM_ERR_OK;
    }

    case BCMOLT_BASE_TYPE_ID_BINARY_FIXED:
    {
        void *string_data = (uint8_t *)data + type->x.binary_fixed.data_offset;
        return BOOL_TO_ERR(bcmolt_buf_read(buf, string_data, type->x.binary_fixed.len));
    }

    case BCMOLT_BASE_TYPE_ID_STRUCT:
    {
        const bcmolt_field_descr *field;
        uint8_t *field_ptr;

        if (type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
        {
            uint16_t i;
            for (i = 0; i < type->x.s.num_fields; ++i)
            {
                field = &type->x.s.fields[i];
                field_ptr = (uint8_t *)data + field->offset;
                err = bcmolt_type_deserialize(field->type, flags, field_ptr, buf, extra_mem);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
            }
        }
        else
        {
            bcmolt_buf field_buf;
            uint16_t id;
            _clear_presence_mask(type, data);
            while (bcmolt_buf_get_remaining_size(buf) > 0)
            {
                err = _deserialize_tlv(buf, &id, &field_buf);
                if (err != BCM_ERR_OK)
                {
                    return err == BCM_ERR_NO_MORE ? BCM_ERR_OK : err;
                }

                field = _find_field_by_id(type->x.s.num_fields, type->x.s.fields, id);
                if (field == NULL)
                {
                    BCM_LOG(INFO, serializer_log_id, "Unknown field discarded, ID=%u\n", id);
                }
                else
                {
                    _set_presence_mask_bit(type, data, id);
                    field_ptr = (uint8_t *)data + field->offset;
                    err = bcmolt_type_deserialize(field->type, flags, field_ptr, &field_buf, extra_mem);
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                }
            }
        }
        return BCM_ERR_OK;
    }

    case BCMOLT_BASE_TYPE_ID_UNION:
    {
        uint16_t id;
        bcmolt_buf field_buf;
        const bcmolt_field_descr *field;
        uint8_t *field_ptr;

        BCMOS_TRACE_CHECK_RETURN(
            type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK,
            BCM_ERR_INTERNAL,
            "Error: unions with no presence mask are not supported.\n");

        _clear_presence_mask(type, data);
        while (bcmolt_buf_get_remaining_size(buf) > 0)
        {
            err = _deserialize_tlv(buf, &id, &field_buf);
            if (err != BCM_ERR_OK)
            {
                return err == BCM_ERR_NO_MORE ? BCM_ERR_OK : err;
            }

            field = _find_field_by_id(type->x.u.num_common_fields, type->x.u.common_fields, id);
            if (field == NULL)
            {
                BCM_LOG(INFO, serializer_log_id, "Unknown field discarded, ID=%u\n", id);
            }
            else
            {
                _set_presence_mask_bit(type, data, id);
                field_ptr = (uint8_t *)data + field->offset;
                err = bcmolt_type_deserialize(field->type, flags, field_ptr, &field_buf, extra_mem);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }

                /* If we just deserialized the classifier field, the classified data will follow */
                if (type->x.u.common_fields[type->x.u.classifier_idx].id == id)
                {
                    const bcmolt_field_descr *substruct = _find_classified_substruct(type, data);
                    if (substruct->type == NULL)
                    {
                        /* We don't know the type - just skip everything until we find the terminator TLV. */
                        do
                        {
                            err = _deserialize_tlv(buf, &id, &field_buf);
                        } while (err == BCM_ERR_OK);
                        if (err != BCM_ERR_NO_MORE)
                        {
                            return err; /* we expect NO_MORE, which is returned when we parse the terminator TLV. */
                        }
                    }
                    else
                    {
                        void *substruct_ptr = (uint8_t *)data + substruct->offset;
                        err = bcmolt_type_deserialize(substruct->type, flags, substruct_ptr, buf, extra_mem);
                        if (err != BCM_ERR_OK)
                        {
                            return err;
                        }
                    }
                }
            }
        }
        return BCM_ERR_OK;
    }

    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
    {
        const bcmolt_type_descr *elem_type;
        void *arr_data;
        uint64_t arr_len = 0;
        uint64_t overflow_elem_count = 0;
        uint16_t idx;

        if (type->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN)
        {
            elem_type = type->x.arr_dyn.elem_type;
            arr_data = _read_dyn_array_ptr(data, type->x.arr_dyn.data_offset);

            /* Unpack the array length (only for dynamically-sized arrays) */
            err = bcmolt_type_deserialize(
                type->x.arr_dyn.len_type,
                BCMOLT_SERIALIZER_FLAG_NONE,
                &arr_len,
                buf,
                extra_mem);
            if (err != BCM_ERR_OK)
            {
                return err;
            }
            arr_len = _read_unum(&arr_len, 0, type->x.arr_dyn.len_type->size);

            if ((flags & BCMOLT_SERIALIZER_FLAG_SKIP_DYN_ARRAY_DATA) != 0)
            {
                flags |= BCMOLT_SERIALIZER_FLAG_SKIP_DATA_ENTIRELY; /* skip the data part of the element TLVs */
            }
            else if (arr_len == 0)
            {
                /* Nothing else to do (no elements to deserialize) */
            }
            else if (arr_data == NULL)
            {
                uint32_t bytes_to_alloc;

                BCMOS_TRACE_CHECK_RETURN(
                    extra_mem == NULL,
                    BCM_ERR_NOMEM,
                    "Error: array field is NULL. You must allocate memory for this pointer before unpacking.\n");

                bytes_to_alloc = BCMOS_ROUND_TO_WORD((uint32_t)arr_len * elem_type->size);
                arr_data = bcmolt_buf_snap_get(extra_mem);
                if (!bcmolt_buf_skip(extra_mem, bytes_to_alloc))
                {
                    return BCM_ERR_NOMEM;
                }
                _write_dyn_array_ptr(data, type->x.arr_dyn.data_offset, arr_data);
            }
            else
            {
                uint64_t old_len = _read_unum(data, type->x.arr_dyn.len_offset, type->x.arr_dyn.len_type->size);
                if (arr_len > old_len)
                {
                    /* Deserialize as many elements as possible into the source array, skipping the rest. */
                    overflow_elem_count = arr_len - old_len;
                    arr_len = old_len;
                }
            }

            _write_unum(data, type->x.arr_dyn.len_offset, type->x.arr_dyn.len_type->size, arr_len);
        }
        else
        {
            elem_type = type->x.arr_fixed.elem_type;
            arr_len = type->x.arr_fixed.size;
            arr_data = (uint8_t *)data + type->x.arr_fixed.data_offset;
        }

        if (type->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
        {
            BCMOS_TRACE_CHECK_RETURN(
                overflow_elem_count > 0,
                BCM_ERR_NOMEM,
                "Error: partially unpacked arrays are not allowed for types without index masks.\n");

            for (idx = 0; idx < arr_len; idx++)
            {
                void *elem_ptr = (uint8_t *)arr_data + (idx * elem_type->size);
                err = bcmolt_type_deserialize(elem_type, flags, elem_ptr, buf, extra_mem);
                if (err != BCM_ERR_OK)
                {
                    return err;
                }
            }
        }
        else
        {
            bcmolt_buf elem_buf;
            _clear_presence_mask(type, data);
            while (bcmolt_buf_get_remaining_size(buf) > 0)
            {
                err = _deserialize_tlv(buf, &idx, &elem_buf);
                if (err != BCM_ERR_OK)
                {
                    return err == BCM_ERR_NO_MORE ? BCM_ERR_OK : err;
                }

                if (idx >= arr_len)
                {
                    if ((idx - arr_len) > overflow_elem_count)
                    {
                        BCM_LOG(WARNING, serializer_log_id, "Out-of-bounds array element discarded, idx=%u\n", idx);
                    }
                }
                else
                {
                    void *elem_ptr = (uint8_t *)arr_data + (idx * elem_type->size);
                    _set_presence_mask_bit(type, data, idx);
                    err = bcmolt_type_deserialize(elem_type, flags, elem_ptr, &elem_buf, extra_mem);
                    if (err != BCM_ERR_OK)
                    {
                        return err;
                    }
                }
            }
        }
        return BCM_ERR_OK;
    }

    default:
        return BCM_ERR_NOT_SUPPORTED;
    }
}

void bcmolt_serializer_init(void)
{
#ifdef ENABLE_LOG
    serializer_log_id = bcm_dev_log_id_register("serializer", DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
#endif
}
