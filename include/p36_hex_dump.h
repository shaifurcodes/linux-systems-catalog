#ifndef P36_HEX_DUMP_H
#define P36_HEX_DUMP_H
#include <stdint.h>
#include <stddef.h>
/*
 * P36 - Hex dump formatter (like kernel print_hex_dump)
 * Output: "0000: 01 02 03 04  05 06 07 08  |........|\n"
 * 16 bytes per line, offset prefix, ASCII column.
 * Used for debugging memory, registers, and network packets.
 */
int  hex_dump(const uint8_t *buf, size_t len, char *out, size_t out_cap);
/* parse a hex string "deadbeef" -> bytes */
int  hex_parse(const char *hexstr, uint8_t *out, size_t out_cap);
/* convert single byte to two hex chars */
void byte_to_hex(uint8_t b, char *hi, char *lo);
#endif