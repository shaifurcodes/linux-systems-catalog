#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p50_snap_health.h"
}
TEST(P50, BasicBehavior) { SnapHealth h; sh_init(&h); sh_report(&h,HEALTH_ERROR,"fail"); sh_report(&h,HEALTH_ERROR,"fail"); sh_report(&h,HEALTH_ERROR,"fail"); EXPECT_TRUE(sh_is_critical(&h)); }
