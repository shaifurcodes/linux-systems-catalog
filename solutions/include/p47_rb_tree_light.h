#ifndef P47_RB_TREE_LIGHT_H
#define P47_RB_TREE_LIGHT_H
#include <stdint.h>
/*
 * P47 - Lightweight red-black tree (subset)
 * Kernel uses rbtree for process scheduling (CFS), mm, timers.
 * Implement: insert, lookup, in-order traversal only.
 * Color balancing required for insert (left-rotate, right-rotate, recolor).
 */
typedef enum { RB_RED, RB_BLACK } RbColor;
typedef struct RbNode {
    uint64_t    key;
    void       *val;
    RbColor     color;
    struct RbNode *left, *right, *parent;
} RbNode;
typedef struct { RbNode *root; int count; } RbTree;
void     rbt_init(RbTree *t);
int      rbt_insert(RbTree *t, RbNode *node, uint64_t key, void *val);
RbNode  *rbt_lookup(const RbTree *t, uint64_t key);
void     rbt_inorder(const RbTree *t, void (*visit)(RbNode *));
int      rbt_count(const RbTree *t);
#endif