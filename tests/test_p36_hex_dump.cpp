#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p36_hex_dump.h"
}
TEST(P36, BasicBehavior) { uint8_t d[]={0xDE,0xAD}; char out[128]; int n=hex_dump(d,2,out,128); EXPECT_TRUE(n>0); }
