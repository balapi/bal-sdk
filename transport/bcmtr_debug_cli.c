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
#include <bcmtr_debug.h>
#include <bcmtr_debug_cli.h>
#include <bcmolt_api_metadata.h>
#include <bcmolt_api_utils.h>

#define BCMTR_CLD_CAST_DISCARD_CONST(p, type)       (type)((long)(p))

static bcmcli_entry *cld_cli_dir;

static bcmos_errno _bcmtr_cld_cli_create(void);
static void _bcmtr_cld_cli_destroy(void);
static bcmolt_devid current_device;

/*
 * CLI handlers
 */

static bcmos_errno _bcmtr_cld_cli_setget_level(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    bcmcli_number obj = bcmcli_parm_get(session, "object")->value.number;
    bcmcli_cmd_parm *grp_parm = bcmcli_parm_get(session, "group");
    bcmcli_number group = grp_parm ? grp_parm->value.number : -1;
    bcmcli_cmd_parm *subgrp_parm = bcmcli_parm_get(session, "subgroup");
    bcmcli_number subgroup = subgrp_parm ? subgrp_parm->value.number : -1;
    bcmtr_cld_type level = (bcmtr_cld_type)bcmcli_parm_get(session, "level")->value.number;
    bcmtr_cld_filter filter = {};
    bcmos_errno rc;

    if (obj == -1 || !bcmcli_parm_is_set(session, bcmcli_parm_get(session, "object")))
    {
        filter.object = BCMOLT_OBJECT_ANY;
    }
    else
    {
        filter.object = (bcmolt_obj_id)obj;
    }

    if (group == -1 || !grp_parm || !bcmcli_parm_is_set(session, grp_parm))
    {
        filter.group = BCMOLT_MGT_GROUP_ANY;
    }
    else
    {
        filter.group = (bcmolt_mgt_group)group;
    }

    if (subgroup == -1 || !subgrp_parm || !bcmcli_parm_is_set(session, subgrp_parm))
    {
        filter.subgroup = BCMOLT_SUBGROUP_ANY;
    }
    else
    {
        filter.subgroup = subgroup;
    }

    /* Get or set level ? */
    if (bcmcli_parm_is_set(session, bcmcli_parm_get(session, "level")))
    {
        rc = bcmtr_cld_level_set(current_device, &filter, level);
    }
    else
    {
        rc = bcmtr_cld_level_get(current_device, &filter, &level);
        if (rc == BCM_ERR_OK)
        {
            bcmcli_session_print(session, "capture:%s log:%s dump:%s cli:%s\n",
                (level & BCMTR_CLD_CAPTURE) ? "on" : "off",
                (level & BCMTR_CLD_LOG) ? "on" : "off",
                ((level & BCMTR_CLD_DUMP) == BCMTR_CLD_DUMP) ? "all" :
                    (level & BCMTR_CLD_DUMP_HDR) ? "headers" : "off",
                (level & BCMTR_CLD_CLI) ? "on" : "off");
        }
    }

    return rc;
}

static bcmos_errno _bcmtr_cld_cli_capture_init(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    bcmcli_number size = bcmcli_parm_get(session, "size")->value.number;
    bcmos_bool stop_on_full = bcmcli_parm_get(session, "stop_on_full")->value.number;
    bcmos_bool autostart = bcmcli_parm_get(session, "autostart")->value.number;
    bcmtr_capture_parm p = {};

    p.size = size;
    p.stop_on_full = stop_on_full;
    p.activate = autostart;

    return bcmtr_capture_init(current_device, &p);
}

static bcmos_errno _bcmtr_cld_cli_capture_delete(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    bcmtr_capture_destroy(current_device);
    return BCM_ERR_OK;
}

static bcmos_errno _bcmtr_cld_cli_capture_start(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    return bcmtr_capture_start_stop(current_device, BCMOS_TRUE);
}

static bcmos_errno _bcmtr_cld_cli_capture_stop(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    return bcmtr_capture_start_stop(current_device, BCMOS_FALSE);
}

static bcmos_errno _bcmtr_cld_cli_capture_dump(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    uint32_t nmsgs;
    bcmos_errno rc;

    rc = bcmtr_capture_dump(session, current_device, &nmsgs);
    if (!rc)
    {
        bcmcli_session_print(session, "Dumped %u messages\n", nmsgs);
    }

    return BCM_ERR_OK;
}

static bcmos_errno _bcmtr_cld_cli_capture_info(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    bcmtr_capture_info info;
    bcmos_errno rc;

    rc = bcmtr_capture_info_get(current_device, &info);
    if (!rc)
    {
        bcmcli_session_print(session, "Buffer: size=%u used=%u. Events: recorded=%u lost=%d. Wraps around:%u\n",
            info.size, info.used, info.msgs, info.lost, info.wa);
    }

    return BCM_ERR_OK;
}


#ifdef BCM_SUBSYSTEM_HOST
static bcmos_errno _bcmtr_cld_cli_device(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t nparms)
{
    bcmos_errno rc = BCM_ERR_OK;

    if (nparms)
    {
        bcmcli_entry *cur_dir = bcmcli_dir_get(session);
        bcmos_bool is_cld_cur_dir = (cur_dir && cur_dir == cld_cli_dir);

        /* Set current_device and rebuild CLI */
        current_device = (bcmolt_devid)parm[0].value.number;

        /* Destroy and re-create CLD CLI directory */
        _bcmtr_cld_cli_destroy();
        rc = _bcmtr_cld_cli_create();

        /* Restore current CLI directory to CLD */
        if (!rc && is_cld_cur_dir)
            bcmcli_dir_set(session, cld_cli_dir);
    }

    bcmcli_session_print(session, "Current device: %ld\n", (long)current_device);

    return rc;
}
#endif

/* allocate memory for name and description and copy to to parm */
static bcmos_errno _bcmtr_cld_copy_parm_name(bcmcli_cmd_parm *parm, const char *name, const char *descr)
{
    parm->name = bcmos_alloc(strlen(name) + 1);
    parm->description = bcmos_alloc(strlen(descr) + 1);
    if ((parm->name == NULL) || (parm->description == NULL))
    {
        /* Successful allocation if any will be released by common cleanup
         * along with the rest of dynamic parameter fields */
        return BCM_ERR_NOMEM;
    }
    strcpy(BCMTR_CLD_CAST_DISCARD_CONST(parm->name, void *), name);
    strcpy(BCMTR_CLD_CAST_DISCARD_CONST(parm->description, void *), descr);
    return BCM_ERR_OK;
}

/* Free "level" command parameters. both name and description are allocated dynamically */
static void _bcmtr_cld_free_level_parms(bcmcli_cmd_parm *parms)
{
    bcmcli_cmd_parm *p = parms;

    while (p->name)
    {
        if (p->type == BCMCLI_PARM_ENUM && p->enum_table)
        {
            if ((p->flags & BCMCLI_PARM_FLAG_SELECTOR))
            {
                bcmcli_enum_val *e = p->enum_table;
                while(e->name)
                {
                    if (e->parms)
                    {
                        _bcmtr_cld_free_level_parms(e->parms);
                    }
                    ++e;
                }
            }
            bcmos_free(p->enum_table);
        }
        if (p->description)
            bcmos_free(BCMTR_CLD_CAST_DISCARD_CONST(p->description, void *));
        if (p->name)
            bcmos_free(BCMTR_CLD_CAST_DISCARD_CONST(p->name, void *));

        ++p;
    }
    bcmos_free(parms);
}

/* Add "level" command */
static bcmos_errno _bcmtr_cld_add_level_cmd(bcmcli_entry *dir)
{
    /* object:            *all, object list
     * group:   selector: *all, group list
     * subgroup:          *all, subgroup list
     * level:   bitmask
     */
    bcmcli_cmd_extra_parm cmd_extras = { .free_parms = _bcmtr_cld_free_level_parms };
    bcmcli_enum_val *obj_selector;
    bcmcli_cmd_parm *cmd_parms;
    static const char *all_name = "*all";
    int n_obj = 0;
    bcmolt_obj_id o;
    bcmos_errno rc = BCM_ERR_NOMEM;

    /* Allocate top level parameters: object selector, level, terminator */
    cmd_parms = bcmos_calloc(sizeof(bcmcli_cmd_parm) * 3);
    if (!cmd_parms)
    {
        return BCM_ERR_NOMEM;
    }

    /* Allocate object enum table. 2 extra entries for *all and terminator */
    obj_selector = bcmos_calloc(sizeof(bcmcli_enum_val) * (BCMOLT_OBJ_ID__NUM_OF + 2));
    if (!obj_selector)
    {
        goto cleanup;
    }

    /* Fill up parameters */
    rc = _bcmtr_cld_copy_parm_name(&cmd_parms[0], "object", "Object Name");
    cmd_parms[0].type = BCMCLI_PARM_ENUM;
    cmd_parms[0].flags = BCMCLI_PARM_FLAG_SELECTOR;
    cmd_parms[0].enum_table = obj_selector;

    rc = rc ? rc : _bcmtr_cld_copy_parm_name(&cmd_parms[1], "level", "Level bitmask: 1=capture,2=log,4=print hdr,8=print body,16=CLI");
    cmd_parms[1].type = BCMCLI_PARM_DECIMAL;
    cmd_parms[1].flags = BCMCLI_PARM_FLAG_OPTIONAL;

    /* obj_selector[0] is reserved for *all */
    obj_selector[0].name = all_name;
    obj_selector[0].val = -1;

    /* Go over objects */
    BCMOLT_API_FOR_EACH_OBJ_ID(o)
    {
        bcmcli_enum_val *grp_selector;
        bcmcli_cmd_parm *grp_parm;
        bcmolt_mgt_group g;
        const bcmolt_obj_descr *obj_descr;
        int n_grp = 0;

        /* Allocate group parameter and selector */
        ++n_obj;
        obj_selector[n_obj].val = o;
        rc = bcmolt_api_obj_descr_get(o, &obj_descr);
        if (rc != BCM_ERR_OK)
            goto cleanup;

        obj_selector[n_obj].name = obj_descr->name;
        obj_selector[n_obj].parms = grp_parm = bcmos_calloc(sizeof(bcmcli_cmd_parm)*2);
        if (!grp_parm)
            goto cleanup;
        rc = _bcmtr_cld_copy_parm_name(grp_parm, "group", "Message group");
        grp_parm->type = BCMCLI_PARM_ENUM;
        grp_parm->flags = BCMCLI_PARM_FLAG_SELECTOR;
        grp_parm->enum_table = grp_selector = bcmos_calloc(sizeof(bcmcli_enum_val) * (BCMOLT_MGT_GROUP__NUM_OF + 1));
        if (!grp_selector)
            goto cleanup;

        /* Selector 0 is reserved for *all */
        grp_selector[0].name = all_name;
        grp_selector[0].val = -1;

        /* Go over groups */
        for (g = (bcmolt_mgt_group)(BCMOLT_MGT_GROUP_KEY + 1); g < BCMOLT_MGT_GROUP__NUM_OF; g++)
        {
            uint16_t subgroup_count = bcmolt_api_group_count_get(o, g);
            bcmcli_enum_val *subgrp_table;
            bcmcli_cmd_parm *subgrp_parm;
            const bcmolt_group_descr *group_descr;
            uint16_t s;
            uint16_t sid;

            if (subgroup_count == 0)
                continue;

            ++n_grp;
            grp_selector[n_grp].name = bcmolt_mgt_group_to_str(g);
            grp_selector[n_grp].val = g;

            /* Skip subgroup selector for groups that don't support it */
            if (g != BCMOLT_MGT_GROUP_AUTO      &&
                g != BCMOLT_MGT_GROUP_OPER      &&
                g != BCMOLT_MGT_GROUP_STAT)
            {
                continue;
            }

            grp_selector[n_grp].parms = subgrp_parm = bcmos_calloc(sizeof(bcmcli_cmd_parm)*2);
            if (!subgrp_parm)
                goto cleanup;
            rc = rc ? rc : _bcmtr_cld_copy_parm_name(subgrp_parm, "subgroup", "Message sub-group");
            subgrp_parm->type = BCMCLI_PARM_ENUM;
            subgrp_parm->enum_table = subgrp_table = bcmos_calloc(sizeof(bcmcli_enum_val) * (subgroup_count + 2));
            if (!subgrp_table)
                goto cleanup;
            subgrp_table[0].name = all_name;
            subgrp_table[0].val = -1;

            /* There are subgroup_count subgroups in total, but subgroup IDs can be non contiguous.
               In the below loop s is index, sid is id. s starts from 1 because the 1st slot is taken by *all */
            for (s = 1, sid = 0; s < subgroup_count; ++sid)
            {
                if (bcmolt_api_group_descr_get(o, g, sid, &group_descr) == BCM_ERR_OK)
                {
                    subgrp_table[s].name = group_descr->name;
                    subgrp_table[s].val = sid;
                    ++s;
                }
            }
        }
    }

    /* Finally add command */
    rc = bcmcli_cmd_add(dir, "level", _bcmtr_cld_cli_setget_level, "Set/get cld level", BCMCLI_ACCESS_ADMIN,
        &cmd_extras, cmd_parms);
    if (rc)
        goto cleanup;
    return BCM_ERR_OK;

cleanup:
    _bcmtr_cld_free_level_parms(cmd_parms);
    return rc;
}

/* Create CLI commands */
static bcmos_errno _bcmtr_cld_cli_create(void)
{
    bcmcli_entry *dir;
    bcmos_errno err;

    dir = bcmcli_dir_add(NULL, "cld", "Transport Capture, Log, Debug", BCMCLI_ACCESS_ADMIN, NULL);
    BCMOS_CHECK_RETURN_ERROR(dir == NULL, BCM_ERR_NOMEM);

    err = _bcmtr_cld_add_level_cmd(dir);
    if (err)
        return err;

#ifdef BCM_SUBSYSTEM_HOST
    /* Get/set current device */
    BCMCLI_MAKE_CMD(dir, "device", "Get/Set the current device", _bcmtr_cld_cli_device,
        BCMCLI_MAKE_PARM_RANGE("device", "device index", BCMCLI_PARM_NUMBER, BCMCLI_PARM_FLAG_OPTIONAL,
            0, BCMTR_MAX_DEVICES-1));
#endif

    BCMCLI_MAKE_CMD(dir, "init", "Initialize capture buffer", _bcmtr_cld_cli_capture_init,
        BCMCLI_MAKE_PARM("size", "Buffer size (bytes)", BCMCLI_PARM_UDECIMAL, 0),
        BCMCLI_MAKE_PARM_ENUM("stop_on_full", "Stop capture when buffer is full (yes) or wrap-around (no)",
            bcmcli_enum_bool_table, 0),
        BCMCLI_MAKE_PARM_ENUM("autostart", "Autostart", bcmcli_enum_bool_table, 0) );

    BCMCLI_MAKE_CMD_NOPARM(dir, "delete", "Destroy buffer", _bcmtr_cld_cli_capture_delete);

    BCMCLI_MAKE_CMD_NOPARM(dir, "start", "Start capture", _bcmtr_cld_cli_capture_start);

    BCMCLI_MAKE_CMD_NOPARM(dir, "stop", "Stop capture", _bcmtr_cld_cli_capture_stop);

    BCMCLI_MAKE_CMD_NOPARM(dir, "dump", "Dump capture buffer", _bcmtr_cld_cli_capture_dump);

    BCMCLI_MAKE_CMD_NOPARM(dir, "info", "Capture info", _bcmtr_cld_cli_capture_info);

    cld_cli_dir = dir;

    return BCM_ERR_OK;

}

/* Destroy CLI commands */
static void _bcmtr_cld_cli_destroy(void)
{
    if (cld_cli_dir)
    {
        bcmcli_token_destroy(cld_cli_dir);
        cld_cli_dir = NULL;
    }
}


/** Initialize CLD CLI commands
 * \returns BCM_ERR_OK (0) if successful
 */
bcmos_errno bcmtr_cld_cli_init(void)
{
    bcmos_errno err = BCM_ERR_OK;

    err = _bcmtr_cld_cli_create();

    return err;
}

/** Clean-up CLD CLI commands */
void bcmtr_cld_cli_exit(void)
{
    _bcmtr_cld_cli_destroy();
}
