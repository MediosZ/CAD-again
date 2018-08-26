import cv2
import numpy as np 
from utils import *
from object import Object

background = np.ones((520, 680, 3))

# draw walls
drawWall(background, 3)

sofa = Object('sofa', (80,60), (200,200), 30)
sofa.draw(background)

cv2.imshow("background", background)
cv2.waitKey()