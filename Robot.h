// Created by XIRHXQ on 12/30/21.

#ifndef V6_0_ROBOT_H
#define V6_0_ROBOT_H

#include "Point.h"


class Robot {
public:
    Point p, v;
    double batt = 20;
    double s = 1;
public:
    Robot();
    Robot(double _x, double _y);
    Robot(Point &_p);
    Robot(Point &_p, Point &_v);
    Robot(Point &_p, Point &_v, double _s);
    Robot(Point &_p, double s_);

    void set_battery(double _b);

    void output();

    void set_position(const Point &_p);

    void set_velocity(const Point &_v);

    void set_velocity(double _x, double _y);

    void set_saturation(double _s);

    void time_forward(double _t);

    const Point &getP() const;
};

double h(Point p, double b);

double hx(Point p, double b);

double hy(Point p, double b);

double hb(Point p, double b);

#endif //V6_0_ROBOT_H
