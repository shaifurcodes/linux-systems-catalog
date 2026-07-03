#ifndef P40_SPINLOCK_SIM_H
#define P40_SPINLOCK_SIM_H
#include <stdbool.h>
#include <stdint.h>
/*
 * P40 - Spinlock and ticket lock simulation
 * Implement a test-and-set spinlock and a ticket lock using GCC __atomic.
 * Track contention statistics (times spun, total acquires).
 */
typedef struct { int _Atomic val; uint64_t acquires; uint64_t spins; } SpinLock;
typedef struct { uint32_t _Atomic next_ticket; uint32_t _Atomic now_serving; } TicketLock;
void spin_init(SpinLock *l);
void spin_lock(SpinLock *l);
bool spin_trylock(SpinLock *l);
void spin_unlock(SpinLock *l);
void ticket_init(TicketLock *l);
void ticket_lock(TicketLock *l);
void ticket_unlock(TicketLock *l);
#endif