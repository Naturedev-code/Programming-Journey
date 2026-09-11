#include <stdio.h>

int main(void)
{
    char number[20];
    char digits[20];
    int count = 0;

    printf("Enter a number: ");
    if (scanf("%19s", number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int start = number[0] == '-' ? 1 : 0;
    if (number[start] == '\0') {
        printf("Invalid input.\n");
        return 1;
    }

    for (int i = start; number[i] != '\0'; i++) {
        if (number[i] < '0' || number[i] > '9') {
            printf("Invalid input.\n");
            return 1;
        }
        digits[count++] = number[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (digits[j] > digits[j + 1]) {
                char temp = digits[j];
                digits[j] = digits[j + 1];
                digits[j + 1] = temp;
            }
        }
    }

    printf("Digits in ascending order: ");
    for (int i = 0; i < count; i++) {
        printf("%c", digits[i]);
    }
    printf("\n");

    return 0;
}