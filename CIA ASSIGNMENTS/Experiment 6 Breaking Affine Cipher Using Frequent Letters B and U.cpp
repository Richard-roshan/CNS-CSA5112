#include <stdio.h>
#include <string.h>
#include <ctype.h>

int inv26_6(int a) {
    a = ((a % 26) + 26) % 26;
    for (int x = 1; x < 26; x++) if ((a * x) % 26 == 1) return x;
    return -1;
}

int main(void) {
    char cipher[1024];
    printf("Enter affine ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    /* Most frequent B -> E 4, second most frequent U -> T 19 */
    int c1 = 'B' - 'A', p1 = 'E' - 'A';
    int c2 = 'U' - 'A', p2 = 'T' - 'A';
    int dp = ((p1 - p2) % 26 + 26) % 26;
    int dc = ((c1 - c2) % 26 + 26) % 26;
    int inv_dp = inv26_6(dp);
    int a = (inv_dp >= 0) ? (dc * inv_dp) % 26 : -1;
    int b = (a >= 0) ? ((c1 - a * p1) % 26 + 26) % 26 : -1;
    int a_inv = (a >= 0) ? inv26_6(a) : -1;

    printf("Derived key: a = %d, b = %d, a^-1 = %d\n", a, b, a_inv);
    if (a_inv >= 0) {
        printf("Decrypted text: ");
        for (int i = 0; cipher[i]; i++) {
            if (isalpha((unsigned char)cipher[i])) {
                char base = isupper((unsigned char)cipher[i]) ? 'A' : 'a';
                int c = cipher[i] - base;
                putchar(base + (((a_inv * (c - b)) % 26 + 26) % 26));
            } else {
                putchar(cipher[i]);
            }
        }
    }
    return 0;
}
