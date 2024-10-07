#
# Full Name: Edward Li Xuan Luo
#  SFU ID #: 301628166
# SFU Email:ell13@sfu.ca
#

#
# Credits for this entire assignment: https://docs.python.org/3/library/turtle.html (the turtle graphics documentation)
#

#
# import the turtle module
# import math for question 3
# import random for question 7
#
import turtle as t
import math
import random as r
#
#speed up drawing
#
t.speed('fastest')
t.hideturtle()

#
# define polygon (question 1)
#
def polygon(n,size):
    #
    # helpful error message if n is less than 3 (the polygon has less than 3 sides)
    #
    if n<3:
        print("Not enough sides for a polygon!")
        return
    #
    # helpful ereror message if size <= 0
    #
    if size<=0:
        print("Sides are not long enough!")
        return
    #
    # define angle
    #
    angle = 360/n

    #
    # for loop to create the polygon
    #
    for num in range(n):
        #
        # make the turtle go forward until the line is of length size
        #
        t.forward(size)
        #
        # turn the angle
        #
        t.left(angle)

#
# define jump_to (question 2)
#
def jump_to(x,y):
    #
    # make the pen go to (x,y) (lift the pen before doing that)
    #
    t.up()
    t.goto(x,y)
    #
    # return the pen to down position
    #
    t.down()

#
# define jump_to_test (question 2)
#
def jump_to_test():
    #
    # define arguments to be passed to polygon
    #
    sides = 5
    length = 50

    #
    # since length is 50 we should move a larger distance than that, say 100
    # create a list with all the coordinates of where we want the turtle to jump so that we can directly use it
    #
    jumps = [(-50,50),(50,-50),(50,50),(-50,-50)]

    #
    #now draw the 4 pentagons
    #
    for num in range(4):
        #
        # jumps[num][0] returns the x coordinate for the polygon that we are on, and jumps[num][1] returns the y cooridnate for the polygon we are on
        # Example: first polygon: num = 0, jumps[num] = (-50,50)   jumps[num][0] = -50, jumps[num][1] = 50
        # The turtle jumps to (-50, 50) to draw the polygon, and each polygon is at least 100 units away from each other
        #
        jump_to(jumps[num][0],jumps[num][1])
        polygon(sides,length)

#
# define circle (question 3)
#
def circle(radius):
    sides = 100
    length = 2*radius*math.sin(math.pi/sides)
    polygon(sides,length)

#
# define circle_test (question 3)
#
def circle_test():
    #
    # set an initial radius of 100, 
    # we want to draw the circle around the center so we set the position down 100 because that is the radius
    #
    cur_rad = 100
    start_pos = (0,-100)

    #
    # for loop to draw the 10 circles
    #
    for num in range(10):
        #
        # Move up from the starting position by 10 units every loop and every circle, decrease cur_rad by 10 every loop as well
        #
        jump_to(start_pos[0], start_pos[1] + 10*num)
        circle(cur_rad - 10*num)

#
# define eye (question 4)
#
def eye(radius):
    #
    # draw the pupil
    #
    t.begin_fill()
    circle(radius/2)
    t.end_fill()

    #
    # draw the rest of the eye
    #
    circle(radius)

#
# define eye_test (question 4)
#
def eye_test():
    #
    # draw the first eye to the left 55 units
    #
    jump_to(-55,0)
    eye(50)
    
    # 
    # draw the second eye to the right 55 units
    #
    jump_to(55,0)
    eye(50)

#
# define nose (question 5)
#
def nose(size):
    #
    # draw the bottom of the nose
    #
    t.forward(size/2)
    #
    # 45 degrees the other way
    #
    t.left(135)
    #
    #draw the rest of the nose
    #
    t.forward(size)

#
# define mouth (question 6)
#
def mouth(size, style):
    if type(style) == str:
        if style == 'happy':
            #
            # draw \/
            #
            t.setheading(-45)
            t.forward(size)
            t.setheading(45)
            t.forward(size)
            t.setheading(0)
            #
            # return to end the function after, since we don't need to run the rest of the function after drawing the expression, same with the others
            #
            return
        
        if style == 'sad':
            #
            # draw /\
            #
            t.setheading(45)
            t.forward(size)
            t.setheading(-45)
            t.forward(size)
            t.setheading(0)
            return
        
        if style == 'surprised':
            circle(size/2)
            return
    #
    # if style is not valid/isn't specified draw neutral face
    # don't need return since it's the end of the function
    #
    t.setheading(0)
    t.forward(size)

#
# define head (question 7)
#
def head(size):
    #
    # draw eyes
    #
    eye_size = size/8
    #
    # move the turtle eye_size + 2 away from the center, draw an eye, then go on the other side and draw another eye
    #
    jump_to(t.xcor()-eye_size-2,t.ycor())
    print(t.pos())
    eye(eye_size)
    # 
    # Move turtle to where it was before
    #
    jump_to(t.xcor()+eye_size+2,t.ycor())
    #
    # draw the other eye
    #
    jump_to(t.xcor()+eye_size+2,t.ycor())
    eye(eye_size)
    #
    # Move the turtle back again
    #
    jump_to(t.xcor()-eye_size-2,t.ycor())
    #
    # s for style, select a random style with r(random module)
    #
    s = r.choice(['happy', 'sad', 'surprised', 'neutral'])
    #
    # draw a circle with radius size for the outline of the head
    #
    circle(size)
eye_test()
#
# Just so that the window isn't removed right away, remove before turning in
#
t.mainloop()