#include <stdio.h>
#include <math.h>

void main(){
    float s;
    float L;
    printf("enter the length of each side of the equilateral triangle: ");
    scanf("%f",&s);
    printf("enter the length of the triangular prism: ");
    scanf("%f",&L);
    float V = L*s*s*sqrt(3) / 4.0;
    printf("The volume of the triangular prism is %0.2f cubic centimeters",V);
}