# q5.py

#
# Full Name: Edward Li Xuan Luo
#  SFU ID #: 301628166
# SFU Email:ell13@sfu.ca
#

# ... put your answer to question 5 here ...
def rand_char():
    import random
    return random.choice('/\\')

n = int(input('How many lines? '))
for integer in range(n):
    for integers1 in range(2*n):
        print(rand_char(), end = '')
    if integer != n-1:
        print('\n')