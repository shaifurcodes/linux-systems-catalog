#include "p29_sysctl_node.h"
#include <string.h>
/* TODO: sysctl_write validates min<=val<=max before writing to *var. */
void sysctl_init(SysctlTable *t) {}
int  sysctl_register(SysctlTable *t, const char *path, int *var, int min, int max) { return -1; }
int  sysctl_read(const SysctlTable *t, const char *path, int *out) { return -1; }
int  sysctl_write(SysctlTable *t, const char *path, int val) { return -1; }