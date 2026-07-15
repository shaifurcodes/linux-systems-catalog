/**
 * @file p05_kfifo.h
 * @brief High-performance bulk ring buffer (FIFO) for byte streams.
 *
 * This module extends a standard single-byte circular buffer to support bulk
 * push (write) and pop (read) operations. It is designed for high-throughput
 * scenarios such as serial driver DMA bursts, network packets, or IPC pipelines.
 *
 * The implementation uses monotonic, unsigned wrapping indices for thread-safety 
 * in single-producer, single-consumer (SPSC) setups and eliminates the classic 
 * "lost slot" capacity limitation.
 */

#ifndef P05_KFIFO_H
#define P05_KFIFO_H

#include <stdint.h>
#include <stddef.h>

/**
 * @struct KFifo
 * @brief Circular queue control block representing the FIFO state.
 */
typedef struct 
{ 
    uint8_t *buf;   /**< Pointer to dynamically allocated memory storage. */
    uint32_t head;  /**< Monotonic read index (continuously increasing). */
    uint32_t tail;  /**< Monotonic write index (continuously increasing). */
    uint32_t cap;   /**< Total capacity of the buffer in bytes. */
} KFifo;

/**
 * @brief Initializes a KFifo instance with dynamically allocated memory.
 * 
 * @param[out] kf   Pointer to the KFifo instance to initialize.
 * @param[in]  cap  Capacity of the buffer in bytes (must be greater than 0).
 * @return int      0 on success, or -1 on initialization/memory allocation failure.
 */
int kf_init(KFifo *kf, uint32_t cap);

/**
 * @brief Destroys a KFifo instance and frees its allocated resources.
 * 
 * @param[in,out] kf Pointer to the KFifo instance to tear down.
 */
void kf_destroy(KFifo *kf);

/**
 * @brief Writes a block of memory into the circular buffer.
 * 
 * Copies up to @p len bytes from the source buffer @p data into the FIFO. 
 * If the free space in the FIFO is smaller than @p len, only the available space 
 * is written.
 * 
 * @param[in,out] kf    Pointer to the active KFifo structure.
 * @param[in]     data  Pointer to the source byte array to copy from.
 * @param[in]     len   Number of bytes requested to write.
 * @return size_t       The actual number of bytes written.
 */
size_t kf_write(KFifo *kf, const uint8_t *data, size_t len);

/**
 * @brief Reads a block of memory out of the circular buffer.
 * 
 * Retrieves up to @p len bytes from the FIFO and copies them into @p out.
 * If the available payload in the FIFO is smaller than @p len, only the 
 * available bytes are read.
 * 
 * @param[in,out] kf   Pointer to the active KFifo structure.
 * @param[out]    out  Pointer to the destination buffer to copy data into.
 * @param[in]     len  Maximum number of bytes requested to read.
 * @return size_t      The actual number of bytes read.
 */
size_t kf_read(KFifo *kf, uint8_t *out, size_t len);

/**
 * @brief Returns the free space available in the buffer for writing.
 * 
 * @param[in] kf  Pointer to the KFifo structure.
 * @return size_t The number of bytes that can currently be written to the FIFO.
 */
size_t kf_avail_write(const KFifo *kf);

/**
 * @brief Returns the number of unread bytes residing in the buffer.
 * 
 * @param[in] kf  Pointer to the KFifo structure.
 * @return size_t The number of bytes available to be read from the FIFO.
 */
size_t kf_avail_read(const KFifo *kf);

#endif /* P05_KFIFO_H */
