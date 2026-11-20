#include <stdio.h>
#include <string.h>
#include <ctype.h>

int m26_12(int x) { return ((x % 26) + 26) % 26; }

int inv26_12(int a) {
    a = m26_12(a);
    for (int x = 1; x < 26; x++) if ((a * x) % 26 == 1) return x;
    return -1;
}

int main(void) {
    int K[2][2], Kinv[2][2];
    char msg[512], clean[512], enc[512], dec[512];

    printf("Enter 2x2 key matrix k00 k01 k10 k11: ");
    scanf("%d %d %d %d", &K[0][0], &K[0][1], &K[1][0], &K[1][1]);
    getchar();
    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);

    int det = m26_12(K[0][0] * K[1][1] - K[0][1] * K[1][0]);
    int dinv = inv26_12(det);
    Kinv[0][0] = m26_12(dinv * K[1][1]);
    Kinv[0][1] = m26_12(dinv * (-K[0][1]));
    Kinv[1][0] = m26_12(dinv * (-K[1][0]));
    Kinv[1][1] = m26_12(dinv * K[0][0]);

    int n = 0;
    for (int i = 0; msg[i]; i++)
        if (isalpha((unsigned char)msg[i])) clean[n++] = (char)toupper((unsigned char)msg[i]);
    if (n % 2 != 0) clean[n++] = 'X';

    for (int i = 0; i < n; i += 2) {
        int a = clean[i] - 'A', b = clean[i + 1] - 'A';
        enc[i] = (char)('A' + m26_12(K[0][0] * a + K[0][1] * b));
        enc[i + 1] = (char)('A' + m26_12(K[1][0] * a + K[1][1] * b));
    }
    enc[n] = '\0';

    for (int i = 0; i < n; i += 2) {
        int a = enc[i] - 'A', b = enc[i + 1] - 'A';
        dec[i] = (char)('A' + m26_12(Kinv[0][0] * a + Kinv[0][1] * b));
        dec[i + 1] = (char)('A' + m26_12(Kinv[1][0] * a + Kinv[1][1] * b));
    }
    dec[n] = '\0';

    printf("Ciphertext: %s\nDecrypted : %s\n", enc, dec);
    return 0;
}
