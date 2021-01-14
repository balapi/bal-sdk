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

#ifndef BCMOLT_MSG_H_
#define BCMOLT_MSG_H_

#include "bcmos_system.h"
#include "bcmolt_presence_mask.h"
#include "bcmolt_mgt_group.h"
#include "bcmolt_buf.h"
#include "bcmolt_system_types.h"
#include "bcmolt_api_model_supporting_enums.h"

/** \defgroup \api_data_types Data Types
 * \ingroup api
 * @{
 */

/** Message direction - request or response */
typedef enum bcmolt_msg_dir
{
    BCMOLT_MSG_DIR_REQUEST,
    BCMOLT_MSG_DIR_RESPONSE
} bcmolt_msg_dir;

/** Message type. Can be a combination of flags */
typedef enum bcmolt_msg_type
{
    BCMOLT_MSG_TYPE_GET  = 0x01,        /**< Get: configuration or statistics */
    BCMOLT_MSG_TYPE_SET  = 0x02,        /**< Set: Configuration, Statistics, Auto, Proxy */
    BCMOLT_MSG_TYPE_CLEAR= 0x04,        /**< Clear: configuration */
    BCMOLT_MSG_TYPE_MULTI= 0x08,        /**< Multi-object: configuration, statistics */

    BCMOLT_MSG_TYPE_GET_MULTI = BCMOLT_MSG_TYPE_GET | BCMOLT_MSG_TYPE_MULTI,
} bcmolt_msg_type;

/** Any object */
#define BCMOLT_OBJECT_ANY       (bcmolt_obj_id)0xffff

/** Any group */
#define BCMOLT_MGT_GROUP_ANY    (bcmolt_mgt_group)0xffff

/** Any subgroup */
#define BCMOLT_SUBGROUP_ANY     0

/** Max error text length */
#define BCMOLT_MAX_ERR_TEXT_LENGTH      256

/* Transport sub-channel handle */
typedef uint16_t bcmolt_subchannel;
#define BCMOLT_SUBCHANNEL_UNDEFINED     0xffff

/** Common message header */
typedef struct bcmolt_msg
{
    bcmolt_obj_id        obj_type;      /**< Object type */
    bcmolt_mgt_group     group;         /**< Management group */
    uint16_t             subgroup;      /**< Subgroup: for operations, autonomous messages, proxy */
    bcmolt_msg_type      type;          /**< Set, Get, Clear */
    bcmolt_msg_dir       dir;           /**< Request/autonomous or Response */
    bcmos_errno          err;           /**< Remote error code */
    uint16_t             corr_tag;      /**< Correlation tag */
    char                 err_text[BCMOLT_MAX_ERR_TEXT_LENGTH];  /**< Error text - if err != 0 */
    bcmolt_loid          loid;          /**  Logical OLT id */
    /* The following fields are internal. They are not sent on the line */
    bcmolt_devid         device;        /*   Device id */
    bcmolt_subchannel    subch;         /*   Transport sub-channel via which the message arrived */
    bcmos_msg            os_msg;        /*   Internal OS message for easy task routing */
    uint32_t             timestamp;     /*   Timestamp when the message has been transmitted/received */
    void                *list_buf;      /*   Memory buffer in which to store variable-sized lists when unpacking */
    uint32_t             list_buf_size; /*   Number of bytes in the variable-sized list buffer */
} bcmolt_msg;

/** Configuration group message header */
typedef struct bcmolt_cfg
{
    bcmolt_msg hdr;             /** Common header */
} bcmolt_cfg;

/** Statistic flags */
typedef enum
{
    BCMOLT_STAT_FLAGS_NONE          = 0x0000, /**< No statistics options set (no clear on read, etc) */
    BCMOLT_STAT_FLAGS_CLEAR_ON_READ = 0x0001, /**< Clear the requested statistics as part of the read operation */
} bcmolt_stat_flags;

/** Statistics group message header */
typedef struct bcmolt_stat
{
    bcmolt_msg hdr;             /** Common header */
} bcmolt_stat;

/** Statistics configuration message header */
typedef struct bcmolt_stat_cfg
{
    bcmolt_msg hdr;             /** Common header */
} bcmolt_stat_cfg;

/** Operation group message header */
typedef struct bcmolt_oper
{
    bcmolt_msg hdr;             /** Common header */
} bcmolt_oper;

/** Autonomous message header */
typedef struct bcmolt_auto
{
    bcmolt_msg hdr;             /** Common header */
} bcmolt_auto;

/** Autonomous message configuration header */
typedef struct bcmolt_auto_cfg
{
    bcmolt_msg hdr;             /** Common header */
} bcmolt_auto_cfg;

/** Message handler */
typedef void (*f_bcmolt_msg_handler)(bcmolt_oltid olt, bcmolt_msg *msg);

/** Autonomous message flags */
typedef enum
{
    BCMOLT_AUTO_FLAGS_NONE      = 0,            /**< Invoke callback in context of RX task */
    BCMOLT_AUTO_FLAGS_DISPATCH  = 0x0001,       /**< Dispatch message to application module */
} bcmolt_auto_flags;

/** Filter flags */
typedef enum
{
    BCMOLT_FILTER_FLAGS_NONE             = 0,
    BCMOLT_FILTER_FLAGS_INVERT_SELECTION = 0x00000001,   /** Return objects NOT selected by filter */
    BCMOLT_FILTER_FLAGS_DISABLE_FILTER   = 0x00000002,   /** Disable the filter entirely */
} bcmolt_filter_flags;

/** Common header for multi-object API messages */
typedef struct bcmolt_multi_msg
{
    bcmolt_msg hdr;                     /**< Common header */
    uint16_t max_responses;             /**< Max number of responses per call - set on creation and doesn't change */
    bcmolt_filter_flags filter_flags;   /**< Filter flags */
} bcmolt_multi_msg;

/** Multi-object configuration group message header */
typedef struct bcmolt_multi_cfg
{
    bcmolt_multi_msg hdr;               /** Common header */
} bcmolt_multi_cfg;

/** Multi-object statistics group message header */
typedef struct bcmolt_multi_stat
{
    bcmolt_multi_msg hdr;               /** Common header */
} bcmolt_multi_stat;

/** @} */

/** Dynamically allocate an API message.
 * If bcmolt_msg_mem_pool_set has been called, this will use a byte pool. Otherwise, it will use bcmos_calloc.
 *
 * \param   The number of bytes in the full message.
 * \returns The newly allocated message, or NULL if no memory is available.
 */
bcmolt_msg *bcmolt_msg_alloc(uint32_t size);

/** Dynamically allocate a multi-object API structure.
 * If bcmolt_msg_mem_pool_set has been called, this will use a byte pool. Otherwise, it will use bcmos_calloc.
 *
 * \param[in]   obj_id         Object ID
 * \param[in]   group          Management group
 * \param[in]   subgroup       Subgroup index (for statistics)
 * \param[in]   key            Pointer to object key
 * \param[in]   max_responses  Maximum number of response objects per API call
 * \returns API message structure including memory for all response messages, or NULL if alloc failed.
 */
bcmolt_multi_msg *bcmolt_multi_msg_alloc(
    bcmolt_obj_id obj_id,
    bcmolt_mgt_group group,
    uint16_t subgroup,
    const void *key,
    uint16_t max_responses);

/** Release message that was allocated with bcmolt_msg_alloc.
 */
void bcmolt_msg_free(bcmolt_msg *msg);

/** Release message that was allocated with bcmolt_multi_msg_alloc.
 */
void bcmolt_multi_msg_free(bcmolt_multi_msg *msg);

/** Initialize the memory pool to be used for dynamic allocation of API messages. If this is not called, dynamic
 * message allocation (e.g. via bcmolt_msg_unpack) will use bcmos_calloc.
 *
 * \param parms Parameters for the byte pool to use for all dynamic API message allocation (size, etc).
 */
void bcmolt_msg_mem_pool_set(const bcmos_byte_pool_parm *parms);

/** Clones a message by packing it to a buffer then unpacking it into the destination message.
 * This uses bcmolt_msg_unpack, so if *dest is NULL, memory will by allocated dynamically using bcmolt_msg_calloc.
 *
 * \param dest A pointer to the location in memory that will hold the cloned message.
 * \param src The message that should be copied.
 * \return An error code or BCM_ERR_OK for success.
 */
bcmos_errno bcmolt_msg_clone(bcmolt_msg **dest, bcmolt_msg *src);

static inline void bcmolt_os_msg_release_cb(bcmos_msg *os_msg)
{
    bcmolt_msg *msg = (bcmolt_msg *)os_msg->data;

    /* We can be here if target module or transport queue overflows.
       Release the message
    */
    bcmolt_msg_free(msg);
}

static inline bcmos_module_id bcmos_module_id_for_device(bcmos_module_id module, bcmolt_devid devid)
{
    return (bcmos_module_id)((int)module + devid);
}
#endif
