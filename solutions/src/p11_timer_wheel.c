#include "p11_timer_wheel.h"
#include <string.h>
/* TODO: slot = expire_tick & (WHEEL_SLOTS-1). tw_tick increments now,
 * walks slot[now & mask], fires callbacks, re-inserts periodic timers. */
void tw_init(TimerWheel *tw) { memset(tw, 0, sizeof(*tw)); }
int  tw_add(TimerWheel *tw, TimerNode *t, uint32_t delay_ticks, uint32_t period) { return -1; }
void tw_tick(TimerWheel *tw) {}
int  tw_cancel(TimerWheel *tw, TimerNode *t) { return -1; }