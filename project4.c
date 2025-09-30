#include<stdio.h>
int main(){
    double num1, num2;
    printf("enter first number:");
    scanf("%lf", &num1);
    printf("enter second number");
    scanf("&lf", &num2);
    printf("/nsum =  &.2lf/n", num1 + num2);
    printf("difference = &.2lf/n", num1 - num2);
    printf("product = &.lf/n", num1 * num2);
if (num2 != 0){
    printf("quotient = &.2lf/n", num1 / num2);
} else {
   printf("quotient = undefined (division by zero)/n");
}
return 0;
}
