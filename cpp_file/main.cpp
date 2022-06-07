#include "utils.h"
#include "XIRHXQ_Swarm.h"

#include <fstream>
#include <ctime>

double f(XIRHXQ_Point _p){
//    return 1;
//    return exp(-(_p.x * _p.x + _p.y * _p.y));
    return exp(-fabs((_p.len2() - 4)) * 2 );
}

int main() {

    time_t tt = time(NULL);
    tm* t = localtime(&tt);
    char pos_out_path[256];
    sprintf(pos_out_path,R"(../data/%02d-%02d_%02d-%02d_pos.csv)", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
    char poly_out_path[256];
    sprintf(poly_out_path,R"(../data/%02d-%02d_%02d-%02d_poly.csv)", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
    char para_out_path[256];
    sprintf(para_out_path,R"(../data/%02d-%02d_%02d-%02d_para.csv)", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);


    XIRHXQ_Point p[10] = {XIRHXQ_Point(-5 ,0),
                          XIRHXQ_Point(5, 0),
                          XIRHXQ_Point(-5, 5),
                          XIRHXQ_Point(5, 5),
                          XIRHXQ_Point(0, 10),
                          XIRHXQ_Point(3,-7)};
    XIRHXQ_Polygon world = XIRHXQ_Polygon(6, p);
    int robot_num = 17;
//    XIRHXQ_Point pos[10] = {XIRHXQ_Point(-3, 4),
//                            XIRHXQ_Point(2, 4),
//                            XIRHXQ_Point(-4, 1),
//                            XIRHXQ_Point(3, 2),
//                            XIRHXQ_Point(1, 1)};

    XIRHXQ_Swarm s = XIRHXQ_Swarm(robot_num, world);
    s.output();

    std::ofstream para_out;
    para_out.open(para_out_path);
    para_out << robot_num << std::endl;
    double x_lim[2], y_lim[2];
    s.get_x_limit(x_lim), s.get_y_limit(y_lim);
    para_out << x_lim[0] << ", " << x_lim[1] << ", " << y_lim[0] << ", " << y_lim[1] << std::endl;
    para_out.close();
    double t_total = 50, t_gap = 0.1;
    for (int iter = 1; iter <= t_total / t_gap; iter++) {
        s.cvt_forward(t_gap, f, pos_out_path, poly_out_path);
    }

    printf("After %.4lf seconds\n", t_total);
    s.output();
    return 0;
}