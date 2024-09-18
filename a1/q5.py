# q5.py

#
# Full Name: Edward Li Xuan Luo
#  SFU ID #: 301628166
# SFU Email:ell13@sfu.ca
#

# ... put your answer to question 5 here ...
#provided function in the question
def rand_char():
    import random
    return random.choice('/\\')

#ask for input
n = int(input('How many lines? '))
#loop n times to print something that has n lines
for integer in range(n):
    #loop n * 2 times to print 2n of random characters (like in the description of the problem)
    for integers1 in range(2*n):
        print(rand_char(), end = '')
    #until the last loop, print a line break to separate each line
    #don't want it on the last loop because it will print an extra unneeded line
    if integer != n-1:
        print('\n')