#include <stdio.h>

long long egcd24(long long a, long long b, long long *x, long long *y) {
    if (b == 0) { *x = 1; *y = 0; return a; }
    long long x1, y1;
    long long g = egcd24(b, a % b, &x1, &y1);
    *x = y1; *y = x1 - (a / b) * y1;
    return g;
}

int main(void) {
    long long e = 31, n = 3599, p = 0, q = 0;
    printf("Enter e and n default 31 3599: ");
    scanf("%lld %lld", &e, &n);

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) { p = i; q = n / i; break; }
    }
    long long phi = (p - 1) * (q - 1);
    long long x, y;
    egcd24(e, phi, &x, &y);
    long long d = ((x % phi) + phi) % phi;
    printf("p = %lld, q = %lld, phi n = %lld, private key d = %lld\n", p, q, phi, d);
    return 0;
}
