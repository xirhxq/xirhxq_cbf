// Created by XIRHXQ on 12/30/21.

#include "utils.h"
#include "XIRHXQ_Robot.h"

XIRHXQ_Robot::XIRHXQ_Robot() {
    p = XIRHXQ_Point();
    v = XIRHXQ_Point();
}

XIRHXQ_Robot::XIRHXQ_Robot(double _x, double _y) {
    p = XIRHXQ_Point(_x, _y);
    v = XIRHXQ_Point();
}

XIRHXQ_Robot::XIRHXQ_Robot(XIRHXQ_Point &_p) {
    p = _p;
    v = XIRHXQ_Point();
}

XIRHXQ_Robot::XIRHXQ_Robot(XIRHXQ_Point &_p, XIRHXQ_Point &_v) {
    p = _p;
    v = _v;
}

XIRHXQ_Robot::XIRHXQ_Robot(XIRHXQ_Point &_p, XIRHXQ_Point &_v, double _s) {
    p = _p;
    v = _v;
    s = _s;
}

XIRHXQ_Robot::XIRHXQ_Robot(XIRHXQ_Point &_p, double _s) {
    p = _p;
    v = XIRHXQ_Point();
    s = _s;
}

void XIRHXQ_Robot::output() {
    printf("An XIRHXQ_Robot @ (%.4lf, %.4lf) with velocity (%.4lf, %.4lf)\n", p.x, p.y, v.x, v.y);
}


void XIRHXQ_Robot::set_position(const XIRHXQ_Point &_p) {
    p = _p;
}

void XIRHXQ_Robot::set_velocity(const XIRHXQ_Point &_v) {
    v = _v;
}

void XIRHXQ_Robot::set_velocity(double _x, double _y) {
    v = XIRHXQ_Point(_x, _y);
}

void XIRHXQ_Robot::set_saturation(double _s) {
    s = _s;
}

void XIRHXQ_Robot::time_forward(double _t) {
    p = p + v.saturation(s) * _t;
}

const XIRHXQ_Point &XIRHXQ_Robot::getP() const {
    return p;
}