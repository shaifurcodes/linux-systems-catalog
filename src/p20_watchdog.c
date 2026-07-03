#include "p20_watchdog.h"
/* TODO: wdt_tick decrements remaining; if reaches 0 and enabled, call on_expire,
 * increment expire_count, reload remaining=timeout_ticks. */
void wdt_init(Watchdog *w, uint32_t timeout, wdt_expire_fn fn, void *arg) {}
void wdt_enable(Watchdog *w) {}
void wdt_disable(Watchdog *w) {}
void wdt_kick(Watchdog *w) {}
void wdt_tick(Watchdog *w) {}
bool wdt_is_healthy(const Watchdog *w) { return false; }