from math import * 
import cv2

class Object:
    def __init__(self, name, size, pos, dir, img):
        self.name = name
        self.size = size
        self.pos = pos 
        self.dir = dir/180*pi
        self.point = []
        print(self.name, 'initialization done')
        self.calPos()
        self.draw(img)

    def draw(self, image):
        cv2.line(image, self.point[0], self.point[1], (0,0,0), 1)
        cv2.line(image, self.point[1], self.point[2], (0,0,0), 1)
        cv2.line(image, self.point[2], self.point[3], (0,0,0), 1)
        cv2.line(image, self.point[3], self.point[0], (0,0,0), 1)
        #print(sin(self.dir), cos(self.dir))
        cv2.line(image, self.pos, 
                (int(self.pos[0] + (self.size[1]/2)*sin(self.dir)), 
                int(self.pos[1] - (self.size[1]/2)*cos(self.dir))), 
                (0,0,255), 2)
        cv2.putText(image,self.name,self.pos, cv2.FONT_HERSHEY_SIMPLEX, 0.4,(255,0,0),1,cv2.LINE_AA)

    def calPos(self):
        theta0 = atan2(self.size[0], self.size[1])
        self.theta0 = theta0
        length = sqrt((self.size[0]/2)**2 + (self.size[1]/2)**2)
        #print(length)
        self.point.append((int(self.pos[0] + length * sin(theta0 - self.dir)), int(self.pos[1] + length * cos(theta0 - self.dir))))
        self.point.append((int(self.pos[0] - length * sin(theta0 + self.dir)), int(self.pos[1] + length * cos(theta0 + self.dir))))
        self.point.append((int(self.pos[0] - length * sin(theta0 - self.dir)), int(self.pos[1] - length * cos(theta0 - self.dir))))
        self.point.append((int(self.pos[0] + length * sin(theta0 + self.dir)), int(self.pos[1] - length * cos(theta0 + self.dir))))
        #print(self.point)