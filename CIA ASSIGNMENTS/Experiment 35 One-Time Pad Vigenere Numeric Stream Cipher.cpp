#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char pt[512], ct[512];
    int n, key_stream[512];

    printf("Enter plaintext: ");
    fgets(pt, sizeof(pt), stdin);
    printf("Enter count of key numbers: ");
    scanf("%d", &n);
    printf("Enter key numbers 0..26: ");
    for (int i = 0; i < n; i++) scanf("%d", &key_stream[i]);

    int ki = 0;
    for (int i = 0; pt[i]; i++) {
        if (isalpha((unsigned char)pt[i])) {
            int low = islower((unsigned char)pt[i]);
            char base = low ? 'a' : 'A';
            int shift = ((key_stream[ki % n] % 26) + 26) % 26;
            ki++;
            ct[i] = (char)(base + ((pt[i] - base + shift) % 26));
        } else {
            ct[i] = pt[i];
        }
    }
    ct[strlen(pt)] = '\0';
    printf("Ciphertext: %s", ct);
    return 0;
}
