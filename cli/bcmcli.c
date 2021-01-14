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


/*******************************************************************
 * bcmcli.c
 *
 * CLI engine
 *
 *******************************************************************/
#include <bcmos_system.h>
#define BCMCLI_INTERNAL
#include <bcmcli.h>
#include <bcmos_types.h>
#include <bcmolt_string.h>

#define BCMCLI_INBUF_LEN            4096
#define BCMCLI_MAX_QUAL_NAME_LENGTH 256
#define BCMCLI_UP_STR               ".."
#define BCMCLI_ROOT_STR             "/"
#define BCMCLI_COMMENT_CHAR         '#'
#define BCMCLI_HELP_CHAR            '?'
#define BCMCLI_ARRAY_DELIM_CHAR     ','
#define BCMCLI_ROOT_HELP            "root directory"
#define BCMCLI_MAX_PARM_VAL_LEN     256
#define BCMCLI_ENUM_MASK_DEL_CHAR   '+'
#define BCMCLI_HELP_BUFFER_SIZE     16384
#define BCMCLI_MAX_ARRAY_LEN        128
#define BCMCLI_EQUAL_CHAR           '='
#define BCMCLI_STRUCT_START_CHAR    '{'
#define BCMCLI_STRUCT_END_CHAR      '}'
#define BCMCLI_STRUCT_START_STR     "{"
#define BCMCLI_STRUCT_END_STR       "}"
#define BCMCLI_ARRAY_START_CHAR     '['
#define BCMCLI_ARRAY_END_CHAR       ']'
#define BCMCLI_ARRAY_START_STR      "["
#define BCMCLI_ARRAY_END_STR        "]"
#define BCMCLI_NO_VALUE_STR         "-"


typedef enum { BCMCLI_ENTRY_DIR, BCMCLI_ENTRY_CMD } bcmcli_entry_selector;

/* External table - boolean values */
bcmcli_enum_val bcmcli_enum_bool_table[] = {
    { .name="true", .val = 1 },
    { .name="yes", .val = 1 },
    { .name="on", .val = 1 },
    { .name="false", .val = 0 },
    { .name="no", .val = 0 },
    { .name="off", .val = 0 },
    BCMCLI_ENUM_LAST
};

/* Monitor token structure */
struct bcmcli_entry
{
    struct bcmcli_entry  *next;
    char *name;                                  /* Command/directory name */
    char *help;                                  /* Command/directory help */
    bcmcli_entry_selector sel;                   /* Entry selector */
    char *alias;                                 /* Alias */
    uint16_t alias_len;                          /* Alias length */
    struct bcmcli_entry *parent;                 /* Parent directory */
    bcmcli_access_right access_right;

    union {
        struct
        {
            struct bcmcli_entry *first;          /* First entry in directory */
            bcmcli_dir_extra_parm extras;        /* Optional extras */
        } dir;
        struct
        {
            bcmcli_cmd_cb cmd_cb;                /* Command callback */
            bcmcli_cmd_parm *parms;              /* Command parameters */
            bcmcli_cmd_extra_parm extras;        /* Optional extras */
            uint16_t num_parms;
        } cmd;
    } u;
};


/* Token types */
typedef enum
{
    BCMCLI_TOKEN_EMPTY = 0,
    BCMCLI_TOKEN_UP    = (1 << 0),
    BCMCLI_TOKEN_ROOT  = (1 << 1),
    BCMCLI_TOKEN_BREAK = (1 << 2),
    BCMCLI_TOKEN_HELP  = (1 << 3),
    BCMCLI_TOKEN_NAME  = (1 << 4),
    BCMCLI_TOKEN_VALUE = (1 << 5),
#define BCMCLI_TOKEN_TYPE_MASK 0xff

    /* Flags */
    BCMCLI_TOKEN_HAS_EQUAL_SIGN = (1 << 8),
    BCMCLI_TOKEN_STRUCT_VALUE = (1 << 9),
    BCMCLI_TOKEN_UNTERMINATED_STRUCT_VALUE = (1 << 10),
    BCMCLI_TOKEN_UNTERMINATED_ARRAY_INDEX = (1 << 11),
} bcmcli_token_type;

/* Name, value pairs */
typedef struct
{
    bcmcli_token_type type;
    const char *name;
    const char *value;
    const char *index;
} bcmcli_name_value;

/* Command parameters array.
 * These arrays can be stacked in case of hierarchical parameter structures (structs)
 */
typedef struct bcmcli_parm_array bcmcli_parm_array;
struct bcmcli_parm_array
{
    bcmcli_cmd_parm *cmd_parms;
    bcmcli_name_value *name_value_pairs;
    uint32_t num_parms;
    uint32_t num_pairs;
    uint32_t num_parsed;
    const char *in_parm;
    bcmcli_parm_value *in_value;
    STAILQ_ENTRY(bcmcli_parm_array) next;
};

/* CLI session data */
typedef struct
{
    bcmcli_entry *curdir;
    bcmcli_entry *curcmd;
    bcmos_bool is_execution;
    bcmos_bool suppress_err_print;
    bcmcli_token_type cur_token_type;
    STAILQ_HEAD(cmd_parms_stack, bcmcli_parm_array) cmd_parms_stack;
    bcmcli_session *session;
    const char *p_inbuf;
    int stop_monitor;
    char inbuf[BCMCLI_INBUF_LEN];
    char help_buf[BCMCLI_HELP_BUFFER_SIZE];
    bcmolt_string help_string;
} bcmcli_session_extras;

static bcmcli_entry           *_bcmcli_root_dir;
static bcmcli_session_extras  *_bcmcli_root_session;
static bcmcli_log_mode         _bcmcli_log_mode;
static bcmcli_session         *_bcmcli_log_session;

#define BCMCLI_MIN_NAME_LENGTH_FOR_ALIAS   3
#define BCMCLI_ROOT_NAME       "/"

/* Internal functions */
static void        _bcmcli_alloc_root(const bcmcli_session_parm *parm);
static void        _bcmcli_display_dir(bcmcli_session_extras *mon_session, bcmcli_entry *p_dir );
static int _bcmcli_parm_array_validate(const char *name, bcmcli_cmd_parm parms[]);
static bcmcli_token_type _bcmcli_get_word(bcmcli_session_extras *session, char **inbuf, char **p_word);
static bcmcli_token_type _bcmcli_analyze_token( const char *name );
static bcmos_errno _bcmcli_parse_parms( bcmcli_session_extras *mon_session, bcmcli_entry *p_token,
    bcmcli_name_value *pairs, int npairs);
static bcmos_errno _bcmcli_extend_parms( bcmcli_session_extras *mon_session, bcmcli_name_value *pairs,
    int npairs, bcmos_bool last_is_space, char *insert_str, uint32_t insert_size);
static bcmcli_entry *_bcmcli_search_token( bcmcli_entry *p_dir, const char *name );
static void        _bcmcli_help_dir( bcmcli_session_extras *mon_session, bcmcli_entry *p_dir );
static void        _bcmcli_help_entry(bcmcli_session_extras *mon_session, bcmcli_entry *p_token,
    bcmcli_name_value *pairs, int npairs);
static void        _bcmcli_help_populated_cmd(bcmcli_session_extras *mon_session, bcmcli_entry *p_token,
    const char *partial_match, bcmos_bool suppress_assigned);
static void        _bcmcli_choose_alias( bcmcli_entry *p_dir, bcmcli_entry *p_new_token );
static bcmcli_cmd_parm *_bcmcli_find_named_parm(bcmcli_session_extras *mon_session, const char *name);
static char       *_bcmcli_strlwr( char *s );
static int         _bcmcli_stricmp( const char *s1, const char *s2, int len );
static bcmos_errno _bcmcli_dft_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val);
static const char *_bcmcli_get_type_name(const bcmcli_cmd_parm *parm);
static void        _bcmcli_dft_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value);
static bcmos_errno _bcmcli_enum_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val);
static void        _bcmcli_enum_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value);
static bcmos_errno _bcmcli_enum_mask_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val);
static void        _bcmcli_enum_mask_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value);
static bcmos_errno _bcmcli_struct_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val);
static void        _bcmcli_struct_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value);
static bcmos_errno _bcmcli_buffer_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val);
static void        _bcmcli_buffer_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value);
static const char *_bcmcli_qualified_name( bcmcli_entry *token, char *buffer, int size);
static bcmos_errno _bcmcli_split(bcmcli_session_extras *mon_session, const char **p_str, int p_str_len,
    bcmcli_name_value **pairs, int *npairs);
static void        _bcmcli_assign_callbacks(bcmcli_cmd_parm *parm);
static void        _bcmcli_log_cmd(const char *cmd);
static void        _bcmcli_log_rc(bcmos_errno rc);

/*
 * Command parameter array stack manipulation
 */
static bcmcli_parm_array *_bcmcli_parm_array_create(bcmcli_session_extras *mon_session,
    const char *in_parm, bcmcli_parm_value *in_value, const bcmcli_cmd_parm parms[],
    bcmcli_name_value pairs[], int npairs);
static bcmos_errno _bcmcli_parm_array_extend(bcmcli_session_extras *mon_session,
    bcmcli_parm_array *pa, uint32_t pos, const bcmcli_cmd_parm extra_parms[]);
static void _bcmcli_parm_array_push(bcmcli_session_extras *mon_session, bcmcli_parm_array *pa);
static bcmcli_parm_array *_bcmcli_parm_array_pop(bcmcli_session_extras *mon_session);
static bcmcli_parm_array *_bcmcli_parm_array_top(bcmcli_session_extras *mon_session);
static bcmcli_parm_array *_bcmcli_parm_array_cur(bcmcli_session_extras *mon_session);
static bcmos_bool _bcmcli_parm_array_is_all_set(bcmcli_session_extras *mon_session, bcmcli_parm_array *pa);

static inline bcmcli_session_extras *_bcmcli_session_data(bcmcli_session *session)
{
    if (!session)
        return _bcmcli_root_session;
    return bcmcli_session_data(session);
}

/** Add subdirectory to the parent directory
 *
 * \param[in]   parent          Parent directory handle. NULL=root
 * \param[in]   name            Directory name
 * \param[in]   help            Help string
 * \param[in]   access_right    Access rights
 * \param[in]   extras          Optional directory descriptor. Mustn't be allocated on the stack.
 * \return      new directory handle or NULL in case of failure
 */
bcmcli_entry *bcmcli_dir_add(bcmcli_entry *parent, const char *name,
                             const char *help, bcmcli_access_right access_right,
                             const bcmcli_dir_extra_parm *extras)
{
    bcmcli_entry *p_dir;
    bcmcli_entry **p_e;

    assert(name);
    assert(help);
    if (!name || !help)
        return NULL;

    if (!_bcmcli_root_dir)
    {
        _bcmcli_alloc_root(NULL);
        if (!_bcmcli_root_dir)
            return NULL;
    }

    if (!parent)
        parent = _bcmcli_root_dir;

    p_dir = bcmcli_dir_find(parent, name);
    if (p_dir != NULL)
    {
        BCMOS_TRACE_ERR("%s directory already created.\n", name);
        return NULL;
    }

    p_dir=(bcmcli_entry *)bcmos_calloc( sizeof(bcmcli_entry) + strlen(name) + strlen(help) + 2 );
    if ( !p_dir )
        return NULL;

    p_dir->name = (char *)(p_dir + 1);
    strcpy( p_dir->name, name);
    p_dir->help = p_dir->name + strlen(name) + 1;
    strcpy(p_dir->help, help);
    p_dir->sel = BCMCLI_ENTRY_DIR;
    _bcmcli_choose_alias( parent, p_dir );
    p_dir->access_right = access_right;
    if (extras)
        p_dir->u.dir.extras = *extras;

    /* Add new directory to the parent's list */
    p_dir->parent = parent;
    p_e = &(parent->u.dir.first);
    while (*p_e)
        p_e = &((*p_e)->next);
    *p_e = p_dir;

    return p_dir;
}

static bcmcli_entry * find_entry_in_dir( bcmcli_entry *dir, const char *name,
        bcmcli_entry_selector type, uint16_t recursive_search)
{
    bcmcli_entry *p1, *p;

    if ( !dir )
    {
        dir = _bcmcli_root_dir;
        if (!dir)
            return NULL;
    }
    p = dir->u.dir.first;
    while (p)
    {
        if ( !_bcmcli_stricmp(p->name, name, -1) && type == p->sel )
            return p;
        if ( recursive_search && p->sel == BCMCLI_ENTRY_DIR )
        {
            p1 = find_entry_in_dir(p, name , type, 1 );
            if ( p1 )
                return p1;
        }
        p = p->next;
    }
    return NULL;
}


/* Scan directory tree and look for directory with name starts from
 * root directory with name root_name
 */
bcmcli_entry *bcmcli_dir_find(bcmcli_entry *parent, const char  *name)
{
    if ( !parent )
        parent = _bcmcli_root_dir;
    return find_entry_in_dir(parent, name, BCMCLI_ENTRY_DIR, 0 );
}


/* Scan directory tree and look for command named "name". */
bcmcli_entry *bcmcli_cmd_find(bcmcli_entry *parent, const char *name )
{
    if ( !parent )
        parent = _bcmcli_root_dir;
    return find_entry_in_dir(parent, name, BCMCLI_ENTRY_CMD, 0 );
}

/* Get CLI entry info */
void bcmcli_entry_info_get(bcmcli_session *session, const bcmcli_entry *entry,
    bcmos_bool *is_dir, const char **name, const char **descr, const bcmcli_entry **parent)
{
    if (is_dir)
        *is_dir = (entry->sel == BCMCLI_ENTRY_DIR);
    if (name)
        *name = entry->name;
    if (descr)
        *descr = entry->help;
    if (parent)
        *parent = entry->parent;
}

/* Validate command parameter or a structure field */
static bcmos_errno _bcmcli_parm_validate(const char *name, bcmcli_cmd_parm *parm)
{
    bcmos_errno rc = BCM_ERR_PARM;

    do
    {
        /* User-defined parameter must have a scan_cb callback for text->value conversion */
        if ((parm->type==BCMCLI_PARM_USERDEF) && !parm->scan_cb)
        {
            bcmos_printf("MON: %s> scan_cb callback must be set for user-defined parameter %s\n", name, parm->name);
            break;
        }
        if (parm->type==BCMCLI_PARM_ENUM || parm->type==BCMCLI_PARM_ENUM_MASK)
        {
            if (!parm->enum_table)
            {
                bcmos_printf("MON: %s> value table must be set in low_val for enum parameter %s\n", name, parm->name);
                break;
            }

            /* Check default value if any */
            if ((parm->flags & BCMCLI_PARM_FLAG_DEFVAL))
            {
                if (_bcmcli_enum_mask_scan_cb(_bcmcli_root_session->session, parm, &parm->value, parm->value.string) < 0)
                {
                    bcmos_printf("MON: %s> default value %s doesn't match any value of enum parameter %s\n", name, parm->value.string, parm->name);
                    break;
                }
            }
            else if ((parm->flags & BCMCLI_PARM_FLAG_OPTIONAL))
            {
                /* Optional enum parameters are initialized by their 1st value by default.
                 * All other parameters are initialized to 0.
                 */
                bcmcli_enum_val *values=parm->enum_table;
                parm->value.enum_val = values[0].val;
            }

            /* All values of enum mask parameters mast be complementary bits */
            if (parm->type==BCMCLI_PARM_ENUM_MASK)
            {
                long all_mask = 0;
                bcmcli_enum_val *values;
                for (values=parm->enum_table; values->name; ++values)
                    all_mask |= values->val;

                for (values=parm->enum_table; values->name; ++values)
                {
                    if ((all_mask & values->val) != values->val)
                    {
                        bcmos_printf("MON: %s> enum_table values of enum_mask parameters must be complementary bits\n", name);
                        break;
                    }
                    all_mask &= ~values->val;
                }
                if (values->name)
                    break;
            }
        }
        else if (parm->type==BCMCLI_PARM_BUFFER)
        {
            if (!parm->value.buffer.start || !parm->value.buffer.len)
            {
                bcmos_printf("MON: %s> value.buffer.start is not set for BUFFER parameter %s\n", name, parm->name);
                break;
            }
            if (parm->max_array_size)
            {
                bcmos_printf("MON: %s> BUFFER arrays are not supported %s\n", name, parm->name);
                break;
            }
        }
        else if (parm->type==BCMCLI_PARM_STRUCT)
        {
            if (parm->max_array_size)
            {
                int j;
                for (j = 0; j < parm->max_array_size; j++)
                {
                    if (!parm->values || !parm->values[j].fields)
                    {
                        bcmos_printf("MON: %s> fields are not set for struct array parameter %s, element %d\n", name, parm->name, j);
                        break;
                    }
                    if (_bcmcli_parm_array_validate(name, parm->values[j].fields) < 0)
                        break;
                }
                /* Problem ? */
                if (j < parm->max_array_size)
                    break;
            }
            else
            {
                if (!parm->value.fields)
                {
                    bcmos_printf("MON: %s> fields are not set for struct parameter %s\n", name, parm->name);
                    break;
                }
                if (_bcmcli_parm_array_validate(name, parm->value.fields) < 0)
                    break;
            }
        }
        if (parm->max_array_size)
        {
            if (!parm->values && parm->type != BCMCLI_PARM_STRUCT)
            {
                bcmos_printf("MON: %s> parm->values must be set for parameter-array %s\n", name, parm->name);
                break;
            }
        }

        rc = BCM_ERR_OK;

    } while (0);

    return rc;
}

/* Validate parameters/fields array.
 * returns the number of valid parameters >= 0 or error < 0
 */
static int _bcmcli_parm_array_validate(const char *name, bcmcli_cmd_parm parms[])
{
    bcmcli_cmd_parm *p;
    bcmos_errno rc = BCM_ERR_OK;

    if (!parms)
        return 0;
    for (p = parms; p->name && rc == BCM_ERR_OK; ++p)
    {
        rc = _bcmcli_parm_validate(name, p);
    }

    return (rc == BCM_ERR_OK) ? (p - parms) : (int)rc;
}


/** Add CLI command
 *
 * \param[in]   dir             Handle of directory to add command to. NULL=root
 * \param[in]   name            Command name
 * \param[in]   cmd_cb          Command handler
 * \param[in]   help            Help string
 * \param[in]   access_right    Access rights
 * \param[in]   extras          Optional extras
 * \param[in]   parms           Optional parameters array. Must not be allocated on the stack!
 *                              If parms!=NULL, the last parameter in the array must have name==NULL.
 * \return
 *      0   =OK\n
 *      <0  =error code
 */
bcmos_errno bcmcli_cmd_add(bcmcli_entry *dir, const char *name, bcmcli_cmd_cb cmd_cb,
    const char *help, bcmcli_access_right access_right,
    const bcmcli_cmd_extra_parm *extras, bcmcli_cmd_parm parms[])
{
    bcmcli_entry *p_token;
    bcmcli_entry **p_e;
    int i;

    assert(name);
    assert(help);
    assert(cmd_cb);
    if (!name || !cmd_cb || !help)
        return BCM_ERR_PARM;

    if (!_bcmcli_root_dir)
    {
        _bcmcli_alloc_root(NULL);
        if (!_bcmcli_root_dir)
            return BCM_ERR_NOMEM;
    }

    if (!dir)
        dir = _bcmcli_root_dir;

    p_token=(bcmcli_entry *)bcmos_calloc( sizeof(bcmcli_entry) + strlen(name) + strlen(help) + 2 );
    if ( !p_token )
        return BCM_ERR_NOMEM;

    /* Copy name */
    p_token->name = (char *)(p_token + 1);
    strcpy( p_token->name, name );
    p_token->help = p_token->name + strlen(name) + 1;
    strcpy(p_token->help, help);
    p_token->sel = BCMCLI_ENTRY_CMD;
    p_token->u.cmd.cmd_cb = cmd_cb;
    p_token->u.cmd.parms = parms;
    if (extras)
        p_token->u.cmd.extras = *extras;
    p_token->access_right = access_right;

    /* Convert name to lower case and choose alias */
    _bcmcli_choose_alias(dir, p_token );

    /* Check parameters */
    i = _bcmcli_parm_array_validate(name, parms);
    if (i < 0)
    {
        bcmos_free( p_token );
        return (bcmos_errno)i;
    }

    p_token->u.cmd.num_parms = i;

    /* Add token to the directory */
    p_token->parent = dir;
    p_e = &(dir->u.dir.first);
    while (*p_e)
        p_e = &((*p_e)->next);
    *p_e = p_token;

    return BCM_ERR_OK;
}


/** Destroy token (command or directory)
 * \param[in]   token           Directory or command token. NULL=root
 */
void bcmcli_token_destroy(bcmcli_entry *token)
{
    if (!token)
    {
        if (!_bcmcli_root_dir)
            return;
        token = _bcmcli_root_dir;
    }
    /* Remove from parent's list */
    if (token->parent)
    {
        bcmcli_entry **p_e;
        p_e = &(token->parent->u.dir.first);
        while (*p_e)
        {
            if (*p_e == token)
            {
                *p_e = token->next;
                break;
            }
            p_e = &((*p_e)->next);
        }
    }

    /* Remove all directory entries */
    if (token->sel == BCMCLI_ENTRY_DIR)
    {
        bcmcli_entry *e = token->u.dir.first;
        while ((e = token->u.dir.first))
            bcmcli_token_destroy(e);
    }
    else if (token->u.cmd.extras.free_parms)
            token->u.cmd.extras.free_parms(token->u.cmd.parms);

    /* Release the token */
    bcmos_free(token);

    if (token == _bcmcli_root_dir)
    {
        _bcmcli_root_dir = NULL;
        if (_bcmcli_root_session)
        {
            bcmcli_session_close(_bcmcli_root_session->session);
            _bcmcli_root_session = NULL;
        }
    }
}

/** Open monitor session
 *
 * Monitor supports multiple simultaneous sessions with different
 * access rights.
 * Note that there already is a default session with full administrative rights,
 * that takes input from stdin and outputs to stdout.
 * \param[in]   parm        Session parameters. Must not be allocated on the stack.
 * \param[out]  p_session   Session handle
 * \return
 *      0   =OK\n
 *      <0  =error code
 */
bcmos_errno bcmcli_session_open(const bcmcli_session_parm *parm, bcmcli_session **p_session)
{
    bcmcli_session *session;
    bcmcli_session_extras *mon_session;
    bcmcli_session_parm session_parms;
    bcmos_errno rc;

    assert(p_session);
    if (!p_session)
        return BCM_ERR_PARM;

    if (!_bcmcli_root_dir)
    {
        _bcmcli_alloc_root(parm);
        if (!_bcmcli_root_dir)
            return BCM_ERR_NOMEM;
    }
    if (parm)
        session_parms = *parm;
    else
    {
        memset(&session_parms, 0, sizeof(session_parms));
        session_parms.name = "unnamed";
    }

    /* Open comm session */
    session_parms.extra_size = sizeof(bcmcli_session_extras);
    rc = bcmcli_session_open_user(&session_parms, &session);
    if (rc)
        return rc;
    mon_session = _bcmcli_session_data(session);
    mon_session->curdir = _bcmcli_root_dir;
    mon_session->session = session;

    *p_session = session;

    return BCM_ERR_OK;
}

#define BCMCLI_PARSE_RETURN(ret) \
    do { \
        rc = ret;   \
        goto bcmcli_parse_out; \
    } while (0)

/* Parse a single command. Stop on ';' or EOL */
static bcmos_errno bcmcli_parse_command(bcmcli_session *session)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    bcmcli_entry  *p_token;
    bcmcli_name_value *pairs = NULL;
    const char *inbuf_org = mon_session->p_inbuf;
    int stop_parsing = 0;
    int npairs;
    int i;
    bcmos_errno rc = BCM_ERR_OK;

    /* Make sure we start fresh */
    bcmcli_session_stack_reset(session);
    STAILQ_INIT(&mon_session->cmd_parms_stack);

    /* Split string to name/value pairs */
    rc = _bcmcli_split(mon_session, &mon_session->p_inbuf, strlen(mon_session->p_inbuf), &pairs, &npairs);
    if (rc)
    {
        if (rc == BCM_ERR_NOENT)
            rc = BCM_ERR_OK;
        BCMCLI_PARSE_RETURN(rc);
    }

    /* Interpret empty string as "display directory" */
    if ( !npairs )
    {
        _bcmcli_display_dir(mon_session, mon_session->curdir );
        BCMCLI_PARSE_RETURN(BCM_ERR_OK);
    }

    mon_session->is_execution = BCMOS_TRUE;
    mon_session->suppress_err_print = BCMOS_FALSE;

    /* Identify parameters */
    for (i=0; i<npairs && !rc && !stop_parsing; i++)
    {
        switch (pairs[i].type & BCMCLI_TOKEN_TYPE_MASK)
        {
        case BCMCLI_TOKEN_NAME:
        case BCMCLI_TOKEN_VALUE:
            /* Identify command. The 1st pair can't contain name, only value */
            if (pairs[i].name)
            {
                bcmcli_session_print(session, "**ERR: %s is unexpected\n", pairs[i].name);
                BCMCLI_PARSE_RETURN(BCM_ERR_PARM);
            }
            p_token = _bcmcli_search_token(mon_session->curdir, pairs[i].value);
            if (p_token == NULL)
            {
                bcmcli_session_print(session, "**ERR: %s is unexpected\n", pairs[i].value);
                BCMCLI_PARSE_RETURN(BCM_ERR_PARM);
            }
            /* Directory or command ? */
            if (p_token->sel == BCMCLI_ENTRY_DIR)
            {
                mon_session->curdir = p_token;
                _bcmcli_display_dir(mon_session, mon_session->curdir );
            }
            else
            {
                bcmcli_parm_array *pa;

                /* Function token */
                stop_parsing = 1;
                mon_session->curcmd = p_token;

                rc = _bcmcli_parse_parms(mon_session, p_token, &pairs[i+1], npairs-i-1);
                if (rc != BCM_ERR_OK)
                {
                    mon_session->suppress_err_print = BCMOS_TRUE; /* already printed */
                    _bcmcli_help_entry(mon_session, p_token, &pairs[i+1], npairs-i-1);
                    break;
                }

                /* Successfully parsed parameters. Invoke command handler */
                _bcmcli_log_cmd(inbuf_org);
                pa = _bcmcli_parm_array_top(mon_session);
                BUG_ON(pa == NULL);
                rc = p_token->u.cmd.cmd_cb(session, pa->cmd_parms, pa->num_pairs);
                if (rc)
                {
                    char buffer[BCMCLI_MAX_QUAL_NAME_LENGTH];
                    bcmcli_session_print(session, "MON: %s> failed with error code %s(%d)\n",
                        _bcmcli_qualified_name(p_token, buffer, sizeof(buffer)),
                        bcmos_strerror(rc), rc);
                }
                _bcmcli_log_rc(rc);
            }
            break;

        case BCMCLI_TOKEN_UP: /* Go to upper directory */
            if (mon_session->curdir->parent)
                mon_session->curdir = mon_session->curdir->parent;
            _bcmcli_display_dir(mon_session, mon_session->curdir );
            break;

        case BCMCLI_TOKEN_ROOT: /* Go to the root directory */
            mon_session->curdir = _bcmcli_root_dir;
            _bcmcli_display_dir(mon_session, mon_session->curdir );
            break;

        case BCMCLI_TOKEN_HELP: /* Display help */
            if (i < npairs-1 &&
                ((p_token = _bcmcli_search_token( mon_session->curdir, pairs[i+1].value)) != NULL ))
            {
                _bcmcli_help_entry(mon_session, p_token, &pairs[i+2], npairs-i-2);
            }
            else
            {
                _bcmcli_help_dir(mon_session, mon_session->curdir);
            }
            stop_parsing = 1;
            break;

        default:
            stop_parsing = 1;
            break;
        }
    }

bcmcli_parse_out:

    return rc;
}

/** Context extension */
bcmos_errno bcmcli_extend(bcmcli_session *session, char *input_str, char *insert_str, uint32_t insert_size)
{
    bcmcli_session_extras *mon_session = _bcmcli_session_data(session);
    bcmcli_entry  *p_token;
    bcmcli_name_value *pairs = NULL;
    bcmos_bool last_is_space;
    int npairs;
    bcmos_errno rc = BCM_ERR_OK;

    if (!mon_session || !mon_session->curdir || !input_str)
        return BCM_ERR_PARM;

    insert_str[0] = 0;
    mon_session->p_inbuf = input_str;

    last_is_space = strlen(input_str) && (input_str[strlen(input_str) - 1] == ' ');

    /* Make sure we start fresh */
    bcmcli_session_stack_reset(session);
    STAILQ_INIT(&mon_session->cmd_parms_stack);

    /* Split string to name/value pairs */
    rc = _bcmcli_split(mon_session, &mon_session->p_inbuf, strlen(mon_session->p_inbuf), &pairs, &npairs);
    if (rc)
        return rc;

    /* empty list - display list of commands */
    if ( !npairs )
    {
        _bcmcli_display_dir(mon_session, mon_session->curdir );
        BCMCLI_PARSE_RETURN(BCM_ERR_OK);
    }

    mon_session->is_execution = BCMOS_FALSE;
    mon_session->suppress_err_print = BCMOS_TRUE;

    /* Identify parameters */
    switch (pairs[0].type)
    {
    case BCMCLI_TOKEN_NAME:
    case BCMCLI_TOKEN_VALUE:
        /* Identify command. The 1st pair can't contain name, only value */
        if (pairs[0].name ||
            !(p_token = _bcmcli_search_token(mon_session->curdir, pairs[0].value)))
        {
            _bcmcli_display_dir(mon_session, mon_session->curdir );
            BCMCLI_PARSE_RETURN(BCM_ERR_PARM);
        }

        /* Directory or command ? */
        if (p_token->sel != BCMCLI_ENTRY_CMD)
            BCMCLI_PARSE_RETURN(BCM_ERR_OK);

        /* Function token */
        mon_session->curcmd = p_token;
        rc = _bcmcli_extend_parms(mon_session, &pairs[1], npairs-1, last_is_space, insert_str, insert_size);
        break;

    default:
        break;
    }

bcmcli_parse_out:
    return rc;
}

/** Parse and execute input string.
 * input_string can contain multiple commands delimited by ';'
 *
 * \param[in]   session         Session handle
 * \param[in]   input_string    String to be parsed. May consist of multiple ';'-delimited commands
 */
bcmos_errno bcmcli_parse(bcmcli_session *session, char* input_string)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    uint32_t input_len;
    int rc = 0;

    if (!mon_session || !mon_session->curdir || !input_string)
        return BCM_ERR_PARM;
    input_len = strlen(input_string);
    if (!input_len)
        return BCM_ERR_OK;

    /* cut CR, LF if any */
    while (input_len && (input_string[input_len-1]=='\n' || input_string[input_len-1]=='\r'))
        input_string[--input_len]=0;

    mon_session->p_inbuf = input_string;
    mon_session->stop_monitor = 0;

    do {
        rc = bcmcli_parse_command(session);
    } while (mon_session->p_inbuf && mon_session->p_inbuf[0] && !mon_session->stop_monitor && !rc);

    return rc ? BCM_ERR_PARSE : BCM_ERR_OK;
}

/** Read input and parse iteratively until EOF or bcmcli_is_stopped()
 *
 * \param[in]   session         Session handle
 * \return
 *      =0  - OK \n
 */
bcmos_errno bcmcli_driver(bcmcli_session *session)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);

    session = mon_session->session;
    mon_session->stop_monitor = 0;
    while (!bcmcli_is_stopped(session) &&
          bcmcli_session_gets(session, mon_session->inbuf, sizeof(mon_session->inbuf)-1))
    {
        /* Session could've been stopped while in "gets". Check again and proceed if active */
        if (!bcmcli_is_stopped(session))
            bcmcli_parse(session, mon_session->inbuf);
    }

    return BCM_ERR_OK;
}


/* Stop monitor driver */
void bcmcli_stop( bcmcli_session *session )
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    assert(mon_session);
    mon_session->stop_monitor = 1;
}

/** Returns 1 if monitor session is stopped
 * \param[in]   session         Session handle
 * \returns 1 if monitor session stopped by bcmcli_stop()\n
 * 0 otherwise
 */
bcmos_bool bcmcli_is_stopped(bcmcli_session *session)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    return mon_session->stop_monitor;
}


/** Get parameter number given its name.
 * The function is intended for use by command handlers
 * \param[in]       session         Session handle
 * \param[in,out]   parm_name       Parameter name
 * \return
 *  >=0 - parameter number\n
 *  <0  - parameter with this name doesn't exist
 */
int bcmcli_parm_number(bcmcli_session *session, const char *parm_name)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    bcmcli_parm_array *pa;
    int i;

    if (!parm_name || !mon_session || !mon_session->curcmd)
        return BCM_ERR_PARM;
    pa = _bcmcli_parm_array_top(mon_session);
    if (!pa  || !pa->cmd_parms)
        return BCM_ERR_PARM;

    for(i=0;
        pa->cmd_parms[i].name &&
            _bcmcli_stricmp( parm_name, pa->cmd_parms[i].name, -1);
        i++)
        ;
    if (!pa->cmd_parms[i].name)
        return BCM_ERR_PARM;
    return i;
}


/** Get parameter by name
 * The function is intended for use by command handlers
 * \param[in]       session         Session handle
 * \param[in]       parm_name       Parameter name
 * \return
 * parameter pointer or NULL if not found
 */
bcmcli_cmd_parm *bcmcli_parm_get(bcmcli_session *session, const char *parm_name)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    bcmcli_parm_array *pa;
    int nparm;

    if (!mon_session)
        return NULL;
    pa = _bcmcli_parm_array_top(mon_session);
    if (!pa  || !pa->cmd_parms)
        return NULL;
    nparm = bcmcli_parm_number(session, parm_name);
    if (nparm < 0)
    {
        return NULL;
    }

    return &pa->cmd_parms[nparm];
}


/** Check if parameter is set
 * \param[in]       session         Session handle
 * \param[in]       parm_number     Parameter number
 * \return
 *  1 if parameter is set\n
 *  0 if parameter is not set or parm_number is invalid
 */
bcmos_errno bcmcli_parm_check(bcmcli_session *session, int parm_number)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    bcmcli_parm_array *pa;

    if (!mon_session || !mon_session->curcmd)
        return BCM_ERR_PARM;
    pa = _bcmcli_parm_array_top(mon_session);
    if (!pa  || !pa->cmd_parms)
        return BCM_ERR_PARM;
    if ((unsigned)parm_number >= pa->num_parms)
        return BCM_ERR_PARM;
    if (!(pa->cmd_parms[parm_number].flags & BCMCLI_PARM_FLAG_ASSIGNED))
        return BCM_ERR_NOENT;
    return BCM_ERR_OK;
}


/** Get enum's parameter string value given its internal value
 * \param[in]       session         Session handle
 * \param[in]       parm            Parameter
 * \return
 *      enum string value or NULL if parameter is not enum or
 *      internal value is invalid
 */
const char *bcmcli_enum_parm_stringval(bcmcli_session *session, const bcmcli_cmd_parm *parm)
{
    if (!parm || parm->type != BCMCLI_PARM_ENUM)
        return NULL;
    return bcmcli_enum_stringval(parm->enum_table, parm->value.unumber);
}


/* Get current directory handle */
bcmcli_entry *bcmcli_dir_get(bcmcli_session *session)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    if (!mon_session)
        return NULL;
    return mon_session->curdir;
}

/* Set current directory */
bcmos_errno bcmcli_dir_set(bcmcli_session *session, bcmcli_entry *dir)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    if (!mon_session)
        return BCM_ERR_PARM;
    /* Check access rights */
    if (!dir)
        dir = _bcmcli_root_dir;
    if (dir->access_right > bcmcli_session_access_right(mon_session->session))
        return BCM_ERR_PERM;
    mon_session->curdir = dir;
    return BCM_ERR_OK;
}

/** Get command that is being executed.
 * The function is intended for use from command handler.
 * \param[in]   session         Session handle
 * \return      The current command handle
 */
bcmcli_entry *bcmcli_cmd_get(bcmcli_session *session)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);
    if (!mon_session)
        return NULL;
    return mon_session->curcmd;
}

/** Get token name
 * \param[in]   token           Directory or command token
 * \return      directory token name
 */
const char *bcmcli_token_name(bcmcli_entry *token)
{
    if (!token)
        return NULL;
    return token->name;
}

bcmcli_cmd_parm *bcmcli_find_named_parm(bcmcli_session *session, const char *name)
{
    bcmcli_cmd_parm * cmd_parm;

    if ( !session || !name || *name=='\0')
        return NULL;

    cmd_parm = _bcmcli_find_named_parm(_bcmcli_session_data(session), name);
    if(cmd_parm && (cmd_parm->flags & BCMCLI_PARM_FLAG_ASSIGNED))
    {
        return cmd_parm;
    }

    return NULL;
}


/* Return TRUE if parameter value is set */
bcmos_bool bcmcli_parm_value_is_set(bcmcli_session *session, const bcmcli_cmd_parm *parm, uint32_t value_index)
{
    bcmcli_session_extras *mon_session=_bcmcli_session_data(session);

    if (value_index >= BCMCLI_MAX_ARRAY_LEN)
    {
        bcmcli_print(NULL, "MON> Value index %u is out of range\n", value_index);
        return BCMOS_FALSE;
    }

    if (!mon_session)
    {
        bcmcli_print(NULL, "MON> Session %p is invalid\n", session);
        return BCMOS_FALSE;
    }

    if (!parm->max_array_size)
        return parm->value.is_set;

    if (value_index >= parm->array_size || !parm->values)
        return BCMOS_FALSE;

    return parm->values[value_index].is_set;
}

/** Print CLI parameter value
 * \param[in]       session         Session handle
 * \param[in]       parm            Parameter
 */
static void bcmcli_parm_value_print(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value)
{
    parm->print_cb(session, parm, value);
}

/** Print CLI parameter
 * \param[in]       session         Session handle
 * \param[in]       parm            Parameter
 */
void bcmcli_parm_print(bcmcli_session *session, const bcmcli_cmd_parm *parm)
{
    if (!bcmcli_parm_is_set(session, parm))
    {
        bcmcli_print(session, "%s=*unset*", parm->name);
        return;
    }
    if (parm->max_array_size)
    {
        int i;
        int values_printed=0;

        if (parm->type != BCMCLI_PARM_STRUCT)
            bcmcli_print(session, "%s=", parm->name);
        for (i=0; i<parm->array_size; i++)
        {
            if (i && parm->type != BCMCLI_PARM_STRUCT)
                bcmcli_print(session, ",");
            if (parm->values[i].is_set)
            {
                if (parm->type == BCMCLI_PARM_STRUCT)
                    bcmcli_print(session, "%s%s[%d]=", values_printed ? " " : "", parm->name, i);
                bcmcli_parm_value_print(session, parm, &parm->values[i]);
                ++values_printed;
            }
        }
    }
    else
    {
        bcmcli_print(session, "%s=", parm->name);
        bcmcli_parm_value_print(session, parm, &parm->value);
    }
}

/** Enable / disable CLI command logging
 * \param[in]   mode    Logging flags
 * \param[in]   session Log session. Must be set if mode != BCMCLI_CMD_LOG_NONE
 * \return 0=OK or error <0
 */
bcmos_errno bcmcli_log_set(bcmcli_log_mode mode, bcmcli_session *session)
{
    if (mode != BCMCLI_LOG_NONE && session == NULL)
    {
        BCMOS_TRACE_ERR("log session must be set\n");
        return BCM_ERR_PARM;
    }
    if (mode == BCMCLI_LOG_NONE)
    {
        _bcmcli_log_session = NULL;
    }
    else
    {
        _bcmcli_log_session = session;
    }
    _bcmcli_log_mode = mode;
    return BCM_ERR_OK;
}

/** Write string to CLI log.
 * The function is ignored if CLI logging is not enabled using bcmcli_log_set()
 * \param[in]   format  printf-like format followed by arguments
 */
void bcmcli_log(const char *format, ...)
{
    va_list ap;
    if (!_bcmcli_log_session)
        return;
    va_start(ap, format);
    bcmcli_session_vprint(_bcmcli_log_session, format, ap);
    va_end(ap);
}

/*********************************************************/
/* Internal functions                                    */
/*********************************************************/

static void _bcmcli_log_cmd(const char *cmd)
{
    switch (_bcmcli_log_mode)
    {
    case BCMCLI_LOG_CLI:
        bcmcli_log("%s\n", cmd);
        break;
    case BCMCLI_LOG_C_COMMENT:
        bcmcli_log("/* %s */\n", cmd);
        break;
    default:
        break;
    }
}

static void _bcmcli_log_rc(bcmos_errno rc)
{
    switch (_bcmcli_log_mode)
    {
    case BCMCLI_LOG_CLI:
        bcmcli_log("# CLI command completed: %s (%d)\n", bcmos_strerror(rc), rc);
        break;
    case BCMCLI_LOG_C_COMMENT:
        bcmcli_log("/* CLI command completed: %s (%d) */\n", bcmos_strerror(rc), rc);
        break;
    default:
        break;
    }

}

static bcmolt_string *_bcmcli_help_string_init(bcmcli_session_extras *mon_session)
{
    bcmolt_string_init(&mon_session->help_string, mon_session->help_buf, sizeof(mon_session->help_buf));
    return &mon_session->help_string;
}

#ifdef CONFIG_LINENOISE
static bcmos_errno _bcmcli_line_edit_cmd(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms)
{
    if (n_parms > 0)
    {
        if ((parm[0].flags & BCMCLI_PARM_FLAG_ASSIGNED))
            linenoiseSetDumbTerminal(session->ln_session, ! parm[0].value.number);
        if ((parm[1].flags & BCMCLI_PARM_FLAG_ASSIGNED))
            linenoiseSetMultiLine(session->ln_session, parm[1].value.number);
    }
    else
    {
        int dumb = linenoiseGetDumbTerminal(session->ln_session);
        int multiline = linenoiseGetMultiLine(session->ln_session);
        bcmcli_session_print(session, "Line editing: %s  Multiline: %s\n",
            dumb ? "off" : "on", multiline ? "on" : "off");
    }
    return BCM_ERR_OK;
}
#endif

/* Allocate root directory and default session */
static void _bcmcli_alloc_root(const bcmcli_session_parm *first_session_parm)
{
    bcmcli_session_parm session_parms;
    bcmcli_session *session;
    int rc;

    /* The very first call. Allocate root structure */
    if ((_bcmcli_root_dir=(bcmcli_entry *)bcmos_calloc(sizeof(bcmcli_entry) + strlen(BCMCLI_ROOT_HELP) + 2 )) == NULL)
        return;
    _bcmcli_root_dir->name = (char *)(_bcmcli_root_dir + 1);
    _bcmcli_root_dir->help = (char *)(_bcmcli_root_dir->name + 1);
    strcpy(_bcmcli_root_dir->help, BCMCLI_ROOT_HELP);
    _bcmcli_root_dir->sel = BCMCLI_ENTRY_DIR;
    _bcmcli_root_dir->access_right = BCMCLI_ACCESS_GUEST;

    memset(&session_parms, 0, sizeof(session_parms));
    session_parms.access_right = BCMCLI_ACCESS_ADMIN;
    session_parms.extra_size = sizeof(bcmcli_session_extras);
    session_parms.name = "monroot";
    if (first_session_parm)
    {
        session_parms.line_edit_mode = first_session_parm->line_edit_mode;
    }
    rc = bcmcli_session_open(&session_parms, &session);
    if (rc)
    {
        bcmos_free(_bcmcli_root_dir);
        _bcmcli_root_dir = NULL;
        _bcmcli_root_session = NULL;
        return;
    }
    _bcmcli_root_session = _bcmcli_session_data(session);
    _bcmcli_root_session->session = session;
    _bcmcli_root_session->curdir = _bcmcli_root_dir;

    /* Add command to disable/enable line editing */
#ifdef CONFIG_LINENOISE
    if (session_parms.line_edit_mode != BCMCLI_LINE_EDIT_DISABLE)
    {
        BCMCLI_MAKE_CMD(NULL, "~", "Enable/disable/query line editing", _bcmcli_line_edit_cmd,
            BCMCLI_MAKE_PARM_ENUM("enable", "Enable line editing", bcmcli_enum_bool_table, BCMCLI_PARM_FLAG_OPTIONAL),
            BCMCLI_MAKE_PARM_ENUM("multiline", "Enable multiline mode", bcmcli_enum_bool_table,
                BCMCLI_PARM_FLAG_OPTIONAL));
    }
#endif
}

/* Display directory */
static void _bcmcli_display_dir(bcmcli_session_extras *mon_session, bcmcli_entry *p_dir)
{
    bcmcli_session *session = mon_session->session;
    bcmcli_entry *p_token;
    bcmcli_entry *prev=NULL;
    bcmolt_string *help_string = _bcmcli_help_string_init(mon_session);

    bcmolt_string_append(help_string, "%s%s> ", (p_dir==_bcmcli_root_dir)?"":".../", p_dir->name );
    p_token = p_dir->u.dir.first;
    while ( p_token )
    {
        if (p_token->access_right <= bcmcli_session_access_right(session))
        {
            if (prev)
                bcmolt_string_append(help_string, ", ");
            bcmolt_string_append(help_string, "%s", p_token->name );
            if (p_token->sel == BCMCLI_ENTRY_DIR )
                bcmolt_string_append(help_string, "/");
            prev = p_token;
        }
        p_token = p_token->next;
    }
    bcmolt_string_append(help_string, "\n");
    bcmcli_session_print(session, "%s", bcmolt_string_get(help_string));
}


/* Is character that can be used in a single token ? */
static inline int _bcmcli_is_special_char(char c)
{
    if (!c)
        return 0;
    return (c == BCMCLI_HELP_CHAR || c == BCMCLI_COMMENT_CHAR || c == BCMCLI_EQUAL_CHAR);
}

/* Make a preliminary analizis of <name> token.
 *   Returns a token type (Empty, Up, Root, Break, Name)
 */
static bcmcli_token_type _bcmcli_analyze_token( const char *name )
{
    if (!name[0] || name[0]==';')
        return BCMCLI_TOKEN_EMPTY;

    if (*name == BCMCLI_COMMENT_CHAR)
        return BCMCLI_TOKEN_BREAK;

    if (!strcmp(name, BCMCLI_UP_STR))
        return BCMCLI_TOKEN_UP;

    if (!strcmp(name, BCMCLI_ROOT_STR))
        return BCMCLI_TOKEN_ROOT;

    if (*name == BCMCLI_HELP_CHAR)
        return BCMCLI_TOKEN_HELP;

    return BCMCLI_TOKEN_VALUE;

}


/* isspace wrapper */
static inline int _bcmcli_isspace(char c)
{
    return isspace((int)c);
}

/* Cut the first word from <p_inbuf>.
 * - Return pointer to start of the word in p_word
 * - 0 terminator is inserted in the end of the word
 * - session->p_inbuf is updated to point after the word
 * Returns token type
 */
static bcmcli_token_type _bcmcli_get_word(bcmcli_session_extras *mon_session, char **buf, char **p_word)
{
    bcmcli_token_type token_type = BCMCLI_TOKEN_EMPTY;
    bcmcli_token_type token_flags = BCMCLI_TOKEN_EMPTY;
    char *p_inbuf = *buf;
    char next_char = 0;
    bcmos_bool quoted_string = BCMOS_FALSE;

    /* Skip leading blanks */
    while (*p_inbuf && (_bcmcli_isspace(*p_inbuf) || (*p_inbuf==',')))
        ++p_inbuf;

    *buf = p_inbuf;
    if (! *p_inbuf)
        return BCMCLI_TOKEN_EMPTY;
    if (*p_inbuf == ';')
    {
        *p_inbuf = 0;
        *buf = ++p_inbuf;
        return BCMCLI_TOKEN_EMPTY;
    }

    /* Quoted string ? */
    if (*p_inbuf == '"')
    {
        quoted_string = BCMOS_TRUE;
        *p_word = ++p_inbuf;
        while ( *p_inbuf && *p_inbuf!='"' )
            ++p_inbuf;
        if (*p_inbuf != '"')
        {
            bcmcli_session_print(mon_session->session, "MON: unterminated string %s\n", *p_word);
            *buf = p_inbuf; /* progress parser past the point of failure */
            return BCMCLI_TOKEN_EMPTY;
        }
        if (*p_inbuf)
            *(p_inbuf++) = 0;
    }
    else if (*p_inbuf == BCMCLI_STRUCT_START_CHAR)
    {
        int bracket_count = 1;

        token_flags |= BCMCLI_TOKEN_STRUCT_VALUE;
        quoted_string = BCMOS_TRUE;
        *p_word = p_inbuf++;
        while (*p_inbuf && bracket_count)
        {
            if (*p_inbuf == BCMCLI_STRUCT_START_CHAR)
                ++bracket_count;
            else if (*p_inbuf == BCMCLI_STRUCT_END_CHAR)
                --bracket_count;
            ++p_inbuf;
        }
        if (bracket_count)
            token_flags |= BCMCLI_TOKEN_UNTERMINATED_STRUCT_VALUE;
        else if (*p_inbuf)
            *(p_inbuf++) = 0;
    }
    else
    {
        *p_word = p_inbuf;
        if (!_bcmcli_is_special_char(*p_inbuf))
        {
            do ++p_inbuf;
            while (*p_inbuf && !_bcmcli_isspace(*p_inbuf) && *p_inbuf!=';' && !_bcmcli_is_special_char(*p_inbuf));
            /* Skip trailing spaces */
            while (*p_inbuf && _bcmcli_isspace(*p_inbuf))
                *(p_inbuf++) = 0;
            next_char = *p_inbuf;
            if (next_char == BCMCLI_EQUAL_CHAR)
            {
                *(p_inbuf++) = 0;
                token_flags |= BCMCLI_TOKEN_HAS_EQUAL_SIGN;
            }
        }
        else if (*p_inbuf)
        {
            ++p_inbuf;
        }
    }
    *buf = p_inbuf;
    token_type   = _bcmcli_analyze_token( *p_word );
    if (token_type == BCMCLI_TOKEN_VALUE &&
        (next_char == BCMCLI_EQUAL_CHAR ||
        ((token_flags & BCMCLI_TOKEN_STRUCT_VALUE) == 0 && strchr(*p_word, BCMCLI_ARRAY_START_CHAR) != NULL)))
    {
        token_type = BCMCLI_TOKEN_NAME;
    }
    if ((token_type == BCMCLI_TOKEN_EMPTY) && quoted_string)
        token_type = BCMCLI_TOKEN_VALUE;
    token_type |= token_flags;
    return token_type;
}


/* split indexed name in format "name[index]" to "name" and "index" component */
static bcmos_errno _bcmcli_set_name_index(bcmcli_session_extras *mon_session, bcmcli_name_value *pair)
{
    char *p_bra, *p_ket;
    uint32_t len;

    if (!pair->name)
        return BCM_ERR_OK;
    p_bra = strchr(pair->name, BCMCLI_ARRAY_START_CHAR);
    if (!p_bra)
        return BCM_ERR_OK;
    p_ket = strchr(p_bra+1, BCMCLI_ARRAY_END_CHAR);

    /* Handle case of missing closing bracket. It can happen either by mistake
     * or during tab completion
     */
    if (!p_ket)
    {
        /* If we are past "=" sign and index is not terminated - it is an error */
        if (pair->value)
        {
            bcmcli_session_print(mon_session->session, "MON: unterminated array index %s\n", pair->name);
            return BCM_ERR_PARM;
        }
        pair->type |= BCMCLI_TOKEN_UNTERMINATED_ARRAY_INDEX;
    }

    *(p_bra++) = 0;
    if (p_ket)
        *p_ket = 0;

    /* Skip leading and trailing spaces */
    while (*p_bra && _bcmcli_isspace(*p_bra))
        ++p_bra;
    len = strlen(p_bra);
    while (len && _bcmcli_isspace(p_bra[len-1]))
    {
        p_bra[len-1] = 0;
        --len;
    }
    pair->index = p_bra;

    return BCM_ERR_OK;
}


#define BCMCLI_SPLIT_RETURN(_rc, _p_str, _copy, _p_stop) \
    do { \
        *(_p_str) += (_p_stop - _copy);\
        return (_rc);\
    } while (0)

/* Split string str to [name=]value pairs.
 * *p_str updated to point to the place where parser stopped
 */
static bcmos_errno _bcmcli_split(bcmcli_session_extras *mon_session, const char **p_str, int p_str_len,
    bcmcli_name_value **p_pairs, int *p_npairs)
{
    const char *str;
    bcmcli_name_value *pairs;
    char *copy_of_str, *tmp_str;
    char *word;
    bcmcli_token_type token_type, prev_type=BCMCLI_TOKEN_EMPTY;
    int n = 0;
    bcmos_errno rc;

    if (!p_str || !*p_str)
        return BCM_ERR_PARM;
    str = *p_str;

    /* Make a copy of parsed string because we are going to insert 0 terminators */
    copy_of_str = bcmcli_session_stack_calloc(mon_session->session, p_str_len + 1);
    if (!copy_of_str)
        return BCM_ERR_NOMEM;

    strncpy(copy_of_str, str, p_str_len);
    copy_of_str[p_str_len] = '\0';

    /* Calculate number of pairs first */
    tmp_str = copy_of_str;
    token_type = _bcmcli_get_word(mon_session, &tmp_str, &word);
    while (token_type != BCMCLI_TOKEN_EMPTY && !(token_type & BCMCLI_TOKEN_BREAK))
    {
        /* Skip =value */
        if (!((prev_type & BCMCLI_TOKEN_NAME) && (token_type & BCMCLI_TOKEN_VALUE)))
            ++n;
        prev_type = token_type;
        token_type = _bcmcli_get_word(mon_session, &tmp_str, &word);
    }
    *p_npairs = n;
    if (!n)
    {
        *p_pairs = NULL;
        rc = (token_type & BCMCLI_TOKEN_BREAK) ? BCM_ERR_NOENT : BCM_ERR_OK;
        BCMCLI_SPLIT_RETURN(rc, p_str, copy_of_str, tmp_str);
    }

    /* Allocate name/value pairs on session stack */
    *p_pairs = pairs = bcmcli_session_stack_calloc(mon_session->session, n * sizeof(bcmcli_name_value));
    if (!pairs)
        BCMCLI_SPLIT_RETURN(BCM_ERR_NOMEM, p_str, copy_of_str, tmp_str);

    /* Now restore the copy of the original string and set names and values */
    rc = BCM_ERR_OK;
    strncpy(copy_of_str, str, p_str_len);
    copy_of_str[p_str_len] = '\0';
    tmp_str = copy_of_str;
    token_type = _bcmcli_get_word(mon_session, &tmp_str, &word);
    prev_type = BCMCLI_TOKEN_EMPTY;
    --pairs; /* it is going to be pre-incremented */
    while ((token_type != BCMCLI_TOKEN_EMPTY) && !(token_type & BCMCLI_TOKEN_BREAK))
    {
        if (!((prev_type & BCMCLI_TOKEN_NAME) && (token_type & BCMCLI_TOKEN_VALUE)))
            ++pairs;
        pairs->type = token_type;
        if (token_type & BCMCLI_TOKEN_NAME)
        {
            pairs->name = word;
            rc = _bcmcli_set_name_index(mon_session, pairs);
            if (rc != BCM_ERR_OK)
                break;
        }
        else
        {
            pairs->value = word;
        }
        prev_type = token_type;
        token_type = _bcmcli_get_word(mon_session, &tmp_str, &word);
    }
    BCMCLI_SPLIT_RETURN(rc, p_str, copy_of_str, tmp_str);
}

/* Find parameter by name */
static bcmcli_cmd_parm *_bcmcli_find_named_parm(bcmcli_session_extras *mon_session, const char *name)
{
    bcmcli_parm_array *pa = _bcmcli_parm_array_cur(mon_session);
    int i;

    if (!pa || !pa->cmd_parms)
        return NULL;

    for (i = 0; i < pa->num_parms; i++)
    {
        if (!_bcmcli_stricmp(name, pa->cmd_parms[i].name, -1))
            return &pa->cmd_parms[i];
    }

    return NULL;
}

/* Extend session parameter table based on selector value */
static bcmos_errno _bcmcli_extend_parm_table(bcmcli_session_extras *mon_session,
    bcmcli_parm_array *pa, bcmcli_cmd_parm **p_selector, const char *value)
{
    bcmcli_cmd_parm *selector = *p_selector;
    bcmcli_enum_val *values=selector->enum_table;
    int nsel = selector - pa->cmd_parms;
    bcmos_errno err;

    /* Find selected value */
    while (values->name)
    {
        if (!_bcmcli_stricmp(values->name, value, -1))
            break;
        ++values;
    }
    if (!values->name)
        return BCM_ERR_INTERNAL;

    /* Extend current parameters array */
    err = _bcmcli_parm_array_extend(mon_session, pa, nsel + 1, values->parms);

    if (err == BCM_ERR_OK)
    {
        *p_selector = &pa->cmd_parms[nsel];
    }

    return err;
}

/* Parse a single parameter value (scalar value or array element) */
static bcmos_errno _bcmcli_parse_1value(bcmcli_session_extras *mon_session, const char *block_name,
    bcmcli_cmd_parm *parm, bcmcli_parm_value *value, const char *string_value,
    int val_len)
{
    bcmos_errno rc;

    if (val_len >= 0)
    {
        /* We are dealing with array element. string_value is comma rather than
         * 0-terminated. Copy it aside.
         */
        char val_copy[val_len + 1];
        strncpy(val_copy, string_value, val_len);
        val_copy[val_len] = 0;
        rc = parm->scan_cb(mon_session->session, parm, value, val_copy);
    }
    else
    {
        rc = parm->scan_cb(mon_session->session, parm, value, string_value);
    }
    if (rc == BCM_ERR_OK)
    {
        value->is_set = BCMOS_TRUE;
    }
    else
    {
        if (!mon_session->suppress_err_print)
        {
            bcmcli_session_print(mon_session->session, "MON: %s> <%s>: value %s is invalid\n",
                block_name, parm->name, string_value);
        }
    }
    return rc;
}


/* Parse parameter value, including array value (comma-delimited list of element values) */
static bcmos_errno _bcmcli_parse_value(bcmcli_session_extras *mon_session, const char *block_name,
    bcmcli_cmd_parm *parm, bcmcli_name_value *name_value)
{
    bcmos_errno rc = BCM_ERR_OK;
    const char *string_value = name_value->value;

    if (name_value->index && !parm->max_array_size)
    {
        bcmcli_session_print(mon_session->session, "MON: %s>: <%s> unexpected index %s\n",
            block_name, parm->name, name_value->index);
        return BCM_ERR_PARM;
    }

    if (parm->max_array_size)
    {
        uint32_t i = 0;
        uint32_t index;

        /* Specific index ? */
        if (name_value->index)
        {
            char *p_end = NULL;
            index = strtoul(name_value->index, &p_end, 0);
            if (index >= parm->max_array_size || (p_end && *p_end) )
            {
                bcmcli_session_print(mon_session->session, "MON: %s>: <%s> index %s is invalid\n",
                    block_name, parm->name, name_value->index);
                return BCM_ERR_PARM;
            }
            rc = _bcmcli_parse_1value(mon_session, block_name,
                parm, &parm->values[index], string_value, -1);
            if (rc == BCM_ERR_OK && parm->array_size < index + 1)
                parm->array_size = index + 1;
        }
        else if (_bcmcli_stricmp(string_value, BCMCLI_ARRAY_EMPTY, -1))
        {
            /* parse comma-delimited array element values */
            for (i = 0; i < parm->max_array_size && string_value && *string_value && !rc; i++)
            {
                const char *pcomma;
                int val_len;

                pcomma = strchr(string_value, BCMCLI_ARRAY_DELIM_CHAR);
                if (pcomma)
                {
                    val_len = pcomma - string_value;
                }
                else
                {
                    val_len = -1; /* to the end of string */
                }
                /* No value ? */
                if (_bcmcli_stricmp(string_value, BCMCLI_PARM_NO_VALUE, val_len))
                {
                    rc = _bcmcli_parse_1value(mon_session, block_name,
                        parm, &parm->values[i], string_value, val_len);
                }
                string_value = pcomma ? pcomma + 1 : NULL;
            }
            /* If all parsed values were ok, but we have more values than array size - it is an error */
            if (string_value && *string_value && !rc)
            {
                rc = BCM_ERR_TOO_MANY;
                if (!mon_session->suppress_err_print)
                {
                    bcmcli_session_print(mon_session->session, "MON: %s> <%s>: too many values. %s is invalid\n",
                        block_name, parm->name, string_value);
                }
            }
            parm->array_size = i;
        }
    }
    else
    {
        if (string_value && strcmp(string_value, BCMCLI_PARM_NO_VALUE))
        {
            rc = _bcmcli_parse_1value(mon_session, block_name,
                parm, &parm->value, string_value, -1);
        }
    }

    return rc;
}

/* Populate session parameters. Apply selectors */
static bcmos_errno _bcmcli_populate_parms(
    bcmcli_session_extras *mon_session,
    const char *block_name,
    bcmcli_parm_array *pa)
{
    const char *parm_value;
    int positional=1;
    bcmcli_cmd_parm *parms = pa->cmd_parms;
    bcmcli_name_value *pairs = pa->name_value_pairs;
    bcmcli_cmd_parm *cur_parm;
    bcmos_errno rc = BCM_ERR_OK;
    int i;
    int j;

    pa->num_parsed = 0;
    parms=pa->cmd_parms;

    /* Build a format string */
    for (i=0; i<pa->num_pairs && pairs[i].type != BCMCLI_TOKEN_BREAK; i++)
    {
        mon_session->cur_token_type = pairs[i].type;
        parm_value = pairs[i].value;
        pa->num_parsed = i;
        cur_parm = NULL;
        rc = BCM_ERR_PARM;

        /* Named parameter ? */
        if (pairs[i].name)
        {
            positional = 0; /* No more positional parameters */
            /* Check name */
            cur_parm = _bcmcli_find_named_parm(mon_session, pairs[i].name);
            if (!cur_parm)
            {
                if (!mon_session->suppress_err_print)
                {
                    bcmcli_session_print(mon_session->session, "MON: %s> parameter <%s> doesn't exist\n",
                        block_name, pairs[i].name);
                }
                break;
            }
            if (!parm_value)
            {
                if (!mon_session->suppress_err_print)
                {
                    bcmcli_session_print(mon_session->session, "MON: %s> <%s>: value is missing\n",
                        block_name, cur_parm->name);
                }
                break;
            }
        }
        else
        {
            /* Parse the parameter name alone (without =value) if the proper flag is set. */
            if (parm_value
                && ((cur_parm = _bcmcli_find_named_parm(mon_session, parm_value)) != NULL)
                && (cur_parm->flags & BCMCLI_PARM_FLAG_OMIT_VAL) != 0)
            {
                parm_value = NULL;
                cur_parm->flags |= BCMCLI_PARM_FLAG_DEFVAL;
                /* If the value-less parameter is an enum, set it to the first enum value. Else, leave it default. */
                if (cur_parm->type == BCMCLI_PARM_ENUM)
                {
                    cur_parm->value.enum_val = cur_parm->enum_table->val;
                }
                positional = 0; /* No more positional parameters */
            }
            else if (parms)
            {
                if (!positional || (parms[i].type == BCMCLI_PARM_STRUCT))
                {
                    if (!mon_session->suppress_err_print)
                        bcmcli_session_print(mon_session->session, "MON: %s> Expected named parameter. Got %s\n", block_name, parm_value);
                    break;
                }
                cur_parm = &parms[i];
            }
            if (!cur_parm || !cur_parm->name)
            {
                if (!mon_session->suppress_err_print)
                    bcmcli_session_print(mon_session->session, "MON: %s> Too many parameters. %s is unexpected\n", block_name, parm_value);
                break;
            }
        }

        if ((cur_parm->flags & BCMCLI_PARM_FLAG_ASSIGNED) && !cur_parm->max_array_size)
        {
            if (!mon_session->suppress_err_print)
            {
                bcmcli_session_print(mon_session->session, "MON: %s> Attempt to assign parameter %s more than once\n",
                    block_name, cur_parm->name);
            }
            break;
        }

        if (pairs[i].index && !cur_parm->max_array_size)
        {
            bcmcli_session_print(mon_session->session, "MON: %s> %s: index %s is unexpected for scalar parameter\n",
                block_name, cur_parm->name, pairs[i].index);
        }

        if (parm_value)
        {
            if (cur_parm->type == BCMCLI_PARM_STRING)
                cur_parm->value.string = parm_value;
            else
            {
                rc = _bcmcli_parse_value(mon_session, block_name, cur_parm, &pairs[i]);
                if (rc)
                    break;

                /* For parameter-selector extend list of parameters accordingly */
                if (cur_parm->flags & BCMCLI_PARM_FLAG_SELECTOR)
                {
                    rc = _bcmcli_extend_parm_table(mon_session, pa, &cur_parm, parm_value);
                    if (rc)
                        break;
                }
            }
            cur_parm->flags |= BCMCLI_PARM_FLAG_ASSIGNED;

            /* Check range */
            if ((cur_parm->flags & BCMCLI_PARM_FLAG_RANGE))
            {
                if (cur_parm->max_array_size)
                {
                    for (j = 0; j < cur_parm->array_size; j++)
                    {
                        if (((cur_parm->values[j].number < cur_parm->low_val) ||
                            (cur_parm->values[j].number > cur_parm->hi_val)))
                        {
                            bcmcli_session_print(mon_session->session, "\nMON: %s> <%s>: %ld out of range (%ld, %ld)\n",
                                block_name, cur_parm->name, cur_parm->values[j].number, cur_parm->low_val, cur_parm->hi_val);
                            rc = BCM_ERR_RANGE;
                            break;
                        }
                    }
                    if (j < cur_parm->array_size)
                        break;
                }
                else if (((cur_parm->value.number < cur_parm->low_val) ||
                    (cur_parm->value.number > cur_parm->hi_val)))
                {
                    bcmcli_session_print(mon_session->session, "\nMON: %s> <%s>: %ld out of range (%ld, %ld)\n",
                        block_name, cur_parm->name, cur_parm->value.number, cur_parm->low_val, cur_parm->hi_val);
                    rc = BCM_ERR_RANGE;
                    break;
                }
            }
        }
        rc = BCM_ERR_OK;
    }
    pa->num_parsed = i;

    /* Final validation */
    if (mon_session->is_execution && rc == BCM_ERR_OK)
    {
        /* Make sure that all mandatory parameters are set. Process default values */
        for (i=0; i<pa->num_parms; i++)
        {
            rc = BCM_ERR_PARM;
            cur_parm = &pa->cmd_parms[i];

            if (!(cur_parm->flags & BCMCLI_PARM_FLAG_ASSIGNED))
            {
                if ((cur_parm->flags & BCMCLI_PARM_FLAG_DEFVAL))
                {
                    cur_parm->flags |= BCMCLI_PARM_FLAG_ASSIGNED;
                }
                else if (!(cur_parm->flags & BCMCLI_PARM_FLAG_OPTIONAL) )
                {
                    /* Mandatory parameter missing */
                    bcmcli_session_print(mon_session->session, "MON: %s> Mandatory parameter <%s> is missing\n",
                        block_name, cur_parm->name);
                    break;
                }
            }
            rc = BCM_ERR_OK;
        }
    }

    return rc;
}

/* Parse p_inbuf string based on parameter descriptions in <p_token>.
 *   Fill parameter values in <p_token>.
 *   Returns the number of parameters filled or BCM_ERR_PARM
 *   To Do: add a option of one-by-one user input of missing parameters.
 */
static bcmos_errno _bcmcli_parse_parms( bcmcli_session_extras *mon_session, bcmcli_entry *cmd, bcmcli_name_value *pairs, int npairs)
{
    bcmcli_parm_array *pa;
    bcmos_errno rc;

    /* Make sure that all structures are terminated */
    if (npairs && (pairs[npairs-1].type & BCMCLI_TOKEN_UNTERMINATED_STRUCT_VALUE))
    {
        bcmcli_session_print(mon_session->session, "MON: %s> Unterminated structure <%s>\n",
            cmd->name, pairs[npairs-1].name ? pairs[npairs-1].name : "");
        return BCM_ERR_PARM;
    }

    /* Create parameters array */
    pa = _bcmcli_parm_array_create(mon_session, NULL, NULL, cmd->u.cmd.parms, pairs, npairs);
    if (pa == NULL)
        return BCM_ERR_NOMEM;

    /* Populate parameter table */
    mon_session->curcmd = cmd;
    rc = _bcmcli_populate_parms(mon_session, cmd->name, pa);

    return rc;
}

/* insert value skipping partial match trhat is already present */
static void _bcmcli_insert(const char *partial_match, const char *insert_val1,
    const char *insert_val2, char *insert_str, uint32_t insert_size)
{
    if (partial_match)
        insert_val1 += strlen(partial_match);
    bcmolt_strncat(insert_str, insert_val1, insert_size);
    if (insert_val2)
        bcmolt_strncat(insert_str, insert_val2, insert_size);
}

static void _bcmcli_update_longest_match(char *longest_match, const char *name)
{
    uint32_t nlen = strlen(name);
    uint32_t lmlen = strlen(longest_match);

    if (nlen < lmlen)
    {
        lmlen = nlen;
    }
    while (lmlen && memcmp(longest_match, name, lmlen))
    {
        --lmlen;
    }
    longest_match[lmlen] = 0;
}


static void _bcmcli_help_parm_brief(bcmcli_session_extras *mon_session, const bcmcli_cmd_parm *parm)
{
    bcmcli_session_print(mon_session->session, "\n\t%s(%s)", parm->name, _bcmcli_get_type_name(parm));
    if (parm->max_array_size || parm->type == BCMCLI_PARM_BUFFER)
    {
        uint32_t num_entries = (parm->type == BCMCLI_PARM_BUFFER) ? parm->value.buffer.len : parm->max_array_size;
        bcmcli_session_print(mon_session->session, "[%u]", num_entries);
    }
    if ((parm->flags & BCMCLI_PARM_FLAG_RANGE))
    {
        bcmcli_parm_value low_val = { {.number = parm->low_val} };
        bcmcli_parm_value hi_val = { {.number = parm->hi_val} };

        bcmcli_session_print(mon_session->session, " [");
        parm->print_cb(mon_session->session, parm, &low_val);
        bcmcli_session_print(mon_session->session, "..");
        parm->print_cb(mon_session->session, parm, &hi_val);
        bcmcli_session_print(mon_session->session, "]");
    }
    bcmcli_session_print(mon_session->session, "- %s\n", parm->description);
}

/* extend value.
 * If !enum - do nothing
 * If more than 1 matching value - display them
 * If no matching value - do nothing
 * If 1 matching value - insert
 */
static void _bcmcli_extend_value(bcmcli_session_extras *mon_session, bcmcli_cmd_parm *parm,
    const char *partial_value, char *insert_str, uint32_t insert_size)
{
    int nmatch = 0;
    bcmcli_enum_val *vals = parm->enum_table;
    char longest_match[BCMCLI_MAX_SEARCH_SUBSTR_LENGTH]="";

    if ((parm->type != BCMCLI_PARM_ENUM && parm->type != BCMCLI_PARM_ENUM_MASK) || !vals)
    {
        if (parm->type == BCMCLI_PARM_STRUCT && partial_value == NULL)
            bcmolt_strncat(insert_str, BCMCLI_STRUCT_START_STR, insert_size);
        _bcmcli_help_parm_brief(mon_session, parm);
        return;
    }

    /* If enum mask, partial value can be a sum of values. Skip past the last '+' sign */
    if (parm->type == BCMCLI_PARM_ENUM_MASK && partial_value)
    {
        char *pdel = strrchr(partial_value, BCMCLI_ENUM_MASK_DEL_CHAR);
        if (pdel)
            partial_value = pdel + 1;
    }

    while (vals->name)
    {
        if (!partial_value || !strncmp(vals->name, partial_value, strlen(partial_value)))
        {
            if (!nmatch)
            {
                bcmolt_strncat(longest_match, vals->name, sizeof(longest_match));
            }
            else
            {
                _bcmcli_update_longest_match(longest_match, vals->name);
            }
            ++nmatch;
        }
        ++vals;
    }
    if (!nmatch)
        return;
    if (nmatch == 1)
    {
        _bcmcli_insert(partial_value, longest_match, " ", insert_str, insert_size);
        return;
    }
    /* display all matching values */
    _bcmcli_insert(partial_value, longest_match, "", insert_str, insert_size);
    bcmcli_session_print(mon_session->session, "\n");
    vals = parm->enum_table;
    while (vals->name)
    {
        if (!partial_value || !strncmp(vals->name, partial_value, strlen(partial_value)))
            bcmcli_session_print(mon_session->session, " %s", vals->name);
        ++vals;
    }
    bcmcli_session_print(mon_session->session, "\n");
}

/* calculate number of matching parameter names */
static int _bcmcli_num_matching_names(bcmcli_session_extras *mon_session, const char *partial_value, const bcmcli_cmd_parm **first_match)
{
    bcmcli_parm_array *pa = _bcmcli_parm_array_cur(mon_session);
    int i;
    int nmatch = 0;

    *first_match = NULL;
    if (!pa)
        return 0;
    for (i = 0; i < pa->num_parms; i++)
    {
        uint32_t flags = pa->cmd_parms[i].flags;
        if ((flags & BCMCLI_PARM_FLAG_ASSIGNED))
            continue;
        if (partial_value && strncmp(pa->cmd_parms[i].name, partial_value, strlen(partial_value)))
            continue;
        if (*first_match == NULL)
            *first_match = &pa->cmd_parms[i];
        ++nmatch;
    }
    return nmatch;
}

/* calculate longest matching string.
 * returns number of matching parameters
 */
static int _bcmcli_longest_match(bcmcli_session_extras *mon_session, const char *partial_value,
    char *longest_match, uint32_t longest_match_size, const bcmcli_cmd_parm **first_match)
{
    int nmatch0 = _bcmcli_num_matching_names(mon_session, partial_value, first_match);
    int nmatch;
    const char *match_name;

    if (!nmatch0)
        return 0;
    match_name = (*first_match)->name;
    if (nmatch0 == 1)
    {
        bcmolt_strncpy(longest_match, match_name, longest_match_size);
        return nmatch0;
    }
    bcmolt_strncpy(longest_match, match_name, longest_match_size);
    nmatch = _bcmcli_num_matching_names(mon_session, longest_match, first_match);
    while (nmatch != nmatch0)
    {
        longest_match[strlen(longest_match)-1] = 0;
        nmatch = _bcmcli_num_matching_names(mon_session, longest_match, first_match);
    }
    return nmatch0;
}

/* display/insert unset matching names
 * If more than 1 matching value - display them
 * If no matching value - do nothing
 * If 1 matching value - insert
 */
static void _bcmcli_extend_name(bcmcli_session_extras *mon_session, const char *partial_value,
    char *insert_str, uint32_t insert_size)
{
    char longest_match[BCMCLI_MAX_SEARCH_SUBSTR_LENGTH]="";
    const bcmcli_cmd_parm *first_match;
    int nmatch = _bcmcli_longest_match(mon_session, partial_value, longest_match,
        sizeof(longest_match), &first_match);

    if (!nmatch)
        return;
    if (!partial_value || strcmp(partial_value, longest_match) || (nmatch==1))
    {
        if (nmatch == 1 && first_match->type == BCMCLI_PARM_STRUCT && first_match->max_array_size)
        {
            _bcmcli_insert(partial_value, longest_match, BCMCLI_ARRAY_START_STR, insert_str, insert_size);
        }
        else
        {
            _bcmcli_insert(partial_value, longest_match, (nmatch == 1) ? "=" : "", insert_str, insert_size);
            if (nmatch == 1 && first_match->type == BCMCLI_PARM_STRUCT)
                bcmolt_strncat(insert_str, BCMCLI_STRUCT_START_STR, insert_size);
        }
    }
    else
    {
        _bcmcli_help_populated_cmd(mon_session, mon_session->curcmd, partial_value, BCMOS_TRUE);
    }
}

static bcmos_bool _bcmcli_is_first_struct_field(bcmcli_session_extras *mon_session)
{
    bcmcli_parm_array *pa = _bcmcli_parm_array_cur(mon_session);
    return (pa != _bcmcli_parm_array_top(mon_session) && !pa->num_parsed);

}

static bcmos_errno _bcmcli_extend_parms( bcmcli_session_extras *mon_session, bcmcli_name_value *pairs,
    int npairs, bcmos_bool last_is_space, char *insert_str, uint32_t insert_size)
{
    bcmos_errno rc;
    bcmcli_cmd_parm *help_parm = NULL;
    bcmcli_parm_array *pa;
    int i;

    /* Create parameters array */
    pa = _bcmcli_parm_array_create(mon_session, NULL, NULL, mon_session->curcmd->u.cmd.parms, pairs, npairs);
    if (pa == NULL)
        return BCM_ERR_NOMEM;

    rc = _bcmcli_populate_parms(mon_session, mon_session->curcmd->name, pa);

    pa = _bcmcli_parm_array_cur(mon_session);
    if (!pa)
        return BCM_ERR_INTERNAL;

    if (rc == BCM_ERR_OK)
    {
        /* If it is unterminated structure and all fields are set, insert terminator */
        if ((pa != _bcmcli_parm_array_top(mon_session)) && _bcmcli_parm_array_is_all_set(mon_session, pa))
        {
            bcmolt_strncat(insert_str, BCMCLI_STRUCT_END_STR, insert_size);
            pa = _bcmcli_parm_array_pop(mon_session);
        }

        /* So far so good */
        /* If there is unset mandatory parameter - insert its name.
         * Otherwise, display list of unset optionally parameters
         */
        /* Find mandatory parameter that is still unassigned */
        for (i = 0; i < pa->num_parms; i++)
        {
            uint32_t flags = pa->cmd_parms[i].flags;
            if (!(flags & (BCMCLI_PARM_FLAG_OPTIONAL | BCMCLI_PARM_FLAG_DEFVAL | BCMCLI_PARM_FLAG_ASSIGNED)))
            {
                help_parm = &pa->cmd_parms[i];
                break;
            }
        }
        if (help_parm)
        {
            /* About to insert the next mandatory parameter.
             * Add space before name if it is not the 1st structure field
             */
            if (!last_is_space && !_bcmcli_is_first_struct_field(mon_session))
                bcmolt_strncat(insert_str, " ", insert_size);
            bcmolt_strncat(insert_str, help_parm->name, insert_size);
            if (help_parm->type == BCMCLI_PARM_STRUCT)
            {
                if (help_parm->max_array_size)
                    bcmolt_strncat(insert_str, BCMCLI_ARRAY_START_STR, insert_size);
                else
                    bcmolt_strncat(insert_str, "=" BCMCLI_STRUCT_START_STR, insert_size);
            }
            else
            {
                bcmolt_strncat(insert_str, "=", insert_size);
            }
        }
        else if (!_bcmcli_parm_array_is_all_set(mon_session, pa))
        {
            if (!last_is_space && !_bcmcli_is_first_struct_field(mon_session))
                bcmolt_strncat(insert_str, " ", insert_size);
            _bcmcli_help_populated_cmd(mon_session, mon_session->curcmd, NULL, BCMOS_TRUE);
        }
    }
    else
    {
        /* Parsing failed. See what stopped at */
        if ((pa->num_parsed < pa->num_pairs) && (pa->name_value_pairs != NULL))
        {
            bcmcli_name_value *last_pair;

            last_pair = &pa->name_value_pairs[pa->num_parsed];
            /* Try to identify by name */
            help_parm = _bcmcli_find_named_parm(mon_session, last_pair->name ? last_pair->name : last_pair->value);
            if (help_parm)
            {
                /* Handle arrays */
                if (last_pair->index)
                {
                    if (!help_parm->max_array_size)
                        return BCM_ERR_OK; /* Error message is already printed */
                    if (! *last_pair->index)
                    {
                        _bcmcli_help_parm_brief(mon_session, help_parm);
                        return BCM_ERR_OK;
                    }
                    if ((last_pair->type & BCMCLI_TOKEN_UNTERMINATED_ARRAY_INDEX) != 0)
                    {
                        bcmolt_strncat(insert_str, BCMCLI_ARRAY_END_STR, insert_size);
                    }
                    if (!last_pair->value && !(last_pair->type & BCMCLI_TOKEN_HAS_EQUAL_SIGN))
                    {
                        bcmolt_strncat(insert_str, "=", insert_size);
                    }
                }
                else if (help_parm->max_array_size && help_parm->type == BCMCLI_PARM_STRUCT)
                {
                    /* Setting multiple values at once is not supported for structures */
                    bcmolt_strncat(insert_str, BCMCLI_ARRAY_START_STR, insert_size);
                    _bcmcli_help_parm_brief(mon_session, help_parm);
                    return BCM_ERR_OK;
                }
                else if (!help_parm->max_array_size &&
                    !last_pair->name &&
                    !(last_pair->type & BCMCLI_TOKEN_HAS_EQUAL_SIGN))
                {
                    bcmolt_strncat(insert_str, "=", insert_size);
                }

                /* Looking for values */
                _bcmcli_extend_value(mon_session, help_parm, last_pair->value, insert_str, insert_size);
            }
            else
            {
                /* Looking for partial name */
                _bcmcli_extend_name(mon_session, last_pair->name ? last_pair->name : last_pair->value,
                    insert_str, insert_size);
            }
        }
    }

    return BCM_ERR_OK;
}

/* Identify token in the given directory */
static bcmcli_entry *_bcmcli_search_token1( bcmcli_entry *p_dir, const char **p_name, int name_len )
{
    bcmcli_entry *p_token = NULL;
    const char *name = *p_name;
    bcmcli_token_type type=_bcmcli_analyze_token(name);

    /* Name can be qualified */
    if ((type & BCMCLI_TOKEN_VALUE) && !strncmp(name, BCMCLI_UP_STR, name_len))
        type = BCMCLI_TOKEN_UP;

    switch(type & BCMCLI_TOKEN_TYPE_MASK)
    {
        case BCMCLI_TOKEN_ROOT:
            p_token = _bcmcli_root_dir;
            *p_name = name + strlen(BCMCLI_ROOT_STR);
            break;
        case BCMCLI_TOKEN_UP:
            if (p_dir->parent)
                p_token = p_dir->parent;
            else
                p_token = p_dir;
            *p_name = name + strlen(BCMCLI_UP_STR) + 1;
            break;
        case BCMCLI_TOKEN_NAME:
        case BCMCLI_TOKEN_VALUE:
            /* Check alias */
            p_token = p_dir->u.dir.first;
            while ( p_token )
            {
                if (p_token->alias &&
                        (name_len == p_token->alias_len) &&
                        !_bcmcli_stricmp(p_token->alias, name, p_token->alias_len))
                    break;
                p_token = p_token->next;
            }
            if (!p_token)
            {
                bcmcli_entry *partial_match = NULL;
                /* Check name */
                p_token = p_dir->u.dir.first;
                while( p_token )
                {
                    if (!_bcmcli_stricmp(p_token->name, name, name_len))
                    {
                        if (name_len == strlen(p_token->name))
                            break;
                        if (!partial_match)
                            partial_match = p_token;
                    }
                    p_token = p_token->next;
                }
                if (!p_token)
                    p_token = partial_match;
            }
            *p_name = name + name_len + 1;
            break;
        default:
            break;
    }

    return p_token;
}


/* Search a token by name in the current directory.
 * The name can be qualified (contain path)
 */
static bcmcli_entry *_bcmcli_search_token( bcmcli_entry *p_dir, const char *name )
{
    bcmcli_entry *p_token;
    const char *name0 = name;
    const char *p_slash;

    if (!name[0])
        return p_dir;

    /* Check if name is qualified */
    do
    {
        p_slash = strchr(name, '/');
        if (p_slash)
        {
            if (p_slash == name0)
            {
                p_dir = p_token = _bcmcli_root_dir;
                name = p_slash + 1;
            }
            else
            {
                p_token = _bcmcli_search_token1(p_dir, &name, p_slash - name);
                if (p_token && (p_token->sel == BCMCLI_ENTRY_DIR))
                    p_dir = p_token;
            }
        }
        else
        {
            p_token = _bcmcli_search_token1(p_dir, &name, strlen(name));
        }
    } while (p_slash && p_token && *name);

    return p_token;
}



/* Display help for each entry in the current directory */
static void  _bcmcli_help_dir(bcmcli_session_extras *mon_session, bcmcli_entry *p_dir)
{
    bcmolt_string *help_string = _bcmcli_help_string_init(mon_session);
    bcmcli_entry *p_token;
    char buffer[BCMCLI_MAX_QUAL_NAME_LENGTH];

    _bcmcli_qualified_name(p_dir, buffer, sizeof(buffer));
    bcmolt_string_append(help_string, "Directory %s/ - %s\n", buffer, p_dir->help);
    bcmolt_string_append(help_string, "Commands:\n");

    p_token = p_dir->u.dir.first;
    while (p_token)
    {
        if (bcmcli_session_access_right(mon_session->session) >= p_token->access_right)
        {
            if (p_token->sel == BCMCLI_ENTRY_DIR)
                bcmolt_string_append(help_string, "\t%s/:  %s directory\n", p_token->name, p_token->help );
            else
            {
                char *peol = strchr(p_token->help, '\n');
                int help_len = peol ? peol - p_token->help : (int)strlen(p_token->help);
                bcmolt_string_append(help_string, "\t%s(%d parms): %.*s\n",
                            p_token->name, p_token->u.cmd.num_parms, help_len, p_token->help );
            }
        }
        p_token = p_token->next;
    }
    bcmolt_string_append(help_string, "Type ? <name> for command help, \"/\"-root, \"..\"-upper\n" );
    bcmcli_session_print(mon_session->session, "%s", bcmolt_string_get(help_string));
}

/* Display help a token */
static void _bcmcli_help_populated_cmd(bcmcli_session_extras *mon_session, bcmcli_entry *p_token,
    const char *partial_match, bcmos_bool suppress_assigned)
{
    bcmcli_parm_array *pa = _bcmcli_parm_array_cur(mon_session);
    char bra, ket;
    uint16_t i;

    if (!pa)
        return;
    if (suppress_assigned)
        bcmcli_session_print(mon_session->session, "\n");
    for ( i=0; i<pa->num_parms; i++ )
    {
        bcmcli_cmd_parm *cur_parm = &pa->cmd_parms[i];
        if (suppress_assigned && (cur_parm->flags & BCMCLI_PARM_FLAG_ASSIGNED))
            continue;
        if (partial_match && memcmp(partial_match, cur_parm->name, strlen(partial_match)))
            continue;

        if ((cur_parm->flags & BCMCLI_PARM_FLAG_OPTIONAL))
        {
            bra = '[';
            ket=']';
        }
        else
        {
            bra = '<';
            ket='>';
        }
        bcmcli_session_print(mon_session->session, "\t%c%s(%s)", bra, cur_parm->name, _bcmcli_get_type_name(cur_parm) );
        if (cur_parm->max_array_size || cur_parm->type == BCMCLI_PARM_BUFFER)
        {
            uint32_t num_entries = (cur_parm->type == BCMCLI_PARM_BUFFER) ? cur_parm->value.buffer.len : cur_parm->max_array_size;
            bcmcli_session_print(mon_session->session, "[%u]", num_entries);
        }
        if (cur_parm->type == BCMCLI_PARM_ENUM || cur_parm->type == BCMCLI_PARM_ENUM_MASK)
        {
            bcmcli_enum_val *values=cur_parm->enum_table;
            bcmcli_session_print(mon_session->session, " {");
            while (values->name)
            {
                if (values!=cur_parm->enum_table)
                    bcmcli_session_print(mon_session->session, ", ");
                bcmcli_session_print(mon_session->session, "%s", values->name);
                ++values;
            }
            bcmcli_session_print(mon_session->session, "}");
        }
        if ((cur_parm->flags & BCMCLI_PARM_FLAG_DEFVAL))
        {
            bcmcli_session_print(mon_session->session, "=");
            cur_parm->print_cb(mon_session->session, cur_parm, &cur_parm->value);
        }
        if ((cur_parm->flags & BCMCLI_PARM_FLAG_RANGE))
        {
            bcmcli_parm_value low_val = { {.number = cur_parm->low_val} };
            bcmcli_parm_value hi_val = { {.number = cur_parm->hi_val} };

            bcmcli_session_print(mon_session->session, " [");
            cur_parm->print_cb(mon_session->session, cur_parm, &low_val);
            bcmcli_session_print(mon_session->session, "..");
            cur_parm->print_cb(mon_session->session, cur_parm, &hi_val);
            bcmcli_session_print(mon_session->session, "]");
        }
        bcmcli_session_print(mon_session->session, "%c ", ket);
        bcmcli_session_print(mon_session->session, "- %s\n", cur_parm->description);
    }

    /* Print extra help if command has unresolved selector */
    if (pa->num_parms &&
        (pa->cmd_parms[pa->num_parms-1].flags & BCMCLI_PARM_FLAG_SELECTOR) &&
        !(pa->cmd_parms[pa->num_parms-1].flags & BCMCLI_PARM_FLAG_ASSIGNED))
    {
        const char *sel_name = pa->cmd_parms[pa->num_parms-1].name;
        bcmcli_session_print(mon_session->session, "Add %s=%s_value to see %s-specific parameters\n",
            sel_name, sel_name, sel_name);
    }
    bcmcli_session_print(mon_session->session, "\n");
}


/* Display help a token */
static void _bcmcli_help_entry(bcmcli_session_extras *mon_session, bcmcli_entry *p_token,
    bcmcli_name_value *pairs, int npairs)
{
    char buffer[BCMCLI_MAX_QUAL_NAME_LENGTH];
    bcmcli_parm_array *pa;

    if (p_token->sel == BCMCLI_ENTRY_DIR)
    {
        _bcmcli_help_dir(mon_session, p_token);
        return;
    }
    mon_session->curcmd = p_token;
    pa = _bcmcli_parm_array_cur(mon_session);
    if (pa == NULL)
    {
        /* Create parameters array */
        pa = _bcmcli_parm_array_create(mon_session, NULL, NULL, p_token->u.cmd.parms, pairs, npairs);
        if (pa == NULL)
            return;
        /* Populate parameter table */
        _bcmcli_populate_parms(mon_session, p_token->name, pa);
    }

    _bcmcli_qualified_name(p_token, buffer, sizeof(buffer));
    bcmcli_session_print(mon_session->session, "%s: \t%s\n", buffer, p_token->help );
    if (pa->num_parms)
    {
        if (pa->in_parm)
            bcmcli_session_print(mon_session->session, "Structure %s fields:\n", pa->in_parm);
        else
            bcmcli_session_print(mon_session->session, "Parameters:\n");
        _bcmcli_help_populated_cmd(mon_session, p_token, NULL, BCMOS_FALSE);
    }
}


/* Choose unique alias for <name> in <p_dir> */
/* Currently only single-character aliases are supported */
static void __bcmcli_chooseAlias(bcmcli_entry *p_dir, bcmcli_entry *p_new_token, int from)
{
    bcmcli_entry *p_token;
    int         i;
    char        c;

    _bcmcli_strlwr( p_new_token->name );
    i = from;
    while ( p_new_token->name[i] )
    {
        c = p_new_token->name[i];
        p_token = p_dir->u.dir.first;

        while ( p_token )
        {
            if (p_token->alias &&
                    (tolower( *p_token->alias ) == c) )
                break;
            if (strlen(p_token->name)<=2 && tolower(p_token->name[0])==c)
                break;
            p_token = p_token->next;
        }
        if (p_token)
            ++i;
        else
        {
            p_new_token->name[i] = toupper( c );
            p_new_token->alias   = &p_new_token->name[i];
            p_new_token->alias_len = 1;
            break;
        }
    }
}

/* isupper wrapper */
static inline int _bcmcli_isupper(char c)
{
    return isupper((int)c);
}

static void _bcmcli_choose_alias(bcmcli_entry *p_dir, bcmcli_entry *p_new_token)
{
    int i=0;
    p_new_token->alias_len = 0;
    p_new_token->alias = NULL;
    /* Don't try to alias something short */
    if (strlen(p_new_token->name) < BCMCLI_MIN_NAME_LENGTH_FOR_ALIAS)
        return;
    /* Try pre-set alias 1st */
    while ( p_new_token->name[i] )
    {
        if (_bcmcli_isupper(p_new_token->name[i]))
            break;
        i++;
    }
    if (p_new_token->name[i])
        __bcmcli_chooseAlias(p_dir, p_new_token, i);
    if (p_new_token->alias != &p_new_token->name[i])
        __bcmcli_chooseAlias(p_dir, p_new_token, 0);
}


/* Convert string s to lower case. Return pointer to s */
static char  * _bcmcli_strlwr( char *s )
{
    char  *s0=s;

    while ( *s )
    {
        *s = tolower( *s );
        ++s;
    }

    return s0;
}


/* Compare strings case incensitive */
static int _bcmcli_stricmp(const char *s1, const char *s2, int len)
{
    int  i;

    for ( i=0; (i<len || len<0); i++ )
    {
        if (tolower( s1[i]) != tolower( s2[i] ))
            return 1;
        if (!s1[i])
            break;
    }

    return 0;
}

static const char *_bcmcli_get_type_name(const bcmcli_cmd_parm *parm)
{
    bcmcli_parm_type type = parm->type;
    static const char *type_name[] = {
        [BCMCLI_PARM_DECIMAL]    = "decimal",
        [BCMCLI_PARM_DECIMAL64]  = "decimal64",
        [BCMCLI_PARM_UDECIMAL]   = "udecimal",
        [BCMCLI_PARM_UDECIMAL64] = "udecimal64",
        [BCMCLI_PARM_HEX]        = "hex",
        [BCMCLI_PARM_HEX64]      = "hex64",
        [BCMCLI_PARM_NUMBER]     = "number",
        [BCMCLI_PARM_NUMBER64]   = "number64",
        [BCMCLI_PARM_UNUMBER]    = "unumber",
        [BCMCLI_PARM_UNUMBER64]  = "unumber64",
        [BCMCLI_PARM_FLOAT]      = "float",
        [BCMCLI_PARM_DOUBLE]     = "double",
        [BCMCLI_PARM_ENUM]       = "enum",
        [BCMCLI_PARM_ENUM_MASK]  = "enum_mask",
        [BCMCLI_PARM_STRING]     = "string",
        [BCMCLI_PARM_IP]         = "IP",
        [BCMCLI_PARM_IPV6]       = "IPv6",
        [BCMCLI_PARM_MAC]        = "MAC",
        [BCMCLI_PARM_BUFFER]     = "buffer",
        [BCMCLI_PARM_STRUCT]     = "struct",
        [BCMCLI_PARM_USERDEF]    = "userdef",
    };
    static const char *undefined = "undefined";
    static const char *selector = "selector";
    if (type > BCMCLI_PARM_USERDEF || !type_name[type])
        return undefined;
    if (type == BCMCLI_PARM_ENUM && (parm->flags & BCMCLI_PARM_FLAG_SELECTOR))
        return selector;
    return type_name[type];
}

/* Assign default callbacks */
static void _bcmcli_assign_callbacks(bcmcli_cmd_parm *parm)
{
    if (parm->type == BCMCLI_PARM_ENUM)
    {
        parm->scan_cb = _bcmcli_enum_scan_cb;
        parm->print_cb = _bcmcli_enum_print_cb;
    }
    else if (parm->type == BCMCLI_PARM_ENUM_MASK)
    {
        parm->scan_cb = _bcmcli_enum_mask_scan_cb;
        parm->print_cb = _bcmcli_enum_mask_print_cb;
    }
    else if (parm->type == BCMCLI_PARM_BUFFER)
    {
        if (!parm->scan_cb)
            parm->scan_cb = _bcmcli_buffer_scan_cb;
        if (!parm->print_cb)
            parm->print_cb = _bcmcli_buffer_print_cb;
    }
    else if (parm->type == BCMCLI_PARM_STRUCT)
    {
        parm->scan_cb = _bcmcli_struct_scan_cb;
        parm->print_cb = _bcmcli_struct_print_cb;
    }
    else
    {
        if (!parm->scan_cb)
            parm->scan_cb = _bcmcli_dft_scan_cb;
        if (!parm->print_cb)
            parm->print_cb = _bcmcli_dft_print_cb;
    }
}


/* Convert hex-string to binary data.
 * Returns: converted length >=0 or error < 0
 */
static int _bcmcli_strhex(const char *src, uint8_t *dst, uint16_t dst_len)
{
    uint16_t src_len = (uint16_t)strlen( src );
    uint16_t i = src_len, j, shift = 0;

    if ( !dst || !dst_len || (src_len > 2*dst_len) || (src_len%2) )
    {
        return BCM_ERR_PARM;
    }

    /* Calculate hex buffer length and fill it up from right-to-left
     * in order to start the process from LS nibble
     */
    dst_len = src_len / 2;
    memset(dst, 0, dst_len);
    j = dst_len-1;
    do
    {
        int c = src[--i];

        if ( (c>='0') && (c<='9') )
        {
            c = c - '0';
        }
        else if ( (c>='a') && (c<='f') )
        {
            c = 0xA + c - 'a';
        }
        else if ( (c>='A') && (c<='F') )
        {
            c = 0xA + c - 'A';
        }
        else
        {
            return BCM_ERR_PARM;
        }

        dst[j] |= (uint8_t)(c<<shift); /* shift can have 1 of 2 values: 0 and 4 */

        j     -= shift>>2;              /* move to the next byte if we've just filled the ms nibble */
        shift ^= 4;                     /* alternate nibbles */

    } while ( i );

    return dst_len;
}

/* Default function for string->value conversion.
 * Returns 0 if OK
 */
static bcmos_errno _bcmcli_dft_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val)
{
    char *p_end = NULL;
    int n;

    if (parm->type == BCMCLI_PARM_UDECIMAL ||
        parm->type == BCMCLI_PARM_UDECIMAL64 ||
        parm->type == BCMCLI_PARM_UNUMBER ||
        parm->type == BCMCLI_PARM_UNUMBER64)
    {
        /* strtoul returns OK even when parsing a negative number */
        if (string_val[0] == '-')
        {
            return BCM_ERR_PARM;
        }
    }

    switch(parm->type)
    {
        case BCMCLI_PARM_DECIMAL:
            value->number = strtol(string_val, &p_end, 10);
            break;
        case BCMCLI_PARM_UDECIMAL:
            value->unumber = strtoul(string_val, &p_end, 10);
            break;
        case BCMCLI_PARM_DECIMAL64:
            value->number64 = strtoll(string_val, &p_end, 10);
            break;
        case BCMCLI_PARM_UDECIMAL64:
            value->unumber64 = strtoull(string_val, &p_end, 10);
            break;
        case BCMCLI_PARM_HEX:
            value->unumber = strtoul(string_val, &p_end, 16);
            break;
        case BCMCLI_PARM_HEX64:
            value->unumber64 = strtoull(string_val, &p_end, 16);
            break;
        case BCMCLI_PARM_NUMBER:
            value->number = strtol(string_val, &p_end, 0);
            break;
        case BCMCLI_PARM_UNUMBER:
            value->unumber = strtoul(string_val, &p_end, 0);
            break;
        case BCMCLI_PARM_NUMBER64:
            value->number64 = strtoll(string_val, &p_end, 0);
            break;
        case BCMCLI_PARM_UNUMBER64:
            value->unumber64 = strtoull(string_val, &p_end, 0);
            break;
        case BCMCLI_PARM_FLOAT:
        case BCMCLI_PARM_DOUBLE:
            value->d = strtod(string_val, &p_end);
            break;
        case BCMCLI_PARM_MAC:
        {
            unsigned m0, m1, m2, m3, m4, m5;
            n = sscanf(string_val, "%02x:%02x:%02x:%02x:%02x:%02x",
                &m0, &m1, &m2, &m3, &m4, &m5);
            if (n != 6)
            {
                n = sscanf(string_val, "%02x%02x%02x%02x%02x%02x",
                    &m0, &m1, &m2, &m3, &m4, &m5);
            }
            if (n != 6)
                return BCM_ERR_PARM;
            if (m0 > 255 || m1 > 255 || m2 > 255 || m3 > 255 || m4 > 255 || m5 > 255)
                return BCM_ERR_PARM;
            value->mac.u8[0] = m0;
            value->mac.u8[1] = m1;
            value->mac.u8[2] = m2;
            value->mac.u8[3] = m3;
            value->mac.u8[4] = m4;
            value->mac.u8[5] = m5;
            break;
        }
        case BCMCLI_PARM_IP:
        {
            int n1, n2, n3, n4;
            n = sscanf(string_val, "%d.%d.%d.%d", &n1, &n2, &n3, &n4);
            if (n != 4)
                return BCM_ERR_PARM;
            if ((unsigned)n1 > 255 || (unsigned)n2 > 255 || (unsigned)n3 > 255 || (unsigned)n4 > 255)
                return BCM_ERR_PARM;
            value->unumber = (n1 << 24) | (n2 << 16) | (n3 << 8) | n4;
            break;
        }
        case BCMCLI_PARM_IPV6:
        {
            unsigned a[16];
            n = sscanf(string_val, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
                &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7],
                &a[8], &a[9], &a[10], &a[11], &a[12], &a[13], &a[14], &a[15]);
            if (n != 16)
                return BCM_ERR_PARM;
            for (n = 0; n < 16; n++)
            {
                if (a[n] > 255)
                    return BCM_ERR_PARM;
                value->ipv6.u8[n] = a[n];
            }
            break;
        }
        default:
            return BCM_ERR_PARM;
    }
    if (p_end && *p_end)
        return BCM_ERR_PARM;
    return BCM_ERR_OK;
}

static void _bcmcli_dft_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value)
{
    switch(parm->type)
    {
        case BCMCLI_PARM_DECIMAL:
            bcmcli_print(session, "%ld", value->number);
            break;
        case BCMCLI_PARM_UDECIMAL:
            bcmcli_print(session, "%lu", value->unumber);
            break;
        case BCMCLI_PARM_DECIMAL64:
            bcmcli_print(session, "%lld", value->number64);
            break;
        case BCMCLI_PARM_UDECIMAL64:
            bcmcli_print(session, "%llu", value->unumber64);
            break;
        case BCMCLI_PARM_HEX:
            bcmcli_print(session, "0x%lx", value->unumber);
            break;
        case BCMCLI_PARM_HEX64:
            bcmcli_print(session, "0x%llx", value->unumber64);
            break;
        case BCMCLI_PARM_NUMBER:
            bcmcli_print(session, "%ld", value->number);
            break;
        case BCMCLI_PARM_NUMBER64:
            bcmcli_print(session, "%lld", value->number64);
            break;
        case BCMCLI_PARM_UNUMBER:
            bcmcli_print(session, "%lu", value->unumber);
            break;
        case BCMCLI_PARM_UNUMBER64:
            bcmcli_print(session, "%llu", value->unumber64);
            break;
        case BCMCLI_PARM_FLOAT:
        case BCMCLI_PARM_DOUBLE:
            bcmcli_print(session, "%f", value->d);
            break;
        case BCMCLI_PARM_STRING:
            bcmcli_print(session, "%s", value->string);
            break;
        case BCMCLI_PARM_MAC:
            bcmcli_print(session, "%02x:%02x:%02x:%02x:%02x:%02x",
                value->mac.u8[0], value->mac.u8[1], value->mac.u8[2],
                value->mac.u8[3], value->mac.u8[4], value->mac.u8[5]);
            break;
        case BCMCLI_PARM_IP:
            bcmcli_print(session, "%d.%d.%d.%d",
                (int)((value->unumber >> 24) & 0xff), (int)((value->unumber >> 16) & 0xff),
                (int)((value->unumber >> 8) & 0xff), (int)(value->unumber & 0xff));
            break;
        case BCMCLI_PARM_IPV6:
            bcmcli_print(session, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
                value->ipv6.u8[0], value->ipv6.u8[1], value->ipv6.u8[2], value->ipv6.u8[3],
                value->ipv6.u8[4], value->ipv6.u8[5], value->ipv6.u8[6], value->ipv6.u8[7],
                value->ipv6.u8[8], value->ipv6.u8[9], value->ipv6.u8[10], value->ipv6.u8[11],
                value->ipv6.u8[12], value->ipv6.u8[13], value->ipv6.u8[14], value->ipv6.u8[15]);
            break;

        default:
            bcmcli_print(session, "*unknown*");
    }
}

static bcmos_errno _bcmcli_enum_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val)
{
    bcmcli_enum_val *values=parm->enum_table;
    while (values->name)
    {
        if (!_bcmcli_stricmp(values->name, string_val, -1))
        {
            value->enum_val = values->val;
            return BCM_ERR_OK;
        }
        ++values;
    }
    return BCM_ERR_PARM;
}

static void _bcmcli_enum_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value)
{
    bcmcli_enum_val *values=parm->enum_table;
    while (values->name)
    {
        if (values->val == value->enum_val)
            break;
        ++values;
    }
    if (values->name)
        bcmcli_print(session, "%s", values->name);
    else
        bcmcli_print(session, "*invalid*");
}

static bcmos_errno _bcmcli_enum_mask_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val)
{
    bcmcli_parm_value val1;
    char *del;
    bcmos_errno err;

    value->number = 0;

    /* string_val is a combination of enum values separated by BCMCLI_ENUM_MASK_DEL_STR */
    del = strchr(string_val, BCMCLI_ENUM_MASK_DEL_CHAR);
    while (del)
    {
        char single_val[64];
        if (del - string_val >= sizeof(single_val))
            return BCM_ERR_OVERFLOW;
        memcpy(single_val, string_val, del - string_val);
        single_val[del - string_val] = 0;
        err = _bcmcli_enum_scan_cb(session, parm, &val1, single_val);
        if (err)
            return err;
        value->enum_val |= val1.enum_val;
        string_val = del+1;
        del = strchr(string_val, BCMCLI_ENUM_MASK_DEL_CHAR);
    }
    err = _bcmcli_enum_scan_cb(session, parm, &val1, string_val);
    if (err)
        return err;
    value->number |= val1.enum_val;
    return BCM_ERR_OK;
}

static void _bcmcli_enum_mask_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value)
{
    bcmcli_enum_val *values=parm->enum_table;
    const char *none = NULL;
    int nprinted = 0;
    while (values->name)
    {
        if (values->val == 0)
        {
            none = values->name;
        }
        if ((values->val & value->enum_val) != 0)
        {
            if (values != parm->enum_table)
                bcmcli_print(session, BCMCLI_ENUM_MASK_DEL_STR);
            bcmcli_print(session, "%s", values->name);
            ++nprinted;
        }
        ++values;
    }
    if (! nprinted)
        bcmcli_print(session, "%s", NULL != none ? none : "0");
}

static bcmos_errno _bcmcli_buffer_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val)
{
    int n;

    if (!value->buffer.start)
        return BCM_ERR_PARM;
    /* coverity[misra_violation] - cross-assignment under union is OK - they're both in the same union member */
    value->buffer.curr = value->buffer.start;
    if (strcmp(string_val, BCMCLI_NO_VALUE_STR) == 0)
    {
        return BCM_ERR_OK;
    }
    n = _bcmcli_strhex(string_val, value->buffer.start, value->buffer.len);
    if (n < 0)
        return BCM_ERR_PARSE;
    if (!bcmolt_buf_skip(&value->buffer, n))
        return BCM_ERR_PARM;
    return BCM_ERR_OK;
}

static void _bcmcli_buffer_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value)
{
    if (value->buffer.len == 0)
    {
        bcmcli_print(session, BCMCLI_NO_VALUE_STR);
    }
    else
    {
        uint32_t length = bcmolt_buf_get_used(&value->buffer);
        int i;
        for (i = 0; i < length; i++)
        {
            bcmcli_print(session, "%02x", value->buffer.start[i]);
        }
    }
}

/* Handle value containing a list of space-delimited struct field values surrounded by braces */
static bcmos_errno _bcmcli_struct_scan_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val)
{
    bcmcli_session_extras *mon_session = _bcmcli_session_data(session);
    bcmcli_token_type struct_token_type = mon_session->cur_token_type;
    const char *p_val = string_val;
    int p_val_len = strlen(p_val);
    bcmcli_name_value *pairs = NULL;
    int npairs = 0;
    bcmcli_parm_array *pa;
    bcmos_errno rc;

    /* make sure the value is surrounded by braces (the end brace is optional in case of tab completion) */
    if (p_val_len == 0 || p_val[0] != BCMCLI_STRUCT_START_CHAR)
        return BCM_ERR_PARM;

    /* extract the space-delimited set of field_name=field_value pairs inside the braces */
    p_val_len -= (p_val[p_val_len - 1] == BCMCLI_STRUCT_END_CHAR) ? 2 : 1;
    p_val++;

    rc = _bcmcli_split(mon_session, &p_val, p_val_len, &pairs, &npairs);
    if (rc != BCM_ERR_OK)
        return rc;

    /* Create parameters array */
    pa = _bcmcli_parm_array_create(mon_session, parm->name, value, value->fields, pairs, npairs);
    if (pa == NULL)
        return BCM_ERR_NOMEM;

    rc = _bcmcli_populate_parms(mon_session, parm->name, pa);

    /* Pop parameter arrays stack if parsing was succesful and struct descriptor properly terminated */
    if (rc == BCM_ERR_OK && (struct_token_type & BCMCLI_TOKEN_UNTERMINATED_STRUCT_VALUE) == 0)
        _bcmcli_parm_array_pop(mon_session);

    return rc;
}

static void _bcmcli_struct_print_cb(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value)
{
    const bcmcli_cmd_parm *field;
    bcmos_bool first = BCMOS_TRUE;

    bcmcli_print(session, "%c", BCMCLI_STRUCT_START_CHAR);
    for (field = value->fields; field && field->name; ++field)
    {
        if (!bcmcli_parm_is_set(session, field))
            continue;
        if (!first)
            bcmcli_print(session, " ");
        bcmcli_parm_print(session, field);
        first = BCMOS_FALSE;
    }
    bcmcli_print(session, "%c", BCMCLI_STRUCT_END_CHAR);
}

static const char *_bcmcli_qualified_name(bcmcli_entry *token, char *buffer, int size )
{
    bcmcli_entry *parent = token->parent;
    char qual_name[BCMCLI_MAX_QUAL_NAME_LENGTH];
    *buffer=0;
    while (parent)
    {
        bcmolt_strncpy(qual_name, parent->name, sizeof(qual_name));
        if (parent->parent)
            bcmolt_strncat(qual_name, "/", sizeof(qual_name));
        bcmolt_strncat(qual_name, buffer, sizeof(qual_name));
        bcmolt_strncpy(buffer, qual_name, size);
        parent = parent->parent;
    }
    size -= strlen(buffer);
    bcmolt_strncat(buffer, token->name, size);
    return buffer;
}


/*
 * Command parameter array stack manipulation
 */

/* Create command parameters array the template specified at
 * CLI command registration time
 */
static bcmcli_parm_array *_bcmcli_parm_array_create(bcmcli_session_extras *mon_session,
    const char *in_parm, bcmcli_parm_value *in_value, const bcmcli_cmd_parm parms[],
    bcmcli_name_value pairs[], int npairs)
{
    bcmcli_parm_array *pa;

    pa = bcmcli_session_stack_calloc(mon_session->session, sizeof(bcmcli_parm_array));
    if (!pa)
        return NULL;

    pa->in_value = in_value;
    pa->in_parm = in_parm;
    if (_bcmcli_parm_array_extend(mon_session, pa, 0, parms) != BCM_ERR_OK)
        return NULL;

    pa->name_value_pairs = pairs;
    pa->num_pairs = npairs;

    _bcmcli_parm_array_push(mon_session, pa);

    return pa;
}

/* Extend command parameters array.
 * This function is used when processing command selector.
 * Additional parameters based on the selector value are inserted into the existing
 * array in position "pos"
 */
static bcmos_errno _bcmcli_parm_array_extend(bcmcli_session_extras *mon_session,
    bcmcli_parm_array *pa, uint32_t pos, const bcmcli_cmd_parm extra_parms[])
{
    uint32_t num_parms;
    bcmcli_cmd_parm *parms;
    uint32_t num_extra_parms;
    int i;

    /* Calculate number of parameters */
    if (!extra_parms)
        return BCM_ERR_OK;
    /* Count extra parameters */
    for (i = 0; extra_parms[i].name != NULL; i++)
        ;
    num_extra_parms = i;
    if (!num_extra_parms)
        return BCM_ERR_OK;

    /* Allocate new block for extended array. The old block will be released eventually
     * when session memory pool is restored
     */
    num_parms = pa->num_parms + num_extra_parms;
    parms = bcmcli_session_stack_calloc(mon_session->session, (num_parms + 1) * sizeof(bcmcli_cmd_parm));
    if (!parms)
        return BCM_ERR_NOMEM;

    /* Copy parameters before the insertion point */
    if (pos)
    {
        memcpy(parms, pa->cmd_parms, pos * sizeof(bcmcli_cmd_parm));
    }

    /* Copy additional parameters */
    for (i = 0; i < num_extra_parms; i++)
    {
        bcmcli_parm_value *values;
        bcmcli_cmd_parm *p = &parms[pos+i];

        *p = extra_parms[i];
        _bcmcli_assign_callbacks(p);

        /* Copy "values" array for arrays */
        if (p->max_array_size)
        {
            if (!p->values)
            {
                bcmcli_print(mon_session->session, "MON %s> \"values\" is not set in array parameter %s\n",
                    mon_session->curcmd->name, p->name);
                return BCM_ERR_INTERNAL;
            }
            values = bcmcli_session_stack_calloc(mon_session->session, p->max_array_size * sizeof(bcmcli_parm_value));
            if (!values)
                return BCM_ERR_NOMEM;
            memcpy(values, p->values, p->max_array_size * sizeof(bcmcli_parm_value));
            p->values = values;
        }
    }

    /* Copy parameters after insertion point */
    if (pos < pa->num_parms)
    {
        memcpy(parms + pos + num_extra_parms, pa->cmd_parms + pos,
            (pa->num_parms - pos) * sizeof(bcmcli_cmd_parm));
    }

    /* Assign new block */
    pa->cmd_parms = parms;
    pa->num_parms += num_extra_parms;
    if (pa->in_value)
        pa->in_value->fields = parms;

    return BCM_ERR_OK;
}

static void _bcmcli_parm_array_push(bcmcli_session_extras *mon_session, bcmcli_parm_array *pa)
{
    STAILQ_INSERT_HEAD(&mon_session->cmd_parms_stack, pa, next);
}

static bcmcli_parm_array *_bcmcli_parm_array_pop(bcmcli_session_extras *mon_session)
{
    STAILQ_REMOVE_HEAD(&mon_session->cmd_parms_stack, next);
    return STAILQ_FIRST(&mon_session->cmd_parms_stack);
}

/* Top-most array. Top-level CLI parameters */
static bcmcli_parm_array *_bcmcli_parm_array_top(bcmcli_session_extras *mon_session)
{
    return STAILQ_LAST(&mon_session->cmd_parms_stack, bcmcli_parm_array, next);
}

/* Current (inner-most) CLI parameters */
static bcmcli_parm_array *_bcmcli_parm_array_cur(bcmcli_session_extras *mon_session)
{
    return STAILQ_FIRST(&mon_session->cmd_parms_stack);
}

/* Return TRUE if all parameters in parm array are set */
static bcmos_bool _bcmcli_parm_array_is_all_set(bcmcli_session_extras *mon_session, bcmcli_parm_array *pa)
{
    bcmos_bool all_set = BCMOS_TRUE;
    int i;
    if (!pa->cmd_parms)
        return BCMOS_TRUE;
    for (i = 0; i < pa->num_parms && all_set; i++)
        all_set = bcmcli_parm_is_set(mon_session->session, &pa->cmd_parms[i]);
    return all_set;
}

/*
 * Exports
 */
EXPORT_SYMBOL(bcmcli_dir_add);
EXPORT_SYMBOL(bcmcli_dir_find);
EXPORT_SYMBOL(bcmcli_token_name);
EXPORT_SYMBOL(bcmcli_cmd_add);
EXPORT_SYMBOL(bcmcli_session_open);
EXPORT_SYMBOL(bcmcli_session_close);
EXPORT_SYMBOL(bcmcli_parse);
EXPORT_SYMBOL(bcmcli_stop);
EXPORT_SYMBOL(bcmcli_is_stopped);
EXPORT_SYMBOL(bcmcli_dir_get);
EXPORT_SYMBOL(bcmcli_dir_set);
EXPORT_SYMBOL(bcmcli_parm_number);
EXPORT_SYMBOL(bcmcli_parm_is_set);
EXPORT_SYMBOL(bcmcli_enum_parm_stringval);
EXPORT_SYMBOL(bcmcli_token_destroy);
EXPORT_SYMBOL(bcmcli_enum_bool_table);
