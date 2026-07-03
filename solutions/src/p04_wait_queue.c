#include "p04_wait_queue.h"
#include <string.h>
/* TODO: FIFO queue of int task IDs. wake_one pops head; wake_all drains. */
void wq_init(WaitQueue *wq) {}
int  wq_add(WaitQueue *wq, int task_id) { return -1; }
int  wq_wake_one(WaitQueue *wq) { return -1; }
int  wq_wake_all(WaitQueue *wq, int *out, int out_sz) { return 0; }
int  wq_count(const WaitQueue *wq) { return 0; }
