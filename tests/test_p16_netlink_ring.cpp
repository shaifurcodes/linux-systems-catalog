#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p16_netlink_ring.h"
}
TEST(P16, BasicBehavior) { NlRing r; nlr_init(&r,256); EXPECT_TRUE(nlr_empty(&r)); }
