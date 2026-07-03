#ifndef P34_BITFIELD_REG_H
#define P34_BITFIELD_REG_H
#include <stdint.h>
/*
 * P34 - Hardware register bitfield accessor (FIELD_GET/FIELD_PREP style)
 * Linux kernel uses FIELD_GET(mask, val) and FIELD_PREP(mask, val).
 * Implement a portable version without typeof/__builtin_ctzl.
 * mask encodes both position and width: e.g. 0x00FF0000 = bits 16..23.
 */
uint32_t reg_field_get(uint32_t reg, uint32_t mask);
uint32_t reg_field_prep(uint32_t val, uint32_t mask);
uint32_t reg_field_set(uint32_t reg, uint32_t mask, uint32_t val);
uint32_t reg_field_clear(uint32_t reg, uint32_t mask);
/* count trailing zeros without __builtin_ctz */
int      ctz32(uint32_t x);
#endif