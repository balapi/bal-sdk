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

#include <bcmos_system.h>
#include <bcm_dev_log.h>
#include "bcmolt_api_model_internal.h"

static dev_log_id api_model_log = DEV_LOG_INVALID_ID;

dev_log_id bcmolt_api_model_log_id_get(void)
{
    return api_model_log;
}

void bcmolt_api_model_init(void)
{
#ifdef ENABLE_LOG
    api_model_log = bcm_dev_log_id_register("api_model", DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
#endif
}
