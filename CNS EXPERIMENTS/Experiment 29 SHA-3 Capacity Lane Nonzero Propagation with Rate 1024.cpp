#include <stdio.h>

int main(void) {
    /* 1600-bit state = 25 lanes of 64 bits; rate = 1024 bits = 16 lanes; capacity = 576 bits = 9 lanes */
    int zero_cap_lanes = 9;
    int rate_lanes_per_block = 16;
    int blocks = 0;

    while (zero_cap_lanes > 0) {
        int touch = (rate_lanes_per_block < zero_cap_lanes) ? rate_lanes_per_block : zero_cap_lanes;
        zero_cap_lanes -= touch;
        blocks++;
    }
    printf("Message blocks needed for all capacity lanes to have nonzero bits: %d\n", blocks);
    return 0;
}
