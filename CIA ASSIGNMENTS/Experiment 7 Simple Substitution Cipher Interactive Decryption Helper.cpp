#include <stdio.h>
#include <string.h>

int main(void) {
    char cipher[2048];
    char map[256] = {0};
    printf("Paste ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);
    cipher[strcspn(cipher, "\r\n")] = '\0';

    int freq[256] = {0};
    for (int i = 0; cipher[i]; i++) freq[(unsigned char)cipher[i]]++;

    printf("Top characters by count:\n");
    for (int rank = 0; rank < 5; rank++) {
        int best = 0;
        for (int c = 1; c < 256; c++) if (freq[c] > freq[best]) best = c;
        if (freq[best] > 0) {
            printf("char '%c' ASCII %d count %d\n", best, best, freq[best]);
            freq[best] = 0;
        }
    }

    int pairs;
    printf("Enter number of symbol-to-plaintext mappings to apply e.g. 3 for e,t,h: ");
    scanf("%d", &pairs);
    for (int i = 0; i < pairs; i++) {
        char sym, pt;
        scanf(" %c %c", &sym, &pt);
        map[(unsigned char)sym] = pt;
    }

    printf("Partial decryption: ");
    for (int i = 0; cipher[i]; i++) {
        char m = map[(unsigned char)cipher[i]];
        putchar(m ? m : '.');
    }
    printf("\n");
    return 0;
}
