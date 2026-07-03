#ifndef P10_PROC_READER_H
#define P10_PROC_READER_H
#include <stdint.h>
/*
 * P10 - /proc/meminfo style parser
 * Parse lines of the form "FieldName: <value> kB"
 * from a buffer (not from the actual filesystem — buffer passed in).
 * Return the value for a given key, or -1 if not found.
 */
long proc_get_field_kb(const char *buf, const char *key);
/* Parse "VmRSS: 1234 kB" style; return bytes */
long proc_get_field_bytes(const char *buf, const char *key);
/* Count how many fields are present */
int  proc_count_fields(const char *buf);
#endif