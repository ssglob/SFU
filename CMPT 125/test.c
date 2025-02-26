#include <stdio.h>
#include <math.h>

int main() {
    int numRows;
    double startAngle, angleStep;

    // Request user input
    printf("Enter the number of rows (max 35): ");
    scanf("%d", &numRows);
    if (numRows > 35) {
        printf("Error: Number of rows cannot exceed 35.\n");
        return 1;
    }

    printf("Enter the starting angle (in degrees): ");
    scanf("%lf", &startAngle);

    printf("Enter the change in angle between successive rows (in degrees): ");
    scanf("%lf", &angleStep);

    // Print the table header
    printf("\n%14s%14s%14s\n", "Angle (deg)", "Sine", "Cosine");

    // Generate and print table rows
    for (int i = 0; i < numRows; i++) {
        double angle = startAngle + i * angleStep;
        double angleRad = angle * M_PI / 180.0; // Convert angle to radians
        double sine = sin(angleRad);
        double cosine = cos(angleRad);

        // Print row with formatted output
        printf("%14.2f%14.4f%14.4f\n", angle, sine, cosine);
    }

    return 0;
}
