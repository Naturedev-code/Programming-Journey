#include <stdio.h>
#include <stdlib.h>
int main()
{
  int numgen, user;
  numgen = rand() % 200 + 1; // Generates a random number from 1-200;
  printf("Choose a number from 1-200: ");
  scanf("%d", &user);
  while (user != numgen)
  { // Implies only when the user entered value is not equal to the generated value;
    if (user > numgen)
      printf("Too High! Try again: ");
    else
      printf("Too Low! Try agian: ");
    scanf("%d", &user); // Reads Value given by user ifthe user entered value is not equal to the generated value;
  }
  printf("Yes!the number is %d", numgen);
  return 0;
}