// Created by XIRHXQ on 12/30/21.

#ifndef CPP_V1_0_XIRHXQ_SWARM_H
#define CPP_V1_0_XIRHXQ_SWARM_H

#include "utils.h"
#include "XIRHXQ_Robot.h"
#include "XIRHXQ_Polygon.h"

class XIRHXQ_Swarm {
public:
    int n;
    double runtime = 0.0;
    XIRHXQ_Robot r[maxp];
    XIRHXQ_Polygon wd;
    double spacing = 0.1;
public:
    XIRHXQ_Swarm();
    XIRHXQ_Swarm(int _n, XIRHXQ_Point _p[], XIRHXQ_Polygon _wd);
    XIRHXQ_Swarm(int _n, XIRHXQ_Polygon _wd);

    void output();

    void random_initial_position();

    void cvt_forward(double _t, const std::function<double(XIRHXQ_Point)>& f,
                     char pos_fn[], char poly_fn[]);
    void get_pos(XIRHXQ_Point _p[]);

    double max_speed();

    void get_x_limit(double _x[]);
    void get_y_limit(double _y[]);
};


#endif //CPP_V1_0_XIRHXQ_SWARM_H
