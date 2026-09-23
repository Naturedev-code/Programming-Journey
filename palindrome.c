#include <stdio.h>
#include <ctype.h>
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

    size_t left = 0;
    size_t right = length;

    while (left < right)
    {
        while (left < right && !isalnum((unsigned char)text[left]))
        {
            left++;
        }
        while (left < right && !isalnum((unsigned char)text[right - 1]))
        {
            right--;
        }

        if (left < right &&
            tolower((unsigned char)text[left]) !=
                tolower((unsigned char)text[right - 1]))
        {
            is_palindrome = 0;
            break;
        }

        left++;
        right--;
    }

    printf("\"%s\" is %s palindrome.\n",
           text, is_palindrome ? "a" : "not a");
    return 0;
}
