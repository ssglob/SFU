#include <stdio.h>
/*
The program takes the number of full hours since the power failure and the number of minutes
since the power failure as separate inputs. It uses the total amount of time since the power
failure to calculate the final temperature of the freezer based on the defined constants and 
inputs. It prints the current temperature and the final temperature of the freezer, both
rounded to 2 decimal places.

T_start is the temperature of the freezer before the power failure.
T_room is the temperature of the room.
*/
#define T_start -10.2
#define T_room 21.8
void main(){
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