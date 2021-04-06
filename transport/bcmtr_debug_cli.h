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

#ifndef BCMTR_DEBUG_CLI_H_
#define BCMTR_DEBUG_CLI_H_

/** Initialize CLD CLI commands
 * \returns BCM_ERR_OK (0) if successful
 */
bcmos_errno bcmtr_cld_cli_init(void);

/** Clean-up CLD CLI commands */
void bcmtr_cld_cli_exit(void);

#endif /* BCMTR_DEBUG_CLI_H_ */
