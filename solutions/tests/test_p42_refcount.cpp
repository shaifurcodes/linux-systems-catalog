#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p42_refcount.h"
}
TEST(P42, BasicBehavior) { RefCount rc; int obj=0; rc_init(&rc,&obj,nullptr); rc_get(&rc); EXPECT_TRUE(rc_read(&rc)==2); }
