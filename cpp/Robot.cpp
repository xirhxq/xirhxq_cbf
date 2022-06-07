// Created by XIRHXQ on 12/30/21.

#include "utils.h"
#include "Robot.h"
#include "Line.h"

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
    btry = _b;
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
    if (p.len() <= 1 && btry <= 40){
        btry += _t * (10);

    }
    else{

        double alphah = 100 * pow(h(p, btry), 2) ;
//    Point sat_v = v.saturation(s);
        Point sat_v = v;
        Point hxy = Point(hx(p, btry), hy(p, btry));
        if (sat_v * hxy + alphah >= 0){
            p = p + sat_v * _t;
        }
        else{
            Line l = Line(hxy.x, hxy.y, alphah);
            Point cbf_v = l.project_point(sat_v);
//        printf("time -----------\n");
        printf("@ (%.2lf, %.2lf) with btry %.2lf\n", p.x, p.y, btry);
        printf("alpahh = %lf hx = %lf hy = %lf\n", alphah, hxy.x, hxy.y);
        printf("sat_v: ");sat_v.output();
        printf("l: ");l.output();
        printf("cbf_v: ");cbf_v.output();
//        p = p + cbf_v.saturation(s) * _t;
            p = p + cbf_v * _t;
        }
        btry -= _t;
    }
}

const Point &Robot::getP() const {
    return p;
}

double h(Point p, double b){
//    printf("b = %lf \n log = %lf \nh = %lf\n", b, log(p.len()), b - log(p.len()));
    return b - 10 - log(p.len());
}

double hx(Point p, double b){
    return - 2.0 * p.x / p.len2();
}

double hy(Point p, double b){
    return - 2.0 * p.y / p.len2();
}