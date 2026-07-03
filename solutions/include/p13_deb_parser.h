#ifndef P13_DEB_PARSER_H
#define P13_DEB_PARSER_H
/*
 * P13 - Debian control file parser (subset)
 * Parse "Field: value\n" multi-line format as found in /var/lib/dpkg/status.
 * Support multi-line values (continuation lines start with a space).
 */
#define DEB_MAX_FIELDS 32
#define DEB_FIELD_LEN  64
#define DEB_VALUE_LEN  512
typedef struct { char key[DEB_FIELD_LEN]; char val[DEB_VALUE_LEN]; } DebField;
typedef struct { DebField fields[DEB_MAX_FIELDS]; int count; } DebControl;
int         deb_parse(const char *buf, DebControl *out);  /* 0=ok */
const char *deb_get(const DebControl *c, const char *key); /* NULL if missing */
#endif