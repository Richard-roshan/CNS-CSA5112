#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char ALPHA_FREQ40[27] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

int main(void) {
    char ct[512];
    int ntop;
    printf("Enter monoalphabetic ciphertext: ");
    fgets(ct, sizeof(ct), stdin);
    ct[strcspn(ct, "\r\n")] = '\0';
    printf("Top N plaintexts: ");
    scanf("%d", &ntop);
    if (ntop < 1) ntop = 1;
    if (ntop > 15) ntop = 15;

    int freq[26] = {0}, idx[26];
    for (int i = 0; ct[i]; i++) if (isalpha((unsigned char)ct[i])) freq[toupper((unsigned char)ct[i]) - 'A']++;
    for (int i = 0; i < 26; i++) idx[i] = i;
    for (int i = 0; i < 26; i++)
        for (int j = i + 1; j < 26; j++)
            if (freq[idx[j]] > freq[idx[i]]) { int t = idx[i]; idx[i] = idx[j]; idx[j] = t; }

    char map0[26];
    for (int i = 0; i < 26; i++) map0[idx[i]] = ALPHA_FREQ40[i];

    srand(40);
    for (int k = 0; k < ntop; k++) {
        char m[26];
        memcpy(m, map0, 26);
        for (int s = 0; s < k * 2; s++) {
            int a = rand() % 26, b = rand() % 26;
            char tmp = m[a]; m[a] = m[b]; m[b] = tmp;
        }
        printf("%d. ", k + 1);
        for (int i = 0; ct[i]; i++) {
            if (isalpha((unsigned char)ct[i])) {
                int low = islower((unsigned char)ct[i]);
                char ch = m[toupper((unsigned char)ct[i]) - 'A'];
                putchar(low ? tolower((unsigned char)ch) : ch);
            } else {
                putchar(ct[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
