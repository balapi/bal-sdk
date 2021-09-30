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

/*
 * API logging support.
 */

#include <bcmolt_api_log.h>
#include <bcmolt_metadata_writer.h>
#include <bcmolt_api_writer.h>

dev_log_id bcmolt_api_log_id;

#ifdef ENABLE_LOG

/* Buffer to accommodate the output of the API writer, before we apply the loop that breaks into separate logger lines in every '\n' */
#define BCMOLT_API_LOG_REC_SIZE 8192

/* maximum number of tasks that can use the API/logger integration simultaneously */
#define BCMOLT_API_LOG_NUM_BLKS 16

#define BCMOLT_API_LOG_STYLE_NORMAL     "\033[0m\033#5"
#define BCMOLT_API_LOG_STYLE_BOLD       "\033[1m"
#define BCMOLT_API_LOG_COLOR_GREEN      "\033[32m"

typedef struct
{
    const bcmolt_msg *msg;
    char *buf;
    uint32_t used;
    bcmos_bool first;
} bcmolt_api_log_rec;

static bcmos_blk_pool bcmolt_api_log_blk_pool;

#endif /* #ifdef ENABLE_LOG */

bcmos_errno bcmolt_api_log_init(void)
{
#ifdef ENABLE_LOG
    if (!bcmolt_api_log_id || bcmolt_api_log_id == DEV_LOG_INVALID_ID)
    {
        bcmolt_api_log_id = bcm_dev_log_id_register("api", DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
        if (bcmolt_api_log_id == DEV_LOG_INVALID_ID)
        {
            BCMOS_TRACE_ERR("Can't register log_id 'api'\n");
            return BCM_ERR_INTERNAL;
        }

        bcmos_blk_pool_parm blk_pool_parm =
        {
            .name = "api_msg_log",
            .blk_size = BCMOLT_API_LOG_REC_SIZE,
            .num_blks = BCMOLT_API_LOG_NUM_BLKS,
        };
        return bcmos_blk_pool_create(&bcmolt_api_log_blk_pool, &blk_pool_parm);
    }
#endif
    return BCM_ERR_OK;
}

#ifdef ENABLE_LOG

static inline uint32_t bcmolt_api_log_buf_remaining(const bcmolt_api_log_rec *rec)
{
    return BCMOLT_API_LOG_REC_SIZE - rec->used;
}

/* "flush" accumulated data to dev_log */
static void _api_log_flush(bcmolt_api_log_rec *rec)
{
    char *p = rec->buf;
    int used = rec->used;

    while (used > 0)
    {
        if (rec->first)
        {
            /* The 1st entry contains less data because of the header. Save room with some spare */
#define API_LOG_FIRST_ENTRY_SIZE    (MAX_DEV_LOG_STRING_SIZE - 40)
            char first_rec_buf[API_LOG_FIRST_ENTRY_SIZE + 1];
            strncpy(first_rec_buf, p, API_LOG_FIRST_ENTRY_SIZE);
            first_rec_buf[API_LOG_FIRST_ENTRY_SIZE] = 0;
            bcm_dev_log_log(bcmolt_api_log_id, DEV_LOG_LEVEL_DEBUG, BCM_LOG_FLAG_CALLER_FMT, "%s", first_rec_buf);
            p += API_LOG_FIRST_ENTRY_SIZE;
            used -= API_LOG_FIRST_ENTRY_SIZE;
            rec->first = BCMOS_FALSE;
        }
        else
        {
            bcm_dev_log_log(bcmolt_api_log_id, DEV_LOG_LEVEL_DEBUG, BCM_LOG_FLAG_NO_HEADER, "%s", p);
            p += MAX_DEV_LOG_STRING_SIZE - 1;
            used -= MAX_DEV_LOG_STRING_SIZE - 1;
        }
    }

    rec->used = 0;
}

static void _api_log_write_cb(void *user_data, const char *format, va_list ap)
{
    int ret;
    bcmolt_api_log_rec *rec = user_data;
    va_list ap_copy;

    va_copy(ap_copy, ap); /* Need to make a copy to allow calling vsnprintf twice */
    ret = vsnprintf(rec->buf + rec->used, bcmolt_api_log_buf_remaining(rec), format, ap);
    if (ret >= bcmolt_api_log_buf_remaining(rec))
    {
        rec->buf[rec->used] = 0; /* Restore 0 terminator after vsnprintf above */
        /* Flush the data accumulated before the current _api_log_write_cb call */
        _api_log_flush(rec);
        /* Can't overflow the 2nd time because API serializer outputs message in small chunks */
        ret = vsnprintf(rec->buf + rec->used, bcmolt_api_log_buf_remaining(rec), format, ap_copy);
    }
    rec->used += ret;
    va_end(ap_copy);
}

static void _api_log_write(void *user_data, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    _api_log_write_cb(user_data, format, ap);
    va_end(ap);
}

#endif

void bcmolt_api_log(bcmolt_oltid olt, const bcmolt_msg *msg)
{
#ifdef ENABLE_LOG

    bcmolt_api_log_rec rec = { .msg = msg, .used = 0, .first = BCMOS_TRUE };
    bcmolt_metadata_writer writer = { .write_cb = _api_log_write_cb, .user_data = &rec };
    bcm_dev_log_level log_level_save = DEV_LOG_LEVEL_NO_LOG;
    bcm_dev_log_level log_level_print = DEV_LOG_LEVEL_NO_LOG;

    /* Exit if api log is not at debug level (optimization) */
    bcm_dev_log_id_get_level(bcmolt_api_log_id, &log_level_print, &log_level_save);
    if (log_level_save < DEV_LOG_LEVEL_DEBUG && log_level_print < DEV_LOG_LEVEL_DEBUG)
        return;

    rec.buf = bcmos_blk_pool_alloc(&bcmolt_api_log_blk_pool);
    if (!rec.buf)
    {
        BCM_LOG(ERROR, bcmolt_api_log_id, "API message log error: log buffer pool exhausted\n");
        return;
    }

    rec.used = sprintf(rec.buf, "/olt %u;%s",  olt, BCMOLT_API_LOG_STYLE_BOLD BCMOLT_API_LOG_COLOR_GREEN);
    /* Lock the logger to make sure that multiple log entries logged here are not interleaved with other entries */
    bcm_dev_log_lock();

    bcmolt_api_write_msg(&writer, msg, BCMOLT_METADATA_WRITE_STYLE_CLI_INPUT);
    _api_log_write(&rec, "%s", BCMOLT_API_LOG_STYLE_NORMAL);
    _api_log_flush(&rec);

    bcm_dev_log_unlock();

    bcmos_blk_pool_free(rec.buf);

#endif /* #ifdef ENABLE_LOG */
}
