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

#ifndef __BCM_DEV_LOG_API_H_
#define __BCM_DEV_LOG_API_H_

#include <bcmos_system.h>

/* Log file type */
typedef enum
{
    BCM_DEV_LOG_FILE_MEMORY,    /**< Memory file */
#ifdef BCM_OS_POSIX
    BCM_DEV_LOG_FILE_REGULAR,   /**< Regular file */
#endif
#ifdef DEV_LOG_SYSLOG
    BCM_DEV_LOG_FILE_SYSLOG,    /**< syslog "file" */
#endif
    BCM_DEV_LOG_FILE_UDEF       /**< User-defined file */
} bcm_dev_log_file_type;


/** Logger initialization parameters */
typedef struct dev_log_init_parms
{
    bcm_dev_log_file_type type;   /**< Log file type */
    uint32_t queue_size;          /**< Max number of entries that can be waiting on dev_log task queue. 0=use default */
#define BCM_DEV_LOG_DEFAULT_QUEUE_SIZE   4096

    union /* Log parameters per log_type */
    {
        uint32_t mem_size;        /**< Memory size for log_type == BCMOLT_LOG_TYPE_MEMORY. 0=use default */
#define BCM_DEV_LOG_DEFAULT_MEM_SIZE     (1024 * 1024)
#ifdef BCM_OS_POSIX
        const char *filename;     /**< For log_type == BCMOLT_LOG_TYPE_FILE */
#endif
    };

    /**< Optional callback to call after common log initialization.
         It can be used to set default log levels, timestamp format, etc.
    */
    bcmos_errno (*post_init_cb)(void);
} dev_log_init_parms;



#endif /* __BCM_DEV_LOG_API_H_ */
