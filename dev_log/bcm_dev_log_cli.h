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

#ifndef BCM_DEV_LOG_CLI_H_
#define BCM_DEV_LOG_CLI_H_

#include <bcmcli.h>
#include <bcmcli_session.h>
#include "bcm_dev_log_task.h"

typedef struct
{
    bcmcli_session *session;
    dev_log_id log_id;
    bcm_dev_log_level log_level;
    char str[MAX_DEV_LOG_STRING_NET_SIZE];
    uint32_t free_len;
} bcm_dev_log_cli_session;

/* create a CLI session adaptation layer that outputs to a dev log instead of to a CLI shell */
bcmos_errno bcm_dev_log_cli_session_create(
    dev_log_id log_id,
    bcm_dev_log_level log_level,
    bcm_dev_log_cli_session **session);

/** initialize the dev log CLI functions 
 *
 * \param[in]   parent          Parent directory handle. NULL=root
 * \return      new directory handle or NULL in case of failure
 */
bcmcli_entry *bcm_dev_log_cli_init(bcmcli_entry *root_dir);

#endif /* BCM_DEV_LOG_CLI_H_ */
