#include "p03_slab_allocator.h"
#include <stdlib.h>
/* TODO: store a next-free index at the start of each free slot.
 * Head of free list = index of first free slot, -1 when empty. */
SlabCache *slab_create(size_t obj_size, size_t capacity) { return NULL; }
void       slab_destroy(SlabCache *sc) {}
void      *slab_alloc(SlabCache *sc) { return NULL; }
void       slab_free(SlabCache *sc, void *ptr) {}
int        slab_free_count(const SlabCache *sc) { return 0; }
