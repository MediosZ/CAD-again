import cv2
from math import * 
import numpy as np 

def drawWall(background, thickness):
    cv2.line(background, (20,20), (20, 500), (0,0,0), thickness)
    cv2.line(background, (20,500), (660, 500), (0,0,0), thickness)
    cv2.line(background, (660,500), (660, 20), (0,0,0), thickness)
    cv2.line(background, (660,20), (20, 20), (0,0,0), thickness)

def distance(pos1, pos2):
    return sqrt((pos1[0] - pos2[0])**2 + (pos1[1] - pos2[1])**2)

#print(distance((1,2), (2,3)))

def redraw(img, objects):
    img = np.ones((520, 680, 3))
    drawWall(img, 3)
    for obj in objects:
        obj.calPos()
        obj.draw(img)
    cv2.imshow("background", img)
    cv2.waitKey(1)

# is a point is out of boundary then return True
def pointOut(pos):
    if pos[0] < 20 or pos[0] > 660:
        return True
    if pos[1] < 20 or pos[1] >500:
        return True
    return False