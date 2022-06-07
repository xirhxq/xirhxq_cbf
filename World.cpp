//
// Created by xirhxq on 2022/3/4.
//

#include "World.h"

World::World() {}

World::World(Polygon _w) {
    w = _w;
}

World::World(Polygon _w, std::vector<Point> _v) {
    w = _w;
    charge_place = _v;
}

Point World::get_random_point() {
    return w.get_random_point();
}

int World::nearest_charge_place(Point _p) {
    assert(!charge_place.empty());
    double res = _p.distance_to(charge_place[0]);
    int id = 0;
    for (int i = 1; i < charge_place.size(); i++){
        if (_p.distance_to(charge_place[i]) < res){
            res = _p.distance_to(charge_place[i]);
            id = i;
        }
    }
    return id;
}

double World::dist_to_charge_place(Point _p) {
    return _p.distance_to(charge_place[nearest_charge_place(Point(_p))]);
}

bool World::is_charging(Point _p) {
    for (int i = 0; i < charge_place.size(); i++){
        if (_p.distance_to(charge_place[i]) <= charge_dist) return true;
    }
    return false;
}
