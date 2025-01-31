#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
/*
The program takes the number of rows in the table, the angle to start with, and the increment
between each angle as separate inputs. It calculates the sine and cosine of the angle in each
iteration, which gets increased by the increment, then prints each value in columns (angle is
rounded to 2 decimal places, sine and cosine to 4) that are
each 14 characters wide. The number of rows printed is the inputted numberOfRows + 1 (to 
include the title).
*/
int main ()
{
	/* ADD CODE HERE TO
       declare and local variables and constants
       input user specified values
	   numberOfRows: number of rows in the table must be 0<numberOfRows <= 35
	   starting angle in degrees
	   difference in angle between successive rows
       print the titles for each row in the table */
    int numberOfRows;
    int countData;
    float angle;
    float increment;
    printf("Enter the number of rows in the table to be produced\nThe number of rows must be between 0 and 35\n");
    scanf("%d",&numberOfRows);
    printf("Enter the starting angle in degrees (e.g. 3.45)\n");
    scanf("%f",&angle);
    printf("Enter increment in angle between rows in degrees (e.g. 0.5)\n");
    scanf("%f",&increment);
    printf("%14s%14s%14s\n","Angle","Sine","Cosine");


	/* This is a loop executed once for each row of the table
	   numberOfRows  rows will be printed */
    for (countData = 0; countData < numberOfRows; countData++ )
    {
		//ADD CODE HERE TO
		//print the (countData+1)st line of the table
        float radians = M_PI * angle / 180;
        printf("%14.2f%14.4f%14.4f\n",angle,sin(radians),cos(radians));
        angle = angle + increment;

    }
    return 0;
}