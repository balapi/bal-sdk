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
#include <bcmolt_buf.h>
#include <bcmolt_string.h>
#include <bcmolt_system_types.h>
#include <bcmolt_system_type_funcs.h>
#include "bcmolt_api_model_supporting_struct_funcs.h"
#include "bcmolt_api_model_supporting_enum_funcs.h"

void bcmolt_intf_ref_set_default(bcmolt_intf_ref *obj)
{
    obj->presence_mask = 0;
    obj->intf_type = BCMOLT_INTERFACE_TYPE_UNASSIGNED;
    obj->intf_id = (bcmolt_interface_id)65535U;
    obj->intf_opt = (bcmolt_intf_opt)0U;
}

bcmos_bool bcmolt_intf_ref_validate(const bcmolt_intf_ref *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INTF_REF_ID_INTF_TYPE))
    {
        switch (obj->intf_type)
        {
        case BCMOLT_INTERFACE_TYPE_PON:
        case BCMOLT_INTERFACE_TYPE_NNI:
        case BCMOLT_INTERFACE_TYPE_HOST:
        case BCMOLT_INTERFACE_TYPE_ERPS:
        case BCMOLT_INTERFACE_TYPE_LAG:
        case BCMOLT_INTERFACE_TYPE_PROTECTION:
        case BCMOLT_INTERFACE_TYPE_UNASSIGNED:
        case BCMOLT_INTERFACE_TYPE_REMOTE_PON:
        case BCMOLT_INTERFACE_TYPE_NIC:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "intf_type: enum value %d is unexpected\n", (int)obj->intf_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INTF_REF_ID_INTF_ID))
    {
        /* obj->intf_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INTF_REF_ID_INTF_OPT))
    {
        if ((obj->intf_opt & ~0x1) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "intf_opt: 0x%X includes invalid bits\n", obj->intf_opt);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_fwd_action_set_default(bcmolt_access_control_fwd_action *obj)
{
    obj->presence_mask = 0;
    obj->action = BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_INVALID;
    bcmolt_intf_ref_set_default(&obj->redirect_intf_ref);
}

bcmos_bool bcmolt_access_control_fwd_action_validate(const bcmolt_access_control_fwd_action *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID_ACTION))
    {
        switch (obj->action)
        {
        case BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_INVALID:
        case BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_TRAP_TO_HOST:
        case BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_DROP:
        case BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_REDIRECT:
        case BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_NO_ACTION:
        case BCMOLT_ACCESS_CONTROL_FWD_ACTION_TYPE_COUNT_ONLY:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "action: enum value %d is unexpected\n", (int)obj->action);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACCESS_CONTROL_FWD_ACTION_ID_REDIRECT_INTF_REF))
    {
        int prefix_len = bcmolt_string_append(err_details, "redirect_intf_ref.");
        if (!bcmolt_intf_ref_validate(&obj->redirect_intf_ref, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_access_control_pkt_modifier_set_default(bcmolt_access_control_pkt_modifier *obj)
{
    obj->presence_mask = 0;
    obj->pkt_modifier_bit_mask = (bcmolt_action_control_pkt_modifiers)0UL;
    obj->o_vid = 0U;
    obj->i_vid = 0U;
    obj->o_pbits = 0;
    obj->i_pbits = 0;
    obj->dscp = 0;
    obj->ttl = 0;
}

bcmos_bool bcmolt_access_control_pkt_modifier_validate(const bcmolt_access_control_pkt_modifier *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_PKT_MODIFIER_BIT_MASK))
    {
        if ((obj->pkt_modifier_bit_mask & ~0xFFUL) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "pkt_modifier_bit_mask: 0x%X includes invalid bits\n", obj->pkt_modifier_bit_mask);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_O_VID))
    {
        /* obj->o_vid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_I_VID))
    {
        /* obj->i_vid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_O_PBITS))
    {
        /* obj->o_pbits can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_I_PBITS))
    {
        /* obj->i_pbits can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_DSCP))
    {
        /* obj->dscp can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACCESS_CONTROL_PKT_MODIFIER_ID_TTL))
    {
        /* obj->ttl can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_action_set_default(bcmolt_action *obj)
{
    obj->presence_mask = 0;
    obj->cmds_bitmask = (bcmolt_action_cmd_id)0UL;
    obj->o_vid = 0U;
    obj->o_pbits = 0;
    obj->i_vid = 0U;
    obj->i_pbits = 0;
    obj->tag_format = BCMOLT_ACTION_TAG_FORMAT_DOT_1_Q;
}

bcmos_bool bcmolt_action_validate(const bcmolt_action *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACTION_ID_CMDS_BITMASK))
    {
        if ((obj->cmds_bitmask & ~0x377UL) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "cmds_bitmask: 0x%X includes invalid bits\n", obj->cmds_bitmask);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACTION_ID_O_VID))
    {
        if (obj->o_vid > 4094U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "o_vid: %u is greater than the maximum value of 4094\n", obj->o_vid);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACTION_ID_O_PBITS))
    {
        if (obj->o_pbits > 7)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "o_pbits: %u is greater than the maximum value of 7\n", obj->o_pbits);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACTION_ID_I_VID))
    {
        if (obj->i_vid > 4094U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "i_vid: %u is greater than the maximum value of 4094\n", obj->i_vid);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACTION_ID_I_PBITS))
    {
        if (obj->i_pbits > 7)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "i_pbits: %u is greater than the maximum value of 7\n", obj->i_pbits);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ACTION_ID_TAG_FORMAT))
    {
        switch (obj->tag_format)
        {
        case BCMOLT_ACTION_TAG_FORMAT_DOT_1_Q:
        case BCMOLT_ACTION_TAG_FORMAT_Q_IN_Q:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tag_format: enum value %d is unexpected\n", (int)obj->tag_format);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_bin_str_16_set_default(bcmolt_bin_str_16 *obj)
{
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
    obj->arr[4] = 0;
    obj->arr[5] = 0;
    obj->arr[6] = 0;
    obj->arr[7] = 0;
    obj->arr[8] = 0;
    obj->arr[9] = 0;
    obj->arr[10] = 0;
    obj->arr[11] = 0;
    obj->arr[12] = 0;
    obj->arr[13] = 0;
    obj->arr[14] = 0;
    obj->arr[15] = 0;
}

bcmos_bool bcmolt_bin_str_16_validate(const bcmolt_bin_str_16 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_aes_key_set_default(bcmolt_aes_key *obj)
{
    obj->presence_mask = 0;
    bcmolt_bin_str_16_set_default(&obj->bytes);
}

bcmos_bool bcmolt_aes_key_validate(const bcmolt_aes_key *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_AES_KEY_ID_BYTES))
    {
        int prefix_len = bcmolt_string_append(err_details, "bytes.");
        if (!bcmolt_bin_str_16_validate(&obj->bytes, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_aes_key_2_set_default(bcmolt_arr_aes_key_2 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    bcmolt_aes_key_set_default(&obj->arr[0]);
    bcmolt_aes_key_set_default(&obj->arr[1]);
}

bcmos_bool bcmolt_arr_aes_key_2_validate(const bcmolt_arr_aes_key_2 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 2; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_aes_key_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_calibration_record_8_set_default(bcmolt_arr_calibration_record_8 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = BCMOLT_CALIBRATION_RECORD_UNSPECIFIED;
    obj->arr[1] = BCMOLT_CALIBRATION_RECORD_UNSPECIFIED;
    obj->arr[2] = BCMOLT_CALIBRATION_RECORD_UNSPECIFIED;
    obj->arr[3] = BCMOLT_CALIBRATION_RECORD_UNSPECIFIED;
    obj->arr[4] = BCMOLT_CALIBRATION_RECORD_UNSPECIFIED;
    obj->arr[5] = BCMOLT_CALIBRATION_RECORD_UNSPECIFIED;
    obj->arr[6] = BCMOLT_CALIBRATION_RECORD_UNSPECIFIED;
    obj->arr[7] = BCMOLT_CALIBRATION_RECORD_UNSPECIFIED;
}

bcmos_bool bcmolt_arr_calibration_record_8_validate(const bcmolt_arr_calibration_record_8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 8; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            switch (obj->arr[i])
            {
            case BCMOLT_CALIBRATION_RECORD_UNSPECIFIED:
            case BCMOLT_CALIBRATION_RECORD_UNCALIBRATED:
            case BCMOLT_CALIBRATION_RECORD_LOOSE:
            case BCMOLT_CALIBRATION_RECORD_SUFFICIENT:
                break;
            default:
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "arr[i]: enum value %d is unexpected\n", (int)obj->arr[i]);
                return BCMOS_FALSE;
            }
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_ds_frequency_offset_set_default(bcmolt_ds_frequency_offset *obj)
{
    obj->presence_mask = 0;
    obj->sign = BCMOLT_SIGN_POSITIVE;
    obj->value = 0;
}

bcmos_bool bcmolt_ds_frequency_offset_validate(const bcmolt_ds_frequency_offset *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_DS_FREQUENCY_OFFSET_ID_SIGN))
    {
        switch (obj->sign)
        {
        case BCMOLT_SIGN_POSITIVE:
        case BCMOLT_SIGN_NEGATIVE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sign: enum value %d is unexpected\n", (int)obj->sign);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_DS_FREQUENCY_OFFSET_ID_VALUE))
    {
        /* obj->value can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_id_set_default(bcmolt_pon_id *obj)
{
    obj->presence_mask = 0;
    obj->administrative_label = 0UL;
    obj->dwlch_id = 0;
}

bcmos_bool bcmolt_pon_id_validate(const bcmolt_pon_id *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ID_ID_ADMINISTRATIVE_LABEL))
    {
        if (obj->administrative_label > 4294967280UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "administrative_label: %u is greater than the maximum value of 4294967280\n", obj->administrative_label);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ID_ID_DWLCH_ID))
    {
        if (obj->dwlch_id > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "dwlch_id: %u is greater than the maximum value of 15\n", obj->dwlch_id);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_channel_profile_set_default(bcmolt_channel_profile *obj)
{
    obj->presence_mask = 0;
    obj->version = 0;
    obj->channel_index = 0;
    bcmolt_ds_frequency_offset_set_default(&obj->ds_frequency_offset);
    obj->channel_partition = 0;
    obj->uwlch_id = 0;
    obj->us_frequency = 0UL;
    obj->us_rate = BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_2_P_5_G;
    obj->default_onu_attenuation = 0;
    obj->response_threshold = 0;
    obj->us_link_type = BCMOLT_LINK_TYPE_UNSPECIFIED;
    obj->is_valid = BCMOS_TRUE;
    bcmolt_pon_id_set_default(&obj->pon_id);
}

bcmos_bool bcmolt_channel_profile_validate(const bcmolt_channel_profile *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_VERSION))
    {
        if (obj->version > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "version: %u is greater than the maximum value of 15\n", obj->version);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_CHANNEL_INDEX))
    {
        if (obj->channel_index > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "channel_index: %u is greater than the maximum value of 15\n", obj->channel_index);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_DS_FREQUENCY_OFFSET))
    {
        int prefix_len = bcmolt_string_append(err_details, "ds_frequency_offset.");
        if (!bcmolt_ds_frequency_offset_validate(&obj->ds_frequency_offset, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_CHANNEL_PARTITION))
    {
        if (obj->channel_partition > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "channel_partition: %u is greater than the maximum value of 15\n", obj->channel_partition);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_UWLCH_ID))
    {
        if (obj->uwlch_id > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "uwlch_id: %u is greater than the maximum value of 15\n", obj->uwlch_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_US_FREQUENCY))
    {
        /* obj->us_frequency can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_US_RATE))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "us_rate: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_DEFAULT_ONU_ATTENUATION))
    {
        if (obj->default_onu_attenuation > 7)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "default_onu_attenuation: %u is greater than the maximum value of 7\n", obj->default_onu_attenuation);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_RESPONSE_THRESHOLD))
    {
        /* obj->response_threshold can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_US_LINK_TYPE))
    {
        switch (obj->us_link_type)
        {
        case BCMOLT_LINK_TYPE_UNSPECIFIED:
        case BCMOLT_LINK_TYPE_B:
        case BCMOLT_LINK_TYPE_A:
        case BCMOLT_LINK_TYPE_A_AND_B:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "us_link_type: enum value %d is unexpected\n", (int)obj->us_link_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_IS_VALID))
    {
        /* obj->is_valid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CHANNEL_PROFILE_ID_PON_ID))
    {
        int prefix_len = bcmolt_string_append(err_details, "pon_id.");
        if (!bcmolt_pon_id_validate(&obj->pon_id, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_channel_profile_8_set_default(bcmolt_arr_channel_profile_8 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    bcmolt_channel_profile_set_default(&obj->arr[0]);
    bcmolt_channel_profile_set_default(&obj->arr[1]);
    bcmolt_channel_profile_set_default(&obj->arr[2]);
    bcmolt_channel_profile_set_default(&obj->arr[3]);
    bcmolt_channel_profile_set_default(&obj->arr[4]);
    bcmolt_channel_profile_set_default(&obj->arr[5]);
    bcmolt_channel_profile_set_default(&obj->arr[6]);
    bcmolt_channel_profile_set_default(&obj->arr[7]);
}

bcmos_bool bcmolt_arr_channel_profile_8_validate(const bcmolt_arr_channel_profile_8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 8; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_channel_profile_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_intf_ref_16_set_default(bcmolt_arr_intf_ref_16 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    bcmolt_intf_ref_set_default(&obj->arr[0]);
    bcmolt_intf_ref_set_default(&obj->arr[1]);
    bcmolt_intf_ref_set_default(&obj->arr[2]);
    bcmolt_intf_ref_set_default(&obj->arr[3]);
    bcmolt_intf_ref_set_default(&obj->arr[4]);
    bcmolt_intf_ref_set_default(&obj->arr[5]);
    bcmolt_intf_ref_set_default(&obj->arr[6]);
    bcmolt_intf_ref_set_default(&obj->arr[7]);
    bcmolt_intf_ref_set_default(&obj->arr[8]);
    bcmolt_intf_ref_set_default(&obj->arr[9]);
    bcmolt_intf_ref_set_default(&obj->arr[10]);
    bcmolt_intf_ref_set_default(&obj->arr[11]);
    bcmolt_intf_ref_set_default(&obj->arr[12]);
    bcmolt_intf_ref_set_default(&obj->arr[13]);
    bcmolt_intf_ref_set_default(&obj->arr[14]);
    bcmolt_intf_ref_set_default(&obj->arr[15]);
}

bcmos_bool bcmolt_arr_intf_ref_16_validate(const bcmolt_arr_intf_ref_16 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 16; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_intf_ref_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_link_state_8_set_default(bcmolt_arr_link_state_8 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = BCMOLT_LINK_STATE_LINK_DOWN;
    obj->arr[1] = BCMOLT_LINK_STATE_LINK_DOWN;
    obj->arr[2] = BCMOLT_LINK_STATE_LINK_DOWN;
    obj->arr[3] = BCMOLT_LINK_STATE_LINK_DOWN;
    obj->arr[4] = BCMOLT_LINK_STATE_LINK_DOWN;
    obj->arr[5] = BCMOLT_LINK_STATE_LINK_DOWN;
    obj->arr[6] = BCMOLT_LINK_STATE_LINK_DOWN;
    obj->arr[7] = BCMOLT_LINK_STATE_LINK_DOWN;
}

bcmos_bool bcmolt_arr_link_state_8_validate(const bcmolt_arr_link_state_8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 8; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            switch (obj->arr[i])
            {
            case BCMOLT_LINK_STATE_LINK_DOWN:
            case BCMOLT_LINK_STATE_LINK_UP:
                break;
            default:
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "arr[i]: enum value %d is unexpected\n", (int)obj->arr[i]);
                return BCMOS_FALSE;
            }
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_nni_id_8_set_default(bcmolt_arr_nni_id_8 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = (bcmolt_nni_id)0;
    obj->arr[1] = (bcmolt_nni_id)0;
    obj->arr[2] = (bcmolt_nni_id)0;
    obj->arr[3] = (bcmolt_nni_id)0;
    obj->arr[4] = (bcmolt_nni_id)0;
    obj->arr[5] = (bcmolt_nni_id)0;
    obj->arr[6] = (bcmolt_nni_id)0;
    obj->arr[7] = (bcmolt_nni_id)0;
}

bcmos_bool bcmolt_arr_nni_id_8_validate(const bcmolt_arr_nni_id_8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 8; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
        }
    }
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_ploam_filter_set_default(bcmolt_ploam_filter *obj)
{
    obj->presence_mask = 0;
    obj->ploam_id = 0;
}

bcmos_bool bcmolt_ploam_filter_validate(const bcmolt_ploam_filter *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PLOAM_FILTER_ID_PLOAM_ID))
    {
        /* obj->ploam_id can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_ploam_filter_5_set_default(bcmolt_arr_ploam_filter_5 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    bcmolt_ploam_filter_set_default(&obj->arr[0]);
    bcmolt_ploam_filter_set_default(&obj->arr[1]);
    bcmolt_ploam_filter_set_default(&obj->arr[2]);
    bcmolt_ploam_filter_set_default(&obj->arr[3]);
    bcmolt_ploam_filter_set_default(&obj->arr[4]);
}

bcmos_bool bcmolt_arr_ploam_filter_5_validate(const bcmolt_arr_ploam_filter_5 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 5; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_ploam_filter_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_policer_ref_set_default(bcmolt_policer_ref *obj)
{
    obj->presence_mask = 0;
    obj->type = BCMOLT_POLICER_REFERENCE_TYPE_POLICER_PROFILE;
    obj->id = 65535U;
}

bcmos_bool bcmolt_policer_ref_validate(const bcmolt_policer_ref *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_POLICER_REF_ID_TYPE))
    {
        switch (obj->type)
        {
        case BCMOLT_POLICER_REFERENCE_TYPE_POLICER_PROFILE:
        case BCMOLT_POLICER_REFERENCE_TYPE_HARDWARE_METER:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "type: enum value %d is unexpected\n", (int)obj->type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_POLICER_REF_ID_ID))
    {
        /* obj->id can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_policer_ref_4_set_default(bcmolt_arr_policer_ref_4 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    bcmolt_policer_ref_set_default(&obj->arr[0]);
    bcmolt_policer_ref_set_default(&obj->arr[1]);
    bcmolt_policer_ref_set_default(&obj->arr[2]);
    bcmolt_policer_ref_set_default(&obj->arr[3]);
}

bcmos_bool bcmolt_arr_policer_ref_4_validate(const bcmolt_arr_policer_ref_4 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 4; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_policer_ref_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_power_consumption_channel_report_set_default(bcmolt_power_consumption_channel_report *obj)
{
    obj->presence_mask = 0;
    obj->ds_wavelength_channel_id = 0;
    obj->us_wavelength_channel_id = 0;
    obj->power_consumption = 0U;
}

bcmos_bool bcmolt_power_consumption_channel_report_validate(const bcmolt_power_consumption_channel_report *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID_DS_WAVELENGTH_CHANNEL_ID))
    {
        /* obj->ds_wavelength_channel_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID_US_WAVELENGTH_CHANNEL_ID))
    {
        /* obj->us_wavelength_channel_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_POWER_CONSUMPTION_CHANNEL_REPORT_ID_POWER_CONSUMPTION))
    {
        /* obj->power_consumption can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_power_consumption_channel_report_8_set_default(bcmolt_arr_power_consumption_channel_report_8 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    bcmolt_power_consumption_channel_report_set_default(&obj->arr[0]);
    bcmolt_power_consumption_channel_report_set_default(&obj->arr[1]);
    bcmolt_power_consumption_channel_report_set_default(&obj->arr[2]);
    bcmolt_power_consumption_channel_report_set_default(&obj->arr[3]);
    bcmolt_power_consumption_channel_report_set_default(&obj->arr[4]);
    bcmolt_power_consumption_channel_report_set_default(&obj->arr[5]);
    bcmolt_power_consumption_channel_report_set_default(&obj->arr[6]);
    bcmolt_power_consumption_channel_report_set_default(&obj->arr[7]);
}

bcmos_bool bcmolt_arr_power_consumption_channel_report_8_validate(const bcmolt_arr_power_consumption_channel_report_8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 8; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_power_consumption_channel_report_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_ip_v_4_src_binding_set_default(bcmolt_ip_v_4_src_binding *obj)
{
    obj->presence_mask = 0;
    bcmos_ipv4_address_init(&obj->src_ip);
    obj->src_ip_mask.u8[0] = 0xFF;
    obj->src_ip_mask.u8[1] = 0xFF;
    obj->src_ip_mask.u8[2] = 0xFF;
    obj->src_ip_mask.u8[3] = 0xFF;
}

bcmos_bool bcmolt_ip_v_4_src_binding_validate(const bcmolt_ip_v_4_src_binding *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_IP_V_4_SRC_BINDING_ID_SRC_IP))
    {
        /* obj->src_ip can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_IP_V_4_SRC_BINDING_ID_SRC_IP_MASK))
    {
        /* obj->src_ip_mask can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_ip_v_6_src_binding_set_default(bcmolt_ip_v_6_src_binding *obj)
{
    obj->presence_mask = 0;
    bcmos_ipv6_address_init(&obj->src_ip_v_6);
    obj->src_ip_v_6_mask.u8[0] = 0xFF;
    obj->src_ip_v_6_mask.u8[1] = 0xFF;
    obj->src_ip_v_6_mask.u8[2] = 0xFF;
    obj->src_ip_v_6_mask.u8[3] = 0xFF;
    obj->src_ip_v_6_mask.u8[4] = 0xFF;
    obj->src_ip_v_6_mask.u8[5] = 0xFF;
    obj->src_ip_v_6_mask.u8[6] = 0xFF;
    obj->src_ip_v_6_mask.u8[7] = 0xFF;
    obj->src_ip_v_6_mask.u8[8] = 0xFF;
    obj->src_ip_v_6_mask.u8[9] = 0xFF;
    obj->src_ip_v_6_mask.u8[10] = 0xFF;
    obj->src_ip_v_6_mask.u8[11] = 0xFF;
    obj->src_ip_v_6_mask.u8[12] = 0xFF;
    obj->src_ip_v_6_mask.u8[13] = 0xFF;
    obj->src_ip_v_6_mask.u8[14] = 0xFF;
    obj->src_ip_v_6_mask.u8[15] = 0xFF;
}

bcmos_bool bcmolt_ip_v_6_src_binding_validate(const bcmolt_ip_v_6_src_binding *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_IP_V_6_SRC_BINDING_ID_SRC_IP_V_6))
    {
        /* obj->src_ip_v_6 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_IP_V_6_SRC_BINDING_ID_SRC_IP_V_6_MASK))
    {
        /* obj->src_ip_v_6_mask can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_src_binding_info_set_default(bcmolt_src_binding_info *obj)
{
    obj->presence_mask = 0;
    bcmos_mac_address_init(&obj->src_mac);
    bcmolt_ip_v_4_src_binding_set_default(&obj->ip_v_4);
    bcmolt_ip_v_6_src_binding_set_default(&obj->ip_v_6);
    obj->src_binding_fields = (bcmolt_src_binding_fields)0U;
}

bcmos_bool bcmolt_src_binding_info_validate(const bcmolt_src_binding_info *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SRC_BINDING_INFO_ID_SRC_MAC))
    {
        /* obj->src_mac can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SRC_BINDING_INFO_ID_IP_V_4))
    {
        int prefix_len = bcmolt_string_append(err_details, "ip_v_4.");
        if (!bcmolt_ip_v_4_src_binding_validate(&obj->ip_v_4, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SRC_BINDING_INFO_ID_IP_V_6))
    {
        int prefix_len = bcmolt_string_append(err_details, "ip_v_6.");
        if (!bcmolt_ip_v_6_src_binding_validate(&obj->ip_v_6, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SRC_BINDING_INFO_ID_SRC_BINDING_FIELDS))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "src_binding_fields: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_src_binding_info_16_set_default(bcmolt_arr_src_binding_info_16 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    bcmolt_src_binding_info_set_default(&obj->arr[0]);
    bcmolt_src_binding_info_set_default(&obj->arr[1]);
    bcmolt_src_binding_info_set_default(&obj->arr[2]);
    bcmolt_src_binding_info_set_default(&obj->arr[3]);
    bcmolt_src_binding_info_set_default(&obj->arr[4]);
    bcmolt_src_binding_info_set_default(&obj->arr[5]);
    bcmolt_src_binding_info_set_default(&obj->arr[6]);
    bcmolt_src_binding_info_set_default(&obj->arr[7]);
    bcmolt_src_binding_info_set_default(&obj->arr[8]);
    bcmolt_src_binding_info_set_default(&obj->arr[9]);
    bcmolt_src_binding_info_set_default(&obj->arr[10]);
    bcmolt_src_binding_info_set_default(&obj->arr[11]);
    bcmolt_src_binding_info_set_default(&obj->arr[12]);
    bcmolt_src_binding_info_set_default(&obj->arr[13]);
    bcmolt_src_binding_info_set_default(&obj->arr[14]);
    bcmolt_src_binding_info_set_default(&obj->arr[15]);
}

bcmos_bool bcmolt_arr_src_binding_info_16_validate(const bcmolt_arr_src_binding_info_16 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 16; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_src_binding_info_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_queue_ref_set_default(bcmolt_tm_queue_ref *obj)
{
    obj->presence_mask = 0;
    obj->sched_id = (bcmolt_tm_sched_id)65535U;
    obj->queue_id = (bcmolt_tm_queue_id)65535U;
}

bcmos_bool bcmolt_tm_queue_ref_validate(const bcmolt_tm_queue_ref *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TM_QUEUE_REF_ID_SCHED_ID))
    {
        /* obj->sched_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TM_QUEUE_REF_ID_QUEUE_ID))
    {
        /* obj->queue_id can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_tm_queue_ref_8_set_default(bcmolt_arr_tm_queue_ref_8 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    bcmolt_tm_queue_ref_set_default(&obj->arr[0]);
    bcmolt_tm_queue_ref_set_default(&obj->arr[1]);
    bcmolt_tm_queue_ref_set_default(&obj->arr[2]);
    bcmolt_tm_queue_ref_set_default(&obj->arr[3]);
    bcmolt_tm_queue_ref_set_default(&obj->arr[4]);
    bcmolt_tm_queue_ref_set_default(&obj->arr[5]);
    bcmolt_tm_queue_ref_set_default(&obj->arr[6]);
    bcmolt_tm_queue_ref_set_default(&obj->arr[7]);
}

bcmos_bool bcmolt_arr_tm_queue_ref_8_validate(const bcmolt_arr_tm_queue_ref_8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 8; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_tm_queue_ref_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_u16_2_set_default(bcmolt_arr_u16_2 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0U;
    obj->arr[1] = 0U;
}

bcmos_bool bcmolt_arr_u16_2_validate(const bcmolt_arr_u16_2 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_arr_u64_4_set_default(bcmolt_arr_u64_4 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0ULL;
    obj->arr[1] = 0ULL;
    obj->arr[2] = 0ULL;
    obj->arr[3] = 0ULL;
}

bcmos_bool bcmolt_arr_u64_4_validate(const bcmolt_arr_u64_4 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_arr_u8_20_set_default(bcmolt_arr_u8_20 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
    obj->arr[4] = 0;
    obj->arr[5] = 0;
    obj->arr[6] = 0;
    obj->arr[7] = 0;
    obj->arr[8] = 0;
    obj->arr[9] = 0;
    obj->arr[10] = 0;
    obj->arr[11] = 0;
    obj->arr[12] = 0;
    obj->arr[13] = 0;
    obj->arr[14] = 0;
    obj->arr[15] = 0;
    obj->arr[16] = 0;
    obj->arr[17] = 0;
    obj->arr[18] = 0;
    obj->arr[19] = 0;
}

bcmos_bool bcmolt_arr_u8_20_validate(const bcmolt_arr_u8_20 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_arr_u8_8_set_default(bcmolt_arr_u8_8 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
    obj->arr[4] = 0;
    obj->arr[5] = 0;
    obj->arr[6] = 0;
    obj->arr[7] = 0;
}

bcmos_bool bcmolt_arr_u8_8_validate(const bcmolt_arr_u8_8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_xgpon_burst_profile_set_default(bcmolt_xgpon_burst_profile *obj)
{
    obj->presence_mask = 0;
    obj->profile_version = 0x0;
    obj->type = BCMOLT_BURST_PROFILE_TYPE_RANGING;
    obj->is_fec_on = BCMOS_FALSE;
    obj->delimiter_size_in_bytes = 0;
    obj->delimiter_pattern_high = 0x0UL;
    obj->delimiter_pattern_low = 0x8UL;
    obj->preamble_length_in_bytes = 8;
    obj->preamble_repeats_count = 0;
    obj->preamble_pattern_high = 0x0UL;
    obj->preamble_pattern_low = 0x0UL;
    obj->pon_tag = 0ULL;
    obj->num_of_guard_bytes = 0UL;
    obj->is_profile_valid = BCMOS_FALSE;
    obj->burst_overhead_size_in_words = 0UL;
}

bcmos_bool bcmolt_xgpon_burst_profile_validate(const bcmolt_xgpon_burst_profile *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_PROFILE_VERSION))
    {
        /* obj->profile_version can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_TYPE))
    {
        switch (obj->type)
        {
        case BCMOLT_BURST_PROFILE_TYPE_RANGING:
        case BCMOLT_BURST_PROFILE_TYPE_DATA:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "type: enum value %d is unexpected\n", (int)obj->type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_IS_FEC_ON))
    {
        /* obj->is_fec_on can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_DELIMITER_SIZE_IN_BYTES))
    {
        if (obj->delimiter_size_in_bytes > 8)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "delimiter_size_in_bytes: %u is greater than the maximum value of 8\n", obj->delimiter_size_in_bytes);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_DELIMITER_PATTERN_HIGH))
    {
        /* obj->delimiter_pattern_high can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_DELIMITER_PATTERN_LOW))
    {
        /* obj->delimiter_pattern_low can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_LENGTH_IN_BYTES))
    {
        if (obj->preamble_length_in_bytes < 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "preamble_length_in_bytes: %u is less than the minimum value of 1\n", obj->preamble_length_in_bytes);
            return BCMOS_FALSE;
        }
        if (obj->preamble_length_in_bytes > 8)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "preamble_length_in_bytes: %u is greater than the maximum value of 8\n", obj->preamble_length_in_bytes);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_REPEATS_COUNT))
    {
        /* obj->preamble_repeats_count can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_PATTERN_HIGH))
    {
        /* obj->preamble_pattern_high can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_PREAMBLE_PATTERN_LOW))
    {
        /* obj->preamble_pattern_low can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_PON_TAG))
    {
        /* obj->pon_tag can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_NUM_OF_GUARD_BYTES))
    {
        /* obj->num_of_guard_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_IS_PROFILE_VALID))
    {
        /* obj->is_profile_valid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_BURST_PROFILE_ID_BURST_OVERHEAD_SIZE_IN_WORDS))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "burst_overhead_size_in_words: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_arr_xgpon_burst_profile_4_set_default(bcmolt_arr_xgpon_burst_profile_4 *obj)
{
    obj->arr_index_mask = 0;
    memset(obj->arr, 0, sizeof(obj->arr));
    bcmolt_xgpon_burst_profile_set_default(&obj->arr[0]);
    bcmolt_xgpon_burst_profile_set_default(&obj->arr[1]);
    bcmolt_xgpon_burst_profile_set_default(&obj->arr[2]);
    bcmolt_xgpon_burst_profile_set_default(&obj->arr[3]);
}

bcmos_bool bcmolt_arr_xgpon_burst_profile_4_validate(const bcmolt_arr_xgpon_burst_profile_4 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    for (uint32_t i = 0; i < 4; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_xgpon_burst_profile_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_automatic_onu_deactivation_set_default(bcmolt_automatic_onu_deactivation *obj)
{
    obj->presence_mask = 0;
    obj->los = BCMOS_FALSE;
    obj->onu_alarms = BCMOS_FALSE;
    obj->tiwi = BCMOS_FALSE;
    obj->ack_timeout = BCMOS_FALSE;
    obj->sfi = BCMOS_FALSE;
    obj->loki = BCMOS_FALSE;
}

bcmos_bool bcmolt_automatic_onu_deactivation_validate(const bcmolt_automatic_onu_deactivation *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_LOS))
    {
        /* obj->los can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_ONU_ALARMS))
    {
        /* obj->onu_alarms can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_TIWI))
    {
        /* obj->tiwi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_ACK_TIMEOUT))
    {
        /* obj->ack_timeout can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_SFI))
    {
        /* obj->sfi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_AUTOMATIC_ONU_DEACTIVATION_ID_LOKI))
    {
        /* obj->loki can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_ber_monitor_params_set_default(bcmolt_ber_monitor_params *obj)
{
    obj->presence_mask = 0;
    obj->us_ber_interval = 5000UL;
    obj->sf_threshold = 3;
    obj->sd_threshold = 5;
}

bcmos_bool bcmolt_ber_monitor_params_validate(const bcmolt_ber_monitor_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_BER_MONITOR_PARAMS_ID_US_BER_INTERVAL))
    {
        if (obj->us_ber_interval > 60000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "us_ber_interval: %u is greater than the maximum value of 60000\n", obj->us_ber_interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_BER_MONITOR_PARAMS_ID_SF_THRESHOLD))
    {
        if (obj->sf_threshold < 3)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sf_threshold: %u is less than the minimum value of 3\n", obj->sf_threshold);
            return BCMOS_FALSE;
        }
        if (obj->sf_threshold > 8)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sf_threshold: %u is greater than the maximum value of 8\n", obj->sf_threshold);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_BER_MONITOR_PARAMS_ID_SD_THRESHOLD))
    {
        if (obj->sd_threshold < 4)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sd_threshold: %u is less than the minimum value of 4\n", obj->sd_threshold);
            return BCMOS_FALSE;
        }
        if (obj->sd_threshold > 9)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sd_threshold: %u is greater than the maximum value of 9\n", obj->sd_threshold);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_bin_str_set_default(bcmolt_bin_str *obj)
{
    obj->len = 0UL;
    obj->arr = NULL;
}

bcmos_bool bcmolt_bin_str_validate(const bcmolt_bin_str *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->len can't be invalid. */
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_bin_str_10_set_default(bcmolt_bin_str_10 *obj)
{
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
    obj->arr[4] = 0;
    obj->arr[5] = 0;
    obj->arr[6] = 0;
    obj->arr[7] = 0;
    obj->arr[8] = 0;
    obj->arr[9] = 0;
}

bcmos_bool bcmolt_bin_str_10_validate(const bcmolt_bin_str_10 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_bin_str_13_set_default(bcmolt_bin_str_13 *obj)
{
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
    obj->arr[4] = 0;
    obj->arr[5] = 0;
    obj->arr[6] = 0;
    obj->arr[7] = 0;
    obj->arr[8] = 0;
    obj->arr[9] = 0;
    obj->arr[10] = 0;
    obj->arr[11] = 0;
    obj->arr[12] = 0;
}

bcmos_bool bcmolt_bin_str_13_validate(const bcmolt_bin_str_13 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_bin_str_36_set_default(bcmolt_bin_str_36 *obj)
{
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
    obj->arr[4] = 0;
    obj->arr[5] = 0;
    obj->arr[6] = 0;
    obj->arr[7] = 0;
    obj->arr[8] = 0;
    obj->arr[9] = 0;
    obj->arr[10] = 0;
    obj->arr[11] = 0;
    obj->arr[12] = 0;
    obj->arr[13] = 0;
    obj->arr[14] = 0;
    obj->arr[15] = 0;
    obj->arr[16] = 0;
    obj->arr[17] = 0;
    obj->arr[18] = 0;
    obj->arr[19] = 0;
    obj->arr[20] = 0;
    obj->arr[21] = 0;
    obj->arr[22] = 0;
    obj->arr[23] = 0;
    obj->arr[24] = 0;
    obj->arr[25] = 0;
    obj->arr[26] = 0;
    obj->arr[27] = 0;
    obj->arr[28] = 0;
    obj->arr[29] = 0;
    obj->arr[30] = 0;
    obj->arr[31] = 0;
    obj->arr[32] = 0;
    obj->arr[33] = 0;
    obj->arr[34] = 0;
    obj->arr[35] = 0;
}

bcmos_bool bcmolt_bin_str_36_validate(const bcmolt_bin_str_36 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_bin_str_4_set_default(bcmolt_bin_str_4 *obj)
{
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
}

bcmos_bool bcmolt_bin_str_4_validate(const bcmolt_bin_str_4 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_bin_str_40_set_default(bcmolt_bin_str_40 *obj)
{
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
    obj->arr[4] = 0;
    obj->arr[5] = 0;
    obj->arr[6] = 0;
    obj->arr[7] = 0;
    obj->arr[8] = 0;
    obj->arr[9] = 0;
    obj->arr[10] = 0;
    obj->arr[11] = 0;
    obj->arr[12] = 0;
    obj->arr[13] = 0;
    obj->arr[14] = 0;
    obj->arr[15] = 0;
    obj->arr[16] = 0;
    obj->arr[17] = 0;
    obj->arr[18] = 0;
    obj->arr[19] = 0;
    obj->arr[20] = 0;
    obj->arr[21] = 0;
    obj->arr[22] = 0;
    obj->arr[23] = 0;
    obj->arr[24] = 0;
    obj->arr[25] = 0;
    obj->arr[26] = 0;
    obj->arr[27] = 0;
    obj->arr[28] = 0;
    obj->arr[29] = 0;
    obj->arr[30] = 0;
    obj->arr[31] = 0;
    obj->arr[32] = 0;
    obj->arr[33] = 0;
    obj->arr[34] = 0;
    obj->arr[35] = 0;
    obj->arr[36] = 0;
    obj->arr[37] = 0;
    obj->arr[38] = 0;
    obj->arr[39] = 0;
}

bcmos_bool bcmolt_bin_str_40_validate(const bcmolt_bin_str_40 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_bin_str_48_set_default(bcmolt_bin_str_48 *obj)
{
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
    obj->arr[4] = 0;
    obj->arr[5] = 0;
    obj->arr[6] = 0;
    obj->arr[7] = 0;
    obj->arr[8] = 0;
    obj->arr[9] = 0;
    obj->arr[10] = 0;
    obj->arr[11] = 0;
    obj->arr[12] = 0;
    obj->arr[13] = 0;
    obj->arr[14] = 0;
    obj->arr[15] = 0;
    obj->arr[16] = 0;
    obj->arr[17] = 0;
    obj->arr[18] = 0;
    obj->arr[19] = 0;
    obj->arr[20] = 0;
    obj->arr[21] = 0;
    obj->arr[22] = 0;
    obj->arr[23] = 0;
    obj->arr[24] = 0;
    obj->arr[25] = 0;
    obj->arr[26] = 0;
    obj->arr[27] = 0;
    obj->arr[28] = 0;
    obj->arr[29] = 0;
    obj->arr[30] = 0;
    obj->arr[31] = 0;
    obj->arr[32] = 0;
    obj->arr[33] = 0;
    obj->arr[34] = 0;
    obj->arr[35] = 0;
    obj->arr[36] = 0;
    obj->arr[37] = 0;
    obj->arr[38] = 0;
    obj->arr[39] = 0;
    obj->arr[40] = 0;
    obj->arr[41] = 0;
    obj->arr[42] = 0;
    obj->arr[43] = 0;
    obj->arr[44] = 0;
    obj->arr[45] = 0;
    obj->arr[46] = 0;
    obj->arr[47] = 0;
}

bcmos_bool bcmolt_bin_str_48_validate(const bcmolt_bin_str_48 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_bin_str_8_set_default(bcmolt_bin_str_8 *obj)
{
    memset(obj->arr, 0, sizeof(obj->arr));
    obj->arr[0] = 0;
    obj->arr[1] = 0;
    obj->arr[2] = 0;
    obj->arr[3] = 0;
    obj->arr[4] = 0;
    obj->arr[5] = 0;
    obj->arr[6] = 0;
    obj->arr[7] = 0;
}

bcmos_bool bcmolt_bin_str_8_validate(const bcmolt_bin_str_8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_cbr_rt_allocation_profile_set_default(bcmolt_cbr_rt_allocation_profile *obj)
{
    obj->presence_mask = 0;
    obj->ma_7 = 64U;
    obj->ma_3 = 256U;
    obj->ma_1 = 512U;
}

bcmos_bool bcmolt_cbr_rt_allocation_profile_validate(const bcmolt_cbr_rt_allocation_profile *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID_MA_7))
    {
        /* obj->ma_7 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID_MA_3))
    {
        /* obj->ma_3 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CBR_RT_ALLOCATION_PROFILE_ID_MA_1))
    {
        /* obj->ma_1 can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_layer_4_port_range_set_default(bcmolt_layer_4_port_range *obj)
{
    obj->presence_mask = 0;
    obj->min = 0U;
    obj->max = 0U;
}

bcmos_bool bcmolt_layer_4_port_range_validate(const bcmolt_layer_4_port_range *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LAYER_4_PORT_RANGE_ID_MIN))
    {
        /* obj->min can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LAYER_4_PORT_RANGE_ID_MAX))
    {
        /* obj->max can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_classifier_ip_v_6_set_default(bcmolt_classifier_ip_v_6 *obj)
{
    obj->presence_mask = 0;
    obj->classifier_ip_v_6_bitmap = 0ULL;
    obj->match_mld_pkts = BCMOS_FALSE;
    bcmos_ipv6_address_init(&obj->dst_ip_v_6);
    obj->dst_ip_v_6_mask.u8[0] = 0xFF;
    obj->dst_ip_v_6_mask.u8[1] = 0xFF;
    obj->dst_ip_v_6_mask.u8[2] = 0xFF;
    obj->dst_ip_v_6_mask.u8[3] = 0xFF;
    obj->dst_ip_v_6_mask.u8[4] = 0xFF;
    obj->dst_ip_v_6_mask.u8[5] = 0xFF;
    obj->dst_ip_v_6_mask.u8[6] = 0xFF;
    obj->dst_ip_v_6_mask.u8[7] = 0xFF;
    obj->dst_ip_v_6_mask.u8[8] = 0xFF;
    obj->dst_ip_v_6_mask.u8[9] = 0xFF;
    obj->dst_ip_v_6_mask.u8[10] = 0xFF;
    obj->dst_ip_v_6_mask.u8[11] = 0xFF;
    obj->dst_ip_v_6_mask.u8[12] = 0xFF;
    obj->dst_ip_v_6_mask.u8[13] = 0xFF;
    obj->dst_ip_v_6_mask.u8[14] = 0xFF;
    obj->dst_ip_v_6_mask.u8[15] = 0xFF;
    bcmos_ipv6_address_init(&obj->src_ip_v_6);
    obj->src_ip_v_6_mask.u8[0] = 0xFF;
    obj->src_ip_v_6_mask.u8[1] = 0xFF;
    obj->src_ip_v_6_mask.u8[2] = 0xFF;
    obj->src_ip_v_6_mask.u8[3] = 0xFF;
    obj->src_ip_v_6_mask.u8[4] = 0xFF;
    obj->src_ip_v_6_mask.u8[5] = 0xFF;
    obj->src_ip_v_6_mask.u8[6] = 0xFF;
    obj->src_ip_v_6_mask.u8[7] = 0xFF;
    obj->src_ip_v_6_mask.u8[8] = 0xFF;
    obj->src_ip_v_6_mask.u8[9] = 0xFF;
    obj->src_ip_v_6_mask.u8[10] = 0xFF;
    obj->src_ip_v_6_mask.u8[11] = 0xFF;
    obj->src_ip_v_6_mask.u8[12] = 0xFF;
    obj->src_ip_v_6_mask.u8[13] = 0xFF;
    obj->src_ip_v_6_mask.u8[14] = 0xFF;
    obj->src_ip_v_6_mask.u8[15] = 0xFF;
    obj->is_one_ext_hdr = BCMOS_FALSE;
}

bcmos_bool bcmolt_classifier_ip_v_6_validate(const bcmolt_classifier_ip_v_6 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_IP_V_6_ID_CLASSIFIER_IP_V_6_BITMAP))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "classifier_ip_v_6_bitmap: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_IP_V_6_ID_MATCH_MLD_PKTS))
    {
        /* obj->match_mld_pkts can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_IP_V_6_ID_DST_IP_V_6))
    {
        /* obj->dst_ip_v_6 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_IP_V_6_ID_DST_IP_V_6_MASK))
    {
        /* obj->dst_ip_v_6_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_IP_V_6_ID_SRC_IP_V_6))
    {
        /* obj->src_ip_v_6 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_IP_V_6_ID_SRC_IP_V_6_MASK))
    {
        /* obj->src_ip_v_6_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_IP_V_6_ID_IS_ONE_EXT_HDR))
    {
        /* obj->is_one_ext_hdr can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_classifier_set_default(bcmolt_classifier *obj)
{
    obj->presence_mask = 0;
    obj->classifier_bitmap = 0ULL;
    obj->o_vid = 0U;
    obj->o_vid_mask = 4095U;
    obj->i_vid = 0U;
    obj->i_vid_mask = 4095U;
    obj->o_pbits = 0;
    obj->o_pbits_mask = 7;
    obj->i_pbits = 0;
    obj->i_pbits_mask = 7;
    obj->ether_type = 0U;
    obj->ether_type_mask = 65535U;
    bcmos_mac_address_init(&obj->dst_mac);
    obj->dst_mac_mask.u8[0] = 0xFF;
    obj->dst_mac_mask.u8[1] = 0xFF;
    obj->dst_mac_mask.u8[2] = 0xFF;
    obj->dst_mac_mask.u8[3] = 0xFF;
    obj->dst_mac_mask.u8[4] = 0xFF;
    obj->dst_mac_mask.u8[5] = 0xFF;
    bcmos_mac_address_init(&obj->src_mac);
    obj->src_mac_mask.u8[0] = 0xFF;
    obj->src_mac_mask.u8[1] = 0xFF;
    obj->src_mac_mask.u8[2] = 0xFF;
    obj->src_mac_mask.u8[3] = 0xFF;
    obj->src_mac_mask.u8[4] = 0xFF;
    obj->src_mac_mask.u8[5] = 0xFF;
    obj->ip_proto = 0;
    obj->ip_proto_mask = 255;
    bcmos_ipv4_address_init(&obj->dst_ip);
    obj->dst_ip_mask.u8[0] = 0xFF;
    obj->dst_ip_mask.u8[1] = 0xFF;
    obj->dst_ip_mask.u8[2] = 0xFF;
    obj->dst_ip_mask.u8[3] = 0xFF;
    obj->dst_port = 0U;
    bcmolt_layer_4_port_range_set_default(&obj->dst_port_range);
    bcmos_ipv4_address_init(&obj->src_ip);
    obj->src_ip_mask.u8[0] = 0xFF;
    obj->src_ip_mask.u8[1] = 0xFF;
    obj->src_ip_mask.u8[2] = 0xFF;
    obj->src_ip_mask.u8[3] = 0xFF;
    obj->src_port = 0U;
    bcmolt_layer_4_port_range_set_default(&obj->src_port_range);
    obj->pkt_tag_type = (bcmolt_pkt_tag_type)0UL;
    bcmolt_classifier_ip_v_6_set_default(&obj->ip_v_6);
    obj->i2_vid = 0U;
    obj->slow_proto_subtype = 0;
}

bcmos_bool bcmolt_classifier_validate(const bcmolt_classifier *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_CLASSIFIER_BITMAP))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "classifier_bitmap: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_O_VID))
    {
        if (obj->o_vid > 4094U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "o_vid: %u is greater than the maximum value of 4094\n", obj->o_vid);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_O_VID_MASK))
    {
        if (obj->o_vid_mask > 4095U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "o_vid_mask: %u is greater than the maximum value of 0xFFF\n", obj->o_vid_mask);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_I_VID))
    {
        if (obj->i_vid > 4094U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "i_vid: %u is greater than the maximum value of 4094\n", obj->i_vid);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_I_VID_MASK))
    {
        if (obj->i_vid_mask > 4095U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "i_vid_mask: %u is greater than the maximum value of 0xFFF\n", obj->i_vid_mask);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_O_PBITS))
    {
        if (obj->o_pbits > 7)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "o_pbits: %u is greater than the maximum value of 7\n", obj->o_pbits);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_O_PBITS_MASK))
    {
        if (obj->o_pbits_mask > 7)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "o_pbits_mask: %u is greater than the maximum value of 7\n", obj->o_pbits_mask);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_I_PBITS))
    {
        if (obj->i_pbits > 7)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "i_pbits: %u is greater than the maximum value of 7\n", obj->i_pbits);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_I_PBITS_MASK))
    {
        if (obj->i_pbits_mask > 7)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "i_pbits_mask: %u is greater than the maximum value of 7\n", obj->i_pbits_mask);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_ETHER_TYPE))
    {
        /* obj->ether_type can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_ETHER_TYPE_MASK))
    {
        /* obj->ether_type_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_DST_MAC))
    {
        /* obj->dst_mac can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_DST_MAC_MASK))
    {
        /* obj->dst_mac_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_SRC_MAC))
    {
        /* obj->src_mac can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_SRC_MAC_MASK))
    {
        /* obj->src_mac_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_IP_PROTO))
    {
        /* obj->ip_proto can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_IP_PROTO_MASK))
    {
        /* obj->ip_proto_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_DST_IP))
    {
        /* obj->dst_ip can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_DST_IP_MASK))
    {
        /* obj->dst_ip_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_DST_PORT))
    {
        /* obj->dst_port can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_DST_PORT_RANGE))
    {
        int prefix_len = bcmolt_string_append(err_details, "dst_port_range.");
        if (!bcmolt_layer_4_port_range_validate(&obj->dst_port_range, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_SRC_IP))
    {
        /* obj->src_ip can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_SRC_IP_MASK))
    {
        /* obj->src_ip_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_SRC_PORT))
    {
        /* obj->src_port can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_SRC_PORT_RANGE))
    {
        int prefix_len = bcmolt_string_append(err_details, "src_port_range.");
        if (!bcmolt_layer_4_port_range_validate(&obj->src_port_range, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_PKT_TAG_TYPE))
    {
        if ((obj->pkt_tag_type & ~0x1FUL) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "pkt_tag_type: 0x%X includes invalid bits\n", obj->pkt_tag_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_IP_V_6))
    {
        int prefix_len = bcmolt_string_append(err_details, "ip_v_6.");
        if (!bcmolt_classifier_ip_v_6_validate(&obj->ip_v_6, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_I2_VID))
    {
        if (obj->i2_vid > 4094U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "i2_vid: %u is greater than the maximum value of 4094\n", obj->i2_vid);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_CLASSIFIER_ID_SLOW_PROTO_SUBTYPE))
    {
        if (obj->slow_proto_subtype < 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "slow_proto_subtype: %u is less than the minimum value of 1\n", obj->slow_proto_subtype);
            return BCMOS_FALSE;
        }
        if (obj->slow_proto_subtype > 10)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "slow_proto_subtype: %u is greater than the maximum value of 10\n", obj->slow_proto_subtype);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_ddr_test_completed_set_default(bcmolt_ddr_test_completed *obj)
{
    obj->presence_mask = 0;
    obj->status = BCMOLT_DDR_TEST_STATUS_COMPLETED;
    obj->u.completed.presence_mask = 0;
    obj->u.completed.cpu_result = BCMOLT_DDR_TEST_RESULT_SUCCESS;
    obj->u.completed.ras_0_result = BCMOLT_DDR_TEST_RESULT_SUCCESS;
    obj->u.completed.ras_1_result = BCMOLT_DDR_TEST_RESULT_SUCCESS;
}

void bcmolt_ddr_test_completed_set_union_default(bcmolt_ddr_test_completed *obj, bcmolt_ddr_test_status type)
{
    obj->status = type;
    switch (type)
    {
    case BCMOLT_DDR_TEST_STATUS_COMPLETED:
        obj->u.completed.presence_mask = 0;
        obj->u.completed.cpu_result = BCMOLT_DDR_TEST_RESULT_SUCCESS;
        obj->u.completed.ras_0_result = BCMOLT_DDR_TEST_RESULT_SUCCESS;
        obj->u.completed.ras_1_result = BCMOLT_DDR_TEST_RESULT_SUCCESS;
        break;
    case BCMOLT_DDR_TEST_STATUS_CONNECTION_FAILED:
        obj->u.connection_failed.presence_mask = 0;
        obj->u.connection_failed.reason = BCMOLT_HOST_CONNECTION_FAIL_REASON_TIMEOUT;
        break;
    default:
        break;
    }
}

bcmos_bool bcmolt_ddr_test_completed_validate(const bcmolt_ddr_test_completed *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_DDR_TEST_COMPLETED_ID_STATUS))
    {
        switch (obj->status)
        {
        case BCMOLT_DDR_TEST_STATUS_COMPLETED:
        case BCMOLT_DDR_TEST_STATUS_CONNECTION_FAILED:
        case BCMOLT_DDR_TEST_STATUS_TIMEOUT:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "status: enum value %d is unexpected\n", (int)obj->status);
            return BCMOS_FALSE;
        }
    }
    switch (obj->status)
    {
    case BCMOLT_DDR_TEST_STATUS_COMPLETED:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.completed.presence_mask, BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID_CPU_RESULT))
        {
            switch (obj->u.completed.cpu_result)
            {
            case BCMOLT_DDR_TEST_RESULT_SUCCESS:
            case BCMOLT_DDR_TEST_RESULT_PHY_INIT_ERROR:
            case BCMOLT_DDR_TEST_RESULT_DRAM_INIT_ERROR:
            case BCMOLT_DDR_TEST_RESULT_SHMOO_ERROR:
            case BCMOLT_DDR_TEST_RESULT_EDIS_TEST_ERROR:
            case BCMOLT_DDR_TEST_RESULT_MEM_TEST_ERROR:
            case BCMOLT_DDR_TEST_RESULT_NOT_TESTED:
                break;
            default:
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "cpu_result: enum value %d is unexpected\n", (int)obj->u.completed.cpu_result);
                return BCMOS_FALSE;
            }
        }
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.completed.presence_mask, BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID_RAS_0_RESULT))
        {
            switch (obj->u.completed.ras_0_result)
            {
            case BCMOLT_DDR_TEST_RESULT_SUCCESS:
            case BCMOLT_DDR_TEST_RESULT_PHY_INIT_ERROR:
            case BCMOLT_DDR_TEST_RESULT_DRAM_INIT_ERROR:
            case BCMOLT_DDR_TEST_RESULT_SHMOO_ERROR:
            case BCMOLT_DDR_TEST_RESULT_EDIS_TEST_ERROR:
            case BCMOLT_DDR_TEST_RESULT_MEM_TEST_ERROR:
            case BCMOLT_DDR_TEST_RESULT_NOT_TESTED:
                break;
            default:
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "ras_0_result: enum value %d is unexpected\n", (int)obj->u.completed.ras_0_result);
                return BCMOS_FALSE;
            }
        }
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.completed.presence_mask, BCMOLT_DDR_TEST_COMPLETED_COMPLETED_ID_RAS_1_RESULT))
        {
            switch (obj->u.completed.ras_1_result)
            {
            case BCMOLT_DDR_TEST_RESULT_SUCCESS:
            case BCMOLT_DDR_TEST_RESULT_PHY_INIT_ERROR:
            case BCMOLT_DDR_TEST_RESULT_DRAM_INIT_ERROR:
            case BCMOLT_DDR_TEST_RESULT_SHMOO_ERROR:
            case BCMOLT_DDR_TEST_RESULT_EDIS_TEST_ERROR:
            case BCMOLT_DDR_TEST_RESULT_MEM_TEST_ERROR:
            case BCMOLT_DDR_TEST_RESULT_NOT_TESTED:
                break;
            default:
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "ras_1_result: enum value %d is unexpected\n", (int)obj->u.completed.ras_1_result);
                return BCMOS_FALSE;
            }
        }
        break;
    }
    case BCMOLT_DDR_TEST_STATUS_CONNECTION_FAILED:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.connection_failed.presence_mask, BCMOLT_DDR_TEST_COMPLETED_CONNECTION_FAILED_ID_REASON))
        {
            switch (obj->u.connection_failed.reason)
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
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "reason: enum value %d is unexpected\n", (int)obj->u.connection_failed.reason);
                return BCMOS_FALSE;
            }
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return BCMOS_TRUE;
}

void bcmolt_debug_device_cfg_set_default(bcmolt_debug_device_cfg *obj)
{
    obj->presence_mask = 0;
    obj->use_prev_pon_serdes_firmware = BCMOS_FALSE;
    obj->use_prev_nni_serdes_firmware = BCMOS_FALSE;
}

bcmos_bool bcmolt_debug_device_cfg_validate(const bcmolt_debug_device_cfg *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_DEBUG_DEVICE_CFG_ID_USE_PREV_PON_SERDES_FIRMWARE))
    {
        /* obj->use_prev_pon_serdes_firmware can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_DEBUG_DEVICE_CFG_ID_USE_PREV_NNI_SERDES_FIRMWARE))
    {
        /* obj->use_prev_nni_serdes_firmware can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_debug_flow_config_set_default(bcmolt_debug_flow_config *obj)
{
    obj->presence_mask = 0;
    obj->untagged_flow = BCMOLT_CONTROL_STATE_DISABLE;
    obj->untagged_vid = (bcmolt_vlan_id)0U;
}

bcmos_bool bcmolt_debug_flow_config_validate(const bcmolt_debug_flow_config *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_DEBUG_FLOW_CONFIG_ID_UNTAGGED_FLOW))
    {
        switch (obj->untagged_flow)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "untagged_flow: enum value %d is unexpected\n", (int)obj->untagged_flow);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_DEBUG_FLOW_CONFIG_ID_UNTAGGED_VID))
    {
        if (obj->untagged_vid > (bcmolt_vlan_id)4095U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "untagged_vid: %u is greater than the maximum value of 4095\n", obj->untagged_vid);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_sched_ref_set_default(bcmolt_tm_sched_ref *obj)
{
    obj->presence_mask = 0;
    obj->id = (bcmolt_tm_sched_id)65535U;
}

bcmos_bool bcmolt_tm_sched_ref_validate(const bcmolt_tm_sched_ref *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TM_SCHED_REF_ID_ID))
    {
        /* obj->id can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_egress_qos_set_default(bcmolt_egress_qos *obj)
{
    obj->presence_mask = 0;
    obj->type = BCMOLT_EGRESS_QOS_TYPE_NONE;
    bcmolt_tm_sched_ref_set_default(&obj->tm_sched);
    obj->u.none.presence_mask = 0;
}

void bcmolt_egress_qos_set_union_default(bcmolt_egress_qos *obj, bcmolt_egress_qos_type type)
{
    obj->type = type;
    switch (type)
    {
    case BCMOLT_EGRESS_QOS_TYPE_FIXED_QUEUE:
        obj->u.fixed_queue.presence_mask = 0;
        obj->u.fixed_queue.queue_id = (bcmolt_tm_queue_id)65535U;
        break;
    case BCMOLT_EGRESS_QOS_TYPE_TC_TO_QUEUE:
        obj->u.tc_to_queue.presence_mask = 0;
        obj->u.tc_to_queue.tc_id = 0;
        obj->u.tc_to_queue.tc_to_queue_id = 0U;
        break;
    case BCMOLT_EGRESS_QOS_TYPE_PBIT_TO_TC:
        obj->u.pbit_to_tc.presence_mask = 0;
        obj->u.pbit_to_tc.pbit_to_tc_id = 0U;
        obj->u.pbit_to_tc.tc_to_queue_id = 0U;
        break;
    case BCMOLT_EGRESS_QOS_TYPE_PRIORITY_TO_QUEUE:
        obj->u.priority_to_queue.presence_mask = 0;
        obj->u.priority_to_queue.tm_qmp_id = (bcmolt_tm_qmp_id)255;
        obj->u.priority_to_queue.tm_q_set_id = (bcmolt_tm_queue_set_id)32768U;
        break;
    case BCMOLT_EGRESS_QOS_TYPE_NONE:
        obj->u.none.presence_mask = 0;
        break;
    default:
        break;
    }
}

bcmos_bool bcmolt_egress_qos_validate(const bcmolt_egress_qos *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_EGRESS_QOS_ID_TYPE))
    {
        switch (obj->type)
        {
        case BCMOLT_EGRESS_QOS_TYPE_FIXED_QUEUE:
        case BCMOLT_EGRESS_QOS_TYPE_TC_TO_QUEUE:
        case BCMOLT_EGRESS_QOS_TYPE_PBIT_TO_TC:
        case BCMOLT_EGRESS_QOS_TYPE_NONE:
        case BCMOLT_EGRESS_QOS_TYPE_PRIORITY_TO_QUEUE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "type: enum value %d is unexpected\n", (int)obj->type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_EGRESS_QOS_ID_TM_SCHED))
    {
        int prefix_len = bcmolt_string_append(err_details, "tm_sched.");
        if (!bcmolt_tm_sched_ref_validate(&obj->tm_sched, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    switch (obj->type)
    {
    case BCMOLT_EGRESS_QOS_TYPE_FIXED_QUEUE:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.fixed_queue.presence_mask, BCMOLT_EGRESS_QOS_FIXED_QUEUE_ID_QUEUE_ID))
        {
            /* obj->u.fixed_queue.queue_id can't be invalid. */
        }
        break;
    }
    case BCMOLT_EGRESS_QOS_TYPE_TC_TO_QUEUE:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.tc_to_queue.presence_mask, BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID_TC_ID))
        {
            if (obj->u.tc_to_queue.tc_id > 7)
            {
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "tc_id: %u is greater than the maximum value of 7\n", obj->u.tc_to_queue.tc_id);
                return BCMOS_FALSE;
            }
        }
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.tc_to_queue.presence_mask, BCMOLT_EGRESS_QOS_TC_TO_QUEUE_ID_TC_TO_QUEUE_ID))
        {
            /* obj->u.tc_to_queue.tc_to_queue_id can't be invalid. */
        }
        break;
    }
    case BCMOLT_EGRESS_QOS_TYPE_PBIT_TO_TC:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.pbit_to_tc.presence_mask, BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID_PBIT_TO_TC_ID))
        {
            /* obj->u.pbit_to_tc.pbit_to_tc_id can't be invalid. */
        }
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.pbit_to_tc.presence_mask, BCMOLT_EGRESS_QOS_PBIT_TO_TC_ID_TC_TO_QUEUE_ID))
        {
            /* obj->u.pbit_to_tc.tc_to_queue_id can't be invalid. */
        }
        break;
    }
    case BCMOLT_EGRESS_QOS_TYPE_PRIORITY_TO_QUEUE:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.priority_to_queue.presence_mask, BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID_TM_QMP_ID))
        {
            if (obj->u.priority_to_queue.tm_qmp_id > (bcmolt_tm_qmp_id)15)
            {
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "tm_qmp_id: %u is greater than the maximum value of 15\n", obj->u.priority_to_queue.tm_qmp_id);
                return BCMOS_FALSE;
            }
        }
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.priority_to_queue.presence_mask, BCMOLT_EGRESS_QOS_PRIORITY_TO_QUEUE_ID_TM_Q_SET_ID))
        {
            /* obj->u.priority_to_queue.tm_q_set_id can't be invalid. */
        }
        break;
    }
    case BCMOLT_EGRESS_QOS_TYPE_NONE:
    {
        break;
    }
    default:
    {
        break;
    }
    }
    return BCMOS_TRUE;
}

void bcmolt_str_64_set_default(bcmolt_str_64 *obj)
{
    memset(obj->str, 0, 64);
}

bcmos_bool bcmolt_str_64_validate(const bcmolt_str_64 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->str can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_embedded_image_entry_set_default(bcmolt_embedded_image_entry *obj)
{
    obj->presence_mask = 0;
    obj->image_type = BCMOLT_DEVICE_IMAGE_TYPE_BOOTLOADER;
    obj->image_size = 0UL;
    obj->crc32 = 0x0UL;
    obj->status = BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS_NONE;
    bcmolt_str_64_set_default(&obj->image_name);
}

bcmos_bool bcmolt_embedded_image_entry_validate(const bcmolt_embedded_image_entry *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_IMAGE_TYPE))
    {
        switch (obj->image_type)
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
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "image_type: enum value %d is unexpected\n", (int)obj->image_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_IMAGE_SIZE))
    {
        /* obj->image_size can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_CRC32))
    {
        /* obj->crc32 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_STATUS))
    {
        switch (obj->status)
        {
        case BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS_NONE:
        case BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS_IN_PROGRESS:
        case BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS_SUCCESS:
        case BCMOLT_EMBEDDED_IMAGE_TRANSFER_STATUS_FAILURE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "status: enum value %d is unexpected\n", (int)obj->status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_EMBEDDED_IMAGE_ENTRY_ID_IMAGE_NAME))
    {
        int prefix_len = bcmolt_string_append(err_details, "image_name.");
        if (!bcmolt_str_64_validate(&obj->image_name, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_embedded_image_entry_list_u8_max_4_set_default(bcmolt_embedded_image_entry_list_u8_max_4 *obj)
{
    obj->len = 0;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_embedded_image_entry_list_u8_max_4_validate(const bcmolt_embedded_image_entry_list_u8_max_4 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (obj->len > 4)
    {
        *err = BCM_ERR_RANGE;
        bcmolt_string_append(err_details, "len: %u is greater than the maximum array length of 4\n", obj->len);
        return BCMOS_FALSE;
    }
    for (uint32_t i = 0; i < obj->len; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_embedded_image_entry_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_erps_intf_ref_set_default(bcmolt_erps_intf_ref *obj)
{
    obj->presence_mask = 0;
    obj->intf_id = (bcmolt_interface_id)65535U;
    obj->intf_type = BCMOLT_INTERFACE_TYPE_UNASSIGNED;
    obj->port_type = (bcmolt_erps_port)0;
    obj->intf_opt = (bcmolt_intf_opt)0U;
    obj->sub_port_idx = 255;
}

bcmos_bool bcmolt_erps_intf_ref_validate(const bcmolt_erps_intf_ref *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ERPS_INTF_REF_ID_INTF_ID))
    {
        /* obj->intf_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ERPS_INTF_REF_ID_INTF_TYPE))
    {
        switch (obj->intf_type)
        {
        case BCMOLT_INTERFACE_TYPE_PON:
        case BCMOLT_INTERFACE_TYPE_NNI:
        case BCMOLT_INTERFACE_TYPE_HOST:
        case BCMOLT_INTERFACE_TYPE_ERPS:
        case BCMOLT_INTERFACE_TYPE_LAG:
        case BCMOLT_INTERFACE_TYPE_PROTECTION:
        case BCMOLT_INTERFACE_TYPE_UNASSIGNED:
        case BCMOLT_INTERFACE_TYPE_REMOTE_PON:
        case BCMOLT_INTERFACE_TYPE_NIC:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "intf_type: enum value %d is unexpected\n", (int)obj->intf_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ERPS_INTF_REF_ID_PORT_TYPE))
    {
        switch (obj->port_type)
        {
        case BCMOLT_ERPS_PORT_WEST_PORT:
        case BCMOLT_ERPS_PORT_SUB_PORT:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "port_type: enum value %d is unexpected\n", (int)obj->port_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ERPS_INTF_REF_ID_INTF_OPT))
    {
        if ((obj->intf_opt & ~0x1) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "intf_opt: 0x%X includes invalid bits\n", obj->intf_opt);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ERPS_INTF_REF_ID_SUB_PORT_IDX))
    {
        /* obj->sub_port_idx can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_extended_dba_priority_adjustment_set_default(bcmolt_extended_dba_priority_adjustment *obj)
{
    obj->presence_mask = 0;
    obj->control = BCMOLT_CONTROL_STATE_DISABLE;
    bcmolt_arr_u8_20_set_default(&obj->slots);
}

bcmos_bool bcmolt_extended_dba_priority_adjustment_validate(const bcmolt_extended_dba_priority_adjustment *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID_CONTROL))
    {
        switch (obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "control: enum value %d is unexpected\n", (int)obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_EXTENDED_DBA_PRIORITY_ADJUSTMENT_ID_SLOTS))
    {
        int prefix_len = bcmolt_string_append(err_details, "slots.");
        if (!bcmolt_arr_u8_20_validate(&obj->slots, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_str_32_set_default(bcmolt_str_32 *obj)
{
    memset(obj->str, 0, 32);
}

bcmos_bool bcmolt_str_32_validate(const bcmolt_str_32 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->str can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_firmware_sw_version_set_default(bcmolt_firmware_sw_version *obj)
{
    obj->presence_mask = 0;
    obj->major = 0;
    obj->minor = 0;
    obj->revision = 0;
    obj->model = 0UL;
    bcmolt_str_32_set_default(&obj->build_time);
}

bcmos_bool bcmolt_firmware_sw_version_validate(const bcmolt_firmware_sw_version *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_FIRMWARE_SW_VERSION_ID_MAJOR))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "major: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_FIRMWARE_SW_VERSION_ID_MINOR))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "minor: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_FIRMWARE_SW_VERSION_ID_REVISION))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "revision: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_FIRMWARE_SW_VERSION_ID_MODEL))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "model: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_FIRMWARE_SW_VERSION_ID_BUILD_TIME))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "build_time: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_gem_port_configuration_set_default(bcmolt_gem_port_configuration *obj)
{
    obj->presence_mask = 0;
    obj->direction = BCMOLT_GEM_PORT_DIRECTION_DOWNSTREAM;
    obj->type = BCMOLT_GEM_PORT_TYPE_UNICAST;
}

bcmos_bool bcmolt_gem_port_configuration_validate(const bcmolt_gem_port_configuration *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GEM_PORT_CONFIGURATION_ID_DIRECTION))
    {
        switch (obj->direction)
        {
        case BCMOLT_GEM_PORT_DIRECTION_DOWNSTREAM:
        case BCMOLT_GEM_PORT_DIRECTION_UPSTREAM:
        case BCMOLT_GEM_PORT_DIRECTION_BIDIRECTIONAL:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "direction: enum value %d is unexpected\n", (int)obj->direction);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GEM_PORT_CONFIGURATION_ID_TYPE))
    {
        switch (obj->type)
        {
        case BCMOLT_GEM_PORT_TYPE_UNICAST:
        case BCMOLT_GEM_PORT_TYPE_MULTICAST:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "type: enum value %d is unexpected\n", (int)obj->type);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_gem_port_id_list_u8_max_16_set_default(bcmolt_gem_port_id_list_u8_max_16 *obj)
{
    obj->len = 0;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_gem_port_id_list_u8_max_16_validate(const bcmolt_gem_port_id_list_u8_max_16 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (obj->len > 16)
    {
        *err = BCM_ERR_RANGE;
        bcmolt_string_append(err_details, "len: %u is greater than the maximum array length of 16\n", obj->len);
        return BCMOS_FALSE;
    }
    for (uint32_t i = 0; i < obj->len; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
        }
    }
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_gpon_onu_alarm_state_set_default(bcmolt_gpon_onu_alarm_state *obj)
{
    obj->presence_mask = 0;
    obj->losi = BCMOLT_STATUS_OFF;
    obj->lofi = BCMOLT_STATUS_OFF;
    obj->loami = BCMOLT_STATUS_OFF;
    obj->dgi = BCMOLT_STATUS_OFF;
    obj->tiwi = BCMOLT_STATUS_OFF;
    obj->dowi = BCMOLT_STATUS_OFF;
    obj->sufi = BCMOLT_STATUS_OFF;
    obj->sfi = BCMOLT_STATUS_OFF;
    obj->sdi = BCMOLT_STATUS_OFF;
    obj->dfi = BCMOLT_STATUS_OFF;
    obj->loai = BCMOLT_STATUS_OFF;
    obj->loki = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_gpon_onu_alarm_state_validate(const bcmolt_gpon_onu_alarm_state *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_LOSI))
    {
        switch (obj->losi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "losi: enum value %d is unexpected\n", (int)obj->losi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_LOFI))
    {
        switch (obj->lofi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lofi: enum value %d is unexpected\n", (int)obj->lofi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_LOAMI))
    {
        switch (obj->loami)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loami: enum value %d is unexpected\n", (int)obj->loami);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_DGI))
    {
        switch (obj->dgi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "dgi: enum value %d is unexpected\n", (int)obj->dgi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_TIWI))
    {
        switch (obj->tiwi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tiwi: enum value %d is unexpected\n", (int)obj->tiwi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_DOWI))
    {
        switch (obj->dowi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "dowi: enum value %d is unexpected\n", (int)obj->dowi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_SUFI))
    {
        switch (obj->sufi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sufi: enum value %d is unexpected\n", (int)obj->sufi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_SFI))
    {
        switch (obj->sfi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sfi: enum value %d is unexpected\n", (int)obj->sfi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_SDI))
    {
        switch (obj->sdi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sdi: enum value %d is unexpected\n", (int)obj->sdi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_DFI))
    {
        switch (obj->dfi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "dfi: enum value %d is unexpected\n", (int)obj->dfi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_LOAI))
    {
        switch (obj->loai)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loai: enum value %d is unexpected\n", (int)obj->loai);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARM_STATE_ID_LOKI))
    {
        switch (obj->loki)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loki: enum value %d is unexpected\n", (int)obj->loki);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_gpon_onu_alarms_set_default(bcmolt_gpon_onu_alarms *obj)
{
    obj->presence_mask = 0;
    obj->losi = BCMOLT_STATUS_OFF;
    obj->lofi = BCMOLT_STATUS_OFF;
    obj->loami = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_gpon_onu_alarms_validate(const bcmolt_gpon_onu_alarms *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARMS_ID_LOSI))
    {
        switch (obj->losi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "losi: enum value %d is unexpected\n", (int)obj->losi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARMS_ID_LOFI))
    {
        switch (obj->lofi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lofi: enum value %d is unexpected\n", (int)obj->lofi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARMS_ID_LOAMI))
    {
        switch (obj->loami)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loami: enum value %d is unexpected\n", (int)obj->loami);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_gpon_onu_alarms_thresholds_set_default(bcmolt_gpon_onu_alarms_thresholds *obj)
{
    obj->presence_mask = 0;
    obj->losi = 4;
    obj->lofi = 4;
    obj->loami = 3;
}

bcmos_bool bcmolt_gpon_onu_alarms_thresholds_validate(const bcmolt_gpon_onu_alarms_thresholds *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID_LOSI))
    {
        if (obj->losi < 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "losi: %u is less than the minimum value of 1\n", obj->losi);
            return BCMOS_FALSE;
        }
        if (obj->losi > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "losi: %u is greater than the maximum value of 15\n", obj->losi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID_LOFI))
    {
        if (obj->lofi < 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lofi: %u is less than the minimum value of 1\n", obj->lofi);
            return BCMOS_FALSE;
        }
        if (obj->lofi > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lofi: %u is greater than the maximum value of 15\n", obj->lofi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_ALARMS_THRESHOLDS_ID_LOAMI))
    {
        if (obj->loami < 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loami: %u is less than the minimum value of 1\n", obj->loami);
            return BCMOS_FALSE;
        }
        if (obj->loami > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loami: %u is greater than the maximum value of 15\n", obj->loami);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_gpon_onu_params_set_default(bcmolt_gpon_onu_params *obj)
{
    obj->presence_mask = 0;
    bcmolt_bin_str_10_set_default(&obj->password);
    obj->us_fec = BCMOS_FALSE;
    obj->omci_port_id = (bcmolt_gem_port_id)65535UL;
    obj->ds_ber_reporting_interval = (bcmolt_ber_interval)0UL;
    bcmolt_gpon_onu_alarm_state_set_default(&obj->alarm_state);
}

bcmos_bool bcmolt_gpon_onu_params_validate(const bcmolt_gpon_onu_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_PARAMS_ID_PASSWORD))
    {
        int prefix_len = bcmolt_string_append(err_details, "password.");
        if (!bcmolt_bin_str_10_validate(&obj->password, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_PARAMS_ID_US_FEC))
    {
        /* obj->us_fec can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_PARAMS_ID_OMCI_PORT_ID))
    {
        if (obj->omci_port_id > (bcmolt_gem_port_id)65536UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "omci_port_id: %u is greater than the maximum value of 65536\n", obj->omci_port_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_PARAMS_ID_DS_BER_REPORTING_INTERVAL))
    {
        if (obj->ds_ber_reporting_interval > (bcmolt_ber_interval)536870911UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ds_ber_reporting_interval: %u is greater than the maximum value of 536870911\n", obj->ds_ber_reporting_interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_ONU_PARAMS_ID_ALARM_STATE))
    {
        int prefix_len = bcmolt_string_append(err_details, "alarm_state.");
        if (!bcmolt_gpon_onu_alarm_state_validate(&obj->alarm_state, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_power_level_set_default(bcmolt_pon_power_level *obj)
{
    obj->presence_mask = 0;
    obj->pls_maximum_allocation_size = 120UL;
    obj->mode = 0;
}

bcmos_bool bcmolt_pon_power_level_validate(const bcmolt_pon_power_level *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_POWER_LEVEL_ID_PLS_MAXIMUM_ALLOCATION_SIZE))
    {
        /* obj->pls_maximum_allocation_size can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_POWER_LEVEL_ID_MODE))
    {
        /* obj->mode can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_gpon_pon_params_set_default(bcmolt_gpon_pon_params *obj)
{
    obj->presence_mask = 0;
    bcmolt_gpon_onu_alarms_thresholds_set_default(&obj->onu_alarms_thresholds);
    obj->preassigned_equalization_delay = 0UL;
    bcmolt_pon_power_level_set_default(&obj->power_level);
    obj->bip32_indication_control = BCMOLT_CONTROL_STATE_ENABLE;
    obj->ds_ber_reporting_interval = (bcmolt_ber_interval)5000UL;
    obj->sr_reporting_block_size = 48;
}

bcmos_bool bcmolt_gpon_pon_params_validate(const bcmolt_gpon_pon_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_PON_PARAMS_ID_ONU_ALARMS_THRESHOLDS))
    {
        int prefix_len = bcmolt_string_append(err_details, "onu_alarms_thresholds.");
        if (!bcmolt_gpon_onu_alarms_thresholds_validate(&obj->onu_alarms_thresholds, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_PON_PARAMS_ID_PREASSIGNED_EQUALIZATION_DELAY))
    {
        if (obj->preassigned_equalization_delay > 16776960UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "preassigned_equalization_delay: %u is greater than the maximum value of 16776960\n", obj->preassigned_equalization_delay);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_PON_PARAMS_ID_POWER_LEVEL))
    {
        int prefix_len = bcmolt_string_append(err_details, "power_level.");
        if (!bcmolt_pon_power_level_validate(&obj->power_level, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_PON_PARAMS_ID_BIP32_INDICATION_CONTROL))
    {
        switch (obj->bip32_indication_control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "bip32_indication_control: enum value %d is unexpected\n", (int)obj->bip32_indication_control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_PON_PARAMS_ID_DS_BER_REPORTING_INTERVAL))
    {
        if (obj->ds_ber_reporting_interval > (bcmolt_ber_interval)536870911UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ds_ber_reporting_interval: %u is greater than the maximum value of 536870911\n", obj->ds_ber_reporting_interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_PON_PARAMS_ID_SR_REPORTING_BLOCK_SIZE))
    {
        /* obj->sr_reporting_block_size can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_str_100_set_default(bcmolt_str_100 *obj)
{
    memset(obj->str, 0, 100);
}

bcmos_bool bcmolt_str_100_validate(const bcmolt_str_100 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->str can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_gpon_trx_set_default(bcmolt_gpon_trx *obj)
{
    obj->presence_mask = 0;
    obj->transceiver_type = BCMOLT_TRX_TYPE_LTE_3680_M;
    bcmolt_str_100_set_default(&obj->trx_name);
}

bcmos_bool bcmolt_gpon_trx_validate(const bcmolt_gpon_trx *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_TRX_ID_TRANSCEIVER_TYPE))
    {
        switch (obj->transceiver_type)
        {
        case BCMOLT_TRX_TYPE_SPS_43_48_H_HP_CDE_SD_2013:
        case BCMOLT_TRX_TYPE_SOG_4321_PSGB:
        case BCMOLT_TRX_TYPE_LTE_3680_M:
        case BCMOLT_TRX_TYPE_SOURCE_PHOTONICS:
        case BCMOLT_TRX_TYPE_LTE_3680_P_TYPE_C_PLUS:
        case BCMOLT_TRX_TYPE_ANY:
        case BCMOLT_TRX_TYPE_WTD_RTXM_167_526_CPLUS:
        case BCMOLT_TRX_TYPE_WTD_RTXM_167_522_BPLUS:
        case BCMOLT_TRX_TYPE_LTE_3680_P_BC:
        case BCMOLT_TRX_TYPE_SOGQ_4321_PSGB_C_PLUS:
        case BCMOLT_TRX_TYPE_WTD_RTXM167_521:
        case BCMOLT_TRX_TYPE_LTE3678:
        case BCMOLT_TRX_TYPE_LTH_5308:
        case BCMOLT_TRX_TYPE_LTF_5308:
        case BCMOLT_TRX_TYPE_LTF_5308_E:
        case BCMOLT_TRX_TYPE_LTF_5306:
        case BCMOLT_TRX_TYPE_LTF_5308_B:
        case BCMOLT_TRX_TYPE_SDDS_ST_XS_CP_CDFA:
        case BCMOLT_TRX_TYPE_COMBO_GENERAL_1:
        case BCMOLT_TRX_TYPE_COMBO_GENERAL_2:
        case BCMOLT_TRX_TYPE_COMBO_GENERAL_3:
        case BCMOLT_TRX_TYPE_COMBO_GENERAL_4:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "transceiver_type: enum value %d is unexpected\n", (int)obj->transceiver_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GPON_TRX_ID_TRX_NAME))
    {
        int prefix_len = bcmolt_string_append(err_details, "trx_name.");
        if (!bcmolt_str_100_validate(&obj->trx_name, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_group_member_info_set_default(bcmolt_group_member_info *obj)
{
    obj->presence_mask = 0;
    bcmolt_intf_ref_set_default(&obj->intf);
    obj->svc_port_id = (bcmolt_service_port_id)0UL;
    bcmolt_egress_qos_set_default(&obj->egress_qos);
}

bcmos_bool bcmolt_group_member_info_validate(const bcmolt_group_member_info *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GROUP_MEMBER_INFO_ID_INTF))
    {
        int prefix_len = bcmolt_string_append(err_details, "intf.");
        if (!bcmolt_intf_ref_validate(&obj->intf, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GROUP_MEMBER_INFO_ID_SVC_PORT_ID))
    {
        if (obj->svc_port_id > (bcmolt_service_port_id)65536UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "svc_port_id: %u is greater than the maximum value of 65536\n", obj->svc_port_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GROUP_MEMBER_INFO_ID_EGRESS_QOS))
    {
        int prefix_len = bcmolt_string_append(err_details, "egress_qos.");
        if (!bcmolt_egress_qos_validate(&obj->egress_qos, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_group_member_info_list_u8_set_default(bcmolt_group_member_info_list_u8 *obj)
{
    obj->len = 0;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_group_member_info_list_u8_validate(const bcmolt_group_member_info_list_u8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->len can't be invalid. */
    for (uint32_t i = 0; i < obj->len; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_group_member_info_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_group_members_update_command_set_default(bcmolt_group_members_update_command *obj)
{
    obj->presence_mask = 0;
    obj->command = BCMOLT_MEMBERS_UPDATE_COMMAND_ADD;
    bcmolt_group_member_info_list_u8_set_default(&obj->members);
}

bcmos_bool bcmolt_group_members_update_command_validate(const bcmolt_group_members_update_command *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID_COMMAND))
    {
        switch (obj->command)
        {
        case BCMOLT_MEMBERS_UPDATE_COMMAND_ADD:
        case BCMOLT_MEMBERS_UPDATE_COMMAND_REMOVE:
        case BCMOLT_MEMBERS_UPDATE_COMMAND_SET:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "command: enum value %d is unexpected\n", (int)obj->command);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_GROUP_MEMBERS_UPDATE_COMMAND_ID_MEMBERS))
    {
        int prefix_len = bcmolt_string_append(err_details, "members.");
        if (!bcmolt_group_member_info_list_u8_validate(&obj->members, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_host_port_params_set_default(bcmolt_host_port_params *obj)
{
    obj->presence_mask = 0;
    obj->pir_kbps = 200000UL;
    obj->queue_size_kbytes = 1000U;
}

bcmos_bool bcmolt_host_port_params_validate(const bcmolt_host_port_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_HOST_PORT_PARAMS_ID_PIR_KBPS))
    {
        if (obj->pir_kbps < 100UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "pir_kbps: %u is less than the minimum value of 100\n", obj->pir_kbps);
            return BCMOS_FALSE;
        }
        if (obj->pir_kbps > 10000000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "pir_kbps: %u is greater than the maximum value of 10000000\n", obj->pir_kbps);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_HOST_PORT_PARAMS_ID_QUEUE_SIZE_KBYTES))
    {
        if (obj->queue_size_kbytes < 10U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "queue_size_kbytes: %u is less than the minimum value of 10\n", obj->queue_size_kbytes);
            return BCMOS_FALSE;
        }
        if (obj->queue_size_kbytes > 10000U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "queue_size_kbytes: %u is greater than the maximum value of 10000\n", obj->queue_size_kbytes);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_host_sw_version_set_default(bcmolt_host_sw_version *obj)
{
    obj->presence_mask = 0;
    obj->major = 0;
    obj->minor = 0;
    obj->revision = 0;
    obj->model = 0U;
    bcmolt_str_64_set_default(&obj->build_time);
}

bcmos_bool bcmolt_host_sw_version_validate(const bcmolt_host_sw_version *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_HOST_SW_VERSION_ID_MAJOR))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "major: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_HOST_SW_VERSION_ID_MINOR))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "minor: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_HOST_SW_VERSION_ID_REVISION))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "revision: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_HOST_SW_VERSION_ID_MODEL))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "model: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_HOST_SW_VERSION_ID_BUILD_TIME))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "build_time: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_hw_pon_id_set_default(bcmolt_hw_pon_id *obj)
{
    obj->presence_mask = 0;
    obj->pon_id_1 = 0UL;
    obj->pon_id_2 = 0UL;
}

bcmos_bool bcmolt_hw_pon_id_validate(const bcmolt_hw_pon_id *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_HW_PON_ID_ID_PON_ID_1))
    {
        /* obj->pon_id_1 can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_HW_PON_ID_ID_PON_ID_2))
    {
        /* obj->pon_id_2 can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_str_256_set_default(bcmolt_str_256 *obj)
{
    memset(obj->str, 0, 256);
}

bcmos_bool bcmolt_str_256_validate(const bcmolt_str_256 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->str can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_ieee_8021_as_tod_set_default(bcmolt_ieee_8021_as_tod *obj)
{
    obj->presence_mask = 0;
    bcmolt_str_256_set_default(&obj->tod_format);
    obj->clock_transport_sample_delay = 0UL;
    obj->tod_read_delay_ms = 0UL;
}

bcmos_bool bcmolt_ieee_8021_as_tod_validate(const bcmolt_ieee_8021_as_tod *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_IEEE_8021_AS_TOD_ID_TOD_FORMAT))
    {
        int prefix_len = bcmolt_string_append(err_details, "tod_format.");
        if (!bcmolt_str_256_validate(&obj->tod_format, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_IEEE_8021_AS_TOD_ID_CLOCK_TRANSPORT_SAMPLE_DELAY))
    {
        /* obj->clock_transport_sample_delay can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_IEEE_8021_AS_TOD_ID_TOD_READ_DELAY_MS))
    {
        if (obj->tod_read_delay_ms > 1000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tod_read_delay_ms: %u is greater than the maximum value of 1000\n", obj->tod_read_delay_ms);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_inband_config_data_set_default(bcmolt_inband_config_data *obj)
{
    obj->presence_mask = 0;
    obj->control = BCMOLT_CONTROL_STATE_DISABLE;
    bcmos_ipv4_address_init(&obj->ip_address);
    obj->udp_port = 0U;
    bcmos_ipv4_address_init(&obj->net_mask);
    bcmos_ipv4_address_init(&obj->gw_address);
    obj->vlan_tag = 0x81000001UL;
}

bcmos_bool bcmolt_inband_config_data_validate(const bcmolt_inband_config_data *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INBAND_CONFIG_DATA_ID_CONTROL))
    {
        switch (obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "control: enum value %d is unexpected\n", (int)obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INBAND_CONFIG_DATA_ID_IP_ADDRESS))
    {
        /* obj->ip_address can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INBAND_CONFIG_DATA_ID_UDP_PORT))
    {
        /* obj->udp_port can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INBAND_CONFIG_DATA_ID_NET_MASK))
    {
        /* obj->net_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INBAND_CONFIG_DATA_ID_GW_ADDRESS))
    {
        /* obj->gw_address can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INBAND_CONFIG_DATA_ID_VLAN_TAG))
    {
        /* obj->vlan_tag can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_inband_conn_data_set_default(bcmolt_inband_conn_data *obj)
{
    obj->presence_mask = 0;
    bcmos_ipv4_address_init(&obj->device_ip_address);
    obj->device_udp_port = 0U;
}

bcmos_bool bcmolt_inband_conn_data_validate(const bcmolt_inband_conn_data *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INBAND_CONN_DATA_ID_DEVICE_IP_ADDRESS))
    {
        /* obj->device_ip_address can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INBAND_CONN_DATA_ID_DEVICE_UDP_PORT))
    {
        /* obj->device_udp_port can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_indication_shaping_set_default(bcmolt_indication_shaping *obj)
{
    obj->presence_mask = 0;
    obj->enabled = BCMOS_FALSE;
    obj->max_rate = 1000UL;
    obj->max_burst = 100UL;
}

bcmos_bool bcmolt_indication_shaping_validate(const bcmolt_indication_shaping *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INDICATION_SHAPING_ID_ENABLED))
    {
        /* obj->enabled can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INDICATION_SHAPING_ID_MAX_RATE))
    {
        if (obj->max_rate < 1UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "max_rate: %u is less than the minimum value of 1\n", obj->max_rate);
            return BCMOS_FALSE;
        }
        if (obj->max_rate > 10000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "max_rate: %u is greater than the maximum value of 10000\n", obj->max_rate);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INDICATION_SHAPING_ID_MAX_BURST))
    {
        if (obj->max_burst < 1UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "max_burst: %u is less than the minimum value of 1\n", obj->max_burst);
            return BCMOS_FALSE;
        }
        if (obj->max_burst > 10000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "max_burst: %u is greater than the maximum value of 10000\n", obj->max_burst);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_inni_config_set_default(bcmolt_inni_config *obj)
{
    obj->presence_mask = 0;
    obj->mode = BCMOLT_INNI_MODE_ALL_1_G;
    obj->mux = BCMOLT_INNI_MUX_NONE;
    obj->cl73_an = BCMOLT_CONTROL_STATE_DISABLE;
    obj->link_training = BCMOLT_CONTROL_STATE_DISABLE;
    obj->inni_fec = BCMOLT_INNI_FEC_MODES_NONE;
    obj->available_lanes = BCMOLT_INNI_LANES_ALL;
    obj->ps_gpio = BCMOLT_GPIO_PIN_UNCONFIGURED;
    obj->gpio_polarity = BCMOLT_GPIO_POLARITY_ACTIVE_LOW;
}

bcmos_bool bcmolt_inni_config_validate(const bcmolt_inni_config *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INNI_CONFIG_ID_MODE))
    {
        switch (obj->mode)
        {
        case BCMOLT_INNI_MODE_ALL_1_G:
        case BCMOLT_INNI_MODE_ALL_2_P_5_G:
        case BCMOLT_INNI_MODE_ALL_10_G_XFI:
        case BCMOLT_INNI_MODE_ALL_10_G_KR:
        case BCMOLT_INNI_MODE_ALL_10_G_SFI:
        case BCMOLT_INNI_MODE_ALL_12_P_5_G:
        case BCMOLT_INNI_MODE_ALL_25_G_XFI:
        case BCMOLT_INNI_MODE_ALL_25_G_KR:
        case BCMOLT_INNI_MODE_ALL_25_G_CR:
        case BCMOLT_INNI_MODE_HALF_10_G_HALF_2_P_5_G:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "mode: enum value %d is unexpected\n", (int)obj->mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INNI_CONFIG_ID_MUX))
    {
        switch (obj->mux)
        {
        case BCMOLT_INNI_MUX_NONE:
        case BCMOLT_INNI_MUX_FOUR_TO_ONE:
        case BCMOLT_INNI_MUX_TWO_TO_ONE:
        case BCMOLT_INNI_MUX_FOUR_TO_ONE_IN_VLAN:
        case BCMOLT_INNI_MUX_TWO_TO_ONE_IN_VLAN:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "mux: enum value %d is unexpected\n", (int)obj->mux);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INNI_CONFIG_ID_CL73_AN))
    {
        switch (obj->cl73_an)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "cl73_an: enum value %d is unexpected\n", (int)obj->cl73_an);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INNI_CONFIG_ID_LINK_TRAINING))
    {
        switch (obj->link_training)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "link_training: enum value %d is unexpected\n", (int)obj->link_training);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INNI_CONFIG_ID_INNI_FEC))
    {
        switch (obj->inni_fec)
        {
        case BCMOLT_INNI_FEC_MODES_NONE:
        case BCMOLT_INNI_FEC_MODES_RS_FEC:
        case BCMOLT_INNI_FEC_MODES_FC_FEC:
        case BCMOLT_INNI_FEC_MODES_AUTO_NEGOTIATE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "inni_fec: enum value %d is unexpected\n", (int)obj->inni_fec);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INNI_CONFIG_ID_AVAILABLE_LANES))
    {
        switch (obj->available_lanes)
        {
        case BCMOLT_INNI_LANES_ALL:
        case BCMOLT_INNI_LANES_EVEN:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "available_lanes: enum value %d is unexpected\n", (int)obj->available_lanes);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INNI_CONFIG_ID_PS_GPIO))
    {
        switch (obj->ps_gpio)
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
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ps_gpio: enum value %d is unexpected\n", (int)obj->ps_gpio);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_INNI_CONFIG_ID_GPIO_POLARITY))
    {
        switch (obj->gpio_polarity)
        {
        case BCMOLT_GPIO_POLARITY_ACTIVE_LOW:
        case BCMOLT_GPIO_POLARITY_ACTIVE_HIGH:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "gpio_polarity: enum value %d is unexpected\n", (int)obj->gpio_polarity);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_intf_ref_list_u8_set_default(bcmolt_intf_ref_list_u8 *obj)
{
    obj->len = 0;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_intf_ref_list_u8_validate(const bcmolt_intf_ref_list_u8 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->len can't be invalid. */
    for (uint32_t i = 0; i < obj->len; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_intf_ref_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_serial_number_set_default(bcmolt_serial_number *obj)
{
    obj->presence_mask = 0;
    bcmolt_bin_str_4_set_default(&obj->vendor_id);
    bcmolt_bin_str_4_set_default(&obj->vendor_specific);
}

bcmos_bool bcmolt_serial_number_validate(const bcmolt_serial_number *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SERIAL_NUMBER_ID_VENDOR_ID))
    {
        int prefix_len = bcmolt_string_append(err_details, "vendor_id.");
        if (!bcmolt_bin_str_4_validate(&obj->vendor_id, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SERIAL_NUMBER_ID_VENDOR_SPECIFIC))
    {
        int prefix_len = bcmolt_string_append(err_details, "vendor_specific.");
        if (!bcmolt_bin_str_4_validate(&obj->vendor_specific, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_onu_aes_key_set_default(bcmolt_itupon_onu_aes_key *obj)
{
    obj->presence_mask = 0;
    bcmolt_aes_key_set_default(&obj->encryption_key);
    obj->key_index = 0;
}

bcmos_bool bcmolt_itupon_onu_aes_key_validate(const bcmolt_itupon_onu_aes_key *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_ONU_AES_KEY_ID_ENCRYPTION_KEY))
    {
        int prefix_len = bcmolt_string_append(err_details, "encryption_key.");
        if (!bcmolt_aes_key_validate(&obj->encryption_key, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_ONU_AES_KEY_ID_KEY_INDEX))
    {
        /* obj->key_index can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_xgpon_onu_alarm_state_set_default(bcmolt_xgpon_onu_alarm_state *obj)
{
    obj->presence_mask = 0;
    obj->losi = BCMOLT_STATUS_OFF;
    obj->lobi = BCMOLT_STATUS_OFF;
    obj->lopci = BCMOLT_STATUS_OFF;
    obj->lopci_mic_error = BCMOLT_STATUS_OFF;
    obj->looci = BCMOLT_STATUS_OFF;
    obj->tiwi = BCMOLT_STATUS_OFF;
    obj->dowi = BCMOLT_STATUS_OFF;
    obj->sufi = BCMOLT_STATUS_OFF;
    obj->sfi = BCMOLT_STATUS_OFF;
    obj->sdi = BCMOLT_STATUS_OFF;
    obj->dfi = BCMOLT_STATUS_OFF;
    obj->dgi = BCMOLT_STATUS_OFF;
    obj->pqsi = BCMOLT_STATUS_OFF;
    obj->loai = BCMOLT_STATUS_OFF;
    obj->loki = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_xgpon_onu_alarm_state_validate(const bcmolt_xgpon_onu_alarm_state *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOSI))
    {
        switch (obj->losi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "losi: enum value %d is unexpected\n", (int)obj->losi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOBI))
    {
        switch (obj->lobi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lobi: enum value %d is unexpected\n", (int)obj->lobi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOPCI))
    {
        switch (obj->lopci)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lopci: enum value %d is unexpected\n", (int)obj->lopci);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOPCI_MIC_ERROR))
    {
        switch (obj->lopci_mic_error)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lopci_mic_error: enum value %d is unexpected\n", (int)obj->lopci_mic_error);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOOCI))
    {
        switch (obj->looci)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "looci: enum value %d is unexpected\n", (int)obj->looci);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_TIWI))
    {
        switch (obj->tiwi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tiwi: enum value %d is unexpected\n", (int)obj->tiwi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_DOWI))
    {
        switch (obj->dowi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "dowi: enum value %d is unexpected\n", (int)obj->dowi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_SUFI))
    {
        switch (obj->sufi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sufi: enum value %d is unexpected\n", (int)obj->sufi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_SFI))
    {
        switch (obj->sfi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sfi: enum value %d is unexpected\n", (int)obj->sfi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_SDI))
    {
        switch (obj->sdi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "sdi: enum value %d is unexpected\n", (int)obj->sdi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_DFI))
    {
        switch (obj->dfi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "dfi: enum value %d is unexpected\n", (int)obj->dfi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_DGI))
    {
        switch (obj->dgi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "dgi: enum value %d is unexpected\n", (int)obj->dgi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_PQSI))
    {
        switch (obj->pqsi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "pqsi: enum value %d is unexpected\n", (int)obj->pqsi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOAI))
    {
        switch (obj->loai)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loai: enum value %d is unexpected\n", (int)obj->loai);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_STATE_ID_LOKI))
    {
        switch (obj->loki)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loki: enum value %d is unexpected\n", (int)obj->loki);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_ps_type_w_set_default(bcmolt_onu_ps_type_w *obj)
{
    obj->presence_mask = 0;
    obj->control = BCMOLT_CONTROL_STATE_DISABLE;
    bcmolt_pon_id_set_default(&obj->partner_pon_id);
    obj->partner_static_eqd = 0UL;
}

bcmos_bool bcmolt_onu_ps_type_w_validate(const bcmolt_onu_ps_type_w *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_PS_TYPE_W_ID_CONTROL))
    {
        switch (obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "control: enum value %d is unexpected\n", (int)obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_PS_TYPE_W_ID_PARTNER_PON_ID))
    {
        int prefix_len = bcmolt_string_append(err_details, "partner_pon_id.");
        if (!bcmolt_pon_id_validate(&obj->partner_pon_id, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_PS_TYPE_W_ID_PARTNER_STATIC_EQD))
    {
        /* obj->partner_static_eqd can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_ngpon2_onu_params_set_default(bcmolt_ngpon2_onu_params *obj)
{
    obj->presence_mask = 0;
    bcmolt_arr_calibration_record_8_set_default(&obj->calibration_record);
    obj->us_line_rate = BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_2_P_5_G;
    obj->tuning_granularity = 0;
    obj->step_tuning_time = 0;
    obj->power_levelling_capabilities = 0;
    obj->tuning_static_eqd = 0UL;
    bcmolt_onu_ps_type_w_set_default(&obj->ps_type_w);
}

bcmos_bool bcmolt_ngpon2_onu_params_validate(const bcmolt_ngpon2_onu_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NGPON2_ONU_PARAMS_ID_CALIBRATION_RECORD))
    {
        int prefix_len = bcmolt_string_append(err_details, "calibration_record.");
        if (!bcmolt_arr_calibration_record_8_validate(&obj->calibration_record, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NGPON2_ONU_PARAMS_ID_US_LINE_RATE))
    {
        switch (obj->us_line_rate)
        {
        case BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_2_P_5_G:
        case BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_10_G:
        case BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_1_G:
        case BCMOLT_UPSTREAM_LINE_RATE_CAPABILITIES_RATE_DUAL_2_P_5_G_AND_10_G:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "us_line_rate: enum value %d is unexpected\n", (int)obj->us_line_rate);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NGPON2_ONU_PARAMS_ID_TUNING_GRANULARITY))
    {
        /* obj->tuning_granularity can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NGPON2_ONU_PARAMS_ID_STEP_TUNING_TIME))
    {
        /* obj->step_tuning_time can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NGPON2_ONU_PARAMS_ID_POWER_LEVELLING_CAPABILITIES))
    {
        /* obj->power_levelling_capabilities can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NGPON2_ONU_PARAMS_ID_TUNING_STATIC_EQD))
    {
        /* obj->tuning_static_eqd can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NGPON2_ONU_PARAMS_ID_PS_TYPE_W))
    {
        int prefix_len = bcmolt_string_append(err_details, "ps_type_w.");
        if (!bcmolt_onu_ps_type_w_validate(&obj->ps_type_w, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_xgpon_onu_registration_keys_set_default(bcmolt_xgpon_onu_registration_keys *obj)
{
    obj->presence_mask = 0;
    bcmolt_aes_key_set_default(&obj->ploam_ik);
    bcmolt_aes_key_set_default(&obj->omci_ik);
    bcmolt_aes_key_set_default(&obj->omci_k1);
    bcmolt_aes_key_set_default(&obj->omci_k2);
    bcmolt_aes_key_set_default(&obj->kek);
}

bcmos_bool bcmolt_xgpon_onu_registration_keys_validate(const bcmolt_xgpon_onu_registration_keys *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_PLOAM_IK))
    {
        int prefix_len = bcmolt_string_append(err_details, "ploam_ik.");
        if (!bcmolt_aes_key_validate(&obj->ploam_ik, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_OMCI_IK))
    {
        int prefix_len = bcmolt_string_append(err_details, "omci_ik.");
        if (!bcmolt_aes_key_validate(&obj->omci_ik, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_OMCI_K1))
    {
        int prefix_len = bcmolt_string_append(err_details, "omci_k1.");
        if (!bcmolt_aes_key_validate(&obj->omci_k1, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_OMCI_K2))
    {
        int prefix_len = bcmolt_string_append(err_details, "omci_k2.");
        if (!bcmolt_aes_key_validate(&obj->omci_k2, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_REGISTRATION_KEYS_ID_KEK))
    {
        int prefix_len = bcmolt_string_append(err_details, "kek.");
        if (!bcmolt_aes_key_validate(&obj->kek, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_request_registration_status_set_default(bcmolt_request_registration_status *obj)
{
    obj->presence_mask = 0;
    obj->request_registration_state = BCMOLT_CONTROL_STATE_DISABLE;
    obj->sma_flag = BCMOS_FALSE;
}

bcmos_bool bcmolt_request_registration_status_validate(const bcmolt_request_registration_status *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_REQUEST_REGISTRATION_STATUS_ID_REQUEST_REGISTRATION_STATE))
    {
        switch (obj->request_registration_state)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "request_registration_state: enum value %d is unexpected\n", (int)obj->request_registration_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_REQUEST_REGISTRATION_STATUS_ID_SMA_FLAG))
    {
        /* obj->sma_flag can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_xgpon_onu_params_set_default(bcmolt_xgpon_onu_params *obj)
{
    obj->presence_mask = 0;
    bcmolt_xgpon_onu_alarm_state_set_default(&obj->alarm_state);
    bcmolt_bin_str_36_set_default(&obj->registration_id);
    bcmolt_ngpon2_onu_params_set_default(&obj->ngpon2);
    bcmolt_xgpon_onu_registration_keys_set_default(&obj->registration_encryption_keys);
    bcmolt_request_registration_status_set_default(&obj->request_registration_status);
    obj->ranging_burst_profile = (bcmolt_burst_profile_index)0;
    obj->data_burst_profile = (bcmolt_burst_profile_index)0;
}

bcmos_bool bcmolt_xgpon_onu_params_validate(const bcmolt_xgpon_onu_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_PARAMS_ID_ALARM_STATE))
    {
        int prefix_len = bcmolt_string_append(err_details, "alarm_state.");
        if (!bcmolt_xgpon_onu_alarm_state_validate(&obj->alarm_state, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_PARAMS_ID_REGISTRATION_ID))
    {
        int prefix_len = bcmolt_string_append(err_details, "registration_id.");
        if (!bcmolt_bin_str_36_validate(&obj->registration_id, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_PARAMS_ID_NGPON2))
    {
        int prefix_len = bcmolt_string_append(err_details, "ngpon2.");
        if (!bcmolt_ngpon2_onu_params_validate(&obj->ngpon2, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_PARAMS_ID_REGISTRATION_ENCRYPTION_KEYS))
    {
        int prefix_len = bcmolt_string_append(err_details, "registration_encryption_keys.");
        if (!bcmolt_xgpon_onu_registration_keys_validate(&obj->registration_encryption_keys, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_PARAMS_ID_REQUEST_REGISTRATION_STATUS))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "request_registration_status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_PARAMS_ID_RANGING_BURST_PROFILE))
    {
        if (obj->ranging_burst_profile > (bcmolt_burst_profile_index)3)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ranging_burst_profile: %u is greater than the maximum value of 3\n", obj->ranging_burst_profile);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_PARAMS_ID_DATA_BURST_PROFILE))
    {
        if (obj->data_burst_profile > (bcmolt_burst_profile_index)3)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "data_burst_profile: %u is greater than the maximum value of 3\n", obj->data_burst_profile);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itu_onu_params_set_default(bcmolt_itu_onu_params *obj)
{
    obj->presence_mask = 0;
    bcmolt_serial_number_set_default(&obj->serial_number);
    obj->ranging_time = 0UL;
    bcmolt_itupon_onu_aes_key_set_default(&obj->encryption_key);
    obj->auto_learning = BCMOS_FALSE;
    obj->disabled_after_discovery = BCMOLT_STATUS_OFF;
    obj->automatic_onu_deactivation_reason = BCMOLT_AUTOMATIC_ONU_DEACTIVATION_REASON_NONE;
    obj->ps_type_c = BCMOS_FALSE;
    bcmolt_gpon_onu_params_set_default(&obj->gpon);
    bcmolt_xgpon_onu_params_set_default(&obj->xgpon);
}

bcmos_bool bcmolt_itu_onu_params_validate(const bcmolt_itu_onu_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_ONU_PARAMS_ID_SERIAL_NUMBER))
    {
        int prefix_len = bcmolt_string_append(err_details, "serial_number.");
        if (!bcmolt_serial_number_validate(&obj->serial_number, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_ONU_PARAMS_ID_RANGING_TIME))
    {
        /* obj->ranging_time can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_ONU_PARAMS_ID_ENCRYPTION_KEY))
    {
        int prefix_len = bcmolt_string_append(err_details, "encryption_key.");
        if (!bcmolt_itupon_onu_aes_key_validate(&obj->encryption_key, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_ONU_PARAMS_ID_AUTO_LEARNING))
    {
        /* obj->auto_learning can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_ONU_PARAMS_ID_DISABLED_AFTER_DISCOVERY))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "disabled_after_discovery: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_ONU_PARAMS_ID_AUTOMATIC_ONU_DEACTIVATION_REASON))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "automatic_onu_deactivation_reason: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_ONU_PARAMS_ID_PS_TYPE_C))
    {
        /* obj->ps_type_c can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_ONU_PARAMS_ID_GPON))
    {
        int prefix_len = bcmolt_string_append(err_details, "gpon.");
        if (!bcmolt_gpon_onu_params_validate(&obj->gpon, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_ONU_PARAMS_ID_XGPON))
    {
        int prefix_len = bcmolt_string_append(err_details, "xgpon.");
        if (!bcmolt_xgpon_onu_params_validate(&obj->xgpon, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_available_bandwidth_set_default(bcmolt_pon_available_bandwidth *obj)
{
    obj->presence_mask = 0;
    obj->cbr_bw = 0UL;
    obj->total_bw = 0UL;
    obj->group_total_bw = 0UL;
    obj->next_onu_total_bw = 0UL;
}

bcmos_bool bcmolt_pon_available_bandwidth_validate(const bcmolt_pon_available_bandwidth *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_CBR_BW))
    {
        /* obj->cbr_bw can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_TOTAL_BW))
    {
        /* obj->total_bw can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_GROUP_TOTAL_BW))
    {
        /* obj->group_total_bw can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_AVAILABLE_BANDWIDTH_ID_NEXT_ONU_TOTAL_BW))
    {
        /* obj->next_onu_total_bw can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_drift_control_set_default(bcmolt_pon_drift_control *obj)
{
    obj->presence_mask = 0;
    obj->drift_interval = 1000UL;
    obj->drift_limit = 8;
    obj->transmission_control_limit = 16;
}

bcmos_bool bcmolt_pon_drift_control_validate(const bcmolt_pon_drift_control *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_DRIFT_CONTROL_ID_DRIFT_INTERVAL))
    {
        if (obj->drift_interval > 60000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "drift_interval: %u is greater than the maximum value of 60000\n", obj->drift_interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_DRIFT_CONTROL_ID_DRIFT_LIMIT))
    {
        if (obj->drift_limit < 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "drift_limit: %u is less than the minimum value of 1\n", obj->drift_limit);
            return BCMOS_FALSE;
        }
        if (obj->drift_limit > 32)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "drift_limit: %u is greater than the maximum value of 32\n", obj->drift_limit);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_DRIFT_CONTROL_ID_TRANSMISSION_CONTROL_LIMIT))
    {
        if (obj->transmission_control_limit < 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "transmission_control_limit: %u is less than the minimum value of 1\n", obj->transmission_control_limit);
            return BCMOS_FALSE;
        }
        if (obj->transmission_control_limit > 64)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "transmission_control_limit: %u is greater than the maximum value of 64\n", obj->transmission_control_limit);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_activation_set_default(bcmolt_onu_activation *obj)
{
    obj->presence_mask = 0;
    obj->key_exchange = BCMOLT_CONTROL_STATE_DISABLE;
    obj->authentication = BCMOLT_CONTROL_STATE_ENABLE;
    obj->fail_due_to_authentication_failure = BCMOLT_CONTROL_STATE_ENABLE;
}

bcmos_bool bcmolt_onu_activation_validate(const bcmolt_onu_activation *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_ACTIVATION_ID_KEY_EXCHANGE))
    {
        switch (obj->key_exchange)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "key_exchange: enum value %d is unexpected\n", (int)obj->key_exchange);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_ACTIVATION_ID_AUTHENTICATION))
    {
        switch (obj->authentication)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "authentication: enum value %d is unexpected\n", (int)obj->authentication);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_ACTIVATION_ID_FAIL_DUE_TO_AUTHENTICATION_FAILURE))
    {
        switch (obj->fail_due_to_authentication_failure)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "fail_due_to_authentication_failure: enum value %d is unexpected\n", (int)obj->fail_due_to_authentication_failure);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_key_exchange_set_default(bcmolt_key_exchange *obj)
{
    obj->presence_mask = 0;
    obj->interval = 10000UL;
    obj->control = BCMOLT_CONTROL_STATE_DISABLE;
    obj->encrypted_ports_only = BCMOLT_CONTROL_STATE_DISABLE;
    obj->gpon_mode = BCMOLT_GPON_KEY_EXCHANGE_MODE_NORMAL;
}

bcmos_bool bcmolt_key_exchange_validate(const bcmolt_key_exchange *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_KEY_EXCHANGE_ID_INTERVAL))
    {
        if (obj->interval < 1000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "interval: %u is less than the minimum value of 1000\n", obj->interval);
            return BCMOS_FALSE;
        }
        if (obj->interval > 3600000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "interval: %u is greater than the maximum value of 3600000\n", obj->interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_KEY_EXCHANGE_ID_CONTROL))
    {
        switch (obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "control: enum value %d is unexpected\n", (int)obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_KEY_EXCHANGE_ID_ENCRYPTED_PORTS_ONLY))
    {
        switch (obj->encrypted_ports_only)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "encrypted_ports_only: enum value %d is unexpected\n", (int)obj->encrypted_ports_only);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_KEY_EXCHANGE_ID_GPON_MODE))
    {
        switch (obj->gpon_mode)
        {
        case BCMOLT_GPON_KEY_EXCHANGE_MODE_NORMAL:
        case BCMOLT_GPON_KEY_EXCHANGE_MODE_ENHANCED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "gpon_mode: enum value %d is unexpected\n", (int)obj->gpon_mode);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_power_management_configuration_set_default(bcmolt_onu_power_management_configuration *obj)
{
    obj->presence_mask = 0;
    obj->ilowpower = 1600UL;
    obj->iaware = 160UL;
    obj->itransinit = 80U;
    obj->itxinit = 80U;
    obj->irxoff = 1600UL;
}

bcmos_bool bcmolt_onu_power_management_configuration_validate(const bcmolt_onu_power_management_configuration *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_ILOWPOWER))
    {
        if (obj->ilowpower < 8UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ilowpower: %u is less than the minimum value of 8\n", obj->ilowpower);
            return BCMOS_FALSE;
        }
        if (obj->ilowpower > 480000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ilowpower: %u is greater than the maximum value of 480000\n", obj->ilowpower);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_IAWARE))
    {
        if (obj->iaware < 8UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "iaware: %u is less than the minimum value of 8\n", obj->iaware);
            return BCMOS_FALSE;
        }
        if (obj->iaware > 480000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "iaware: %u is greater than the maximum value of 480000\n", obj->iaware);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_ITRANSINIT))
    {
        if (obj->itransinit > 8000U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "itransinit: %u is greater than the maximum value of 8000\n", obj->itransinit);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_ITXINIT))
    {
        if (obj->itxinit > 8000U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "itxinit: %u is greater than the maximum value of 8000\n", obj->itxinit);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_POWER_MANAGEMENT_CONFIGURATION_ID_IRXOFF))
    {
        if (obj->irxoff < 8UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "irxoff: %u is less than the minimum value of 8\n", obj->irxoff);
            return BCMOS_FALSE;
        }
        if (obj->irxoff > 480000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "irxoff: %u is greater than the maximum value of 480000\n", obj->irxoff);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_periodic_standby_pon_monitoring_set_default(bcmolt_periodic_standby_pon_monitoring *obj)
{
    obj->presence_mask = 0;
    obj->interval = 5000UL;
    obj->control = BCMOLT_CONTROL_STATE_DISABLE;
}

bcmos_bool bcmolt_periodic_standby_pon_monitoring_validate(const bcmolt_periodic_standby_pon_monitoring *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID_INTERVAL))
    {
        if (obj->interval < 1000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "interval: %u is less than the minimum value of 1000\n", obj->interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PERIODIC_STANDBY_PON_MONITORING_ID_CONTROL))
    {
        switch (obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "control: enum value %d is unexpected\n", (int)obj->control);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_prbs_checker_config_set_default(bcmolt_prbs_checker_config *obj)
{
    obj->presence_mask = 0;
    obj->polynom = BCMOLT_PRBS_POLYNOMIAL_PRBS_7;
    obj->mode = BCMOLT_PRBS_CHECKER_MODE_SELF_SYNC;
    obj->data_invert = BCMOS_FALSE;
    obj->control = BCMOLT_CONTROL_STATE_DISABLE;
    obj->is_tdmr_xgs = BCMOS_TRUE;
}

bcmos_bool bcmolt_prbs_checker_config_validate(const bcmolt_prbs_checker_config *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_CHECKER_CONFIG_ID_POLYNOM))
    {
        switch (obj->polynom)
        {
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_7:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_9:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_11:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_15:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_23:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_31:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_58:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "polynom: enum value %d is unexpected\n", (int)obj->polynom);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_CHECKER_CONFIG_ID_MODE))
    {
        switch (obj->mode)
        {
        case BCMOLT_PRBS_CHECKER_MODE_SELF_SYNC:
        case BCMOLT_PRBS_CHECKER_MODE_INITIAL_SEED_MODE:
        case BCMOLT_PRBS_CHECKER_MODE_INITIAL_SEED_MODE_2:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "mode: enum value %d is unexpected\n", (int)obj->mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_CHECKER_CONFIG_ID_DATA_INVERT))
    {
        /* obj->data_invert can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_CHECKER_CONFIG_ID_CONTROL))
    {
        switch (obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "control: enum value %d is unexpected\n", (int)obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_CHECKER_CONFIG_ID_IS_TDMR_XGS))
    {
        /* obj->is_tdmr_xgs can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_prbs_generator_config_set_default(bcmolt_prbs_generator_config *obj)
{
    obj->presence_mask = 0;
    obj->polynom = BCMOLT_PRBS_POLYNOMIAL_PRBS_7;
    obj->error_insert = BCMOS_FALSE;
    obj->invert = BCMOS_FALSE;
    obj->control = BCMOLT_CONTROL_STATE_DISABLE;
}

bcmos_bool bcmolt_prbs_generator_config_validate(const bcmolt_prbs_generator_config *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_GENERATOR_CONFIG_ID_POLYNOM))
    {
        switch (obj->polynom)
        {
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_7:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_9:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_11:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_15:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_23:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_31:
        case BCMOLT_PRBS_POLYNOMIAL_PRBS_58:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "polynom: enum value %d is unexpected\n", (int)obj->polynom);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_GENERATOR_CONFIG_ID_ERROR_INSERT))
    {
        /* obj->error_insert can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_GENERATOR_CONFIG_ID_INVERT))
    {
        /* obj->invert can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_GENERATOR_CONFIG_ID_CONTROL))
    {
        switch (obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "control: enum value %d is unexpected\n", (int)obj->control);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_prbs_status_set_default(bcmolt_prbs_status *obj)
{
    obj->presence_mask = 0;
    obj->lock_state = BCMOLT_PRBS_LOCK_STATE_UNLOCKED;
    obj->error_counts = 0UL;
    obj->loss_sync = BCMOS_FALSE;
    obj->ber = 0;
    obj->test_status = BCMOLT_PRBS_TEST_STATUS_TYPE_STATUS_NA;
}

bcmos_bool bcmolt_prbs_status_validate(const bcmolt_prbs_status *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_STATUS_ID_LOCK_STATE))
    {
        switch (obj->lock_state)
        {
        case BCMOLT_PRBS_LOCK_STATE_UNLOCKED:
        case BCMOLT_PRBS_LOCK_STATE_LOCKED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lock_state: enum value %d is unexpected\n", (int)obj->lock_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_STATUS_ID_ERROR_COUNTS))
    {
        /* obj->error_counts can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_STATUS_ID_LOSS_SYNC))
    {
        /* obj->loss_sync can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_STATUS_ID_BER))
    {
        /* obj->ber can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PRBS_STATUS_ID_TEST_STATUS))
    {
        switch (obj->test_status)
        {
        case BCMOLT_PRBS_TEST_STATUS_TYPE_STATUS_NA:
        case BCMOLT_PRBS_TEST_STATUS_TYPE_TEST_CONTINUE:
        case BCMOLT_PRBS_TEST_STATUS_TYPE_TEST_DONE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "test_status: enum value %d is unexpected\n", (int)obj->test_status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_protection_switching_set_default(bcmolt_itupon_protection_switching *obj)
{
    obj->presence_mask = 0;
    obj->timeout = 100U;
    obj->gpio_pin = BCMOLT_GPIO_PIN_UNCONFIGURED;
    obj->ps_c_wait_before_deactivation_timeout = 1000U;
    obj->options = (bcmolt_pon_protection_switching_options)0UL;
}

bcmos_bool bcmolt_itupon_protection_switching_validate(const bcmolt_itupon_protection_switching *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_TIMEOUT))
    {
        /* obj->timeout can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_GPIO_PIN))
    {
        switch (obj->gpio_pin)
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
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "gpio_pin: enum value %d is unexpected\n", (int)obj->gpio_pin);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_PS_C_WAIT_BEFORE_DEACTIVATION_TIMEOUT))
    {
        /* obj->ps_c_wait_before_deactivation_timeout can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_PROTECTION_SWITCHING_ID_OPTIONS))
    {
        if ((obj->options & ~0x3UL) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "options: 0x%X includes invalid bits\n", obj->options);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_ituonu_upgrade_params_set_default(bcmolt_ituonu_upgrade_params *obj)
{
    obj->presence_mask = 0;
    obj->response_timeout_ms = 1000UL;
    obj->max_retry_count = 23;
    obj->omci_format = BCMOLT_OMCI_DEVICE_ID_BASELINE;
    obj->window_size = 32U;
    obj->activate_commit = BCMOS_FALSE;
    obj->delay_for_commit_ms = 45000UL;
    obj->max_activation_attempts = 23;
    obj->end_swdl_delay_ms = 30000UL;
}

bcmos_bool bcmolt_ituonu_upgrade_params_validate(const bcmolt_ituonu_upgrade_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUONU_UPGRADE_PARAMS_ID_RESPONSE_TIMEOUT_MS))
    {
        if (obj->response_timeout_ms < 50UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "response_timeout_ms: %u is less than the minimum value of 50\n", obj->response_timeout_ms);
            return BCMOS_FALSE;
        }
        if (obj->response_timeout_ms > 1000000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "response_timeout_ms: %u is greater than the maximum value of 1000000\n", obj->response_timeout_ms);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUONU_UPGRADE_PARAMS_ID_MAX_RETRY_COUNT))
    {
        /* obj->max_retry_count can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUONU_UPGRADE_PARAMS_ID_OMCI_FORMAT))
    {
        switch (obj->omci_format)
        {
        case BCMOLT_OMCI_DEVICE_ID_BASELINE:
        case BCMOLT_OMCI_DEVICE_ID_EXTENDED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "omci_format: enum value %d is unexpected\n", (int)obj->omci_format);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUONU_UPGRADE_PARAMS_ID_WINDOW_SIZE))
    {
        if (obj->window_size < 1U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "window_size: %u is less than the minimum value of 1\n", obj->window_size);
            return BCMOS_FALSE;
        }
        if (obj->window_size > 256U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "window_size: %u is greater than the maximum value of 256\n", obj->window_size);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUONU_UPGRADE_PARAMS_ID_ACTIVATE_COMMIT))
    {
        /* obj->activate_commit can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUONU_UPGRADE_PARAMS_ID_DELAY_FOR_COMMIT_MS))
    {
        if (obj->delay_for_commit_ms > 1000000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "delay_for_commit_ms: %u is greater than the maximum value of 1000000\n", obj->delay_for_commit_ms);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUONU_UPGRADE_PARAMS_ID_MAX_ACTIVATION_ATTEMPTS))
    {
        /* obj->max_activation_attempts can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUONU_UPGRADE_PARAMS_ID_END_SWDL_DELAY_MS))
    {
        if (obj->end_swdl_delay_ms > 1000000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "end_swdl_delay_ms: %u is greater than the maximum value of 1000000\n", obj->end_swdl_delay_ms);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_upgrade_status_set_default(bcmolt_onu_upgrade_status *obj)
{
    obj->presence_mask = 0;
    obj->onu_id = (bcmolt_onu_id)0U;
    obj->bytes_transmitted = 0UL;
    obj->status = BCMOLT_ONU_UPGRADE_STATUS_CODE_TRANSFERRING_IMAGE;
}

bcmos_bool bcmolt_onu_upgrade_status_validate(const bcmolt_onu_upgrade_status *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_UPGRADE_STATUS_ID_ONU_ID))
    {
        /* obj->onu_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_UPGRADE_STATUS_ID_BYTES_TRANSMITTED))
    {
        /* obj->bytes_transmitted can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_UPGRADE_STATUS_ID_STATUS))
    {
        switch (obj->status)
        {
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_TRANSFERRING_IMAGE:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_FINALIZING_TRANSFER:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_ACTIVATING:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_SUCCESS:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_INTERNAL_ERROR:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_ONU_RESPONSE_TIMEOUT:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_MESSAGE_SEND_FAILED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_SYNC_ERROR:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_COMMIT_FAILED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_PARSE_ERROR:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_TCI_MISMATCH:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_GET_IMAGE_FAILED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_ACTIVATION_FAILED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_ONU_DEACTIVATED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_PROCESSING_ERROR:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_NOT_SUPPORTED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_PARAMETER_ERROR:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_UNKNOWN_MANAGED_ENTITY:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_UNKNOWN_MANAGED_ENTITY_INSTANCE:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_OMCI_DEVICE_BUSY:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_UNDEFINED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_NOT_FOUND:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_NO_ACCESS:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_FULL:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_ILLEGAL_OPERATION:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_UNKNOWN_ID:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_BAD_BLOCK:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_TIMEOUT:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_BUSY:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_INCOMPATIBLE_FILE:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_DPOE_CORRUPTED_FILE:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_ERROR_NOT_DEFINED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_ERROR_ALLOC_EXCEEDED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_ERROR_ILLEGAL_OP:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_ERROR_FILE_EXISTS:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_END_WRITING_NVS:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_END_CRC_ERROR:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_END_PARAMETER_ERROR:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_CTC_END_COMMAND_NOT_SUPPORTED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_OK:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_UNDEFINED:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_NOT_FOUND:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_NO_ACCESS:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_FULL:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_ILLEGAL_OP:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_UNKNOWN_ID:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_BAD_BLOCK:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_TIMEOUT:
        case BCMOLT_ONU_UPGRADE_STATUS_CODE_BRCM_OAM_BUSY:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "status: enum value %d is unexpected\n", (int)obj->status);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_upgrade_status_list_u32_max_128_set_default(bcmolt_onu_upgrade_status_list_u32_max_128 *obj)
{
    obj->len = 0UL;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_onu_upgrade_status_list_u32_max_128_validate(const bcmolt_onu_upgrade_status_list_u32_max_128 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (obj->len > 128)
    {
        *err = BCM_ERR_RANGE;
        bcmolt_string_append(err_details, "len: %u is greater than the maximum array length of 128\n", obj->len);
        return BCMOS_FALSE;
    }
    for (uint32_t i = 0; i < obj->len; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_onu_upgrade_status_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_onu_upgrade_status_set_default(bcmolt_pon_onu_upgrade_status *obj)
{
    obj->presence_mask = 0;
    obj->overall_status = BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_NOT_STARTED;
    obj->file_size_in_bytes = 0UL;
    bcmolt_onu_upgrade_status_list_u32_max_128_set_default(&obj->onu_status);
}

bcmos_bool bcmolt_pon_onu_upgrade_status_validate(const bcmolt_pon_onu_upgrade_status *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ONU_UPGRADE_STATUS_ID_OVERALL_STATUS))
    {
        switch (obj->overall_status)
        {
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_NOT_STARTED:
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_IN_PROGRESS:
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_SUCCESS:
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_FAILURE:
        case BCMOLT_PON_NI_ONU_UPGRADE_STATUS_CODE_ABORTED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "overall_status: enum value %d is unexpected\n", (int)obj->overall_status);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ONU_UPGRADE_STATUS_ID_FILE_SIZE_IN_BYTES))
    {
        /* obj->file_size_in_bytes can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ONU_UPGRADE_STATUS_ID_ONU_STATUS))
    {
        if (obj->onu_status.len > 128)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "onu_status: %u is greater than the maximum array length of 128\n", obj->onu_status.len);
            return BCMOS_FALSE;
        }
        int prefix_len = bcmolt_string_append(err_details, "onu_status.");
        if (!bcmolt_onu_upgrade_status_list_u32_max_128_validate(&obj->onu_status, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_xgpon_onu_alarms_thresholds_set_default(bcmolt_xgpon_onu_alarms_thresholds *obj)
{
    obj->presence_mask = 0;
    obj->losi = 4;
    obj->lobi = 4;
    obj->looci = 3;
    obj->lopci = 3;
}

bcmos_bool bcmolt_xgpon_onu_alarms_thresholds_validate(const bcmolt_xgpon_onu_alarms_thresholds *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOSI))
    {
        /* obj->losi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOBI))
    {
        /* obj->lobi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOOCI))
    {
        /* obj->looci can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARMS_THRESHOLDS_ID_LOPCI))
    {
        /* obj->lopci can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_xgpon_onu_alarm_indication_control_set_default(bcmolt_xgpon_onu_alarm_indication_control *obj)
{
    obj->presence_mask = 0;
    obj->loai = BCMOLT_CONTROL_STATE_DISABLE;
    obj->loki = BCMOLT_CONTROL_STATE_DISABLE;
}

bcmos_bool bcmolt_xgpon_onu_alarm_indication_control_validate(const bcmolt_xgpon_onu_alarm_indication_control *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID_LOAI))
    {
        switch (obj->loai)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loai: enum value %d is unexpected\n", (int)obj->loai);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARM_INDICATION_CONTROL_ID_LOKI))
    {
        switch (obj->loki)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loki: enum value %d is unexpected\n", (int)obj->loki);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_xgpon_multicast_key_set_default(bcmolt_xgpon_multicast_key *obj)
{
    obj->presence_mask = 0;
    bcmolt_arr_aes_key_2_set_default(&obj->key);
    obj->key_index = 0;
}

bcmos_bool bcmolt_xgpon_multicast_key_validate(const bcmolt_xgpon_multicast_key *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_MULTICAST_KEY_ID_KEY))
    {
        int prefix_len = bcmolt_string_append(err_details, "key.");
        if (!bcmolt_arr_aes_key_2_validate(&obj->key, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_MULTICAST_KEY_ID_KEY_INDEX))
    {
        if (obj->key_index > 2)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "key_index: %u is greater than the maximum value of 2\n", obj->key_index);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_tuning_configuration_set_default(bcmolt_onu_tuning_configuration *obj)
{
    obj->presence_mask = 0;
    obj->tsource = 1000UL;
    obj->ttarget = 1000UL;
    obj->request_registration_required = BCMOS_TRUE;
    obj->range_mode = BCMOLT_ONU_TUNING_RANGE_MODE_RE_RANGE;
    obj->retry_interval = 250UL;
}

bcmos_bool bcmolt_onu_tuning_configuration_validate(const bcmolt_onu_tuning_configuration *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_TUNING_CONFIGURATION_ID_TSOURCE))
    {
        if (obj->tsource < 100UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tsource: %u is less than the minimum value of 100\n", obj->tsource);
            return BCMOS_FALSE;
        }
        if (obj->tsource > 60000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tsource: %u is greater than the maximum value of 60000\n", obj->tsource);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_TUNING_CONFIGURATION_ID_TTARGET))
    {
        if (obj->ttarget < 100UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ttarget: %u is less than the minimum value of 100\n", obj->ttarget);
            return BCMOS_FALSE;
        }
        if (obj->ttarget > 60000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ttarget: %u is greater than the maximum value of 60000\n", obj->ttarget);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_TUNING_CONFIGURATION_ID_REQUEST_REGISTRATION_REQUIRED))
    {
        /* obj->request_registration_required can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_TUNING_CONFIGURATION_ID_RANGE_MODE))
    {
        switch (obj->range_mode)
        {
        case BCMOLT_ONU_TUNING_RANGE_MODE_RE_RANGE:
        case BCMOLT_ONU_TUNING_RANGE_MODE_STATIC_RANGE:
        case BCMOLT_ONU_TUNING_RANGE_MODE_PRE_PROVISIONED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "range_mode: enum value %d is unexpected\n", (int)obj->range_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ONU_TUNING_CONFIGURATION_ID_RETRY_INTERVAL))
    {
        if (obj->retry_interval < 50UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "retry_interval: %u is less than the minimum value of 50\n", obj->retry_interval);
            return BCMOS_FALSE;
        }
        if (obj->retry_interval > 60000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "retry_interval: %u is greater than the maximum value of 60000\n", obj->retry_interval);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_ngpon2_pon_params_set_default(bcmolt_ngpon2_pon_params *obj)
{
    obj->presence_mask = 0;
    obj->ngpon2_amd1 = BCMOLT_CONTROL_STATE_DISABLE;
    bcmolt_onu_tuning_configuration_set_default(&obj->onu_tuning);
}

bcmos_bool bcmolt_ngpon2_pon_params_validate(const bcmolt_ngpon2_pon_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NGPON2_PON_PARAMS_ID_NGPON2_AMD1))
    {
        switch (obj->ngpon2_amd1)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ngpon2_amd1: enum value %d is unexpected\n", (int)obj->ngpon2_amd1);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NGPON2_PON_PARAMS_ID_ONU_TUNING))
    {
        int prefix_len = bcmolt_string_append(err_details, "onu_tuning.");
        if (!bcmolt_onu_tuning_configuration_validate(&obj->onu_tuning, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_ploam_retransmission_set_default(bcmolt_ploam_retransmission *obj)
{
    obj->presence_mask = 0;
    obj->retrans_ranging_time = 0;
    obj->retrans_assign_alloc_id = 0;
    obj->retrans_key_control = 0;
    obj->retrans_request_registration = 0;
}

bcmos_bool bcmolt_ploam_retransmission_validate(const bcmolt_ploam_retransmission *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_RANGING_TIME))
    {
        /* obj->retrans_ranging_time can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_ASSIGN_ALLOC_ID))
    {
        /* obj->retrans_assign_alloc_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_KEY_CONTROL))
    {
        /* obj->retrans_key_control can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PLOAM_RETRANSMISSION_ID_RETRANS_REQUEST_REGISTRATION))
    {
        /* obj->retrans_request_registration can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_operation_control_set_default(bcmolt_operation_control *obj)
{
    obj->presence_mask = 0;
    obj->re = 0;
    obj->odn_class = BCMOLT_ODN_CLASS_N1;
    obj->ds_fec_mode = BCMOLT_CONTROL_STATE_ENABLE;
    obj->protocol = BCMOLT_TC_PROTOCOL_TC_LAYER_PROTOCOL_G_989_P_3;
    obj->ds_link_type = BCMOLT_LINK_TYPE_UNSPECIFIED;
    bcmolt_pon_id_set_default(&obj->pon_id);
    obj->c = 0;
    obj->tol = 0U;
}

bcmos_bool bcmolt_operation_control_validate(const bcmolt_operation_control *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_OPERATION_CONTROL_ID_RE))
    {
        if (obj->re > 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "re: %u is greater than the maximum value of 1\n", obj->re);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_OPERATION_CONTROL_ID_ODN_CLASS))
    {
        switch (obj->odn_class)
        {
        case BCMOLT_ODN_CLASS_N1:
        case BCMOLT_ODN_CLASS_N2:
        case BCMOLT_ODN_CLASS_E1:
        case BCMOLT_ODN_CLASS_E2:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "odn_class: enum value %d is unexpected\n", (int)obj->odn_class);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_OPERATION_CONTROL_ID_DS_FEC_MODE))
    {
        switch (obj->ds_fec_mode)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ds_fec_mode: enum value %d is unexpected\n", (int)obj->ds_fec_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_OPERATION_CONTROL_ID_PROTOCOL))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "protocol: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_OPERATION_CONTROL_ID_DS_LINK_TYPE))
    {
        switch (obj->ds_link_type)
        {
        case BCMOLT_LINK_TYPE_UNSPECIFIED:
        case BCMOLT_LINK_TYPE_B:
        case BCMOLT_LINK_TYPE_A:
        case BCMOLT_LINK_TYPE_A_AND_B:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ds_link_type: enum value %d is unexpected\n", (int)obj->ds_link_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_OPERATION_CONTROL_ID_PON_ID))
    {
        int prefix_len = bcmolt_string_append(err_details, "pon_id.");
        if (!bcmolt_pon_id_validate(&obj->pon_id, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_OPERATION_CONTROL_ID_C))
    {
        if (obj->c > 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "c: %u is greater than the maximum value of 1\n", obj->c);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_OPERATION_CONTROL_ID_TOL))
    {
        if (obj->tol > 511U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tol: %u is greater than the maximum value of 511\n", obj->tol);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_periodic_ploams_set_default(bcmolt_periodic_ploams *obj)
{
    obj->presence_mask = 0;
    obj->control = BCMOLT_CONTROL_STATE_DISABLE;
    obj->interval_ms = 5000UL;
}

bcmos_bool bcmolt_periodic_ploams_validate(const bcmolt_periodic_ploams *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PERIODIC_PLOAMS_ID_CONTROL))
    {
        switch (obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "control: enum value %d is unexpected\n", (int)obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PERIODIC_PLOAMS_ID_INTERVAL_MS))
    {
        if (obj->interval_ms < 500UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "interval_ms: %u is less than the minimum value of 500\n", obj->interval_ms);
            return BCMOS_FALSE;
        }
        if (obj->interval_ms > 10000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "interval_ms: %u is greater than the maximum value of 10000\n", obj->interval_ms);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_xgpon_pon_params_set_default(bcmolt_xgpon_pon_params *obj)
{
    obj->presence_mask = 0;
    bcmolt_hw_pon_id_set_default(&obj->hw_pon_id);
    bcmolt_xgpon_onu_alarms_thresholds_set_default(&obj->onu_alarms_thresholds);
    bcmolt_xgpon_onu_alarm_indication_control_set_default(&obj->alarm_indication_control);
    bcmolt_xgpon_multicast_key_set_default(&obj->multicast_key);
    obj->min_data_gem_port_id = (bcmolt_gem_port_id)1024UL;
    bcmolt_ngpon2_pon_params_set_default(&obj->ngpon2);
    obj->tdma_2_5_g_discovery = BCMOLT_CONTROL_STATE_DISABLE;
    obj->tdma_10_g_discovery = BCMOLT_CONTROL_STATE_DISABLE;
    bcmolt_ploam_retransmission_set_default(&obj->ploam_retransmission);
    obj->tdma_number_of_2_5_g_active_onus = 0U;
    obj->tdma_number_of_10_g_active_onus = 0U;
    bcmolt_operation_control_set_default(&obj->operation_control);
    bcmolt_periodic_ploams_set_default(&obj->periodic_ploams);
}

bcmos_bool bcmolt_xgpon_pon_params_validate(const bcmolt_xgpon_pon_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_HW_PON_ID))
    {
        int prefix_len = bcmolt_string_append(err_details, "hw_pon_id.");
        if (!bcmolt_hw_pon_id_validate(&obj->hw_pon_id, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_ONU_ALARMS_THRESHOLDS))
    {
        int prefix_len = bcmolt_string_append(err_details, "onu_alarms_thresholds.");
        if (!bcmolt_xgpon_onu_alarms_thresholds_validate(&obj->onu_alarms_thresholds, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_ALARM_INDICATION_CONTROL))
    {
        int prefix_len = bcmolt_string_append(err_details, "alarm_indication_control.");
        if (!bcmolt_xgpon_onu_alarm_indication_control_validate(&obj->alarm_indication_control, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_MULTICAST_KEY))
    {
        int prefix_len = bcmolt_string_append(err_details, "multicast_key.");
        if (!bcmolt_xgpon_multicast_key_validate(&obj->multicast_key, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_MIN_DATA_GEM_PORT_ID))
    {
        if (obj->min_data_gem_port_id < (bcmolt_gem_port_id)1021UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "min_data_gem_port_id: %u is less than the minimum value of 1021\n", obj->min_data_gem_port_id);
            return BCMOS_FALSE;
        }
        if (obj->min_data_gem_port_id > (bcmolt_gem_port_id)57599UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "min_data_gem_port_id: %u is greater than the maximum value of 57599\n", obj->min_data_gem_port_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_NGPON2))
    {
        int prefix_len = bcmolt_string_append(err_details, "ngpon2.");
        if (!bcmolt_ngpon2_pon_params_validate(&obj->ngpon2, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_TDMA_2_5_G_DISCOVERY))
    {
        switch (obj->tdma_2_5_g_discovery)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tdma_2_5_g_discovery: enum value %d is unexpected\n", (int)obj->tdma_2_5_g_discovery);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_TDMA_10_G_DISCOVERY))
    {
        switch (obj->tdma_10_g_discovery)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tdma_10_g_discovery: enum value %d is unexpected\n", (int)obj->tdma_10_g_discovery);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_PLOAM_RETRANSMISSION))
    {
        int prefix_len = bcmolt_string_append(err_details, "ploam_retransmission.");
        if (!bcmolt_ploam_retransmission_validate(&obj->ploam_retransmission, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_TDMA_NUMBER_OF_2_5_G_ACTIVE_ONUS))
    {
        /* obj->tdma_number_of_2_5_g_active_onus can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_TDMA_NUMBER_OF_10_G_ACTIVE_ONUS))
    {
        /* obj->tdma_number_of_10_g_active_onus can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_OPERATION_CONTROL))
    {
        int prefix_len = bcmolt_string_append(err_details, "operation_control.");
        if (!bcmolt_operation_control_validate(&obj->operation_control, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_PON_PARAMS_ID_PERIODIC_PLOAMS))
    {
        int prefix_len = bcmolt_string_append(err_details, "periodic_ploams.");
        if (!bcmolt_periodic_ploams_validate(&obj->periodic_ploams, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_dba_set_default(bcmolt_itupon_dba *obj)
{
    obj->presence_mask = 0;
    obj->implementation_type = BCMOLT_DBA_IMPLEMENTATION_TYPE_INTERNAL;
    obj->num_of_frames_per_map = BCMOLT_NUM_OF_FRAMES_PER_MAP_X_8;
    obj->external_dba_options = (bcmolt_external_dba_options)0UL;
    bcmolt_extended_dba_priority_adjustment_set_default(&obj->extended_dba_priority_adjustment);
    obj->dba_options = (bcmolt_dba_options)0;
}

bcmos_bool bcmolt_itupon_dba_validate(const bcmolt_itupon_dba *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_DBA_ID_IMPLEMENTATION_TYPE))
    {
        switch (obj->implementation_type)
        {
        case BCMOLT_DBA_IMPLEMENTATION_TYPE_INTERNAL:
        case BCMOLT_DBA_IMPLEMENTATION_TYPE_EXTERNAL:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "implementation_type: enum value %d is unexpected\n", (int)obj->implementation_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_DBA_ID_NUM_OF_FRAMES_PER_MAP))
    {
        switch (obj->num_of_frames_per_map)
        {
        case BCMOLT_NUM_OF_FRAMES_PER_MAP_X_1:
        case BCMOLT_NUM_OF_FRAMES_PER_MAP_X_2:
        case BCMOLT_NUM_OF_FRAMES_PER_MAP_X_4:
        case BCMOLT_NUM_OF_FRAMES_PER_MAP_X_8:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "num_of_frames_per_map: enum value %d is unexpected\n", (int)obj->num_of_frames_per_map);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_DBA_ID_EXTERNAL_DBA_OPTIONS))
    {
        if ((obj->external_dba_options & ~0x1UL) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "external_dba_options: 0x%X includes invalid bits\n", obj->external_dba_options);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_DBA_ID_EXTENDED_DBA_PRIORITY_ADJUSTMENT))
    {
        int prefix_len = bcmolt_string_append(err_details, "extended_dba_priority_adjustment.");
        if (!bcmolt_extended_dba_priority_adjustment_validate(&obj->extended_dba_priority_adjustment, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_DBA_ID_DBA_OPTIONS))
    {
        if ((obj->dba_options & ~0x1) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "dba_options: 0x%X includes invalid bits\n", obj->dba_options);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itu_pon_params_set_default(bcmolt_itu_pon_params *obj)
{
    obj->presence_mask = 0;
    bcmolt_pon_available_bandwidth_set_default(&obj->available_bandwidth);
    obj->ranging_window_size = 0UL;
    obj->eqd_cycles_number = 2UL;
    bcmolt_pon_drift_control_set_default(&obj->drift_control);
    obj->los_alarm_threshold = 4;
    bcmolt_ber_monitor_params_set_default(&obj->ber_monitor);
    obj->ack_timeout = 2000UL;
    bcmolt_onu_activation_set_default(&obj->onu_activation);
    bcmolt_key_exchange_set_default(&obj->key_exchange);
    obj->min_data_alloc_id = (bcmolt_alloc_id)1024U;
    bcmolt_cbr_rt_allocation_profile_set_default(&obj->cbr_rt_allocation_profile);
    bcmolt_arr_u16_2_set_default(&obj->cbr_nrt_allocation_profile);
    memset(obj->cbr_nrt_allocation_profile.arr, 0, sizeof(obj->cbr_nrt_allocation_profile.arr));
    obj->cbr_nrt_allocation_profile.arr[0] = 4096U;
    obj->cbr_nrt_allocation_profile.arr[1] = 8192U;
    bcmolt_onu_power_management_configuration_set_default(&obj->power_management);
    bcmolt_periodic_standby_pon_monitoring_set_default(&obj->periodic_standby_pon_monitoring);
    bcmolt_prbs_checker_config_set_default(&obj->prbs_checker);
    bcmolt_prbs_generator_config_set_default(&obj->prbs_generator);
    bcmolt_prbs_status_set_default(&obj->prbs_status);
    obj->prbs_status.lock_state = BCMOLT_PRBS_LOCK_STATE_UNLOCKED;
    obj->dba_mode = BCMOLT_DBA_MODE_NORMAL;
    bcmolt_itupon_protection_switching_set_default(&obj->protection_switching);
    bcmolt_automatic_onu_deactivation_set_default(&obj->automatic_onu_deactivation);
    obj->automatic_onu_deactivation.los = BCMOS_FALSE;
    obj->automatic_onu_deactivation.onu_alarms = BCMOS_FALSE;
    obj->automatic_onu_deactivation.tiwi = BCMOS_FALSE;
    obj->automatic_onu_deactivation.ack_timeout = BCMOS_FALSE;
    obj->automatic_onu_deactivation.sfi = BCMOS_FALSE;
    obj->automatic_onu_deactivation.loki = BCMOS_FALSE;
    obj->us_bandwidth_limit = 311040000UL;
    bcmolt_ituonu_upgrade_params_set_default(&obj->onu_upgrade_params);
    bcmolt_pon_onu_upgrade_status_set_default(&obj->onu_upgrade_status);
    obj->ds_fec_mode = BCMOLT_CONTROL_STATE_ENABLE;
    bcmolt_xgpon_pon_params_set_default(&obj->xgpon);
    bcmolt_gpon_pon_params_set_default(&obj->gpon);
    obj->bw_eligibility_class_stats = BCMOS_FALSE;
    bcmolt_itupon_dba_set_default(&obj->dba);
    obj->bw_eligibility_stats_clear_on_read = BCMOS_TRUE;
}

bcmos_bool bcmolt_itu_pon_params_validate(const bcmolt_itu_pon_params *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_AVAILABLE_BANDWIDTH))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "available_bandwidth: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_RANGING_WINDOW_SIZE))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "ranging_window_size: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_EQD_CYCLES_NUMBER))
    {
        if (obj->eqd_cycles_number > 255UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "eqd_cycles_number: %u is greater than the maximum value of 255\n", obj->eqd_cycles_number);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_DRIFT_CONTROL))
    {
        int prefix_len = bcmolt_string_append(err_details, "drift_control.");
        if (!bcmolt_pon_drift_control_validate(&obj->drift_control, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_LOS_ALARM_THRESHOLD))
    {
        /* obj->los_alarm_threshold can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_BER_MONITOR))
    {
        int prefix_len = bcmolt_string_append(err_details, "ber_monitor.");
        if (!bcmolt_ber_monitor_params_validate(&obj->ber_monitor, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_ACK_TIMEOUT))
    {
        /* obj->ack_timeout can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_ONU_ACTIVATION))
    {
        int prefix_len = bcmolt_string_append(err_details, "onu_activation.");
        if (!bcmolt_onu_activation_validate(&obj->onu_activation, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_KEY_EXCHANGE))
    {
        int prefix_len = bcmolt_string_append(err_details, "key_exchange.");
        if (!bcmolt_key_exchange_validate(&obj->key_exchange, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_MIN_DATA_ALLOC_ID))
    {
        if (obj->min_data_alloc_id < (bcmolt_alloc_id)256U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "min_data_alloc_id: %u is less than the minimum value of 256\n", obj->min_data_alloc_id);
            return BCMOS_FALSE;
        }
        if (obj->min_data_alloc_id > (bcmolt_alloc_id)14591U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "min_data_alloc_id: %u is greater than the maximum value of 14591\n", obj->min_data_alloc_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_CBR_RT_ALLOCATION_PROFILE))
    {
        int prefix_len = bcmolt_string_append(err_details, "cbr_rt_allocation_profile.");
        if (!bcmolt_cbr_rt_allocation_profile_validate(&obj->cbr_rt_allocation_profile, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_CBR_NRT_ALLOCATION_PROFILE))
    {
        int prefix_len = bcmolt_string_append(err_details, "cbr_nrt_allocation_profile.");
        if (!bcmolt_arr_u16_2_validate(&obj->cbr_nrt_allocation_profile, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_POWER_MANAGEMENT))
    {
        int prefix_len = bcmolt_string_append(err_details, "power_management.");
        if (!bcmolt_onu_power_management_configuration_validate(&obj->power_management, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_PERIODIC_STANDBY_PON_MONITORING))
    {
        int prefix_len = bcmolt_string_append(err_details, "periodic_standby_pon_monitoring.");
        if (!bcmolt_periodic_standby_pon_monitoring_validate(&obj->periodic_standby_pon_monitoring, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_PRBS_CHECKER))
    {
        int prefix_len = bcmolt_string_append(err_details, "prbs_checker.");
        if (!bcmolt_prbs_checker_config_validate(&obj->prbs_checker, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_PRBS_GENERATOR))
    {
        int prefix_len = bcmolt_string_append(err_details, "prbs_generator.");
        if (!bcmolt_prbs_generator_config_validate(&obj->prbs_generator, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_PRBS_STATUS))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "prbs_status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_DBA_MODE))
    {
        switch (obj->dba_mode)
        {
        case BCMOLT_DBA_MODE_NORMAL:
        case BCMOLT_DBA_MODE_EXTENDED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "dba_mode: enum value %d is unexpected\n", (int)obj->dba_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_PROTECTION_SWITCHING))
    {
        int prefix_len = bcmolt_string_append(err_details, "protection_switching.");
        if (!bcmolt_itupon_protection_switching_validate(&obj->protection_switching, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_AUTOMATIC_ONU_DEACTIVATION))
    {
        int prefix_len = bcmolt_string_append(err_details, "automatic_onu_deactivation.");
        if (!bcmolt_automatic_onu_deactivation_validate(&obj->automatic_onu_deactivation, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_US_BANDWIDTH_LIMIT))
    {
        /* obj->us_bandwidth_limit can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_ONU_UPGRADE_PARAMS))
    {
        int prefix_len = bcmolt_string_append(err_details, "onu_upgrade_params.");
        if (!bcmolt_ituonu_upgrade_params_validate(&obj->onu_upgrade_params, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_ONU_UPGRADE_STATUS))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "onu_upgrade_status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_DS_FEC_MODE))
    {
        switch (obj->ds_fec_mode)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ds_fec_mode: enum value %d is unexpected\n", (int)obj->ds_fec_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_XGPON))
    {
        int prefix_len = bcmolt_string_append(err_details, "xgpon.");
        if (!bcmolt_xgpon_pon_params_validate(&obj->xgpon, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_GPON))
    {
        int prefix_len = bcmolt_string_append(err_details, "gpon.");
        if (!bcmolt_gpon_pon_params_validate(&obj->gpon, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_BW_ELIGIBILITY_CLASS_STATS))
    {
        /* obj->bw_eligibility_class_stats can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_DBA))
    {
        int prefix_len = bcmolt_string_append(err_details, "dba.");
        if (!bcmolt_itupon_dba_validate(&obj->dba, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_PON_PARAMS_ID_BW_ELIGIBILITY_STATS_CLEAR_ON_READ))
    {
        /* obj->bw_eligibility_stats_clear_on_read can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itu_tod_set_default(bcmolt_itu_tod *obj)
{
    obj->presence_mask = 0;
    obj->tod_enable = BCMOLT_CONTROL_STATE_DISABLE;
    obj->tod_gpio_pin = BCMOLT_GPIO_PIN_UNCONFIGURED;
    obj->connected_internally = BCMOS_FALSE;
    obj->tod_string_length = 16;
}

bcmos_bool bcmolt_itu_tod_validate(const bcmolt_itu_tod *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_TOD_ID_TOD_ENABLE))
    {
        switch (obj->tod_enable)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tod_enable: enum value %d is unexpected\n", (int)obj->tod_enable);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_TOD_ID_TOD_GPIO_PIN))
    {
        switch (obj->tod_gpio_pin)
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
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tod_gpio_pin: enum value %d is unexpected\n", (int)obj->tod_gpio_pin);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_TOD_ID_CONNECTED_INTERNALLY))
    {
        /* obj->connected_internally can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITU_TOD_ID_TOD_STRING_LENGTH))
    {
        if (obj->tod_string_length > 64)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tod_string_length: %u is greater than the maximum value of 64\n", obj->tod_string_length);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_onu_eqd_set_default(bcmolt_itupon_onu_eqd *obj)
{
    obj->presence_mask = 0;
    obj->onu_id = (bcmolt_onu_id)0U;
    obj->eqd = 0UL;
}

bcmos_bool bcmolt_itupon_onu_eqd_validate(const bcmolt_itupon_onu_eqd *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_ONU_EQD_ID_ONU_ID))
    {
        /* obj->onu_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_ITUPON_ONU_EQD_ID_EQD))
    {
        /* obj->eqd can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_itupon_onu_eqd_list_u32_set_default(bcmolt_itupon_onu_eqd_list_u32 *obj)
{
    obj->len = 0UL;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_itupon_onu_eqd_list_u32_validate(const bcmolt_itupon_onu_eqd_list_u32 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->len can't be invalid. */
    for (uint32_t i = 0; i < obj->len; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_itupon_onu_eqd_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_dump_filters_set_default(bcmolt_l2_dump_filters *obj)
{
    obj->presence_mask = 0;
    obj->o_vid = (bcmolt_vlan_id)0U;
    obj->i_vid = (bcmolt_vlan_id)0U;
    bcmolt_intf_ref_set_default(&obj->interface);
    bcmos_mac_address_init(&obj->mac_address);
    bcmos_mac_address_init(&obj->mac_address_mask);
    obj->domain = (bcmolt_l2_event_report_control)0U;
    obj->pkt_tag_type = (bcmolt_pkt_tag_type)0UL;
    obj->svc_port_id = (bcmolt_service_port_id)0UL;
}

bcmos_bool bcmolt_l2_dump_filters_validate(const bcmolt_l2_dump_filters *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_DUMP_FILTERS_ID_O_VID))
    {
        /* obj->o_vid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_DUMP_FILTERS_ID_I_VID))
    {
        /* obj->i_vid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_DUMP_FILTERS_ID_INTERFACE))
    {
        int prefix_len = bcmolt_string_append(err_details, "interface.");
        if (!bcmolt_intf_ref_validate(&obj->interface, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_DUMP_FILTERS_ID_MAC_ADDRESS))
    {
        /* obj->mac_address can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_DUMP_FILTERS_ID_MAC_ADDRESS_MASK))
    {
        /* obj->mac_address_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_DUMP_FILTERS_ID_DOMAIN))
    {
        if ((obj->domain & ~0x3) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "domain: 0x%X includes invalid bits\n", obj->domain);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_DUMP_FILTERS_ID_PKT_TAG_TYPE))
    {
        if ((obj->pkt_tag_type & ~0x1FUL) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "pkt_tag_type: 0x%X includes invalid bits\n", obj->pkt_tag_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_DUMP_FILTERS_ID_SVC_PORT_ID))
    {
        if (obj->svc_port_id > (bcmolt_service_port_id)65536UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "svc_port_id: %u is greater than the maximum value of 65536\n", obj->svc_port_id);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_mact_entry_set_default(bcmolt_l2_mact_entry *obj)
{
    obj->presence_mask = 0;
    obj->pkt_tag_type = (bcmolt_pkt_tag_type)0UL;
    obj->o_vid = (bcmolt_vlan_id)0U;
    obj->i_vid = (bcmolt_vlan_id)0U;
    bcmolt_intf_ref_set_default(&obj->interface);
    obj->svc_port_id = (bcmolt_service_port_id)0UL;
    bcmos_mac_address_init(&obj->mac_address);
    obj->event_type = (bcmolt_l2_event)0;
    obj->is_static = BCMOS_FALSE;
}

bcmos_bool bcmolt_l2_mact_entry_validate(const bcmolt_l2_mact_entry *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_MACT_ENTRY_ID_PKT_TAG_TYPE))
    {
        if ((obj->pkt_tag_type & ~0x1FUL) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "pkt_tag_type: 0x%X includes invalid bits\n", obj->pkt_tag_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_MACT_ENTRY_ID_O_VID))
    {
        /* obj->o_vid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_MACT_ENTRY_ID_I_VID))
    {
        /* obj->i_vid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_MACT_ENTRY_ID_INTERFACE))
    {
        int prefix_len = bcmolt_string_append(err_details, "interface.");
        if (!bcmolt_intf_ref_validate(&obj->interface, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_MACT_ENTRY_ID_SVC_PORT_ID))
    {
        if (obj->svc_port_id > (bcmolt_service_port_id)65536UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "svc_port_id: %u is greater than the maximum value of 65536\n", obj->svc_port_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_MACT_ENTRY_ID_MAC_ADDRESS))
    {
        /* obj->mac_address can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_MACT_ENTRY_ID_EVENT_TYPE))
    {
        switch (obj->event_type)
        {
        case BCMOLT_L2_EVENT_DUMPED:
        case BCMOLT_L2_EVENT_LEARNED:
        case BCMOLT_L2_EVENT_AGED:
        case BCMOLT_L2_EVENT_MOVED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "event_type: enum value %d is unexpected\n", (int)obj->event_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_L2_MACT_ENTRY_ID_IS_STATIC))
    {
        /* obj->is_static can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_l2_mact_entry_list_u32_set_default(bcmolt_l2_mact_entry_list_u32 *obj)
{
    obj->len = 0UL;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_l2_mact_entry_list_u32_validate(const bcmolt_l2_mact_entry_list_u32 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->len can't be invalid. */
    for (uint32_t i = 0; i < obj->len; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_l2_mact_entry_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_global_parms_set_default(bcmolt_lag_global_parms *obj)
{
    obj->presence_mask = 0;
    obj->polynomial = BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X8003;
    obj->hash_field = (bcmolt_lag_hash_field_flags)7UL;
}

bcmos_bool bcmolt_lag_global_parms_validate(const bcmolt_lag_global_parms *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LAG_GLOBAL_PARMS_ID_POLYNOMIAL))
    {
        switch (obj->polynomial)
        {
        case BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X8003:
        case BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X8101:
        case BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X84A1:
        case BCMOLT_LAG_HASH_POLYNOMIAL_CRC16_0X9019:
        case BCMOLT_LAG_HASH_POLYNOMIAL_CRC_16_0X100D7:
        case BCMOLT_LAG_HASH_POLYNOMIAL_CRC_16_0X10AC5:
        case BCMOLT_LAG_HASH_POLYNOMIAL_CRC_16_0X12105:
        case BCMOLT_LAG_HASH_POLYNOMIAL_CRC_16_0X1203D:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "polynomial: enum value %d is unexpected\n", (int)obj->polynomial);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LAG_GLOBAL_PARMS_ID_HASH_FIELD))
    {
        if ((obj->hash_field & ~0x7FFUL) != 0)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "hash_field: 0x%X includes invalid bits\n", obj->hash_field);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_lag_interface_members_update_command_set_default(bcmolt_lag_interface_members_update_command *obj)
{
    obj->presence_mask = 0;
    obj->command = BCMOLT_MEMBERS_UPDATE_COMMAND_ADD;
    bcmolt_arr_nni_id_8_set_default(&obj->nni_ids);
    memset(obj->nni_ids.arr, 0, sizeof(obj->nni_ids.arr));
    obj->nni_ids.arr[0] = (bcmolt_nni_id)255;
    obj->nni_ids.arr[1] = (bcmolt_nni_id)255;
    obj->nni_ids.arr[2] = (bcmolt_nni_id)255;
    obj->nni_ids.arr[3] = (bcmolt_nni_id)255;
    obj->nni_ids.arr[4] = (bcmolt_nni_id)255;
    obj->nni_ids.arr[5] = (bcmolt_nni_id)255;
    obj->nni_ids.arr[6] = (bcmolt_nni_id)255;
    obj->nni_ids.arr[7] = (bcmolt_nni_id)255;
}

bcmos_bool bcmolt_lag_interface_members_update_command_validate(const bcmolt_lag_interface_members_update_command *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID_COMMAND))
    {
        switch (obj->command)
        {
        case BCMOLT_MEMBERS_UPDATE_COMMAND_ADD:
        case BCMOLT_MEMBERS_UPDATE_COMMAND_REMOVE:
        case BCMOLT_MEMBERS_UPDATE_COMMAND_SET:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "command: enum value %d is unexpected\n", (int)obj->command);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LAG_INTERFACE_MEMBERS_UPDATE_COMMAND_ID_NNI_IDS))
    {
        int prefix_len = bcmolt_string_append(err_details, "nni_ids.");
        if (!bcmolt_arr_nni_id_8_validate(&obj->nni_ids, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_local_mep_set_default(bcmolt_local_mep *obj)
{
    obj->presence_mask = 0;
    obj->id = (bcmolt_mep_id)65535U;
    obj->interval = BCMOLT_CCM_INTERVAL_RATE_100_MS;
    obj->state = BCMOLT_CONTROL_STATE_DISABLE;
}

bcmos_bool bcmolt_local_mep_validate(const bcmolt_local_mep *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOCAL_MEP_ID_ID))
    {
        if (obj->id > (bcmolt_mep_id)8191U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "id: %u is greater than the maximum value of 8191\n", obj->id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOCAL_MEP_ID_INTERVAL))
    {
        switch (obj->interval)
        {
        case BCMOLT_CCM_INTERVAL_RATE_3_3MS:
        case BCMOLT_CCM_INTERVAL_RATE_10_MS:
        case BCMOLT_CCM_INTERVAL_RATE_100_MS:
        case BCMOLT_CCM_INTERVAL_RATE_1_SEC:
        case BCMOLT_CCM_INTERVAL_RATE_10_SEC:
        case BCMOLT_CCM_INTERVAL_RATE_60_SEC:
        case BCMOLT_CCM_INTERVAL_RATE_600_SEC:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "interval: enum value %d is unexpected\n", (int)obj->interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOCAL_MEP_ID_STATE))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_log_level_msg_count_set_default(bcmolt_log_level_msg_count *obj)
{
    obj->presence_mask = 0;
    obj->no_log = 0UL;
    obj->fatal = 0UL;
    obj->error = 0UL;
    obj->warning = 0UL;
    obj->info = 0UL;
    obj->debug = 0UL;
}

bcmos_bool bcmolt_log_level_msg_count_validate(const bcmolt_log_level_msg_count *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOG_LEVEL_MSG_COUNT_ID_NO_LOG))
    {
        /* obj->no_log can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOG_LEVEL_MSG_COUNT_ID_FATAL))
    {
        /* obj->fatal can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOG_LEVEL_MSG_COUNT_ID_ERROR))
    {
        /* obj->error can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOG_LEVEL_MSG_COUNT_ID_WARNING))
    {
        /* obj->warning can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOG_LEVEL_MSG_COUNT_ID_INFO))
    {
        /* obj->info can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOG_LEVEL_MSG_COUNT_ID_DEBUG))
    {
        /* obj->debug can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_log_level_per_file_set_default(bcmolt_log_level_per_file *obj)
{
    obj->presence_mask = 0;
    obj->print = BCMOLT_LOG_LEVEL_NO_LOG;
    obj->save = BCMOLT_LOG_LEVEL_NO_LOG;
}

bcmos_bool bcmolt_log_level_per_file_validate(const bcmolt_log_level_per_file *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOG_LEVEL_PER_FILE_ID_PRINT))
    {
        switch (obj->print)
        {
        case BCMOLT_LOG_LEVEL_NO_LOG:
        case BCMOLT_LOG_LEVEL_FATAL:
        case BCMOLT_LOG_LEVEL_ERROR:
        case BCMOLT_LOG_LEVEL_WARNING:
        case BCMOLT_LOG_LEVEL_INFO:
        case BCMOLT_LOG_LEVEL_DEBUG:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "print: enum value %d is unexpected\n", (int)obj->print);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_LOG_LEVEL_PER_FILE_ID_SAVE))
    {
        switch (obj->save)
        {
        case BCMOLT_LOG_LEVEL_NO_LOG:
        case BCMOLT_LOG_LEVEL_FATAL:
        case BCMOLT_LOG_LEVEL_ERROR:
        case BCMOLT_LOG_LEVEL_WARNING:
        case BCMOLT_LOG_LEVEL_INFO:
        case BCMOLT_LOG_LEVEL_DEBUG:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "save: enum value %d is unexpected\n", (int)obj->save);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_str_48_set_default(bcmolt_str_48 *obj)
{
    memset(obj->str, 0, 48);
}

bcmos_bool bcmolt_str_48_validate(const bcmolt_str_48 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->str can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_meg_cfg_set_default(bcmolt_meg_cfg *obj)
{
    obj->presence_mask = 0;
    bcmolt_str_48_set_default(&obj->name);
    obj->format = BCMOLT_MEG_FORMAT_ICC;
    obj->level = BCMOLT_MEG_LEVEL_LEVEL_2;
}

bcmos_bool bcmolt_meg_cfg_validate(const bcmolt_meg_cfg *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_MEG_CFG_ID_NAME))
    {
        int prefix_len = bcmolt_string_append(err_details, "name.");
        if (!bcmolt_str_48_validate(&obj->name, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_MEG_CFG_ID_FORMAT))
    {
        switch (obj->format)
        {
        case BCMOLT_MEG_FORMAT_IEEE_8021_AG_1:
        case BCMOLT_MEG_FORMAT_IEEE_8021_AG_2:
        case BCMOLT_MEG_FORMAT_ICC:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "format: enum value %d is unexpected\n", (int)obj->format);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_MEG_CFG_ID_LEVEL))
    {
        switch (obj->level)
        {
        case BCMOLT_MEG_LEVEL_LEVEL_0:
        case BCMOLT_MEG_LEVEL_LEVEL_1:
        case BCMOLT_MEG_LEVEL_LEVEL_2:
        case BCMOLT_MEG_LEVEL_LEVEL_3:
        case BCMOLT_MEG_LEVEL_LEVEL_4:
        case BCMOLT_MEG_LEVEL_LEVEL_5:
        case BCMOLT_MEG_LEVEL_LEVEL_6:
        case BCMOLT_MEG_LEVEL_LEVEL_7:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "level: enum value %d is unexpected\n", (int)obj->level);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_mirror_action_set_default(bcmolt_mirror_action *obj)
{
    obj->presence_mask = 0;
    bcmolt_intf_ref_set_default(&obj->mirror_dest_intf);
}

bcmos_bool bcmolt_mirror_action_validate(const bcmolt_mirror_action *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_MIRROR_ACTION_ID_MIRROR_DEST_INTF))
    {
        int prefix_len = bcmolt_string_append(err_details, "mirror_dest_intf.");
        if (!bcmolt_intf_ref_validate(&obj->mirror_dest_intf, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_nni_link_status_set_default(bcmolt_nni_link_status *obj)
{
    obj->presence_mask = 0;
    obj->link_status = BCMOLT_TRIVALENT_FALSE;
    obj->signal_detected = BCMOLT_TRIVALENT_FALSE;
    obj->pmd_locked = BCMOLT_TRIVALENT_FALSE;
}

bcmos_bool bcmolt_nni_link_status_validate(const bcmolt_nni_link_status *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NNI_LINK_STATUS_ID_LINK_STATUS))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "link_status: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NNI_LINK_STATUS_ID_SIGNAL_DETECTED))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "signal_detected: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_NNI_LINK_STATUS_ID_PMD_LOCKED))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "pmd_locked: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_onu_id_list_u32_set_default(bcmolt_onu_id_list_u32 *obj)
{
    obj->len = 0UL;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_onu_id_list_u32_validate(const bcmolt_onu_id_list_u32 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->len can't be invalid. */
    for (uint32_t i = 0; i < obj->len; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
        }
    }
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_pcie_conn_data_set_default(bcmolt_pcie_conn_data *obj)
{
    obj->presence_mask = 0;
    obj->host_dma_rx_queue_size = 128U;
    obj->host_dma_tx_queue_size = 128U;
    obj->mtu = (bcmolt_mtu)4096UL;
    obj->avs_control = BCMOS_FALSE;
    obj->debug_trace = BCMOS_FALSE;
}

bcmos_bool bcmolt_pcie_conn_data_validate(const bcmolt_pcie_conn_data *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PCIE_CONN_DATA_ID_HOST_DMA_RX_QUEUE_SIZE))
    {
        /* obj->host_dma_rx_queue_size can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PCIE_CONN_DATA_ID_HOST_DMA_TX_QUEUE_SIZE))
    {
        /* obj->host_dma_tx_queue_size can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PCIE_CONN_DATA_ID_MTU))
    {
        if (obj->mtu < (bcmolt_mtu)4096UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "mtu: %u is less than the minimum value of 4096\n", obj->mtu);
            return BCMOS_FALSE;
        }
        if (obj->mtu > (bcmolt_mtu)16384UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "mtu: %u is greater than the maximum value of 16384\n", obj->mtu);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PCIE_CONN_DATA_ID_AVS_CONTROL))
    {
        /* obj->avs_control can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PCIE_CONN_DATA_ID_DEBUG_TRACE))
    {
        /* obj->debug_trace can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_policer_action_set_default(bcmolt_policer_action *obj)
{
    obj->presence_mask = 0;
    obj->state = BCMOLT_CONFIG_STATE_NOT_CONFIGURED;
    bcmolt_arr_policer_ref_4_set_default(&obj->policer_ref);
}

bcmos_bool bcmolt_policer_action_validate(const bcmolt_policer_action *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_POLICER_ACTION_ID_STATE))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_POLICER_ACTION_ID_POLICER_REF))
    {
        int prefix_len = bcmolt_string_append(err_details, "policer_ref.");
        if (!bcmolt_arr_policer_ref_4_validate(&obj->policer_ref, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_alloc_sla_set_default(bcmolt_pon_alloc_sla *obj)
{
    obj->presence_mask = 0;
    obj->cbr_rt_bw = 0UL;
    obj->cbr_nrt_bw = 0UL;
    obj->guaranteed_bw = 0UL;
    obj->maximum_bw = 0UL;
    obj->additional_bw_eligibility = BCMOLT_ADDITIONAL_BW_ELIGIBILITY_NONE;
    obj->cbr_rt_compensation = BCMOS_FALSE;
    obj->cbr_rt_ap_index = 0;
    obj->cbr_nrt_ap_index = 0;
    obj->alloc_type = BCMOLT_ALLOC_TYPE_NONE;
    obj->weight = 0;
    obj->priority = 0;
}

bcmos_bool bcmolt_pon_alloc_sla_validate(const bcmolt_pon_alloc_sla *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_CBR_RT_BW))
    {
        /* obj->cbr_rt_bw can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_CBR_NRT_BW))
    {
        /* obj->cbr_nrt_bw can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_GUARANTEED_BW))
    {
        /* obj->guaranteed_bw can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_MAXIMUM_BW))
    {
        /* obj->maximum_bw can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_ADDITIONAL_BW_ELIGIBILITY))
    {
        switch (obj->additional_bw_eligibility)
        {
        case BCMOLT_ADDITIONAL_BW_ELIGIBILITY_NONE:
        case BCMOLT_ADDITIONAL_BW_ELIGIBILITY_NON_ASSURED:
        case BCMOLT_ADDITIONAL_BW_ELIGIBILITY_BEST_EFFORT:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "additional_bw_eligibility: enum value %d is unexpected\n", (int)obj->additional_bw_eligibility);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_CBR_RT_COMPENSATION))
    {
        /* obj->cbr_rt_compensation can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_CBR_RT_AP_INDEX))
    {
        if (obj->cbr_rt_ap_index > 32)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "cbr_rt_ap_index: %u is greater than the maximum value of 32\n", obj->cbr_rt_ap_index);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_CBR_NRT_AP_INDEX))
    {
        if (obj->cbr_nrt_ap_index > 1)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "cbr_nrt_ap_index: %u is greater than the maximum value of 1\n", obj->cbr_nrt_ap_index);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_ALLOC_TYPE))
    {
        switch (obj->alloc_type)
        {
        case BCMOLT_ALLOC_TYPE_NONE:
        case BCMOLT_ALLOC_TYPE_NSR:
        case BCMOLT_ALLOC_TYPE_SR:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "alloc_type: enum value %d is unexpected\n", (int)obj->alloc_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_WEIGHT))
    {
        if (obj->weight > 100)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "weight: %u is greater than the maximum value of 100\n", obj->weight);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_ALLOC_SLA_ID_PRIORITY))
    {
        if (obj->priority > 7)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "priority: %u is greater than the maximum value of 7\n", obj->priority);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_pon_distance_set_default(bcmolt_pon_distance *obj)
{
    obj->presence_mask = 0;
    obj->max_log_distance = 20UL;
    obj->max_diff_reach = 20UL;
}

bcmos_bool bcmolt_pon_distance_validate(const bcmolt_pon_distance *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_DISTANCE_ID_MAX_LOG_DISTANCE))
    {
        if (obj->max_log_distance < 1UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "max_log_distance: %u is less than the minimum value of 1\n", obj->max_log_distance);
            return BCMOS_FALSE;
        }
        if (obj->max_log_distance > 100UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "max_log_distance: %u is greater than the maximum value of 100\n", obj->max_log_distance);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PON_DISTANCE_ID_MAX_DIFF_REACH))
    {
        if (obj->max_diff_reach < 1UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "max_diff_reach: %u is less than the minimum value of 1\n", obj->max_diff_reach);
            return BCMOS_FALSE;
        }
        if (obj->max_diff_reach > 65UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "max_diff_reach: %u is greater than the maximum value of 65\n", obj->max_diff_reach);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_protection_type_set_default(bcmolt_protection_type *obj)
{
    obj->presence_mask = 0;
    obj->mode = BCMOLT_NNI_PROTECTION_MODE_UNASSIGNED;
}

bcmos_bool bcmolt_protection_type_validate(const bcmolt_protection_type *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_PROTECTION_TYPE_ID_MODE))
    {
        switch (obj->mode)
        {
        case BCMOLT_NNI_PROTECTION_MODE_UNASSIGNED:
        case BCMOLT_NNI_PROTECTION_MODE_ERPS:
        case BCMOLT_NNI_PROTECTION_MODE_NNI:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "mode: enum value %d is unexpected\n", (int)obj->mode);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_remote_mep_set_default(bcmolt_remote_mep *obj)
{
    obj->presence_mask = 0;
    obj->id = (bcmolt_mep_id)65535U;
    obj->loc_clear_threshold = BCMOLT_LOC_CLEAR_THRESHOLD_CCM_INTERVAL_TIMES_2;
    obj->state = BCMOLT_CONTROL_STATE_ENABLE;
}

bcmos_bool bcmolt_remote_mep_validate(const bcmolt_remote_mep *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_REMOTE_MEP_ID_ID))
    {
        if (obj->id > (bcmolt_mep_id)8191U)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "id: %u is greater than the maximum value of 8191\n", obj->id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_REMOTE_MEP_ID_LOC_CLEAR_THRESHOLD))
    {
        switch (obj->loc_clear_threshold)
        {
        case BCMOLT_LOC_CLEAR_THRESHOLD_CCM_INTERVAL:
        case BCMOLT_LOC_CLEAR_THRESHOLD_CCM_INTERVAL_TIMES_2:
        case BCMOLT_LOC_CLEAR_THRESHOLD_CCM_INTERVAL_TIMES_3:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "loc_clear_threshold: enum value %d is unexpected\n", (int)obj->loc_clear_threshold);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_REMOTE_MEP_ID_STATE))
    {
        *err = BCM_ERR_READ_ONLY;
        bcmolt_string_append(err_details, "state: field is read-only and cannot be set\n");
        return BCMOS_FALSE;
    }
    return BCMOS_TRUE;
}

void bcmolt_ring_port_detailed_state_set_default(bcmolt_ring_port_detailed_state *obj)
{
    obj->presence_mask = 0;
    obj->rx_state = BCMOLT_RING_PORT_STATE_UNASSIGNED;
    obj->tx_state = BCMOLT_RING_PORT_STATE_UNASSIGNED;
}

bcmos_bool bcmolt_ring_port_detailed_state_validate(const bcmolt_ring_port_detailed_state *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_RING_PORT_DETAILED_STATE_ID_RX_STATE))
    {
        switch (obj->rx_state)
        {
        case BCMOLT_RING_PORT_STATE_UNASSIGNED:
        case BCMOLT_RING_PORT_STATE_BLOCKED:
        case BCMOLT_RING_PORT_STATE_UNBLOCKED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "rx_state: enum value %d is unexpected\n", (int)obj->rx_state);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_RING_PORT_DETAILED_STATE_ID_TX_STATE))
    {
        switch (obj->tx_state)
        {
        case BCMOLT_RING_PORT_STATE_UNASSIGNED:
        case BCMOLT_RING_PORT_STATE_BLOCKED:
        case BCMOLT_RING_PORT_STATE_UNBLOCKED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "tx_state: enum value %d is unexpected\n", (int)obj->tx_state);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_rssi_measurement_result_set_default(bcmolt_rssi_measurement_result *obj)
{
    obj->presence_mask = 0;
    obj->rssi_done = BCMOS_FALSE;
    obj->error = BCMOS_FALSE;
}

bcmos_bool bcmolt_rssi_measurement_result_validate(const bcmolt_rssi_measurement_result *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_RSSI_MEASUREMENT_RESULT_ID_RSSI_DONE))
    {
        /* obj->rssi_done can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_RSSI_MEASUREMENT_RESULT_ID_ERROR))
    {
        /* obj->error can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_service_discovery_set_default(bcmolt_service_discovery *obj)
{
    obj->presence_mask = 0;
    obj->interval = 1000UL;
    obj->control = BCMOLT_CONTROL_STATE_DISABLE;
    obj->onu_post_discovery_mode = BCMOLT_ONU_POST_DISCOVERY_MODE_NONE;
    obj->burst_profile = (bcmolt_burst_profile_index)0;
}

bcmos_bool bcmolt_service_discovery_validate(const bcmolt_service_discovery *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SERVICE_DISCOVERY_ID_INTERVAL))
    {
        if (obj->interval < 1000UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "interval: %u is less than the minimum value of 1000\n", obj->interval);
            return BCMOS_FALSE;
        }
        if (obj->interval > 2147483UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "interval: %u is greater than the maximum value of 2147483\n", obj->interval);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SERVICE_DISCOVERY_ID_CONTROL))
    {
        switch (obj->control)
        {
        case BCMOLT_CONTROL_STATE_DISABLE:
        case BCMOLT_CONTROL_STATE_ENABLE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "control: enum value %d is unexpected\n", (int)obj->control);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SERVICE_DISCOVERY_ID_ONU_POST_DISCOVERY_MODE))
    {
        switch (obj->onu_post_discovery_mode)
        {
        case BCMOLT_ONU_POST_DISCOVERY_MODE_NONE:
        case BCMOLT_ONU_POST_DISCOVERY_MODE_ACTIVATE:
        case BCMOLT_ONU_POST_DISCOVERY_MODE_DISABLE:
        case BCMOLT_ONU_POST_DISCOVERY_MODE_PROVISION_AND_ACTIVATE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "onu_post_discovery_mode: enum value %d is unexpected\n", (int)obj->onu_post_discovery_mode);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SERVICE_DISCOVERY_ID_BURST_PROFILE))
    {
        if (obj->burst_profile > (bcmolt_burst_profile_index)3)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "burst_profile: %u is greater than the maximum value of 3\n", obj->burst_profile);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_stat_alarm_trigger_config_set_default(bcmolt_stat_alarm_trigger_config *obj)
{
    obj->presence_mask = 0;
    obj->type = BCMOLT_STAT_CONDITION_TYPE_NONE;
    obj->u.none.presence_mask = 0;
}

void bcmolt_stat_alarm_trigger_config_set_union_default(bcmolt_stat_alarm_trigger_config *obj, bcmolt_stat_condition_type type)
{
    obj->type = type;
    switch (type)
    {
    case BCMOLT_STAT_CONDITION_TYPE_RATE_THRESHOLD:
        obj->u.rate_threshold.presence_mask = 0;
        obj->u.rate_threshold.rising = 0ULL;
        obj->u.rate_threshold.falling = 0ULL;
        break;
    case BCMOLT_STAT_CONDITION_TYPE_RATE_RANGE:
        obj->u.rate_range.presence_mask = 0;
        obj->u.rate_range.upper = 0ULL;
        obj->u.rate_range.lower = 0ULL;
        break;
    case BCMOLT_STAT_CONDITION_TYPE_VALUE_THRESHOLD:
        obj->u.value_threshold.presence_mask = 0;
        obj->u.value_threshold.limit = 0ULL;
        break;
    case BCMOLT_STAT_CONDITION_TYPE_NONE:
        obj->u.none.presence_mask = 0;
        break;
    default:
        break;
    }
}

bcmos_bool bcmolt_stat_alarm_trigger_config_validate(const bcmolt_stat_alarm_trigger_config *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_STAT_ALARM_TRIGGER_CONFIG_ID_TYPE))
    {
        switch (obj->type)
        {
        case BCMOLT_STAT_CONDITION_TYPE_NONE:
        case BCMOLT_STAT_CONDITION_TYPE_RATE_THRESHOLD:
        case BCMOLT_STAT_CONDITION_TYPE_RATE_RANGE:
        case BCMOLT_STAT_CONDITION_TYPE_VALUE_THRESHOLD:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "type: enum value %d is unexpected\n", (int)obj->type);
            return BCMOS_FALSE;
        }
    }
    switch (obj->type)
    {
    case BCMOLT_STAT_CONDITION_TYPE_RATE_THRESHOLD:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.rate_threshold.presence_mask, BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID_RISING))
        {
            /* obj->u.rate_threshold.rising can't be invalid. */
        }
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.rate_threshold.presence_mask, BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_THRESHOLD_ID_FALLING))
        {
            /* obj->u.rate_threshold.falling can't be invalid. */
        }
        break;
    }
    case BCMOLT_STAT_CONDITION_TYPE_RATE_RANGE:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.rate_range.presence_mask, BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID_UPPER))
        {
            /* obj->u.rate_range.upper can't be invalid. */
        }
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.rate_range.presence_mask, BCMOLT_STAT_ALARM_TRIGGER_CONFIG_RATE_RANGE_ID_LOWER))
        {
            /* obj->u.rate_range.lower can't be invalid. */
        }
        break;
    }
    case BCMOLT_STAT_CONDITION_TYPE_VALUE_THRESHOLD:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.value_threshold.presence_mask, BCMOLT_STAT_ALARM_TRIGGER_CONFIG_VALUE_THRESHOLD_ID_LIMIT))
        {
            /* obj->u.value_threshold.limit can't be invalid. */
        }
        break;
    }
    case BCMOLT_STAT_CONDITION_TYPE_NONE:
    {
        break;
    }
    default:
    {
        break;
    }
    }
    return BCMOS_TRUE;
}

void bcmolt_stat_alarm_soak_config_set_default(bcmolt_stat_alarm_soak_config *obj)
{
    obj->presence_mask = 0;
    obj->active_soak_time = 0UL;
    obj->clear_soak_time = 0UL;
}

bcmos_bool bcmolt_stat_alarm_soak_config_validate(const bcmolt_stat_alarm_soak_config *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_STAT_ALARM_SOAK_CONFIG_ID_ACTIVE_SOAK_TIME))
    {
        /* obj->active_soak_time can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_STAT_ALARM_SOAK_CONFIG_ID_CLEAR_SOAK_TIME))
    {
        /* obj->clear_soak_time can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_stat_alarm_config_set_default(bcmolt_stat_alarm_config *obj)
{
    obj->presence_mask = 0;
    bcmolt_stat_alarm_trigger_config_set_default(&obj->trigger);
    bcmolt_stat_alarm_soak_config_set_default(&obj->soak);
}

bcmos_bool bcmolt_stat_alarm_config_validate(const bcmolt_stat_alarm_config *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_STAT_ALARM_CONFIG_ID_TRIGGER))
    {
        int prefix_len = bcmolt_string_append(err_details, "trigger.");
        if (!bcmolt_stat_alarm_trigger_config_validate(&obj->trigger, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_STAT_ALARM_CONFIG_ID_SOAK))
    {
        int prefix_len = bcmolt_string_append(err_details, "soak.");
        if (!bcmolt_stat_alarm_soak_config_validate(&obj->soak, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_str_128_set_default(bcmolt_str_128 *obj)
{
    memset(obj->str, 0, 128);
}

bcmos_bool bcmolt_str_128_validate(const bcmolt_str_128 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->str can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_str_16_set_default(bcmolt_str_16 *obj)
{
    memset(obj->str, 0, 16);
}

bcmos_bool bcmolt_str_16_validate(const bcmolt_str_16 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->str can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_str_2000_set_default(bcmolt_str_2000 *obj)
{
    memset(obj->str, 0, 2000);
}

bcmos_bool bcmolt_str_2000_validate(const bcmolt_str_2000 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->str can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_str_2048_set_default(bcmolt_str_2048 *obj)
{
    memset(obj->str, 0, 2048);
}

bcmos_bool bcmolt_str_2048_validate(const bcmolt_str_2048 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->str can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_sw_error_set_default(bcmolt_sw_error *obj)
{
    obj->presence_mask = 0;
    obj->first_error_time_us = 0ULL;
    obj->last_error_time_us = 0ULL;
    obj->line_number = 0UL;
    obj->error_counter = 0UL;
    obj->instance = 0UL;
    bcmolt_str_64_set_default(&obj->filename);
    bcmolt_str_64_set_default(&obj->task_name);
}

bcmos_bool bcmolt_sw_error_validate(const bcmolt_sw_error *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SW_ERROR_ID_FIRST_ERROR_TIME_US))
    {
        /* obj->first_error_time_us can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SW_ERROR_ID_LAST_ERROR_TIME_US))
    {
        /* obj->last_error_time_us can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SW_ERROR_ID_LINE_NUMBER))
    {
        /* obj->line_number can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SW_ERROR_ID_ERROR_COUNTER))
    {
        /* obj->error_counter can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SW_ERROR_ID_INSTANCE))
    {
        /* obj->instance can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SW_ERROR_ID_FILENAME))
    {
        int prefix_len = bcmolt_string_append(err_details, "filename.");
        if (!bcmolt_str_64_validate(&obj->filename, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SW_ERROR_ID_TASK_NAME))
    {
        int prefix_len = bcmolt_string_append(err_details, "task_name.");
        if (!bcmolt_str_64_validate(&obj->task_name, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_system_profile_set_default(bcmolt_system_profile *obj)
{
    obj->presence_mask = 0;
    obj->ng_2_sys_id = 0UL;
    obj->version = 0;
    obj->channel_spacing = 100;
    obj->us_operating_wavelength_bands = BCMOLT_US_OPERATING_WAVELENGTH_BANDS_EXPANDED_SPECTRUM_WIDE_BAND;
    obj->us_mse = 20;
    obj->loose_calibration_bound = 0;
    obj->fsr = 0U;
    obj->twdm_channel_count = 8;
}

bcmos_bool bcmolt_system_profile_validate(const bcmolt_system_profile *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SYSTEM_PROFILE_ID_NG_2_SYS_ID))
    {
        if (obj->ng_2_sys_id > 1048575UL)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "ng_2_sys_id: %u is greater than the maximum value of 1048575\n", obj->ng_2_sys_id);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SYSTEM_PROFILE_ID_VERSION))
    {
        if (obj->version > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "version: %u is greater than the maximum value of 15\n", obj->version);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SYSTEM_PROFILE_ID_CHANNEL_SPACING))
    {
        if (obj->channel_spacing < 50)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "channel_spacing: %u is less than the minimum value of 50\n", obj->channel_spacing);
            return BCMOS_FALSE;
        }
        if (obj->channel_spacing > 200)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "channel_spacing: %u is greater than the maximum value of 200\n", obj->channel_spacing);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SYSTEM_PROFILE_ID_US_OPERATING_WAVELENGTH_BANDS))
    {
        switch (obj->us_operating_wavelength_bands)
        {
        case BCMOLT_US_OPERATING_WAVELENGTH_BANDS_EXPANDED_SPECTRUM_WIDE_BAND:
        case BCMOLT_US_OPERATING_WAVELENGTH_BANDS_EXPANDED_SPECTRUM_REDUCED_BAND:
        case BCMOLT_US_OPERATING_WAVELENGTH_BANDS_EXPANDED_SPECTRUM_NARROW_BAND:
        case BCMOLT_US_OPERATING_WAVELENGTH_BANDS_SHARED_SPECTRUM_WIDE_BAND:
        case BCMOLT_US_OPERATING_WAVELENGTH_BANDS_SHARED_SPECTRUM_REDUCED_BAND:
        case BCMOLT_US_OPERATING_WAVELENGTH_BANDS_SHARED_SPECTRUM_NARROW_BAND:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "us_operating_wavelength_bands: enum value %d is unexpected\n", (int)obj->us_operating_wavelength_bands);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SYSTEM_PROFILE_ID_US_MSE))
    {
        if (obj->us_mse < 12)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "us_mse: %u is less than the minimum value of 12\n", obj->us_mse);
            return BCMOS_FALSE;
        }
        if (obj->us_mse > 25)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "us_mse: %u is greater than the maximum value of 25\n", obj->us_mse);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SYSTEM_PROFILE_ID_LOOSE_CALIBRATION_BOUND))
    {
        /* obj->loose_calibration_bound can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SYSTEM_PROFILE_ID_FSR))
    {
        /* obj->fsr can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_SYSTEM_PROFILE_ID_TWDM_CHANNEL_COUNT))
    {
        if (obj->twdm_channel_count > 15)
        {
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "twdm_channel_count: %u is greater than the maximum value of 15\n", obj->twdm_channel_count);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_sched_param_set_default(bcmolt_tm_sched_param *obj)
{
    obj->presence_mask = 0;
    obj->type = BCMOLT_TM_SCHED_PARAM_TYPE_UNDEFINED;
}

void bcmolt_tm_sched_param_set_union_default(bcmolt_tm_sched_param *obj, bcmolt_tm_sched_param_type type)
{
    obj->type = type;
    switch (type)
    {
    case BCMOLT_TM_SCHED_PARAM_TYPE_PRIORITY:
        obj->u.priority.presence_mask = 0;
        obj->u.priority.priority = (bcmolt_tm_priority)0;
        break;
    case BCMOLT_TM_SCHED_PARAM_TYPE_WEIGHT:
        obj->u.weight.presence_mask = 0;
        obj->u.weight.weight = (bcmolt_tm_weight)0;
        break;
    default:
        break;
    }
}

bcmos_bool bcmolt_tm_sched_param_validate(const bcmolt_tm_sched_param *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TM_SCHED_PARAM_ID_TYPE))
    {
        switch (obj->type)
        {
        case BCMOLT_TM_SCHED_PARAM_TYPE_UNDEFINED:
        case BCMOLT_TM_SCHED_PARAM_TYPE_PRIORITY:
        case BCMOLT_TM_SCHED_PARAM_TYPE_WEIGHT:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "type: enum value %d is unexpected\n", (int)obj->type);
            return BCMOS_FALSE;
        }
    }
    switch (obj->type)
    {
    case BCMOLT_TM_SCHED_PARAM_TYPE_PRIORITY:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.priority.presence_mask, BCMOLT_TM_SCHED_PARAM_PRIORITY_ID_PRIORITY))
        {
            /* obj->u.priority.priority can't be invalid. */
        }
        break;
    }
    case BCMOLT_TM_SCHED_PARAM_TYPE_WEIGHT:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.weight.presence_mask, BCMOLT_TM_SCHED_PARAM_WEIGHT_ID_WEIGHT))
        {
            if (obj->u.weight.weight < (bcmolt_tm_weight)1)
            {
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "weight: %u is less than the minimum value of 1\n", obj->u.weight.weight);
                return BCMOS_FALSE;
            }
            if (obj->u.weight.weight > (bcmolt_tm_weight)63)
            {
                *err = BCM_ERR_RANGE;
                bcmolt_string_append(err_details, "weight: %u is greater than the maximum value of 63\n", obj->u.weight.weight);
                return BCMOS_FALSE;
            }
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_sched_attachment_point_set_default(bcmolt_tm_sched_attachment_point *obj)
{
    obj->presence_mask = 0;
    obj->type = BCMOLT_TM_SCHED_OUTPUT_TYPE_UNDEFINED;
}

void bcmolt_tm_sched_attachment_point_set_union_default(bcmolt_tm_sched_attachment_point *obj, bcmolt_tm_sched_output_type type)
{
    obj->type = type;
    switch (type)
    {
    case BCMOLT_TM_SCHED_OUTPUT_TYPE_INTERFACE:
        obj->u.interface.presence_mask = 0;
        bcmolt_intf_ref_set_default(&obj->u.interface.interface_ref);
        break;
    case BCMOLT_TM_SCHED_OUTPUT_TYPE_TM_SCHED:
        obj->u.tm_sched.presence_mask = 0;
        obj->u.tm_sched.tm_sched_id = 0UL;
        bcmolt_tm_sched_param_set_default(&obj->u.tm_sched.tm_sched_param);
        break;
    default:
        break;
    }
}

bcmos_bool bcmolt_tm_sched_attachment_point_validate(const bcmolt_tm_sched_attachment_point *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TM_SCHED_ATTACHMENT_POINT_ID_TYPE))
    {
        switch (obj->type)
        {
        case BCMOLT_TM_SCHED_OUTPUT_TYPE_UNDEFINED:
        case BCMOLT_TM_SCHED_OUTPUT_TYPE_INTERFACE:
        case BCMOLT_TM_SCHED_OUTPUT_TYPE_TM_SCHED:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "type: enum value %d is unexpected\n", (int)obj->type);
            return BCMOS_FALSE;
        }
    }
    switch (obj->type)
    {
    case BCMOLT_TM_SCHED_OUTPUT_TYPE_INTERFACE:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.interface.presence_mask, BCMOLT_TM_SCHED_ATTACHMENT_POINT_INTERFACE_ID_INTERFACE_REF))
        {
            int prefix_len = bcmolt_string_append(err_details, "interface_ref.");
            if (!bcmolt_intf_ref_validate(&obj->u.interface.interface_ref, err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
        break;
    }
    case BCMOLT_TM_SCHED_OUTPUT_TYPE_TM_SCHED:
    {
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.tm_sched.presence_mask, BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID_TM_SCHED_ID))
        {
            /* obj->u.tm_sched.tm_sched_id can't be invalid. */
        }
        if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->u.tm_sched.presence_mask, BCMOLT_TM_SCHED_ATTACHMENT_POINT_TM_SCHED_ID_TM_SCHED_PARAM))
        {
            int prefix_len = bcmolt_string_append(err_details, "tm_sched_param.");
            if (!bcmolt_tm_sched_param_validate(&obj->u.tm_sched.tm_sched_param, err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return BCMOS_TRUE;
}

void bcmolt_tm_shaping_set_default(bcmolt_tm_shaping *obj)
{
    obj->presence_mask = 0;
    obj->cir = 0UL;
    obj->pir = 0UL;
    obj->burst = 0UL;
}

bcmos_bool bcmolt_tm_shaping_validate(const bcmolt_tm_shaping *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TM_SHAPING_ID_CIR))
    {
        /* obj->cir can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TM_SHAPING_ID_PIR))
    {
        /* obj->pir can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TM_SHAPING_ID_BURST))
    {
        /* obj->burst can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_topology_map_set_default(bcmolt_topology_map *obj)
{
    obj->presence_mask = 0;
    obj->local_device_id = (bcmolt_ldid)0;
    obj->olt_device_id = (bcmolt_odid)0;
    obj->physical_if_id = (bcmolt_interface_id)0U;
    bcmolt_str_16_set_default(&obj->user_string);
}

bcmos_bool bcmolt_topology_map_validate(const bcmolt_topology_map *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TOPOLOGY_MAP_ID_LOCAL_DEVICE_ID))
    {
        /* obj->local_device_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TOPOLOGY_MAP_ID_OLT_DEVICE_ID))
    {
        /* obj->olt_device_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TOPOLOGY_MAP_ID_PHYSICAL_IF_ID))
    {
        /* obj->physical_if_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TOPOLOGY_MAP_ID_USER_STRING))
    {
        int prefix_len = bcmolt_string_append(err_details, "user_string.");
        if (!bcmolt_str_16_validate(&obj->user_string, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_topology_map_list_u32_set_default(bcmolt_topology_map_list_u32 *obj)
{
    obj->len = 0UL;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_topology_map_list_u32_validate(const bcmolt_topology_map_list_u32 *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->len can't be invalid. */
    for (uint32_t i = 0; i < obj->len; i++)
    {
        if (_BCMOLT_ARRAY_MASK_BIT_IS_SET(obj->arr_index_mask, i))
        {
            int prefix_len = bcmolt_string_append(err_details, "arr[%d].", i);
            if (!bcmolt_topology_map_validate(&obj->arr[i], err, err_details))
            {
                return BCMOS_FALSE;
            }
            bcmolt_string_rewind(err_details, prefix_len);
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_topology_set_default(bcmolt_topology *obj)
{
    obj->presence_mask = 0;
    obj->num_switch_ports = 0;
    bcmolt_topology_map_list_u32_set_default(&obj->topology_maps);
}

bcmos_bool bcmolt_topology_validate(const bcmolt_topology *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TOPOLOGY_ID_NUM_SWITCH_PORTS))
    {
        /* obj->num_switch_ports can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TOPOLOGY_ID_TOPOLOGY_MAPS))
    {
        int prefix_len = bcmolt_string_append(err_details, "topology_maps.");
        if (!bcmolt_topology_map_list_u32_validate(&obj->topology_maps, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}

void bcmolt_trap_config_set_default(bcmolt_trap_config *obj)
{
    obj->presence_mask = 0;
    obj->tpid = 0U;
    obj->vlan_id = (bcmolt_vlan_id)0U;
    obj->vlan_mask = (bcmolt_vlan_id)65535U;
    obj->cfi = 0;
    obj->pbits = 0;
    obj->enable = BCMOS_FALSE;
}

bcmos_bool bcmolt_trap_config_validate(const bcmolt_trap_config *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TRAP_CONFIG_ID_TPID))
    {
        /* obj->tpid can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TRAP_CONFIG_ID_VLAN_ID))
    {
        /* obj->vlan_id can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TRAP_CONFIG_ID_VLAN_MASK))
    {
        /* obj->vlan_mask can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TRAP_CONFIG_ID_CFI))
    {
        /* obj->cfi can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TRAP_CONFIG_ID_PBITS))
    {
        /* obj->pbits can't be invalid. */
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_TRAP_CONFIG_ID_ENABLE))
    {
        /* obj->enable can't be invalid. */
    }
    return BCMOS_TRUE;
}

void bcmolt_u64_list_u32_hex_set_default(bcmolt_u64_list_u32_hex *obj)
{
    obj->len = 0UL;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_u64_list_u32_hex_validate(const bcmolt_u64_list_u32_hex *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->len can't be invalid. */
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_u8_list_u8_hex_set_default(bcmolt_u8_list_u8_hex *obj)
{
    obj->len = 0;
    obj->arr_index_mask = 0;
    obj->arr = NULL;
}

bcmos_bool bcmolt_u8_list_u8_hex_validate(const bcmolt_u8_list_u8_hex *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    /* obj->len can't be invalid. */
    /* obj->arr can't be invalid. */
    return BCMOS_TRUE;
}

void bcmolt_xgpon_onu_alarms_set_default(bcmolt_xgpon_onu_alarms *obj)
{
    obj->presence_mask = 0;
    obj->losi = BCMOLT_STATUS_OFF;
    obj->lobi = BCMOLT_STATUS_OFF;
    obj->lopci_miss = BCMOLT_STATUS_OFF;
    obj->lopci_mic_error = BCMOLT_STATUS_OFF;
}

bcmos_bool bcmolt_xgpon_onu_alarms_validate(const bcmolt_xgpon_onu_alarms *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARMS_ID_LOSI))
    {
        switch (obj->losi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "losi: enum value %d is unexpected\n", (int)obj->losi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARMS_ID_LOBI))
    {
        switch (obj->lobi)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lobi: enum value %d is unexpected\n", (int)obj->lobi);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARMS_ID_LOPCI_MISS))
    {
        switch (obj->lopci_miss)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lopci_miss: enum value %d is unexpected\n", (int)obj->lopci_miss);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_ONU_ALARMS_ID_LOPCI_MIC_ERROR))
    {
        switch (obj->lopci_mic_error)
        {
        case BCMOLT_STATUS_OFF:
        case BCMOLT_STATUS_ON:
        case BCMOLT_STATUS_NO_CHANGE:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "lopci_mic_error: enum value %d is unexpected\n", (int)obj->lopci_mic_error);
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

void bcmolt_xgpon_trx_set_default(bcmolt_xgpon_trx *obj)
{
    obj->presence_mask = 0;
    bcmolt_arr_xgpon_burst_profile_4_set_default(&obj->burst_profile);
    memset(obj->burst_profile.arr, 0, sizeof(obj->burst_profile.arr));
    bcmolt_xgpon_burst_profile_set_default(&obj->burst_profile.arr[0]);
    obj->burst_profile.arr[0].profile_version = 0x0;
    obj->burst_profile.arr[0].type = BCMOLT_BURST_PROFILE_TYPE_RANGING;
    obj->burst_profile.arr[0].is_fec_on = BCMOS_FALSE;
    obj->burst_profile.arr[0].delimiter_size_in_bytes = 8;
    obj->burst_profile.arr[0].delimiter_pattern_high = 0xB3BDD310UL;
    obj->burst_profile.arr[0].delimiter_pattern_low = 0xB2C50FA1UL;
    obj->burst_profile.arr[0].preamble_length_in_bytes = 8;
    obj->burst_profile.arr[0].preamble_repeats_count = 20;
    obj->burst_profile.arr[0].preamble_pattern_high = 0xAAAAAAAAUL;
    obj->burst_profile.arr[0].preamble_pattern_low = 0xAAAAAAAAUL;
    obj->burst_profile.arr[0].pon_tag = 0ULL;
    obj->burst_profile.arr[0].num_of_guard_bytes = 16UL;
    obj->burst_profile.arr[0].is_profile_valid = BCMOS_TRUE;
    obj->burst_profile.arr[0].burst_overhead_size_in_words = 78UL;
    bcmolt_xgpon_burst_profile_set_default(&obj->burst_profile.arr[1]);
    obj->burst_profile.arr[1].profile_version = 0x0;
    obj->burst_profile.arr[1].type = BCMOLT_BURST_PROFILE_TYPE_DATA;
    obj->burst_profile.arr[1].is_fec_on = BCMOS_FALSE;
    obj->burst_profile.arr[1].delimiter_size_in_bytes = 8;
    obj->burst_profile.arr[1].delimiter_pattern_high = 0xB3BDD310UL;
    obj->burst_profile.arr[1].delimiter_pattern_low = 0xB2C50FA1UL;
    obj->burst_profile.arr[1].preamble_length_in_bytes = 8;
    obj->burst_profile.arr[1].preamble_repeats_count = 9;
    obj->burst_profile.arr[1].preamble_pattern_high = 0xAAAAAAAAUL;
    obj->burst_profile.arr[1].preamble_pattern_low = 0xAAAAAAAAUL;
    obj->burst_profile.arr[1].pon_tag = 0ULL;
    obj->burst_profile.arr[1].num_of_guard_bytes = 16UL;
    obj->burst_profile.arr[1].is_profile_valid = BCMOS_TRUE;
    obj->burst_profile.arr[1].burst_overhead_size_in_words = 56UL;
    bcmolt_xgpon_burst_profile_set_default(&obj->burst_profile.arr[2]);
    obj->burst_profile.arr[2].profile_version = 0x0;
    obj->burst_profile.arr[2].type = BCMOLT_BURST_PROFILE_TYPE_RANGING;
    obj->burst_profile.arr[2].is_fec_on = BCMOS_TRUE;
    obj->burst_profile.arr[2].delimiter_size_in_bytes = 8;
    obj->burst_profile.arr[2].delimiter_pattern_high = 0xB3BDD310UL;
    obj->burst_profile.arr[2].delimiter_pattern_low = 0xB2C50FA1UL;
    obj->burst_profile.arr[2].preamble_length_in_bytes = 8;
    obj->burst_profile.arr[2].preamble_repeats_count = 20;
    obj->burst_profile.arr[2].preamble_pattern_high = 0xAAAAAAAAUL;
    obj->burst_profile.arr[2].preamble_pattern_low = 0xAAAAAAAAUL;
    obj->burst_profile.arr[2].pon_tag = 0ULL;
    obj->burst_profile.arr[2].num_of_guard_bytes = 16UL;
    obj->burst_profile.arr[2].is_profile_valid = BCMOS_TRUE;
    obj->burst_profile.arr[2].burst_overhead_size_in_words = 78UL;
    bcmolt_xgpon_burst_profile_set_default(&obj->burst_profile.arr[3]);
    obj->burst_profile.arr[3].profile_version = 0x0;
    obj->burst_profile.arr[3].type = BCMOLT_BURST_PROFILE_TYPE_DATA;
    obj->burst_profile.arr[3].is_fec_on = BCMOS_TRUE;
    obj->burst_profile.arr[3].delimiter_size_in_bytes = 8;
    obj->burst_profile.arr[3].delimiter_pattern_high = 0xB3BDD310UL;
    obj->burst_profile.arr[3].delimiter_pattern_low = 0xB2C50FA1UL;
    obj->burst_profile.arr[3].preamble_length_in_bytes = 8;
    obj->burst_profile.arr[3].preamble_repeats_count = 9;
    obj->burst_profile.arr[3].preamble_pattern_high = 0xAAAAAAAAUL;
    obj->burst_profile.arr[3].preamble_pattern_low = 0xAAAAAAAAUL;
    obj->burst_profile.arr[3].pon_tag = 0ULL;
    obj->burst_profile.arr[3].num_of_guard_bytes = 16UL;
    obj->burst_profile.arr[3].is_profile_valid = BCMOS_TRUE;
    obj->burst_profile.arr[3].burst_overhead_size_in_words = 56UL;
    obj->transceiver_type = BCMOLT_XGPON_TRX_TYPE_LTH_7222_PC;
    bcmolt_str_100_set_default(&obj->trx_name);
}

bcmos_bool bcmolt_xgpon_trx_validate(const bcmolt_xgpon_trx *obj, bcmos_errno *err, bcmolt_string *err_details)
{
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_TRX_ID_BURST_PROFILE))
    {
        int prefix_len = bcmolt_string_append(err_details, "burst_profile.");
        if (!bcmolt_arr_xgpon_burst_profile_4_validate(&obj->burst_profile, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_TRX_ID_TRANSCEIVER_TYPE))
    {
        switch (obj->transceiver_type)
        {
        case BCMOLT_XGPON_TRX_TYPE_LTH_7222_PC:
        case BCMOLT_XGPON_TRX_TYPE_WTD_RTXM266_702:
        case BCMOLT_XGPON_TRX_TYPE_LTH_7222_BC_PLUS:
        case BCMOLT_XGPON_TRX_TYPE_LTH_7226_PC:
        case BCMOLT_XGPON_TRX_TYPE_LTH_5302_PC:
        case BCMOLT_XGPON_TRX_TYPE_LTW_627_X_PC:
        case BCMOLT_XGPON_TRX_TYPE_XPP_XE_R_3_CDFB:
        case BCMOLT_XGPON_TRX_TYPE_LTH_7226_A_PC_PLUS:
        case BCMOLT_XGPON_TRX_TYPE_D272RR_SSCB_DM:
        case BCMOLT_XGPON_TRX_TYPE_LTH_5308:
        case BCMOLT_XGPON_TRX_TYPE_LTF_5308:
        case BCMOLT_XGPON_TRX_TYPE_LTF_7226_B:
        case BCMOLT_XGPON_TRX_TYPE_LTF_5308_E:
        case BCMOLT_XGPON_TRX_TYPE_LTF_5306:
        case BCMOLT_XGPON_TRX_TYPE_LTF_5308_B:
        case BCMOLT_XGPON_TRX_TYPE_SDDS_ST_XS_CP_CDFA:
        case BCMOLT_XGPON_TRX_TYPE_LTF_5308_E_SL:
        case BCMOLT_XGPON_TRX_TYPE_XGS_GENERAL_1:
        case BCMOLT_XGPON_TRX_TYPE_XGS_GENERAL_2:
        case BCMOLT_XGPON_TRX_TYPE_XGS_GENERAL_3:
        case BCMOLT_XGPON_TRX_TYPE_XGS_GENERAL_4:
        case BCMOLT_XGPON_TRX_TYPE_COMBO_GENERAL_1:
        case BCMOLT_XGPON_TRX_TYPE_COMBO_GENERAL_2:
        case BCMOLT_XGPON_TRX_TYPE_COMBO_GENERAL_3:
        case BCMOLT_XGPON_TRX_TYPE_COMBO_GENERAL_4:
            break;
        default:
            *err = BCM_ERR_RANGE;
            bcmolt_string_append(err_details, "transceiver_type: enum value %d is unexpected\n", (int)obj->transceiver_type);
            return BCMOS_FALSE;
        }
    }
    if (_BCMOLT_FIELD_MASK_BIT_IS_SET(obj->presence_mask, BCMOLT_XGPON_TRX_ID_TRX_NAME))
    {
        int prefix_len = bcmolt_string_append(err_details, "trx_name.");
        if (!bcmolt_str_100_validate(&obj->trx_name, err, err_details))
        {
            return BCMOS_FALSE;
        }
        bcmolt_string_rewind(err_details, prefix_len);
    }
    return BCMOS_TRUE;
}


