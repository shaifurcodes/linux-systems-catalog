#include "p12_snap_version.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* TODO: strip epoch (N:) from both sides. Then compare segment by segment:
 * if both chars are digits, extract full integer and compare numerically.
 * else compare single char by ASCII value. */
int  snap_version_cmp(const char *a, const char *b) { return 0; }
bool snap_version_satisfies(const char *ver, const char *constraint) { return false; }