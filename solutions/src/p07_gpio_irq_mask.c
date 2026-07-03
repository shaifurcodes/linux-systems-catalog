#include "p07_gpio_irq_mask.h"
/* TODO: pure bit manipulation. No loops needed except enable_range.
 * pending = status_reg & mask_reg (interrupts that are enabled AND firing) */
void     gpio_irq_init(GpioIrqCtrl *g) {}
void     gpio_irq_enable(GpioIrqCtrl *g, int pin) {}
void     gpio_irq_disable(GpioIrqCtrl *g, int pin) {}
bool     gpio_irq_is_enabled(const GpioIrqCtrl *g, int pin) { return false; }
void     gpio_irq_enable_range(GpioIrqCtrl *g, int lo, int hi) {}
uint32_t gpio_irq_pending(const GpioIrqCtrl *g, uint32_t status_reg) { return 0; }