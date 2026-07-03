#include "p39_lockfree_stack.h"
/* TODO: push: new->next = head; CAS(&head, expected, new) loop until success.
 * pop: old=head; CAS(&head, old, old->next) loop. Return old or NULL. */
void    lfs_init(LFStack *s) {}
void    lfs_push(LFStack *s, LFNode *node) {}
LFNode *lfs_pop(LFStack *s) { return NULL; }
bool    lfs_empty(const LFStack *s) { return true; }