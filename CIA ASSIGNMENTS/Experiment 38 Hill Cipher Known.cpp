#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int mod_26(int val) {
    int r = val % 26;
    return r < 0 ? r + 26 : r;
}

static int inv_mod_26(int a) {
    a = mod_26(a);
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1) return x;
    }
    return -1;
}

static int solve_key_from_pairs(const char *pt_str, const char *ct_str, int K_out[2][2]) {
    char p[4], c[4];
    int pn = 0, cn = 0;

    for (int i = 0; pt_str[i] && pn < 4; i++) {
        if (isalpha((unsigned char)pt_str[i])) {
            p[pn++] = (char)toupper((unsigned char)pt_str[i]);
        }
    }
    for (int i = 0; ct_str[i] && cn < 4; i++) {
        if (isalpha((unsigned char)ct_str[i])) {
            c[cn++] = (char)toupper((unsigned char)ct_str[i]);
        }
    }
    if (pn < 4 || cn < 4) return 0;

    /* Column-wise 2x2 matrices: digraph 0 in col 0, digraph 1 in col 1 */
    int P[2][2] = {{p[0] - 'A', p[2] - 'A'}, {p[1] - 'A', p[3] - 'A'}};
    int C[2][2] = {{c[0] - 'A', c[2] - 'A'}, {c[1] - 'A', c[3] - 'A'}};

    int det = mod_26(P[0][0] * P[1][1] - P[0][1] * P[1][0]);
    int det_inv = inv_mod_26(det);
    if (det_inv < 0) return 0;

    int P_inv[2][2] = {
        {mod_26(det_inv * P[1][1]), mod_26(-det_inv * P[0][1])},
        {mod_26(-det_inv * P[1][0]), mod_26(det_inv * P[0][0])}
    };

    for (int r = 0; r < 2; r++) {
        for (int col = 0; col < 2; col++) {
            K_out[r][col] = mod_26(C[r][0] * P_inv[0][col] + C[r][1] * P_inv[1][col]);
        }
    }
    return 1;
}

static void encrypt_digraphs(const int K[2][2], const char *pt_str, char *ct_out) {
    char clean[512];
    int n = 0;
    for (int i = 0; pt_str[i]; i++) {
        if (isalpha((unsigned char)pt_str[i])) {
            clean[n++] = (char)toupper((unsigned char)pt_str[i]);
        }
    }
    if (n % 2 != 0) clean[n++] = 'Z';

    for (int i = 0; i < n; i += 2) {
        int x0 = clean[i] - 'A';
        int x1 = clean[i + 1] - 'A';
        ct_out[i]     = (char)('A' + mod_26(K[0][0] * x0 + K[0][1] * x1));
        ct_out[i + 1] = (char)('A' + mod_26(K[1][0] * x0 + K[1][1] * x1));
    }
    ct_out[n] = '\0';
}

int main(void) {
    int mode;
    printf("1. Known-plaintext recovery from given P and C pairs\n");
    printf("2. Chosen-plaintext test using chosen digraphs HA and IC\n");
    printf("Select mode 1 or 2: ");
    scanf("%d", &mode);
    getchar();

    if (mode == 1) {
        char pt4[64], ct4[64];
        int K[2][2];
        printf("Enter 4 known plaintext letters e.g. HELP: ");
        fgets(pt4, sizeof(pt4), stdin);
        printf("Enter 4 corresponding ciphertext letters: ");
        fgets(ct4, sizeof(ct4), stdin);

        if (solve_key_from_pairs(pt4, ct4, K)) {
            printf("Recovered key matrix:\n%d  %d\n%d  %d\n", K[0][0], K[0][1], K[1][0], K[1][1]);
        } else {
            printf("Chosen plaintext letters did not yield an invertible matrix mod 26.\n");
        }
    } else {
        int secret_K[2][2], recovered_K[2][2];
        const char *chosen_pt = "HAIC";
        char chosen_ct[16];

        printf("Enter 2x2 secret key k00 k01 k10 k11: ");
        scanf("%d %d %d %d", &secret_K[0][0], &secret_K[0][1], &secret_K[1][0], &secret_K[1][1]);

        encrypt_digraphs(secret_K, chosen_pt, chosen_ct);
        printf("Chosen plaintext: %s -> Oracle ciphertext: %s\n", chosen_pt, chosen_ct);

        if (solve_key_from_pairs(chosen_pt, chosen_ct, recovered_K)) {
            printf("Recovered key matrix:\n%d  %d\n%d  %d\n",
                   recovered_K[0][0], recovered_K[0][1], recovered_K[1][0], recovered_K[1][1]);
        } else {
            printf("Recovery failed.\n");
        }
    }
    return 0;
}
