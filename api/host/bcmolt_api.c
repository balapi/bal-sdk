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
#define BCMOLT_API_INTERNAL

#include <bcmtr_interface.h>
#include <bcmolt_api.h>
#include <bcmolt_api_translation.h>
#include <bcmolt_api_metadata.h>
#include <bcmolt_api_utils.h>
#include <bcmolt_msg_pack.h>
#include <bcmolt_api_tags.h>
#include <bcmolt_api_log.h>

/* Initialize API layer */
bcmos_errno bcmolt_api_init(void)
{
    bcmos_errno err;
    err = bcmolt_api_translate_init();
    if (err != BCM_ERR_OK)
        return err;
    bcmolt_api_log_init();
    bcmolt_api_model_init();
    bcmolt_api_tags_init();

    return BCM_ERR_OK;
}

static inline bcmos_errno bcmolt_api_call(bcmolt_oltid olt, bcmolt_msg *msg)
{
    bcmos_errno err;

    /* Log configuration API before it is translated */
    if ((msg->type & BCMOLT_MSG_TYPE_GET) == 0)
    {
        bcmolt_api_log(olt, msg);
    }

    err = bcmolt_api_validate_for_api_call(msg);
    if (err != BCM_ERR_OK)
    {
        return err;
    }

    /* Translate API based on the OLT topology and invoke the RPC */
    return bcmolt_api_translate_and_call(olt, msg);
}

/* Set configuration */
bcmos_errno bcmolt_cfg_set(bcmolt_oltid olt, bcmolt_cfg *cfg)
{
    cfg->hdr.type = BCMOLT_MSG_TYPE_SET;
    return bcmolt_api_call(olt, &cfg->hdr);
}

/* Get configuration */
bcmos_errno bcmolt_cfg_get(bcmolt_oltid olt, bcmolt_cfg *cfg)
{
    cfg->hdr.type = BCMOLT_MSG_TYPE_GET;
    return bcmolt_api_call(olt, &cfg->hdr);
}

/* Clear configuration */
bcmos_errno bcmolt_cfg_clear(bcmolt_oltid olt, bcmolt_cfg *cfg)
{
    cfg->hdr.type = BCMOLT_MSG_TYPE_CLEAR;
    return bcmolt_api_call(olt, &cfg->hdr);
}

/* Get statistics */
bcmos_errno bcmolt_stat_get(bcmolt_oltid olt, bcmolt_stat *stat, bcmolt_stat_flags flags)
{
    stat->hdr.type = BCMOLT_MSG_TYPE_GET;
    if ((flags & BCMOLT_STAT_FLAGS_CLEAR_ON_READ))
    {
        stat->hdr.type |= BCMOLT_MSG_TYPE_CLEAR;
    }
    return bcmolt_api_call(olt, &stat->hdr);
}

/* Get statistics configuration */
bcmos_errno bcmolt_stat_cfg_get(bcmolt_oltid olt, bcmolt_stat_cfg *cfg)
{
    cfg->hdr.type = BCMOLT_MSG_TYPE_GET;
    return bcmolt_api_call(olt, &cfg->hdr);
}

/* Set statistics configuration */
bcmos_errno bcmolt_stat_cfg_set(bcmolt_oltid olt, bcmolt_stat_cfg *cfg)
{
    cfg->hdr.type = BCMOLT_MSG_TYPE_SET;
    return bcmolt_api_call(olt, &cfg->hdr);
}

/* Invoke operation */
bcmos_errno bcmolt_oper_submit(bcmolt_oltid olt, bcmolt_oper *oper)
{
    oper->hdr.type = BCMOLT_MSG_TYPE_SET;
    return bcmolt_api_call(olt, &oper->hdr);
}

/* (Un)Register auto/proxy message */
static bcmos_errno bcmolt_rx_cb_set_clear(
    bcmolt_oltid olt,
    bcmolt_rx_cfg *rx_cfg,
    bcmos_bool is_set)
{
    bcmtr_handler_parm tparm = {};
    bcmolt_ldid ldid;
    bcmolt_gdid gdid;
    bcmolt_pon_lif lif;
    bcmolt_pon_pif pif;
    bcmos_errno rc = BCM_ERR_OK;

    if (!rx_cfg)
        return BCM_ERR_PARM;

    if (is_set && !rx_cfg->rx_cb)
        return BCM_ERR_PARM;

    tparm.object = rx_cfg->obj_type;
    tparm.app_cb = rx_cfg->rx_cb;
    tparm.flags = rx_cfg->flags;
    tparm.olt = olt;
    tparm.group = BCMOLT_MGT_GROUP_AUTO;
    tparm.subgroup = (rx_cfg->obj_type != BCMOLT_OBJECT_ANY) ? rx_cfg->subgroup : BCMOLT_SUBGROUP_ANY;
    if (rx_cfg->flags == BCMOLT_AUTO_FLAGS_DISPATCH)
        tparm.module = rx_cfg->module;

    /* Register for all/selected OLT interfaces - per topology */
    rc = BCM_ERR_NOT_CONNECTED;
    for (lif = 0;
         bcmolt_apitopo_lif_to_pif(olt, lif, &gdid, &ldid, &pif) == BCM_ERR_OK;
         lif++)
    {
        /* Skip interfaces that are not present in pon_ni_mask, if set */
        if (rx_cfg->pon_ni_mask && 0 == (rx_cfg->pon_ni_mask & (1 << lif)))
            continue;

        tparm.instance = pif;
        if (is_set)
        {
            rc = bcmtr_msg_handler_register(gdid, &tparm);
        }
        else
        {
            rc = bcmtr_msg_handler_unregister(gdid, &tparm);
        }
    }
    return rc;
}

/* Register Autonomous Indication Message Handler */
bcmos_errno bcmolt_ind_subscribe(bcmolt_oltid olt, bcmolt_rx_cfg *rx_cfg)
{
    return bcmolt_rx_cb_set_clear(olt, rx_cfg, BCMOS_TRUE);
}

/* Un-register Autonomous Indication Message Handler registered by bcmolt_ind_subscribe() */
bcmos_errno bcmolt_ind_unsubscribe(bcmolt_oltid olt, bcmolt_rx_cfg *rx_cfg)
{
    return bcmolt_rx_cb_set_clear(olt, rx_cfg, BCMOS_FALSE);
}

/* Get configuration of multiple objects */
bcmos_errno bcmolt_multi_cfg_get(
    bcmolt_oltid olt,
    bcmolt_multi_cfg *cfg,
    bcmolt_filter_flags filter_flags)
{
    cfg->hdr.filter_flags = filter_flags;
    cfg->hdr.hdr.type = BCMOLT_MSG_TYPE_GET_MULTI;
    return bcmolt_api_call(olt, &cfg->hdr.hdr);
}

/* Get statistics of multiple objects */
bcmos_errno bcmolt_multi_stat_get(
    bcmolt_oltid olt,
    bcmolt_multi_stat *stat,
    bcmolt_stat_flags stat_flags,
    bcmolt_filter_flags filter_flags)
{
    stat->hdr.filter_flags = filter_flags;
    stat->hdr.hdr.type = BCMOLT_MSG_TYPE_GET_MULTI;
    if ((stat_flags & BCMOLT_STAT_FLAGS_CLEAR_ON_READ) != 0)
    {
        stat->hdr.hdr.type |= BCMOLT_MSG_TYPE_CLEAR;
    }
    return bcmolt_api_call(olt, &stat->hdr.hdr);
}
