#include <stdio.h>

int main(void)
{
    char string[100];
    int count = 0;

    printf("Enter a string: ");
    if (scanf("%99s", string) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    while (string[count] != '\0') {
        count++;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (string[j] > string[j + 1]) {
                char temp = string[j];
                string[j] = string[j + 1];
                string[j + 1] = temp;
            }
        }
    }

    printf("String in ascending order: %s\n", string);

    return 0;
}