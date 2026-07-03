
#include <gtest/gtest.h>
extern "C" {
#include "p08_mmio_rw.h"
}
TEST(Mmio, Write32Read32) {
    MmioRegion r; mmio_init(&r);
    mmio_write32(&r, 0, 0xDEADBEEF);
    EXPECT_EQ(mmio_read32(&r, 0), 0xDEADBEEFu);
}
TEST(Mmio, SetClearBits) {
    MmioRegion r; mmio_init(&r);
    mmio_write32(&r, 4, 0x00FF00FF);
    mmio_set_bits(&r, 4, 0xFF000000);
    EXPECT_EQ(mmio_read32(&r, 4), 0xFF0F00FFu & mmio_read32(&r, 4) | 0xFF0000FFu);
    mmio_clear_bits(&r, 4, 0x000000FF);
    EXPECT_EQ(mmio_read32(&r, 4) & 0xFF, 0u);
}
TEST(Mmio, Write8Read8) {
    MmioRegion r; mmio_init(&r);
    mmio_write8(&r, 10, 0xAB);
    EXPECT_EQ(mmio_read8(&r, 10), 0xABu);
}
