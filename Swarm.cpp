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

void Swarm::init_log_path(char *_p) {
    data_log.open(_p, std::ios::app);
}

void Swarm::end_log() {
    data_log << std::fixed << std::setprecision(6) << data_j.dump(4);
    data_log.close();
}

void Swarm::para_log_once() {
    data_j["para"]["number"] = n;
    double x_lim[2], y_lim[2];
    get_x_limit(x_lim), get_y_limit(y_lim);
    data_j["para"]["lim"]["x"] = {x_lim[0], x_lim[1]};
    data_j["para"]["lim"]["y"] = {y_lim[0], y_lim[1]};
}

void Swarm::log_once() {
    json tmp_j;
    tmp_j["runtime"] = runtime;
    for (int i = 1; i <= n; i++){
        tmp_j["robot"][i - 1] = {
            {"x", r[i].p.x},
            {"y", r[i].p.y},
            {"btry", r[i].btry}
        };
    }
    data_j["state"].push_back(tmp_j);
}

void Swarm::cvt_forward(double _t, const std::function<double(Point, double)>& f) {
    CVT c = CVT(n, wd);
    for (int i = 1; i <= n; i++){
        c.pt[i] = r[i].p;
    }
    c.cal_poly();
    c.cal_centroid(std::bind(f, std::placeholders::_1, runtime), spacing);


    json tmp_j;

    for (int i = 1; i <= n; i++){
        tmp_j[i - 1]["num"] = c.pl[i].n + 1;
        for (int j = 1; j <= c.pl[i].n; j++) {
            tmp_j[i - 1]["pos"].push_back({{"x", c.pl[i].p[j].x}, {"y", c.pl[i].p[j].y}});
        }
        tmp_j[i - 1]["pos"].push_back({{"x", c.pl[i].p[1].x}, {"y", c.pl[i].p[1].y}});
        r[i].set_velocity(c.ct[i] - r[i].p);
        r[i].time_forward(_t);
    }
    int sz = data_j["state"].size();
    data_j["state"][sz - 1]["cvt"] = tmp_j;
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