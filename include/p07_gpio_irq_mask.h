#ifndef P07_GPIO_IRQ_MASK_H
#define P07_GPIO_IRQ_MASK_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P07 - GPIO interrupt mask register operations
 * Simulates a 32-bit MMIO interrupt mask register (each bit = one GPIO line).
 * Common in Linux gpio/irqchip drivers.
 */
typedef struct { volatile uint32_t mask_reg; } GpioIrqCtrl;
void     gpio_irq_init(GpioIrqCtrl *g);
void     gpio_irq_enable(GpioIrqCtrl *g, int pin);   /* set bit */
void     gpio_irq_disable(GpioIrqCtrl *g, int pin);  /* clear bit */
bool     gpio_irq_is_enabled(const GpioIrqCtrl *g, int pin);
void     gpio_irq_enable_range(GpioIrqCtrl *g, int lo, int hi);
uint32_t gpio_irq_pending(const GpioIrqCtrl *g, uint32_t status_reg);
#endif