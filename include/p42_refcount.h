#ifndef P42_REFCOUNT_H
#define P42_REFCOUNT_H
#include <stdbool.h>
#include <stdint.h>
/*
 * P42 - Reference counting with saturation (like Linux kref / refcount_t)
 * Saturates at UINT32_MAX (never wraps). Decrement to 0 calls release cb.
 * Protect against use-after-free by detecting get() on a zero refcount.
 */
typedef void (*release_fn)(void *obj);
typedef struct {
    uint32_t _Atomic count;
    release_fn release;
    void *obj;
} RefCount;
void rc_init(RefCount *rc, void *obj, release_fn fn);
bool rc_get(RefCount *rc);    /* false if already zero (dead object) */
bool rc_put(RefCount *rc);    /* true if this was the last ref (release called) */
uint32_t rc_read(const RefCount *rc);
#endif