#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p35_run_length.h"
}
TEST(P35, BasicBehavior) { uint8_t in[]={1,1,1,2,2,3}; uint8_t out[16]; int n=rle_encode(in,6,out,16); EXPECT_TRUE(n==6); }
