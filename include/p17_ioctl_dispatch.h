#ifndef P17_IOCTL_DISPATCH_H
#define P17_IOCTL_DISPATCH_H
#include <stdint.h>
/*
 * P17 - ioctl command dispatch table
 * Map ioctl command numbers to handler functions (like a driver's unlocked_ioctl).
 * Supports up to 32 registered commands. Unknown cmd returns -ENOTTY (-25).
 */
#define IOCTL_MAX_CMDS 32
#define ENOTTY 25
typedef long (*ioctl_fn)(uint32_t cmd, unsigned long arg);
typedef struct { uint32_t cmd; ioctl_fn handler; } IoctlEntry;
typedef struct { IoctlEntry table[IOCTL_MAX_CMDS]; int count; } IoctlTable;
void ioctl_table_init(IoctlTable *t);
int  ioctl_register(IoctlTable *t, uint32_t cmd, ioctl_fn fn);
long ioctl_dispatch(const IoctlTable *t, uint32_t cmd, unsigned long arg);
int  ioctl_unregister(IoctlTable *t, uint32_t cmd);
#endif