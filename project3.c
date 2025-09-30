#include<stdio.h>
int main(){
    int a, b;
    printf("enter two number");
    scanf("%d %d", &a, &b);
    if (a==0){
       printf("error: invalid if divided by zero");}
    else{
       printf("sum = %d", a + b);
       printf("difference = %d", a - b);
       printf("product = %d", a * b);
       printf("quotient = %d", a / b);}
return 0;
}
