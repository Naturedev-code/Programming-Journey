// STUDENT MANAGEMENT SYSTEM
#include <stdio.h>
#include <string.h>

// Reads marks and accepts only numbers between 0 and 100.
float read_marks(const char *subject)
{
    float marks;

    while (1)
    {
        printf("Enter marks for %s (0-100): ", subject);

        // scanf returns 1 when the user enters a valid number.
        if (scanf("%f", &marks) == 1 && marks >= 0 && marks <= 100)
        {
            return marks; // Return the valid marks.
        }

        // Display an error when marks are greater than 100 or invalid.
        printf("Invalid marks. Please enter a value between 0 and 100.\n");

        // Remove invalid input before asking the user again.
        while (getchar() != '\n');
    }
}

struct student
{
    char fname[50]; // First name
    char lname[50];
    int Rollno;
    float science;  // subject
    float maths;    // subject
    float computer; // subject

    float total;
    float percentage;
    char grade[50];
};
int main()
{
    int i, n;
    printf("Enter Number of student: ");
    scanf("%d", &n);
      struct student x[n];
    
    for (i = 0; i < n; i++)
    {
        printf("Reading Student Data for student no. %d\n", i + 1);
        printf("Enter Student's First Name:\n");
        scanf("%s", x[i].fname);
         printf("Enter Student's last Name:\n");
        scanf("%s", x[i].lname);
        printf("Enter Student's Roll no:\n");
        scanf("%d", &x[i].Rollno);

        // Use read_marks so every subject is limited to 0-100.
        x[i].science = read_marks("Science");
        x[i].maths = read_marks("Maths");
        x[i].computer = read_marks("Computer");
        
    }
    printf("\n");
    for (i = 0; i < n; i++)
    {
        x[i].total = x[i].science + x[i].maths + x[i].computer;
        x[i].percentage = x[i].total / 300 * 100;
        if (x[i].percentage >= 90)
        {
            strcpy(x[i].grade, "A+");
        }
        else if (x[i].percentage >= 80)
        {
            strcpy(x[i].grade, "A");
        }
        else if (x[i].percentage >= 70)
        {
            strcpy(x[i].grade, "B+");
        }
        else if (x[i].percentage >= 60)
        {
            strcpy(x[i].grade, "B");
        }
        else if (x[i].percentage >= 50)
        {
            strcpy(x[i].grade, "C+");
        }
        else if (x[i].percentage >= 40)
        {
            strcpy(x[i].grade, "C");
        }

        else
            {
                strcpy(x[i].grade, "F");
            }
    }
    printf("\n===============================================================\n");
    printf("                    STUDENT RESULT SUMMARY\n");
    printf("===============================================================\n");
    printf("| %-3s | %-20s | %-6s | %-7s | %-6s | %-8s | %-7s | %-6s | %-5s |\n",
           "No.", "Name", "Roll", "Science", "Maths", "Computer",
           "Total", "Percent", "Grade");
    printf("|-----|----------------------|--------|---------|--------|----------|---------|--------|-------|\n");

    for (i = 0; i < n; i++)
    {
        char full_name[101];

        // snprintf safely combines the first and last names without exceeding full_name's size.
        snprintf(full_name, sizeof(full_name), "%s %s", x[i].fname, x[i].lname);
        printf("| %-3d | %-20s | %-6d | %7.2f | %6.2f | %8.2f | %7.2f | %6.2f%% | %-5s |\n",
               i + 1, full_name, x[i].Rollno, x[i].science, x[i].maths, 
               x[i].computer, x[i].total, x[i].percentage, x[i].grade);
    }

    printf("===============================================================\n");
}

/*
Format examples:
%3d   // right-aligned integer
%-3d  // left-aligned integer
%7.2f // floating-point number, width 7, 2 decimal places
%-20s // left-aligned string, width 20
*/