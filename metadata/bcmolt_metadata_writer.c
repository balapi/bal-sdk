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
#include <bcmolt_string.h>
#include <bcmolt_utils.h>
#include "bcmolt_type_metadata.h"
#include "bcmolt_set_metadata.h"
#include "bcmolt_metadata_writer.h"

#define INDENT "  "
#define MAX_FIELDS_FOR_SINGLE_LINE 5
#define RETURN_IF_ERROR(rc) do { if (rc != BCM_ERR_OK) return rc; } while (0)
#define PRESENCE_MASK_FLAGS (BCMOLT_FIELD_FLAGS_PRESENCE_MASK | BCMOLT_FIELD_FLAGS_INDEX_MASK)
#define DB_PREFIX "%36s : "

void bcmolt_metadata_write(const bcmolt_metadata_writer *writer, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    writer->write_cb(writer->user_data, format, ap);
    va_end(ap);
}

static bcmos_errno read_unum(
    const bcmolt_metadata_writer *writer,
    uint8_t byte_width,
    const void *data,
    uint64_t *n)
{
    switch (byte_width)
    {
    case 1:
        {
            uint8_t n1 = *(const uint8_t *)data;
            *n = n1;
            break;
        }
    case 2:
        {
            uint16_t n2 = *(const uint16_t *)data;
            *n = n2;
            break;
        }
    case 4:
        {
            uint32_t n4 = *(const uint32_t *)data;
            *n = n4;
            break;
        }
    case 8:
        {
            memcpy(n, data, sizeof(*n));
            break;
        }
    default:
        bcmolt_metadata_write(writer, "\n*** number size %u is not supported\n", byte_width);
        return BCM_ERR_NOT_SUPPORTED;
    }
    return BCM_ERR_OK;
}

static bcmos_errno read_snum_writer(const bcmolt_metadata_writer *writer,
    uint8_t byte_width,
    const void *data,
    int64_t *n)
{
    if (BCM_ERR_NOT_SUPPORTED == bcmolt_read_snum(byte_width, data, n))
    {
        bcmolt_metadata_write(writer, "\n*** number size %u is not supported\n", byte_width);
        return BCM_ERR_NOT_SUPPORTED;
    }
    return BCM_ERR_OK;
}

static void strcat_upper(char *dest, uint32_t dest_len, const char *src, uint32_t src_len)
{
    uint32_t src_idx;
    uint32_t dest_idx;

    for (dest_idx = 0; dest_idx < dest_len - 1; ++dest_idx)
    {
        if (dest[dest_idx] == '\0')
        {
            break;
        }
    }

    for (src_idx = 0; src_idx < src_len && dest_idx < dest_len - 1; ++src_idx, ++dest_idx)
    {
        dest[dest_idx] = src[src_idx];
        if (dest[dest_idx] >= 'a' && dest[dest_idx] <= 'z')
        {
            dest[dest_idx] = 'A' + (dest[dest_idx] - 'a');
        }
    }

    dest[dest_idx] = '\0';
}

static const char *get_c_enum_id(const bcmolt_type_descr *td, const char *name)
{
    static char full_name_buf[256];
    full_name_buf[0] = '\0';
    strcat_upper(full_name_buf, sizeof(full_name_buf), "BCMOLT_", 7);
    strcat_upper(full_name_buf, sizeof(full_name_buf), td->name, strlen(td->name));
    strcat_upper(full_name_buf, sizeof(full_name_buf), "_", 1);
    strcat_upper(full_name_buf, sizeof(full_name_buf), name, strlen(name));
    return full_name_buf;
}

static bcmos_errno write_simple_value(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    uint32_t style)
{
    bcmos_errno rc = BCM_ERR_OK;

    if (style & BCMOLT_METADATA_WRITE_STYLE_MASK_ONLY)
    {
        bcmolt_metadata_write(writer, "yes");
        return rc;
    }

    switch (td->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_SNUM:       /* signed number */
        {
            int64_t n = 0;
            rc = read_snum_writer(writer, td->size, data, &n);
            bcmolt_metadata_write(writer, "%lld", (long long)n);
            break;
        }

    case BCMOLT_BASE_TYPE_ID_UNUM:       /* unsigned number */
        {
            uint64_t n = 0;
            rc = read_unum(writer, td->size, data, &n);
            bcmolt_metadata_write(writer, "%llu", (unsigned long long)n);
            break;
        }

    case BCMOLT_BASE_TYPE_ID_UNUM_HEX:   /* unsigned number printed in hex */
        {
            uint64_t n = 0;
            rc = read_unum(writer, td->size, data, &n);
            bcmolt_metadata_write(writer, "0x%llx", (unsigned long long)n);
            break;
        }

    case BCMOLT_BASE_TYPE_ID_FLOAT:      /* floating-point number */
        {
            if (td->size == sizeof(float))
            {
                bcmolt_metadata_write(writer, "%f", *(const float *)data);
            }
            else if (td->size == sizeof(double))
            {
                bcmolt_metadata_write(writer, "%e", *(const double *)data);
            }
            else
            {
                bcmolt_metadata_write(writer, "\n*** floating-point number of width %u is not supported\n", td->size);
                rc = BCM_ERR_NOT_SUPPORTED;
            }
            break;
        }

    case BCMOLT_BASE_TYPE_ID_BOOL:
        {
            const char *no_str = style & BCMOLT_METADATA_WRITE_STYLE_C_INIT ? "BCMOS_FALSE" : "no";
            const char *yes_str = style & BCMOLT_METADATA_WRITE_STYLE_C_INIT ? "BCMOS_TRUE" : "yes";
            uint64_t n = 0;
            rc = read_unum(writer, td->size, data, &n);
            bcmolt_metadata_write(writer, "%s", n == 0 ? no_str : yes_str);
            break;
        }

    case BCMOLT_BASE_TYPE_ID_STRING:     /* string */
        {
            if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
            {
                bcmolt_metadata_write(writer, "(bcmolt_%s){ .str = ", td->name);
            }
            if (td->size == 0)
            {
                bcmolt_metadata_write(writer, "\"%s\"", (const char *)data);
            }
            else
            {
                /* we know the size of the buffer */
                bcmolt_metadata_write(writer, "\"%.*s\"", td->size, (const char *)data);
            }
            if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
            {
                bcmolt_metadata_write(writer, " }");
            }
            break;
        }

    case BCMOLT_BASE_TYPE_ID_IPV4:       /* IPv4 address */
        {
            uint32_t ip;
            memcpy(&ip, data, sizeof(ip));
            bcmolt_metadata_write(
                writer,
                style & BCMOLT_METADATA_WRITE_STYLE_C_INIT ? "bcmos_ipv4_address_make(%d, %d, %d, %d)" : "%d.%d.%d.%d",
                (ip >> 24) & 0xff,
                (ip >> 16) & 0xff,
                (ip >> 8) & 0xff,
                ip & 0xff);
            break;
        }

    case BCMOLT_BASE_TYPE_ID_IPV6:       /* IPv6 address */
        {
            int i;
            bcmos_ipv6_address ip;
            memcpy(ip.u8, data, sizeof(ip.u8));

            if ((style & BCMOLT_METADATA_WRITE_STYLE_C_INIT) != 0)
            {
                bcmolt_metadata_write(writer, "((bcmos_ipv6_address){ .u8 = {");
                for (i = 0; i < sizeof(ip.u8); i++)
                {
                    if (i != 0)
                    {
                        bcmolt_metadata_write(writer, ",");
                    }
                    bcmolt_metadata_write(writer, "0x%02X", ip.u8[i]);
                }
                bcmolt_metadata_write(writer, " } })");
            }
            else
            {
                for (i = 0; i < sizeof(ip.u8); i += 2)
                {
                    if (i != 0)
                    {
                        bcmolt_metadata_write(writer, ":");
                    }
                    bcmolt_metadata_write(writer, "%02X%02X", ip.u8[i], ip.u8[i + 1]);
                }
            }
            break;
        }

    case BCMOLT_BASE_TYPE_ID_MAC:        /* MAC address */
        {
            bcmos_mac_address mac;
            memcpy(mac.u8, data, sizeof(mac.u8));
            bcmolt_metadata_write(
                writer,
                style & BCMOLT_METADATA_WRITE_STYLE_C_INIT ?
                "((bcmos_mac_address){ .u8 = { 0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x } })" :
                "%02x:%02x:%02x:%02x:%02x:%02x",
                mac.u8[0], mac.u8[1], mac.u8[2], mac.u8[3], mac.u8[4], mac.u8[5]);
            break;
        }

    case BCMOLT_BASE_TYPE_ID_ENUM:       /* enum */
        {
            uint64_t n = 0;
            const char *s;
            bcmos_errno err;
            rc = read_unum(writer, td->size, data, &n);
            BUG_ON(td->x.e.vals == NULL);
            err = bcmolt_enum_stringval_check(td->x.e.vals, (long)n, &s);
            if (BCM_ERR_OK == err)
            {
                if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
                {
                    s = get_c_enum_id(td, s);
                }
                bcmolt_metadata_write(writer, "%s", s);
            }
            else
            {
                /* If enum is not found, print the value */
                bcmolt_metadata_write(writer, "unknown: %u", n);
            }
            break;
        }

    case BCMOLT_BASE_TYPE_ID_ENUM_MASK:
        {
            uint64_t n = 0;
            const char *s;
            const char *none = NULL;
            const bcmolt_enum_val *value = td->x.e.vals;
            bcmos_bool first = BCMOS_TRUE;
            BUG_ON(value == NULL);
            rc = read_unum(writer, td->size, data, &n);
            while (value->name != NULL)
            {
                if (value->val == 0)
                {
                    none = value->name;
                }
                if ((value->val & n) != 0)
                {
                    s = value->name;
                    if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
                    {
                        s = get_c_enum_id(td, s);
                    }
                    bcmolt_metadata_write(
                        writer,
                        "%s%s",
                        first ? "" : (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT ? "|" : BCMOLT_ENUM_MASK_DEL_STR),
                        s);
                    first = BCMOS_FALSE;
                    n -= value->val;
                }
                ++value;
            }
            if (first)
            {
                bcmolt_metadata_write(writer, "%s", (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT) || (NULL == none) ? "0" : none);
            }
            break;
        }

    default:
        bcmolt_metadata_write(writer, "\n*** type %d is not supported\n", (int)td->base_type);
        rc = BCM_ERR_NOT_SUPPORTED;
        break;
    }
    return rc;
}

static bcmos_bool is_simple_type(const bcmolt_type_descr *td)
{
    switch (td->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_STRUCT:
    case BCMOLT_BASE_TYPE_ID_UNION:
    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
        return BCMOS_FALSE;
    default:
        return BCMOS_TRUE;
    }
}

static bcmos_bool is_nested_type(const bcmolt_type_descr *td)
{
    switch (td->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
        return !is_simple_type(td->x.arr_fixed.elem_type);
    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
        return !is_simple_type(td->x.arr_dyn.elem_type);
    default:
        return !is_simple_type(td);
    }
}

static bcmos_bool is_field_present(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *struct_descr,
    const void *struct_data,
    const bcmolt_field_descr *field)
{
    uint32_t field_tags = field->tags & ~writer->ignore_tags;
    if ((writer->filter_tags != 0) && (field_tags != 0))
    {
        if ((writer->filter_tags & field_tags) == 0)
        {
            return BCMOS_FALSE;
        }
    }

    uint64_t pm_value_num = 0;
    if (struct_descr->mask_offset == BCMOLT_TYPE_DESCR_NO_MASK)
    {
        return BCMOS_TRUE; /* no presence mask - all fields are present */
    }
    read_unum(writer, 8, (const uint8_t *)struct_data + struct_descr->mask_offset, &pm_value_num);
    return (pm_value_num == 0) || (((pm_value_num >> field->id) & 1) != 0); /* 0 means all fields are present */
}

static bcmos_bool struct_should_print_on_one_line(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data)
{
    uint16_t f;
    uint16_t num_fields_to_print = 0;
    for (f = 0; f < td->x.s.num_fields; f++)
    {
        if (is_nested_type(td->x.s.fields[f].type))
        {
            return BCMOS_FALSE; /* don't do any complex nesting on one line */
        }
        if (is_field_present(writer, td, data, &td->x.s.fields[f]))
        {
            num_fields_to_print++;
        }
    }
    return num_fields_to_print <= MAX_FIELDS_FOR_SINGLE_LINE;
}

static void write_indent(const bcmolt_metadata_writer *writer, uint16_t indent_level)
{
    while (indent_level > 0)
    {
        bcmolt_metadata_write(writer, INDENT);
        indent_level--;
    }
}

void bcmolt_metadata_write_indented(
    const bcmolt_metadata_writer *writer,
    uint16_t indent_level,
    const char *format,
    ...)
{
    write_indent(writer, indent_level);

    va_list ap;
    va_start(ap, format);
    writer->write_cb(writer->user_data, format, ap);
    va_end(ap);
}

/* Write all of the fields of a struct (without the outer "name={}"). */
static bcmos_errno write_struct_fields(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *parent,
    const bcmolt_field_descr *fields,
    uint16_t num_fields,
    const void *data,
    uint32_t style,
    uint16_t indent_level)
{
    bcmos_errno rc;
    uint16_t f;
    uint16_t field_indent_level = style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED ? indent_level + 1 : 0;
    bcmos_bool first_field = BCMOS_TRUE;

    for (f = 0; f < num_fields; f++)
    {
        const bcmolt_field_descr *fld = &fields[f];
        char field_prefix[BCMOLT_MAX_METADATA_NAME_LENGTH] = {};
        void *fdata = (void *)((long)data + fld->offset);

        if (!is_field_present(writer, parent, data, fld))
        {
            continue; /* not in the presence mask */
        }

        if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
        {
            if (!first_field)
            {
                bcmolt_strncat(field_prefix, ", ", sizeof(field_prefix));
            }
            bcmolt_strncat(field_prefix, ".", sizeof(field_prefix));
            bcmolt_strncat(field_prefix, fld->name, sizeof(field_prefix));
            bcmolt_strncat(field_prefix, "=", sizeof(field_prefix));
        }
        else
        {
            if (!first_field)
            {
                bcmolt_strncpy(
                    field_prefix,
                    style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED ? "\n" : " ",
                    sizeof(field_prefix));
            }
        }

        first_field = BCMOS_FALSE;
        rc = bcmolt_metadata_write_elem(
            writer,
            fld->type,
            fdata,
            fld->name,
            style,
            field_indent_level,
            field_prefix,
            "");
        RETURN_IF_ERROR(rc);
    }

    return BCM_ERR_OK;
}

/* Write a single field/property of an array type (fixed or dynamic). */
static bcmos_errno write_array(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    uint32_t size,
    uint64_t index_mask,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    bcmos_errno rc;
    uint32_t i;
    bcmos_bool first = BCMOS_TRUE;

    if (is_simple_type(td))
    {
        bcmolt_metadata_write(writer, prefix);
        if (!(style & BCMOLT_METADATA_WRITE_STYLE_DB))
        {
            write_indent(writer, indent_level);
            if (!(style & BCMOLT_METADATA_WRITE_STYLE_C_INIT))
            {
                bcmolt_metadata_write(writer, "%s=", name);
            }
        }
        else
        {
            bcmolt_metadata_write(writer, DB_PREFIX, name);
            write_indent(writer, indent_level);
        }

        for (i = 0; i < size; ++i)
        {
            void *fdata = (void *)((long)data + (td->size * i));
            if (!first)
            {
                bcmolt_metadata_write(writer, ",");
            }
            first = BCMOS_FALSE;
            if (index_mask != 0 && (index_mask & (1ULL << i)) == 0)
            {
                bcmolt_metadata_write(writer, BCMOLT_PARM_NO_VALUE_STR);
                continue; /* the list element isn't present */
            }
            rc = write_simple_value(writer, td, fdata, style);
            RETURN_IF_ERROR(rc);
        }
        bcmolt_metadata_write(writer, suffix);
        return BCM_ERR_OK;
    }
    else if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
    {
        bcmolt_metadata_write(writer, "%s{", prefix);
        for (i = 0; i < size; ++i)
        {
            char idx_prefix[BCMOLT_MAX_METADATA_NAME_LENGTH] = {};
            void *fdata = (void *)((long)data + (td->size * i));

            if (index_mask != 0 && (index_mask & (1ULL << i)) == 0)
            {
                continue; /* the list element isn't present */
            }

            snprintf(idx_prefix, sizeof(idx_prefix), "%s[%u]=", first ? "" : ", ", i);
            first = BCMOS_FALSE;
            rc = bcmolt_metadata_write_elem(writer, td, fdata, "", style, indent_level, idx_prefix, "");
            RETURN_IF_ERROR(rc);
        }
        bcmolt_metadata_write(writer, "}%s", suffix);
        return BCM_ERR_OK;
    }
    else
    {
        if (style & BCMOLT_METADATA_WRITE_STYLE_DB)
        {
            bcmolt_metadata_write(writer, "%s", prefix);
            bcmolt_metadata_write(writer, DB_PREFIX, name);
            write_indent(writer, indent_level);
            bcmolt_metadata_write(writer, "{");
            indent_level++;
        }

        for (i = 0; i < size; ++i)
        {
            char elem_name[BCMOLT_MAX_METADATA_NAME_LENGTH] = {};
            char elem_prefix[BCMOLT_MAX_METADATA_NAME_LENGTH] = {};
            void *fdata = (void *)((long)data + (td->size * i));

            if (index_mask != 0 && (index_mask & (1ULL << i)) == 0)
            {
                continue; /* the list element isn't present */
            }

            bcmolt_strncpy(elem_prefix, prefix, sizeof(elem_prefix));
            if (!first)
            {
                bcmolt_strncpy(
                    elem_prefix,
                    style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED ? "\n" : " ",
                    sizeof(elem_prefix));
            }

            first = BCMOS_FALSE;
            snprintf(elem_name, sizeof(elem_name), "%s[%u]", name, i);
            rc = bcmolt_metadata_write_elem(writer, td, fdata, elem_name, style, indent_level, elem_prefix, suffix);
            RETURN_IF_ERROR(rc);
        }

        if (style & BCMOLT_METADATA_WRITE_STYLE_DB)
        {
            bcmolt_metadata_write(writer, " }");
        }

        return BCM_ERR_OK;
    }
}

/* Write a single field/property of binary string type (fixed or dynamic). */
static bcmos_errno write_binary(
    const bcmolt_metadata_writer *writer,
    uint32_t size,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    uint32_t i;

    if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
    {
        /* In C, binary strings need to be formatted as arrays. */
        bcmolt_type_descr byte = { .base_type = BCMOLT_BASE_TYPE_ID_UNUM_HEX, .size = 1 };
        return write_array(writer, &byte, size, 0, data, name, style, indent_level, prefix, suffix);
    }

    bcmolt_metadata_write(writer, prefix);
    write_indent(writer, indent_level);
    bcmolt_metadata_write(writer, "%s=", name);
    for (i = 0; i < size; ++i)
    {
        bcmolt_metadata_write(writer, "%02x", ((const uint8_t *)data)[i]);
    }
    bcmolt_metadata_write(writer, suffix);
    return BCM_ERR_OK;
}

/* Write a single field/property of a 'simple' (non-structured) type. */
static bcmos_errno write_simple_elem(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    bcmos_errno rc;
    bcmolt_metadata_write(writer, prefix);
    if (!(style & BCMOLT_METADATA_WRITE_STYLE_DB))
    {
        write_indent(writer, indent_level);
        if (!(style & BCMOLT_METADATA_WRITE_STYLE_C_INIT))
        {
            bcmolt_metadata_write(writer, "%s=", name);
        }
    }
    else
    {
        bcmolt_metadata_write(writer, DB_PREFIX, name);
        write_indent(writer, indent_level);
    }
    rc = write_simple_value(writer, td, data, style);
    RETURN_IF_ERROR(rc);
    bcmolt_metadata_write(writer, suffix);
    return BCM_ERR_OK;
}

/* Write a single field/property of a fixed-size array type. */
static bcmos_errno write_fixed_array_elem(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    const void *arr_data = (const uint8_t *)data + td->x.arr_fixed.data_offset;
    const bcmolt_type_descr *elem = td->x.arr_fixed.elem_type;
    uint32_t size = td->x.arr_fixed.size;
    uint64_t index_mask = 0;

    if (td->mask_offset != BCMOLT_TYPE_DESCR_NO_MASK)
    {
        read_unum(writer, 8, (const uint8_t *)data + td->mask_offset, &index_mask);
    }

    return write_array(writer, elem, size, index_mask, arr_data, name, style, indent_level, prefix, suffix);
}

/* Write a single field/property of a dynamically-sized array type. */
static bcmos_errno write_dyn_array_elem(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    const void *arr_data;
    uint64_t array_size;
    uint64_t index_mask = 0;
    bcmos_errno err;

    if (td->x.arr_dyn.is_array_backend)
    {
        arr_data = (const uint8_t *)data + td->x.arr_dyn.data_offset;
    }
    else
    {
        const void *arr_data_ptr = (const uint8_t *)data + td->x.arr_dyn.data_offset;
        arr_data = *(void * const *)arr_data_ptr;
    }

    if (td->mask_offset != BCMOLT_TYPE_DESCR_NO_MASK)
    {
        read_unum(writer, 8, (const uint8_t *)data + td->mask_offset, &index_mask);
    }
    err = read_unum(writer, td->x.arr_dyn.len_type->size, data, &array_size);
    if (err != BCM_ERR_OK)
        return err;

    if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
    {
        bcmolt_metadata_write(writer, "%s{%u, %s}%s", prefix, array_size, name, suffix);
        return BCM_ERR_OK;
    }
    else
    {
        const bcmolt_type_descr *elem = td->x.arr_dyn.elem_type;
        data = (const uint8_t *)data + td->x.arr_dyn.data_offset;
        return write_array(writer, elem, array_size, index_mask, arr_data, name, style, indent_level, prefix, suffix);
    }
}

/* Write a single field/property of a fixed-size binary string type (byte buffer). */
static bcmos_errno write_fixed_binary_elem(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    uint32_t size = td->x.binary_fixed.len;
    if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
    {
        bcmolt_metadata_write(writer, "((bcmolt_%s){ .arr = {", td->name);
    }
    bcmos_errno rc = write_binary(writer, size, data, name, style, indent_level, prefix, suffix);
    if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
    {
        bcmolt_metadata_write(writer, " } })");
    }
    return rc;
}

/* Write a single field/property of a dynamically-sized binary string type (byte buffer). */
static bcmos_errno write_dyn_binary_elem(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    uint32_t size = *(const uint32_t *)data;
    const void *arr_data_ptr = (const uint8_t *)data + td->x.binary_dyn.data_offset;
    const void *arr_data = *(void * const *)arr_data_ptr;
    if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
    {
        bcmolt_metadata_write(writer, "((bcmolt_%s){ .len = %u, .arr = (uint8_t[]){", td->name, size);
    }
    bcmos_errno rc = write_binary(writer, size, arr_data, name, style, indent_level, prefix, suffix);
    if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
    {
        bcmolt_metadata_write(writer, " } })");
    }
    return rc;
}

/* Write a single field/property of a struct type. */
static bcmos_errno write_struct_elem(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    bcmos_errno rc;

    if (td->x.s.num_fields == 0)
    {
        return BCM_ERR_OK; /* nothing to do */
    }
    BUG_ON(td->x.s.fields == NULL);

    /* Write the struct on one line if it's simple and small. */
    if (style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED && !(style & BCMOLT_METADATA_WRITE_STYLE_DB) && struct_should_print_on_one_line(writer, td, data))
    {
        style &= ~BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED;
        style |= BCMOLT_METADATA_WRITE_STYLE_SPACE_SEPARATED;
    }

    bcmolt_metadata_write(writer, prefix);
    if (!(style & BCMOLT_METADATA_WRITE_STYLE_DB))
    {
        write_indent(writer, indent_level);
        if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
        {
            bcmolt_metadata_write(writer, "{");
        }
        else if (name != NULL)
        {
            bcmolt_metadata_write(writer, "%s={", name);
            if (style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED)
            {
                bcmolt_metadata_write(writer, "\n");
            }
        }
    }
    else
    {
        bcmolt_metadata_write(writer, DB_PREFIX, name ? name : "");
        write_indent(writer, indent_level);
        bcmolt_metadata_write(writer, "{\n");
    }

    rc = write_struct_fields(writer, td, td->x.s.fields, td->x.s.num_fields, data, style, indent_level);
    RETURN_IF_ERROR(rc);

    if (style & BCMOLT_METADATA_WRITE_STYLE_DB)
    {
        bcmolt_metadata_write(writer, " ");
    }
    else if (style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED)
    {
        bcmolt_metadata_write(writer, "\n");
        write_indent(writer, indent_level);
    }

    if (name != NULL)
    {
        bcmolt_metadata_write(writer, "}");
    }

    bcmolt_metadata_write(writer, "%s", suffix);

    return BCM_ERR_OK;
}

/* Write a single field/property of a union type. */
static bcmos_errno write_union_elem(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    bcmos_errno rc;
    const bcmolt_field_descr *fld;
    int num_union_vals;
    int64_t selector_val = 0;

    if (td->x.u.num_common_fields == 0 || td->x.u.common_fields == NULL)
    {
        bcmolt_metadata_write(writer, "\n*** union types with no common fields not supported\n");
        return BCM_ERR_INTERNAL;
    }

    bcmolt_metadata_write(writer, prefix);
    if (!(style & BCMOLT_METADATA_WRITE_STYLE_DB))
    {
        write_indent(writer, indent_level);
        if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
        {
            bcmolt_metadata_write(writer, "{");
        }
        else
        {
            if (name != NULL)
            {
                bcmolt_metadata_write(writer, "%s={", name);
                if ((style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED)
                    && !(style & BCMOLT_METADATA_WRITE_STYLE_MASK_ONLY))
                {
                    bcmolt_metadata_write(writer, "\n");
                }
            }
        }
    }
    else
    {
        bcmolt_metadata_write(writer, DB_PREFIX, name ? name : "");
        write_indent(writer, indent_level);
        bcmolt_metadata_write(writer, "{\n");
    }

    /* skip unions completely in mask only mode as we don't have the classifer value */
    if (!(style & BCMOLT_METADATA_WRITE_STYLE_MASK_ONLY))
    {
        /* Write the common fields just like any other struct. */
        rc = write_struct_fields(writer, td, td->x.u.common_fields, td->x.u.num_common_fields, data, style, indent_level);
        RETURN_IF_ERROR(rc);

        /* Find the classifier field and record some information about it. If the classifier isn't present, we're done. */
        fld = &td->x.u.common_fields[td->x.u.classifier_idx];
        if (is_field_present(writer, td, data, fld))
        {
            rc = read_snum_writer(writer, fld->type->size, (void *)((long)data + fld->offset), &selector_val);
            RETURN_IF_ERROR(rc);

            num_union_vals = bcmolt_get_num_enum_vals(fld->type->x.e.vals);
            if ((unsigned)selector_val >= num_union_vals)
            {
                bcmolt_metadata_write(writer, "\n*** invalid union selector value %lld\n", (long long)selector_val);
                return BCM_ERR_INTERNAL;
            }

            /* Now write the "selected" field. */
            fld = &td->x.u.union_fields[selector_val];
            if (fld->type != NULL)
            {
                void *fdata;
                BUG_ON(fld->type->base_type != BCMOLT_BASE_TYPE_ID_STRUCT);

                if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
                {
                    bcmolt_metadata_write(writer, ", .u={.%s={", fld->name);
                }
                else
                {
                    bcmolt_metadata_write(writer, style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED ? "\n" : " ");
                }

                fdata = (void *)((long)data + fld->offset);
                rc = write_struct_fields(
                    writer, fld->type, fld->type->x.s.fields, fld->type->x.s.num_fields, fdata, style, indent_level);
                RETURN_IF_ERROR(rc);

                if (style & BCMOLT_METADATA_WRITE_STYLE_C_INIT)
                {
                    bcmolt_metadata_write(writer, "}}");
                }
            }
        }
    }

    if (style & BCMOLT_METADATA_WRITE_STYLE_DB)
    {
        bcmolt_metadata_write(writer, " ");
    }
    else if ((style & BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED)
        && !(style & BCMOLT_METADATA_WRITE_STYLE_MASK_ONLY))
    {
        bcmolt_metadata_write(writer, "\n");
        write_indent(writer, indent_level);
    }

    if (name != NULL)
    {
        bcmolt_metadata_write(writer, "}");
    }

    bcmolt_metadata_write(writer, "%s", suffix);

    return BCM_ERR_OK;
}

bcmos_errno bcmolt_metadata_write_elem(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix)
{
    switch (td->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_STRUCT:
        return write_struct_elem(writer, td, data, name, style, indent_level, prefix, suffix);
    case BCMOLT_BASE_TYPE_ID_UNION:
        return write_union_elem(writer, td, data, name, style, indent_level, prefix, suffix);
    case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
        return write_fixed_array_elem(writer, td, data, name, style, indent_level, prefix, suffix);
    case BCMOLT_BASE_TYPE_ID_ARR_DYN:
        return write_dyn_array_elem(writer, td, data, name, style, indent_level, prefix, suffix);
    case BCMOLT_BASE_TYPE_ID_BINARY_FIXED:
        return write_fixed_binary_elem(writer, td, data, name, style, indent_level, prefix, suffix);
    case BCMOLT_BASE_TYPE_ID_BINARY_DYN:
        return write_dyn_binary_elem(writer, td, data, name, style, indent_level, prefix, suffix);
    default:
        return write_simple_elem(writer, td, data, name, style, indent_level, prefix, suffix);
    }
}
