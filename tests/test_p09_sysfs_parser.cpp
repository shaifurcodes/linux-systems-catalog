
#include <gtest/gtest.h>
extern "C" {
#include "p09_sysfs_parser.h"
}
TEST(Sysfs, ParseInt) { long v; EXPECT_EQ(sysfs_parse_int("42\n", &v), 0); EXPECT_EQ(v, 42); }
TEST(Sysfs, ParseBoolVariants) {
    bool b;
    EXPECT_EQ(sysfs_parse_bool("1", &b), 0); EXPECT_TRUE(b);
    EXPECT_EQ(sysfs_parse_bool("true", &b), 0); EXPECT_TRUE(b);
    EXPECT_EQ(sysfs_parse_bool("off", &b), 0); EXPECT_FALSE(b);
    EXPECT_EQ(sysfs_parse_bool("0", &b), 0); EXPECT_FALSE(b);
}
TEST(Sysfs, ParseAttrInt) {
    SysfsAttr a;
    EXPECT_EQ(sysfs_parse("speed=100\n", &a), 0);
    EXPECT_STREQ(a.key, "speed");
    EXPECT_EQ(a.type, SYSFS_INT);
    EXPECT_EQ(a.v.ival, 100);
}
