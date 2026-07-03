#ifndef P45_MEMPOOL_H
#define P45_MEMPOOL_H
#include <stddef.h>
#include <stdint.h>
/*
 * P45 - Memory pool with alignment support
 * Arena allocator: bump pointer inside a fixed buffer.
 * Supports alignment requirements (4, 8, 16, 64 byte).
 * reset() frees entire pool at once (no per-object free).
 */
typedef struct { uint8_t *base; size_t cap; size_t used; size_t allocs; } MemPool;
int   mp_init(MemPool *mp, size_t cap);
void  mp_destroy(MemPool *mp);
void *mp_alloc(MemPool *mp, size_t size, size_t align);  /* NULL if OOM */
void  mp_reset(MemPool *mp);
size_t mp_used(const MemPool *mp);
size_t mp_remaining(const MemPool *mp);
#endif