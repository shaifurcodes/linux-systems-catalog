#include "p18_dma_scatter.h"
#include <stdint.h>
/* TODO: split [buf, buf+total_len) into segments of at most max_seg bytes.
 * Each entry: addr=current pointer, len=min(max_seg, remaining). */
int    sg_build(SgList *sg, const void *buf, size_t total_len, size_t max_seg) { return -1; }
size_t sg_total_len(const SgList *sg) { return 0; }
int    sg_nents(const SgList *sg) { return 0; }