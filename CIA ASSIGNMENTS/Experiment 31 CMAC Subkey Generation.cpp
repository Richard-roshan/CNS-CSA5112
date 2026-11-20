#include <stdio.h>
#include <stdint.h>
#include <string.h>

void shift_left_one31(uint8_t *b, int len) {
    uint8_t carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        uint8_t nc = (uint8_t)((b[i] >> 7) & 1u);
        b[i] = (uint8_t)((b[i] << 1) | carry);
        carry = nc;
    }
}

void cmac_k1_k2_31(const uint8_t *L, int len, uint8_t rb, uint8_t *K1, uint8_t *K2) {
    memcpy(K1, L, (size_t)len);
    int msb1 = (K1[0] >> 7) & 1;
    shift_left_one31(K1, len);
    if (msb1) K1[len - 1] ^= rb;

    memcpy(K2, K1, (size_t)len);
    int msb2 = (K2[0] >> 7) & 1;
    shift_left_one31(K2, len);
    if (msb2) K2[len - 1] ^= rb;
}

int main(void) {
    uint8_t L8[8] = {0}, K1_8[8], K2_8[8];
    cmac_k1_k2_31(L8, 8, 0x1B, K1_8, K2_8);
    printf("64-bit constant R64 = 0x1B -> K1[7] = %02X, K2[7] = %02X\n", K1_8[7], K2_8[7]);

    uint8_t L16[16] = {0}, K1_16[16], K2_16[16];
    L16[0] = 0x80;
    cmac_k1_k2_31(L16, 16, 0x87, K1_16, K2_16);
    printf("128-bit constant R128 = 0x87 -> K1[15] = %02X, K2[15] = %02X\n", K1_16[15], K2_16[15]);
    return 0;
}
