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

/* bcmolt_type_metadata.h:
 * Helper types/functions for describing data types and their fields.
 */

#ifndef BCMOLT_TYPE_METADATA_H
#define BCMOLT_TYPE_METADATA_H

#include <bcmos_system.h>
#include <bcmolt_system_types_typedefs.h>
#include "bcmolt_buf.h"
#include "bcmolt_presence_mask.h"
#include "bcmolt_mgt_group.h"

/* Max length of a a name string (type name, field name, etc). */
#define BCMOLT_MAX_METADATA_NAME_LENGTH 80

/* Max length of a help string (description, usage, etc). */
#define BCMOLT_MAX_METADATA_HELP_LENGTH 128

/* Standard strings used to represent certain values across the system (declared here for convenience). */
#define BCMOLT_ARRAY_EMPTY_STR    "-"
#define BCMOLT_PARM_NO_VALUE_STR  "_"
#define BCMOLT_ENUM_MASK_DEL_STR  "+"

/* Numeric type used for storing enum values. */
typedef long bcmolt_enum_number;

/* Generic ID number (field, group, etc). */
typedef uint16_t bcmolt_meta_id;

/* Enum attribute value. Arrays of this type are terminated by an element with name==NULL. */
typedef struct
{
    const char *name;       /**< Enum symbolic name */
    bcmolt_enum_number val; /**< Enum internal value */
    uint32_t tags;          /**< Bitmask of tags that apply to this enum entry */
} bcmolt_enum_val;

#define BCMOLT_MAX_ENUM_VALUES 128       /**< Max number of enum values in a value->name table */
#define BCMOLT_ENUM_LAST       {NULL, 0} /**< Last entry in an enum value->name table */

#define BCMOLT_METADATA_MGT_GROUP_KEY 0  /**< Management group 0 is always "key" for any API */

/* Flags that apply to any field/property */
typedef enum
{
    BCMOLT_FIELD_FLAGS_NONE          = 0,
    BCMOLT_FIELD_FLAGS_RESERVED      = 1 << 0, /* field is reserved (not in use) */
    BCMOLT_FIELD_FLAGS_READ_ONLY     = 1 << 1, /* field is read-only */
    BCMOLT_FIELD_FLAGS_OPTIONAL_FLAG = 1 << 2, /* field is the boolean 'xx is set' for the following optional field */
    BCMOLT_FIELD_FLAGS_DEVICE_ID     = 1 << 3, /* field represents a device ID */
    BCMOLT_FIELD_FLAGS_INTERFACE_ID  = 1 << 4, /* field represents a PON interface ID */
} bcmolt_field_flags;

/* Base data types */
typedef enum
{
    BCMOLT_BASE_TYPE_ID_SNUM,         /* signed number */
    BCMOLT_BASE_TYPE_ID_UNUM,         /* unsigned number */
    BCMOLT_BASE_TYPE_ID_UNUM_HEX,     /* unsigned number printed in hex */
    BCMOLT_BASE_TYPE_ID_FLOAT,        /* floating-point number */
    BCMOLT_BASE_TYPE_ID_BOOL,         /* boolean (zero=no, nonzero=yes) */
    BCMOLT_BASE_TYPE_ID_STRING,       /* string */
    BCMOLT_BASE_TYPE_ID_IPV4,         /* IPv4 address */
    BCMOLT_BASE_TYPE_ID_IPV6,         /* IPv6 address */
    BCMOLT_BASE_TYPE_ID_MAC,          /* MAC address */
    BCMOLT_BASE_TYPE_ID_ENUM,         /* enum */
    BCMOLT_BASE_TYPE_ID_ENUM_MASK,    /* bitmask enum */
    BCMOLT_BASE_TYPE_ID_STRUCT,       /* struct */
    BCMOLT_BASE_TYPE_ID_UNION,        /* union */
    BCMOLT_BASE_TYPE_ID_ARR_DYN,      /* dynamically-sized array */
    BCMOLT_BASE_TYPE_ID_ARR_FIXED,    /* fixed-size array */
    BCMOLT_BASE_TYPE_ID_BINARY_DYN,   /* dynamically-sized binary string (32 bits of length + byte buffer) */
    BCMOLT_BASE_TYPE_ID_BINARY_FIXED, /* fixed-size binary string (byte buffer) */
} bcmolt_base_type_id;

typedef struct bcmolt_type_descr bcmolt_type_descr;

/* Constant indicating that a field has no field ID.
 * Used when no containing presence mask exists, or when the field is special, such as a presence mask itself. */
#define BCMOLT_FIELD_DESCR_ID_NONE 0xFF

/* Field/property descriptor */
typedef struct
{
    const char *name;               /* Field name */
    const char *descr;              /* Field description */
    const char *cli_name;           /* Short CLI name - can be missing */
    bcmolt_meta_id id;              /* Field persistent ID number (or top-level property ID number) */
    uint32_t tags;                  /* Bitmask of tags that apply to this field */
    uint16_t offset;                /* Offset from the beginning of the structure */
    const bcmolt_type_descr *type;  /* Field type */
    bcmolt_field_flags flags;       /* Per-field flags */
} bcmolt_field_descr;

#define BCMOLT_TYPE_DESCR_NO_MASK 0xFFFF /* No presence mask/index mask exists for this struct/array */

/* Data type descriptor */
struct bcmolt_type_descr
{
    const char *name;               /* Type name */
    const char *descr;              /* Type description - can be missing */
    const char *cli_name;           /* Short CLI name - can be missing */
    bcmolt_base_type_id base_type;  /* Base type: snum, unum, string, ip, enum, etc */
    uint32_t min_val;               /* Min value for range check */
    uint32_t max_val;               /* Max value for range check */
    uint16_t size;                  /* Size (calculated with sizeof) */
    uint16_t mask_offset;           /* Offset from the start of a the data to its presence mask/index mask.
                                       Will be set to BCMOLT_TYPE_DESCR_NO_MASK if no mask is present. */

    /* The following union is qualified by the base_type and contains additional info for specific base types */
    union
    {
        struct
        {
            const bcmolt_type_descr *base_type;      /* Enum base numeric type */
            const bcmolt_enum_val *vals;             /* Enum value array - the last value has name=NULL */
        } e;
        struct
        {
            uint16_t num_fields;                     /* Number of elements in the following structure */
            const bcmolt_field_descr *fields;        /* Structure field array - contains num_elements values */
        } s;
        struct
        {
            uint16_t num_common_fields;              /* Number of non-union fields at the start of the struct */
            const bcmolt_field_descr *common_fields; /* Common field array - contains num_elements values */
            uint16_t classifier_idx;                 /* Index of the classifier field within common_fields */
            const bcmolt_field_descr *union_fields;  /* Sub-struct fields under the union (name == NULL if no fields
                                                        present, one per enum entry in the classifier type, plus one
                                                        for default) */
        } u;
        struct
        {
            const bcmolt_type_descr *elem_type;      /* Array element type */
            const bcmolt_type_descr *len_type;       /* Length field numeric type */
            uint16_t len_offset;                     /* Offset of the length field within the container struct */
            uint16_t data_offset;                    /* Offset of the array data within the container struct */
            uint16_t max_size;                       /* Max array size */
            bcmos_bool is_array_backend;             /* Is the backend an array pre-allocated to max size? */
        } arr_dyn;
        struct
        {
            const bcmolt_type_descr *elem_type;      /* Array element type */
            uint16_t size;                           /* Fixed array size */
            uint16_t data_offset;                    /* Offset of the actual array within the container struct */
        } arr_fixed;
        struct
        {
            uint16_t len_offset;                     /* Offset of the length field within the container struct */
            uint16_t data_offset;                    /* Offset of the actual pointer within the container struct */
        } binary_dyn;
        struct
        {
            uint16_t len;                            /* Fixed binary string length */
            uint16_t data_offset;                    /* Offset of the actual array within the container struct */
        } binary_fixed;
    } x;
};

/* Multi-object group descriptor. */
typedef struct
{
    uint32_t container_size;                  /* Size of the multi-object key/data container struct */
    uint32_t key_offset;                      /* Offset of the 'key' field */
    uint32_t next_key_offset;                 /* Offset of the 'next_key' field */
    uint32_t filter_offset;                   /* Offset of the 'filter' field */
    uint32_t request_offset;                  /* Offset of the 'request' field */
    uint32_t more_offset;                     /* Offset of the 'more' field */
    uint32_t num_responses_offset;            /* Offset of the 'num_responses' field */
    uint32_t responses_offset;                /* Offset of the 'responses' field */
} bcmolt_multi_group_descr;

/* Object group descriptor (e.g. cfg or a single operation). */
typedef struct
{
    const bcmolt_type_descr *type;            /* Generic struct type descriptor (name, size, fields, etc) */
    const char *name;                         /* Group name */
    const char *descr;                        /* Group description */
    bcmolt_meta_id obj_id;                    /* Object persistent ID number */
    bcmolt_mgt_group mgt_group;               /* Message group type */
    bcmolt_meta_id id;                        /* Group ID number (unique persistent ID for all groups in the object) */
    uint8_t subgroup_idx;                     /* Subgroup index (relative to group type) */
    uint32_t global_id;                       /* Global group ID (combined object/group type/subgroup) */
    uint32_t tags;                            /* Bitmask of tags that apply to this group */
    uint32_t container_size;                  /* Size of the key/data container struct (0 for key groups) */
    uint32_t key_size;                        /* Size of the 'key' top-level field */
    uint32_t key_offset;                      /* Offset of the 'key' top-level field */
    uint32_t data_size;                       /* Size of the 'data' top-level field */
    uint32_t data_offset;                     /* Offset of the 'data' top-level field */
    const bcmolt_multi_group_descr *multi;    /* Descriptor for the group's multi-object container (if there is one) */
} bcmolt_group_descr;

/* Function that determines which tags are active, based on object key plus system state. */
typedef uint32_t (*bcmolt_get_active_tags_cb)(bcmolt_oltid olt, const void *obj_key);

/* Object descriptor */
typedef struct
{
    const char *name;                          /* Object name */
    const char *descr;                         /* Object description */
    bcmolt_meta_id id;                         /* Object persistent ID number */
    uint32_t tags;                             /* Bitmask of tags that apply to this object */
    bcmolt_get_active_tags_cb get_active_tags; /* Function to determine which tags are active based on system state */
    uint16_t num_groups;                       /* Number of groups in 'groups' */
    const bcmolt_group_descr **groups;         /* All groups under this object (cfg, operations, etc) */
} bcmolt_obj_descr;

/* Metadata tag descriptor */
typedef struct
{
    uint32_t id;                               /* Tag ID number */
    const char *name;                          /* Tag name */
} bcmolt_tag_descr;

/** Check if an enum has a string value given its internal value.
 * \param[in] table Enum table.
 * \param[in] value Internal value.
 * \param[out] enum_str enum string value internal value is valid.
 * \return BCM_ERR_NOENT if internal value is invalid.
 */
static inline bcmos_errno bcmolt_enum_stringval_check(
    const bcmolt_enum_val table[],
    bcmolt_enum_number value,
    const char **enum_str)
{
    while (table->name)
    {
        if (table->val == value)
        {
            *enum_str = table->name;
            return BCM_ERR_OK;
        }
        ++table;
    }
    return BCM_ERR_NOENT;
}

/** Get enum's string value given its internal value.
 * \param[in] table Enum table.
 * \param[in] value Internal value.
 * \return enum string value or the string "<NULL>" if internal value is invalid.
 */
static inline const char *bcmolt_enum_stringval(const bcmolt_enum_val table[], bcmolt_enum_number value)
{
    const char *enum_str;
    bcmos_errno err = bcmolt_enum_stringval_check(table, value, &enum_str);
    if (BCM_ERR_OK != err)
    {
        return "<NULL>";
    }
    return enum_str;
}

/** Convert an enum value to the corresponding string (this relies on x_string_table existing for type x). */
#define BCMOLT_ENUM_STRING_VAL(enum_name, value) \
    bcmolt_enum_stringval(enum_name ## _string_table, (value))

/* Calculate number of enum values. */
int bcmolt_get_num_enum_vals(const bcmolt_enum_val *vals);

/* Common type descriptors for common/primitive types. */
extern const bcmolt_type_descr type_descr_uint8_t;
extern const bcmolt_type_descr type_descr_uint16_t;
extern const bcmolt_type_descr type_descr_uint32_t;
extern const bcmolt_type_descr type_descr_uint64_t;
extern const bcmolt_type_descr type_descr_uint8_t_hex;
extern const bcmolt_type_descr type_descr_uint16_t_hex;
extern const bcmolt_type_descr type_descr_uint32_t_hex;
extern const bcmolt_type_descr type_descr_uint64_t_hex;
extern const bcmolt_type_descr type_descr_int8_t;
extern const bcmolt_type_descr type_descr_int16_t;
extern const bcmolt_type_descr type_descr_int32_t;
extern const bcmolt_type_descr type_descr_int64_t;
extern const bcmolt_type_descr type_descr_float;
extern const bcmolt_type_descr type_descr_double;
extern const bcmolt_type_descr type_descr_bcmos_mac_address;
extern const bcmolt_type_descr type_descr_bcmos_ipv4_address;
extern const bcmolt_type_descr type_descr_bcmos_ipv6_address;
extern const bcmolt_type_descr type_descr_bcmos_bool;

#endif
