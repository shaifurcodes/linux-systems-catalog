#include "p13_deb_parser.h"
#include <string.h>
#include <stdlib.h>
/* TODO: line-by-line. If line starts with ' ' or '\t' it continues prev field.
 * Otherwise split on first ':'. Strip leading/trailing whitespace from value. */
int         deb_parse(const char *buf, DebControl *out) { return -1; }
const char *deb_get(const DebControl *c, const char *key) { return NULL; }