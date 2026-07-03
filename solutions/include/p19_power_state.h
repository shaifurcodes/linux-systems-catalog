#ifndef P19_POWER_STATE_H
#define P19_POWER_STATE_H
#include <stdbool.h>
/*
 * P19 - Device power state machine (Linux PM: D0/D1/D2/D3)
 * Implement transitions and transition validation.
 * Invalid transitions must be rejected.
 * Track transition count and time-in-state (simulated tick counter).
 */
typedef enum { D0=0, D1, D2, D3, D_INVALID } DState;
typedef struct {
    DState   current;
    int      transition_count;
    uint32_t ticks_in_state;
    uint32_t now;
} PowerDev;
void   pwr_init(PowerDev *d);
int    pwr_transition(PowerDev *d, DState target); /* 0=ok, -1=invalid */
void   pwr_tick(PowerDev *d);
bool   pwr_is_active(const PowerDev *d);   /* D0 = active */
bool   pwr_transition_allowed(DState from, DState to);
#endif