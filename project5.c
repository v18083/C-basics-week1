#include<stdio.h>
int main(){
    int num1, num2, result;
    char operation;

    printf("enter num1:");
    scanf("%f", &num1);

    printf("enter num2:");
    scanf("%f", &num2);

    printf("choose operation (+, -, *, /):");
    scanf("%f", &operation);
    
    switch (operation) {
           case '+':
                result = num1 + num2;
                break;
           case '-':
                result = num1 - num2;
                break;
           case '*':
                result = num1 * num2;
                break;
           case '/':
                if (num2 != 0){
                result = num1 / num2;
                } else {
                    printf("error: division by zero!/n");
                    return 1;
                }
                break;
           default:
                printf("error: invalid operation!/n");
                return 1;
     }
     printf("result = %.2f/n", result);
return 0;
}
