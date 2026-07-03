#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p22_devtree_prop.h"
}
TEST(P22, BasicBehavior) { uint8_t p[]={0,0,0,42}; uint32_t v; dt_read_u32(p,4,0,&v); EXPECT_TRUE(v==42); }
