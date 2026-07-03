#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p34_bitfield_reg.h"
}
TEST(P34, BasicBehavior) {  EXPECT_TRUE(reg_field_get(0x00AB0000,0x00FF0000)==0xAB); }
