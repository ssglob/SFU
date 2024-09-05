# q1.py

#
# Full Name:
#  SFU ID #:
# SFU Email:
#
'''Put your answer to this question in q1.py.

Write a program that asks the user for their name and age, and then prints a message saying how old they'll be in 25 years. Use f-strings to print the output.

For example:

What's your name? Elon
How old are you? 51

Hi Elon! In 25 years it will be 2049 and you'll be 76 years old.
You don't need to do any error checking: assume a sensible name and integer age are entered.'''
# ... put your answer to question 1 here ...
name = input("What's your name? ")
age = input("How old are you? ")
print(f"Hi {name}! In 25 years it will be 2049 and you will be {int(age) + 25:,} years old.")