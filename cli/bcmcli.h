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
 * bcmcli.h
 *
 * CLI engine
 *
 *******************************************************************/

#ifndef BCMCLI_H

#define BCMCLI_H

#include <bcmos_system.h>
#include <bcmcli_session.h>
#include <bcmolt_buf.h>
#ifndef BCM_OPEN_SOURCE
#include <bcmolt_type_metadata.h>
#else
typedef long bcmolt_enum_number;
#define BCMOLT_PARM_NO_VALUE_STR  "_"
#define BCMOLT_ARRAY_EMPTY_STR    "-"
#define BCMOLT_MAX_METADATA_NAME_LENGTH 80
#define BCMOLT_ENUM_MASK_DEL_STR  "+"
#endif

/** \defgroup bcm_cli Broadcom CLI Engine
 * Broadcom CLI engine is used for all configuration and status monitoring.\n
 * It doesn't have built-in scripting capabilities (logical expressions, loops),
 * but can be used in combination with any available scripting language.\n
 * Broadcom CLI supports the following features:\n
 * - parameter number and type validation (simplifies command handlers development)
 * - parameter value range checking
 * - mandatory and optional parameters
 * - positional and named parameters
 * - parameters with default values
 * - enum parameters can have arbitrary values
 * - automatic command help generation
 * - automatic or user-defined command shortcuts
 * - command handlers return completion status to enable scripting
 * - multiple sessions
 * - session access rights
 * - extendible. Supports user-defined parameter types
 * - relatively low stack usage
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define BCMCLI_MAX_SEARCH_SUBSTR_LENGTH BCMOLT_MAX_METADATA_NAME_LENGTH

#define BCMCLI_ARRAY_EMPTY        BCMOLT_ARRAY_EMPTY_STR
#define BCMCLI_PARM_NO_VALUE      BCMOLT_PARM_NO_VALUE_STR
#define BCMCLI_ENUM_MASK_DEL_STR  BCMOLT_ENUM_MASK_DEL_STR

/** Monitor entry handle
 */
typedef struct bcmcli_entry bcmcli_entry;

/* if BCMCLI_PARM_USERIO flag is set:
   low_val: t_userscanf_f function
   high_val: t_userprintf_f function
*/

/** Function parameter structure */
typedef struct bcmcli_cmd_parm bcmcli_cmd_parm;

/** Parameter type */
typedef enum
{
    BCMCLI_PARM_NONE,
    BCMCLI_PARM_DECIMAL,         /**< Decimal number */
    BCMCLI_PARM_DECIMAL64,       /**< Signed 64-bit decimal */
    BCMCLI_PARM_UDECIMAL,        /**< Unsigned decimal number */
    BCMCLI_PARM_UDECIMAL64,      /**< Unsigned 64-bit decimal number */
    BCMCLI_PARM_HEX,             /**< Hexadecimal number */
    BCMCLI_PARM_HEX64,           /**< 64-bit hexadecimal number */
    BCMCLI_PARM_NUMBER,          /**< Decimal number or hex number prefixed by 0x */
    BCMCLI_PARM_NUMBER64,        /**< 64bit decimal number or hex number prefixed by 0x */
    BCMCLI_PARM_UNUMBER,         /**< Unsigned decimal number or hex number prefixed by 0x */
    BCMCLI_PARM_UNUMBER64,       /**< Unsigned 64bit decimal number or hex number prefixed by 0x */
    BCMCLI_PARM_FLOAT,           /**< IEEE 32-bit floating-point number */
    BCMCLI_PARM_DOUBLE,          /**< IEEE 64-bit floating point number */
    BCMCLI_PARM_STRING,          /**< String */
    BCMCLI_PARM_ENUM,            /**< Enumeration */
    BCMCLI_PARM_ENUM_MASK,       /**< Bitmask created from enumeration values */
    BCMCLI_PARM_IP,              /**< IP address n.n.n.n */
    BCMCLI_PARM_IPV6,            /**< IPv6 address */
    BCMCLI_PARM_MAC,             /**< MAC address xx:xx:xx:xx:xx:xx */
    BCMCLI_PARM_BUFFER,          /**< Byte array */
    BCMCLI_PARM_STRUCT,          /**< Structure */

    BCMCLI_PARM_USERDEF          /**< User-defined parameter. User must provide scan_cb */
} bcmcli_parm_type;

/** Enum attribute value.
 *
 *  Enum values is an array of bcmcli_enum_val terminated by element with name==NULL.
 *  This is an extension of the generic enum value 'bcmolt_enum_val' with additional parameters.
 */
typedef struct bcmcli_enum_val
{
    const char *name;           /**< Enum symbolic name */
    bcmolt_enum_number val;     /**< Enum internal value */
    bcmcli_cmd_parm *parms;     /**< Extension parameter table for enum-selector */
} bcmcli_enum_val;
#define BCMCLI_ENUM_LAST { NULL, 0, NULL }  /**< Last entry in enum table */

/** Boolean values (true/false, yes/no, on/off)
 *
 */
extern bcmcli_enum_val bcmcli_enum_bool_table[];

/* Monitor data types */
typedef long bcmcli_number;      /**< Type underlying BCMCLI_PARM_NUMBER, BCMCLI_PARM_DECIMAL */
typedef long bcmcli_unumber;     /**< Type underlying BCMCLI_PARM_HEX, BCMCLI_PARM_UDECIMAL */
typedef long bcmcli_number64;    /**< Type underlying BCMCLI_PARM_NUMBER64, BCMCLI_PARM_DECIMAL64 */
typedef long bcmcli_unumber64;   /**< Type underlying BCMCLI_PARM_HEX64, BCMCLI_PARM_UDECIMAL64 */

/** Parameter value */
typedef struct bcmcli_parm_value
{
    union
    {
        long number;                    /**< Signed number */
        unsigned long unumber;          /**< Unsigned number */
        long long number64;             /**< Signed 64-bit number */
        unsigned long long unumber64;   /**< Unsigned 64-bit number */
        const char *string;             /**< 0-terminated string */
        double d;                       /**< Double-precision floating point number */
        bcmos_mac_address mac;          /**< MAC address */
        bcmos_ipv6_address ipv6;        /**< IPv6 address */
        bcmolt_buf buffer;              /**< Buffer: used for BCMCLI_PARM_BUFFER */
        bcmolt_enum_number enum_val;    /**< Enum value (number) */
        bcmcli_cmd_parm *fields;        /**< Structure fields */
    };
    bcmos_bool is_set;
}  bcmcli_parm_value;

/** User-defined scan function.
 * The function is used for parsing user-defined parameter types
 * Returns: 0-ok, <=error
 *
 */
typedef bcmos_errno (*bcmcli_scan_cb)(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    bcmcli_parm_value *value, const char *string_val);

/** User-defined print value function.
 * The function is used for printing values of user-defined parameter types
 *
 */
typedef void (*bcmcli_print_cb)(bcmcli_session *session, const bcmcli_cmd_parm *parm,
    const bcmcli_parm_value *value);


/** Function parameter structure */
struct bcmcli_cmd_parm
{
   const char *name;            /**< Parameter name. Shouldn't be allocated on stack! */
   const char *description;     /**< Parameter description. Shouldn't be allocated on stack! */
   bcmcli_parm_type type;       /**< Parameter type */
   uint8_t flags;               /**< Combination of BCMCLI_PARM_xx flags */
#define BCMCLI_PARM_FLAG_NONE       0x00 /**< For use instead of magic number 0 when no flags apply */
#define BCMCLI_PARM_FLAG_OPTIONAL   0x01 /**< Parameter is optional */
#define BCMCLI_PARM_FLAG_DEFVAL     0x02 /**< Default value is set */
#define BCMCLI_PARM_FLAG_RANGE      0x04 /**< Range is set */
#define BCMCLI_PARM_FLAG_EOL        0x08 /**< String from the current parser position till EOL */
#define BCMCLI_PARM_FLAG_SELECTOR   0x10 /**< Parameter selects other parameters */
#define BCMCLI_PARM_FLAG_OMIT_VAL   0x20 /**< Allow only the name of the parameter to be specified (without =value) */
#define BCMCLI_PARM_FLAG_ASSIGNED   0x40 /**< Internal flag: parameter is assigned */

   bcmcli_number low_val;       /**< Low val for range checking */
   bcmcli_number hi_val;        /**< Hi val for range checking */
   bcmcli_parm_value value;     /**< Value */
   bcmcli_enum_val *enum_table; /**< Table containing { enum_name, enum_value } pairs */
   bcmcli_scan_cb scan_cb;      /**< User-defined scan function for BCMCLI_PARM_USERDEF parameter type */
   bcmcli_print_cb print_cb;    /**< User-defined print function for BCMCLI_PARM_USERDEF parameter type */
   uint32_t max_array_size;     /**< Max array size for array-parameter */
   uint32_t array_size;         /**< Actual array size for array-parameter */
   bcmcli_parm_value *values;   /**< Array values */
   void *user_data;             /**< User data - passed transparently to command handler */
};

/** Command parameter list terminator */
#define BCMCLI_PARM_LIST_TERMINATOR  { .name=NULL, .description=NULL, .type=BCMCLI_PARM_NONE }

/** Helper macro: make simple parameter
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _type     Parameter type
 * \param[in] _flags    Parameter flags
 */
#define BCMCLI_MAKE_PARM(_name, _descr, _type, _flags) \
    { .name=(_name), .description=(_descr), .type=(_type), .flags=(_flags) }

/** Helper macro: make simple parameter
 * \param[in] _name       Parameter name
 * \param[in] _descr      Parameter description
 * \param[in] _type       Parameter type
 * \param[in] _flags      Parameter flags
 * \param[in] _size       Max array size
 * \param[in] _values     Array values buffer
 */
#define BCMCLI_MAKE_PARM_ARRAY(_name, _descr, _type, _flags, _size, _values) \
    { .name=(_name), .description=(_descr), .type=(_type), .flags=(_flags),\
        .max_array_size=(_size), .values=(_values) }

/** Helper macro: make simple parameter for arrays of enums
 * \param[in] _name       Parameter name
 * \param[in] _descr      Parameter description
 * \param[in] _type       Parameter type
 * \param[in] _flags      Parameter flags
 * \param[in] _size       Max array size
 * \param[in] _values     Array values buffer
 * \param[in] _enum_table An array of enums that may be in the array
 */
#define BCMCLI_MAKE_PARM_ENUM_ARRAY(_name, _descr, _type, _flags, _size, _values, _enum_table) \
    { .name=(_name), .description=(_descr), .type=(_type), .flags=(_flags),\
        .max_array_size=(_size), .values=(_values), .enum_table=(_enum_table) }

/** Helper macro: make range parameter
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _type     Parameter type
 * \param[in] _flags    Parameter flags
 * \param[in] _min      Min value
 * \param[in] _max      Max value
 */
#define BCMCLI_MAKE_PARM_RANGE(_name, _descr, _type, _flags, _min, _max) \
    { .name=(_name), .description=(_descr), .type=(_type), .flags=(_flags) | BCMCLI_PARM_FLAG_RANGE, \
        .low_val=(_min), .hi_val=(_max) }

/** Helper macro: make range parameter for arrays with range
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _type     Parameter type
 * \param[in] _flags    Parameter flags
 * \param[in] _size     Max array size
 * \param[in] _values   Array values buffer
 * \param[in] _min      Min value
 * \param[in] _max      Max value
 */
#define BCMCLI_MAKE_PARM_ARRAY_RANGE(_name, _descr, _type, _flags, _size, _values, _min, _max) \
    { .name=(_name), .description=(_descr), .type=(_type), .flags=(_flags) | BCMCLI_PARM_FLAG_RANGE,\
         .max_array_size=(_size), .values=(_values), .low_val=(_min), .hi_val=(_max) }

/** Helper macro: make parameter with default value
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _type     Parameter type
 * \param[in] _flags    Parameter flags
 * \param[in] _dft      Default value
 */
#define BCMCLI_MAKE_PARM_DEFVAL(_name, _descr, _type, _flags, _dft) \
    { .name=(_name), .description=(_descr), .type=(_type), .flags=(_flags) | BCMCLI_PARM_FLAG_DEFVAL, \
        .value = {{_dft}} }

/** Helper macro: make range parameter with default value
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _type     Parameter type
 * \param[in] _flags    Parameter flags
 * \param[in] _min      Min value
 * \param[in] _max      Max value
 * \param[in] _dft      Default value
 */
#define BCMCLI_MAKE_PARM_RANGE_DEFVAL(_name, _descr, _type, _flags, _min, _max, _dft) \
    { .name=(_name), .description=(_descr), .type=(_type), \
        .flags=(_flags) | BCMCLI_PARM_FLAG_RANGE | BCMCLI_PARM_FLAG_DEFVAL, \
        .low_val=(_min), .hi_val=(_max), .value = {{_dft}} }

/** Helper macro: make enum parameter
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _values   Enum values table
 * \param[in] _flags    Parameter flags
 */
#define BCMCLI_MAKE_PARM_ENUM(_name, _descr, _values, _flags) \
    { .name=(_name), .description=(_descr), .type=BCMCLI_PARM_ENUM, .flags=(_flags), .enum_table=(_values)}

/** Helper macro: make enum parameter with default value
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _values   Enum values table
 * \param[in] _flags    Parameter flags
 * \param[in] _dft      Default value
 */
#define BCMCLI_MAKE_PARM_ENUM_DEFVAL(_name, _descr, _values, _flags, _dft) \
    { .name=(_name), .description=(_descr), .type=BCMCLI_PARM_ENUM, .flags=(_flags) | BCMCLI_PARM_FLAG_DEFVAL,\
        .low_val=0, .hi_val=0, .value={{.string=_dft}}, .enum_table=(_values) }

/** Helper macro: make enum mask parameter
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _values   Enum values table
 * \param[in] _flags    Parameter flags
 */
#define BCMCLI_MAKE_PARM_ENUM_MASK(_name, _descr, _values, _flags) \
    { .name=(_name), .description=(_descr), .type=BCMCLI_PARM_ENUM_MASK, .flags=(_flags), \
        .low_val=0, .hi_val=0, .value={}, .enum_table=(_values) }

/** Helper macro: make enum_mask parameter with default value
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _values   Enum values table
 * \param[in] _flags    Parameter flags
 * \param[in] _dft      Default value
 */
#define BCMCLI_MAKE_PARM_ENUM_MASK_DEFVAL(_name, _descr, _values, _flags, _dft) \
    { .name=(_name), .description=(_descr), .type=BCMCLI_PARM_ENUM_MASK, .flags=(_flags) | BCMCLI_PARM_FLAG_DEFVAL,\
        .low_val=0, .hi_val=0, .value={{.string=_dft}}, .enum_table=(_values) }

/** Helper macro: make enum-selector parameter
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _values   Selector values table
 * \param[in] _flags    Parameter flags
 */
#define BCMCLI_MAKE_PARM_SELECTOR(_name, _descr, _values, _flags) \
    { .name=(_name), .description=(_descr), .type=BCMCLI_PARM_ENUM, .flags=(_flags) | BCMCLI_PARM_FLAG_SELECTOR,\
        .low_val=0, .hi_val=0, .value={}, .enum_table=(_values) }

/** Helper macro: make buffer parameter
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _flags    Parameter flags
 * \param[in] _buf      Memory buffer associated with the parameter
 * \param[in] _size     Buffer size
 */
#define BCMCLI_MAKE_PARM_BUFFER(_name, _descr, _flags, _buf, _size) \
    { .name=(_name), .description=(_descr), .type=BCMCLI_PARM_BUFFER, \
        .flags=(_flags), .value = {{.buffer = {.start = _buf, .curr = _buf, .len = _size}}} }

/** Helper macro: make struct parameter
 * \param[in] _name     Parameter name
 * \param[in] _descr    Parameter description
 * \param[in] _flags    Parameter flags
 * \param[in] _fields   Structure fields
 */
#define BCMCLI_MAKE_PARM_STRUCT(_name, _descr, _flags, _fields) \
    { .name=(_name), .description=(_descr), .type=BCMCLI_PARM_STRUCT, \
        .flags=(_flags), .value.fields = _fields }

/** Register command without parameters helper */
#define BCMCLI_MAKE_CMD_NOPARM(dir, cmd, help, cb) \
{\
    bcmos_errno bcmcli_cmd_add_err = bcmcli_cmd_add(dir, cmd, cb, help, BCMCLI_ACCESS_ADMIN, NULL, NULL);\
    BUG_ON(BCM_ERR_OK != bcmcli_cmd_add_err);\
}

/** Register command helper */
#define BCMCLI_MAKE_CMD(dir, cmd, help, cb, parms...)                           \
{                                                                               \
    static bcmcli_cmd_parm cmd_parms[]={                                        \
        parms,                                                                  \
        BCMCLI_PARM_LIST_TERMINATOR                                             \
    };                                                                          \
    bcmos_errno bcmcli_cmd_add_err = bcmcli_cmd_add(dir, cmd, cb, help, BCMCLI_ACCESS_ADMIN, NULL, cmd_parms);   \
    BUG_ON(BCM_ERR_OK != bcmcli_cmd_add_err);\
}

/** Optional custom directory handlers */
typedef void (*bcmcli_dir_enter_leave_cb)(bcmcli_session *session, bcmcli_entry *dir, int is_enter);

/** Optional command or directory help callback
 * \param[in]   session     Session handle
 * \param[in]   h           Command or directory handle
 * \param[in]   parms       Parameter(s) - the rest of the command string.
 *                          Can be used for example to get help on individual parameters
 */
typedef void (*bcmcli_help_cb)(bcmcli_session *session, bcmcli_entry *h, const char *parms);


/** Extra parameters of monitor directory.
 * See \ref bcmcli_dir_add
 *
 */
typedef struct bcmcli_dir_extra_parm
{
    void *user_priv;            /**< private data passed to enter_leave_cb */
    bcmcli_dir_enter_leave_cb enter_leave_cb; /**< callback function to be called when session enters/leavs the directory */
    bcmcli_help_cb help_cb;     /**< Help function called to print directory help instead of the automatic help */
} bcmcli_dir_extra_parm;


/** Extra parameters of monitor command.
 * See \ref bcmcli_cmd_add
 *
 */
typedef struct bcmcli_cmd_extra_parm
{
    bcmcli_help_cb help_cb;     /**< Optional help callback. Can be used for more sophisticated help, e.g., help for specific parameters */
    uint32_t flags;             /**< Command flags */
    void (*free_parms)(bcmcli_cmd_parm *parms);    /* Optional user-defined free */
} bcmcli_cmd_extra_parm;


/** Monitor command handler prototype */
typedef bcmos_errno (*bcmcli_cmd_cb)(bcmcli_session *session, const bcmcli_cmd_parm parm[], uint16_t n_parms);

/** CLI command logging mode */
typedef enum
{
    BCMCLI_LOG_NONE,                /**< Disable logging */
    BCMCLI_LOG_CLI,                 /**< Log commands as is and rc as CLI comment*/
    BCMCLI_LOG_C_COMMENT            /**< Log as C comments */
} bcmcli_log_mode;

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
                             const bcmcli_dir_extra_parm *extras);


/** Scan directory tree and look for directory named "name".
 *
 * \param[in]   parent          Directory sub-tree root. NULL=root
 * \param[in]   name            Name of directory to be found
 * \return      directory handle if found or NULL if not found
 */
bcmcli_entry *bcmcli_dir_find(bcmcli_entry *parent, const char *name);


/** Scan directory tree and look for command named "name".
 *
 * \param[in]   parent          Directory sub-tree root. NULL=root
 * \param[in]   name            Name of command to be found
 * \return      command handle if found or NULL if not found
 */
bcmcli_entry *bcmcli_cmd_find(bcmcli_entry *parent, const char *name);


/** Get token name
 * \param[in]   token           Directory or command token
 * \return      directory token name
 */
const char *bcmcli_token_name(bcmcli_entry *token);

/** Find the CLI parameter with the specified name (case insensitive).
 * \param[in]   session  CLI session
 * \param[in]   name     Parameter name
 * \return      The CLI parameter that was found, or NULL if not found
 */
bcmcli_cmd_parm *bcmcli_find_named_parm(bcmcli_session *session, const char *name);

/** Query parameter value status.
 * The function can be used for scalar and array parameters
 * \param[in]   session         CLI session
 * \param[in]   parm            Parameter from the array passed to the CLI command handler
 *                              or returned by bcmcli_find_named_parm()
 * \param[in]   value_index     value_index - for array parameters
 * \return      BCMOS_TRUE if the parameter value is set, BCMOS_FALSE otherwise
 */
bcmos_bool bcmcli_parm_value_is_set(bcmcli_session *session, const bcmcli_cmd_parm *parm, uint32_t value_index);

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
                  const bcmcli_cmd_extra_parm *extras, bcmcli_cmd_parm parms[]);


/** Destroy token (command or directory)
 * \param[in]   token           Directory or command token. NULL=root
 */
void bcmcli_token_destroy(bcmcli_entry *token);

/** Parse and execute input string.
 * input_string can contain multiple commands delimited by ';'
 *
 * \param[in]   session         Session handle
 * \param[in]   input_string    String to be parsed
 * \return
 *      =0  - OK \n
 *      -EINVAL - parsing error\n
 *      other - return code - as returned from command handler.
 *            It is recommended to return -EINTR to interrupt monitor loop.
 */
bcmos_errno bcmcli_parse(bcmcli_session *session, char *input_string);

/** Read input and parse iteratively until EOF or bcmcli_is_stopped()
 *
 * \param[in]   session         Session handle
 * \return
 *      =0  - OK \n
 */
bcmos_errno bcmcli_driver(bcmcli_session *session);

/** Stop monitor driver.
 * The function stops \ref bcmcli_driver
 * \param[in]   session         Session handle
 */
void bcmcli_stop(bcmcli_session *session);

/** Returns 1 if monitor session is stopped
 * \param[in]   session         Session handle
 * \returns 1 if monitor session stopped by bcmcli_stop()\n
 * 0 otherwise
 */
bcmos_bool bcmcli_is_stopped(bcmcli_session *session);

/** Get current directory for the session,
 * \param[in]   session         Session handle
 * \return      The current directory handle
 */
bcmcli_entry *bcmcli_dir_get(bcmcli_session *session);

/** Set current directory for the session.
 * \param[in]   session         Session handle
 * \param[in]   dir             Directory that should become current
 * \return
 *      =0  - OK
 *      <0  - error
 */
bcmos_errno bcmcli_dir_set(bcmcli_session *session, bcmcli_entry *dir);

/** Get command that is being executed.
 * The function is intended for use from command handler.
 * \param[in]   session         Session handle
 * \return      The current command handle
 */
bcmcli_entry *bcmcli_cmd_get(bcmcli_session *session);

/* Get CLI entry info
 * \param[in]   session
 * \param[in]   entry
 * \param[out]  is_dir
 * \param[out]  name
 * \param[out]  descr
 * \param[out]  parent
 */
void bcmcli_entry_info_get(bcmcli_session *session, const bcmcli_entry *entry,
    bcmos_bool *is_dir, const char **name, const char **descr, const bcmcli_entry **parent);

/** Get parameter number given its name.
 * The function is intended for use by command handlers
 * \param[in]       session         Session handle
 * \param[in]       parm_name       Parameter name
 * \return
 *  >=0 - parameter number\n
 *  <0  - parameter with this name doesn't exist
 */
int bcmcli_parm_number(bcmcli_session *session, const char *parm_name);

/** Get parameter by name
 * The function is intended for use by command handlers
 * \param[in]       session         Session handle
 * \param[in]       parm_name       Parameter name
 * \return
 * parameter pointer or NULL if not found
 */
bcmcli_cmd_parm *bcmcli_parm_get(bcmcli_session *session, const char *parm_name);

/** Check if parameter is set
 * The function is intended for use by command handlers
 * \param[in]       session         Session handle
 * \param[in]       parm            Parameter name
 * \return
 * TRUE if parameter is set, FALSE otherwise
 */
static inline bcmos_bool bcmcli_parm_is_set(bcmcli_session *session, const bcmcli_cmd_parm *parm)
{
    bcmos_bool parm_is_set = BCMOS_FALSE;
    if (parm)
    {
        parm_is_set = (parm->flags & BCMCLI_PARM_FLAG_ASSIGNED) ? BCMOS_TRUE : BCMOS_FALSE;
    }
    return parm_is_set;
}

/** Check if parameter is set
 * \param[in]       session         Session handle
 * \param[in]       parm_number     Parameter number
 * \return
 *  0 if parameter is set\n
 *  BCM_ERR_NOENT if parameter is not set
 *  BCM_ERR_PARM if parm_number is invalid
 */
bcmos_errno bcmcli_parm_check(bcmcli_session *session, int parm_number);


/** Get enum's string value given its internal value
 * \param[in]       table           Enum table
 * \param[in]       value           Internal value
 * \return
 *      enum string value or NULL if internal value is invalid
 */
static inline const char *bcmcli_enum_stringval(const bcmcli_enum_val table[], long value)
{
    while(table->name)
    {
        if (table->val==value)
            return table->name;
        ++table;
    }
    return NULL;
}


/** Get enum's parameter string value given its internal value
 * \param[in]       session         Session handle
 * \param[in]       parm            Parameter
 * \return
 *      enum string value or NULL if parameter is not enum or
 *      internal value is invalid
 */
const char *bcmcli_enum_parm_stringval(bcmcli_session *session, const bcmcli_cmd_parm *parm);


/** Print CLI parameter value
 * \param[in]       session         Session handle
 * \param[in]       parm            Parameter
 */
void bcmcli_parm_print(bcmcli_session *session, const bcmcli_cmd_parm *parm);

/* Redefine bcmcli_session_print --> bcmcli_print */
#define bcmcli_print bcmcli_session_print

/** Enable / disable CLI command logging
 * \param[in]   mode    Logging flags
 * \param[in]   session Log session. Must be set if mode != BCMCLI_CMD_LOG_NONE
 * \return 0=OK or error <0
 */
bcmos_errno bcmcli_log_set(bcmcli_log_mode mode, bcmcli_session *session);

/** Write string to CLI log.
 * The function is ignored if CLI logging is not enabled using bcmcli_log_set()
 * \param[in]   format  printf-like format followed by arguments
 */
void bcmcli_log(const char *format, ...);

#ifdef __cplusplus
}
#endif

/** @} end bcm_cli group */

#endif /* #ifndef BCM_CLI_H */
