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

#ifndef _BCMOLT_CONV_H_
#define _BCMOLT_CONV_H_

#include <bcmolt_utils.h>

/* Macro for generating a generic conversion from type A to type B.
 * Example:
 *
 *      BCMOLT_TYPE2TYPE(bws_dba_control_id, bws_dba_control_cb, static)
 *
 * will expand to:
 *
 *     typedef struct
 *     {
 *         bws_dba_control_id from;
 *         bws_dba_control_cb to;
 *     }
 *     bws_dba_control_id2bws_dba_control_cb_t;
 *
 *     static bws_dba_control_id2bws_dba_control_cb_t bws_dba_control_id2bws_dba_control_cb[];
 *
 *     static inline bws_dba_control_cb bws_dba_control_id2bws_dba_control_cb_conv(bws_dba_control_id from)
 *     {
 *         const bws_dba_control_id2bws_dba_control_cb_t *arr = bws_dba_control_id2bws_dba_control_cb;
 *         for (; arr->from != (bws_dba_control_id)-1 && arr->from != from; arr++);
 *         return arr->to;
 *     }
 */
#define BCMOLT_TYPE2TYPE(from_type, to_type, scope) \
    typedef struct \
    { \
        from_type from; \
        to_type to; \
    } \
    from_type##2##to_type##_t; \
    scope from_type##2##to_type##_t from_type##2##to_type[]; \
    static inline to_type from_type##2##to_type##_conv(from_type from) \
    { \
        const from_type##2##to_type##_t *arr = from_type##2##to_type; \
        for (; arr->from != (from_type)-1 && arr->from != from; arr++); \
        return arr->to; \
    }

/* Macro for generating a generic conversion from type A to a constant string.
 * Example:
 *
 *      BCMOLT_TYPE2STR(pon_mode, extern)
 *
 * will expand to:
 *
 *     typedef struct
 *     {
 *         pon_mode from;
 *         const char *to;
 *     }
 *     pon_mode2str_t;
 *
 *     extern pon_mode2str_t pon_mode2str[];
 *
 *     static inline const char *pon_mode2str_conv(pon_mode from)
 *     {
 *         const pon_mode2str_t *arr = pon_mode2str;
 *         for (; arr->from != (pon_mode)-1 && arr->from != from; arr++);
 *         return arr->to;
 *     }
 */
#define BCMOLT_TYPE2STR(from_type, scope) \
    typedef struct \
    { \
        from_type from; \
        const char *to; \
    } \
    from_type##2str_t; \
    scope from_type##2str_t from_type##2str[]; \
    static inline const char *from_type##2str_conv(from_type from) \
    { \
        const from_type##2str_t *arr = from_type##2str; \
        for (; arr->from != (from_type)-1 && arr->from != from; arr++); \
        if (arr->to == NULL) \
        { \
            BCMOS_TRACE_ERR("Unknown id %d\n", from); \
            return "NULL"; \
        } \
        return arr->to; \
    }

/* Macro for generating a generic conversion from type A to an integer.
 * Example:
 *
 *      BCMOLT_TYPE2INT(ploam_ds_gpon_message_id, repetitions, extern)
 *
 * will expand to:
 *
 *     typedef struct
 *     {
 *         ploam_ds_gpon_message_id from;
 *         int to;
 *     }
 *     ploam_ds_gpon_message_id2repetitions_t;
 *
 *     extern ploam_ds_gpon_message_id2repetitions_t ploam_ds_gpon_message_id2repetitions[];
 *
 *     static inline int ploam_ds_gpon_message_id2repetitions_conv(ploam_ds_gpon_message_id from)
 *     {
 *         const ploam_ds_gpon_message_id2repetitions_t *arr = ploam_ds_gpon_message_id2repetitions;
 *         for (; arr->from != (ploam_ds_gpon_message_id)-1 && arr->from != from; arr++);
 *         return arr->to;
 *     }
 */
#define BCMOLT_TYPE2INT(from_type, to_name, scope) \
    typedef struct \
    { \
        from_type from; \
        int to; \
    } \
    from_type##2##to_name##_t; \
    scope from_type##2##to_name##_t from_type##2##to_name[]; \
    static inline int from_type##2##to_name##_conv(from_type from) \
    { \
        const from_type##2##to_name##_t *arr = from_type##2##to_name; \
        for (; arr->from != (from_type)-1 && arr->from != from; arr++); \
        return arr->to; \
    }

/* Although we have BCMOLT_TYPE2STR, int2str_t is still required when the same generic pointer needs to point to 2 different types (e.g: one specific for GPON and
 * the other specific for XGPON). */
typedef struct
{
    int from;
    const char *to;
} int2str_t;

static inline const char *int2str(const int2str_t *arr, int from)
{
    for (; arr->from != -1 && arr->from != from; arr++);
    return arr->to;
}

/* Although we have BCMOLT_TYPE2INT, int2int_t is still required when the same generic pointer needs to point to 2 different types (e.g: one specific for GPON and
 * the other specific for XGPON). */
typedef struct
{
    int from;
    int to;
} int2int_t;

static inline int int2int(const int2int_t *arr, int from)
{
    for (; arr->from != -1 && arr->from != from; arr++);
    return arr->to;
}

char *bcmolt_strftime(char *time_str, time_t t, const char *timezone_str);

typedef const char *(*bcmolt_bit2str_conv_cb)(uint32_t bit);

/* Build a human readable string from multiple bit values (e.g. "buffer_swap|quiet_window"). */
char *bcmolt_bits2str_conv(char *events_str, uint32_t size, uint32_t bits, bcmolt_bit2str_conv_cb conv_cb);

#endif
