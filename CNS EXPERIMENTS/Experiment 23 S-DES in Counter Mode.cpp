#include <stdio.h>
#include <stdint.h>

static uint8_t pbox(uint16_t val, const int *perm, int n, int width) {
    uint8_t out = 0;
    for (int i = 0; i < n; i++) {
        uint8_t bit = (uint8_t)((val >> (width - perm[i])) & 1u);
        out = (uint8_t)((out << 1) | bit);
    }
    return out;
}

static uint8_t lshift5(uint8_t x, int bits) {
    bits %= 5;
    return (uint8_t)(((x << bits) | (x >> (5 - bits))) & 0x1Fu);
}

static void gen_sdes_keys(uint16_t key10, uint8_t *k1, uint8_t *k2) {
    static const int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    static const int P8[8]   = {6, 3, 7, 4, 8, 5, 10, 9};

    uint8_t k_p10 = pbox(key10, P10, 10, 10);
    uint8_t left  = lshift5((uint8_t)((k_p10 >> 5) & 0x1Fu), 1);
    uint8_t right = lshift5((uint8_t)(k_p10 & 0x1Fu), 1);
    *k1 = pbox((uint16_t)((left << 5) | right), P8, 8, 10);

    left  = lshift5(left, 2);
    right = lshift5(right, 2);
    *k2 = pbox((uint16_t)((left << 5) | right), P8, 8, 10);
}

static uint8_t round_fk(uint8_t state8, uint8_t subkey8) {
    static const int EP[8] = {4, 1, 2, 3, 2, 3, 4, 1};
    static const int P4[4] = {2, 4, 3, 1};
    static const uint8_t S0[4][4] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };
    static const uint8_t S1[4][4] = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };

    uint8_t hi = (uint8_t)((state8 >> 4) & 0x0Fu);
    uint8_t lo = (uint8_t)(state8 & 0x0Fu);

    uint8_t expanded = (uint8_t)(pbox(lo, EP, 8, 4) ^ subkey8);
    uint8_t n0 = (uint8_t)((expanded >> 4) & 0x0Fu);
    uint8_t n1 = (uint8_t)(expanded & 0x0Fu);

    int r0 = (((n0 >> 3) & 1) << 1) | (n0 & 1);
    int c0 = (n0 >> 1) & 3;
    int r1 = (((n1 >> 3) & 1) << 1) | (n1 & 1);
    int c1 = (n1 >> 1) & 3;

    uint8_t s_combined = (uint8_t)((S0[r0][c0] << 2) | S1[r1][c1]);
    uint8_t p4_out = pbox(s_combined, P4, 4, 4);
    return (uint8_t)(((hi ^ p4_out) << 4) | lo);
}

static uint8_t sdes_enc_block(uint8_t block8, uint16_t key10) {
    static const int IP[8]     = {2, 6, 3, 1, 4, 8, 5, 7};
    static const int IP_INV[8] = {4, 1, 3, 5, 7, 2, 8, 6};

    uint8_t k1, k2;
    gen_sdes_keys(key10, &k1, &k2);

    uint8_t x = pbox(block8, IP, 8, 8);
    x = round_fk(x, k1);
    x = (uint8_t)(((x & 0x0Fu) << 4) | ((x >> 4) & 0x0Fu));
    x = round_fk(x, k2);
    return pbox(x, IP_INV, 8, 8);
}

static void sdes_ctr_process(const uint8_t *in, uint8_t *out, int blocks, uint8_t counter, uint16_t key10) {
    for (int i = 0; i < blocks; i++) {
        uint8_t stream_block = sdes_enc_block((uint8_t)(counter + i), key10);
        out[i] = (uint8_t)(in[i] ^ stream_block);
    }
}

static void print_bin8(uint8_t v) {
    for (int b = 7; b >= 0; b--) {
        putchar(((v >> b) & 1u) ? '1' : '0');
        if (b == 4) putchar(' ');
    }
}

int main(void) {
    uint16_t key10 = 0x1FD; /* 01111 11101 */
    uint8_t start_ctr = 0x00; /* 0000 0000 */
    uint8_t pt[3] = {0x01, 0x02, 0x04}; /* 0000 0001  0000 0010  0000 0100 */
    uint8_t ct[3] = {0};
    uint8_t decrypted[3] = {0};

    sdes_ctr_process(pt, ct, 3, start_ctr, key10);
    sdes_ctr_process(ct, decrypted, 3, start_ctr, key10);

    printf("CTR Ciphertext : ");
    for (int i = 0; i < 3; i++) {
        print_bin8(ct[i]);
        if (i < 2) printf("  ");
    }
    printf("\n");

    printf("CTR Decrypted  : ");
    for (int i = 0; i < 3; i++) {
        print_bin8(decrypted[i]);
        if (i < 2) printf("  ");
    }
    printf("\n");
    return 0;
}
