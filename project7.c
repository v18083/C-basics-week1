#include<stdio.h>
int main(){
    int a, b, c;
    printf("enter three number:");
    scanf("%d %d %d", &a, &b, &c);
    int largest = (a > b) ? (a > c ? a: c) : (b > c ? b : c);
    printf("the largest number is %d", largest);
return 0;
}
