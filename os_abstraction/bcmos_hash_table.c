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
#include "bcmos_hash_table.h"

#define ht_overhead     sizeof(void *)

/** Create a hash table using a block pool
 *  \param[in] pool_parm            pointer to block pool parameters
 *  \param[in] max_data_entries     Maximum entries the hash table needs to hold
 *  \param[in] entry_size           Size of each entry in bytes
 *  \param[in] key_size             Size of each key in bytes
 *  \return pointer to newly created hash table
 */
static hash_table *hash_table_create_in_pool(bcmos_blk_pool_parm *pool_parm,
                                             uint32_t max_data_entries,
                                             uint16_t entry_size,
                                             uint8_t key_size)
{
    uint32_t lookup_table_entries = max_data_entries + (max_data_entries / 4);
    hash_table *ht;
    bcmos_errno err;

    if (pool_parm == NULL)
    {
        BUG();
        return NULL;
    }

    entry_size += key_size;

    ht = bcmos_alloc(sizeof(hash_table));
    if (ht == NULL)
    {
        BUG();
        return NULL;
    }

    ht->obj_len = entry_size;
    ht->key_len = key_size;
    ht->data_offset = ht_overhead;
    ht->ht_lookup_tbl_entries = lookup_table_entries;
    ht->ht_max_data_entries = max_data_entries;
    ht->look_up_entries_tbl = bcmos_alloc(lookup_table_entries * sizeof(ht_block));

    if (ht->look_up_entries_tbl == NULL)
    {
        bcmos_free(ht);
        BUG();
        return NULL;
    }

    ht->ht_cur_entries = 0;
    err = bcmos_blk_pool_create(&ht->key_data_pool, pool_parm);

    if (err != BCM_ERR_OK)
    {
        bcmos_free(ht->look_up_entries_tbl);
        bcmos_free(ht);
        BUG();
        return NULL;
    }

    if (ht->ht_max_data_entries > ht->ht_lookup_tbl_entries)
    {
        BUG();
    }

    ht->obj_len -= ht->key_len;

    memset(ht->look_up_entries_tbl, 0, lookup_table_entries * sizeof(ht_block));
    return ht;
}

hash_table *hash_table_create(uint32_t max_data_entries,
                              uint16_t entry_size,
                              uint8_t key_size,
                              char *pool_name)
{
    bcmos_blk_pool_parm parm = {0};

    parm.name = pool_name;
    parm.blk_size = entry_size + key_size + ht_overhead;
    parm.num_blks = max_data_entries;

    return hash_table_create_in_pool(&parm, max_data_entries, entry_size, key_size);
}

/** Hash a length of bytes into a uint32_t
 *  \param[in] key      Bytes to hash
 *  \param[in] len      Number of bytes in key
 *  \return The hash as a uint32_t
 */
static uint32_t get_hash_for_key(const uint8_t *key, uint8_t len)
{
    uint32_t hash = 5381;
    uint8_t i;
    const uint8_t *tmp = key;
    for (i = 0; i < len; tmp++, i++)
    {
        hash = ((hash << 5) + hash) + (*tmp);
    }

    return hash;
}

/** Gets a hash key used for the keyDataPool in the HashTable
 *  \param[in] ht   Associated hashtable we are getting hash for key for
 *  \param[in] key  Key we are getting hash for
 *  \return An index into the keyDataPool
 */
static uint32_t get_hash_val_for_key(const hash_table *ht, const uint8_t *key)
{
    return get_hash_for_key(key, ht->key_len) % ht->ht_lookup_tbl_entries;
}

/** Returns the location of the key within an HtBlock
 *  \param[in] ht       Hash table in question
 *  \param[in] block    HtBlock in question
 *  \return pointer to the data within the block
 */
static uint8_t *get_key_from_block_in_table(const hash_table *ht, ht_block *block)
{
    return(uint8_t *) block + ht->data_offset + ht->obj_len;
}

/** Gets and populates a HtBlock with all of its data
 *  \param[in] next     Next block in this buckets chain
 *  \param[in] ht       Hash table in question
 *  \param[in] key      This blocks key
 *  \param[in] val      This blocks data
 *  \return The block that we allocated and returned
 */
static ht_block *fill_ht_block(ht_block *next,
                               hash_table *ht,
                               const uint8_t *key,
                               const void *val)
{
    ht_block *dest_block = bcmos_blk_pool_alloc(&ht->key_data_pool);

    if (dest_block != NULL)
    {
        /* storage is nextobj ptr, hash obj,
	    key which keeps all uint32_t aligned. */
        dest_block->next_chain = next;

        if (val != NULL)
        {
            memcpy((uint8_t *) dest_block + ht->data_offset, val, ht->obj_len);
        }
        else
        {
            memset((uint8_t *) dest_block + ht->data_offset,0,ht->obj_len);
        }

        /* Need to put key in after obj */
        memcpy(
              (uint8_t *) dest_block + ht->data_offset + ht->obj_len,
              key,
              ht->key_len);
    }

    return dest_block;
}

/** Determine whether two keys in a particular hash table match
 *  \param[in] ht       Hashtable
 *  \param[in] key_a    first key to compare
 *  \param[in] key_b    second key to compare
 *  \return whether they are the same
 */
static bcmos_bool is_key_match(const hash_table *ht, const uint8_t *key_a, const uint8_t *key_b)
{
    return memcmp(key_a, key_b, ht->key_len) == 0;
}

/** Searches a chained bucket looking for an instance of the key.  If found returns the block if found the key in.
 *  Prev guy is set to the block in the chain before the block we returned (except in the case * where there is no
 *  block before the one we returned.
 *  \param[in] ht           HashTable in question
 *  \param[in] key_to_find  Key we wonder if exists
 *  \param[in] chain_start  Where to start looking in the chain
 *  \param[in] prev_block   The previous guy before the block we returned (if exists)
 *  \return The block that matches doesExists (if exists)
 */
static ht_block *get_key_loc_in_chain(
                                     const hash_table *ht,
                                     const uint8_t *key_to_find,
                                     ht_block *chain_start,
                                     ht_block **prev_block)
{
    *prev_block = NULL;
    while (chain_start != NULL)
    {
        if (is_key_match(ht, key_to_find, get_key_from_block_in_table(ht, chain_start)))
        {
            return chain_start;
        }
        *prev_block = chain_start;
        chain_start = chain_start->next_chain;
    }
    return NULL;
}

bcmos_bool hash_table_remove(hash_table *ht, const uint8_t *key)
{
    uint32_t hash_val = get_hash_val_for_key(ht, key);
    ht_block *prev_entry;
    ht_block *entry = get_key_loc_in_chain(
        ht,
        key,
        ht->look_up_entries_tbl[hash_val].next_chain,
        &prev_entry);

    if (entry == NULL)
    {
        /* No one to delete */
        return BCMOS_FALSE;
    }
    else
    {
        ht->ht_cur_entries--;
        if (prev_entry == NULL)
        {
            /* last entry */
            ht->look_up_entries_tbl[hash_val].next_chain = entry->next_chain;
        }
        else
        {
            prev_entry->next_chain = entry->next_chain;
        }
        bcmos_blk_pool_free(entry);
        return BCMOS_TRUE;
    }
}

/** Returns a pointer to the data within the HT
 *  \param[in] ht           Hashtable in question
 *  \param[in] block_ptr    HtBlock that we wonder where its data is
 */
static void *get_ht_data_ptr(const hash_table *ht, ht_block *block_ptr)
{
    return(uint8_t*)block_ptr + ht->data_offset;
}


/** Get an entry in the hash table
 *  \param[in] ht       pointer to hash table
 *  \param[in] key      pointer to key data
 *  \param[in] hash_val hash value of key
 *  \return pointer to hash table entry
 */
static inline void *ht_get_internal(const hash_table *ht,
                                    const uint8_t *key,
                                    uint32_t hash_val)
{
    ht_block *tmp;
    ht_block *ret;
    ret = get_key_loc_in_chain(
                              ht,
                              key,
                              ht->look_up_entries_tbl[hash_val].next_chain,
                              &tmp);
    if (ret != NULL)
    {
        return get_ht_data_ptr(ht,ret);
    }
    else
    {
        return ret;
    }
}

void *hash_table_get(const hash_table *ht, const uint8_t *key)
{
    uint32_t hashVal = get_hash_val_for_key(ht, key);
    return ht_get_internal(ht,key,hashVal);
}

void *hash_table_put(hash_table *ht, const uint8_t *key, const void *val)
{
    void *ret_block;
    uint32_t hash_val;
    if (ht->ht_cur_entries >= ht->ht_max_data_entries)
    {
        return NULL;
    }
    hash_val = get_hash_val_for_key(ht, key);

    ret_block = ht_get_internal((const hash_table *) ht, key, hash_val);
    if (ret_block != NULL)
    {
        /* replace existing value with new value */
        if (val != NULL)
        {
            memcpy(ret_block, val, ht->obj_len);
        }
        else
        {
            memset(ret_block, 0, ht->obj_len);
        }
        return ret_block;
    }
    else
    {
        ht_block *new_block=fill_ht_block(
                                         ht->look_up_entries_tbl[hash_val].next_chain, ht, key, val);
        if (new_block != NULL)
        {
            ht->look_up_entries_tbl[hash_val].next_chain = new_block;
            ht->ht_cur_entries++;
            return get_ht_data_ptr(ht,new_block);
        }
        else
        {
            return NULL;
        }
    }

}

ht_iterator ht_iterator_get(const hash_table *ht)
{
    ht_iterator to_ret;
    to_ret.ht = ht;
    to_ret.cur_idx = 0;
    to_ret.removed_at = BCMOS_FALSE;
    to_ret.still_valid = BCMOS_TRUE;
    to_ret.cur_block = NULL;
    return to_ret;
}

ht_iterator ht_iterator_get_by_key(const hash_table *ht, const uint8_t *key)
{
    ht_block *tmp;
    uint32_t hash_val = get_hash_val_for_key(ht, key);
    ht_iterator to_ret = {};
    to_ret.ht = ht;
    to_ret.removed_at = BCMOS_FALSE;
    to_ret.cur_block = get_key_loc_in_chain(ht, key, ht->look_up_entries_tbl[hash_val].next_chain, &tmp);
    to_ret.still_valid = (to_ret.cur_block != NULL);
    to_ret.cur_idx = hash_val;

    return to_ret;
}

/** Advance linear scan iterator
 *  \param[in] it   Iterator to advance
 */
static void ht_iterator_scan_adv(ht_iterator *it)
{
    if (it->cur_block != NULL)
    {
        it->cur_block = it->cur_block->next_chain;
        if (it->cur_block != NULL)
        {
            it->still_valid = BCMOS_TRUE;
            return;
        }
        else
        {
            it->cur_idx++;
        }
    }
    /* find non null entry */
    while (it->cur_idx < it->ht->ht_lookup_tbl_entries)
    {
        if (it->ht->look_up_entries_tbl[it->cur_idx].next_chain != NULL)
        {
            it->cur_block = it->ht->look_up_entries_tbl[it->cur_idx].next_chain;
            it->still_valid = BCMOS_TRUE;
            return;
        }
        else
        {
            it->cur_idx++;
        }
    }
    it->still_valid = BCMOS_FALSE;
}

void ht_iterator_deref(const ht_iterator *hti, uint8_t **key, void **obj)
{
    if (!hti->still_valid)
    {
        BCMOS_TRACE_ERR("%s: Invalid deref\n", __FUNCTION__);
    }
    else
    {
        *key = get_key_from_block_in_table(hti->ht, hti->cur_block);
        *obj = get_ht_data_ptr(hti->ht, hti->cur_block);    /* to data */
    }
}

void ht_iterator_remove_at(hash_table *ht, ht_iterator *it)
{
    if (ht != it->ht)
    {
        BCMOS_TRACE_ERR("%s: Incorrect writeable hash table pointer\n", __FUNCTION__);
    }
    else if (it->removed_at)
    {
        BCMOS_TRACE_ERR("%s: No delete twice\n", __FUNCTION__);
    }
    else
    {
        uint8_t *key;
        uint8_t *obj;
        ht_iterator_deref(it, &key, (void **) &obj);
        it->removed_at = BCMOS_TRUE;
        it->still_valid = ht_iterator_next(it);
        if (!hash_table_remove(ht, key))
        {
            BCMOS_TRACE_ERR("%s: Remove error\n", __FUNCTION__);
        }
    }
}

bcmos_bool ht_iterator_next(ht_iterator *it)
{
    if (it->still_valid)
    {
        if (it->removed_at)
        {
            it->removed_at = BCMOS_FALSE;
        }
        else
        {
            ht_iterator_scan_adv(it);
        }
    }
    return it->still_valid;   /* No entry found */
}

void hash_table_clear(hash_table *ht)
{
    ht_iterator it = ht_iterator_get(ht);
    while (ht_iterator_next(&it))
    {
        ht_iterator_remove_at(ht, &it);
    }
}
