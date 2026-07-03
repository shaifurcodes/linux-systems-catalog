#ifndef P20_WATCHDOG_H
#define P20_WATCHDOG_H
#include <stdbool.h>
#include <stdint.h>
/*
 * P20 - Software watchdog timer
 * A watchdog must be "kicked" (reset) before its timeout expires.
 * If not kicked in time, it fires a callback (simulating a system reset).
 * Supports enable/disable and timeout reconfiguration.
 */
typedef void (*wdt_expire_fn)(void *arg);
typedef struct {
    uint32_t      timeout_ticks;
    uint32_t      remaining;
    bool          enabled;
    wdt_expire_fn on_expire;
    void         *arg;
    int           expire_count;
} Watchdog;
void wdt_init(Watchdog *w, uint32_t timeout, wdt_expire_fn fn, void *arg);
void wdt_enable(Watchdog *w);
void wdt_disable(Watchdog *w);
void wdt_kick(Watchdog *w);          /* reset countdown */
void wdt_tick(Watchdog *w);          /* advance one tick */
bool wdt_is_healthy(const Watchdog *w);
#endif