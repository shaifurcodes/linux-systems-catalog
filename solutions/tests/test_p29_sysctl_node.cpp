#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p29_sysctl_node.h"
}
TEST(P29, BasicBehavior) { SysctlTable t; sysctl_init(&t); int v=0; sysctl_register(&t,"k/x",&v,0,100); EXPECT_TRUE(sysctl_write(&t,"k/x",50)==0); }
