#include "p09_sysfs_parser.h"
#include <string.h>
#include <stdlib.h>
/* TODO: split on '=', strip trailing newline, detect type by trying strtol first,
 * then bool keywords, else treat as string. */
int sysfs_parse(const char *buf, SysfsAttr *out) { return -1; }
int sysfs_parse_int(const char *buf, long *out) { return -1; }
int sysfs_parse_bool(const char *buf, bool *out) { return -1; }