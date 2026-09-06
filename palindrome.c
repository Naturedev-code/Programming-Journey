#include <stdio.h>
int main()
{

    int n, i, check;
    do
    {
        int fact = 1;

        printf("Enter the number: ");
        scanf("%d", &n);
        for (i = 1; i <= n; i++)
        {
            fact = fact * i;
        }
        printf("The factorial of %d is %d\n", n, fact);
        printf("Do you want to find palindrome again (Y=1,n=0)\n");
        scanf("%d", &check);
    } while (check == 1);
    return 0;
}