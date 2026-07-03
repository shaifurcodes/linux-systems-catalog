#include "p01_ring_buffer.h"
/* TODO: implement. Remember: cap must be power of two.
 * index into buf = value & (cap - 1)   <-- no division needed */
int rb_init(RingBuffer *rb, size_t cap) { return -1; }
void rb_destroy(RingBuffer *rb) {}
int rb_push(RingBuffer *rb, uint8_t byte) { return -1; }
int rb_pop(RingBuffer *rb, uint8_t *out) { return -1; }
size_t rb_used(const RingBuffer *rb) { return 0; }
bool rb_is_empty(const RingBuffer *rb) { return true; }
bool rb_is_full(const RingBuffer *rb) { return false; }
