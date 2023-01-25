/*
<:copyright-BRCM:2016-2020:proprietary:standard

 Copyright (c) 2016-2020 Broadcom. All Rights Reserved

 This program is the proprietary software of Broadcom and/or its
 licensors, and may only be used, duplicated, modified or distributed pursuant
 to the terms and conditions of a separate, written license agreement executed
 between you and Broadcom (an "Authorized License").  Except as set forth in
 an Authorized License, Broadcom grants no license (express or implied), right
 to use, or waiver of any kind with respect to the Software, and Broadcom
 expressly reserves all rights in and to the Software and all intellectual
 property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE
 NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY
 BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.

 Except as expressly set forth in the Authorized License,

 1. This program, including its structure, sequence and organization,
    constitutes the valuable trade secrets of Broadcom, and you shall use
    all reasonable efforts to protect the confidentiality thereof, and to
    use this information only in connection with your use of Broadcom
    integrated circuit products.

 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
    RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND
    ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT,
    FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
    COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE
    TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR
    PERFORMANCE OF THE SOFTWARE.

 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR
    ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
    INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY
    WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
    IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES;
    OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE
    SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS
    SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY
    LIMITED REMEDY.
:>
 */

/**
 * bcmolt_bit_utils.h
 *  Created on: 03/10/2014
 *      Author: cpark1
 *
 * This bit vector implementation is used for the EPON encryption.
 * There is a certain hardware restriction that the global encryption mode
 * can not be changed when a link encryption is configured for a different
 * encryption mode.
 * Likewise, the link encryption mode can not be changed if the global
 * encryption mode is set to other mode.
 * Therefore, when the host tries to change any of them, the OLT needs to
 * check either the global encryption mode or the link encryption mode
 * before applying the change.
 * In the old implementation (like Pioneer), the firmware iterates through
 * every link records of each PON port and check the encryption mode of each.
 * This is very inefficient and time consuming.
 * The host may want to know how many links are enabled for the encryption,
 * or which link is enabled, etc.
 * I thought that a bit vector implementation is best satisfies.
 * Also, this implementation exactly reflects the IC implementation, so we
 * can use it to mirror the hardware status.
 *
 */

#ifndef BCMOLT_BIT_UTILS_H
#define BCMOLT_BIT_UTILS_H

#include "bcmos_system.h"

/* the current (draft) design of the ASIC uses 32-bit bitmap data port */
typedef uint32_t bv_bits;

typedef struct
{
    uint32_t nbits;
    bv_bits *vector;
} bit_vector;

#define _BITS_SZ(type) (sizeof(type) * CHAR_BIT)

#define BITS_SZ _BITS_SZ(bv_bits)

#define BITS_SET(val, mask) (((val) & (mask)) == (mask))

#define BCM_BIT_IS_SET(x, n) (((x) >> (n)) & 1U)
#define BCM_CLR_BIT(x, n) ((x) &= (~(1UL << (n))))
#define BCM_SET_BIT(x, n) ((x) |= (1UL << (n)))

/* Generate an 8-bit mask of 1's up to the MSB of the provided value */
#define MASK8(v) ((((v) - 1) >> 1) | (((v) - 1) >> 2) | (((v) - 1) >> 4))
/* Generate a 16-bit mask of 1's up to the MSB of the provided value */
#define MASK16(v) (MASK8(v) | (((v) - 1) >> 8))
/* Generate a 32-bit mask of 1's up to the MSB of the provided value */
#define MASK32(v) (MASK16(v) | (((v) - 1) >> 16))

/** Test if all given bits are set in the given data word
 * \param[in]   word    Given data word to test
 * \param[in]   mask    Test mask
 * \return      TRUE if all the bits in the bitMask are set
 */
static inline bcmos_bool test_bits_set(uint32_t word, uint32_t mask)
{
    return (word & mask) == mask;
}

/** Test if all given bits are clear in the given data word
 * \param       word    Given word to test
 * \param       mask Test mask
 * \return      TRUE if all the bits given by bitMask are clear
 */
static inline bcmos_bool test_bits_clear(uint32_t word, uint32_t mask)
{
    return (word & mask) == 0;
}

/** Test whether any of the given bits are set in a value
 * \param[in]   val     The value to test
 * \param[in]   bits    The bits to test for
 * \return      TRUE if any of the bits are set in the value, FALSE otherwise
 */
static inline bcmos_bool test_bits_any(uint32_t val, uint32_t bits)
{
    return (val & bits) != 0;
}

/** return true if only one bit is set for a given integer.
 */
static inline bcmos_bool is_one_bit_set(uint32_t number)
{
    return (number & (number - 1)) == 0;
}

/** dynamically allocate space for an array of `nbits' bits and initalize
 *  the bits to all be zero.
 *
 * \param[out]  bv      pointer to a bit_vector struct.
 * \param[in]   nbits   number of bits to allocate.
 * \return      FALSE if space was not available, otherwise TRUE.
 */
bcmos_bool bcmolt_bv_new(bit_vector *bv, const uint32_t nbits);

/** return the value of the `offset'th bit element of the bit vector.
 *
 * \param[in]   bv      pointer to a bit_vector struct.
 * \param[in]   offset  offset of bit to test.
 * \return      FALSE if the bit offset is out of range, otherwise TRUE.
 */
bcmos_bool bcmolt_bv_get(const bit_vector *bv, const uint32_t offset);

/** set or clear the bit in position `offset' of the bit vector.
 *  bv->vector[bit_pos] is to be set (assigned to 1) if value is TRUE,
 *  otherwise it is to be cleared (assigned to 0).
 *
 * \param[in]   bv      pointer to a bit_vector struct.
 * \param[in]   offset  offset of bit to set or clear.
 * \param[in]   value   boolean value. TRUE for set, FALSE for clear.
 * \return      FALSE if the bit offset is out of range, otherwise TRUE.
 */
void bcmolt_bv_assign(bit_vector *bv, const uint32_t offset, const bcmos_bool value);

/** set or clear 'nbits' bits of given bit vector.
 *
 * \param[in]   bv      pointer to a bit_vector struct.
 * \param[in]   nbits   number of bits to set or clear.
 * \param[in]   value   boolean value. TRUE for set, FALSE for clear.
 * \return      FALSE if the bit offset is out of range, otherwise TRUE.
 */
void bv_assign_nbits(bit_vector *bv, const uint32_t nbits,
    const bcmos_bool value);

/** toggle the bit in position `offset' of the bit vector.
 *  i.e. if it was 1 it is 0; if it was 0 it is 1.
 *
 * \param[in]   bv      pointer to a bit_vector struct.
 * \param[in]   offset  offset of bit to toggle.
 * \return      FALSE if the bit offset is out of range, otherwise TRUE.
 */
void bcmolt_bv_toggle(bit_vector *bv, const uint32_t offset);

/** copy bit vector from 'src' to 'dst'.
 *
 * \param[out]  dst     pointer to a bit_vector struct to copy to.
 * \param[in]   src     pointer to a bit_vector struct to copy from.
 * \param[in]   nbits   number of bits to copy.
 * \return      none.
 */
void bcmolt_bv_copy(bit_vector *dst, const bit_vector *src, const uint32_t nbits);

/** Print bit pattern of word FORMATTED to string.
 *
 * \param[in]   value   value to transform to bit string.
 * \param[in]   bitcnt  count of bits to be shown.
 * \param[out]  outstr  pointer to a output buffer to store the string.
 * \return      none
 * \warning     this fn doesn't check the size of 'outstr'.
 *              the caller should ensure 'outstr' has enough room for the
 *              bit string, space characters and null terminator.
 */
void bcmolt_bit_string(const bv_bits value, const uint32_t bitcnt, char *outstr);

/** Print all bits in the bit vector.
 *
 * \param[in]   bv      pointer to a bit_vector struct.
 * \return      none.
 */
void bcmolt_bv_dump(const bit_vector *bv);

/** Count the number of bits set in a long integer.
 *
 * \param[in]   num     integer value.
 * \return      number of bits set.
 */
uint32_t bcmolt_bit_count(uint32_t num);

/** Count the number of bits set in the whole bit vector.
 *
 * \param[in]   bv      pointer to the bit vector struct.
 * \return      number of bits set.
 */
uint32_t bcmolt_bv_bit_count(const bit_vector *bv);

/** Copy bit range from a 32-bit word array to an arbitrary bit position of
 *  the destination 32-bit word array.
 *
 * \param[in]   dst             destination buffer (big endian)
 * \param[in]   dst_bytes       destination buffer size in bytes
 * \param[in]   dst_bit_pos     least bit position to dest
 * \param[in]   src             source buffer (little endian)
 * \param[in]   src_bits        many bits to copy from source
 */
void bcmos_bit_range_set(uint32_t *dst, uint32_t dst_bytes, uint16_t dst_bit_pos,
    uint32_t *src, uint16_t n_bits);

/** Get bit range at an arbitrary bit position of a 32-bit word array
 *
 * \param[in]   src             source buffer (e.g. dataport) (big endian)
 * \param[in]   src_bytes       source buffer size in bytes
 * \param[in]   src_bit_pos     least bit position of the source
 * \param[in]   dst             destination buffer to store the bit value (little endian)
 * \param[in]   n_bits          how many bits to copy from source
 */
void bcmos_bit_range_get(const uint32_t *src, uint32_t src_bytes,
    uint16_t src_bit_pos, uint32_t *dst, uint16_t n_bits);

#endif /* BCMOLT_BIT_UTILS_H */
