from utils import distance
import math

# wo consider these things
# accessibility, visibility, pairwise distance, pirewise direction, self location
# let's say we have several furnitures: 
# three plants, two chairs, one tv, and one sofa
# one point is that the tv and the sofa is a pair of things, and the tv should just on the wall 



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
    print("visbility cost is ", visibility_cost)

    # Accessibility except for plants
    for i in range(4):
        for (index, obj2) in enumerate(objects):
            if i == index:
                continue
            accessibility_cost += max(0, (1 - distance(objects[i].acc_pos, obj2.pos)/(objects[i].acc_lenth + obj2.length)))
    print("accessibility cost is ", accessibility_cost)

    # Direction for tv: objects[3]
    # we define the direction of tv is 0 and it is at bottom
    # that means the pos of tv is (x, 495), the dir of it is 0
    direction_cost = abs(objects[3].dir - 0)
    print("direction_cost is ", direction_cost)

    distance_cost = abs(objects[3].pos[1] - 495)
    print("distance_cost is ", distance_cost)
    
    # pairwise direction and pairwise distance for tv: objects[3] and sofa: objects[0]

    pair_direction_cost = abs((objects[0].dir - objects[3].dir) - math.pi)
    print("pair_direction_cost is ", pair_direction_cost)
    pair_distance_cost = abs(distance(objects[0].pos, objects[3].pos) - 200)
    print("pair_distance_cost is ", pair_distance_cost)

    final_cost = visibility_cost + accessibility_cost + direction_cost + distance_cost + pair_direction_cost + pair_distance_cost
    print("final cost is ", final_cost)