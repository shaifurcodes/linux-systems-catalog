#ifndef P49_CPU_AFFINITY_MAP_H
#define P49_CPU_AFFINITY_MAP_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P49 - CPU affinity map (cpumask_t-lite)
 * Track which CPUs are allowed for a task (like taskset / sched_setaffinity).
 * Operations on bitmasks up to 64 CPUs.
 */
typedef struct { uint64_t bits; } CpuMask;
void     cm_zero(CpuMask *m);
void     cm_fill(CpuMask *m, int ncpus);
void     cm_set(CpuMask *m, int cpu);
void     cm_clear(CpuMask *m, int cpu);
bool     cm_test(const CpuMask *m, int cpu);
int      cm_weight(const CpuMask *m);          /* number of CPUs set */
int      cm_first(const CpuMask *m);           /* lowest set CPU, -1 if empty */
int      cm_next(const CpuMask *m, int prev);  /* next set CPU after prev */
void     cm_and(CpuMask *dst, const CpuMask *a, const CpuMask *b);
void     cm_or(CpuMask *dst,  const CpuMask *a, const CpuMask *b);
#endif