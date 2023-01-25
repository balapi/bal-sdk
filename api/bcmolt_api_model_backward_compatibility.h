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

#ifndef BCMOLT_API_MODEL_BACKWARD_COMPATIBILITY_H_
#define BCMOLT_API_MODEL_BACKWARD_COMPATIBILITY_H_

#include "bcmolt_api_model_supporting_structs.h"
#include "bcmolt_api_model_supporting_enums.h"

/* As of BAL 3.12, "flow interface type" and "flow interface reference" are obsolete in favor of the generic types. */
typedef bcmolt_intf_ref bcmolt_flow_intf_ref;
typedef bcmolt_interface_type bcmolt_flow_interface_type;
#define BCMOLT_FLOW_INTERFACE_TYPE_PON BCMOLT_INTERFACE_TYPE_PON
#define BCMOLT_FLOW_INTERFACE_TYPE_NNI BCMOLT_INTERFACE_TYPE_NNI
#define BCMOLT_FLOW_INTERFACE_TYPE_HOST BCMOLT_INTERFACE_TYPE_HOST
#define BCMOLT_FLOW_INTERFACE_TYPE_ERPS BCMOLT_INTERFACE_TYPE_ERPS
#define BCMOLT_FLOW_INTERFACE_TYPE_PROTECTION BCMOLT_INTERFACE_TYPE_PROTECTION
#define BCMOLT_FLOW_INTERFACE_TYPE_LAG BCMOLT_INTERFACE_TYPE_LAG
#define BCMOLT_FLOW_INTERFACE_TYPE_UNASSIGNED BCMOLT_INTERFACE_TYPE_UNASSIGNED
#define bcmolt_flow_interface_type_string_table bcmolt_interface_type_string_table

#endif
