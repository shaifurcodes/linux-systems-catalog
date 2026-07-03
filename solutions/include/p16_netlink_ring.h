#ifndef P16_NETLINK_RING_H
#define P16_NETLINK_RING_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
/*
 * P16 - Netlink message ring (variable-length messages)
 * Store variable-length netlink-style messages in a contiguous ring buffer.
 * Each message is prefixed with a 4-byte length header.
 * If a message does not fit, drop it and increment drop_count.
 */
typedef struct {
    uint8_t *buf;
    uint32_t cap, head, tail;
    uint32_t drop_count;
} NlRing;
int    nlr_init(NlRing *r, uint32_t cap);
void   nlr_destroy(NlRing *r);
int    nlr_push(NlRing *r, const void *msg, uint32_t len);
int    nlr_pop(NlRing *r, void *out, uint32_t *len);
bool   nlr_empty(const NlRing *r);
#endif