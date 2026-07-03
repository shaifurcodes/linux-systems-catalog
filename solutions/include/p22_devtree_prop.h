#ifndef P22_DEVTREE_PROP_H
#define P22_DEVTREE_PROP_H
#include <stdint.h>
#include <stddef.h>
/*
 * P22 - Device tree property parser
 * Device tree properties are byte blobs. Common types:
 *   u32 cell list, string list, reg (addr+size pairs).
 * Parse a property blob into typed values.
 */
int  dt_read_u32(const uint8_t *prop, size_t len, int idx, uint32_t *out);
int  dt_read_u64(const uint8_t *prop, size_t len, int idx, uint64_t *out);
int  dt_read_string(const uint8_t *prop, size_t len, int idx, char *out, size_t out_sz);
/* reg property: address_cells=1, size_cells=1 */
int  dt_read_reg(const uint8_t *prop, size_t len, int idx, uint32_t *addr, uint32_t *size);
#endif