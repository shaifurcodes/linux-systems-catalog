#ifndef P11_TIMER_WHEEL_H
#define P11_TIMER_WHEEL_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P11 - Software timer wheel (simplified Linux hrtimer/timer_list)
 * Fixed 256-slot wheel, 1 tick = 1ms.
 * Timers fire when the wheel hand reaches their slot.
 * Supports single-shot and periodic timers.
 */
#define WHEEL_SLOTS 256
typedef void (*timer_cb)(void *arg);
typedef struct TimerNode {
    uint32_t       expire_tick;
    uint32_t       period_ticks; /* 0 = one-shot */
    timer_cb       cb;
    void          *arg;
    struct TimerNode *next;
} TimerNode;
typedef struct { TimerNode *slots[WHEEL_SLOTS]; uint32_t now; } TimerWheel;
void tw_init(TimerWheel *tw);
int  tw_add(TimerWheel *tw, TimerNode *t, uint32_t delay_ticks, uint32_t period);
void tw_tick(TimerWheel *tw);        /* advance one tick, fire expired timers */
int  tw_cancel(TimerWheel *tw, TimerNode *t);
#endif