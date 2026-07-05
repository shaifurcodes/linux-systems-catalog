#include "p03_slab_allocator.h"
#include <stdlib.h>
#include <stdint.h>

struct SlabCache {
    char *memory;         /* The raw block of allocated memory */
    size_t obj_size;      /* Size of each object (adjusted for minimal index size) */
    size_t capacity;      /* Total number of slots available */
    ptrdiff_t free_head;  /* Index of the first free slot, or -1 if full */
    int free_count;       /* Tracking the current number of free slots */
};

SlabCache *slab_create(size_t obj_size, size_t capacity) {
    if (capacity == 0) return NULL;

    /* Ensure each object slot is at least large enough to hold a next-index integer.
     * We use ptrdiff_t to store indices safely. */
    if (obj_size < sizeof(ptrdiff_t)) {
        obj_size = sizeof(ptrdiff_t);
    }

    SlabCache *sc = (SlabCache *)malloc(sizeof(SlabCache));
    if (!sc) return NULL;

    sc->memory = (char *)malloc(obj_size * capacity);
    if (!sc->memory) {
        free(sc);
        return NULL;
    }

    sc->obj_size = obj_size;
    sc->capacity = capacity;
    sc->free_head = 0;
    sc->free_count = (int)capacity;

    /* Initialize the intrusive free list: each slot stores the index of the next slot.
     * The last slot stores -1 to signify the end of the free list. */
    for (size_t i = 0; i < capacity; i++) {
        char *slot_ptr = sc->memory + (i * obj_size);
        ptrdiff_t *next_free_slot = (ptrdiff_t *)slot_ptr;
        
        if (i == capacity - 1) {
            *next_free_slot = -1; /* End of list */
        } else {
            *next_free_slot = (ptrdiff_t)(i + 1);
        }
    }

    return sc;
}

void slab_destroy(SlabCache *sc) {
    if (!sc) return;
    free(sc->memory);
    free(sc);
}

void *slab_alloc(SlabCache *sc) {
    if (!sc || sc->free_head == -1) {
        return NULL; /* Out of memory / Exhausted */
    }

    /* O(1) Allocation: Pop the head from the free list */
    ptrdiff_t allocated_idx = sc->free_head;
    char *allocated_ptr = sc->memory + (allocated_idx * sc->obj_size);

    /* The first bytes of the free slot contain the index of the *next* free slot */
    sc->free_head = *(ptrdiff_t *)allocated_ptr;
    sc->free_count--;

    return (void *)allocated_ptr;
}

void slab_free(SlabCache *sc, void *ptr) {
    if (!sc || !ptr) return;

    /* Calculate the index of the pointer based on memory offsets */
    char *char_ptr = (char *)ptr;
    ptrdiff_t offset = char_ptr - sc->memory;
    ptrdiff_t free_idx = offset / sc->obj_size;

    /* Sanity bounds-checking */
    if (free_idx < 0 || (size_t)free_idx >= sc->capacity) return;

    /* O(1) Free: Push the slot back onto the front of the free list */
    ptrdiff_t *next_free_slot = (ptrdiff_t *)ptr;
    *next_free_slot = sc->free_head;
    
    sc->free_head = free_idx;
    sc->free_count++;
}

int slab_free_count(const SlabCache *sc) {
    return sc ? sc->free_count : 0;
}
