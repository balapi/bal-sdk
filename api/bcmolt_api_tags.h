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

#ifndef BCMOLT_API_TAGS_H_
#define BCMOLT_API_TAGS_H_

#include <bcmos_system.h>
#include <bcmolt_api_model.h>

/**
 * Get tags for system level objects (not associated with a specific device)
 *
 * @param obj_id object type
 *
 * @return bcmolt_tag
 */
bcmolt_tag bcmolt_system_object_get_active_tags(bcmolt_obj_id obj_id);

/**
 * Get tags for objects associated with a specific device instance
 *
 * @param obj_id object type
 * @param olt user appl = goid, daemon = n/a, embedded = n/a
 * @param device user appl = odid, daemon = ldid, embedded = n/a
 *
 * @return bcmolt_tag
 */
bcmolt_tag bcmolt_device_object_get_active_tags(bcmolt_obj_id obj_id, bcmolt_oltid olt, bcmolt_devid device);

/**
 * Get tags for objects associated with a specific PON NI instance
 *
 * @param obj_id object type
 * @param olt user appl = goid, daemon = ldid, embedded = n/a
 * @param pon_ni user appl = LIF, daemon = PIF, embedded = PIF
 *
 * @return bcmolt_tag
 */
bcmolt_tag bcmolt_pon_object_get_active_tags(bcmolt_obj_id obj_id, bcmolt_oltid olt, bcmolt_pon_ni pon_ni);

void bcmolt_api_tags_init(void);

#endif /* BCMOLT_API_TAGS_H_ */

