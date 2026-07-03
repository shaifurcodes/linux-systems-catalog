#ifndef P29_SYSCTL_NODE_H
#define P29_SYSCTL_NODE_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P29 - sysctl node table (proc_dointvec style)
 * Register integer sysctl variables with min/max validation.
 * Read/write via path strings like "kernel/pid_max".
 */
#define SYSCTL_MAX 32
typedef struct {
    char    path[64];
    int    *var;
    int     min_val;
    int     max_val;
} SysctlNode;
typedef struct { SysctlNode nodes[SYSCTL_MAX]; int count; } SysctlTable;
void sysctl_init(SysctlTable *t);
int  sysctl_register(SysctlTable *t, const char *path, int *var, int min, int max);
int  sysctl_read(const SysctlTable *t, const char *path, int *out);
int  sysctl_write(SysctlTable *t, const char *path, int val); /* -1 if OOB */
#endif