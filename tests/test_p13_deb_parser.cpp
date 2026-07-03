#include <gtest/gtest.h>
extern "C" {
#include "p13_deb_parser.h"
}

TEST(p13_deb_parser, ParseBasic) { DebControl c; ASSERT_EQ(deb_parse("Package: vim\nVersion: 9.0\n", &c), 0); EXPECT_STREQ(deb_get(&c,"Package"),"vim"); }

TEST(p13_deb_parser, MissingKey) { DebControl c; deb_parse("A: 1\n",&c); EXPECT_EQ(deb_get(&c,"Z"),nullptr); }
