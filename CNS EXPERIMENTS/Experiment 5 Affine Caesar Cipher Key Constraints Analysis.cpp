#include <stdio.h>

int gcd5(int a, int b) {
    while (b != 0) { int t = b; b = a % b; a = t; }
    return a;
}

int main(void) {
    printf("a. Limitations on b: None for bijectivity mod 26; b in 0..25 shifts all values equally.\n");
    printf("b. Disallowed values of a in 0..25 where gcd a, 26 != 1:\n");
    for (int a = 0; a < 26; a++) {
        if (gcd5(a, 26) != 1) {
            printf("a = %d maps 0 and %d to the same ciphertext when b = 0.\n", a, 26 / gcd5(a, 26));
        }
    }
    return 0;
}
