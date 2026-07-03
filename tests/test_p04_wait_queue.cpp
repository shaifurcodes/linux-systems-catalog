
#include <gtest/gtest.h>
extern "C" {
#include "p04_wait_queue.h"
}
TEST(WaitQueue, AddWakeOne) {
    WaitQueue wq; wq_init(&wq);
    wq_add(&wq, 10); wq_add(&wq, 20);
    EXPECT_EQ(wq_count(&wq), 2);
    EXPECT_EQ(wq_wake_one(&wq), 10);
    EXPECT_EQ(wq_count(&wq), 1);
}
TEST(WaitQueue, WakeAll) {
    WaitQueue wq; wq_init(&wq);
    for(int i=1;i<=5;i++) wq_add(&wq, i);
    int out[8]; int n = wq_wake_all(&wq, out, 8);
    EXPECT_EQ(n, 5); EXPECT_EQ(wq_count(&wq), 0);
}
TEST(WaitQueue, EmptyWake) { WaitQueue wq; wq_init(&wq); EXPECT_EQ(wq_wake_one(&wq), -1); }
