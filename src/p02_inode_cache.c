#include "p02_inode_cache.h"
#include <string.h>
/* TODO: implement. Hash by ino % INODE_CACHE_SIZE; linear probe on collision.
 * Eviction: find slot with lowest lru_tick. */
void        ic_init(InodeCache *c) {}
void        ic_insert(InodeCache *c, uint64_t ino, uint32_t mode, uint64_t size) {}
InodeEntry *ic_lookup(InodeCache *c, uint64_t ino) { return NULL; }
void        ic_evict(InodeCache *c, uint64_t ino) {}
int         ic_count(const InodeCache *c) { return 0; }
