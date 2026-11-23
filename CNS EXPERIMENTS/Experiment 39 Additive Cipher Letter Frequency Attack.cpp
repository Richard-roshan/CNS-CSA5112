#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const double EFREQ39[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406,  6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978,  2.360, 0.150, 1.974, 0.074
};

typedef struct { int shift; double score; char pt[512]; } R39;

int cmp39(const void *a, const void *b) {
    double d = ((const R39 *)a)->score - ((const R39 *)b)->score;
    return (d < 0) ? -1 : (d > 0) ? 1 : 0;
}

int main(void) {
    char ct[512];
    int ntop;
    printf("Enter additive ciphertext: ");
    fgets(ct, sizeof(ct), stdin);
    ct[strcspn(ct, "\r\n")] = '\0';
    printf("Top N plaintexts: ");
    scanf("%d", &ntop);
    if (ntop < 1) ntop = 1;
    if (ntop > 26) ntop = 26;

    R39 arr[26];
    for (int s = 0; s < 26; s++) {
        int c[26] = {0}, tot = 0;
        for (int i = 0; ct[i]; i++) {
            if (isalpha((unsigned char)ct[i])) {
                char base = isupper((unsigned char)ct[i]) ? 'A' : 'a';
                char p = (char)(base + (((ct[i] - base - s) % 26 + 26) % 26));
                arr[s].pt[i] = p;
                c[toupper((unsigned char)p) - 'A']++;
                tot++;
            } else {
                arr[s].pt[i] = ct[i];
            }
        }
        arr[s].pt[strlen(ct)] = '\0';
        arr[s].shift = s;
        double sc = 0.0;
        for (int i = 0; i < 26; i++) {
            double ex = (EFREQ39[i] / 100.0) * tot;
            double df = c[i] - ex;
            sc += (df * df) / (ex > 0 ? ex : 1.0);
        }
        arr[s].score = sc;
    }
    qsort(arr, 26, sizeof(R39), cmp39);
    for (int i = 0; i < ntop; i++) printf("%d. [k=%d] %s\n", i + 1, arr[i].shift, arr[i].pt);
    return 0;
}
