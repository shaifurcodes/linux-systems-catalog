#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p45_mempool.h"
}
TEST(P45, BasicBehavior) { MemPool mp; mp_init(&mp,1024); void *p=mp_alloc(&mp,64,8); EXPECT_TRUE(p!=nullptr); }
