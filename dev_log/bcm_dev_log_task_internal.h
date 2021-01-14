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

#ifndef __BCM_DEV_LOG_TASK_INTERNAL_H_
#define __BCM_DEV_LOG_TASK_INTERNAL_H_

#ifdef ENABLE_LOG

#include <bcmos_system.h>

#define LOG_NAME_NO_INSTANCE 0xff
#define LOG_NAME_LENGTH (MAX_DEV_LOG_ID_NAME + 1)

typedef enum
{
    BCM_DEV_LOG_STATE_UNINITIALIZED,
    BCM_DEV_LOG_STATE_DISABLED,
    BCM_DEV_LOG_STATE_ENABLED,
} bcm_dev_log_state;

typedef struct
{
    bcm_dev_log_parm dev_log_parm;
    bcm_dev_log_file files[DEV_LOG_MAX_FILES]; /* log files */
    uint32_t msg_count; /* Message counter */
    dev_log_id_parm ids[DEV_LOG_MAX_IDS]; /* dev_log IDS array */
    bcm_dev_log_state state;
    bcmos_msg_queue save_queue; /* Log messages to be saved to RAM (first stage of pipeline) */
    bcmos_msg_queue print_queue; /* Log messages to be printed (second stage of pipeline) */
    bcmos_task save_task;
    bcmos_task print_task;
    bcmos_sem save_task_is_terminated;
    bcmos_sem print_task_is_terminated;
    bcmos_msg_pool pool;
    bcm_dev_log_flags flags; /* General flags applied on the entire feature (unlike file flags which reside in 'files' sub-structure). */
} bcm_dev_log;

typedef struct
{
    dev_log_id_parm *log_id;
    uint32_t time_stamp;
    bcm_dev_log_level msg_level;
    uint32_t flags;
    union
    {
        struct
        {
            const char *fmt;
            /* Room for MAX + 1 arguments since the argument list needs to start on an 8-byte boundary - the first
             * entry may be unused if the array doesn't naturally start on an 8-byte boundary. */
            const void *args[DEV_LOG_MAX_ARGS + 1];
        } fmt_args; /* Relevant in default mode - when not using BCM_LOG_FLAG_CALLER_FMT */
        char str[MAX_DEV_LOG_STRING_SIZE]; /* Relevant only if using BCM_LOG_FLAG_CALLER_FMT */
    } u;
} dev_log_queue_msg;

typedef struct
{
    char name[LOG_NAME_LENGTH];
    uint8_t first_instance;
    uint8_t last_instance;
} log_name_table;

extern bcm_dev_log dev_log;
extern const char *log_level_str;

extern log_name_table logs_names[DEV_LOG_MAX_IDS];
extern uint8_t log_name_table_index;

bcmos_errno _bcm_dev_log_file_clear_no_lock(uint32_t file_index);

#endif /* ENABLE_LOG */

#endif /* __BCM_DEV_LOG_TASK_INTERNAL_H_ */
