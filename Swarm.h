// Created by XIRHXQ on 12/30/21.

#ifndef V6_0_SWARM_H
#define V6_0_SWARM_H

#include "utils.h"
#include "Robot.h"
#include "Polygon.h"

#include <fstream>

class Swarm {
public:
    int n;
    double runtime = 0.0;
    Robot r[maxp];
    Polygon wd;
    double spacing = 0.1;
    std::ofstream data_log;
    json data_j;
public:
    Swarm();
    Swarm(int _n, Point _p[], Polygon _wd);
    Swarm(int _n, Polygon _wd);

    void output();

    void random_initial_position();

    void init_log_path(char _p[]);
    void end_log();
    void para_log_once();
    void log_once();

    void cvt_forward(double _t, const std::function<double(Point, double)>& f);
    void get_pos(Point _p[]);

    double max_speed();

    void get_x_limit(double _x[]);
    void get_y_limit(double _y[]);
};


#endif //V6_0_SWARM_H