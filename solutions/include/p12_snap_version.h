#ifndef P12_SNAP_VERSION_H
#define P12_SNAP_VERSION_H
#include <stdbool.h>
/*
 * P12 - Snap version string comparison
 * Snap uses epoch:upstream~debian style versioning (subset of deb).
 * Implement comparison returning <0, 0, >0 (like strcmp).
 * Rules: compare epoch first (int), then upstream char-by-char
 *        digits compared numerically, non-digits compared by ASCII.
 */
int  snap_version_cmp(const char *a, const char *b);
bool snap_version_satisfies(const char *ver, const char *constraint);
     /* constraint: ">=1.2.3" ">1.0" "=2.0" "<=3.1" */
#endif