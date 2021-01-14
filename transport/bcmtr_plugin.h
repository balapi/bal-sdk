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

#ifndef BCMTR_PLUGIN_H_
#define BCMTR_PLUGIN_H_

#include <bcmos_system.h>
#include <bcmolt_msg.h>

#include <bcmtr_interface.h>
#include <bcmtr_header.h>

/** Plugin channel */
typedef unsigned long bcmtr_plugin_channel;

/* Plugin configuration */
typedef bcmtr_conn_parms bcmtr_plugin_cfg;

/* Receive callback function */
typedef bcmos_errno (*bcmtr_plugin_recv)(bcmtr_plugin_channel ch, bcmolt_devid *device,
    bcmolt_subchannel *subch, bcmos_buf **pbuf);

/** Transport driver. This structure is set by transport plugin
 */
typedef struct {
    /** Open communication channel, establish communication */
    bcmos_errno (*open)(bcmolt_devid device, bcmtr_plugin_cfg *cfg, bcmtr_plugin_channel *ch);
    /** Close communication channel */
    bcmos_errno (*close)(bcmtr_plugin_channel ch);
    /** Send data. buf ownership passes to the plugin.
     * It is plugin's responsibility to make sure that the buffer is released eventually */
    bcmos_errno (*send)(bcmtr_plugin_channel ch, bcmolt_devid device, bcmolt_subchannel subch,
        bcmos_buf *buf, bcmtr_send_flags flags);
} bcmtr_driver;

/** Receive data block */
typedef struct
{
    bcmtr_plugin_channel ch;
    bcmtr_plugin_recv recv;
} bcmtr_plugin_recv_info;

/*
 * Functions exposed by transport layer for plugin's benefit
 */

/** Pass received buffer to transport layer */
void bcmtr_packet_receive(bcmolt_devid device, bcmolt_subchannel subch, bcmos_buf *buf);

/** Create RX task.
 * The task will call plugin's recv callback pertiodically
 */
bcmos_errno bcmtr_rx_task_create(bcmos_task *task, const char *name, bcmtr_plugin_recv_info *recv_info);

#ifdef BCM_SUBSYSTEM_EMBEDDED

/*
 * Unmanaged channel support
 */

/** Find subchannel by network address and refresh client's timestamp */
bcmos_errno bcmtr_subch_get_by_address(const uint8_t addr[], uint32_t addr_len, bcmolt_subchannel *subch);

/** Get subchannel address */
bcmos_errno bcmtr_subch_address_get(bcmolt_subchannel subch, uint8_t addr[], uint32_t *addr_len);

#endif

#endif /* BCMTR_PLUGIN_H_ */
