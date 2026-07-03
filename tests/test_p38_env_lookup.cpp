#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p38_env_lookup.h"
}
TEST(P38, BasicBehavior) { EnvStore e; env_init(&e); env_set(&e,"HOME","/root"); EXPECT_TRUE(strcmp(env_get(&e,"HOME"),"/root")==0); }
