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

#include "bcmolt_api.h"
#include "bcmolt_api_tags.h"

#ifdef BCMOLT_CONFIG_MODE_PROPRIETARY

bcmolt_tag bcmolt_debug_get_active_tags(bcmolt_devid dev, const bcmolt_debug_key *key)
{
    return bcmolt_device_object_get_active_tags(BCMOLT_OBJ_ID_DEBUG, dev, key->device_id);
}

bcmolt_tag bcmolt_internal_nni_serdes_get_active_tags(bcmolt_devid dev, const bcmolt_internal_nni_serdes_key *key)
{
    return bcmolt_device_object_get_active_tags(BCMOLT_OBJ_ID_INTERNAL_NNI_SERDES, dev, key->device_id);
}

bcmolt_tag bcmolt_iwf_get_active_tags(bcmolt_devid dev, const bcmolt_iwf_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_IWF, dev, key->pon_ni);
}

bcmolt_tag bcmolt_iwf_ds_egress_flow_get_active_tags(bcmolt_devid dev, const bcmolt_iwf_ds_egress_flow_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_IWF_DS_EGRESS_FLOW, dev, key->pon_ni);
}

bcmolt_tag bcmolt_iwf_ds_ingress_flow_get_active_tags(bcmolt_devid dev, const bcmolt_iwf_ds_ingress_flow_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_IWF_DS_INGRESS_FLOW, dev, key->pon_ni);
}

bcmolt_tag bcmolt_iwf_mac_table_get_active_tags(bcmolt_devid dev, const bcmolt_iwf_mac_table_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_IWF_MAC_TABLE, dev, key->pon_ni);
}

bcmolt_tag bcmolt_iwf_us_flow_get_active_tags(bcmolt_devid dev, const bcmolt_iwf_us_flow_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_IWF_US_FLOW, dev, key->pon_ni);
}

bcmolt_tag bcmolt_trx_calibration_get_active_tags(bcmolt_devid dev, const bcmolt_trx_calibration_key *key)
{
    return bcmolt_device_object_get_active_tags(BCMOLT_OBJ_ID_TRX_CALIBRATION, dev, key->device_id);
}

bcmolt_tag bcmolt_xpon_serdes_get_active_tags(bcmolt_devid dev, const bcmolt_xpon_serdes_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_XPON_SERDES, dev, key->pon_ni);
}

#endif

bcmolt_tag bcmolt_device_get_active_tags(bcmolt_devid dev, const bcmolt_device_key *key)
{
    return bcmolt_device_object_get_active_tags(BCMOLT_OBJ_ID_DEVICE, dev, key->device_id);
}

#ifdef BCMOLT_CONFIG_MODE_EPON

bcmolt_tag bcmolt_epon_denied_link_get_active_tags(bcmolt_devid dev, const bcmolt_epon_denied_link_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_EPON_DENIED_LINK, dev, key->pon_ni);
}

bcmolt_tag bcmolt_epon_link_get_active_tags(bcmolt_devid dev, const bcmolt_epon_link_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_EPON_LINK, dev, key->pon_ni);
}

bcmolt_tag bcmolt_ieee_25g_demo_onu_get_active_tags(bcmolt_devid dev, const bcmolt_ieee_25g_demo_onu_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_IEEE_25G_DEMO_ONU, dev, key->pon_ni);
}

bcmolt_tag bcmolt_ieee_25g_demo_onu_epon_link_get_active_tags(bcmolt_devid dev, const bcmolt_ieee_25g_demo_onu_epon_link_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_IEEE_25G_DEMO_ONU_EPON_LINK, dev, key->pon_ni);
}

#endif

bcmolt_tag bcmolt_access_control_get_active_tags(bcmolt_devid dev, const bcmolt_access_control_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_ACCESS_CONTROL);
}

bcmolt_tag bcmolt_flow_get_active_tags(bcmolt_devid dev, const bcmolt_flow_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_FLOW);
}

bcmolt_tag bcmolt_gpio_get_active_tags(bcmolt_devid dev, const bcmolt_gpio_key *key)
{
    return bcmolt_device_object_get_active_tags(BCMOLT_OBJ_ID_GPIO, dev, key->device_id);
}

bcmolt_tag bcmolt_group_get_active_tags(bcmolt_devid dev, const bcmolt_group_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_GROUP);
}

bcmolt_tag bcmolt_internal_nni_get_active_tags(bcmolt_devid dev, const bcmolt_internal_nni_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_INTERNAL_NNI, dev, key->pon_ni);
}

bcmolt_tag bcmolt_itupon_alloc_get_active_tags(bcmolt_devid dev, const bcmolt_itupon_alloc_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_ITUPON_ALLOC, dev, key->pon_ni);
}

bcmolt_tag bcmolt_itupon_gem_get_active_tags(bcmolt_devid dev, const bcmolt_itupon_gem_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_ITUPON_GEM, dev, key->pon_ni);
}

bcmolt_tag bcmolt_log_get_active_tags(bcmolt_devid dev, const bcmolt_log_key *key)
{
    return bcmolt_device_object_get_active_tags(BCMOLT_OBJ_ID_LOG, dev, key->device_id);
}

bcmolt_tag bcmolt_log_file_get_active_tags(bcmolt_devid dev, const bcmolt_log_file_key *key)
{
    return bcmolt_device_object_get_active_tags(BCMOLT_OBJ_ID_LOG_FILE, dev, key->device_id);
}

bcmolt_tag bcmolt_ngpon2_channel_get_active_tags(bcmolt_devid dev, const bcmolt_ngpon2_channel_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_NGPON2_CHANNEL, dev, key->pon_ni);
}

bcmolt_tag bcmolt_nni_interface_get_active_tags(bcmolt_devid dev, const bcmolt_nni_interface_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_NNI_INTERFACE);
}

bcmolt_tag bcmolt_olt_get_active_tags(bcmolt_devid dev, const bcmolt_olt_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_OLT);
}

bcmolt_tag bcmolt_onu_get_active_tags(bcmolt_devid dev, const bcmolt_onu_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_ONU, dev, key->pon_ni);
}

bcmolt_tag bcmolt_pbit_to_tc_get_active_tags(bcmolt_devid dev, const bcmolt_pbit_to_tc_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_PBIT_TO_TC);
}

bcmolt_tag bcmolt_pon_interface_get_active_tags(bcmolt_devid dev, const bcmolt_pon_interface_key *key)
{
    return bcmolt_pon_object_get_active_tags(BCMOLT_OBJ_ID_PON_INTERFACE, dev, key->pon_ni);
}

bcmolt_tag bcmolt_software_error_get_active_tags(bcmolt_devid dev, const bcmolt_software_error_key *key)
{
    return bcmolt_device_object_get_active_tags(BCMOLT_OBJ_ID_SOFTWARE_ERROR, dev, key->device_id);
}

bcmolt_tag bcmolt_tc_to_queue_get_active_tags(bcmolt_devid dev, const bcmolt_tc_to_queue_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_TC_TO_QUEUE);
}

bcmolt_tag bcmolt_tm_queue_get_active_tags(bcmolt_devid dev, const bcmolt_tm_queue_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_TM_QUEUE);
}

bcmolt_tag bcmolt_tm_sched_get_active_tags(bcmolt_devid dev, const bcmolt_tm_sched_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_TM_SCHED);
}

bcmolt_tag bcmolt_tm_qmp_get_active_tags(bcmolt_devid dev, const bcmolt_tm_qmp_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_TM_QMP);
}

bcmolt_tag bcmolt_erps_interface_get_active_tags(bcmolt_devid dev, const bcmolt_erps_interface_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_ERPS_INTERFACE);
}

bcmolt_tag bcmolt_eth_oam_get_active_tags(bcmolt_devid dev, const bcmolt_eth_oam_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_ETH_OAM);
}

bcmolt_tag bcmolt_protection_interface_get_active_tags(bcmolt_devid dev, const bcmolt_protection_interface_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_PROTECTION_INTERFACE);
}

bcmolt_tag bcmolt_inband_mgmt_channel_get_active_tags(bcmolt_devid dev, const bcmolt_inband_mgmt_channel_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_INBAND_MGMT_CHANNEL);
}

bcmolt_tag bcmolt_policer_profile_get_active_tags(bcmolt_devid dev, const bcmolt_policer_profile_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_POLICER_PROFILE);
}

bcmolt_tag bcmolt_switch_inni_get_active_tags(bcmolt_devid dev, const bcmolt_switch_inni_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_SWITCH_INNI);
}

bcmolt_tag bcmolt_lag_interface_get_active_tags(bcmolt_devid dev, const bcmolt_lag_interface_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_LAG_INTERFACE);
}

bcmolt_tag bcmolt_bal_system_get_active_tags(bcmolt_devid dev, const bcmolt_bal_system_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_BAL_SYSTEM);
}

bcmolt_tag bcmolt_api_msg_get_active_tags(bcmolt_oltid olt, const bcmolt_msg *msg)
{
    bcmos_errno err;
    const bcmolt_obj_descr *obj;
    const bcmolt_group_descr *group;
    void *key;
    uint32_t tags;

    err = bcmolt_api_obj_descr_get(msg->obj_type, &obj);
    BUG_ON(err != BCM_ERR_OK);

    err = bcmolt_api_group_descr_get(msg->obj_type, msg->group, msg->subgroup, &group);
    BUG_ON(err != BCM_ERR_OK);

    if ((msg->type & BCMOLT_MSG_TYPE_MULTI) != 0)
    {
        key = (void *)((long)msg + group->multi->key_offset);
    }
    else
    {
        key = (void *)((long)msg + group->key_offset);
    }

    tags = obj->get_active_tags(olt, key);

    return (bcmolt_tag)tags;
}

static bcmolt_tag bcmolt_chip_family_tags(bcmolt_chip_family chip)
{
    switch (chip)
    {
#ifndef BCM_OPEN_SOURCE
    case BCMOLT_CHIP_FAMILY_CHIP_FAMILY_6862_X:
        return BCMOLT_TAG_BCM6862X;
    case BCMOLT_CHIP_FAMILY_CHIP_FAMILY_6865_X:
        return BCMOLT_TAG_BCM6865X;
#endif
    default:
        return BCMOLT_TAG__NONE;
    }
}

static bcmolt_tag bcmolt_common_active_tags(bcmolt_chip_family chip_family)
{
    bcmolt_tag active_tags = (bcmolt_tag)(BCMOLT_TAG_DEVICE | BCMOLT_TAG_SYSTEM);
    active_tags |= bcmolt_chip_family_tags(chip_family);
    return active_tags;
}

static bcmolt_tag bcmolt_pon_type_get_tags(bcmolt_pon_type pon_type)
{
    for (const bcmolt_enum_val *enum_val = bcmolt_pon_type_string_table;
         enum_val->name != NULL;
         ++enum_val)
    {
        if (enum_val->val == pon_type)
        {
            return (bcmolt_tag)enum_val->tags;
        }
    }

    return BCMOLT_TAG__NONE;
}

bcmolt_tag bcmolt_dev_get_active_tags(bcmolt_system_mode system_mode, bcmolt_chip_family chip_family)
{
    bcmolt_tag active_tags = bcmolt_common_active_tags(chip_family);
    active_tags |= bcmolt_system_mode_tags(system_mode);
    return active_tags;
}

bcmolt_tag bcmolt_pon_get_active_tags(
    bcmolt_pon_ni pon_ni,
    bcmolt_chip_family chip_family,
    bcmolt_pon_type pon_type)
{
    bcmolt_tag active_tags = bcmolt_common_active_tags(chip_family);

    switch (pon_type)
    {
#ifndef BCM_OPEN_SOURCE
    case BCMOLT_PON_TYPE_XGS_GPON_WDMA:
        /* the even PONs are XGS, the odd PONs are GPON */
        if (pon_ni & 0x1)
            active_tags |= BCMOLT_TAG_GPON;
        else
            active_tags |= BCMOLT_TAG_XGS;
        break;
    case BCMOLT_PON_TYPE_XGS_XGPON_TDMR_GPON_WDMA:
        /* the even PONs are XGS XGPON TDMR, the odd PONs are GPON */
        if (pon_ni & 0x1)
            active_tags |= BCMOLT_TAG_GPON;
        else
            active_tags |= BCMOLT_TAG_TDMA;
        break;
#endif
    default:
        active_tags |= bcmolt_pon_type_get_tags(pon_type);
        break;
    }

    return active_tags;
}

bcmolt_pon_type bcmolt_pon_get_type(bcmolt_oltid olt_id, bcmolt_pon_ni pon_ni)
{
    bcmolt_pon_interface_key pon_key = { .pon_ni = pon_ni };
    bcmolt_pon_interface_cfg pon_cfg = { };

    BCMOLT_CFG_INIT(&pon_cfg, pon_interface, pon_key);
    BCMOLT_MSG_FIELD_GET(&pon_cfg, pon_type);

    bcmos_errno err = bcmolt_cfg_get(olt_id, &pon_cfg.hdr);
    if (err == BCM_ERR_OK)
    {
        return pon_cfg.data.pon_type;
    }
    else
    {
        return BCMOLT_PON_TYPE_UNKNOWN;
    }
}

bcmolt_tag bcmolt_host_log_file_get_active_tags(bcmolt_devid dev, const bcmolt_host_log_file_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_HOST_LOG_FILE);
}

bcmolt_tag bcmolt_host_log_get_active_tags(bcmolt_devid dev, const bcmolt_host_log_key *key)
{
    (void)key;
    return bcmolt_system_object_get_active_tags(BCMOLT_OBJ_ID_HOST_LOG);
}
