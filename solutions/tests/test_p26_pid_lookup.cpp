#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p26_pid_lookup.h"
}
TEST(P26, BasicBehavior) { PidMap pm; pid_map_init(&pm); int p=pid_alloc(&pm); EXPECT_TRUE(p>=2); }
