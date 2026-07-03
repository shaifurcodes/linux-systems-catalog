#include "p43_fsm_uart.h"
#include <string.h>
/* TODO: feed byte into current state, transition accordingly.
 * CRC8 polynomial 0x07 (same as SMBus). On DONE validate CRC. */
void    uart_fsm_init(UartFsm *f) {}
int     uart_fsm_feed(UartFsm *f, uint8_t byte) { return -1; }
void    uart_fsm_reset(UartFsm *f) {}
uint8_t uart_crc8(const uint8_t *data, uint8_t len) { return 0; }