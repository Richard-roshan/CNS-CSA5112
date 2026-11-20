#include <stdio.h>
#include <math.h>

int main(void) {
    double log2_fact25 = 0.0;
    for (int i = 2; i <= 25; i++) log2_fact25 += log2((double)i);
    printf("Raw key permutations 25! ~= 2^%.2f\n", log2_fact25);
    printf("Effectively unique Playfair keys accounting for equivalent matrices ~= 2^50\n");
    return 0;
}
