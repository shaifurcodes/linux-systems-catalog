#ifndef P23_FIRMWARE_CRC_H
#define P23_FIRMWARE_CRC_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
/*
 * P23 - Firmware image CRC32 verifier
 * Firmware images end with a 4-byte CRC32 (little-endian).
 * Verify integrity and compute CRC for new images.
 * Use CRC32 polynomial 0xEDB88320 (IEEE 802.3, same as Linux kernel).
 */
uint32_t fw_crc32(const uint8_t *data, size_t len);
bool     fw_verify(const uint8_t *image, size_t image_len);  /* last 4 bytes = CRC of preceding */
void     fw_append_crc(uint8_t *image, size_t data_len);     /* write CRC into [data_len..data_len+3] */
#endif