#ifndef P39_LOCKFREE_STACK_H
#define P39_LOCKFREE_STACK_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P40 - Lock-free stack using GCC atomics (used in kernel-bypass paths)
 * Implement using __atomic_compare_exchange_n.
 * Nodes are caller-allocated (intrusive). Max 64 nodes.
 */
typedef struct LFNode { struct LFNode *next; int val; } LFNode;
typedef struct { LFNode * _Atomic head; } LFStack;
void  lfs_init(LFStack *s);
void  lfs_push(LFStack *s, LFNode *node);
LFNode *lfs_pop(LFStack *s);
bool  lfs_empty(const LFStack *s);
#endif