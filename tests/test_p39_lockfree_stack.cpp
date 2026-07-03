#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p39_lockfree_stack.h"
}
TEST(P39, BasicBehavior) { LFStack s; lfs_init(&s); LFNode n; n.val=7; lfs_push(&s,&n); EXPECT_TRUE(!lfs_empty(&s)); }
