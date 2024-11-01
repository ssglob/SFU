# a4.py

#
# Full Name: Edward Li Xuan Luo
#  SFU ID #: 301628166
# SFU Email: ell13@sfu.ca
#

#
# import turtle
#
import turtle as t

t.tracer(0)
t.hideturtle()

#
# define turtle_draw1(commands, step_size, turning_angle) (question 1)
#
def turtle_draw1(commands, step_size, turning_angle):
    t.pendown()
    for char in commands:
        if char == 'F':
            t.forward(step_size)
        elif char == 'L':
            t.left(turning_angle)
        elif char == 'R':
            t.right(turning_angle)

#
# define turtle_draw2(commands, step_size, turning_angle) (question 2)
#
def turtle_draw2(commands, step_size, turning_angle):
    t.pendown()
    for char in commands:
        if char == 'F' or char == 'G':
            t.forward(step_size)
        elif char == 'L' or char == '-':
            t.left(turning_angle)
        elif char == 'R' or char == '+':
            t.right(turning_angle)

#
# define turtle_draw3(commands, step_size, turning_angle) (question 3)
#
def turtle_draw3(commands, step_size, turning_angle):
    t.pendown()
    for char in commands:
        if char == 'F' or char == 'G':
            t.forward(step_size)
        elif char == 'L' or char == '-':
            t.left(turning_angle)
        elif char == 'R' or char == '+':
            t.right(turning_angle)
        elif char == 'U':
            t.penup()
        elif char == 'D':
            t.pendown()
        elif char == 'C':
            t.clear()
        elif char == '*':
            t.reset()

#define dragon_rule and repeat_rule (problem 4)
def dragon_rule(commands):
    r = ''
    for char in commands:
        if char == 'F':
            r += 'F+G'
        elif char == 'G':
            r += 'F-G'
        else:
            r += char
    return r

def repeat_rule(n, rule, start_commands):
    """Repeats the rule n times, beginning with start_commands.
    - n is an int greater than 0.

    - rule is a function (such as dragon_rule) that takes a string of commands 
    and returns a new string of commands.
    
    - start_commands is a string of commands.
    """
    result = start_commands
    for i in range(n):
        result = rule(result)
    return result

#
# define is_turtle_list(x) (question 5)
#
def is_turtle_list(x):
    if type(x) != list or len(x)!=3:
        return False
    if not type(x[0]) in [float,int] or not type(x[1]) in [float,int]:
        return False
    if x[0]<=0 or type(x[2])!= str:
        return False
    return True


t.update()
t.mainloop()