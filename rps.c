#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char *choice_name(int choice)
{
    const char *names[] = {"", "Rock", "Paper", "Scissors"};
    return names[choice];
}

int main(void)
{
    int choice;
    int computer;
    int wins = 0;
    int losses = 0;
    int draws = 0;

    srand((unsigned int)time(NULL));
    printf("Rock, Paper, Scissors\n");

    while (1)
    {
        printf("\n1. Rock  2. Paper  3. Scissors  0. Quit\nChoice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }
        if (choice == 0)
        {
            break;
        }
        if (choice < 1 || choice > 3)
        {
            printf("Choose 0, 1, 2, or 3.\n");
            continue;
        }

        computer = rand() % 3 + 1;
        printf("You chose %s; computer chose %s.\n",
               choice_name(choice), choice_name(computer));

        if (choice == computer)
        {
            printf("Draw.\n");
            draws++;
        }
        else if ((choice == 1 && computer == 3) ||
                 (choice == 2 && computer == 1) ||
                 (choice == 3 && computer == 2))
        {
            printf("You win!\n");
            wins++;
        }
        else
        {
            printf("You lose.\n");
            losses++;
        }
    }

    printf("\nFinal score - Wins: %d, Losses: %d, Draws: %d\n",
           wins, losses, draws);
    return 0;
}
