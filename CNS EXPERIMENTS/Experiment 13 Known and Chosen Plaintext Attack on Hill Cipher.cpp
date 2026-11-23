#include <stdio.h>
#include <ctype.h>

int m26_13(int x) { return ((x % 26) + 26) % 26; }

int inv26_13(int a) {
    a = m26_13(a);
    for (int x = 1; x < 26; x++) if ((a * x) % 26 == 1) return x;
    return -1;
}

int main(void) {
    char p[5], c[5];
    printf("Enter 4 plaintext letters e.g. ABCD: ");
    scanf("%4s", p);
    printf("Enter 4 corresponding ciphertext letters: ");
    scanf("%4s", c);

    int P[2][2] = {
        {toupper((unsigned char)p[0]) - 'A', toupper((unsigned char)p[2]) - 'A'},
        {toupper((unsigned char)p[1]) - 'A', toupper((unsigned char)p[3]) - 'A'}
    };
    int C[2][2] = {
        {toupper((unsigned char)c[0]) - 'A', toupper((unsigned char)c[2]) - 'A'},
        {toupper((unsigned char)c[1]) - 'A', toupper((unsigned char)c[3]) - 'A'}
    };
    int det = m26_13(P[0][0] * P[1][1] - P[0][1] * P[1][0]);
    int dinv = inv26_13(det);
    if (dinv < 0) {
        printf("Plaintext matrix not invertible mod 26; for chosen plaintext use A C B D.\n");
        return 1;
    }
    int Pinv[2][2] = {
        {m26_13(dinv * P[1][1]), m26_13(dinv * (-P[0][1]))},
        {m26_13(dinv * (-P[1][0])), m26_13(dinv * P[0][0])}
    };
    int K[2][2];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            K[i][j] = m26_13(C[i][0] * Pinv[0][j] + C[i][1] * Pinv[1][j]);

    printf("Recovered key matrix:\n%d %d\n%d %d\n", K[0][0], K[0][1], K[1][0], K[1][1]);
    return 0;
}
