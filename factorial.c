#include <stdio.h>

int main(void)
{
    unsigned int number;
    unsigned long long factorial = 1;

    printf("Enter a non-negative integer (0-20): ");
    if (scanf("%u", &number) != 1 || number > 20)
    {
        printf("Please enter a whole number from 0 to 20.\n");
        return 1;
    }

    for (unsigned int value = 2; value <= number; value++)
    {
        factorial *= value;
    }

    printf("%u! = %llu\n", number, factorial);
    return 0;
}
