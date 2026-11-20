#include <stdio.h>
#include <stdint.h>
#include <string.h>

int pad_bit_stream(const uint8_t *in, int in_bytes, uint8_t *out, int block_bytes) {
    memcpy(out, in, (size_t)in_bytes);
    out[in_bytes] = 0x80; /* 1 bit followed by zero bits */
    int total = in_bytes + 1;
    while (total % block_bytes != 0) {
        out[total++] = 0x00;
    }
    return total;
}

int main(void) {
    uint8_t full_block[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t padded[16];
    int out_len = pad_bit_stream(full_block, 8, padded, 8);
    printf("Input bytes: 8 -> Padded bytes with extra block: %d\n", out_len);
    printf("Motivation: guarantees unambiguous unpadding even when final block is full.\n");
    return 0;
}
