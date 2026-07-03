#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p23_firmware_crc.h"
}
TEST(P23, BasicBehavior) { uint8_t img[20]={0}; fw_append_crc(img,16); EXPECT_TRUE(fw_verify(img,20)); }
