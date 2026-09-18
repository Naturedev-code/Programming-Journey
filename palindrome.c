#include <stdio.h>
#include <string.h>

int main(void)
{
    char text[101];
    size_t length;
    int is_palindrome = 1;

    printf("Enter a word or phrase: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
    {
        printf("Unable to read input.\n");
        return 1;
    }

    text[strcspn(text, "\n")] = '\0';
    length = strlen(text);

    for (size_t left = 0; left < length / 2; left++)
    {
        if (text[left] != text[length - left - 1])
        {
            is_palindrome = 0;
            break;
        }
    }

    printf("\"%s\" is %s palindrome.\n",
           text, is_palindrome ? "a" : "not a");
    return 0;
}
