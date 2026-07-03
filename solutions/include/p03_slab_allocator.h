#ifndef P03_SLAB_ALLOCATOR_H
#define P03_SLAB_ALLOCATOR_H
#include <stddef.h>
#include <stdbool.h>
/*
 * P03 - Fixed-size slab allocator (kernel kmem_cache style)
 * Pre-allocates a slab of N objects of fixed obj_size.
 * alloc() returns a free slot in O(1); free() returns it.
 * Use a free-list of indices stored inside free slots (intrusive).
 */
typedef struct SlabCache SlabCache;
SlabCache *slab_create(size_t obj_size, size_t capacity);
void       slab_destroy(SlabCache *sc);
void      *slab_alloc(SlabCache *sc);    /* NULL if exhausted */
void       slab_free(SlabCache *sc, void *ptr);
int        slab_free_count(const SlabCache *sc);
#endif
