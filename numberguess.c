#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    const int maximum = 200;
    int secret;
    int guess;
    int attempts = 0;

    srand((unsigned int)time(NULL));
    secret = rand() % maximum + 1;
    printf("Guess the number (1-%d).\n", maximum);

    do
    {
        printf("Enter your guess: ");
        if (scanf("%d", &guess) != 1 || guess < 1 || guess > maximum)
        {
            printf("Please enter a number from 1 to %d.\n", maximum);
            return 1;
        }

        attempts++;
        if (guess < secret)
        {
            printf("Too low.\n");
        }
        else if (guess > secret)
        {
            printf("Too high.\n");
        }
    } while (guess != secret);

    printf("Correct! You found %d in %d attempt%s.\n",
           secret, attempts, attempts == 1 ? "" : "s");
    return 0;
}
