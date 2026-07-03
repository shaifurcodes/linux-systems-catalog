#include <gtest/gtest.h>
#include <cstring>
extern "C" {
#include "p43_fsm_uart.h"
}
TEST(P43, BasicBehavior) { UartFsm f; uart_fsm_init(&f); EXPECT_TRUE(f.state==UART_IDLE); }
