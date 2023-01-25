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
#include <bcmcli.h>
#include "bcmolt_set_metadata.h"
#include "bcmolt_type_metadata.h"
#include "bcmolt_metadata_cli.h"

#define METACLI_CAST_DISCARD_CONST(p, type)       (type)((long)(p))
#define METACLI_DEFAULT_BUFFER_MAX_LENGTH         4096

/* bool enum table */
static bcmcli_enum_val bool_enum[] =
{
    { .name = "yes", .val = 1 },
    { .name = "no", .val = 0 },
    BCMOLT_ENUM_LAST,
};

static bcmos_bool _metacli_is_skip_field(const bcmolt_field_descr *fd, bcmolt_metadata_cli_flags flags)
{
    const char *name = fd->cli_name ? fd->cli_name : fd->name;

    if ((flags & BCMOLT_METADATA_CLI_FLAGS_ACCESS_WRITE) && (fd->flags & BCMOLT_FIELD_FLAGS_READ_ONLY))
        return BCMOS_TRUE;

    return (name == NULL || !strcmp(name, "reserved")) ? BCMOS_TRUE : BCMOS_FALSE;
}

/* calculate number of fields in type */
static uint32_t _metacli_get_num_fields_in_type(const bcmolt_type_descr *td, bcmolt_metadata_cli_flags flags)
{
    uint16_t f;
    uint32_t nf = 0;

    switch (td->base_type)
    {
        case BCMOLT_BASE_TYPE_ID_STRUCT:
        {
            if (!td->x.s.num_fields)
                return 0;
            BUG_ON(!td->x.s.fields);
            for (f = 0; f < td->x.s.num_fields; f++)
            {
                if (!_metacli_is_skip_field(&td->x.s.fields[f], flags))
                    ++nf;
            }
            break;
        }

        case BCMOLT_BASE_TYPE_ID_UNION:
        {
            /* Union. Count only common fields */
            if (!td->x.u.num_common_fields)
                return 0;
            BUG_ON(!td->x.u.common_fields);
            for (f = 0; f < td->x.u.num_common_fields; f++)
            {
                if (!_metacli_is_skip_field(&td->x.u.common_fields[f], flags))
                    ++nf;
            }
            break;
        }

        default:
        {
            nf = 1;
            break;
        }
    }

    return nf;
}

static void _metacli_set_num_range(const bcmolt_type_descr *td, bcmcli_cmd_parm *cmd_parm)
{
    /* Explicit range ? */
    if (td->min_val != td->max_val || td->min_val)
    {
        cmd_parm->flags |= BCMCLI_PARM_FLAG_RANGE;
        cmd_parm->low_val = td->min_val;
        cmd_parm->hi_val = td->max_val;
        return;
    }

    /* Do not check range of 4 byte numbers */
    if (td->size >= 4)
        return;

    if (td->base_type == BCMOLT_BASE_TYPE_ID_UNUM ||
        td->base_type == BCMOLT_BASE_TYPE_ID_UNUM_HEX)
    {
        cmd_parm->hi_val = (1LL << td->size*8) - 1;
        cmd_parm->flags |= BCMCLI_PARM_FLAG_RANGE;
    }
    else if (td->base_type == BCMOLT_BASE_TYPE_ID_SNUM)
    {
        cmd_parm->hi_val = (1LL << (td->size*8 - 1)) - 1;
        cmd_parm->low_val = 0 - cmd_parm->hi_val - 1;
        cmd_parm->flags |= BCMCLI_PARM_FLAG_RANGE;
    }
}

/* clone enum table */
static bcmcli_enum_val *_metacli_clone_enum_table(const bcmolt_enum_val *enum_metadata)
{
    const bcmolt_enum_val *val = enum_metadata;
    bcmcli_enum_val *clone_table;
    long n;

    for( val = enum_metadata, n = 0; val && val->name; ++val )
        ++n;

    clone_table = bcmos_calloc(sizeof(bcmcli_enum_val) * (n + 1));
    if (!clone_table)
    {
        return NULL;
    }
    for( val = enum_metadata, n = 0; val && val->name; ++val, ++n )
    {
        clone_table[n].name = val->name;
        clone_table[n].val = val->val;
    }
    return clone_table;
}

/* map to CLI type */
static bcmos_errno _metacli_map_type(bcmcli_session *session, const bcmolt_type_descr *td, bcmcli_cmd_parm *parm)
{
    bcmos_errno rc = BCM_ERR_OK;

    /* Map type */
    switch(td->base_type)
    {
    case BCMOLT_BASE_TYPE_ID_SNUM:
        parm->type = BCMCLI_PARM_NUMBER;
        break;
    case BCMOLT_BASE_TYPE_ID_UNUM:
        parm->type = BCMCLI_PARM_UNUMBER;
        break;
    case BCMOLT_BASE_TYPE_ID_UNUM_HEX:
        parm->type = BCMCLI_PARM_HEX;
        break;
    case BCMOLT_BASE_TYPE_ID_BOOL:
        parm->type = BCMCLI_PARM_ENUM;
        parm->enum_table = bool_enum;
        break;
    case BCMOLT_BASE_TYPE_ID_FLOAT:
        parm->type = td->size == sizeof(double) ? BCMCLI_PARM_DOUBLE : BCMCLI_PARM_FLOAT;
        break;
    case BCMOLT_BASE_TYPE_ID_STRING:
        parm->type = BCMCLI_PARM_STRING;
        break;
    case BCMOLT_BASE_TYPE_ID_IPV4:
        parm->type = BCMCLI_PARM_IP;
        break;
    case BCMOLT_BASE_TYPE_ID_IPV6:
        parm->type = BCMCLI_PARM_IPV6;
        break;
    case BCMOLT_BASE_TYPE_ID_MAC:
        parm->type = BCMCLI_PARM_MAC;
        break;
    case BCMOLT_BASE_TYPE_ID_ENUM:
        parm->type = BCMCLI_PARM_ENUM;
        parm->enum_table = _metacli_clone_enum_table(td->x.e.vals);
        if (!parm->enum_table)
            rc = BCM_ERR_NOMEM;
        break;
    case BCMOLT_BASE_TYPE_ID_ENUM_MASK:
        parm->type = BCMCLI_PARM_ENUM_MASK;
        parm->enum_table = _metacli_clone_enum_table(td->x.e.vals);
        if (!parm->enum_table)
            rc = BCM_ERR_NOMEM;
        break;
    case BCMOLT_BASE_TYPE_ID_STRUCT:
    case BCMOLT_BASE_TYPE_ID_UNION:
        parm->type = BCMCLI_PARM_STRUCT;
        break;
    case BCMOLT_BASE_TYPE_ID_BINARY_DYN:
    case BCMOLT_BASE_TYPE_ID_BINARY_FIXED:
        parm->type = BCMCLI_PARM_BUFFER;
        break;
    default:
        bcmcli_print(session, "*** can't map type %s (%d)\n", td->name, (int)td->base_type);
        rc = BCM_ERR_NOT_SUPPORTED;
        break;
    }

    return rc;
}

/* populate single parameter */
static bcmos_errno _metacli_parm_populate_1(
    bcmcli_session *session,
    const bcmolt_field_descr *pd,
    const bcmolt_type_descr *td,
    const bcmolt_type_descr *elem_td,
    bcmcli_cmd_parm *parm,
    uint32_t parm_flags)
{
    bcmos_errno rc;

    parm->name = pd->name;
    parm->description = pd->descr;
    parm->flags = parm_flags;
    parm->user_data = METACLI_CAST_DISCARD_CONST(pd, void *);
    if (pd->flags & BCMOLT_FIELD_FLAGS_OPTIONAL_FLAG)
        parm->flags |= BCMCLI_PARM_FLAG_OPTIONAL;

    /* Set parameter type */
    rc = _metacli_map_type(session, elem_td, parm);
    if (rc != BCM_ERR_OK)
    {
        return rc;
    }

    /* If the parameter is a buffer, allocate memory for it. */
    if (parm->type == BCMCLI_PARM_BUFFER)
    {
        uint32_t buf_size = td->base_type == BCMOLT_BASE_TYPE_ID_BINARY_FIXED
            ? td->x.binary_fixed.len
            : METACLI_DEFAULT_BUFFER_MAX_LENGTH;

        parm->value.buffer.start = bcmos_calloc(buf_size);
        if (!parm->value.buffer.start)
            return BCM_ERR_NOMEM;
        bcmolt_buf_init(&parm->value.buffer, buf_size, parm->value.buffer.start);
    }

    /* Arrays require more work.
     * - Calculate size. Known for fixed arrays, hard-coded max for dynamic.
     * - Allocate array of values based on CLI parameter type.
     */
    if (td != elem_td)
    {
        uint32_t array_size = td->base_type == BCMOLT_BASE_TYPE_ID_ARR_FIXED
            ? td->x.arr_fixed.size
            : td->x.arr_dyn.max_size;

        if (!array_size)
        {
            bcmcli_print(session, "*** Error in %s array descriptor. Size is not set.\n", td->name);
            return BCM_ERR_INTERNAL;
        }

        parm->values = bcmos_calloc(sizeof(bcmcli_parm_value) * array_size);
        if (!parm->values)
        {
            return BCM_ERR_NOMEM;
        }
        parm->max_array_size = array_size;
        /* If parameter is struct or union, propagate field set per array value */
        if (parm->type == BCMCLI_PARM_STRUCT)
        {
            int i;
            for (i=0; i<array_size; i++)
            {
                parm->values[i].fields = parm->value.fields;
            }
        }
    }

    /* Set range */
    if (parm->type == BCMCLI_PARM_NUMBER  ||
        parm->type == BCMCLI_PARM_UNUMBER ||
        parm->type == BCMCLI_PARM_HEX)
    {
        _metacli_set_num_range(elem_td, parm);
    }

    return BCM_ERR_OK;
}

/* Allocate CLI parameter array */
static bcmcli_cmd_parm *_metacli_parm_array_alloc(int nparms)
{
    bcmcli_cmd_parm *parms;
    parms = bcmos_calloc(sizeof(bcmcli_cmd_parm) * (nparms + 1));
    return parms;
}

/* Populate struct/union fields */
static bcmos_errno _metacli_populate_struct_fields(
    bcmcli_session *session,
    const bcmolt_type_descr *td,
    bcmcli_cmd_parm *parms,
    uint32_t num_parms,
    bcmolt_metadata_cli_flags flags,
    uint32_t parm_flags,
    bcmcli_cmd_parm **p_sel_parm)
{
    uint32_t num_meta_fields;
    const bcmolt_field_descr *fields;
    bcmcli_cmd_parm *sel_parm = NULL;
    bcmos_errno rc = BCM_ERR_OK;
    uint32_t f, p;

    if (td->base_type == BCMOLT_BASE_TYPE_ID_STRUCT)
    {
        num_meta_fields = td->x.s.num_fields;
        fields = td->x.s.fields;
    }
    else
    {
        num_meta_fields = td->x.u.num_common_fields;
        fields = td->x.u.common_fields;
    }
    for (f=0, p=0; f<num_meta_fields && rc == BCM_ERR_OK; f++)
    {
        if (_metacli_is_skip_field(&fields[f], flags))
            continue;
        if (p >= num_parms)
            break;
        if ((td->base_type == BCMOLT_BASE_TYPE_ID_UNION) && (f == td->x.u.classifier_idx))
            sel_parm = &parms[p];
        rc = bcmolt_metadata_cli_parm_populate_from_pd(session, &fields[f], &parms[p], flags, parm_flags);
        ++p;
    }
    if (p != num_parms)
    {
        bcmcli_print(session, "%s: %s: calculated and populated number of structure fields don't match %u/%u\n",
            __FUNCTION__, td->name, num_parms, p);
        rc = BCM_ERR_INTERNAL;
    }

    if (p_sel_parm)
        *p_sel_parm = sel_parm;

    return rc;
}

static const bcmolt_type_descr *_metacli_get_type_descr_for_read(const bcmolt_type_descr *td)
{
    /* For read access, instead of setting the property, we specify whether or not to read it.
     * - Simple types: boolean ("yes" to read).
     * - Structs: struct full of booleans ("{}" to read all, "{sub_field=yes}" to read a sub-field only.
     * - Unions: same as structs, but union sub-structures cannot be included (sub-structs will be read
     *           if the selector field is read).
     * - Arrays: allow reading of individual indices (e.g. "array_field[0]={sub_field=yes}").
     */
    switch (td->base_type)
    {
        case BCMOLT_BASE_TYPE_ID_ARR_DYN:
        case BCMOLT_BASE_TYPE_ID_ARR_FIXED:
        case BCMOLT_BASE_TYPE_ID_STRUCT:
        case BCMOLT_BASE_TYPE_ID_UNION:
            /* don't change the type - continue to recurse down the tree */
            return td;
        default:
            return &type_descr_bcmos_bool;
    }
}

bcmos_errno bcmolt_metadata_cli_parm_populate_from_pd(
    bcmcli_session *session,
    const bcmolt_field_descr *pd,
    bcmcli_cmd_parm *parm,
    bcmolt_metadata_cli_flags flags,
    uint32_t parm_flags)
{
    const bcmolt_type_descr *td = pd->type;
    const bcmolt_type_descr *elem_td;
    uint32_t nf;
    bcmos_errno rc = BCM_ERR_OK;

    if (_metacli_is_skip_field(pd, flags))
        return BCM_ERR_OK;

    if ((flags & BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ))
    {
        td = _metacli_get_type_descr_for_read(td);
        parm_flags |= BCMCLI_PARM_FLAG_OMIT_VAL;
    }

    /* In case of arrays we should
     * - store array type descriptor FFU and replace the "current" type descriptor with element type
     */
    elem_td = td;
    if (td->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN || td->base_type == BCMOLT_BASE_TYPE_ID_ARR_FIXED)
    {
        elem_td = td->base_type == BCMOLT_BASE_TYPE_ID_ARR_DYN ? td->x.arr_dyn.elem_type : td->x.arr_fixed.elem_type;
        if ((flags & BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ))
            elem_td = _metacli_get_type_descr_for_read(elem_td);
    }

    if (elem_td->base_type == BCMOLT_BASE_TYPE_ID_STRUCT || elem_td->base_type == BCMOLT_BASE_TYPE_ID_UNION)
    {
        /* Struct or union */
        bcmcli_cmd_parm *field_parms;
        bcmcli_cmd_parm *sel_parm = NULL;

        nf = _metacli_get_num_fields_in_type(elem_td, flags);
        if (!nf)
            return BCM_ERR_OK;
        BUG_ON(!elem_td->x.s.fields);
        field_parms = _metacli_parm_array_alloc(nf);
        if (field_parms == NULL)
            return BCM_ERR_NOMEM;
        parm->value.fields = field_parms;
        rc = _metacli_populate_struct_fields(session, elem_td, field_parms, nf, flags, parm_flags, &sel_parm);

        /* For union set up selector */
        if ((flags & (BCMOLT_METADATA_CLI_FLAGS_ACCESS_WRITE | BCMOLT_METADATA_CLI_FLAGS_ACCESS_WRITE_ALL))
            && elem_td->base_type == BCMOLT_BASE_TYPE_ID_UNION
            && sel_parm != NULL)
        {
            bcmcli_enum_val *e;
            BUG_ON(sel_parm->enum_table == NULL);

            /* Now set-up selector */
            sel_parm->flags |= BCMCLI_PARM_FLAG_SELECTOR;

            for(e = sel_parm->enum_table; e && e->name && rc == BCM_ERR_OK; ++e)
            {
                const bcmolt_field_descr *union_case;
                const bcmolt_type_descr *union_case_type;
                uint32_t nf_case;

                union_case = &elem_td->x.u.union_fields[e - sel_parm->enum_table];
                if (union_case->name == NULL)
                    continue;
                union_case_type = union_case->type;
                BUG_ON(union_case_type == NULL);
                BUG_ON(union_case_type->base_type != BCMOLT_BASE_TYPE_ID_STRUCT);
                nf_case = _metacli_get_num_fields_in_type(union_case_type, flags);
                if (nf_case)
                {
                    e->parms = _metacli_parm_array_alloc(nf_case);
                    if (!e->parms)
                    {
                        rc = BCM_ERR_NOMEM;
                        break;
                    }
                    rc = _metacli_populate_struct_fields(session, union_case_type, e->parms,
                        nf_case, flags, parm_flags, NULL);
                }
            }
        }
    }

    /* Done with struct/union fields. Finish populating the CLI parameter */
    rc = (rc != BCM_ERR_OK) ? rc : _metacli_parm_populate_1(session, pd, td, elem_td, parm, parm_flags);

    return rc;
}

/* populate CLI parameter table */
static bcmos_errno _metacli_parms_populate(
    bcmcli_session *session,
    const bcmolt_metadata_set *set,
    uint16_t o,
    bcmolt_mgt_group group,
    uint16_t subgroup,
    bcmolt_metadata_cli_flags flags,
    bcmcli_cmd_parm *parms,
    uint32_t parm_flags)
{
    uint32_t nf;
    bcmos_errno rc;
    const bcmolt_group_descr *group_descr;

    rc = bcmolt_group_descr_get(set, o, group, subgroup, &group_descr);
    if (rc != BCM_ERR_OK)
        return rc;

    nf = _metacli_get_num_fields_in_type(group_descr->type, flags);
    if (!nf)
        return BCM_ERR_OK;

    return _metacli_populate_struct_fields(session, group_descr->type, parms, nf, flags, parm_flags, NULL);
}


/* compact selector table. squeeze out values that don't have parameter table attached */
static void _metacli_compact_selector(bcmcli_enum_val *selector, int size)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        if (!selector[i].parms)
        {
            for ( j = i + 1; j < size && !selector[j].parms; j ++)
                ;
            if (j < size)
            {
                memcpy(&selector[i], &selector[j], sizeof(bcmcli_enum_val));
                memset(&selector[j], 0, sizeof(bcmcli_enum_val));
            }
            else
            {
                memset(&selector[i], 0, sizeof(bcmcli_enum_val));
            }
        }
    }
}

/* Free CLI parameters. both name and description are allocated dynamically */
static void _metacli_free_parms(bcmcli_cmd_parm *parms)
{
    bcmcli_cmd_parm *p = parms;

    while (p->name)
    {
        if ((p->flags & BCMCLI_PARM_FLAG_SELECTOR))
        {
            /* Remove selector table */
            bcmcli_enum_val *sel = p->enum_table;
            if (sel)
            {
                bcmcli_enum_val *e = sel;
                while(e->name)
                {
                    if (e->parms)
                    {
                        _metacli_free_parms(e->parms);
                    }
                    ++e;
                }
            }
        }
        if (p->enum_table && p->enum_table != bool_enum)
            bcmos_free(p->enum_table);
        if (p->max_array_size && p->values)
            bcmos_free(p->values);
        if (p->type == BCMCLI_PARM_BUFFER && p->value.buffer.start)
            bcmos_free(p->value.buffer.start);
        if (p->type == BCMCLI_PARM_STRUCT && p->value.fields)
            _metacli_free_parms(p->value.fields);

        ++p;
    }
    bcmos_free(parms);
}

/* Allocate and set up object parameters */
static bcmcli_cmd_parm *_metacli_obj_parm_alloc_populate(
    bcmcli_session *session,
    const bcmolt_metadata_set *set,
    uint16_t o,
    bcmolt_mgt_group group,
    uint16_t subgroup,
    bcmolt_metadata_cli_flags flags)
{
    static const char *filter_parm_name = "filter";
    static const char *filter_parm_descr = "Filter object parameters";
    uint32_t nkeyfields = 0;
    uint32_t nextrafields = 0;
    uint32_t nfields = 0;
    bcmos_errno rc = BCM_ERR_OK;
    bcmcli_cmd_parm *parms = NULL;
    const bcmolt_group_descr *group_descr;
    bcmos_bool is_multi = ((flags & BCMOLT_METADATA_CLI_FLAGS_MULTI) != BCMOLT_METADATA_CLI_FLAGS_NONE);
    bcmos_bool has_filter = is_multi;

    do
    {
        bcmcli_cmd_parm *parm_ptr;

        if (is_multi)
        {
            /* Stat-get multi can be missing a filter struct in the case where there is no cfg for the object. */
            if (group != BCMOLT_MGT_GROUP_CFG)
            {
                rc = bcmolt_group_descr_get(set, o, BCMOLT_MGT_GROUP_CFG, 0, &group_descr);
                has_filter = (rc == BCM_ERR_OK);
            }
            nextrafields = has_filter ? 1 : 0; /* for "filter" parameter */
        }

        if ((flags & BCMOLT_METADATA_CLI_FLAGS_IGNORE_KEY) == BCMOLT_METADATA_CLI_FLAGS_NONE)
        {
            /* Get number of key fields and save it */
            rc = bcmolt_group_descr_get(set, o, BCMOLT_MGT_GROUP_KEY, 0, &group_descr);
            BUG_ON(rc != BCM_ERR_OK && rc != BCM_ERR_NOENT);
            nkeyfields = _metacli_get_num_fields_in_type(group_descr->type, flags);
        }

        if ((flags & BCMOLT_METADATA_CLI_FLAGS_IGNORE_FIELDS) == BCMOLT_METADATA_CLI_FLAGS_NONE)
        {
            /* Number of object fields */
            rc = bcmolt_group_descr_get(set, o, group, subgroup, &group_descr);
            BUG_ON(rc != BCM_ERR_OK && rc != BCM_ERR_NOENT);
            nfields = group_descr->type == NULL ? 0 : _metacli_get_num_fields_in_type(group_descr->type, flags);
        }

        /* Allocate parameter table and populate it */
        parms = _metacli_parm_array_alloc(nfields + nkeyfields + nextrafields);
        if (!parms)
        {
            rc = BCM_ERR_NOMEM;
            break;
        }

        parm_ptr = parms;
        if (nkeyfields)
        {
            rc = _metacli_parms_populate(
                session,
                set,
                o,
                BCMOLT_MGT_GROUP_KEY,
                0,
                BCMOLT_METADATA_CLI_FLAGS_NONE,
                parm_ptr,
                is_multi ? BCMCLI_PARM_FLAG_OPTIONAL : 0);
            if (rc != BCM_ERR_OK)
                break;
            parm_ptr += nkeyfields;
        }
        if (has_filter)
        {
            /* Filter parameter. Note that for filter even read-only fields are settable */
            parm_ptr->name = filter_parm_name;
            parm_ptr->description = filter_parm_descr;
            parm_ptr->type = BCMCLI_PARM_STRUCT;
            parm_ptr->flags = BCMCLI_PARM_FLAG_OPTIONAL;
            parm_ptr->value.fields = _metacli_obj_parm_alloc_populate(
                session,
                set,
                o,
                BCMOLT_MGT_GROUP_CFG,
                0,
                BCMOLT_METADATA_CLI_FLAGS_MULTI_GET_FILTER);
            if (!parm_ptr->value.fields)
            {
                rc = BCM_ERR_NOMEM;
                break;
            }
            ++parm_ptr;
        }
        if (nfields)
        {
            rc = _metacli_parms_populate(session, set, o, group, subgroup, flags, parm_ptr, BCMCLI_PARM_FLAG_OPTIONAL);
            if (rc != BCM_ERR_OK)
                break;
            parm_ptr += nfields;
        }
    } while (0);

    if (rc != BCM_ERR_OK)
    {
        if (parms)
            _metacli_free_parms(parms);
        parms = NULL;
    }

    return parms;
}

/* Allocate command parameters.
 * The number of parameters depends on the management group.
 * command parameters are:
 * - object_name (selector)
 * - object_key_fields
 * - per-group extra parameters
 *          - STAT: clear
 *          - OPER: oper_name
 * - per_group_fields filtered by access
 */
static bcmos_errno _metacli_cmd_parms_alloc(bcmolt_mgt_group group, bcmolt_metadata_cli_flags flags,
    bcmcli_cmd_parm **p_parms, uint32_t *p_nparms)
{
    static const char *clear_parm_name = "clear";
    static const char *clear_parm_descr = "clear on read";
    static const char *max_msgs_parm_name = "max_msgs";
    static const char *max_msgs_parm_descr = "max number of API GET messages to receive per call";
    static const char *filter_invert_parm_name = "filter_invert";
    static const char *filter_invert_parm_descr = "invert filter (select objects that don't match)";
    static const char *obj_parm_name = "object";
    static const char *obj_parm_descr = "Object Type";

    int nparms;
    int parm_idx;
    bcmcli_cmd_parm *parms;

    nparms = 1; /* object */
    if (group == BCMOLT_MGT_GROUP_STAT)
    {
        nparms++; /* clear */
    }
    if ((flags & BCMOLT_METADATA_CLI_FLAGS_MULTI) != BCMOLT_METADATA_CLI_FLAGS_NONE)
    {
        nparms += 2; /* max msgs + invert flag */
    }

    parms = _metacli_parm_array_alloc(nparms);
    if (!parms)
        return BCM_ERR_NOMEM;

    parm_idx = 0;
    if (group == BCMOLT_MGT_GROUP_STAT)
    {
        /* Add a 'clear on read' to stats group */
        parms[parm_idx].type = BCMCLI_PARM_ENUM;
        parms[parm_idx].enum_table = bool_enum;
        parms[parm_idx].name = clear_parm_name;
        parms[parm_idx].description = clear_parm_descr;
        parm_idx++;
    }
    if ((flags & BCMOLT_METADATA_CLI_FLAGS_MULTI) != BCMOLT_METADATA_CLI_FLAGS_NONE)
    {
        /* max msgs + invert flag + object */
        parms[parm_idx].type = BCMCLI_PARM_UNUMBER;
        parms[parm_idx].name = max_msgs_parm_name;
        parms[parm_idx].description = max_msgs_parm_descr;
        parm_idx++;

        parms[parm_idx].type = BCMCLI_PARM_ENUM;
        parms[parm_idx].enum_table = bool_enum;
        parms[parm_idx].name = filter_invert_parm_name;
        parms[parm_idx].description = filter_invert_parm_descr;
        parm_idx++;
    }

    /* Set up object parameter. Selector table will be added elsewhere */
    parms[parm_idx].type = BCMCLI_PARM_ENUM;
    parms[parm_idx].flags = BCMCLI_PARM_FLAG_SELECTOR;
    parms[parm_idx].name = obj_parm_name;
    parms[parm_idx].description = obj_parm_descr;

    *p_parms = parms;
    *p_nparms = nparms;

    return BCM_ERR_OK;
}

bcmos_errno bcmolt_metadata_cli_command_add(
    bcmcli_session *session,
    const bcmolt_metadata_set *set,
    bcmcli_entry *dir,
    const char *cmd_name,
    const char *cmd_descr,
    bcmolt_mgt_group group,
    bcmcli_cmd_cb cmd_handler,
    bcmolt_metadata_cli_flags flags)
{
    static const char *sub_parm_name = "sub";
    static const char *sub_parm_descr = "Subgroup (specific operation)";

    bcmcli_cmd_extra_parm cmd_extras = { .free_parms = _metacli_free_parms };
    bcmcli_cmd_parm *cmd_parms;
    bcmcli_enum_val *obj_selector;
    uint16_t o;
    bcmos_errno rc;
    uint32_t num_cmd_parms;
    int n_obj;

    /* Allocate parameter table */
    rc = _metacli_cmd_parms_alloc(group, flags, &cmd_parms, &num_cmd_parms);
    if (rc != BCM_ERR_OK)
        return rc;

    /* Allocate enough space for all object entries as well as a terminator entry (which is left NULL) */
    obj_selector = bcmos_calloc(sizeof(bcmcli_enum_val) * (set->obj_id_count + 1));
    if (!obj_selector)
        goto nomem_cleanup;
    cmd_parms[num_cmd_parms - 1].enum_table = obj_selector;

    /* Allocate parameter table */
    n_obj = 0;
    for (o = 0; o < set->obj_id_count; o++)
    {
        const bcmolt_obj_descr *obj_descr;
        uint16_t subgroup_count;
        uint32_t size;
        uint16_t s;
        uint16_t sid;

        obj_selector[n_obj].val = o;
        rc = bcmolt_obj_descr_get(set, o, &obj_descr);
        if (rc)
            continue;
        obj_selector[n_obj].name = obj_descr->name;

        subgroup_count = bcmolt_group_count_get(set, o, group);
        if (!subgroup_count)
            continue;

        /* Allocate subgroup selector if necessary */
        if (group != BCMOLT_MGT_GROUP_CFG)
        {
            bcmcli_enum_val *sub_selector;

            /* Allocate subgroup enum table */
            sub_selector = bcmos_calloc(sizeof(bcmcli_enum_val) * (subgroup_count + 1));
            if (!sub_selector)
                goto nomem_cleanup;

            /* Allocate single subgroup command parameter */
            size = sizeof(bcmcli_cmd_parm) * 2;
            obj_selector[n_obj].parms = bcmos_calloc(size);
            if (!obj_selector[n_obj].parms)
            {
                bcmos_free(sub_selector);
                goto nomem_cleanup;
            }

            /* Setup single subgroup command parameter */
            obj_selector[n_obj].parms[0].type = BCMCLI_PARM_ENUM;
            obj_selector[n_obj].parms[0].flags = BCMCLI_PARM_FLAG_SELECTOR;
            obj_selector[n_obj].parms[0].enum_table = sub_selector;
            obj_selector[n_obj].parms[0].name = sub_parm_name;
            obj_selector[n_obj].parms[0].description = sub_parm_descr;

            /* There are subgroup_count subgroups in total, but subgroup IDs can be non contiguous.
               In the below loop s is index, sid is id */
            for (s = 0, sid = 0; s < subgroup_count; ++sid)
            {
                const bcmolt_group_descr *group_descr;

                /* Fetch group descriptor. The function can fail because subgroup ID space can have holes.
                   When querying hole in the middle of ID space, the function returns BCM_ERR_NOENT */
                rc = bcmolt_group_descr_get(set, o, group, sid, &group_descr);
                BUG_ON(rc != BCM_ERR_OK && rc != BCM_ERR_NOENT);
                if (rc != BCM_ERR_OK)
                    continue;

                /* Setup entry in subgroup enum table */
                sub_selector[s].name = group_descr->name;
                sub_selector[s].val = sid;
                /* Allocate parameter table and populate it */
                sub_selector[s].parms = _metacli_obj_parm_alloc_populate(session, set, o, group, sid, flags);
                if (!sub_selector[s].parms)
                {
                    rc = BCM_ERR_NOMEM;
                    goto nomem_cleanup;
                }
                ++s;
            }

            /* Compact sub_selector enum. Removes holes (values without parameter table) */
            _metacli_compact_selector(sub_selector, subgroup_count);
        }
        else
        {
            /* Configuration group */
            obj_selector[n_obj].parms = _metacli_obj_parm_alloc_populate(session, set, o, group, 0, flags);
            if (!obj_selector[n_obj].parms)
            {
                rc = BCM_ERR_NOMEM;
                goto nomem_cleanup;
            }
        }

        ++n_obj; /* number of configured objects */
    }

    /* Compact obj_selector enum. Removes holes (values without parameter table) */
    _metacli_compact_selector(obj_selector, set->obj_id_count);

    /* We are ready to add this command */
    rc = bcmcli_cmd_add(dir, cmd_name, cmd_handler, cmd_descr,
        (flags & BCMOLT_METADATA_CLI_FLAGS_ACCESS_READ) ? BCMCLI_ACCESS_GUEST : BCMCLI_ACCESS_ADMIN,
        &cmd_extras, cmd_parms);
    if (rc)
        goto nomem_cleanup;
    return BCM_ERR_OK;

nomem_cleanup:
    if (obj_selector)
    {
        for (o = 0; o < set->obj_id_count; o++)
        {
            if (obj_selector[o].parms)
                _metacli_free_parms(obj_selector[o].parms);
        }
        bcmos_free(obj_selector);
    }
    bcmos_free(cmd_parms);
    return rc;
}
