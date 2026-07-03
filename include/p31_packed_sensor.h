#ifndef P31_PACKED_SENSOR_H
#define P31_PACKED_SENSOR_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P31 - Packed sensor data frame (IoT protocol encoding)
 * Sensor transmits 4-byte frames: [temp:12bit][humidity:10bit][status:4bit][alert:6bit]
 * All big-endian bit-packed from MSB.
 * Implement encode/decode without structs (raw uint32_t).
 */
uint32_t sensor_encode(uint16_t temp_raw, uint16_t humid_raw, uint8_t status, uint8_t alert);
void     sensor_decode(uint32_t frame, uint16_t *temp, uint16_t *humid, uint8_t *status, uint8_t *alert);
bool     sensor_frame_valid(uint32_t frame);  /* alert bit 0 = parity of other bits */
#endif