/**
 * @file p04_wait_queue.c
 * @brief Implementation of the simulated wait queue circular buffer logic.
 */

#include "p04_wait_queue.h"
#include <stddef.h> 

/**
 * @brief Initializes a WaitQueue structure to an empty state.
 * @param wq Pointer to the WaitQueue structure to initialize.
 */
void wq_init(WaitQueue *wq) {
    if (wq == NULL) {
        return;
    }
    wq->head = 0;
    wq->tail = 0;
    wq->count = 0;
}

/**
 * @brief Enqueues a task ID at the tail of the wait queue.
 * @param wq Pointer to the WaitQueue structure.
 * @param task_id The unique integer identifier of the task.
 * @return int 0 on success, or -1 if the queue is full (capacity reached).
 */
int wq_add(WaitQueue *wq, int task_id) {
    if (wq == NULL || wq->count >= WQ_MAX) {
        return -1; 
    }

    // Insert task at current write index
    wq->tasks[wq->tail] = task_id;
    
    // Increment index and wrap around using modulo math if WQ_MAX is reached
    wq->tail = (wq->tail + 1) % WQ_MAX;
    wq->count++;

    return 0;
}

/**
 * @brief Removes and returns the head task from the wait queue.
 * @param wq Pointer to the WaitQueue structure.
 * @return int The unblocked task_id on success, or -1 if the queue is empty.
 */
int wq_wake_one(WaitQueue *wq) {
    if (wq == NULL || wq->count == 0) {
        return -1;
    }

    // Capture task at current read index
    int task_id = wq->tasks[wq->head];
    
    // Increment index and wrap around using modulo math if WQ_MAX is reached
    wq->head = (wq->head + 1) % WQ_MAX;
    wq->count--;

    return task_id;
}

/**
 * @brief Drains all tasks from the queue into an external array.
 * @param wq Pointer to the WaitQueue structure.
 * @param out Pointer to an external array where woken task IDs will be stored.
 * @param out_sz Maximum capacity of the destination 'out' array.
 * @return int The actual number of tasks successfully woken and copied.
 */
int wq_wake_all(WaitQueue *wq, int *out, int out_sz) {
    if (wq == NULL || out == NULL || out_sz <= 0) {
        return 0;
    }

    int woken = 0;
    
    // Iteratively drain the queue until it is empty or output buffer fills up
    while (wq->count > 0 && woken < out_sz) {
        out[woken] = wq_wake_one(wq);
        woken++;
    }

    return woken;
}

/**
 * @brief Retrieves the current number of tasks residing in the queue.
 * @param wq Constant pointer to the WaitQueue structure (read-only).
 * @return int The total count of waiting tasks.
 */
int wq_count(const WaitQueue *wq) {
    if (wq == NULL) {
        return 0;
    }
    return wq->count;
}
