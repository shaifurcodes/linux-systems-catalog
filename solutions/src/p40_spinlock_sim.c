#include "p40_spinlock_sim.h"
/* TODO: spin_lock: while(__atomic_test_and_set(&l->val, __ATOMIC_ACQUIRE)) l->spins++.
 * ticket_lock: my=atomic_fetch_add(next_ticket,1); while(now_serving!=my) spin. */
void spin_init(SpinLock *l) {}
void spin_lock(SpinLock *l) {}
bool spin_trylock(SpinLock *l) { return false; }
void spin_unlock(SpinLock *l) {}
void ticket_init(TicketLock *l) {}
void ticket_lock(TicketLock *l) {}
void ticket_unlock(TicketLock *l) {}