#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void reverse_array(int *start, int *end)
{
    while (start < end)
    {
        int temporary = *start;
        *start = *end;
        *end = temporary;
        start++;
        end--;
    }
}

static void sort_array(int *start, int *end)
{
    for (int *outer = start; outer <= end; outer++)
    {
        for (int *inner = outer + 1; inner <= end; inner++)
        {
            if (*inner < *outer)
            {
                int temporary = *outer;
                *outer = *inner;
                *inner = temporary;
            }
        }
    }
}

int main(void)
{
    int count;
    int *numbers;
    int *current;
    int minimum;
    int maximum;
    long long total = 0;
    double median = 0.0;

    printf("How many integers do you want to enter? ");
    if (scanf("%d", &count) != 1 || count <= 0)
    {
        printf("Please enter a positive number of integers.\n");
        return 1;
    }

    if ((size_t)count > SIZE_MAX / sizeof(*numbers))
    {
        printf("Too many integers to allocate safely.\n");
        return 1;
    }

    numbers = malloc((size_t)count * sizeof(*numbers));
    if (numbers == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }

    printf("Enter %d integers:\n", count);
    for (current = numbers; current < numbers + count; current++)
    {
        if (scanf("%d", current) != 1)
        {
            printf("Invalid input. Please enter integers only.\n");
            free(numbers);
            return 1;
        }
    }

    minimum = *numbers;
    maximum = *numbers;

    for (current = numbers; current < numbers + count; current++)
    {
        if (*current < minimum)
        {
            minimum = *current;
        }
        if (*current > maximum)
        {
            maximum = *current;
        }
        total += *current;
    }

    sort_array(numbers, numbers + count - 1);
    if (count % 2 == 0)
    {
        /* Convert before adding to avoid overflowing an integer. */
        median = ((double)numbers[(count / 2) - 1] +
                  (double)numbers[count / 2]) / 2.0;
    }
    else
    {
        median = (double)numbers[count / 2];
    }

    reverse_array(numbers, numbers + count - 1);

    printf("\nMinimum: %d\n", minimum);
    printf("Maximum: %d\n", maximum);
    printf("Average: %.2f\n", (double)total / count);
    printf("Median: %.2f\n", median);
    printf("Numbers in descending order: ");

    for (current = numbers; current < numbers + count; current++)
    {
        printf("%d", *current);
        if (current < numbers + count - 1)
        {
            printf(" ");
        }
    }
    printf("\n");

    free(numbers);
    return 0;
}
