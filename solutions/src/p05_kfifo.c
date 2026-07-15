/**
 * @file p05_kfifo.c
 * @brief Thread-safe-ready, zero-waste ring buffer (FIFO) stream interface.
 *
 * This implementation utilizes a monotonic indexing approach where the head and
 * tail pointers grow continuously up to UINT32_MAX before wrapping naturally 
 * via unsigned overflow. This allows full utilization of the buffer capacity
 * without reserving a "dead slot" or utilizing state booleans to distinguish
 * between "full" and "empty" states.
 * 
 * @note This implementation is lock-free for single-producer, single-consumer 
 * (SPSC) scenarios provided that read/write pointer updates are atomic.
 */

#include "p05_kfifo.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Evaluates the minimum of two values.
 * @warning Evaluates arguments multiple times; do not pass expressions with side effects.
 */
#define MIN(a, b)  ((a) < (b) ? (a) : (b))

/**
 * @brief Dynamic initializer for the circular buffer.
 * 
 * Allocates raw byte storage and initializes monotonic markers.
 * 
 * @param[out] kf   Pointer to the KFifo instance to initialize.
 * @param[in]  cap  Desired capacity in bytes. Must be greater than 0.
 * @return int      0 on success, or -1 on validation/memory allocation failure.
 */
int kf_init(KFifo *kf, uint32_t cap) { 
    if (!kf || cap == 0) {
        return -1;
    }
    kf->buf = (uint8_t *)malloc(cap); 
    if (!kf->buf) {
        return -1;
    }
    kf->cap = cap;
    kf->head = 0;
    kf->tail = 0; 
    return 0; 
}

/**
 * @brief Teardown function to free internal ring buffer resources.
 * 
 * Safely releases dynamically allocated memory and clears struct metadata
 * to minimize dangling pointer vulnerabilities.
 * 
 * @param[in,out] kf Pointer to the KFifo instance to destroy.
 */
void kf_destroy(KFifo *kf) {
    if (kf) {
        free(kf->buf);
        kf->buf = NULL;
        kf->cap = 0;
        kf->head = 0;
        kf->tail = 0;
    }
}

/**
 * @brief Writes a bulk sequence of bytes to the circular buffer.
 * 
 * Copies as many bytes as possible up to the specified length without overwriting
 * unread data. If the write boundary overflows the physical buffer edge, the 
 * transaction is split into two rapid, optimized memcpy stages.
 * 
 * @param[in,out] kf    Pointer to the active KFifo structure.
 * @param[in]     data  Pointer to the source byte-array.
 * @param[in]     len   Amount of bytes requested to write.
 * @return size_t       The actual number of bytes written (may be less than requested).
 */
size_t kf_write(KFifo *kf, const uint8_t *data, size_t len) { 
    if (!kf || !kf->buf || !data || len == 0) {
        return 0; 
    }
    
    size_t write_len = MIN(len, kf_avail_write(kf));
    if (write_len == 0) {
        return 0;
    }
    
    uint32_t tail_indx = kf->tail % kf->cap;
    size_t chunk_1 = MIN(write_len, kf->cap - tail_indx); 
    size_t chunk_2 = write_len - chunk_1;
    
    memcpy(&kf->buf[tail_indx], data, chunk_1);
    if (chunk_2 > 0) {
        memcpy(&kf->buf[0], data + chunk_1, chunk_2);
    }
    
    kf->tail += write_len;
    return write_len;
}

/**
 * @brief Reads a bulk sequence of bytes out of the circular buffer.
 * 
 * Extracts ready bytes into a destination memory stream up to the requested length.
 * If the read pointer wraps around the physical array end, memory retrieval is 
 * executed in two highly optimized contiguous chunks.
 * 
 * @param[in,out] kf   Pointer to the active KFifo structure.
 * @param[out]    out  Pointer to the destination buffer to fill.
 * @param[in]     len  Maximum number of bytes to retrieve.
 * @return size_t      The actual number of bytes successfully read.
 */
size_t kf_read(KFifo *kf, uint8_t *out, size_t len) { 
    if (!kf || !kf->buf || !out || len == 0) {
        return 0;
    }
    
    size_t read_len = MIN(len, kf_avail_read(kf));
    if (read_len == 0) {
        return 0;
    }
    
    uint32_t head_indx = kf->head % kf->cap;
    size_t chunk_1 = MIN(read_len, kf->cap - head_indx); 
    size_t chunk_2 = read_len - chunk_1;
    
    memcpy(out, &kf->buf[head_indx], chunk_1); 
    if (chunk_2 > 0) {
        memcpy(out + chunk_1, &kf->buf[0], chunk_2);
    }
    
    kf->head += read_len;
    return read_len; 
}

/**
 * @brief Calculates available space remaining to write to.
 * 
 * Uses unsigned monotonic pointer difference to guarantee accurate calculations
 * even when `tail` overflows `UINT32_MAX`.
 * 
 * @param[in] kf  Pointer to the KFifo structure.
 * @return size_t Amount of free writable space in bytes.
 */
size_t kf_avail_write(const KFifo *kf) { 
    if (!kf) return 0; 
    return (kf->cap - (kf->tail - kf->head));
}

/**
 * @brief Calculates available unread payload space.
 * 
 * @param[in] kf  Pointer to the KFifo structure.
 * @return size_t Amount of readable bytes currently residing in the buffer.
 */
size_t kf_avail_read(const KFifo *kf) { 
    if (!kf) return 0; 
    return (kf->tail - kf->head);
}
