
#include <stdio.h>
#include <string.h>

int main()
{
    char text[100];
    int key, choice, i;

    printf("1. Encryption\n");
    printf("2. Decryption\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key: ");
    scanf("%d", &key);

    key = key % 26;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            if (choice == 1)
                text[i] = (text[i] - 'A' + key) % 26 + 'A';
            else
                text[i] = (text[i] - 'A' - key + 26) % 26 + 'A';
        }
    }

    printf("Result: %s", text);
    return 0;
}
