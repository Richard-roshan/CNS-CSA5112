#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char kw[128], plain[512], cipher_alpha[27];
    int used[26] = {0}, idx = 0;

    printf("Enter keyword e.g. CIPHER: ");
    scanf("%127s", kw);
    getchar();
    printf("Enter plaintext: ");
    fgets(plain, sizeof(plain), stdin);

    for (int i = 0; kw[i]; i++) {
        if (isalpha((unsigned char)kw[i])) {
            int c = toupper((unsigned char)kw[i]) - 'A';
            if (!used[c]) { used[c] = 1; cipher_alpha[idx++] = (char)('A' + c); }
        }
    }
    for (int c = 0; c < 26; c++) if (!used[c]) cipher_alpha[idx++] = (char)('A' + c);
    cipher_alpha[26] = '\0';

    printf("Cipher alphabet: %s\n", cipher_alpha);
    printf("Ciphertext     : ");
    for (int i = 0; plain[i]; i++) {
        if (isalpha((unsigned char)plain[i])) {
            int low = islower((unsigned char)plain[i]);
            char ch = cipher_alpha[toupper((unsigned char)plain[i]) - 'A'];
            putchar(low ? tolower((unsigned char)ch) : ch);
        } else {
            putchar(plain[i]);
        }
    }
    return 0;
}
