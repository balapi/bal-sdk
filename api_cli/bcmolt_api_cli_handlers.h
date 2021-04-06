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

#ifndef BCMOLT_API_CLI_HANDLERS_H_
#define BCMOLT_API_CLI_HANDLERS_H_

#include <bcmos_system.h>
#include <bcmcli.h>
#include <bcmolt_api_model.h>

/* The maximum amount of dynamic memory available for API CLI commands. */
#define APICLI_BYTE_POOL_SIZE (64 * 1024)

/* The maximum amount of memory that will be pre-allocated for uninitialized variable-size lists in a GET request. */
#define APICLI_DYNAMIC_LIST_BUFFER_SIZE (32 * 1024)

/* Perform an API call based on CLI input. */
bcmos_errno bcmolt_cli_api_call(
    bcmolt_devid device_id,
    bcmolt_mgt_group group_type,
    bcmolt_msg_type msg_type,
    bcmcli_session *session);

bcmos_bool bcmolt_api_cli_filter_get(void);

void bcmolt_api_cli_filter_set(bcmos_bool filter);

bcmos_errno apicli_msg_dump(bcmcli_session *session, bcmolt_devid dev, bcmolt_msg *msg);

#endif
