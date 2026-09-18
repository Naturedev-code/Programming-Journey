#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

static void remove_newline(char *text)
{
    text[strcspn(text, "\n")] = '\0';
}

int main(void)
{
    char filename[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    char line[BUFFER_SIZE];
    FILE *file;

    printf("Enter a file name: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL)
    {
        printf("Unable to read the file name.\n");
        return 1;
    }
    remove_newline(filename);

    if (filename[0] == '\0')
    {
        printf("The file name cannot be empty.\n");
        return 1;
    }

    printf("Enter a message to save: ");
    if (fgets(message, sizeof(message), stdin) == NULL)
    {
        printf("Unable to read the message.\n");
        return 1;
    }

    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Unable to open \"%s\" for writing.\n", filename);
        return 1;
    }

    if (fputs(message, file) == EOF)
    {
        printf("Unable to write to \"%s\".\n", filename);
        fclose(file);
        return 1;
    }

    if (fclose(file) != 0)
    {
        printf("Unable to close \"%s\" after writing.\n", filename);
        return 1;
    }

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Unable to open \"%s\" for reading.\n", filename);
        return 1;
    }

    printf("\nContents of \"%s\":\n", filename);
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    if (ferror(file))
    {
        printf("\nUnable to read from \"%s\".\n", filename);
        fclose(file);
        return 1;
    }

    if (fclose(file) != 0)
    {
        printf("\nUnable to close \"%s\" after reading.\n", filename);
        return 1;
    }

    return 0;
}
