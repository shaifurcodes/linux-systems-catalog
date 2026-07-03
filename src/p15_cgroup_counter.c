#include "p15_cgroup_counter.h"
#include <string.h>
#include <stdint.h>
/* TODO: charge walks from idx up to root, adding bytes to each ancestor.
 * If any ancestor would exceed its limit, abort and unroll. */
void     cgt_init(CGroupTree *t) {}
int      cgt_add(CGroupTree *t, const char *name, uint64_t limit, int parent_idx) { return -1; }
int      cgt_charge(CGroupTree *t, int idx, uint64_t bytes) { return -1; }
void     cgt_uncharge(CGroupTree *t, int idx, uint64_t bytes) {}
uint64_t cgt_usage(const CGroupTree *t, int idx) { return 0; }