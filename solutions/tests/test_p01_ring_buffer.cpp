
#include <gtest/gtest.h>
extern "C" { 
#include "p01_ring_buffer.h" 
}
class RbTest : public ::testing::Test {
protected: RingBuffer rb;
    void SetUp() override { ASSERT_EQ(rb_init(&rb, 8), 0); }
    void TearDown() override { rb_destroy(&rb); }
};
TEST_F(RbTest, RejectNonPow2) { RingBuffer r; EXPECT_EQ(rb_init(&r, 7), -1); }
TEST_F(RbTest, EmptyState) { EXPECT_TRUE(rb_is_empty(&rb)); EXPECT_EQ(rb_used(&rb), 0u); }
TEST_F(RbTest, PushPop) { EXPECT_EQ(rb_push(&rb, 0xAB), 0); uint8_t v; EXPECT_EQ(rb_pop(&rb, &v), 0); EXPECT_EQ(v, 0xAB); }
TEST_F(RbTest, FillFull) { for(int i=0;i<8;i++) rb_push(&rb, i); EXPECT_TRUE(rb_is_full(&rb)); EXPECT_EQ(rb_push(&rb, 9), -1); }
TEST_F(RbTest, WrapAround) {
    for(int i=0;i<8;i++) rb_push(&rb, i);
    uint8_t v; rb_pop(&rb, &v); rb_pop(&rb, &v);
    rb_push(&rb, 100); rb_push(&rb, 101);
    EXPECT_EQ(rb_used(&rb), 8u);
    rb_pop(&rb, &v); EXPECT_EQ(v, 2);
}
TEST_F(RbTest, PopEmpty) { uint8_t v; EXPECT_EQ(rb_pop(&rb, &v), -1); }
