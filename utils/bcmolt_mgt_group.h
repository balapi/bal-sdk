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

/** Management group - key, config, operation, etc */

#ifndef BCMOLT_MGT_GROUP_H_
#define BCMOLT_MGT_GROUP_H_

typedef enum bcmolt_mgt_group
{
    BCMOLT_MGT_GROUP__BEGIN,
    BCMOLT_MGT_GROUP_KEY = BCMOLT_MGT_GROUP__BEGIN, /**< key that uniquely identifies object instance */
    BCMOLT_MGT_GROUP_CFG,                           /**< Configuration */
    BCMOLT_MGT_GROUP_STAT,                          /**< Statistics */
    BCMOLT_MGT_GROUP_STAT_CFG,                      /**< Statistics threshold configuration */
    BCMOLT_MGT_GROUP_AUTO,                          /**< Autonomous indications */
    BCMOLT_MGT_GROUP_AUTO_CFG,                      /**< Autonomous indication configuration */
    BCMOLT_MGT_GROUP_OPER,                          /**< Operations */
    BCMOLT_MGT_GROUP__NUM_OF
} bcmolt_mgt_group;

/* Message group name */
const char *bcmolt_mgt_group_to_str(bcmolt_mgt_group group);

#endif
