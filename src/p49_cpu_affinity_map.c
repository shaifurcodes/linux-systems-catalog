#include "p49_cpu_affinity_map.h"
/* TODO: cm_weight = __builtin_popcountll(bits).
 * cm_first = __builtin_ctzll(bits) if bits!=0 else -1.
 * cm_next: mask out bits 0..prev, then cm_first of result. */
void cm_zero(CpuMask *m) {}
void cm_fill(CpuMask *m, int ncpus) {}
void cm_set(CpuMask *m, int cpu) {}
void cm_clear(CpuMask *m, int cpu) {}
bool cm_test(const CpuMask *m, int cpu) { return false; }
int  cm_weight(const CpuMask *m) { return 0; }
int  cm_first(const CpuMask *m) { return -1; }
int  cm_next(const CpuMask *m, int prev) { return -1; }
void cm_and(CpuMask *dst, const CpuMask *a, const CpuMask *b) {}
void cm_or(CpuMask *dst,  const CpuMask *a, const CpuMask *b) {}