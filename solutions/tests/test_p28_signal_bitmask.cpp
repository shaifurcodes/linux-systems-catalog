#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p28_signal_bitmask.h"
}
TEST(P28, BasicBehavior) { SigSet s; sigset_empty(&s); sigset_add(&s,9); EXPECT_TRUE(sigset_has(&s,9)); }
