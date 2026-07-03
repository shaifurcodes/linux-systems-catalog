#include "p34_bitfield_reg.h"
/* TODO: ctz32 by shifting right until (x&1)==1. Count steps.
 * reg_field_get: (reg & mask) >> ctz32(mask)
 * reg_field_prep: (val << ctz32(mask)) & mask */
int      ctz32(uint32_t x) { return 0; }
uint32_t reg_field_get(uint32_t reg, uint32_t mask) { return 0; }
uint32_t reg_field_prep(uint32_t val, uint32_t mask) { return 0; }
uint32_t reg_field_set(uint32_t reg, uint32_t mask, uint32_t val) { return reg; }
uint32_t reg_field_clear(uint32_t reg, uint32_t mask) { return reg; }