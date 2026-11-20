#include <stdio.h>
#include <string.h>
#include <ctype.h>

void pf3_matrix(const char *key, char m[5][5]) {
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

void pf3_pos(char m[5][5], char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (m[i][j] == ch) { *r = i; *c = j; return; }
}

int main(void) {
    char key[128], text[512], clean[512], pairs[1024], out[1024], m[5][5];
    printf("Enter keyword: ");
    scanf("%127s", key);
    getchar();
    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    pf3_matrix(key, m);

    int n = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha((unsigned char)text[i])) {
            char ch = (char)toupper((unsigned char)text[i]);
            clean[n++] = (ch == 'J') ? 'I' : ch;
        }
    }
    int idx = 0, i = 0;
    while (i < n) {
        char a = clean[i];
        char b = (i + 1 < n) ? clean[i + 1] : 'X';
        if (a == b) { pairs[idx++] = a; pairs[idx++] = 'X'; i++; }
        else { pairs[idx++] = a; pairs[idx++] = b; i += 2; }
    }
    for (int k = 0; k < idx; k += 2) {
        int r1, c1, r2, c2;
        pf3_pos(m, pairs[k], &r1, &c1);
        pf3_pos(m, pairs[k + 1], &r2, &c2);
        if (r1 == r2) { out[k] = m[r1][(c1 + 1) % 5]; out[k + 1] = m[r2][(c2 + 1) % 5]; }
        else if (c1 == c2) { out[k] = m[(r1 + 1) % 5][c1]; out[k + 1] = m[(r2 + 1) % 5][c2]; }
        else { out[k] = m[r1][c2]; out[k + 1] = m[r2][c1]; }
    }
    out[idx] = '\0';
    printf("Ciphertext: %s\n", out);
    return 0;
}
