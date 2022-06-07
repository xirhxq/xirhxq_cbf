// Created by XIRHXQ on 12/30/21.

#include "Swarm.h"
#include "CVT.h"
#include "Robot.h"

#include <fstream>
#include <iomanip>

Swarm::Swarm() {
    n = 0;
    runtime = 0.0;
}

Swarm::Swarm(int _n, Point *_p, Polygon _wd) {
    n = _n;
    for (int i = 1; i <= n; i++){
        r[i].set_position(_p[i - 1]);
    }
    wd = _wd;
    runtime = 0.0;
}

Swarm::Swarm(int _n, Polygon _wd) {
    n = _n;
    wd = _wd;
    runtime = 0.0;
    random_initial_position();
    for (int i = 1; i <= _n; i++){
        r[i].set_battery(5 + i * 10);
    }
}

void Swarm::output(){
    printf("An Swarm with %d robots @ time %.4lf: ---------\n", n, runtime);
    for (int i = 1; i <= n; i++){
        printf("Robot #%d: ", i);
        r[i].output();
    }
    printf("Max speed is %.4lf\n", max_speed());
    printf("--------------\n");
}

void Swarm::random_initial_position() {
    for (int i = 1; i <= n; i++){
        r[i].p = wd.get_random_point();
    }
}

void Swarm::init_para_log_path(char *_p) {
    para_log.open(_p, std::ios::app);
}

void Swarm::init_pos_log_path(char *_p) {
    pos_log.open(_p, std::ios::app);
}

void Swarm::init_poly_log_path(char *_p) {
    poly_log.open(_p, std::ios::app);
}

void Swarm::end_log() {
    para_log.close();
    poly_log.close();
    pos_log.close();
}

void Swarm::para_log_once() {
    para_log << n << std::endl;
    double x_lim[2], y_lim[2];
    get_x_limit(x_lim), get_y_limit(y_lim);
    para_log << x_lim[0] << ", " << x_lim[1] << ", " << y_lim[0] << ", " << y_lim[1] << std::endl;
}

void Swarm::pos_log_once() {
    pos_log << std::fixed << std::setprecision(6) << runtime << std::endl;
    for (int i = 1; i <= n; i++){
        pos_log << std::fixed << std::setprecision(6) << r[i].p.x << ", " << r[i].p.y << ", " << r[i].btry;
        if (i < n) pos_log << ", ";
        else pos_log << std::endl;
    }
}

void Swarm::cvt_forward(double _t, const std::function<double(Point, double)>& f) {
    CVT c = CVT(n, wd);
    for (int i = 1; i <= n; i++){
        c.pt[i] = r[i].p;
    }
    c.cal_poly();
    c.cal_centroid(std::bind(f, std::placeholders::_1, runtime), spacing);
    for (int i = 1; i <= n; i++){
        poly_log << std::fixed << std::setprecision(6) <<  c.pl[i].n << ", ";
        for (int j = 1; j <= c.pl[i].n; j++) {
            poly_log << std::fixed << std::setprecision(6) << c.pl[i].p[j].x << ", " << c.pl[i].p[j].y << ", ";
        }
        poly_log << std::fixed << std::setprecision(6) << c.pl[i].p[1].x << ", " << c.pl[i].p[1].y << std::endl;

        r[i].set_velocity(c.ct[i] - r[i].p);
        r[i].time_forward(_t);
    }
    runtime += _t;
}

void Swarm::get_pos(Point _p[]) {
    for (int i = 1; i <= n; i++){
        _p[i - 1] = r[i].getP();
    }
}

double Swarm::max_speed() {
    double res = 0.0;
    for (int i = 1; i <= n; i++){
        res = fmax(res, r[i].v.len());
    }
    return res;
}

void Swarm::get_x_limit(double _x[]) {
    wd.get_x_limit(_x);
}

void Swarm::get_y_limit(double *_y) {
    wd.get_y_limit(_y);
}