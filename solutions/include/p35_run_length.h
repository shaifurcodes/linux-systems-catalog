#ifndef P35_RUN_LENGTH_H
#define P35_RUN_LENGTH_H
#include <stddef.h>
#include <stdint.h>
/*
 * P35 - Run-length encoding for binary firmware patches
 * Format: [count:u8][byte:u8] pairs. count=0 is invalid (skip).
 * Used in delta firmware update compression.
 */
int rle_encode(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap);
int rle_decode(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap);
/* returns -1 if output buffer too small; else returns bytes written */
#endif