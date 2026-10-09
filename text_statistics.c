#include <ctype.h>
#include <stdio.h>

int main(void)
{
    int character;
    int in_word = 0;
    unsigned long characters = 0;
    unsigned long words = 0;
    unsigned long lines = 0;

    printf("Enter text (press Ctrl+Z then Enter on Windows to finish):\n");

    while ((character = getchar()) != EOF)
    {
        characters++;
        if (character == '\n')
        {
            lines++;
        }

        if (isspace((unsigned char)character))
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            words++;
            in_word = 1;
        }
    }

    printf("\nCharacters: %lu\n", characters);
    printf("Words: %lu\n", words);
    printf("Lines: %lu\n", lines);
    return 0;
}
