#include <stdio.h>
#include <string.h>
#include <ctype.h>

void pf10_pos(const char m[5][5], char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (m[i][j] == ch) { *r = i; *c = j; return; }
}

int main(void) {
    const char m[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
    const char *pt = "Must see you over Cadogan West. Coming at once.";
    char clean[512], pairs[1024];
    int n = 0;

    for (int i = 0; pt[i]; i++) {
        if (isalpha((unsigned char)pt[i])) {
            char ch = (char)toupper((unsigned char)pt[i]);
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

    printf("Ciphertext: ");
    for (int k = 0; k < idx; k += 2) {
        int r1, c1, r2, c2;
        pf10_pos(m, pairs[k], &r1, &c1);
        pf10_pos(m, pairs[k + 1], &r2, &c2);
        if (r1 == r2) { putchar(m[r1][(c1 + 1) % 5]); putchar(m[r2][(c2 + 1) % 5]); }
        else if (c1 == c2) { putchar(m[(r1 + 1) % 5][c1]); putchar(m[(r2 + 1) % 5][c2]); }
        else { putchar(m[r1][c2]); putchar(m[r2][c1]); }
    }
    printf("\n");
    return 0;
}
