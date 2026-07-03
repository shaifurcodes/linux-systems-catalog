#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p33_crc32.h"
}
TEST(P33, BasicBehavior) { uint8_t d[]={1,2,3,4}; uint32_t c=crc32_buf(d,4); EXPECT_TRUE(c!=0); }
