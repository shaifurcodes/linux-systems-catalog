
#include <gtest/gtest.h>
extern "C" {
#include "p07_gpio_irq_mask.h"
}
TEST(GpioIrq, EnableDisable) {
    GpioIrqCtrl g; gpio_irq_init(&g);
    gpio_irq_enable(&g, 5);
    EXPECT_TRUE(gpio_irq_is_enabled(&g, 5));
    gpio_irq_disable(&g, 5);
    EXPECT_FALSE(gpio_irq_is_enabled(&g, 5));
}
TEST(GpioIrq, Range) {
    GpioIrqCtrl g; gpio_irq_init(&g);
    gpio_irq_enable_range(&g, 8, 11);
    for(int i=8;i<=11;i++) EXPECT_TRUE(gpio_irq_is_enabled(&g, i));
    EXPECT_FALSE(gpio_irq_is_enabled(&g, 7));
}
TEST(GpioIrq, Pending) {
    GpioIrqCtrl g; gpio_irq_init(&g);
    gpio_irq_enable(&g, 3);
    uint32_t status = (1u<<3)|(1u<<7);
    EXPECT_EQ(gpio_irq_pending(&g, status), 1u<<3);
}
