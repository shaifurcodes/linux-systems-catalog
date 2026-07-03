#ifndef P15_CGROUP_COUNTER_H
#define P15_CGROUP_COUNTER_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P15 - cgroup resource counter (memory.usage_in_bytes style)
 * Hierarchical counter: child charges propagate up to parent.
 * Supports limit enforcement and overflow detection.
 */
#define CGROUP_MAX 16
typedef struct CGroup {
    char        name[32];
    uint64_t    usage;
    uint64_t    limit;    /* UINT64_MAX = unlimited */
    int         parent;   /* index, -1 = root */
} CGroup;
typedef struct { CGroup groups[CGROUP_MAX]; int count; } CGroupTree;
void     cgt_init(CGroupTree *t);
int      cgt_add(CGroupTree *t, const char *name, uint64_t limit, int parent_idx);
int      cgt_charge(CGroupTree *t, int idx, uint64_t bytes); /* 0=ok, -1=limit exceeded */
void     cgt_uncharge(CGroupTree *t, int idx, uint64_t bytes);
uint64_t cgt_usage(const CGroupTree *t, int idx);
#endif