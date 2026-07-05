/**
 * @file p03_slab_allocator.h
 * @brief Fixed-size slab allocator (kernel kmem_cache style).
 *
 * This allocator manages a pre-allocated "slab" of memory divided into a fixed 
 * number of equal-sized object slots. It provides O(1) time complexity for both 
 * allocation and deallocation by utilizing an intrusive free-list of indices 
 * stored directly within unallocated memory slots.
 */

#ifndef P03_SLAB_ALLOCATOR_H
#define P03_SLAB_ALLOCATOR_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @struct SlabCache
 * @brief Opaque handle representing the slab allocator instance.
 */
typedef struct SlabCache SlabCache;

/**
 * @brief Creates and initializes a new slab cache instance.
 *
 * Allocates a continuous block of memory large enough to hold @p capacity objects 
 * of size @p obj_size. Note that if @p obj_size is smaller than the size of an 
 * internal tracking index, it will be silently padded to ensure safety and alignment.
 *
 * @param[in] obj_size Size of each individual object slot in bytes.
 * @param[in] capacity Total number of object slots to pre-allocate.
 * @return Pointer to the initialized SlabCache instance, or NULL if initialization fails.
 */
SlabCache *slab_create(size_t obj_size, size_t capacity);

/**
 * @brief Destroys the slab cache and releases all associated memory.
 *
 * This completely tears down the cache structure and returns its memory pool back 
 * to the system. Any outstanding object pointers allocated from this slab become 
 * immediately invalid.
 *
 * @param[in,out] sc Pointer to the SlabCache instance to destroy. If NULL, does nothing.
 */
void slab_destroy(SlabCache *sc);

/**
 * @brief Allocates an object slot from the slab cache.
 *
 * Pulls the next available slot from the head of the intrusive free-list in O(1) time.
 *
 * @param[in,out] sc Pointer to the active SlabCache instance.
 * @return Void pointer to the allocated object slot, or NULL if the cache is exhausted.
 */
void *slab_alloc(SlabCache *sc);

/**
 * @brief Frees an object slot back into the slab cache.
 *
 * Returns an allocated slot to the front of the intrusive free-list in O(1) time.
 * If @p ptr does not belong to this cache or is out of bounds, the behavior is safely ignored.
 *
 * @param[in,out] sc Pointer to the active SlabCache instance.
 * @param[in]     ptr Pointer to the object slot to free. If NULL, does nothing.
 */
void slab_free(SlabCache *sc, void *ptr);

/**
 * @brief Retrieves the current number of available free slots in the slab cache.
 *
 * @param[in] sc Pointer to the SlabCache instance.
 * @return The number of unallocated slots remaining, or 0 if the cache is NULL.
 */
int slab_free_count(const SlabCache *sc);

#endif /* P03_SLAB_ALLOCATOR_H */
