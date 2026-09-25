#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER 2147483647L

static int read_number(long *number)
{
    char input[128];
    char *end;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return 0;
    }
    if (strchr(input, '\n') == NULL && getchar() != EOF)
    {
        return 0;
    }

    errno = 0;
    *number = strtol(input, &end, 10);
    if (end == input || errno == ERANGE)
    {
        return 0;
    }
    while (isspace((unsigned char)*end))
    {
        end++;
    }

    return *end == '\0' && *number >= 0 && *number <= MAX_NUMBER;
}

static int is_prime(long number)
{
    if (number < 2)
    {
        return 0;
    }
    if (number % 2 == 0)
    {
        return number == 2;
    }

    /* A composite number has a factor at most its square root.
       Division avoids the overflow possible with divisor * divisor. */
    for (long divisor = 3; divisor <= number / divisor; divisor += 2)
    {
        if (number % divisor == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    long number;

    printf("Enter a whole number (0-%ld): ", MAX_NUMBER);
    fflush(stdout);
    if (!read_number(&number))
    {
        printf("Please enter one whole number from 0 to %ld.\n", MAX_NUMBER);
        return 1;
    }

    printf("%ld is %sprime.\n", number, is_prime(number) ? "" : "not ");
    return 0;
}
