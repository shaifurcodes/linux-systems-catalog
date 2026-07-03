#include "p16_netlink_ring.h"
#include <stdlib.h>
#include <string.h>
/* TODO: prefix each message with uint32_t len. On push, check (4+len) <= avail.
 * On pop, read the length header first, then copy the payload. */
int  nlr_init(NlRing *r, uint32_t cap) { return -1; }
void nlr_destroy(NlRing *r) {}
int  nlr_push(NlRing *r, const void *msg, uint32_t len) { return -1; }
int  nlr_pop(NlRing *r, void *out, uint32_t *len) { return -1; }
bool nlr_empty(const NlRing *r) { return true; }