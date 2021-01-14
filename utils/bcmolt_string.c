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

#include "bcmolt_string.h"
#include "bcmolt_math.h"

int bcmolt_string_copy(bcmolt_string *str, const char *buf, uint32_t size)
{
    int to_copy = MIN(size, str->remaining);
    memcpy(str->curr, buf, to_copy);
    str->remaining -= to_copy;
    str->curr += to_copy;
    str->curr[0] = '\0';
    return to_copy;
}

int bcmolt_string_append(bcmolt_string *str, const char *fmt, ...)
{
    int n;
    va_list args;

    va_start(args, fmt);
    n = vsnprintf(str->curr, str->remaining, fmt, args);
    va_end(args);
    if (n > 0)
    {
        if (n > str->remaining)
        {
            n = str->remaining;
        }
        str->remaining -= n;
        str->curr += n;
    }

    return n;
}

const char *bcmolt_string_get(bcmolt_string *str)
{
    return str->str;
}

void bcmolt_string_reset(bcmolt_string *str)
{
    str->str[0] = '\0';
    str->curr = str->str;
    str->remaining = str->max_len;
}

void bcmolt_string_rewind(bcmolt_string *str, int len)
{
    int used = str->curr - str->str;
    len = MIN(len, used);
    str->remaining += len;
    str->curr -= len;
    str->curr[0] = '\0';
}

void bcmolt_string_init(bcmolt_string *str, char *buf, uint32_t max_len)
{
    str->str = buf;
    str->max_len = max_len;
    bcmolt_string_reset(str);
}

char *bcmolt_string_indent(char *dst, uint32_t dst_size, uint32_t indent_level)
{
    uint32_t i;
    char *s = dst;

    for (i = 0; i < indent_level; i++)
    {
        int len;

        len = snprintf(s, dst_size, "%s", TAB2);
        if (len < 0)
            break;
        s += len;
        dst_size -= len;
    }

    return dst;
}

