#include <stdio.h>

int main(void)
{
    int first_number;
    int second_number;

    printf("Enter two numbers: ");
    if (scanf("%d %d", &first_number, &second_number) != 2)
    {
        printf("Please enter valid integers.\n");
        return 1;
    }

    printf("The sum is %d.\n", first_number + second_number);

    return 0;
}
