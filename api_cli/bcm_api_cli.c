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
#include <bcmolt_api.h>
#include <bcmolt_api_metadata.h>
#include <bcmolt_api_utils.h>
#include <bcmolt_api_writer.h>
#include <bcmolt_metadata_cli.h>
#ifdef BCM_SUBSYSTEM_HOST
#include <bcmolt_olt_selector.h>
#include <bcmolt_api_topology.h>
#endif

#include "bcm_api_cli.h"
#include "bcmolt_api_cli_handlers.h"

/* Current session */
static bcmcli_session *current_session;

/* Current device */
static bcmolt_oltid current_olt;

/* Parent directory */
static bcmcli_entry *api_parent_dir;

#ifdef BCM_SUBSYSTEM_HOST

static bcmcli_session *_apicli_log;
static bcmos_file *_apicli_log_file;

#endif

/*
 * Command handlers
 */

static bcmos_errno _apicli_objects_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    int rc;
    bcmolt_obj_id o;
    const bcmolt_obj_descr *descr;

    bcmcli_print(session, "System Object Types:\n");
    bcmcli_print(session, "=======================================\n");
    bcmcli_print(session, "Id   Name                   Description\n");
    bcmcli_print(session, "=======================================\n");
    BCMOLT_API_FOR_EACH_OBJ_ID(o)
    {
        rc = bcmolt_api_obj_descr_get(o, &descr);
        if (!rc)
            bcmcli_print(session, "%.4d %-22s %s\n", o, descr->name, descr->descr);
    }

    return BCM_ERR_OK;
}

static bcmos_errno _apicli_set_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    return bcmolt_cli_api_call(current_olt, BCMOLT_MGT_GROUP_CFG, BCMOLT_MSG_TYPE_SET, session);
}

static bcmos_errno _apicli_get_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    return bcmolt_cli_api_call(current_olt, BCMOLT_MGT_GROUP_CFG, BCMOLT_MSG_TYPE_GET, session);
}

static bcmos_errno _apicli_clear_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    return bcmolt_cli_api_call(current_olt, BCMOLT_MGT_GROUP_CFG, BCMOLT_MSG_TYPE_CLEAR, session);
}

static bcmos_errno _apicli_stat_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    return bcmolt_cli_api_call(current_olt, BCMOLT_MGT_GROUP_STAT, BCMOLT_MSG_TYPE_GET, session);
}

static bcmos_errno _apicli_oper_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    return bcmolt_cli_api_call(current_olt, BCMOLT_MGT_GROUP_OPER, BCMOLT_MSG_TYPE_SET, session);
}

static bcmos_errno _apicli_stat_cfg_set_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    return bcmolt_cli_api_call(current_olt, BCMOLT_MGT_GROUP_STAT_CFG, BCMOLT_MSG_TYPE_SET, session);
}

static bcmos_errno _apicli_stat_cfg_get_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    return bcmolt_cli_api_call(current_olt, BCMOLT_MGT_GROUP_STAT_CFG, BCMOLT_MSG_TYPE_GET, session);
}

static bcmos_errno _apicli_cfg_get_multi_handler(
    bcmcli_session *session,
    const bcmcli_cmd_parm parm[],
    uint16_t nparms)
{
    return bcmolt_cli_api_call(current_olt, BCMOLT_MGT_GROUP_CFG, BCMOLT_MSG_TYPE_GET_MULTI, session);
}

static bcmos_errno _apicli_stat_get_multi_handler(
    bcmcli_session *session,
    const bcmcli_cmd_parm parm[],
    uint16_t nparms)
{
    return bcmolt_cli_api_call(current_olt, BCMOLT_MGT_GROUP_STAT, BCMOLT_MSG_TYPE_GET_MULTI, session);
}

#ifdef BCM_SUBSYSTEM_HOST
/* Current device change indication */
static void _api_cli_olt_change_ind(bcmcli_session *session, bcmolt_oltid olt)
{
    current_olt = olt;
    bcm_api_cli_set_commands(session);
}

static int _apicli_log_write_cb(bcmcli_session *session, const char *buf, uint32_t size)
{
    if (_apicli_log_file == NULL || buf == NULL)
        return BCM_ERR_INTERNAL;
    bcmos_file_write(_apicli_log_file, buf, size);
    //fflush(_apicli_log_file);
    return BCM_ERR_OK;
}

/* Enable/disable API logging
 *       BCMCLI_MAKE_PARM("file", "Log file. Use \"-\" to disable logging", BCMCLI_PARM_STRING, 0));
 */
static bcmos_errno _apicli_log_handler(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    const char *fname = parm[0].value.string;
    bcmcli_session_parm session_params =
    {
        .write = _apicli_log_write_cb,
        .name = "api_log"
    };
    bcmos_errno rc;
    time_t start_time;

    /* Close existing log session if any */
    if (_apicli_log)
    {
        bcmcli_log_set(BCMCLI_LOG_NONE, NULL);
        bcmcli_session_close(_apicli_log);
        bcmos_file_close(_apicli_log_file);
        _apicli_log = NULL;
        _apicli_log_file = NULL;
    }

    if (!strcmp(fname, "-"))
        return BCM_ERR_OK;

    /* Starting a new log session */
    _apicli_log_file = bcmos_file_open(fname, BCMOS_FILE_FLAG_APPEND);
    if (_apicli_log_file == NULL)
    {
        bcmcli_print(session, "Can't open file %s for logging\n", fname);
        return BCM_ERR_PARM;
    }
    rc = bcmcli_session_open_user(&session_params, &_apicli_log);
    if (rc)
    {
        bcmos_file_close(_apicli_log_file);
        _apicli_log_file = NULL;
        bcmcli_print(session, "Can't open log session. Error %s\n", bcmos_strerror(rc));
        return rc;
    }
    time(&start_time);
    bcmcli_log_set(BCMCLI_LOG_C_COMMENT, _apicli_log);
    bcmcli_log("/* API logging session started. %s */\n", ctime(&start_time));
    return BCM_ERR_OK;
}

#endif /* #ifdef BCM_SUBSYSTEM_HOST */

static bcmos_errno _apicli_set_filter(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    const bcmcli_cmd_parm *state_parm = bcmcli_find_named_parm(session, "state");
    if (NULL != state_parm)
    {
        bcmolt_api_cli_filter_set((bcmos_bool)state_parm->value.enum_val);
    }

    bcmcli_print(session, "Filtering by tags is %sabled\n", bcmolt_api_cli_filter_get() ? "en" : "dis");

    return BCM_ERR_OK;
}

static void api_cli_find_del_cmd(bcmcli_entry *dir, const char *cmd_name)
{
    bcmcli_entry *cmd;
    cmd = bcmcli_cmd_find(dir, cmd_name);
    if (cmd)
    {
        bcmcli_token_destroy(cmd);
    }
}

/* Unregisters commands and directories */
static void api_cli_del_commands(bcmcli_session *session)
{
    bcmcli_entry *dir;

    dir = bcmcli_dir_find(api_parent_dir, "api");
    if (!dir)
    {
        return;
    }
    api_cli_find_del_cmd(dir, "set");
    api_cli_find_del_cmd(dir, "get");
    api_cli_find_del_cmd(dir, "multiget");
    api_cli_find_del_cmd(dir, "clear");
    api_cli_find_del_cmd(dir, "modify");
    api_cli_find_del_cmd(dir, "stat");
    api_cli_find_del_cmd(dir, "multistat");
    api_cli_find_del_cmd(dir, "oper");
    api_cli_find_del_cmd(dir, "saset");
    api_cli_find_del_cmd(dir, "saget");
    api_cli_find_del_cmd(dir, "register");
    api_cli_find_del_cmd(dir, "unregister");
    api_cli_find_del_cmd(dir, "objects");
#ifdef BCM_SUBSYSTEM_HOST
    api_cli_find_del_cmd(dir, "log");
#endif
}

static bcmos_errno _api_cli_add(
    bcmcli_entry *dir,
    const char *cmd_name,
    const char *cmd_descr,
    bcmolt_mgt_group group,
    bcmcli_cmd_cb cmd_handler,
    bcmolt_metadata_cli_flags flags)
{
    return bcmolt_metadata_cli_command_add(
        current_session,
        bcmolt_api_metadata,
        dir,
        cmd_name,
        cmd_descr,
        group,
        cmd_handler,
        flags);
}

/* Registers commands and directories */
static bcmos_errno _api_cli_add_commands(bcmcli_session *session)
{
    bcmcli_entry *api_dir;
    bcmos_errno rc;

    if ((api_dir = bcmcli_dir_find(api_parent_dir, "api")) == NULL)
    {
        api_dir = bcmcli_dir_add(api_parent_dir, "api", "Maple API", BCMCLI_ACCESS_GUEST, NULL);
        if (api_dir == NULL)
        {
            bcmcli_session_print(session, "Can't create api directory\n");
            return BCM_ERR_INTERNAL;
        }
    }

    current_session = session;

    /* Now generate and add commands */
    rc = _api_cli_add(api_dir, "set", "Set object configuration", BCMOLT_MGT_GROUP_CFG,
        _apicli_set_handler, BCMOLT_METADATA_CLI_FLAGS_ACCESS_WRITE);
    rc = rc ? rc : _api_cli_add(api_dir, "get", "Get object configuration", BCMOLT_MGT_GROUP_CFG,
        _apicli_get_handler, BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ);
    rc = rc ? rc : _api_cli_add(api_dir, "clear", "Clear object configuration", BCMOLT_MGT_GROUP_CFG,
        _apicli_clear_handler,
        (bcmolt_metadata_cli_flags)(BCMOLT_METADATA_CLI_FLAGS_IGNORE_FIELDS | BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ));
    rc = rc ? rc : _api_cli_add(api_dir, "stat", "Get statistics", BCMOLT_MGT_GROUP_STAT,
        _apicli_stat_handler, BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ);
    rc = rc ? rc : _api_cli_add(api_dir, "oper", "Initiate Operation", BCMOLT_MGT_GROUP_OPER,
        _apicli_oper_handler, BCMOLT_METADATA_CLI_FLAGS_ACCESS_WRITE);
    rc = rc ? rc : _api_cli_add(api_dir, "saset", "Set statistic alarm configuration",
        BCMOLT_MGT_GROUP_STAT_CFG, _apicli_stat_cfg_set_handler, BCMOLT_METADATA_CLI_FLAGS_ACCESS_WRITE);
    rc = rc ? rc : _api_cli_add(api_dir, "saget", "Get statistic alarm configuration",
        BCMOLT_MGT_GROUP_STAT_CFG, _apicli_stat_cfg_get_handler, BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ);
    rc = rc ? rc : _api_cli_add(api_dir, "multiget", "Get configuration for multiple objects",
        BCMOLT_MGT_GROUP_CFG, _apicli_cfg_get_multi_handler,
        (bcmolt_metadata_cli_flags)(BCMOLT_METADATA_CLI_FLAGS_MULTI | BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ));
    rc = rc ? rc : _api_cli_add(api_dir, "multistat", "Get statistics for multiple objects",
        BCMOLT_MGT_GROUP_STAT, _apicli_stat_get_multi_handler,
        (bcmolt_metadata_cli_flags)(BCMOLT_METADATA_CLI_FLAGS_MULTI | BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ));

    /* List all system objects */
    rc = rc ? rc : bcmcli_cmd_add(api_dir, "objects", _apicli_objects_handler,
        "Object Types", BCMCLI_ACCESS_GUEST, NULL, NULL);

#if defined(BCM_SUBSYSTEM_HOST)
    BCMCLI_MAKE_CMD(api_dir, "log", "Log API calls", _apicli_log_handler,
        BCMCLI_MAKE_PARM("file", "Log file. Use \"-\" to disable logging", BCMCLI_PARM_STRING, 0));
#endif

    BCMCLI_MAKE_CMD(api_dir, "filter", "Filter get responses based on system mode", _apicli_set_filter,
        BCMCLI_MAKE_PARM_ENUM("state", "Filter state", bcmcli_enum_bool_table, BCMCLI_PARM_FLAG_OPTIONAL));

    return rc;
}

/* Update API CLI commands for the current device */
bcmos_errno bcm_api_cli_set_commands(bcmcli_session *session)
{
    bcmos_errno rc;
    api_cli_del_commands(session);
    rc = _api_cli_add_commands(session);
    return rc;
}

/* Init API CLI commands for the current device */
bcmos_errno bcm_api_cli_init(bcmcli_entry *parent_dir, bcmcli_session *session)
{
    bcmos_errno rc;

    api_parent_dir = parent_dir;

    rc = bcm_api_cli_set_commands(session);

#ifdef BCM_SUBSYSTEM_HOST
    /* Subscribe for device change indication */
    rc = rc ? rc : bcmolt_olt_sel_ind_register(_api_cli_olt_change_ind);
#endif

    return rc;
}

