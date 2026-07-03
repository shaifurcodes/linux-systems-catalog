#include "p17_ioctl_dispatch.h"
#include <string.h>
/* TODO: linear search table by cmd. dispatch returns fn(cmd,arg) or -ENOTTY. */
void ioctl_table_init(IoctlTable *t) {}
int  ioctl_register(IoctlTable *t, uint32_t cmd, ioctl_fn fn) { return -1; }
long ioctl_dispatch(const IoctlTable *t, uint32_t cmd, unsigned long arg) { return -ENOTTY; }
int  ioctl_unregister(IoctlTable *t, uint32_t cmd) { return -1; }