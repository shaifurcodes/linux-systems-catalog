#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p27_mount_parser.h"
}
TEST(P27, BasicBehavior) { MountTable t; mt_parse("/dev/sda1 / ext4 rw 0 0\n",&t); EXPECT_TRUE(t.count==1); }
