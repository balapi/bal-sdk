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

#ifndef BCMTR_DEBUG_H_
#define BCMTR_DEBUG_H_

#include <bcm_config.h>
#include <bcmolt_msg_pack.h>
#include <bcmtr_header.h>
#include <bcmcli.h>

/* CLD stands for capture,log,debug */

/** Capture, log, debug type */
typedef enum
{
    BCMTR_CLD_NONE      = 0,            /**< Off */
    BCMTR_CLD_CAPTURE   = 0x01,         /**< Message capture */
    BCMTR_CLD_LOG       = 0x02,         /**< Message logging */
    BCMTR_CLD_DUMP_HDR  = 0x04,         /**< Message header dump */
    BCMTR_CLD_DUMP      = 0x0C,         /**< Message header and body dump */
    BCMTR_CLD_CLI       = 0x10,         /**< Message CLI command */
} bcmtr_cld_type;

/** Event type */
typedef enum
{
    BCMTR_CLD_EV_SEND,                  /**< Send message */
    BCMTR_CLD_EV_RECV,                  /**< Receive message */
    BCMTR_CLD_EV_RECV_DISCARD,          /**< Receive message discarded */
    BCMTR_CLD_EV_TIMEOUT,               /**< Request timed out waiting for response */
} bcmtr_cld_event_type;

/** Capture, log, debug filter */
typedef struct
{
    bcmolt_mgt_group group;     /**< Message group. Can be BCMOLT_MGT_GROUP_ANY */
    bcmolt_obj_id object;       /**< Object. Can be BCMOLT_OBJECT_ANY */
    uint16_t subgroup;          /**< Message subgroup. Can be BCMOLT_SUBGROUP_ANY */
} bcmtr_cld_filter;

/** Initialize transport capture,log, debug service
 * \param[in]   parent  Parent CLI directory. Can be NULL
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_cld_init(bcmcli_session *session);

/** Clean up transport capture, log, debug service
 */
void bcmtr_cld_exit(void);

/** Set capture, log, debug for selected messages
 * \param[in]   device          Device id
 * \param[in]   filter          Message filter
 * \param[in]   cld_level       Capture, log, debug level. Can be a combination of BCMTR_CLD_.. constants
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_cld_level_set(bcmolt_devid device, const bcmtr_cld_filter *filter, bcmtr_cld_type cld_level);

/** Get capture, log, debug for selected message
 * \param[in]   device          Device id
 * \param[in]   filter          Message filter. Wildcards are not allowed.
 * \param[out]  cld_level       Capture, log, debug level
 * \returns BCM_ERR_OK or error code
 */
bcmos_errno bcmtr_cld_level_get(bcmolt_devid device, const bcmtr_cld_filter *filter, bcmtr_cld_type *cld_level);

/*
 * Message capture functions
 */

/**
 * Message capture facility allows capturing messages between the host
 * and OLT at real time. The recorded trace can be dumped in
 * human readable format or "played back" in order to reproduce
 * the configuration under test.
 * @{
 */

/** Minimal trace buffer size (bytes) */
#define BCMTR_CAPTURE_MIN_BUF_SIZE          (16*1024)

/** Capture buffer configuration parameters */
typedef struct bcmtr_capture_parm
{
    uint32_t size;              /**< Capture buffer size. Must be at least \ref BCMTR_CAPTURE_MIN_BUF_SIZE bytes */
    void *ptr;                  /**< Optional capture buffer pointer. Allocated automatically if NULL */
    bcmos_bool stop_on_full;    /**< TRUE-stop recording when buffer is full. FALSE=circular buffer */
    bcmos_bool activate;        /**< Auto-activate capture immediately after init */
} bcmtr_capture_parm;

/** Capture info record */
typedef struct bcmtr_capture_info
{
    uint32_t size;              /**< Capture buffer size */
    uint32_t used;              /**< Used bytes */
    uint32_t wa;                /**< Number of times capture buffer wrapped around */
    uint32_t msgs;              /**< Number of complete messages stored in the capture buffer */
    uint32_t lost;              /**< Number of messages lost due to buffer overflow */
} bcmtr_capture_info;

/* Capture entry header
 *
 * Followed by msg_size bytes of message data
 */
typedef struct
{
    uint32_t msg_size;          /**< Message size (bytes); MUST be the first member */
    uint32_t event;             /**< bcmtr_cld_event_type event */
    uint32_t timestamp;         /**< Message timestamp (us) */
    /* Followed by message data padded to the nearest 4 bytes */
} bcmtr_capture_entry;

/** Initialize capture buffer
 *
 * This function must be called first.
 * \param[in]   olt     Olt index
 * \param[in]   cfg     Capture configuration parameters
 * \return 0=success or error code
 */
bcmos_errno bcmtr_capture_init(bcmolt_devid olt, const bcmtr_capture_parm *parm);

/** Destroy capture buffer
 *
 * Destroy buffer initialized by bcmtr_capture_Init().
 * \param[in]   olt     Olt index
 * Following this call all recording is lost.
 */
void bcmtr_capture_destroy(bcmolt_devid olt);

/** Get capture recording info
 *
 * \param[in]   olt     Olt index
 * \param[out]  info    Capture information
 * \return 0=success or error code
 */
bcmos_errno bcmtr_capture_info_get(bcmolt_devid olt, bcmtr_capture_info *info);

/** Get the number of readable bytes in the capture buffer
 *
 * \param[in]   olt             OLT index
 * \param[out]  size            Number of readable bytes
 */
bcmos_errno bcmtr_capture_size_get(bcmolt_devid olt, uint32_t *size);

/** Read portion of capture
 *
 * This function reads recorded data into a user buffer starting at the specified offset from the beginning of the
 * capture up to the specified length. Applications can use this function in order to save capture into file or dump it.
 *
 * \param[in]   olt             OLT index
 * \param[out]  buf             User buffer
 * \param[in]   offset          Buffer offset to start read (bytes)
 * \param[in/out]  length       in: Maximum number of bytes to read into the user buffer
 *                              out: Remaining unused bytes in user buffer
 * \return 0=success or error code
 */
bcmos_errno bcmtr_capture_read(bcmolt_devid olt, uint8_t *buf, uint32_t offset, uint32_t *length);

/** Advance buffer to next capture entry
 *
 * Helper function used to scan buffer read by bcmtr_capture_read()
 *
 * \param[in/out]   buf         Capture buffer
 * \param[out]      hdr         Capture entry header
 * \param[out]      msg         Pointer to packed message
 */
bcmos_bool bcmtr_capture_entry_get_next(bcmolt_buf *buf, bcmtr_capture_entry *hdr, uint8_t **msg);

/** Decode and dump capture recording
 *
 * This function interprets and dumps capture recording.
 *
 * \param[in]   session CLI session
 * \param[in]   olt     OLT index
 * \param[out]  nmsgs   Number of messages dumped
 * \return 0=success or error code
 */
bcmos_errno bcmtr_capture_dump(bcmcli_session *session, bcmolt_devid olt, uint32_t *nmsgs);

/** (Re)start / Suspend capture recording
 *
 * \param[in]   olt     OLT index
 * \param[in]   start   TRUE=start, FALSE=suspend
 * \return 0=success or error code
 */
bcmos_errno bcmtr_capture_start_stop(bcmolt_devid olt, bcmos_bool start);

/** Are we actively capturing?
 *
 * \param[in]   olt     OLT index
 * \return TRUE=actively capturing, FALSE=NOT capturing
 */
bcmos_bool bcmtr_capture_is_active(bcmolt_devid olt);

/** Convert entry to platform specific format
 *
 * \param[in/out]   buf     Capture buffer
 * \param[out]      entry   Capture entry header
 *
 * \return TRUE if success, FALSE otherwise
 */
bcmos_bool bcmtr_capture_entry_unpack(bcmolt_buf *buf, bcmtr_capture_entry *entry);

/*
 * Internal functions - called from transport level
 */

/* Per-OLT, per-command combined trace,log,debug level */
extern bcmtr_cld_type bcmtr_cld_active_level[BCMTR_MAX_DEVICES][BCMOLT_API_GROUP_ID__NUM_OF];

/* Notify message.
 * Called by transport layer
 */
void bcmtr_cld_notify(bcmolt_devid device, bcmtr_cld_type level, const bcmtr_hdr *hdr,
    bcmtr_cld_event_type ev, uint32_t ts, const uint8_t *packed, uint32_t packed_length,
    bcmolt_msg *msg);

/* Check if CLD is enabled for the message and record if yes
 * Called by transport layer
 */
#define BCMTR_CLD_CHECK_NOTIFY(_device, _hdr, _ev, _ts, _packed, _packed_length, _msg) \
    do {\
        const bcmolt_group_descr *_group_descr;\
        bcmos_errno _err = bcmolt_api_group_descr_get_by_group_id((_hdr)->obj, (_hdr)->group_id, &_group_descr);\
        if (_err == BCM_ERR_OK && bcmtr_cld_active_level[_device][_group_descr->global_id]) \
        { \
            bcmtr_cld_notify(_device, bcmtr_cld_active_level[_device][_group_descr->global_id],\
                _hdr, _ev, _ts, _packed, _packed_length, _msg); \
        } \
    } while (0)

#endif /* BCMTR_DEBUG_H_ */
