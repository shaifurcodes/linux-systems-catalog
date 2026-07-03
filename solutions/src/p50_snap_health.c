#include "p50_snap_health.h"
#include <string.h>
/* TODO: sh_report appends to circular history, increments consecutive_errors on ERROR,
 * resets it on OK. sh_is_critical: consecutive_errors >= 3. */
void   sh_init(SnapHealth *h) {}
void   sh_report(SnapHealth *h, HealthStatus s, const char *msg) {}
void   sh_tick(SnapHealth *h) {}
bool   sh_is_critical(const SnapHealth *h) { return false; }
HealthRecord *sh_latest(SnapHealth *h) { return NULL; }
int    sh_error_streak(const SnapHealth *h) { return 0; }