#ifndef P14_UEVENT_FILTER_H
#define P14_UEVENT_FILTER_H
#include <stdbool.h>
/*
 * P14 - udev uevent filter
 * uevents arrive as "KEY=VALUE\0KEY=VALUE\0..." null-separated strings.
 * Implement a simple rule matcher: match if ALL specified key=value pairs match.
 * Used in udev rules and snapd device assignment.
 */
#define UE_MAX_RULES 16
typedef struct { char key[32]; char val[64]; } UeventRule;
typedef struct { UeventRule rules[UE_MAX_RULES]; int count; } UeventFilter;
void uf_init(UeventFilter *f);
int  uf_add_rule(UeventFilter *f, const char *key, const char *val);
bool uf_matches(const UeventFilter *f, const char *uevent_buf, size_t len);
const char *uf_get_value(const char *uevent_buf, size_t len, const char *key);
#endif