#ifndef P05_KFIFO_H
#define P05_KFIFO_H
#include <stdint.h>
#include <stddef.h>
/*
 * P05 - kfifo bulk read/write (byte stream, not single byte)
 * Extend P01: push/pop N bytes at once (like serial driver DMA burst).
 * Returns bytes actually written/read (may be less than requested if near full/empty).
 */
typedef struct { uint8_t *buf; uint32_t head, tail, cap; } KFifo;
int    kf_init(KFifo *kf, uint32_t cap);
void   kf_destroy(KFifo *kf);
size_t kf_write(KFifo *kf, const uint8_t *data, size_t len);
size_t kf_read(KFifo *kf, uint8_t *out, size_t len);
size_t kf_avail_write(const KFifo *kf);
size_t kf_avail_read(const KFifo *kf);
#endif
