import cv2

def drawWall(background, thickness):
    cv2.line(background, (20,20), (20, 500), (0,0,0), thickness)
    cv2.line(background, (20,500), (660, 500), (0,0,0), thickness)
    cv2.line(background, (660,500), (660, 20), (0,0,0), thickness)
    cv2.line(background, (660,20), (20, 20), (0,0,0), thickness)
