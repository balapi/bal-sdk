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

#include <bcmos_system.h>
#include <bcmcli.h>
#include <bcmolt_api_utils.h>
#include <bcmtr_interface.h>
#include <bcmtr_internal.h>
#include <bcmtr_transport_cli.h>
#include <bcmolt_api_metadata.h>
#ifdef BCMTR_PERFTEST
#include <test/bcmtr_perftest.h>
#endif

/*
 * CLI support
 */
static bcmcli_entry *trcli_dir;

/* Connect
   BCMCLI_MAKE_PARM_RANGE("device", "Device index", BCMCLI_PARM_DECIMAL, 0,
   BCMCLI_MAKE_PARM_RANGE("type", "Transport_type", BCMCLI_PARM_ENUM, 0,
   BCMCLI_MAKE_PARM("peer_ip_addr", "IP address", BCMCLI_PARM_IP, BCMCLI_PARM_FLAG_OPTIONAL),
   BCMCLI_MAKE_PARM_RANGE("peer_udp_port", "UDP port", BCMCLI_PARM_NUMBER, BCMCLI_PARM_FLAG_OPTIONAL,
        0, 0xffff));
*/
static bcmos_errno _bcmtr_cli_connect(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    bcmolt_devid device = (bcmolt_devid)bcmcli_parm_get(session, "device")->value.number;
    bcmtr_conn_parms conn_parms = {};
    bcmcli_cmd_parm *p;

    conn_parms.type = (bcmtr_transport_type)bcmcli_parm_get(session, "type")->value.number;

    p = bcmcli_parm_get(session, "peer_ip_addr");
    if (bcmcli_parm_is_set(session, p))
        conn_parms.x.cm.udp.ip.u32 = p->value.number;

    p = bcmcli_parm_get(session, "peer_udp_port");
    if (bcmcli_parm_is_set(session, p))
        conn_parms.x.cm.udp.port = p->value.number;

    return bcmtr_connect(device, &conn_parms);
}

/* Disconnect
   BCMCLI_MAKE_PARM_RANGE("device", "Device index", BCMCLI_PARM_DECIMAL, 0,
   */
static bcmos_errno _bcmtr_cli_disconnect(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    bcmolt_devid device = (bcmolt_devid)parm[0].value.number;
    return bcmtr_disconnect(device);
}

/* Stat
   BCMCLI_MAKE_PARM_RANGE("device", "Device index", BCMCLI_PARM_DECIMAL, 0,
   */
static bcmos_errno _bcmtr_cli_stat(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    bcmolt_devid device = (bcmolt_devid)parm[0].value.number;
    bcmtr_stat stat;
    bcmos_errno err;

    err = bcmtr_stat_get(device, &stat);
    if (err)
        return err;

    bcmcli_session_print(session, "%-24s : %d\n", "msg_sent", stat.msg_sent);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_resp_received", stat.msg_resp_received);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_req_auto_received", stat.msg_req_auto_received);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_req_timeout", stat.msg_req_timeout);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_reass_timeout", stat.msg_reass_timeout);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_no_req", stat.msg_no_req);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_no_mem", stat.msg_no_mem);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_comm_err", stat.msg_comm_err);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_ready_timeout", stat.msg_ready_timeout);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_too_many_req", stat.msg_too_many_req);
    bcmcli_session_print(session, "%-24s : %d\n", "msg_too_many_auto", stat.msg_too_many_auto);
    bcmcli_session_print(session, "%-24s : %d\n", "frag_received", stat.frag_received);
    bcmcli_session_print(session, "%-24s : %d\n", "frag_invalid", stat.frag_invalid);
    bcmcli_session_print(session, "%-24s : %d\n", "translation_errors", stat.translate_errors);
    bcmcli_session_print(session, "%-24s : %d\n", "unpack_errors", stat.unpack_errors);
    bcmcli_session_print(session, "%-24s : %d\n", "pack_errors", stat.pack_errors);
    bcmcli_session_print(session, "%-24s : %d\n", "no_rx_handler", stat.no_rx_handler);
    bcmcli_session_print(session, "%-24s : %d\n", "not_connected", stat.not_connected);

    return BCM_ERR_OK;
}

/* Register
   BCMCLI_MAKE_PARM_RANGE("device", "Device index", BCMCLI_PARM_DECIMAL, 0,
   */
static bcmos_errno _bcmtr_cli_register_info(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    bcmolt_devid device = (bcmolt_devid)parm[0].value.number;
    bcmtr_handler_parm p =
    {
        .instance = (uint8_t)parm[1].value.number,
        .group = (bcmolt_mgt_group)parm[2].value.number,
    };

    if (p.instance >= BCMTR_MAX_INSTANCES)
    {
        return BCM_ERR_PARM;
    }

    BCMOLT_API_FOR_EACH_OBJ_ID(p.object)
    {
        bcmolt_api_group_id group_id;
        const bcmolt_obj_descr *obj_descr;
        const bcmolt_group_descr *group_descr;

        if (bcmolt_api_obj_descr_get(p.object, &obj_descr) != BCM_ERR_OK)
            continue;

        for (p.subgroup = 0; bcmtr_msg_handler_register_get(device, &p) == BCM_ERR_OK; p.subgroup++)
        {
            bcmos_errno err = bcmolt_api_group_id_combine(p.object, p.group, p.subgroup, &group_id);
            BCMOS_RETURN_IF_ERROR(err);

            if (bcmolt_api_group_descr_get(p.object, p.group, p.subgroup, &group_descr) != BCM_ERR_OK)
                continue;

            bcmcli_session_print(session, "%s - %s : msg_id=%u ", obj_descr->name, group_descr->name, group_id);
            if (p.app_cb)
            {
                bcmcli_session_print(session, "module:%d func:%p\n", p.module, p.app_cb);
            }
            else
            {
                bcmcli_session_print(session, "NONE\n");
            }
        }
    }
    return BCM_ERR_OK;
}


bcmos_errno bcmtr_cli_init(void)
{
    if ((trcli_dir=bcmcli_dir_find(NULL, "transport")) != NULL)
        return BCM_ERR_ALREADY;
    trcli_dir = bcmcli_dir_add(NULL, "transport", "Maple Transport", BCMCLI_ACCESS_GUEST, NULL);
    if (!trcli_dir)
    {
        printf("Can't create transport directory\n");
        return BCM_ERR_INTERNAL;
    }

    {
        static bcmcli_enum_val transport_type_enum_table[] = {
            { .name = "conn_mgr", .val = (long)BCMTR_TRANSPORT_TYPE_CONN_MGR },
            { .name = "pcie", .val = (long)BCMTR_TRANSPORT_TYPE_PCIE },
            { .name = "unix_domain", .val = (long)BCMTR_TRANSPORT_TYPE_UNIX_DOMAIN },
            { .name = "trmux", .val = (long)BCMTR_TRANSPORT_TYPE_TRMUX },
            BCMCLI_ENUM_LAST
        };
        BCMCLI_MAKE_CMD(trcli_dir, "connect", "Connect", _bcmtr_cli_connect,
            BCMCLI_MAKE_PARM_RANGE("device", "Device index", BCMCLI_PARM_DECIMAL, 0,
                0, BCMTR_MAX_DEVICES-1),
            BCMCLI_MAKE_PARM_ENUM("type", "type", transport_type_enum_table, 0)
#if defined(BCMTR_UDP_SUPPORT)
            ,BCMCLI_MAKE_PARM("peer_ip_addr", "IP address", BCMCLI_PARM_IP, BCMCLI_PARM_FLAG_OPTIONAL),
            BCMCLI_MAKE_PARM_RANGE("peer_udp_port", "UDP port", BCMCLI_PARM_NUMBER, BCMCLI_PARM_FLAG_OPTIONAL,
                0, 0xffff)
#endif
                );
    }

    BCMCLI_MAKE_CMD(trcli_dir, "disconnect", "Disconnect", _bcmtr_cli_disconnect,
        BCMCLI_MAKE_PARM_RANGE("device", "Device index", BCMCLI_PARM_DECIMAL, 0,
        0, BCMTR_MAX_DEVICES-1));

    BCMCLI_MAKE_CMD(trcli_dir, "stat", "Transport statistics", _bcmtr_cli_stat,
        BCMCLI_MAKE_PARM_RANGE("device", "Device index", BCMCLI_PARM_DECIMAL, 0,
        0, BCMTR_MAX_DEVICES-1));

    {
        static bcmcli_enum_val groups[] =
        {
#if defined(BCM_SUBSYSTEM_HOST) || defined(BCM_SUBSYSTEM_OPENCPU)
            { .name = "auto", .val = BCMOLT_MGT_GROUP_AUTO },
#else
            { .name = "cfg", .val = BCMOLT_MGT_GROUP_CFG },
            { .name = "stat", .val = BCMOLT_MGT_GROUP_STAT },
            { .name = "stat_cfg", .val = BCMOLT_MGT_GROUP_STAT_CFG },
            { .name = "oper", .val = BCMOLT_MGT_GROUP_OPER },
#endif
            { .name = NULL }

        };
        BCMCLI_MAKE_CMD(trcli_dir, "registration", "Transport RX registration info", _bcmtr_cli_register_info,
            BCMCLI_MAKE_PARM_RANGE("device", "Device index", BCMCLI_PARM_DECIMAL, 0,
            0, BCMTR_MAX_DEVICES-1),
            BCMCLI_MAKE_PARM_RANGE("pon_ni", "PON NI", BCMCLI_PARM_DECIMAL, 0,
            0, BCMTR_MAX_INSTANCES-1),
            BCMCLI_MAKE_PARM_ENUM("group", "Management group", groups, 0) );
    }

    /* Performance testing directory */
#ifdef BCMTR_PERFTEST
    bcmtr_test_init();
#endif

    return BCM_ERR_OK;
}

void bcmtr_cli_exit(void)
{
    if (trcli_dir)
    {
        bcmcli_token_destroy(trcli_dir);
        trcli_dir = NULL;
    }
}
