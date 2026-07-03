#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p25_log_circ.h"
}
TEST(P25, BasicBehavior) { LogBuf lb; log_init(&lb); log_write(&lb,3,"hello"); EXPECT_TRUE(log_count(&lb)==1); }
