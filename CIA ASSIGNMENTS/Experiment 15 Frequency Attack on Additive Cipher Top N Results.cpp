	#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const double F15[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406,  6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978,  2.360, 0.150, 1.974, 0.074
};

typedef struct { int k; double chi2; char s[512]; } C15;

int cmp15(const void *a, const void *b) {
    double d = ((const C15 *)a)->chi2 - ((const C15 *)b)->chi2;
    return (d < 0) ? -1 : (d > 0) ? 1 : 0;
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
    if (top > 26) top = 26;

    C15 list[26];
    for (int k = 0; k < 26; k++) {
        int cnt[26] = {0}, tot = 0;
        for (int i = 0; ciph[i]; i++) {
            if (isalpha((unsigned char)ciph[i])) {
                char base = isupper((unsigned char)ciph[i]) ? 'A' : 'a';
                char p = (char)(base + (((ciph[i] - base - k) % 26 + 26) % 26));
                list[k].s[i] = p;
                cnt[toupper((unsigned char)p) - 'A']++;
                tot++;
            } else {
                list[k].s[i] = ciph[i];
            }
        }
        list[k].s[strlen(ciph)] = '\0';
        list[k].k = k;
        double chi = 0.0;
        for (int i = 0; i < 26; i++) {
            double exp = (F15[i] / 100.0) * tot;
            double df = cnt[i] - exp;
            chi += (df * df) / (exp > 0 ? exp : 1.0);
        }
        list[k].chi2 = chi;
    }
    qsort(list, 26, sizeof(C15), cmp15);
    for (int i = 0; i < top; i++) printf("%d. shift %d: %s\n", i + 1, list[i].k, list[i].s);
    return 0;
}
