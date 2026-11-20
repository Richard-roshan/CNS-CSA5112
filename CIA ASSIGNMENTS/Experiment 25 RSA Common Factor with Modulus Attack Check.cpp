#include <stdio.h>

long long gcd25(long long a, long long b) {
    while (b != 0) { long long t = b; b = a % b; a = t; }
    return a;
}

int main(void) {
    long long n, block_m;
    printf("Enter modulus n and plaintext block sharing factor with n: ");
    scanf("%lld %lld", &n, &block_m);
    long long g = gcd25(block_m, n);
    if (g > 1 && g < n) {
        printf("Yes, common factor found: p = %lld, q = %lld\n", g, n / g);
    } else {
        printf("No nontrivial factor found.\n");
    }
    return 0;
}
