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

#ifndef BCMOLT_API_TOPOLOGY_H_
#define BCMOLT_API_TOPOLOGY_H_

#include <bcmos_system.h>
#include <bcmolt_system_types_typedefs.h>

/** Global OLT ID alias */
#define bcmolt_goid bcmolt_oltid
#define BCMOLT_GOID_UNDEFINED (bcmolt_goid)(-1)

/** OLT on a line card. Declared in bcmolt_system_types.h */
/* typedef uint8_t bcmolt_loid; */

/** Global device id alias */
#define bcmolt_gdid bcmolt_devid
#define BCMOLT_GDID_UNDEFINED (bcmolt_gdid)(-1)

/** Device id on a line card. Declared in bcmolt_system_types.h */
/* typedef uint8_t bcmolt_ldid; */

/** PON interface id on a line card */
typedef bcmolt_interface bcmolt_pon_lif;
#define BCMOLT_PON_LIF_UNDEFINED (bcmolt_pon_lif)(-1)

/** Interface id on MAC device */
typedef bcmolt_interface bcmolt_pon_pif;
#define BCMOLT_PON_PIF_UNDEFINED (bcmolt_pon_pif)(-1)

/** Initialize API topolology layer */
bcmos_errno bcmolt_apitopo_init(void);

/*
 * OLT ID translation
 */

/** Set { Global device id, Global OLT ID } - { OLT ID on Linecard } mapping
 * \param[in]   gdid    Global device ID
 * \param[in]   goid    Global OLT ID
 * \param[in]   loid    OLT ID on the line card
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_goid_to_loid_set(bcmolt_gdid gdid, bcmolt_goid goid, bcmolt_loid loid);

/** Clear all mappings for OLT
 * \param[in]   goid    Global OLT ID
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_olt_clear(bcmolt_goid goid);

/** Map GOID to { LCID, LOID }
 * \param[in]   goid    Global OLT ID
 * \param[out]  loid    OLT ID on the line card
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_goid_to_loid(bcmolt_goid goid, bcmolt_loid *loid);

/** Map { GDID, LOID } to GOID
 * \param[in]   gdid    Global device ID
 * \param[in]   loid    OLT ID on the line card
 * \param[out]  goid    Global OLT ID
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_loid_to_goid(bcmolt_gdid gdid, bcmolt_loid loid, bcmolt_goid *goid);

/*
 * Device ID translation
 */

/** Allocate unused Global Device ID and set Set { Line card, Device ID on Line card } - { Global Device ID } mapping
 * \param[out]  gdid    Device ID on the OLT
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_gdid_alloc(bcmolt_gdid *gdid);

/** Free device id allocated by bcmolt_apitopo_gdid_alloc()
 * \param[in]   gdid    Device ID on the OLT
 */
void bcmolt_apitopo_gdid_free(bcmolt_gdid gdid);

/** Set { Global Device ID } to { Device ID on Line card } mapping
 * \param[in]   gdid    Global device id
 * \param[in]   ldid    Device ID on the line card
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_gdid_to_ldid_set(bcmolt_gdid gdid, bcmolt_ldid ldid);

/** Map { Global Device ID } to { Device ID on Line card }
 * \param[in]   gdid    Global device id
 * \param[out]  ldid    Device ID on the line card
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_gdid_to_ldid(bcmolt_gdid gdid, bcmolt_ldid *ldid);

/** Set { Device ID on OLT } - { Global device ID } mapping
 * \param[in]   goid    Global OLT ID
 * \param[in]   odid    Device ID on the OLT
 * \param[in]   gdid    Global device id
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_odid_to_gdid_set(bcmolt_goid goid, bcmolt_odid odid, bcmolt_gdid gdid);

/** Map { Device ID on OLT } to { Device ID on Line card, global device }
 * \param[in]   goid    Global OLT ID
 * \param[in]   odid    Device ID on the OLT
 * \param[out]  gdid    Global device id
 * \param[out]  ldid    Device ID on the line card
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_odid_to_gdid_ldid(bcmolt_goid goid, bcmolt_odid odid, bcmolt_gdid *gdid, bcmolt_ldid *ldid);

/** Map { Device ID on Line card } to { Device ID on OLT }
 * \param[in]   goid    Global OLT ID
 * \param[in]   ldid    Device ID on the line card
 * \param[out]  odid    Device ID on the OLT
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_ldid_to_odid(bcmolt_goid goid, bcmolt_ldid ldid, bcmolt_odid *odid);

/*
 * Interface ID translation
 */

/** Set { OLT ID, PON Interface on OLT } - { device, PON interface on device } translation
 * \param[in]   goid    Global OLT ID
 * \param[in]   lif     PON interface ID on the OLT
 * \param[in]   ldid    Device ID on the line card
 * \param[in]   pif     PON interface ID on the device
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_lif_to_pif_set(bcmolt_goid goid, bcmolt_pon_lif lif, bcmolt_ldid ldid, bcmolt_pon_pif pif);

/** Map { OLT ID, PON Interface on OLT } to { device, PON interface on device }
 * \param[in]   goid    Global OLT ID
 * \param[in]   lif     PON interface ID on the OLT
 * \param[out]  gdid    Global device id
 * \param[out]  ldid    Device ID on the line card
 * \param[out]  pif     PON interface ID on the device
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_lif_to_pif(bcmolt_goid goid, bcmolt_pon_lif lif,
    bcmolt_gdid *gdid, bcmolt_ldid *ldid, bcmolt_pon_pif *pif);

/** Map { device, PON interface on device } to { OLT ID, PON Interface on OLT }
 * \param[in]   gdid    Global device id
 * \param[in]   pif     PON interface ID on the device
 * \param[out]  goid    Global OLT ID
 * \param[out]  lif     PON interface ID on the OLT
 * \returns BCM_ERR_OK (0) or error code < 0
 */
bcmos_errno bcmolt_apitopo_pif_to_lif(bcmolt_gdid gdid, bcmolt_pon_pif pif, bcmolt_goid *goid, bcmolt_pon_lif *lif);

#endif /* BCMOLT_API_TOPOLOGY_H_ */
