#include <stdio.h>
#include <stdint.h>

uint64_t des_feistel_round33(uint64_t block64, uint64_t subkey48) {
    uint32_t L = (uint32_t)(block64 >> 32);
    uint32_t R = (uint32_t)(block64 & 0xFFFFFFFFu);
    uint32_t f_out = (uint32_t)(((uint64_t)R ^ (subkey48 >> 16)) & 0xFFFFFFFFu);
    uint32_t next_L = R;
    uint32_t next_R = L ^ f_out;
    return (((uint64_t)next_L) << 32) | (uint64_t)next_R;
}

int main(void) {
    uint64_t pt64, key56;
    printf("Enter 64-bit plaintext and 56-bit key in hex: ");
    scanf("%llx %llx", &pt64, &key56);

    uint64_t state = pt64;
    for (int r = 0; r < 16; r++) {
        uint64_t sk = (key56 << (r % 8)) & 0x0000FFFFFFFFFFFFULL;
        state = des_feistel_round33(state, sk);
    }
    printf("DES 64-bit output block: %016llX\n", (unsigned long long)state);
    return 0;
}
