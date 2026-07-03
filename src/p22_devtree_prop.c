#include "p22_devtree_prop.h"
#include <string.h>
/* TODO: u32 values are big-endian in device tree. Byte-swap on little-endian hosts.
 * u32[idx]: offset = idx*4. u64[idx]: offset = idx*8.
 * string[idx]: skip idx null-terminated strings. */
int dt_read_u32(const uint8_t *prop, size_t len, int idx, uint32_t *out) { return -1; }
int dt_read_u64(const uint8_t *prop, size_t len, int idx, uint64_t *out) { return -1; }
int dt_read_string(const uint8_t *prop, size_t len, int idx, char *out, size_t out_sz) { return -1; }
int dt_read_reg(const uint8_t *prop, size_t len, int idx, uint32_t *addr, uint32_t *size) { return -1; }