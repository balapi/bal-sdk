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

#include <bcmos_system.h>
#include <bcmolt_api.h>
#include <bcmolt_msg.h>
#include <bcmolt_msg_pack.h>
#include <bcmolt_buf.h>
#include <bcmolt_string.h>
#include <bcmolt_system_types.h>
#include <bcmolt_system_type_funcs.h>
#include "bcmolt_api_model_api_struct_funcs.h"
#include "bcmolt_api_model_supporting_struct_funcs.h"
#include "bcmolt_api_model_supporting_enum_funcs.h"

void bcmolt_access_control_key_set_default(
    bcmolt_access_control_key *p_obj)
{
    p_obj->id = (bcmolt_access_control_id)0U;
}

bcmos_bool bcmolt_access_control_key_validate(
    const bcmolt_access_control_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_access_control_id)6399U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 6399\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_cfg_data_set_default(
    bcmolt_access_control_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_classifier_set_default(&p_obj->classifier);
    p_obj->priority = 0U;
    bcmolt_access_control_fwd_action_set_default(&p_obj->forwarding_action);
    bcmolt_access_control_pkt_modifier_set_default(&p_obj->modifier_action);
    p_obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    p_obj->statistics_control = BCMOLT_CONTROL_STATE_DISABLE;
    p_obj->cookie = (bcmolt_cookie)0ULL;
    bcmolt_intf_ref_list_u8_set_default(&p_obj->interface_refs);
    bcmolt_policer_action_set_default(&p_obj->policer_action);
    bcmolt_mirror_action_set_default(&p_obj->mirror_action);
    p_obj->stage = BCMOLT_STAGE_INGRESS;
}

bcmos_bool bcmolt_access_control_cfg_data_validate(
    const bcmolt_access_control_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_CLASSIFIER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "classifier.");
        if (!bcmolt_classifier_validate(&p_obj->classifier, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_PRIORITY))
    {
        /* p_obj->priority can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_FORWARDING_ACTION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "forwarding_action.");
        if (!bcmolt_access_control_fwd_action_validate(&p_obj->forwarding_action, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_MODIFIER_ACTION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "modifier_action.");
        if (!bcmolt_access_control_pkt_modifier_validate(&p_obj->modifier_action, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_STATISTICS_CONTROL))
    {
        switch (p_obj->statistics_control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "statistics_control: enum value %d is unexpected\n", (int)p_obj->statistics_control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_COOKIE))
    {
        /* p_obj->cookie can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_INTERFACE_REFS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "interface_refs: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_POLICER_ACTION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "policer_action.");
        if (!bcmolt_policer_action_validate(&p_obj->policer_action, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_MIRROR_ACTION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "mirror_action.");
        if (!bcmolt_mirror_action_validate(&p_obj->mirror_action, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_CFG_DATA_ID_STAGE))
    {
        switch (p_obj->stage)
        {
        case BCMOLT_STAGE_INGRESS:
        case BCMOLT_STAGE_EGRESS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stage: enum value %d is unexpected\n", (int)p_obj->stage);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_stats_data_set_default(
    bcmolt_access_control_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->packets = 0ULL;
    p_obj->bytes = 0ULL;
    bcmolt_arr_u64_4_set_default(&p_obj->policer_packets_passed_ukmb);
    bcmolt_arr_u64_4_set_default(&p_obj->policer_packets_dropped_ukmb);
    bcmolt_arr_u64_4_set_default(&p_obj->policer_bytes_passed_ukmb);
    bcmolt_arr_u64_4_set_default(&p_obj->policer_bytes_dropped_ukmb);
}

bcmos_bool bcmolt_access_control_stats_data_validate(
    const bcmolt_access_control_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_PACKETS))
    {
        /* p_obj->packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_BYTES))
    {
        /* p_obj->bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_PASSED_UKMB))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "policer_packets_passed_ukmb.");
        if (!bcmolt_arr_u64_4_validate(&p_obj->policer_packets_passed_ukmb, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_DROPPED_UKMB))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "policer_packets_dropped_ukmb.");
        if (!bcmolt_arr_u64_4_validate(&p_obj->policer_packets_dropped_ukmb, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_PASSED_UKMB))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "policer_bytes_passed_ukmb.");
        if (!bcmolt_arr_u64_4_validate(&p_obj->policer_bytes_passed_ukmb, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_DROPPED_UKMB))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "policer_bytes_dropped_ukmb.");
        if (!bcmolt_arr_u64_4_validate(&p_obj->policer_bytes_dropped_ukmb, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_receive_eth_packet_data_set_default(
    bcmolt_access_control_receive_eth_packet_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_intf_ref_set_default(&p_obj->interface_ref);
    p_obj->svc_port_id = (bcmolt_service_port_id)0UL;
    p_obj->lag_member_nni_id = 0;
    bcmolt_bin_str_set_default(&p_obj->buffer);
}

bcmos_bool bcmolt_access_control_receive_eth_packet_data_validate(
    const bcmolt_access_control_receive_eth_packet_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_INTERFACE_REF))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "interface_ref.");
        if (!bcmolt_intf_ref_validate(&p_obj->interface_ref, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_SVC_PORT_ID))
    {
        if (p_obj->svc_port_id > (bcmolt_service_port_id)65536UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "svc_port_id: %u is greater than the maximum value of 65536\n", p_obj->svc_port_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_LAG_MEMBER_NNI_ID))
    {
        /* p_obj->lag_member_nni_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_RECEIVE_ETH_PACKET_DATA_ID_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "buffer.");
        if (!bcmolt_bin_str_validate(&p_obj->buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_interfaces_update_data_set_default(
    bcmolt_access_control_interfaces_update_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->command = BCMOLT_MEMBERS_UPDATE_COMMAND_ADD;
    bcmolt_intf_ref_list_u8_set_default(&p_obj->interface_ref_list);
}

bcmos_bool bcmolt_access_control_interfaces_update_data_validate(
    const bcmolt_access_control_interfaces_update_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID_COMMAND))
    {
        switch (p_obj->command)
        {
        case BCMOLT_MEMBERS_UPDATE_COMMAND_ADD:
        case BCMOLT_MEMBERS_UPDATE_COMMAND_REMOVE:
        case BCMOLT_MEMBERS_UPDATE_COMMAND_SET:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "command: enum value %d is unexpected\n", (int)p_obj->command);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_INTERFACES_UPDATE_DATA_ID_INTERFACE_REF_LIST))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "interface_ref_list.");
        if (!bcmolt_intf_ref_list_u8_validate(&p_obj->interface_ref_list, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_stats_cfg_data_set_default(
    bcmolt_access_control_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->policer_packets_passed_ukmb);
    bcmolt_stat_alarm_config_set_default(&p_obj->policer_packets_dropped_ukmb);
    bcmolt_stat_alarm_config_set_default(&p_obj->policer_bytes_passed_ukmb);
    bcmolt_stat_alarm_config_set_default(&p_obj->policer_bytes_dropped_ukmb);
}

bcmos_bool bcmolt_access_control_stats_cfg_data_validate(
    const bcmolt_access_control_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_PACKETS_PASSED_UKMB))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "policer_packets_passed_ukmb.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->policer_packets_passed_ukmb, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_PACKETS_DROPPED_UKMB))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "policer_packets_dropped_ukmb.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->policer_packets_dropped_ukmb, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_BYTES_PASSED_UKMB))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "policer_bytes_passed_ukmb.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->policer_bytes_passed_ukmb, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_CFG_DATA_ID_POLICER_BYTES_DROPPED_UKMB))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "policer_bytes_dropped_ukmb.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->policer_bytes_dropped_ukmb, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_stats_alarm_raised_data_set_default(
    bcmolt_access_control_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_PACKETS;
}

bcmos_bool bcmolt_access_control_stats_alarm_raised_data_validate(
    const bcmolt_access_control_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_PACKETS:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_BYTES:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_PASSED_UKMB:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_DROPPED_UKMB:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_PASSED_UKMB:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_DROPPED_UKMB:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_stats_alarm_cleared_data_set_default(
    bcmolt_access_control_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_PACKETS;
}

bcmos_bool bcmolt_access_control_stats_alarm_cleared_data_validate(
    const bcmolt_access_control_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_PACKETS:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_BYTES:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_PASSED_UKMB:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_PACKETS_DROPPED_UKMB:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_PASSED_UKMB:
        case BCMOLT_ACCESS_CONTROL_STATS_DATA_ID_POLICER_BYTES_DROPPED_UKMB:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_auto_cfg_data_set_default(
    bcmolt_access_control_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->receive_eth_packet = BCMOS_FALSE;
    p_obj->stats_alarm_cleared = BCMOS_FALSE;
    p_obj->stats_alarm_raised = BCMOS_FALSE;
}

bcmos_bool bcmolt_access_control_auto_cfg_data_validate(
    const bcmolt_access_control_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID_RECEIVE_ETH_PACKET))
    {
        /* p_obj->receive_eth_packet can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED))
    {
        /* p_obj->stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ACCESS_CONTROL_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED))
    {
        /* p_obj->stats_alarm_raised can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_bal_system_cfg_data_set_default(
    bcmolt_bal_system_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->config_state = BCMOLT_CONFIG_STATE_CONFIGURED;
    bcmolt_lag_global_parms_set_default(&p_obj->lag_parms);
    bcmolt_host_port_params_set_default(&p_obj->host_port);
    p_obj->nto1_programming_model = BCMOLT_NTO1_PROGRAMMING_MODE_ASYMMETRIC;
}

bcmos_bool bcmolt_bal_system_cfg_data_validate(
    const bcmolt_bal_system_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_BAL_SYSTEM_CFG_DATA_ID_CONFIG_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "config_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_BAL_SYSTEM_CFG_DATA_ID_LAG_PARMS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "lag_parms.");
        if (!bcmolt_lag_global_parms_validate(&p_obj->lag_parms, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_BAL_SYSTEM_CFG_DATA_ID_HOST_PORT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "host_port.");
        if (!bcmolt_host_port_params_validate(&p_obj->host_port, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_BAL_SYSTEM_CFG_DATA_ID_NTO1_PROGRAMMING_MODEL))
    {
        switch (p_obj->nto1_programming_model)
        {
        case BCMOLT_NTO1_PROGRAMMING_MODE_ASYMMETRIC:
        case BCMOLT_NTO1_PROGRAMMING_MODE_SYMMETRIC:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "nto1_programming_model: enum value %d is unexpected\n", (int)p_obj->nto1_programming_model);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_bal_system_key_set_default(
    bcmolt_bal_system_key *p_obj)
{
    p_obj->id = (bcmolt_bal_system_id)0;
}

bcmos_bool bcmolt_bal_system_key_validate(
    const bcmolt_bal_system_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_bal_system_id)0)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 0\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_device_key_set_default(
    bcmolt_device_key *p_obj)
{
    p_obj->device_id = (bcmolt_odid)0;
}

bcmos_bool bcmolt_device_key_validate(
    const bcmolt_device_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->device_id can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_device_cfg_data_set_default(
    bcmolt_device_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->system_mode = (bcmolt_system_mode)0;
    p_obj->keepalive_interval = 5UL;
    p_obj->keepalive_tolerance = 3UL;
    bcmolt_firmware_sw_version_set_default(&p_obj->firmware_sw_version);
    p_obj->chip_family = BCMOLT_CHIP_FAMILY_UNKNOWN;
    p_obj->chip_id = 0x0UL;
    p_obj->chip_revision = (bcmolt_device_chip_revision)0;
    p_obj->chip_voltage = 0UL;
    p_obj->chip_temperature = 0L;
    bcmolt_debug_device_cfg_set_default(&p_obj->debug);
    p_obj->protection_switching_ext_irq = BCMOLT_EXT_IRQ_UNCONFIGURED;
    bcmolt_indication_shaping_set_default(&p_obj->indication_shaping);
    p_obj->tod_uart_baudrate = BCMOLT_UART_BAUDRATE_UART_RATE_9600;
    bcmolt_itu_tod_set_default(&p_obj->itu_tod);
    bcmolt_ieee_8021_as_tod_set_default(&p_obj->ieee_8021_as_tod);
    bcmolt_embedded_image_entry_list_u8_max_4_set_default(&p_obj->embedded_image_list);
    p_obj->wd_enable = BCMOS_TRUE;
    p_obj->wd_ip_traffic_timeout = 300U;
    p_obj->comm_mode = BCMOLT_COMM_MODE_PCIE;
    bcmolt_pcie_conn_data_set_default(&p_obj->pcie_conn_data);
    p_obj->itu_multipon_dba_enable = BCMOS_FALSE;
    p_obj->itu_low_latency_dba_enable = BCMOS_FALSE;
    p_obj->logger_enable = BCMOS_TRUE;
    bcmolt_inni_config_set_default(&p_obj->inni_config);
    p_obj->ras_ddr_mode = BCMOLT_RAS_DDR_USAGE_MODE_NO_DDR;
    p_obj->itu_enable_inni_mux = BCMOS_FALSE;
    bcmolt_arr_ploam_filter_5_set_default(&p_obj->trap_gpon_ploam);
    bcmolt_arr_ploam_filter_5_set_default(&p_obj->trap_xgpon_ploam);
    p_obj->debug_uart_port_swap = BCMOS_FALSE;
    bcmolt_inband_conn_data_set_default(&p_obj->inband_conn_data);
    p_obj->inband_internal_nni = (bcmolt_pon_ni)255;
    bcmolt_str_32_set_default(&p_obj->debug_bas_code);
    p_obj->debug_bas_enabled = BCMOS_FALSE;
}

bcmos_bool bcmolt_device_cfg_data_validate(
    const bcmolt_device_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_SYSTEM_MODE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "system_mode: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_KEEPALIVE_INTERVAL))
    {
        if (p_obj->keepalive_interval > 15UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "keepalive_interval: %u is greater than the maximum value of 15\n", p_obj->keepalive_interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_KEEPALIVE_TOLERANCE))
    {
        if (p_obj->keepalive_tolerance > 5UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "keepalive_tolerance: %u is greater than the maximum value of 5\n", p_obj->keepalive_tolerance);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_FIRMWARE_SW_VERSION))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "firmware_sw_version: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_CHIP_FAMILY))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "chip_family: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_CHIP_ID))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "chip_id: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_CHIP_REVISION))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "chip_revision: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_CHIP_VOLTAGE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "chip_voltage: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_CHIP_TEMPERATURE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "chip_temperature: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_DEBUG))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "debug.");
        if (!bcmolt_debug_device_cfg_validate(&p_obj->debug, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_PROTECTION_SWITCHING_EXT_IRQ))
    {
        switch (p_obj->protection_switching_ext_irq)
        {
        case BCMOLT_EXT_IRQ_EXT_IRQ0:
        case BCMOLT_EXT_IRQ_EXT_IRQ1:
        case BCMOLT_EXT_IRQ_EXT_IRQ2:
        case BCMOLT_EXT_IRQ_EXT_IRQ3:
        case BCMOLT_EXT_IRQ_EXT_IRQ4:
        case BCMOLT_EXT_IRQ_EXT_IRQ5:
        case BCMOLT_EXT_IRQ_UNCONFIGURED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "protection_switching_ext_irq: enum value %d is unexpected\n", (int)p_obj->protection_switching_ext_irq);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_INDICATION_SHAPING))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "indication_shaping.");
        if (!bcmolt_indication_shaping_validate(&p_obj->indication_shaping, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_TOD_UART_BAUDRATE))
    {
        switch (p_obj->tod_uart_baudrate)
        {
        case BCMOLT_UART_BAUDRATE_UART_RATE_4800:
        case BCMOLT_UART_BAUDRATE_UART_RATE_9600:
        case BCMOLT_UART_BAUDRATE_UART_RATE_14400:
        case BCMOLT_UART_BAUDRATE_UART_RATE_19200:
        case BCMOLT_UART_BAUDRATE_UART_RATE_38400:
        case BCMOLT_UART_BAUDRATE_UART_RATE_57600:
        case BCMOLT_UART_BAUDRATE_UART_RATE_115200:
        case BCMOLT_UART_BAUDRATE_UART_RATE_230400:
        case BCMOLT_UART_BAUDRATE_UART_RATE_380400:
        case BCMOLT_UART_BAUDRATE_UART_RATE_460800:
        case BCMOLT_UART_BAUDRATE_UART_RATE_921600:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "tod_uart_baudrate: enum value %d is unexpected\n", (int)p_obj->tod_uart_baudrate);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_ITU_TOD))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "itu_tod.");
        if (!bcmolt_itu_tod_validate(&p_obj->itu_tod, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_IEEE_8021_AS_TOD))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ieee_8021_as_tod.");
        if (!bcmolt_ieee_8021_as_tod_validate(&p_obj->ieee_8021_as_tod, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_EMBEDDED_IMAGE_LIST))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "embedded_image_list: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_WD_ENABLE))
    {
        /* p_obj->wd_enable can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_WD_IP_TRAFFIC_TIMEOUT))
    {
        if (p_obj->wd_ip_traffic_timeout < 5U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "wd_ip_traffic_timeout: %u is less than the minimum value of 5\n", p_obj->wd_ip_traffic_timeout);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_COMM_MODE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "comm_mode: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_PCIE_CONN_DATA))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "pcie_conn_data: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_ITU_MULTIPON_DBA_ENABLE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "itu_multipon_dba_enable: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_ITU_LOW_LATENCY_DBA_ENABLE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "itu_low_latency_dba_enable: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_LOGGER_ENABLE))
    {
        /* p_obj->logger_enable can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_INNI_CONFIG))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "inni_config: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_RAS_DDR_MODE))
    {
        switch (p_obj->ras_ddr_mode)
        {
        case BCMOLT_RAS_DDR_USAGE_MODE_NO_DDR:
        case BCMOLT_RAS_DDR_USAGE_MODE_ONE_DDR:
        case BCMOLT_RAS_DDR_USAGE_MODE_TWO_DDRS:
        case BCMOLT_RAS_DDR_USAGE_MODE_FOUR_DDRS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "ras_ddr_mode: enum value %d is unexpected\n", (int)p_obj->ras_ddr_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_ITU_ENABLE_INNI_MUX))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "itu_enable_inni_mux: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_TRAP_GPON_PLOAM))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "trap_gpon_ploam.");
        if (!bcmolt_arr_ploam_filter_5_validate(&p_obj->trap_gpon_ploam, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_TRAP_XGPON_PLOAM))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "trap_xgpon_ploam.");
        if (!bcmolt_arr_ploam_filter_5_validate(&p_obj->trap_xgpon_ploam, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_DEBUG_UART_PORT_SWAP))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "debug_uart_port_swap: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_INBAND_CONN_DATA))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "inband_conn_data: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_INBAND_INTERNAL_NNI))
    {
        if (p_obj->inband_internal_nni > (bcmolt_pon_ni)15)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "inband_internal_nni: %u is greater than the maximum value of 15\n", p_obj->inband_internal_nni);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_DEBUG_BAS_CODE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "debug_bas_code.");
        if (!bcmolt_str_32_validate(&p_obj->debug_bas_code, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CFG_DATA_ID_DEBUG_BAS_ENABLED))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "debug_bas_enabled: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_device_connect_data_set_default(
    bcmolt_device_connect_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->system_mode = (bcmolt_system_mode)0;
    p_obj->comm_mode = BCMOLT_COMM_MODE_PCIE;
    bcmolt_pcie_conn_data_set_default(&p_obj->pcie_conn_data);
    bcmolt_inband_conn_data_set_default(&p_obj->inband_conn_data);
    p_obj->itu_multipon_dba_enable = BCMOS_FALSE;
    bcmolt_inni_config_set_default(&p_obj->inni_config);
    p_obj->ras_ddr_mode = BCMOLT_RAS_DDR_USAGE_MODE_FOUR_DDRS;
    p_obj->ddr_test_mode = BCMOLT_DDR_TEST_MODE_NO_TEST;
    p_obj->itu_change_inni_mux_enable = BCMOS_FALSE;
    p_obj->itu_low_latency_dba_enable = BCMOS_FALSE;
    p_obj->debug_uart_port_swap = BCMOS_FALSE;
}

bcmos_bool bcmolt_device_connect_data_validate(
    const bcmolt_device_connect_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_SYSTEM_MODE))
    {
        switch (p_obj->system_mode)
        {
        case BCMOLT_SYSTEM_MODE_GPON__16_X:
        case BCMOLT_SYSTEM_MODE_XGPON__2_X:
        case BCMOLT_SYSTEM_MODE_XGPON__8_X:
        case BCMOLT_SYSTEM_MODE_XGS__2_X:
        case BCMOLT_SYSTEM_MODE_XGS__16_X:
        case BCMOLT_SYSTEM_MODE_XGS_XGPON__2_X_COEX_TDMA:
        case BCMOLT_SYSTEM_MODE_NGPON2__2_X_10G:
        case BCMOLT_SYSTEM_MODE_XGS__8_X_GPON__8_X_WDMA:
        case BCMOLT_SYSTEM_MODE_XGS__1_X:
        case BCMOLT_SYSTEM_MODE_XGPON__1_X:
        case BCMOLT_SYSTEM_MODE_ITU__8_X_IEEE__8_X:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "system_mode: enum value %d is unexpected\n", (int)p_obj->system_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_COMM_MODE))
    {
        switch (p_obj->comm_mode)
        {
        case BCMOLT_COMM_MODE_PCIE:
        case BCMOLT_COMM_MODE_IN_BAND:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "comm_mode: enum value %d is unexpected\n", (int)p_obj->comm_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_PCIE_CONN_DATA))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "pcie_conn_data.");
        if (!bcmolt_pcie_conn_data_validate(&p_obj->pcie_conn_data, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_INBAND_CONN_DATA))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "inband_conn_data.");
        if (!bcmolt_inband_conn_data_validate(&p_obj->inband_conn_data, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_ITU_MULTIPON_DBA_ENABLE))
    {
        /* p_obj->itu_multipon_dba_enable can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_INNI_CONFIG))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "inni_config.");
        if (!bcmolt_inni_config_validate(&p_obj->inni_config, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_RAS_DDR_MODE))
    {
        switch (p_obj->ras_ddr_mode)
        {
        case BCMOLT_RAS_DDR_USAGE_MODE_NO_DDR:
        case BCMOLT_RAS_DDR_USAGE_MODE_ONE_DDR:
        case BCMOLT_RAS_DDR_USAGE_MODE_TWO_DDRS:
        case BCMOLT_RAS_DDR_USAGE_MODE_FOUR_DDRS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "ras_ddr_mode: enum value %d is unexpected\n", (int)p_obj->ras_ddr_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_DDR_TEST_MODE))
    {
        switch (p_obj->ddr_test_mode)
        {
        case BCMOLT_DDR_TEST_MODE_NO_TEST:
        case BCMOLT_DDR_TEST_MODE_ALL_DDRS:
        case BCMOLT_DDR_TEST_MODE_CPU_DDR:
        case BCMOLT_DDR_TEST_MODE_RAS_DDRS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "ddr_test_mode: enum value %d is unexpected\n", (int)p_obj->ddr_test_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_ITU_CHANGE_INNI_MUX_ENABLE))
    {
        /* p_obj->itu_change_inni_mux_enable can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_ITU_LOW_LATENCY_DBA_ENABLE))
    {
        /* p_obj->itu_low_latency_dba_enable can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECT_DATA_ID_DEBUG_UART_PORT_SWAP))
    {
        /* p_obj->debug_uart_port_swap can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_device_host_keep_alive_data_set_default(
    bcmolt_device_host_keep_alive_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->sequence_number = 0UL;
    p_obj->time_stamp = 0UL;
}

bcmos_bool bcmolt_device_host_keep_alive_data_validate(
    const bcmolt_device_host_keep_alive_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID_SEQUENCE_NUMBER))
    {
        /* p_obj->sequence_number can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_HOST_KEEP_ALIVE_DATA_ID_TIME_STAMP))
    {
        /* p_obj->time_stamp can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_device_set_8021_as_tod_string_data_set_default(
    bcmolt_device_set_8021_as_tod_string_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_str_256_set_default(&p_obj->tod_string);
}

bcmos_bool bcmolt_device_set_8021_as_tod_string_data_validate(
    const bcmolt_device_set_8021_as_tod_string_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SET_8021_AS_TOD_STRING_DATA_ID_TOD_STRING))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tod_string.");
        if (!bcmolt_str_256_validate(&p_obj->tod_string, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_device_image_transfer_start_data_set_default(
    bcmolt_device_image_transfer_start_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->image_type = BCMOLT_DEVICE_IMAGE_TYPE_BOOTLOADER;
    p_obj->image_size = 0UL;
    p_obj->crc32 = 0x0UL;
    bcmolt_str_64_set_default(&p_obj->image_name);
}

bcmos_bool bcmolt_device_image_transfer_start_data_validate(
    const bcmolt_device_image_transfer_start_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_IMAGE_TYPE))
    {
        switch (p_obj->image_type)
        {
        case BCMOLT_DEVICE_IMAGE_TYPE_BOOTLOADER:
        case BCMOLT_DEVICE_IMAGE_TYPE_APPLICATION:
        case BCMOLT_DEVICE_IMAGE_TYPE_ITU_PON_ONU_FIRMWARE:
        case BCMOLT_DEVICE_IMAGE_TYPE_EPON_ONU_FIRMWARE:
        case BCMOLT_DEVICE_IMAGE_TYPE_DDR_PHY:
        case BCMOLT_DEVICE_IMAGE_TYPE_CFE:
        case BCMOLT_DEVICE_IMAGE_TYPE_OPEN_CPU_LINUX_IMG:
        case BCMOLT_DEVICE_IMAGE_TYPE_OPEN_CPU_DTB_IMG:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "image_type: enum value %d is unexpected\n", (int)p_obj->image_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_IMAGE_SIZE))
    {
        /* p_obj->image_size can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_CRC32))
    {
        /* p_obj->crc32 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_START_DATA_ID_IMAGE_NAME))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "image_name.");
        if (!bcmolt_str_64_validate(&p_obj->image_name, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_device_image_transfer_data_data_set_default(
    bcmolt_device_image_transfer_data_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->block_number = 0UL;
    p_obj->more_data = BCMOS_FALSE;
    bcmolt_bin_str_set_default(&p_obj->data);
}

bcmos_bool bcmolt_device_image_transfer_data_data_validate(
    const bcmolt_device_image_transfer_data_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID_BLOCK_NUMBER))
    {
        /* p_obj->block_number can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID_MORE_DATA))
    {
        /* p_obj->more_data can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_DATA_DATA_ID_DATA))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "data.");
        if (!bcmolt_bin_str_validate(&p_obj->data, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_device_run_ddr_test_data_set_default(
    bcmolt_device_run_ddr_test_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->cpu = BCMOS_FALSE;
    p_obj->ras_0 = BCMOS_FALSE;
    p_obj->ras_1 = BCMOS_FALSE;
}

bcmos_bool bcmolt_device_run_ddr_test_data_validate(
    const bcmolt_device_run_ddr_test_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID_CPU))
    {
        /* p_obj->cpu can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID_RAS_0))
    {
        /* p_obj->ras_0 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_RUN_DDR_TEST_DATA_ID_RAS_1))
    {
        /* p_obj->ras_1 can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_device_device_ready_data_set_default(
    bcmolt_device_device_ready_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_firmware_sw_version_set_default(&p_obj->firmware_sw_version);
    p_obj->system_mode = (bcmolt_system_mode)0;
    p_obj->keepalive_interval = 5UL;
    p_obj->keepalive_tolerance = 3UL;
    p_obj->standalone = BCMOS_FALSE;
    p_obj->chip_family = BCMOLT_CHIP_FAMILY_UNKNOWN;
}

bcmos_bool bcmolt_device_device_ready_data_validate(
    const bcmolt_device_device_ready_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_READY_DATA_ID_FIRMWARE_SW_VERSION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "firmware_sw_version.");
        if (!bcmolt_firmware_sw_version_validate(&p_obj->firmware_sw_version, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_READY_DATA_ID_SYSTEM_MODE))
    {
        switch (p_obj->system_mode)
        {
        case BCMOLT_SYSTEM_MODE_GPON__16_X:
        case BCMOLT_SYSTEM_MODE_XGPON__2_X:
        case BCMOLT_SYSTEM_MODE_XGPON__8_X:
        case BCMOLT_SYSTEM_MODE_XGS__2_X:
        case BCMOLT_SYSTEM_MODE_XGS__16_X:
        case BCMOLT_SYSTEM_MODE_XGS_XGPON__2_X_COEX_TDMA:
        case BCMOLT_SYSTEM_MODE_NGPON2__2_X_10G:
        case BCMOLT_SYSTEM_MODE_XGS__8_X_GPON__8_X_WDMA:
        case BCMOLT_SYSTEM_MODE_XGS__1_X:
        case BCMOLT_SYSTEM_MODE_XGPON__1_X:
        case BCMOLT_SYSTEM_MODE_ITU__8_X_IEEE__8_X:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "system_mode: enum value %d is unexpected\n", (int)p_obj->system_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_READY_DATA_ID_KEEPALIVE_INTERVAL))
    {
        if (p_obj->keepalive_interval > 15UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "keepalive_interval: %u is greater than the maximum value of 15\n", p_obj->keepalive_interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_READY_DATA_ID_KEEPALIVE_TOLERANCE))
    {
        /* p_obj->keepalive_tolerance can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_READY_DATA_ID_STANDALONE))
    {
        /* p_obj->standalone can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_READY_DATA_ID_CHIP_FAMILY))
    {
        switch (p_obj->chip_family)
        {
        case BCMOLT_CHIP_FAMILY_UNKNOWN:
        case BCMOLT_CHIP_FAMILY_CHIP_FAMILY_6862_X:
        case BCMOLT_CHIP_FAMILY_CHIP_FAMILY_6865_X:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "chip_family: enum value %d is unexpected\n", (int)p_obj->chip_family);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_device_device_keep_alive_data_set_default(
    bcmolt_device_device_keep_alive_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->sequence_number = 0UL;
    p_obj->time_stamp = 0UL;
    p_obj->keepalive_interval = 0UL;
    p_obj->keepalive_tolerance = 0UL;
}

bcmos_bool bcmolt_device_device_keep_alive_data_validate(
    const bcmolt_device_device_keep_alive_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_SEQUENCE_NUMBER))
    {
        /* p_obj->sequence_number can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_TIME_STAMP))
    {
        /* p_obj->time_stamp can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_KEEPALIVE_INTERVAL))
    {
        /* p_obj->keepalive_interval can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DEVICE_KEEP_ALIVE_DATA_ID_KEEPALIVE_TOLERANCE))
    {
        /* p_obj->keepalive_tolerance can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_device_connection_failure_data_set_default(
    bcmolt_device_connection_failure_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->reason = BCMOLT_HOST_CONNECTION_FAIL_REASON_TIMEOUT;
    p_obj->device_in_reset = BCMOS_FALSE;
    bcmolt_str_256_set_default(&p_obj->error_text);
}

bcmos_bool bcmolt_device_connection_failure_data_validate(
    const bcmolt_device_connection_failure_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID_REASON))
    {
        switch (p_obj->reason)
        {
        case BCMOLT_HOST_CONNECTION_FAIL_REASON_TIMEOUT:
        case BCMOLT_HOST_CONNECTION_FAIL_REASON_KEEPALIVE:
        case BCMOLT_HOST_CONNECTION_FAIL_REASON_SOFTWARE_VERSION_MISMATCH:
        case BCMOLT_HOST_CONNECTION_FAIL_REASON_CONNECTION_PARAM_MISMATCH:
        case BCMOLT_HOST_CONNECTION_FAIL_REASON_RECONNECT_TIMEOUT:
        case BCMOLT_HOST_CONNECTION_FAIL_REASON_INTERNAL_ERROR:
        case BCMOLT_HOST_CONNECTION_FAIL_REASON_SYSTEM_MODE_NOT_SUPPORTED:
        case BCMOLT_HOST_CONNECTION_FAIL_REASON_PARAMETER:
        case BCMOLT_HOST_CONNECTION_FAIL_REASON_DDR_TEST_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "reason: enum value %d is unexpected\n", (int)p_obj->reason);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID_DEVICE_IN_RESET))
    {
        /* p_obj->device_in_reset can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECTION_FAILURE_DATA_ID_ERROR_TEXT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "error_text.");
        if (!bcmolt_str_256_validate(&p_obj->error_text, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_device_connection_complete_data_set_default(
    bcmolt_device_connection_complete_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->standalone = BCMOS_FALSE;
    p_obj->system_mode = (bcmolt_system_mode)0;
}

bcmos_bool bcmolt_device_connection_complete_data_validate(
    const bcmolt_device_connection_complete_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID_STANDALONE))
    {
        /* p_obj->standalone can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CONNECTION_COMPLETE_DATA_ID_SYSTEM_MODE))
    {
        switch (p_obj->system_mode)
        {
        case BCMOLT_SYSTEM_MODE_GPON__16_X:
        case BCMOLT_SYSTEM_MODE_XGPON__2_X:
        case BCMOLT_SYSTEM_MODE_XGPON__8_X:
        case BCMOLT_SYSTEM_MODE_XGS__2_X:
        case BCMOLT_SYSTEM_MODE_XGS__16_X:
        case BCMOLT_SYSTEM_MODE_XGS_XGPON__2_X_COEX_TDMA:
        case BCMOLT_SYSTEM_MODE_NGPON2__2_X_10G:
        case BCMOLT_SYSTEM_MODE_XGS__8_X_GPON__8_X_WDMA:
        case BCMOLT_SYSTEM_MODE_XGS__1_X:
        case BCMOLT_SYSTEM_MODE_XGPON__1_X:
        case BCMOLT_SYSTEM_MODE_ITU__8_X_IEEE__8_X:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "system_mode: enum value %d is unexpected\n", (int)p_obj->system_mode);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_device_disconnection_complete_data_set_default(
    bcmolt_device_disconnection_complete_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->reason = BCMOLT_DEVICE_DISCONNECT_REASON_FAILED_TO_CONNECT;
}

bcmos_bool bcmolt_device_disconnection_complete_data_validate(
    const bcmolt_device_disconnection_complete_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DISCONNECTION_COMPLETE_DATA_ID_REASON))
    {
        switch (p_obj->reason)
        {
        case BCMOLT_DEVICE_DISCONNECT_REASON_FAILED_TO_CONNECT:
        case BCMOLT_DEVICE_DISCONNECT_REASON_DISCONNECT_REQUEST:
        case BCMOLT_DEVICE_DISCONNECT_REASON_RESET_REQUEST:
        case BCMOLT_DEVICE_DISCONNECT_REASON_KA_FAILURE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "reason: enum value %d is unexpected\n", (int)p_obj->reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_device_sw_error_data_set_default(
    bcmolt_device_sw_error_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_str_100_set_default(&p_obj->task_name);
    bcmolt_str_100_set_default(&p_obj->file_name);
    p_obj->line_number = 0UL;
    p_obj->pon_ni = 0;
}

bcmos_bool bcmolt_device_sw_error_data_validate(
    const bcmolt_device_sw_error_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SW_ERROR_DATA_ID_TASK_NAME))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "task_name.");
        if (!bcmolt_str_100_validate(&p_obj->task_name, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SW_ERROR_DATA_ID_FILE_NAME))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "file_name.");
        if (!bcmolt_str_100_validate(&p_obj->file_name, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SW_ERROR_DATA_ID_LINE_NUMBER))
    {
        /* p_obj->line_number can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SW_ERROR_DATA_ID_PON_NI))
    {
        /* p_obj->pon_ni can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_device_sw_exception_data_set_default(
    bcmolt_device_sw_exception_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->cpu_id = 0;
    bcmolt_str_2000_set_default(&p_obj->text);
}

bcmos_bool bcmolt_device_sw_exception_data_validate(
    const bcmolt_device_sw_exception_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID_CPU_ID))
    {
        /* p_obj->cpu_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SW_EXCEPTION_DATA_ID_TEXT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "text.");
        if (!bcmolt_str_2000_validate(&p_obj->text, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_device_image_transfer_complete_data_set_default(
    bcmolt_device_image_transfer_complete_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->image_type = BCMOLT_DEVICE_IMAGE_TYPE_BOOTLOADER;
    p_obj->block_number = 0UL;
    p_obj->status = BCMOLT_IMAGE_TRANSFER_STATUS_SUCCESS;
}

bcmos_bool bcmolt_device_image_transfer_complete_data_validate(
    const bcmolt_device_image_transfer_complete_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID_IMAGE_TYPE))
    {
        switch (p_obj->image_type)
        {
        case BCMOLT_DEVICE_IMAGE_TYPE_BOOTLOADER:
        case BCMOLT_DEVICE_IMAGE_TYPE_APPLICATION:
        case BCMOLT_DEVICE_IMAGE_TYPE_ITU_PON_ONU_FIRMWARE:
        case BCMOLT_DEVICE_IMAGE_TYPE_EPON_ONU_FIRMWARE:
        case BCMOLT_DEVICE_IMAGE_TYPE_DDR_PHY:
        case BCMOLT_DEVICE_IMAGE_TYPE_CFE:
        case BCMOLT_DEVICE_IMAGE_TYPE_OPEN_CPU_LINUX_IMG:
        case BCMOLT_DEVICE_IMAGE_TYPE_OPEN_CPU_DTB_IMG:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "image_type: enum value %d is unexpected\n", (int)p_obj->image_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID_BLOCK_NUMBER))
    {
        /* p_obj->block_number can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_IMAGE_TRANSFER_COMPLETE_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_IMAGE_TRANSFER_STATUS_SUCCESS:
        case BCMOLT_IMAGE_TRANSFER_STATUS_MEMORY_ALLOCATION_FAILURE:
        case BCMOLT_IMAGE_TRANSFER_STATUS_UNSUPPORTED_FILE_TYPE:
        case BCMOLT_IMAGE_TRANSFER_STATUS_CRC_ERROR:
        case BCMOLT_IMAGE_TRANSFER_STATUS_BLOCK_OUT_OF_SYNC:
        case BCMOLT_IMAGE_TRANSFER_STATUS_INTERNAL_ERROR:
        case BCMOLT_IMAGE_TRANSFER_STATUS_INVALID_STATE:
        case BCMOLT_IMAGE_TRANSFER_STATUS_PREMATURE_TERMINATION:
        case BCMOLT_IMAGE_TRANSFER_STATUS_ACK_TIMEOUT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_device_ddr_test_complete_data_set_default(
    bcmolt_device_ddr_test_complete_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_ddr_test_completed_set_default(&p_obj->ddr_test);
}

bcmos_bool bcmolt_device_ddr_test_complete_data_validate(
    const bcmolt_device_ddr_test_complete_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_DDR_TEST_COMPLETE_DATA_ID_DDR_TEST))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ddr_test.");
        if (!bcmolt_ddr_test_completed_validate(&p_obj->ddr_test, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_device_sw_health_check_failure_data_set_default(
    bcmolt_device_sw_health_check_failure_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_str_100_set_default(&p_obj->module_name);
    p_obj->module_id = 0U;
    p_obj->status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_device_sw_health_check_failure_data_validate(
    const bcmolt_device_sw_health_check_failure_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID_MODULE_NAME))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "module_name.");
        if (!bcmolt_str_100_validate(&p_obj->module_name, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID_MODULE_ID))
    {
        /* p_obj->module_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_SW_HEALTH_CHECK_FAILURE_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_device_change_inni_mux_data_set_default(
    bcmolt_device_change_inni_mux_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->mux = BCMOLT_INNI_MUX_NONE;
    p_obj->nni_connection = BCMOLT_NNI_CONNECTION_PRIMARY;
}

bcmos_bool bcmolt_device_change_inni_mux_data_validate(
    const bcmolt_device_change_inni_mux_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID_MUX))
    {
        switch (p_obj->mux)
        {
        case BCMOLT_INNI_MUX_NONE:
        case BCMOLT_INNI_MUX_FOUR_TO_ONE:
        case BCMOLT_INNI_MUX_TWO_TO_ONE:
        case BCMOLT_INNI_MUX_FOUR_TO_ONE_IN_VLAN:
        case BCMOLT_INNI_MUX_TWO_TO_ONE_IN_VLAN:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "mux: enum value %d is unexpected\n", (int)p_obj->mux);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_CHANGE_INNI_MUX_DATA_ID_NNI_CONNECTION))
    {
        switch (p_obj->nni_connection)
        {
        case BCMOLT_NNI_CONNECTION_PRIMARY:
        case BCMOLT_NNI_CONNECTION_BACKUP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "nni_connection: enum value %d is unexpected\n", (int)p_obj->nni_connection);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_device_inni_mux_configuration_completed_data_set_default(
    bcmolt_device_inni_mux_configuration_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->new_mux = BCMOLT_INNI_MUX_NONE;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_device_inni_mux_configuration_completed_data_validate(
    const bcmolt_device_inni_mux_configuration_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID_NEW_MUX))
    {
        switch (p_obj->new_mux)
        {
        case BCMOLT_INNI_MUX_NONE:
        case BCMOLT_INNI_MUX_FOUR_TO_ONE:
        case BCMOLT_INNI_MUX_TWO_TO_ONE:
        case BCMOLT_INNI_MUX_FOUR_TO_ONE_IN_VLAN:
        case BCMOLT_INNI_MUX_TWO_TO_ONE_IN_VLAN:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_mux: enum value %d is unexpected\n", (int)p_obj->new_mux);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_INNI_MUX_CONFIGURATION_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_device_tod_calibration_done_data_set_default(
    bcmolt_device_tod_calibration_done_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->pon_ni = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_TOD_CALIBRATION_FAIL_REASON_NONE;
}

bcmos_bool bcmolt_device_tod_calibration_done_data_validate(
    const bcmolt_device_tod_calibration_done_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID_PON_NI))
    {
        /* p_obj->pon_ni can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_TOD_CALIBRATION_DONE_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_TOD_CALIBRATION_FAIL_REASON_NONE:
        case BCMOLT_TOD_CALIBRATION_FAIL_REASON_PPS_TIMEOUT:
        case BCMOLT_TOD_CALIBRATION_FAIL_REASON_UART_READ_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_device_auto_cfg_data_set_default(
    bcmolt_device_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->connection_complete = BCMOS_FALSE;
    p_obj->connection_established = BCMOS_FALSE;
    p_obj->connection_failure = BCMOS_FALSE;
    p_obj->ddr_test_complete = BCMOS_FALSE;
    p_obj->device_keep_alive = BCMOS_FALSE;
    p_obj->device_ready = BCMOS_FALSE;
    p_obj->disconnection_complete = BCMOS_FALSE;
    p_obj->image_transfer_complete = BCMOS_FALSE;
    p_obj->inni_mux_configuration_completed = BCMOS_FALSE;
    p_obj->sw_error = BCMOS_FALSE;
    p_obj->sw_exception = BCMOS_FALSE;
    p_obj->sw_health_check_failure = BCMOS_FALSE;
    p_obj->tod_calibration_done = BCMOS_FALSE;
}

bcmos_bool bcmolt_device_auto_cfg_data_validate(
    const bcmolt_device_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_CONNECTION_COMPLETE))
    {
        /* p_obj->connection_complete can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_CONNECTION_ESTABLISHED))
    {
        /* p_obj->connection_established can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_CONNECTION_FAILURE))
    {
        /* p_obj->connection_failure can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DDR_TEST_COMPLETE))
    {
        /* p_obj->ddr_test_complete can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DEVICE_KEEP_ALIVE))
    {
        /* p_obj->device_keep_alive can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DEVICE_READY))
    {
        /* p_obj->device_ready can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_DISCONNECTION_COMPLETE))
    {
        /* p_obj->disconnection_complete can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_IMAGE_TRANSFER_COMPLETE))
    {
        /* p_obj->image_transfer_complete can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_INNI_MUX_CONFIGURATION_COMPLETED))
    {
        /* p_obj->inni_mux_configuration_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_SW_ERROR))
    {
        /* p_obj->sw_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_SW_EXCEPTION))
    {
        /* p_obj->sw_exception can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_SW_HEALTH_CHECK_FAILURE))
    {
        /* p_obj->sw_health_check_failure can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_DEVICE_AUTO_CFG_DATA_ID_TOD_CALIBRATION_DONE))
    {
        /* p_obj->tod_calibration_done can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_interface_key_set_default(
    bcmolt_erps_interface_key *p_obj)
{
    p_obj->id = (bcmolt_erps_id)0U;
}

bcmos_bool bcmolt_erps_interface_key_validate(
    const bcmolt_erps_interface_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_erps_id)4096U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 4096\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_interface_cfg_data_set_default(
    bcmolt_erps_interface_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    bcmolt_intf_ref_set_default(&p_obj->east_port);
    bcmolt_intf_ref_set_default(&p_obj->west_port);
    p_obj->control_vlan_id = (bcmolt_vlan_id)65535U;
    p_obj->east_port_state = BCMOLT_RING_PORT_STATE_UNASSIGNED;
    p_obj->west_port_state = BCMOLT_RING_PORT_STATE_UNASSIGNED;
    bcmolt_arr_intf_ref_16_set_default(&p_obj->sub_port_list);
    bcmolt_ring_port_detailed_state_set_default(&p_obj->east_port_detailed_state);
    bcmolt_ring_port_detailed_state_set_default(&p_obj->west_port_detailed_state);
}

bcmos_bool bcmolt_erps_interface_cfg_data_validate(
    const bcmolt_erps_interface_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_EAST_PORT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "east_port.");
        if (!bcmolt_intf_ref_validate(&p_obj->east_port, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_WEST_PORT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "west_port.");
        if (!bcmolt_intf_ref_validate(&p_obj->west_port, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_CONTROL_VLAN_ID))
    {
        if (p_obj->control_vlan_id > (bcmolt_vlan_id)4094U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "control_vlan_id: %u is greater than the maximum value of 4094\n", p_obj->control_vlan_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_EAST_PORT_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "east_port_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_WEST_PORT_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "west_port_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_SUB_PORT_LIST))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "sub_port_list: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_EAST_PORT_DETAILED_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "east_port_detailed_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_CFG_DATA_ID_WEST_PORT_DETAILED_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "west_port_detailed_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_interface_set_ring_port_control_data_set_default(
    bcmolt_erps_interface_set_ring_port_control_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->command = BCMOLT_ERPS_CONTROL_UNASSIGNED;
    p_obj->port = (bcmolt_ring_port)0;
}

bcmos_bool bcmolt_erps_interface_set_ring_port_control_data_validate(
    const bcmolt_erps_interface_set_ring_port_control_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID_COMMAND))
    {
        switch (p_obj->command)
        {
        case BCMOLT_ERPS_CONTROL_UNASSIGNED:
        case BCMOLT_ERPS_CONTROL_BLOCK_PORT_RX:
        case BCMOLT_ERPS_CONTROL_BLOCK_PORT_TX:
        case BCMOLT_ERPS_CONTROL_UNBLOCK_PORT_RX:
        case BCMOLT_ERPS_CONTROL_UNBLOCK_PORT_TX:
        case BCMOLT_ERPS_CONTROL_FLUSH_PORT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "command: enum value %d is unexpected\n", (int)p_obj->command);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_SET_RING_PORT_CONTROL_DATA_ID_PORT))
    {
        switch (p_obj->port)
        {
        case BCMOLT_RING_PORT_EAST:
        case BCMOLT_RING_PORT_WEST:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "port: enum value %d is unexpected\n", (int)p_obj->port);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_interface_ring_port_control_data_set_default(
    bcmolt_erps_interface_ring_port_control_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->port_id = (bcmolt_ring_port)0;
    p_obj->command = BCMOLT_ERPS_CONTROL_UNASSIGNED;
    p_obj->port_state = BCMOLT_RING_PORT_STATE_UNASSIGNED;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    bcmolt_ring_port_detailed_state_set_default(&p_obj->port_detailed_state);
}

bcmos_bool bcmolt_erps_interface_ring_port_control_data_validate(
    const bcmolt_erps_interface_ring_port_control_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_PORT_ID))
    {
        switch (p_obj->port_id)
        {
        case BCMOLT_RING_PORT_EAST:
        case BCMOLT_RING_PORT_WEST:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "port_id: enum value %d is unexpected\n", (int)p_obj->port_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_COMMAND))
    {
        switch (p_obj->command)
        {
        case BCMOLT_ERPS_CONTROL_UNASSIGNED:
        case BCMOLT_ERPS_CONTROL_BLOCK_PORT_RX:
        case BCMOLT_ERPS_CONTROL_BLOCK_PORT_TX:
        case BCMOLT_ERPS_CONTROL_UNBLOCK_PORT_RX:
        case BCMOLT_ERPS_CONTROL_UNBLOCK_PORT_TX:
        case BCMOLT_ERPS_CONTROL_FLUSH_PORT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "command: enum value %d is unexpected\n", (int)p_obj->command);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_PORT_STATE))
    {
        switch (p_obj->port_state)
        {
        case BCMOLT_RING_PORT_STATE_UNASSIGNED:
        case BCMOLT_RING_PORT_STATE_BLOCKED:
        case BCMOLT_RING_PORT_STATE_UNBLOCKED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "port_state: enum value %d is unexpected\n", (int)p_obj->port_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_RING_PORT_CONTROL_DATA_ID_PORT_DETAILED_STATE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "port_detailed_state.");
        if (!bcmolt_ring_port_detailed_state_validate(&p_obj->port_detailed_state, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_interface_set_intf_opt_data_set_default(
    bcmolt_erps_interface_set_intf_opt_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->port = (bcmolt_ring_port)0;
    p_obj->intf_opt = (bcmolt_intf_opt)0U;
}

bcmos_bool bcmolt_erps_interface_set_intf_opt_data_validate(
    const bcmolt_erps_interface_set_intf_opt_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_SET_INTF_OPT_DATA_ID_PORT))
    {
        switch (p_obj->port)
        {
        case BCMOLT_RING_PORT_EAST:
        case BCMOLT_RING_PORT_WEST:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "port: enum value %d is unexpected\n", (int)p_obj->port);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_SET_INTF_OPT_DATA_ID_INTF_OPT))
    {
        if ((p_obj->intf_opt & ~0x1) != 0)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "intf_opt: 0x%X includes invalid bits\n", p_obj->intf_opt);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_interface_port_update_data_set_default(
    bcmolt_erps_interface_port_update_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->command = (bcmolt_port_command)0;
    p_obj->port = (bcmolt_erps_port)0;
    bcmolt_intf_ref_set_default(&p_obj->intf_ref);
}

bcmos_bool bcmolt_erps_interface_port_update_data_validate(
    const bcmolt_erps_interface_port_update_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID_COMMAND))
    {
        switch (p_obj->command)
        {
        case BCMOLT_PORT_COMMAND_ADD_PORT:
        case BCMOLT_PORT_COMMAND_REMOVE_PORT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "command: enum value %d is unexpected\n", (int)p_obj->command);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID_PORT))
    {
        switch (p_obj->port)
        {
        case BCMOLT_ERPS_PORT_WEST_PORT:
        case BCMOLT_ERPS_PORT_SUB_PORT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "port: enum value %d is unexpected\n", (int)p_obj->port);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_PORT_UPDATE_DATA_ID_INTF_REF))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "intf_ref.");
        if (!bcmolt_intf_ref_validate(&p_obj->intf_ref, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_interface_set_intf_opt_complete_data_set_default(
    bcmolt_erps_interface_set_intf_opt_complete_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->port = (bcmolt_ring_port)0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_erps_interface_set_intf_opt_complete_data_validate(
    const bcmolt_erps_interface_set_intf_opt_complete_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_SET_INTF_OPT_COMPLETE_DATA_ID_PORT))
    {
        switch (p_obj->port)
        {
        case BCMOLT_RING_PORT_EAST:
        case BCMOLT_RING_PORT_WEST:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "port: enum value %d is unexpected\n", (int)p_obj->port);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_SET_INTF_OPT_COMPLETE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_interface_port_update_complete_data_set_default(
    bcmolt_erps_interface_port_update_complete_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->command = (bcmolt_port_command)0;
    p_obj->port = (bcmolt_erps_port)0;
    bcmolt_intf_ref_set_default(&p_obj->intf_ref);
    p_obj->result = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_erps_interface_port_update_complete_data_validate(
    const bcmolt_erps_interface_port_update_complete_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_COMMAND))
    {
        switch (p_obj->command)
        {
        case BCMOLT_PORT_COMMAND_ADD_PORT:
        case BCMOLT_PORT_COMMAND_REMOVE_PORT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "command: enum value %d is unexpected\n", (int)p_obj->command);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_PORT))
    {
        switch (p_obj->port)
        {
        case BCMOLT_ERPS_PORT_WEST_PORT:
        case BCMOLT_ERPS_PORT_SUB_PORT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "port: enum value %d is unexpected\n", (int)p_obj->port);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_INTF_REF))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "intf_ref.");
        if (!bcmolt_intf_ref_validate(&p_obj->intf_ref, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_PORT_UPDATE_COMPLETE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_interface_auto_cfg_data_set_default(
    bcmolt_erps_interface_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->port_update_complete = BCMOS_FALSE;
    p_obj->ring_port_control = BCMOS_FALSE;
    p_obj->set_intf_opt_complete = BCMOS_FALSE;
}

bcmos_bool bcmolt_erps_interface_auto_cfg_data_validate(
    const bcmolt_erps_interface_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID_PORT_UPDATE_COMPLETE))
    {
        /* p_obj->port_update_complete can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID_RING_PORT_CONTROL))
    {
        /* p_obj->ring_port_control can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ERPS_INTERFACE_AUTO_CFG_DATA_ID_SET_INTF_OPT_COMPLETE))
    {
        /* p_obj->set_intf_opt_complete can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_key_set_default(
    bcmolt_eth_oam_key *p_obj)
{
    p_obj->id = (bcmolt_eth_oam_id)0;
}

bcmos_bool bcmolt_eth_oam_key_validate(
    const bcmolt_eth_oam_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_eth_oam_id)127)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 127\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_cfg_data_set_default(
    bcmolt_eth_oam_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    bcmolt_intf_ref_set_default(&p_obj->intf_ref);
    bcmolt_local_mep_set_default(&p_obj->local_mep);
    bcmolt_remote_mep_set_default(&p_obj->remote_mep);
    bcmolt_meg_cfg_set_default(&p_obj->meg);
    p_obj->source_mac.u8[0] = 0x1;
    p_obj->source_mac.u8[1] = 0x2;
    p_obj->source_mac.u8[2] = 0x3;
    p_obj->source_mac.u8[3] = 0x4;
    p_obj->source_mac.u8[4] = 0x5;
    p_obj->source_mac.u8[5] = 0x6;
    p_obj->dest_mac.u8[0] = 0x1;
    p_obj->dest_mac.u8[1] = 0x80;
    p_obj->dest_mac.u8[2] = 0xC2;
    p_obj->dest_mac.u8[3] = 0x0;
    p_obj->dest_mac.u8[4] = 0x0;
    p_obj->dest_mac.u8[5] = 0x30;
    p_obj->pkt_tag_type = BCMOLT_PKT_TAG_TYPE_SINGLE_TAG;
    p_obj->o_vid = (bcmolt_vlan_id)0U;
    p_obj->o_pbits = 7;
    p_obj->o_tpid = 0x8100;
    p_obj->i_vid = (bcmolt_vlan_id)0U;
    p_obj->i_pbits = 0;
    p_obj->i_tpid = 0U;
}

bcmos_bool bcmolt_eth_oam_cfg_data_validate(
    const bcmolt_eth_oam_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_INTF_REF))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "intf_ref.");
        if (!bcmolt_intf_ref_validate(&p_obj->intf_ref, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_LOCAL_MEP))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "local_mep.");
        if (!bcmolt_local_mep_validate(&p_obj->local_mep, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_REMOTE_MEP))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "remote_mep.");
        if (!bcmolt_remote_mep_validate(&p_obj->remote_mep, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_MEG))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "meg.");
        if (!bcmolt_meg_cfg_validate(&p_obj->meg, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_SOURCE_MAC))
    {
        /* p_obj->source_mac can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_DEST_MAC))
    {
        /* p_obj->dest_mac can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_PKT_TAG_TYPE))
    {
        if ((p_obj->pkt_tag_type & ~0x1FUL) != 0)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "pkt_tag_type: 0x%X includes invalid bits\n", p_obj->pkt_tag_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_O_VID))
    {
        if (p_obj->o_vid > (bcmolt_vlan_id)4094U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "o_vid: %u is greater than the maximum value of 4094\n", p_obj->o_vid);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_O_PBITS))
    {
        if (p_obj->o_pbits > 7)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "o_pbits: %u is greater than the maximum value of 7\n", p_obj->o_pbits);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_O_TPID))
    {
        /* p_obj->o_tpid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_I_VID))
    {
        if (p_obj->i_vid > (bcmolt_vlan_id)4094U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "i_vid: %u is greater than the maximum value of 4094\n", p_obj->i_vid);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_I_PBITS))
    {
        if (p_obj->i_pbits > 7)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "i_pbits: %u is greater than the maximum value of 7\n", p_obj->i_pbits);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CFG_DATA_ID_I_TPID))
    {
        /* p_obj->i_tpid can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_ccm_event_data_set_default(
    bcmolt_eth_oam_ccm_event_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->event = BCMOLT_CCM_EVENT_UNASSIGNED;
}

bcmos_bool bcmolt_eth_oam_ccm_event_data_validate(
    const bcmolt_eth_oam_ccm_event_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_CCM_EVENT_DATA_ID_EVENT))
    {
        switch (p_obj->event)
        {
        case BCMOLT_CCM_EVENT_UNASSIGNED:
        case BCMOLT_CCM_EVENT_LOC_ON:
        case BCMOLT_CCM_EVENT_LOC_OFF:
        case BCMOLT_CCM_EVENT_RDI_SET:
        case BCMOLT_CCM_EVENT_RDI_RESET:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "event: enum value %d is unexpected\n", (int)p_obj->event);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_stats_data_set_default(
    bcmolt_eth_oam_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->ccm_tx_count = 0ULL;
    p_obj->ccm_rx_count = 0ULL;
}

bcmos_bool bcmolt_eth_oam_stats_data_validate(
    const bcmolt_eth_oam_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_TX_COUNT))
    {
        /* p_obj->ccm_tx_count can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_RX_COUNT))
    {
        /* p_obj->ccm_rx_count can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_set_mep_state_data_set_default(
    bcmolt_eth_oam_set_mep_state_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->type = BCMOLT_MEP_TYPE_MEP;
    p_obj->state = BCMOLT_CONTROL_STATE_ENABLE;
}

bcmos_bool bcmolt_eth_oam_set_mep_state_data_validate(
    const bcmolt_eth_oam_set_mep_state_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID_TYPE))
    {
        switch (p_obj->type)
        {
        case BCMOLT_MEP_TYPE_MEP:
        case BCMOLT_MEP_TYPE_RMEP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "type: enum value %d is unexpected\n", (int)p_obj->type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_SET_MEP_STATE_DATA_ID_STATE))
    {
        switch (p_obj->state)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "state: enum value %d is unexpected\n", (int)p_obj->state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_state_change_data_set_default(
    bcmolt_eth_oam_state_change_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    p_obj->old_state = BCMOLT_CONTROL_STATE_DISABLE;
    p_obj->new_state = BCMOLT_CONTROL_STATE_DISABLE;
}

bcmos_bool bcmolt_eth_oam_state_change_data_validate(
    const bcmolt_eth_oam_state_change_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID_OLD_STATE))
    {
        switch (p_obj->old_state)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "old_state: enum value %d is unexpected\n", (int)p_obj->old_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_STATE_CHANGE_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_stats_cfg_data_set_default(
    bcmolt_eth_oam_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->ccm_tx_count);
    bcmolt_stat_alarm_config_set_default(&p_obj->ccm_rx_count);
}

bcmos_bool bcmolt_eth_oam_stats_cfg_data_validate(
    const bcmolt_eth_oam_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_STATS_CFG_DATA_ID_CCM_TX_COUNT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ccm_tx_count.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->ccm_tx_count, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_STATS_CFG_DATA_ID_CCM_RX_COUNT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ccm_rx_count.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->ccm_rx_count, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_stats_alarm_raised_data_set_default(
    bcmolt_eth_oam_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_TX_COUNT;
}

bcmos_bool bcmolt_eth_oam_stats_alarm_raised_data_validate(
    const bcmolt_eth_oam_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_TX_COUNT:
        case BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_RX_COUNT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_stats_alarm_cleared_data_set_default(
    bcmolt_eth_oam_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_TX_COUNT;
}

bcmos_bool bcmolt_eth_oam_stats_alarm_cleared_data_validate(
    const bcmolt_eth_oam_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_TX_COUNT:
        case BCMOLT_ETH_OAM_STATS_DATA_ID_CCM_RX_COUNT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_eth_oam_auto_cfg_data_set_default(
    bcmolt_eth_oam_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->ccm_event = BCMOS_FALSE;
    p_obj->state_change = BCMOS_FALSE;
    p_obj->stats_alarm_cleared = BCMOS_FALSE;
    p_obj->stats_alarm_raised = BCMOS_FALSE;
}

bcmos_bool bcmolt_eth_oam_auto_cfg_data_validate(
    const bcmolt_eth_oam_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_CCM_EVENT))
    {
        /* p_obj->ccm_event can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_STATE_CHANGE))
    {
        /* p_obj->state_change can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED))
    {
        /* p_obj->stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ETH_OAM_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED))
    {
        /* p_obj->stats_alarm_raised can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_flow_cfg_data_set_default(
    bcmolt_flow_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_intf_ref_set_default(&p_obj->ingress_intf);
    bcmolt_intf_ref_set_default(&p_obj->egress_intf);
    p_obj->onu_id = (bcmolt_onu_id)65535U;
    p_obj->svc_port_id = (bcmolt_service_port_id)65535UL;
    bcmolt_classifier_set_default(&p_obj->classifier);
    p_obj->priority = 10U;
    bcmolt_action_set_default(&p_obj->action);
    p_obj->group_id = (bcmolt_group_id)65535U;
    bcmolt_egress_qos_set_default(&p_obj->egress_qos);
    p_obj->state = BCMOLT_FLOW_STATE_NOT_CONFIGURED;
    p_obj->local_switching = BCMOLT_CONTROL_STATE_DISABLE;
    p_obj->statistics = BCMOLT_CONTROL_STATE_DISABLE;
    p_obj->cookie = (bcmolt_cookie)0ULL;
    p_obj->mac_table_miss_action = BCMOLT_MAC_TABLE_MISS_ACTION_FLOOD;
    p_obj->policer_profile = (bcmolt_policer_profile_id)65535U;
    p_obj->um_forwarding = BCMOLT_UM_FWRD_STATE_DISABLE;
    p_obj->bc_forwarding = BCMOLT_BC_FWRD_STATE_ENABLE;
    bcmolt_arr_src_binding_info_16_set_default(&p_obj->src_bindings);
}

bcmos_bool bcmolt_flow_cfg_data_validate(
    const bcmolt_flow_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_INGRESS_INTF))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ingress_intf.");
        if (!bcmolt_intf_ref_validate(&p_obj->ingress_intf, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_EGRESS_INTF))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "egress_intf.");
        if (!bcmolt_intf_ref_validate(&p_obj->egress_intf, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_ONU_ID))
    {
        /* p_obj->onu_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_SVC_PORT_ID))
    {
        if (p_obj->svc_port_id > (bcmolt_service_port_id)65536UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "svc_port_id: %u is greater than the maximum value of 65536\n", p_obj->svc_port_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_CLASSIFIER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "classifier.");
        if (!bcmolt_classifier_validate(&p_obj->classifier, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_PRIORITY))
    {
        /* p_obj->priority can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_ACTION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "action.");
        if (!bcmolt_action_validate(&p_obj->action, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_GROUP_ID))
    {
        /* p_obj->group_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_EGRESS_QOS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "egress_qos.");
        if (!bcmolt_egress_qos_validate(&p_obj->egress_qos, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_STATE))
    {
        switch (p_obj->state)
        {
        case BCMOLT_FLOW_STATE_NOT_CONFIGURED:
        case BCMOLT_FLOW_STATE_DISABLE:
        case BCMOLT_FLOW_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "state: enum value %d is unexpected\n", (int)p_obj->state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_LOCAL_SWITCHING))
    {
        switch (p_obj->local_switching)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "local_switching: enum value %d is unexpected\n", (int)p_obj->local_switching);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_STATISTICS))
    {
        switch (p_obj->statistics)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "statistics: enum value %d is unexpected\n", (int)p_obj->statistics);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_COOKIE))
    {
        /* p_obj->cookie can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_MAC_TABLE_MISS_ACTION))
    {
        switch (p_obj->mac_table_miss_action)
        {
        case BCMOLT_MAC_TABLE_MISS_ACTION_FLOOD:
        case BCMOLT_MAC_TABLE_MISS_ACTION_DROP:
        case BCMOLT_MAC_TABLE_MISS_ACTION_ERPS_DEFAULT:
        case BCMOLT_MAC_TABLE_MISS_ACTION_FLOOD_TO_FLOWS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "mac_table_miss_action: enum value %d is unexpected\n", (int)p_obj->mac_table_miss_action);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_POLICER_PROFILE))
    {
        if (p_obj->policer_profile < (bcmolt_policer_profile_id)1U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "policer_profile: %u is less than the minimum value of 1\n", p_obj->policer_profile);
            return BCMOS_FALSE;
        }
        if (p_obj->policer_profile > (bcmolt_policer_profile_id)1023U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "policer_profile: %u is greater than the maximum value of 1023\n", p_obj->policer_profile);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_UM_FORWARDING))
    {
        switch (p_obj->um_forwarding)
        {
        case BCMOLT_UM_FWRD_STATE_DISABLE:
        case BCMOLT_UM_FWRD_STATE_ENABLE:
        case BCMOLT_UM_FWRD_STATE_IGMP_ICMPV6:
        case BCMOLT_UM_FWRD_STATE_FLOOD_TO_FLOWS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "um_forwarding: enum value %d is unexpected\n", (int)p_obj->um_forwarding);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_BC_FORWARDING))
    {
        switch (p_obj->bc_forwarding)
        {
        case BCMOLT_BC_FWRD_STATE_DISABLE:
        case BCMOLT_BC_FWRD_STATE_ENABLE:
        case BCMOLT_BC_FWRD_STATE_FLOOD_TO_FLOWS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "bc_forwarding: enum value %d is unexpected\n", (int)p_obj->bc_forwarding);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_CFG_DATA_ID_SRC_BINDINGS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "src_bindings: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_flow_key_set_default(
    bcmolt_flow_key *p_obj)
{
    p_obj->flow_id = (bcmolt_flow_id)0U;
    p_obj->flow_type = BCMOLT_FLOW_TYPE_UPSTREAM;
}

bcmos_bool bcmolt_flow_key_validate(
    const bcmolt_flow_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->flow_id can't be invalid. */
    switch (p_obj->flow_type)
    {
    case BCMOLT_FLOW_TYPE_UPSTREAM:
    case BCMOLT_FLOW_TYPE_DOWNSTREAM:
    case BCMOLT_FLOW_TYPE_MULTICAST:
    case BCMOLT_FLOW_TYPE_XCONNECT:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "flow_type: enum value %d is unexpected\n", (int)p_obj->flow_type);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_flow_stats_data_set_default(
    bcmolt_flow_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rx_packets = 0ULL;
    p_obj->rx_bytes = 0ULL;
    p_obj->tx_packets = 0ULL;
    p_obj->tx_bytes = 0ULL;
}

bcmos_bool bcmolt_flow_stats_data_validate(
    const bcmolt_flow_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_DATA_ID_RX_PACKETS))
    {
        /* p_obj->rx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_DATA_ID_TX_PACKETS))
    {
        /* p_obj->tx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_DATA_ID_TX_BYTES))
    {
        /* p_obj->tx_bytes can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_flow_send_eth_packet_data_set_default(
    bcmolt_flow_send_eth_packet_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_bin_str_set_default(&p_obj->buffer);
    p_obj->inject_type = BCMOLT_INJECT_TYPE_INJECT_AT_EGRESS;
    bcmolt_intf_ref_set_default(&p_obj->ingress_intf);
    p_obj->svc_port_id = (bcmolt_service_port_id)65535UL;
}

bcmos_bool bcmolt_flow_send_eth_packet_data_validate(
    const bcmolt_flow_send_eth_packet_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "buffer.");
        if (!bcmolt_bin_str_validate(&p_obj->buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_INJECT_TYPE))
    {
        switch (p_obj->inject_type)
        {
        case BCMOLT_INJECT_TYPE_INJECT_AT_EGRESS:
        case BCMOLT_INJECT_TYPE_INJECT_AT_INGRESS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "inject_type: enum value %d is unexpected\n", (int)p_obj->inject_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_INGRESS_INTF))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ingress_intf.");
        if (!bcmolt_intf_ref_validate(&p_obj->ingress_intf, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_SEND_ETH_PACKET_DATA_ID_SVC_PORT_ID))
    {
        if (p_obj->svc_port_id > (bcmolt_service_port_id)65536UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "svc_port_id: %u is greater than the maximum value of 65536\n", p_obj->svc_port_id);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_flow_src_binding_update_data_set_default(
    bcmolt_flow_src_binding_update_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->command = BCMOLT_BINDING_COMMAND_ADD;
    bcmolt_src_binding_info_set_default(&p_obj->src_binding);
}

bcmos_bool bcmolt_flow_src_binding_update_data_validate(
    const bcmolt_flow_src_binding_update_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_SRC_BINDING_UPDATE_DATA_ID_COMMAND))
    {
        switch (p_obj->command)
        {
        case BCMOLT_BINDING_COMMAND_ADD:
        case BCMOLT_BINDING_COMMAND_REMOVE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "command: enum value %d is unexpected\n", (int)p_obj->command);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_SRC_BINDING_UPDATE_DATA_ID_SRC_BINDING))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "src_binding.");
        if (!bcmolt_src_binding_info_validate(&p_obj->src_binding, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_flow_stats_cfg_data_set_default(
    bcmolt_flow_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bytes);
}

bcmos_bool bcmolt_flow_stats_cfg_data_validate(
    const bcmolt_flow_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_CFG_DATA_ID_RX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_CFG_DATA_ID_TX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_CFG_DATA_ID_TX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_flow_stats_alarm_raised_data_set_default(
    bcmolt_flow_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_FLOW_STATS_DATA_ID_RX_PACKETS;
}

bcmos_bool bcmolt_flow_stats_alarm_raised_data_validate(
    const bcmolt_flow_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_FLOW_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_FLOW_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_FLOW_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_FLOW_STATS_DATA_ID_TX_BYTES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_flow_stats_alarm_cleared_data_set_default(
    bcmolt_flow_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_FLOW_STATS_DATA_ID_RX_PACKETS;
}

bcmos_bool bcmolt_flow_stats_alarm_cleared_data_validate(
    const bcmolt_flow_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_FLOW_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_FLOW_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_FLOW_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_FLOW_STATS_DATA_ID_TX_BYTES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_flow_auto_cfg_data_set_default(
    bcmolt_flow_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stats_alarm_cleared = BCMOS_FALSE;
    p_obj->stats_alarm_raised = BCMOS_FALSE;
}

bcmos_bool bcmolt_flow_auto_cfg_data_validate(
    const bcmolt_flow_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED))
    {
        /* p_obj->stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_FLOW_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED))
    {
        /* p_obj->stats_alarm_raised can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_gpio_key_set_default(
    bcmolt_gpio_key *p_obj)
{
    p_obj->device_id = (bcmolt_odid)0;
    p_obj->gpio_id = BCMOLT_GPIO_PIN_PIN0;
}

bcmos_bool bcmolt_gpio_key_validate(
    const bcmolt_gpio_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->device_id can't be invalid. */
    switch (p_obj->gpio_id)
    {
    case BCMOLT_GPIO_PIN_PIN0:
    case BCMOLT_GPIO_PIN_PIN1:
    case BCMOLT_GPIO_PIN_PIN2:
    case BCMOLT_GPIO_PIN_PIN3:
    case BCMOLT_GPIO_PIN_PIN4:
    case BCMOLT_GPIO_PIN_PIN5:
    case BCMOLT_GPIO_PIN_PIN6:
    case BCMOLT_GPIO_PIN_PIN7:
    case BCMOLT_GPIO_PIN_PIN8:
    case BCMOLT_GPIO_PIN_PIN9:
    case BCMOLT_GPIO_PIN_PIN10:
    case BCMOLT_GPIO_PIN_PIN11:
    case BCMOLT_GPIO_PIN_PIN12:
    case BCMOLT_GPIO_PIN_PIN13:
    case BCMOLT_GPIO_PIN_PIN14:
    case BCMOLT_GPIO_PIN_PIN15:
    case BCMOLT_GPIO_PIN_PIN16:
    case BCMOLT_GPIO_PIN_PIN17:
    case BCMOLT_GPIO_PIN_PIN18:
    case BCMOLT_GPIO_PIN_PIN19:
    case BCMOLT_GPIO_PIN_PIN20:
    case BCMOLT_GPIO_PIN_PIN21:
    case BCMOLT_GPIO_PIN_PIN22:
    case BCMOLT_GPIO_PIN_PIN23:
    case BCMOLT_GPIO_PIN_PIN24:
    case BCMOLT_GPIO_PIN_PIN25:
    case BCMOLT_GPIO_PIN_PIN26:
    case BCMOLT_GPIO_PIN_PIN27:
    case BCMOLT_GPIO_PIN_PIN28:
    case BCMOLT_GPIO_PIN_PIN29:
    case BCMOLT_GPIO_PIN_PIN30:
    case BCMOLT_GPIO_PIN_PIN31:
    case BCMOLT_GPIO_PIN_PIN32:
    case BCMOLT_GPIO_PIN_PIN33:
    case BCMOLT_GPIO_PIN_PIN34:
    case BCMOLT_GPIO_PIN_PIN35:
    case BCMOLT_GPIO_PIN_PIN36:
    case BCMOLT_GPIO_PIN_PIN37:
    case BCMOLT_GPIO_PIN_PIN38:
    case BCMOLT_GPIO_PIN_PIN39:
    case BCMOLT_GPIO_PIN_PIN40:
    case BCMOLT_GPIO_PIN_PIN41:
    case BCMOLT_GPIO_PIN_PIN42:
    case BCMOLT_GPIO_PIN_PIN43:
    case BCMOLT_GPIO_PIN_PIN44:
    case BCMOLT_GPIO_PIN_PIN45:
    case BCMOLT_GPIO_PIN_PIN46:
    case BCMOLT_GPIO_PIN_PIN47:
    case BCMOLT_GPIO_PIN_PIN48:
    case BCMOLT_GPIO_PIN_PIN49:
    case BCMOLT_GPIO_PIN_PIN50:
    case BCMOLT_GPIO_PIN_PIN51:
    case BCMOLT_GPIO_PIN_PIN52:
    case BCMOLT_GPIO_PIN_PIN53:
    case BCMOLT_GPIO_PIN_PIN54:
    case BCMOLT_GPIO_PIN_PIN55:
    case BCMOLT_GPIO_PIN_PIN56:
    case BCMOLT_GPIO_PIN_PIN57:
    case BCMOLT_GPIO_PIN_PIN58:
    case BCMOLT_GPIO_PIN_PIN59:
    case BCMOLT_GPIO_PIN_PIN60:
    case BCMOLT_GPIO_PIN_PIN61:
    case BCMOLT_GPIO_PIN_PIN62:
    case BCMOLT_GPIO_PIN_PIN63:
    case BCMOLT_GPIO_PIN_PIN64:
    case BCMOLT_GPIO_PIN_PIN65:
    case BCMOLT_GPIO_PIN_PIN66:
    case BCMOLT_GPIO_PIN_PIN67:
    case BCMOLT_GPIO_PIN_PIN68:
    case BCMOLT_GPIO_PIN_PIN69:
    case BCMOLT_GPIO_PIN_PIN70:
    case BCMOLT_GPIO_PIN_PIN71:
    case BCMOLT_GPIO_PIN_PIN72:
    case BCMOLT_GPIO_PIN_PIN73:
    case BCMOLT_GPIO_PIN_PIN74:
    case BCMOLT_GPIO_PIN_PIN75:
    case BCMOLT_GPIO_PIN_PIN76:
    case BCMOLT_GPIO_PIN_PIN77:
    case BCMOLT_GPIO_PIN_PIN78:
    case BCMOLT_GPIO_PIN_PIN79:
    case BCMOLT_GPIO_PIN_PIN80:
    case BCMOLT_GPIO_PIN_PIN81:
    case BCMOLT_GPIO_PIN_PIN82:
    case BCMOLT_GPIO_PIN_PIN83:
    case BCMOLT_GPIO_PIN_PIN84:
    case BCMOLT_GPIO_PIN_PIN85:
    case BCMOLT_GPIO_PIN_PIN86:
    case BCMOLT_GPIO_PIN_PIN87:
    case BCMOLT_GPIO_PIN_PIN88:
    case BCMOLT_GPIO_PIN_PIN89:
    case BCMOLT_GPIO_PIN_PIN90:
    case BCMOLT_GPIO_PIN_PIN91:
    case BCMOLT_GPIO_PIN_PIN92:
    case BCMOLT_GPIO_PIN_PIN93:
    case BCMOLT_GPIO_PIN_PIN94:
    case BCMOLT_GPIO_PIN_PIN95:
    case BCMOLT_GPIO_PIN_PIN96:
    case BCMOLT_GPIO_PIN_PIN97:
    case BCMOLT_GPIO_PIN_PIN98:
    case BCMOLT_GPIO_PIN_PIN99:
    case BCMOLT_GPIO_PIN_PIN100:
    case BCMOLT_GPIO_PIN_PIN101:
    case BCMOLT_GPIO_PIN_PIN102:
    case BCMOLT_GPIO_PIN_PIN103:
    case BCMOLT_GPIO_PIN_PIN104:
    case BCMOLT_GPIO_PIN_PIN105:
    case BCMOLT_GPIO_PIN_PIN106:
    case BCMOLT_GPIO_PIN_PIN107:
    case BCMOLT_GPIO_PIN_PIN108:
    case BCMOLT_GPIO_PIN_PIN109:
    case BCMOLT_GPIO_PIN_PIN110:
    case BCMOLT_GPIO_PIN_PIN111:
    case BCMOLT_GPIO_PIN_PIN112:
    case BCMOLT_GPIO_PIN_PIN113:
    case BCMOLT_GPIO_PIN_PIN114:
    case BCMOLT_GPIO_PIN_PIN115:
    case BCMOLT_GPIO_PIN_PIN116:
    case BCMOLT_GPIO_PIN_PIN117:
    case BCMOLT_GPIO_PIN_PIN118:
    case BCMOLT_GPIO_PIN_PIN119:
    case BCMOLT_GPIO_PIN_PIN120:
    case BCMOLT_GPIO_PIN_PIN121:
    case BCMOLT_GPIO_PIN_PIN122:
    case BCMOLT_GPIO_PIN_PIN123:
    case BCMOLT_GPIO_PIN_PIN124:
    case BCMOLT_GPIO_PIN_PIN125:
    case BCMOLT_GPIO_PIN_PIN126:
    case BCMOLT_GPIO_PIN_PIN127:
    case BCMOLT_GPIO_PIN_PIN128:
    case BCMOLT_GPIO_PIN_PIN129:
    case BCMOLT_GPIO_PIN_PIN130:
    case BCMOLT_GPIO_PIN_PIN131:
    case BCMOLT_GPIO_PIN_PIN132:
    case BCMOLT_GPIO_PIN_PIN133:
    case BCMOLT_GPIO_PIN_PIN134:
    case BCMOLT_GPIO_PIN_PIN135:
    case BCMOLT_GPIO_PIN_PIN136:
    case BCMOLT_GPIO_PIN_PIN137:
    case BCMOLT_GPIO_PIN_PIN138:
    case BCMOLT_GPIO_PIN_PIN139:
    case BCMOLT_GPIO_PIN_PIN140:
    case BCMOLT_GPIO_PIN_PIN141:
    case BCMOLT_GPIO_PIN_PIN142:
    case BCMOLT_GPIO_PIN_PIN143:
    case BCMOLT_GPIO_PIN_PIN144:
    case BCMOLT_GPIO_PIN_PIN145:
    case BCMOLT_GPIO_PIN_PIN146:
    case BCMOLT_GPIO_PIN_PIN147:
    case BCMOLT_GPIO_PIN_PIN148:
    case BCMOLT_GPIO_PIN_PIN149:
    case BCMOLT_GPIO_PIN_PIN150:
    case BCMOLT_GPIO_PIN_PIN151:
    case BCMOLT_GPIO_PIN_PIN152:
    case BCMOLT_GPIO_PIN_PIN153:
    case BCMOLT_GPIO_PIN_PIN154:
    case BCMOLT_GPIO_PIN_PIN155:
    case BCMOLT_GPIO_PIN_PIN156:
    case BCMOLT_GPIO_PIN_PIN157:
    case BCMOLT_GPIO_PIN_PIN158:
    case BCMOLT_GPIO_PIN_PIN159:
    case BCMOLT_GPIO_PIN_PIN160:
    case BCMOLT_GPIO_PIN_PIN161:
    case BCMOLT_GPIO_PIN_PIN162:
    case BCMOLT_GPIO_PIN_PIN163:
    case BCMOLT_GPIO_PIN_PIN164:
    case BCMOLT_GPIO_PIN_PIN165:
    case BCMOLT_GPIO_PIN_PIN166:
    case BCMOLT_GPIO_PIN_PIN167:
    case BCMOLT_GPIO_PIN_PIN168:
    case BCMOLT_GPIO_PIN_PIN169:
    case BCMOLT_GPIO_PIN_PIN170:
    case BCMOLT_GPIO_PIN_PIN171:
    case BCMOLT_GPIO_PIN_PIN172:
    case BCMOLT_GPIO_PIN_PIN173:
    case BCMOLT_GPIO_PIN_PIN174:
    case BCMOLT_GPIO_PIN_PIN175:
    case BCMOLT_GPIO_PIN_PIN176:
    case BCMOLT_GPIO_PIN_PIN177:
    case BCMOLT_GPIO_PIN_PIN178:
    case BCMOLT_GPIO_PIN_PIN179:
    case BCMOLT_GPIO_PIN_PIN180:
    case BCMOLT_GPIO_PIN_PIN181:
    case BCMOLT_GPIO_PIN_PIN182:
    case BCMOLT_GPIO_PIN_PIN183:
    case BCMOLT_GPIO_PIN_PIN184:
    case BCMOLT_GPIO_PIN_PIN185:
    case BCMOLT_GPIO_PIN_PIN186:
    case BCMOLT_GPIO_PIN_PIN187:
    case BCMOLT_GPIO_PIN_PIN188:
    case BCMOLT_GPIO_PIN_PIN189:
    case BCMOLT_GPIO_PIN_PIN190:
    case BCMOLT_GPIO_PIN_PIN191:
    case BCMOLT_GPIO_PIN_PIN192:
    case BCMOLT_GPIO_PIN_PIN193:
    case BCMOLT_GPIO_PIN_PIN194:
    case BCMOLT_GPIO_PIN_PIN195:
    case BCMOLT_GPIO_PIN_PIN196:
    case BCMOLT_GPIO_PIN_PIN197:
    case BCMOLT_GPIO_PIN_PIN198:
    case BCMOLT_GPIO_PIN_PIN199:
    case BCMOLT_GPIO_PIN_PIN200:
    case BCMOLT_GPIO_PIN_PIN201:
    case BCMOLT_GPIO_PIN_PIN202:
    case BCMOLT_GPIO_PIN_PIN203:
    case BCMOLT_GPIO_PIN_PIN204:
    case BCMOLT_GPIO_PIN_PIN205:
    case BCMOLT_GPIO_PIN_UNCONFIGURED:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "gpio_id: enum value %d is unexpected\n", (int)p_obj->gpio_id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_gpio_cfg_data_set_default(
    bcmolt_gpio_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->direction = BCMOLT_GPIO_PIN_DIR_INPUT;
    p_obj->value = BCMOLT_GPIO_VALUE_CLEAR;
}

bcmos_bool bcmolt_gpio_cfg_data_validate(
    const bcmolt_gpio_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GPIO_CFG_DATA_ID_DIRECTION))
    {
        switch (p_obj->direction)
        {
        case BCMOLT_GPIO_PIN_DIR_INPUT:
        case BCMOLT_GPIO_PIN_DIR_OUTPUT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "direction: enum value %d is unexpected\n", (int)p_obj->direction);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GPIO_CFG_DATA_ID_VALUE))
    {
        switch (p_obj->value)
        {
        case BCMOLT_GPIO_VALUE_CLEAR:
        case BCMOLT_GPIO_VALUE_SET:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "value: enum value %d is unexpected\n", (int)p_obj->value);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_group_cfg_data_set_default(
    bcmolt_group_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_group_member_info_list_u8_set_default(&p_obj->members);
    p_obj->cookie = (bcmolt_cookie)0ULL;
    p_obj->type = BCMOLT_GROUP_TYPE_NONE;
    p_obj->state = BCMOLT_GROUP_STATE_NOT_CONFIGURED;
    bcmolt_action_set_default(&p_obj->action);
}

bcmos_bool bcmolt_group_cfg_data_validate(
    const bcmolt_group_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GROUP_CFG_DATA_ID_MEMBERS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "members: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GROUP_CFG_DATA_ID_COOKIE))
    {
        /* p_obj->cookie can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GROUP_CFG_DATA_ID_TYPE))
    {
        switch (p_obj->type)
        {
        case BCMOLT_GROUP_TYPE_NONE:
        case BCMOLT_GROUP_TYPE_MULTICAST:
        case BCMOLT_GROUP_TYPE_N_TO_1:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "type: enum value %d is unexpected\n", (int)p_obj->type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GROUP_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GROUP_CFG_DATA_ID_ACTION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "action.");
        if (!bcmolt_action_validate(&p_obj->action, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_group_key_set_default(
    bcmolt_group_key *p_obj)
{
    p_obj->id = (bcmolt_group_id)0U;
}

bcmos_bool bcmolt_group_key_validate(
    const bcmolt_group_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->id can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_group_members_update_data_set_default(
    bcmolt_group_members_update_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_group_members_update_command_set_default(&p_obj->members_cmd);
}

bcmos_bool bcmolt_group_members_update_data_validate(
    const bcmolt_group_members_update_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GROUP_MEMBERS_UPDATE_DATA_ID_MEMBERS_CMD))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "members_cmd.");
        if (!bcmolt_group_members_update_command_validate(&p_obj->members_cmd, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_group_complete_members_update_data_set_default(
    bcmolt_group_complete_members_update_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_NONE;
}

bcmos_bool bcmolt_group_complete_members_update_data_validate(
    const bcmolt_group_complete_members_update_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GROUP_COMPLETE_MEMBERS_UPDATE_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_NONE:
        case BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_PARM:
        case BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_INTERNAL:
        case BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_SW:
        case BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_MAC:
        case BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_SVC_PORT_MISS_MATCH:
        case BCMOLT_GROUP_MEMBER_UPDATE_FAIL_REASON_QOS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_group_auto_cfg_data_set_default(
    bcmolt_group_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->complete_members_update = BCMOS_FALSE;
}

bcmos_bool bcmolt_group_auto_cfg_data_validate(
    const bcmolt_group_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_GROUP_AUTO_CFG_DATA_ID_COMPLETE_MEMBERS_UPDATE))
    {
        /* p_obj->complete_members_update can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_host_log_key_set_default(
    bcmolt_host_log_key *p_obj)
{
    bcmolt_str_100_set_default(&p_obj->name);
}

bcmos_bool bcmolt_host_log_key_validate(
    const bcmolt_host_log_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    int prefix_len = bcmolt_string_append(p_err_details, "name.");
    if (!bcmolt_str_100_validate(&p_obj->name, p_err, p_err_details))
    {
        return BCMOS_FALSE;
    }
    bcmolt_string_rewind(p_err_details, prefix_len);
    return BCMOS_TRUE;
}

void bcmolt_host_log_cfg_data_set_default(
    bcmolt_host_log_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->type = BCMOLT_LOG_TYPE_NONE;
    p_obj->style = BCMOLT_LOG_STYLE_NORMAL;
    bcmolt_log_level_per_file_set_default(&p_obj->level);
    bcmolt_log_level_msg_count_set_default(&p_obj->msg_count);
    p_obj->lost_msg_count = 0UL;
}

bcmos_bool bcmolt_host_log_cfg_data_validate(
    const bcmolt_host_log_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_CFG_DATA_ID_TYPE))
    {
        switch (p_obj->type)
        {
        case BCMOLT_LOG_TYPE_NONE:
        case BCMOLT_LOG_TYPE_PRINT:
        case BCMOLT_LOG_TYPE_SAVE:
        case BCMOLT_LOG_TYPE_BOTH:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "type: enum value %d is unexpected\n", (int)p_obj->type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_CFG_DATA_ID_STYLE))
    {
        switch (p_obj->style)
        {
        case BCMOLT_LOG_STYLE_NORMAL:
        case BCMOLT_LOG_STYLE_BOLD:
        case BCMOLT_LOG_STYLE_UNDERLINE:
        case BCMOLT_LOG_STYLE_BLINK:
        case BCMOLT_LOG_STYLE_REVERSE_VIDEO:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "style: enum value %d is unexpected\n", (int)p_obj->style);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_CFG_DATA_ID_LEVEL))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "level.");
        if (!bcmolt_log_level_per_file_validate(&p_obj->level, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_CFG_DATA_ID_MSG_COUNT))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "msg_count: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_CFG_DATA_ID_LOST_MSG_COUNT))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "lost_msg_count: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_host_log_file_key_set_default(
    bcmolt_host_log_file_key *p_obj)
{
    p_obj->file_id = BCMOLT_HOST_LOG_FILE_ID_SRAM;
}

bcmos_bool bcmolt_host_log_file_key_validate(
    const bcmolt_host_log_file_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    switch (p_obj->file_id)
    {
    case BCMOLT_HOST_LOG_FILE_ID_SRAM:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "file_id: enum value %d is unexpected\n", (int)p_obj->file_id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_host_log_file_cfg_data_set_default(
    bcmolt_host_log_file_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->wrap_around = BCMOS_TRUE;
    p_obj->clear_after_read = BCMOS_FALSE;
    p_obj->msg_count = 0UL;
    p_obj->msgs_read = 0UL;
    p_obj->msgs_remaining = 0UL;
    bcmolt_str_2048_set_default(&p_obj->buffer);
}

bcmos_bool bcmolt_host_log_file_cfg_data_validate(
    const bcmolt_host_log_file_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_WRAP_AROUND))
    {
        /* p_obj->wrap_around can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_CLEAR_AFTER_READ))
    {
        /* p_obj->clear_after_read can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_MSG_COUNT))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "msg_count: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_MSGS_READ))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "msgs_read: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_MSGS_REMAINING))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "msgs_remaining: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_HOST_LOG_FILE_CFG_DATA_ID_BUFFER))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "buffer: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_inband_mgmt_channel_cfg_data_set_default(
    bcmolt_inband_mgmt_channel_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_intf_ref_set_default(&p_obj->nni_intf);
    p_obj->policer_profile = (bcmolt_policer_profile_id)65535U;
    p_obj->nic_intf_id = (bcmolt_interface_id)0U;
    p_obj->vlan_id = 0U;
    bcmos_mac_address_init(&p_obj->nic_card_mac);
    p_obj->action = BCMOLT_INBAND_MGMT_ACTION_TYPE_NONE;
    p_obj->state = BCMOLT_INBAND_MGMT_STATE_NOT_CONFIGURED;
}

bcmos_bool bcmolt_inband_mgmt_channel_cfg_data_validate(
    const bcmolt_inband_mgmt_channel_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_NNI_INTF))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "nni_intf.");
        if (!bcmolt_intf_ref_validate(&p_obj->nni_intf, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_POLICER_PROFILE))
    {
        if (p_obj->policer_profile < (bcmolt_policer_profile_id)1U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "policer_profile: %u is less than the minimum value of 1\n", p_obj->policer_profile);
            return BCMOS_FALSE;
        }
        if (p_obj->policer_profile > (bcmolt_policer_profile_id)1023U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "policer_profile: %u is greater than the maximum value of 1023\n", p_obj->policer_profile);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_NIC_INTF_ID))
    {
        /* p_obj->nic_intf_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_VLAN_ID))
    {
        if (p_obj->vlan_id < 1U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "vlan_id: %u is less than the minimum value of 1\n", p_obj->vlan_id);
            return BCMOS_FALSE;
        }
        if (p_obj->vlan_id > 4094U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "vlan_id: %u is greater than the maximum value of 4094\n", p_obj->vlan_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_NIC_CARD_MAC))
    {
        /* p_obj->nic_card_mac can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_ACTION))
    {
        switch (p_obj->action)
        {
        case BCMOLT_INBAND_MGMT_ACTION_TYPE_NONE:
        case BCMOLT_INBAND_MGMT_ACTION_TYPE_REMOVE_ADD_OUTER_TAG:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "action: enum value %d is unexpected\n", (int)p_obj->action);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INBAND_MGMT_CHANNEL_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_inband_mgmt_channel_key_set_default(
    bcmolt_inband_mgmt_channel_key *p_obj)
{
    p_obj->id = (bcmolt_inband_mgmt_instance_id)0;
}

bcmos_bool bcmolt_inband_mgmt_channel_key_validate(
    const bcmolt_inband_mgmt_channel_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->id can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_key_set_default(
    bcmolt_internal_nni_key *p_obj)
{
    p_obj->pon_ni = (bcmolt_pon_ni)0;
}

bcmos_bool bcmolt_internal_nni_key_validate(
    const bcmolt_internal_nni_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->pon_ni > (bcmolt_pon_ni)15)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "pon_ni: %u is greater than the maximum value of 15\n", p_obj->pon_ni);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_cfg_data_set_default(
    bcmolt_internal_nni_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmos_mac_address_init(&p_obj->mac_address);
    p_obj->active_nni = BCMOLT_NNI_CONNECTION_PRIMARY;
    bcmolt_nni_link_status_set_default(&p_obj->status);
    bcmolt_nni_link_status_set_default(&p_obj->backup_status);
    p_obj->loopback_type = BCMOLT_NNI_LOOPBACK_TYPE_NONE;
    p_obj->status_polling_interval_ms = 50UL;
    p_obj->redundancy = BCMOLT_INTERNAL_NNI_REDUNDANCY_NONE;
    p_obj->flow_control = BCMOLT_CONTROL_STATE_ENABLE;
    bcmolt_inband_config_data_set_default(&p_obj->inband_mgmt);
    bcmolt_trap_config_set_default(&p_obj->trap_config);
    p_obj->oversubscription = BCMOS_FALSE;
    bcmolt_prbs_generator_config_set_default(&p_obj->prbs_generator);
    bcmolt_prbs_checker_config_set_default(&p_obj->prbs_checker);
    bcmolt_prbs_status_set_default(&p_obj->prbs_status);
    p_obj->nni_swap_delay_us = 320UL;
    p_obj->flow_control_mode = BCMOLT_FLOW_CONTROL_MODE_FLOW_CONTROL_NONE;
}

bcmos_bool bcmolt_internal_nni_cfg_data_validate(
    const bcmolt_internal_nni_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_MAC_ADDRESS))
    {
        /* p_obj->mac_address can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_ACTIVE_NNI))
    {
        switch (p_obj->active_nni)
        {
        case BCMOLT_NNI_CONNECTION_PRIMARY:
        case BCMOLT_NNI_CONNECTION_BACKUP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "active_nni: enum value %d is unexpected\n", (int)p_obj->active_nni);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_STATUS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_BACKUP_STATUS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "backup_status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_LOOPBACK_TYPE))
    {
        switch (p_obj->loopback_type)
        {
        case BCMOLT_NNI_LOOPBACK_TYPE_NONE:
        case BCMOLT_NNI_LOOPBACK_TYPE_LINE:
        case BCMOLT_NNI_LOOPBACK_TYPE_REMOTE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "loopback_type: enum value %d is unexpected\n", (int)p_obj->loopback_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_STATUS_POLLING_INTERVAL_MS))
    {
        if (p_obj->status_polling_interval_ms > 2000000UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status_polling_interval_ms: %u is greater than the maximum value of 2000000\n", p_obj->status_polling_interval_ms);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_REDUNDANCY))
    {
        switch (p_obj->redundancy)
        {
        case BCMOLT_INTERNAL_NNI_REDUNDANCY_NONE:
        case BCMOLT_INTERNAL_NNI_REDUNDANCY_MANUAL:
        case BCMOLT_INTERNAL_NNI_REDUNDANCY_AUTOSWITCH:
        case BCMOLT_INTERNAL_NNI_REDUNDANCY_GPIO:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "redundancy: enum value %d is unexpected\n", (int)p_obj->redundancy);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_FLOW_CONTROL))
    {
        switch (p_obj->flow_control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "flow_control: enum value %d is unexpected\n", (int)p_obj->flow_control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_INBAND_MGMT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "inband_mgmt.");
        if (!bcmolt_inband_config_data_validate(&p_obj->inband_mgmt, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_TRAP_CONFIG))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "trap_config.");
        if (!bcmolt_trap_config_validate(&p_obj->trap_config, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_OVERSUBSCRIPTION))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "oversubscription: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_PRBS_GENERATOR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "prbs_generator.");
        if (!bcmolt_prbs_generator_config_validate(&p_obj->prbs_generator, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_PRBS_CHECKER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "prbs_checker.");
        if (!bcmolt_prbs_checker_config_validate(&p_obj->prbs_checker, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_PRBS_STATUS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "prbs_status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_NNI_SWAP_DELAY_US))
    {
        if (p_obj->nni_swap_delay_us > 300000UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "nni_swap_delay_us: %u is greater than the maximum value of 300000\n", p_obj->nni_swap_delay_us);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_CFG_DATA_ID_FLOW_CONTROL_MODE))
    {
        switch (p_obj->flow_control_mode)
        {
        case BCMOLT_FLOW_CONTROL_MODE_FLOW_CONTROL_NONE:
        case BCMOLT_FLOW_CONTROL_MODE_PAUSE:
        case BCMOLT_FLOW_CONTROL_MODE_PFC:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "flow_control_mode: enum value %d is unexpected\n", (int)p_obj->flow_control_mode);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_status_changed_data_set_default(
    bcmolt_internal_nni_status_changed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->new_status = BCMOLT_STATUS_OFF;
    p_obj->link = BCMOLT_NNI_CONNECTION_PRIMARY;
    p_obj->previous_active = BCMOLT_NNI_CONNECTION_PRIMARY;
    p_obj->new_active = BCMOLT_NNI_CONNECTION_PRIMARY;
}

bcmos_bool bcmolt_internal_nni_status_changed_data_validate(
    const bcmolt_internal_nni_status_changed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_NEW_STATUS))
    {
        switch (p_obj->new_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_status: enum value %d is unexpected\n", (int)p_obj->new_status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_LINK))
    {
        switch (p_obj->link)
        {
        case BCMOLT_NNI_CONNECTION_PRIMARY:
        case BCMOLT_NNI_CONNECTION_BACKUP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "link: enum value %d is unexpected\n", (int)p_obj->link);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_PREVIOUS_ACTIVE))
    {
        switch (p_obj->previous_active)
        {
        case BCMOLT_NNI_CONNECTION_PRIMARY:
        case BCMOLT_NNI_CONNECTION_BACKUP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "previous_active: enum value %d is unexpected\n", (int)p_obj->previous_active);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_STATUS_CHANGED_DATA_ID_NEW_ACTIVE))
    {
        switch (p_obj->new_active)
        {
        case BCMOLT_NNI_CONNECTION_PRIMARY:
        case BCMOLT_NNI_CONNECTION_BACKUP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_active: enum value %d is unexpected\n", (int)p_obj->new_active);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_nni_stats_data_set_default(
    bcmolt_internal_nni_nni_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rx_good_frames = 0ULL;
    p_obj->rx_control_frames = 0ULL;
    p_obj->rx_pause_frames = 0ULL;
    p_obj->rx_pfc_frames = 0ULL;
    p_obj->rx_unsupported_opcode = 0ULL;
    p_obj->rx_unsupported_da = 0ULL;
    p_obj->rx_alignment_errors = 0ULL;
    p_obj->rx_length_out_of_range = 0ULL;
    p_obj->rx_code_errors = 0ULL;
    p_obj->rx_jabber_frames = 0ULL;
    p_obj->rx_mtu_check_errors = 0ULL;
    p_obj->rx_promiscuous_frames = 0ULL;
    p_obj->rx_vlan_frames = 0ULL;
    p_obj->rx_double_vlan_frames = 0ULL;
    p_obj->rx_truncated_frames = 0ULL;
    p_obj->rx_undersize_frames = 0ULL;
    p_obj->rx_fragmented_frames = 0ULL;
    p_obj->tx_good_frames = 0ULL;
    p_obj->tx_pause_frames = 0ULL;
    p_obj->tx_pfc_frames = 0ULL;
    p_obj->tx_jabber_frames = 0ULL;
    p_obj->tx_control_frames = 0ULL;
    p_obj->tx_oversize_frames = 0ULL;
    p_obj->tx_fragmented_frames = 0ULL;
    p_obj->tx_error_frames = 0ULL;
    p_obj->tx_vlan_frames = 0ULL;
    p_obj->tx_double_vlan_frames = 0ULL;
    p_obj->tx_runt_frames = 0ULL;
    p_obj->tx_underrun_frames = 0ULL;
}

bcmos_bool bcmolt_internal_nni_nni_stats_data_validate(
    const bcmolt_internal_nni_nni_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_GOOD_FRAMES))
    {
        /* p_obj->rx_good_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CONTROL_FRAMES))
    {
        /* p_obj->rx_control_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PAUSE_FRAMES))
    {
        /* p_obj->rx_pause_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PFC_FRAMES))
    {
        /* p_obj->rx_pfc_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_OPCODE))
    {
        /* p_obj->rx_unsupported_opcode can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_DA))
    {
        /* p_obj->rx_unsupported_da can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_ALIGNMENT_ERRORS))
    {
        /* p_obj->rx_alignment_errors can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_LENGTH_OUT_OF_RANGE))
    {
        /* p_obj->rx_length_out_of_range can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CODE_ERRORS))
    {
        /* p_obj->rx_code_errors can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_JABBER_FRAMES))
    {
        /* p_obj->rx_jabber_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_MTU_CHECK_ERRORS))
    {
        /* p_obj->rx_mtu_check_errors can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PROMISCUOUS_FRAMES))
    {
        /* p_obj->rx_promiscuous_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_VLAN_FRAMES))
    {
        /* p_obj->rx_vlan_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_DOUBLE_VLAN_FRAMES))
    {
        /* p_obj->rx_double_vlan_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_TRUNCATED_FRAMES))
    {
        /* p_obj->rx_truncated_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNDERSIZE_FRAMES))
    {
        /* p_obj->rx_undersize_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_FRAGMENTED_FRAMES))
    {
        /* p_obj->rx_fragmented_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_GOOD_FRAMES))
    {
        /* p_obj->tx_good_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PAUSE_FRAMES))
    {
        /* p_obj->tx_pause_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PFC_FRAMES))
    {
        /* p_obj->tx_pfc_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_JABBER_FRAMES))
    {
        /* p_obj->tx_jabber_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_CONTROL_FRAMES))
    {
        /* p_obj->tx_control_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_OVERSIZE_FRAMES))
    {
        /* p_obj->tx_oversize_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_FRAGMENTED_FRAMES))
    {
        /* p_obj->tx_fragmented_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_ERROR_FRAMES))
    {
        /* p_obj->tx_error_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_VLAN_FRAMES))
    {
        /* p_obj->tx_vlan_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_DOUBLE_VLAN_FRAMES))
    {
        /* p_obj->tx_double_vlan_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_RUNT_FRAMES))
    {
        /* p_obj->tx_runt_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_UNDERRUN_FRAMES))
    {
        /* p_obj->tx_underrun_frames can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_enet_stats_data_set_default(
    bcmolt_internal_nni_enet_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rx_bytes = 0ULL;
    p_obj->rx_frames = 0ULL;
    p_obj->rx_frames_64 = 0ULL;
    p_obj->rx_frames_65_127 = 0ULL;
    p_obj->rx_frames_128_255 = 0ULL;
    p_obj->rx_frames_256_511 = 0ULL;
    p_obj->rx_frames_512_1023 = 0ULL;
    p_obj->rx_frames_1024_1518 = 0ULL;
    p_obj->rx_frames_1519_2047 = 0ULL;
    p_obj->rx_frames_2048_4095 = 0ULL;
    p_obj->rx_frames_4096_9216 = 0ULL;
    p_obj->rx_frames_9217_16383 = 0ULL;
    p_obj->rx_broadcast_frames = 0ULL;
    p_obj->rx_data_bytes = 0ULL;
    p_obj->rx_multicast_frames = 0ULL;
    p_obj->rx_unicast_frames = 0ULL;
    p_obj->rx_abort_frames = 0ULL;
    p_obj->rx_fcs_error = 0ULL;
    p_obj->rx_oversize_error = 0ULL;
    p_obj->rx_runt_error = 0ULL;
    p_obj->tx_bytes = 0ULL;
    p_obj->tx_frames = 0ULL;
    p_obj->tx_frames_64 = 0ULL;
    p_obj->tx_frames_65_127 = 0ULL;
    p_obj->tx_frames_128_255 = 0ULL;
    p_obj->tx_frames_256_511 = 0ULL;
    p_obj->tx_frames_512_1023 = 0ULL;
    p_obj->tx_frames_1024_1518 = 0ULL;
    p_obj->tx_frames_1519_2047 = 0ULL;
    p_obj->tx_frames_2048_4095 = 0ULL;
    p_obj->tx_frames_4096_9216 = 0ULL;
    p_obj->tx_frames_9217_16383 = 0ULL;
    p_obj->tx_broadcast_frames = 0ULL;
    p_obj->tx_data_bytes = 0ULL;
    p_obj->tx_multicast_frames = 0ULL;
    p_obj->tx_unicast_frames = 0ULL;
    p_obj->tx_abort_frames = 0ULL;
    p_obj->tx_fcs_error = 0ULL;
}

bcmos_bool bcmolt_internal_nni_enet_stats_data_validate(
    const bcmolt_internal_nni_enet_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES))
    {
        /* p_obj->rx_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_64))
    {
        /* p_obj->rx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_65_127))
    {
        /* p_obj->rx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_128_255))
    {
        /* p_obj->rx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_256_511))
    {
        /* p_obj->rx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_512_1023))
    {
        /* p_obj->rx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1024_1518))
    {
        /* p_obj->rx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1519_2047))
    {
        /* p_obj->rx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_2048_4095))
    {
        /* p_obj->rx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_4096_9216))
    {
        /* p_obj->rx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_9217_16383))
    {
        /* p_obj->rx_frames_9217_16383 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BROADCAST_FRAMES))
    {
        /* p_obj->rx_broadcast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_DATA_BYTES))
    {
        /* p_obj->rx_data_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_MULTICAST_FRAMES))
    {
        /* p_obj->rx_multicast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_UNICAST_FRAMES))
    {
        /* p_obj->rx_unicast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_ABORT_FRAMES))
    {
        /* p_obj->rx_abort_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FCS_ERROR))
    {
        /* p_obj->rx_fcs_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_OVERSIZE_ERROR))
    {
        /* p_obj->rx_oversize_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_RUNT_ERROR))
    {
        /* p_obj->rx_runt_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BYTES))
    {
        /* p_obj->tx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES))
    {
        /* p_obj->tx_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_64))
    {
        /* p_obj->tx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_65_127))
    {
        /* p_obj->tx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_128_255))
    {
        /* p_obj->tx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_256_511))
    {
        /* p_obj->tx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_512_1023))
    {
        /* p_obj->tx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1024_1518))
    {
        /* p_obj->tx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1519_2047))
    {
        /* p_obj->tx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_2048_4095))
    {
        /* p_obj->tx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_4096_9216))
    {
        /* p_obj->tx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_9217_16383))
    {
        /* p_obj->tx_frames_9217_16383 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BROADCAST_FRAMES))
    {
        /* p_obj->tx_broadcast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_DATA_BYTES))
    {
        /* p_obj->tx_data_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_MULTICAST_FRAMES))
    {
        /* p_obj->tx_multicast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_UNICAST_FRAMES))
    {
        /* p_obj->tx_unicast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_ABORT_FRAMES))
    {
        /* p_obj->tx_abort_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FCS_ERROR))
    {
        /* p_obj->tx_fcs_error can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_packet_captured_data_set_default(
    bcmolt_internal_nni_packet_captured_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->packet_size = 0UL;
    bcmolt_bin_str_set_default(&p_obj->buffer);
}

bcmos_bool bcmolt_internal_nni_packet_captured_data_validate(
    const bcmolt_internal_nni_packet_captured_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID_PACKET_SIZE))
    {
        /* p_obj->packet_size can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_PACKET_CAPTURED_DATA_ID_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "buffer.");
        if (!bcmolt_bin_str_validate(&p_obj->buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_send_eth_packet_data_set_default(
    bcmolt_internal_nni_send_eth_packet_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_bin_str_set_default(&p_obj->buffer);
}

bcmos_bool bcmolt_internal_nni_send_eth_packet_data_validate(
    const bcmolt_internal_nni_send_eth_packet_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_SEND_ETH_PACKET_DATA_ID_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "buffer.");
        if (!bcmolt_bin_str_validate(&p_obj->buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_nni_stats_cfg_data_set_default(
    bcmolt_internal_nni_nni_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_good_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_control_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_pause_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_pfc_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_unsupported_opcode);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_unsupported_da);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_alignment_errors);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_length_out_of_range);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_code_errors);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_jabber_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_mtu_check_errors);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_promiscuous_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_vlan_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_double_vlan_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_truncated_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_undersize_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_fragmented_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_good_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_pause_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_pfc_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_jabber_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_control_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_oversize_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_fragmented_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_error_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_vlan_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_double_vlan_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_runt_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_underrun_frames);
}

bcmos_bool bcmolt_internal_nni_nni_stats_cfg_data_validate(
    const bcmolt_internal_nni_nni_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_GOOD_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_good_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_good_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_CONTROL_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_control_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_control_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_PAUSE_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_pause_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_pause_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_PFC_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_pfc_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_pfc_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_UNSUPPORTED_OPCODE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_unsupported_opcode.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_unsupported_opcode, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_UNSUPPORTED_DA))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_unsupported_da.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_unsupported_da, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_ALIGNMENT_ERRORS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_alignment_errors.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_alignment_errors, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_LENGTH_OUT_OF_RANGE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_length_out_of_range.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_length_out_of_range, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_CODE_ERRORS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_code_errors.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_code_errors, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_JABBER_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_jabber_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_jabber_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_MTU_CHECK_ERRORS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_mtu_check_errors.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_mtu_check_errors, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_PROMISCUOUS_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_promiscuous_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_promiscuous_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_VLAN_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_vlan_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_vlan_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_DOUBLE_VLAN_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_double_vlan_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_double_vlan_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_TRUNCATED_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_truncated_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_truncated_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_UNDERSIZE_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_undersize_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_undersize_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_RX_FRAGMENTED_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_fragmented_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_fragmented_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_GOOD_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_good_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_good_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_PAUSE_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_pause_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_pause_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_PFC_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_pfc_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_pfc_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_JABBER_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_jabber_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_jabber_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_CONTROL_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_control_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_control_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_OVERSIZE_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_oversize_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_oversize_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_FRAGMENTED_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_fragmented_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_fragmented_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_ERROR_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_error_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_error_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_VLAN_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_vlan_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_vlan_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_DOUBLE_VLAN_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_double_vlan_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_double_vlan_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_RUNT_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_runt_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_runt_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_CFG_DATA_ID_TX_UNDERRUN_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_underrun_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_underrun_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_nni_stats_alarm_raised_data_set_default(
    bcmolt_internal_nni_nni_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_GOOD_FRAMES;
}

bcmos_bool bcmolt_internal_nni_nni_stats_alarm_raised_data_validate(
    const bcmolt_internal_nni_nni_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_GOOD_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CONTROL_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PAUSE_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PFC_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_OPCODE:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_DA:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_ALIGNMENT_ERRORS:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_LENGTH_OUT_OF_RANGE:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CODE_ERRORS:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_JABBER_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_MTU_CHECK_ERRORS:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PROMISCUOUS_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_VLAN_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_DOUBLE_VLAN_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_TRUNCATED_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNDERSIZE_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_FRAGMENTED_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_GOOD_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PAUSE_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PFC_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_JABBER_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_CONTROL_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_OVERSIZE_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_FRAGMENTED_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_ERROR_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_VLAN_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_DOUBLE_VLAN_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_RUNT_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_UNDERRUN_FRAMES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_nni_stats_alarm_cleared_data_set_default(
    bcmolt_internal_nni_nni_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_GOOD_FRAMES;
}

bcmos_bool bcmolt_internal_nni_nni_stats_alarm_cleared_data_validate(
    const bcmolt_internal_nni_nni_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_NNI_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_GOOD_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CONTROL_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PAUSE_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PFC_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_OPCODE:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNSUPPORTED_DA:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_ALIGNMENT_ERRORS:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_LENGTH_OUT_OF_RANGE:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_CODE_ERRORS:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_JABBER_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_MTU_CHECK_ERRORS:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_PROMISCUOUS_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_VLAN_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_DOUBLE_VLAN_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_TRUNCATED_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_UNDERSIZE_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_RX_FRAGMENTED_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_GOOD_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PAUSE_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_PFC_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_JABBER_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_CONTROL_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_OVERSIZE_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_FRAGMENTED_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_ERROR_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_VLAN_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_DOUBLE_VLAN_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_RUNT_FRAMES:
        case BCMOLT_INTERNAL_NNI_NNI_STATS_DATA_ID_TX_UNDERRUN_FRAMES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_enet_stats_cfg_data_set_default(
    bcmolt_internal_nni_enet_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_9217_16383);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_broadcast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_data_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_multicast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_unicast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_abort_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_fcs_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_oversize_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_runt_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_9217_16383);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_broadcast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_data_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_multicast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_unicast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_abort_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_fcs_error);
}

bcmos_bool bcmolt_internal_nni_enet_stats_cfg_data_validate(
    const bcmolt_internal_nni_enet_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_BROADCAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_broadcast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_broadcast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_DATA_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_data_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_data_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_MULTICAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_multicast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_multicast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_UNICAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_unicast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_unicast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_ABORT_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_abort_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_abort_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_FCS_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_fcs_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_fcs_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_OVERSIZE_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_oversize_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_oversize_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_RX_RUNT_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_runt_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_runt_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_BROADCAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_broadcast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_broadcast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_DATA_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_data_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_data_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_MULTICAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_multicast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_multicast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_UNICAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_unicast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_unicast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_ABORT_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_abort_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_abort_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_CFG_DATA_ID_TX_FCS_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_fcs_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_fcs_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_enet_stats_alarm_raised_data_set_default(
    bcmolt_internal_nni_enet_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_internal_nni_enet_stats_alarm_raised_data_validate(
    const bcmolt_internal_nni_enet_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BROADCAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_DATA_BYTES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_MULTICAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_UNICAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_ABORT_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FCS_ERROR:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_OVERSIZE_ERROR:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_RUNT_ERROR:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_9217_16383:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BROADCAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_DATA_BYTES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_MULTICAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_UNICAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_ABORT_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FCS_ERROR:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_enet_stats_alarm_cleared_data_set_default(
    bcmolt_internal_nni_enet_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_internal_nni_enet_stats_alarm_cleared_data_validate(
    const bcmolt_internal_nni_enet_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_ENET_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_BROADCAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_DATA_BYTES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_MULTICAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_UNICAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_ABORT_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_FCS_ERROR:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_OVERSIZE_ERROR:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_RX_RUNT_ERROR:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FRAMES_9217_16383:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_BROADCAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_DATA_BYTES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_MULTICAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_UNICAST_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_ABORT_FRAMES:
        case BCMOLT_INTERNAL_NNI_ENET_STATS_DATA_ID_TX_FCS_ERROR:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_internal_nni_auto_cfg_data_set_default(
    bcmolt_internal_nni_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->enet_stats_alarm_cleared = BCMOS_FALSE;
    p_obj->enet_stats_alarm_raised = BCMOS_FALSE;
    p_obj->nni_stats_alarm_cleared = BCMOS_FALSE;
    p_obj->nni_stats_alarm_raised = BCMOS_FALSE;
    p_obj->packet_captured = BCMOS_FALSE;
    p_obj->status_changed = BCMOS_FALSE;
    p_obj->swap_completed = BCMOS_FALSE;
}

bcmos_bool bcmolt_internal_nni_auto_cfg_data_validate(
    const bcmolt_internal_nni_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_ENET_STATS_ALARM_CLEARED))
    {
        /* p_obj->enet_stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_ENET_STATS_ALARM_RAISED))
    {
        /* p_obj->enet_stats_alarm_raised can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_NNI_STATS_ALARM_CLEARED))
    {
        /* p_obj->nni_stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_NNI_STATS_ALARM_RAISED))
    {
        /* p_obj->nni_stats_alarm_raised can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_PACKET_CAPTURED))
    {
        /* p_obj->packet_captured can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_STATUS_CHANGED))
    {
        /* p_obj->status_changed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_INTERNAL_NNI_AUTO_CFG_DATA_ID_SWAP_COMPLETED))
    {
        /* p_obj->swap_completed can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_key_set_default(
    bcmolt_itupon_alloc_key *p_obj)
{
    p_obj->pon_ni = (bcmolt_pon_ni)0;
    p_obj->alloc_id = (bcmolt_alloc_id)0U;
}

bcmos_bool bcmolt_itupon_alloc_key_validate(
    const bcmolt_itupon_alloc_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->pon_ni > (bcmolt_pon_ni)15)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "pon_ni: %u is greater than the maximum value of 15\n", p_obj->pon_ni);
        return BCMOS_FALSE;
    }
    if (p_obj->alloc_id > (bcmolt_alloc_id)16383U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "alloc_id: %u is greater than the maximum value of 16383\n", p_obj->alloc_id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_cfg_data_set_default(
    bcmolt_itupon_alloc_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_ACTIVATION_STATE_NOT_CONFIGURED;
    bcmolt_pon_alloc_sla_set_default(&p_obj->sla);
    p_obj->onu_id = (bcmolt_onu_id)0U;
    p_obj->collect_stats = BCMOS_FALSE;
    p_obj->onu_tcont_max_queue_size = 0UL;
    p_obj->latency_sensitive = BCMOS_FALSE;
    p_obj->enable_latency_stats = BCMOS_FALSE;
}

bcmos_bool bcmolt_itupon_alloc_cfg_data_validate(
    const bcmolt_itupon_alloc_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_SLA))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "sla.");
        if (!bcmolt_pon_alloc_sla_validate(&p_obj->sla, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_ONU_ID))
    {
        /* p_obj->onu_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_COLLECT_STATS))
    {
        /* p_obj->collect_stats can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_ONU_TCONT_MAX_QUEUE_SIZE))
    {
        if (p_obj->onu_tcont_max_queue_size > 16777215UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "onu_tcont_max_queue_size: %u is greater than the maximum value of 16777215\n", p_obj->onu_tcont_max_queue_size);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_LATENCY_SENSITIVE))
    {
        /* p_obj->latency_sensitive can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_CFG_DATA_ID_ENABLE_LATENCY_STATS))
    {
        /* p_obj->enable_latency_stats can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_configuration_completed_data_set_default(
    bcmolt_itupon_alloc_configuration_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->new_state = BCMOLT_ACTIVATION_STATE_NOT_CONFIGURED;
}

bcmos_bool bcmolt_itupon_alloc_configuration_completed_data_validate(
    const bcmolt_itupon_alloc_configuration_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_CONFIGURATION_COMPLETED_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_ACTIVATION_STATE_NOT_CONFIGURED:
        case BCMOLT_ACTIVATION_STATE_INACTIVE:
        case BCMOLT_ACTIVATION_STATE_PROCESSING:
        case BCMOLT_ACTIVATION_STATE_ACTIVE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_get_stats_data_set_default(
    bcmolt_itupon_alloc_get_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->num_of_cycles = 1UL;
}

bcmos_bool bcmolt_itupon_alloc_get_stats_data_validate(
    const bcmolt_itupon_alloc_get_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_GET_STATS_DATA_ID_NUM_OF_CYCLES))
    {
        if (p_obj->num_of_cycles < 1UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "num_of_cycles: %u is less than the minimum value of 1\n", p_obj->num_of_cycles);
            return BCMOS_FALSE;
        }
        if (p_obj->num_of_cycles > 10000UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "num_of_cycles: %u is greater than the maximum value of 10000\n", p_obj->num_of_cycles);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_get_alloc_stats_completed_data_set_default(
    bcmolt_itupon_alloc_get_alloc_stats_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->average_nsr_used = 0UL;
    p_obj->average_nsr_allocated = 0UL;
    p_obj->average_sr_report = 0UL;
}

bcmos_bool bcmolt_itupon_alloc_get_alloc_stats_completed_data_validate(
    const bcmolt_itupon_alloc_get_alloc_stats_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_AVERAGE_NSR_USED))
    {
        /* p_obj->average_nsr_used can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_AVERAGE_NSR_ALLOCATED))
    {
        /* p_obj->average_nsr_allocated can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_GET_ALLOC_STATS_COMPLETED_DATA_ID_AVERAGE_SR_REPORT))
    {
        /* p_obj->average_sr_report can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_set_state_data_set_default(
    bcmolt_itupon_alloc_set_state_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_ALLOC_OPERATION_ACTIVATE;
}

bcmos_bool bcmolt_itupon_alloc_set_state_data_validate(
    const bcmolt_itupon_alloc_set_state_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_SET_STATE_DATA_ID_STATE))
    {
        switch (p_obj->state)
        {
        case BCMOLT_ALLOC_OPERATION_ACTIVATE:
        case BCMOLT_ALLOC_OPERATION_DEACTIVATE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "state: enum value %d is unexpected\n", (int)p_obj->state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_stats_data_set_default(
    bcmolt_itupon_alloc_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rx_bytes = 0ULL;
}

bcmos_bool bcmolt_itupon_alloc_stats_data_validate(
    const bcmolt_itupon_alloc_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data_set_default(
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->tm_used = 0ULL;
    p_obj->tm_allocated = 0ULL;
    p_obj->bufocc = 0ULL;
    p_obj->used_cbr = 0ULL;
    p_obj->used_guaranteed_above_cbr = 0ULL;
    p_obj->used_additional = 0ULL;
}

bcmos_bool bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data_validate(
    const bcmolt_itupon_alloc_alloc_onu_accumulated_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED))
    {
        /* p_obj->tm_used can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_ALLOCATED))
    {
        /* p_obj->tm_allocated can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_BUFOCC))
    {
        /* p_obj->bufocc can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_CBR))
    {
        /* p_obj->used_cbr can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_GUARANTEED_ABOVE_CBR))
    {
        /* p_obj->used_guaranteed_above_cbr can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_ADDITIONAL))
    {
        /* p_obj->used_additional can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_latency_stats_data_set_default(
    bcmolt_itupon_alloc_latency_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->onu_tcont_max_queue_size = 0ULL;
    p_obj->allocation_busy = 0ULL;
    p_obj->latency_bucket_0_100_usec = 0ULL;
    p_obj->latency_bucket_100_200_usec = 0ULL;
    p_obj->latency_bucket_200_300_usec = 0ULL;
    p_obj->latency_bucket_300_400_usec = 0ULL;
    p_obj->latency_bucket_400_600_usec = 0ULL;
    p_obj->latency_bucket_600_800_usec = 0ULL;
    p_obj->latency_bucket_800_1000_usec = 0ULL;
    p_obj->latency_bucket_1_3_msec = 0ULL;
    p_obj->latency_bucket_3_5_msec = 0ULL;
    p_obj->latency_bucket_5_10_msec = 0ULL;
    p_obj->latency_bucket_more_than_10_msec = 0ULL;
}

bcmos_bool bcmolt_itupon_alloc_latency_stats_data_validate(
    const bcmolt_itupon_alloc_latency_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_ONU_TCONT_MAX_QUEUE_SIZE))
    {
        /* p_obj->onu_tcont_max_queue_size can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_ALLOCATION_BUSY))
    {
        /* p_obj->allocation_busy can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_0_100_USEC))
    {
        /* p_obj->latency_bucket_0_100_usec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_100_200_USEC))
    {
        /* p_obj->latency_bucket_100_200_usec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_200_300_USEC))
    {
        /* p_obj->latency_bucket_200_300_usec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_300_400_USEC))
    {
        /* p_obj->latency_bucket_300_400_usec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_400_600_USEC))
    {
        /* p_obj->latency_bucket_400_600_usec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_600_800_USEC))
    {
        /* p_obj->latency_bucket_600_800_usec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_800_1000_USEC))
    {
        /* p_obj->latency_bucket_800_1000_usec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_1_3_MSEC))
    {
        /* p_obj->latency_bucket_1_3_msec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_3_5_MSEC))
    {
        /* p_obj->latency_bucket_3_5_msec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_5_10_MSEC))
    {
        /* p_obj->latency_bucket_5_10_msec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_MORE_THAN_10_MSEC))
    {
        /* p_obj->latency_bucket_more_than_10_msec can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_stats_cfg_data_set_default(
    bcmolt_itupon_alloc_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
}

bcmos_bool bcmolt_itupon_alloc_stats_cfg_data_validate(
    const bcmolt_itupon_alloc_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_stats_alarm_raised_data_set_default(
    bcmolt_itupon_alloc_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ITUPON_ALLOC_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_itupon_alloc_stats_alarm_raised_data_validate(
    const bcmolt_itupon_alloc_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ITUPON_ALLOC_STATS_DATA_ID_RX_BYTES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_stats_alarm_cleared_data_set_default(
    bcmolt_itupon_alloc_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ITUPON_ALLOC_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_itupon_alloc_stats_alarm_cleared_data_validate(
    const bcmolt_itupon_alloc_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ITUPON_ALLOC_STATS_DATA_ID_RX_BYTES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data_set_default(
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->tm_used);
    bcmolt_stat_alarm_config_set_default(&p_obj->tm_allocated);
    bcmolt_stat_alarm_config_set_default(&p_obj->bufocc);
    bcmolt_stat_alarm_config_set_default(&p_obj->used_cbr);
    bcmolt_stat_alarm_config_set_default(&p_obj->used_guaranteed_above_cbr);
    bcmolt_stat_alarm_config_set_default(&p_obj->used_additional);
}

bcmos_bool bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data_validate(
    const bcmolt_itupon_alloc_alloc_onu_accumulated_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_TM_USED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tm_used.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tm_used, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_TM_ALLOCATED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tm_allocated.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tm_allocated, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_BUFOCC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "bufocc.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->bufocc, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_USED_CBR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "used_cbr.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->used_cbr, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_USED_GUARANTEED_ABOVE_CBR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "used_guaranteed_above_cbr.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->used_guaranteed_above_cbr, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_USED_ADDITIONAL))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "used_additional.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->used_additional, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data_set_default(
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED;
}

bcmos_bool bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data_validate(
    const bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_ALLOCATED:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_BUFOCC:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_CBR:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_GUARANTEED_ABOVE_CBR:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_ADDITIONAL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data_set_default(
    bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED;
}

bcmos_bool bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data_validate(
    const bcmolt_itupon_alloc_alloc_onu_accumulated_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_ALLOCATED:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_BUFOCC:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_CBR:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_GUARANTEED_ABOVE_CBR:
        case BCMOLT_ITUPON_ALLOC_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_ADDITIONAL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_latency_stats_cfg_data_set_default(
    bcmolt_itupon_alloc_latency_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->onu_tcont_max_queue_size);
    bcmolt_stat_alarm_config_set_default(&p_obj->allocation_busy);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_0_100_usec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_100_200_usec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_200_300_usec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_300_400_usec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_400_600_usec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_600_800_usec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_800_1000_usec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_1_3_msec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_3_5_msec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_5_10_msec);
    bcmolt_stat_alarm_config_set_default(&p_obj->latency_bucket_more_than_10_msec);
}

bcmos_bool bcmolt_itupon_alloc_latency_stats_cfg_data_validate(
    const bcmolt_itupon_alloc_latency_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_ONU_TCONT_MAX_QUEUE_SIZE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "onu_tcont_max_queue_size.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->onu_tcont_max_queue_size, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_ALLOCATION_BUSY))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "allocation_busy.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->allocation_busy, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_0_100_USEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_0_100_usec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_0_100_usec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_100_200_USEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_100_200_usec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_100_200_usec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_200_300_USEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_200_300_usec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_200_300_usec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_300_400_USEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_300_400_usec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_300_400_usec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_400_600_USEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_400_600_usec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_400_600_usec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_600_800_USEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_600_800_usec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_600_800_usec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_800_1000_USEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_800_1000_usec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_800_1000_usec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_1_3_MSEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_1_3_msec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_1_3_msec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_3_5_MSEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_3_5_msec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_3_5_msec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_5_10_MSEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_5_10_msec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_5_10_msec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_CFG_DATA_ID_LATENCY_BUCKET_MORE_THAN_10_MSEC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "latency_bucket_more_than_10_msec.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->latency_bucket_more_than_10_msec, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_latency_stats_alarm_raised_data_set_default(
    bcmolt_itupon_alloc_latency_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_ONU_TCONT_MAX_QUEUE_SIZE;
}

bcmos_bool bcmolt_itupon_alloc_latency_stats_alarm_raised_data_validate(
    const bcmolt_itupon_alloc_latency_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_ONU_TCONT_MAX_QUEUE_SIZE:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_ALLOCATION_BUSY:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_0_100_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_100_200_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_200_300_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_300_400_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_400_600_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_600_800_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_800_1000_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_1_3_MSEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_3_5_MSEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_5_10_MSEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_MORE_THAN_10_MSEC:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_latency_stats_alarm_cleared_data_set_default(
    bcmolt_itupon_alloc_latency_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_ONU_TCONT_MAX_QUEUE_SIZE;
}

bcmos_bool bcmolt_itupon_alloc_latency_stats_alarm_cleared_data_validate(
    const bcmolt_itupon_alloc_latency_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_LATENCY_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_ONU_TCONT_MAX_QUEUE_SIZE:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_ALLOCATION_BUSY:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_0_100_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_100_200_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_200_300_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_300_400_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_400_600_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_600_800_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_800_1000_USEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_1_3_MSEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_3_5_MSEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_5_10_MSEC:
        case BCMOLT_ITUPON_ALLOC_LATENCY_STATS_DATA_ID_LATENCY_BUCKET_MORE_THAN_10_MSEC:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_alloc_auto_cfg_data_set_default(
    bcmolt_itupon_alloc_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alloc_onu_accumulated_stats_alarm_cleared = BCMOS_FALSE;
    p_obj->alloc_onu_accumulated_stats_alarm_raised = BCMOS_FALSE;
    p_obj->configuration_completed = BCMOS_FALSE;
    p_obj->get_alloc_stats_completed = BCMOS_FALSE;
    p_obj->latency_stats_alarm_cleared = BCMOS_FALSE;
    p_obj->latency_stats_alarm_raised = BCMOS_FALSE;
    p_obj->stats_alarm_cleared = BCMOS_FALSE;
    p_obj->stats_alarm_raised = BCMOS_FALSE;
}

bcmos_bool bcmolt_itupon_alloc_auto_cfg_data_validate(
    const bcmolt_itupon_alloc_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_ALLOC_ONU_ACCUMULATED_STATS_ALARM_CLEARED))
    {
        /* p_obj->alloc_onu_accumulated_stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_ALLOC_ONU_ACCUMULATED_STATS_ALARM_RAISED))
    {
        /* p_obj->alloc_onu_accumulated_stats_alarm_raised can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_CONFIGURATION_COMPLETED))
    {
        /* p_obj->configuration_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_GET_ALLOC_STATS_COMPLETED))
    {
        /* p_obj->get_alloc_stats_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_LATENCY_STATS_ALARM_CLEARED))
    {
        /* p_obj->latency_stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_LATENCY_STATS_ALARM_RAISED))
    {
        /* p_obj->latency_stats_alarm_raised can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED))
    {
        /* p_obj->stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_ALLOC_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED))
    {
        /* p_obj->stats_alarm_raised can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_gem_key_set_default(
    bcmolt_itupon_gem_key *p_obj)
{
    p_obj->pon_ni = (bcmolt_pon_ni)0;
    p_obj->gem_port_id = (bcmolt_gem_port_id)0UL;
}

bcmos_bool bcmolt_itupon_gem_key_validate(
    const bcmolt_itupon_gem_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->pon_ni > (bcmolt_pon_ni)15)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "pon_ni: %u is greater than the maximum value of 15\n", p_obj->pon_ni);
        return BCMOS_FALSE;
    }
    if (p_obj->gem_port_id > (bcmolt_gem_port_id)65536UL)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "gem_port_id: %u is greater than the maximum value of 65536\n", p_obj->gem_port_id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_gem_cfg_data_set_default(
    bcmolt_itupon_gem_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_gem_port_configuration_set_default(&p_obj->configuration);
    p_obj->onu_id = (bcmolt_onu_id)0U;
    p_obj->state = BCMOLT_ACTIVATION_STATE_NOT_CONFIGURED;
    p_obj->encryption_mode = BCMOLT_CONTROL_STATE_DISABLE;
    p_obj->upstream_destination_queue = BCMOLT_US_GEM_PORT_DESTINATION_DATA;
    p_obj->control = BCMOLT_CONTROL_STATE_DISABLE;
    p_obj->mac_table_entry_limit = 0U;
    bcmolt_debug_flow_config_set_default(&p_obj->debug_flow_config);
}

bcmos_bool bcmolt_itupon_gem_cfg_data_validate(
    const bcmolt_itupon_gem_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CFG_DATA_ID_CONFIGURATION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "configuration.");
        if (!bcmolt_gem_port_configuration_validate(&p_obj->configuration, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CFG_DATA_ID_ONU_ID))
    {
        /* p_obj->onu_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CFG_DATA_ID_ENCRYPTION_MODE))
    {
        switch (p_obj->encryption_mode)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "encryption_mode: enum value %d is unexpected\n", (int)p_obj->encryption_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CFG_DATA_ID_UPSTREAM_DESTINATION_QUEUE))
    {
        switch (p_obj->upstream_destination_queue)
        {
        case BCMOLT_US_GEM_PORT_DESTINATION_DATA:
        case BCMOLT_US_GEM_PORT_DESTINATION_CPU:
        case BCMOLT_US_GEM_PORT_DESTINATION_OMCI:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "upstream_destination_queue: enum value %d is unexpected\n", (int)p_obj->upstream_destination_queue);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CFG_DATA_ID_CONTROL))
    {
        switch (p_obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "control: enum value %d is unexpected\n", (int)p_obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CFG_DATA_ID_MAC_TABLE_ENTRY_LIMIT))
    {
        if (p_obj->mac_table_entry_limit > 128U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "mac_table_entry_limit: %u is greater than the maximum value of 128\n", p_obj->mac_table_entry_limit);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CFG_DATA_ID_DEBUG_FLOW_CONFIG))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "debug_flow_config.");
        if (!bcmolt_debug_flow_config_validate(&p_obj->debug_flow_config, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_gem_stats_data_set_default(
    bcmolt_itupon_gem_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rx_packets = 0ULL;
    p_obj->rx_bytes = 0ULL;
    p_obj->tx_packets = 0ULL;
    p_obj->tx_bytes = 0ULL;
}

bcmos_bool bcmolt_itupon_gem_stats_data_validate(
    const bcmolt_itupon_gem_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_PACKETS))
    {
        /* p_obj->rx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_PACKETS))
    {
        /* p_obj->tx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_BYTES))
    {
        /* p_obj->tx_bytes can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_gem_configuration_completed_data_set_default(
    bcmolt_itupon_gem_configuration_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->new_state = BCMOLT_ACTIVATION_STATE_NOT_CONFIGURED;
}

bcmos_bool bcmolt_itupon_gem_configuration_completed_data_validate(
    const bcmolt_itupon_gem_configuration_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_CONFIGURATION_COMPLETED_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_ACTIVATION_STATE_NOT_CONFIGURED:
        case BCMOLT_ACTIVATION_STATE_INACTIVE:
        case BCMOLT_ACTIVATION_STATE_PROCESSING:
        case BCMOLT_ACTIVATION_STATE_ACTIVE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_gem_set_state_data_set_default(
    bcmolt_itupon_gem_set_state_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_GEM_PORT_OPERATION_ACTIVATE;
}

bcmos_bool bcmolt_itupon_gem_set_state_data_validate(
    const bcmolt_itupon_gem_set_state_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_SET_STATE_DATA_ID_STATE))
    {
        switch (p_obj->state)
        {
        case BCMOLT_GEM_PORT_OPERATION_ACTIVATE:
        case BCMOLT_GEM_PORT_OPERATION_DEACTIVATE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "state: enum value %d is unexpected\n", (int)p_obj->state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_gem_stats_cfg_data_set_default(
    bcmolt_itupon_gem_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bytes);
}

bcmos_bool bcmolt_itupon_gem_stats_cfg_data_validate(
    const bcmolt_itupon_gem_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_RX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_TX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_CFG_DATA_ID_TX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_gem_stats_alarm_raised_data_set_default(
    bcmolt_itupon_gem_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_PACKETS;
}

bcmos_bool bcmolt_itupon_gem_stats_alarm_raised_data_validate(
    const bcmolt_itupon_gem_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_BYTES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_gem_stats_alarm_cleared_data_set_default(
    bcmolt_itupon_gem_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_PACKETS;
}

bcmos_bool bcmolt_itupon_gem_stats_alarm_cleared_data_validate(
    const bcmolt_itupon_gem_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_ITUPON_GEM_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_ITUPON_GEM_STATS_DATA_ID_TX_BYTES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_gem_auto_cfg_data_set_default(
    bcmolt_itupon_gem_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->configuration_completed = BCMOS_FALSE;
    p_obj->stats_alarm_cleared = BCMOS_FALSE;
    p_obj->stats_alarm_raised = BCMOS_FALSE;
}

bcmos_bool bcmolt_itupon_gem_auto_cfg_data_validate(
    const bcmolt_itupon_gem_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID_CONFIGURATION_COMPLETED))
    {
        /* p_obj->configuration_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED))
    {
        /* p_obj->stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ITUPON_GEM_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED))
    {
        /* p_obj->stats_alarm_raised can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_mac_table_key_set_default(
    bcmolt_l2_mac_table_key *p_obj)
{
    p_obj->id = (bcmolt_l2_mac_table_id)0;
}

bcmos_bool bcmolt_l2_mac_table_key_validate(
    const bcmolt_l2_mac_table_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_l2_mac_table_id)0)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 0\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_mac_table_cfg_data_set_default(
    bcmolt_l2_mac_table_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_CONFIG_STATE_CONFIGURED;
    p_obj->dump_status = BCMOLT_L2_MACT_DUMP_STATUS_NOT_STARTED;
    p_obj->last_dump_result = BCMOLT_L2_MACT_DUMP_STATUS_NOT_STARTED;
    p_obj->report_event = (bcmolt_l2_event_report_control)0U;
}

bcmos_bool bcmolt_l2_mac_table_cfg_data_validate(
    const bcmolt_l2_mac_table_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_CFG_DATA_ID_DUMP_STATUS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "dump_status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_CFG_DATA_ID_LAST_DUMP_RESULT))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "last_dump_result: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_CFG_DATA_ID_REPORT_EVENT))
    {
        if ((p_obj->report_event & ~0x3) != 0)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "report_event: 0x%X includes invalid bits\n", p_obj->report_event);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_mac_table_dump_data_set_default(
    bcmolt_l2_mac_table_dump_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_str_128_set_default(&p_obj->file_name);
    p_obj->mode = BCMOLT_L2_DUMP_MODE_DYNAMIC;
    bcmolt_l2_dump_filters_set_default(&p_obj->filters);
    p_obj->report_as_indication = BCMOLT_CONTROL_STATE_DISABLE;
    p_obj->max_entry_per_indication = 512U;
}

bcmos_bool bcmolt_l2_mac_table_dump_data_validate(
    const bcmolt_l2_mac_table_dump_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_DUMP_DATA_ID_FILE_NAME))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "file_name.");
        if (!bcmolt_str_128_validate(&p_obj->file_name, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_DUMP_DATA_ID_MODE))
    {
        if ((p_obj->mode & ~0x3) != 0)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "mode: 0x%X includes invalid bits\n", p_obj->mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_DUMP_DATA_ID_FILTERS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "filters.");
        if (!bcmolt_l2_dump_filters_validate(&p_obj->filters, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_DUMP_DATA_ID_REPORT_AS_INDICATION))
    {
        switch (p_obj->report_as_indication)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "report_as_indication: enum value %d is unexpected\n", (int)p_obj->report_as_indication);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_DUMP_DATA_ID_MAX_ENTRY_PER_INDICATION))
    {
        /* p_obj->max_entry_per_indication can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_mac_table_dump_complete_data_set_default(
    bcmolt_l2_mac_table_dump_complete_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_str_128_set_default(&p_obj->file_name);
    p_obj->result = BCMOLT_L2_MACT_DUMP_STATUS_NOT_STARTED;
}

bcmos_bool bcmolt_l2_mac_table_dump_complete_data_validate(
    const bcmolt_l2_mac_table_dump_complete_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_DUMP_COMPLETE_DATA_ID_FILE_NAME))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "file_name.");
        if (!bcmolt_str_128_validate(&p_obj->file_name, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_DUMP_COMPLETE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_L2_MACT_DUMP_STATUS_NOT_STARTED:
        case BCMOLT_L2_MACT_DUMP_STATUS_IN_PROGRESS:
        case BCMOLT_L2_MACT_DUMP_STATUS_SUCCESS:
        case BCMOLT_L2_MACT_DUMP_STATUS_FAILED:
        case BCMOLT_L2_MACT_DUMP_STATUS_ABORTED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_mac_table_network_events_data_set_default(
    bcmolt_l2_mac_table_network_events_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_l2_mact_entry_list_u32_set_default(&p_obj->entries);
}

bcmos_bool bcmolt_l2_mac_table_network_events_data_validate(
    const bcmolt_l2_mac_table_network_events_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_NETWORK_EVENTS_DATA_ID_ENTRIES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "entries.");
        if (!bcmolt_l2_mact_entry_list_u32_validate(&p_obj->entries, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_mac_table_pon_events_data_set_default(
    bcmolt_l2_mac_table_pon_events_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_l2_mact_entry_list_u32_set_default(&p_obj->entries);
}

bcmos_bool bcmolt_l2_mac_table_pon_events_data_validate(
    const bcmolt_l2_mac_table_pon_events_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_PON_EVENTS_DATA_ID_ENTRIES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "entries.");
        if (!bcmolt_l2_mact_entry_list_u32_validate(&p_obj->entries, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_mac_table_auto_cfg_data_set_default(
    bcmolt_l2_mac_table_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->dump_complete = BCMOS_FALSE;
    p_obj->network_events = BCMOS_FALSE;
    p_obj->pon_events = BCMOS_FALSE;
}

bcmos_bool bcmolt_l2_mac_table_auto_cfg_data_validate(
    const bcmolt_l2_mac_table_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_AUTO_CFG_DATA_ID_DUMP_COMPLETE))
    {
        /* p_obj->dump_complete can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_AUTO_CFG_DATA_ID_NETWORK_EVENTS))
    {
        /* p_obj->network_events can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_L2_MAC_TABLE_AUTO_CFG_DATA_ID_PON_EVENTS))
    {
        /* p_obj->pon_events can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_key_set_default(
    bcmolt_lag_interface_key *p_obj)
{
    p_obj->id = (bcmolt_lag_interface_id)0U;
}

bcmos_bool bcmolt_lag_interface_key_validate(
    const bcmolt_lag_interface_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_lag_interface_id)31U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 31\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_cfg_data_set_default(
    bcmolt_lag_interface_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->config_state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    p_obj->psc_mode = BCMOLT_LAG_PSC_MODE_SMOOTH_DIVISION;
    p_obj->state = BCMOLT_INTERFACE_STATE_ACTIVE_WORKING;
    bcmolt_protection_type_set_default(&p_obj->protection_type);
    bcmolt_arr_nni_id_8_set_default(&p_obj->nni_ids);
    memset(p_obj->nni_ids.arr, 0, sizeof(p_obj->nni_ids.arr));
    p_obj->nni_ids.arr[0] = (bcmolt_nni_id)255;
    p_obj->nni_ids.arr[1] = (bcmolt_nni_id)255;
    p_obj->nni_ids.arr[2] = (bcmolt_nni_id)255;
    p_obj->nni_ids.arr[3] = (bcmolt_nni_id)255;
    p_obj->nni_ids.arr[4] = (bcmolt_nni_id)255;
    p_obj->nni_ids.arr[5] = (bcmolt_nni_id)255;
    p_obj->nni_ids.arr[6] = (bcmolt_nni_id)255;
    p_obj->nni_ids.arr[7] = (bcmolt_nni_id)255;
    bcmolt_arr_link_state_8_set_default(&p_obj->member_status);
    p_obj->member_count = 0;
    p_obj->member_up_count = 0;
    p_obj->lag_health = BCMOLT_LAG_HEALTH_DOWN;
    p_obj->sub_type = BCMOLT_LAG_SUBTYPE_UNASSIGNED;
}

bcmos_bool bcmolt_lag_interface_cfg_data_validate(
    const bcmolt_lag_interface_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_CONFIG_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "config_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_PSC_MODE))
    {
        switch (p_obj->psc_mode)
        {
        case BCMOLT_LAG_PSC_MODE_ROUND_ROBIN:
        case BCMOLT_LAG_PSC_MODE_SMOOTH_DIVISION:
        case BCMOLT_LAG_PSC_MODE_MULTIPLICATION:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "psc_mode: enum value %d is unexpected\n", (int)p_obj->psc_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_PROTECTION_TYPE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "protection_type: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_NNI_IDS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "nni_ids: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_MEMBER_STATUS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "member_status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_MEMBER_COUNT))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "member_count: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_MEMBER_UP_COUNT))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "member_up_count: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_LAG_HEALTH))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "lag_health: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_CFG_DATA_ID_SUB_TYPE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "sub_type: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_stats_data_set_default(
    bcmolt_lag_interface_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rx_bytes = 0ULL;
    p_obj->rx_packets = 0ULL;
    p_obj->rx_ucast_packets = 0ULL;
    p_obj->rx_mcast_packets = 0ULL;
    p_obj->rx_bcast_packets = 0ULL;
    p_obj->rx_error_packets = 0ULL;
    p_obj->rx_fcs_error_packets = 0ULL;
    p_obj->rx_undersize_packets = 0ULL;
    p_obj->rx_oversize_packets = 0ULL;
    p_obj->rx_jabber_packets = 0ULL;
    p_obj->tx_bytes = 0ULL;
    p_obj->tx_packets = 0ULL;
    p_obj->tx_ucast_packets = 0ULL;
    p_obj->tx_mcast_packets = 0ULL;
    p_obj->tx_bcast_packets = 0ULL;
    p_obj->tx_error_packets = 0ULL;
    p_obj->tx_undersize_packets = 0ULL;
    p_obj->tx_oversize_packets = 0ULL;
    p_obj->tx_jabber_packets = 0ULL;
    p_obj->rx_frames_64 = 0ULL;
    p_obj->rx_frames_65_127 = 0ULL;
    p_obj->rx_frames_128_255 = 0ULL;
    p_obj->rx_frames_256_511 = 0ULL;
    p_obj->rx_frames_512_1023 = 0ULL;
    p_obj->rx_frames_1024_1518 = 0ULL;
    p_obj->rx_frames_1519_2047 = 0ULL;
    p_obj->rx_frames_2048_4095 = 0ULL;
    p_obj->rx_frames_4096_9216 = 0ULL;
    p_obj->rx_frames_9217_16383 = 0ULL;
    p_obj->tx_frames_64 = 0ULL;
    p_obj->tx_frames_65_127 = 0ULL;
    p_obj->tx_frames_128_255 = 0ULL;
    p_obj->tx_frames_256_511 = 0ULL;
    p_obj->tx_frames_512_1023 = 0ULL;
    p_obj->tx_frames_1024_1518 = 0ULL;
    p_obj->tx_frames_1519_2047 = 0ULL;
    p_obj->tx_frames_2048_4095 = 0ULL;
    p_obj->tx_frames_4096_9216 = 0ULL;
    p_obj->tx_frames_9217_16383 = 0ULL;
}

bcmos_bool bcmolt_lag_interface_stats_data_validate(
    const bcmolt_lag_interface_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_PACKETS))
    {
        /* p_obj->rx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS))
    {
        /* p_obj->rx_ucast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS))
    {
        /* p_obj->rx_mcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS))
    {
        /* p_obj->rx_bcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS))
    {
        /* p_obj->rx_error_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS))
    {
        /* p_obj->rx_fcs_error_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS))
    {
        /* p_obj->rx_undersize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS))
    {
        /* p_obj->rx_oversize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS))
    {
        /* p_obj->rx_jabber_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BYTES))
    {
        /* p_obj->tx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_PACKETS))
    {
        /* p_obj->tx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS))
    {
        /* p_obj->tx_ucast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS))
    {
        /* p_obj->tx_mcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS))
    {
        /* p_obj->tx_bcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS))
    {
        /* p_obj->tx_error_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS))
    {
        /* p_obj->tx_undersize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS))
    {
        /* p_obj->tx_oversize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS))
    {
        /* p_obj->tx_jabber_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_64))
    {
        /* p_obj->rx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127))
    {
        /* p_obj->rx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255))
    {
        /* p_obj->rx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511))
    {
        /* p_obj->rx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023))
    {
        /* p_obj->rx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518))
    {
        /* p_obj->rx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047))
    {
        /* p_obj->rx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095))
    {
        /* p_obj->rx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216))
    {
        /* p_obj->rx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383))
    {
        /* p_obj->rx_frames_9217_16383 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_64))
    {
        /* p_obj->tx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127))
    {
        /* p_obj->tx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255))
    {
        /* p_obj->tx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511))
    {
        /* p_obj->tx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023))
    {
        /* p_obj->tx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518))
    {
        /* p_obj->tx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047))
    {
        /* p_obj->tx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095))
    {
        /* p_obj->tx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216))
    {
        /* p_obj->tx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383))
    {
        /* p_obj->tx_frames_9217_16383 can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_members_update_data_set_default(
    bcmolt_lag_interface_members_update_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_lag_interface_members_update_command_set_default(&p_obj->members_cmd);
}

bcmos_bool bcmolt_lag_interface_members_update_data_validate(
    const bcmolt_lag_interface_members_update_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_DATA_ID_MEMBERS_CMD))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "members_cmd.");
        if (!bcmolt_lag_interface_members_update_command_validate(&p_obj->members_cmd, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_complete_members_update_data_set_default(
    bcmolt_lag_interface_complete_members_update_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_NONE;
}

bcmos_bool bcmolt_lag_interface_complete_members_update_data_validate(
    const bcmolt_lag_interface_complete_members_update_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_COMPLETE_MEMBERS_UPDATE_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_NONE:
        case BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_PARM:
        case BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_INTERNAL:
        case BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_SW:
        case BCMOLT_LAG_MEMBER_UPDATE_FAIL_REASON_IN_USE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_state_update_data_set_default(
    bcmolt_lag_interface_state_update_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->lag_state = BCMOLT_INTERFACE_OPERATION_ACTIVE_WORKING;
}

bcmos_bool bcmolt_lag_interface_state_update_data_validate(
    const bcmolt_lag_interface_state_update_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATE_UPDATE_DATA_ID_LAG_STATE))
    {
        switch (p_obj->lag_state)
        {
        case BCMOLT_INTERFACE_OPERATION_INACTIVE:
        case BCMOLT_INTERFACE_OPERATION_ACTIVE_WORKING:
        case BCMOLT_INTERFACE_OPERATION_ACTIVE_STANDBY:
        case BCMOLT_INTERFACE_OPERATION_DISABLE:
        case BCMOLT_INTERFACE_OPERATION_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "lag_state: enum value %d is unexpected\n", (int)p_obj->lag_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_state_updated_data_set_default(
    bcmolt_lag_interface_state_updated_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->new_state = BCMOLT_INTERFACE_STATE_INACTIVE;
    p_obj->old_state = BCMOLT_INTERFACE_STATE_INACTIVE;
    p_obj->fault_code = (bcmolt_link_fault_code)0;
}

bcmos_bool bcmolt_lag_interface_state_updated_data_validate(
    const bcmolt_lag_interface_state_updated_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_INTERFACE_STATE_INACTIVE:
        case BCMOLT_INTERFACE_STATE_PROCESSING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_WORKING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_STANDBY:
        case BCMOLT_INTERFACE_STATE_DISABLED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID_OLD_STATE))
    {
        switch (p_obj->old_state)
        {
        case BCMOLT_INTERFACE_STATE_INACTIVE:
        case BCMOLT_INTERFACE_STATE_PROCESSING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_WORKING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_STANDBY:
        case BCMOLT_INTERFACE_STATE_DISABLED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "old_state: enum value %d is unexpected\n", (int)p_obj->old_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATE_UPDATED_DATA_ID_FAULT_CODE))
    {
        if ((p_obj->fault_code & ~0x3) != 0)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fault_code: 0x%X includes invalid bits\n", p_obj->fault_code);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_lag_health_change_data_set_default(
    bcmolt_lag_interface_lag_health_change_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->new_state = BCMOLT_LAG_HEALTH_DOWN;
    p_obj->old_state = BCMOLT_LAG_HEALTH_DOWN;
}

bcmos_bool bcmolt_lag_interface_lag_health_change_data_validate(
    const bcmolt_lag_interface_lag_health_change_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_LAG_HEALTH_DOWN:
        case BCMOLT_LAG_HEALTH_DEGRADED:
        case BCMOLT_LAG_HEALTH_UP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_LAG_HEALTH_CHANGE_DATA_ID_OLD_STATE))
    {
        switch (p_obj->old_state)
        {
        case BCMOLT_LAG_HEALTH_DOWN:
        case BCMOLT_LAG_HEALTH_DEGRADED:
        case BCMOLT_LAG_HEALTH_UP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "old_state: enum value %d is unexpected\n", (int)p_obj->old_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_stats_cfg_data_set_default(
    bcmolt_lag_interface_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_ucast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_mcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_error_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_fcs_error_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_undersize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_oversize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_jabber_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_ucast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_mcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_error_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_undersize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_oversize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_jabber_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_9217_16383);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_9217_16383);
}

bcmos_bool bcmolt_lag_interface_stats_cfg_data_validate(
    const bcmolt_lag_interface_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_UCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_ucast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_ucast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_MCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_mcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_mcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_BCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_ERROR_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_error_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_error_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FCS_ERROR_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_fcs_error_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_fcs_error_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_UNDERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_undersize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_undersize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_OVERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_oversize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_oversize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_JABBER_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_jabber_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_jabber_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_UCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_ucast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_ucast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_MCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_mcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_mcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_BCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_ERROR_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_error_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_error_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_UNDERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_undersize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_undersize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_OVERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_oversize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_oversize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_JABBER_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_jabber_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_jabber_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_stats_alarm_raised_data_set_default(
    bcmolt_lag_interface_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_lag_interface_stats_alarm_raised_data_validate(
    const bcmolt_lag_interface_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_stats_alarm_cleared_data_set_default(
    bcmolt_lag_interface_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_lag_interface_stats_alarm_cleared_data_validate(
    const bcmolt_lag_interface_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_LAG_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_auto_cfg_data_set_default(
    bcmolt_lag_interface_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->complete_members_update = BCMOS_FALSE;
    p_obj->lag_health_change = BCMOS_FALSE;
    p_obj->state_updated = BCMOS_FALSE;
    p_obj->stats_alarm_cleared = BCMOS_FALSE;
    p_obj->stats_alarm_raised = BCMOS_FALSE;
}

bcmos_bool bcmolt_lag_interface_auto_cfg_data_validate(
    const bcmolt_lag_interface_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_COMPLETE_MEMBERS_UPDATE))
    {
        /* p_obj->complete_members_update can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_LAG_HEALTH_CHANGE))
    {
        /* p_obj->lag_health_change can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_STATE_UPDATED))
    {
        /* p_obj->state_updated can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED))
    {
        /* p_obj->stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LAG_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED))
    {
        /* p_obj->stats_alarm_raised can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_log_key_set_default(
    bcmolt_log_key *p_obj)
{
    p_obj->device_id = (bcmolt_odid)0;
    bcmolt_str_100_set_default(&p_obj->name);
}

bcmos_bool bcmolt_log_key_validate(
    const bcmolt_log_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->device_id can't be invalid. */
    int prefix_len = bcmolt_string_append(p_err_details, "name.");
    if (!bcmolt_str_100_validate(&p_obj->name, p_err, p_err_details))
    {
        return BCMOS_FALSE;
    }
    bcmolt_string_rewind(p_err_details, prefix_len);
    return BCMOS_TRUE;
}

void bcmolt_log_cfg_data_set_default(
    bcmolt_log_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->type = BCMOLT_LOG_TYPE_NONE;
    p_obj->style = BCMOLT_LOG_STYLE_NORMAL;
    bcmolt_log_level_per_file_set_default(&p_obj->level);
    bcmolt_log_level_msg_count_set_default(&p_obj->msg_count);
    p_obj->lost_msg_count = 0UL;
}

bcmos_bool bcmolt_log_cfg_data_validate(
    const bcmolt_log_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_CFG_DATA_ID_TYPE))
    {
        switch (p_obj->type)
        {
        case BCMOLT_LOG_TYPE_NONE:
        case BCMOLT_LOG_TYPE_PRINT:
        case BCMOLT_LOG_TYPE_SAVE:
        case BCMOLT_LOG_TYPE_BOTH:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "type: enum value %d is unexpected\n", (int)p_obj->type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_CFG_DATA_ID_STYLE))
    {
        switch (p_obj->style)
        {
        case BCMOLT_LOG_STYLE_NORMAL:
        case BCMOLT_LOG_STYLE_BOLD:
        case BCMOLT_LOG_STYLE_UNDERLINE:
        case BCMOLT_LOG_STYLE_BLINK:
        case BCMOLT_LOG_STYLE_REVERSE_VIDEO:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "style: enum value %d is unexpected\n", (int)p_obj->style);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_CFG_DATA_ID_LEVEL))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "level.");
        if (!bcmolt_log_level_per_file_validate(&p_obj->level, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_CFG_DATA_ID_MSG_COUNT))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "msg_count: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_CFG_DATA_ID_LOST_MSG_COUNT))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "lost_msg_count: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_log_file_key_set_default(
    bcmolt_log_file_key *p_obj)
{
    p_obj->device_id = (bcmolt_odid)0;
    p_obj->file_id = BCMOLT_LOG_FILE_ID_SRAM;
}

bcmos_bool bcmolt_log_file_key_validate(
    const bcmolt_log_file_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->device_id can't be invalid. */
    switch (p_obj->file_id)
    {
    case BCMOLT_LOG_FILE_ID_SRAM:
    case BCMOLT_LOG_FILE_ID_DDR:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "file_id: enum value %d is unexpected\n", (int)p_obj->file_id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_log_file_cfg_data_set_default(
    bcmolt_log_file_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->wrap_around = BCMOS_TRUE;
    p_obj->clear_after_read = BCMOS_FALSE;
    p_obj->msg_count = 0UL;
    p_obj->msgs_read = 0UL;
    p_obj->msgs_remaining = 0UL;
    bcmolt_str_2048_set_default(&p_obj->buffer);
}

bcmos_bool bcmolt_log_file_cfg_data_validate(
    const bcmolt_log_file_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_FILE_CFG_DATA_ID_WRAP_AROUND))
    {
        /* p_obj->wrap_around can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_FILE_CFG_DATA_ID_CLEAR_AFTER_READ))
    {
        /* p_obj->clear_after_read can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_FILE_CFG_DATA_ID_MSG_COUNT))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "msg_count: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_FILE_CFG_DATA_ID_MSGS_READ))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "msgs_read: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_FILE_CFG_DATA_ID_MSGS_REMAINING))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "msgs_remaining: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_LOG_FILE_CFG_DATA_ID_BUFFER))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "buffer: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_ngpon2_channel_key_set_default(
    bcmolt_ngpon2_channel_key *p_obj)
{
    p_obj->pon_ni = (bcmolt_pon_ni)0;
}

bcmos_bool bcmolt_ngpon2_channel_key_validate(
    const bcmolt_ngpon2_channel_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->pon_ni > (bcmolt_pon_ni)15)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "pon_ni: %u is greater than the maximum value of 15\n", p_obj->pon_ni);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_ngpon2_channel_cfg_data_set_default(
    bcmolt_ngpon2_channel_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_system_profile_set_default(&p_obj->system_profile);
    bcmolt_arr_channel_profile_8_set_default(&p_obj->channel_profile);
}

bcmos_bool bcmolt_ngpon2_channel_cfg_data_validate(
    const bcmolt_ngpon2_channel_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID_SYSTEM_PROFILE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "system_profile.");
        if (!bcmolt_system_profile_validate(&p_obj->system_profile, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NGPON2_CHANNEL_CFG_DATA_ID_CHANNEL_PROFILE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "channel_profile.");
        if (!bcmolt_arr_channel_profile_8_validate(&p_obj->channel_profile, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_key_set_default(
    bcmolt_nni_interface_key *p_obj)
{
    p_obj->id = (bcmolt_nni_id)255;
}

bcmos_bool bcmolt_nni_interface_key_validate(
    const bcmolt_nni_interface_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->id can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_state_change_data_set_default(
    bcmolt_nni_interface_state_change_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    p_obj->old_state = BCMOLT_INTERFACE_STATE_INACTIVE;
    p_obj->new_state = BCMOLT_INTERFACE_STATE_INACTIVE;
}

bcmos_bool bcmolt_nni_interface_state_change_data_validate(
    const bcmolt_nni_interface_state_change_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID_OLD_STATE))
    {
        switch (p_obj->old_state)
        {
        case BCMOLT_INTERFACE_STATE_INACTIVE:
        case BCMOLT_INTERFACE_STATE_PROCESSING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_WORKING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_STANDBY:
        case BCMOLT_INTERFACE_STATE_DISABLED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "old_state: enum value %d is unexpected\n", (int)p_obj->old_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATE_CHANGE_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_INTERFACE_STATE_INACTIVE:
        case BCMOLT_INTERFACE_STATE_PROCESSING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_WORKING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_STANDBY:
        case BCMOLT_INTERFACE_STATE_DISABLED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_cfg_data_set_default(
    bcmolt_nni_interface_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->config_state = BCMOLT_CONFIG_STATE_CONFIGURED;
    p_obj->state = BCMOLT_INTERFACE_STATE_INACTIVE;
    bcmolt_protection_type_set_default(&p_obj->protection_type);
    p_obj->link_state = BCMOLT_LINK_STATE_LINK_DOWN;
    p_obj->link_fault_code = (bcmolt_link_fault_code)0;
    bcmolt_str_48_set_default(&p_obj->description);
    p_obj->mtu = 9600UL;
    p_obj->speed = 0UL;
    p_obj->duplex = BCMOLT_DUPLEX_MODE_FULL;
    p_obj->auto_negotiate = BCMOLT_CONTROL_STATE_DISABLE;
    p_obj->sub_type = BCMOLT_NNI_SUBTYPE_NETWORK;
}

bcmos_bool bcmolt_nni_interface_cfg_data_validate(
    const bcmolt_nni_interface_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_CONFIG_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "config_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_PROTECTION_TYPE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "protection_type: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_LINK_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "link_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_LINK_FAULT_CODE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "link_fault_code: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_DESCRIPTION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "description.");
        if (!bcmolt_str_48_validate(&p_obj->description, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_MTU))
    {
        if (p_obj->mtu < 261UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "mtu: %u is less than the minimum value of 261\n", p_obj->mtu);
            return BCMOS_FALSE;
        }
        if (p_obj->mtu > 9600UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "mtu: %u is greater than the maximum value of 9600\n", p_obj->mtu);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_SPEED))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "speed: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_DUPLEX))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "duplex: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_AUTO_NEGOTIATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "auto_negotiate: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_CFG_DATA_ID_SUB_TYPE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "sub_type: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_set_nni_state_data_set_default(
    bcmolt_nni_interface_set_nni_state_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->nni_state = BCMOLT_INTERFACE_OPERATION_INACTIVE;
}

bcmos_bool bcmolt_nni_interface_set_nni_state_data_validate(
    const bcmolt_nni_interface_set_nni_state_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_SET_NNI_STATE_DATA_ID_NNI_STATE))
    {
        switch (p_obj->nni_state)
        {
        case BCMOLT_INTERFACE_OPERATION_INACTIVE:
        case BCMOLT_INTERFACE_OPERATION_ACTIVE_WORKING:
        case BCMOLT_INTERFACE_OPERATION_ACTIVE_STANDBY:
        case BCMOLT_INTERFACE_OPERATION_DISABLE:
        case BCMOLT_INTERFACE_OPERATION_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "nni_state: enum value %d is unexpected\n", (int)p_obj->nni_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_stats_data_set_default(
    bcmolt_nni_interface_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rx_bytes = 0ULL;
    p_obj->rx_packets = 0ULL;
    p_obj->rx_ucast_packets = 0ULL;
    p_obj->rx_mcast_packets = 0ULL;
    p_obj->rx_bcast_packets = 0ULL;
    p_obj->rx_error_packets = 0ULL;
    p_obj->rx_fcs_error_packets = 0ULL;
    p_obj->rx_undersize_packets = 0ULL;
    p_obj->rx_oversize_packets = 0ULL;
    p_obj->rx_jabber_packets = 0ULL;
    p_obj->tx_bytes = 0ULL;
    p_obj->tx_packets = 0ULL;
    p_obj->tx_ucast_packets = 0ULL;
    p_obj->tx_mcast_packets = 0ULL;
    p_obj->tx_bcast_packets = 0ULL;
    p_obj->tx_error_packets = 0ULL;
    p_obj->tx_undersize_packets = 0ULL;
    p_obj->tx_oversize_packets = 0ULL;
    p_obj->tx_jabber_packets = 0ULL;
    p_obj->rx_frames_64 = 0ULL;
    p_obj->rx_frames_65_127 = 0ULL;
    p_obj->rx_frames_128_255 = 0ULL;
    p_obj->rx_frames_256_511 = 0ULL;
    p_obj->rx_frames_512_1023 = 0ULL;
    p_obj->rx_frames_1024_1518 = 0ULL;
    p_obj->rx_frames_1519_2047 = 0ULL;
    p_obj->rx_frames_2048_4095 = 0ULL;
    p_obj->rx_frames_4096_9216 = 0ULL;
    p_obj->rx_frames_9217_16383 = 0ULL;
    p_obj->tx_frames_64 = 0ULL;
    p_obj->tx_frames_65_127 = 0ULL;
    p_obj->tx_frames_128_255 = 0ULL;
    p_obj->tx_frames_256_511 = 0ULL;
    p_obj->tx_frames_512_1023 = 0ULL;
    p_obj->tx_frames_1024_1518 = 0ULL;
    p_obj->tx_frames_1519_2047 = 0ULL;
    p_obj->tx_frames_2048_4095 = 0ULL;
    p_obj->tx_frames_4096_9216 = 0ULL;
    p_obj->tx_frames_9217_16383 = 0ULL;
}

bcmos_bool bcmolt_nni_interface_stats_data_validate(
    const bcmolt_nni_interface_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_PACKETS))
    {
        /* p_obj->rx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS))
    {
        /* p_obj->rx_ucast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS))
    {
        /* p_obj->rx_mcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS))
    {
        /* p_obj->rx_bcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS))
    {
        /* p_obj->rx_error_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS))
    {
        /* p_obj->rx_fcs_error_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS))
    {
        /* p_obj->rx_undersize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS))
    {
        /* p_obj->rx_oversize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS))
    {
        /* p_obj->rx_jabber_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BYTES))
    {
        /* p_obj->tx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_PACKETS))
    {
        /* p_obj->tx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS))
    {
        /* p_obj->tx_ucast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS))
    {
        /* p_obj->tx_mcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS))
    {
        /* p_obj->tx_bcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS))
    {
        /* p_obj->tx_error_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS))
    {
        /* p_obj->tx_undersize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS))
    {
        /* p_obj->tx_oversize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS))
    {
        /* p_obj->tx_jabber_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_64))
    {
        /* p_obj->rx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127))
    {
        /* p_obj->rx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255))
    {
        /* p_obj->rx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511))
    {
        /* p_obj->rx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023))
    {
        /* p_obj->rx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518))
    {
        /* p_obj->rx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047))
    {
        /* p_obj->rx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095))
    {
        /* p_obj->rx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216))
    {
        /* p_obj->rx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383))
    {
        /* p_obj->rx_frames_9217_16383 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_64))
    {
        /* p_obj->tx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127))
    {
        /* p_obj->tx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255))
    {
        /* p_obj->tx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511))
    {
        /* p_obj->tx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023))
    {
        /* p_obj->tx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518))
    {
        /* p_obj->tx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047))
    {
        /* p_obj->tx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095))
    {
        /* p_obj->tx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216))
    {
        /* p_obj->tx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383))
    {
        /* p_obj->tx_frames_9217_16383 can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_link_state_change_data_set_default(
    bcmolt_nni_interface_link_state_change_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->old_state = BCMOLT_LINK_STATE_LINK_DOWN;
    p_obj->new_state = BCMOLT_LINK_STATE_LINK_DOWN;
}

bcmos_bool bcmolt_nni_interface_link_state_change_data_validate(
    const bcmolt_nni_interface_link_state_change_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID_OLD_STATE))
    {
        switch (p_obj->old_state)
        {
        case BCMOLT_LINK_STATE_LINK_DOWN:
        case BCMOLT_LINK_STATE_LINK_UP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "old_state: enum value %d is unexpected\n", (int)p_obj->old_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_LINK_STATE_CHANGE_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_LINK_STATE_LINK_DOWN:
        case BCMOLT_LINK_STATE_LINK_UP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_fault_code_change_data_set_default(
    bcmolt_nni_interface_fault_code_change_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->old_fault_code = (bcmolt_link_fault_code)0;
    p_obj->new_fault_code = (bcmolt_link_fault_code)0;
}

bcmos_bool bcmolt_nni_interface_fault_code_change_data_validate(
    const bcmolt_nni_interface_fault_code_change_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_FAULT_CODE_CHANGE_DATA_ID_OLD_FAULT_CODE))
    {
        if ((p_obj->old_fault_code & ~0x3) != 0)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "old_fault_code: 0x%X includes invalid bits\n", p_obj->old_fault_code);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_FAULT_CODE_CHANGE_DATA_ID_NEW_FAULT_CODE))
    {
        if ((p_obj->new_fault_code & ~0x3) != 0)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_fault_code: 0x%X includes invalid bits\n", p_obj->new_fault_code);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_stats_cfg_data_set_default(
    bcmolt_nni_interface_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_ucast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_mcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_error_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_fcs_error_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_undersize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_oversize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_jabber_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_ucast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_mcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_error_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_undersize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_oversize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_jabber_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_9217_16383);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_9217_16383);
}

bcmos_bool bcmolt_nni_interface_stats_cfg_data_validate(
    const bcmolt_nni_interface_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_UCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_ucast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_ucast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_MCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_mcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_mcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_BCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_ERROR_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_error_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_error_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FCS_ERROR_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_fcs_error_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_fcs_error_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_UNDERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_undersize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_undersize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_OVERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_oversize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_oversize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_JABBER_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_jabber_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_jabber_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_UCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_ucast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_ucast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_MCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_mcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_mcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_BCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_ERROR_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_error_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_error_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_UNDERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_undersize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_undersize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_OVERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_oversize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_oversize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_JABBER_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_jabber_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_jabber_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_stats_alarm_raised_data_set_default(
    bcmolt_nni_interface_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_nni_interface_stats_alarm_raised_data_validate(
    const bcmolt_nni_interface_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_stats_alarm_cleared_data_set_default(
    bcmolt_nni_interface_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_nni_interface_stats_alarm_cleared_data_validate(
    const bcmolt_nni_interface_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_MCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_BCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_ERROR_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FCS_ERROR_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_UNDERSIZE_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_OVERSIZE_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_JABBER_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_MCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_BCAST_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_ERROR_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_UNDERSIZE_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_OVERSIZE_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_JABBER_PACKETS:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_NNI_INTERFACE_STATS_DATA_ID_TX_FRAMES_9217_16383:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_interface_auto_cfg_data_set_default(
    bcmolt_nni_interface_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->fault_code_change = BCMOS_FALSE;
    p_obj->link_state_change = BCMOS_FALSE;
    p_obj->state_change = BCMOS_FALSE;
    p_obj->stats_alarm_cleared = BCMOS_FALSE;
    p_obj->stats_alarm_raised = BCMOS_FALSE;
}

bcmos_bool bcmolt_nni_interface_auto_cfg_data_validate(
    const bcmolt_nni_interface_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_FAULT_CODE_CHANGE))
    {
        /* p_obj->fault_code_change can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_LINK_STATE_CHANGE))
    {
        /* p_obj->link_state_change can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_STATE_CHANGE))
    {
        /* p_obj->state_change can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED))
    {
        /* p_obj->stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_NNI_INTERFACE_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED))
    {
        /* p_obj->stats_alarm_raised can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_olt_key_set_default(
    bcmolt_olt_key *p_obj)
{
    p_obj->reserved = 0;
}

bcmos_bool bcmolt_olt_key_validate(
    const bcmolt_olt_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->reserved can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_olt_cfg_data_set_default(
    bcmolt_olt_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_topology_set_default(&p_obj->topology);
    p_obj->bal_state = BCMOLT_BAL_STATE_BAL_STARTING;
    bcmolt_host_sw_version_set_default(&p_obj->host_sw_version);
}

bcmos_bool bcmolt_olt_cfg_data_validate(
    const bcmolt_olt_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_CFG_DATA_ID_TOPOLOGY))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "topology: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_CFG_DATA_ID_BAL_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "bal_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_CFG_DATA_ID_HOST_SW_VERSION))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "host_sw_version: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_olt_bal_failure_data_set_default(
    bcmolt_olt_bal_failure_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->reason = (bcmolt_bal_fail_reason)0;
}

bcmos_bool bcmolt_olt_bal_failure_data_validate(
    const bcmolt_olt_bal_failure_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_BAL_FAILURE_DATA_ID_REASON))
    {
        switch (p_obj->reason)
        {
        case BCMOLT_BAL_FAIL_REASON_SWITCH_TIMED_OUT:
        case BCMOLT_BAL_FAIL_REASON_SWITCH_INTERNAL_ERROR:
        case BCMOLT_BAL_FAIL_REASON_BAL_TIMED_OUT:
        case BCMOLT_BAL_FAIL_REASON_BAL_INTERNAL_ERROR:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "reason: enum value %d is unexpected\n", (int)p_obj->reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_olt_sw_error_data_set_default(
    bcmolt_olt_sw_error_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_str_100_set_default(&p_obj->task_name);
    bcmolt_str_100_set_default(&p_obj->file_name);
    p_obj->line_number = 0UL;
    bcmolt_str_256_set_default(&p_obj->error_string);
    p_obj->severity = BCMOLT_SW_ERROR_SEVERITY_HIGH;
}

bcmos_bool bcmolt_olt_sw_error_data_validate(
    const bcmolt_olt_sw_error_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_SW_ERROR_DATA_ID_TASK_NAME))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "task_name.");
        if (!bcmolt_str_100_validate(&p_obj->task_name, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_SW_ERROR_DATA_ID_FILE_NAME))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "file_name.");
        if (!bcmolt_str_100_validate(&p_obj->file_name, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_SW_ERROR_DATA_ID_LINE_NUMBER))
    {
        /* p_obj->line_number can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_SW_ERROR_DATA_ID_ERROR_STRING))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "error_string.");
        if (!bcmolt_str_256_validate(&p_obj->error_string, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_SW_ERROR_DATA_ID_SEVERITY))
    {
        switch (p_obj->severity)
        {
        case BCMOLT_SW_ERROR_SEVERITY_HIGH:
        case BCMOLT_SW_ERROR_SEVERITY_FATAL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "severity: enum value %d is unexpected\n", (int)p_obj->severity);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_olt_reset_data_set_default(
    bcmolt_olt_reset_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->mode = (bcmolt_reset_mode)0;
}

bcmos_bool bcmolt_olt_reset_data_validate(
    const bcmolt_olt_reset_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_RESET_DATA_ID_MODE))
    {
        switch (p_obj->mode)
        {
        case BCMOLT_RESET_MODE_HOST:
        case BCMOLT_RESET_MODE_ALL:
        case BCMOLT_RESET_MODE_HOST_ISSU:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "mode: enum value %d is unexpected\n", (int)p_obj->mode);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_olt_auto_cfg_data_set_default(
    bcmolt_olt_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->bal_failure = BCMOS_FALSE;
    p_obj->bal_ready = BCMOS_FALSE;
    p_obj->sw_error = BCMOS_FALSE;
}

bcmos_bool bcmolt_olt_auto_cfg_data_validate(
    const bcmolt_olt_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_AUTO_CFG_DATA_ID_BAL_FAILURE))
    {
        /* p_obj->bal_failure can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_AUTO_CFG_DATA_ID_BAL_READY))
    {
        /* p_obj->bal_ready can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_OLT_AUTO_CFG_DATA_ID_SW_ERROR))
    {
        /* p_obj->sw_error can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_key_set_default(
    bcmolt_onu_key *p_obj)
{
    p_obj->pon_ni = (bcmolt_pon_ni)0;
    p_obj->onu_id = (bcmolt_onu_id)0U;
}

bcmos_bool bcmolt_onu_key_validate(
    const bcmolt_onu_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->pon_ni > (bcmolt_pon_ni)15)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "pon_ni: %u is greater than the maximum value of 15\n", p_obj->pon_ni);
        return BCMOS_FALSE;
    }
    /* p_obj->onu_id can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_onu_cfg_data_set_default(
    bcmolt_onu_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->onu_state = BCMOLT_ONU_STATE_NOT_CONFIGURED;
    p_obj->onu_old_state = BCMOLT_ONU_STATE_NOT_CONFIGURED;
    p_obj->onu_rate = BCMOLT_ONU_RATE_RATE_10G_DS_10G_US;
    bcmolt_itu_onu_params_set_default(&p_obj->itu);
}

bcmos_bool bcmolt_onu_cfg_data_validate(
    const bcmolt_onu_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CFG_DATA_ID_ONU_STATE))
    {
        switch (p_obj->onu_state)
        {
        case BCMOLT_ONU_STATE_NOT_CONFIGURED:
        case BCMOLT_ONU_STATE_INACTIVE:
        case BCMOLT_ONU_STATE_ACTIVE:
        case BCMOLT_ONU_STATE_ACTIVE_STANDBY:
        case BCMOLT_ONU_STATE_DISABLED:
        case BCMOLT_ONU_STATE_AWAKE_FREE:
        case BCMOLT_ONU_STATE_PROCESSING:
        case BCMOLT_ONU_STATE_LOW_POWER_DOZE:
        case BCMOLT_ONU_STATE_LOW_POWER_SLEEP:
        case BCMOLT_ONU_STATE_LOW_POWER_WATCH:
        case BCMOLT_ONU_STATE_UNAWARE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "onu_state: enum value %d is unexpected\n", (int)p_obj->onu_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CFG_DATA_ID_ONU_OLD_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "onu_old_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CFG_DATA_ID_ONU_RATE))
    {
        switch (p_obj->onu_rate)
        {
        case BCMOLT_ONU_RATE_RATE_10G_DS_10G_US:
        case BCMOLT_ONU_RATE_RATE_10G_DS_2P5G_US:
        case BCMOLT_ONU_RATE_RATE_10G_DS_1G_US:
        case BCMOLT_ONU_RATE_RATE_2P5G_DS_1P25G_US:
        case BCMOLT_ONU_RATE_RATE_1G_DS_1G_US:
        case BCMOLT_ONU_RATE_RATE_25G_DS_25G_US:
        case BCMOLT_ONU_RATE_RATE_25G_DS_10G_US:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "onu_rate: enum value %d is unexpected\n", (int)p_obj->onu_rate);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CFG_DATA_ID_ITU))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "itu.");
        if (!bcmolt_itu_onu_params_validate(&p_obj->itu, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_itu_pon_stats_data_set_default(
    bcmolt_onu_itu_pon_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->positive_drift = 0ULL;
    p_obj->negative_drift = 0ULL;
    p_obj->delimiter_miss_detection = 0ULL;
    p_obj->bip_errors = 0ULL;
    p_obj->bip_units = 0ULL;
    p_obj->fec_corrected_symbols = 0ULL;
    p_obj->fec_codewords_corrected = 0ULL;
    p_obj->fec_codewords_uncorrectable = 0ULL;
    p_obj->fec_codewords = 0ULL;
    p_obj->fec_corrected_units = 0ULL;
    p_obj->xgem_key_errors = 0ULL;
    p_obj->xgem_loss = 0ULL;
    p_obj->rx_ploams_error = 0ULL;
    p_obj->rx_ploams_non_idle = 0ULL;
    p_obj->rx_omci = 0ULL;
    p_obj->rx_omci_packets_crc_error = 0ULL;
    p_obj->rx_bytes = 0ULL;
    p_obj->rx_packets = 0ULL;
    p_obj->tx_bytes = 0ULL;
    p_obj->tx_packets = 0ULL;
    p_obj->ber_reported = 0ULL;
    p_obj->lcdg_errors = 0ULL;
    p_obj->rdi_errors = 0ULL;
}

bcmos_bool bcmolt_onu_itu_pon_stats_data_validate(
    const bcmolt_onu_itu_pon_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_POSITIVE_DRIFT))
    {
        /* p_obj->positive_drift can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_NEGATIVE_DRIFT))
    {
        /* p_obj->negative_drift can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_DELIMITER_MISS_DETECTION))
    {
        /* p_obj->delimiter_miss_detection can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_ERRORS))
    {
        /* p_obj->bip_errors can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_UNITS))
    {
        /* p_obj->bip_units can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_SYMBOLS))
    {
        /* p_obj->fec_corrected_symbols can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_CORRECTED))
    {
        /* p_obj->fec_codewords_corrected can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTABLE))
    {
        /* p_obj->fec_codewords_uncorrectable can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS))
    {
        /* p_obj->fec_codewords can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_UNITS))
    {
        /* p_obj->fec_corrected_units can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_KEY_ERRORS))
    {
        /* p_obj->xgem_key_errors can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_LOSS))
    {
        /* p_obj->xgem_loss can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR))
    {
        /* p_obj->rx_ploams_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE))
    {
        /* p_obj->rx_ploams_non_idle can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI))
    {
        /* p_obj->rx_omci can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR))
    {
        /* p_obj->rx_omci_packets_crc_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PACKETS))
    {
        /* p_obj->rx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_BYTES))
    {
        /* p_obj->tx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_PACKETS))
    {
        /* p_obj->tx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BER_REPORTED))
    {
        /* p_obj->ber_reported can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_LCDG_ERRORS))
    {
        /* p_obj->lcdg_errors can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RDI_ERRORS))
    {
        /* p_obj->rdi_errors can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_set_onu_state_data_set_default(
    bcmolt_onu_set_onu_state_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->onu_state = BCMOLT_ONU_OPERATION_INACTIVE;
    p_obj->measure_rssi = BCMOS_FALSE;
}

bcmos_bool bcmolt_onu_set_onu_state_data_validate(
    const bcmolt_onu_set_onu_state_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SET_ONU_STATE_DATA_ID_ONU_STATE))
    {
        switch (p_obj->onu_state)
        {
        case BCMOLT_ONU_OPERATION_INACTIVE:
        case BCMOLT_ONU_OPERATION_ACTIVE:
        case BCMOLT_ONU_OPERATION_DISABLE:
        case BCMOLT_ONU_OPERATION_ENABLE:
        case BCMOLT_ONU_OPERATION_ACTIVE_STANDBY:
        case BCMOLT_ONU_OPERATION_AWAKE_FREE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "onu_state: enum value %d is unexpected\n", (int)p_obj->onu_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SET_ONU_STATE_DATA_ID_MEASURE_RSSI))
    {
        /* p_obj->measure_rssi can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_request_registration_data_set_default(
    bcmolt_onu_request_registration_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->sma_flag = BCMOS_FALSE;
}

bcmos_bool bcmolt_onu_request_registration_data_validate(
    const bcmolt_onu_request_registration_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_REQUEST_REGISTRATION_DATA_ID_SMA_FLAG))
    {
        /* p_obj->sma_flag can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_change_power_levelling_data_set_default(
    bcmolt_onu_change_power_levelling_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->control = BCMOLT_POWER_LEVELLING_CONTROL_DIRECT;
    p_obj->attenuation = 0;
}

bcmos_bool bcmolt_onu_change_power_levelling_data_validate(
    const bcmolt_onu_change_power_levelling_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID_CONTROL))
    {
        switch (p_obj->control)
        {
        case BCMOLT_POWER_LEVELLING_CONTROL_DIRECT:
        case BCMOLT_POWER_LEVELLING_CONTROL_DECREASE:
        case BCMOLT_POWER_LEVELLING_CONTROL_INCREASE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "control: enum value %d is unexpected\n", (int)p_obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CHANGE_POWER_LEVELLING_DATA_ID_ATTENUATION))
    {
        /* p_obj->attenuation can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_adjust_tx_wavelength_data_set_default(
    bcmolt_onu_adjust_tx_wavelength_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->frequency_adjustment_direction = BCMOLT_FREQUENCY_ADJUSTMENT_DIRECTION_LOWER;
    p_obj->frequency_adjustment_size = 0;
}

bcmos_bool bcmolt_onu_adjust_tx_wavelength_data_validate(
    const bcmolt_onu_adjust_tx_wavelength_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID_FREQUENCY_ADJUSTMENT_DIRECTION))
    {
        switch (p_obj->frequency_adjustment_direction)
        {
        case BCMOLT_FREQUENCY_ADJUSTMENT_DIRECTION_LOWER:
        case BCMOLT_FREQUENCY_ADJUSTMENT_DIRECTION_HIGHER:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "frequency_adjustment_direction: enum value %d is unexpected\n", (int)p_obj->frequency_adjustment_direction);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ADJUST_TX_WAVELENGTH_DATA_ID_FREQUENCY_ADJUSTMENT_SIZE))
    {
        /* p_obj->frequency_adjustment_size can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_secure_mutual_authentication_data_set_default(
    bcmolt_onu_secure_mutual_authentication_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_aes_key_set_default(&p_obj->master_key);
    bcmolt_bin_str_set_default(&p_obj->buffer);
    p_obj->mic = 0UL;
}

bcmos_bool bcmolt_onu_secure_mutual_authentication_data_validate(
    const bcmolt_onu_secure_mutual_authentication_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID_MASTER_KEY))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "master_key.");
        if (!bcmolt_aes_key_validate(&p_obj->master_key, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "buffer.");
        if (!bcmolt_bin_str_validate(&p_obj->buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_DATA_ID_MIC))
    {
        /* p_obj->mic can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_tuning_out_data_set_default(
    bcmolt_onu_tuning_out_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_pon_id_set_default(&p_obj->target_ds_pon_id);
    bcmolt_pon_id_set_default(&p_obj->target_us_pon_id);
    p_obj->time_to_switch = 0UL;
    p_obj->rollback = BCMOS_FALSE;
    p_obj->status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_onu_tuning_out_data_validate(
    const bcmolt_onu_tuning_out_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TUNING_OUT_DATA_ID_TARGET_DS_PON_ID))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "target_ds_pon_id.");
        if (!bcmolt_pon_id_validate(&p_obj->target_ds_pon_id, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TUNING_OUT_DATA_ID_TARGET_US_PON_ID))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "target_us_pon_id.");
        if (!bcmolt_pon_id_validate(&p_obj->target_us_pon_id, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TUNING_OUT_DATA_ID_TIME_TO_SWITCH))
    {
        if (p_obj->time_to_switch < 500UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "time_to_switch: %u is less than the minimum value of 500\n", p_obj->time_to_switch);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TUNING_OUT_DATA_ID_ROLLBACK))
    {
        /* p_obj->rollback can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TUNING_OUT_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_xgpon_alarm_data_set_default(
    bcmolt_onu_xgpon_alarm_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_xgpon_onu_alarms_set_default(&p_obj->xgpon_onu_alarm);
}

bcmos_bool bcmolt_onu_xgpon_alarm_data_validate(
    const bcmolt_onu_xgpon_alarm_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_XGPON_ALARM_DATA_ID_XGPON_ONU_ALARM))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "xgpon_onu_alarm.");
        if (!bcmolt_xgpon_onu_alarms_validate(&p_obj->xgpon_onu_alarm, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_gpon_alarm_data_set_default(
    bcmolt_onu_gpon_alarm_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_gpon_onu_alarms_set_default(&p_obj->gpon_onu_alarm);
}

bcmos_bool bcmolt_onu_gpon_alarm_data_validate(
    const bcmolt_onu_gpon_alarm_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_GPON_ALARM_DATA_ID_GPON_ONU_ALARM))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "gpon_onu_alarm.");
        if (!bcmolt_gpon_onu_alarms_validate(&p_obj->gpon_onu_alarm, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_dowi_data_set_default(
    bcmolt_onu_dowi_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
    p_obj->drift_value = 0L;
    p_obj->new_eqd = 0UL;
}

bcmos_bool bcmolt_onu_dowi_data_validate(
    const bcmolt_onu_dowi_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_DOWI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_DOWI_DATA_ID_DRIFT_VALUE))
    {
        /* p_obj->drift_value can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_DOWI_DATA_ID_NEW_EQD))
    {
        /* p_obj->new_eqd can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_sfi_data_set_default(
    bcmolt_onu_sfi_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
    p_obj->ber = 0UL;
}

bcmos_bool bcmolt_onu_sfi_data_validate(
    const bcmolt_onu_sfi_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SFI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SFI_DATA_ID_BER))
    {
        /* p_obj->ber can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_sdi_data_set_default(
    bcmolt_onu_sdi_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
    p_obj->ber = 0UL;
}

bcmos_bool bcmolt_onu_sdi_data_validate(
    const bcmolt_onu_sdi_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SDI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SDI_DATA_ID_BER))
    {
        /* p_obj->ber can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_dfi_data_set_default(
    bcmolt_onu_dfi_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_onu_dfi_data_validate(
    const bcmolt_onu_dfi_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_DFI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_pqsi_data_set_default(
    bcmolt_onu_pqsi_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_onu_pqsi_data_validate(
    const bcmolt_onu_pqsi_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PQSI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_sufi_data_set_default(
    bcmolt_onu_sufi_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_onu_sufi_data_validate(
    const bcmolt_onu_sufi_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SUFI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_tiwi_data_set_default(
    bcmolt_onu_tiwi_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
    p_obj->drift_value = 0L;
}

bcmos_bool bcmolt_onu_tiwi_data_validate(
    const bcmolt_onu_tiwi_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TIWI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TIWI_DATA_ID_DRIFT_VALUE))
    {
        /* p_obj->drift_value can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_looci_data_set_default(
    bcmolt_onu_looci_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_onu_looci_data_validate(
    const bcmolt_onu_looci_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_LOOCI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_loai_data_set_default(
    bcmolt_onu_loai_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_onu_loai_data_validate(
    const bcmolt_onu_loai_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_LOAI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_dgi_data_set_default(
    bcmolt_onu_dgi_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_onu_dgi_data_validate(
    const bcmolt_onu_dgi_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_DGI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_pee_data_set_default(
    bcmolt_onu_pee_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_onu_pee_data_validate(
    const bcmolt_onu_pee_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PEE_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_pst_data_set_default(
    bcmolt_onu_pst_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->link_number = 0UL;
    p_obj->k1 = 0;
    p_obj->k2 = 0;
}

bcmos_bool bcmolt_onu_pst_data_validate(
    const bcmolt_onu_pst_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PST_DATA_ID_LINK_NUMBER))
    {
        /* p_obj->link_number can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PST_DATA_ID_K1))
    {
        /* p_obj->k1 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PST_DATA_ID_K2))
    {
        /* p_obj->k2 can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_ranging_completed_data_set_default(
    bcmolt_onu_ranging_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_RANGING_FAIL_REASON_NONE;
    p_obj->eqd = 0UL;
    p_obj->number_of_ploams = 0;
}

bcmos_bool bcmolt_onu_ranging_completed_data_validate(
    const bcmolt_onu_ranging_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_RANGING_FAIL_REASON_NONE:
        case BCMOLT_RANGING_FAIL_REASON_RANGING_ACK_TIMEOUT:
        case BCMOLT_RANGING_FAIL_REASON_PLOAM_DATA_MISMATCH:
        case BCMOLT_RANGING_FAIL_REASON_PLOAM_TYPE_MISMATCH:
        case BCMOLT_RANGING_FAIL_REASON_PLOAM_ONU_ID_MISMATCH:
        case BCMOLT_RANGING_FAIL_REASON_DRIFT_EXCEEDED:
        case BCMOLT_RANGING_FAIL_REASON_NO_PLOAM_RECEIVED:
        case BCMOLT_RANGING_FAIL_REASON_LOS:
        case BCMOLT_RANGING_FAIL_REASON_ALARMS:
        case BCMOLT_RANGING_FAIL_REASON_FORCE_DEACTIVATE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_EQD))
    {
        /* p_obj->eqd can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_RANGING_COMPLETED_DATA_ID_NUMBER_OF_PLOAMS))
    {
        /* p_obj->number_of_ploams can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_onu_activation_completed_data_set_default(
    bcmolt_onu_onu_activation_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_ACTIVATION_FAIL_REASON_NONE;
    bcmolt_bin_str_36_set_default(&p_obj->registration_id);
    bcmolt_xgpon_onu_registration_keys_set_default(&p_obj->registration_encryption_keys);
    bcmolt_rssi_measurement_result_set_default(&p_obj->rssi_measurement);
}

bcmos_bool bcmolt_onu_onu_activation_completed_data_validate(
    const bcmolt_onu_onu_activation_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_ACTIVATION_FAIL_REASON_NONE:
        case BCMOLT_ACTIVATION_FAIL_REASON_RANGING:
        case BCMOLT_ACTIVATION_FAIL_REASON_PASSWORD_AUTHENTICATION:
        case BCMOLT_ACTIVATION_FAIL_REASON_LOS:
        case BCMOLT_ACTIVATION_FAIL_REASON_ONU_ALARM:
        case BCMOLT_ACTIVATION_FAIL_REASON_SWITCH_OVER:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_REGISTRATION_ID))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "registration_id.");
        if (!bcmolt_bin_str_36_validate(&p_obj->registration_id, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_REGISTRATION_ENCRYPTION_KEYS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "registration_encryption_keys.");
        if (!bcmolt_xgpon_onu_registration_keys_validate(&p_obj->registration_encryption_keys, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_ACTIVATION_COMPLETED_DATA_ID_RSSI_MEASUREMENT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rssi_measurement.");
        if (!bcmolt_rssi_measurement_result_validate(&p_obj->rssi_measurement, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_onu_deactivation_completed_data_set_default(
    bcmolt_onu_onu_deactivation_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_DEACTIVATION_FAIL_REASON_NONE;
}

bcmos_bool bcmolt_onu_onu_deactivation_completed_data_validate(
    const bcmolt_onu_onu_deactivation_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_DEACTIVATION_COMPLETED_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_DEACTIVATION_FAIL_REASON_NONE:
        case BCMOLT_DEACTIVATION_FAIL_REASON_FAIL:
        case BCMOLT_DEACTIVATION_FAIL_REASON_SWITCH_OVER:
        case BCMOLT_DEACTIVATION_FAIL_REASON_FORCE_DEACTIVATION:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_onu_enable_completed_data_set_default(
    bcmolt_onu_onu_enable_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_serial_number_set_default(&p_obj->serial_number);
}

bcmos_bool bcmolt_onu_onu_enable_completed_data_validate(
    const bcmolt_onu_onu_enable_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_ENABLE_COMPLETED_DATA_ID_SERIAL_NUMBER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "serial_number.");
        if (!bcmolt_serial_number_validate(&p_obj->serial_number, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_onu_disable_completed_data_set_default(
    bcmolt_onu_onu_disable_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_serial_number_set_default(&p_obj->serial_number);
    p_obj->fail_reason = BCMOLT_DEACTIVATION_FAIL_REASON_NONE;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_onu_onu_disable_completed_data_validate(
    const bcmolt_onu_onu_disable_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID_SERIAL_NUMBER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "serial_number.");
        if (!bcmolt_serial_number_validate(&p_obj->serial_number, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_DEACTIVATION_FAIL_REASON_NONE:
        case BCMOLT_DEACTIVATION_FAIL_REASON_FAIL:
        case BCMOLT_DEACTIVATION_FAIL_REASON_SWITCH_OVER:
        case BCMOLT_DEACTIVATION_FAIL_REASON_FORCE_DEACTIVATION:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_DISABLE_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_rssi_measurement_completed_data_set_default(
    bcmolt_onu_rssi_measurement_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_RSSI_MEASUREMENT_FAIL_REASON_NONE;
}

bcmos_bool bcmolt_onu_rssi_measurement_completed_data_validate(
    const bcmolt_onu_rssi_measurement_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_RSSI_MEASUREMENT_COMPLETED_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_RSSI_MEASUREMENT_FAIL_REASON_NONE:
        case BCMOLT_RSSI_MEASUREMENT_FAIL_REASON_NO_DELIMITER:
        case BCMOLT_RSSI_MEASUREMENT_FAIL_REASON_NO_ACCESS:
        case BCMOLT_RSSI_MEASUREMENT_FAIL_REASON_ONU_NO_LONGER_ACTIVE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_invalid_dbru_report_data_set_default(
    bcmolt_onu_invalid_dbru_report_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alloc_id = (bcmolt_alloc_id)0U;
}

bcmos_bool bcmolt_onu_invalid_dbru_report_data_validate(
    const bcmolt_onu_invalid_dbru_report_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_INVALID_DBRU_REPORT_DATA_ID_ALLOC_ID))
    {
        if (p_obj->alloc_id > (bcmolt_alloc_id)16383U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alloc_id: %u is greater than the maximum value of 16383\n", p_obj->alloc_id);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_key_exchange_completed_data_set_default(
    bcmolt_onu_key_exchange_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_itupon_onu_aes_key_set_default(&p_obj->new_key);
}

bcmos_bool bcmolt_onu_key_exchange_completed_data_validate(
    const bcmolt_onu_key_exchange_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_KEY_EXCHANGE_COMPLETED_DATA_ID_NEW_KEY))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "new_key.");
        if (!bcmolt_itupon_onu_aes_key_validate(&p_obj->new_key, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_key_exchange_key_mismatch_data_set_default(
    bcmolt_onu_key_exchange_key_mismatch_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_aes_key_set_default(&p_obj->expected_key);
    bcmolt_aes_key_set_default(&p_obj->received_key);
}

bcmos_bool bcmolt_onu_key_exchange_key_mismatch_data_validate(
    const bcmolt_onu_key_exchange_key_mismatch_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID_EXPECTED_KEY))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "expected_key.");
        if (!bcmolt_aes_key_validate(&p_obj->expected_key, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_KEY_EXCHANGE_KEY_MISMATCH_DATA_ID_RECEIVED_KEY))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "received_key.");
        if (!bcmolt_aes_key_validate(&p_obj->received_key, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_loki_data_set_default(
    bcmolt_onu_loki_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_onu_loki_data_validate(
    const bcmolt_onu_loki_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_LOKI_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_memi_data_set_default(
    bcmolt_onu_memi_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_bin_str_13_set_default(&p_obj->ploam_buffer);
}

bcmos_bool bcmolt_onu_memi_data_validate(
    const bcmolt_onu_memi_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_MEMI_DATA_ID_PLOAM_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ploam_buffer.");
        if (!bcmolt_bin_str_13_validate(&p_obj->ploam_buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_omci_port_id_configuration_completed_data_set_default(
    bcmolt_onu_omci_port_id_configuration_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->gem_port = (bcmolt_gem_port_id)0UL;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->operation = BCMOLT_OMCI_PORT_ID_OPERATION_CONFIGURE;
}

bcmos_bool bcmolt_onu_omci_port_id_configuration_completed_data_validate(
    const bcmolt_onu_omci_port_id_configuration_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID_GEM_PORT))
    {
        if (p_obj->gem_port > (bcmolt_gem_port_id)65536UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "gem_port: %u is greater than the maximum value of 65536\n", p_obj->gem_port);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_OMCI_PORT_ID_CONFIGURATION_COMPLETED_DATA_ID_OPERATION))
    {
        switch (p_obj->operation)
        {
        case BCMOLT_OMCI_PORT_ID_OPERATION_CONFIGURE:
        case BCMOLT_OMCI_PORT_ID_OPERATION_REMOVE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "operation: enum value %d is unexpected\n", (int)p_obj->operation);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_ber_interval_configuration_completed_data_set_default(
    bcmolt_onu_ber_interval_configuration_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->ber_interval = (bcmolt_ber_interval)0UL;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_onu_ber_interval_configuration_completed_data_validate(
    const bcmolt_onu_ber_interval_configuration_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID_BER_INTERVAL))
    {
        /* p_obj->ber_interval can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_BER_INTERVAL_CONFIGURATION_COMPLETED_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_err_data_set_default(
    bcmolt_onu_err_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->bip8_errors = 0UL;
}

bcmos_bool bcmolt_onu_err_data_validate(
    const bcmolt_onu_err_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ERR_DATA_ID_BIP8_ERRORS))
    {
        /* p_obj->bip8_errors can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_password_authentication_completed_data_set_default(
    bcmolt_onu_password_authentication_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_NONE;
    bcmolt_bin_str_10_set_default(&p_obj->password);
}

bcmos_bool bcmolt_onu_password_authentication_completed_data_validate(
    const bcmolt_onu_password_authentication_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_NONE:
        case BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_PASSWORD_INCONSISTENCY:
        case BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_PASSWORD_MISMATCH:
        case BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_PASSWORD_AUTHENTICATION_TIMEOUT:
        case BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_ONU_ALARM:
        case BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_LOS_EVENT:
        case BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_DISABLE_EVENT:
        case BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_SWITCH_OVER:
        case BCMOLT_PASSWORD_AUTHENTICATION_FAIL_REASON_FORCE_DEACTIVATION:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PASSWORD_AUTHENTICATION_COMPLETED_DATA_ID_PASSWORD))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "password.");
        if (!bcmolt_bin_str_10_validate(&p_obj->password, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_key_exchange_unconsecutive_index_data_set_default(
    bcmolt_onu_key_exchange_unconsecutive_index_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->expected_index = 0UL;
    p_obj->actual_index = 0UL;
}

bcmos_bool bcmolt_onu_key_exchange_unconsecutive_index_data_validate(
    const bcmolt_onu_key_exchange_unconsecutive_index_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID_EXPECTED_INDEX))
    {
        /* p_obj->expected_index can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_KEY_EXCHANGE_UNCONSECUTIVE_INDEX_DATA_ID_ACTUAL_INDEX))
    {
        /* p_obj->actual_index can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_key_exchange_decrypt_required_data_set_default(
    bcmolt_onu_key_exchange_decrypt_required_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_aes_key_set_default(&p_obj->new_key);
}

bcmos_bool bcmolt_onu_key_exchange_decrypt_required_data_validate(
    const bcmolt_onu_key_exchange_decrypt_required_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_KEY_EXCHANGE_DECRYPT_REQUIRED_DATA_ID_NEW_KEY))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "new_key.");
        if (!bcmolt_aes_key_validate(&p_obj->new_key, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_onu_activation_standby_completed_data_set_default(
    bcmolt_onu_onu_activation_standby_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_onu_onu_activation_standby_completed_data_validate(
    const bcmolt_onu_onu_activation_standby_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_ACTIVATION_STANDBY_COMPLETED_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_power_management_state_change_data_set_default(
    bcmolt_onu_power_management_state_change_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->old_state = BCMOLT_ONU_STATE_NOT_CONFIGURED;
    p_obj->new_state = BCMOLT_ONU_STATE_NOT_CONFIGURED;
    p_obj->reason = BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_POWER_MANAGEMENT_ENABLED;
}

bcmos_bool bcmolt_onu_power_management_state_change_data_validate(
    const bcmolt_onu_power_management_state_change_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID_OLD_STATE))
    {
        switch (p_obj->old_state)
        {
        case BCMOLT_ONU_STATE_NOT_CONFIGURED:
        case BCMOLT_ONU_STATE_INACTIVE:
        case BCMOLT_ONU_STATE_ACTIVE:
        case BCMOLT_ONU_STATE_ACTIVE_STANDBY:
        case BCMOLT_ONU_STATE_DISABLED:
        case BCMOLT_ONU_STATE_AWAKE_FREE:
        case BCMOLT_ONU_STATE_PROCESSING:
        case BCMOLT_ONU_STATE_LOW_POWER_DOZE:
        case BCMOLT_ONU_STATE_LOW_POWER_SLEEP:
        case BCMOLT_ONU_STATE_LOW_POWER_WATCH:
        case BCMOLT_ONU_STATE_UNAWARE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "old_state: enum value %d is unexpected\n", (int)p_obj->old_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_ONU_STATE_NOT_CONFIGURED:
        case BCMOLT_ONU_STATE_INACTIVE:
        case BCMOLT_ONU_STATE_ACTIVE:
        case BCMOLT_ONU_STATE_ACTIVE_STANDBY:
        case BCMOLT_ONU_STATE_DISABLED:
        case BCMOLT_ONU_STATE_AWAKE_FREE:
        case BCMOLT_ONU_STATE_PROCESSING:
        case BCMOLT_ONU_STATE_LOW_POWER_DOZE:
        case BCMOLT_ONU_STATE_LOW_POWER_SLEEP:
        case BCMOLT_ONU_STATE_LOW_POWER_WATCH:
        case BCMOLT_ONU_STATE_UNAWARE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_POWER_MANAGEMENT_STATE_CHANGE_DATA_ID_REASON))
    {
        switch (p_obj->reason)
        {
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_POWER_MANAGEMENT_ENABLED:
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_POWER_MANAGEMENT_DISABLED:
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_SLEEP_REQUEST_AWAKE:
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_SLEEP_REQUEST_DOZE:
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_SLEEP_REQUEST_SLEEP:
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_SLEEP_REQUEST_WATCH:
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_TERI_EXPIRED:
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_TALERTED_EXPIRED:
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_ALARM:
        case BCMOLT_POWER_MANAGEMENT_TRANSITION_REASON_FORCE_DEACTIVATION:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "reason: enum value %d is unexpected\n", (int)p_obj->reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_possible_drift_data_set_default(
    bcmolt_onu_possible_drift_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->alarm_status = BCMOLT_STATUS_OFF;
    p_obj->estimated_drift = 0L;
}

bcmos_bool bcmolt_onu_possible_drift_data_validate(
    const bcmolt_onu_possible_drift_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID_ALARM_STATUS))
    {
        switch (p_obj->alarm_status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "alarm_status: enum value %d is unexpected\n", (int)p_obj->alarm_status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_POSSIBLE_DRIFT_DATA_ID_ESTIMATED_DRIFT))
    {
        /* p_obj->estimated_drift can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_registration_id_data_set_default(
    bcmolt_onu_registration_id_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_bin_str_36_set_default(&p_obj->registration_id);
    p_obj->request_registration_status = BCMOLT_RESULT_SUCCESS;
    p_obj->request_registration_fail_reason = BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_NONE;
}

bcmos_bool bcmolt_onu_registration_id_data_validate(
    const bcmolt_onu_registration_id_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_REGISTRATION_ID_DATA_ID_REGISTRATION_ID))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "registration_id.");
        if (!bcmolt_bin_str_36_validate(&p_obj->registration_id, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_REGISTRATION_ID_DATA_ID_REQUEST_REGISTRATION_STATUS))
    {
        switch (p_obj->request_registration_status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "request_registration_status: enum value %d is unexpected\n", (int)p_obj->request_registration_status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_REGISTRATION_ID_DATA_ID_REQUEST_REGISTRATION_FAIL_REASON))
    {
        switch (p_obj->request_registration_fail_reason)
        {
        case BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_NONE:
        case BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_REGISTRATION_PLOAM_TIMEOUT:
        case BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_ONU_ALARM:
        case BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_DEACTIVATION:
        case BCMOLT_REQUEST_REGISTRATION_FAIL_REASON_DISABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "request_registration_fail_reason: enum value %d is unexpected\n", (int)p_obj->request_registration_fail_reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_power_level_report_data_set_default(
    bcmolt_onu_power_level_report_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->attenuation = 0;
    p_obj->power_levelling_capability = 0;
}

bcmos_bool bcmolt_onu_power_level_report_data_validate(
    const bcmolt_onu_power_level_report_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID_ATTENUATION))
    {
        /* p_obj->attenuation can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_POWER_LEVEL_REPORT_DATA_ID_POWER_LEVELLING_CAPABILITY))
    {
        /* p_obj->power_levelling_capability can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_power_consumption_report_data_set_default(
    bcmolt_onu_power_consumption_report_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_arr_power_consumption_channel_report_8_set_default(&p_obj->power_consumption_report);
}

bcmos_bool bcmolt_onu_power_consumption_report_data_validate(
    const bcmolt_onu_power_consumption_report_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_POWER_CONSUMPTION_REPORT_DATA_ID_POWER_CONSUMPTION_REPORT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "power_consumption_report.");
        if (!bcmolt_arr_power_consumption_channel_report_8_validate(&p_obj->power_consumption_report, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_secure_mutual_authentication_failure_data_set_default(
    bcmolt_onu_secure_mutual_authentication_failure_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_SECURE_MUTUAL_AUTHENTICATION_FAIL_REASON_TIMEOUT;
}

bcmos_bool bcmolt_onu_secure_mutual_authentication_failure_data_validate(
    const bcmolt_onu_secure_mutual_authentication_failure_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_SECURE_MUTUAL_AUTHENTICATION_FAILURE_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_SECURE_MUTUAL_AUTHENTICATION_FAIL_REASON_TIMEOUT:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_onu_tuning_out_completed_data_set_default(
    bcmolt_onu_onu_tuning_out_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_TUNE_OUT_FAIL_REASON_NONE;
}

bcmos_bool bcmolt_onu_onu_tuning_out_completed_data_validate(
    const bcmolt_onu_onu_tuning_out_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_TUNING_OUT_COMPLETED_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_TUNE_OUT_FAIL_REASON_NONE:
        case BCMOLT_TUNE_OUT_FAIL_REASON_NACK_PLOAM_RECEIVED:
        case BCMOLT_TUNE_OUT_FAIL_REASON_NO_TUNING_RESPONSE_PLOAM_RECEIVED:
        case BCMOLT_TUNE_OUT_FAIL_REASON_TSOURCE_TIMEOUT:
        case BCMOLT_TUNE_OUT_FAIL_REASON_ROLLBACK_REQUEST:
        case BCMOLT_TUNE_OUT_FAIL_REASON_SWITCH_OVER:
        case BCMOLT_TUNE_OUT_FAIL_REASON_FORCE_DEACTIVATE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_onu_tuning_in_completed_data_set_default(
    bcmolt_onu_onu_tuning_in_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_TUNE_IN_FAIL_REASON_NONE;
}

bcmos_bool bcmolt_onu_onu_tuning_in_completed_data_validate(
    const bcmolt_onu_onu_tuning_in_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ONU_TUNING_IN_COMPLETED_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_TUNE_IN_FAIL_REASON_NONE:
        case BCMOLT_TUNE_IN_FAIL_REASON_NO_TUNING_RESPONSE_PLOAM_RECEIVED:
        case BCMOLT_TUNE_IN_FAIL_REASON_ONU_ACTIVATION_FAILED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_tuning_response_data_set_default(
    bcmolt_onu_tuning_response_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->ack = BCMOS_FALSE;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_onu_tuning_response_data_validate(
    const bcmolt_onu_tuning_response_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TUNING_RESPONSE_DATA_ID_ACK))
    {
        /* p_obj->ack can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TUNING_RESPONSE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_ploam_packet_data_set_default(
    bcmolt_onu_ploam_packet_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->default_key = BCMOS_FALSE;
    bcmolt_bin_str_40_set_default(&p_obj->ploam);
}

bcmos_bool bcmolt_onu_ploam_packet_data_validate(
    const bcmolt_onu_ploam_packet_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PLOAM_PACKET_DATA_ID_DEFAULT_KEY))
    {
        /* p_obj->default_key can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_PLOAM_PACKET_DATA_ID_PLOAM))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ploam.");
        if (!bcmolt_bin_str_40_validate(&p_obj->ploam, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_cpu_packets_data_set_default(
    bcmolt_onu_cpu_packets_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->packet_type = BCMOLT_PACKET_TYPE_ETH;
    p_obj->calc_crc = BCMOS_FALSE;
    p_obj->number_of_packets = 0;
    p_obj->packet_size = 0U;
    bcmolt_bin_str_set_default(&p_obj->buffer);
}

bcmos_bool bcmolt_onu_cpu_packets_data_validate(
    const bcmolt_onu_cpu_packets_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CPU_PACKETS_DATA_ID_PACKET_TYPE))
    {
        switch (p_obj->packet_type)
        {
        case BCMOLT_PACKET_TYPE_ETH:
        case BCMOLT_PACKET_TYPE_OMCI:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "packet_type: enum value %d is unexpected\n", (int)p_obj->packet_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CPU_PACKETS_DATA_ID_CALC_CRC))
    {
        /* p_obj->calc_crc can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CPU_PACKETS_DATA_ID_NUMBER_OF_PACKETS))
    {
        if (p_obj->number_of_packets > 32)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "number_of_packets: %u is greater than the maximum value of 32\n", p_obj->number_of_packets);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CPU_PACKETS_DATA_ID_PACKET_SIZE))
    {
        if (p_obj->packet_size > 2000U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "packet_size: %u is greater than the maximum value of 2000\n", p_obj->packet_size);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CPU_PACKETS_DATA_ID_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "buffer.");
        if (!bcmolt_bin_str_validate(&p_obj->buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_cpu_packet_data_set_default(
    bcmolt_onu_cpu_packet_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->port_id = 0U;
    p_obj->crc_ok = BCMOS_FALSE;
    p_obj->packet_size = 0UL;
    bcmolt_bin_str_set_default(&p_obj->buffer);
}

bcmos_bool bcmolt_onu_cpu_packet_data_validate(
    const bcmolt_onu_cpu_packet_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CPU_PACKET_DATA_ID_PORT_ID))
    {
        /* p_obj->port_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CPU_PACKET_DATA_ID_CRC_OK))
    {
        /* p_obj->crc_ok can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CPU_PACKET_DATA_ID_PACKET_SIZE))
    {
        /* p_obj->packet_size can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_CPU_PACKET_DATA_ID_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "buffer.");
        if (!bcmolt_bin_str_validate(&p_obj->buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_omci_packet_data_set_default(
    bcmolt_onu_omci_packet_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->port_id = 0U;
    p_obj->crc_ok = BCMOS_FALSE;
    p_obj->packet_size = 0UL;
    bcmolt_bin_str_set_default(&p_obj->buffer);
}

bcmos_bool bcmolt_onu_omci_packet_data_validate(
    const bcmolt_onu_omci_packet_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_OMCI_PACKET_DATA_ID_PORT_ID))
    {
        /* p_obj->port_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_OMCI_PACKET_DATA_ID_CRC_OK))
    {
        /* p_obj->crc_ok can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_OMCI_PACKET_DATA_ID_PACKET_SIZE))
    {
        /* p_obj->packet_size can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_OMCI_PACKET_DATA_ID_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "buffer.");
        if (!bcmolt_bin_str_validate(&p_obj->buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_rei_data_set_default(
    bcmolt_onu_rei_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->bip8_errors = 0UL;
}

bcmos_bool bcmolt_onu_rei_data_validate(
    const bcmolt_onu_rei_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_REI_DATA_ID_BIP8_ERRORS))
    {
        /* p_obj->bip8_errors can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_state_change_data_set_default(
    bcmolt_onu_state_change_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->new_onu_state = BCMOLT_ONU_OPERATION_INACTIVE;
}

bcmos_bool bcmolt_onu_state_change_data_validate(
    const bcmolt_onu_state_change_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_STATE_CHANGE_DATA_ID_NEW_ONU_STATE))
    {
        switch (p_obj->new_onu_state)
        {
        case BCMOLT_ONU_OPERATION_INACTIVE:
        case BCMOLT_ONU_OPERATION_ACTIVE:
        case BCMOLT_ONU_OPERATION_DISABLE:
        case BCMOLT_ONU_OPERATION_ENABLE:
        case BCMOLT_ONU_OPERATION_ACTIVE_STANDBY:
        case BCMOLT_ONU_OPERATION_AWAKE_FREE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_onu_state: enum value %d is unexpected\n", (int)p_obj->new_onu_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_range_value_changed_data_set_default(
    bcmolt_onu_range_value_changed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->range_value_tq = (bcmolt_time_quanta)0UL;
}

bcmos_bool bcmolt_onu_range_value_changed_data_validate(
    const bcmolt_onu_range_value_changed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_RANGE_VALUE_CHANGED_DATA_ID_RANGE_VALUE_TQ))
    {
        /* p_obj->range_value_tq can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_xpon_unknown_ploam_data_set_default(
    bcmolt_onu_xpon_unknown_ploam_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_bin_str_48_set_default(&p_obj->ploam_buffer);
}

bcmos_bool bcmolt_onu_xpon_unknown_ploam_data_validate(
    const bcmolt_onu_xpon_unknown_ploam_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_XPON_UNKNOWN_PLOAM_DATA_ID_PLOAM_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ploam_buffer.");
        if (!bcmolt_bin_str_48_validate(&p_obj->ploam_buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_trap_ploam_received_data_set_default(
    bcmolt_onu_trap_ploam_received_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->message_id = 0;
    p_obj->onu_id = 0U;
    bcmolt_u8_list_u8_hex_set_default(&p_obj->data);
}

bcmos_bool bcmolt_onu_trap_ploam_received_data_validate(
    const bcmolt_onu_trap_ploam_received_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID_MESSAGE_ID))
    {
        /* p_obj->message_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID_ONU_ID))
    {
        /* p_obj->onu_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_TRAP_PLOAM_RECEIVED_DATA_ID_DATA))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "data.");
        if (!bcmolt_u8_list_u8_hex_validate(&p_obj->data, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_itu_alloc_onu_accumulated_stats_data_set_default(
    bcmolt_onu_itu_alloc_onu_accumulated_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->tm_used = 0ULL;
    p_obj->tm_allocated = 0ULL;
    p_obj->bufocc = 0ULL;
    p_obj->used_cbr = 0ULL;
    p_obj->used_guaranteed_above_cbr = 0ULL;
    p_obj->used_additional = 0ULL;
}

bcmos_bool bcmolt_onu_itu_alloc_onu_accumulated_stats_data_validate(
    const bcmolt_onu_itu_alloc_onu_accumulated_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED))
    {
        /* p_obj->tm_used can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_ALLOCATED))
    {
        /* p_obj->tm_allocated can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_BUFOCC))
    {
        /* p_obj->bufocc can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_CBR))
    {
        /* p_obj->used_cbr can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_GUARANTEED_ABOVE_CBR))
    {
        /* p_obj->used_guaranteed_above_cbr can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_ADDITIONAL))
    {
        /* p_obj->used_additional can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_itu_pon_stats_cfg_data_set_default(
    bcmolt_onu_itu_pon_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->positive_drift);
    bcmolt_stat_alarm_config_set_default(&p_obj->negative_drift);
    bcmolt_stat_alarm_config_set_default(&p_obj->delimiter_miss_detection);
    bcmolt_stat_alarm_config_set_default(&p_obj->bip_errors);
    bcmolt_stat_alarm_config_set_default(&p_obj->bip_units);
    bcmolt_stat_alarm_config_set_default(&p_obj->fec_corrected_symbols);
    bcmolt_stat_alarm_config_set_default(&p_obj->fec_codewords_corrected);
    bcmolt_stat_alarm_config_set_default(&p_obj->fec_codewords_uncorrectable);
    bcmolt_stat_alarm_config_set_default(&p_obj->fec_codewords);
    bcmolt_stat_alarm_config_set_default(&p_obj->fec_corrected_units);
    bcmolt_stat_alarm_config_set_default(&p_obj->xgem_key_errors);
    bcmolt_stat_alarm_config_set_default(&p_obj->xgem_loss);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_ploams_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_ploams_non_idle);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_omci);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_omci_packets_crc_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->ber_reported);
    bcmolt_stat_alarm_config_set_default(&p_obj->lcdg_errors);
    bcmolt_stat_alarm_config_set_default(&p_obj->rdi_errors);
}

bcmos_bool bcmolt_onu_itu_pon_stats_cfg_data_validate(
    const bcmolt_onu_itu_pon_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_POSITIVE_DRIFT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "positive_drift.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->positive_drift, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_NEGATIVE_DRIFT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "negative_drift.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->negative_drift, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_DELIMITER_MISS_DETECTION))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "delimiter_miss_detection.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->delimiter_miss_detection, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_BIP_ERRORS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "bip_errors.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->bip_errors, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_BIP_UNITS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "bip_units.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->bip_units, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CORRECTED_SYMBOLS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "fec_corrected_symbols.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->fec_corrected_symbols, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS_CORRECTED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "fec_codewords_corrected.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->fec_codewords_corrected, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS_UNCORRECTABLE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "fec_codewords_uncorrectable.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->fec_codewords_uncorrectable, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "fec_codewords.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->fec_codewords, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_FEC_CORRECTED_UNITS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "fec_corrected_units.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->fec_corrected_units, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_XGEM_KEY_ERRORS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "xgem_key_errors.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->xgem_key_errors, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_XGEM_LOSS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "xgem_loss.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->xgem_loss, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_ploams_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_ploams_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_NON_IDLE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_ploams_non_idle.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_ploams_non_idle, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_omci.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_omci, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_omci_packets_crc_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_omci_packets_crc_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_TX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_TX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_BER_REPORTED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ber_reported.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->ber_reported, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_LCDG_ERRORS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "lcdg_errors.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->lcdg_errors, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_CFG_DATA_ID_RDI_ERRORS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rdi_errors.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rdi_errors, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_itu_pon_stats_alarm_raised_data_set_default(
    bcmolt_onu_itu_pon_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ONU_ITU_PON_STATS_DATA_ID_POSITIVE_DRIFT;
}

bcmos_bool bcmolt_onu_itu_pon_stats_alarm_raised_data_validate(
    const bcmolt_onu_itu_pon_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_POSITIVE_DRIFT:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_NEGATIVE_DRIFT:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_DELIMITER_MISS_DETECTION:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_ERRORS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_UNITS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_SYMBOLS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_CORRECTED:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTABLE:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_UNITS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_KEY_ERRORS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_LOSS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BER_REPORTED:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_LCDG_ERRORS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RDI_ERRORS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_itu_pon_stats_alarm_cleared_data_set_default(
    bcmolt_onu_itu_pon_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ONU_ITU_PON_STATS_DATA_ID_POSITIVE_DRIFT;
}

bcmos_bool bcmolt_onu_itu_pon_stats_alarm_cleared_data_validate(
    const bcmolt_onu_itu_pon_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_PON_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_POSITIVE_DRIFT:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_NEGATIVE_DRIFT:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_DELIMITER_MISS_DETECTION:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_ERRORS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BIP_UNITS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_SYMBOLS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_CORRECTED:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTABLE:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_FEC_CORRECTED_UNITS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_KEY_ERRORS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_XGEM_LOSS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_BER_REPORTED:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_LCDG_ERRORS:
        case BCMOLT_ONU_ITU_PON_STATS_DATA_ID_RDI_ERRORS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data_set_default(
    bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->tm_used);
    bcmolt_stat_alarm_config_set_default(&p_obj->tm_allocated);
    bcmolt_stat_alarm_config_set_default(&p_obj->bufocc);
    bcmolt_stat_alarm_config_set_default(&p_obj->used_cbr);
    bcmolt_stat_alarm_config_set_default(&p_obj->used_guaranteed_above_cbr);
    bcmolt_stat_alarm_config_set_default(&p_obj->used_additional);
}

bcmos_bool bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data_validate(
    const bcmolt_onu_itu_alloc_onu_accumulated_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_TM_USED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tm_used.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tm_used, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_TM_ALLOCATED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tm_allocated.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tm_allocated, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_BUFOCC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "bufocc.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->bufocc, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_USED_CBR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "used_cbr.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->used_cbr, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_USED_GUARANTEED_ABOVE_CBR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "used_guaranteed_above_cbr.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->used_guaranteed_above_cbr, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_CFG_DATA_ID_USED_ADDITIONAL))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "used_additional.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->used_additional, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data_set_default(
    bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED;
}

bcmos_bool bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data_validate(
    const bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_ALLOCATED:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_BUFOCC:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_CBR:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_GUARANTEED_ABOVE_CBR:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_ADDITIONAL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data_set_default(
    bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED;
}

bcmos_bool bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data_validate(
    const bcmolt_onu_itu_alloc_onu_accumulated_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_USED:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_TM_ALLOCATED:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_BUFOCC:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_CBR:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_GUARANTEED_ABOVE_CBR:
        case BCMOLT_ONU_ITU_ALLOC_ONU_ACCUMULATED_STATS_DATA_ID_USED_ADDITIONAL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_auto_cfg_data_set_default(
    bcmolt_onu_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->ber_interval_configuration_completed = BCMOS_FALSE;
    p_obj->cpu_packet = BCMOS_FALSE;
    p_obj->dfi = BCMOS_FALSE;
    p_obj->dgi = BCMOS_FALSE;
    p_obj->dowi = BCMOS_FALSE;
    p_obj->err = BCMOS_FALSE;
    p_obj->gpon_alarm = BCMOS_FALSE;
    p_obj->invalid_dbru_report = BCMOS_FALSE;
    p_obj->itu_alloc_onu_accumulated_stats_alarm_cleared = BCMOS_FALSE;
    p_obj->itu_alloc_onu_accumulated_stats_alarm_raised = BCMOS_FALSE;
    p_obj->itu_pon_stats_alarm_cleared = BCMOS_FALSE;
    p_obj->itu_pon_stats_alarm_raised = BCMOS_FALSE;
    p_obj->key_exchange_completed = BCMOS_FALSE;
    p_obj->key_exchange_cycle_skipped = BCMOS_FALSE;
    p_obj->key_exchange_decrypt_required = BCMOS_FALSE;
    p_obj->key_exchange_key_mismatch = BCMOS_FALSE;
    p_obj->key_exchange_key_request_timeout = BCMOS_FALSE;
    p_obj->key_exchange_unconsecutive_index = BCMOS_FALSE;
    p_obj->loai = BCMOS_FALSE;
    p_obj->loki = BCMOS_FALSE;
    p_obj->looci = BCMOS_FALSE;
    p_obj->memi = BCMOS_FALSE;
    p_obj->omci_packet = BCMOS_FALSE;
    p_obj->omci_port_id_configuration_completed = BCMOS_FALSE;
    p_obj->onu_activation_completed = BCMOS_FALSE;
    p_obj->onu_activation_standby_completed = BCMOS_FALSE;
    p_obj->onu_deactivation_completed = BCMOS_FALSE;
    p_obj->onu_disable_completed = BCMOS_FALSE;
    p_obj->onu_enable_completed = BCMOS_FALSE;
    p_obj->onu_ready_for_data_grant = BCMOS_FALSE;
    p_obj->onu_tuning_in_completed = BCMOS_FALSE;
    p_obj->onu_tuning_out_completed = BCMOS_FALSE;
    p_obj->optical_reflection = BCMOS_FALSE;
    p_obj->password_authentication_completed = BCMOS_FALSE;
    p_obj->pee = BCMOS_FALSE;
    p_obj->possible_drift = BCMOS_FALSE;
    p_obj->power_consumption_report = BCMOS_FALSE;
    p_obj->power_level_report = BCMOS_FALSE;
    p_obj->power_management_state_change = BCMOS_FALSE;
    p_obj->pqsi = BCMOS_FALSE;
    p_obj->pst = BCMOS_FALSE;
    p_obj->range_value_changed = BCMOS_FALSE;
    p_obj->ranging_completed = BCMOS_FALSE;
    p_obj->registration_id = BCMOS_FALSE;
    p_obj->rei = BCMOS_FALSE;
    p_obj->rssi_measurement_completed = BCMOS_FALSE;
    p_obj->sdi = BCMOS_FALSE;
    p_obj->secure_mutual_authentication_failure = BCMOS_FALSE;
    p_obj->sfi = BCMOS_FALSE;
    p_obj->state_change = BCMOS_FALSE;
    p_obj->sufi = BCMOS_FALSE;
    p_obj->tiwi = BCMOS_FALSE;
    p_obj->trap_ploam_received = BCMOS_FALSE;
    p_obj->tuning_response = BCMOS_FALSE;
    p_obj->xgpon_alarm = BCMOS_FALSE;
    p_obj->xpon_unknown_ploam = BCMOS_FALSE;
}

bcmos_bool bcmolt_onu_auto_cfg_data_validate(
    const bcmolt_onu_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_BER_INTERVAL_CONFIGURATION_COMPLETED))
    {
        /* p_obj->ber_interval_configuration_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_CPU_PACKET))
    {
        /* p_obj->cpu_packet can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_DFI))
    {
        /* p_obj->dfi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_DGI))
    {
        /* p_obj->dgi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_DOWI))
    {
        /* p_obj->dowi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ERR))
    {
        /* p_obj->err can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_GPON_ALARM))
    {
        /* p_obj->gpon_alarm can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_INVALID_DBRU_REPORT))
    {
        /* p_obj->invalid_dbru_report can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ITU_ALLOC_ONU_ACCUMULATED_STATS_ALARM_CLEARED))
    {
        /* p_obj->itu_alloc_onu_accumulated_stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ITU_ALLOC_ONU_ACCUMULATED_STATS_ALARM_RAISED))
    {
        /* p_obj->itu_alloc_onu_accumulated_stats_alarm_raised can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_CLEARED))
    {
        /* p_obj->itu_pon_stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_RAISED))
    {
        /* p_obj->itu_pon_stats_alarm_raised can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_COMPLETED))
    {
        /* p_obj->key_exchange_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_CYCLE_SKIPPED))
    {
        /* p_obj->key_exchange_cycle_skipped can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_DECRYPT_REQUIRED))
    {
        /* p_obj->key_exchange_decrypt_required can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_KEY_MISMATCH))
    {
        /* p_obj->key_exchange_key_mismatch can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_KEY_REQUEST_TIMEOUT))
    {
        /* p_obj->key_exchange_key_request_timeout can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_KEY_EXCHANGE_UNCONSECUTIVE_INDEX))
    {
        /* p_obj->key_exchange_unconsecutive_index can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_LOAI))
    {
        /* p_obj->loai can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_LOKI))
    {
        /* p_obj->loki can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_LOOCI))
    {
        /* p_obj->looci can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_MEMI))
    {
        /* p_obj->memi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_OMCI_PACKET))
    {
        /* p_obj->omci_packet can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_OMCI_PORT_ID_CONFIGURATION_COMPLETED))
    {
        /* p_obj->omci_port_id_configuration_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_ACTIVATION_COMPLETED))
    {
        /* p_obj->onu_activation_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_ACTIVATION_STANDBY_COMPLETED))
    {
        /* p_obj->onu_activation_standby_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_DEACTIVATION_COMPLETED))
    {
        /* p_obj->onu_deactivation_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_DISABLE_COMPLETED))
    {
        /* p_obj->onu_disable_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_ENABLE_COMPLETED))
    {
        /* p_obj->onu_enable_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_READY_FOR_DATA_GRANT))
    {
        /* p_obj->onu_ready_for_data_grant can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_TUNING_IN_COMPLETED))
    {
        /* p_obj->onu_tuning_in_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_ONU_TUNING_OUT_COMPLETED))
    {
        /* p_obj->onu_tuning_out_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_OPTICAL_REFLECTION))
    {
        /* p_obj->optical_reflection can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_PASSWORD_AUTHENTICATION_COMPLETED))
    {
        /* p_obj->password_authentication_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_PEE))
    {
        /* p_obj->pee can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_POSSIBLE_DRIFT))
    {
        /* p_obj->possible_drift can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_POWER_CONSUMPTION_REPORT))
    {
        /* p_obj->power_consumption_report can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_POWER_LEVEL_REPORT))
    {
        /* p_obj->power_level_report can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_POWER_MANAGEMENT_STATE_CHANGE))
    {
        /* p_obj->power_management_state_change can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_PQSI))
    {
        /* p_obj->pqsi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_PST))
    {
        /* p_obj->pst can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_RANGE_VALUE_CHANGED))
    {
        /* p_obj->range_value_changed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_RANGING_COMPLETED))
    {
        /* p_obj->ranging_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_REGISTRATION_ID))
    {
        /* p_obj->registration_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_REI))
    {
        /* p_obj->rei can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_RSSI_MEASUREMENT_COMPLETED))
    {
        /* p_obj->rssi_measurement_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_SDI))
    {
        /* p_obj->sdi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_SECURE_MUTUAL_AUTHENTICATION_FAILURE))
    {
        /* p_obj->secure_mutual_authentication_failure can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_SFI))
    {
        /* p_obj->sfi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_STATE_CHANGE))
    {
        /* p_obj->state_change can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_SUFI))
    {
        /* p_obj->sufi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_TIWI))
    {
        /* p_obj->tiwi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_TRAP_PLOAM_RECEIVED))
    {
        /* p_obj->trap_ploam_received can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_TUNING_RESPONSE))
    {
        /* p_obj->tuning_response can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_XGPON_ALARM))
    {
        /* p_obj->xgpon_alarm can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_ONU_AUTO_CFG_DATA_ID_XPON_UNKNOWN_PLOAM))
    {
        /* p_obj->xpon_unknown_ploam can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pbit_to_tc_key_set_default(
    bcmolt_pbit_to_tc_key *p_obj)
{
    p_obj->id = 0U;
    p_obj->dir = (bcmolt_tm_sched_dir)0;
}

bcmos_bool bcmolt_pbit_to_tc_key_validate(
    const bcmolt_pbit_to_tc_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id < 1U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is less than the minimum value of 1\n", p_obj->id);
        return BCMOS_FALSE;
    }
    if (p_obj->id > 4096U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 4096\n", p_obj->id);
        return BCMOS_FALSE;
    }
    switch (p_obj->dir)
    {
    case BCMOLT_TM_SCHED_DIR_US:
    case BCMOLT_TM_SCHED_DIR_DS:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "dir: enum value %d is unexpected\n", (int)p_obj->dir);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_pbit_to_tc_cfg_data_set_default(
    bcmolt_pbit_to_tc_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_bin_str_8_set_default(&p_obj->tc);
}

bcmos_bool bcmolt_pbit_to_tc_cfg_data_validate(
    const bcmolt_pbit_to_tc_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PBIT_TO_TC_CFG_DATA_ID_TC))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tc.");
        if (!bcmolt_bin_str_8_validate(&p_obj->tc, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_policer_profile_key_set_default(
    bcmolt_policer_profile_key *p_obj)
{
    p_obj->id = (bcmolt_policer_profile_id)0U;
}

bcmos_bool bcmolt_policer_profile_key_validate(
    const bcmolt_policer_profile_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id < (bcmolt_policer_profile_id)1U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is less than the minimum value of 1\n", p_obj->id);
        return BCMOS_FALSE;
    }
    if (p_obj->id > (bcmolt_policer_profile_id)1023U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 1023\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_policer_profile_cfg_data_set_default(
    bcmolt_policer_profile_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    p_obj->type = BCMOLT_POLICER_TYPE_SR_TCM;
    p_obj->traffic_type = BCMOLT_TRAFFIC_TYPE_BROADCAST;
    p_obj->cir_kbps = 100UL;
    p_obj->eir_kbps = 50UL;
    p_obj->cbs_kb = 64UL;
    p_obj->ebs_kb = 32UL;
    p_obj->color_awareness = BCMOS_FALSE;
    p_obj->color_marking = BCMOS_FALSE;
}

bcmos_bool bcmolt_policer_profile_cfg_data_validate(
    const bcmolt_policer_profile_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_POLICER_PROFILE_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_POLICER_PROFILE_CFG_DATA_ID_TYPE))
    {
        switch (p_obj->type)
        {
        case BCMOLT_POLICER_TYPE_SR_TCM:
        case BCMOLT_POLICER_TYPE_TR_TCM_RFC4115:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "type: enum value %d is unexpected\n", (int)p_obj->type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_POLICER_PROFILE_CFG_DATA_ID_TRAFFIC_TYPE))
    {
        switch (p_obj->traffic_type)
        {
        case BCMOLT_TRAFFIC_TYPE_BROADCAST:
        case BCMOLT_TRAFFIC_TYPE_KNOWN_UNICAST:
        case BCMOLT_TRAFFIC_TYPE_UNK_UNICAST:
        case BCMOLT_TRAFFIC_TYPE_MULTICAST:
        case BCMOLT_TRAFFIC_TYPE_ALL_TRAFFIC:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "traffic_type: enum value %d is unexpected\n", (int)p_obj->traffic_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_POLICER_PROFILE_CFG_DATA_ID_CIR_KBPS))
    {
        if (p_obj->cir_kbps > 100000000UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "cir_kbps: %u is greater than the maximum value of 100000000\n", p_obj->cir_kbps);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_POLICER_PROFILE_CFG_DATA_ID_EIR_KBPS))
    {
        if (p_obj->eir_kbps > 100000000UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "eir_kbps: %u is greater than the maximum value of 100000000\n", p_obj->eir_kbps);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_POLICER_PROFILE_CFG_DATA_ID_CBS_KB))
    {
        if (p_obj->cbs_kb < 1UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "cbs_kb: %u is less than the minimum value of 1\n", p_obj->cbs_kb);
            return BCMOS_FALSE;
        }
        if (p_obj->cbs_kb > 33292UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "cbs_kb: %u is greater than the maximum value of 33292\n", p_obj->cbs_kb);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_POLICER_PROFILE_CFG_DATA_ID_EBS_KB))
    {
        if (p_obj->ebs_kb < 1UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "ebs_kb: %u is less than the minimum value of 1\n", p_obj->ebs_kb);
            return BCMOS_FALSE;
        }
        if (p_obj->ebs_kb > 33292UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "ebs_kb: %u is greater than the maximum value of 33292\n", p_obj->ebs_kb);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_POLICER_PROFILE_CFG_DATA_ID_COLOR_AWARENESS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "color_awareness: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_POLICER_PROFILE_CFG_DATA_ID_COLOR_MARKING))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "color_marking: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_key_set_default(
    bcmolt_pon_interface_key *p_obj)
{
    p_obj->pon_ni = (bcmolt_pon_ni)0;
}

bcmos_bool bcmolt_pon_interface_key_validate(
    const bcmolt_pon_interface_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->pon_ni > (bcmolt_pon_ni)15)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "pon_ni: %u is greater than the maximum value of 15\n", p_obj->pon_ni);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_cfg_data_set_default(
    bcmolt_pon_interface_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_INTERFACE_STATE_INACTIVE;
    p_obj->pon_type = BCMOLT_PON_TYPE_UNKNOWN;
    p_obj->los_status = BCMOLT_STATUS_OFF;
    p_obj->los_initial_value = BCMOLT_STATUS_OFF;
    bcmolt_service_discovery_set_default(&p_obj->discovery);
    bcmolt_itu_pon_params_set_default(&p_obj->itu);
    bcmolt_pon_distance_set_default(&p_obj->pon_distance);
    p_obj->number_of_active_onus = 0U;
    p_obj->number_of_active_standby_onus = 0U;
    bcmolt_gpon_trx_set_default(&p_obj->gpon_trx);
    bcmolt_xgpon_trx_set_default(&p_obj->xgpon_trx);
    bcmolt_xgpon_trx_set_default(&p_obj->xgs_ngpon2_trx);
    p_obj->los_wait_timeout = 10UL;
}

bcmos_bool bcmolt_pon_interface_cfg_data_validate(
    const bcmolt_pon_interface_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_PON_TYPE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "pon_type: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_LOS_STATUS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "los_status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_LOS_INITIAL_VALUE))
    {
        switch (p_obj->los_initial_value)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "los_initial_value: enum value %d is unexpected\n", (int)p_obj->los_initial_value);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_DISCOVERY))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "discovery.");
        if (!bcmolt_service_discovery_validate(&p_obj->discovery, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_ITU))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "itu.");
        if (!bcmolt_itu_pon_params_validate(&p_obj->itu, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_PON_DISTANCE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "pon_distance.");
        if (!bcmolt_pon_distance_validate(&p_obj->pon_distance, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_NUMBER_OF_ACTIVE_ONUS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "number_of_active_onus: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_NUMBER_OF_ACTIVE_STANDBY_ONUS))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "number_of_active_standby_onus: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_GPON_TRX))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "gpon_trx.");
        if (!bcmolt_gpon_trx_validate(&p_obj->gpon_trx, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_XGPON_TRX))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "xgpon_trx.");
        if (!bcmolt_xgpon_trx_validate(&p_obj->xgpon_trx, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_XGS_NGPON2_TRX))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "xgs_ngpon2_trx.");
        if (!bcmolt_xgpon_trx_validate(&p_obj->xgs_ngpon2_trx, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CFG_DATA_ID_LOS_WAIT_TIMEOUT))
    {
        if (p_obj->los_wait_timeout > 1000UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "los_wait_timeout: %u is greater than the maximum value of 1000\n", p_obj->los_wait_timeout);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_itu_pon_stats_data_set_default(
    bcmolt_pon_interface_itu_pon_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->fec_codewords = 0ULL;
    p_obj->bip_units = 0ULL;
    p_obj->bip_errors = 0ULL;
    p_obj->rx_gem = 0ULL;
    p_obj->rx_gem_dropped = 0ULL;
    p_obj->rx_gem_idle = 0ULL;
    p_obj->rx_gem_corrected = 0ULL;
    p_obj->rx_crc_error = 0ULL;
    p_obj->rx_fragment_error = 0ULL;
    p_obj->rx_packets_dropped = 0ULL;
    p_obj->rx_dropped_too_short = 0ULL;
    p_obj->rx_dropped_too_long = 0ULL;
    p_obj->rx_key_error = 0ULL;
    p_obj->rx_cpu_omci_packets_dropped = 0;
    p_obj->tx_ploams = 0ULL;
    p_obj->rx_ploams_dropped = 0ULL;
    p_obj->rx_allocations_valid = 0ULL;
    p_obj->rx_allocations_invalid = 0ULL;
    p_obj->rx_allocations_disabled = 0ULL;
    p_obj->rx_ploams = 0ULL;
    p_obj->rx_ploams_non_idle = 0ULL;
    p_obj->rx_ploams_error = 0ULL;
    p_obj->rx_cpu = 0ULL;
    p_obj->rx_omci = 0ULL;
    p_obj->rx_omci_packets_crc_error = 0ULL;
    p_obj->tx_packets = 0ULL;
    p_obj->tx_gem = 0ULL;
    p_obj->tx_cpu = 0ULL;
    p_obj->tx_omci = 0ULL;
    p_obj->tx_dropped_illegal_length = 0ULL;
    p_obj->tx_dropped_tpid_miss = 0ULL;
    p_obj->tx_dropped_vid_miss = 0ULL;
    p_obj->tx_dropped_total = 0ULL;
    p_obj->rx_xgtc_headers = 0ULL;
    p_obj->rx_xgtc_corrected = 0ULL;
    p_obj->rx_xgtc_uncorrected = 0ULL;
    p_obj->fec_codewords_uncorrected = 0ULL;
    p_obj->rx_gem_illegal = 0ULL;
    p_obj->rx_packets = 0ULL;
    p_obj->tx_bytes = 0ULL;
    p_obj->rx_bytes = 0ULL;
}

bcmos_bool bcmolt_pon_interface_itu_pon_stats_data_validate(
    const bcmolt_pon_interface_itu_pon_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS))
    {
        /* p_obj->fec_codewords can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_UNITS))
    {
        /* p_obj->bip_units can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_ERRORS))
    {
        /* p_obj->bip_errors can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM))
    {
        /* p_obj->rx_gem can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_DROPPED))
    {
        /* p_obj->rx_gem_dropped can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_IDLE))
    {
        /* p_obj->rx_gem_idle can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_CORRECTED))
    {
        /* p_obj->rx_gem_corrected can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CRC_ERROR))
    {
        /* p_obj->rx_crc_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_FRAGMENT_ERROR))
    {
        /* p_obj->rx_fragment_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS_DROPPED))
    {
        /* p_obj->rx_packets_dropped can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_SHORT))
    {
        /* p_obj->rx_dropped_too_short can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_LONG))
    {
        /* p_obj->rx_dropped_too_long can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_KEY_ERROR))
    {
        /* p_obj->rx_key_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU_OMCI_PACKETS_DROPPED))
    {
        /* p_obj->rx_cpu_omci_packets_dropped can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PLOAMS))
    {
        /* p_obj->tx_ploams can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_DROPPED))
    {
        /* p_obj->rx_ploams_dropped can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_VALID))
    {
        /* p_obj->rx_allocations_valid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_INVALID))
    {
        /* p_obj->rx_allocations_invalid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_DISABLED))
    {
        /* p_obj->rx_allocations_disabled can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS))
    {
        /* p_obj->rx_ploams can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE))
    {
        /* p_obj->rx_ploams_non_idle can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR))
    {
        /* p_obj->rx_ploams_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU))
    {
        /* p_obj->rx_cpu can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI))
    {
        /* p_obj->rx_omci can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR))
    {
        /* p_obj->rx_omci_packets_crc_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PACKETS))
    {
        /* p_obj->tx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_GEM))
    {
        /* p_obj->tx_gem can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_CPU))
    {
        /* p_obj->tx_cpu can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_OMCI))
    {
        /* p_obj->tx_omci can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_ILLEGAL_LENGTH))
    {
        /* p_obj->tx_dropped_illegal_length can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TPID_MISS))
    {
        /* p_obj->tx_dropped_tpid_miss can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_VID_MISS))
    {
        /* p_obj->tx_dropped_vid_miss can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TOTAL))
    {
        /* p_obj->tx_dropped_total can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_HEADERS))
    {
        /* p_obj->rx_xgtc_headers can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_CORRECTED))
    {
        /* p_obj->rx_xgtc_corrected can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_UNCORRECTED))
    {
        /* p_obj->rx_xgtc_uncorrected can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTED))
    {
        /* p_obj->fec_codewords_uncorrected can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_ILLEGAL))
    {
        /* p_obj->rx_gem_illegal can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS))
    {
        /* p_obj->rx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_BYTES))
    {
        /* p_obj->tx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_ae_stats_data_set_default(
    bcmolt_pon_interface_ae_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rx_bytes = 0ULL;
    p_obj->rx_frames = 0ULL;
    p_obj->rx_frames_64 = 0ULL;
    p_obj->rx_frames_65_127 = 0ULL;
    p_obj->rx_frames_128_255 = 0ULL;
    p_obj->rx_frames_256_511 = 0ULL;
    p_obj->rx_frames_512_1023 = 0ULL;
    p_obj->rx_frames_1024_1518 = 0ULL;
    p_obj->rx_frames_1519_2047 = 0ULL;
    p_obj->rx_frames_2048_4095 = 0ULL;
    p_obj->rx_frames_4096_9216 = 0ULL;
    p_obj->rx_frames_9217_16383 = 0ULL;
    p_obj->rx_broadcast_frames = 0ULL;
    p_obj->rx_data_bytes = 0ULL;
    p_obj->rx_multicast_frames = 0ULL;
    p_obj->rx_unicast_frames = 0ULL;
    p_obj->rx_abort_frames = 0ULL;
    p_obj->rx_fcs_error = 0ULL;
    p_obj->rx_oversize_error = 0ULL;
    p_obj->rx_runt_error = 0ULL;
    p_obj->tx_bytes = 0ULL;
    p_obj->tx_frames = 0ULL;
    p_obj->tx_frames_64 = 0ULL;
    p_obj->tx_frames_65_127 = 0ULL;
    p_obj->tx_frames_128_255 = 0ULL;
    p_obj->tx_frames_256_511 = 0ULL;
    p_obj->tx_frames_512_1023 = 0ULL;
    p_obj->tx_frames_1024_1518 = 0ULL;
    p_obj->tx_frames_1519_2047 = 0ULL;
    p_obj->tx_frames_2048_4095 = 0ULL;
    p_obj->tx_frames_4096_9216 = 0ULL;
    p_obj->tx_frames_9217_16383 = 0ULL;
    p_obj->tx_broadcast_frames = 0ULL;
    p_obj->tx_data_bytes = 0ULL;
    p_obj->tx_multicast_frames = 0ULL;
    p_obj->tx_unicast_frames = 0ULL;
    p_obj->tx_abort_frames = 0ULL;
}

bcmos_bool bcmolt_pon_interface_ae_stats_data_validate(
    const bcmolt_pon_interface_ae_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES))
    {
        /* p_obj->rx_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_64))
    {
        /* p_obj->rx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_65_127))
    {
        /* p_obj->rx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_128_255))
    {
        /* p_obj->rx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_256_511))
    {
        /* p_obj->rx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_512_1023))
    {
        /* p_obj->rx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1024_1518))
    {
        /* p_obj->rx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1519_2047))
    {
        /* p_obj->rx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_2048_4095))
    {
        /* p_obj->rx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_4096_9216))
    {
        /* p_obj->rx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_9217_16383))
    {
        /* p_obj->rx_frames_9217_16383 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BROADCAST_FRAMES))
    {
        /* p_obj->rx_broadcast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_DATA_BYTES))
    {
        /* p_obj->rx_data_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_MULTICAST_FRAMES))
    {
        /* p_obj->rx_multicast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_UNICAST_FRAMES))
    {
        /* p_obj->rx_unicast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_ABORT_FRAMES))
    {
        /* p_obj->rx_abort_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FCS_ERROR))
    {
        /* p_obj->rx_fcs_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_OVERSIZE_ERROR))
    {
        /* p_obj->rx_oversize_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_RUNT_ERROR))
    {
        /* p_obj->rx_runt_error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BYTES))
    {
        /* p_obj->tx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES))
    {
        /* p_obj->tx_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_64))
    {
        /* p_obj->tx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_65_127))
    {
        /* p_obj->tx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_128_255))
    {
        /* p_obj->tx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_256_511))
    {
        /* p_obj->tx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_512_1023))
    {
        /* p_obj->tx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1024_1518))
    {
        /* p_obj->tx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1519_2047))
    {
        /* p_obj->tx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_2048_4095))
    {
        /* p_obj->tx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_4096_9216))
    {
        /* p_obj->tx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_9217_16383))
    {
        /* p_obj->tx_frames_9217_16383 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BROADCAST_FRAMES))
    {
        /* p_obj->tx_broadcast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_DATA_BYTES))
    {
        /* p_obj->tx_data_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_MULTICAST_FRAMES))
    {
        /* p_obj->tx_multicast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_UNICAST_FRAMES))
    {
        /* p_obj->tx_unicast_frames can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_ABORT_FRAMES))
    {
        /* p_obj->tx_abort_frames can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_set_pon_interface_state_data_set_default(
    bcmolt_pon_interface_set_pon_interface_state_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->operation = BCMOLT_INTERFACE_OPERATION_INACTIVE;
}

bcmos_bool bcmolt_pon_interface_set_pon_interface_state_data_validate(
    const bcmolt_pon_interface_set_pon_interface_state_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_SET_PON_INTERFACE_STATE_DATA_ID_OPERATION))
    {
        switch (p_obj->operation)
        {
        case BCMOLT_INTERFACE_OPERATION_INACTIVE:
        case BCMOLT_INTERFACE_OPERATION_ACTIVE_WORKING:
        case BCMOLT_INTERFACE_OPERATION_ACTIVE_STANDBY:
        case BCMOLT_INTERFACE_OPERATION_DISABLE:
        case BCMOLT_INTERFACE_OPERATION_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "operation: enum value %d is unexpected\n", (int)p_obj->operation);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_set_onu_state_data_set_default(
    bcmolt_pon_interface_set_onu_state_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->onu_state = BCMOLT_ONU_OPERATION_INACTIVE;
}

bcmos_bool bcmolt_pon_interface_set_onu_state_data_validate(
    const bcmolt_pon_interface_set_onu_state_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_SET_ONU_STATE_DATA_ID_ONU_STATE))
    {
        switch (p_obj->onu_state)
        {
        case BCMOLT_ONU_OPERATION_INACTIVE:
        case BCMOLT_ONU_OPERATION_ACTIVE:
        case BCMOLT_ONU_OPERATION_DISABLE:
        case BCMOLT_ONU_OPERATION_ENABLE:
        case BCMOLT_ONU_OPERATION_ACTIVE_STANDBY:
        case BCMOLT_ONU_OPERATION_AWAKE_FREE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "onu_state: enum value %d is unexpected\n", (int)p_obj->onu_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_disable_serial_number_data_set_default(
    bcmolt_pon_interface_disable_serial_number_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->control = BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_UNICAST_DISABLE;
    bcmolt_serial_number_set_default(&p_obj->serial_number);
}

bcmos_bool bcmolt_pon_interface_disable_serial_number_data_validate(
    const bcmolt_pon_interface_disable_serial_number_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID_CONTROL))
    {
        switch (p_obj->control)
        {
        case BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_UNICAST_DISABLE:
        case BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_UNICAST_ENABLE:
        case BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_BROADCAST_ENABLE:
        case BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_BROADCAST_DISABLE:
        case BCMOLT_DISABLE_SERIAL_NUMBER_CONTROL_DISABLE_DISCOVERY:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "control: enum value %d is unexpected\n", (int)p_obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_DISABLE_SERIAL_NUMBER_DATA_ID_SERIAL_NUMBER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "serial_number.");
        if (!bcmolt_serial_number_validate(&p_obj->serial_number, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_run_special_bw_map_data_set_default(
    bcmolt_pon_interface_run_special_bw_map_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->number_of_cycle = 0;
    p_obj->allocation_number = 0;
    p_obj->bw_map_array = 0;
}

bcmos_bool bcmolt_pon_interface_run_special_bw_map_data_validate(
    const bcmolt_pon_interface_run_special_bw_map_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID_NUMBER_OF_CYCLE))
    {
        /* p_obj->number_of_cycle can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID_ALLOCATION_NUMBER))
    {
        /* p_obj->allocation_number can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_RUN_SPECIAL_BW_MAP_DATA_ID_BW_MAP_ARRAY))
    {
        /* p_obj->bw_map_array can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_start_onu_upgrade_data_set_default(
    bcmolt_pon_interface_start_onu_upgrade_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_onu_id_list_u32_set_default(&p_obj->list_of_onu_ids);
}

bcmos_bool bcmolt_pon_interface_start_onu_upgrade_data_validate(
    const bcmolt_pon_interface_start_onu_upgrade_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_START_ONU_UPGRADE_DATA_ID_LIST_OF_ONU_IDS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "list_of_onu_ids.");
        if (!bcmolt_onu_id_list_u32_validate(&p_obj->list_of_onu_ids, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_set_default(
    bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->onu_state = BCMOLT_SWITCH_OVER_TYPE_C_ONU_STATE_ACTIVE;
    bcmolt_onu_id_list_u32_set_default(&p_obj->onu_list);
}

bcmos_bool bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data_validate(
    const bcmolt_pon_interface_protection_switching_type_c_set_multiple_onu_state_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID_ONU_STATE))
    {
        switch (p_obj->onu_state)
        {
        case BCMOLT_SWITCH_OVER_TYPE_C_ONU_STATE_ACTIVE:
        case BCMOLT_SWITCH_OVER_TYPE_C_ONU_STATE_ACTIVE_STANDBY:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "onu_state: enum value %d is unexpected\n", (int)p_obj->onu_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TYPE_C_SET_MULTIPLE_ONU_STATE_DATA_ID_ONU_LIST))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "onu_list.");
        if (!bcmolt_onu_id_list_u32_validate(&p_obj->onu_list, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_set_default(
    bcmolt_pon_interface_protection_switching_apply_rerange_delta_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rerange_delta = 0UL;
}

bcmos_bool bcmolt_pon_interface_protection_switching_apply_rerange_delta_data_validate(
    const bcmolt_pon_interface_protection_switching_apply_rerange_delta_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_APPLY_RERANGE_DELTA_DATA_ID_RERANGE_DELTA))
    {
        /* p_obj->rerange_delta can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_cpu_packets_data_set_default(
    bcmolt_pon_interface_cpu_packets_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->packet_type = BCMOLT_PACKET_TYPE_ETH;
    p_obj->calc_crc = BCMOS_FALSE;
    bcmolt_gem_port_id_list_u8_max_16_set_default(&p_obj->gem_port_list);
    bcmolt_bin_str_set_default(&p_obj->buffer);
}

bcmos_bool bcmolt_pon_interface_cpu_packets_data_validate(
    const bcmolt_pon_interface_cpu_packets_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_PACKET_TYPE))
    {
        switch (p_obj->packet_type)
        {
        case BCMOLT_PACKET_TYPE_ETH:
        case BCMOLT_PACKET_TYPE_OMCI:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "packet_type: enum value %d is unexpected\n", (int)p_obj->packet_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_CALC_CRC))
    {
        /* p_obj->calc_crc can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_GEM_PORT_LIST))
    {
        if (p_obj->gem_port_list.len > 16)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "gem_port_list: %u is greater than the maximum array length of 16\n", p_obj->gem_port_list.len);
            return BCMOS_FALSE;
        }
        int prefix_len = bcmolt_string_append(p_err_details, "gem_port_list.");
        if (!bcmolt_gem_port_id_list_u8_max_16_validate(&p_obj->gem_port_list, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CPU_PACKETS_DATA_ID_BUFFER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "buffer.");
        if (!bcmolt_bin_str_validate(&p_obj->buffer, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_broadcast_ploam_packet_data_set_default(
    bcmolt_pon_interface_broadcast_ploam_packet_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_bin_str_40_set_default(&p_obj->ploam);
}

bcmos_bool bcmolt_pon_interface_broadcast_ploam_packet_data_validate(
    const bcmolt_pon_interface_broadcast_ploam_packet_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_BROADCAST_PLOAM_PACKET_DATA_ID_PLOAM))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "ploam.");
        if (!bcmolt_bin_str_40_validate(&p_obj->ploam, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_state_change_completed_data_set_default(
    bcmolt_pon_interface_state_change_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    p_obj->previous_state = BCMOLT_INTERFACE_STATE_INACTIVE;
    p_obj->new_state = BCMOLT_INTERFACE_STATE_INACTIVE;
}

bcmos_bool bcmolt_pon_interface_state_change_completed_data_validate(
    const bcmolt_pon_interface_state_change_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID_PREVIOUS_STATE))
    {
        switch (p_obj->previous_state)
        {
        case BCMOLT_INTERFACE_STATE_INACTIVE:
        case BCMOLT_INTERFACE_STATE_PROCESSING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_WORKING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_STANDBY:
        case BCMOLT_INTERFACE_STATE_DISABLED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "previous_state: enum value %d is unexpected\n", (int)p_obj->previous_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_STATE_CHANGE_COMPLETED_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_INTERFACE_STATE_INACTIVE:
        case BCMOLT_INTERFACE_STATE_PROCESSING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_WORKING:
        case BCMOLT_INTERFACE_STATE_ACTIVE_STANDBY:
        case BCMOLT_INTERFACE_STATE_DISABLED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_tod_request_completed_data_set_default(
    bcmolt_pon_interface_tod_request_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_str_64_set_default(&p_obj->tod_string);
    p_obj->sfc = 0ULL;
    p_obj->rtc_offset_sec = 0ULL;
    p_obj->rtc_offset_nsec = 0UL;
    p_obj->status = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_pon_interface_tod_request_completed_data_validate(
    const bcmolt_pon_interface_tod_request_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_TOD_STRING))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tod_string.");
        if (!bcmolt_str_64_validate(&p_obj->tod_string, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_SFC))
    {
        /* p_obj->sfc can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_RTC_OFFSET_SEC))
    {
        /* p_obj->rtc_offset_sec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_RTC_OFFSET_NSEC))
    {
        /* p_obj->rtc_offset_nsec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_TOD_REQUEST_COMPLETED_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_los_data_set_default(
    bcmolt_pon_interface_los_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->status = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_pon_interface_los_data_validate(
    const bcmolt_pon_interface_los_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_LOS_DATA_ID_STATUS))
    {
        switch (p_obj->status)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "status: enum value %d is unexpected\n", (int)p_obj->status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_protection_switching_traffic_resume_data_set_default(
    bcmolt_pon_interface_protection_switching_traffic_resume_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_TRAFFIC_RESUME_RESULT_SUCCESS;
}

bcmos_bool bcmolt_pon_interface_protection_switching_traffic_resume_data_validate(
    const bcmolt_pon_interface_protection_switching_traffic_resume_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_TRAFFIC_RESUME_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_TRAFFIC_RESUME_RESULT_SUCCESS:
        case BCMOLT_TRAFFIC_RESUME_RESULT_FAILURE:
        case BCMOLT_TRAFFIC_RESUME_RESULT_SUSPECTED_LOS:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_protection_switching_onus_ranged_data_set_default(
    bcmolt_pon_interface_protection_switching_onus_ranged_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_itupon_onu_eqd_list_u32_set_default(&p_obj->onus);
}

bcmos_bool bcmolt_pon_interface_protection_switching_onus_ranged_data_validate(
    const bcmolt_pon_interface_protection_switching_onus_ranged_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_ONUS_RANGED_DATA_ID_ONUS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "onus.");
        if (!bcmolt_itupon_onu_eqd_list_u32_validate(&p_obj->onus, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_protection_switching_switchover_completed_data_set_default(
    bcmolt_pon_interface_protection_switching_switchover_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_pon_interface_protection_switching_switchover_completed_data_validate(
    const bcmolt_pon_interface_protection_switching_switchover_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_set_default(
    bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->number_of_detected_delimiter = 0UL;
    p_obj->energy_detect_signal = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data_validate(
    const bcmolt_pon_interface_standby_pon_monitoring_cycle_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID_NUMBER_OF_DETECTED_DELIMITER))
    {
        /* p_obj->number_of_detected_delimiter can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_STANDBY_PON_MONITORING_CYCLE_COMPLETED_DATA_ID_ENERGY_DETECT_SIGNAL))
    {
        switch (p_obj->energy_detect_signal)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "energy_detect_signal: enum value %d is unexpected\n", (int)p_obj->energy_detect_signal);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_onu_discovered_data_set_default(
    bcmolt_pon_interface_onu_discovered_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_serial_number_set_default(&p_obj->serial_number);
    p_obj->ranging_time = 0UL;
    p_obj->onu_id = (bcmolt_onu_id)0U;
    p_obj->upstream_line_rate_capabilities = BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_2_P_5_G;
    p_obj->current_downstream_pon_id = 0;
    p_obj->current_upstream_pon_id = 0;
    bcmolt_arr_calibration_record_8_set_default(&p_obj->calibration_record);
    p_obj->tuning_granularity = 0;
    p_obj->step_tuning_time = 0;
    p_obj->attenuation = 0;
    p_obj->power_levelling_capabilities = 0;
}

bcmos_bool bcmolt_pon_interface_onu_discovered_data_validate(
    const bcmolt_pon_interface_onu_discovered_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_SERIAL_NUMBER))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "serial_number.");
        if (!bcmolt_serial_number_validate(&p_obj->serial_number, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_RANGING_TIME))
    {
        /* p_obj->ranging_time can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_ONU_ID))
    {
        /* p_obj->onu_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_UPSTREAM_LINE_RATE_CAPABILITIES))
    {
        switch (p_obj->upstream_line_rate_capabilities)
        {
        case BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_2_P_5_G:
        case BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_10_G:
        case BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_1_G:
        case BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_DUAL_2_P_5_G_AND_10_G:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "upstream_line_rate_capabilities: enum value %d is unexpected\n", (int)p_obj->upstream_line_rate_capabilities);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_CURRENT_DOWNSTREAM_PON_ID))
    {
        /* p_obj->current_downstream_pon_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_CURRENT_UPSTREAM_PON_ID))
    {
        /* p_obj->current_upstream_pon_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_CALIBRATION_RECORD))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "calibration_record.");
        if (!bcmolt_arr_calibration_record_8_validate(&p_obj->calibration_record, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_TUNING_GRANULARITY))
    {
        /* p_obj->tuning_granularity can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_STEP_TUNING_TIME))
    {
        /* p_obj->step_tuning_time can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_ATTENUATION))
    {
        if (p_obj->attenuation > 7)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "attenuation: %u is greater than the maximum value of 7\n", p_obj->attenuation);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_DISCOVERED_DATA_ID_POWER_LEVELLING_CAPABILITIES))
    {
        if (p_obj->power_levelling_capabilities > 127)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "power_levelling_capabilities: %u is greater than the maximum value of 127\n", p_obj->power_levelling_capabilities);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_cpu_packets_failure_data_set_default(
    bcmolt_pon_interface_cpu_packets_failure_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->error = BCMOLT_PACKET_INJECTION_ERROR_GEM_PORT_NOT_ACTIVE;
    p_obj->gem_port_id = (bcmolt_gem_port_id)0UL;
}

bcmos_bool bcmolt_pon_interface_cpu_packets_failure_data_validate(
    const bcmolt_pon_interface_cpu_packets_failure_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID_ERROR))
    {
        switch (p_obj->error)
        {
        case BCMOLT_PACKET_INJECTION_ERROR_GEM_PORT_NOT_ACTIVE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "error: enum value %d is unexpected\n", (int)p_obj->error);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_CPU_PACKETS_FAILURE_DATA_ID_GEM_PORT_ID))
    {
        if (p_obj->gem_port_id > (bcmolt_gem_port_id)65536UL)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "gem_port_id: %u is greater than the maximum value of 65536\n", p_obj->gem_port_id);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_activate_all_onus_completed_data_set_default(
    bcmolt_pon_interface_activate_all_onus_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
}

bcmos_bool bcmolt_pon_interface_activate_all_onus_completed_data_validate(
    const bcmolt_pon_interface_activate_all_onus_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ACTIVATE_ALL_ONUS_COMPLETED_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_onu_upgrade_complete_data_set_default(
    bcmolt_pon_interface_onu_upgrade_complete_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->overall_status = BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_NOT_STARTED;
    p_obj->file_size_in_bytes = 0UL;
    bcmolt_onu_upgrade_status_list_u32_max_128_set_default(&p_obj->onu_status);
}

bcmos_bool bcmolt_pon_interface_onu_upgrade_complete_data_validate(
    const bcmolt_pon_interface_onu_upgrade_complete_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID_OVERALL_STATUS))
    {
        switch (p_obj->overall_status)
        {
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_NOT_STARTED:
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_IN_PROGRESS:
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_SUCCESS:
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_FAILURE:
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_ABORTED:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "overall_status: enum value %d is unexpected\n", (int)p_obj->overall_status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID_FILE_SIZE_IN_BYTES))
    {
        /* p_obj->file_size_in_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_UPGRADE_COMPLETE_DATA_ID_ONU_STATUS))
    {
        if (p_obj->onu_status.len > 128)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "onu_status: %u is greater than the maximum array length of 128\n", p_obj->onu_status.len);
            return BCMOS_FALSE;
        }
        int prefix_len = bcmolt_string_append(p_err_details, "onu_status.");
        if (!bcmolt_onu_upgrade_status_list_u32_max_128_validate(&p_obj->onu_status, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_mpcp_timestamp_changed_data_set_default(
    bcmolt_pon_interface_mpcp_timestamp_changed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->mpcp_timestamp = 0UL;
}

bcmos_bool bcmolt_pon_interface_mpcp_timestamp_changed_data_validate(
    const bcmolt_pon_interface_mpcp_timestamp_changed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_MPCP_TIMESTAMP_CHANGED_DATA_ID_MPCP_TIMESTAMP))
    {
        /* p_obj->mpcp_timestamp can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_switch_pon_type_data_set_default(
    bcmolt_pon_interface_switch_pon_type_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->new_pon_type = BCMOLT_PON_TYPE_UNKNOWN;
}

bcmos_bool bcmolt_pon_interface_switch_pon_type_data_validate(
    const bcmolt_pon_interface_switch_pon_type_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_DATA_ID_NEW_PON_TYPE))
    {
        switch (p_obj->new_pon_type)
        {
        case BCMOLT_PON_TYPE_UNKNOWN:
        case BCMOLT_PON_TYPE_GPON:
        case BCMOLT_PON_TYPE_XGPON:
        case BCMOLT_PON_TYPE_XGS:
        case BCMOLT_PON_TYPE_NGPON2_2P5G:
        case BCMOLT_PON_TYPE_NGPON2_10G:
        case BCMOLT_PON_TYPE_XGS_XGPON_TDMR:
        case BCMOLT_PON_TYPE_XGS_GPON_WDMA:
        case BCMOLT_PON_TYPE_XGS_XGPON_TDMR_GPON_WDMA:
        case BCMOLT_PON_TYPE_XGPON_GPON_WDMA:
        case BCMOLT_PON_TYPE_XGS_XGS_WDMA:
        case BCMOLT_PON_TYPE_GPON_GPON_WDMA:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_pon_type: enum value %d is unexpected\n", (int)p_obj->new_pon_type);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_switch_pon_type_completed_data_set_default(
    bcmolt_pon_interface_switch_pon_type_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    p_obj->fail_reason = BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_NONE;
    p_obj->new_type = BCMOLT_PON_TYPE_UNKNOWN;
    p_obj->old_type = BCMOLT_PON_TYPE_UNKNOWN;
}

bcmos_bool bcmolt_pon_interface_switch_pon_type_completed_data_validate(
    const bcmolt_pon_interface_switch_pon_type_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_FAIL_REASON))
    {
        switch (p_obj->fail_reason)
        {
        case BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_NONE:
        case BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_INTERNAL_ERROR:
        case BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_ALREADY_RUNNING:
        case BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_BAD_PON_STATE:
        case BCMOLT_SWITCH_PON_TYPE_FAIL_REASON_BAD_DEV_STATE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "fail_reason: enum value %d is unexpected\n", (int)p_obj->fail_reason);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_NEW_TYPE))
    {
        switch (p_obj->new_type)
        {
        case BCMOLT_PON_TYPE_UNKNOWN:
        case BCMOLT_PON_TYPE_GPON:
        case BCMOLT_PON_TYPE_XGPON:
        case BCMOLT_PON_TYPE_XGS:
        case BCMOLT_PON_TYPE_NGPON2_2P5G:
        case BCMOLT_PON_TYPE_NGPON2_10G:
        case BCMOLT_PON_TYPE_XGS_XGPON_TDMR:
        case BCMOLT_PON_TYPE_XGS_GPON_WDMA:
        case BCMOLT_PON_TYPE_XGS_XGPON_TDMR_GPON_WDMA:
        case BCMOLT_PON_TYPE_XGPON_GPON_WDMA:
        case BCMOLT_PON_TYPE_XGS_XGS_WDMA:
        case BCMOLT_PON_TYPE_GPON_GPON_WDMA:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_type: enum value %d is unexpected\n", (int)p_obj->new_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_SWITCH_PON_TYPE_COMPLETED_DATA_ID_OLD_TYPE))
    {
        switch (p_obj->old_type)
        {
        case BCMOLT_PON_TYPE_UNKNOWN:
        case BCMOLT_PON_TYPE_GPON:
        case BCMOLT_PON_TYPE_XGPON:
        case BCMOLT_PON_TYPE_XGS:
        case BCMOLT_PON_TYPE_NGPON2_2P5G:
        case BCMOLT_PON_TYPE_NGPON2_10G:
        case BCMOLT_PON_TYPE_XGS_XGPON_TDMR:
        case BCMOLT_PON_TYPE_XGS_GPON_WDMA:
        case BCMOLT_PON_TYPE_XGS_XGPON_TDMR_GPON_WDMA:
        case BCMOLT_PON_TYPE_XGPON_GPON_WDMA:
        case BCMOLT_PON_TYPE_XGS_XGS_WDMA:
        case BCMOLT_PON_TYPE_GPON_GPON_WDMA:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "old_type: enum value %d is unexpected\n", (int)p_obj->old_type);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_rogue_detection_tool_data_set_default(
    bcmolt_pon_interface_rogue_detection_tool_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->start_offset = 0U;
    p_obj->use_onu_id = 0;
    p_obj->onu_id = 0U;
}

bcmos_bool bcmolt_pon_interface_rogue_detection_tool_data_validate(
    const bcmolt_pon_interface_rogue_detection_tool_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID_START_OFFSET))
    {
        /* p_obj->start_offset can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID_USE_ONU_ID))
    {
        /* p_obj->use_onu_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DATA_ID_ONU_ID))
    {
        /* p_obj->onu_id can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_rogue_detection_tool_done_data_set_default(
    bcmolt_pon_interface_rogue_detection_tool_done_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->result = BCMOLT_RESULT_SUCCESS;
    bcmolt_u64_list_u32_hex_set_default(&p_obj->output);
    p_obj->onu_id = 0U;
}

bcmos_bool bcmolt_pon_interface_rogue_detection_tool_done_data_validate(
    const bcmolt_pon_interface_rogue_detection_tool_done_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID_RESULT))
    {
        switch (p_obj->result)
        {
        case BCMOLT_RESULT_SUCCESS:
        case BCMOLT_RESULT_FAIL:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "result: enum value %d is unexpected\n", (int)p_obj->result);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID_OUTPUT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "output.");
        if (!bcmolt_u64_list_u32_hex_validate(&p_obj->output, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ROGUE_DETECTION_TOOL_DONE_DATA_ID_ONU_ID))
    {
        /* p_obj->onu_id can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_onu_upgrade_activate_commit_data_set_default(
    bcmolt_pon_interface_onu_upgrade_activate_commit_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_onu_id_list_u32_set_default(&p_obj->list_of_onu_ids);
}

bcmos_bool bcmolt_pon_interface_onu_upgrade_activate_commit_data_validate(
    const bcmolt_pon_interface_onu_upgrade_activate_commit_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ONU_UPGRADE_ACTIVATE_COMMIT_DATA_ID_LIST_OF_ONU_IDS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "list_of_onu_ids.");
        if (!bcmolt_onu_id_list_u32_validate(&p_obj->list_of_onu_ids, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_itu_pon_stats_cfg_data_set_default(
    bcmolt_pon_interface_itu_pon_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->fec_codewords);
    bcmolt_stat_alarm_config_set_default(&p_obj->bip_units);
    bcmolt_stat_alarm_config_set_default(&p_obj->bip_errors);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_gem);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_gem_dropped);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_gem_idle);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_gem_corrected);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_crc_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_fragment_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_packets_dropped);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_dropped_too_short);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_dropped_too_long);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_key_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_cpu_omci_packets_dropped);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_ploams);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_ploams_dropped);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_allocations_valid);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_allocations_invalid);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_allocations_disabled);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_ploams);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_ploams_non_idle);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_ploams_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_cpu);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_omci);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_omci_packets_crc_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_gem);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_cpu);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_omci);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_dropped_illegal_length);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_dropped_tpid_miss);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_dropped_vid_miss);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_dropped_total);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_xgtc_headers);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_xgtc_corrected);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_xgtc_uncorrected);
    bcmolt_stat_alarm_config_set_default(&p_obj->fec_codewords_uncorrected);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_gem_illegal);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
}

bcmos_bool bcmolt_pon_interface_itu_pon_stats_cfg_data_validate(
    const bcmolt_pon_interface_itu_pon_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "fec_codewords.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->fec_codewords, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_BIP_UNITS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "bip_units.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->bip_units, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_BIP_ERRORS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "bip_errors.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->bip_errors, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_gem.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_gem, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_DROPPED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_gem_dropped.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_gem_dropped, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_IDLE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_gem_idle.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_gem_idle, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_CORRECTED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_gem_corrected.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_gem_corrected, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_CRC_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_crc_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_crc_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_FRAGMENT_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_fragment_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_fragment_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PACKETS_DROPPED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_packets_dropped.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_packets_dropped, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_DROPPED_TOO_SHORT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_dropped_too_short.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_dropped_too_short, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_DROPPED_TOO_LONG))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_dropped_too_long.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_dropped_too_long, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_KEY_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_key_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_key_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_CPU_OMCI_PACKETS_DROPPED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_cpu_omci_packets_dropped.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_cpu_omci_packets_dropped, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_PLOAMS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_ploams.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_ploams, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_DROPPED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_ploams_dropped.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_ploams_dropped, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_ALLOCATIONS_VALID))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_allocations_valid.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_allocations_valid, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_ALLOCATIONS_INVALID))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_allocations_invalid.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_allocations_invalid, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_ALLOCATIONS_DISABLED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_allocations_disabled.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_allocations_disabled, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_ploams.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_ploams, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_NON_IDLE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_ploams_non_idle.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_ploams_non_idle, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PLOAMS_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_ploams_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_ploams_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_CPU))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_cpu.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_cpu, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_omci.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_omci, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_omci_packets_crc_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_omci_packets_crc_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_GEM))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_gem.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_gem, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_CPU))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_cpu.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_cpu, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_OMCI))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_omci.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_omci, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_ILLEGAL_LENGTH))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_dropped_illegal_length.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_dropped_illegal_length, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_TPID_MISS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_dropped_tpid_miss.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_dropped_tpid_miss, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_VID_MISS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_dropped_vid_miss.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_dropped_vid_miss, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_DROPPED_TOTAL))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_dropped_total.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_dropped_total, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_XGTC_HEADERS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_xgtc_headers.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_xgtc_headers, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_XGTC_CORRECTED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_xgtc_corrected.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_xgtc_corrected, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_XGTC_UNCORRECTED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_xgtc_uncorrected.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_xgtc_uncorrected, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_FEC_CODEWORDS_UNCORRECTED))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "fec_codewords_uncorrected.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->fec_codewords_uncorrected, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_GEM_ILLEGAL))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_gem_illegal.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_gem_illegal, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_TX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_set_default(
    bcmolt_pon_interface_itu_pon_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS;
}

bcmos_bool bcmolt_pon_interface_itu_pon_stats_alarm_raised_data_validate(
    const bcmolt_pon_interface_itu_pon_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_UNITS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_ERRORS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_DROPPED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_IDLE:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_CORRECTED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CRC_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_FRAGMENT_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS_DROPPED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_SHORT:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_LONG:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_KEY_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU_OMCI_PACKETS_DROPPED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PLOAMS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_DROPPED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_VALID:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_INVALID:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_DISABLED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_GEM:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_CPU:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_OMCI:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_ILLEGAL_LENGTH:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TPID_MISS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_VID_MISS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TOTAL:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_HEADERS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_CORRECTED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_UNCORRECTED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_ILLEGAL:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_BYTES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_set_default(
    bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS;
}

bcmos_bool bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data_validate(
    const bcmolt_pon_interface_itu_pon_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_ITU_PON_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_UNITS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_BIP_ERRORS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_DROPPED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_IDLE:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_CORRECTED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CRC_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_FRAGMENT_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS_DROPPED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_SHORT:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_DROPPED_TOO_LONG:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_KEY_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU_OMCI_PACKETS_DROPPED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PLOAMS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_DROPPED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_VALID:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_INVALID:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_ALLOCATIONS_DISABLED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_NON_IDLE:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PLOAMS_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_CPU:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_OMCI_PACKETS_CRC_ERROR:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_GEM:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_CPU:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_OMCI:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_ILLEGAL_LENGTH:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TPID_MISS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_VID_MISS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_DROPPED_TOTAL:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_HEADERS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_CORRECTED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_XGTC_UNCORRECTED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_FEC_CODEWORDS_UNCORRECTED:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_GEM_ILLEGAL:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_PON_INTERFACE_ITU_PON_STATS_DATA_ID_RX_BYTES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_ae_stats_cfg_data_set_default(
    bcmolt_pon_interface_ae_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_9217_16383);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_broadcast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_data_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_multicast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_unicast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_abort_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_fcs_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_oversize_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_runt_error);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_9217_16383);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_broadcast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_data_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_multicast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_unicast_frames);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_abort_frames);
}

bcmos_bool bcmolt_pon_interface_ae_stats_cfg_data_validate(
    const bcmolt_pon_interface_ae_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_BROADCAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_broadcast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_broadcast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_DATA_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_data_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_data_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_MULTICAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_multicast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_multicast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_UNICAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_unicast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_unicast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_ABORT_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_abort_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_abort_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_FCS_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_fcs_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_fcs_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_OVERSIZE_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_oversize_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_oversize_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_RX_RUNT_ERROR))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_runt_error.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_runt_error, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_BROADCAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_broadcast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_broadcast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_DATA_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_data_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_data_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_MULTICAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_multicast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_multicast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_UNICAST_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_unicast_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_unicast_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_CFG_DATA_ID_TX_ABORT_FRAMES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_abort_frames.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_abort_frames, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_ae_stats_alarm_raised_data_set_default(
    bcmolt_pon_interface_ae_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_pon_interface_ae_stats_alarm_raised_data_validate(
    const bcmolt_pon_interface_ae_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BROADCAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_DATA_BYTES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_MULTICAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_UNICAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_ABORT_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FCS_ERROR:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_OVERSIZE_ERROR:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_RUNT_ERROR:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_9217_16383:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BROADCAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_DATA_BYTES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_MULTICAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_UNICAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_ABORT_FRAMES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_ae_stats_alarm_cleared_data_set_default(
    bcmolt_pon_interface_ae_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_pon_interface_ae_stats_alarm_cleared_data_validate(
    const bcmolt_pon_interface_ae_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AE_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_BROADCAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_DATA_BYTES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_MULTICAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_UNICAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_ABORT_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_FCS_ERROR:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_OVERSIZE_ERROR:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_RX_RUNT_ERROR:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_FRAMES_9217_16383:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_BROADCAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_DATA_BYTES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_MULTICAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_UNICAST_FRAMES:
        case BCMOLT_PON_INTERFACE_AE_STATS_DATA_ID_TX_ABORT_FRAMES:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_interface_auto_cfg_data_set_default(
    bcmolt_pon_interface_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->activate_all_onus_completed = BCMOS_FALSE;
    p_obj->ae_stats_alarm_cleared = BCMOS_FALSE;
    p_obj->ae_stats_alarm_raised = BCMOS_FALSE;
    p_obj->cpu_packets_failure = BCMOS_FALSE;
    p_obj->deactivate_all_onus_completed = BCMOS_FALSE;
    p_obj->disable_all_onus_completed = BCMOS_FALSE;
    p_obj->enable_all_onus_completed = BCMOS_FALSE;
    p_obj->ieee_rogue_detection_completed = BCMOS_FALSE;
    p_obj->itu_pon_stats_alarm_cleared = BCMOS_FALSE;
    p_obj->itu_pon_stats_alarm_raised = BCMOS_FALSE;
    p_obj->los = BCMOS_FALSE;
    p_obj->mpcp_timestamp_changed = BCMOS_FALSE;
    p_obj->onu_discovered = BCMOS_FALSE;
    p_obj->onu_upgrade_complete = BCMOS_FALSE;
    p_obj->protection_switching_onus_ranged = BCMOS_FALSE;
    p_obj->protection_switching_rerange_failure = BCMOS_FALSE;
    p_obj->protection_switching_switchover_completed = BCMOS_FALSE;
    p_obj->protection_switching_traffic_resume = BCMOS_FALSE;
    p_obj->rogue_detection_tool_done = BCMOS_FALSE;
    p_obj->serial_number_acquisition_cycle_start = BCMOS_FALSE;
    p_obj->standby_pon_monitoring_cycle_completed = BCMOS_FALSE;
    p_obj->state_change_completed = BCMOS_FALSE;
    p_obj->switch_pon_type_completed = BCMOS_FALSE;
    p_obj->tod_request_completed = BCMOS_FALSE;
}

bcmos_bool bcmolt_pon_interface_auto_cfg_data_validate(
    const bcmolt_pon_interface_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ACTIVATE_ALL_ONUS_COMPLETED))
    {
        /* p_obj->activate_all_onus_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_AE_STATS_ALARM_CLEARED))
    {
        /* p_obj->ae_stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_AE_STATS_ALARM_RAISED))
    {
        /* p_obj->ae_stats_alarm_raised can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_CPU_PACKETS_FAILURE))
    {
        /* p_obj->cpu_packets_failure can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_DEACTIVATE_ALL_ONUS_COMPLETED))
    {
        /* p_obj->deactivate_all_onus_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_DISABLE_ALL_ONUS_COMPLETED))
    {
        /* p_obj->disable_all_onus_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ENABLE_ALL_ONUS_COMPLETED))
    {
        /* p_obj->enable_all_onus_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_IEEE_ROGUE_DETECTION_COMPLETED))
    {
        /* p_obj->ieee_rogue_detection_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_CLEARED))
    {
        /* p_obj->itu_pon_stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ITU_PON_STATS_ALARM_RAISED))
    {
        /* p_obj->itu_pon_stats_alarm_raised can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_LOS))
    {
        /* p_obj->los can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_MPCP_TIMESTAMP_CHANGED))
    {
        /* p_obj->mpcp_timestamp_changed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ONU_DISCOVERED))
    {
        /* p_obj->onu_discovered can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ONU_UPGRADE_COMPLETE))
    {
        /* p_obj->onu_upgrade_complete can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_ONUS_RANGED))
    {
        /* p_obj->protection_switching_onus_ranged can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_RERANGE_FAILURE))
    {
        /* p_obj->protection_switching_rerange_failure can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_SWITCHOVER_COMPLETED))
    {
        /* p_obj->protection_switching_switchover_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCHING_TRAFFIC_RESUME))
    {
        /* p_obj->protection_switching_traffic_resume can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_ROGUE_DETECTION_TOOL_DONE))
    {
        /* p_obj->rogue_detection_tool_done can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_SERIAL_NUMBER_ACQUISITION_CYCLE_START))
    {
        /* p_obj->serial_number_acquisition_cycle_start can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_STANDBY_PON_MONITORING_CYCLE_COMPLETED))
    {
        /* p_obj->standby_pon_monitoring_cycle_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_STATE_CHANGE_COMPLETED))
    {
        /* p_obj->state_change_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_SWITCH_PON_TYPE_COMPLETED))
    {
        /* p_obj->switch_pon_type_completed can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PON_INTERFACE_AUTO_CFG_DATA_ID_TOD_REQUEST_COMPLETED))
    {
        /* p_obj->tod_request_completed can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_protection_interface_key_set_default(
    bcmolt_protection_interface_key *p_obj)
{
    p_obj->id = (bcmolt_protection_interface_id)0U;
}

bcmos_bool bcmolt_protection_interface_key_validate(
    const bcmolt_protection_interface_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_protection_interface_id)63U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 63\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_protection_interface_cfg_data_set_default(
    bcmolt_protection_interface_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    bcmolt_intf_ref_set_default(&p_obj->primary_interface);
    bcmolt_intf_ref_set_default(&p_obj->secondary_interface);
    p_obj->active_interface = BCMOLT_ACTIVE_INTERFACE_UNASSIGNED;
}

bcmos_bool bcmolt_protection_interface_cfg_data_validate(
    const bcmolt_protection_interface_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_PRIMARY_INTERFACE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "primary_interface.");
        if (!bcmolt_intf_ref_validate(&p_obj->primary_interface, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_SECONDARY_INTERFACE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "secondary_interface.");
        if (!bcmolt_intf_ref_validate(&p_obj->secondary_interface, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PROTECTION_INTERFACE_CFG_DATA_ID_ACTIVE_INTERFACE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "active_interface: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_protection_interface_protection_switch_completed_data_set_default(
    bcmolt_protection_interface_protection_switch_completed_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->active_interface = BCMOLT_ACTIVE_INTERFACE_UNASSIGNED;
}

bcmos_bool bcmolt_protection_interface_protection_switch_completed_data_validate(
    const bcmolt_protection_interface_protection_switch_completed_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PROTECTION_INTERFACE_PROTECTION_SWITCH_COMPLETED_DATA_ID_ACTIVE_INTERFACE))
    {
        switch (p_obj->active_interface)
        {
        case BCMOLT_ACTIVE_INTERFACE_UNASSIGNED:
        case BCMOLT_ACTIVE_INTERFACE_PRIMARY:
        case BCMOLT_ACTIVE_INTERFACE_SECONDARY:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "active_interface: enum value %d is unexpected\n", (int)p_obj->active_interface);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_protection_interface_auto_cfg_data_set_default(
    bcmolt_protection_interface_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->protection_switch_completed = BCMOS_FALSE;
}

bcmos_bool bcmolt_protection_interface_auto_cfg_data_validate(
    const bcmolt_protection_interface_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_PROTECTION_INTERFACE_AUTO_CFG_DATA_ID_PROTECTION_SWITCH_COMPLETED))
    {
        /* p_obj->protection_switch_completed can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_software_error_key_set_default(
    bcmolt_software_error_key *p_obj)
{
    p_obj->device_id = (bcmolt_odid)0;
    p_obj->idx = 0UL;
}

bcmos_bool bcmolt_software_error_key_validate(
    const bcmolt_software_error_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->device_id can't be invalid. */
    /* p_obj->idx can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_software_error_cfg_data_set_default(
    bcmolt_software_error_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_sw_error_set_default(&p_obj->entry);
}

bcmos_bool bcmolt_software_error_cfg_data_validate(
    const bcmolt_software_error_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SOFTWARE_ERROR_CFG_DATA_ID_ENTRY))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "entry: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_switch_inni_key_set_default(
    bcmolt_switch_inni_key *p_obj)
{
    p_obj->id = (bcmolt_switch_inni_id)0;
}

bcmos_bool bcmolt_switch_inni_key_validate(
    const bcmolt_switch_inni_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_switch_inni_id)127)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 127\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_switch_inni_cfg_data_set_default(
    bcmolt_switch_inni_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->config_state = BCMOLT_CONFIG_STATE_CONFIGURED;
    p_obj->link_state = BCMOLT_LINK_STATE_LINK_DOWN;
}

bcmos_bool bcmolt_switch_inni_cfg_data_validate(
    const bcmolt_switch_inni_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_CFG_DATA_ID_CONFIG_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "config_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_CFG_DATA_ID_LINK_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "link_state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_switch_inni_stats_data_set_default(
    bcmolt_switch_inni_stats_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->rx_bytes = 0ULL;
    p_obj->rx_packets = 0ULL;
    p_obj->rx_ucast_packets = 0ULL;
    p_obj->rx_mcast_packets = 0ULL;
    p_obj->rx_bcast_packets = 0ULL;
    p_obj->rx_error_packets = 0ULL;
    p_obj->rx_fcs_error_packets = 0ULL;
    p_obj->rx_undersize_packets = 0ULL;
    p_obj->rx_oversize_packets = 0ULL;
    p_obj->rx_jabber_packets = 0ULL;
    p_obj->tx_bytes = 0ULL;
    p_obj->tx_packets = 0ULL;
    p_obj->tx_ucast_packets = 0ULL;
    p_obj->tx_mcast_packets = 0ULL;
    p_obj->tx_bcast_packets = 0ULL;
    p_obj->tx_error_packets = 0ULL;
    p_obj->tx_undersize_packets = 0ULL;
    p_obj->tx_oversize_packets = 0ULL;
    p_obj->tx_jabber_packets = 0ULL;
    p_obj->rx_frames_64 = 0ULL;
    p_obj->rx_frames_65_127 = 0ULL;
    p_obj->rx_frames_128_255 = 0ULL;
    p_obj->rx_frames_256_511 = 0ULL;
    p_obj->rx_frames_512_1023 = 0ULL;
    p_obj->rx_frames_1024_1518 = 0ULL;
    p_obj->rx_frames_1519_2047 = 0ULL;
    p_obj->rx_frames_2048_4095 = 0ULL;
    p_obj->rx_frames_4096_9216 = 0ULL;
    p_obj->rx_frames_9217_16383 = 0ULL;
    p_obj->tx_frames_64 = 0ULL;
    p_obj->tx_frames_65_127 = 0ULL;
    p_obj->tx_frames_128_255 = 0ULL;
    p_obj->tx_frames_256_511 = 0ULL;
    p_obj->tx_frames_512_1023 = 0ULL;
    p_obj->tx_frames_1024_1518 = 0ULL;
    p_obj->tx_frames_1519_2047 = 0ULL;
    p_obj->tx_frames_2048_4095 = 0ULL;
    p_obj->tx_frames_4096_9216 = 0ULL;
    p_obj->tx_frames_9217_16383 = 0ULL;
}

bcmos_bool bcmolt_switch_inni_stats_data_validate(
    const bcmolt_switch_inni_stats_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BYTES))
    {
        /* p_obj->rx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_PACKETS))
    {
        /* p_obj->rx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UCAST_PACKETS))
    {
        /* p_obj->rx_ucast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_MCAST_PACKETS))
    {
        /* p_obj->rx_mcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BCAST_PACKETS))
    {
        /* p_obj->rx_bcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_ERROR_PACKETS))
    {
        /* p_obj->rx_error_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FCS_ERROR_PACKETS))
    {
        /* p_obj->rx_fcs_error_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UNDERSIZE_PACKETS))
    {
        /* p_obj->rx_undersize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_OVERSIZE_PACKETS))
    {
        /* p_obj->rx_oversize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_JABBER_PACKETS))
    {
        /* p_obj->rx_jabber_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BYTES))
    {
        /* p_obj->tx_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_PACKETS))
    {
        /* p_obj->tx_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UCAST_PACKETS))
    {
        /* p_obj->tx_ucast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_MCAST_PACKETS))
    {
        /* p_obj->tx_mcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BCAST_PACKETS))
    {
        /* p_obj->tx_bcast_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_ERROR_PACKETS))
    {
        /* p_obj->tx_error_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UNDERSIZE_PACKETS))
    {
        /* p_obj->tx_undersize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_OVERSIZE_PACKETS))
    {
        /* p_obj->tx_oversize_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_JABBER_PACKETS))
    {
        /* p_obj->tx_jabber_packets can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_64))
    {
        /* p_obj->rx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_65_127))
    {
        /* p_obj->rx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_128_255))
    {
        /* p_obj->rx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_256_511))
    {
        /* p_obj->rx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_512_1023))
    {
        /* p_obj->rx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1024_1518))
    {
        /* p_obj->rx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1519_2047))
    {
        /* p_obj->rx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_2048_4095))
    {
        /* p_obj->rx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_4096_9216))
    {
        /* p_obj->rx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_9217_16383))
    {
        /* p_obj->rx_frames_9217_16383 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_64))
    {
        /* p_obj->tx_frames_64 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_65_127))
    {
        /* p_obj->tx_frames_65_127 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_128_255))
    {
        /* p_obj->tx_frames_128_255 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_256_511))
    {
        /* p_obj->tx_frames_256_511 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_512_1023))
    {
        /* p_obj->tx_frames_512_1023 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1024_1518))
    {
        /* p_obj->tx_frames_1024_1518 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1519_2047))
    {
        /* p_obj->tx_frames_1519_2047 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_2048_4095))
    {
        /* p_obj->tx_frames_2048_4095 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_4096_9216))
    {
        /* p_obj->tx_frames_4096_9216 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_9217_16383))
    {
        /* p_obj->tx_frames_9217_16383 can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_switch_inni_link_state_change_data_set_default(
    bcmolt_switch_inni_link_state_change_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->old_state = BCMOLT_LINK_STATE_LINK_DOWN;
    p_obj->new_state = BCMOLT_LINK_STATE_LINK_DOWN;
}

bcmos_bool bcmolt_switch_inni_link_state_change_data_validate(
    const bcmolt_switch_inni_link_state_change_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_LINK_STATE_CHANGE_DATA_ID_OLD_STATE))
    {
        switch (p_obj->old_state)
        {
        case BCMOLT_LINK_STATE_LINK_DOWN:
        case BCMOLT_LINK_STATE_LINK_UP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "old_state: enum value %d is unexpected\n", (int)p_obj->old_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_LINK_STATE_CHANGE_DATA_ID_NEW_STATE))
    {
        switch (p_obj->new_state)
        {
        case BCMOLT_LINK_STATE_LINK_DOWN:
        case BCMOLT_LINK_STATE_LINK_UP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "new_state: enum value %d is unexpected\n", (int)p_obj->new_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_switch_inni_stats_cfg_data_set_default(
    bcmolt_switch_inni_stats_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_ucast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_mcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_bcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_error_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_fcs_error_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_undersize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_oversize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_jabber_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bytes);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_ucast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_mcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_bcast_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_error_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_undersize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_oversize_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_jabber_packets);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->rx_frames_9217_16383);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_64);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_65_127);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_128_255);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_256_511);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_512_1023);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1024_1518);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_1519_2047);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_2048_4095);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_4096_9216);
    bcmolt_stat_alarm_config_set_default(&p_obj->tx_frames_9217_16383);
}

bcmos_bool bcmolt_switch_inni_stats_cfg_data_validate(
    const bcmolt_switch_inni_stats_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_UCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_ucast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_ucast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_MCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_mcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_mcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_BCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_bcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_bcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_ERROR_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_error_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_error_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FCS_ERROR_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_fcs_error_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_fcs_error_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_UNDERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_undersize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_undersize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_OVERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_oversize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_oversize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_JABBER_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_jabber_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_jabber_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_BYTES))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bytes.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bytes, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_UCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_ucast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_ucast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_MCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_mcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_mcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_BCAST_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_bcast_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_bcast_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_ERROR_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_error_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_error_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_UNDERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_undersize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_undersize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_OVERSIZE_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_oversize_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_oversize_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_JABBER_PACKETS))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_jabber_packets.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_jabber_packets, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_RX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->rx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_64))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_64.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_64, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_65_127))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_65_127.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_65_127, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_128_255))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_128_255.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_128_255, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_256_511))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_256_511.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_256_511, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_512_1023))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_512_1023.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_512_1023, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_1024_1518))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1024_1518.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1024_1518, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_1519_2047))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_1519_2047.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_1519_2047, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_2048_4095))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_2048_4095.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_2048_4095, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_4096_9216))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_4096_9216.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_4096_9216, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_CFG_DATA_ID_TX_FRAMES_9217_16383))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tx_frames_9217_16383.");
        if (!bcmolt_stat_alarm_config_validate(&p_obj->tx_frames_9217_16383, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_switch_inni_stats_alarm_raised_data_set_default(
    bcmolt_switch_inni_stats_alarm_raised_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_switch_inni_stats_alarm_raised_data_validate(
    const bcmolt_switch_inni_stats_alarm_raised_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_ALARM_RAISED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_MCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_ERROR_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FCS_ERROR_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UNDERSIZE_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_OVERSIZE_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_JABBER_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_MCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_ERROR_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UNDERSIZE_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_OVERSIZE_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_JABBER_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_9217_16383:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_switch_inni_stats_alarm_cleared_data_set_default(
    bcmolt_switch_inni_stats_alarm_cleared_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->stat = BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BYTES;
}

bcmos_bool bcmolt_switch_inni_stats_alarm_cleared_data_validate(
    const bcmolt_switch_inni_stats_alarm_cleared_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_STATS_ALARM_CLEARED_DATA_ID_STAT))
    {
        switch (p_obj->stat)
        {
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BYTES:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_MCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_BCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_ERROR_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FCS_ERROR_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_UNDERSIZE_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_OVERSIZE_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_JABBER_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BYTES:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_MCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_BCAST_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_ERROR_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_UNDERSIZE_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_OVERSIZE_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_JABBER_PACKETS:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_64:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_65_127:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_128_255:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_256_511:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_512_1023:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1024_1518:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_1519_2047:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_2048_4095:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_4096_9216:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_RX_FRAMES_9217_16383:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_64:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_65_127:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_128_255:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_256_511:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_512_1023:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1024_1518:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_1519_2047:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_2048_4095:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_4096_9216:
        case BCMOLT_SWITCH_INNI_STATS_DATA_ID_TX_FRAMES_9217_16383:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "stat: enum value %d is unexpected\n", (int)p_obj->stat);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_switch_inni_auto_cfg_data_set_default(
    bcmolt_switch_inni_auto_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->link_state_change = BCMOS_FALSE;
    p_obj->stats_alarm_cleared = BCMOS_FALSE;
    p_obj->stats_alarm_raised = BCMOS_FALSE;
}

bcmos_bool bcmolt_switch_inni_auto_cfg_data_validate(
    const bcmolt_switch_inni_auto_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID_LINK_STATE_CHANGE))
    {
        /* p_obj->link_state_change can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID_STATS_ALARM_CLEARED))
    {
        /* p_obj->stats_alarm_cleared can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_SWITCH_INNI_AUTO_CFG_DATA_ID_STATS_ALARM_RAISED))
    {
        /* p_obj->stats_alarm_raised can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_tc_to_queue_key_set_default(
    bcmolt_tc_to_queue_key *p_obj)
{
    p_obj->id = 0U;
    p_obj->dir = (bcmolt_tm_sched_dir)0;
}

bcmos_bool bcmolt_tc_to_queue_key_validate(
    const bcmolt_tc_to_queue_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id < 1U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is less than the minimum value of 1\n", p_obj->id);
        return BCMOS_FALSE;
    }
    if (p_obj->id > 4096U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 4096\n", p_obj->id);
        return BCMOS_FALSE;
    }
    switch (p_obj->dir)
    {
    case BCMOLT_TM_SCHED_DIR_US:
    case BCMOLT_TM_SCHED_DIR_DS:
        break;
    default:
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "dir: enum value %d is unexpected\n", (int)p_obj->dir);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_tc_to_queue_cfg_data_set_default(
    bcmolt_tc_to_queue_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_arr_tm_queue_ref_8_set_default(&p_obj->queue);
}

bcmos_bool bcmolt_tc_to_queue_cfg_data_validate(
    const bcmolt_tc_to_queue_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TC_TO_QUEUE_CFG_DATA_ID_QUEUE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "queue.");
        if (!bcmolt_arr_tm_queue_ref_8_validate(&p_obj->queue, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_qmp_key_set_default(
    bcmolt_tm_qmp_key *p_obj)
{
    p_obj->id = (bcmolt_tm_qmp_id)255;
}

bcmos_bool bcmolt_tm_qmp_key_validate(
    const bcmolt_tm_qmp_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_tm_qmp_id)15)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 15\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_qmp_cfg_data_set_default(
    bcmolt_tm_qmp_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->type = BCMOLT_TM_QMP_TYPE_UNDEFINED;
    bcmolt_arr_u8_8_set_default(&p_obj->pbits_to_tmq_id);
    p_obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
}

bcmos_bool bcmolt_tm_qmp_cfg_data_validate(
    const bcmolt_tm_qmp_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QMP_CFG_DATA_ID_TYPE))
    {
        switch (p_obj->type)
        {
        case BCMOLT_TM_QMP_TYPE_UNDEFINED:
        case BCMOLT_TM_QMP_TYPE_PBITS:
        case BCMOLT_TM_QMP_TYPE_DSCP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "type: enum value %d is unexpected\n", (int)p_obj->type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QMP_CFG_DATA_ID_PBITS_TO_TMQ_ID))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "pbits_to_tmq_id.");
        if (!bcmolt_arr_u8_8_validate(&p_obj->pbits_to_tmq_id, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QMP_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_queue_key_set_default(
    bcmolt_tm_queue_key *p_obj)
{
    p_obj->sched_id = (bcmolt_tm_sched_id)65535U;
    p_obj->tm_q_set_id = (bcmolt_tm_queue_set_id)32768U;
    p_obj->id = (bcmolt_tm_queue_id)65535U;
}

bcmos_bool bcmolt_tm_queue_key_validate(
    const bcmolt_tm_queue_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->sched_id can't be invalid. */
    /* p_obj->tm_q_set_id can't be invalid. */
    /* p_obj->id can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_tm_queue_cfg_data_set_default(
    bcmolt_tm_queue_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    bcmolt_tm_sched_param_set_default(&p_obj->tm_sched_param);
    p_obj->profile_id = (bcmolt_tm_queue_profile_id)0U;
    bcmolt_tm_shaping_set_default(&p_obj->rate);
    p_obj->rate.cir = 0UL;
    p_obj->rate.pir = 0UL;
    p_obj->rate.burst = 0UL;
    p_obj->control_state = BCMOLT_CONTROL_STATE_ENABLE;
    bcmolt_tm_sched_attachment_point_set_default(&p_obj->cir_attachment_point);
}

bcmos_bool bcmolt_tm_queue_cfg_data_validate(
    const bcmolt_tm_queue_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QUEUE_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QUEUE_CFG_DATA_ID_TM_SCHED_PARAM))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "tm_sched_param.");
        if (!bcmolt_tm_sched_param_validate(&p_obj->tm_sched_param, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QUEUE_CFG_DATA_ID_PROFILE_ID))
    {
        if (p_obj->profile_id > (bcmolt_tm_queue_profile_id)63U)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "profile_id: %u is greater than the maximum value of 63\n", p_obj->profile_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QUEUE_CFG_DATA_ID_RATE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rate.");
        if (!bcmolt_tm_shaping_validate(&p_obj->rate, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QUEUE_CFG_DATA_ID_CONTROL_STATE))
    {
        switch (p_obj->control_state)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "control_state: enum value %d is unexpected\n", (int)p_obj->control_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QUEUE_CFG_DATA_ID_CIR_ATTACHMENT_POINT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "cir_attachment_point.");
        if (!bcmolt_tm_sched_attachment_point_validate(&p_obj->cir_attachment_point, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_queue_profile_key_set_default(
    bcmolt_tm_queue_profile_key *p_obj)
{
    p_obj->id = (bcmolt_tm_queue_profile_id)0U;
}

bcmos_bool bcmolt_tm_queue_profile_key_validate(
    const bcmolt_tm_queue_profile_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (p_obj->id > (bcmolt_tm_queue_profile_id)63U)
    {
        *p_err = BCM_ERR_RANGE;
        bcmolt_string_append(p_err_details, "id: %u is greater than the maximum value of 63\n", p_obj->id);
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_queue_profile_cfg_data_set_default(
    bcmolt_tm_queue_profile_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    p_obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    p_obj->enqueue = BCMOLT_ENQUEUE_ALGORITHM_TAIL_DROP;
    bcmolt_taildrop_params_set_default(&p_obj->taildrop);
}

bcmos_bool bcmolt_tm_queue_profile_cfg_data_validate(
    const bcmolt_tm_queue_profile_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QUEUE_PROFILE_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QUEUE_PROFILE_CFG_DATA_ID_ENQUEUE))
    {
        switch (p_obj->enqueue)
        {
        case BCMOLT_ENQUEUE_ALGORITHM_TAIL_DROP:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "enqueue: enum value %d is unexpected\n", (int)p_obj->enqueue);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_QUEUE_PROFILE_CFG_DATA_ID_TAILDROP))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "taildrop.");
        if (!bcmolt_taildrop_params_validate(&p_obj->taildrop, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_sched_key_set_default(
    bcmolt_tm_sched_key *p_obj)
{
    p_obj->id = (bcmolt_tm_sched_id)0U;
}

bcmos_bool bcmolt_tm_sched_key_validate(
    const bcmolt_tm_sched_key *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    /* p_obj->id can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_tm_sched_cfg_data_set_default(
    bcmolt_tm_sched_cfg_data *p_obj)
{
    p_obj->presence_mask = 0;
    bcmolt_tm_sched_attachment_point_set_default(&p_obj->attachment_point);
    p_obj->sched_type = BCMOLT_TM_SCHED_TYPE_UNDEFINED;
    p_obj->num_priorities = 0;
    bcmolt_tm_shaping_set_default(&p_obj->rate);
    p_obj->rate.cir = 0UL;
    p_obj->rate.pir = 0UL;
    p_obj->rate.burst = 0UL;
    p_obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    bcmolt_tm_sched_attachment_point_set_default(&p_obj->cir_attachment_point);
}

bcmos_bool bcmolt_tm_sched_cfg_data_validate(
    const bcmolt_tm_sched_cfg_data *p_obj,
    bcmos_errno *p_err,
    bcmolt_string *p_err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_SCHED_CFG_DATA_ID_ATTACHMENT_POINT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "attachment_point.");
        if (!bcmolt_tm_sched_attachment_point_validate(&p_obj->attachment_point, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_SCHED_CFG_DATA_ID_SCHED_TYPE))
    {
        switch (p_obj->sched_type)
        {
        case BCMOLT_TM_SCHED_TYPE_UNDEFINED:
        case BCMOLT_TM_SCHED_TYPE_WFQ:
        case BCMOLT_TM_SCHED_TYPE_SP:
        case BCMOLT_TM_SCHED_TYPE_SP_WFQ:
            break;
        default:
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "sched_type: enum value %d is unexpected\n", (int)p_obj->sched_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_SCHED_CFG_DATA_ID_NUM_PRIORITIES))
    {
        if (p_obj->num_priorities > 9)
        {
            *p_err = BCM_ERR_RANGE;
            bcmolt_string_append(p_err_details, "num_priorities: %u is greater than the maximum value of 9\n", p_obj->num_priorities);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_SCHED_CFG_DATA_ID_RATE))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "rate.");
        if (!bcmolt_tm_shaping_validate(&p_obj->rate, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_SCHED_CFG_DATA_ID_STATE))
    {
        *p_err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(p_err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(p_obj->presence_mask, BCMOLT_TM_SCHED_CFG_DATA_ID_CIR_ATTACHMENT_POINT))
    {
        int prefix_len = bcmolt_string_append(p_err_details, "cir_attachment_point.");
        if (!bcmolt_tm_sched_attachment_point_validate(&p_obj->cir_attachment_point, p_err, p_err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(p_err_details, prefix_len);
    }
    return BCMOS_TRUE;
}


