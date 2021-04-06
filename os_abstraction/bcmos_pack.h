/*
<:copyright-BRCM:2016-2019:Apache:standard

 Copyright (c) 2016-2019 Broadcom. All Rights Reserved

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

#ifndef BCMOS_PACK_H_
#define BCMOS_PACK_H_


/*
 * Packing macros
 *
 * Usage:
 * struct __PACKED_ATTR_START__ my_packed_struct
 * {
 *      ...
 * } __PACKED_ATTR_END__ ;
 *
 */

#ifdef __GNUC__

#define __PACKED_ATTR_START__
#define __PACKED_ATTR_END__ __attribute__ ((packed))

#else

#error define __PACKED_ATTR_START__,  __PACKED_ATTR_END__ for this compiler

#endif

/*
 * Macros for bit-field manipulation
 * For each field F requires 2 constants
 * - F_S - field shift
 * - F_W - field width
 */
#define BCM_FIELD_GET(_w, _f)           (((_w)>>_f ## _S) & ((1 << _f ## _W) - 1))
#define BCM_FIELD(_f, _v)               ((_v & ((1 << _f ## _W) - 1)) << _f ## _S)
#define BCM_FIELD_SET(_w, _f, _v)       (_w) |= BCM_FIELD(_f, _v)


#endif /* BCMOS_PACK_H_ */
