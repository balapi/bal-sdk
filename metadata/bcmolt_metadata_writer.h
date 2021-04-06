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
#ifndef BCMOLT_METADATA_WRITER_H_
#define BCMOLT_METADATA_WRITER_H_

/* bcmolt_metadata_writer.h
 * Utility functions to write the contents of a object/structure/field to an output stream in a readable format.
 */

#include <bcmos_system.h>
#include "bcmolt_type_metadata.h"

typedef enum
{
    BCMOLT_METADATA_WRITE_STYLE_LINE_SEPARATED = (1 << 0),
    BCMOLT_METADATA_WRITE_STYLE_SPACE_SEPARATED = (1 << 1),
    BCMOLT_METADATA_WRITE_STYLE_VERBOSE = (1 << 2),
    BCMOLT_METADATA_WRITE_STYLE_C_INIT = (1 << 3),
    BCMOLT_METADATA_WRITE_STYLE_CLI_INPUT = (1 << 4),
} bcmolt_api_write_style;

typedef void (*bcmolt_metadata_writer_write)(void *user_data, const char *format, va_list ap);

/* Handle that can be passed on to the various bcmolt_api_write_xx calls in order to print message/structure data. */
typedef struct
{
    bcmolt_metadata_writer_write write_cb;   /* Will be called whenever there is data to be printed. */
    void *user_data;                         /* Will be passed into write_cb as the first argument. */
    uint32_t filter_tags;                    /* Only write fields which have one or more of these tags */
    uint32_t ignore_tags;                    /* Ignore these tags when filtering fields */
} bcmolt_metadata_writer;

/* Write a single property. */
bcmos_errno bcmolt_metadata_write_prop(
    const bcmolt_metadata_writer *writer,
    const bcmolt_field_descr *pd,
    const void *prop_data);

/* Write a single property value in C initializer format. */
bcmos_errno bcmolt_metadata_write_prop_initializer(
    const bcmolt_metadata_writer *writer,
    const bcmolt_field_descr *pd,
    const void *prop_data);

/* Write a single metadata element (field, property, etc). Generally for internal use. */
bcmos_errno bcmolt_metadata_write_elem(
    const bcmolt_metadata_writer *writer,
    const bcmolt_type_descr *td,
    const void *data,
    const char *name,
    uint32_t style,
    uint16_t indent_level,
    const char *prefix,
    const char *suffix);

#endif /* BCMOLT_METADATA_WRITER_H_ */
