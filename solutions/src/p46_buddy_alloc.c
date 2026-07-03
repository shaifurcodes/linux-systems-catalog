#include "p46_buddy_alloc.h"
#include <string.h>
/* TODO: npages must be power of two. Find aligned run of npages free pages.
 * buddy_free: set bits and try merging with adjacent buddy block. */
void  buddy_init(BuddyAlloc *b) {}
int   buddy_alloc(BuddyAlloc *b, int npages) { return -1; }
void  buddy_free(BuddyAlloc *b, int page_idx, int npages) {}
bool  buddy_page_free(const BuddyAlloc *b, int page_idx) { return false; }
int   buddy_free_pages(const BuddyAlloc *b) { return 0; }