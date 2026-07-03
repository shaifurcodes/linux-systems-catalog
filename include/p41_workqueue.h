#ifndef P41_WORKQUEUE_H
#define P41_WORKQUEUE_H
#include <stdbool.h>
/*
 * P41 - Work queue (kernel workqueue-lite)
 * Deferred work items executed in submission order.
 * Supports delayed items (run after N ticks) and cancellation.
 */
#define WQ_MAX_ITEMS 32
typedef void (*work_fn)(void *arg);
typedef struct {
    work_fn  fn;
    void    *arg;
    uint32_t run_at_tick;
    bool     cancelled;
    int      id;
} WorkItem;
typedef struct { WorkItem items[WQ_MAX_ITEMS]; int count; uint32_t tick; int next_id; } WorkQueue;
void wq_init(WorkQueue *wq);
int  wq_submit(WorkQueue *wq, work_fn fn, void *arg, uint32_t delay_ticks);
int  wq_cancel(WorkQueue *wq, int id);
int  wq_run_pending(WorkQueue *wq);   /* run all items due at current tick; returns count run */
void wq_tick(WorkQueue *wq);
#endif