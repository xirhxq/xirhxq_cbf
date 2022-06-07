// Created by XIRHXQ on 12/30/21.

#ifndef V8_0_SWARM_H
#define V8_0_SWARM_H

#include "utils.h"
#include "Robot.h"
#include "computing_geometry/Polygon.h"
#include "World.h"
#include "First_Order_UGV.h"

#include <fstream>

class Swarm {
public:
    int n;
    double runtime = 0.0;
    First_Order_UGV r[maxp];
    World wd;
    double spacing = 0.1;
    std::ofstream data_log;
    json data_j;
public:
    Swarm(int _n, Point _p[], World& _wd);
    Swarm(int _n, World& _wd);

    void output();

    void random_initial_position();
    void set_charge_place(int _n, Point _c[], double _d[]);

    void init_log_path(char _p[]);
    void end_log();
    void para_log_once();
    void log_once();

    void time_forward(double _t);

    void cvt_forward(double _t, const std::function<double(Point, double)>& f);
    void get_pos(Point _p[]);

    void get_x_limit(double _x[]);
    void get_y_limit(double _y[]);
};


#endif //V8_0_SWARM_H