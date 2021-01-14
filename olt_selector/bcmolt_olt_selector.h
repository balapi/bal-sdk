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

/*
 * bcmolt_olt_selector.h
 * Set / get current OLT for all CLI commands
 */

#ifndef _BCMOLT_OLT_SELECTOR_H_
#define _BCMOLT_OLT_SELECTOR_H_

#include <bcmolt_msg.h>
#include <bcmcli.h>

/* Current OLT change notification callback */
typedef void (*F_current_olt_change_ind)(bcmcli_session *session, bcmolt_oltid olt);

/* Register for current device change notification.
 * Multiple clients can register.
 */
bcmos_errno bcmolt_olt_sel_ind_register(F_current_olt_change_ind cb);

/* Initialize OLT selector module */
bcmos_errno bcmolt_olt_sel_init(bcmcli_entry *parent_dir);

/* Get current OLT */
bcmolt_oltid bcmolt_olt_sel_current(void);

#endif /* _BCMOLT_OLT_SELECTOR_H_ */
