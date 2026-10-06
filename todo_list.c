#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TITLE_LENGTH 100

typedef struct
{
    char title[MAX_TITLE_LENGTH];
    int completed;
} Task;

static void trim_newline(char *text)
{
    text[strcspn(text, "\n")] = '\0';
}

static void print_tasks(const Task tasks[], size_t task_count)
{
    if (task_count == 0)
    {
        printf("No tasks yet.\n");
        return;
    }

    for (size_t i = 0; i < task_count; i++)
    {
        printf("%zu. [%c] %s\n", i + 1, tasks[i].completed ? 'x' : ' ',
               tasks[i].title);
    }
}

static int read_task_number(size_t task_count, size_t *task_index)
{
    char input[32];
    char *end;
    unsigned long number;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return 0;
    }

    number = strtoul(input, &end, 10);
    if (end == input || (*end != '\n' && *end != '\0') ||
        number == 0 || number > task_count)
    {
        return 0;
    }

    *task_index = (size_t)number - 1;
    return 1;
}

int main(void)
{
    Task tasks[MAX_TASKS];
    size_t task_count = 0;
    char command[16];

    printf("To-Do List\n");
    printf("Commands: add, list, complete, delete, quit\n");

    for (;;)
    {
        printf("\nCommand: ");
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            printf("\nInput ended. Goodbye.\n");
            return 0;
        }
        trim_newline(command);

        if (strcmp(command, "add") == 0)
        {
            if (task_count == MAX_TASKS)
            {
                printf("The task list is full.\n");
                continue;
            }

            printf("Task title: ");
            if (fgets(tasks[task_count].title,
                      sizeof(tasks[task_count].title), stdin) == NULL)
            {
                printf("Input ended. Task was not added.\n");
                return 1;
            }
            trim_newline(tasks[task_count].title);
            if (tasks[task_count].title[0] == '\0')
            {
                printf("Task title cannot be empty.\n");
                continue;
            }

            tasks[task_count].completed = 0;
            task_count++;
            printf("Task added.\n");
        }
        else if (strcmp(command, "list") == 0)
        {
            print_tasks(tasks, task_count);
        }
        else if (strcmp(command, "complete") == 0 ||
                 strcmp(command, "delete") == 0)
        {
            size_t task_index;

            print_tasks(tasks, task_count);
            if (task_count == 0)
            {
                continue;
            }

            printf("Task number: ");
            if (!read_task_number(task_count, &task_index))
            {
                printf("Invalid task number.\n");
                continue;
            }

            if (strcmp(command, "complete") == 0)
            {
                tasks[task_index].completed = 1;
                printf("Task completed.\n");
            }
            else
            {
                for (size_t i = task_index; i + 1 < task_count; i++)
                {
                    tasks[i] = tasks[i + 1];
                }
                task_count--;
                printf("Task deleted.\n");
            }
        }
        else if (strcmp(command, "quit") == 0)
        {
            printf("Goodbye.\n");
            return 0;
        }
        else if (command[0] == '\0')
        {
            printf("Please enter a command.\n");
        }
        else
        {
            printf("Unknown command. Use add, list, complete, delete, or quit.\n");
        }
    }
}
