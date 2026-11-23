#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char text[512], out[512];
    int n, shifts[512], dec;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    printf("Number of shift values: ");
    scanf("%d", &n);
    printf("Enter shift values: ");
    for (int i = 0; i < n; i++) scanf("%d", &shifts[i]);
    printf("0 = Encrypt, 1 = Decrypt: ");
    scanf("%d", &dec);

    int si = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha((unsigned char)text[i])) {
            int low = islower((unsigned char)text[i]);
            char base = low ? 'a' : 'A';
            int p = text[i] - base;
            int s = ((shifts[si % n] % 26) + 26) % 26;
            si++;
            int v = dec ? ((p - s + 26) % 26) : ((p + s) % 26);
            out[i] = (char)(base + v);
        } else {
            out[i] = text[i];
        }
    }
    out[strlen(text)] = '\0';
    printf("Result: %s", out);
    return 0;
}n
