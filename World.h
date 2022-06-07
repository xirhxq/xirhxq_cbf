//
// Created by xirhxq on 2022/3/4.
//

#ifndef V8_0_WORLD_H
#define V8_0_WORLD_H

#include "utils.h"
#include "computing_geometry/Polygon.h"


class World {
public:
    Polygon w;

public:
    World();
    World(Polygon &);

    Point get_random_point();

//    bool charge_place(Point);
//
//    double charge_distance(Point);
};


#endif //V8_0_WORLD_H
