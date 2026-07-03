#ifndef P32_ENDIAN_CONV_H
#define P32_ENDIAN_CONV_H
#include <stdint.h>
/*
 * P32 - Endianness conversion (like Linux cpu_to_be32 / le32_to_cpu)
 * Implement without relying on compiler builtins (for portability).
 * Also implement network byte-order helpers (htons/htonl equivalent).
 */
uint16_t bswap16(uint16_t x);
uint32_t bswap32(uint32_t x);
uint64_t bswap64(uint64_t x);
uint32_t cpu_to_be32(uint32_t x);  /* host -> big-endian */
uint32_t be32_to_cpu(uint32_t x);  /* big-endian -> host */
uint32_t cpu_to_le32(uint32_t x);
uint32_t le32_to_cpu(uint32_t x);
#endif