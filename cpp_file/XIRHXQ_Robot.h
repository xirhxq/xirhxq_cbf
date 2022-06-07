// Created by XIRHXQ on 12/30/21.

#ifndef CPP_V1_0_XIRHXQ_ROBOT_H
#define CPP_V1_0_XIRHXQ_ROBOT_H

#include "XIRHXQ_Point.h"


class XIRHXQ_Robot {
public:
    XIRHXQ_Point p, v;
    double s = 1;
public:
    XIRHXQ_Robot();
    XIRHXQ_Robot(double _x, double _y);
    XIRHXQ_Robot(XIRHXQ_Point &_p);
    XIRHXQ_Robot(XIRHXQ_Point &_p, XIRHXQ_Point &_v);
    XIRHXQ_Robot(XIRHXQ_Point &_p, XIRHXQ_Point &_v, double _s);
    XIRHXQ_Robot(XIRHXQ_Point &_p, double s_);

    void output();

    void set_position(const XIRHXQ_Point &_p);

    void set_velocity(const XIRHXQ_Point &_v);

    void set_velocity(double _x, double _y);

    void set_saturation(double _s);

    void time_forward(double _t);

    const XIRHXQ_Point &getP() const;
};

#endif //CPP_V1_0_XIRHXQ_ROBOT_H
