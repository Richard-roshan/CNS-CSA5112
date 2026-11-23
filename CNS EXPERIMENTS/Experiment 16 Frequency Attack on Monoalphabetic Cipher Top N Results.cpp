#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char ORD16[27] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

double sc16(const char *s) {
    double r = 0.0;
    for (int i = 0; s[i]; i++) {
        if (isalpha((unsigned char)s[i])) {
            char u = (char)toupper((unsigned char)s[i]);
            for (int j = 0; j < 26; j++) if (ORD16[j] == u) { r += (26 - j); break; }
        }
    }
    return r;
}

int main(void) {
    char ciph[512];
    int top;
    printf("Enter ciphertext: ");
    fgets(ciph, sizeof(ciph), stdin);
    ciph[strcspn(ciph, "\r\n")] = '\0';
    printf("Top N plaintexts e.g. 10: ");
    scanf("%d", &top);
    if (top < 1) top = 1;
    if (top > 15) top = 15;

    int cnt[26] = {0}, idx[26];
    for (int i = 0; ciph[i]; i++) if (isalpha((unsigned char)ciph[i])) cnt[toupper((unsigned char)ciph[i]) - 'A']++;
    for (int i = 0; i < 26; i++) idx[i] = i;
    for (int i = 0; i < 26; i++)
        for (int j = i + 1; j < 26; j++)
            if (cnt[idx[j]] > cnt[idx[i]]) { int t = idx[i]; idx[i] = idx[j]; idx[j] = t; }

    char base_map[26];
    for (int r = 0; r < 26; r++) base_map[idx[r]] = ORD16[r];

    srand(16);
    for (int t = 0; t < top; t++) {
        char m[26], out[512];
        memcpy(m, base_map, 26);
        for (int p = 0; p < t * 2; p++) {
            int a = rand() % 26, b = rand() % 26;
            char tmp = m[a]; m[a] = m[b]; m[b] = tmp;
        }
        for (int i = 0; ciph[i]; i++) {
            if (isalpha((unsigned char)ciph[i])) {
                int low = islower((unsigned char)ciph[i]);
                char ch = m[toupper((unsigned char)ciph[i]) - 'A'];
                out[i] = low ? (char)tolower((unsigned char)ch) : ch;
            } else {
                out[i] = ciph[i];
            }
        }
        out[strlen(ciph)] = '\0';
        printf("%d. score %.1f: %s\n", t + 1, sc16(out), out);
    }
    return 0;
}
