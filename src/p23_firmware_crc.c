#include "p23_firmware_crc.h"
/* TODO: build lookup table from polynomial 0xEDB88320.
 * table[i] = reflect and XOR 8 times. Standard CRC32 implementation. */
uint32_t fw_crc32(const uint8_t *data, size_t len) { return 0; }
bool     fw_verify(const uint8_t *image, size_t image_len) { return false; }
void     fw_append_crc(uint8_t *image, size_t data_len) {}