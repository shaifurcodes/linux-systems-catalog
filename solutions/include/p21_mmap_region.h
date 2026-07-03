#ifndef P21_MMAP_REGION_H
#define P21_MMAP_REGION_H
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
/*
 * P21 - mmap region tracker
 * Track mapped memory regions [start, start+len).
 * Support overlap detection, merge of adjacent regions, and unmapping.
 * Max 32 regions.
 */
#define MMAP_MAX 32
typedef struct { uintptr_t start; size_t len; int prot; } MmapRegion;
typedef struct { MmapRegion regions[MMAP_MAX]; int count; } MmapTracker;
void  mm_init(MmapTracker *t);
int   mm_map(MmapTracker *t, uintptr_t start, size_t len, int prot);   /* -1 if overlap */
int   mm_unmap(MmapTracker *t, uintptr_t start, size_t len);
bool  mm_is_mapped(const MmapTracker *t, uintptr_t addr);
int   mm_region_count(const MmapTracker *t);
#endif