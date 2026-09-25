#include <stdio.h>
#include <stdlib.h>

struct Student
{
    char first_name[50];
    char last_name[50];
    int roll_number;
    float science;
    float mathematics;
    float computer;
};

static int read_marks(const char *subject, float *marks)
{
    while (1)
    {
        int status;
        int character;

        printf("Enter %s marks (0-100): ", subject);
        status = scanf("%f", marks);
        if (status == EOF)
        {
            return 0;
        }
        if (status == 1 && *marks >= 0.0f && *marks <= 100.0f)
        {
            return 1;
        }

        printf("Enter a valid mark between 0 and 100.\n");
        while ((character = getchar()) != '\n' && character != EOF)
        {
        }
        if (character == EOF)
        {
            return 0;
        }
    }
}

static const char *grade_for(float percentage)
{
    if (percentage >= 90.0f) return "A+";
    if (percentage >= 80.0f) return "A";
    if (percentage >= 70.0f) return "B+";
    if (percentage >= 60.0f) return "B";
    if (percentage >= 50.0f) return "C+";
    if (percentage >= 40.0f) return "C";
    return "F";
}

int main(void)
{
    int count;
    struct Student *students;

    printf("How many students? ");
    if (scanf("%d", &count) != 1 || count <= 0 || count > 100)
    {
        printf("Enter a number of students from 1 to 100.\n");
        return 1;
    }

    students = calloc((size_t)count, sizeof(*students));
    if (students == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }

    for (int index = 0; index < count; index++)
    {
        struct Student *student = &students[index];

        printf("\nStudent %d\n", index + 1);
        printf("First name: ");
        if (scanf("%49s", student->first_name) != 1)
        {
            printf("Invalid name.\n");
            free(students);
            return 1;
        }
        printf("Last name: ");
        if (scanf("%49s", student->last_name) != 1)
        {
            printf("Invalid name.\n");
            free(students);
            return 1;
        }
        printf("Roll number: ");
        if (scanf("%d", &student->roll_number) != 1 ||
            student->roll_number <= 0)
        {
            printf("Invalid roll number.\n");
            free(students);
            return 1;
        }

        if (!read_marks("Science", &student->science) ||
            !read_marks("Mathematics", &student->mathematics) ||
            !read_marks("Computer", &student->computer))
        {
            printf("Input ended before all marks were entered.\n");
            free(students);
            return 1;
        }
    }

    printf("\nStudent Result Summary\n");
    printf("%-4s %-25s %-8s %-8s %-8s %-8s %-10s %-5s\n",
           "No.", "Name", "Science", "Maths", "Computer",
           "Total", "Percent", "Grade");
    printf("----------------------------------------------------------------------------\n");

    for (int index = 0; index < count; index++)
    {
        const struct Student *student = &students[index];
        float total = student->science + student->mathematics +
                      student->computer;
        float percentage = total / 3.0f;
        char name[101];

        snprintf(name, sizeof(name), "%s %s",
                 student->first_name, student->last_name);
        printf("%-4d %-25s %8.2f %8.2f %8.2f %8.2f %9.2f%% %-5s\n",
               index + 1, name, student->science, student->mathematics,
               student->computer, total, percentage, grade_for(percentage));
    }

    free(students);
    return 0;
}
