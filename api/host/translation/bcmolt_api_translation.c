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

/*
 * API translation service
 * Translates
 * - global OLT id : OLT id on a line card
 * - global device id : device id on line card : device id on OLT
 * - PON interface on OLT : PON interface on MAC device
 */

#include <bcmolt_api_translation.h>
#include <bcmolt_api_topology.h>
#include <bcmolt_api_metadata.h>
#include <bcmolt_api_conn_mgr.h>
#include <bcmtr_interface.h>
#include <bcmolt_api.h>
#include <bcmolt_api_utils.h>

/* Translate indication key and deliver to registered callback */
static bcmos_errno bcmolt_api_translate_indication(bcmolt_devid device, bcmolt_oltid olt, bcmolt_msg *msg);

/* Initialize translation layer */
bcmos_errno bcmolt_api_translate_init(void)
{
    bcmos_errno err;
    bcmtr_rx_translate_cb_register(bcmolt_api_translate_indication);
    err = bcmolt_apitopo_init();
    return err;
}

/* Cleanup translation layer */
void bcmolt_api_translate_exit(void)
{
    bcmtr_rx_translate_cb_register(NULL);
}

/* Initialize translation layer for an OLT */
bcmos_errno bcmolt_api_translate_olt_init(
    bcmolt_oltid olt,
    bcmolt_loid loid,
    bcmolt_gdid *ldid_to_gdid_array,
    const bcmolt_topology *topo)
{
    bcmolt_interface_id lif;
    bcmos_errno err = BCM_ERR_OK;

    /* Go over all logical interfaces */
    for (lif = 0; lif < topo->topology_maps.len; lif++)
    {
        bcmolt_topology_map *map = &topo->topology_maps.arr[lif];
        bcmolt_ldid ldid = map->local_device_id;

        if (ldid >= BCM_MAX_DEVS_PER_LINE_CARD)
        {
            BCM_LOG(ERROR, bcmolt_api_log_id,
                "OLT_%u: local_device_id %u is out of range 0..%d. Ignored\n",
                olt, ldid, BCM_MAX_DEVS_PER_LINE_CARD-1);
            continue;
        }

        /* Allocate global device IDs for all devices in the OLT which are not allocated yet */
        if (ldid_to_gdid_array[ldid] == BCMOLT_GDID_UNDEFINED)
        {
            err = bcmolt_apitopo_gdid_alloc(&ldid_to_gdid_array[ldid]);
            if (err != BCM_ERR_OK)
            {
                BCM_LOG(ERROR, bcmolt_api_log_id, "OLT_%u: Can't allocate gdid for ldid %u - %s\n",
                    olt, ldid, bcmos_strerror(err));
                break;
            }

            /* Create GDID - LDID mapping */
            err = bcmolt_apitopo_gdid_to_ldid_set(ldid_to_gdid_array[ldid], ldid);
            if (err != BCM_ERR_OK)
            {
                BCM_LOG(ERROR, bcmolt_api_log_id, "OLT_%u: Can't create gdid %u - ldid %u mapping - %s\n",
                    olt, ldid_to_gdid_array[ldid], ldid, bcmos_strerror(err));
                bcmolt_apitopo_gdid_free(ldid_to_gdid_array[ldid]);
                ldid_to_gdid_array[ldid] = BCMOLT_GDID_UNDEFINED;
                break;
            }
        }

        err = bcmolt_apitopo_goid_to_loid_set(ldid_to_gdid_array[ldid], olt, loid);
        if (err != BCM_ERR_OK && err != BCM_ERR_ALREADY)
        {
            BCM_LOG(ERROR, bcmolt_api_log_id, "bcmolt_apitopo_goid_to_loid_set(%u, %u, %u) -> %s\n",
                ldid_to_gdid_array[ldid], olt, loid, bcmos_strerror(err));
            break;
        }

        /* Device on OLT mapping */
        err = bcmolt_apitopo_odid_to_gdid_set(olt, map->olt_device_id, ldid_to_gdid_array[ldid]);
        if (err != BCM_ERR_OK && err != BCM_ERR_ALREADY)
        {
            BCM_LOG(ERROR, bcmolt_api_log_id, "OLT_%u: Can't create odid %u - gdid %u - %s\n",
                olt, map->olt_device_id, ldid_to_gdid_array[ldid], bcmos_strerror(err));
            break;
        }

        /* Interfaces */
        err = bcmolt_apitopo_lif_to_pif_set(olt, lif, map->local_device_id, map->physical_if_id);
        if (err != BCM_ERR_OK)
        {
            BCM_LOG(ERROR, bcmolt_api_log_id, "OLT_%u: Can't create lif %u - pif %u mapping - %s\n",
                olt, lif, map->physical_if_id, bcmos_strerror(err));
            break;
        }
    }

    if (err != BCM_ERR_OK)
    {
        bcmolt_apitopo_olt_clear(olt);
        return err;
    }

    return err;
}

/* Cleanup translation layer for an OLT */
void bcmolt_api_translate_olt_exit(bcmolt_oltid olt)
{
    /* Cleanup */
    bcmolt_apitopo_olt_clear(olt);
}

/* Translate request key, make RPC using transport layer and translate response */
bcmos_errno bcmolt_api_translate_and_call(bcmolt_oltid olt, bcmolt_msg *msg)
{
    bcmolt_loid loid;
    bcmolt_ldid odid; /* intentionally declared as bcmolt_ldid to keep bcmolt_devif_get() happy */
    bcmos_bool has_device;
    bcmolt_ldid ldid;
    bcmolt_gdid gdid;
    bcmos_bool has_interface;
    bcmolt_interface lif;
    bcmolt_pon_pif pif;
    bcmos_errno err;

    if (!bcmolt_api_conn_mgr_is_connected(olt))
        return BCM_ERR_NOT_CONNECTED;

    /* Translate OLT */
    err = bcmolt_apitopo_goid_to_loid(olt, &loid);
    if (err != BCM_ERR_OK)
        return err;

    /* Fetch device and interface ID from the message */
    odid = 0; /* use 0 as default value in case there is neither lif nor odid in the key */
    lif = BCMOLT_INTERFACE_UNDEFINED;
    bcmolt_devif_get(msg, &has_device, &odid, &has_interface, &lif);

    /* Translate the key if necessary */
    if (has_interface)
    {
        /* Identify transport channel based on lif, translate lif -> pif in the key */
        err = bcmolt_apitopo_lif_to_pif(olt, (bcmolt_pon_lif)lif, &gdid, &ldid, &pif);
        if (err != BCM_ERR_OK)
        {
            return BCMOLT_MSG_ERR(msg, bcmolt_api_log_id, err,
                "Can't translate logical interface id %u on OLT %u", lif, olt);
        }
    }
    else
    {
        /* Identify transport channel based on odid, translate odid -> ldid in the key */
        pif = 0;
        err = bcmolt_apitopo_odid_to_gdid_ldid(olt, (bcmolt_odid)odid, &gdid, &ldid);
        if (err != BCM_ERR_OK)
        {
            return BCMOLT_MSG_ERR(msg, bcmolt_api_log_id, err,
                "Can't translate device id %u on OLT %u", odid, olt);
        }
    }

    /* Translate message key */
    bcmolt_devif_set(msg, ldid, pif);
    msg->device = ldid;
    msg->loid = loid;

    /* Send request and wait for response */
    err = bcmtr_call(gdid, msg);

    /* Restore message key */
    bcmolt_devif_set(msg, (bcmolt_odid)odid, lif);

    return err;
}

static bcmos_errno bcmolt_api_translate_indication(bcmolt_devid device, bcmolt_oltid olt, bcmolt_msg *msg)
{
    /* If message contains OLT ID - translate it and make sure that it matches
        the OLT transport handler was registered with
    */
    bcmos_bool has_device;
    bcmolt_ldid ldid = BCMOLT_LDID_UNDEFINED;
    bcmos_bool has_interface;
    bcmolt_interface pif = BCMOLT_INTERFACE_UNDEFINED;
    bcmolt_odid odid = BCMOLT_ODID_UNDEFINED;
    bcmolt_pon_lif lif = BCMOLT_PON_LIF_UNDEFINED;
    bcmolt_goid goid;
    bcmos_errno err;

    /* Make sure that OLT matches */
    if (msg->loid != BCMOLT_LOID_UNDEFINED)
    {
        err = bcmolt_apitopo_loid_to_goid(device, msg->loid, &goid);
        if (err != BCM_ERR_OK)
            return err;
        if (goid != olt)
            return BCM_ERR_MISMATCH;
    }
    else
    {
        err = bcmolt_apitopo_goid_to_loid(olt, &msg->loid);
        if (err != BCM_ERR_OK)
            return err;
    }

    /* Translate key
        - ldid --> odid in device key
        - pif --> lif
    */
    bcmolt_devif_get(msg, &has_device, &ldid, &has_interface, &pif);
    if (has_device)
    {
        /* At this point ldid is wrong because device that sets it doesn't know it.
           Take it from "device" parameter.
        */
        err = bcmolt_apitopo_gdid_to_ldid(device, &ldid);
        err = err ? err : bcmolt_apitopo_ldid_to_odid(olt, ldid, &odid);
        if (err != BCM_ERR_OK)
            return err;
    }
    if (has_interface)
    {
        err = bcmolt_apitopo_pif_to_lif(device, (bcmolt_pon_pif)pif, &goid, &lif);
        if (err != BCM_ERR_OK)
            return err;
    }
    bcmolt_devif_set(msg, odid, lif);
    return BCM_ERR_OK;
}
