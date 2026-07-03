#include "p25_log_circ.h"
#include <string.h>
#include <stdint.h>
/* TODO: pack [len:u16][level:u8][text...] sequentially. On overflow,
 * advance tail past the oldest record to make room. */
void log_init(LogBuf *lb) {}
int  log_write(LogBuf *lb, uint8_t level, const char *msg) { return -1; }
int  log_read_next(LogBuf *lb, uint8_t *level, char *out, size_t out_sz) { return -1; }
int  log_count(const LogBuf *lb) { return 0; }