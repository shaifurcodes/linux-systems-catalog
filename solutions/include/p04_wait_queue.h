#ifndef P04_WAIT_QUEUE_H
#define P04_WAIT_QUEUE_H

#include <stdbool.h>

/**
 * @file p04_wait_queue.h
 * @brief Simulated wait-queue implementation for integer-based task tracking.
 *
 * This component models the basic behavior of a Linux kernel `wait_queue_head_t`.
 * It allows task IDs to block (queue) and unblock (dequeue) using a 
 * FIFO (First-In, First-Out) circular buffer. It does not handle actual 
 * multi-threaded concurrency primitives.
 */

/**
 * @brief Maximum capacity of the wait queue.
 */
#define WQ_MAX 32

/**
 * @struct WaitQueue
 * @brief Structure representing a fixed-size FIFO circular wait queue.
 */
typedef struct { 
    int tasks[WQ_MAX]; /**< Array holding the queued integer task IDs. */ 
    int head;          /**< Index of the next task to be popped (read pointer). */
    int tail;          /**< Index where the next task will be added (write pointer). */
    int count;         /**< Total number of tasks currently in the queue. */
} WaitQueue;

/**
 * @brief Initializes a WaitQueue structure to an empty state.
 *
 * Resets the head, tail, and element count to zero. Must be called
 * before using any other wait queue operations.
 *
 * @param wq Pointer to the WaitQueue structure to initialize.
 */
void wq_init(WaitQueue *wq);

/**
 * @brief Enqueues a task ID at the tail of the wait queue.
 *
 * @param wq Pointer to the WaitQueue structure.
 * @param task_id The unique integer identifier of the task.
 * @return int 0 on success, or -1 if the queue is full (capacity reached).
 */
int wq_add(WaitQueue *wq, int task_id);

/**
 * @brief Removes and returns the head task from the wait queue.
 *
 * Simulates waking up a single task using FIFO ordering.
 *
 * @param wq Pointer to the WaitQueue structure.
 * @return int The unblocked task_id on success, or -1 if the queue is empty.
 */
int wq_wake_one(WaitQueue *wq);

/**
 * @brief Drains all tasks from the queue into an external array.
 *
 * Simulates a "wake all" event, emptying the queue up to the bounds
 * of the provided output buffer size.
 *
 * @param wq Pointer to the WaitQueue structure.
 * @param out Pointer to an external array where woken task IDs will be stored.
 * @param out_sz Maximum capacity of the destination 'out' array.
 * @return int The actual number of tasks successfully woken and copied.
 */
int wq_wake_all(WaitQueue *wq, int *out, int out_sz);

/**
 * @brief Retrieves the current number of tasks residing in the queue.
 *
 * @param wq Constant pointer to the WaitQueue structure (read-only).
 * @return int The total count of waiting tasks.
 */
int wq_count(const WaitQueue *wq);

#endif //P04_WAIT_QUEUE_H
