#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p20_watchdog.h"
}
TEST(P20, BasicBehavior) { Watchdog w; wdt_init(&w,10,nullptr,nullptr); wdt_enable(&w); EXPECT_TRUE(wdt_is_healthy(&w)); }
