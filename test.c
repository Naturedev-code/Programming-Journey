#include <stdio.h>
#include <string.h>

int main(void)
{
    char text[100];
    size_t length;

    printf("Enter a word to sort alphabetically: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
    {
        printf("Unable to read input.\n");
        return 1;
    }

    text[strcspn(text, "\n")] = '\0';
    length = strlen(text);

    for (size_t pass = 0; pass + 1 < length; pass++)
    {
        int changed = 0;
        for (size_t index = 0; index + 1 < length - pass; index++)
        {
            if (text[index] > text[index + 1])
            {
                char temporary = text[index];
                text[index] = text[index + 1];
                text[index + 1] = temporary;
                changed = 1;
            }
        }
        if (!changed)
        {
            break;
        }
    }

    printf("Sorted text: %s\n", text);
    return 0;
}
