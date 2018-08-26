import cv2
import numpy as np 
from utils import *
from object import Object

background = np.ones((520, 680, 3))
objects = []
# draw walls
drawWall(background, 3)

def init():
    objects.append(Object('sofa', (80,60), (280,200), 30, background))
    objects.append(Object('chair', (50,50), (380,300), 40, background))  
    objects.append(Object('chair', (50,50), (190,420), 120, background))   
    objects.append(Object('plant', (30,30), (420,280), -150, background))
    objects.append(Object('plant', (30,30), (320,190), -120, background))
    objects.append(Object('plant', (30,30), (230,50), -100, background)) 
    objects.append(Object('tv', (130,10), (280,300), -50, background))

    cv2.imshow("background", background)
    cv2.waitKey()

init()