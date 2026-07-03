#ifndef P50_SNAP_HEALTH_H
#define P50_SNAP_HEALTH_H
#include <stdbool.h>
#include <stdint.h>
/*
 * P50 - Snap health check state tracker (snapd snap.health API)
 * Snaps report health: ok/waiting/blocked/error with optional message.
 * Track history (last 8 states), detect repeated errors, emit alerts.
 */
typedef enum { HEALTH_OK, HEALTH_WAITING, HEALTH_BLOCKED, HEALTH_ERROR } HealthStatus;
typedef struct {
    HealthStatus status;
    char         message[128];
    uint32_t     tick;
} HealthRecord;
#define HEALTH_HIST 8
typedef struct {
    HealthRecord history[HEALTH_HIST];
    int          hist_count;
    int          head;
    uint32_t     now;
    int          consecutive_errors;
} SnapHealth;
void   sh_init(SnapHealth *h);
void   sh_report(SnapHealth *h, HealthStatus s, const char *msg);
void   sh_tick(SnapHealth *h);
bool   sh_is_critical(const SnapHealth *h);  /* 3+ consecutive errors */
HealthRecord *sh_latest(SnapHealth *h);
int    sh_error_streak(const SnapHealth *h);
#endif