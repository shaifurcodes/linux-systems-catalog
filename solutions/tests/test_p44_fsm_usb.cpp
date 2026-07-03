#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p44_fsm_usb.h"
}
TEST(P44, BasicBehavior) { UsbDev d; usb_dev_init(&d); EXPECT_TRUE(d.state==USB_ATTACHED); }
