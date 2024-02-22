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

#ifndef BCMOLT_API_MACROS_H_
#define BCMOLT_API_MACROS_H_

#include <bcmolt_msg.h>
#include <bcmolt_type_metadata.h>

/** \defgroup api_macros Message Access Macros
 * \ingroup(api)
 * @{
 */

/*
 * Message Initialization Macros
 */

/* Initialize object key structure
 * \param[in]   _s      KEY structure
 * \param[in]   _obj    Object type
 */
#define BCMOLT_KEY_INIT(_s, _obj) \
    do {\
        bcmolt_ ## _obj ## _key *_x_ = _s;\
        memset(_x_, 0, sizeof(*_x_));\
        bcmolt_ ## _obj ## _key_set_default(_s);\
    } while (0)


/* Initialize request. Internal macro
 * \param[in]   _h      Message header
 * \param[in]   _obj    Object type
 * \param[in]   _grp    message type
 * \param[in]   _subgrp message subgroup
 */
#define _BCMOLT_REQ_INIT(_h, _obj, _grp, _subgrp) \
    (_h)->hdr.dir = BCMOLT_MSG_DIR_REQUEST;\
    (_h)->hdr.err = BCM_ERR_OK;\
    (_h)->hdr.obj_type = bcmolt_obj_id_ ## _obj;\
    (_h)->hdr.group = _grp;\
    (_h)->hdr.subgroup = (uint16_t)_subgrp;\
    (_h)->hdr.corr_tag = 0;\
    (_h)->hdr.loid = BCMOLT_LOID_UNDEFINED;

/** Initialize configuration structure
 * \param[in]   _s      Configuration structure
 * \param[in]   _obj    Object type
 * \param[in]   _key    Object key
 */
#define BCMOLT_CFG_INIT(_s, _obj, _key) \
    do {\
        bcmolt_ ## _obj ## _cfg *_x_ = _s;\
        memset(_x_, 0, sizeof(*_x_));\
        _BCMOLT_REQ_INIT(&((_x_)->hdr), _obj, BCMOLT_MGT_GROUP_CFG, 0);\
        (_x_)->key = _key;\
    } while (0)

/** Initialize statistics structure
 * \param[in]   _s      Statistics structure
 * \param[in]   _obj    Object type
 * \param[in]   _stat   Statistics type
 * \param[in]   _key    Object key
 */
#define BCMOLT_STAT_INIT(_s, _obj, _stat, _key) \
    do {\
        bcmolt_ ## _obj ## _ ## _stat *_x_ = _s;\
        memset(_x_, 0, sizeof(*_x_));\
        _BCMOLT_REQ_INIT(&((_x_)->hdr), _obj, BCMOLT_MGT_GROUP_STAT, bcmolt_ ## _obj ## _stat_subgroup_ ## _stat);\
        (_x_)->key = _key;\
    } while (0)

/** Initialize statistic configuration structure
 * \param[in]   _s      Statistics configuration structure
 * \param[in]   _obj    Object type
 * \param[in]   _stat   Statistics type
 * \param[in]   _key    Object key
 */
#define BCMOLT_STAT_CFG_INIT(_s, _obj, _stat, _key) \
    do {\
        bcmolt_ ## _obj ## _ ## _stat ## _cfg *_x_ = _s;\
        memset(_x_, 0, sizeof(*_x_));\
        _BCMOLT_REQ_INIT(&((_x_)->hdr), _obj, BCMOLT_MGT_GROUP_STAT_CFG,\
            bcmolt_ ## _obj ## _stat_cfg_subgroup_ ## _stat ## _cfg);\
        (_x_)->key = _key;\
    } while (0)

/** Initialize indication configuration structure
 * \param[in]   _s      Indication configuration structure
 * \param[in]   _obj    Object type
 * \param[in]   _key    Object key
 */
#define BCMOLT_AUTO_CFG_INIT(_s, _obj, _key) \
    do {\
        bcmolt_ ## _obj ## _auto_cfg *_x_ = _s;\
        memset(_x_, 0, sizeof(*_x_));\
        _BCMOLT_REQ_INIT(&((_x_)->hdr), _obj, BCMOLT_MGT_GROUP_AUTO_CFG, 0);\
        (_x_)->key = _key;\
    } while (0)

/** Initialize operation structure
 * \param[in]   _s      Operation structure
 * \param[in]   _obj    Object type
 * \param[in]   _op     Operation type
 * \param[in]   _key    Object key
 */
#define BCMOLT_OPER_INIT(_s, _obj, _op, _key) \
    do {\
        bcmolt_ ## _obj ## _ ## _op *_x_ = _s;\
        memset(_x_, 0, sizeof(*_x_));\
        _BCMOLT_REQ_INIT(&((_x_)->hdr), _obj, BCMOLT_MGT_GROUP_OPER, bcmolt_ ## _obj ## _oper_subgroup_ ## _op);\
        (_x_)->key = _key;\
    } while (0)

/** Initialize autonomous indication structure
 * \param[in]   _s      Autonomous indication structure
 * \param[in]   _obj    Object type
 * \param[in]   _au     Autonomous indication type
 * \param[in]   _key    Object key
 */
#define BCMOLT_AUTO_INIT(_s, _obj, _au, _key) \
    do {\
        bcmolt_ ## _obj ## _ ## _au *_x_ = _s;\
        memset(_x_, 0, sizeof(*_x_));\
        _BCMOLT_REQ_INIT(&((_x_)->hdr), _obj, BCMOLT_MGT_GROUP_AUTO, bcmolt_ ## _obj ## _auto_subgroup_ ## _au);\
        (_x_)->key = _key;\
    } while (0)

/** Set the memory buffer to use for variable-sized lists within a cfg get
 * \param[in]   _s      Configuration structure
 * \param[in]   _obj    Object type
 * \param[in]   _buf    Pointer to a location in memory in which to store the lists
 * \param[in]   _len    Length of the buffer pointed to by _buf
 */
#define BCMOLT_CFG_LIST_BUF_SET(_s, _obj, _buf, _len) \
    do {\
        bcmolt_ ## _obj ## _cfg *_x_ = _s;\
        _x_->hdr.hdr.list_buf = _buf;\
        _x_->hdr.hdr.list_buf_size = _len;\
    } while (0)

/** \defgroup fields Field access
 * @{
 */

/** Indicate that an API field is present (set/requested) */
#define BCMOLT_FIELD_SET_PRESENT(_s_ptr, _s_type, _f_name)                      \
    (_s_ptr)->presence_mask |= (1ULL << bcmolt_ ## _s_type ## _id_ ## _f_name)

#define BCMOLT_FIELD_CLEAR_PRESENT(_s_ptr, _s_type, _f_name)                    \
    (_s_ptr)->presence_mask &= ~(1ULL << bcmolt_ ## _s_type ## _id_ ## _f_name)

/** Set API field value */
#define BCMOLT_FIELD_SET(_s_ptr, _s_type, _f_name, _field_value)                \
    do {                                                                        \
        BCMOLT_FIELD_SET_PRESENT(_s_ptr, _s_type, _f_name);                     \
        (_s_ptr)->_f_name = (_field_value);                                     \
    } while(0)

static inline bcmos_bool bcmolt_field_is_set(bcmolt_presence_mask pm, bcmolt_meta_id field_id)
{
    return (pm == 0) || ((pm & (1ULL << field_id)) != 0);
}

/** Check if API field is present (set/requested) */
#define BCMOLT_FIELD_IS_SET(_s_ptr, _s_type, _f_name)                           \
    bcmolt_field_is_set((_s_ptr)->presence_mask, bcmolt_ ## _s_type ## _id_ ## _f_name)

/** Set field value in the message.
 * Unlike BCMOLT_FIELD_SET() macro, BCMOLT_MSG_FIELD_SET() takes fully qualified field name.
 * The macro can be used even for fields which are deeply embedded in levels of sub-structures.
 */
#define BCMOLT_MSG_FIELD_SET(_msg_ptr, _fully_qualified_field_name, _field_value)  \
    do {                                                                           \
        (_msg_ptr)->data._fully_qualified_field_name = (_field_value);             \
        bcmolt_api_set_prop_present(&((_msg_ptr)->hdr.hdr), &((_msg_ptr)->data._fully_qualified_field_name));\
    } while(0)

#define BCMOLT_MULTI_MSG_FILTER_SET(_msg_ptr, _fully_qualified_field_name, _field_value)  \
    do {                                                                           \
        (_msg_ptr)->filter._fully_qualified_field_name = (_field_value);             \
        bcmolt_api_set_prop_present(&((_msg_ptr)->hdr.hdr.hdr), &((_msg_ptr)->filter._fully_qualified_field_name));\
    } while(0)

/** Mark field for retrieval by bcmolt_cfg_get() request
 * Unlike BCMOLT_FIELD_SET_PRESENT() macro, BCMOLT_MSG_FIELD_GET() takes fully qualified field name.
 * The macro can be used even for fields which are deeply embedded in levels of sub-structures.
 */
#define BCMOLT_MSG_FIELD_GET(_msg_ptr, _fully_qualified_field_name)                \
    bcmolt_api_set_prop_present(&((_msg_ptr)->hdr.hdr), &((_msg_ptr)->data._fully_qualified_field_name))

#define BCMOLT_MULTI_MSG_FIELD_GET(_msg_ptr, _fully_qualified_field_name)                \
    bcmolt_api_set_prop_present(&((_msg_ptr)->hdr.hdr.hdr), &((_msg_ptr)->request._fully_qualified_field_name))


/** @} */

/** \defgroup arrays Array element access
 * @{
 */

/* Check if array structure has a dynamically allocated "arr" field */
#define _BCMOLT_ARRAY_IS_DYNAMIC(_a_ptr)                                        \
    ((const void *)(_a_ptr) != (const void *)(&((_a_ptr)->arr_index_mask)))

/* Check if array is empty */
#define BCMOLT_ARRAY_IS_EMPTY_RAW(_a_ptr)       \
    ((_a_ptr)->arr_index_mask == 0)

/* Check if array index is valid */
#define _BCMOLT_ARRAY_ELEM_IDX_IS_VALID(_a_ptr, _idx)                           \
    (_BCMOLT_ARRAY_IS_DYNAMIC(_a_ptr) ||                                        \
     ((int)(_idx) * sizeof((_a_ptr)->arr[0]) < sizeof((_a_ptr)->arr)))

/* Check if array index is in bounds */
#define _BCMOLT_ARRAY_ELEM_IDX_IS_IN_BOUNDS(_a_ptr, _idx)                        \
    (_BCMOLT_ARRAY_ELEM_IDX_IS_VALID(_a_ptr, _idx) &&                            \
     (_BCMOLT_ARRAY_IS_DYNAMIC(_a_ptr) || (int)(_idx) < sizeof((_a_ptr)->arr_index_mask) * 8))

/** Set presence flag for array element.
 * Note: array indices >63 cannot be covered by the index mask and are assumed to always be set.
 *
 * \param[in]   _a_ptr  pointer to the array attribute/field structure.
 *              the structure contains 2 fields: arr_index_mask and array "arr"
 * \param[in]   _idx    array element index
 * \returns     BCM_ERR_OK if it is valid
 *              BCM_ERR_RANGE (<0) if index is out of range
 */
#define BCMOLT_ARRAY_ELEM_SET_PRESENT(_a_ptr, _idx)                             \
    (!_BCMOLT_ARRAY_ELEM_IDX_IS_IN_BOUNDS(_a_ptr, _idx) ? BCM_ERR_RANGE :       \
     (((int)(_idx) > 63) ? BCM_ERR_OK :                                         \
      ((_a_ptr)->arr_index_mask |= (1ULL << (int)(_idx)), BCM_ERR_OK)))

/** Clear presence flag for array element.
 * Note: array indices >63 cannot be covered by the index mask and are assumed to always be set.
 *
 * \param[in]   _a_ptr  pointer to the array attribute/field structure.
 *              the structure contains 2 fields: arr_index_mask and array "arr"
 * \param[in]   _idx    array element index
 * \returns     BCM_ERR_OK if it is valid
 *              BCM_ERR_RANGE (<0) if index is out of range
 */
#define BCMOLT_ARRAY_ELEM_SET_NOT_PRESENT(_a_ptr, _idx)                             \
    (!_BCMOLT_ARRAY_ELEM_IDX_IS_IN_BOUNDS(_a_ptr, _idx) ? BCM_ERR_RANGE :       \
     (((int)(_idx) > 63) ? BCM_ERR_OK :                                         \
      ((_a_ptr)->arr_index_mask &= ~(1ULL << (int)(_idx)), BCM_ERR_OK)))

static inline bcmos_bool bcmolt_array_elem_is_present(bcmolt_presence_mask idx_mask, int idx)
{
    return (idx > 63) || (idx_mask == 0) || ((idx_mask & (1ULL << idx)) != 0);
}

/** Check if array element is present.
 * Note: array indices >63 cannot be covered by the index mask and are assumed to always be set.
 *
 * \param[in]   _a_ptr  pointer to the array attribute/field structure.
 *              the structure contains 2 fields: arr_index_mask and array "arr"
 * \param[in]   _idx    array element index
 * \returns     BCMOS_TRUE if element is present
 */
#define BCMOLT_ARRAY_ELEM_IS_PRESENT(_a_ptr, _idx)                              \
    (_BCMOLT_ARRAY_ELEM_IDX_IS_VALID(_a_ptr, _idx) &&                           \
    bcmolt_array_elem_is_present((_a_ptr)->arr_index_mask, (int)(_idx)))

/** Check if array element is present.
 * Note: array indices >63 cannot be covered by the index mask and are assumed to always be set.
 * Note: This "raw" version does not treat PM = 0 as all-fields-present. Useful in handling "Set" APIs.
 *
 * \param[in]   _a_ptr  pointer to the array attribute/field structure.
 *              the structure contains 2 fields: arr_index_mask and array "arr"
 * \param[in]   _idx    array element index
 * \returns     BCMOS_TRUE if element is present
 */
#define BCMOLT_ARRAY_ELEM_IS_PRESENT_RAW(_a_ptr, _idx)                  \
    (_BCMOLT_ARRAY_ELEM_IDX_IS_VALID(_a_ptr, _idx) &&                   \
     ((int)(_idx) > 63 ||                                               \
      (((_a_ptr)->arr_index_mask & (1ULL << (int)(_idx))) != 0)))

/** Set array element
 * \param[in]   _a_ptr  pointer to the array attribute/field structure.
 *              the structure contains 2 fields: arr_index_mask and array "arr"
 * \param[in]   _idx    array element index
 * \param[in]   _val    element value to be set
 * \returns     BCM_ERR_OK if it is valid
 *              BCM_ERR_RANGE (<0) if index is out of range
 *              BCM_ERR_NULL (<0) if "arr" was null (for dynamically allocated arrays)
 */
#define BCMOLT_ARRAY_ELEM_SET(_a_ptr, _idx, _val)                                   \
    ((_BCMOLT_ARRAY_IS_DYNAMIC(_a_ptr) && ((_a_ptr)->arr == NULL)) ? BCM_ERR_NULL : \
     ((BCMOLT_ARRAY_ELEM_SET_PRESENT(_a_ptr, _idx) != BCM_ERR_OK) ? BCM_ERR_RANGE : \
      ((_a_ptr)->arr[_idx] = _val, BCM_ERR_OK)))

/** Clear array element
 * \param[in]   _a_ptr  pointer to the array attribute/field structure.
 *              the structure contains 2 fields: arr_index_mask and array "arr"
 * \param[in]   _idx    array element index
 * \returns     BCM_ERR_OK if it is valid
 *              BCM_ERR_RANGE (<0) if index is out of range
 *              BCM_ERR_NULL (<0) if "arr" was null (for dynamically allocated arrays)
 */
#define BCMOLT_ARRAY_ELEM_CLEAR(_a_ptr, _idx)                           \
    ((_BCMOLT_ARRAY_IS_DYNAMIC(_a_ptr) && ((_a_ptr)->arr == NULL)) ? BCM_ERR_NULL : \
     ((BCMOLT_ARRAY_ELEM_SET_NOT_PRESENT(_a_ptr, _idx) != BCM_ERR_OK) ? BCM_ERR_RANGE : \
      BCM_ERR_OK))

/** @} */

/** \defgroup multi_api_func Multi-object property access macros
 * @{
 */

/*
 * Macros for multi-object configuration and statistics retrieval
 */

/** Allocate a multi-object configuration API structure.
 *  This allocates memory - once the structure is no longer in use, it must be freed with bcmolt_multi_msg_free().
 *
 * \param[in]   _obj            Object type
 * \param[in]   _key            Object key
 * \param[in]   _max_responses  Maximum number of response objects per API call
 */
#define BCMOLT_MULTI_CFG_ALLOC(_obj, _key, _max_responses) \
    ((bcmolt_ ## _obj ## _multi_cfg *) \
        bcmolt_multi_msg_alloc(bcmolt_obj_id_ ## _obj, BCMOLT_MGT_GROUP_CFG, 0, &(_key), (_max_responses)))

/** Allocate a multi-object statistics API structure.
 *  This allocates memory - once the structure is no longer in use, it must be freed with bcmolt_multi_msg_free().
 *
 * \param[in]   _obj            Object type
 * \param[in]   _stat           Statistics type
 * \param[in]   _key            Object key
 * \param[in]   _max_responses  Maximum number of response objects per API call
 */
#define BCMOLT_MULTI_STAT_ALLOC(_obj, _stat, _key, _max_responses) \
    ((bcmolt_ ## _obj ## _multi_ ## _stat *) \
        bcmolt_multi_msg_alloc( \
            bcmolt_obj_id_ ## _obj, \
            BCMOLT_MGT_GROUP_STAT, \
            (uint16_t)bcmolt_ ## _obj ## _stat_subgroup_ ## _stat, \
            &(_key), \
            (_max_responses)))

/** Set a key field to a wildcard value, meaning it will be ignored when performing a multi-object API.
 *
 * \param[in]   _f_ptr  Pointer to the field to set
 */
#define BCMOLT_KEY_SET_TO_WILDCARD(_f_ptr) memset((_f_ptr), 0xFF, sizeof(*(_f_ptr)))

/** Checks if a key field is set to a wildcard value, meaning it will be ignored when performing a multi-object API.
 *
 * \param[in]   _f_ptr  Pointer to the field to check
 */
#define BCMOLT_KEY_IS_WILDCARD(_f_ptr) bcmolt_key_is_wildcard((const uint8_t *)(_f_ptr), sizeof(*(_f_ptr)))

/** Internal helper function for BCMOLT_KEY_IS_WILDCARD. */
static inline bcmos_bool bcmolt_key_is_wildcard(const uint8_t *f_ptr, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
    {
        if (f_ptr[i] != 0xFF)
        {
            return BCMOS_FALSE;
        }
    }
    return BCMOS_TRUE;
}

/** @} */

/** @} */

#endif /* BCMOLT_API_MACROS_H_ */
