#ifndef P30_OOM_SCORE_H
#define P30_OOM_SCORE_H
#include <stdint.h>
/*
 * P30 - OOM killer score calculator
 * Linux OOM killer selects the process with the highest oom_score.
 * score = (rss_pages * 1000 / total_pages) + oom_score_adj
 * oom_score_adj range: -1000..1000
 * Select the victim from a table of processes.
 */
#define OOM_MAX_PROCS 64
typedef struct { int pid; uint64_t rss_pages; int oom_adj; char name[32]; } ProcInfo;
typedef struct { ProcInfo procs[OOM_MAX_PROCS]; int count; uint64_t total_pages; } OomTable;
void oom_init(OomTable *t, uint64_t total_pages);
int  oom_add_proc(OomTable *t, int pid, uint64_t rss, int adj, const char *name);
int  oom_score(const OomTable *t, int idx);
int  oom_select_victim(const OomTable *t);   /* returns pid of highest scorer */
#endif