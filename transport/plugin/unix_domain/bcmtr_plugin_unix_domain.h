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

#ifndef BCMTR_PLUGIN_UNIX_DOMAIN_H_
#define BCMTR_PLUGIN_UNIX_DOMAIN_H_

#include "bcmtr_internal.h"

#define SOCKET_PATH " bcm68620"

/* Header added/stripped by transport and trmux Unix Domain plugins */
typedef struct bcmud_packet_hdr
{
    uint16_t data_length;
    uint16_t device;
} bcmud_packet_hdr;

bcmos_errno bcmtr_plugin_unix_domain_init(bcmtr_plugin_cfg *cfg, bcmtr_driver *driver);

#endif
