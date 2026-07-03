#include "p30_oom_score.h"
#include <string.h>
/* TODO: oom_score(idx) = (rss_pages*1000/total_pages) + oom_adj, clamp 0..2000.
 * oom_select_victim: iterate all, return pid of max score. */
void oom_init(OomTable *t, uint64_t total_pages) {}
int  oom_add_proc(OomTable *t, int pid, uint64_t rss, int adj, const char *name) { return -1; }
int  oom_score(const OomTable *t, int idx) { return 0; }
int  oom_select_victim(const OomTable *t) { return -1; }