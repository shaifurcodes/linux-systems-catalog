#include "p47_rb_tree_light.h"
#include <string.h>
/* TODO: standard RB insert with rotations. No delete required.
 * After BST insert, fix violations: uncle red -> recolor; uncle black -> rotate. */
void    rbt_init(RbTree *t) {}
int     rbt_insert(RbTree *t, RbNode *node, uint64_t key, void *val) { return -1; }
RbNode *rbt_lookup(const RbTree *t, uint64_t key) { return NULL; }
void    rbt_inorder(const RbTree *t, void (*visit)(RbNode *)) {}
int     rbt_count(const RbTree *t) { return 0; }