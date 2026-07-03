#include "p38_env_lookup.h"
#include <string.h>
#include <stdlib.h>
/* TODO: env_expand: scan for '$KEY', look up in store, substitute.
 * env_parse_file: split on '\n', then on first '='. */
void        env_init(EnvStore *e) {}
int         env_set(EnvStore *e, const char *key, const char *val) { return -1; }
const char *env_get(const EnvStore *e, const char *key) { return NULL; }
int         env_parse_file(const char *buf, EnvStore *e) { return -1; }
int         env_expand(const EnvStore *e, const char *in, char *out, int out_sz) { return -1; }