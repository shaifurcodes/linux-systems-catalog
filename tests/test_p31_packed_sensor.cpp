#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p31_packed_sensor.h"
}
TEST(P31, BasicBehavior) { uint32_t f=sensor_encode(0xAAA,0x155,0xF,0x3F); uint16_t tmp,hum; uint8_t st,al; sensor_decode(f,&tmp,&hum,&st,&al); EXPECT_TRUE(tmp==0xAAA); }
