// Created by XIRHXQ on 12/30/21.

#include "utils.h"
#include "Robot.h"
#include "Line.h"
#include "CBF.h"

Robot::Robot() {
    p = Point();
    v = Point();
}

Robot::Robot(double _x, double _y) {
    p = Point(_x, _y);
    v = Point();
}

Robot::Robot(Point &_p) {
    p = _p;
    v = Point();
}

Robot::Robot(Point &_p, Point &_v) {
    p = _p;
    v = _v;
}

Robot::Robot(Point &_p, Point &_v, double _s) {
    p = _p;
    v = _v;
    s = _s;
}

Robot::Robot(Point &_p, double _s) {
    p = _p;
    v = Point();
    s = _s;
}

void Robot::set_battery(double _b) {
    batt = _b;
}

void Robot::output() {
    printf("An Robot @ (%.4lf, %.4lf) with velocity (%.4lf, %.4lf)\n", p.x, p.y, v.x, v.y);
}


void Robot::set_position(const Point &_p) {
    p = _p;
}

void Robot::set_velocity(const Point &_v) {
    v = _v;
}

void Robot::set_velocity(double _x, double _y) {
    v = Point(_x, _y);
}

void Robot::set_saturation(double _s) {
    s = _s;
}

void Robot::time_forward(double _t) {
    if (p.len() <= 1 && batt <= 40){
        batt += _t * (10);
    }
    else{
        std::function<double(Point, double)> h = [](Point _p, double _b){return _b - log(_p.len());};
        std::function<double(Point, double)> hx = [](Point _p, double _b){return - _p.x / _p.len2();};
        std::function<double(Point, double)> hy = [](Point _p, double _b){return - _p.y / _p.len2();};
        std::function<double(Point, double)> hb = [](Point _p, double _b) {return 1.0;};
        CBF cbf_batt(h, hx, hy, hb);
        p = p + cbf_batt.constraint(p, batt, v).saturation(s) * _t;
        batt -= _t;
    }
}

const Point &Robot::getP() const {
    return p;
}