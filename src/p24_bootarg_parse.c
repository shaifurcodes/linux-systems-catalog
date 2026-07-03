#include "p24_bootarg_parse.h"
#include <string.h>
#include <stdlib.h>
/* TODO: tokenise on spaces. For key=value, compare key portion only.
 * bootarg_parse_console: find "console=", split value on ','. */
bool        bootarg_has_flag(const char *cmdline, const char *flag) { return false; }
const char *bootarg_get_value(const char *cmdline, const char *key, char *out, int out_sz) { return NULL; }
int         bootarg_count(const char *cmdline) { return 0; }
int         bootarg_parse_console(const char *cmdline, char *dev, int dev_sz, int *baud) { return -1; }