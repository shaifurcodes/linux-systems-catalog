#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p24_bootarg_parse.h"
}
TEST(P24, BasicBehavior) {  EXPECT_TRUE(bootarg_has_flag("quiet ro","ro")); }
