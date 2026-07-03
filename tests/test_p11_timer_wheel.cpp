
#include <gtest/gtest.h>
extern "C" {
#include "p11_timer_wheel.h"
}
static int fire_count = 0;
static void on_fire(void *a) { fire_count++; }
TEST(TimerWheel, SingleShot) {
    TimerWheel tw; tw_init(&tw); fire_count=0;
    TimerNode t;
    tw_add(&tw, &t, 5, 0);
    for(int i=0;i<5;i++) tw_tick(&tw);
    EXPECT_EQ(fire_count, 1);
    for(int i=0;i<5;i++) tw_tick(&tw);
    EXPECT_EQ(fire_count, 1);
}
TEST(TimerWheel, Periodic) {
    TimerWheel tw; tw_init(&tw); fire_count=0;
    TimerNode t;
    tw_add(&tw, &t, 4, 4);
    for(int i=0;i<12;i++) tw_tick(&tw);
    EXPECT_EQ(fire_count, 3);
}
TEST(TimerWheel, Cancel) {
    TimerWheel tw; tw_init(&tw); fire_count=0;
    TimerNode t;
    tw_add(&tw, &t, 10, 0);
    tw_cancel(&tw, &t);
    for(int i=0;i<15;i++) tw_tick(&tw);
    EXPECT_EQ(fire_count, 0);
}
