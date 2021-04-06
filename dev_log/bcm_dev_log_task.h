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

#ifndef __BCM_DEV_LOG_TASK_H_
#define __BCM_DEV_LOG_TASK_H_

#include "bcm_dev_log_api.h"

/* Because we cast from dev_log_id to pointer type in bcm_dev_log.c, we want it to be the same size as a pointer size (e.g: "typedef uint32_t dev_log_id" won't work
 * on 64bit platform). */
typedef unsigned long dev_log_id;

#define DEV_LOG_INVALID_ID              (dev_log_id)UINT_MAX

#ifdef ENABLE_LOG

/* Uncomment the following line to enable info prints for dev_log debugging */
/* #define DEV_LOG_DEBUG */

#include <bcmos_system.h>

/********************************************/
/*                                          */
/* Log macros                               */
/*                                          */
/********************************************/

/********************************************/
/*                                          */
/* Defines/Typedefs                         */
/*                                          */
/********************************************/

#define STRINGIFY(x) #x
#define STRINGIFY_EXPAND(str) STRINGIFY(str)

#ifdef __KERNEL__
#define DEV_LOG_PRINTF printk
#define DEV_LOG_VPRINTF vprintk
#else
#define DEV_LOG_PRINTF bcmos_printf
#define DEV_LOG_VPRINTF bcmos_vprintf
#endif

#ifdef DEV_LOG_DEBUG
#define DEV_LOG_INFO_PRINTF(fmt, args...) DEV_LOG_PRINTF("(%s:" STRINGIFY_EXPAND(__LINE__) ") " fmt, __FUNCTION__, ##args)
#else
static inline void dev_log_info_printf_ignore(const char *fmt, ...) { }
#define DEV_LOG_INFO_PRINTF(fmt, args...) dev_log_info_printf_ignore(fmt, ##args)
#endif
#define DEV_LOG_ERROR_PRINTF(fmt, args...) DEV_LOG_PRINTF("(%s:" STRINGIFY_EXPAND(__LINE__) ") " fmt, __FUNCTION__, ##args)

/* IMPORTANT! when modifying DEV_LOG_MAX_ARGS,
 * don't forget to add/remove _BCM_LOG_ARGS... macros in order to force number of arguments in compile time
 */
#define DEV_LOG_MAX_ARGS                36
/* String bigger than this size will be cut                     */
#define MAX_DEV_LOG_ID_NAME             32  /* Maximum size of log_id name */
#define DEV_LOG_MAX_IDS                 512
#define DEV_LOG_MAX_FILES               2
#define MAX_DEV_LOG_STRING_SIZE         256 /* Note that this size includes header. */
#define MAX_DEV_LOG_HEADER_SIZE         (7 + 16 + 20) /* (time=16, ID=20, delimiters=7) */
#define MAX_DEV_LOG_STRING_NET_SIZE     (MAX_DEV_LOG_STRING_SIZE - MAX_DEV_LOG_HEADER_SIZE)
#define DEV_LOG_INVALID_INDEX           UINT_MAX
#define DEV_LOG_DROP_REPORT_RATE_US     1000000 /* 1 second */
#define DEV_LOG_DROP_REPORT_DROP_THRESHOLD 1000
#define DEV_LOG_ENDIAN                  BCMOS_ENDIAN_LITTLE

/* If the log message pool utilization is >= this percentage, do not print messages (only save them).
 * (note that error/fatal messages will not objey this rule). */
#define DEV_LOG_SKIP_PRINT_THRESHOLD_PERCENT 50

/* If the log message pool utilization is >= this percentage, drop all messages that aren't 'error' or 'fatal' level. */
#define DEV_LOG_ERROR_ONLY_THRESHOLD_PERCENT 75

/* Log level enum */
typedef enum
{
    DEV_LOG_LEVEL_NO_LOG = 0,
    DEV_LOG_LEVEL_FATAL,
    DEV_LOG_LEVEL_ERROR,
    DEV_LOG_LEVEL_WARNING,
    DEV_LOG_LEVEL_INFO,
    DEV_LOG_LEVEL_DEBUG,

    DEV_LOG_LEVEL_NUM_OF
} bcm_dev_log_level;

/* Log type enum */
typedef enum
{
    /* Bit[0] - Print Enable, Bit[1] - Save Enable */
    DEV_LOG_ID_TYPE_NONE = 0,       /* NO SAVE, NO PRINT*/
    DEV_LOG_ID_TYPE_PRINT = 1,
    DEV_LOG_ID_TYPE_SAVE = 1 << 1,
    DEV_LOG_ID_TYPE_BOTH = DEV_LOG_ID_TYPE_PRINT | DEV_LOG_ID_TYPE_SAVE, /* SAVE & PRINT */
} bcm_dev_log_id_type;

typedef enum
{
    BCM_DEV_LOG_FLAG_NONE = 0,

    /* Even if logger is disabled, BCM_LOG() calls are redirected to bcmos_printf(). */
    BCM_DEV_LOG_FLAG_DISABLED_WITH_PRINTF = 1 << 0,

    /* When bcm_dev_log_destroy() is called, do not wait for outstanding log messages to be drained. Discard the
     * messages and destroy the task immediately. */
    BCM_DEV_LOG_FLAG_DESTROY_IMMEDIATELY = 1 << 1,

    /* Allow registration of duplicate names. Typically this is used when killing a task and creating it again. */
    BCM_DEV_LOG_FLAG_ALLOW_DUPLICATES = 1 << 2,
} bcm_dev_log_flags;

typedef enum
{
    BCM_DEV_LOG_FILE_FLAG_NONE = 0,
    BCM_DEV_LOG_FILE_FLAG_VALID = 1, /**< file is valid */
    BCM_DEV_LOG_FILE_FLAG_WRAP_AROUND = 1 << 1, /**< new messages will override old */
    BCM_DEV_LOG_FILE_FLAG_STOP_WHEN_FULL = 1 << 2, /**< stop logging if the file is full */
    BCM_DEV_LOG_FILE_FLAG_CLEAR_AFTER_READ = 1 << 4, /**< auto-clear log when it is fully read */
} bcm_dev_log_file_flags;

typedef enum
{
    BCM_DEV_LOG_STYLE_NORMAL,
    BCM_DEV_LOG_STYLE_BOLD,
    BCM_DEV_LOG_STYLE_UNDERLINE,
    BCM_DEV_LOG_STYLE_BLINK,
    BCM_DEV_LOG_STYLE_REVERSE_VIDEO,
} bcm_dev_log_style;

/********************************************/
/*                                          */
/* Callbacks functions                      */
/*                                          */
/********************************************/

/* Default logger ID */
extern dev_log_id def_log_id;

typedef struct bcm_dev_log_file_parm bcm_dev_log_file_parm;
typedef struct bcm_dev_log_file bcm_dev_log_file;

/****************************************************************************************/
/* OPEN CALLBACK: open memory/file                                                      */
/* file_parm - file parameters                                                          */
/* file      - file                                                                     */
/****************************************************************************************/
typedef bcmos_errno (*bcm_dev_log_file_open_cb)(const bcm_dev_log_file_parm *file_parm, bcm_dev_log_file *file);

/****************************************************************************************/
/* CLOSE CALLBACK: close memory/file                                                    */
/* file      - file handle                                                              */
/****************************************************************************************/
typedef bcmos_errno (*bcm_dev_log_file_close_cb)(bcm_dev_log_file *file);

/****************************************************************************************/
/* REWIND CALLBACK: clears memory/file                                                  */
/* file      - file handle                                                              */
/****************************************************************************************/
typedef bcmos_errno (*bcm_dev_log_file_rewind_cb)(bcm_dev_log_file *file);

/****************************************************************************************/
/* READ_CALLBACK: read form memory/file                                                 */
/* offset - the offset in bytes to read from, output                                    */
/* buf    - Where to put the result                                                     */
/* length - Buffer length                                                               */
/* This function should return the number of bytes actually read from file or 0 if EOF  */
/****************************************************************************************/
typedef int (*bcm_dev_log_file_read_cb)(bcm_dev_log_file *file, uint32_t *offset, void *buf, uint32_t length);

/****************************************************************************************/
/* WRITE_CALLBACK: write form memory/file                                               */
/* buf    - The buffer that should be written                                           */
/* length - The number of bytes to write                                                */
/* This function should return the number of bytes actually written to file or 0 if EOF */
/****************************************************************************************/
typedef int (*bcm_dev_log_file_write_cb)(bcm_dev_log_file *file, const void *buf, uint32_t length);

/* File almost full indication callback prototype */
typedef bcmos_errno (*F_dev_log_file_almost_full)(long priv);

/* File parameters */
struct bcm_dev_log_file_parm
{
    bcm_dev_log_file_type type;
    /* File-access callbacks can be NULL for memory files, in this case start_addr    */
    /* should be a valid memory address, all read/writes options will be        */
    /* performed directly to this memory                                        */
    void *start_addr;
    uint32_t size;
    bcm_dev_log_file_open_cb open_cb;
    bcm_dev_log_file_close_cb close_cb;
    bcm_dev_log_file_write_cb write_cb;
    bcm_dev_log_file_read_cb read_cb;
    bcm_dev_log_file_rewind_cb rewind_cb;
    bcm_dev_log_file_flags flags;
    void *udef_parms;
};

#define FILE_MAGIC_STR_SIZE             16
#define FILE_MAGIC_STR "@LOGFILE MAGIC@" /* length should be FILE_MAGIC_STR_SIZE (including '\0') */

/* File almost full indication control info */
typedef struct dev_log_almost_full_info
{
    F_dev_log_file_almost_full send_ind_cb;
    uint32_t threshold;
    bcmos_bool ind_sent;
    long priv;
} dev_log_almost_full_info;

/* Memory file header */
typedef struct dev_log_mem_file_header
{
    uint32_t file_wrap_cnt;
    uint32_t write_offset;
    uint32_t data_size;
    uint32_t num_msgs;
    char file_magic[FILE_MAGIC_STR_SIZE];
    char msg_buffer[0];
} dev_log_mem_file_header;

struct bcm_dev_log_file
{
    bcm_dev_log_file_parm file_parm;
    dev_log_almost_full_info almost_full;
    bcmos_bool is_full;
    union
    {
        /* Memory file */
        struct
        {
            bcmos_mutex mutex; /* Mutex to lock file access while printing it */
            dev_log_mem_file_header file_header;
        } mem_file;

#ifdef BCM_OS_POSIX
        FILE *reg_file_handle;
#endif

        /* User-defined file handle */
        unsigned long udef_handle;
    } u;
};

/*******************************************************************************************************/
/* Get time callback should return an integer representing time. If NULL time prints will be disabled. */
/*******************************************************************************************************/
typedef uint32_t (*bcm_dev_log_get_time_cb)(void);

/********************************************************************************************************/
/* Time to string callback receives timestamp (us) and should convert into time_str                     */
/* time_str_size is the maximum number of bytes to be copied. In the end function should update the     */
/* number bytes actually written                                                                        */
/* If NULL time will printed as an unsigned integer.                                                    */
/********************************************************************************************************/
typedef int (*bcm_dev_log_time_to_str_cb)(uint32_t time, char *time_str, int time_str_size);
typedef void (*bcm_dev_log_print_cb)(void *arg, const char *fmt, ...);

/********************************************/
/*                                          */
/* Structs                                  */
/*                                          */
/********************************************/

typedef struct
{
    bcm_dev_log_get_time_cb get_time_cb;
    bcm_dev_log_time_to_str_cb time_to_str_cb;
    bcm_dev_log_print_cb print_cb;
    void *print_cb_arg;
    bcm_dev_log_file_parm log_file[DEV_LOG_MAX_FILES];
} bcm_dev_log_parm;

#ifdef TRIGGER_LOGGER_FEATURE
typedef struct
{
   uint32_t threshold;  /* every threshold messages, print one */
   uint32_t counter;    /* current index - runs from 0 to threshold, periodically */
} dev_log_id_throttle;

typedef struct
{
   uint32_t start_threshold; /* start printing when threshold is reached */
   uint32_t stop_threshold;  /* stop printing when threshold is reached, starting counting from start, if 0, do no stop */
   uint32_t counter;         /* current index - runs : first - from 0 to start_threshold
                                                       second - from start_threshold to stop_threshold */
   int32_t repeat_threshold;/* the trigger period, how many times the trigger is set, -1 = always */
   int32_t repeat;          /* current repeat counter */
} dev_log_id_trigger;
#endif

typedef struct
{
    bcmos_bool is_active;
    char name[MAX_DEV_LOG_ID_NAME];
    bcm_dev_log_id_type log_type;
    bcm_dev_log_id_type default_log_type;
    bcm_dev_log_level log_level_print;
    bcm_dev_log_level log_level_save;
    bcm_dev_log_level default_log_level;
    bcm_dev_log_style style;
    uint32_t lost_msg_cnt;
    uint32_t print_skipped_count; /* see DEV_LOG_SKIP_PRINT_THRESHOLD_PERCENT */
    uint32_t counters[DEV_LOG_LEVEL_NUM_OF];
#ifdef TRIGGER_LOGGER_FEATURE
    bcm_dev_log_level throttle_log_level;
    dev_log_id_throttle throttle;
    bcm_dev_log_level trigger_log_level;
    dev_log_id_trigger trigger;
#endif
} dev_log_id_parm;

/********************************************/
/*                                          */
/* Functions prototypes                     */
/*                                          */
/********************************************/

/** Tear down the dev_log, freeing all OS resources. */
void bcm_dev_log_destroy(void);

/* This function creates default logger that supports logging on the screen and
 * into 0 or more memory files.
 */
bcmos_errno bcm_dev_log_init_default_logger(void **start_addresses,
    uint32_t *sizes,
    bcm_dev_log_file_flags *flags,
    uint32_t num_files,
    uint32_t stack_size,
    bcmos_task_priority priority,
    uint32_t pool_size);

/* This function is more flexible comparing with bcm_dev_log_init_default_logger().
 * It creates logger that supports logging on the screen and into 0 or more
 * memory, regular and user-defined files.
 */
bcmos_errno bcm_dev_log_init_default_logger_ext(
    bcm_dev_log_parm *dev_log_parm,
    uint32_t num_files,
    uint32_t stack_size,
    bcmos_task_priority priority,
    uint32_t pool_size);

/**
 * @brief   High-level initialization function intended mainly for host use.
 * @note    Logger is initialized with a single log file using abbreviated set
            of init parameters
 * @param   init_parms: Initialization parameters
 * @retval  BCM_ERR_OK(0) if successful or error code < 0
 */
bcmos_errno bcm_log_init(const dev_log_init_parms *init_parms);

/************************************************************************/
/*                                                                      */
/* Name: bcm_dev_log_id_register                                        */
/*                                                                      */
/* Abstract: Add new ID to dev_log and return it to user                */
/*                                                                      */
/* Arguments:                                                           */
/*   name                - ID name                                      */
/*   default_log_level   - ID default log level                         */
/*   default_log_type    - ID default log type                          */
/*                                                                      */
/* Return Value:                                                        */
/*   new ID                                                             */
/*                                                                      */
/************************************************************************/
dev_log_id bcm_dev_log_id_register(const char *name,
    bcm_dev_log_level default_log_level,
    bcm_dev_log_id_type default_log_type);

/********************************************************************************************/
/*                                                                                          */
/* Name: bcm_dev_log_id_unregister                                                          */
/*                                                                                          */
/* Abstract: Unregister a registered log ID                                                 */
/*                                                                                          */
/* Arguments:                                                                               */
/*   - id        - The ID in the Dev log (what we got form bcm_dev_log_id_register)         */
/*                                                                                          */
/* Return Value:                                                                            */
/*   none                                                                                   */
/*                                                                                          */
/********************************************************************************************/
void bcm_dev_log_id_unregister(dev_log_id id);

/********************************************************************************************/
/*                                                                                          */
/* Name: bcm_dev_log_id_set_type                                                            */
/*                                                                                          */
/* Abstract: Set current log type for an ID                                                 */
/*                                                                                          */
/* Arguments:                                                                               */
/*   - id        - The ID in the Dev log (what we got form bcm_dev_log_id_register)         */
/*   - log_type  - New log type                                                             */
/*                                                                                          */
/* Return Value:                                                                            */
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)              */
/*                                                                                          */
/********************************************************************************************/
bcmos_errno bcm_dev_log_id_set_type(dev_log_id id, bcm_dev_log_id_type log_type);

/********************************************************************************************/
/*                                                                                          */
/* Name: bcm_dev_log_id_set_level                                                           */
/*                                                                                          */
/* Abstract: Set current log level for an ID                                                */
/*                                                                                          */
/* Arguments:                                                                               */
/*   - id        - The ID in the Dev log (what we got form bcm_dev_log_id_register)         */
/*   - log_level - New log level                                                            */
/*                                                                                          */
/* Return Value:                                                                            */
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)              */
/*                                                                                          */
/********************************************************************************************/
bcmos_errno bcm_dev_log_id_set_level(dev_log_id id, bcm_dev_log_level log_level_print, bcm_dev_log_level log_level_save);

/********************************************************************************************/
/*                                                                                          */
/* Name: bcm_dev_log_id_set_levels_and_type_to_default                                      */
/*                                                                                          */
/* Abstract: Set log_type and log_level to default (creation) values for an ID              */
/*                                                                                          */
/* Arguments:                                                                               */
/*   - id    - The ID in the Dev log (what we got form bcm_dev_log_id_register)             */
/*                                                                                          */
/* Return Value:                                                                            */
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)              */
/*                                                                                          */
/********************************************************************************************/
bcmos_errno bcm_dev_log_id_set_levels_and_type_to_default(dev_log_id id);

/********************************************************************************************/
/*                                                                                          */
/* Name: bcm_dev_log_level_set_style                                                        */
/*                                                                                          */
/* Abstract: Set log style per level                                                        */
/*                                                                                          */
/* Arguments:                                                                               */
/*   - level    - Log level                                                                 */
/*   - style    - The style of the log, NORMAL, BOLD, UNDERLINE, BLINK, REVERSE_VIDEO       */
/*                                                                                          */
/* Return Value:                                                                            */
/*   none                                                                                   */
/*                                                                                          */
/********************************************************************************************/
void bcm_dev_log_level_set_style(bcm_dev_log_level level, bcm_dev_log_style style);

/********************************************************************************************/
/*                                                                                          */
/* Name: bcm_dev_log_id_set_style                                                           */
/*                                                                                          */
/* Abstract: Set log style per log id                                                       */
/*                                                                                          */
/* Arguments:                                                                               */
/*   - id    - The ID in the Dev log (what we got form bcm_dev_log_id_register)             */
/*   - style    - The style of the log, NORMAL, BOLD, UNDERLINE, BLINK, REVERSE_VIDEO       */
/*                                                                                          */
/* Return Value:                                                                            */
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)              */
/*                                                                                          */
/********************************************************************************************/
bcmos_errno bcm_dev_log_id_set_style(dev_log_id id, bcm_dev_log_style style);

/************************************************************************************************/
/*                                                                                              */
/* Name: bcm_dev_log_id_clear_counters                                                          */
/*                                                                                              */
/* Abstract: Clear counter for an ID                                                            */
/*                                                                                              */
/* Arguments:                                                                                   */
/*   - id                - The ID in the Dev log (what we got form bcm_dev_log_id_register)     */
/*                                                                                              */
/* Return Value:                                                                                */
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)                  */
/*                                                                                              */
/************************************************************************************************/
bcmos_errno bcm_dev_log_id_clear_counters(dev_log_id id);

/********************************************************************************************/
/*                                                                                          */
/* Name: bcm_dev_log_id_get                                                                 */
/*                                                                                          */
/* Abstract: Get the ID status (type, level, counters ...)                                  */
/*                                                                                          */
/* Arguments:                                                                               */
/*   - id            - The ID in the Dev log (what we got form bcm_dev_log_id_register)     */
/*   - parm          - Returned status structure                                            */
/*                                                                                          */
/* Return Value:                                                                            */
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)              */
/*                                                                                          */
/********************************************************************************************/
bcmos_errno bcm_dev_log_id_get(dev_log_id id, dev_log_id_parm *parm);

/********************************************************************************************/
/*                                                                                          */
/* Name: bcm_dev_log_id_set                                                                 */
/*                                                                                          */
/* Abstract: set the ID status (type, level, style ...)                                     */
/*                                                                                          */
/* Arguments:                                                                               */
/*   - id            - The ID in the Dev log (what we got form bcm_dev_log_id_register)     */
/*   - parm          - structure to set                                                     */
/*                                                                                          */
/* Return Value:                                                                            */
/*   bcmos_errno - Success code (BCM_ERR_OK) or Error code (see bcmos_errno.h)              */
/*                                                                                          */
/********************************************************************************************/
bcmos_errno bcm_dev_log_id_set(dev_log_id id, dev_log_id_parm *parm);

/********************************************************************************/
/*                                                                              */
/* Name: bcm_dev_log_id_get_by_index                                            */
/*                                                                              */
/* Abstract: Return ID for index, if no such index return (DEV_LOG_INVALID_ID)  */
/*                                                                              */
/* Arguments:                                                                   */
/* index         - The index of the ID in the global array.                     */
/*                                                                              */
/* Return Value:                                                                */
/*   uint32_t - The ID (DEV_LOG_INVALID_ID if index is not valid)               */
/*                                                                              */
/********************************************************************************/
dev_log_id bcm_dev_log_id_get_by_index(uint32_t index);

/********************************************************************************/
/*                                                                              */
/* Name: bcm_dev_log_get_index_by_id                                            */
/*                                                                              */
/* Abstract: Return ID for index, if no such index return (DEV_LOG_INVALID_ID)  */
/*                                                                              */
/* Arguments:                                                                   */
/* id                        - Log id.                                          */
/*                                                                              */
/* Return Value:                                                                */
/*   uint32_t - The index ID (DEV_LOG_INVALID_INDEX if id is not valid)         */
/*                                                                              */
/********************************************************************************/
uint32_t bcm_dev_log_get_index_by_id(dev_log_id id);

/********************************************************************************/
/*                                                                              */
/* Name: bcm_dev_log_id_get_next                                                */
/*                                                                              */
/* Abstract: Return the next active ID following a given ID                     */
/*                                                                              */
/* Arguments:                                                                   */
/* id                        - Log id. Use DEV_LOG_INVALID_ID to start the      */
/*                                iteration.                                    */
/*                                                                              */
/* Return Value:                                                                */
/*   uint32_t - The next ID or DEV_LOG_INVALID_ID if no more                    */
/*                                                                              */
/********************************************************************************/
dev_log_id bcm_dev_log_id_get_next(dev_log_id id);

/********************************************************************************/
/*                                                                              */
/* Name: bcm_dev_log_id_get_by_name                                             */
/*                                                                              */
/* Abstract: Return ID index for name                                           */
/*                                                                              */
/* Arguments:                                                                   */
/* name         - The name of the ID                                            */
/*                                                                              */
/* Return Value:                                                                */
/*   dev_log_id - The ID index (-1 if name is not valid)                        */
/*                                                                              */
/********************************************************************************/
dev_log_id bcm_dev_log_id_get_by_name(const char *name);

bcmos_bool bcm_dev_log_get_control(void);
void bcm_dev_log_set_control(bcmos_bool control);

bcm_dev_log_file_flags bcm_dev_log_get_file_flags(uint32_t file_id);
void bcm_dev_log_set_file_flags(uint32_t file_id, bcm_dev_log_file_flags flags);

bcm_dev_log_flags bcm_dev_log_get_flags(void);
void bcm_dev_log_set_flags(bcm_dev_log_flags flags);

void bcm_dev_log_set_print_cb(bcm_dev_log_print_cb cb);
void bcm_dev_log_set_get_time_cb(bcm_dev_log_get_time_cb cb);
void bcm_dev_log_set_time_to_str_cb(bcm_dev_log_time_to_str_cb cb);

/* File index to file handle */
bcm_dev_log_file *bcm_dev_log_file_get(uint32_t file_index);

/* Get number of messages stored in the file */
uint32_t bcm_dev_log_get_num_of_messages(const bcm_dev_log_file *file);

/* Get file info: max data size, used bytes */
bcmos_errno bcm_dev_log_get_file_info(bcm_dev_log_file *file, uint32_t *file_size, uint32_t *used_bytes);

/* Read from file.
 * \param[in]           file    File to read from
 * \param[in,out]       offset  offset to read from. 0=read from the start
 * \param[in,out]       buf     buffer to read records to
 * \param[in]           buf_len buf size
 * \returns - number of bytes read >= 0 or bcmos_errno < 0
 * 0 = no more records to read
 * BCM_ERR_OVERFLOW - buffer is too short for log record
 */
int bcm_dev_log_file_read(bcm_dev_log_file *file, uint32_t *offset, char *buf, uint32_t buf_len);

/* Clear file
 * \param[in]           file    File handle
 * \returns     bcmos_errno error code
 */
bcmos_errno bcm_dev_log_file_clear(bcm_dev_log_file *file);

/* Attach file to memory buffer.
 * The file data can be read using bcm_dev_log_file_read or bcm_dev_log_file_read_cut
 * \param[in]           buf     buffer to be interpreted as memory file
 * \param[in]           buf_len buf size
 * \param[out]          file    File handle.
 * file_handle has to be destroyed using bcm_dev_log_file_detach() when no longer needed.
 * \returns     bcmos_errno error code
 */
bcmos_errno bcm_dev_log_file_attach(void *buf, uint32_t buf_len, bcm_dev_log_file *file);

/* Detach file handle from memory buffer.
 * Following this call, the file handle becomes invalid
 * \param[in]           file    File handle.
 * \returns     bcmos_errno error code
 */
bcmos_errno bcm_dev_log_file_detach(bcm_dev_log_file *file);

/* Register indication to be sent when file utilization crosses threshold */
bcmos_errno bcm_dev_log_almost_full_ind_register(bcm_dev_log_file *file, uint32_t used_bytes_threshold,
    F_dev_log_file_almost_full send_ind_cb, long ind_cb_priv);

void dev_log_get_log_name_table(char *buffer, uint32_t buf_len);

void bcm_dev_log_drop_report(void);

/** Helper function to determine if a given log level qualifies as an error. */
static inline bcmos_bool bcm_dev_log_level_is_error(bcm_dev_log_level log_level)
{
    return log_level == DEV_LOG_LEVEL_FATAL || log_level == DEV_LOG_LEVEL_ERROR;
}

/** Returns the percentage (0 - 100) of the msg pool that is currently in use. */
uint8_t bcm_dev_log_pool_occupancy_percent_get(void);

#ifdef TRIGGER_LOGGER_FEATURE
bcmos_errno bcm_dev_log_set_throttle(dev_log_id id, bcm_dev_log_level log_level, uint32_t throttle);

bcmos_errno bcm_dev_log_set_trigger(dev_log_id id, bcm_dev_log_level log_level, uint32_t start, uint32_t stop, int32_t repeat);
#endif /* TRIGGER_LOGGER_FEATURE */

void dev_log_oops_complete_cb(void);

#endif /* ENABLE_LOG */

#endif /* __BCM_DEV_LOG_TASK_H_ */
