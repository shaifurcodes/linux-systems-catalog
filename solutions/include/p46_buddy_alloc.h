#ifndef P46_BUDDY_ALLOC_H
#define P46_BUDDY_ALLOC_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
/*
 * P46 - Buddy allocator (simplified Linux page allocator)
 * Manages 64 pages of size PAGE_SIZE=4096.
 * Allocate in power-of-two page counts only.
 * On free, merge with buddy if both are free.
 */
#define PAGE_SIZE  4096
#define TOTAL_PAGES 64
typedef struct { uint64_t free_bitmap; } BuddyAlloc;
void  buddy_init(BuddyAlloc *b);
int   buddy_alloc(BuddyAlloc *b, int npages);   /* returns page index or -1 */
void  buddy_free(BuddyAlloc *b, int page_idx, int npages);
bool  buddy_page_free(const BuddyAlloc *b, int page_idx);
int   buddy_free_pages(const BuddyAlloc *b);
#endif