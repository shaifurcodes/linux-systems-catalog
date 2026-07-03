#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p37_argv_parse.h"
}
TEST(P37, BasicBehavior) { ArgList al; argv_parse("cmd -v --out=file",&al); EXPECT_TRUE(argv_has_flag(&al,"-v")); }
