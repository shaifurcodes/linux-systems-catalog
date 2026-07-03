#ifndef P43_FSM_UART_H
#define P43_FSM_UART_H
#include <stdint.h>
#include <stdbool.h>
/*
 * P43 - UART framing FSM
 * Protocol: [START:0xAA][LEN:u8][PAYLOAD:LEN bytes][CRC8:u8]
 * FSM processes one byte at a time (interrupt-driven style).
 * States: IDLE -> SYNC -> LENGTH -> PAYLOAD -> CHECKSUM -> DONE/ERROR
 */
typedef enum { UART_IDLE, UART_SYNC, UART_LEN, UART_PAYLOAD, UART_CRC, UART_DONE, UART_ERROR } UartState;
typedef struct {
    UartState state;
    uint8_t   buf[256];
    uint8_t   expected_len;
    uint8_t   received;
    uint8_t   crc_accum;
} UartFsm;
void uart_fsm_init(UartFsm *f);
int  uart_fsm_feed(UartFsm *f, uint8_t byte);  /* returns 1=frame ready, 0=in progress, -1=error */
void uart_fsm_reset(UartFsm *f);
uint8_t uart_crc8(const uint8_t *data, uint8_t len);
#endif