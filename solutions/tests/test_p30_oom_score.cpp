#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p30_oom_score.h"
}
TEST(P30, BasicBehavior) { OomTable t; oom_init(&t,1000); oom_add_proc(&t,42,100,0,"bash"); EXPECT_TRUE(oom_select_victim(&t)==42); }
