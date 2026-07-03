
#include <gtest/gtest.h>
extern "C" {
#include "p03_slab_allocator.h"
}
TEST(Slab, AllocFree) {
    SlabCache *sc = slab_create(64, 8);
    ASSERT_NE(sc, nullptr);
    void *p = slab_alloc(sc);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(slab_free_count(sc), 7);
    slab_free(sc, p);
    EXPECT_EQ(slab_free_count(sc), 8);
    slab_destroy(sc);
}
TEST(Slab, Exhausted) {
    SlabCache *sc = slab_create(8, 2);
    slab_alloc(sc); slab_alloc(sc);
    EXPECT_EQ(slab_alloc(sc), nullptr);
    slab_destroy(sc);
}
TEST(Slab, ReuseFreed) {
    SlabCache *sc = slab_create(16, 4);
    void *p = slab_alloc(sc);
    slab_free(sc, p);
    void *p2 = slab_alloc(sc);
    EXPECT_NE(p2, nullptr);
    slab_destroy(sc);
}
