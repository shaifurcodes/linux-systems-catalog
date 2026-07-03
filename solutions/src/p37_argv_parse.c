#include "p37_argv_parse.h"
#include <string.h>
/* TODO: tokenise cmdline into buf, set argv[] pointers into buf.
 * Handle: "quoted string", escaped\ space, bare tokens. */
int  argv_parse(const char *cmdline, ArgList *out) { return -1; }
bool argv_has_flag(const ArgList *al, const char *flag) { return false; }
const char *argv_get_value(const ArgList *al, const char *key) { return NULL; }