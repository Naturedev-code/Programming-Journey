#include <stdio.h>
#include <string.h>
int main()
{
  int  o;
  char V[10];
  double x,y; 
  
  do
  {
    printf("Enter two numbers: ");
  scanf("%lf%lf", &x, &y);

    printf("Choose Following Operator Multiply=1,Divide=2,Subraction=3,Addition=4: ");
    scanf("%d", &o);
    if (o == 1)
    {
      printf("The Multiplication of respective numbers is: %lf\n", x * y); // Multiplication
    }
    else if (o == 2)
    {
      printf("The divison of respective numbers is: %lf\n", x / y); // Division
    }
    else if (o == 3)
    {
      printf("The difference of respective numbers is: %lf\n", x - y); // Subraction
    }
    else if (o == 4)
    {
      printf("The addition of respective numbers is: %lf\n", x + y); // Addition
    }
    else
    {
      printf("Invalid\n");
    }
    printf("Do you want to calcualte again? Y/N: ");
    scanf("%s", V);
  }

 while (strcmp(V, "Y") == 0 || strcmp(V, "y") == 0);

return 0;
}