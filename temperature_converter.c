#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const double minimum_celsius = -273.15;
    const double minimum_fahrenheit = -459.67;
    char input[128];
    char *end;
    char unit;
    double value;
    double celsius;
    double fahrenheit;
    double kelvin;

    printf("Enter a temperature and unit (C, F, or K), for example 25 C: ");
    fflush(stdout);
    if (fgets(input, sizeof(input), stdin) == NULL ||
        (strchr(input, '\n') == NULL && getchar() != EOF))
    {
        printf("Unable to read a complete temperature.\n");
        return 1;
    }

    errno = 0;
    value = strtod(input, &end);
    if (end == input || errno == ERANGE || !isfinite(value))
    {
        printf("Please enter a finite number followed by C, F, or K.\n");
        return 1;
    }
    while (isspace((unsigned char)*end)) end++;
    unit = (char)toupper((unsigned char)*end);
    if (unit != 'C' && unit != 'F' && unit != 'K')
    {
        printf("Unknown unit. Use C, F, or K.\n");
        return 1;
    }
    end++;
    while (isspace((unsigned char)*end)) end++;
    if (*end != '\0')
    {
        printf("Unexpected text after the unit.\n");
        return 1;
    }

    /* Validate in the original scale to preserve the absolute-zero boundary. */
    if ((unit == 'C' && value < minimum_celsius) ||
        (unit == 'F' && value < minimum_fahrenheit) ||
        (unit == 'K' && value < 0.0))
    {
        printf("Temperature cannot be below absolute zero.\n");
        return 1;
    }

    if (unit == 'F') celsius = (value - 32.0) / 1.8;
    else if (unit == 'K') celsius = value - 273.15;
    else celsius = value;

    fahrenheit = unit == 'F' ? value : celsius * 1.8 + 32.0;
    kelvin = unit == 'K' ? value : celsius + 273.15;
    /* A valid absolute-zero input can round slightly below zero in Kelvin. */
    if (kelvin <= 0.0) kelvin = 0.0;
    if (!isfinite(fahrenheit) || !isfinite(kelvin))
    {
        printf("Conversion is outside the supported numeric range.\n");
        return 1;
    }

    printf("Celsius: %.2f C\n", celsius);
    printf("Fahrenheit: %.2f F\n", fahrenheit);
    printf("Kelvin: %.2f K\n", kelvin);
    return 0;
}
