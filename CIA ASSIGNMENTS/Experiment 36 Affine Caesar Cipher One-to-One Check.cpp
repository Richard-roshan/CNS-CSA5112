#include <stdio.h>

int gcd36(int a, int b) {
    while (b != 0) { int t = b; b = a % b; a = t; }
    return a;
}

int main(void) {
    int a, b;
    printf("Enter a and b: ");
    scanf("%d %d", &a, &b);

    int one_to_one = (gcd36(a, 26) == 1);
    printf("Affine cipher is %sone-to-one mod 26.\n", one_to_one ? "" : "NOT ");
    if (!one_to_one) {
        int step = 26 / (gcd36(a, 26) > 0 ? gcd36(a, 26) : 26);
        printf("Collision example: p = 0 and p = %d both map to C = %d\n",
               step, ((a * 0 + b) % 26 + 26) % 26);
    }
    return 0;
}
