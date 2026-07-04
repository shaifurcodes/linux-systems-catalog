#ifndef P02_INODE_CACHE_H
#define P02_INODE_CACHE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * @file p02_inode_cache.h
 * @brief Simple inode cache featuring an open-addressed hash table with LRU eviction.
 *
 * This implementation mimics basic Linux dcache/icache behaviors. It uses linear
 * probing to handle hash collisions and utilizes a special Tombstone marker 
 * (0xFFFFFFFFFFFFFFFF) during evictions to maintain the integrity of collision chains.
 */

/** 
 * @brief Fixed capacity maximum slots allocated for the cache array. 
 */
#define INODE_CACHE_SIZE 64

/**
 * @brief Represents a single cached inode entry slot.
 */
typedef struct {
    /** 
     * @brief Inode number unique identifier.
     * Value rules: 0 = completely empty slot, 0xFFFFFFFFFFFFFFFF = Tombstone (evicted slot).
     */
    uint64_t ino;      
    uint32_t mode;     /**< File mode / permissions flags. */
    uint64_t size;     /**< Size of the file in bytes. */
    uint32_t lru_tick; /**< Age tracker counter. Higher values indicate more recent access. */
} InodeEntry;

/**
 * @brief Main container wrapping the fixed-size cache storage array.
 */
typedef struct { 
    InodeEntry slots[INODE_CACHE_SIZE]; /**< Array containing the hash table entries. */
    uint32_t tick;                      /**< Global monotonic counter tracking cache access events. */
} InodeCache;

/**
 * @brief Initializes the inode cache data structures.
 * 
 * Clears out all entries by setting every slot's inode number to 0 (empty)
 * and resets the global tick counter back to zero.
 * 
 * @param c Pointer to the InodeCache instance to initialize.
 */
void ic_init(InodeCache *c);

/**
 * @brief Inserts or updates an entry inside the cache structure.
 * 
 * This function hashes the node by calculating `ino % INODE_CACHE_SIZE` and resolves
 * collisions using linear probing. If the inode already exists, its attributes are 
 * updated and its age tick increases. If the cache is full, the global least recently 
 * used (LRU) node is evicted. New data can safely overwrite empty slots or tombstones.
 * 
 * @param c    Pointer to the active InodeCache context instance.
 * @param ino  Target inode identifier key to insert or update.
 * @param mode The file access mode permissions payload.
 * @param size Total file size value payload.
 */
void ic_insert(InodeCache *c, uint64_t ino, uint32_t mode, uint64_t size);

/**
 * @brief Searches for a specific inode matching the provided key.
 * 
 * The algorithm begins querying at the initial hash modulo location and scans forward.
 * It will skip past Tombstone markers to preserve collision search chains, and terminates
 * immediately upon finding a match or encountering a completely empty slot (0).
 * 
 * @param c   Pointer to the active InodeCache context instance.
 * @param ino Target inode identifier key to search for.
 * @return InodeEntry* Pointer to the matching entry slot (with updated LRU tick) on a hit, 
 *                     or NULL if the entry is missing.
 */
InodeEntry *ic_lookup(InodeCache *c, uint64_t ino);

/**
 * @brief Explicitly evicts a targeted inode out of the cache.
 * 
 * Locates the requested inode using standard lookup probing patterns. Instead of clearing
 * the entry down to zero—which would corrupt subsequent linear collision lookups—it flags
 * the target slot with a Tombstone marker (`0xFFFFFFFFFFFFFFFF`).
 * 
 * @param c   Pointer to the active InodeCache context instance.
 * @param ino Target inode identifier key to remove.
 */
void ic_evict(InodeCache *c, uint64_t ino);

/**
 * @brief Compiles a count of all valid active nodes currently cached.
 * 
 * Scans the underlying storage array and returns the number of slots that do not contain 
 * an empty indicator (0) or an active Tombstone flag.
 * 
 * @param c Constant pointer to the InodeCache instance to scan.
 * @return int Total number of legitimate cached entries.
 */
int ic_count(const InodeCache *c);

#endif // P02_INODE_CACHE_H

