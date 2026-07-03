
#include <gtest/gtest.h>
extern "C" {
#include "p05_kfifo.h"
}
TEST(KFifo, BulkWriteRead) {
    KFifo kf; kf_init(&kf, 16);
    uint8_t data[] = {1,2,3,4,5};
    EXPECT_EQ(kf_write(&kf, data, 5), 5u);
    uint8_t out[5]; EXPECT_EQ(kf_read(&kf, out, 5), 5u);
    for(int i=0;i<5;i++) EXPECT_EQ(out[i], data[i]);
    kf_destroy(&kf);
}
TEST(KFifo, PartialWrite) {
    KFifo kf; kf_init(&kf, 4);
    uint8_t data[] = {0,1,2,3,4,5};
    size_t w = kf_write(&kf, data, 6);
    EXPECT_LE(w, 4u);
    kf_destroy(&kf);
}
