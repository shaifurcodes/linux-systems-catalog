#ifndef P01_RING_BUFFER_H
#define P01_RING_BUFFER_H
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
/*
 * P01 - Kernel-style ring buffer (kfifo-like)
 * Used by: kernel log, serial drivers, DMA descriptors.
 * Constraint: capacity must be a power of two (allows mask instead of modulo).
 *
 * Hint: head & tail are ever-increasing; index = val & (cap-1)
 *       full  when (head - tail) == cap
 *       empty when head == tail
 */
typedef struct {
    uint8_t *buf;
    uint32_t head;   /* write index, never wraps */
    uint32_t tail;   /* read  index, never wraps */
    uint32_t cap;    /* must be power of two     */
} RingBuffer;

int      rb_init(RingBuffer *rb, uint32_t cap);   /* returns -1 if cap not pow2 */
void     rb_destroy(RingBuffer *rb);
int      rb_push(RingBuffer *rb, uint8_t byte);   /* -1 if full  */
int      rb_pop(RingBuffer *rb, uint8_t *out);    /* -1 if empty */
uint32_t rb_used(const RingBuffer *rb);
bool     rb_is_empty(const RingBuffer *rb);
bool     rb_is_full(const RingBuffer *rb);
#endif
