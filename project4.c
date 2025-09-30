#include<stdio.h>
int main(){
    int celsius;
    int fahrenheit;
    printf("enter temperature in celsius:");
    scanf("%f", &celsius);
    fahrenheit = (celsius * 9/5) + 32;
    printf("in fahrenheit: %.1f/n", fahrenheit);
    
    printf("enter temperature in fahrenheit:");
    scanf("%f", &fahrenheit);
    celsius = (fahrenheit - 32) * 5/9;
    printf("in celsius: %.1f/n", celsius);
return 0;
}
