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

/*
 * API logging support.
 */

#ifndef BCMOLT_API_LOG_
#define BCMOLT_API_LOG_

#include <bcmos_system.h>
#include <bcmolt_msg.h>
#include <bcm_dev_log.h>

bcmos_errno bcmolt_api_log_init(void);

void bcmolt_api_log(bcmolt_oltid olt, const bcmolt_msg *msg);

#endif /* #ifndef BCMOLT_API_LOG_ */