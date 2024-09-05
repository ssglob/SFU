# q3.py

#
# Full Name:
#  SFU ID #:
# SFU Email:
#
'''Put your answer to this question in q3.py.

Write a program that asks the user to enter a message and a box character, and then prints the message in a box made from the box character. Print it in exactly the style shown in the examples.

For example:

What do you want your sign to say? Code Carefully
What character do you want for the box? !

!!!!!!!!!!!!!!!!!!
! Code Carefully !
!!!!!!!!!!!!!!!!!!
Or:

What do you want your sign to say? SFU
What character do you want for the box? %

%%%%%%%
% SFU %
%%%%%%%
Make sure your box has exactly the same format as shown. Note that there is one space before the message, and one space after the message.

Assume the user enters a single character for the box character.'''
# ... put your answer to question 3 here ...
text = input("What do you want your sign to say? ")
char = input("What character do you want for the box? ")
print(f"{(len(text) + 4) * char}\n{char + " " + text + " " + char}\n{(len(text) + 4) * char}")