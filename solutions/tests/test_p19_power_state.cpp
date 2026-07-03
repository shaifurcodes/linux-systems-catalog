#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p19_power_state.h"
}
TEST(P19, BasicBehavior) { PowerDev d; pwr_init(&d); EXPECT_TRUE(pwr_is_active(&d)); }
