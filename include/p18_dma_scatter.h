#ifndef P18_DMA_SCATTER_H
#define P18_DMA_SCATTER_H
#include <stddef.h>
#include <stdint.h>
/*
 * P18 - DMA scatter-gather list builder
 * DMA transfers use scatter-gather lists: arrays of (phys_addr, length) pairs.
 * Build an sg list from a virtual buffer, respecting a max_seg_size constraint.
 * (Simulated: phys_addr = (uintptr_t)virt_addr for testing.)
 */
#define SG_MAX_ENTRIES 64
typedef struct { uintptr_t addr; size_t len; } SgEntry;
typedef struct { SgEntry entries[SG_MAX_ENTRIES]; int count; } SgList;
int sg_build(SgList *sg, const void *buf, size_t total_len, size_t max_seg);
size_t sg_total_len(const SgList *sg);
int    sg_nents(const SgList *sg);
#endif