#include <stdio.h>
#include <stdint.h>

int main(void) {
    static const int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    uint64_t key56;
    printf("Enter 56-bit key in hex e.g. 133457799BBCDFF: ");
    scanf("%llx", &key56);
    key56 &= 0x00FFFFFFFFFFFFFFULL;

    printf("Forward shift schedule K1..K16 and decryption order K16..K1:\n");
    for (int round = 1; round <= 16; round++) {
        printf("Round %2d: left shift %d | Decrypt uses subkey K%d\n", round, shifts[round - 1], 17 - round);
    }
    printf("Initial key mask value: 0x%014llX\n", (unsigned long long)key56);
    return 0;
}
