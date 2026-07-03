#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p46_buddy_alloc.h"
}
TEST(P46, BasicBehavior) { BuddyAlloc b; buddy_init(&b); int p=buddy_alloc(&b,1); EXPECT_TRUE(p>=0); }
