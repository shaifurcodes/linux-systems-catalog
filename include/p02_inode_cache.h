#ifndef P02_INODE_CACHE_H
#define P02_INODE_CACHE_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P02 - Simple inode cache (hash table + LRU eviction)
 * Mimics Linux dcache/icache behaviour.
 * Fixed capacity INODE_CACHE_SIZE=64 slots.
 * On lookup miss + cache full: evict the least recently used entry.
 */
#define INODE_CACHE_SIZE 64

typedef struct {
    uint64_t ino;      /* inode number, 0 = empty slot */
    uint32_t mode;
    uint64_t size;
    uint32_t lru_tick; /* higher = more recent */
} InodeEntry;

typedef struct { InodeEntry slots[INODE_CACHE_SIZE]; uint32_t tick; } InodeCache;

void         ic_init(InodeCache *c);
void         ic_insert(InodeCache *c, uint64_t ino, uint32_t mode, uint64_t size);
InodeEntry  *ic_lookup(InodeCache *c, uint64_t ino);  /* NULL on miss */
void         ic_evict(InodeCache *c, uint64_t ino);
int          ic_count(const InodeCache *c);
#endif
