#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p18_dma_scatter.h"
}
TEST(P18, BasicBehavior) { SgList sg; sg_build(&sg,(void*)0x1000,4096,1024); EXPECT_TRUE(sg_nents(&sg)==4); }
