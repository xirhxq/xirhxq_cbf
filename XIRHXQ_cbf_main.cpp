#include "utils.h"
#include "computing_geometry/Point.h"
#include "Swarm.h"

#include <fstream>
#include <ctime>

double f(Point _p, double t){
//    return 1;
//    if (t <= 20)    return 1;
//    else if (t <= 40) return exp(-(_p-Point(5, 5)).len2());
//    else if (t <= 70) return 10 * exp(-fmax((_p-Point(2.5, 2.5)).len2(), 4));
//    double mid = fabs((_p-Point(2.5, 2.5)).len2() - 4);
//    double mid = fabs(_p.x + _p.y - 5);
//    return 10000 * exp(-mid * mid);
//    return exp(-fabs((_p.len2() - 4)) * 2 );
    return exp(-fabs((_p - Point(10.0, 5.0)).len2() - 16) * 2);
}

int main() {
    time_t tt = time(NULL);
    tm* t = localtime(&tt);
    char data_out_path[256];
    sprintf(data_out_path,R"(../data/%02d-%02d_%02d-%02d_data.json)",
            t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);


    Point p[10] = {Point(0, 0),
                   Point(20, 0),
                   Point(0, 10),
                   Point(20, 10)};
    Polygon wd_p(4, p);
    World world(wd_p);

    Point c[8] = {Point(1.0, 2.0),
                  Point(1.0, 4.0),
                  Point(1.0, 6.0),
                  Point(1.0, 8.0),
                  Point(19.0, 2.0),
                  Point(19.0, 4.0),
                  Point(19.0, 6.0),
                  Point(19.0, 8.0)};
    std::function<double(Point)> nearest_dis = [=](Point _p){
        double res = _p.distance_to(c[0]);
        for (int i = 1; i < 8; i++){
            res = std::min(res, _p.distance_to(c[i]));
        }
        return res;
    };
    double d[8] = {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3};

    Point init_pos[8] = {Point(3.0, 2.0),
                         Point(3.0, 4.0),
                         Point(3.0, 6.0),
                         Point(3.0, 8.0),
                         Point(17.0, 2.0),
                         Point(17.0, 4.0),
                         Point(17.0, 6.0),
                         Point(17.0, 8.0)};

    Swarm s = Swarm(12, world);
    s.set_charge_place(8, c, d);
    s.init_log_path(data_out_path);
    s.para_log_once();

    s.output();

    double t_total = 40, t_gap = 0.02;
    for (int iter = 1; iter <= t_total / t_gap; iter++) {
        s.log_once();
//        printf("time : %.2lf -------------\n", t_gap * iter);
//        s.time_forward(t_gap);
        s.cvt_forward(t_gap, f);
//        s.output();
//        return 0;
    }

    printf("After %.4lf seconds\n", t_total);

    s.output();
    s.end_log();
    printf("Data saved in %s\n", data_out_path);
    return 0;
}