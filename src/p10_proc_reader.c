#include "p10_proc_reader.h"
#include <string.h>
#include <stdlib.h>
/* TODO: strstr for key, then scan past ':' and whitespace, strtol for value.
 * proc_get_field_bytes: multiply kB value by 1024. */
long proc_get_field_kb(const char *buf, const char *key) { return -1; }
long proc_get_field_bytes(const char *buf, const char *key) { return -1; }
int  proc_count_fields(const char *buf) { return 0; }