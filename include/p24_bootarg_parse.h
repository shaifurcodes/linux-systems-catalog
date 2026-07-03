#ifndef P24_BOOTARG_PARSE_H
#define P24_BOOTARG_PARSE_H
#include <stdbool.h>
/*
 * P24 - Linux kernel boot argument parser
 * Parse cmdline strings like "console=ttyS0,115200 root=/dev/sda1 ro quiet"
 * Extract: presence of flags, values of key=value params.
 */
bool        bootarg_has_flag(const char *cmdline, const char *flag);
const char *bootarg_get_value(const char *cmdline, const char *key, char *out, int out_sz);
int         bootarg_count(const char *cmdline);
/* Parse "console=ttyS0,115200" -> device="ttyS0", baud=115200 */
int         bootarg_parse_console(const char *cmdline, char *dev, int dev_sz, int *baud);
#endif