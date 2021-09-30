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

static bcmos_timer dev_log_timer;

/* Store timestamp per every rate-limited log ID. */
static uint64_t rate_limit_id2timestamp[DEV_LOG_RATE_LIMIT_ID__NUM_OF];

const char *dev_log_basename(const char *str)
{
    const char *slash;
    if ((slash = strchr(str, '/')))
    {
        const char *str0 = str;
        str = strchr(slash+1, ' ');
        /* If log format string was created by BCM_LOG macro and there is no corruption of some kind
         * str above is guaranteed to be != NULL. However, making str!=NULL assumption makes dev_log
         * vulnerable to bugs in the caller. In this case the following inexpensive check prevents crash
         * in dev_Log and helps in identifying the real culprit.
         */
        if (!str)
            return str0;
        while (str[0] != '/')
            str--;
        str++;
    }
    return str;
}

#ifdef TRIGGER_LOGGER_FEATURE

/* check if the message fits the level and the other criteria for a trigger
   return 1 if yes, the message will be printed
   and returns 0 if the message will not be printed
*/
static bcmos_bool check_trigger(dev_log_id_parm *id, bcm_dev_log_level log_level)
{
    /* the level of the message must be exactly the trigger level */
    if (id->trigger_log_level != log_level)
        return BCMOS_FALSE; /* do not print the message  - the level does not fit */

    id->trigger.counter++;
    if (id->trigger.counter >= id->trigger.start_threshold)
    {
        if (id->trigger.counter >= id->trigger.stop_threshold)
        {
            /* trigger finished, check repeat */
            if (id->trigger.repeat_threshold)
            {
                id->trigger.repeat++;
                if (id->trigger.repeat < id->trigger.repeat_threshold)
                {
                    /* rewind trigger conditions */
                    id->trigger.counter = 0;
                }
            }
        }
        else /* trigger is active : counter greater than start and less than end */
            return BCMOS_TRUE; /* print the message */
    }
    return BCMOS_FALSE;/* do not print the message  - still less than start threshold */
}

/* check if the message fits the level and the criteria for throttle
   return 1 if yes, the message will be printed
   and returns 0 if the message will not be printed
*/
static bcmos_bool check_throttle(dev_log_id_parm *id, bcm_dev_log_level log_level)
{
    /* check if any throttle is defined */
    if (id->throttle_log_level != DEV_LOG_LEVEL_NO_LOG)
        return BCMOS_TRUE; /* print the message  - no trigger is set */

    /* the level of the message must be exactly the throttle level */
    if (id->throttle_log_level != log_level)
        return BCMOS_FALSE; /* do not print the message  - the level does not fit */

    id->throttle.counter++;
    if (id->throttle.counter >= id->throttle.threshold)
    {
        id->throttle.counter = 0;
        return BCMOS_TRUE;
    }
    return BCMOS_FALSE;/* do not print the message  - still less than start threshold */
}

#endif

#if defined(BCM_SUBSYSTEM_HOST)
static bcmos_mutex dev_log_lock;
#endif

void bcm_dev_log_frontend_init(void)
{
#if defined(BCM_SUBSYSTEM_HOST)
    bcmos_mutex_create(&dev_log_lock, 0, "dev_log_lock");
#endif
}

static bcmos_timer_rc bcm_dev_log_msg_send_timer_cb(bcmos_timer *timer, long data)
{
    bcmos_msg *msg = (bcmos_msg *)data;
    bcmos_msg_send(&dev_log.save_queue, msg, BCMOS_MSG_SEND_AUTO_FREE);
    return BCMOS_TIMER_OK;
}

uint8_t bcm_dev_log_pool_occupancy_percent_get(void)
{
    bcmos_msg_pool_info msg_pool_info;
    bcmos_errno error = bcmos_msg_pool_query(&dev_log.pool, &msg_pool_info);
    if (error != BCM_ERR_OK)
    {
        DEV_LOG_ERROR_PRINTF("bcmos_msg_pool_query() returned %s (%d)\n", bcmos_strerror(error), error);
        return 0;
    }
    return (uint8_t)((100 * (msg_pool_info.parm.size - msg_pool_info.stat.free)) / msg_pool_info.parm.size);
}

static bcmos_bool bcm_dev_log_should_drop(
    dev_log_id_parm *id,
    bcm_dev_log_level log_level,
    uint32_t rate_us,
    dev_log_rate_limit_id rate_limit_id)
{
    /* If the msg pool is sufficiently full, drop all non-error messages */
    if (!bcm_dev_log_level_is_error(log_level) &&
        bcm_dev_log_pool_occupancy_percent_get() >= DEV_LOG_ERROR_ONLY_THRESHOLD_PERCENT)
    {
        bcm_dev_log_drop_report();
        return BCMOS_TRUE;
    }

#ifdef TRIGGER_LOGGER_FEATURE
    /* if trigger defined - ignore throttle and printing level */
    if (id->trigger_log_level != DEV_LOG_LEVEL_NO_LOG)
        return check_trigger(id, log_level);
#endif

    /* if trigger is not fullfilled - check other conditions */
    if (log_level > id->log_level_print && log_level > id->log_level_save)
        return BCMOS_TRUE;

#ifdef TRIGGER_LOGGER_FEATURE
    if (!check_throttle(id, log_level))
        return BCMOS_TRUE;
#endif

    if (rate_us && rate_limit_id != DEV_LOG_RATE_LIMIT_ID_NONE)
    {
        uint64_t curr_timestamp;

        /* Do rate limit. */
        curr_timestamp = bcmos_timestamp64();
        if (curr_timestamp - rate_limit_id2timestamp[rate_limit_id] < rate_us)
            return BCMOS_TRUE; /* Filter out this message. */
        rate_limit_id2timestamp[rate_limit_id] = curr_timestamp;
    }

    return BCMOS_FALSE;
}

#if defined(BCM_SUBSYSTEM_HOST)

/* The following functions might be used on the host side to make sure
   that multiple log entries are "together",ie are not interleaved
   with other log entries. It might be necessary if application needs to log
   a very long string that must be split into multiple log entries.
*/
void bcm_dev_log_lock(void)
{
    bcmos_mutex_lock(&dev_log_lock);
}

void bcm_dev_log_unlock(void)
{
    bcmos_mutex_unlock(&dev_log_lock);
}

#endif /* #if defined(BCM_SUBSYSTEM_HOST) */

const char * last_format = NULL;
static void _bcm_dev_log_vlog(dev_log_id id,
    bcm_dev_log_level log_level,
    uint32_t flags,
    uint32_t rate_us,
    dev_log_rate_limit_id rate_limit_id,
    const char *fmt,
    va_list args)
{
    dev_log_id_parm *parm = (dev_log_id_parm *)id;
    dev_log_queue_msg *log_queue_msg;
    bcmos_errno error = BCM_ERR_OK;
    bcmos_msg *msg;
    last_format = fmt;

    if (dev_log.state != BCM_DEV_LOG_STATE_ENABLED)
    {
        if (dev_log.flags & BCM_DEV_LOG_FLAG_DISABLED_WITH_PRINTF)
            DEV_LOG_VPRINTF(fmt, args);
        return;
    }
    if (!id || (id == DEV_LOG_INVALID_ID))
    {
        /* If this ID was not registered - or registered incorrectly */
        DEV_LOG_ERROR_PRINTF("Error: id not valid (0x%x)\n", (unsigned int)id);
        DEV_LOG_VPRINTF(fmt, args); /* This will allow us to debug what line caused the bug. */
        return;
    }
    if ((log_level >= DEV_LOG_LEVEL_NUM_OF) || (log_level == DEV_LOG_LEVEL_NO_LOG))
    {
        DEV_LOG_ERROR_PRINTF("log_level (%u) is invalid\n", log_level);
        DEV_LOG_VPRINTF(fmt, args); /* This will allow us to debug what line caused the bug. */
        return;
    }
    if (parm->log_type == DEV_LOG_ID_TYPE_NONE)
    {
        return;
    }
#if defined(BCM_SUBSYSTEM_HOST) || defined(ASPEN_VLSI_SIM)
    /* Always use CALLER_FMT mode on the host to avoid portability issues with
     * transferring va_list as an array */
    flags |= BCM_LOG_FLAG_CALLER_FMT;
#endif

    /* Update log id counters  */
    parm->counters[log_level]++;

    if (bcm_dev_log_should_drop(parm, log_level, rate_us, rate_limit_id))
        return;

    msg = bcmos_msg_pool_alloc(&dev_log.pool);
    if (!msg)
    {
        bcm_dev_log_drop_report();
        return;
    }
    log_queue_msg = msg->data;
    /* Create log message */
    log_queue_msg->log_id = parm;
    log_queue_msg->time_stamp = dev_log.dev_log_parm.get_time_cb();
    log_queue_msg->msg_level = log_level;
    log_queue_msg->flags = flags;
#ifndef BCM_SUBSYSTEM_HOST
    /* It is not really necessary to compile out non CALLER_FMT case on the host.
     * However, keeping unused code will make Coverity unhappy */
    if (unlikely(flags & BCM_LOG_FLAG_CALLER_FMT))
    {
#endif /* #ifndef BCM_SUBSYSTEM_HOST */
        vsnprintf(log_queue_msg->u.str, MAX_DEV_LOG_STRING_SIZE, (flags & BCM_LOG_FLAG_FILENAME_IN_FMT) ? dev_log_basename(fmt) : fmt, args);
#ifndef BCM_SUBSYSTEM_HOST
    }
    else
    {
        uint32_t i;
        uint32_t offset;
        log_queue_msg->u.fmt_args.fmt = fmt;

        offset = ((long)log_queue_msg->u.fmt_args.args % 8 == 0) ? 0 : 1; /* start on an 8-byte boundary */
        for (i = 0; i < DEV_LOG_MAX_ARGS; i++)
        {
            log_queue_msg->u.fmt_args.args[i + offset] = va_arg(args, void *);
        }
    }
#endif /* #ifndef BCM_SUBSYSTEM_HOST */

    if (bcmos_sem_post_is_allowed())
    {
#ifdef BCM_SUBSYSTEM_HOST
        bcm_dev_log_lock();
#endif
        error = bcmos_msg_send(&dev_log.save_queue, msg, BCMOS_MSG_SEND_AUTO_FREE);
#ifdef BCM_SUBSYSTEM_HOST
        bcm_dev_log_unlock();
#endif
    }
    else
    {
        bcmos_timer_parm timer_params =
        {
            .name = "dev_log_timer",
            .handler = bcm_dev_log_msg_send_timer_cb,
        };

        if (!(dev_log_timer.flags & BCMOS_TIMER_FLAG_VALID))
            bcmos_timer_create(&dev_log_timer, &timer_params);
        /* Limitation: We don't send more than 1 logger message even if _bcm_dev_log_vlog() was called multiple timers in IRQs disabled mode because we have a single timer. */
        if (!bcmos_timer_is_running(&dev_log_timer))
        {
            bcmos_timer_handler_set(&dev_log_timer, bcm_dev_log_msg_send_timer_cb, (long)msg);
            bcmos_timer_start(&dev_log_timer, 0);
        }
    }

    if (error != BCM_ERR_OK)
    {
        parm->lost_msg_cnt++;
    }
}

void bcm_dev_log_vlog(dev_log_id id,
    bcm_dev_log_level log_level,
    uint32_t flags,
    const char *fmt,
    va_list args)
{
    _bcm_dev_log_vlog(id, log_level, flags, 0, DEV_LOG_RATE_LIMIT_ID_NONE, fmt, args);
}

/* IMPORTANT!!!
 * The function bcm_dev_log_log() must have even number of arguments before the '...' (see comments on header file).
 */
void bcm_dev_log_log(dev_log_id id,
    bcm_dev_log_level log_level,
    uint32_t flags,
    const char *fmt,
    ...)
{
    va_list args;

    va_start(args, fmt);
    bcm_dev_log_vlog(id, log_level, flags, fmt, args);
    va_end(args);
}

void bcm_dev_log_log_ratelimit(dev_log_id id,
    bcm_dev_log_level log_level,
    uint32_t flags,
    uint32_t rate_us,
    dev_log_rate_limit_id rate_limit_id,
    const char *fmt,
    ...)
{
    va_list args;

    va_start(args, fmt);
    _bcm_dev_log_vlog(id, log_level, flags, rate_us, rate_limit_id, fmt, args);
    va_end(args);
}

#ifdef BCMOS_TRACE_IN_DEV_LOG

static dev_log_id bcmos_trace_dev_log_id[] =
{
    [BCMOS_TRACE_LEVEL_NONE] = DEV_LOG_INVALID_ID,
    [BCMOS_TRACE_LEVEL_ERROR] = DEV_LOG_INVALID_ID,
    [BCMOS_TRACE_LEVEL_INFO] = DEV_LOG_INVALID_ID,
    [BCMOS_TRACE_LEVEL_VERBOSE] = DEV_LOG_INVALID_ID,
    [BCMOS_TRACE_LEVEL_DEBUG] = DEV_LOG_INVALID_ID
};

static bcm_dev_log_level bcmos_trace_dev_log_level[] =
{
    [BCMOS_TRACE_LEVEL_ERROR] = DEV_LOG_LEVEL_ERROR,
    [BCMOS_TRACE_LEVEL_INFO] = DEV_LOG_LEVEL_INFO,
    [BCMOS_TRACE_LEVEL_VERBOSE] = DEV_LOG_LEVEL_INFO,
    [BCMOS_TRACE_LEVEL_DEBUG] = DEV_LOG_LEVEL_DEBUG
};

#endif

/********************************************************************************************/
/*                                                                                          */
/* Name: bcm_dev_log_os_trace_init                                                          */
/*                                                                                          */
/* Abstract: Direct bcmos_trace() output to log                                             */
/* Arguments: NONE                                                                          */
/*                                                                                          */
/* Return Value:                                                                            */
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)              */
/*                                                                                          */
/********************************************************************************************/
bcmos_errno bcm_dev_log_os_trace_init(void)
{
#ifdef BCMOS_TRACE_IN_DEV_LOG
    bcmos_trace_dev_log_id[BCMOS_TRACE_LEVEL_ERROR] = bcm_dev_log_id_register("trace_error",
        DEV_LOG_LEVEL_ERROR, DEV_LOG_ID_TYPE_BOTH);
    bcmos_trace_dev_log_id[BCMOS_TRACE_LEVEL_INFO] = bcm_dev_log_id_register("trace_info",
        DEV_LOG_LEVEL_INFO, DEV_LOG_ID_TYPE_BOTH);
    bcmos_trace_dev_log_id[BCMOS_TRACE_LEVEL_VERBOSE] = bcmos_trace_dev_log_id[BCMOS_TRACE_LEVEL_INFO];
    bcmos_trace_dev_log_id[BCMOS_TRACE_LEVEL_DEBUG] = bcm_dev_log_id_register("trace_debug",
        DEV_LOG_LEVEL_DEBUG, DEV_LOG_ID_TYPE_BOTH);
    if (bcmos_trace_dev_log_id[BCMOS_TRACE_LEVEL_ERROR] == DEV_LOG_INVALID_ID ||
        bcmos_trace_dev_log_id[BCMOS_TRACE_LEVEL_INFO]  == DEV_LOG_INVALID_ID ||
        bcmos_trace_dev_log_id[BCMOS_TRACE_LEVEL_DEBUG] == DEV_LOG_INVALID_ID)
    {
        return BCM_ERR_NORES;
    }
    return BCM_ERR_OK;
#else /* #ifdef BCMOS_TRACE_IN_DEV_LOG */
    return BCM_ERR_NOT_SUPPORTED;
#endif
}

#ifdef BCMOS_TRACE_IN_DEV_LOG

/* Direct OS trace to dev_log */
void bcmos_trace(bcmos_trace_level level, const char *format, ...)
{
    va_list args;

    va_start(args, format);

    if (bcmos_trace_dev_log_id[level] == DEV_LOG_INVALID_ID)
    {
        /* The OS trace hasn't been initialized yet, so just use system printf. */
        bcmos_vprintf(format, args);
    }
    else
    {
        if (dev_log.state == BCM_DEV_LOG_STATE_ENABLED)
        {
            if (level == BCMOS_TRACE_LEVEL_ERROR)
                bcm_dev_log_vlog(bcmos_trace_dev_log_id[level], bcmos_trace_dev_log_level[level], BCM_LOG_FLAG_CALLER_FMT, format, args);
            else
                bcm_dev_log_vlog(bcmos_trace_dev_log_id[level], bcmos_trace_dev_log_level[level], 0, format, args);
        }
    }

    va_end(args);
}

#endif

static const char *double2two_int_leading_zeros_arr[] =
{
    "",
    "0",
    "00",
    "000",
    "0000",
    "00000",
    "000000",
    "0000000",
    "00000000",
    "000000000",
    "0000000000",
    "00000000000",
    "000000000000",
    "0000000000000",
    "00000000000000",
    "000000000000000",
};

void dev_log_double2two_int_conv(double double_val, uint8_t precision, double2two_int_t *result)
{
    ulong_t i;
    double fraction;

    result->int_val = double_val;
    result->leading_zeros = "";
    result->fraction = 0;

    fraction = (double_val - (double)result->int_val);

    if (!fraction)
        return; /* Corner case: the given value is 0. */

    /* Calculate the number of leading zeros (in i) and point to the corresponding leading zero string. */
    for (i = 0; i < MIN(16, precision); i++)
    {
        if (fraction * pow(10, i) > 0.1)
        {
            result->leading_zeros = double2two_int_leading_zeros_arr[i];
            break;
        }
    }

    if (precision <= i)
        return; /* We "wasted" all the precision on the leading zeros. */

    result->fraction = fraction * pow(10, precision);
}

char *dev_log_double2str_conv(double double_val, uint8_t precision, char *str)
{
    double2two_int_t result;

    dev_log_double2two_int_conv(double_val, precision, &result);
    sprintf(str, "%-lu.%s%-lu", result.int_val, result.leading_zeros, result.fraction);

    return str;
}

#ifdef __KERNEL__
EXPORT_SYMBOL(bcm_dev_log_id_register);
EXPORT_SYMBOL(bcm_dev_log_id_unregister);
EXPORT_SYMBOL(bcm_dev_log_log);
EXPORT_SYMBOL(bcmos_trace);
#endif

#endif /* ENABLE_LOG */
