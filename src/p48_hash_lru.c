#include "p48_hash_lru.h"
#include <string.h>
/* TODO: hash bucket = key % LRU_CAP. On lru_get: move accessed node to MRU end.
 * On lru_put when full: evict lru_tail (LRU end), then insert at lru_head. */
void lru_init(LruCache *c) {}
void lru_put(LruCache *c, uint64_t key, uint64_t val) {}
bool lru_get(LruCache *c, uint64_t key, uint64_t *val) { return false; }
void lru_evict_lru(LruCache *c) {}
int  lru_count(const LruCache *c) { return 0; }