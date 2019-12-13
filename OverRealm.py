import turtle
import random

class Point:
    xCoord = 0
    yCoord = 0
    def __init__(self, xIn, yIn):
        self.xCoord = xIn
        self.yCoord = yIn
    def x(self):
        return self.xCoord
    def y(self):
        return self.yCoord
    def setX(self, xIn):
        self.xCoord = xIn
    def setY(self, yIn):
        self.yCoord = yIn

class OverRealm:
    speed = {
        "right" : 0,
        "left"  : 0,
        "up"    : 0,
        "down"  : 0,
        }

    grass = []

    window = 0


    def __init__(self):
        print("over realm understood")
        
    def draw(self):
        self.window.tracer()
        self.window.clear()
  
    def right(self):
        if (self.speed["right"] < 10):
            self.speed["right"] += 1   
        self.draw()  

    def left(self):
        if (self.speed["left"] < 10):
            self.speed["left"] += 1   
        self.draw()

    def up(self):
        if (self.speed["up"] < 10):
            self.speed["up"] += 1  
        self.draw() 

    def down(self):
        if (self.speed["down"] < 10):
            self.speed["down"] += 1  
        self.draw() 

    def enter(self):  # if over realm is entered begin the loop
        self.window = turtle.Screen()
        self.window.bgcolor("#44444")

        #The listeners for the arrow keys and the WASD keys
        self.window.onkey(self.up, "Up")
        self.window.onkey(self.up, "W")
        self.window.onkey(self.down, "Down")
        self.window.onkey(self.down, "S")
        self.window.onkey(self.left, "Left")
        self.window.onkey(self.left, "A")
        self.window.onkey(self.right, "Right")
        self.window.onkey(self.right, "D")

        self.window.listen()
        self.window.mainloop()
        return "NULL"
