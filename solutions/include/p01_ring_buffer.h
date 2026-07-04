/**
 * @file p01_ring_buffer.h
 * @brief Public API for a high-performance, kernel-style ring buffer.
 *
 * This API provides a thread-safe (single-producer, single-consumer) FIFO 
 * buffer utility. 
 *
 * @note The capacity MUST be a power of two to optimize indexing performance.
 *
 * @license MIT License
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice shall be included in all copies or substantial 
 * portions of the Software.
 */

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
    size_t head;   /* write index, never wraps */
    size_t tail;   /* read  index, never wraps */
    size_t cap;    /* must be power of two     */
} RingBuffer;

int      rb_init(RingBuffer *rb, size_t cap);   /* returns -1 if cap not pow2 */
void     rb_destroy(RingBuffer *rb);
int      rb_push(RingBuffer *rb, uint8_t byte);   /* -1 if full  */
int      rb_pop(RingBuffer *rb, uint8_t *out);    /* -1 if empty */
size_t rb_used(const RingBuffer *rb);
bool     rb_is_empty(const RingBuffer *rb);
bool     rb_is_full(const RingBuffer *rb);
#endif
