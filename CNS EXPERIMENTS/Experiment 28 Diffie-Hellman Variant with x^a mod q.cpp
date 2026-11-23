#include <stdio.h>

long long mpow28(long long b, long long e, long long m) {
    long long r = 1; b %= m;
    while (e > 0) { if (e & 1LL) r = (r * b) % m; b = (b * b) % m; e >>= 1; }
    return r;
}

int main(void) {
    long long a, q, x_alice, x_bob;
    printf("Enter public a, modulus q, Alice secret x, Bob secret y: ");
    scanf("%lld %lld %lld %lld", &a, &q, &x_alice, &x_bob);

    /* If Alice sends x^a mod q and Bob sends y^a mod q, both can compute x^y mod q if a is known */
    long long sent_a = mpow28(x_alice, a, q);
    long long sent_b = mpow28(x_bob, a, q);
    long long shared = mpow28(x_alice, x_bob, q);

    printf("Alice sends %lld, Bob sends %lld, shared key x^y mod q = %lld\n", sent_a, sent_b, shared);
    printf("Eve can solve discrete logs in prime power or small subgroups to recover x and y.\n");
    return 0;
}
