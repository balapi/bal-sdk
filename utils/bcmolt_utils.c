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

#include "bcmolt_utils.h"

/* HexPrint a single line */
#define BYTES_IN_LINE 16

#define b2a(c)  (isprint(c)?c:'.')

static void _hexprint1(bcmos_msg_print_cb print_cb, void *context, uint16_t o, const uint8_t *p_data, uint16_t count, const char *indent)
{
    int i;

    if (indent)
        print_cb(context, "%s", indent);

    print_cb(context, "%04x: ", o);
    for (i=0; i<count; i++)
    {
        print_cb(context, "%02x", p_data[i]);
        if (!((i+1)%4))
            print_cb(context, " ");
    }
    for (; i<BYTES_IN_LINE; i++)
    {
        if (!((i+1)%4))
            print_cb(context, "   ");
        else
            print_cb(context, "  ");
    }
    for (i=0; i<count; i++)
        print_cb(context, "%c", b2a(p_data[i]));
    print_cb(context, "\n");
}

static void _default_print_cb(void *context, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    bcmos_vprintf(format, args);
    va_end(args);
}

void bcmos_hexdump(bcmos_msg_print_cb print_cb, void *context, const void *buffer, uint32_t offset, uint32_t count, const char *indent)
{
    const uint8_t *p_data = buffer;
    uint16_t n;

    if (print_cb == NULL)
        print_cb = _default_print_cb;

    while (count)
    {
        n = (count > BYTES_IN_LINE) ? BYTES_IN_LINE : count;
        _hexprint1(print_cb, context, offset, p_data, n, indent);
        count -= n;
        p_data += n;
        offset += n;
    }
}

void bcmos_hexdump_one_line(const char *funcname,
    uint32_t lineno,
    bcmos_msg_print_cb print_cb,
    void *context,
    char *out_buf,
    uint32_t max_buf_size,
    const void *buffer,
    uint32_t start_offset,
    uint32_t byte_count,
    const char *prefix,
    const char *suffix)
{
    const uint8_t *p_data = buffer;
    uint32_t data_offset = start_offset;
    size_t out_buf_offset = 0;
    uint32_t tmp_num_chars = 0;

    memset(out_buf, 0, max_buf_size);

    if (prefix)
    {
        tmp_num_chars = snprintf(out_buf + out_buf_offset, /* out_buf start offset */
            max_buf_size - out_buf_offset, /* remaining space in out_buf */
            "\n%40s:%-5u  %s", funcname, lineno, prefix);
    }
    else
    {
        tmp_num_chars = snprintf(out_buf + out_buf_offset, /* out_buf start offset */
            max_buf_size - out_buf_offset, /* remaining space in out_buf */
            "\n");
    }
    out_buf_offset += tmp_num_chars;

    while ((data_offset < (start_offset + byte_count)) && (out_buf_offset < max_buf_size))
    {
        tmp_num_chars = snprintf(out_buf + out_buf_offset, /* out_buf start offset */
            max_buf_size - out_buf_offset, /* remaining space in out_buf */
            "%02x ",
            p_data[data_offset++]); /* byte to dump */
        BUG_UNLESS(3 == tmp_num_chars);
        out_buf_offset += tmp_num_chars;
    }

    if (tmp_num_chars < max_buf_size)
    {
        if (suffix)
        {
            tmp_num_chars = snprintf(out_buf + out_buf_offset, /* out_buf start offset */
                max_buf_size - out_buf_offset, /* remaining space in out_buf */
                "%s", suffix);
        }
        else
        {
            tmp_num_chars = snprintf(out_buf + out_buf_offset, /* out_buf start offset */
                max_buf_size - out_buf_offset, /* remaining space in out_buf */
                "\n");
        }
        out_buf_offset += tmp_num_chars;
        BUG_UNLESS(out_buf_offset < max_buf_size);
    }

    print_cb(context, "%s", out_buf);
}

bcmos_errno bcmolt_read_snum(uint8_t byte_width, const void *data, int64_t *n)
{
    switch (byte_width)
    {
    case 1:
    {
        int8_t n1 = *(const int8_t *)data;
        *n = n1;
        break;
    }
    case 2:
    {
        int16_t n2 = *(const int16_t *)data;
        *n = n2;
        break;
    }
    case 4:
    {
        int32_t n4 = *(const int32_t *)data;
        *n = n4;
        break;
    }
    case 8:
    {
        memcpy(n, data, sizeof(*n));
        break;
    }
    default:
        return BCM_ERR_NOT_SUPPORTED;
    }
    return BCM_ERR_OK;
}
