//
// Created by xirhxq on 2022/3/4.
//

#ifndef V9_0_WORLD_H
#define V9_0_WORLD_H

#include "utils.h"
#include "computing_geometry/Polygon.h"


class World {
public:
    Polygon w;
    std::vector<Point> charge_place;
    double charge_dist = 0.3;
    std::function<Point (double)> target_pos;
    std::function<double (Point, double)> dens;

public:
    World();
    World(Polygon);
    World(Polygon, std::vector<Point>);

    int nearest_charge_place(Point);
    double dist_to_charge_place(Point);
    bool is_charging(Point);
    Point get_random_point();

};


#endif //V9_0_WORLD_H
