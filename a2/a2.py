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
# this makes it so that we don't see the turtle drawing, and we update at the end to see whatever the turtle 
# drew, making it a lot faster.
#
t.hideturtle()
t.tracer(0,0)

#
# set t.colormode to 255 so that I can use random rgb values in question 8
#
t.colormode(255)

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
    # 45 degrees towards the left, so 90 + 45 = 135
    #
    t.left(135)
    #
    #draw the rest of the nose, slightly bigger than the bottom
    #
    t.forward(size/2 + size/4)

#
# define mouth (question 6)
#
def mouth(size, style):
    #
    # move the turtle left to make space to draw the mouth in the head
    # since it's going at an angle, we can use trigonometry, so import math
    # cos(angle) = x/hyp, so x = hyp*cos(angle), and angle = 45 (or pi/4 in radians) here and hyp = size
    # we also want to move the turtle up for happy to make space to draw the mouth in the head, down for sad
    # same thing as the x for happy and sad except using sin, and divide sin by 2 so that the drawing 
    # is centered around where the turtle was
    # we didn't divide the cos(pi/4) one by 2 because there are 2 x
    #
    import math
    if style == 'happy':
        jump_to(t.xcor()-size*math.cos(math.pi/4),t.ycor()+size*math.sin(math.pi/4)/2)
    elif style == 'sad':
        jump_to(t.xcor()-size*math.cos(math.pi/4),t.ycor()-size*math.sin(math.pi/4)/2)

    #
    # we don't have to move the surprised face left but we do have to move it down
    # by radius. We have to move surprised face down because the drawing starts going up
    #
    elif style == 'surprised':
        jump_to(t.xcor(),t.ycor()-size/2)

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
    # for netural face we only need to jump to the left by half of size
    # we do not have to move neutral face down
    #
    jump_to(t.xcor()-size/2,t.ycor())
    t.setheading(0)
    t.forward(size)

#
# define head (question 7)
#
def head(size):
    #
    # create a variable that saves the current position
    #
    cur_pos = None
    #
    # draw eyes
    #
    eye_size = size/4
    #
    # move the turtle eye_size + size/20 away from the center, draw an eye,
    # then go on the other side and draw another eye
    # Save the current position first!
    #
    cur_pos = t.pos()
    jump_to(t.xcor()-eye_size-size/20,t.ycor())
    eye(eye_size)
    # 
    # Move turtle to where it was before, unpack cur_pos into jump_to
    #
    jump_to(*cur_pos)
    #
    # draw the other eye
    #
    jump_to(t.xcor()+eye_size+size/20,t.ycor())
    eye(eye_size)
    #
    # Move the turtle back again
    #
    jump_to(*cur_pos)
    #
    # jump to the bottom of the nose
    #
    jump_to(t.xcor(),t.ycor()-size/3)
    #
    # save the position of the turtle so that we can come back after drawing the nose
    #
    cur_pos = t.pos()
    #
    # draw the nose
    #
    nose(size/2)
    #
    # return to the previous position and set angle back to 0
    #
    t.setheading(0)
    jump_to(*cur_pos)
    #
    # s for style, select a random style with r(random module)
    #
    s = r.choice(['happy', 'sad', 'surprised', 'neutral'])
    #
    # move down to draw the mouth and save cur_pos
    #
    jump_to(t.xcor(),t.ycor()-size/3)
    cur_pos = t.pos()
    #
    # draw the mouth (I changed mouth function to move left for this)
    #
    mouth(size/2,s)
    #
    # return to original position and don't need to return angle to 0
    # because mouth returns it to 0
    #
    jump_to(*cur_pos)
    #
    # now move down to draw the outline of the head and we are done!
    #
    jump_to(t.xcor(),t.ycor()-size/2)
    #
    # draw a circle with radius size for the outline of the head
    #
    circle(size)

#
# define stick figure (question 8)
#
def stick_figure(size):
    #
    # make a variable to save the current position of the turtle
    # also randomize colour by choosing random rgb values
    #
    cur_pos = None
    rgb = (r.randint(0,255),r.randint(0,255),r.randint(0,255))
    t.color(rgb)
    #
    # draw a head with a size of size
    #
    head(size)
    #
    # draw the body, point in a random direction for a random pose
    # make the random angle between 210 and 330
    # halfway down draw the arms
    #
    angle = r.randint(210,330)
    t.setheading(angle)
    t.forward(size/2)
    #
    # save cur_pos because we will start drawing the arms
    #
    cur_pos = t.pos()
    #
    # random arm direction (left arm)
    # we can make it between 0 and 180 degrees in relation to angle,
    # but make it 20 and 160 in relation to angle so that
    # the arm doesn't look like it's part of the body line.
    # to get an angle in relation with angle, just subtract angle by that angle, for left arm
    # go back to cur_pos after the arm is done to draw the other arm
    #
    t.setheading(angle-r.randint(20,160))
    t.forward(size/2)
    jump_to(*cur_pos)
    #
    # draw right arm in a random direction, between 20 and 160 (right arm)
    # return to cur_pos and continue drawing the body
    # add random angle to angle for right arm
    #
    t.setheading(angle+r.randint(20,160))
    t.forward(size/2)
    jump_to(*cur_pos)
    t.setheading(angle)
    t.forward(size/2)
    #
    # first save cur_pos
    # now draw legs, not random so it doesn't look wacky, return to cur_pos to draw the next leg
    #
    cur_pos = t.pos()
    t.setheading(225)
    t.forward(size/2)
    jump_to(*cur_pos)
    t.setheading(-45)
    t.forward(size/2)
    #
    # done drawing!
    #

#
# define crowd (question 9)
#
def crowd(n, min_size, max_size):
    #
    # get the screen size so that we can choose a random position that is actually on the screen
    #
    screen = t.getscreen()
    width,height = screen.screensize()[0],screen.screensize()[1]
    #
    # loop through range(n) and draw a stick figure at a random position every iteration
    #
    for i in range(n):
        #
        # make sure to always be max_size*2 away from the borders so that the stick figure is on the screen
        # 0,0 is in the center so we want negative width to positive width, same for height
        # floor divide to make the result an int
        #
        rand_x = r.randint(-width+max_size*2,width-max_size*2)
        rand_y = r.randint(-height+max_size*2,height-max_size*2)
        jump_to(rand_x,rand_y)
        stick_figure(r.randint(min_size,max_size))
stick_figure(100)

#
# Just so that the window isn't removed right away, remove before turning in
# update so that we can see the result
#
t.update()
t.mainloop()