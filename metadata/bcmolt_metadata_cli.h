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
#ifndef BCMOLT_METADATA_CLI_H_
#define BCMOLT_METADATA_CLI_H_

/* bcmolt_metadata_cli.h
 * Utility functions to generate CLI commands based on metadata structures/objects/etc.
 */

#include <bcmos_system.h>
#include <bcmcli.h>
#include "bcmolt_set_metadata.h"
#include "bcmolt_type_metadata.h"

typedef enum
{
    BCMOLT_METADATA_CLI_FLAGS_NONE = 0,
    BCMOLT_METADATA_CLI_FLAGS_IGNORE_FIELDS    = (1 << 0),
    BCMOLT_METADATA_CLI_FLAGS_IGNORE_KEY       = (1 << 1),
    BCMOLT_METADATA_CLI_FLAGS_MULTI            = (1 << 2),
    BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ      = (1 << 3),
    BCMOLT_METADATA_CLI_FLAGS_ACCESS_WRITE     = (1 << 4),
    BCMOLT_METADATA_CLI_FLAGS_ACCESS_WRITE_ALL = (1 << 5), /* write access for everything, even read-only fields */

    /* Multi-get filters don't have a key, and even read-only fields are settable. */
    BCMOLT_METADATA_CLI_FLAGS_MULTI_GET_FILTER =
        BCMOLT_METADATA_CLI_FLAGS_IGNORE_KEY | BCMOLT_METADATA_CLI_FLAGS_ACCESS_WRITE_ALL,
} bcmolt_metadata_cli_flags;

/* Populate CLI parameter from a property/field descriptor.
 * If the property/field is a struct/union, this function will create the appropriate CLI parameters hierarchy. */
bcmos_errno bcmolt_metadata_cli_parm_populate_from_pd(
    bcmcli_session *session,
    const bcmolt_field_descr *pd,
    bcmcli_cmd_parm *parm,
    bcmolt_metadata_cli_flags flags,
    uint32_t parm_flags);

/* Read generated info and add CLI command for a given metadata API call. */
bcmos_errno bcmolt_metadata_cli_command_add(
    bcmcli_session *session,
    const bcmolt_metadata_set *set,
    bcmcli_entry *dir,
    const char *cmd_name,
    const char *cmd_descr,
    bcmolt_mgt_group group,
    bcmcli_cmd_cb cmd_handler,
    bcmolt_metadata_cli_flags flags);

#endif /* BCMOLT_METADATA_CLI_H_ */
