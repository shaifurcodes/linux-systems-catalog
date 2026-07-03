#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p40_spinlock_sim.h"
}
TEST(P40, BasicBehavior) { SpinLock l; spin_init(&l); spin_lock(&l); spin_unlock(&l); EXPECT_TRUE(l.acquires==1); }
