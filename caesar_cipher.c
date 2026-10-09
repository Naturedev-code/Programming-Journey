#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_shift(void)
{
    char input[32];
    char *end;
    long shift;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return -1;
    }

    shift = strtol(input, &end, 10);
    while (isspace((unsigned char)*end))
    {
        end++;
    }

    if (end == input || *end != '\0' || shift < 0 || shift > 25)
    {
        return -1;
    }
    return (int)shift;
}

static void transform(char *text, int shift)
{
    for (char *character = text; *character != '\0'; character++)
    {
        if (isupper((unsigned char)*character))
        {
            *character = (char)('A' + (*character - 'A' + shift) % 26);
        }
        else if (islower((unsigned char)*character))
        {
            *character = (char)('a' + (*character - 'a' + shift) % 26);
        }
    }
}

int main(void)
{
    char operation[8];
    char text[256];
    int shift;

    printf("Encrypt or decrypt? (e/d): ");
    if (fgets(operation, sizeof(operation), stdin) == NULL ||
        (operation[0] != 'e' && operation[0] != 'E' &&
         operation[0] != 'd' && operation[0] != 'D'))
    {
        fprintf(stderr, "Please choose 'e' for encrypt or 'd' for decrypt.\n");
        return 1;
    }

    printf("Shift (0-25): ");
    shift = read_shift();
    if (shift < 0)
    {
        fprintf(stderr, "The shift must be a whole number from 0 to 25.\n");
        return 1;
    }

    if (operation[0] == 'd' || operation[0] == 'D')
    {
        shift = (26 - shift) % 26;
    }

    printf("Text: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
    {
        fprintf(stderr, "No text was provided.\n");
        return 1;
    }

    text[strcspn(text, "\n")] = '\0';
    transform(text, shift);
    printf("Result: %s\n", text);
    return 0;
}
