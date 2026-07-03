#include "p08_mmio_rw.h"
#include <string.h>
/* TODO: cast mem+offset to volatile uint32_t* for 32-bit ops.
 * mmio_set_bits: read-modify-write with | mask
 * mmio_clear_bits: read-modify-write with & ~mask */
void     mmio_init(MmioRegion *r) { memset((void*)r->mem, 0, MMIO_SIZE); }
void     mmio_write32(MmioRegion *r, uint32_t offset, uint32_t val) {}
uint32_t mmio_read32(const MmioRegion *r, uint32_t offset) { return 0; }
void     mmio_write8(MmioRegion *r, uint32_t offset, uint8_t val) {}
uint8_t  mmio_read8(const MmioRegion *r, uint32_t offset) { return 0; }
void     mmio_set_bits(MmioRegion *r, uint32_t offset, uint32_t mask) {}
void     mmio_clear_bits(MmioRegion *r, uint32_t offset, uint32_t mask) {}