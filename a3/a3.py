# a3.py

#
# Full Name: Edward Li Xuan Luo
#  SFU ID #: 301628166
# SFU Email: ell13@sfu.ca
#

#
# Source used for this assignment: https://docs.python.org/3/library/turtle.html
#

#
# import turtle and math for question 4+
# import a2 for question 6+
#
import turtle as t
import math
import a2
t.tracer(0)
t.hideturtle()
#
# define is_int (question 1)
#

def is_int(n):
    """ Returns True of n is an int, and False otherwise.
    >>> is_int('5')
    True
    >>> is_int('5.6')
    False
    """
    try:
        int(n)
        return True
    except ValueError:
        return False

#
# define ask_int1 (question 1)
#

def ask_int1(prompt):
    #
    # while loop, if is_int(a) returns false then keep asking and getting input
    #
    a = ''
    while not is_int(a):
        a = input(prompt)
    return int(a)

#
# define ask_int2 (question 2)
#

def ask_int2(prompt):
    #
    # same as ask_int1 but with error messages
    #
    a = ''
    while not is_int(a):
        a = input(prompt)
        if not is_int(a):
            print(f'Sorry, I don\'t know what int "{a}" is. Please try again.')
    return int(a)

#
# define ask_int_between (question 3)
#

def ask_int_between(lo,hi):
    #
    # while loop, if user enters invalid int or int not in 
    # between lo and hi print error and ask again
    #
    a = ''
    while not is_int(a) or a<lo or a>hi:
        a = input(f'Enter a number between {lo} and {hi}: ')
        if not is_int(a):
            print(f'Please try again: I don\'t know what int "{a}" is.')
            #
            # skip the other conditionals because int(a) will return an error
            #
            continue
        a = int(a)
        if a<lo:
            print(f'Please try again: {a} is too low.')
        elif a>hi:
            print(f'Please try again: {a} is too high.')
    return a

#
# define pentagon_at (question 4)
#

def pentagon_at(x, y, size):
    t.penup()
    t.goto(x,y)
    t.pendown()
    #
    # orig_angle is the angle it started on, angle is the angle that I change to draw the pentagon
    #
    orig_angle = t.heading()
    angle = t.heading()
    for i in range(5):
        t.setheading(angle)
        t.forward(size)
        angle += 360/5
    t.setheading(orig_angle)

#
# define pentagonal_flower(x,y,size) (question 5)
#

def pentagonal_flower(x, y, size):
    n = ask_int_between(5,50)
    #
    # for loop to draw all the pentagons, using pentagon_at(x,y,size)
    #
    for i in range(n):
        pentagon_at(x,y,size)
        t.right(360/n)

#
# define draw_figure_rand(size) (question 6)
#

def draw_figure_rand(size):
    a2.stick_figure(size)

#
# define figure_row(x, y, n) (question 7)
#

def figure_row(x, y, n):
    #
    # get the screen's width so that we can calculate the spacing we need
    # multiply it by 2 as that is the real width of the screen
    #
    spacing = t.screensize()[0] * 2
    #
    # subtract spacing by the distance from the left border to x so we know how much 
    # space we have on the right of (x,y)
    #
    spacing -= t.screensize()[0]+x
    #
    # divide spacing by n+1 to fit in n stick figures and have a bit of space
    #
    spacing = spacing/(n+1)
    size = 15
    #
    # set a min for spacing so that the stick figures don't overlap
    #
    if spacing<=size*2:
        spacing += size*2
    #
    # now just draw the row of stick figures
    # need to move turtle to draw stick figure with (x,y) as the bottom left corner
    #
    position = (x+size+math.sin(math.pi/4)*size/4, y+size+math.sin(math.pi/4)*size/2)
    for i in range(n):
        #
        # update position every loop
        #
        a2.jump_to(position[0], position[1])
        draw_figure_rand(size)

        t.setheading(0)
        position = (position[0]+spacing, position[1])
        
#
# define figure_grid(x, y, r, c) (question 8)
#

def figure_grid(x, y, r, c):
    #
    # since figure_row decides spacing based on x, we only need to decide spacing based on y
    #
    spacing = t.screensize()[1] * 2
    #
    # subtract spacing by how far y is from the top of the screen
    #
    spacing -= t.screensize()[1]-y
    spacing = spacing/(r+1)
    #
    # want to start further down since (x,y) is the bottom left corner
    #
    position = (x,y-spacing)
    #
    # loop through all the rows and draw a row of stick figures
    #
    for i in range(r):
        figure_row(position[0],position[1],c)
        position = (position[0],position[1]-spacing)
figure_row(-400,0,100)

t.update()
t.mainloop()