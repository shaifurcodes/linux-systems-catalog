#include "p36_hex_dump.h"
#include <string.h>
#include <stdio.h>
/* TODO: snprintf per line. ASCII column: printable chars as-is, else '.'.
 * hex_parse: each pair of hex chars -> one byte. */
int  hex_dump(const uint8_t *buf, size_t len, char *out, size_t out_cap) { return -1; }
int  hex_parse(const char *hexstr, uint8_t *out, size_t out_cap) { return -1; }
void byte_to_hex(uint8_t b, char *hi, char *lo) {}