#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p49_cpu_affinity_map.h"
}
TEST(P49, BasicBehavior) { CpuMask m; cm_zero(&m); cm_set(&m,3); EXPECT_TRUE(cm_test(&m,3)); }
