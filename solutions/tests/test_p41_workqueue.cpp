#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p41_workqueue.h"
}
TEST(P41, BasicBehavior) { WorkQueue wq; wq_init(&wq); EXPECT_TRUE(wq.count==0); }
