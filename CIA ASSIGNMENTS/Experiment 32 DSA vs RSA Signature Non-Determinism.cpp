#include <stdio.h>

int main(void) {
    long long msg_hash, k1, k2;
    printf("Enter message hash and two per-signature nonces k1 k2: ");
    scanf("%lld %lld %lld", &msg_hash, &k1, &k2);
    printf("DSA signature 1 uses hash %lld with k1 = %lld\n", msg_hash, k1);
    printf("DSA signature 2 uses hash %lld with k2 = %lld\n", msg_hash, k2);
    printf("Implication: DSA signatures vary each time so identical signatures do not leak repetition,\n");
    printf("whereas reusing k across two messages allows recovering the private signing key.\n");
    return 0;
}
