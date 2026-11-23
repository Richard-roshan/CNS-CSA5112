#include <stdio.h>
#include <string.h>
#include <ctype.h>

void build_key_alphabet(const char *keyword, char cipher_alpha[26]) {
    int used[26] = {0};
    int idx = 0;

    for (int i = 0; keyword[i]; i++) {
        if (isalpha((unsigned char)keyword[i])) {
            int c = toupper((unsigned char)keyword[i]) - 'A';
            if (!used[c]) {
                used[c] = 1;
                cipher_alpha[idx++] = (char)('A' + c);
            }
        }
    }
    for (int c = 0; c < 26; c++) {
        if (!used[c]) {
            cipher_alpha[idx++] = (char)('A' + c);
        }
    }
}

void mono_process(const char *in, char *out, const char cipher_alpha[26], int decrypt) {
    char inv[26];
    if (decrypt) {
        for (int i = 0; i < 26; i++) {
            inv[cipher_alpha[i] - 'A'] = (char)('A' + i);
        }
    }
    for (int i = 0; in[i]; i++) {
        if (isalpha((unsigned char)in[i])) {
            int is_low = islower((unsigned char)in[i]);
            int pos = toupper((unsigned char)in[i]) - 'A';
            char mapped = decrypt ? inv[pos] : cipher_alpha[pos];
            out[i] = is_low ? (char)tolower((unsigned char)mapped) : mapped;
        } else {
            out[i] = in[i];
        }
    }
    out[strlen(in)] = '\0';
}

int main(void) {
    char keyword[128], plain[512], cipher[512], recovered[512];
    char alpha[26];

    printf("Enter keyword e.g. CIPHER: ");
    scanf("%127s", keyword);
    getchar();
    printf("Enter message: ");
    fgets(plain, sizeof(plain), stdin);

    build_key_alphabet(keyword, alpha);
    mono_process(plain, cipher, alpha, 0);
    mono_process(cipher, recovered, alpha, 1);

    printf("Ciphertext: %s", cipher);
    printf("Decrypted : %s", recovered);
    return 0;
}
