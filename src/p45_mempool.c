#include "p45_mempool.h"
#include <stdlib.h>
#include <string.h>
/* TODO: align up: ptr = (ptr + align-1) & ~(align-1). Check ptr+size <= base+cap. */
int    mp_init(MemPool *mp, size_t cap) { return -1; }
void   mp_destroy(MemPool *mp) {}
void  *mp_alloc(MemPool *mp, size_t size, size_t align) { return NULL; }
void   mp_reset(MemPool *mp) {}
size_t mp_used(const MemPool *mp) { return 0; }
size_t mp_remaining(const MemPool *mp) { return 0; }