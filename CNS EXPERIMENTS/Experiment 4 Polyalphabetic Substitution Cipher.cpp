#include <stdio.h>
#include <string.h>
#include <ctype.h>

void poly_cipher(const char *in, const char *key, char *out, int decrypt) {
    int klen = (int)strlen(key), ki = 0;
    for (int i = 0; in[i]; i++) {
        if (isalpha((unsigned char)in[i])) {
            int low = islower((unsigned char)in[i]);
            char base = low ? 'a' : 'A';
            int p = in[i] - base;
            int k = toupper((unsigned char)key[ki % klen]) - 'A';
            ki++;
            int v = decrypt ? ((p - k + 26) % 26) : ((p + k) % 26);
            out[i] = (char)(base + v);
        } else {
            out[i] = in[i];
        }
    }
    out[strlen(in)] = '\0';
}

int main(void) {
    char key[128], plain[512], cipher[512], dec[512];
    printf("Enter repeating key: ");
    scanf("%127s", key);
    getchar();
    printf("Enter plaintext: ");
    fgets(plain, sizeof(plain), stdin);
    poly_cipher(plain, key, cipher, 0);
    poly_cipher(cipher, key, dec, 1);
    printf("Ciphertext: %s", cipher);
    printf("Decrypted : %s", dec);
    return 0;
}
