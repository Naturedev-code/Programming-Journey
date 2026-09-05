#include <stdio.h>
#include <stdlib.h> // in order to use rand()
#include <time.h>   //in order to use srand()
int main()
{
    int choice, r, wins = 0, loss = 0,draw=0;
    srand(time(NULL)); //generates randomness
    do
    {

        printf("Choose Rock:1 , Paper:2 , scissor:3 ");
        scanf("%d", &choice);

        r = rand() % 3 + 1; // Generates number from 1-3;
        if (choice == r)
        {
            printf("Draw\n");
            draw++;
        }
        else if (choice == 1 && r == 2 || choice == 2 && r == 3 || choice == 3 && r == 1)
        {
            printf("You Lose \n");
            loss++;
        }

        else
        {
            printf("You win \n");
            wins++;
        }
        printf("Do you want to play again?  Y=1/No=2\n");
        scanf("%d", &choice);

    } while (choice == 1);
    printf("\n -->FINAL SCORE <-- \n");
    printf("The total win is %d\n", wins);
    printf("The total loss is %d\n", loss);
     printf("The total draw is %d\n", draw);
    return 0;
}