#include <gtest/gtest.h>
extern "C" {
#include "p15_cgroup_counter.h"
}

TEST(p15_cgroup_counter, Charge) { CGroupTree t; cgt_init(&t); int r=cgt_add(&t,"root",1024,- 1); EXPECT_EQ(cgt_charge(&t,r,512),0); EXPECT_EQ(cgt_usage(&t,r),512u); }

TEST(p15_cgroup_counter, LimitExceeded) { CGroupTree t; cgt_init(&t); int r=cgt_add(&t,"root",100,-1); EXPECT_EQ(cgt_charge(&t,r,200),-1); EXPECT_EQ(cgt_usage(&t,r),0u); }
