#include <gtest/gtest.h>
extern "C" {
#include "p12_snap_version.h"
}

TEST(p12_snap_version, CmpEqual) { EXPECT_EQ(snap_version_cmp("1.2.3","1.2.3"),0); }

TEST(p12_snap_version, CmpLess) { EXPECT_LT(snap_version_cmp("1.0","1.2"),0); }

TEST(p12_snap_version, CmpGreater) { EXPECT_GT(snap_version_cmp("2.0","1.99"),0); }

TEST(p12_snap_version, Epoch) { EXPECT_GT(snap_version_cmp("1:1.0","0:9.9"),0); }

TEST(p12_snap_version, Satisfies) { EXPECT_TRUE(snap_version_satisfies("2.1",">=2.0")); EXPECT_FALSE(snap_version_satisfies("1.0",">=2.0")); }
