#ifndef P08_MMIO_RW_H
#define P08_MMIO_RW_H
#include <stdint.h>
/*
 * P08 - MMIO register read/write helpers
 * Simulates readl/writel/readw/writeb used in Linux device drivers.
 * Uses a byte array as the "device MMIO window".
 * All accesses must be volatile and respect alignment.
 */
#define MMIO_SIZE 256
typedef struct { volatile uint8_t mem[MMIO_SIZE]; } MmioRegion;
void     mmio_init(MmioRegion *r);
void     mmio_write32(MmioRegion *r, uint32_t offset, uint32_t val);
uint32_t mmio_read32(const MmioRegion *r, uint32_t offset);
void     mmio_write8(MmioRegion *r, uint32_t offset, uint8_t val);
uint8_t  mmio_read8(const MmioRegion *r, uint32_t offset);
void     mmio_set_bits(MmioRegion *r, uint32_t offset, uint32_t mask);
void     mmio_clear_bits(MmioRegion *r, uint32_t offset, uint32_t mask);
#endif