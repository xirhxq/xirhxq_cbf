#include "utils.h"
#include "Point.h"
#include "Swarm.h"

#include <fstream>
#include <ctime>

double f(Point _p, double t){
//    if (t <= 20)    return 1;
//    else if (t <= 40) return exp(-_p.len2());
//    else if (t <= 70) return 10 * exp(-fmax((_p-Point(2.5, 2.5)).len2(), 4));
//    double mid = fabs((_p-Point(2.5, 2.5)).len2() - 4);
//    double mid = fabs(_p.x + _p.y - 5);
//    return 10000 * exp(-mid * mid);
//    return exp(-fabs((_p.len2() - 4)) * 2 );
    return 1;
}

int main() {
    time_t tt = time(NULL);
    tm* t = localtime(&tt);
    char pos_out_path[256];
    sprintf(pos_out_path,R"(../../data/%02d-%02d_%02d-%02d_pos.csv)", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
    char poly_out_path[256];
    sprintf(poly_out_path,R"(../../data/%02d-%02d_%02d-%02d_poly.csv)", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
    char para_out_path[256];
    sprintf(para_out_path,R"(../../data/%02d-%02d_%02d-%02d_para.csv)", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);


    Point p[10] = {Point(0, 0),
                   Point(5, 0),
                   Point(0, 5),
                   Point(5, 5)};
    Polygon world = Polygon(4, p);
    int robot_num = 1;

    Swarm s = Swarm(robot_num, world);
    s.init_poly_log_path(poly_out_path);
    s.init_pos_log_path(pos_out_path);
    s.init_para_log_path(para_out_path);
    s.para_log_once();

    s.output();

    double t_total = 7, t_gap = 0.02;
    for (int iter = 1; iter <= t_total / t_gap; iter++) {
        s.pos_log_once();
        printf("time : %.2lf -------------\n", t_gap * iter);
        s.cvt_forward(t_gap, f);
    }

    printf("After %.4lf seconds\n", t_total);
    s.output();

    s.end_log();
    return 0;
}