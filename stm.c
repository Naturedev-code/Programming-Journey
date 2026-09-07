// STUDENT MANAGEMENT SYSTEM
#include <stdio.h>
#include <string.h>

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
        printf("Enter Student's Marks For Science:\n");
        scanf("%f", &x[i].science);
        printf("Enter Student's Marks For Maths:\n");
        scanf("%f", &x[i].maths);
        printf("Enter Student's Marks For Computer:\n");
        scanf("%f", &x[i].computer);
        
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
    for (i = 0; i < n; i++)

    {
        printf("Displaying Record of Student No. %d\n", i + 1);
        printf("Name of Student: %s %s\n", x[i].fname,x[i].lname);
        printf("Rollno. of Student: %d\n", x[i].Rollno);
        printf("\n");
        printf("\n");
        printf("Marks of Science: %.2f\n", x[i].science);
        printf("Marks of Maths: %.2f\n", x[i].maths);
        printf("Marks of Computer: %.2f\n", x[i].computer);
        printf("\n");
        printf("\n");
        printf("Total Marks is: %.2f\n", x[i].total);
        printf("Total Percentage is: %.2f\n", x[i].percentage);
        printf("Grade is: %s\n", x[i].grade);
    }
}
