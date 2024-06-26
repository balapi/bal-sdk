/*
<:copyright-BRCM:2016-2024:Apache:standard
 
 Copyright (c) 2016-2024 Broadcom. All Rights Reserved
 
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
 
 *  :>
*/

#include "bcmos_system.h"
#include "math.h"
#include "bcmolt_bit_utils.h"

bcmos_bool bcmolt_bv_new(bit_vector *bv, const uint32_t nbits)
{
    uint32_t nwords = BCMOS_DIVIDE_ROUND_UP(nbits, (BITS_SZ));

    bv->nbits = nbits;
    bv->vector = (bv_bits *)bcmos_calloc(nwords * sizeof(bv_bits));
    return bv->vector != NULL;
}

bcmos_bool bcmolt_bv_get(const bit_vector *bv, const uint32_t offset)
{
    bcmos_bool rv = BCMOS_FALSE;

    if (offset <= bv->nbits)
    {
        rv = test_bits_set(bv->vector[(offset / BITS_SZ)],
            (1 << (offset % BITS_SZ)));
    }
    else
    {
        BCMOS_TRACE_ERR("out of range %u\n", offset);
    }
    return rv;
}

void bcmolt_bv_assign(bit_vector *bv,
    const uint32_t offset,
    const bcmos_bool value)
{
    if (offset <= bv->nbits)
    {
        if (value)
        {
            bv->vector[offset / BITS_SZ] |= (1 << (offset % BITS_SZ));
        }
        else
        {
            bv->vector[offset / BITS_SZ] &= ~(1 << (offset % BITS_SZ));
        }
    }
    else
    {
        BCMOS_TRACE_ERR("out of range %u\n", offset);
    }
}

void bcmolt_bv_toggle(bit_vector *bv, const uint32_t offset)
{
    if (offset <= bv->nbits)
    {
        bv->vector[offset / BITS_SZ] ^= (1 << (offset % BITS_SZ));
    }
    else
    {
        BCMOS_TRACE_ERR("out of range %u\n", offset);
    }
}

void bcmolt_bv_copy(bit_vector *dst,
    const bit_vector *src,
    const uint32_t nbits)
{
    uint32_t i;
    uint32_t nwords = nbits / BITS_SZ;
    bv_bits bit_remainder = nbits % BITS_SZ;

    if ((nbits <= dst->nbits) && (nbits <= src->nbits))
    {
        for (i = 0; i < nwords; i++)
        {
            dst->vector[i] = src->vector[i];
        }

        if (0 != bit_remainder)
        {
            dst->vector[nwords] = (dst->vector[nwords] & ~((2 ^ bit_remainder) - 1)) |
                (src->vector[nwords] & ((2 ^ bit_remainder) - 1));
        }
    }
    else
    {
        BCMOS_TRACE_ERR("out of range %u\n", nbits);
    }
}

void bcmolt_bit_string(const bv_bits value, const uint32_t bitcnt, char *outstr)
{
    uint32_t offset;

    if (bitcnt <= BITS_SZ)
    {
        for (offset = 0; offset < bitcnt; offset++)
        {
            *outstr++ = ((value >> offset) & 1) + '0';
            if ((((offset + 1) % 4) == 0))
            {
                *outstr++ = ' ';
            }
        }
    }

    *outstr = '\0';
}

void bcmolt_bv_dump(const bit_vector *bv)
{
    uint32_t idx; /* word idx */
    char outstr[BITS_SZ + 8 + 1]; /* 8 spaces + null */

    for (idx = 0; idx < (bv->nbits / BITS_SZ); idx++)
    {
        bcmolt_bit_string(bv->vector[idx], BITS_SZ, outstr);
        bcmos_printf("%s\n", outstr);
    }

    if (0 != (bv->nbits % BITS_SZ))
    {
        bcmolt_bit_string(bv->vector[idx], (bv->nbits % BITS_SZ), outstr);
        bcmos_printf("%s\n", outstr);
    }
}

uint32_t bcmolt_bit_count(uint32_t num)
{
    num = ((num & 0xAAAAAAAAL) >> 1) + (num & 0x55555555L);
    num = ((num & 0xCCCCCCCCL) >> 2) + (num & 0x33333333L);
    num = ((num & 0xF0F0F0F0L) >> 4) + (num & 0x0F0F0F0FL);
    num = ((num & 0xFF00FF00L) >> 8) + (num & 0x00FF00FFL);
    num = ((num & 0xFFFF0000L) >> 16) + (num & 0x0000FFFFL);
    return num;
}

uint32_t bcmolt_bv_bit_count(const bit_vector *bv)
{
    uint32_t nwords = BCMOS_DIVIDE_ROUND_UP(bv->nbits, (BITS_SZ));
    uint32_t cnt = 0;

    while (0 != nwords--)
    {
        cnt += bcmolt_bit_count(bv->vector[nwords]);
    }

    return cnt;
}

void bcmos_bit_range_set(uint32_t *dst, uint32_t dst_bytes, uint16_t dst_bit_pos,
    uint32_t *src, uint16_t n_bits)
{
    uint16_t bp = dst_bit_pos;
    uint16_t len;
    uint32_t wp;
    uint32_t mask;
    uint32_t src_idx;
    uint32_t dst_idx;

    wp = bp / 32;
    bp = bp & (32 - 1);
    src_idx = 0;

    for (len = n_bits; len > 0; len -= 32)
    {
        if (bp != 0)
        {
            mask = (len < 32) ? (1 << len) - 1 : 0xFFFFFFFF;
            dst_idx = wp;
            dst[dst_idx] &= ~(mask << bp);
            dst[dst_idx] |= src[src_idx] << bp;
            wp++;
            if (len > (32 - bp))
            {
                dst_idx = wp;
                dst[dst_idx] &= ~(mask >> (32 - bp));
                dst[dst_idx] |= src[src_idx] >> (32 - bp) & ((1 << bp) - 1);
            }
        }
        else
        {
            dst_idx = wp;
            if (len < 32)
            {
                mask = (1 << len) - 1;
                dst[dst_idx] &= ~mask;
                dst[dst_idx] |= src[src_idx] << bp;
            }
            else
            {
                dst[dst_idx] = src[src_idx];
            }
            wp++;
        }
        src_idx++;
    }
}

void bcmos_bit_range_get(const uint32_t *src, uint32_t src_bytes,
    uint16_t src_bit_pos, uint32_t *dst, uint16_t n_bits)
{
    uint16_t bp = src_bit_pos; /* for readability */
    uint16_t len = n_bits;
    uint32_t wp;
    uint32_t src_idx;
    uint32_t dst_idx;

    if (n_bits == 1)
    {
        wp = bp / 32;
        bp = bp & (32 - 1);
        src_idx = BCMOS_DIVIDE_ROUND_UP(src_bytes, 4) - 1 - wp;
        dst[0] = ((src[src_idx] & (1 << bp)) != 0) ? 1 : 0;
        return;
    }

    wp = bp / 32;
    bp = bp & (32 - 1);
    dst_idx = 0;

    for (; len > 0; len -= 32)
    {
        if (bp != 0)
        {
            src_idx = BCMOS_DIVIDE_ROUND_UP(src_bytes, 4) - 1 - wp;
            dst[dst_idx] = src[src_idx] >> bp & ((1 << (32 - bp)) - 1);
            wp++;
            if (len > (32 - bp))
            {
                src_idx = BCMOS_DIVIDE_ROUND_UP(src_bytes, 4) - 1 - wp;
                dst[dst_idx] |= src[src_idx] << (32 - bp);
            }
        }
        else
        {
            src_idx = BCMOS_DIVIDE_ROUND_UP(src_bytes, 4) - 1 - wp;
            dst[dst_idx] = src[src_idx];
            wp++;
        }

        if (len < 32)
        {
            dst[dst_idx] &= ((1 << len) - 1);
        }
        dst_idx++;
    }
}
