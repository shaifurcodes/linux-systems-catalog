#include "p27_mount_parser.h"
#include <string.h>
#include <stdlib.h>
/* TODO: sscanf(line, "%s %s %s %s %*d %*d", ...) or manual split on spaces. */
int         mt_parse(const char *buf, MountTable *out) { return -1; }
MountEntry *mt_find_by_mountpoint(MountTable *t, const char *mp) { return NULL; }
MountEntry *mt_find_by_device(MountTable *t, const char *dev) { return NULL; }
int         mt_count_fstype(const MountTable *t, const char *fstype) { return 0; }