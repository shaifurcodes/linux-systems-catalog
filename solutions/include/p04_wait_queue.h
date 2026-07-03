#ifndef P04_WAIT_QUEUE_H
#define P04_WAIT_QUEUE_H
#include <stdbool.h>
/*
 * P04 - Wait-queue (simulated, no real threads)
 * Models Linux wait_queue_head_t: tasks block until a condition is met.
 * Simplified: tasks are represented by integer IDs.
 * wake_one() removes and returns the head task; wake_all() drains the queue.
 */
#define WQ_MAX 32
typedef struct { int tasks[WQ_MAX]; int head, tail, count; } WaitQueue;
void wq_init(WaitQueue *wq);
int  wq_add(WaitQueue *wq, int task_id);   /* -1 if full */
int  wq_wake_one(WaitQueue *wq);           /* returns task_id or -1 */
int  wq_wake_all(WaitQueue *wq, int *out, int out_sz); /* returns count woken */
int  wq_count(const WaitQueue *wq);
#endif
