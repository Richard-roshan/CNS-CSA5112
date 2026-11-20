#include <stdio.h>
#include <stdint.h>

/* Simple byte permutation cipher for demonstrating CBC error propagation */
static uint8_t permute_byte(uint8_t x, uint8_t key) {
    uint8_t t = (uint8_t)(x ^ key);
    return (uint8_t)(((t & 0x0Fu) << 4) | ((t >> 4) & 0x0Fu));
}

static uint8_t inv_permute_byte(uint8_t y, uint8_t key) {
    uint8_t sw = (uint8_t)(((y & 0x0Fu) << 4) | ((y >> 4) & 0x0Fu));
    return (uint8_t)(sw ^ key);
}

static void cbc_enc(const uint8_t *pt, uint8_t *ct, int len, uint8_t iv, uint8_t key) {
    uint8_t chain = iv;
    for (int i = 0; i < len; i++) {
        ct[i] = permute_byte((uint8_t)(pt[i] ^ chain), key);
        chain = ct[i];
    }
}

static void cbc_dec(const uint8_t *ct, uint8_t *pt, int len, uint8_t iv, uint8_t key) {
    uint8_t chain = iv;
    for (int i = 0; i < len; i++) {
        pt[i] = (uint8_t)(inv_permute_byte(ct[i], key) ^ chain);
        chain = ct[i];
    }
}

int main(void) {
    int n = 4;
    uint8_t pt[4] = {0x10, 0x20, 0x30, 0x40};
    uint8_t ct[4], rx_ct[4], dec_from_ct_err[4], dec_from_pt_err[4];
    uint8_t iv = 0x5A, key = 0x3C;

    cbc_enc(pt, ct, n, iv, key);

    /* Case A: 1-bit error in transmitted ciphertext block C1 index 1 */
    for (int i = 0; i < n; i++) rx_ct[i] = ct[i];
    rx_ct[1] ^= 0x01;
    cbc_dec(rx_ct, dec_from_ct_err, n, iv, key);

    printf("Case A Ciphertext error in C1:\n");
    printf("Recovered plaintexts: %02X %02X %02X %02X\n",
           dec_from_ct_err[0], dec_from_ct_err[1], dec_from_ct_err[2], dec_from_ct_err[3]);
    printf("Answer a: P1 and P2 are corrupted; blocks beyond P2 are unaffected.\n\n");

    /* Case B: 1-bit error in source plaintext block P0 index 0 */
    uint8_t pt_bad[4] = {0x11, 0x20, 0x30, 0x40};
    uint8_t ct_from_pt_err[4];
    cbc_enc(pt_bad, ct_from_pt_err, n, iv, key);
    cbc_dec(ct_from_pt_err, dec_from_pt_err, n, iv, key);

    printf("Case B Source plaintext error in P0:\n");
    printf("Original CT : %02X %02X %02X %02X\n", ct[0], ct[1], ct[2], ct[3]);
    printf("Modified CT : %02X %02X %02X %02X\n",
           ct_from_pt_err[0], ct_from_pt_err[1], ct_from_pt_err[2], ct_from_pt_err[3]);
    printf("Recovered PT: %02X %02X %02X %02X\n",
           dec_from_pt_err[0], dec_from_pt_err[1], dec_from_pt_err[2], dec_from_pt_err[3]);
    printf("Answer b: Error propagates through all ciphertext blocks from the altered block onward,\n");
    printf("and the receiver recovers the altered plaintext block and subsequent blocks.\n");
    return 0;
}
