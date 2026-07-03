#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p32_endian_conv.h"
}
TEST(P32, BasicBehavior) {  EXPECT_TRUE(bswap32(0x12345678)==0x78563412); }
