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
#include "bcmos_rw_lock.h"

struct bcmos_rw_lock
{
    /* the actual lock, held by the writer, used by the reader to safely obtain a read lock, but not held to allow
     * multiple readers */
    bcmos_mutex lock;
    /* used by the writer to prevent new readers from obtaining read locks while a writer is waiting */
    bcmos_mutex read_lock;
    /* used by readers to signal waiting writers that they have finished reading */
    bcmos_sem write_lock;
    /* current number of readers */
    uint32_t readers;
};

bcmos_errno bcmos_rw_lock_create(bcmos_rw_lock **lock)
{
    bcmos_errno err;
    *lock = (bcmos_rw_lock*)bcmos_calloc(sizeof(bcmos_rw_lock));
    if (*lock == NULL)
    {
        BUG();
        return BCM_ERR_NOMEM;
    }
    if (BCM_ERR_OK != (err = bcmos_mutex_create(&(*lock)->lock, 0, "bcmos_rw_lock_create_lock")))
    {
        BUG();
        return err;
    }
    if (BCM_ERR_OK != (err = bcmos_mutex_create(&(*lock)->read_lock, 0, "bcmos_rw_lock_create_rw_lock")))
    {
        BUG();
        return err;
    }
    (*lock)->readers = 0;
    if (BCM_ERR_OK != (err = bcmos_sem_create(&(*lock)->write_lock, 1, 0, "bcmos_rw_lock_create_write_lock")))
    {
        BUG();
        return err;
    }
    return err;
}

/*lint -e{455} suppress "thread mutex has not been locked" */
void bcmos_rw_write_lock(bcmos_rw_lock* lock)
{
    /* prevent any new readers from trying to obtain a read lock */
    bcmos_mutex_lock(&lock->read_lock);
    /* lock the actual lock */
    bcmos_mutex_lock(&lock->lock);
    while (lock->readers != 0)
    {
        /* there are still readers holding read locks, release the lock */
        bcmos_mutex_unlock(&lock->lock);
        /* wait for the signal from the last reader before trying again */
        bcmos_sem_wait(&lock->write_lock, BCMOS_WAIT_FOREVER);
        /* lock the actual lock and check for readers again */
        bcmos_mutex_lock(&lock->lock);
    }
    /* no more readers, allow new readers to wait on the lock */
    bcmos_mutex_unlock(&lock->read_lock);
}
/*lint +e{454} suppress "thread mutex has not been locked" */

void bcmos_rw_write_release(bcmos_rw_lock* lock)
{
    /*lint --e{455} suppress "thread mutex has not been locked" */
    bcmos_mutex_unlock(&lock->lock);
}

void bcmos_rw_read_lock(bcmos_rw_lock* lock)
{
    /* wait for anyone trying to get a write lock */
    bcmos_mutex_lock(&lock->read_lock);
    /* wait for the lock to be released */
    bcmos_mutex_lock(&lock->lock);
    lock->readers++;
    /* reset the signal to the writers */
    bcmos_sem_wait(&lock->write_lock, BCMOS_NO_WAIT);
    /* all done, release everything so other readers can get a read lock */
    bcmos_mutex_unlock(&lock->lock);
    bcmos_mutex_unlock(&lock->read_lock);
}

void bcmos_rw_read_release(bcmos_rw_lock* lock)
{
    /* get a lock to prevent interruptions */
    bcmos_mutex_lock(&lock->lock);
    if (--lock->readers == 0)
    {
        /* if we're the last reader, signal that the lock is available for a writer */
        bcmos_sem_post(&lock->write_lock);
    }
    bcmos_mutex_unlock(&lock->lock);
}

