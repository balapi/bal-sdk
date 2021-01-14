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

#ifndef BCMOS_HASH_TABLE_H_
#define BCMOS_HASH_TABLE_H_

#include "bcmos_system.h"

typedef struct ht_block ht_block;
struct ht_block
{
    ht_block *next_chain;
};

typedef struct
{
    uint16_t obj_len;
    uint8_t key_len;
    uint32_t data_offset;
    uint32_t ht_lookup_tbl_entries;
    uint32_t ht_max_data_entries;
    bcmos_blk_pool key_data_pool;
    ht_block *look_up_entries_tbl;
    uint32_t ht_cur_entries;
} hash_table;

typedef struct
{
    const hash_table *ht;
    uint32_t cur_idx;
    ht_block *cur_block;
    bcmos_bool removed_at;
    bcmos_bool still_valid;
} ht_iterator;

/** Create a hash table
 *  \param[in] max_data_entries     Maximum entries the hash table needs to hold
 *  \param[in] entry_size           Size of each entry in bytes
 *  \param[in] key_size             Size of each key in bytes
 *  \param[in] pool_name            Friendly name to identify the hash table's memory pool
 *  \return pointer to newly created hash table
 */
hash_table *hash_table_create(uint32_t max_data_entries,
                              uint16_t entry_size,
                              uint8_t key_size,
                              char *pool_name);

/** Removes all entries from a HashTable.
 *  \param[in] ht   Hash table to remove all entries from
 */
void hash_table_clear(hash_table *ht);

/** Gets a pointer to an entry within the hash table (if exists)
 *  \param[in] ht   Hashtable in question
 *  \param[in] key  Key to look for.
 *  \return Non null if we found a data item associated with KEY.
 */
void *hash_table_get(const hash_table *ht, const uint8_t *key);

/** Returns pointers to the key and value that an iterator is pointing at. Warning: key may not be uint32_t aligned.
 *  DO NOT DELETE THE ELEMENT THE ITERATOR POINTS AT AND AND TRY TO USE THE ITERATOR SUBSEQUENTLY. If you need to do
 *  this use ht_iterator_remove_at
 *  \param[in] hti  Iterator
 *  \param[in] key  Pointer to key to fill
 *  \param[in] obj  Pointer to obj to fill.
 */
void ht_iterator_deref(const ht_iterator *hti, uint8_t **key, void **obj);

/** Get an interator for traversing a hashtable.
 *  \param[in] ht   Hashtable to traverse
 *  \return The iterator.
 */
ht_iterator ht_iterator_get(const hash_table *ht);

/** Get an interator for traversing a hashtable based on an entry's key.
 *  \param[in] ht   Hashtable to traverse
 *  \param[in] key  key of entry to return
 *  \return The iterator.
 */
ht_iterator ht_iterator_get_by_key(const hash_table *ht, const uint8_t *key);

/** Advances a HashTable iterator to the next location within the HashTable.
 *  \param[in] it   Iterator to advance
 *  \return TRUE if there was a next element
 */
bcmos_bool ht_iterator_next(ht_iterator *it);

/** Deletes the entry where the iterator points to and advances the iterator returning whether the advance worked or
 *  not.
 *  \param[in] ht   Writable reference to the hash table (the iterator only has read permission)
 *  \param[in] it   Itreator pointing at entry to delete.
 */
void ht_iterator_remove_at(hash_table *ht, ht_iterator *it);

/** Attempts to associate key with val in the hash table. If key already exists overwrites what was at key with val.
 *  Otherwise allocates an entry within the hashtable for key and copies val into it.
 *  \param[in] ht   Hashtable to add or modify
 *  \param[in] key  Key to try and associate with val.
 *  \param[in] val  Val to associate
 *  \return NULL if fail, else pointer to just added block.
 */
void *hash_table_put(hash_table *ht, const uint8_t *key, const void *val);

/** Removes an entry (if exists) from the hash table.
 *  \param[in] ht   HashTable to remove from.
 *  \param[in] key  Key to remove
 *  \return BCMOS_TRUE if anything was removed, otherwise BCMOS_FALSE.
 */
bcmos_bool hash_table_remove(hash_table *ht, const uint8_t *key);

#endif /* Hash.h */
