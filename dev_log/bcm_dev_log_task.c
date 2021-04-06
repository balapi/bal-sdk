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

#ifdef ENABLE_LOG

#include "bcm_dev_log_task.h"
#include "bcm_dev_log_task_internal.h"
#include "bcm_dev_log.h"
#if defined(LINUX_KERNEL_SPACE) && !defined(__KERNEL__)
#include "bcmos_mgmt_type.h"
#include "bcmolt_dev_log_linux.h"
#include "bcmolt_dev_log_linux_ud.h"
#endif

#ifdef DEV_LOG_SYSLOG
#include <syslog.h>
#endif

#define USE_ANSI_ESCAPE_CODES

#ifdef USE_ANSI_ESCAPE_CODES
#define DEV_LOG_STYLE_NORMAL        "\033[0m\033#5"
#define DEV_LOG_STYLE_BOLD          "\033[1m"
#define DEV_LOG_STYLE_UNDERLINE     "\033[4m"
#define DEV_LOG_STYLE_BLINK         "\033[5m"
#define DEV_LOG_STYLE_REVERSE_VIDEO "\033[7m"
#else
#define DEV_LOG_STYLE_NORMAL        "    "
#define DEV_LOG_STYLE_BOLD          "*** "
#define DEV_LOG_STYLE_UNDERLINE     "___ "
#define DEV_LOG_STYLE_BLINK         "o_o "
#define DEV_LOG_STYLE_REVERSE_VIDEO "!!! "
#endif

#define DEV_LOG_MSG_START_CHAR      0x1e        /* record separator character */

#define MEM_FILE_HDR_SIZE       sizeof(dev_log_mem_file_header)

#define LOG_MIN(a,b)        (((int)(a) <= (int)(b)) ? (a) : (b))

dev_log_id def_log_id;

static int default_write_callback_unprotected(bcm_dev_log_file *file, const void *buf, uint32_t length);

static bcm_dev_log_style dev_log_level2style[DEV_LOG_LEVEL_NUM_OF] =
{
    [DEV_LOG_LEVEL_FATAL] = BCM_DEV_LOG_STYLE_NORMAL,
    [DEV_LOG_LEVEL_ERROR] = BCM_DEV_LOG_STYLE_NORMAL,
    [DEV_LOG_LEVEL_WARNING] = BCM_DEV_LOG_STYLE_NORMAL,
    [DEV_LOG_LEVEL_INFO] = BCM_DEV_LOG_STYLE_NORMAL,
    [DEV_LOG_LEVEL_DEBUG] = BCM_DEV_LOG_STYLE_NORMAL,
};

static const char *dev_log_style_array[] =
{
    [BCM_DEV_LOG_STYLE_NORMAL] = DEV_LOG_STYLE_NORMAL,
    [BCM_DEV_LOG_STYLE_BOLD] = DEV_LOG_STYLE_BOLD,
    [BCM_DEV_LOG_STYLE_UNDERLINE] = DEV_LOG_STYLE_UNDERLINE,
    [BCM_DEV_LOG_STYLE_BLINK] = DEV_LOG_STYLE_BLINK,
    [BCM_DEV_LOG_STYLE_REVERSE_VIDEO] = DEV_LOG_STYLE_REVERSE_VIDEO,
};

bcm_dev_log dev_log = {{0}};
const char *log_level_str = "?FEWID";

static void bcm_dev_log_shutdown_msg_release(bcmos_msg *m)
{
    (void)m; /* do nothing, the message is statically allocated */
}

static bcmos_msg shutdown_msg = { .release = bcm_dev_log_shutdown_msg_release };

static void bcm_dev_log_file_save_msg(bcm_dev_log_file *files, const char *message)
{
    uint32_t i;
    uint32_t len = strlen(message) + 1; /* including 0 terminator */

    for (i = 0; (i < DEV_LOG_MAX_FILES) && (files[i].file_parm.flags & BCM_DEV_LOG_FILE_FLAG_VALID); i++)
    {
        files[i].file_parm.write_cb(&files[i], message, len);
    }
}

static void dev_log_save_task_format_message(dev_log_queue_msg *receive_msg, char *log_string, uint32_t log_string_size, ...)
{
    uint32_t length;
    char time_str[17];
    dev_log_id_parm *log_id = receive_msg->log_id;
    bcm_dev_log_level msg_level = receive_msg->msg_level;

    /* Build message header */
    *log_string = '\0';
    if (!(receive_msg->flags & BCM_LOG_FLAG_NO_HEADER))
    {
        length = sizeof(time_str);
        dev_log.dev_log_parm.time_to_str_cb(receive_msg->time_stamp, time_str, length);
        snprintf(
            log_string,
            log_string_size,
            "[%s: %c %-20s] ",
            time_str,
            log_level_str[msg_level],
            log_id->name);
    }

    /* Modify the __FILE__ format so it would print the filename only without the path.
     * If using BCM_LOG_FLAG_CALLER_FMT, it is done in caller context, because filename might be long, taking a lot of
     * the space of the message itself. */
    if ((receive_msg->flags & BCM_LOG_FLAG_FILENAME_IN_FMT) && !(receive_msg->flags & BCM_LOG_FLAG_CALLER_FMT))
    {
        /* coverity[misra_violation] - cross-assignment under union is OK - they're both in the same union member */
        receive_msg->u.fmt_args.fmt = dev_log_basename(receive_msg->u.fmt_args.fmt);
    }

    if (receive_msg->flags & BCM_LOG_FLAG_CALLER_FMT)
    {
        /* Copy user string to buffer */
        strncat(log_string, receive_msg->u.str, log_string_size - strlen(log_string) - 1);
    }
    else
    {
        uint32_t offset = ((long)receive_msg->u.fmt_args.args % 8 == 0) ? 0 : 1; /* start on an 8-byte boundary */

#ifndef COMPILATION_32_BIT
        /* NOTE: why do we use so terrible input:
         * It is impossible to send va_list structure from bcm_dev_log.c. So we send array of arguments only.
         * The va_list maintains pointers to temporary memory on the stack.
         * After the function with variable args has returned, this automatic storage is gone and the contents are no longer usable.
         * Because of this, we cannot simply keep a copy of the va_list itself - the memory it references will contain unpredictable content.
         * In addition internal struct va_list is different in 64-bit and 32-bit, in ARM, in posix etc., so we cannot assume what exactly its fields contain */

        snprintf(log_string + strlen(log_string),
            log_string_size - strlen(log_string),
            receive_msg->u.fmt_args.fmt,
            receive_msg->u.fmt_args.args[offset],
            receive_msg->u.fmt_args.args[offset+1],
            receive_msg->u.fmt_args.args[offset+2],
            receive_msg->u.fmt_args.args[offset+3],
            receive_msg->u.fmt_args.args[offset+4],
            receive_msg->u.fmt_args.args[offset+5],
            receive_msg->u.fmt_args.args[offset+6],
            receive_msg->u.fmt_args.args[offset+7],
            receive_msg->u.fmt_args.args[offset+8],
            receive_msg->u.fmt_args.args[offset+9],
            receive_msg->u.fmt_args.args[offset+10],
            receive_msg->u.fmt_args.args[offset+11],
            receive_msg->u.fmt_args.args[offset+12],
            receive_msg->u.fmt_args.args[offset+13],
            receive_msg->u.fmt_args.args[offset+14],
            receive_msg->u.fmt_args.args[offset+15],
            receive_msg->u.fmt_args.args[offset+16],
            receive_msg->u.fmt_args.args[offset+17],
            receive_msg->u.fmt_args.args[offset+18],
            receive_msg->u.fmt_args.args[offset+19],
            receive_msg->u.fmt_args.args[offset+20],
            receive_msg->u.fmt_args.args[offset+21],
            receive_msg->u.fmt_args.args[offset+22],
            receive_msg->u.fmt_args.args[offset+23],
            receive_msg->u.fmt_args.args[offset+24],
            receive_msg->u.fmt_args.args[offset+25],
            receive_msg->u.fmt_args.args[offset+26],
            receive_msg->u.fmt_args.args[offset+27],
            receive_msg->u.fmt_args.args[offset+28],
            receive_msg->u.fmt_args.args[offset+29],
            receive_msg->u.fmt_args.args[offset+30],
            receive_msg->u.fmt_args.args[offset+31],
            receive_msg->u.fmt_args.args[offset+32],
            receive_msg->u.fmt_args.args[offset+33],
            receive_msg->u.fmt_args.args[offset+34],
            receive_msg->u.fmt_args.args[offset+35]);
#else
        va_list ap;
        *(void **)&ap = &receive_msg->u.fmt_args.args[offset];
        /* Copy user string to buffer */
        vsnprintf(log_string + strlen(log_string),
            log_string_size - strlen(log_string),
            receive_msg->u.fmt_args.fmt,
            ap);
#endif
    }

    /* Force last char to be end of string */
    log_string[MAX_DEV_LOG_STRING_SIZE - 1] = '\0';
}

static void dev_log_save_task_handle_message(bcmos_msg *msg)
{
    static char log_string[MAX_DEV_LOG_STRING_SIZE];
    dev_log_queue_msg *receive_msg = msg->data;
    dev_log_id_parm *log_id = receive_msg->log_id;
    bcm_dev_log_level msg_level = receive_msg->msg_level;

    dev_log_save_task_format_message(receive_msg, log_string, sizeof(log_string));

    /* At this point, if the message is going to be sent to the print task, save the formatted string then forward it.
     * Otherwise, we can release the message before writing it to RAM. */
    if ((log_id->log_type & DEV_LOG_ID_TYPE_PRINT) &&
        (msg_level <= log_id->log_level_print))
    {
        if (!bcm_dev_log_level_is_error(msg_level) &&
            (receive_msg->flags & BCM_LOG_FLAG_DONT_SKIP_PRINT) != 0 &&
            bcm_dev_log_pool_occupancy_percent_get() >= DEV_LOG_SKIP_PRINT_THRESHOLD_PERCENT)
        {
            log_id->print_skipped_count++;
            bcmos_msg_free(msg);
        }
        else
        {
            strcpy(receive_msg->u.str, log_string); /* so the print task doesn't need to re-format it */

            bcmos_msg_send(&dev_log.print_queue, msg, BCMOS_MSG_SEND_AUTO_FREE);
        }
    }
    else
    {
        bcmos_msg_free(msg);
    }

    /* Save to file */
    if ((log_id->log_type & DEV_LOG_ID_TYPE_SAVE) &&
        (msg_level <= log_id->log_level_save))
    {
        bcm_dev_log_file_save_msg(dev_log.files, log_string);
    }
}

static void dev_log_print_task_handle_message(bcmos_msg *msg)
{
    static char log_string[MAX_DEV_LOG_STRING_SIZE];
    dev_log_queue_msg *receive_msg = msg->data;
    dev_log_id_parm *log_id = receive_msg->log_id;
    bcm_dev_log_level msg_level = receive_msg->msg_level;

    /* make a local copy of the pre-formatted string (it was formatted in the save task) */
    strcpy(log_string, receive_msg->u.str);

    /* free the message ASAP since printing might take some time */
    bcmos_msg_free(msg);

    if (log_id->style == BCM_DEV_LOG_STYLE_NORMAL &&
        dev_log_level2style[msg_level] == BCM_DEV_LOG_STYLE_NORMAL)
    {
        dev_log.dev_log_parm.print_cb(dev_log.dev_log_parm.print_cb_arg, "%s", log_string);
    }
    else
    {
        /* If style was set per log id, then use it. */
        if (log_id->style != BCM_DEV_LOG_STYLE_NORMAL)
        {
            dev_log.dev_log_parm.print_cb(
                dev_log.dev_log_parm.print_cb_arg,
                "%s%s%s",
                dev_log_style_array[log_id->style],
                log_string,
                dev_log_style_array[BCM_DEV_LOG_STYLE_NORMAL]);
        }
        else
        {
            /* Otherwise - style was set per log level. */
            dev_log.dev_log_parm.print_cb(
                dev_log.dev_log_parm.print_cb_arg,
                "%s%s%s",
                dev_log_style_array[dev_log_level2style[msg_level]],
                log_string,
                dev_log_style_array[BCM_DEV_LOG_STYLE_NORMAL]);
        }
    }
}

static int dev_log_print_task(long data)
{
    bcmos_msg *m;
    bcmos_errno error;
    const char error_str[MAX_DEV_LOG_STRING_SIZE] = "Error: Can't receive from queue - dev_log print task exit\n";

    while (1)
    {
        error = bcmos_msg_recv(&dev_log.print_queue, BCMOS_WAIT_FOREVER, &m);
        if (error != BCM_ERR_OK)
        {
            DEV_LOG_ERROR_PRINTF("%s", error_str);
            dev_log.dev_log_parm.print_cb(dev_log.dev_log_parm.print_cb_arg, "%s", error_str);
            bcm_dev_log_file_save_msg(dev_log.files, error_str);
            return (int)error;
        }

        if (m == &shutdown_msg)
        {
            break; /* shut down gracefully */
        }
        else
        {
            dev_log_print_task_handle_message(m);
        }
    }

    bcmos_sem_post(&dev_log.print_task_is_terminated);

    return 0;
}

static int dev_log_save_task(long data)
{
    bcmos_msg *m;
    bcmos_errno error;
    const char error_str[MAX_DEV_LOG_STRING_SIZE] = "Error: Can't receive from queue - dev_log save task exit\n";

    while (1)
    {
        error = bcmos_msg_recv(&dev_log.save_queue, BCMOS_WAIT_FOREVER, &m);

        if (error != BCM_ERR_OK)
        {
            DEV_LOG_ERROR_PRINTF("%s", error_str);
            dev_log.dev_log_parm.print_cb(dev_log.dev_log_parm.print_cb_arg, "%s", error_str);
            bcm_dev_log_file_save_msg(dev_log.files, error_str);
            return (int)error;
        }

        if (m == &shutdown_msg)
        {
            break; /* shut down gracefully */
        }
        else
        {
            dev_log_save_task_handle_message(m);
        }
    }

    bcmos_sem_post(&dev_log.save_task_is_terminated);

    return 0;
}

extern const char * last_format;
void dev_log_oops_complete_cb(void)
{
    bcmos_msg *m;
    uint32_t i;
    if (last_format)
    {
       printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! last format %s \n ",last_format);
    }


    /* We start traversing print queue. Those are already formatted messages that were forwarded from the save task.
     * Then we proceed to traversing save queue. Those are messages that haven't reached the print task yet.
     * We read from queue with timeout=0, meaning non-blocking call (we cannot wait in oops time - all OS services are down). */
    while (bcmos_msg_recv(&dev_log.print_queue, 0, &m) == BCM_ERR_OK)
        dev_log_print_task_handle_message(m);

    for (i = 0; (i < DEV_LOG_MAX_FILES) && (dev_log.files[i].file_parm.flags & BCM_DEV_LOG_FILE_FLAG_VALID); i++)
    {
        if (dev_log.files[i].file_parm.type == BCM_DEV_LOG_FILE_MEMORY)
            dev_log.files[i].file_parm.write_cb = default_write_callback_unprotected; /* Avoid bcmos_mutex_lock()/bcmos_mutex_unlock() in regular (protected) version. */
    }

    while (bcmos_msg_recv(&dev_log.save_queue, 0, &m) == BCM_ERR_OK)
    {
        static char log_string[MAX_DEV_LOG_STRING_SIZE];
        dev_log_queue_msg *receive_msg;
        dev_log_id_parm *log_id;
        bcm_dev_log_level msg_level;

        receive_msg = m->data;
        log_id = receive_msg->log_id;
        msg_level = receive_msg->msg_level;
        dev_log_save_task_format_message(receive_msg, log_string, sizeof(log_string));
        if ((log_id->log_type & DEV_LOG_ID_TYPE_PRINT) &&
            (msg_level <= log_id->log_level_print))
        {
            strcpy(receive_msg->u.str, log_string);
            dev_log_print_task_handle_message(m);
        }
        else
        {
            bcmos_msg_free(m);
        }

        /* Save to file */
        if ((log_id->log_type & DEV_LOG_ID_TYPE_SAVE) &&
            (msg_level <= log_id->log_level_save))
        {
            bcm_dev_log_file_save_msg(dev_log.files, log_string);
        }
    }
}

static int default_time_to_str(uint32_t time_stamp, char *time_str, int time_str_size)
{
    return snprintf(time_str, time_str_size, "%u", time_stamp);
}

static uint32_t default_get_time(void)
{
    return 0;
}

static void default_print(void *arg, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    bcmos_vprintf(format, args);
    va_end(args);
}

static bcmos_errno default_open_callback_cond_reset(const bcm_dev_log_file_parm *file_parm, bcm_dev_log_file *file, bcmos_bool is_rewind)
{
    bcmos_errno err;

    if (!file->file_parm.start_addr || file->file_parm.size <= MEM_FILE_HDR_SIZE)
        return BCM_ERR_PARM;

    /* Create file mutex */
    err = bcmos_mutex_create(&file->u.mem_file.mutex, 0, NULL);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't create mutex (error: %d)\n", (int)err);
        return err;
    }

    /* Check file magic string */
    memcpy(&file->u.mem_file.file_header, (uint8_t *)file->file_parm.start_addr, MEM_FILE_HDR_SIZE);
    if (memcmp(FILE_MAGIC_STR, file->u.mem_file.file_header.file_magic, FILE_MAGIC_STR_SIZE))
    {
        DEV_LOG_INFO_PRINTF("No file magic string - file is empty/corrupt\n");
        if (!is_rewind || !file->file_parm.rewind_cb)
        {
            bcmos_mutex_destroy(&file->u.mem_file.mutex);
            return BCM_ERR_NOENT;
        }
        return file->file_parm.rewind_cb(file);
    }

    DEV_LOG_INFO_PRINTF("Attached to existing file\n");

    return BCM_ERR_OK;
}

static bcmos_errno default_open_callback(const bcm_dev_log_file_parm *file_parm, bcm_dev_log_file *file)
{
    return default_open_callback_cond_reset(file_parm, file, BCMOS_TRUE);
}

static bcmos_errno default_close_callback(bcm_dev_log_file *file)
{
    bcmos_mutex_destroy(&file->u.mem_file.mutex);
    return BCM_ERR_OK;
}

/* Look for start of msg character */
static int get_msg_start_offset(bcm_dev_log_file *file, uint32_t offset, uint32_t max_len)
{
    uint8_t *buf, *msg;

    buf = (uint8_t *)file->file_parm.start_addr + offset + MEM_FILE_HDR_SIZE;
    msg = memchr(buf, DEV_LOG_MSG_START_CHAR, max_len);
    if (!msg)
        return -1;
    return (msg - buf + 1);
}

/* Look for 0-terminator */
static int get_msg_end_offset(bcm_dev_log_file *file, uint32_t offset, uint32_t max_len)
{
    uint8_t *buf, *end;

    buf = (uint8_t *)file->file_parm.start_addr + offset + MEM_FILE_HDR_SIZE;
    end = memchr(buf, 0, max_len);
    if (!end)
        return -1;
    return (end - buf + 1);
}

static int default_read_callback(bcm_dev_log_file *log_file, uint32_t *p_offset, void *buf, uint32_t length)
{
    uint32_t offset = *p_offset;
    uint32_t output_length = 0;
    uint32_t scan_length = 0;
    int start, end;
    bcmos_bool read_wrap = BCMOS_FALSE;

    /* If file wrapped around, offset is indeterminate, scan for start from current offset to end of file buffer,
     * if start not found, then try again from beginning of buffer up to write ptr */
    if (log_file->u.mem_file.file_header.file_wrap_cnt)
    {
        scan_length = log_file->u.mem_file.file_header.data_size - offset;

        if (scan_length <= 0)
        {
            /* Insane offset passed in from user, reset it */
            DEV_LOG_ERROR_PRINTF("%s: reset bad read offset:%d (> size of log buffer)\n", __FUNCTION__, offset);
            *p_offset = 0;
            return 0;
        }

        /* Find beginning of the next message */
        start = get_msg_start_offset(log_file, offset, scan_length);
        if (start < 0)
        {
            /* Didn't find any up to the end of buffer. Scan again from the start, up to write offset */
            offset = 0;
            if (!log_file->u.mem_file.file_header.write_offset)
                return 0;

            start = get_msg_start_offset(log_file, 0, log_file->u.mem_file.file_header.write_offset - 1);
            if (start <= 0)
            {
                return 0;
            }
        }
    }
    else
    {
        /* file not wrapped, scan from current offset up to write ptr */
        scan_length = log_file->u.mem_file.file_header.write_offset - offset;

        /* Scan for start of message. Without wrap-around it should be between read offset, and the write ptr */
        start = get_msg_start_offset(log_file, offset, scan_length);
        if (start <= 0)
            return 0;
    }
    offset += start;

    /* We have the beginning. Now find the end of message and copy to the user buffer if there is enough room */
    if (offset + length > log_file->u.mem_file.file_header.data_size)
    {
        /* Possible read wrap may occur, scan up to end of file buffer first */
        scan_length = log_file->u.mem_file.file_header.data_size - offset;
        end = get_msg_end_offset(log_file, offset, scan_length);
        if (end >= 0)
        {
            /* Found end before end of buffer, no read wrap, just copy and return */
            memcpy(buf, (uint8_t *)log_file->file_parm.start_addr + MEM_FILE_HDR_SIZE + offset, end);
            *p_offset += start + end;
            return end;
        }

        /* Didn't find end of message in the end of file buffer. Copy first part from offset up to end of buffer, then wrap around */
        memcpy(buf, (uint8_t *)log_file->file_parm.start_addr + MEM_FILE_HDR_SIZE + offset, scan_length);
        output_length = scan_length;
        buf = (uint8_t *)buf + scan_length;
        length -= scan_length; /* reduce remaining buffer space by size copied */
        offset = 0; /* Reset to beginning of buffer for final "end" scan */
        read_wrap = BCMOS_TRUE;
        scan_length = log_file->u.mem_file.file_header.write_offset - 1; /* Limit wrapped end scan from beginning of buffer up to write ptr */
    }
    else
    {
        /* No read wrap, just scan for end from current offset to the end of the file , since the end might be past the buffer length */
        scan_length = log_file->u.mem_file.file_header.data_size - offset;
    }

    end = get_msg_end_offset(log_file, offset, scan_length);
    if (end <= 0)
    {
        /* something is wrong. msg is not terminated */
        DEV_LOG_ERROR_PRINTF("%s: no message end found!\n", __FUNCTION__);
        return 0;
    }

    /* If there is no room for the whole message - return overflow */
    if (end > length)
        return (int)BCM_ERR_OVERFLOW;

    /* Copy whole message, or second part for wrapped read */
    memcpy(buf, (uint8_t *)log_file->file_parm.start_addr + MEM_FILE_HDR_SIZE + offset, end);
    output_length += end;

    if (read_wrap)
    {
        /* Reset wrapped read ptr, and write wrap count */
        log_file->u.mem_file.file_header.file_wrap_cnt = 0;
        *p_offset = end;
    }
    else
        *p_offset += start + output_length; /* Increment read ptr */

    return output_length;
}

static int get_num_of_overwritten_messages(uint8_t *buf, uint32_t length)
{
    uint8_t *p;
    int n = 0;

    do
    {
        p = memchr(buf, DEV_LOG_MSG_START_CHAR, length);
        if (p == NULL)
            break;
        ++n;
        length -= (p + 1 - buf);
        buf = p + 1;
    } while(length);

    return n;
}

static int default_write_callback_unprotected(bcm_dev_log_file *file, const void *buf, uint32_t length)
{
    uint32_t offset, next_offset;
    uint8_t *p;
    int n_overwritten = 0;

    if ((file->file_parm.flags & BCM_DEV_LOG_FILE_FLAG_STOP_WHEN_FULL) && file->is_full)
        return 0;

    if (!length)
        return 0;

    offset = file->u.mem_file.file_header.write_offset;
    next_offset = offset + length + 1; /* 1 extra character for record delimiter */

    /* Handle overflow */
    if (next_offset >= file->u.mem_file.file_header.data_size)
    {
        uint32_t tail_length;

        /* Split buffer in 2 */
        tail_length = next_offset - file->u.mem_file.file_header.data_size;   /* 2nd segment length */

        if ((file->file_parm.flags & BCM_DEV_LOG_FILE_FLAG_STOP_WHEN_FULL) && tail_length)
        {
            file->is_full = BCMOS_TRUE;
            return 0;
        }

        length -= tail_length;
        /* "if (next_offset >= file->u.mem_file.file_header.data_size)" condition
         * guarantees that there is room for at least 1 character in the end of file */
        p = (uint8_t *)file->file_parm.start_addr + offset + MEM_FILE_HDR_SIZE;
        if (file->u.mem_file.file_header.file_wrap_cnt)
            n_overwritten += get_num_of_overwritten_messages(p, length + 1);

        *p = DEV_LOG_MSG_START_CHAR;
        if (length)
        {
            memcpy(p + 1, buf, length);
            buf = (const uint8_t *)buf + length;
        }
        if (tail_length)
        {
            p = (uint8_t *)file->file_parm.start_addr + MEM_FILE_HDR_SIZE;
            if (file->u.mem_file.file_header.file_wrap_cnt)
                n_overwritten += get_num_of_overwritten_messages(p, tail_length);
            memcpy(p, buf, tail_length);
            ++file->u.mem_file.file_header.file_wrap_cnt;
        }
        next_offset = tail_length;
    }
    else
    {
        p = (uint8_t *)file->file_parm.start_addr + MEM_FILE_HDR_SIZE + offset;
        if (file->u.mem_file.file_header.file_wrap_cnt)
            n_overwritten += get_num_of_overwritten_messages(p, length + 1);
        *(p++) = DEV_LOG_MSG_START_CHAR;
        memcpy(p, buf, length);
    }
    file->u.mem_file.file_header.write_offset = next_offset;
    file->u.mem_file.file_header.num_msgs += (1 - n_overwritten);

    /* update the header */
    memcpy((uint8_t *)file->file_parm.start_addr, &file->u.mem_file.file_header, MEM_FILE_HDR_SIZE);

    /* send almost full indication if necessary */
    if (file->almost_full.send_ind_cb &&
        !file->almost_full.ind_sent &&
        file->u.mem_file.file_header.write_offset > file->almost_full.threshold)
    {
        file->almost_full.ind_sent = (file->almost_full.send_ind_cb(file->almost_full.priv) == BCM_ERR_OK);
    }

    return length;
}

static int default_write_callback(bcm_dev_log_file *file, const void *buf, uint32_t length)
{
    bcmos_mutex_lock(&file->u.mem_file.mutex);
    length = default_write_callback_unprotected(file, buf, length);
    bcmos_mutex_unlock(&file->u.mem_file.mutex);

    return length;
}

static bcmos_errno default_rewind_callback(bcm_dev_log_file *file)
{
    bcmos_mutex_lock(&file->u.mem_file.mutex);

    DEV_LOG_INFO_PRINTF("Clear file\n");
    file->u.mem_file.file_header.file_wrap_cnt = 0;
    file->u.mem_file.file_header.write_offset = 0;
    file->u.mem_file.file_header.data_size = file->file_parm.size - MEM_FILE_HDR_SIZE;
    file->u.mem_file.file_header.num_msgs = 0;
    strcpy(file->u.mem_file.file_header.file_magic, FILE_MAGIC_STR);
    memcpy((uint8_t *)file->file_parm.start_addr, &file->u.mem_file.file_header, MEM_FILE_HDR_SIZE);
    file->almost_full.ind_sent = BCMOS_FALSE;

    bcmos_mutex_unlock(&file->u.mem_file.mutex);

    return BCM_ERR_OK;
}

static void set_default_file_callbacks(bcm_dev_log_file *file)
{
    file->file_parm.open_cb = default_open_callback;
    file->file_parm.close_cb = default_close_callback;
    file->file_parm.read_cb = default_read_callback;
    file->file_parm.write_cb = default_write_callback;
    file->file_parm.rewind_cb = default_rewind_callback;
}

static inline bcmos_bool bcm_dev_log_is_memory_file(bcm_dev_log_file *file)
{
    return (file->file_parm.open_cb == default_open_callback);
}

bcmos_errno bcm_dev_log_file_clear(bcm_dev_log_file *file)
{
    if (!file || !(file->file_parm.flags & BCM_DEV_LOG_FILE_FLAG_VALID))
        return BCM_ERR_PARM;

    if (!file->file_parm.rewind_cb)
        return BCM_ERR_NOT_SUPPORTED;

    return file->file_parm.rewind_cb(file);
}

/* File index to file handle */
bcm_dev_log_file *bcm_dev_log_file_get(uint32_t file_index)
{
    bcm_dev_log_file *file = &dev_log.files[file_index];

    if ((file_index >= DEV_LOG_MAX_FILES) || !(file->file_parm.flags & BCM_DEV_LOG_FILE_FLAG_VALID))
        return NULL;
    return file;
}

/* Read from file */
int bcm_dev_log_file_read(bcm_dev_log_file *file, uint32_t *offset, char *buf, uint32_t buf_len)
{
    int len;
    if (!file || !buf || !(file->file_parm.flags & BCM_DEV_LOG_FILE_FLAG_VALID))
        return (int)BCM_ERR_PARM;

    len = file->file_parm.read_cb(file, offset, buf, buf_len);
    /* If nothing more to read and CLEAR_AFTER_READ mode, read again under lock and clear if no new records */
    if (!len && bcm_dev_log_is_memory_file(file) && (file->file_parm.flags & BCM_DEV_LOG_FILE_FLAG_CLEAR_AFTER_READ))
    {
        bcmos_mutex_lock(&file->u.mem_file.mutex);
        len = file->file_parm.read_cb(file, offset, buf, buf_len);
        if (!len)
        {
            file->file_parm.rewind_cb(file);
            *offset = 0; /* Also reset user read ptr when log file is cleared down! */
        }
        bcmos_mutex_unlock(&file->u.mem_file.mutex);
    }
    return len;
}

/* Attach file to memory buffer */
bcmos_errno bcm_dev_log_file_attach(void *buf, uint32_t buf_len, bcm_dev_log_file *file)
{
    bcmos_errno rc;
    dev_log_mem_file_header *hdr = (dev_log_mem_file_header *)buf;

    if (!buf || !file || buf_len <= MEM_FILE_HDR_SIZE)
        return BCM_ERR_PARM;

    if (memcmp(FILE_MAGIC_STR, hdr->file_magic, FILE_MAGIC_STR_SIZE))
        return BCM_ERR_NOENT;

#if DEV_LOG_ENDIAN != BCM_CPU_ENDIAN
    hdr->file_wrap_cnt = bcmos_endian_swap_u32(hdr->file_wrap_cnt);
    hdr->write_offset = bcmos_endian_swap_u32(hdr->write_offset);
    hdr->data_size = bcmos_endian_swap_u32(hdr->data_size);
    hdr->num_msgs = bcmos_endian_swap_u32(hdr->num_msgs);
#endif

    memset(file, 0, sizeof(*file));
    file->file_parm.start_addr = buf;
    file->file_parm.size = buf_len;
    file->file_parm.flags = BCM_DEV_LOG_FILE_FLAG_VALID;
    set_default_file_callbacks(file);
    rc = default_open_callback_cond_reset(&file->file_parm, file, BCMOS_FALSE);
    if (rc)
        return rc;

    if (!file->u.mem_file.file_header.num_msgs)
        return BCM_ERR_NOENT;

    return BCM_ERR_OK;
}

/* Detach file handle from memory buffer */
bcmos_errno bcm_dev_log_file_detach(bcm_dev_log_file *file)
{
    if (!file || !(file->file_parm.flags & BCM_DEV_LOG_FILE_FLAG_VALID))
        return BCM_ERR_PARM;
    file->file_parm.flags = BCM_DEV_LOG_FILE_FLAG_VALID;
    bcmos_mutex_destroy(&file->u.mem_file.mutex);
    return BCM_ERR_OK;
}

#ifdef BCM_OS_POSIX
    /* Regular file callbacks */

/****************************************************************************************/
/* OPEN CALLBACK: open memory/file                                                      */
/* file_parm - file parameters                                                          */
/* file      - file                                                                     */
/****************************************************************************************/
static bcmos_errno _dev_log_reg_file_open(const bcm_dev_log_file_parm *file_parm, bcm_dev_log_file *file)
{
    bcmos_errno err = BCM_ERR_OK;

    file->file_parm = *file_parm;
    file->u.reg_file_handle = fopen((char *)file_parm->udef_parms, "w+");
    if (!file->u.reg_file_handle)
    {
        bcmos_printf("DEV_LOG: can't open file %s for writing\n", (char *)file_parm->udef_parms);
        err = BCM_ERR_IO;
    }
    return err;
}

/****************************************************************************************/
/* CLOSE CALLBACK: close memory/file                                                      */
/* file      - file handle                                                              */
/****************************************************************************************/
static bcmos_errno _dev_log_reg_file_close(bcm_dev_log_file *file)
{
    if (file->u.reg_file_handle)
    {
        fclose(file->u.reg_file_handle);
        /* coverity[misra_violation] - we're not "using" the closed file handle, we're invalidating it */
        file->u.reg_file_handle = NULL;
    }
    return BCM_ERR_OK;
}

/****************************************************************************************/
/* REWIND CALLBACK: clears memory/file                                                  */
/* file      - file handle                                                              */
/****************************************************************************************/
static bcmos_errno _dev_log_reg_file_rewind(bcm_dev_log_file *file)
{
    bcmos_errno err = BCM_ERR_OK;
    FILE *f;

    if (file->u.reg_file_handle)
    {
        f = freopen((const char *)file->file_parm.udef_parms, "w+", file->u.reg_file_handle);
        if (NULL != f)
        {
            file->u.reg_file_handle = f;
        }
        else
        {
            err = BCM_ERR_IO;
            bcmos_printf("DEV_LOG: can't open file %s for writing\n", (char *)file->file_parm.udef_parms);
        }
    }
    return err;
}

/****************************************************************************************/
/* READ_CALLBACK: read form memory/file                                                 */
/* offset - the offset in bytes to read from, output                                    */
/* buf    - Where to put the result                                                     */
/* length - Buffer length                                                               */
/* This function should return the number of bytes actually read from file or 0 if EOF  */
/****************************************************************************************/
static int _dev_log_reg_file_read(bcm_dev_log_file *file, uint32_t *offset, void *buf, uint32_t length)
{
    int n = 0;
    if (file->u.reg_file_handle)
    {
        if (!fseek(file->u.reg_file_handle, SEEK_SET, *offset))
            n = fread(buf, 1, length, file->u.reg_file_handle);
        *offset = ftell(file->u.reg_file_handle);
    }
    return (n < 0) ? 0 : n;
}

/****************************************************************************************/
/* WRITE_CALLBACK: write form memory/file                                               */
/* buf    - The buffer that should be written                                           */
/* length - The number of bytes to write                                                */
/* This function should return the number of bytes actually written to file or 0 if EOF */
/****************************************************************************************/
static int _dev_log_reg_file_write(bcm_dev_log_file *file, const void *buf, uint32_t length)
{
    const char *cbuf = (const char *)buf;
    int n = 0;
    if (file->u.reg_file_handle)
    {
        /* Remove 0 terminator */
        if (length && !cbuf[length-1])
            --length;
        n = fwrite(buf, 1, length, file->u.reg_file_handle);
        fflush(file->u.reg_file_handle);
    }
    return n;
}

static void set_regular_file_callbacks(bcm_dev_log_file *file)
{
    file->file_parm.open_cb = _dev_log_reg_file_open;
    file->file_parm.close_cb = _dev_log_reg_file_close;
    file->file_parm.read_cb = _dev_log_reg_file_read;
    file->file_parm.write_cb = _dev_log_reg_file_write;
    file->file_parm.rewind_cb = _dev_log_reg_file_rewind;
}

#endif /* #ifdef BCM_OS_POSIX */

#ifdef DEV_LOG_SYSLOG
    /* linux syslog integration */
/****************************************************************************************/
/* OPEN CALLBACK: open syslog interface                                                 */
/* file_parm->udef_parm contains optional log ident                                     */
/****************************************************************************************/
static bcmos_errno _dev_log_syslog_file_open(const bcm_dev_log_file_parm *file_parm, bcm_dev_log_file *file)
{
    file->file_parm = *file_parm;
    openlog((const char *)file_parm->udef_parms, 0, LOG_USER);
    return BCM_ERR_OK;
}

/****************************************************************************************/
/* CLOSE CALLBACK: close syslog interface                                               */
/****************************************************************************************/
static bcmos_errno _dev_log_syslog_file_close(bcm_dev_log_file *file)
{
    closelog();
    return BCM_ERR_OK;
}

/****************************************************************************************/
/* REWIND CALLBACK: not supported by syslog. Return OK to prevent request failure       */
/****************************************************************************************/
static bcmos_errno _dev_log_syslog_file_rewind(bcm_dev_log_file *file)
{
    return BCM_ERR_OK;
}

/****************************************************************************************/
/* READ_CALLBACK: reading from syslog is not supported                                  */
/****************************************************************************************/
static int _dev_log_syslog_file_read(bcm_dev_log_file *file, uint32_t *offset, void *buf, uint32_t length)
{
    return 0;
}

/****************************************************************************************/
/* WRITE_CALLBACK: write to syslog                                                      */
/* buf    - The buffer that should be written                                           */
/* length - The number of bytes to write                                                */
/* This function should return the number of bytes actually written to file or 0 if EOF */
/****************************************************************************************/
static int _dev_log_syslog_file_write(bcm_dev_log_file *file, const void *buf, uint32_t length)
{
    const char *cbuf = (const char *)buf;
    static int log_priority = LOG_DEBUG;

    /* Identify log lovel */
    if (cbuf && cbuf[0] == '[')
    {
        const char *clevel = strchr(cbuf, ' ');
        if (clevel)
        {
            switch (*(clevel + 1))
            {
            case 'F':
                log_priority = LOG_CRIT;
                break;
            case 'E':
                log_priority = LOG_ERR;
                break;
            case 'W':
                log_priority = LOG_WARNING;
                break;
            case 'I':
                log_priority = LOG_INFO;
                break;
            case 'D':
                log_priority = LOG_DEBUG;
                break;
            default:
                break;
            }
        }
    }
    syslog(log_priority, "%s", cbuf);
    return length;
}

static void set_syslog_file_callbacks(bcm_dev_log_file *file)
{
    file->file_parm.open_cb = _dev_log_syslog_file_open;
    file->file_parm.close_cb = _dev_log_syslog_file_close;
    file->file_parm.read_cb = _dev_log_syslog_file_read;
    file->file_parm.write_cb = _dev_log_syslog_file_write;
    file->file_parm.rewind_cb = _dev_log_syslog_file_rewind;
}

#endif /* #ifdef DEV_LOG_SYSLOG */

static bcmos_errno bcm_dev_log_create(
    const bcm_dev_log_parm *dev_log_parm,
    const bcmos_task_parm *save_task_parm,
    const bcmos_task_parm *print_task_parm,
    const bcmos_msg_queue_parm *save_queue_parm,
    const bcmos_msg_queue_parm *print_queue_parm,
    const bcmos_msg_pool_parm *pool_parm)
{
    bcmos_errno err;
    int i;

    if (!dev_log_parm)
        return BCM_ERR_PARM;

    if (dev_log.state != BCM_DEV_LOG_STATE_UNINITIALIZED)
        return BCM_ERR_ALREADY;
    /* Set user callbacks */
    dev_log.dev_log_parm = *dev_log_parm;
    if (!dev_log.dev_log_parm.print_cb)
        dev_log.dev_log_parm.print_cb = default_print;
    if (!dev_log.dev_log_parm.get_time_cb)
        dev_log.dev_log_parm.get_time_cb = default_get_time;
    if (!dev_log.dev_log_parm.time_to_str_cb)
        dev_log.dev_log_parm.time_to_str_cb = default_time_to_str;

    for (i = 0; (i < DEV_LOG_MAX_FILES) && (dev_log_parm->log_file[i].flags & BCM_DEV_LOG_FILE_FLAG_VALID); i++)
    {
        /* Copy log files */
        dev_log.files[i].file_parm = dev_log_parm->log_file[i];
        if (!dev_log.files[i].file_parm.open_cb)
        {
            if (dev_log.files[i].file_parm.type == BCM_DEV_LOG_FILE_MEMORY)
                set_default_file_callbacks(&dev_log.files[i]);
#ifdef BCM_OS_POSIX
            else if (dev_log.files[i].file_parm.type == BCM_DEV_LOG_FILE_REGULAR)
            {
                set_regular_file_callbacks(&dev_log.files[i]);
            }
#endif
#ifdef DEV_LOG_SYSLOG
            else if (dev_log.files[i].file_parm.type == BCM_DEV_LOG_FILE_SYSLOG)
                set_syslog_file_callbacks(&dev_log.files[i]);
#endif
            else
            {
                DEV_LOG_ERROR_PRINTF("file%d: open_cb must be set for user-defined file\n\n", i);
                continue;
            }
        }
        err = dev_log.files[i].file_parm.open_cb(&dev_log.files[i].file_parm, &dev_log.files[i]);
        if (err)
        {
            DEV_LOG_ERROR_PRINTF("file%d: open failed: %s (%d)\n\n", i, bcmos_strerror(err), err );
            continue;
        }
        DEV_LOG_INFO_PRINTF("file: start_addr: 0x%p, size: %u, max msg size %u\n",
            dev_log.files[i].file_parm.start_addr, dev_log.files[i].file_parm.size, MAX_DEV_LOG_STRING_SIZE);
    }

    /* Create pool */
    err = bcmos_msg_pool_create(&dev_log.pool, pool_parm);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't create pool (error: %d)\n", (int)err);
        return err;
    }

    /* Create message queues */
    err = bcmos_msg_queue_create(&dev_log.save_queue, save_queue_parm);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("(%s) Error: Can't create save queue (error: %d)\n", __FUNCTION__, (int)err);
        return err;
    }

    err = bcmos_msg_queue_create(&dev_log.print_queue, print_queue_parm);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("(%s) Error: Can't create print queue (error: %d)\n", __FUNCTION__, (int)err);
        return err;
    }

    /* Create tasks */
    err = bcmos_task_create(&dev_log.save_task, save_task_parm);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't spawn save task (error: %d)\n", (int)err);
        return err;
    }
    err = bcmos_task_create(&dev_log.print_task, print_task_parm);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't spawn print task (error: %d)\n", (int)err);
        return err;
    }
    err = bcmos_sem_create(&dev_log.save_task_is_terminated, 0, 0, "save_task_sem");
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't create save task sem (error: %d)\n", (int)err);
        return err;
    }
    err = bcmos_sem_create(&dev_log.print_task_is_terminated, 0, 0, "print_task_sem");
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't create print task sem (error: %d)\n", (int)err);
        return err;
    }

    dev_log.state = BCM_DEV_LOG_STATE_ENABLED;

    return BCM_ERR_OK;
}

void bcm_dev_log_destroy(void)
{
    bcmos_errno err;
    uint32_t i;
    bcmos_msg_send_flags msg_flags;

    if (dev_log.state == BCM_DEV_LOG_STATE_UNINITIALIZED)
    {
        return;
    }

    /* Send a shutdown message to each task. When received by the main loops, it will tear down the tasks gracefully.
     * If the flag is set to tear down immediately, we'll send an URGENT teardown message, so it'll be handled before
     * all oustanding log messages (the oustanding log messages will be freed during bcmos_msg_queue_destroy). */
    msg_flags = BCMOS_MSG_SEND_NOLIMIT;
    if ((dev_log.flags & BCM_DEV_LOG_FLAG_DESTROY_IMMEDIATELY) != 0)
        msg_flags |= BCMOS_MSG_SEND_URGENT;

    /* The save task depends on the print task, so we terminate the save task first. */
    bcmos_msg_send(&dev_log.save_queue, &shutdown_msg, msg_flags);
    bcmos_sem_wait(&dev_log.save_task_is_terminated, BCMOS_WAIT_FOREVER);

    bcmos_msg_send(&dev_log.print_queue, &shutdown_msg, msg_flags);
    bcmos_sem_wait(&dev_log.print_task_is_terminated, BCMOS_WAIT_FOREVER);

    bcmos_sem_destroy(&dev_log.save_task_is_terminated);
    bcmos_sem_destroy(&dev_log.print_task_is_terminated);

    err = bcmos_task_destroy(&dev_log.save_task);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't destroy dev_log save task (error: %d)\n", (int)err);
    }

    err = bcmos_task_destroy(&dev_log.print_task);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't destroy dev_log print task (error: %d)\n", (int)err);
    }

    err = bcmos_msg_queue_destroy(&dev_log.save_queue);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't destroy save queue (error: %d)\n", (int)err);
    }

    err = bcmos_msg_queue_destroy(&dev_log.print_queue);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't destroy print queue (error: %d)\n", (int)err);
    }

    err = bcmos_msg_pool_destroy(&dev_log.pool);
    if (err != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("Error: Can't destroy pool (error: %d)\n", (int)err);
    }

    for (i = 0; (i < DEV_LOG_MAX_FILES) && (dev_log.dev_log_parm.log_file[i].flags & BCM_DEV_LOG_FILE_FLAG_VALID); i++)
    {
        dev_log.files[i].file_parm.close_cb(&dev_log.files[i]);
    }

    dev_log.state = BCM_DEV_LOG_STATE_UNINITIALIZED;
}

typedef struct
{
    bcmos_msg msg;
    dev_log_queue_msg log_queue_msg;
    bcmos_bool lock;
    bcmos_fastlock fastlock;
} bcm_dev_log_drop_msg;

typedef struct
{
    bcm_dev_log_drop_msg msg;
    uint32_t drops;
    uint32_t reported_drops;
    bcmos_timer timer;
    uint32_t last_report_timestamp;
} bcm_dev_log_drop;

static bcm_dev_log_drop dev_log_drop;

static void bcm_dev_log_log_message_release_drop(bcmos_msg *m)
{
    unsigned long flags;

    flags = bcmos_fastlock_lock(&dev_log_drop.msg.fastlock);
    dev_log_drop.msg.lock = BCMOS_FALSE;
    bcmos_fastlock_unlock(&dev_log_drop.msg.fastlock, flags);

    /* Schedule a timer to report extra drops, because we may not meet DEV_LOG_DROP_REPORT_DROP_THRESHOLD soon. */
    bcmos_timer_start(&dev_log_drop.timer, DEV_LOG_DROP_REPORT_RATE_US);
}

static void _bcm_dev_log_drop_report(void)
{
    bcmos_msg *msg;
    dev_log_queue_msg *log_queue_msg;
    static char drop_str[MAX_DEV_LOG_STRING_SIZE];

    msg = &dev_log_drop.msg.msg;
    msg->release = bcm_dev_log_log_message_release_drop;
    log_queue_msg = &dev_log_drop.msg.log_queue_msg;
    log_queue_msg->flags = BCM_LOG_FLAG_DONT_SKIP_PRINT;
    log_queue_msg->time_stamp = dev_log.dev_log_parm.get_time_cb();
    log_queue_msg->msg_level = DEV_LOG_LEVEL_ERROR;
    sprintf(drop_str, "Log message pool exhausted, dropped message count=%u\n", dev_log_drop.drops - dev_log_drop.reported_drops);
    log_queue_msg->u.fmt_args.fmt = (const char *)drop_str;
    log_queue_msg->log_id = (dev_log_id_parm *)def_log_id;
    log_queue_msg->time_stamp = dev_log.dev_log_parm.get_time_cb();
    dev_log_drop.reported_drops = dev_log_drop.drops;
    dev_log_drop.last_report_timestamp = bcmos_timestamp();

    msg->data = log_queue_msg;
    msg->size = sizeof(*log_queue_msg);
    bcmos_msg_send(&dev_log.save_queue, msg, BCMOS_MSG_SEND_AUTO_FREE);
}

void bcm_dev_log_drop_report(void)
{
    unsigned long flags;

    dev_log_drop.drops++;

    flags = bcmos_fastlock_lock(&dev_log_drop.msg.fastlock);
    /* The 1st drop report will be done immediately, because although DEV_LOG_DROP_REPORT_DROP_THRESHOLD isn't reached, the time difference is greater than
     * DEV_LOG_DROP_REPORT_RATE_US. */
    if (dev_log_drop.msg.lock ||
        ((dev_log_drop.drops - dev_log_drop.reported_drops < DEV_LOG_DROP_REPORT_DROP_THRESHOLD) &&
        (bcmos_timestamp() - dev_log_drop.last_report_timestamp < DEV_LOG_DROP_REPORT_RATE_US)))
    {
        bcmos_fastlock_unlock(&dev_log_drop.msg.fastlock, flags);
        return;
    }

    dev_log_drop.msg.lock = BCMOS_TRUE;
    bcmos_fastlock_unlock(&dev_log_drop.msg.fastlock, flags);

    /* Do the actual report. */
    _bcm_dev_log_drop_report();
}

static bcmos_timer_rc bcm_dev_log_drop_timer_cb(bcmos_timer *timer, long data)
{
    unsigned long flags;

    flags = bcmos_fastlock_lock(&dev_log_drop.msg.fastlock);
    if (dev_log_drop.msg.lock)
    {
        bcmos_fastlock_unlock(&dev_log_drop.msg.fastlock, flags);
        /* Logger task hasn't released the lock yet.
         * bcm_dev_log_log_message_release_drop() will (re)start drop reporting timer eventually. */
    }
    else
    {
        if (dev_log_drop.drops == dev_log_drop.reported_drops)
        {
            /* No new drops to report. */
            bcmos_fastlock_unlock(&dev_log_drop.msg.fastlock, flags);
            return BCMOS_TIMER_OK;
        }
        dev_log_drop.msg.lock = BCMOS_TRUE;
        bcmos_fastlock_unlock(&dev_log_drop.msg.fastlock, flags);

        /* Do the actual report. */
        _bcm_dev_log_drop_report();
    }

    return BCMOS_TIMER_OK;
}

bcmos_errno bcm_dev_log_init_default_logger_ext(
    bcm_dev_log_parm *dev_log_parm,
    uint32_t num_files,
    uint32_t stack_size,
    bcmos_task_priority priority,
    uint32_t pool_size)
{
    bcmos_errno err;
    bcmos_task_parm save_task_parm = {0};
    bcmos_task_parm print_task_parm = {0};
    bcmos_msg_queue_parm print_queue_parm = {0};
    bcmos_msg_queue_parm save_queue_parm = {0};
    bcmos_msg_pool_parm pool_parm = {0};
    bcmos_timer_parm timer_params =
    {
        .name = "dev_log_drop_timer",
        .owner = BCMOS_MODULE_ID_NONE, /* Will be called in ISR context */
        .handler = bcm_dev_log_drop_timer_cb,
    };

    if (!dev_log_parm)
    {
        DEV_LOG_ERROR_PRINTF("Error: dev_log_parm must be set\n");
        return BCM_ERR_PARM;
    }

    save_task_parm.priority = priority;
    save_task_parm.stack_size = stack_size;
    save_task_parm.name = "dev_log_save";
    save_task_parm.handler = dev_log_save_task;
    save_task_parm.data = 0;

    print_task_parm.priority = priority;
    print_task_parm.stack_size = stack_size;
    print_task_parm.name = "dev_log_print";
    print_task_parm.handler = dev_log_print_task;
    print_task_parm.data = 0;

    /* It is important to avoid terminating logger task during an exception, as logger task is low priority and might have backlog of unhandled messages.
     * Even if as a result of the exception the logger task will be in a deadlock waiting for a resource (semaphore/mutex/timer), it is in lower priority than CLI and thus should not block
     * CLI. */
    save_task_parm.flags = BCMOS_TASK_FLAG_NO_SUSPEND_ON_OOPS;
    print_task_parm.flags = BCMOS_TASK_FLAG_NO_SUSPEND_ON_OOPS;

    save_queue_parm.name = "dev_log_save";
    save_queue_parm.size = 0; /* unlimited */
    print_queue_parm.name = "dev_log_print";
    print_queue_parm.size = 0; /* unlimited */

    pool_parm.name = "dev_log";
    pool_parm.size = pool_size;
    pool_parm.data_size = sizeof(dev_log_queue_msg);

    def_log_id = bcm_dev_log_id_register("default", DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
    err = bcmos_timer_create(&dev_log_drop.timer, &timer_params);
    BCMOS_TRACE_CHECK_RETURN(err, err, "bcmos_timer_create");
    bcmos_fastlock_init(&dev_log_drop.msg.fastlock, 0);

    if (!dev_log_parm->get_time_cb)
        dev_log_parm->get_time_cb = bcmos_timestamp;

    err = bcm_dev_log_create(
        dev_log_parm,
        &save_task_parm,
        &print_task_parm,
        &save_queue_parm,
        &print_queue_parm,
        &pool_parm);
    BCMOS_TRACE_CHECK_RETURN(err, err, "bcm_dev_log_create");
    return BCM_ERR_OK;
}

bcmos_errno bcm_dev_log_init_default_logger(void **start_addresses,
    uint32_t *sizes,
    bcm_dev_log_file_flags *flags,
    uint32_t num_files,
    uint32_t stack_size,
    bcmos_task_priority priority,
    uint32_t pool_size)
{
    bcm_dev_log_parm dev_log_parm = {0};
    uint32_t i;

    for (i = 0; i < num_files; i++)
    {
        dev_log_parm.log_file[i].start_addr = start_addresses[i];
        dev_log_parm.log_file[i].size = sizes[i];
        /* size[i] might be 0 in simulation build for sram buffer. */
        dev_log_parm.log_file[i].flags = (bcm_dev_log_file_flags)
            ((sizes[i] ? BCM_DEV_LOG_FILE_FLAG_VALID : BCM_DEV_LOG_FILE_FLAG_NONE) |
            (flags ? flags[i] : BCM_DEV_LOG_FILE_FLAG_WRAP_AROUND));
    }
    return bcm_dev_log_init_default_logger_ext(&dev_log_parm, num_files, stack_size, priority,
        pool_size);
}

/* Log entry timestamp formatting callback */
static int bcm_log_time_to_ms_str_cb(uint32_t time_stamp, char *time_str, int time_str_size)
{
    return snprintf(time_str, time_str_size, "%u", time_stamp / 1000); /* convert from usec to msec. */
}

/* Simplified init function intended mainly for host use */
bcmos_errno bcm_log_init(const dev_log_init_parms *init_parms)
{
    bcmos_errno rc;
    bcm_dev_log_parm log_parms = {};
    uint32_t queue_size;

    log_parms.time_to_str_cb = bcm_log_time_to_ms_str_cb;
    if (init_parms->type == BCM_DEV_LOG_FILE_MEMORY)
    {
        log_parms.log_file[0].size = init_parms->mem_size ?
            init_parms->mem_size : BCM_DEV_LOG_DEFAULT_MEM_SIZE;
        log_parms.log_file[0].start_addr = bcmos_calloc(log_parms.log_file[0].size);
        log_parms.log_file[0].flags = (bcm_dev_log_file_flags)(BCM_DEV_LOG_FILE_FLAG_WRAP_AROUND | BCM_DEV_LOG_FILE_FLAG_CLEAR_AFTER_READ);
        if (log_parms.log_file[0].start_addr == NULL)
            return BCM_ERR_NOMEM;
    }
#ifdef BCM_OS_POSIX
    else if (init_parms->type == BCM_DEV_LOG_FILE_REGULAR)
    {
        if (init_parms->filename == NULL)
        {
            bcmos_printf("%s: filename is required for log type BCMOLT_LOG_TYPE_FILE\n", __FUNCTION__);
            return BCM_ERR_PARM;
        }
        log_parms.log_file[0].udef_parms = (char *)(long)init_parms->filename;
    }
#endif
    else
#ifdef DEV_LOG_SYSLOG
    if (init_parms->type != BCM_DEV_LOG_FILE_SYSLOG)
#endif
    {
        bcmos_printf("%s: log type %d is invalid\n", __FUNCTION__, init_parms->type);
        return BCM_ERR_PARM;
    }
    log_parms.log_file[0].type = init_parms->type;
    log_parms.log_file[0].flags |= BCM_DEV_LOG_FILE_FLAG_VALID;
    queue_size = init_parms->queue_size ? init_parms->queue_size : BCM_DEV_LOG_DEFAULT_QUEUE_SIZE;

    /* Only init a single log file */
    rc = bcm_dev_log_init_default_logger_ext(&log_parms, 1, 0x4000, TASK_PRIORITY_DEV_LOG, queue_size);
    BCMOS_TRACE_CHECK_RETURN(rc, rc, "bcm_dev_log_init_default_logger_ext()\n");

    bcm_dev_log_level_set_style(DEV_LOG_LEVEL_WARNING, BCM_DEV_LOG_STYLE_BOLD);

    if (init_parms->post_init_cb != NULL)
    {
        rc = init_parms->post_init_cb();
        BCMOS_TRACE_CHECK_RETURN(rc, rc, "%s: post_init_cb()\n", __FUNCTION__);
    }

    BCM_LOG(INFO, def_log_id, "Logging started\n");

    return BCM_ERR_OK;
}

log_name_table logs_names[DEV_LOG_MAX_IDS];
uint8_t log_name_table_index = 0;

static void dev_log_add_log_name_to_table(const char *name)
{
    char _name[MAX_DEV_LOG_ID_NAME + 1] = {};
    char *p = _name;
    char *p_end;
    int i = 0;
    long val = -1;

    strncpy(_name, name, MAX_DEV_LOG_ID_NAME);
    while (*p)
    {
        /* While there are more characters to process... */
        if (isdigit(*p))
        {
            /* Upon finding a digit, ... */
            val = strtol(p, &p_end, 10); /* Read a number, ... */
            if ((_name + strlen(_name)) != p_end)
            {
                DEV_LOG_ERROR_PRINTF("Error: dev_log_add_log_name_to_table %s)\n", name);
            }
            *p = '\0';
            break;
        }
        else
        {
            /* Otherwise, move on to the next character. */
            p++;
        }
    }
    for (i = 0; i < log_name_table_index; i++)
    {
        if (strcmp(_name, logs_names[i].name) == 0)
        {
            if (val < logs_names[i].first_instance)
            {
                logs_names[i].first_instance = val;
            }
            if (val > logs_names[i].last_instance)
            {
                logs_names[i].last_instance = val;
            }
            break;
        }
    }
    if ((i == log_name_table_index) && (i < DEV_LOG_MAX_IDS))
    {
        strncpy(logs_names[i].name, name, MAX_DEV_LOG_ID_NAME);
        if (val == -1)
        {
            val = LOG_NAME_NO_INSTANCE;
        }
        logs_names[i].last_instance = val;
        logs_names[i].first_instance = val;
        log_name_table_index++;
    }
}

void dev_log_get_log_name_table(char *buffer, uint32_t buf_len)
{
    uint32_t i = 0;
    uint32_t buf_len_free = buf_len;

    buffer[0] = '\0';
    for (i = 0; i < log_name_table_index; i++)
    {
        if (logs_names[i].first_instance == LOG_NAME_NO_INSTANCE)
        {
            snprintf(&buffer[strlen(buffer)], buf_len_free, "%s\n", logs_names[i].name);
        }
        else
        {
            snprintf(&buffer[strlen(buffer)], buf_len_free, "%s %d - %d\n", logs_names[i].name, logs_names[i].first_instance, logs_names[i].last_instance);
        }
        buffer[buf_len - 1] = '\0';
        buf_len_free = buf_len - strlen(buffer);
        if (buf_len_free <= 1)
        {
            DEV_LOG_ERROR_PRINTF("Error: dev_log_get_log_name_table too long\n");
            break;
        }
    }
}

static dev_log_id _bcm_dev_log_id_get_by_name(const char *name)
{
    uint32_t i;

    for (i = 0; i < BCM_SIZEOFARRAY(dev_log.ids); i++)
    {
        if (!dev_log.ids[i].is_active)
            continue;

        if (!strcmp(dev_log.ids[i].name, name))
        {
            return (dev_log_id)&dev_log.ids[i];
        }
    }

    return DEV_LOG_INVALID_ID;
}

static dev_log_id_parm *bcm_dev_log_get_free_id(void)
{
    uint32_t i;

    for (i = 0; i < BCM_SIZEOFARRAY(dev_log.ids); i++)
    {
        if (!dev_log.ids[i].is_active)
            return &dev_log.ids[i];
    }

    return NULL;
}

dev_log_id bcm_dev_log_id_register(const char *name,
    bcm_dev_log_level default_log_level,
    bcm_dev_log_id_type default_log_type)
{
    dev_log_id_parm *new_id;

    /* Check that we have room for one more ID */
    new_id = bcm_dev_log_get_free_id();
    if (!new_id)
    {
        DEV_LOG_ERROR_PRINTF("Error: Failed to register log ID for '%s' - out of free log IDs\n", name);
        return DEV_LOG_INVALID_ID;
    }

    /* Check that the log name isn't already registered */
    if (!(dev_log.flags & BCM_DEV_LOG_FLAG_ALLOW_DUPLICATES) && _bcm_dev_log_id_get_by_name(name) != DEV_LOG_INVALID_ID)
    {
        DEV_LOG_ERROR_PRINTF("Error: duplicate log name \"%s\"\n", name);
        return DEV_LOG_INVALID_ID;
    }

    /* Add prefix for kernel log_ids in order to avoid clash with similarly-names logs in the user space */
#ifdef __KERNEL__
    strcpy(new_id->name, "k_");
#endif

    /* Set log_id parameters */
    strncat(new_id->name, name, sizeof(new_id->name) - strlen(new_id->name));
    new_id->name[MAX_DEV_LOG_ID_NAME - 1] = '\0';

    new_id->default_log_type = default_log_type;
    new_id->default_log_level = default_log_level;

    dev_log_add_log_name_to_table(new_id->name);

    bcm_dev_log_id_set_levels_and_type_to_default((dev_log_id)new_id);
    new_id->style = BCM_DEV_LOG_STYLE_NORMAL;
    new_id->is_active = BCMOS_TRUE;

    return (dev_log_id)new_id;
}

void bcm_dev_log_id_unregister(dev_log_id id)
{
    dev_log_id_parm *parm = (dev_log_id_parm *)id;

    parm->is_active = BCMOS_FALSE;
    *parm->name = '\0';
}

bcmos_errno bcm_dev_log_id_set_type(dev_log_id id, bcm_dev_log_id_type log_type)
{
    dev_log_id_parm *parm = (dev_log_id_parm *)id;

    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        return BCM_ERR_PARM;
    }

    /* In linux kernel we only support save */
#ifdef __KERNEL__
    if (log_type & DEV_LOG_ID_TYPE_BOTH)
        log_type = DEV_LOG_ID_TYPE_SAVE;
#endif

    DEV_LOG_INFO_PRINTF("ID: 0x%lx, New log type: %d\n", id, (int)log_type);

    parm->log_type = log_type;

    /* In linux user space we need to notify kernel integration code */
#if defined(LINUX_KERNEL_SPACE) && !defined(__KERNEL__)
    if (using_inband_get())
    {
        bcm_dev_log_linux_id_set_type_ud(id, log_type);
    }
    else
    {
        bcm_dev_log_linux_id_set_type(id, log_type);
    }
#endif

    return BCM_ERR_OK;
}

bcmos_errno bcm_dev_log_id_set_level(dev_log_id id, bcm_dev_log_level log_level_print, bcm_dev_log_level log_level_save)
{
    dev_log_id_parm *parm = (dev_log_id_parm *)id;

    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        return BCM_ERR_PARM;
    }

    if ((log_level_print >= DEV_LOG_LEVEL_NUM_OF) || (log_level_save >= DEV_LOG_LEVEL_NUM_OF))
    {
        DEV_LOG_ERROR_PRINTF("Error: wrong parameters\n");
        return BCM_ERR_PARM;
    }

    DEV_LOG_INFO_PRINTF("ID: 0x%p, New: log_level_print=%u, log_level_save=%u\n",
        (void *)parm,
        log_level_print,
        log_level_save);

    parm->log_level_print = log_level_print;
    parm->log_level_save = log_level_save;

    /* In linux user space we need to notify kernel integration code */
#if defined(LINUX_KERNEL_SPACE) && !defined(__KERNEL__)
    if (using_inband_get())
    {
        bcm_dev_log_linux_id_set_level_ud(id, log_level_print, log_level_save);
    }
    else
    {
        bcm_dev_log_linux_id_set_level(id, log_level_print, log_level_save);
    }
#endif

    return BCM_ERR_OK;
}

bcmos_errno bcm_dev_log_id_set_levels_and_type_to_default(dev_log_id id)
{
    dev_log_id_parm *parm = (dev_log_id_parm *)id;

    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        return BCM_ERR_PARM;
    }

    parm->log_level_print = parm->default_log_level;
    parm->log_level_save = parm->default_log_level;
    parm->log_type = parm->default_log_type;

#ifdef TRIGGER_LOGGER_FEATURE
    memset(&parm->throttle,0, sizeof(dev_log_id_throttle));
    memset(&parm->trigger, 0, sizeof(dev_log_id_trigger));
    parm->throttle_log_level = DEV_LOG_LEVEL_NO_LOG;
    parm->trigger_log_level = DEV_LOG_LEVEL_NO_LOG;
#endif

    /* In linux kernel space we don't support PRINT, only SAVE */
#ifdef __KERNEL__
    if (parm->log_type & DEV_LOG_ID_TYPE_BOTH)
        parm->log_type = DEV_LOG_ID_TYPE_SAVE;
#endif

    return BCM_ERR_OK;
}

void bcm_dev_log_level_set_style(bcm_dev_log_level level, bcm_dev_log_style style)
{
    dev_log_level2style[level] = style;
}

bcmos_errno bcm_dev_log_id_set_style(dev_log_id id, bcm_dev_log_style style)
{
    dev_log_id_parm *parm = (dev_log_id_parm *)id;

    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        return BCM_ERR_PARM;
    }
    parm->style = style;
    return BCM_ERR_OK;
}

bcmos_errno bcm_dev_log_id_clear_counters(dev_log_id id)
{
    dev_log_id_parm *parm = (dev_log_id_parm *)id;

    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        return BCM_ERR_PARM;
    }
    memset(parm->counters, 0, sizeof(parm->counters));
    parm->lost_msg_cnt = 0;
    parm->print_skipped_count = 0;

    return BCM_ERR_OK;
}

bcmos_errno bcm_dev_log_id_get(dev_log_id id, dev_log_id_parm *parm)
{
    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        return BCM_ERR_PARM;
    }

    *parm = *(dev_log_id_parm *)id;

    return BCM_ERR_OK;
}

bcmos_errno bcm_dev_log_id_set(dev_log_id id, dev_log_id_parm *parm)
{
    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        return BCM_ERR_PARM;
    }

    *(dev_log_id_parm *)id = *parm;

    return BCM_ERR_OK;
}

dev_log_id bcm_dev_log_id_get_by_index(uint32_t index)
{
    if (index >= BCM_SIZEOFARRAY(dev_log.ids) || !dev_log.ids[index].is_active)
        return DEV_LOG_INVALID_ID;

    return (dev_log_id)&dev_log.ids[index];
}

uint32_t bcm_dev_log_get_index_by_id(dev_log_id id)
{
    uint32_t idx = (dev_log_id_parm *)id - &dev_log.ids[0];

    if (idx >= BCM_SIZEOFARRAY(dev_log.ids))
        idx = DEV_LOG_INVALID_INDEX;

    /* Return idx even is "is_active" is false. This is because the callers rely on this. */
    return idx;
}

dev_log_id bcm_dev_log_id_get_next(dev_log_id id)
{
    if (id == DEV_LOG_INVALID_ID)
        id = (dev_log_id)&dev_log.ids;
    else
        id = (dev_log_id)((dev_log_id_parm *)id + 1);

    for (; bcm_dev_log_get_index_by_id(id) != DEV_LOG_INVALID_INDEX && !((dev_log_id_parm *)id)->is_active;
        id = (dev_log_id)((dev_log_id_parm *)id + 1));
    return bcm_dev_log_get_index_by_id(id) == DEV_LOG_INVALID_INDEX ? DEV_LOG_INVALID_ID : id;
}

dev_log_id bcm_dev_log_id_get_by_name(const char *name)
{
    dev_log_id id;

    if (name == NULL)
    {
        return DEV_LOG_INVALID_ID;
    }

    id = _bcm_dev_log_id_get_by_name(name);
    if (id == DEV_LOG_INVALID_ID)
    {
        DEV_LOG_ERROR_PRINTF("Error: can't find name\n");
    }

    return id;
}

bcmos_bool bcm_dev_log_get_control(void)
{
    return dev_log.state == BCM_DEV_LOG_STATE_ENABLED;
}

uint32_t bcm_dev_log_get_num_of_messages(const bcm_dev_log_file *file)
{
    return file->u.mem_file.file_header.num_msgs;
}

void bcm_dev_log_set_control(bcmos_bool control)
{
    if (control && dev_log.state == BCM_DEV_LOG_STATE_DISABLED)
        dev_log.state = BCM_DEV_LOG_STATE_ENABLED;
    else if (!control && dev_log.state == BCM_DEV_LOG_STATE_ENABLED)
        dev_log.state = BCM_DEV_LOG_STATE_DISABLED;
}

bcm_dev_log_file_flags bcm_dev_log_get_file_flags(uint32_t file_id)
{
    return dev_log.files[file_id].file_parm.flags;
}

void bcm_dev_log_set_file_flags(uint32_t file_id, bcm_dev_log_file_flags flags)
{
    dev_log.files[file_id].file_parm.flags = flags;
}

bcm_dev_log_flags bcm_dev_log_get_flags(void)
{
    return dev_log.flags;
}

void bcm_dev_log_set_flags(bcm_dev_log_flags flags)
{
    dev_log.flags = flags;
}

void bcm_dev_log_set_print_cb(bcm_dev_log_print_cb cb)
{
    dev_log.dev_log_parm.print_cb = cb;
}

void bcm_dev_log_set_get_time_cb(bcm_dev_log_get_time_cb cb)
{
    dev_log.dev_log_parm.get_time_cb = cb;
}

void bcm_dev_log_set_time_to_str_cb(bcm_dev_log_time_to_str_cb cb)
{
    dev_log.dev_log_parm.time_to_str_cb = cb;
}

#ifdef TRIGGER_LOGGER_FEATURE
/********************************************************************************************/
/*																							*/
/* Name: bcm_dev_log_set_throttle															*/
/*																							*/
/* Abstract: Set throttle level for the specific log is and its level						*/
/*																							*/
/* Arguments:																				*/
/*   - id		- The ID in the Dev log (what we got form bcm_dev_log_id_register)		*/
/*   - log_level	- log level												                */
/*   - throttle	- throttle number, 0 - no throttle										*/
/*																							*/
/* Return Value:																			*/
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)              */
/*																							*/
/********************************************************************************************/
bcmos_errno bcm_dev_log_set_throttle(dev_log_id id, bcm_dev_log_level log_level, uint32_t throttle)
{
    dev_log_id_parm *parm = (dev_log_id_parm *)id;

    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        return BCM_ERR_PARM;
    }
    parm->throttle_log_level = log_level;
    parm->throttle.threshold = throttle;
    parm->throttle.counter = 0;

    return BCM_ERR_OK;
}

/********************************************************************************************/
/*																							*/
/* Name: bcm_dev_log_set_trigger															*/
/*																							*/
/* Abstract: Set trigger counters for the specific log is and its level						*/
/*																							*/
/* Arguments:																				*/
/*   - id		- The ID in the Dev log (what we got form bcm_dev_log_id_register)		*/
/*   - log_level	- log level											                	*/
/*   - start 	- start printing after this number, 0 - no trigger						*/
/*   - stop   	- stop printing after this number,  0 - do not stop						*/
/*   - repeat 	- start printing after this number, 0 - no repeat, -1 always			*/
/*																							*/
/* Return Value:																			*/
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)              */
/*																							*/
/********************************************************************************************/
bcmos_errno bcm_dev_log_set_trigger(dev_log_id id, bcm_dev_log_level log_level, uint32_t start, uint32_t stop, int32_t repeat)
{
    dev_log_id_parm *parm = (dev_log_id_parm *)id;

    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        return BCM_ERR_PARM;
    }
    parm->trigger_log_level = log_level;
    parm->trigger.start_threshold = start;
    parm->trigger.stop_threshold = stop;
    parm->trigger.repeat_threshold = repeat;
    parm->trigger.counter = 0;
    parm->trigger.repeat = 0;

    return BCM_ERR_OK;
}
#endif /* TRIGGER_LOGGER_FEATURE */

/* Get file info: max data size, used bytes */
bcmos_errno bcm_dev_log_get_file_info(bcm_dev_log_file *file, uint32_t *file_size, uint32_t *used_bytes)
{
    if (!file || !file_size || !used_bytes)
        return BCM_ERR_PARM;
    /* Only supported for memory files */
    if (!bcm_dev_log_is_memory_file(file))
        return BCM_ERR_NOT_SUPPORTED;
    *file_size = file->u.mem_file.file_header.data_size;
    *used_bytes = (file->u.mem_file.file_header.file_wrap_cnt || file->is_full) ?
        file->u.mem_file.file_header.data_size : file->u.mem_file.file_header.write_offset;
    return BCM_ERR_OK;
}

/* Register indication to be sent when file utilization crosses threshold */
bcmos_errno bcm_dev_log_almost_full_ind_register(bcm_dev_log_file *file, uint32_t used_bytes_threshold,
    F_dev_log_file_almost_full send_ind_cb, long ind_cb_priv)
{
    if (!file || (used_bytes_threshold && !send_ind_cb))
        return BCM_ERR_PARM;
    /* Only supported for memory files */
    if (!bcm_dev_log_is_memory_file(file))
        return BCM_ERR_NOT_SUPPORTED;

    bcmos_mutex_lock(&file->u.mem_file.mutex);
    file->almost_full.threshold = used_bytes_threshold;
    file->almost_full.send_ind_cb = send_ind_cb;
    file->almost_full.priv = ind_cb_priv;
    file->almost_full.ind_sent = BCMOS_FALSE;
    bcmos_mutex_unlock(&file->u.mem_file.mutex);

    return BCM_ERR_OK;
}

#endif /* ENABLE_LOG */
