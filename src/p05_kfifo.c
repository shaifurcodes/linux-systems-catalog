#include "p05_kfifo.h"
#include <stdlib.h>
/* TODO: wrap P01 ring buffer to handle byte slices.
 * kf_write copies min(len, avail_write) bytes; returns count actually written. */
int    kf_init(KFifo *kf, uint32_t cap) { return -1; }
void   kf_destroy(KFifo *kf) {}
size_t kf_write(KFifo *kf, const uint8_t *data, size_t len) { return 0; }
size_t kf_read(KFifo *kf, uint8_t *out, size_t len) { return 0; }
size_t kf_avail_write(const KFifo *kf) { return 0; }
size_t kf_avail_read(const KFifo *kf) { return 0; }
