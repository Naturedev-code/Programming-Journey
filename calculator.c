#include <stdio.h>

static int read_double(const char *prompt, double *value)
{
    printf("%s", prompt);
    return scanf("%lf", value) == 1;
}

int main(void)
{
    double first;
    double second;
    double result;
    char operation;

    printf("Simple Calculator\n");
    printf("=================\n");
    if (!read_double("Enter the first number: ", &first) ||
        !read_double("Enter the second number: ", &second))
    {
        printf("Invalid number entered.\n");
        return 1;
    }

    printf("Choose an operation (+, -, *, /): ");
    if (scanf(" %c", &operation) != 1)
    {
        printf("Invalid operation.\n");
        return 1;
    }

    switch (operation)
    {
    case '+':
        result = first + second;
        break;
    case '-':
        result = first - second;
        break;
    case '*':
        result = first * second;
        break;
    case '/':
        if (second == 0.0)
        {
            printf("Division by zero is not allowed.\n");
            return 1;
        }
        result = first / second;
        break;
    default:
        printf("Unknown operation.\n");
        return 1;
    }

    printf("Result: %.2f\n", result);
    return 0;
}
