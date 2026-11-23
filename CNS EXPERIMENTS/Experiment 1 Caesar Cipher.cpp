#include <stdio.h>
#include <ctype.h>

void caesar(char *text, int k) {
    k = ((k % 26) + 26) % 26;
    for (int i = 0; text[i]; i++) {
        if (isalpha((unsigned char)text[i])) {
            char base = isupper((unsigned char)text[i]) ? 'A' : 'a';
            text[i] = (char)(((text[i] - base + k) % 26) + base);
        }
    }
}

int main(void) {
    char msg[512];
    int k;
    printf("Enter text: ");
    fgets(msg, sizeof(msg), stdin);
    printf("Enter shift k (1..25): ");
    scanf("%d", &k);

    caesar(msg, k);
    printf("Ciphertext: %s", msg);
    return 0;
}
