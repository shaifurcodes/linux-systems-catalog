/**
 * @file p01_ring_buffer.h
 * @brief Public API for a high-performance, kernel-style ring buffer.
 *
 * This API provides a lightweight, thread-safe (single-producer, single-consumer) 
 * FIFO buffer utility suitable for kernel logging, serial drivers, and DMA descriptors.
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

/**
 * @struct RingBuffer
 * @brief Structure representing the ring buffer instance.
 *
 * Utilizes ever-increasing tracking indices to eliminate wrapping logic overhead.
 */
typedef struct {
  uint8_t *buf; /**< Pointer to the dynamically allocated data buffer. */
  size_t head;  /**< Write index. Ever-increasing, never manually wrapped. */
  size_t tail;  /**< Read index. Ever-increasing, never manually wrapped. */
  size_t cap;   /**< Total capacity of the buffer. Must be a power of two. */
} RingBuffer;

/**
 * @brief Initializes a RingBuffer instance.
 *
 * Allocates internal buffer memory and resets tracking state.
 *
 * @note The capacity parameter must be a power of two.
 * @param rb Pointer to the RingBuffer structure to initialize.
 * @param cap The desired capacity of the buffer (must be a power of two).
 * @return 0 on success, -1 if the capacity is invalid or allocation fails.
 */
int rb_init(RingBuffer *rb, size_t cap);

/**
 * @brief Frees all resources associated with the RingBuffer.
 *
 * @param rb Pointer to the RingBuffer instance to destroy. Safe if NULL.
 */
void rb_destroy(RingBuffer *rb);

/**
 * @brief Pushes a single byte onto the ring buffer.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @param byte The data byte to insert.
 * @return 0 on success, -1 if the buffer is full or the instance is invalid.
 */
int rb_push(RingBuffer *rb, uint8_t byte);

/**
 * @brief Pops a single byte off the ring buffer.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @param out Destination pointer where the retrieved byte will be stored.
 * @return 0 on success, -1 if the buffer is empty or pointers are invalid.
 */
int rb_pop(RingBuffer *rb, uint8_t *out);

/**
 * @brief Calculates the number of bytes currently stored in the ring buffer.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @return The total number of unread bytes, or 0 if rb is NULL.
 */
size_t rb_used(const RingBuffer *rb);

/**
 * @brief Checks if the ring buffer contains no data.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @return true if empty or rb is NULL, false otherwise.
 */
bool rb_is_empty(const RingBuffer *rb);

/**
 * @brief Checks if the ring buffer has reached its maximum capacity.
 *
 * @param rb Pointer to the RingBuffer instance.
 * @return true if full, false if space is available or rb is NULL.
 */
bool rb_is_full(const RingBuffer *rb);
#endif
