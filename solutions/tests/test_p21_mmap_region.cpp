#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p21_mmap_region.h"
}
TEST(P21, BasicBehavior) { MmapTracker t; mm_init(&t); mm_map(&t,0x1000,4096,3); EXPECT_TRUE(mm_is_mapped(&t,0x1000)); }
