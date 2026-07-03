#include "p19_power_state.h"
/* TODO: allowed transitions: any Dx -> D0 (resume), D0->D1->D2->D3 (suspend).
 * D3->D2 direct is NOT allowed (must go through D0). */
void   pwr_init(PowerDev *d) {}
int    pwr_transition(PowerDev *d, DState target) { return -1; }
void   pwr_tick(PowerDev *d) {}
bool   pwr_is_active(const PowerDev *d) { return false; }
bool   pwr_transition_allowed(DState from, DState to) { return false; }