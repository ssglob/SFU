#include <stdio.h>

void main(){
    float T_start = -10.2;
    float T_room = 21.8;
    printf("enter the number of full hours since the power failed: ");
    int hours;
    int minutes;
    scanf("%d",&hours);
    printf("enter the number of additional minutes since the power failed: ");
    scanf("%d",&minutes);
    float power_off = minutes/60.0 + hours/1.0;
    float cur_T = T_start/1.0 + 0.05 * power_off * (T_room-T_start);
    printf("The power has been off for %0.2lf hours\n",power_off);
    printf("Estimated present temperature in freezer is %0.2lf degrees Celsius",cur_T);
}