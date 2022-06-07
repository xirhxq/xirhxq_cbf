// Created by XIRHXQ on 12/30/21.

#include "XIRHXQ_Swarm.h"
#include "XIRHXQ_CVT.h"
#include "XIRHXQ_Robot.h"

#include <fstream>
#include <iomanip>

XIRHXQ_Swarm::XIRHXQ_Swarm() {
    n = 0;
    runtime = 0.0;
}

XIRHXQ_Swarm::XIRHXQ_Swarm(int _n, XIRHXQ_Point *_p, XIRHXQ_Polygon _wd) {
    n = _n;
    for (int i = 1; i <= n; i++){
        r[i].set_position(_p[i - 1]);
    }
    wd = _wd;
    runtime = 0.0;
}

XIRHXQ_Swarm::XIRHXQ_Swarm(int _n, XIRHXQ_Polygon _wd) {
    n = _n;
    wd = _wd;
    runtime = 0.0;
    random_initial_position();
}

void XIRHXQ_Swarm::output(){
    printf("An XIRHXQ_Swarm with %d robots @ time %.4lf: ---------\n", n, runtime);
    for (int i = 1; i <= n; i++){
        printf("Robot #%d: ", i);
        r[i].output();
    }
    printf("Max speed is %.4lf\n", max_speed());
    printf("--------------\n");
}

void XIRHXQ_Swarm::random_initial_position() {
    for (int i = 1; i <= n; i++){
        r[i].p = wd.get_random_point();
    }
}

void XIRHXQ_Swarm::cvt_forward(double _t, const std::function<double(XIRHXQ_Point)>& f,
                               char pos_fn[], char poly_fn[]) {
    XIRHXQ_CVT c = XIRHXQ_CVT(n, wd);
    for (int i = 1; i <= n; i++){
        c.pt[i] = r[i].p;
    }
    c.cal_poly();
    c.cal_centroid(f, spacing);

    std::ofstream pos_out, poly_out;
    pos_out.open(pos_fn, std::ios::app);
    poly_out.open(poly_fn, std::ios::app);
    for (int i = 1; i <= n; i++){
        poly_out << std::fixed << std::setprecision(6) <<  c.pl[i].n << ", ";
        for (int j = 1; j <= c.pl[i].n; j++) {
            poly_out << std::fixed << std::setprecision(6) << c.pl[i].p[j].x << ", " << c.pl[i].p[j].y << ", ";
        }
        poly_out << std::fixed << std::setprecision(6) << c.pl[i].p[1].x << ", " << c.pl[i].p[1].y << std::endl;

        pos_out << std::fixed << std::setprecision(6) <<  r[i].p.x << ", " << r[i].p.y;
        if (i < n) pos_out << ", ";
        else pos_out << std::endl;

        r[i].set_velocity(c.ct[i] - r[i].p);
        r[i].time_forward(_t);
    }
    runtime += _t;
    pos_out.close();
    poly_out.close();
}

void XIRHXQ_Swarm::get_pos(XIRHXQ_Point _p[]) {
    for (int i = 1; i <= n; i++){
        _p[i - 1] = r[i].getP();
    }
}

double XIRHXQ_Swarm::max_speed() {
    double res = 0.0;
    for (int i = 1; i <= n; i++){
        res = fmax(res, r[i].v.len());
    }
    return res;
}

void XIRHXQ_Swarm::get_x_limit(double _x[]) {
    wd.get_x_limit(_x);
}

void XIRHXQ_Swarm::get_y_limit(double *_y) {
    wd.get_y_limit(_y);
}