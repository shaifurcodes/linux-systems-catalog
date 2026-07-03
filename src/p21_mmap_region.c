#include "p21_mmap_region.h"
#include <string.h>
/* TODO: mm_map checks all existing regions for overlap before inserting.
 * Overlap: !(new_end <= exist_start || new_start >= exist_end) */
void  mm_init(MmapTracker *t) {}
int   mm_map(MmapTracker *t, uintptr_t start, size_t len, int prot) { return -1; }
int   mm_unmap(MmapTracker *t, uintptr_t start, size_t len) { return -1; }
bool  mm_is_mapped(const MmapTracker *t, uintptr_t addr) { return false; }
int   mm_region_count(const MmapTracker *t) { return 0; }