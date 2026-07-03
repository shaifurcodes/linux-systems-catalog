#include "p14_uevent_filter.h"
#include <string.h>
#include <stddef.h>
/* TODO: walk null-separated KV pairs; for uf_matches, ALL rules must match. */
void uf_init(UeventFilter *f) {}
int  uf_add_rule(UeventFilter *f, const char *key, const char *val) { return -1; }
bool uf_matches(const UeventFilter *f, const char *uevent_buf, size_t len) { return false; }
const char *uf_get_value(const char *uevent_buf, size_t len, const char *key) { return NULL; }