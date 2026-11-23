#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint64_t k56;
    printf("Enter 56-bit key in hex: ");
    scanf("%llx", &k56);
    k56 &= 0x00FFFFFFFFFFFFFFULL;

    uint32_t C = (uint32_t)((k56 >> 28) & 0x0FFFFFFFu);
    uint32_t D = (uint32_t)(k56 & 0x0FFFFFFFu);
    printf("Disjoint 28-bit halves: C = 0x%07X, D = 0x%07X\n", C, D);

    for (int r = 1; r <= 16; r++) {
        uint32_t c_part = C & 0x00FFFFFFu;
        uint32_t d_part = D & 0x00FFFFFFu;
        uint64_t sub48 = (((uint64_t)c_part) << 24) | (uint64_t)d_part;
        printf("Round %2d 48-bit sample: 0x%012llX\n", r, (unsigned long long)sub48);
    }
    return 0;
}
