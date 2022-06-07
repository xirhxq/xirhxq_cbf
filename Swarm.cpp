// Created by XIRHXQ on 12/30/21.

#include "Swarm.h"
#include "computing_geometry/CVT.h"

#include <fstream>
#include <iomanip>

Swarm::Swarm(int _n, Point *_p, World& _wd){
    n = _n;
    for (int i = 1; i <= _n; i++){
        r[i] = Robot(3);
        r[i].X << _p[i - 1].x, _p[i - 1].y,  1.0 * (rand() % 40) / 40 + 10;
        r[i].F << 0, 0, -1;
    }
    wd = _wd;
    runtime = 0.0;
}

Swarm::Swarm(int _n, World& _wd) {
    n = _n;
    wd = _wd;
    runtime = 0.0;
    for (int i = 1; i <= _n; i++){
        r[i] = Robot(4);
        r[i].G(2, 2) = 0;
        r[i].G(3, 3) = 0;
//        r[i].batt_ord = 3;
        r[i].set_battery(20.0 * (rand() % 100) / 100 + 10);
        r[i].X(3) = 0;
//        r[i].set_battery(i * 10 + 10);
//        r[i].F << 0, 0, -1;
        r[i].F << 0, 0, -1, 10000;
    }
    random_initial_position();
}

void Swarm::output(){
    printf("An Swarm with %d robots @ time %.4lf: ---------\n", n, runtime);
    for (int i = 1; i <= n; i++){
        printf("Robot #%d: ", i);
        r[i].output();
    }
    printf("--------------\n");
}

void Swarm::random_initial_position() {
    for (int i = 1; i <= n; i++){
        r[i].set_position(wd.get_random_point());
    }
}

void Swarm::set_h() {
    std::function<double(Point, World)> nearest_dis = [=](Point _p, World _w){
        return _w.dist_to_charge_place(_p) / _w.charge_dist;
    };
    for (int i = 1; i <= n; i++){
        std::function<double(VectorXd)> dis_h = [=](VectorXd _x){
            return _x(r[i].batt_ord) -
            log(nearest_dis(Point(_x(r[i].x_ord), _x(r[i].y_ord)), wd));
        };
        r[i].energy_cbf.h = dis_h;
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
    data_j["para"]["charge"]["num"] = wd.charge_place.size();
    for (int i = 0; i < wd.charge_place.size(); i++){
        data_j["para"]["charge"]["pos"].push_back({
            {"x", wd.charge_place[i].x},
            {"y", wd.charge_place[i].y}
        });
        data_j["para"]["charge"]["dist"].push_back(wd.charge_dist);
    }
}

void Swarm::log_once() {
    json tmp_j;
    tmp_j["runtime"] = runtime;
    for (int i = 1; i <= n; i++){
        tmp_j["robot"][i - 1] = {
            {"x", r[i].x()},
            {"y", r[i].y()},
            {"batt", r[i].batt()},
            {"camera", r[i].camera()},
            {"energy_cbf", r[i].energy_cbf.h(r[i].X)}
        };
    }
    data_j["state"].push_back(tmp_j);
}

void Swarm::time_forward(double _t) {
    for (int i = 1; i <= n; i++){
        VectorXd u{3};
        u << 0, 0, 0;
        r[i].time_forward(u, _t, wd);
    }
    runtime += _t;
}

void Swarm::cvt_forward(double _t, const std::function<double(Point, double)>& f) {
    CVT c = CVT(n, wd.w);
    for (int i = 1; i <= n; i++){
        c.pt[i] = r[i].xy();
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
        Point up = c.ct[i] - r[i].xy();
        VectorXd u;
        u.resize(r[i].X.size());
        u.setZero();
        u(r[i].x_ord) = up.x;
        u(r[i].y_ord) = up.y;
//        std::cout << u << std::endl;
        r[i].time_forward(u, _t, wd);
    }
    int sz = data_j["state"].size();
    data_j["state"][sz - 1]["cvt"] = tmp_j;
    runtime += _t;
}

void Swarm::get_pos(Point _p[]) {
    for (int i = 1; i <= n; i++){
        _p[i - 1] = r[i].xy();
    }
}

void Swarm::get_x_limit(double _x[]) {
    wd.w.get_x_limit(_x);
}

void Swarm::get_y_limit(double *_y) {
    wd.w.get_y_limit(_y);
}