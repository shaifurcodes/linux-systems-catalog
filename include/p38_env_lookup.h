#ifndef P38_ENV_LOOKUP_H
#define P38_ENV_LOOKUP_H
#include <stdbool.h>
/*
 * P38 - Environment variable store (snapd/systemd unit env parsing)
 * Parse "KEY=VALUE\n" format environment files.
 * Support variable expansion: VALUE can reference $OTHER_KEY.
 * Max depth 4 expansion.
 */
#define ENV_MAX 64
typedef struct { char key[64]; char val[256]; } EnvVar;
typedef struct { EnvVar vars[ENV_MAX]; int count; } EnvStore;
void        env_init(EnvStore *e);
int         env_set(EnvStore *e, const char *key, const char *val);
const char *env_get(const EnvStore *e, const char *key);
int         env_parse_file(const char *buf, EnvStore *e);
int         env_expand(const EnvStore *e, const char *in, char *out, int out_sz);
#endif