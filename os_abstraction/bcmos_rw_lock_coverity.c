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

/* bcmos_rw_lock_coverity.c: Dramatically simplified model of a reader/writer lock so Coverity can understand it.
 *
 * We could use code-level annotations in bcmos_rw_lock.c to prevent the Coverity errors, but then Coverity would
 * lose the fact that these functions do take/release locks, just like a regular mutex.
 */

#include "bcmos_rw_lock.h"

struct bcmos_rw_lock
{
    bcmos_mutex lock;
};

bcmos_errno bcmos_rw_lock_create(bcmos_rw_lock **lock)
{
    bcmos_errno err;
    *lock = (bcmos_rw_lock*)bcmos_calloc(sizeof(bcmos_rw_lock));
    BUG_ON(*lock == NULL);
    err = bcmos_mutex_create(&(*lock)->lock, 0, "bcmos_rw_lock_create_lock");
    BUG_ON(err != BCM_ERR_OK);
    return BCM_ERR_OK;
}

void bcmos_rw_write_lock(bcmos_rw_lock* lock)
{
    bcmos_mutex_lock(&lock->lock);
}

void bcmos_rw_write_release(bcmos_rw_lock* lock)
{
    bcmos_mutex_unlock(&lock->lock);
}

void bcmos_rw_read_lock(bcmos_rw_lock* lock)
{
    bcmos_mutex_lock(&lock->lock);
}

void bcmos_rw_read_release(bcmos_rw_lock* lock)
{
    bcmos_mutex_unlock(&lock->lock);
}
