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

#ifndef _BCMOLT_MATH_H_
#define _BCMOLT_MATH_H_

#define ROUND_U32(size_in_bytes) ((uint32_t)((size_in_bytes) + 0.5))
#define CEIL_U32(size_in_bytes) (((size_in_bytes)-(uint32_t)(size_in_bytes)) > 0 ? ((uint32_t)(size_in_bytes)+1) : (uint32_t)(size_in_bytes))
#define SQUARE(x) ((x) * (x))
#define PERCENT(percent, x) (((float)(percent) * (x)) / 100)

/*
 * Unit Conversion
 */
#define BITS_TO_BYTES(bits) ((bits) >> 3)
#define BYTES_TO_BITS(bytes) ((bytes) << 3)

/* Quantization */

/*
 * VAL_TO_BIN classifies the value of val to the proper bin
 * val - a value in the range [0, maxval]
 * bin - a value in the range [0, bins-1] (result of macro)
 */
#define VAL_TO_BIN(val, maxval, bins) ((val) < (maxval) ? ((val) * (bins)) / (maxval) : (bins) - 1)

/* If a value is in a certain bin, it is in the range [min_bin_val, max_bin_val]
 * min_bin_val - minimum value that belongs to bin
 * max_bin_val - maximum value that belongs to bin
 */
#define BIN_TO_MIN_BIN_VAL(bin, maxval, bins) ((bin) * ((double)(maxval) / (bins)))
#define BIN_TO_MAX_BIN_VAL(bin, maxval, bins) (((bin) + 1) * ((double)(maxval) / (bins)))

#define GET_MASK(width)             ((1 << (width)) - 1)

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX3
#define MAX3(a, b, c) MAX(MAX(a, b), c)
#endif
#ifndef MIN3
#define MIN3(a, b, c) MIN(MIN(a, b), c)
#endif

#define CEILING(a, b)   (((a) + ((b) - 1)) / (b))

/* Divide a by b (a/b) and round (up or down) to the nearest integer */
#define DIV_ROUND(a, b) (((a) + ((b) / 2)) / (b))

#define TWO_TO_POWER_OF(x) (1 << (x))

#endif /* _BCMOLT_MATH_H_ */
