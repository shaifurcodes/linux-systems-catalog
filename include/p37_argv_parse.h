#ifndef P37_ARGV_PARSE_H
#define P37_ARGV_PARSE_H
#include <stdbool.h>
/*
 * P37 - argv/getopt-style argument parser
 * Parse a command-line string into argc/argv (like wordexp without shell).
 * Support quoted strings and escaped spaces.
 * Also implement a simple flag parser: -f, --flag, --key=value.
 */
#define ARGV_MAX 32
#define ARGV_BUF 256
typedef struct { char *argv[ARGV_MAX]; char buf[ARGV_BUF]; int argc; } ArgList;
int  argv_parse(const char *cmdline, ArgList *out);
bool argv_has_flag(const ArgList *al, const char *flag);  /* "-v" or "--verbose" */
const char *argv_get_value(const ArgList *al, const char *key); /* "--output=file" -> "file" */
#endif