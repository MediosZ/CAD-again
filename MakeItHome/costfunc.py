from utils import distance, redraw
import math
import random
from matplotlib import pyplot as plt

# wo consider these things
# accessibility, visibility, pairwise distance, pirewise direction, self location
# let's say we have several furnitures: 
# three plants, two chairs, one tv, and one sofa
# one point is that the tv and the sofa is a pair of things, and the tv should just on the wall 

cost = []
x = []
def CostFunction(objects):
    final_cost = 0
    visibility_cost = 0
    accessibility_cost = 0
    direction_cost = 0
    pair_direction_cost = 0
    distance_cost = 0
    pair_distance_cost = 0
    # Visibility
    for (index1, obj1) in enumerate(objects):
        for (index2, obj2) in enumerate(objects):
            if index1 == index2:
                continue
            visibility_cost += max(0, (1 - distance(obj1.pos, obj2.pos)/(obj1.length + obj2.length)))
    #print("visbility cost is ", visibility_cost)

    # Accessibility except for plants
    for i in range(4):
        for (index, obj2) in enumerate(objects):
            if i == index:
                continue
            accessibility_cost += max(0, (1 - distance(objects[i].acc_pos, obj2.pos)/(objects[i].acc_lenth + obj2.length)))
    #print("accessibility cost is ", accessibility_cost)

    # Direction for tv: objects[3]
    # we define the direction of tv is 0 and it is at bottom
    # that means the pos of tv is (x, 495), the dir of it is 0
    direction_cost = abs(objects[3].dir - 0)
    #print("direction_cost is ", direction_cost)

    distance_cost = abs(objects[3].pos[1] - 495)
    #print("distance_cost is ", distance_cost)
    
    # pairwise direction and pairwise distance for tv: objects[3] and sofa: objects[0]

    pair_direction_cost = abs((objects[0].dir - objects[3].dir) - math.pi)
    #print("pair_direction_cost is ", pair_direction_cost)
    pair_distance_cost = abs(distance(objects[0].pos, objects[3].pos) - 200)
    #pair_distance_cost = abs(objects[0].pos[1] - objects[3].pos[1] - 200) + abs(objects[0].pos[0] - objects[3].pos[0])
    #print("pair_distance_cost is ", pair_distance_cost)

    final_cost = visibility_cost + accessibility_cost + 10 * direction_cost + distance_cost + pair_direction_cost + pair_distance_cost
    #print("final cost is ", final_cost)
    return final_cost


def update(objects, times):
    temp = []
    for i in range(times):
        temp.clear()
        last_cost = CostFunction(objects)
        for i, obj in enumerate(objects):
            temp.append((obj.pos, obj.dir))
            prob = random.uniform(0,1)
            if prob <= 0.4:
                obj.pos = (int(obj.pos[0] + random.uniform(-10, 10)), int(obj.pos[1] + random.uniform(-10, 10)))
            elif prob <= 0.8:
                obj.dir = obj.dir + random.uniform(-1, 1)
            else:
                obj.pos = (int(obj.pos[0] + random.uniform(-10, 10)), int(obj.pos[1] + random.uniform(-10, 10)))
                obj.dir = obj.dir + random.uniform(-1, 1)
            obj.calPos()
            if obj.isOut():
                obj.pos = temp[i][0]
                obj.dir = temp[i][1]
        current_cost = CostFunction(objects)
        
        print("result is ", last_cost, current_cost)
        if current_cost < last_cost:
            print("good next one")
            continue
        else:
            print("bad one")
            for i, obj in enumerate(objects):
                obj.pos = temp[i][0]
                obj.dir = temp[i][1]
            #print("it be", CostFunction(objects), last_cost)
            continue
    
        #print(temp)
        # randomly change a little bit


def updateWithSA(objects, times, image):
    temp = []
    for time in range(times):
        temper = float(times) /10 / float(time+1)
        degeree = 0
        if time < times / 3:
            degeree = 1
        elif time < times * 2/3:
            degeree = 0.6
        else:
            degeree = 0.3
        temp.clear()
        last_cost = CostFunction(objects)
        x.append(time)
        cost.append(last_cost)
        for i, obj in enumerate(objects):
            temp.append((obj.pos, obj.dir))
            prob = random.uniform(0,1)
            if prob <= 0.4:
                obj.pos = (int(obj.pos[0] + degeree * random.uniform(-10, 10)), int(obj.pos[1] + degeree * random.uniform(-10, 10)))
            elif prob <= 0.8:
                obj.dir = obj.dir + degeree * random.uniform(-1, 1)
            else:
                obj.pos = (int(obj.pos[0] + degeree * random.uniform(-10, 10)), int(obj.pos[1] + degeree * random.uniform(-10, 10)))
                obj.dir = obj.dir + degeree * random.uniform(-1, 1)
            obj.calPos()
            if obj.isOut():
                obj.pos = temp[i][0]
                obj.dir = temp[i][1]
        current_cost = CostFunction(objects)
        print("result is ", last_cost, current_cost)
        if current_cost < last_cost:
            print("good next one")
            redraw(image, objects)
            continue
        else:
            print("bad one")
            energy = current_cost - last_cost
            try:
                accept_prob = max(0, (1 - math.exp(energy / temper)))
            except:
                accept_prob = 0
            
            choice = random.uniform(0,1)
            if choice <accept_prob:
                print("prob is ", accept_prob, temper, energy)
                print("but accept it")
                redraw(image, objects)
                continue
            for i, obj in enumerate(objects):
                obj.pos = temp[i][0]
                obj.dir = temp[i][1]
            #print("it be", CostFunction(objects), last_cost)
            redraw(image, objects)
            continue
    plt.plot(x, cost)
    plt.show()
