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

/** A write-biased readers-writer lock
 *  NOTE: DO NOT attempt to obtain a write lock on a thread that is already holding a read lock or vice versa - this
 *  will result in a deadlock. Multiple read locks from the same thread are safe, multiple write locks are NOT.
 */
#ifndef BCMOS_RW_LOCK_H_
#define BCMOS_RW_LOCK_H_
#include "bcmos_system.h"

typedef struct bcmos_rw_lock bcmos_rw_lock;

/** Initialize a lock
 *  \param[out] lock    the newly created lock
 *  \return error code
 */
bcmos_errno bcmos_rw_lock_create(bcmos_rw_lock **lock);

/** Obtain a write lock
 *  \param[in] lock     the lock to operate on
 */
void bcmos_rw_write_lock(bcmos_rw_lock* lock);

/** Release a write lock
 *  \param[in] lock     the lock to operate on
 */
void bcmos_rw_write_release(bcmos_rw_lock* lock);

/** Obtain a read lock
 *  \param[in] lock     the lock to operate on
 */
void bcmos_rw_read_lock(bcmos_rw_lock* lock);

/** Release a read lock
 *  \param[in] lock     the lock to operate on
 */
void bcmos_rw_read_release(bcmos_rw_lock* lock);

#endif
