# q2.py

#
# Full Name: Edward Li Xuan Luo
#  SFU ID #: 301628166
# SFU Email:ell13@sfu.ca
#
'''Put your answer to this question in q2.py.

Write a program that converts feet 
 to meters 
 using the formula 
. Ask the user to enter a measurement in feet, and then print it in meters:

How many feet? 21
21.0 is about 6.4 meters
Use f-strings to format your output. It should work for any number the user enters. Make your output the same as shown. The value for both the feet and meters should be printed to exactly 1 decimal place.

You can assume the user enters a valid number.'''
# ... put your answer to question 2 here ...
feet = float(input("How many feet? "))
meters = feet * .3048
print(f"{feet:,.1f} feet is about {meters:,.1f} meters.")