#include <stdio.h>
#include <stdint.h>

uint64_t mac_block30(uint64_t x, uint64_t k) {
    return ((x ^ k) << 3) | ((x ^ k) >> 61);
}

int main(void) {
    uint64_t X = 0x1122334455667788ULL, K = 0x0F0F0F0F0F0F0F0FULL;
    uint64_t T = mac_block30(X, K);
    uint64_t block2 = X ^ T;
    uint64_t T2 = mac_block30(block2 ^ T, K);
    printf("One-block tag T = %016llX | Forged X || X^T tag = %016llX\n",
           (unsigned long long)T, (unsigned long long)T2);
    return 0;
}
