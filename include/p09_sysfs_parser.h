#ifndef P09_SYSFS_PARSER_H
#define P09_SYSFS_PARSER_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P09 - sysfs attribute parser
 * Parse key=value pairs as written to a sysfs node.
 * Format: "key=value\n" or "key=value" (newline optional).
 * Supports int, bool (0/1/true/false/on/off), and string values.
 */
typedef enum { SYSFS_INT, SYSFS_BOOL, SYSFS_STR } SysfsType;
typedef struct {
    char key[64];
    SysfsType type;
    union { long   ival; bool bval; char sval[64]; } v;
} SysfsAttr;
int sysfs_parse(const char *buf, SysfsAttr *out);   /* 0 ok, -1 error */
int sysfs_parse_int(const char *buf, long *out);
int sysfs_parse_bool(const char *buf, bool *out);   /* 0/1/true/false/on/off */
#endif