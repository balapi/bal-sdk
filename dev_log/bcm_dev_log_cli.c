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
#include <bcm_dev_log.h>
#include <bcm_dev_log_task_internal.h>

#include <bcmcli.h>
#include <bcm_dev_log_cli.h>

/* We don't support dev_log CLI in linux kernel space */
#ifndef __KERNEL__

/* Dev log CLI session supports receiving long lines - we shall simply split them into shorter log messages. */
#define DEV_LOG_CLI_SESSION_MAX_MSG_SIZE (MAX_DEV_LOG_STRING_NET_SIZE * 10)

enum
{
    ID_BY_INDEX,
    ID_BY_NAME,
};

static bcmos_errno bcm_dev_log_file_print(uint32_t file_index, int32_t msgs_num, bcm_dev_log_print_cb print_callback, void *arg, bcmos_bool clear)
{
    bcm_dev_log_file *file;
    char log_string[MAX_DEV_LOG_STRING_SIZE];
    int length;
    uint32_t num_msgs;
    uint32_t i;
    uint32_t offset = 0;
    bcmos_errno err = BCM_ERR_OK;

    file = bcm_dev_log_file_get(file_index);
    if (!file)
        return BCM_ERR_PARM;

    num_msgs = bcm_dev_log_get_num_of_messages(file);
    if (msgs_num && msgs_num < num_msgs)
        num_msgs = msgs_num;

    DEV_LOG_INFO_PRINTF("file=%p, print %d msgs from file (orig: %d)\n", (void *)file, (int)num_msgs, (int)msgs_num);

    /* Print file */
    for (i = 0; (i < msgs_num) || !msgs_num; i++)
    {
        /* Read from file */
        length = bcm_dev_log_file_read(file, &offset, log_string, sizeof(log_string));
        if (!length)
            break;
        print_callback(arg, log_string);
    }

    if (clear == BCMOS_TRUE)
        err = bcm_dev_log_file_clear(file);

    return err;
}

static const char *dev_log_str_style(bcm_dev_log_style style)
{
    static const char *strings[] =
    {
        [BCM_DEV_LOG_STYLE_NORMAL] = "NORMAL",
        [BCM_DEV_LOG_STYLE_BOLD] = "BOLD",
        [BCM_DEV_LOG_STYLE_UNDERLINE] = "UNDERLINE",
        [BCM_DEV_LOG_STYLE_BLINK] = "BLINK",
        [BCM_DEV_LOG_STYLE_REVERSE_VIDEO] = "REVERSE_VIDEO",
    };
    return strings[style > BCM_DEV_LOG_STYLE_REVERSE_VIDEO ? BCM_DEV_LOG_STYLE_REVERSE_VIDEO : style];
}
#ifdef TRIGGER_LOGGER_FEATURE
static void bcm_dev_log_cli_session_print_features(bcmcli_session *session, const char *tabs, const dev_log_id_parm *id_parm)
{
    bcmcli_session_print(session,
        "%sthrottle : level = %c, threshold = %-5u\n",
        tabs,
        log_level_str[id_parm->throttle_log_level],
        id_parm->throttle.threshold);

    bcmcli_session_print(session,
        "%strigger : level = %c, start = %-5u, stop = %-5u, repeat = %-5u\n",
        tabs,
        log_level_str[id_parm->trigger_log_level],
        id_parm->trigger.start_threshold,
        id_parm->trigger.stop_threshold,
        id_parm->trigger.repeat_threshold);
}
#endif

static void bcm_dev_log_cli_session_print_id_parm(bcmcli_session *session, const char *tabs, const dev_log_id_parm *id_parm)
{
    bcmcli_session_print(session,
        "name=%16s, log_type=%u, default_log_type=%u, log_level_print=%c (%u), log_level_save=%c (%u), default_log_level=%c (%u), style=%s (%u), lost_msg_cnt=%u, print_skipped_count=%u\n",
        id_parm->name,
        id_parm->log_type,
        id_parm->default_log_type,
        log_level_str[id_parm->log_level_print],
        id_parm->log_level_print,
        log_level_str[id_parm->log_level_save],
        id_parm->log_level_save,
        log_level_str[id_parm->default_log_level],
        id_parm->default_log_level,
        dev_log_str_style(id_parm->style),
        id_parm->style,
        id_parm->lost_msg_cnt,
        id_parm->print_skipped_count);
    bcmcli_session_print(session,
        "%scounters          = {%c %-5u,%c %-5u,%c %-5u,%c %-5u,%c %-5u,%c %-5u}\n",
        tabs,
        log_level_str[DEV_LOG_LEVEL_NO_LOG],
        id_parm->counters[DEV_LOG_LEVEL_NO_LOG],
        log_level_str[DEV_LOG_LEVEL_FATAL],
        id_parm->counters[DEV_LOG_LEVEL_FATAL],
        log_level_str[DEV_LOG_LEVEL_ERROR],
        id_parm->counters[DEV_LOG_LEVEL_ERROR],
        log_level_str[DEV_LOG_LEVEL_WARNING],
        id_parm->counters[DEV_LOG_LEVEL_WARNING],
        log_level_str[DEV_LOG_LEVEL_INFO],
        id_parm->counters[DEV_LOG_LEVEL_INFO],
        log_level_str[DEV_LOG_LEVEL_DEBUG],
        id_parm->counters[DEV_LOG_LEVEL_DEBUG]);
#ifdef TRIGGER_LOGGER_FEATURE
    bcm_dev_log_cli_session_print_features(session, tabs, id_parm);
#endif
}

static bcmos_errno bcm_dev_log_cli_print_dev_log(
    bcmcli_session *session,
    const bcmcli_cmd_parm parm[],
    uint16_t n_parms)
{
    uint32_t i;
    bcm_dev_log_file *file;
    dev_log_id log_id = DEV_LOG_INVALID_ID;

    for (i = 0; i < DEV_LOG_MAX_FILES; i++)
    {
        file = bcm_dev_log_file_get(i);
        if (!file)
            continue;
        bcmcli_session_print(session, BCM_TAB  "file[%u]:\n", i);
        bcmcli_session_print(session, BCM_TAB2 "max_msgs = %u\n", bcm_dev_log_get_num_of_messages(file));
        bcmcli_session_print(session, BCM_TAB2 "file_parm:\n");
        bcmcli_session_print(session, BCM_TAB3 "start_addr = %p\n", dev_log.files[i].file_parm.start_addr);
        bcmcli_session_print(session, BCM_TAB3 "size       = %u\n", dev_log.files[i].file_parm.size);
        bcmcli_session_print(session, BCM_TAB3 "read_cb    = %p\n", (void *)dev_log.files[i].file_parm.read_cb);
        bcmcli_session_print(session, BCM_TAB3 "write_cb   = %p\n", (void *)dev_log.files[i].file_parm.write_cb);
        bcmcli_session_print(session, BCM_TAB3 "flags      = %x\n", dev_log.files[i].file_parm.flags);
    }
    bcmcli_session_print(session, BCM_TAB "state     = %u\n", dev_log.state);
    bcmcli_session_print(session, BCM_TAB "msg_count = %u\n", dev_log.msg_count);
    bcmcli_session_print(session, BCM_TAB "save_queue:\n");
    bcmcli_session_print(session, BCM_TAB2 "is_waiting  = %u\n", dev_log.save_queue.is_waiting);
    bcmcli_session_print(session, BCM_TAB "print_queue:\n");
    bcmcli_session_print(session, BCM_TAB2 "is_waiting  = %u\n", dev_log.print_queue.is_waiting);
    bcmcli_session_print(session, BCM_TAB "save_task:\n");
    bcmcli_session_print(session, BCM_TAB2 "active_modules  = %u\n", dev_log.save_task.active_modules);
    bcmcli_session_print(session, BCM_TAB2 "current_module  = %u\n", dev_log.save_task.current_module);
    bcmcli_session_print(session, BCM_TAB "print_task:\n");
    bcmcli_session_print(session, BCM_TAB2 "active_modules  = %u\n", dev_log.print_task.active_modules);
    bcmcli_session_print(session, BCM_TAB2 "current_module  = %u\n", dev_log.print_task.current_module);

    bcmcli_session_print(session, BCM_TAB  "ids[]:\n");
    while ((log_id = bcm_dev_log_id_get_next(log_id)) != DEV_LOG_INVALID_ID)
    {
        bcmcli_session_print(session, BCM_TAB2  "ids[%2u]: ", bcm_dev_log_get_index_by_id(log_id));
        bcm_dev_log_cli_session_print_id_parm(session, BCM_TAB3, (dev_log_id_parm *)log_id);
    }

    for (i = 0; i < log_name_table_index; i++)
    {
        if (logs_names[i].first_instance == LOG_NAME_NO_INSTANCE)
        {
            bcmcli_session_print(session, BCM_TAB2  "%s\n", logs_names[i].name);
        }
        else
        {
            bcmcli_session_print(session, BCM_TAB2  "%s %d - %d\n", logs_names[i].name, logs_names[i].first_instance, logs_names[i].last_instance);
        }
    }

    return BCM_ERR_OK;
}

static bcmos_errno bcm_dev_log_cli_logger_control(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    bcm_dev_log_set_control(parm[0].value.unumber != 0);
    return BCM_ERR_OK;
}

static bcmos_errno bcm_dev_log_cli_file_print(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    return bcm_dev_log_file_print(
        parm[0].value.unumber,
        0,
        (bcm_dev_log_print_cb)bcmcli_session_print,
        session,
        (bcmos_bool)parm[1].value.unumber);
}

static bcmos_errno bcm_dev_log_cli_file_clear(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    bcm_dev_log_file *file = bcm_dev_log_file_get(parm[0].value.unumber);
    if (!file)
        return BCM_ERR_PARM;
    return bcm_dev_log_file_clear(file);
}

static bcmos_errno bcm_dev_log_cli_file_set_flags(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log.files[parm[0].value.unumber].file_parm.flags |= (bcm_dev_log_file_flags)parm[1].value.unumber;
    return BCM_ERR_OK;
}

static bcmos_errno bcm_dev_log_cli_file_reset_flags(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log.files[parm[0].value.unumber].file_parm.flags = BCM_DEV_LOG_FILE_FLAG_NONE;
    return BCM_ERR_OK;
}

static bcmos_errno bcm_dev_log_cli_id_get(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;
    dev_log_id_parm id_parm;
    bcmos_errno err;

    id = parm[0].value.unumber == ID_BY_INDEX ? bcm_dev_log_id_get_by_index(parm[1].value.unumber) :
        bcm_dev_log_id_get_by_name(parm[1].value.string);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;

    err = bcm_dev_log_id_get(id, &id_parm);
    if (err)
    {
        bcmcli_session_print(session, "Error: can get id (err: %d)\n", err);
        return err;
    }

    bcm_dev_log_cli_session_print_id_parm(session, BCM_TAB, &id_parm);

    return BCM_ERR_OK;
}

static bcmos_errno bcm_dev_log_cli_id_set_type(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;

    id = bcm_dev_log_id_get_by_index(parm[0].value.unumber);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;

    return bcm_dev_log_id_set_type(id, (bcm_dev_log_id_type)parm[1].value.unumber);
}

static bcmos_errno bcm_dev_log_cli_id_set_level(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;

    id = bcm_dev_log_id_get_by_index(parm[0].value.unumber);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;

    return bcm_dev_log_id_set_level(
        id,
        (bcm_dev_log_level)parm[1].value.unumber,
        (bcm_dev_log_level)parm[2].value.unumber);
}

static bcmos_errno bcm_dev_log_cli_name_set_level(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;

    id = bcm_dev_log_id_get_by_name(parm[0].value.string);
    if (id == DEV_LOG_INVALID_ID)
    {
        return BCM_ERR_NOENT;
    }

    return bcm_dev_log_id_set_level(
        id,
        (bcm_dev_log_level)parm[1].value.unumber,
        (bcm_dev_log_level)parm[2].value.unumber);
}

static bcmos_errno bcm_dev_log_cli_id_set_to_default(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;

    id = bcm_dev_log_id_get_by_index(parm[0].value.unumber);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;

    return bcm_dev_log_id_set_level_and_type_to_default(id);
}

static bcmos_errno bcm_dev_log_cli_id_set_style(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;
    bcm_dev_log_style style;

    id = bcm_dev_log_id_get_by_index(bcmcli_find_named_parm(session, "index")->value.unumber);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;
    style = (bcm_dev_log_style)bcmcli_find_named_parm(session, "style")->value.unumber;

    return bcm_dev_log_id_set_style(id, style);
}

static bcmos_errno bcm_dev_log_cli_id_clear_counters(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;

    id = bcm_dev_log_id_get_by_index(parm[0].value.unumber);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;

    return bcm_dev_log_id_clear_counters(id);
}

static bcmos_errno bcm_dev_log_cli_log(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;
    bcm_dev_log_level log_level;
    uint32_t count = 1;
    const char *string;
    bcmcli_cmd_parm *cmd_parm;

    id = bcm_dev_log_id_get_by_index(parm[0].value.unumber);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;

    if ((cmd_parm = bcmcli_find_named_parm(session, "count")))
    {
        count = cmd_parm->value.unumber;
        if (!count)
        {
            count = 1;
        }
    }

    log_level = (bcm_dev_log_level)parm[1].value.unumber;
    string = parm[2].value.string;

    while (count--)
    {
        bcm_dev_log_log(id, log_level, BCM_LOG_FLAG_NONE, "%5u| Message: %s\n", count, string);
    }

    return BCM_ERR_OK;
}

static bcmos_errno bcm_dev_log_cli_set_level_and_type_all(
    bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    bcm_dev_log_id_set_all set_all = (bcm_dev_log_id_set_all)bcmcli_find_named_parm(session, "set_all")->value.unumber;
    bcmos_errno err;

    err = bcm_dev_log_set_level_and_type_all(set_all);

    if (err != BCM_ERR_OK)
    {
        bcmcli_session_print(session, "Error setting log type/level for all log IDs\n");
        return err;
    }

    return BCM_ERR_OK;
}

static bcmos_errno bcm_dev_log_cli_instance_enable(
    bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    bcmos_bool enable = (bcmos_bool)bcmcli_find_named_parm(session, "enable")->value.unumber;
    uint32_t inst = bcmcli_find_named_parm(session, "instance")->value.unumber;
    static char log_name[(MAX_DEV_LOG_ID_NAME + 1)] = {};
    dev_log_id log_id;
    bcmos_errno err;
    uint32_t i;
    char inst_str[10] = {}; /* uint32 can have up to 9 chars + 1 for NULL */

    snprintf(inst_str, sizeof(inst_str), "%u", inst);

    for (i = 0; i < log_name_table_index; i++)
    {
        if (logs_names[i].first_instance != LOG_NAME_NO_INSTANCE &&
            inst >= logs_names[i].first_instance &&
            inst <= logs_names[i].last_instance)
        {
            if ((strlen(logs_names[i].name) + strlen(inst_str)) > MAX_DEV_LOG_ID_NAME)
            {
                bcmcli_session_print(session, "Error: log name is too long %s%s\n", logs_names[i].name, inst_str);
                return BCM_ERR_INTERNAL;
            }
            strncpy(log_name, logs_names[i].name, MAX_DEV_LOG_ID_NAME);
            strncat(log_name, inst_str, MAX_DEV_LOG_ID_NAME - strlen(log_name));
            log_id = bcm_dev_log_id_get_by_name(log_name);
            if (log_id == DEV_LOG_INVALID_ID)
            {
                bcmcli_session_print(session, "Error: log ID not found: %s\n", log_name);
                return BCM_ERR_INTERNAL;
            }
            err = bcm_dev_log_id_set_type(log_id, enable ? DEV_LOG_ID_TYPE_BOTH : DEV_LOG_ID_TYPE_NONE);
            if (err != BCM_ERR_OK)
            {
                bcmcli_session_print(session, "Error setting log type: %s\n", bcmos_strerror(err));
                return err;
            }
            bcmcli_session_print(session, "Log '%s' %s\n", log_name, enable ? "enabled" : "disabled");
        }
    }

    return BCM_ERR_OK;
}

#ifdef TRIGGER_LOGGER_FEATURE
static bcmos_errno bcm_dev_log_cli_throttle(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;

    id = bcm_dev_log_id_get_by_index(parm[0].value.unumber);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;

    return bcm_dev_log_set_throttle(id, parm[1].value.unumber, parm[2].value.unumber);
}

static bcmos_errno bcm_dev_log_cli_trigger(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;
    int32_t repeat = 0;
    bcmcli_cmd_parm *cmd_parm;

    id = bcm_dev_log_id_get_by_index(parm[0].value.unumber);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;

    if ((cmd_parm = bcmcli_find_named_parm(session, "repeat")))
        repeat = cmd_parm->value.number;

    return bcm_dev_log_set_trigger(id, parm[1].value.unumber, parm[2].value.unumber, parm[3].value.unumber, repeat);
}

static bcmos_errno bcm_dev_log_cli_get_features(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    dev_log_id id;
    dev_log_id_parm id_parm;
    bcmos_errno err;

    id = bcm_dev_log_id_get_by_index(parm[0].value.unumber);
    if (id == DEV_LOG_INVALID_ID)
        return BCM_ERR_NOENT;

    err = bcm_dev_log_id_get(id, &id_parm);
    if (err)
    {
        bcmcli_session_print(session, "Error: can get id (err: %d)\n", err);
        return err;
    }

    bcm_dev_log_cli_session_print_features(session, BCM_TAB, &id_parm);

    return BCM_ERR_OK;
}
#endif

static int dev_log_cli_session_write_cb(bcmcli_session *cli_session, const char *buf, uint32_t size)
{
    bcm_dev_log_cli_session *session = bcmcli_session_user_priv(cli_session);
    char tmp_str[DEV_LOG_CLI_SESSION_MAX_MSG_SIZE] = {};
    char *p;
    uint32_t tmp_str_len;

    strncpy(tmp_str, buf, sizeof(tmp_str) - 1); /* leave room for the terminator */

    p = tmp_str;
    tmp_str_len = strlen(tmp_str);
    while (tmp_str_len > session->free_len)
    {
        /* Not enough space in 'str' for concatenating what's in 'p' -> split it. */
        strncat(session->str, p, session->free_len);
        bcm_dev_log_log(
            session->log_id, session->log_level, BCM_LOG_FLAG_NO_HEADER | BCM_LOG_FLAG_CALLER_FMT, "%s", session->str);
        *session->str = '\0';
        p += session->free_len;
        tmp_str_len -= session->free_len;
        session->free_len = MAX_DEV_LOG_STRING_NET_SIZE - 1;
    }

    /* Enough space in 'str' for concatenating what's in 'p'. */
    strncat(session->str, p, tmp_str_len);
    session->free_len -= tmp_str_len;

    /* If the message is not terminated by '\n', do not submit the message to logger yet
     * (rather save it, waiting for a later message with '\n'). */
    if (session->str[strlen(session->str) - 1] == '\n')
    {
        bcm_dev_log_log(
            session->log_id, session->log_level, BCM_LOG_FLAG_NO_HEADER | BCM_LOG_FLAG_CALLER_FMT, "%s", session->str);
        *session->str = '\0';
        session->free_len = MAX_DEV_LOG_STRING_NET_SIZE - 1;
    }

    return size;
}

bcmos_errno bcm_dev_log_cli_session_create(
    dev_log_id log_id,
    bcm_dev_log_level log_level,
    bcm_dev_log_cli_session **session)
{
    bcmos_errno err;
    bcmcli_session_parm session_params = { .write = dev_log_cli_session_write_cb };

    *session = bcmos_calloc(sizeof(bcm_dev_log_cli_session));
    if (*session == NULL)
    {
        return BCM_ERR_NOMEM;
    }

    session_params.user_priv = *session;
    err = bcmcli_session_open(&session_params, &((*session)->session));
    if (err != BCM_ERR_OK)
    {
        bcmos_free(*session);
        *session = NULL;
        return err;
    }

    (*session)->log_id = log_id;
    (*session)->log_level = log_level;
    (*session)->free_len = MAX_DEV_LOG_STRING_NET_SIZE - 1;
    return BCM_ERR_OK;
}

bcmcli_entry *bcm_dev_log_cli_init(bcmcli_entry *root_dir)
{
    bcmcli_entry *dir;
    static bcmcli_enum_val enum_table_log_level[] =
    {
        { .name = "NO_LOG", .val = (long)DEV_LOG_LEVEL_NO_LOG },
        { .name = "FATAL", .val = (long)DEV_LOG_LEVEL_FATAL },
        { .name = "ERROR", .val = (long)DEV_LOG_LEVEL_ERROR },
        { .name = "WARNING", .val = (long)DEV_LOG_LEVEL_WARNING},
        { .name = "INFO", .val = (long)DEV_LOG_LEVEL_INFO },
        { .name = "DEBUG", .val = (long)DEV_LOG_LEVEL_DEBUG },
        BCMCLI_ENUM_LAST
    };

    dir = bcmcli_dir_add(root_dir, "logger", "Dev Log", BCMCLI_ACCESS_GUEST, NULL);
    BUG_ON(dir == NULL);

    {
        BCMCLI_MAKE_CMD_NOPARM(dir, "print_dev_log", "Print Dev log", bcm_dev_log_cli_print_dev_log);
    }
    {
        BCMCLI_MAKE_CMD(dir, "logger_control", "Logger Control", bcm_dev_log_cli_logger_control,
            BCMCLI_MAKE_PARM_RANGE("enable", "enable", BCMCLI_PARM_UDECIMAL, 0, 0, 1));
    }
    {
        BCMCLI_MAKE_CMD(dir, "file_print", "Print logger file", bcm_dev_log_cli_file_print,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_MAKE_PARM_RANGE("clear", "clear", BCMCLI_PARM_UDECIMAL, 0, 0, 1));
    }
    {
        BCMCLI_MAKE_CMD(dir, "file_clear", "Clear file", bcm_dev_log_cli_file_clear,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0));
    }
    {
        static bcmcli_enum_val enum_table_file_flags[] =
        {
            { .name = "VALID", .val = (long)BCM_DEV_LOG_FILE_FLAG_VALID },
            { .name = "WRAP_AROUND", .val = (long)BCM_DEV_LOG_FILE_FLAG_WRAP_AROUND },
            { .name = "STOP_WHEN_FULL", .val = (long)BCM_DEV_LOG_FILE_FLAG_STOP_WHEN_FULL },
            BCMCLI_ENUM_LAST
        };
        BCMCLI_MAKE_CMD(dir, "file_set_flags", "Set file flags", bcm_dev_log_cli_file_set_flags,
            BCMCLI_MAKE_PARM_RANGE("index", "index", BCMCLI_PARM_UDECIMAL, 0, 0, DEV_LOG_MAX_FILES-1),
            BCMCLI_MAKE_PARM_ENUM("flags", "flags", enum_table_file_flags, 0));
    }
    {
        BCMCLI_MAKE_CMD(dir, "file_reset_flags", "Reset file flags", bcm_dev_log_cli_file_reset_flags,
            BCMCLI_MAKE_PARM_RANGE("index", "index", BCMCLI_PARM_UDECIMAL, 0, 0, DEV_LOG_MAX_FILES-1));
    }
    {
        static bcmcli_cmd_parm set1[]=
        {
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_PARM_LIST_TERMINATOR
        };
        static bcmcli_cmd_parm set2[] =
        {
            BCMCLI_MAKE_PARM("name", "name", BCMCLI_PARM_STRING, 0),
            BCMCLI_PARM_LIST_TERMINATOR
        };
        static bcmcli_enum_val selector_table[] =
        {
            { .name = "by_index", .val = ID_BY_INDEX, .parms = set1 },
            { .name = "by_name", .val = ID_BY_NAME, .parms = set2 },
            BCMCLI_ENUM_LAST
        };
        BCMCLI_MAKE_CMD(dir, "id_get", "id_get", bcm_dev_log_cli_id_get,
            BCMCLI_MAKE_PARM_SELECTOR("by", "by", selector_table, 0));
    }
    {
        static bcmcli_enum_val enum_table_log_type[] =
        {
            { .name = "none", .val = (long)DEV_LOG_ID_TYPE_NONE },
            { .name = "print", .val = (long)DEV_LOG_ID_TYPE_PRINT },
            { .name = "save", .val = (long)DEV_LOG_ID_TYPE_SAVE },
            { .name = "both", .val = (long)DEV_LOG_ID_TYPE_BOTH },
            BCMCLI_ENUM_LAST
        };

        BCMCLI_MAKE_CMD(dir, "id_set_type", "id_set_type", bcm_dev_log_cli_id_set_type,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_MAKE_PARM_ENUM("log_type", "log_type", enum_table_log_type, 0));
    }
    {
        BCMCLI_MAKE_CMD(dir, "id_set_level", "id_set_level", bcm_dev_log_cli_id_set_level,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_MAKE_PARM_ENUM("log_level_print", "log_level", enum_table_log_level, 0),
            BCMCLI_MAKE_PARM_ENUM("log_level_save", "log_level", enum_table_log_level, 0));
    }
    {
        BCMCLI_MAKE_CMD(dir, "name_set_level", "name_set_level", bcm_dev_log_cli_name_set_level,
            BCMCLI_MAKE_PARM("name", "name", BCMCLI_PARM_STRING, 0),
            BCMCLI_MAKE_PARM_ENUM("log_level_print", "log_level", enum_table_log_level, 0),
            BCMCLI_MAKE_PARM_ENUM("log_level_save", "log_level", enum_table_log_level, 0));
    }
    {
        BCMCLI_MAKE_CMD(dir, "id_set_to_default", "id_set_to_default", bcm_dev_log_cli_id_set_to_default,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0));
    }
    {
        static bcmcli_enum_val enum_table_log_style[] =
        {
            { .name = "normal", .val = (long)BCM_DEV_LOG_STYLE_NORMAL },
            { .name = "bold", .val = (long)BCM_DEV_LOG_STYLE_BOLD },
            { .name = "underline", .val = (long)BCM_DEV_LOG_STYLE_UNDERLINE },
            { .name = "blink", .val = (long)BCM_DEV_LOG_STYLE_BLINK },
            { .name = "reverse_video", .val = (long)BCM_DEV_LOG_STYLE_REVERSE_VIDEO },
            BCMCLI_ENUM_LAST
        };
        BCMCLI_MAKE_CMD(dir, "id_set_style", "id_set_style", bcm_dev_log_cli_id_set_style,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_MAKE_PARM_ENUM("style", "style", enum_table_log_style, 0));
    }
    {
        BCMCLI_MAKE_CMD(dir, "id_clear_counters", "id_clear_counters", bcm_dev_log_cli_id_clear_counters,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0));
    }
    {
        BCMCLI_MAKE_CMD(dir, "log", "log", bcm_dev_log_cli_log,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_MAKE_PARM_ENUM("log_level_print", "log_level", enum_table_log_level, 0),
            BCMCLI_MAKE_PARM("string", "string", BCMCLI_PARM_STRING, 0),
            BCMCLI_MAKE_PARM("count", "Number of messages to send", BCMCLI_PARM_UDECIMAL, BCMCLI_PARM_FLAG_OPTIONAL));
    }
    {
        BCMCLI_MAKE_CMD(dir, "instance_enable", "enable/disable instance number", bcm_dev_log_cli_instance_enable,
            BCMCLI_MAKE_PARM_ENUM("enable", "enable", bcmcli_enum_bool_table, 0),
            BCMCLI_MAKE_PARM("instance", "instance number", BCMCLI_PARM_UDECIMAL, 0));
    }
#ifdef TRIGGER_LOGGER_FEATURE
    {
        BCMCLI_MAKE_CMD(dir, "id_set_throttle", "set throttle", bcm_dev_log_cli_throttle,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_MAKE_PARM_ENUM("log_level_print", "log_level", enum_table_log_level, 0),
            BCMCLI_MAKE_PARM("throttle", "throttle", BCMCLI_PARM_UDECIMAL, 0));
    }
    {
        BCMCLI_MAKE_CMD(dir, "id_set_trigger", "set trigger", bcm_dev_log_cli_trigger,
            BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_MAKE_PARM_ENUM("log_level_print", "log_level", enum_table_log_level, 0),
            BCMCLI_MAKE_PARM("start", "start", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_MAKE_PARM("stop", "stop", BCMCLI_PARM_UDECIMAL, 0),
            BCMCLI_MAKE_PARM("repeat", "repeat", BCMCLI_PARM_DECIMAL, BCMCLI_PARM_FLAG_OPTIONAL));
    }
    {
        BCMCLI_MAKE_CMD(dir, "id_get_feature", "get feature", bcm_dev_log_cli_get_features,
           BCMCLI_MAKE_PARM("index", "index", BCMCLI_PARM_UDECIMAL, 0));
    }
#endif
    {
        static bcmcli_enum_val enum_table_log_set_all[] =
        {
            { .name = "none", .val = (long)DEV_LOG_ID_SET_ALL_NONE },
            { .name = "default", .val = (long)DEV_LOG_ID_SET_ALL_DEFAULT },
            BCMCLI_ENUM_LAST
        };

        BCMCLI_MAKE_CMD(dir, "set_level_and_type_all", "set_level_and_type_all", bcm_dev_log_cli_set_level_and_type_all,
            BCMCLI_MAKE_PARM_ENUM("set_all", "log_type", enum_table_log_set_all, 0));
    }
    return dir;
}

#endif /* #ifndef __KERNEL__ */
