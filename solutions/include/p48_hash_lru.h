#ifndef P48_HASH_LRU_H
#define P48_HASH_LRU_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P48 - LRU cache with hash map (like Linux page cache / dcache)
 * Combine a hash table for O(1) lookup with a doubly-linked LRU list.
 * On capacity: evict LRU entry before inserting new one.
 * Capacity: 32 entries, key: uint64_t, value: uint64_t.
 */
#define LRU_CAP 32
typedef struct LruNode {
    uint64_t key, val;
    struct LruNode *prev, *next;
    struct LruNode *hash_next;
} LruNode;
typedef struct { LruNode nodes[LRU_CAP]; LruNode *heads[LRU_CAP]; LruNode *lru_head, *lru_tail; int count; } LruCache;
void     lru_init(LruCache *c);
void     lru_put(LruCache *c, uint64_t key, uint64_t val);
bool     lru_get(LruCache *c, uint64_t key, uint64_t *val);
void     lru_evict_lru(LruCache *c);
int      lru_count(const LruCache *c);
#endif