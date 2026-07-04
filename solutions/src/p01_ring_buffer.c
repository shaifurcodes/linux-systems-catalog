/**
 * @file p01_ring_buffer.c
 * @brief Implementation of the power-of-two ring buffer.
 *
 * This implementation relies on unsigned integer wrapping semantics and 
 * bitwise AND masking instead of modulo (%) operations to achieve 
 * kernel-level instruction efficiency.
 *
 * @license MIT License (See p01_ring_buffer.h for full text)
 */

#include "p01_ring_buffer.h"
#include <stdlib.h>

/**
 * @brief Checks if a capacity value is a non-zero power of two.
 *
 * Uses a bitwise trick where a power of two has exactly one bit set.
 *
 * @param cap The capacity value to check.
 * @return true if cap is a power of two, false otherwise.
 */
bool static inline is_power_of_two(size_t cap) {
  return (cap > 0) && ((cap & (cap - 1)) == 0);
}

/**
 * @brief Calculates the number of bytes currently stored in the ring buffer.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @return The number of bytes used, or 0 if rb is NULL.
 */
size_t rb_used(const RingBuffer *rb) {
  // Unsigned subtraction safely handles natural integer overflow wrapping.
  return rb ? (rb->head - rb->tail) : 0;
}

/**
 * @brief Checks if the ring buffer is empty.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @return true if empty or rb is NULL, false otherwise.
 */
bool rb_is_empty(const RingBuffer *rb) {
  return rb ? (rb->head == rb->tail) : true;
}

/**
 * @brief Checks if the ring buffer is completely full.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @return true if full, false if not full or rb is NULL.
 */
bool rb_is_full(const RingBuffer *rb) {
  return rb ? (rb_used(rb) == rb->cap) : false;
}

/**
 * @brief Initializes a RingBuffer instance.
 *
 * Allocates memory for the internal buffer and resets tracking indices.
 *
 * @param rb Pointer to the RingBuffer to initialize.
 * @param cap Capacity of the buffer. Must be a power of two.
 * @return 0 on success, -1 if arguments are invalid or allocation fails.
 */
int rb_init(RingBuffer *rb, size_t cap) {
  if (!rb || !is_power_of_two(cap)) {
    return -1;
  }
  rb->buf = (uint8_t *)malloc(cap);
  if (!rb->buf) {
    return -1;
  }
  rb->cap = cap;
  rb->head = 0;
  rb->tail = 0;
  return 0;
}

/**
 * @brief Frees the internal buffer resources and resets the structure fields.
 *
 * @param rb Pointer to the RingBuffer instance to destroy. Safe if NULL.
 */
void rb_destroy(RingBuffer *rb) {
  if (rb) {
    free(rb->buf);
    rb->buf = NULL;
    rb->cap = 0;
    rb->head = 0;
    rb->tail = 0;
  }
}

/**
 * @brief Pushes a single byte onto the ring buffer.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @param byte The data byte to add.
 * @return 0 on success, -1 if the buffer is full or rb is NULL.
 */
int rb_push(RingBuffer *rb, uint8_t byte) {
  if (!rb || rb_is_full(rb)) {
    return -1;
  }
  // Masking with (cap - 1) maps the ever-increasing head index to the array.
  rb->buf[rb->head & (rb->cap - 1)] = byte;
  ++rb->head;
  return 0;
}

/**
 * @brief Pops a single byte off the ring buffer.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @param out Destination pointer where the popped byte will be written.
 * @return 0 on success, -1 if the buffer is empty or pointers are invalid.
 */
int rb_pop(RingBuffer *rb, uint8_t *out) {
  if (!rb || !out || rb_is_empty(rb)) {
    return -1;
  }
  // Masking with (cap - 1) maps the ever-increasing tail index to the array.
  *out = rb->buf[rb->tail & (rb->cap - 1)];
  ++rb->tail;
  return 0;
}
