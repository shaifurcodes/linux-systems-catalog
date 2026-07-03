#include "p42_refcount.h"
/* TODO: rc_get: CAS loop: if count==0 return false; else increment.
 * rc_put: decrement; if new==0 call release(obj) and return true. */
void     rc_init(RefCount *rc, void *obj, release_fn fn) {}
bool     rc_get(RefCount *rc) { return false; }
bool     rc_put(RefCount *rc) { return false; }
uint32_t rc_read(const RefCount *rc) { return 0; }