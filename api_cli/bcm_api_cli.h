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

#ifndef BCM_API_CLI_H_
#define BCM_API_CLI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <bcmolt_msg.h>
#include <bcmcli.h>
#include <bcmolt_api_cli_handlers.h>

/* Initialize API CLI */
bcmos_errno bcm_api_cli_init(bcmcli_entry *parent_dir, bcmcli_session *session);

/* Update API CLI commands for the current device */
bcmos_errno bcm_api_cli_set_commands(bcmcli_session *session);

#ifdef __cplusplus
}
#endif

#endif /* BCM_API_CLI_H_ */
