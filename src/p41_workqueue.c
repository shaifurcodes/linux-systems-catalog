#include "p41_workqueue.h"
#include <string.h>
/* TODO: wq_run_pending scans all non-cancelled items where run_at_tick<=tick,
 * calls fn(arg), marks as done (remove or invalidate). */
void wq_init(WorkQueue *wq) {}
int  wq_submit(WorkQueue *wq, work_fn fn, void *arg, uint32_t delay_ticks) { return -1; }
int  wq_cancel(WorkQueue *wq, int id) { return -1; }
int  wq_run_pending(WorkQueue *wq) { return 0; }
void wq_tick(WorkQueue *wq) {}