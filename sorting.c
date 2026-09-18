#include <stdio.h>

int main(void)
{
    int numbers[100];
    int count;

    printf("How many integers do you want to sort (1-100)? ");
    if (scanf("%d", &count) != 1 || count < 1 || count > 100)
    {
        printf("Please enter a count from 1 to 100.\n");
        return 1;
    }

    printf("Enter %d integers: ", count);
    for (int index = 0; index < count; index++)
    {
        if (scanf("%d", &numbers[index]) != 1)
        {
            printf("Invalid integer entered.\n");
            return 1;
        }
    }

    for (int pass = 0; pass < count - 1; pass++)
    {
        int changed = 0;
        for (int index = 0; index < count - pass - 1; index++)
        {
            if (numbers[index] > numbers[index + 1])
            {
                int temporary = numbers[index];
                numbers[index] = numbers[index + 1];
                numbers[index + 1] = temporary;
                changed = 1;
            }
        }
        if (!changed)
        {
            break;
        }
    }

    printf("Sorted numbers: ");
    for (int index = 0; index < count; index++)
    {
        printf("%d%s", numbers[index], index + 1 == count ? "\n" : " ");
    }
    return 0;
}
