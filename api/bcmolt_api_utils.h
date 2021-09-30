/*
<:copyright-BRCM:2016-2019:Apache:standard

 Copyright (c) 2016-2019 Broadcom. All Rights Reserved

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

 *  :>
 */

#ifndef _BCMOLT_API_UTILS_H_
#define _BCMOLT_API_UTILS_H_

#include <bcmos_system.h>
#include <bcmolt_msg.h>
#include <bcmolt_utils.h>
#include "bcmolt_api_metadata.h"
#include <bcm_dev_log.h>

#define BCMOLT_PROP_TERMINATE UINT32_MAX

/* The longest path string length */
#define BCMOLT_API_MAX_TYPE_DESCR_PATH_STR 256

typedef struct bcmolt_api_prop_tree bcmolt_api_prop_tree;

/* Defines a node in an hierarchical tree structure. */
struct bcmolt_api_prop_tree
{
    uint32_t prop;
    bcmolt_api_prop_tree *sub_tree;
    void *data; /* User data */
    uint32_t options; /* Generic options pertaining to the user data */
};

/* The longest depth of path to a leaf. */
#define BCMOLT_API_MAX_PATH_DEPTH 16

/* Internal helper function for BCMOLT_API_NEXT_ID. */
static inline uint8_t bcmolt_api_next_id_generic(uint8_t cur_id, uint8_t count, uint64_t full_mask)
{
    while (cur_id < count)
    {
        ++cur_id;
        if ((full_mask & (1ull << cur_id)) != 0)
        {
            break;
        }
    }
    return cur_id;
}

/* Macro to determine the next valid ID number of a given type.
 * NOTE: the seemingly redundant cast to int is to avoid the -Wbad-function-cast false error.
 * \param type The name of the ID type (e.g. 'bcmolt_object_id').
 * \param val An ID number.
 * \return The next ID number (or xx__NUM_OF if no more are available).
 */
#define BCMOLT_API_NEXT_ID(type, val) \
    ((type)((int)bcmolt_api_next_id_generic((uint8_t)(val), (uint8_t)type ## __num_of, type ## _full_mask)))

/* Macro to iterate over each defined value for a given ID type (object ID, field ID, etc).
 * \param type The name of the ID type (e.g. 'bcmolt_object_id').
 * \param var An variable with the ID enum type.
 */
#define BCMOLT_API_FOR_EACH_ID(type, var) \
    for ((var) = type ## __begin; \
        (var) < type ## __num_of; \
        (var) = BCMOLT_API_NEXT_ID(type, var))

/* Macro to iterate over each defined object ID. */
#define BCMOLT_API_FOR_EACH_OBJ_ID(var) BCMOLT_API_FOR_EACH_ID(bcmolt_obj_id, var)

typedef enum
{
    BCMOLT_API_PROP_NODE_TYPE_INVALID,
    BCMOLT_API_PROP_NODE_TYPE_FIELD,
    BCMOLT_API_PROP_NODE_TYPE_ARRAY_INDEX,
} bcmolt_api_prop_node_type;

typedef struct
{
    bcmolt_api_prop_node_type type;
    union
    {
        const bcmolt_field_descr *field;
        uint16_t array_index;
    } u;
} bcmolt_api_prop_node;

/* This struct describes the absolute path to a leaf. */
typedef struct
{
    bcmolt_api_prop_node nodes[BCMOLT_API_MAX_PATH_DEPTH];
    uint32_t curr_depth;
} bcmolt_api_prop_path;

/* Callback for property tree traversal.
 * 'field_descr' is the current field description being traversed
 * 'field_data' is the current field's data (from a message) being traversed
 * 'node' is the current node being traversed
 * 'context' is any user context
 * 'path' is the absolute path to the current object being traversed
 * Return value:
 * - BCMOS_ERR_OK means continue recursion
 * - Otherwise, stop recursion
 * */
typedef bcmos_errno (*bcmolt_api_prop_iter_cb)(const bcmolt_field_descr *field_descr, const uint8_t *field_data, const bcmolt_api_prop_tree *node, void *context,
    const bcmolt_api_prop_path *path);

/* Get the pointer to the presence mask within 'data' (representing a structure). */
const bcmolt_presence_mask *bcmolt_api_get_presence_mask_ptr(const uint8_t *data, const bcmolt_type_descr *type_descr);

/* Get the value of the presence mask within 'data' (representing a structure). */
bcmolt_presence_mask bcmolt_api_get_presence_mask(const uint8_t *data, const bcmolt_type_descr *type_descr);

/* Construct the presence mask of all possible fields within 'type_descr' (representing a structure). */
bcmolt_presence_mask bcmolt_api_get_presence_mask_all(const bcmolt_type_descr *type_descr);

/* Recursively walk through the properties that are set in 'msg', trying to find if they are also set in 'tree'.
 * For every match, call the corresponding callback ('cb') with its context ('context').
 * If 'tree' is NULL, then it is equivalent to a situation in which all properties are set.
 * Return value:
 * - BCM_ERR_OK if all callbacks returned BCM_ERR_OK, or other error if one of the callbacks returned an error. */
bcmos_errno bcmolt_api_prop_iter_func(const bcmolt_msg *msg, const bcmolt_api_prop_tree *tree, bcmolt_api_prop_iter_cb cb, void *context, const char *func, int line);

#define bcmolt_api_prop_iter(msg, tree, cb, context) bcmolt_api_prop_iter_func(msg, tree, cb, context, __FUNCTION__, __LINE__)

/* Recursively walk through the properties that are set in 'msg', trying to find if they are also set in 'tree'.
 * If the property is found in both 'msg' and 'tree':
 *   - Return true
 *   - In 'path' return the absolute path to the property
 * Otherwise:
 *   - Return false
 *   - In 'path' return the empty path */
bcmos_bool bcmolt_api_prop_tree_is_set(const bcmolt_msg *msg, const bcmolt_api_prop_tree *tree, bcmolt_api_prop_path *path);

/* For each property which is both set in the message and specified in the tree:
   compare the data in to_compare to the message
   Return true if all properties match (path will be empty)
   Return false if any properties differ (path will contain first non-matching property */
bcmos_bool bcmolt_api_prop_tree_compare(
    const bcmolt_msg *msg,
    const bcmolt_api_prop_tree *tree,
    const void *msg_data,
    const void *to_compare,
    bcmolt_api_prop_path *path);

/* Same as bcmolt_api_prop_tree_is_set(), but works on a single property described by its offset from the beginning of a message.
 * !!WARNING!!
 * If the union type is NOT set (e.g. - in a cfg get), then this function CANNOT be used.
 */
bcmos_bool bcmolt_api_prop_is_set(const bcmolt_msg *msg, const void *prop_ptr, bcmolt_api_prop_path *path);

/* Set all presence mask bits for the given sub-property recursively. This function works at any property depth for
 * structures, static arrays and dynamic arrays.
 * \param msg The API message header.
 * \param prop_ptr The address of the property you want to request.
 */
void bcmolt_api_set_prop_present(bcmolt_msg *msg, const void *prop_ptr);

/* Clear the lowest-level presence mask bit for a given sub-property. This function works at any property depth for
 * structures, static arrays and dynamic arrays.
 * \param msg The API message header.
 * \param prop_ptr The address of the property you want to request.
 */
void bcmolt_api_clear_prop_presence(bcmolt_msg *msg, const void *prop_ptr);

/* Get the the string representation of an absolute path into 'path_str'. */
char *bcmolt_api_prop_get_path_str(const bcmolt_api_prop_path *path, char *path_str, uint32_t max_path_str_len);

/* Perform various checks to make sure a message is valid for a top-level API call. */
bcmos_errno bcmolt_api_validate_for_api_call(bcmolt_msg *msg);

bcmos_errno bcmolt_msg_err(
    bcmolt_msg *msg,
    dev_log_id log_id,
    bcmos_errno err,
    const bcmolt_api_prop_path *path,
    const char *fmt,
    ...)__attribute__((format(__printf__, 5, 6)));

#ifdef ENABLE_LOG
/** Set message error. Cannot be static inline, as it uses variable argument list. */
/** This function does NOT produce the line numnber file name */
/* convenience macro for calling above function with no field path info, it does include line and file name in the output */
#define BCMOLT_MSG_ERR(msg, log_id, err, fmt, args...) \
    bcmolt_msg_err(msg, log_id, err, NULL, "%s%d| " fmt, dev_log_basename(__FILE__" "), __LINE__, ##args)

/* convenience macro for calling above function with field path info, it does include line and file name in the output */
#define BCMOLT_MSG_ERR_PATH(msg, log_id, err, path, fmt, args...) \
    bcmolt_msg_err(msg, log_id, err, path, "%s%d| " fmt, dev_log_basename(__FILE__" "), __LINE__, ##args)
#else
/* NOTE: The underlying calls tl bcmolt_msg_err will ignore the log_id parameter when ENABLE_LOG is not defined*/
#define BCMOLT_MSG_ERR(msg, log_id, err, fmt, args...) \
    bcmolt_msg_err(msg, 0, err, NULL, "%s%d| " fmt, __FILE__" ", __LINE__, ##args)

/* convenience macro for calling above function with field path info, it does include line and file name in the output */
#define BCMOLT_MSG_ERR_PATH(msg, log_id, err, path, fmt, args...) \
    bcmolt_msg_err(msg, 0, err, path, "%s%d| " fmt, __FILE__" ", __LINE__, ##args)
#endif

typedef enum
{
    BCMOLT_API_PM_COPY_MODE_DEST,
    BCMOLT_API_PM_COPY_MODE_SRC,
    BCMOLT_API_PM_COPY_MODE_IGNORE,
} bcmolt_api_pm_copy_mode;

/* Helper function for BCMOLT_API_COPY_FIELD() - not usually called directly. */
void bcmolt_api_copy_field_generic(
    const bcmolt_type_descr *type,
    void *dest,
    const void *src,
    bcmolt_api_pm_copy_mode mode);

/* Helper function for BCMOLT_API_CHECK_FIELD_EQUALITY() - not usually called directly. */
bcmos_bool bcmolt_api_check_field_equality_generic(const bcmolt_type_descr *type, const void *a, const void *b);

/* Helper function for BCMOLT_API_COPY_MULTIGET_PRESENCE_MASK() - not usually called directly. */
void bcmolt_api_copy_multiget_presence_mask(const bcmolt_type_descr *type, void *dest, const void *src);

/** Copy an API field of type 'type' from 'src' to 'dest' using the src presence mask.
 *
 * NOTE: this works properly for all data types, except those that contain dynamic arrays. For dynamic arrays/binary
 * strings, this simply copies the entire struct by value (including the length, data pointer and index mask). It's
 * up to the caller to manually copy the actual array content into local storage manually after calling this macro.
 *
 * \param type The full data type name - works for primitives e.g. uint32_t as well as API types.
 * \param dest The destination data pointer (type must be '<type>*').
 * \param src The source data pointer (type must be 'const <type>*').
 */
#define BCMOLT_API_COPY_FIELD_SRC_PM(type, dest, src) \
    do \
    { \
        /* Make local copies for type safety. */ \
        type *__dest_copy = (dest); \
        const type *__src_copy = (src); \
        bcmolt_api_copy_field_generic( \
            &type_descr_ ## type, __dest_copy, __src_copy, BCMOLT_API_PM_COPY_MODE_SRC); \
    } while (0)

/** Copy an API field of type 'type' from 'src' to 'dest' using the dest presence mask.
 *
 * NOTE: this works properly for all data types, except those that contain dynamic arrays. For dynamic arrays/binary
 * strings, this simply copies the entire struct by value (including the length, data pointer and index mask). It's
 * up to the caller to manually copy the actual array content into local storage manually after calling this macro.
 *
 * \param type The full data type name - works for primitives e.g. uint32_t as well as API types.
 * \param dest The destination data pointer (type must be '<type>*').
 * \param src The source data pointer (type must be 'const <type>*').
 */
#define BCMOLT_API_COPY_FIELD_DST_PM(type, dest, src) \
    do \
    { \
        /* Make local copies for type safety. */ \
        type *__dest_copy = (dest); \
        const type *__src_copy = (src); \
        bcmolt_api_copy_field_generic( \
            &type_descr_ ## type, __dest_copy, __src_copy, BCMOLT_API_PM_COPY_MODE_DEST); \
    } while (0)

/** Check if an two values for an API field, 'a' and 'b' are equal, using the presence mask from 'a'.
 *
 * NOTE: This has the same limitations as BCMOLT_API_COPY_FIELD_SRC_PM.
 *
 * \param type The full data type name - works for primitives e.g. uint32_t as well as API types.
 * \param a The first value pointer (type must be 'const <type>*').
 * \param b The second value pointer (type must be 'const <type>*').
 * \return BCMOS_TRUE if 'a' and 'b' are equal, BCMOS_FALSE otherwise.
 */
#define BCMOLT_API_CHECK_FIELD_EQUALITY(type, a, b) \
    (((a) != (const type *)NULL) /* provides some basic type checking (most compilers will complain) */ \
     && ((b) != (const type *)NULL) \
     && bcmolt_api_check_field_equality_generic(&type_descr_ ## type, (a), (b)))

/** Prepare an API multi-object get request, based on the incoming filter/request data structure.
 *
 * This function will process the hierarchical presence masks in the incoming data structure, with the result being
 * logically OR'd into the destination structure. This should be called twice - once with the filter and once with the
 * requested data. This will cause us to return all fields that are either filtered on or requested specifically.
 *
 * NOTE: we don't support requesting dynamically-sized lists in the context of a multi-object get. All
 * dynamically-sized lists will have their presence mask bits turned off.
 *
 * \param type The full data type name.
 * \param dest The destination data pointer (type must be '<type>*').
 * \param src The incoming request data pointer (type must be 'const <type>*').
 */
#define BCMOLT_API_COPY_MULTIGET_PRESENCE_MASK(type, dest, src) \
    do \
    { \
        /* Make local copies for type safety. */ \
        type *__dest_copy = (dest); \
        const type *__src_copy = (src); \
        bcmolt_api_copy_multiget_presence_mask(&type_descr_ ## type, __dest_copy, __src_copy); \
    } while (0)

/** Set an API strucure to defaults, respecting the existing presence masks
 *
 * \param type The full data type name - works for primitives e.g. uint32_t as well as API types.
 * \param dest The destination data pointer (type must be '<type>*').
 */
#define BCMOLT_SET_DEFAULT_DATA(type, dest) \
    do \
    { \
        type __defaults; \
        type ## _set_default(&__defaults); \
        BCMOLT_API_COPY_FIELD_DST_PM(type, dest, &__defaults); \
    } while (0)

/* Log a given message into the device logger. */
bcmos_errno bcmolt_api_msg_log(dev_log_id log_id, bcmolt_msg *msg);

/* Get the set of tags that represent a given field (inheriting tags from the parent as necessary. */
bcmolt_tag bcmolt_api_get_field_tags(
    const bcmolt_msg *msg,
    const bcmolt_api_prop_path *path,
    const bcmolt_field_descr *field);

/* Initialize API utils library */
bcmos_errno bcmolt_api_utils_init(void);

#endif
