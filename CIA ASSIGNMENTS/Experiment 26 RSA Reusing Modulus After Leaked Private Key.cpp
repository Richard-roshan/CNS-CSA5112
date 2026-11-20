#include <stdio.h>

long long egcd26(long long a, long long b, long long *x, long long *y) {
    if (b == 0) { *x = 1; *y = 0; return a; }
    long long x1, y1, g = egcd26(b, a % b, &x1, &y1);
    *x = y1; *y = x1 - (a / b) * y1;
    return g;
}

int main(void) {
    long long e_old, d_old, e_new;
    printf("Enter old e, leaked d_old, and new e_new: ");
    scanf("%lld %lld %lld", &e_old, &d_old, &e_new);

    /* e_old * d_old - 1 is a multiple of phi n */
    long long k_phi = e_old * d_old - 1;
    printf("No, reusing modulus n is unsafe because e*d - 1 = k*phi n exposes phi n multiple %lld.\n", k_phi);
    printf("Target new exponent e_new = %lld should be generated with a fresh modulus n.\n", e_new);
    return 0;
}
