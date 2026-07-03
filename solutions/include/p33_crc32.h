#ifndef P33_CRC32_H
#define P33_CRC32_H
#include <stdint.h>
#include <stddef.h>
/*
 * P33 - CRC32 with incremental update (like Linux lib/crc32.c)
 * Used for: block device checksums, firmware integrity, snap assertions.
 * Support incremental computation across multiple buffers.
 */
uint32_t crc32_init(void);                              /* returns 0xFFFFFFFF */
uint32_t crc32_update(uint32_t crc, const uint8_t *buf, size_t len);
uint32_t crc32_final(uint32_t crc);                     /* XOR with 0xFFFFFFFF */
uint32_t crc32_buf(const uint8_t *buf, size_t len);     /* one-shot */
int      crc32_verify(const uint8_t *buf, size_t len, uint32_t expected);
#endif