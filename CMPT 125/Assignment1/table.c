#include <stdio.h>
#include <math.h>
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