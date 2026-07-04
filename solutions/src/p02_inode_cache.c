#include "p02_inode_cache.h"
#include <string.h>
#include <stddef.h>

/* Special internal sentinel value indicating a slot has been evicted.
 * Using a tombstone prevents breaking the linear probing collision chain. Lookups 
 * bypass tombstones to continue the search, while insertions treat them as reusable spaces. */
#define TOMBSTONE 0xFFFFFFFFFFFFFFFFULL

void ic_init(InodeCache *c) {
    if (!c) return;
    memset(c->slots, 0, sizeof(c->slots));
    c->tick = 0;
}

/* 
 * LOOKUP: Starts at the hash modulo location, then chains forward using size_t indexing.
 * It skips tombstones and only stops if it finds the item or hits a true 0.
 */
InodeEntry *ic_lookup(InodeCache *c, uint64_t ino) {
    if (!c || ino == 0 || ino == TOMBSTONE) return NULL;

    size_t start_index = (size_t)(ino % INODE_CACHE_SIZE);
    size_t i = start_index;

    do {
        if (c->slots[i].ino == ino) {
            c->tick++;
            c->slots[i].lru_tick = c->tick;
            return &c->slots[i];
        }
        // A true 0 means the end of the collision chain. 
        // Note: We DO NOT stop on a TOMBSTONE!
        if (c->slots[i].ino == 0) {
            return NULL;
        }
        i = (i + 1) % INODE_CACHE_SIZE; // Chain to the next slot
    } while (i != start_index);

    return NULL;
}

/* 
 * INSERT: Checks if the item exists first. If not, chains forward from the 
 * modulo location to find the first available slot (either 0 or a tombstone).
 */
void ic_insert(InodeCache *c, uint64_t ino, uint32_t mode, uint64_t size) {
    if (!c || ino == 0 || ino == TOMBSTONE) return;

    // 1. Update if it already exists in the cache
    InodeEntry *existing = ic_lookup(c, ino);
    if (existing) {
        existing->mode = mode;
        existing->size = size;
        return;
    }

    // 2. Find an available slot (0 or Tombstone) starting from the hash location
    size_t start_index = (size_t)(ino % INODE_CACHE_SIZE);
    size_t i = start_index;
    size_t target_slot = (size_t)-1; // Sentinels match memory limits

    do {
        if (c->slots[i].ino == 0 || c->slots[i].ino == TOMBSTONE) {
            target_slot = i;
            break;
        }
        i = (i + 1) % INODE_CACHE_SIZE;
    } while (i != start_index);

    // 3. Cache is full: find the global LRU entry to evict
    if (target_slot == (size_t)-1) {
        uint32_t min_tick = 0xFFFFFFFF;
        size_t lru_slot = 0;

        for (size_t j = 0; j < INODE_CACHE_SIZE; j++) {
            // Only evict valid, active items
            if (c->slots[j].ino != 0 && c->slots[j].ino != TOMBSTONE) {
                if (c->slots[j].lru_tick < min_tick) {
                    min_tick = c->slots[j].lru_tick;
                    lru_slot = j;
                }
            }
        }
        target_slot = lru_slot;
    }

    // 4. Write the data into the found slot
    c->tick++;
    c->slots[target_slot].ino = ino;
    c->slots[target_slot].mode = mode;
    c->slots[target_slot].size = size;
    c->slots[target_slot].lru_tick = c->tick;
}

/* 
 * EVICT: Finds the item by chaining from the hash location and turns it into a tombstone.
 */
void ic_evict(InodeCache *c, uint64_t ino) {
    if (!c || ino == 0 || ino == TOMBSTONE) return;

    size_t start_index = (size_t)(ino % INODE_CACHE_SIZE);
    size_t i = start_index;

    do {
        if (c->slots[i].ino == ino) {
            c->slots[i].ino = TOMBSTONE; // Leave a tombstone to preserve the chain
            c->slots[i].mode = 0;
            c->slots[i].size = 0;
            c->slots[i].lru_tick = 0;
            return;
        }
        if (c->slots[i].ino == 0) {
            return; // Hit a true empty slot, item doesn't exist
        }
        i = (i + 1) % INODE_CACHE_SIZE;
    } while (i != start_index);
}

/* 
 * COUNT: Loops through using size_t but returns an int as required by the header declaration.
 */
int ic_count(const InodeCache *c) {
    if (!c) return 0;

    int count = 0;
    for (size_t i = 0; i < INODE_CACHE_SIZE; i++) {
        // Count only actual valid inodes
        if (c->slots[i].ino != 0 && c->slots[i].ino != TOMBSTONE) {
            count++;
        }
    }
    return count;
}
