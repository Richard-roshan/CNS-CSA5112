#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void) {
    uint8_t msg[8] = {'A','B','C','D','E','F','G','H'};
    uint8_t buf[16];
    memcpy(buf, msg, 8);
    buf[8] = 0x80;
    for (int i = 9; i < 16; i++) buf[i] = 0x00;

    printf("Original block length: 8 bytes -> Padded length: 16 bytes\n");
    printf("Motivation: receiver always strips padding bits cleanly without guessing whether last block was padded.\n");
    return 0;
}
