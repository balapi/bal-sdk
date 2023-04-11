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
#define BCMOLT_API_INTERNAL

#include "bcmolt_api.h"
#include "bcmolt_api_tags.h"
#include <bcmolt_api_topology.h>
#include <bcmolt_api_conn_mgr.h>

typedef struct
{
    bcmolt_system_mode system_mode;
    bcmolt_chip_family chip_family;
} bcmolt_api_tag_device_info;

typedef struct
{
    bcmolt_api_tag_device_info dev_info[BCM_MAX_DEVS_PER_OLT];
    bcmolt_pon_type pon_type[BCM_MAX_PONS_PER_OLT];
    bcmos_bool subscribed;
} bcmolt_api_tag_olt_info;

static bcmolt_api_tag_olt_info olt_info[BCM_MAX_OLTS];

bcmolt_system_mode bcmolt_api_system_mode_get(bcmolt_oltid olt, bcmolt_devid device)
{
    return olt_info[olt].dev_info[device].system_mode;
}

static void bcmolt_api_system_mode_set(bcmolt_oltid olt, bcmolt_devid device, bcmolt_system_mode sys_mode)
{
    olt_info[olt].dev_info[device].system_mode = sys_mode;
}

static bcmolt_chip_family bcmolt_api_chip_family_get(bcmolt_oltid olt, bcmolt_devid device)
{
    return olt_info[olt].dev_info[device].chip_family;
}

static void bcmolt_api_chip_family_set(bcmolt_oltid olt, bcmolt_devid device, bcmolt_chip_family chip)
{
    olt_info[olt].dev_info[device].chip_family = chip;
}

static bcmolt_pon_type bcmolt_api_pon_type_get(bcmolt_oltid olt, bcmolt_pon_ni pon_ni)
{
    return olt_info[olt].pon_type[pon_ni];
}

static void bcmolt_api_pon_type_set(bcmolt_oltid olt, bcmolt_pon_ni pon_ni, bcmolt_pon_type pon_type)
{
    olt_info[olt].pon_type[pon_ni] = pon_type;
}

static void bcmolt_api_tags_pon_types_update(bcmolt_oltid olt_id, bcmolt_odid device_id)
{
    for (bcmolt_pon_ni pon = 0; pon < BCM_MAX_PONS_PER_OLT; ++pon)
    {
        bcmolt_gdid gdid;
        bcmolt_ldid req_ldid, ldid;
        bcmolt_pon_pif pif;
        bcmos_errno err;

        err = bcmolt_apitopo_odid_to_gdid_ldid(olt_id, device_id, &gdid, &req_ldid);
        err = err ? err : bcmolt_apitopo_lif_to_pif(olt_id, pon, &gdid, &ldid, &pif);
        if ((err == BCM_ERR_OK) && (req_ldid == ldid))
        {
            bcmolt_api_pon_type_set(olt_id, pon, bcmolt_pon_get_type(olt_id, pon));
        }
    }
}

static void bcmolt_api_tags_olt_connected(bcmolt_oltid olt_id)
{
    for (bcmolt_odid dev = 0; dev < BCM_MAX_DEVS_PER_OLT; ++dev)
    {
        bcmos_errno rc;
        bcmolt_device_cfg dev_cfg = { };
        bcmolt_device_key dev_key = { .device_id = dev };
        bcmolt_gdid gdid;
        bcmolt_ldid ldid;

        rc = bcmolt_apitopo_odid_to_gdid_ldid(olt_id, dev, &gdid, &ldid);
        if (BCM_ERR_OK != rc)
        {
            continue; /* This device doesn't exist, skip it */
        }

        BCMOLT_CFG_INIT(&dev_cfg, device, dev_key);
        BCMOLT_FIELD_SET_PRESENT(&dev_cfg.data, device_cfg_data, system_mode);
        BCMOLT_FIELD_SET_PRESENT(&dev_cfg.data, device_cfg_data, chip_family);

        rc = bcmolt_cfg_get(olt_id, &dev_cfg.hdr);
        if (BCM_ERR_OK == rc)
        {
            bcmolt_api_system_mode_set(olt_id, dev, dev_cfg.data.system_mode);
            bcmolt_api_chip_family_set(olt_id, dev, dev_cfg.data.chip_family);
        }
        bcmolt_api_tags_pon_types_update(olt_id, dev);
    }
}

static void bcmolt_api_tags_device_ready(bcmolt_oltid olt_id, bcmolt_msg *msg)
{
    bcmolt_device_device_ready *ready = (bcmolt_device_device_ready *)msg;

    bcmolt_api_system_mode_set(olt_id, ready->key.device_id, ready->data.system_mode);
    bcmolt_api_chip_family_set(olt_id, ready->key.device_id, ready->data.chip_family);
    bcmolt_api_tags_pon_types_update(olt_id, ready->key.device_id);

    bcmolt_msg_free(msg);
}

static void bcmolt_api_tags_switch_pon_type_completed(bcmolt_oltid olt_id, bcmolt_msg *msg)
{
    bcmolt_pon_interface_switch_pon_type_completed *switch_type = (bcmolt_pon_interface_switch_pon_type_completed *)msg;

    bcmolt_api_pon_type_set(olt_id, switch_type->key.pon_ni, switch_type->data.new_type);

    bcmolt_msg_free(msg);
}

bcmolt_tag bcmolt_system_object_get_active_tags(bcmolt_obj_id obj_id)
{
    return bcmolt_object_tags(obj_id);
}

bcmolt_tag bcmolt_device_object_get_active_tags(bcmolt_obj_id obj_id, bcmolt_oltid olt, bcmolt_devid device)
{
    bcmolt_system_mode system_mode = bcmolt_api_system_mode_get(olt, device);
    bcmolt_chip_family chip_family = bcmolt_api_chip_family_get(olt, device);
    return bcmolt_dev_get_active_tags(system_mode, chip_family);
}

bcmolt_tag bcmolt_pon_object_get_active_tags(bcmolt_obj_id obj_id, bcmolt_oltid olt, bcmolt_pon_ni pon_ni)
{
    bcmolt_gdid global_dev;
    bcmolt_ldid line_card_dev;
    bcmolt_odid olt_dev;
    bcmolt_pon_pif pif;
    bcmos_errno rc;

    rc = bcmolt_apitopo_lif_to_pif(olt, pon_ni, &global_dev, &line_card_dev, &pif);
    if (BCM_ERR_OK == rc)
    {
        rc = bcmolt_apitopo_ldid_to_odid(olt, line_card_dev, &olt_dev);
        if (BCM_ERR_OK == rc)
        {
            bcmolt_chip_family chip_family = bcmolt_api_chip_family_get(olt, olt_dev);
            bcmolt_pon_type pon_type = bcmolt_api_pon_type_get(olt, pon_ni);

            return bcmolt_pon_get_active_tags(pif, chip_family, pon_type);
        }
    }

    return bcmolt_object_tags(obj_id);
}

static void bcmolt_api_tags_olt_connection_changed(
    bcmolt_goid olt,
    bcmolt_api_conn_status status,
    bcmolt_olt_disconnect_reason reason)
{
    if (BCMOLT_API_CONN_STATUS_CONNECTED == status)
    {
        bcmolt_api_tags_olt_connected(olt);

        if (!olt_info[olt].subscribed)
        {
            bcmolt_rx_cfg rx_cfg = { };
            bcmos_errno err;

            rx_cfg.obj_type = BCMOLT_OBJ_ID_DEVICE;
            rx_cfg.subgroup = BCMOLT_DEVICE_AUTO_SUBGROUP_DEVICE_READY;
            rx_cfg.rx_cb = bcmolt_api_tags_device_ready;
            err = bcmolt_ind_subscribe(olt, &rx_cfg);
            if (err != BCM_ERR_OK)
            {
                BCM_LOG(
                    ERROR,
                    bcmolt_api_log_id,
                    "Failed to subscribe to device ready indication. Error %s\n",
                    bcmos_strerror(err));
                return;
            }

            rx_cfg.obj_type = BCMOLT_OBJ_ID_PON_INTERFACE;
            rx_cfg.subgroup = BCMOLT_PON_INTERFACE_AUTO_SUBGROUP_SWITCH_PON_TYPE_COMPLETED;
            rx_cfg.rx_cb = bcmolt_api_tags_switch_pon_type_completed;
            err = bcmolt_ind_subscribe(olt, &rx_cfg);
            if (err != BCM_ERR_OK)
            {
                BCM_LOG(
                    ERROR,
                    bcmolt_api_log_id,
                    "Failed to subscribe to switch PON type completed indication. Error %s\n",
                    bcmos_strerror(err));
                return;
            }

            olt_info[olt].subscribed = BCMOS_TRUE;
        }
    }
}

void bcmolt_api_tags_init(void)
{
    for (bcmolt_oltid olt = 0; olt < BCM_MAX_OLTS; ++olt)
    {
        for (bcmolt_devid dev = 0; dev < BCM_MAX_DEVS_PER_OLT; ++dev)
        {
            olt_info[olt].dev_info[dev].system_mode = BCMOLT_SYSTEM_MODE__NUM_OF;
            olt_info[olt].dev_info[dev].chip_family = BCMOLT_CHIP_FAMILY_UNKNOWN;
        }

        for (bcmolt_pon_ni pon = 0; pon < BCM_MAX_PONS_PER_OLT; ++pon)
        {
            olt_info[olt].pon_type[pon] = BCMOLT_PON_TYPE_UNKNOWN;
        }
    }

    bcmolt_api_conn_mgr_ind_subscribe(bcmolt_api_tags_olt_connection_changed);
}

