#include <stdio.h>
#include <stdlib.h>
int main()
{
    int choice, r;
    do
    {

        printf("Choose Rock:1 , Paper:2 , scissor:3 ");
        scanf("%d", &choice);
        r = rand() % 3 + 1; // Generates number from 1-3;
        if (choice == r)
            printf("Draw\n");
        else if (choice == 1 && r == 2 || choice == 2 && r == 3 || choice == 3 && r == 1)

            printf("You Lose \n");
        else
            printf("You win \n");
        printf("Do you want to play again?  Y=1/No=2\n");
        scanf("%d", &choice);
    } while (choice == 1);
    return 0;
}