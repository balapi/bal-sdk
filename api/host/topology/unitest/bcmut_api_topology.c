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
#include <bcmut.h>
#include <bcmolt_api_topology.h>

static bcmolt_gdid gdid;

/* Test functions in OLT ID translation group */
static void test_olt_id_translate(void **state)
{
    bcmolt_goid goid;
    bcmolt_loid loid;
    bcmos_errno err;

    /* Translate goid -> loid before it is mapped */
    err = bcmolt_apitopo_goid_to_loid(255, &loid);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_goid_to_loid(1, &loid);
    assert_true(err == BCM_ERR_NOENT);

    /* Translate loid -> goid before it is mapped */
    err = bcmolt_apitopo_loid_to_goid(0, 255, &goid);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_loid_to_goid(0, 1, &goid);
    assert_true(err == BCM_ERR_NOENT);

    /* Map goid - loid. At this point it should fail because gdid is not mapped */
    err = bcmolt_apitopo_goid_to_loid_set(255, 0, 0);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_goid_to_loid_set(0, 255, 0);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_goid_to_loid_set(0, 0, 255);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_goid_to_loid_set(0, 0, 0);
    assert_true(err == BCM_ERR_NOENT);

    /* Allocate gdid */
    err = bcmolt_apitopo_gdid_alloc(&gdid);
    assert_true(err == BCM_ERR_OK);
    err = bcmolt_apitopo_gdid_alloc(&gdid);
    assert_true(err == BCM_ERR_OK);
    assert_true(gdid == 1);
    err = bcmolt_apitopo_gdid_to_ldid_set(gdid, 255);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_gdid_to_ldid_set(gdid, 1);
    assert_true(err == BCM_ERR_OK);

    /* Set goid - loid mapping */
    err = bcmolt_apitopo_goid_to_loid_set(1, 1, 1);
    assert_true(err == BCM_ERR_OK);
    err = bcmolt_apitopo_goid_to_loid(1, &loid);
    assert_true(err == BCM_ERR_OK);
    assert_true(loid == 1);
    err = bcmolt_apitopo_loid_to_goid(1, 1, &goid);
    assert_true(err == BCM_ERR_OK);
    assert_true(goid == 1);
}

static void test_dev_id_translate(void **state)
{
    bcmolt_gdid gdid1;
    bcmolt_goid goid;
    bcmolt_ldid ldid;
    bcmolt_odid odid;
    bcmos_errno err;

    /* Translate goid -> loid before it is mapped */
    err = bcmolt_apitopo_gdid_to_ldid(255, &ldid);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_gdid_to_ldid(0, &ldid);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_gdid_to_ldid(1, &ldid);
    assert_true(err == BCM_ERR_OK);
    assert_true(ldid == 1);

    /* Translate loid -> goid before it is mapped */
    err = bcmolt_apitopo_loid_to_goid(0, 255, &goid);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_loid_to_goid(0, 1, &goid);
    assert_true(err == BCM_ERR_NOENT);

    /* Map goid - odid */
    err = bcmolt_apitopo_odid_to_gdid_set(255, 0, 0);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_odid_to_gdid_set(0, 255, 0);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_odid_to_gdid_set(0, 0, 255);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_odid_to_gdid_set(5, 0, 0);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_odid_to_gdid_set(1, 0, 1);
    assert_true(err == BCM_ERR_OK);

    /* Test mappings */
    err = bcmolt_apitopo_odid_to_gdid_ldid(255, 0, &gdid1, &ldid);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_odid_to_gdid_ldid(0, 255, &gdid1, &ldid);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_odid_to_gdid_ldid(1, 1, &gdid1, &ldid);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_odid_to_gdid_ldid(1, 0, &gdid1, &ldid);
    assert_true(err == BCM_ERR_OK);
    assert_true(gdid1 == 1);
    assert_true(ldid == 1);

    err = bcmolt_apitopo_ldid_to_odid(255, 0, &odid);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_ldid_to_odid(0, 255, &odid);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_ldid_to_odid(0, 1, &odid);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_ldid_to_odid(1, 0, &odid);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_ldid_to_odid(1, 1, &odid);
    assert_true(err == BCM_ERR_OK);
    assert_true(odid == 0);

    err = bcmolt_apitopo_olt_clear(1);
    assert_true(err == BCM_ERR_OK);
    err = bcmolt_apitopo_odid_to_gdid_ldid(1, 1, &gdid1, &ldid);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_ldid_to_odid(1, 1, &odid);
    assert_true(err == BCM_ERR_NOENT);
}


static void test_interface_translate(void **state)
{
    bcmolt_pon_pif pif;
    bcmolt_pon_lif lif;
    bcmolt_goid goid;
    bcmolt_gdid gdid1;
    bcmolt_ldid ldid;
    bcmos_errno err;

    /* Restore mappings */
    err = bcmolt_apitopo_goid_to_loid_set(1, 1, 1);
    assert_true(err == BCM_ERR_OK);
    err = bcmolt_apitopo_odid_to_gdid_set(1, 0, 1);
    assert_true(err == BCM_ERR_OK);

    err = bcmolt_apitopo_lif_to_pif_set(255, 0, 0, 0);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_lif_to_pif_set(0, 255, 0, 0);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_lif_to_pif_set(0, 0, 255, 0);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_lif_to_pif_set(0, 0, 0, 255);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_lif_to_pif_set(5, 3, 0, 2);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_lif_to_pif_set(7, 3, 0, 2);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_lif_to_pif_set(1, 3, 1, 2);
    assert_true(err == BCM_ERR_OK);

    err = bcmolt_apitopo_lif_to_pif(255, 0, &gdid1, &ldid, &pif);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_lif_to_pif(0, 255, &gdid1, &ldid, &pif);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_lif_to_pif(0, 3, &gdid1, &ldid, &pif);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_lif_to_pif(0, 0, &gdid1, &ldid, &pif);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_lif_to_pif(1, 3, &gdid1, &ldid, &pif);
    assert_true(err == BCM_ERR_OK);
    assert_true(gdid == 1);
    assert_true(ldid == 1);
    assert_true(pif == 2);

    err = bcmolt_apitopo_pif_to_lif(255, 0, &goid, &lif);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_pif_to_lif(0, 255, &goid, &lif);
    assert_true(err == BCM_ERR_PARM);
    err = bcmolt_apitopo_pif_to_lif(0, 2, &goid, &lif);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_pif_to_lif(1, 0, &goid, &lif);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_pif_to_lif(1, 2, &goid, &lif);
    assert_true(err == BCM_ERR_OK);
    assert_true(goid == 1);
    assert_true(lif == 3);

    /* Try to create an extra mapping to the same PIF */
    err = bcmolt_apitopo_goid_to_loid_set(1, 0, 0);
    assert_true(err == BCM_ERR_OK);
    err = bcmolt_apitopo_odid_to_gdid_set(0, 0, 1);
    assert_true(err == BCM_ERR_OK);
    err = bcmolt_apitopo_lif_to_pif_set(0, 1, 1, 2);
    assert_true(err == BCM_ERR_ALREADY);

    /* Free gdid and make sure that mappings fail */
    bcmolt_apitopo_gdid_free(1);
    err = bcmolt_apitopo_lif_to_pif(1, 3, &gdid1, &ldid, &pif);
    assert_true(err == BCM_ERR_NOENT);
    err = bcmolt_apitopo_pif_to_lif(1, 2, &goid, &lif);
    assert_true(err == BCM_ERR_NOENT);

}

static const struct CMUnitTest test_funcs[] =
{
    cmocka_unit_test(test_olt_id_translate),
    cmocka_unit_test(test_dev_id_translate),
    cmocka_unit_test(test_interface_translate),
};

static bcmut_file api_topology_ut_file(void)
{
    bcmolt_apitopo_init();
    return (bcmut_file){__FILE__, BCM_SIZEOFARRAY(test_funcs), test_funcs};
}

static const bcmut_file_init_cb test_files[] =
{
    api_topology_ut_file
};

extern bcmut_module api_topology_ut_tests(void);
bcmut_module api_topology_ut_tests(void)
{
    return (bcmut_module){ BCM_SIZEOFARRAY(test_files), test_files };
}
