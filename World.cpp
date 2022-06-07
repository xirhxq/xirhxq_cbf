//
// Created by xirhxq on 2022/3/4.
//

#include "World.h"

World::World() {}

World::World(Polygon& _w) {
    w = _w;
}

Point World::get_random_point() {
    return w.get_random_point();
}

//bool World::charge_place(Point _p) {
//    if (_p.distance_to(Point(1.0, 1.0)) <= 0.3) return true;
//    if (_p.distance_to(Point(1.0, 2.0)) <= 0.3) return true;
//    if (_p.distance_to(Point(1.0, 3.0)) <= 0.3) return true;
//    if (_p.distance_to(Point(1.0, 4.0)) <= 0.3) return true;
//    if (_p.len() <= 1) return true;
//    return false;
//}
//
//double World::charge_distance(Point _p) {
//    double res = _p.distance_to(Point(1.0, 1.0));
//    res = std::min(res, _p.distance_to(Point(1.0, 2.0)));
//    res = std::min(res, _p.distance_to(Point(1.0, 3.0)));
//    res = std::min(res, _p.distance_to(Point(1.0, 4.0)));
//    return res;
//}