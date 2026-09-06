#include<stdio.h>

int main(){
    int n, originalNum, reversedNum = 0, remainder, check;
    
    do{
        printf("Enter the number: ");
        scanf("%d", &n);
        
        originalNum = n;
        
  
        while(n > 0){
            remainder = n % 10;
            reversedNum = reversedNum * 10 + remainder;
            n = n / 10;
        }
      
        if(originalNum == reversedNum){
            printf("%d is a PALINDROME\n", originalNum);
        } else {
            printf("%d is NOT a palindrome\n", originalNum);
        }
        
        reversedNum = 0;  
        printf("Do you want to check palindrome again? (Y=1, N=0): ");
        scanf("%d", &check);
    }while(check == 1);
    
    return 0;
}