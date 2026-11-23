#include <stdio.h>
#include <stdint.h>

uint64_t strong_block_enc(uint64_t b, uint64_t k) {
    b ^= k;
    b = (b << 13) | (b >> 51);
    return b ^ 0x9E3779B97F4A7C15ULL;
}

int main(void) {
    uint64_t pt[2], ct[2], iv, k;
    printf("Enter IV and key in hex: ");
    scanf("%llx %llx", &iv, &k);
    printf("Enter 2 64-bit plaintext blocks in hex: ");
    scanf("%llx %llx", &pt[0], &pt[1]);

    uint64_t prev = iv;
    for (int i = 0; i < 2; i++) {
        ct[i] = strong_block_enc(pt[i] ^ prev, k);
        prev = ct[i];
    }
    printf("CBC Ciphertext: %016llX %016llX\n", (unsigned long long)ct[0], (unsigned long long)ct[1]);
    printf("a. For security: choose stronger cipher such as 3DES.\n");
    printf("b. For performance: choose faster cipher such as single DES or AES.\n");
    return 0;
}
