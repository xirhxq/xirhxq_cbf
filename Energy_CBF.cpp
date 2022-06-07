//
// Created by xirhxq on 2022/3/7.
//

#include "Energy_CBF.h"

#include <utility>

Energy_CBF::Energy_CBF() {
    charge_place.clear();
}

void Energy_CBF::new_charge_place(Point _p, double _d) {
    charge_place.push_back(_p);
    charge_dist.push_back(_d);
}

int Energy_CBF::nearest_charge_place(Point _p) {
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

double Energy_CBF::dist_to_charge_place(Point _p) {
    return _p.distance_to(charge_place[nearest_charge_place(Point(_p))]);
}

bool Energy_CBF::is_charging(Point _p) {
    for (int i = 0; i < charge_place.size(); i++){
        if (_p.distance_to(charge_place[i]) <= charge_dist[i]) return true;
    }
    return false;
}

double Energy_CBF::h(VectorXd _v) {
    return _v(2) - log(dist_to_charge_place(Point(_v)) / charge_dist[nearest_charge_place(Point(_v))]);
}

double Energy_CBF::dh(VectorXd _x, int _i){
    VectorXd x_plus_dx = _x, x_minus_dx = _x;
    x_plus_dx(_i) += delta;
    x_minus_dx(_i) -= delta;
    return (h(x_plus_dx) - h(x_minus_dx)) / 2.0 / delta;
}

double Energy_CBF::dh_dx(VectorXd _v) {
    return dh(std::move(_v), x_ord);
}

double Energy_CBF::dh_dy(VectorXd _v) {
    return dh(std::move(_v), y_ord);
}

double Energy_CBF::dh_db(VectorXd _v) {
    return dh(std::move(_v), b_ord);
}

Point Energy_CBF::constraint(VectorXd _x, Point _p) {
    double alpha_h = alpha(h(_x));
    if (dh_dx(_x) * _p.x + dh_dy(_x) * _p.y + alpha_h - dh_db(_x) >= 0){
        return _p;
    }
    else {
        return Line(dh_dx(_x), dh_dy(_x),
                    alpha_h - dh_db(_x)).project_point(_p);
    }
}
