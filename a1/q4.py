# q4.py

#
# Full Name:
#  SFU ID #:
# SFU Email:
#
'''
Here is a sample run:

+-----------------------+
| Welcome to CyberCone! |
+-----------------------+

How many scoops do you want? 3
Ok, 3 scoops it is.

What is the radius of a scoop in cm? 2.1
Each scoop is radius 2.10cm

What is the height of the cone in cm? 4.22
Cone height is 4.22cm

        Cost of your 3-scoop cone: $13.78
Total height of your 3-scoop cone: 16.82cm
Some important details:

Print the title box at the top exactly as shown.
You can assume that the number entered by the user are always sensible, i.e. the number of scoops is an integer greater than 0, and the scoop radius and cone height are greater than 0.
The scoop radius, cone height, and cost should all be printed to exactly 2 decimal digits, as shown the sample run.
The formulas for the volumes of spheres and cones can be found online.'''
# ... put your answer to question 4 here ...
print("+-----------------------+\n| Welcome to CyberCone! |\n+-----------------------+")

scoops = int(input("How many scoops do you want? "))
print(f"Ok, {scoops} scoops it is.")

rad = float(input("What is the radius of a scoop in cm? "))
print(f"Each scoop is radius {rad:,.2f}cm")

height = int(input("What is the height of the cone in cm? "))
print(f"Cone height is {height:,.2f}cm")

totalheight = 