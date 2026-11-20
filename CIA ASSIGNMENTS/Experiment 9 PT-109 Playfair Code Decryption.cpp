#include <stdio.h>
#include <string.h>
#include <ctype.h>

void pf9_matrix(const char *key, char m[5][5]) {
    int used[26] = {0};
    used['J' - 'A'] = 1;
    int r = 0, c = 0;
    for (int i = 0; key[i]; i++) {
        if (isalpha((unsigned char)key[i])) {
            char ch = (char)toupper((unsigned char)key[i]);
            if (ch == 'J') ch = 'I';
            if (!used[ch - 'A']) {
                used[ch - 'A'] = 1;
                m[r][c++] = ch;
                if (c == 5) { c = 0; r++; }
            }
        }
    }
    for (int k = 0; k < 26; k++) {
        if (!used[k]) {
            m[r][c++] = (char)('A' + k);
            if (c == 5) { c = 0; r++; }
        }
    }
}

void pf9_pos(char m[5][5], char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (m[i][j] == ch) { *r = i; *c = j; return; }
}

int main(void) {
    const char *msg =
        "KXJEY UREBE ZWEHE WRYTU HEYFS "
        "KREHE GOYFI WTTTU OLKSY CAJPO "
        "BOTEI ZONTX BYBNT GONEY CUZWR "
        "GDSON SXBOU YWRHE BAAHY USEDQ";
    char key[128], m[5][5], clean[1024];
    int n = 0;

    printf("Enter Playfair keyword: ");
    scanf("%127s", key);
    pf9_matrix(key, m);

    for (int i = 0; msg[i]; i++) {
        if (isalpha((unsigned char)msg[i])) {
            char ch = (char)toupper((unsigned char)msg[i]);
            clean[n++] = (ch == 'J') ? 'I' : ch;
        }
    }

    printf("Decrypted PT-109 text: ");
    for (int i = 0; i + 1 < n; i += 2) {
        int r1, c1, r2, c2;
        pf9_pos(m, clean[i], &r1, &c1);
        pf9_pos(m, clean[i + 1], &r2, &c2);
        if (r1 == r2) { putchar(m[r1][(c1 + 4) % 5]); putchar(m[r2][(c2 + 4) % 5]); }
        else if (c1 == c2) { putchar(m[(r1 + 4) % 5][c1]); putchar(m[(r2 + 4) % 5][c2]); }
        else { putchar(m[r1][c2]); putchar(m[r2][c1]); }
    }
    printf("\n");
    return 0;
}
