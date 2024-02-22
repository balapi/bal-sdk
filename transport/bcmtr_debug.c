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
#include <bcmcli_session.h>
#include <bcmolt_api_metadata.h>
#include <bcmolt_api_utils.h>
#include <bcmolt_math.h>
#include <bcmolt_api_writer.h>

#ifdef ENABLE_LOG
#include <bcm_dev_log.h>
#endif

#ifdef ENABLE_CLI
#include <bcmtr_debug_cli.h>
#endif
#include <bcm_api_cli.h>

/* Messages are recorded in the following format:
 * uint32_t - event type
 * uint32_t - timestamp
 * uint32_t - message data size
 * <message data> - padded to the nearest 4 bytes
 * uint32_t - total size - total capture entry size, including control info
 */

/* Overhead size: entry header + uint32_t suffix */
#define BCMTR_CAPTURE_OVERHEAD_SIZE  (sizeof(bcmtr_capture_entry) + sizeof(uint32_t))

#define BCMTR_CAPTURE_ENTRY_FIELDS  (sizeof(bcmtr_capture_entry) / sizeof(uint32_t))

/* Maximum total number of characters for a message dump */
#define BCMTR_MAX_MSG_DUMP_STR_SIZE 4096

/* Capture control block */
typedef struct
{
    bcmtr_capture_parm parm;            /* Capture configuration */
    bcmos_bool active;

    uint8_t *start;
    uint8_t *end;
    uint8_t *cur;
    uint32_t size;                      /* Buffer size */
    uint32_t used;                      /* Bytes used */
    uint32_t wa;                        /* Number of times buffer wrapped around */
    uint32_t events;                    /* Number of capture events */
} bcmtr_capture_buf;

static bcmtr_capture_buf capture_buf[BCMTR_MAX_DEVICES];

/* CLI session where to dump */
static bcmcli_session *bcmtr_cld_session;

#ifdef ENABLE_LOG
/* Logger used for BCMTR_CLD_LOG */
static dev_log_id bcmtr_cld_log_id;
#endif

/* Global variable: per msg_id CLD level */
bcmtr_cld_type bcmtr_cld_active_level[BCMTR_MAX_DEVICES][BCMOLT_API_GROUP_ID__NUM_OF][BCMTR_CLD_MSG_TYPE__NUM_OF];

/* Create a dummy CLI session so we can print to a buffer internally before printing to the real CLI.
 * This way, the output can't be interrupted by another print. */
#ifdef ENABLE_CLI
static char bcmtr_cld_scratch_buf[BCMTR_MAX_MSG_DUMP_STR_SIZE];
static uint32_t bcmtr_cld_scratch_pos = 0;

#ifndef CONFIG_AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT
/* If 'bcmtr_cld_scratch_buf' is accessed directly as in bcmtr_cld_output_to_dev_log() and not from bcmcli_session context, it is not mutex protected.
 * That is why we add the 'bcmtr_cld_scratch_buf_mutex'. */
static bcmos_mutex bcmtr_cld_scratch_buf_mutex;
#endif
#endif
static bcmcli_session *bcmtr_cld_scratch_session;

/*
 * Internal functions
 */

#ifdef ENABLE_CLI
/* CLI session print callback for the scratch buffer */
static int bcmtr_log_cli_print(bcmcli_session *session, const char *buf, uint32_t size)
{
#ifndef CONFIG_AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT
    bcmos_mutex_lock(&bcmtr_cld_scratch_buf_mutex);
#endif

    size = MIN(size, BCMTR_MAX_MSG_DUMP_STR_SIZE - bcmtr_cld_scratch_pos);
    if (size > 0)
    {
        memcpy(&bcmtr_cld_scratch_buf[bcmtr_cld_scratch_pos], buf, size);
    }
    bcmtr_cld_scratch_pos += size;
    
#ifndef CONFIG_AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT
    bcmos_mutex_unlock(&bcmtr_cld_scratch_buf_mutex);
#endif
    return size;
}
#endif

/* Get message event name */
static inline const char *bcmtr_cld_event_name(bcmtr_cld_event_type ev)
{
    static const char *ev_name[] = {
        [BCMTR_CLD_EV_SEND]     = "tx",
        [BCMTR_CLD_EV_RECV]     = "rx",
        [BCMTR_CLD_EV_RECV_DISCARD] = "rx-discard",
        [BCMTR_CLD_EV_TIMEOUT] = "timeout"
    };
    return ev_name[ev];
}

/* Store data in capture buffer */
static inline void _bcmtr_capture_store(bcmtr_capture_buf *tb, const void *data, uint32_t size)
{
    int32_t left = (int32_t)(tb->end - tb->cur);
    if (left >= (int32_t)size)
    {
        memcpy(tb->cur, data, size);
        tb->cur += size;
    }
    else
    {
        memcpy(tb->cur, data, left);
        memcpy(tb->start, (const uint8_t *)data + left, size - left);
        tb->cur = tb->start + size - left;
        ++tb->wa;
    }
    tb->used += size;
    if (tb->used > tb->size)
        tb->used = tb->size;
}


/* Get capture entry size and start pointer given pointer right after the entry */
static void _bcmtr_capture_get_prev(bcmtr_capture_buf *tb, uint8_t *ptr, uint32_t *prev_size, uint8_t **prev_ptr)
{
    uint32_t size;
    uint8_t *prev;

    if (ptr == tb->start)
        ptr = tb->end;
    size = *(((uint32_t *)(long)ptr) - 1);
    BUG_ON(!size || size > 0xffff || (size & 0x3));
    prev = ptr - size;
    if (prev < tb->start)
        prev = tb->end - (size - (ptr - tb->start));
    *prev_size = size;
    *prev_ptr = prev;
}

/* Get number of complete messages stored in capture buffer. Optionally, a pointer to the first
 * record can also be retrieved. */
static uint32_t _bcmtr_capture_nmsgs(bcmtr_capture_buf *tb, uint8_t **start)
{
    uint32_t n = 0;
    uint32_t prev_length;
    uint8_t *prev_start = tb->cur;
    uint8_t *cur_hdr = NULL;
    uint8_t *prev = NULL;

    if (!tb->used)
        return 0;

    /* Unwind capture buffer backward */
    while (n < tb->events)
    {
        prev = prev_start;
        _bcmtr_capture_get_prev(tb, prev, &prev_length, &prev_start);
        if (prev_start >= prev)
            break;
        ++n;
        cur_hdr = prev_start;
    }

    /* If buffer has wrapped around - continue unwinding */
    if (tb->wa)
    {
        prev = prev_start;

        /* Make sure that prev_start is between last previous and current. Otherwise,
         * previous can wrap backwards and become > tb->cur, causing erroneous reads. */
        while ((prev_start >= tb->cur) && (prev_start <= prev))
        {
            prev = prev_start;
            cur_hdr = prev_start;
            _bcmtr_capture_get_prev(tb, prev_start, &prev_length, &prev_start);
            ++n;
        }
    }

    /* start is not a required parameter */
    if (start)
        *start = cur_hdr;

    return n;
}

static inline void _bcmtr_capture_wrap(uint8_t **cur, bcmtr_capture_buf *tb)
{
    if (*cur >= tb->end)
    {
        *cur = tb->start + (*cur - tb->end);
    }
}

static inline uint32_t _bcmtr_capture_msg_size_get(uint8_t *buf)
{
    /* WARNING: do NOT access any members of bcmtr_capture_entry other than msg_size (the first member) as they may
       have been wrapped to the beginning of the buffer. */
    return ((bcmtr_capture_entry *)(long)buf)->msg_size;
}

static void _bcmtr_capture_copy(
    bcmtr_capture_buf *tb,
    uint8_t **dst,
    uint8_t *src,
    uint32_t to_copy,
    uint32_t *remaining)
{
    uint32_t left;

    left = tb->end - src;
    if (left < to_copy)
    {
        memcpy(*dst, src, left);
        memcpy((*dst) + left, tb->start, to_copy - left);
    }
    else
    {
        memcpy(*dst, src, to_copy);
    }
    (*dst) += to_copy;
    (*remaining) -= to_copy;
}

static void _bcmtr_capture_copy_bounded(
    bcmtr_capture_buf *tb,
    uint8_t **dst,
    uint8_t *src,
    uint32_t to_copy,
    uint32_t *remaining,
    uint32_t bound)
{
    if (bound < to_copy)
    {
        src += to_copy - bound;
        to_copy = bound;
    }
    if ((*remaining) < to_copy)
    {
        to_copy = *remaining;
    }
    _bcmtr_capture_copy(tb, dst, src, to_copy, remaining);
}

/* Set capture, log, debug for selected messages */
bcmos_errno bcmtr_cld_level_set(bcmolt_devid device, const bcmtr_cld_filter *filter, bcmtr_cld_type cld_level)
{
    bcmolt_api_group_id msg_id;
    bcmos_errno rc;

    if ((unsigned)device >= BCMTR_MAX_DEVICES || !filter)
    {
        return BCM_ERR_PARM;
    }

    /* Handle wildcard object */
    if (filter->object == BCMOLT_OBJECT_ANY)
    {
        bcmtr_cld_filter f = *filter;

        BCMOLT_API_FOR_EACH_OBJ_ID(f.object)
        {
            bcmtr_cld_level_set(device, &f, cld_level);
        }

        return BCM_ERR_OK;
    }

    /* Handle wildcard group */
    if (filter->group == BCMOLT_MGT_GROUP_ANY)
    {
        bcmtr_cld_filter f = *filter;

        f.subgroup = BCMOLT_SUBGROUP_ANY;
        for (f.group = BCMOLT_MGT_GROUP_CFG; f.group <= BCMOLT_MGT_GROUP__NUM_OF; f.group++)
        {
            bcmtr_cld_level_set(device, &f, cld_level);
        }

        return BCM_ERR_OK;
    }

    /* Handle wildcard subgroup */
    if (filter->group == BCMOLT_MGT_GROUP_ANY ||
        ((filter->group == BCMOLT_MGT_GROUP_AUTO || filter->group == BCMOLT_MGT_GROUP_OPER ||
          filter->group == BCMOLT_MGT_GROUP_STAT || filter->group == BCMOLT_MGT_GROUP_STAT_CFG) &&
         filter->subgroup == BCMOLT_SUBGROUP_ANY))
    {
        bcmtr_cld_filter f = *filter;
        uint16_t subgroup_count = bcmolt_api_group_count_get(f.object, f.group);
        uint16_t count;

        for (f.subgroup = 0, count=0;
             count < subgroup_count;
             ++f.subgroup)
        {
            if (bcmolt_api_group_id_combine(f.object, f.group, f.subgroup, &msg_id) == BCM_ERR_OK)
            {
                bcmtr_cld_level_set(device, &f, cld_level);
                ++count;
            }
        }

        return BCM_ERR_OK;
    }
    
    if (filter->msg_type == BCMTR_CLD_MSG_TYPE_ANY)
    {
        bcmtr_cld_filter f = *filter;

        for (f.msg_type = BCMTR_CLD_MSG_TYPE__BEGIN; f.msg_type < BCMTR_CLD_MSG_TYPE__NUM_OF; f.msg_type++)
            bcmtr_cld_level_set(device, &f, cld_level);

        return BCM_ERR_OK;
    }

    /* If we are here - it is not a wildcard */
    rc = bcmolt_api_group_id_combine(filter->object, filter->group, filter->subgroup, &msg_id);
    if (rc)
        return rc;

    BUG_ON((unsigned)msg_id >= BCMOLT_API_GROUP_ID__NUM_OF);
    bcmtr_cld_active_level[device][msg_id][filter->msg_type] = cld_level;
    return BCM_ERR_OK;
}

/* Get capture, log, debug for selected message */
bcmos_errno bcmtr_cld_level_get(bcmolt_devid device, const bcmtr_cld_filter *filter, bcmtr_cld_type *cld_level)
{
    bcmolt_api_group_id msg_id;
    bcmos_errno rc;

    if ((unsigned)device >= BCMTR_MAX_DEVICES || !filter)
    {
        return BCM_ERR_PARM;
    }
    
    rc = bcmolt_api_group_id_combine(filter->object, filter->group, filter->subgroup, &msg_id);
    if (rc)
        return rc;
    
    BUG_ON((unsigned)msg_id >= BCMOLT_API_GROUP_ID__NUM_OF);
    *cld_level = bcmtr_cld_active_level[device][msg_id][filter->msg_type];
    return BCM_ERR_OK;
}

/** Initialize capture */
bcmos_errno bcmtr_capture_init(bcmolt_devid olt, const bcmtr_capture_parm *parm)
{
    bcmtr_capture_buf *tb;

    if (olt >= BCMTR_MAX_DEVICES || !parm)
        return BCM_ERR_PARM;
    if (capture_buf[olt].start)
    {
        bcmcli_session_print(bcmtr_cld_session, "TRACE/%d: already initialized\n", olt);
        return BCM_ERR_PARM;
    }

    if (parm->size < BCMTR_CAPTURE_MIN_BUF_SIZE)
    {
        bcmcli_session_print(bcmtr_cld_session, "TRACE/%d: capture buffer is too small (%u < %d)\n",
            olt, parm->size, BCMTR_CAPTURE_MIN_BUF_SIZE);
        return BCM_ERR_PARM;
    }

    tb = &capture_buf[olt];
    tb->size = parm->size & ~0x3;
    /* User-supplied or dynamically allocated buffer ? */
    if (parm->ptr)
        tb->start = parm->ptr;
    else
    {
        tb->start = bcmos_alloc(parm->size);
        if (!tb->start)
        {
            bcmcli_session_print(bcmtr_cld_session, "TRACE/%d: can't allocate capture buffer\n", olt);
            tb->size = 0;
            return BCM_ERR_NOMEM;
        }
    }
    tb->end = (void *)((long)tb->start + parm->size);
    tb->cur = tb->start;
    tb->used = tb->wa = 0;
    tb->active = parm->activate;
    tb->parm = *parm;

    return BCM_ERR_OK;
}

/** Destroy capture buffer */
void bcmtr_capture_destroy(bcmolt_devid olt)
{
    bcmtr_capture_buf *tb;

    if (olt >= BCMTR_MAX_DEVICES)
        return;
    tb = &capture_buf[olt];
    tb->active = BCMOS_FALSE;
    if (tb->start && !tb->parm.ptr)
        bcmos_free(tb->start);
    memset(tb, 0, sizeof(*tb));
}

/** Get capture recording info */
bcmos_errno bcmtr_capture_info_get(bcmolt_devid olt, bcmtr_capture_info *info)
{
    bcmtr_capture_buf *tb;

    if (olt >= BCMTR_MAX_DEVICES || !info)
        return BCM_ERR_PARM;
    tb = &capture_buf[olt];
    if (tb->active)
    {
        bcmcli_session_print(bcmtr_cld_session, "TRACE/%d: must stop first\n", olt);
        return BCM_ERR_PARM;
    }
    info->size = tb->size;
    info->used = tb->used;
    info->wa   = tb->wa;
    info->msgs = _bcmtr_capture_nmsgs(tb, NULL);
    info->lost = tb->events - info->msgs;
    return BCM_ERR_OK;
}

bcmos_errno bcmtr_capture_size_get(bcmolt_devid olt, uint32_t *size)
{
    bcmtr_capture_buf *tb;
    uint32_t n = 0;
    uint8_t *cur_hdr = NULL;
    uint32_t i;

    *size = 0;
    if (olt >= BCMTR_MAX_DEVICES)
    {
        return BCM_ERR_PARM;
    }
    tb = &capture_buf[olt];
    if (!tb->start)
    {
        bcmcli_session_print(bcmtr_cld_session, "TRACE/%d: not initialized\n", olt);
        return BCM_ERR_PARM;
    }
    if (tb->active)
    {
        bcmcli_session_print(bcmtr_cld_session, "TRACE/%d: must stop first\n", olt);
        return BCM_ERR_PARM;
    }

    if (!tb->used)
    {
        return BCM_ERR_OK;
    }

    /* Unwind capture buffer backward to get to the 1st recorded message */
    n = _bcmtr_capture_nmsgs(tb, &cur_hdr);

    /* "first" points to the 1st recorded entry and "n" contains number of messages.
     * Now go forward and copy to the user buffer
     */
    BUG_ON(!cur_hdr);
    for (i = 0; i < n; i++)
    {
        uint32_t msg_size = _bcmtr_capture_msg_size_get(cur_hdr) + sizeof(bcmtr_capture_entry);
        uint32_t rounded_size = BCMOS_ROUND_UP(msg_size, sizeof(uint32_t));

        (*size) += msg_size;

        /* Move to the next entry in capture buffer */
        cur_hdr += rounded_size + sizeof(uint32_t);
        _bcmtr_capture_wrap(&cur_hdr, tb);
    }

    return BCM_ERR_OK;
}

bcmos_errno bcmtr_capture_read(bcmolt_devid olt, uint8_t *buf, uint32_t offset, uint32_t *length)
{
    bcmtr_capture_buf *tb;
    uint32_t n = 0;
    uint8_t *cur_hdr = NULL;
    uint32_t cur_offset = 0;
    uint32_t i;

    if (olt >= BCMTR_MAX_DEVICES || !buf)
    {
        return BCM_ERR_PARM;
    }
    tb = &capture_buf[olt];
    if (!tb->start)
    {
        bcmcli_session_print(bcmtr_cld_session, "TRACE/%d: not initialized\n", olt);
        return BCM_ERR_PARM;
    }
    if (tb->active)
    {
        bcmcli_session_print(bcmtr_cld_session, "TRACE/%d: must stop first\n", olt);
        return BCM_ERR_PARM;
    }

    if (!tb->used)
    {
        return BCM_ERR_OK;
    }

    /* Unwind capture buffer backward to get to the 1st recorded message */
    n = _bcmtr_capture_nmsgs(tb, &cur_hdr);

    /* "first" points to the 1st recorded entry and "n" contains number of messages.
     * Now go forward and copy to the user buffer
     */
    BUG_ON(!cur_hdr);
    for (i = 0; (i < n) && ((*length) > 0); i++)
    {
        uint32_t msg_size = _bcmtr_capture_msg_size_get(cur_hdr);
        uint32_t rounded_size = BCMOS_ROUND_UP(msg_size, sizeof(uint32_t));

        cur_offset += sizeof(bcmtr_capture_entry);
        if (cur_offset > offset)
        {
            uint32_t temp[BCMTR_CAPTURE_ENTRY_FIELDS];
            uint8_t j;

            for (j = 0; j < BCMTR_CAPTURE_ENTRY_FIELDS; j++)
            {
                temp[j] = BCMOLT_BUF_ENDIAN_CPU_TO_BUF(U32, *((uint32_t*)(long)cur_hdr));
                cur_hdr += sizeof(uint32_t);
                _bcmtr_capture_wrap(&cur_hdr, tb);
            }

            _bcmtr_capture_copy_bounded(
                tb,
                &buf,
                (uint8_t*)temp,
                sizeof(bcmtr_capture_entry),
                length,
                cur_offset - offset);
        }
        else
        {
            cur_hdr += sizeof(bcmtr_capture_entry);
        }

        cur_offset += msg_size;
        if (cur_offset > offset)
        {
            _bcmtr_capture_copy_bounded(
                tb,
                &buf,
                cur_hdr,
                msg_size,
                length,
                cur_offset - offset);
        }

        /* Move to the next entry in capture buffer */
        cur_hdr += rounded_size + sizeof(uint32_t);
        _bcmtr_capture_wrap(&cur_hdr, tb);
    }

    return BCM_ERR_OK;
}

bcmos_bool bcmtr_capture_entry_get_next(bcmolt_buf *buf, bcmtr_capture_entry *hdr, uint8_t **msg)
{
    bcmos_bool valid;

    BUG_ON(buf == NULL);
    BUG_ON(hdr == NULL);

    valid = bcmtr_capture_entry_unpack(buf, hdr);
    if (msg != NULL)
    {
        *msg = bcmolt_buf_snap_get(buf);
    }
    return valid && bcmolt_buf_skip(buf, hdr->msg_size);
}

#ifdef ENABLE_CLI
/** Decode and dump capture recording */
bcmos_errno bcmtr_capture_dump(bcmcli_session *session, bcmolt_devid olt, uint32_t *nmsgs)
{
    bcmtr_capture_entry hdr;
    uint8_t *msg_start;
    bcmolt_buf buf;
    uint8_t *data;
    uint32_t length;
    uint32_t remaining;
    bcmos_errno rc;

    rc = bcmtr_capture_size_get(olt, &length);
    if (rc != BCM_ERR_OK)
        return rc;

    bcmos_dynamic_memory_allocation_blocking_suspend();

    /* Allocate temp buffer and read data into it */
    data = bcmos_calloc(length);

    bcmos_dynamic_memory_allocation_blocking_resume();
    
    if (data == NULL)
    {
        bcmcli_session_print(session, "TRACE/%d: no memory\n", olt);
        return BCM_ERR_NOMEM;
    }

    remaining = length;
    rc = bcmtr_capture_read(olt, data, 0, &remaining);
    if (BCM_ERR_OK != rc)
    {
        bcmos_free(data);
        return rc;
    }

    /* Dump */
    bcmolt_buf_init(&buf, length - remaining, data);
    while (bcmtr_capture_entry_get_next(&buf, &hdr, &msg_start))
    {
        bcmolt_buf msg_buf;
        bcmolt_msg *msg = NULL;
        bcmos_errno err;

        bcmcli_session_print(session, "\n%08x %s:\n", hdr.timestamp, bcmtr_cld_event_name((bcmtr_cld_event_type)hdr.event));
        bcmolt_buf_init(&msg_buf, hdr.msg_size, msg_start);
        err = bcmolt_msg_unpack(&msg_buf, &msg);
        if (BCM_ERR_OK == err)
        {
            (void)apicli_msg_dump(session, olt, msg);
            bcmolt_msg_free(msg);
        }
        else
        {
            bcmcli_session_hexdump(session, msg_start, 0, hdr.msg_size, NULL);
        }
    }

    bcmos_free(data);

    *nmsgs = _bcmtr_capture_nmsgs(&capture_buf[olt], NULL);

    return BCM_ERR_OK;
}
#endif

/** (Re)start / Suspend capture recording */
bcmos_errno bcmtr_capture_start_stop(bcmolt_devid olt, bcmos_bool start)
{
    if (olt >= BCMTR_MAX_DEVICES)
        return BCM_ERR_PARM;
    if (!capture_buf[olt].start && start)
    {
        bcmcli_session_print(bcmtr_cld_session,
            "TRACE/%d: Can't start recording - must initialize first\n", olt);
        return BCM_ERR_PARM;
    }
    capture_buf[olt].active = start;
    return BCM_ERR_OK;
}

bcmos_bool bcmtr_capture_is_active(bcmolt_devid olt)
{
    return capture_buf[olt].active;
}

bcmos_bool bcmtr_capture_entry_unpack(bcmolt_buf *buf, bcmtr_capture_entry *entry)
{
    return
        bcmolt_buf_read_u32(buf, &entry->msg_size) &&
        bcmolt_buf_read_u32(buf, &entry->event) &&
        bcmolt_buf_read_u32(buf, &entry->timestamp);
}

/* Notify message to capture module - called from the transport layer */
static void bcmtr_capture_notify(bcmolt_devid device, const bcmtr_hdr *trhdr,
    bcmtr_cld_event_type ev, uint32_t ts,
    const void *packed, uint32_t packed_length, bcmolt_msg *msg)
{
    bcmtr_capture_buf *tb;
    bcmtr_capture_entry hdr;
    uint32_t rounded_size;

    tb = &capture_buf[device];

    /* Sanity */
    if (!packed)
        return;
    hdr.msg_size = packed_length;
    /* Enable & overflow checks */
    if (!tb->active)
        return;
    if (tb->parm.stop_on_full && (tb->used + hdr.msg_size + BCMTR_CAPTURE_OVERHEAD_SIZE > tb->size))
        return;
    hdr.timestamp = ts;
    hdr.event = ev;
    rounded_size = BCMOS_ROUND_UP(hdr.msg_size, sizeof(uint32_t));
    _bcmtr_capture_store(tb, &hdr, sizeof(hdr));
    _bcmtr_capture_store(tb, packed, rounded_size); /* overflow by up to 3 bytes; is this safe? */
    rounded_size += sizeof(bcmtr_capture_entry) + sizeof(uint32_t);
    _bcmtr_capture_store(tb, &rounded_size, sizeof(rounded_size));
    ++tb->events;
}

/* Notify message to logger */
static void bcmtr_log_notify(bcmolt_devid device, const bcmtr_hdr *hdr,
    bcmtr_cld_event_type ev, uint32_t ts,
    const void *packed, uint32_t packed_length, bcmolt_msg *msg)
{
#ifdef ENABLE_LOG
    bcmos_errno err;
    const bcmolt_obj_descr *obj_descr;
    const bcmolt_group_descr *group_descr;

    err = bcmolt_api_obj_descr_get(hdr->obj, &obj_descr);
    BCMOS_CHECK_RETURN(err != BCM_ERR_OK, err,);

    /* Get name of specific subgroup */
    err = bcmolt_api_group_descr_get_by_group_id(hdr->obj, hdr->group_id, &group_descr);
    BCMOS_CHECK_RETURN(err != BCM_ERR_OK, err,);

    /* log with the header but without file/line number (file/line number isn't helpful here). */
    bcm_dev_log_log(
        bcmtr_cld_log_id,
        DEV_LOG_LEVEL_INFO,
        BCM_LOG_FLAG_NONE,
        "%s %s: corr_tag=%u instance=%d obj=%s group=%s subgrp=%s org_ts=%u err=%s\n",
        bcmtr_cld_event_name(ev),
        hdr->dir == BCMOLT_MSG_DIR_RESPONSE ? "response" : "request",
        hdr->corr_tag,
        hdr->instance,
        obj_descr->name,
        bcmolt_mgt_group_to_str(group_descr->mgt_group),
        group_descr->name,
        ts,
        msg ? bcmos_strerror(msg->err) : "N/A");
#endif
}

#if defined(ENABLE_CLI) && defined(ENABLE_LOG)
#ifndef CONFIG_AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT
/* Breaks 'bcmtr_cld_scratch_buf' into multiple logger lines. */
static void bcmtr_cld_cli_output_via_dev_log(void)
{
    uint32_t start_pos;
    uint32_t end_pos;

    bcmos_mutex_lock(&bcmtr_cld_scratch_buf_mutex);
    for (start_pos = 0, end_pos = start_pos + MIN(bcmtr_cld_scratch_pos, MAX_DEV_LOG_STRING_NET_SIZE - 1); start_pos < bcmtr_cld_scratch_pos && end_pos <= bcmtr_cld_scratch_pos;
        start_pos = end_pos, end_pos = start_pos + MIN(bcmtr_cld_scratch_pos - start_pos, MAX_DEV_LOG_STRING_NET_SIZE - 1))
    {
        char c;
        char last_char = bcmtr_cld_scratch_buf[end_pos - 1];

        c = bcmtr_cld_scratch_buf[end_pos];
        bcmtr_cld_scratch_buf[end_pos] = '\0';
        /* Do not add extra '\n' if the current line is already terminated by '\n' (typically the last line is terminated by '\n', whereas the rest of the lines are not). */
        bcm_dev_log_log(bcmtr_cld_log_id, DEV_LOG_LEVEL_INFO, BCM_LOG_FLAG_CALLER_FMT, "%s%s", &bcmtr_cld_scratch_buf[start_pos], last_char == '\n' ? "" : "\n");
        bcmtr_cld_scratch_buf[end_pos] = c;
    }
    bcmos_mutex_unlock(&bcmtr_cld_scratch_buf_mutex);
}
#endif
#endif

/* Dump message header and/or body */
static void bcmtr_dump_notify(
    bcmolt_devid device,
    bcmtr_cld_type level,
    const bcmtr_hdr *hdr,
    bcmtr_cld_event_type ev,
    uint32_t ts,
    const void *packed,
    uint32_t packed_length,
    bcmolt_msg *msg)
{
#ifdef ENABLE_CLI
    bcmos_errno err;
    const bcmolt_obj_descr *obj_descr;
    const bcmolt_group_descr *group_descr;

    err = bcmolt_api_obj_descr_get(hdr->obj, &obj_descr);
    BCMOS_CHECK_RETURN(err != BCM_ERR_OK, err,);

    /* Get name of specific subgroup */
    err = bcmolt_api_group_descr_get_by_group_id(hdr->obj, hdr->group_id, &group_descr);
    BCMOS_CHECK_RETURN(err != BCM_ERR_OK, err,);

    /* always dump the message header to the scratch CLI session */
    bcmcli_session_print(
        bcmtr_cld_scratch_session,
        "[-- CLD: %s %s: corr_tag=%u instance=%d obj=%s(%d) group=%s(%d) subgrp=%s(%d)",
        bcmtr_cld_event_name(ev),
        hdr->dir == BCMOLT_MSG_DIR_RESPONSE ? "response" : "request",
        hdr->corr_tag,
        hdr->instance,
        obj_descr->name, hdr->obj,
        bcmolt_mgt_group_to_str(group_descr->mgt_group), group_descr->mgt_group,
        group_descr->name, group_descr->subgroup_idx);

    if (hdr->more_fragments || (hdr->frag_number != 0))
    {
        bcmcli_session_print(
            bcmtr_cld_scratch_session,
            " more_fragments=%d fragment_number=%u",
            hdr->more_fragments,
            hdr->frag_number);
    }

    bcmcli_session_print(bcmtr_cld_scratch_session, " --]\n");

    /* if configured for a full message dump, write the message data to the scratch session */
    if ((level & BCMTR_CLD_DUMP) == BCMTR_CLD_DUMP)
    {
        if (msg != NULL)
        {
            bcmcli_session_print(bcmtr_cld_scratch_session, "[-- CLD Message Dump Start --]\n");
            apicli_msg_dump(bcmtr_cld_scratch_session, device, msg);
        }
        else
        {
            bcmcli_session_print(bcmtr_cld_scratch_session, "[-- CLD Message Hex Dump Start --]\n");
            bcmcli_session_hexdump(bcmtr_cld_scratch_session, packed, 0, packed_length, NULL);
        }
        bcmcli_session_print(bcmtr_cld_scratch_session, "[-- CLD Message Dump End --]\n");
    }

    /* Write the scratch session's buffer to the real CLI and reset it */
    bcmcli_session_write(bcmtr_cld_session, bcmtr_cld_scratch_buf, bcmtr_cld_scratch_pos);

    bcmtr_cld_scratch_pos = 0;
#endif
}

#ifdef ENABLE_CLI
static void _bcmtr_msg_write_cb(void *user_data, const char *format, va_list ap)
{
    bcmcli_session_vprint((bcmcli_session *)user_data, format, ap);
}
#endif

static void bcmtr_cli_notify(const bcmolt_msg *msg)
{
#ifdef ENABLE_CLI
    /* don't generate CLI commands for responses/indications */
    if ((msg->dir == BCMOLT_MSG_DIR_REQUEST) && (msg->group != BCMOLT_MGT_GROUP_AUTO))
    {
        bcmos_errno err;
        bcmolt_metadata_writer writer = { .write_cb = _bcmtr_msg_write_cb, .user_data = bcmtr_cld_scratch_session };
        err = bcmolt_api_write_msg(&writer, msg, BCMOLT_METADATA_WRITE_STYLE_CLI_INPUT);
        if (BCM_ERR_OK != err)
        {
            BCMOS_TRACE_ERR("Error generating CLI command for API: %s\n", bcmos_strerror(err));
        }

#ifdef CONFIG_AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT
        /* Write the scratch session's buffer to the real CLI and reset it */
        bcmcli_session_write(bcmtr_cld_session, bcmtr_cld_scratch_buf, bcmtr_cld_scratch_pos);
#elif ENABLE_LOG
        bcmtr_cld_cli_output_via_dev_log();
#endif

        bcmtr_cld_scratch_pos = 0;
    }
#endif
}

/* Notify capture, log, debug */
void bcmtr_cld_notify(bcmolt_devid device, bcmtr_cld_type level, const bcmtr_hdr *hdr,
    bcmtr_cld_event_type ev, uint32_t ts, const uint8_t *packed, uint32_t packed_length,
    bcmolt_msg *msg)
{
    if ((level & BCMTR_CLD_CAPTURE))
        bcmtr_capture_notify(device, hdr, ev, ts, packed, packed_length, msg);
    if ((level & BCMTR_CLD_LOG))
        bcmtr_log_notify(device, hdr, ev, ts, packed, packed_length, msg);
    if ((level & BCMTR_CLD_DUMP))
        bcmtr_dump_notify(device, level, hdr, ev, ts, packed, packed_length, msg);
    if ((level & BCMTR_CLD_CLI))
        bcmtr_cli_notify(msg);
}

/* Ignore GET */
#ifdef CONFIG_AUTO_CLD_EXCLUDE_GET
static void bcmtr_cld_auto_exclude_msg_type_get(void)
{
    bcmtr_cld_filter filter =
    {
        .group = BCMOLT_MGT_GROUP_ANY,
        .object = BCMOLT_OBJECT_ANY,
        .subgroup = BCMOLT_SUBGROUP_ANY,
        .msg_type = BCMTR_CLD_MSG_TYPE_GET
    };
    
    bcmtr_cld_level_set(0, &filter, BCMTR_CLD_NONE);
}
#endif

/* Ignore device keep-alive */
#ifdef CONFIG_AUTO_CLD_EXCLUDE_DEVICE_KEEP_ALIVE
static void bcmtr_cld_auto_exclude_device_keep_alive(void)
{
    bcmtr_cld_filter filter =
    {
        .group = BCMOLT_MGT_GROUP_OPER,
        .object = BCMOLT_OBJ_ID_DEVICE,
        .subgroup = BCMOLT_DEVICE_OPER_SUBGROUP_HOST_KEEP_ALIVE,
        .msg_type = BCMTR_CLD_MSG_TYPE_ANY
    };

    bcmtr_cld_level_set(0, &filter, BCMTR_CLD_NONE);

    filter.group = BCMOLT_MGT_GROUP_AUTO;

    bcmtr_cld_level_set(0, &filter, BCMTR_CLD_NONE);
}
#endif

/* Ignore CPU packets (OMCI messages) */
#ifdef CONFIG_AUTO_CLD_EXCLUDE_CPU_PACKETS
static void bcmtr_cld_auto_exclude_cpu_packets(void)
{
    bcmtr_cld_filter filter =
    {
        .group = BCMOLT_MGT_GROUP_OPER,
        .object = BCMOLT_OBJ_ID_PON_INTERFACE,
        .subgroup = BCMOLT_PON_INTERFACE_OPER_SUBGROUP_CPU_PACKETS,
        .msg_type = BCMTR_CLD_MSG_TYPE_ANY
    };

    bcmtr_cld_level_set(0, &filter, BCMTR_CLD_NONE); 

    filter.object = BCMOLT_OBJ_ID_ONU;
    filter.subgroup = BCMOLT_ONU_OPER_SUBGROUP_CPU_PACKETS;

    bcmtr_cld_level_set(0, &filter, BCMTR_CLD_NONE);
}
#endif

/* Allows fine exclusion of certain types of messages. */
static void bcmtr_cld_auto_exclude(void)
{
#ifdef CONFIG_AUTO_CLD_EXCLUDE_GET
    bcmtr_cld_auto_exclude_msg_type_get();
#endif

#ifdef CONFIG_AUTO_CLD_EXCLUDE_DEVICE_KEEP_ALIVE
    bcmtr_cld_auto_exclude_device_keep_alive();
#endif

#ifdef CONFIG_AUTO_CLD_EXCLUDE_CPU_PACKETS
    bcmtr_cld_auto_exclude_cpu_packets();
#endif
}

bcmos_errno bcmtr_cld_init(bcmcli_session *session)
{
    static bcmos_bool initialized;
    bcmos_errno err;
    bcmtr_cld_filter filter =
    {
        .group = BCMOLT_MGT_GROUP_ANY,
        .object = BCMOLT_OBJECT_ANY,
        .subgroup = BCMOLT_SUBGROUP_ANY,
        .msg_type = BCMTR_CLD_MSG_TYPE_ANY
    };
    bcmtr_cld_type cld_level = BCMTR_CLD_NONE;
#ifdef CONFIG_AUTO_CLD_CAPTURE_BUF_SIZE_BYTES
    bcmtr_capture_parm capture_parm =
    {
        .size = CONFIG_AUTO_CLD_CAPTURE_BUF_SIZE_BYTES,
        .stop_on_full = BCMOS_FALSE,
        .activate = BCMOS_TRUE
    };
#endif

    if (initialized)
        return BCM_ERR_OK;

#ifdef ENABLE_CLI
    bcmcli_session_parm scratch_session_parm = { .write = bcmtr_log_cli_print };
#ifndef CONFIG_AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT
    bcmos_mutex_create(&bcmtr_cld_scratch_buf_mutex, 0, "bcmtr_cld_scratch_buf_mutex");
#endif
#endif

    err = bcmcli_session_open_user(&scratch_session_parm, &bcmtr_cld_scratch_session);
    BCMOS_CHECK_RETURN_ERROR(err != BCM_ERR_OK, err);

    bcmtr_cld_session = session;

#ifdef ENABLE_LOG
    bcmtr_cld_log_id = bcm_dev_log_id_register("cld", DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
#endif

#ifdef CONFIG_AUTO_CLD_CAPTURE_BUF_SIZE_BYTES
    if (capture_parm.size)
    {
        err = bcmtr_capture_init(0, &capture_parm); 
        if (err)
            return err;

        cld_level |= BCMTR_CLD_CAPTURE;
    }
#endif
#ifdef CONFIG_AUTO_CLD_LOG
    cld_level |= BCMTR_CLD_LOG;
#endif
#ifdef CONFIG_AUTO_CLD_DUMP
    cld_level |= BCMTR_CLD_DUMP;
#endif
#ifdef CONFIG_AUTO_CLD_CLI
    cld_level |= BCMTR_CLD_CLI;
#endif
    
    bcmtr_cld_level_set(0, &filter, cld_level);
    
    bcmtr_cld_auto_exclude();

    initialized = BCMOS_TRUE;

    return BCM_ERR_OK;
}

/** Clean up transport capture, log, debug service
 */
void bcmtr_cld_exit(void)
{
#ifdef ENABLE_CLI
#ifndef CONFIG_AUTO_CLD_CLI_OUTPUT_VIA_SESSION_PRINT
    bcmos_mutex_destroy(&bcmtr_cld_scratch_buf_mutex);
#endif
    bcmtr_cld_cli_exit();
#endif
    if (bcmtr_cld_scratch_session)
    {
        bcmcli_session_close(bcmtr_cld_scratch_session);
        bcmtr_cld_scratch_session = NULL;
    }
}
