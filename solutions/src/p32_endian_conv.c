#include "p32_endian_conv.h"
/* TODO: detect host endianness with a union or static const.
 * bswap32: ((x>>24)&0xFF) | ((x>>8)&0xFF00) | ((x<<8)&0xFF0000) | (x<<24) */
uint16_t bswap16(uint16_t x) { return 0; }
uint32_t bswap32(uint32_t x) { return 0; }
uint64_t bswap64(uint64_t x) { return 0; }
uint32_t cpu_to_be32(uint32_t x) { return 0; }
uint32_t be32_to_cpu(uint32_t x) { return 0; }
uint32_t cpu_to_le32(uint32_t x) { return 0; }
uint32_t le32_to_cpu(uint32_t x) { return 0; }