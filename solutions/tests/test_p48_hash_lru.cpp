#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p48_hash_lru.h"
}
TEST(P48, BasicBehavior) { LruCache c; lru_init(&c); lru_put(&c,1,100); uint64_t v; lru_get(&c,1,&v); EXPECT_TRUE(v==100); }
