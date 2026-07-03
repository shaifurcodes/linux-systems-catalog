#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p17_ioctl_dispatch.h"
}
TEST(P17, BasicBehavior) { IoctlTable t; ioctl_table_init(&t); EXPECT_TRUE(t.count==0); }
