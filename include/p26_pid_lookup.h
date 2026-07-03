#ifndef P26_PID_LOOKUP_H
#define P26_PID_LOOKUP_H
#include <stdint.h>
/*
 * P26 - PID table (kernel pidmap-lite)
 * Allocate and free PIDs from a bitmap. Max 1024 PIDs.
 * PID 0 and 1 are always reserved.
 * alloc_pid() returns the lowest available PID.
 */
#define PID_MAX 1024
typedef struct { uint32_t bitmap[PID_MAX/32]; } PidMap;
void pid_map_init(PidMap *pm);
int  pid_alloc(PidMap *pm);          /* returns pid or -1 if exhausted */
void pid_free(PidMap *pm, int pid);
int  pid_in_use(const PidMap *pm, int pid);
int  pid_count_free(const PidMap *pm);
#endif