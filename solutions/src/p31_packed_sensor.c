#include "p31_packed_sensor.h"
/* TODO: bit layout MSB->LSB: [31:20]=temp(12) [19:10]=humid(10) [9:6]=status(4) [5:0]=alert(6)
 * encode: shift each field into position and OR together.
 * decode: mask and shift right. */
uint32_t sensor_encode(uint16_t temp_raw, uint16_t humid_raw, uint8_t status, uint8_t alert) { return 0; }
void     sensor_decode(uint32_t frame, uint16_t *temp, uint16_t *humid, uint8_t *status, uint8_t *alert) {}
bool     sensor_frame_valid(uint32_t frame) { return false; }