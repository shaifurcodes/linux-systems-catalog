#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p47_rb_tree_light.h"
}
TEST(P47, BasicBehavior) { RbTree t; rbt_init(&t); RbNode n; rbt_insert(&t,&n,42,nullptr); EXPECT_TRUE(rbt_count(&t)==1); }
