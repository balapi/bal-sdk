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
 * API side topology manager.
 * Topology Data Base is used for translation between various identifiers
 */

#include <bcmolt_api_topology.h>

/* OLT interface mapping info */
typedef struct bcmolt_api_topo_lif_info
{
    bcmolt_odid odid;   /* Device ID on a line card */
    bcmolt_pon_pif pif; /* Interface on the device */
} bcmolt_api_topo_lif_info;

/* Global OLT mapping info */
typedef struct bcmolt_api_topo_golt_info
{
    bcmolt_loid loid;   /* OLT id on the line card */
    bcmolt_gdid gdid[BCM_MAX_DEVS_PER_OLT];
    bcmolt_api_topo_lif_info ifs[BCM_MAX_PONS_PER_OLT];
} bcmolt_api_topo_golt_info;

/* Physical interface mapping info */
typedef struct bcmolt_api_topo_pif_info
{
    bcmolt_goid goid;   /* OLT reference */
    bcmolt_pon_lif lif; /* Logical intertface on the PON */
} bcmolt_api_topo_pif_info;

/* Global device mapping info */
typedef struct bcmolt_api_topo_gdev_info
{
    bcmolt_ldid ldid;   /* Device ID on a line card */
    bcmolt_api_topo_pif_info ifs[BCM_MAX_PONS_PER_DEV];
    bcmolt_goid goid[BCM_MAX_OLTS_PER_LINE_CARD];
    bcmos_bool allocated;
} bcmolt_api_topo_gdev_info;

static bcmolt_api_topo_golt_info bcmolt_golt_array[BCM_MAX_OLTS];
static bcmolt_api_topo_gdev_info bcmolt_gdev_array[BCM_MAX_DEVS];

/** Initialize API topolology layer */
bcmos_errno bcmolt_apitopo_init(void)
{
    bcmolt_goid g;
    bcmolt_gdid d;

    for (g = 0; g < BCM_MAX_OLTS; g++)
    {
        bcmolt_apitopo_olt_clear(g);
    }

    for (d = 0; d < BCM_MAX_DEVS; d++)
    {
        bcmolt_loid loid;
        bcmolt_pon_pif pif;
        bcmolt_gdev_array[d].ldid = BCMOLT_LDID_UNDEFINED;
        for (loid = 0; loid < BCM_MAX_OLTS_PER_LINE_CARD; loid++)
            bcmolt_gdev_array[d].goid[loid] = BCMOLT_GOID_UNDEFINED;
        for (pif = 0; pif < BCM_MAX_PONS_PER_DEV; pif++)
        {
            bcmolt_gdev_array[d].ifs[pif].lif = BCMOLT_PON_LIF_UNDEFINED;
            bcmolt_gdev_array[d].ifs[pif].goid = BCMOLT_GOID_UNDEFINED;
        }
    }

    return BCM_ERR_OK;
}


/*
 * OLT ID translation
 */

/* Store translation info */
bcmos_errno bcmolt_apitopo_goid_to_loid_set(bcmolt_gdid gdid, bcmolt_goid goid, bcmolt_loid loid)
{
    if (gdid >= BCM_MAX_DEVS || goid >= BCM_MAX_OLTS || loid >= BCM_MAX_OLTS_PER_LINE_CARD)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Check configuration. gdid %u/%d goid %u/%d loid %u/%d\n",
            gdid, BCM_MAX_DEVS, goid, BCM_MAX_OLTS, loid, BCM_MAX_OLTS_PER_LINE_CARD);
    }
    if (bcmolt_gdev_array[gdid].ldid == BCMOLT_LDID_UNDEFINED)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_NOENT, "gdid %d is not allocated\n", gdid);
    }
    bcmolt_golt_array[goid].loid = loid;
    bcmolt_gdev_array[gdid].goid[loid] = goid;
    return BCM_ERR_OK;
}

/* Clear all mappings for OLT */
bcmos_errno bcmolt_apitopo_olt_clear(bcmolt_goid goid)
{
    bcmolt_loid loid;
    bcmolt_odid odid;
    bcmolt_pon_lif lif;

    if (goid >= BCM_MAX_OLTS)
        return BCM_ERR_PARM;

    loid = bcmolt_golt_array[goid].loid;
    bcmolt_golt_array[goid].loid = BCMOLT_LOID_UNDEFINED;

    for (odid = 0; odid < BCM_MAX_DEVS_PER_OLT; odid++)
    {
        bcmolt_gdid gdid = bcmolt_golt_array[goid].gdid[odid];
        bcmolt_golt_array[goid].gdid[odid] = BCMOLT_GDID_UNDEFINED;
        if (gdid < BCM_MAX_DEVS)
        {
            bcmolt_pon_pif pif;
            bcmolt_gdev_array[gdid].goid[loid] = BCMOLT_GDID_UNDEFINED;
            for (pif = 0; pif < BCM_MAX_PONS_PER_DEV; pif++)
            {
                if (bcmolt_gdev_array[gdid].ifs[pif].goid == goid)
                {
                    bcmolt_gdev_array[gdid].ifs[pif].lif = BCMOLT_PON_LIF_UNDEFINED;
                    bcmolt_gdev_array[gdid].ifs[pif].goid = BCMOLT_GOID_UNDEFINED;
                }
            }
        }
    }

    for (lif = 0; lif < BCM_MAX_PONS_PER_OLT; lif++)
    {
        bcmolt_golt_array[goid].ifs[lif].odid = BCMOLT_ODID_UNDEFINED;
        bcmolt_golt_array[goid].ifs[lif].pif = BCMOLT_PON_PIF_UNDEFINED;
    }

    return BCM_ERR_OK;
}

/** Map GOID to LOID */
bcmos_errno bcmolt_apitopo_goid_to_loid(bcmolt_goid goid, bcmolt_loid *loid)
{
    if (goid >= BCM_MAX_OLTS)
        return BCM_ERR_PARM;
    if (bcmolt_golt_array[goid].loid >= BCM_MAX_OLTS_PER_LINE_CARD)
        return BCM_ERR_NOENT;
    *loid = bcmolt_golt_array[goid].loid;
    return BCM_ERR_OK;
}

/** Map { GDID, LOID } to GOID */
bcmos_errno bcmolt_apitopo_loid_to_goid(bcmolt_gdid gdid, bcmolt_loid loid, bcmolt_goid *goid)
{
    if (gdid >= BCM_MAX_DEVS || loid >= BCM_MAX_OLTS_PER_LINE_CARD)
        return BCM_ERR_PARM;
    if (bcmolt_gdev_array[gdid].goid[loid] >= BCM_MAX_OLTS)
        return BCM_ERR_NOENT;
    *goid = bcmolt_gdev_array[gdid].goid[loid];
    return BCM_ERR_OK;
}

/*
 * Device ID translation
 */

/** Set { Device ID on OLT } - { Global device ID } mapping */
bcmos_errno bcmolt_apitopo_odid_to_gdid_set(bcmolt_goid goid, bcmolt_odid odid, bcmolt_gdid gdid)
{
    if (goid >= BCM_MAX_OLTS || odid >= BCM_MAX_DEVS_PER_OLT || gdid >= BCM_MAX_DEVS)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Check configuration. goid %u/%d odid %u/%d gdid %u/%d\n",
            goid, BCM_MAX_OLTS, odid, BCM_MAX_DEVS_PER_OLT, gdid, BCM_MAX_DEVS);
    }
    /* Make sure that goid is mapped */
    if (bcmolt_golt_array[goid].loid == BCMOLT_LOID_UNDEFINED)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Check configuration. goid %u is not mapped to loid\n", goid);
    }
    /* Make sure that gdid is mapped */
    if (bcmolt_gdev_array[gdid].ldid == BCMOLT_LDID_UNDEFINED)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Check configuration. gdid %u is not mapped to ldid\n", gdid);
    }
    bcmolt_golt_array[goid].gdid[odid] = gdid;

    return BCM_ERR_OK;
}

/** Map { Device ID on OLT } to { Global device id, device ID on Line card } */
bcmos_errno bcmolt_apitopo_odid_to_gdid_ldid(bcmolt_goid goid, bcmolt_odid odid, bcmolt_gdid *gdid, bcmolt_ldid *ldid)
{
    if (goid >= BCM_MAX_OLTS || odid >= BCM_MAX_DEVS_PER_OLT)
        return BCM_ERR_PARM;
    *gdid = bcmolt_golt_array[goid].gdid[odid];
    if (*gdid >= BCM_MAX_DEVS || bcmolt_gdev_array[*gdid].ldid == BCMOLT_LDID_UNDEFINED)
        return BCM_ERR_NOENT;
    *ldid = bcmolt_gdev_array[*gdid].ldid;
    return BCM_ERR_OK;
}

/** Map { Device ID on Line card } to { Device ID on OLT } */
bcmos_errno bcmolt_apitopo_ldid_to_odid(bcmolt_goid goid, bcmolt_ldid ldid, bcmolt_odid *odid)
{
    bcmolt_odid d;
    if (goid >= BCM_MAX_OLTS || ldid >= BCM_MAX_DEVS_PER_LINE_CARD)
        return BCM_ERR_PARM;
    for (d = 0; d < BCM_MAX_DEVS_PER_OLT; d++)
    {
        bcmolt_gdid gdid = bcmolt_golt_array[goid].gdid[d];
        if (gdid < BCM_MAX_DEVS && bcmolt_gdev_array[gdid].ldid == ldid)
        {
            *odid = d;
            return BCM_ERR_OK;
        }
    }
    return BCM_ERR_NOENT;
}

/** Allocate unused Global Device ID */
bcmos_errno bcmolt_apitopo_gdid_alloc(bcmolt_gdid *gdid)
{
    bcmolt_gdid g;

    for (g = 0; g < BCM_MAX_DEVS; g++)
    {
        if (!bcmolt_gdev_array[g].allocated)
            break;
    }
    if (g >= BCM_MAX_DEVS)
        return BCM_ERR_TOO_MANY;

    bcmolt_gdev_array[g].allocated = BCMOS_TRUE;
    *gdid = g;

    return BCM_ERR_OK;
}

/** Set { Global Device ID } to { Device ID on Line card } mapping
 * \param[in]   gdid    Global device id
 * \param[in]   ldid    Device ID on the line card
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_gdid_to_ldid_set(bcmolt_gdid gdid, bcmolt_ldid ldid)
{
    if (gdid >= BCM_MAX_DEVS || ldid >= BCM_MAX_DEVS_PER_LINE_CARD)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Check configuration. gdid %u/%d ldid %u/%u\n",
            gdid, BCM_MAX_DEVS, ldid, BCM_MAX_DEVS_PER_LINE_CARD);
    }
    if (!bcmolt_gdev_array[gdid].allocated)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "gdid %u is not allocated\n", gdid);
    }
    if (bcmolt_gdev_array[gdid].ldid != BCMOLT_LDID_UNDEFINED && bcmolt_gdev_array[gdid].ldid != ldid)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_ALREADY, "gdid %u is already mapped to ldid %u\n",
            gdid, bcmolt_gdev_array[gdid].ldid);
    }
    bcmolt_gdev_array[gdid].ldid = ldid;
    return BCM_ERR_OK;
}

/** Free device id allocated by bcmolt_apitopo_gdid_alloc() */
void bcmolt_apitopo_gdid_free(bcmolt_gdid gdid)
{
    bcmolt_loid loid;
    bcmolt_pon_pif pif;

    if (gdid >= BCM_MAX_DEVS)
        return;

    if (!bcmolt_gdev_array[gdid].allocated)
        return;

    /* Clear gdid -. ldid mapping */
    bcmolt_gdev_array[gdid].ldid = BCMOLT_LDID_UNDEFINED;

    /* Clear gdid references in OLT DBs */
    for (loid = 0; loid < BCM_MAX_OLTS_PER_LINE_CARD; loid++)
    {
        bcmolt_goid goid = bcmolt_gdev_array[gdid].goid[loid];
        bcmolt_odid odid;

        if (goid >= BCM_MAX_OLTS)
            continue;

        /* Go over devices on the OLT and clear mapping if match */
        for (odid = 0; odid < BCM_MAX_DEVS_PER_OLT; odid++)
        {
            if (bcmolt_golt_array[goid].gdid[odid] == gdid)
            {
                bcmolt_golt_array[goid].gdid[odid] = BCMOLT_GDID_UNDEFINED;
                break;
            }
        }
    }

    /* Now clear references to PON interfaces belonging to the device */
    for (pif = 0; pif < BCM_MAX_PONS_PER_DEV; pif++)
    {
        bcmolt_goid goid = bcmolt_gdev_array[gdid].ifs[pif].goid;
        bcmolt_pon_lif lif = bcmolt_gdev_array[gdid].ifs[pif].lif;

        bcmolt_gdev_array[gdid].ifs[pif].lif = BCMOLT_PON_LIF_UNDEFINED;
        bcmolt_gdev_array[gdid].ifs[pif].goid = BCMOLT_GOID_UNDEFINED;
        if (goid < BCM_MAX_OLTS && lif < BCM_MAX_PONS_PER_OLT)
        {
            bcmolt_golt_array[goid].ifs[lif].odid = BCMOLT_ODID_UNDEFINED;
            bcmolt_golt_array[goid].ifs[lif].pif = BCMOLT_PON_PIF_UNDEFINED;
        }
    }

    bcmolt_gdev_array[gdid].allocated = BCMOS_FALSE;
}

/** Map { Global Device ID } to { Line card, Device ID on Line card } */
bcmos_errno bcmolt_apitopo_gdid_to_ldid(bcmolt_gdid gdid, bcmolt_ldid *ldid)
{
    if (gdid >= BCM_MAX_DEVS)
        return BCM_ERR_PARM;
    if (bcmolt_gdev_array[gdid].ldid == BCMOLT_LDID_UNDEFINED)
        return BCM_ERR_NOENT;
    *ldid = bcmolt_gdev_array[gdid].ldid;
    return BCM_ERR_OK;
}

/*
 * Interface ID translation
 */

/** Set { OLT ID, PON Interface on OLT } - { device, PON interface on device } translation */
bcmos_errno bcmolt_apitopo_lif_to_pif_set(bcmolt_goid goid, bcmolt_pon_lif lif, bcmolt_ldid ldid, bcmolt_pon_pif pif)
{
    bcmolt_odid odid;
    bcmolt_gdid gdid;

    if (goid >= BCM_MAX_OLTS || lif >= BCM_MAX_PONS_PER_OLT || ldid >= BCM_MAX_DEVS_PER_LINE_CARD || pif >= BCM_MAX_PONS_PER_DEV)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Check configuration. goid %u/%d lif %u/%d ldid %u/%d pif %u/%u\n",
            goid, BCM_MAX_OLTS, lif, BCM_MAX_PONS_PER_OLT, ldid, BCM_MAX_DEVS_PER_LINE_CARD, pif, BCM_MAX_PONS_PER_DEV);
    }
    if (bcmolt_apitopo_ldid_to_odid(goid, ldid, &odid) != BCM_ERR_OK ||
        (gdid = bcmolt_golt_array[goid].gdid[odid]) >= BCM_MAX_DEVS)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_PARM, "Check configuration. ldid %u is not mapped on goid %u\n", ldid, goid);
    }

    /* Make sure that not already mampped */
    if (bcmolt_gdev_array[gdid].ifs[pif].lif != BCMOLT_PON_PIF_UNDEFINED)
    {
        BCMOS_TRACE_RETURN(BCM_ERR_ALREADY,
            "Can't map pif %u on ldid %u to goid %u lif %u. It is already mapped to goid %u lif %u\n",
            pif, ldid, goid, lif, bcmolt_gdev_array[gdid].ifs[pif].goid, bcmolt_gdev_array[gdid].ifs[pif].lif);
    }

    /* Create mapping in OLT DB */
    bcmolt_golt_array[goid].ifs[lif].odid = odid;
    bcmolt_golt_array[goid].ifs[lif].pif = pif;

    /* Create mapping in device DB */
    bcmolt_gdev_array[gdid].ifs[pif].goid = goid;
    bcmolt_gdev_array[gdid].ifs[pif].lif = lif;

    return BCM_ERR_OK;
}

/** Map { OLT ID, PON Interface on OLT } to { device, PON interface on device } */
bcmos_errno bcmolt_apitopo_lif_to_pif(bcmolt_goid goid, bcmolt_pon_lif lif,
    bcmolt_gdid *gdid, bcmolt_ldid *ldid, bcmolt_pon_pif *pif)
{
    if (goid >= BCM_MAX_OLTS || lif >= BCM_MAX_PONS_PER_OLT)
        return BCM_ERR_PARM;
    /* Is interface mapped ? */
    if (bcmolt_golt_array[goid].ifs[lif].odid >= BCM_MAX_DEVS_PER_OLT)
        return BCM_ERR_NOENT;
    *gdid = bcmolt_golt_array[goid].gdid[bcmolt_golt_array[goid].ifs[lif].odid];
    if (*gdid >= BCM_MAX_DEVS)
        return BCM_ERR_NOENT;
    *ldid = bcmolt_gdev_array[*gdid].ldid;
    *pif = bcmolt_golt_array[goid].ifs[lif].pif;

    return BCM_ERR_OK;
}

/** Map { device, PON interface on device } to { OLT ID, PON Interface on OLT } */
bcmos_errno bcmolt_apitopo_pif_to_lif(bcmolt_gdid gdid, bcmolt_pon_pif pif, bcmolt_goid *goid, bcmolt_pon_lif *lif)
{
    bcmolt_ldid ldid;

    if (gdid >= BCM_MAX_DEVS || pif >= BCM_MAX_PONS_PER_DEV)
        return BCM_ERR_PARM;
    ldid = bcmolt_gdev_array[gdid].ldid;
    /* Is gdid mapped ? */
    if (ldid >= BCM_MAX_DEVS_PER_LINE_CARD)
        return BCM_ERR_NOENT;
    /* Is interface mapped ? */
    if (bcmolt_gdev_array[gdid].ifs[pif].goid >= BCM_MAX_OLTS)
        return BCM_ERR_NOENT;

    *goid = bcmolt_gdev_array[gdid].ifs[pif].goid;
    *lif = bcmolt_gdev_array[gdid].ifs[pif].lif;

    return BCM_ERR_OK;
}
