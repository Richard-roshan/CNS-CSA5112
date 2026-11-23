#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char FREQ_ORD37[27] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

int main(void) {
    char ciph[512];
    int top_n;
    printf("Enter ciphertext: ");
    fgets(ciph, sizeof(ciph), stdin);
    ciph[strcspn(ciph, "\r\n")] = '\0';
    printf("How many top plaintexts: ");
    scanf("%d", &top_n);
    if (top_n < 1) top_n = 1;
    if (top_n > 15) top_n = 15;

    int cnt[26] = {0}, ord[26];
    for (int i = 0; ciph[i]; i++) if (isalpha((unsigned char)ciph[i])) cnt[toupper((unsigned char)ciph[i]) - 'A']++;
    for (int i = 0; i < 26; i++) ord[i] = i;
    for (int i = 0; i < 26; i++)
        for (int j = i + 1; j < 26; j++)
            if (cnt[ord[j]] > cnt[ord[i]]) { int t = ord[i]; ord[i] = ord[j]; ord[j] = t; }

    char base_map[26];
    for (int i = 0; i < 26; i++) base_map[ord[i]] = FREQ_ORD37[i];

    srand(37);
    for (int k = 0; k < top_n; k++) {
        char m[26];
        memcpy(m, base_map, 26);
        for (int s = 0; s < k * 2; s++) {
            int x = rand() % 26, y = rand() % 26;
            char tmp = m[x]; m[x] = m[y]; m[y] = tmp;
        }
        printf("%d. ", k + 1);
        for (int i = 0; ciph[i]; i++) {
            if (isalpha((unsigned char)ciph[i])) {
                int low = islower((unsigned char)ciph[i]);
                char ch = m[toupper((unsigned char)ciph[i]) - 'A'];
                putchar(low ? tolower((unsigned char)ch) : ch);
            } else {
                putchar(ciph[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
