#include <gtest/gtest.h>
extern "C" {
#include "p02_inode_cache.h"
}
TEST(InodeCache, InsertLookup) {
    InodeCache c; ic_init(&c);
    ic_insert(&c, 42, 0755, 1024);
    auto *e = ic_lookup(&c, 42);
    ASSERT_NE(e, nullptr);
    EXPECT_EQ(e->mode, 0755u);
    EXPECT_EQ(e->size, 1024u);
}
TEST(InodeCache, MissReturnsNull) { InodeCache c; ic_init(&c); EXPECT_EQ(ic_lookup(&c, 999), nullptr); }
TEST(InodeCache, Evict) {
    InodeCache c; ic_init(&c);
    ic_insert(&c, 1, 0644, 0);
    ic_evict(&c, 1);
    EXPECT_EQ(ic_lookup(&c, 1), nullptr);
}
TEST(InodeCache, LRUEvictionOnFull) {
    InodeCache c; ic_init(&c);
    for(int i=0; i<INODE_CACHE_SIZE; i++) ic_insert(&c, i, 0, 0);
    ic_insert(&c, 9999, 0, 0);
    EXPECT_NE(ic_lookup(&c, 9999), nullptr);
    EXPECT_EQ(ic_count(&c), INODE_CACHE_SIZE);
}
