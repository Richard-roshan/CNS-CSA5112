#include <stdio.h>
#include <stdint.h>

static uint8_t p22(uint16_t v, const int *arr, int n, int sz) {
    uint8_t r = 0;
    for (int i = 0; i < n; i++) r = (uint8_t)((r << 1) | ((v >> (sz - arr[i])) & 1u));
    return r;
}

static uint8_t rot5_22(uint8_t x, int s) {
    s %= 5;
    return (uint8_t)(((x << s) | (x >> (5 - s))) & 0x1Fu);
}

static void keys22(uint16_t k10, uint8_t *k1, uint8_t *k2) {
    static const int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    static const int P8[8] = {6, 3, 7, 4, 8, 5, 10, 9};
    uint8_t p = p22(k10, P10, 10, 10);
    uint8_t l = rot5_22((p >> 5) & 0x1Fu, 1), r = rot5_22(p & 0x1Fu, 1);
    *k1 = p22((uint16_t)((l << 5) | r), P8, 8, 10);
    l = rot5_22(l, 2); r = rot5_22(r, 2);
    *k2 = p22((uint16_t)((l << 5) | r), P8, 8, 10);
}

static uint8_t fk22(uint8_t b, uint8_t sk) {
    static const int EP[8] = {4, 1, 2, 3, 2, 3, 4, 1};
    static const int P4[4] = {2, 4, 3, 1};
    static const uint8_t S0[4][4] = {{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
    static const uint8_t S1[4][4] = {{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};
    uint8_t l = (b >> 4) & 0x0Fu, r = b & 0x0Fu;
    uint8_t e = p22(r, EP, 8, 4) ^ sk;
    uint8_t el = (e >> 4) & 0x0Fu, er = e & 0x0Fu;
    uint8_t s = (uint8_t)((S0[(((el >> 3) & 1) << 1) | (el & 1)][(el >> 1) & 3] << 2) |
                          S1[(((er >> 3) & 1) << 1) | (er & 1)][(er >> 1) & 3]);
    return (uint8_t)(((l ^ p22(s, P4, 4, 4)) << 4) | r);
}

uint8_t sdes22_enc(uint8_t pt, uint16_t k10) {
    static const int IP[8] = {2,6,3,1,4,8,5,7}, IPi[8] = {4,1,3,5,7,2,8,6};
    uint8_t k1, k2; keys22(k10, &k1, &k2);
    uint8_t x = fk22(p22(pt, IP, 8, 8), k1);
    x = (uint8_t)(((x & 0x0F) << 4) | (x >> 4));
    return p22(fk22(x, k2), IPi, 8, 8);
}

uint8_t sdes22_dec(uint8_t ct, uint16_t k10) {
    static const int IP[8] = {2,6,3,1,4,8,5,7}, IPi[8] = {4,1,3,5,7,2,8,6};
    uint8_t k1, k2; keys22(k10, &k1, &k2);
    uint8_t x = fk22(p22(ct, IP, 8, 8), k2);
    x = (uint8_t)(((x & 0x0F) << 4) | (x >> 4));
    return p22(fk22(x, k1), IPi, 8, 8);
}

int main(void) {
    uint8_t pt[2] = {0x01, 0x23}, ct[2], rec[2], iv = 0xAA;
    uint16_t key = 0x1FD;
    uint8_t prev = iv;
    for (int i = 0; i < 2; i++) { ct[i] = sdes22_enc(pt[i] ^ prev, key); prev = ct[i]; }
    prev = iv;
    for (int i = 0; i < 2; i++) { rec[i] = sdes22_dec(ct[i], key) ^ prev; prev = ct[i]; }
    printf("CBC CT: %02X %02X | Decrypted: %02X %02X\n", ct[0], ct[1], rec[0], rec[1]);
    return 0;
}
