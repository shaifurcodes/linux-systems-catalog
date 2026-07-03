#ifndef P25_LOG_CIRC_H
#define P25_LOG_CIRC_H
#include <stdint.h>
#include <stddef.h>
/*
 * P25 - Kernel circular log buffer (dmesg-style)
 * Variable-length text messages stored in a ring.
 * Each record: [uint16_t len][uint8_t level][char text[len]].
 * Oldest records are overwritten when buffer is full.
 */
#define LOG_BUF_SIZE 4096
typedef struct {
    uint8_t  buf[LOG_BUF_SIZE];
    uint32_t head, tail;
    uint32_t count;
} LogBuf;
void log_init(LogBuf *lb);
int  log_write(LogBuf *lb, uint8_t level, const char *msg); /* overwrites old if full */
int  log_read_next(LogBuf *lb, uint8_t *level, char *out, size_t out_sz);
int  log_count(const LogBuf *lb);
#endif