#include "p35_run_length.h"
/* TODO: encode: scan runs of identical bytes, emit [count][byte].
 * count capped at 255. decode: repeat byte 'count' times. */
int rle_encode(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap) { return -1; }
int rle_decode(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap) { return -1; }