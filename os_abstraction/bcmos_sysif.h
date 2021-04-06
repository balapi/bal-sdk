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
 * bcmos_sysif.h
 *
 * This internal header file includes OS-specific services
 * that are referred in OS-independent OS abstraction implementation
 *
 */

#ifndef BCMOS_SYSIF_H_
#define BCMOS_SYSIF_H_

/*
 * OS-specific init
 */

/** Initialize system library
 * Must be called before any other system function
 * \returns 0=OK or error code <0
 */
bcmos_errno bcmos_sys_init(void);

/** Clean-up system library
 */
void bcmos_sys_exit(void);


/*
 * Timer support
 */

/* OS abstraction must define struct bcmos_sys_timer
 */
typedef struct bcmos_sys_timer bcmos_sys_timer;

/* System timer handler. Implemented in common OS abstraction services */
typedef void (*bcmos_sys_timer_handler)(void *data);

/* Create system timer
 * It is expected that only one high-resolution system timer is needed.
 * It is used to "kick" timer pool implemented in OS abstraction
 * \param[in]   timer   System timer
 * \param[in]   handler Timer handler
 * \param[in]   data    Data to be passed to the handler
 * \returns 0 if OK or error < 0
 */
bcmos_errno bcmos_sys_timer_create(bcmos_sys_timer *timer, bcmos_sys_timer_handler handler, void *data);

/* Destroy system timer
 * \param[in]   timer   System timer
 */
void bcmos_sys_timer_destroy(bcmos_sys_timer *timer);

/* Start system timer
 * \param[in]   timer           System timer
 * \param[in]   interval        Interval (us)
 */
void bcmos_sys_timer_start(bcmos_sys_timer *timer, uint32_t interval);

/* Stop system timer
 * \param[in]   timer           System timer
 */
void bcmos_sys_timer_stop(bcmos_sys_timer *timer);

#endif /* BCMOS_SYSIF_H_ */
