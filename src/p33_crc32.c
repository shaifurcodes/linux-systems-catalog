#include "p33_crc32.h"
/* TODO: same polynomial as P23 (0xEDB88320). Build table once.
 * crc32_buf = crc32_final(crc32_update(crc32_init(), buf, len)) */
uint32_t crc32_init(void) { return 0xFFFFFFFF; }
uint32_t crc32_update(uint32_t crc, const uint8_t *buf, size_t len) { return crc; }
uint32_t crc32_final(uint32_t crc) { return crc ^ 0xFFFFFFFF; }
uint32_t crc32_buf(const uint8_t *buf, size_t len) { return 0; }
int      crc32_verify(const uint8_t *buf, size_t len, uint32_t expected) { return -1; }