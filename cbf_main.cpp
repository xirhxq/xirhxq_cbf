#include "utils.h"
#include "computing_geometry/Point.h"
#include "Swarm.h"

#include <fstream>
#include <ctime>

double f(Point _p, double t) {
//    return 1;
//    if (t <= 20)    return 1;
//    else if (t <= 40) return exp(-(_p-Point(5, 5)).len2());
//    else if (t <= 70) return 10 * exp(-fmax((_p-Point(2.5, 2.5)).len2(), 4));
//    double mid = fabs((_p-Point(2.5, 2.5)).len2() - 4);
//    double mid = fabs(_p.x + _p.y - 5);
//    return 10000 * exp(-mid * mid);
//    return exp(-fabs((_p.len2() - 4)) * 2 );
    return exp(-fabs((_p - Point(10.0, 5.0)).len() - 4) * 5);
}

int main() {
    clock_t start = clock();

    time_t tt = time(NULL);
    tm *t = localtime(&tt);
    char data_out_path[256];
    sprintf(data_out_path, R"(../data/%02d-%02d_%02d-%02d_data.json)",
            t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);


    Polygon wd_p({  Point(0, 0),
                    Point(20, 0),
                    Point(0, 10),
                    Point(20, 10)
    });

    std::vector<Point> c = {Point(19.0, 2.0),
                            Point(19.0, 4.0),
                            Point(19.0, 6.0),
                            Point(19.0, 8.0),
                            Point(1.0, 2.0),
                            Point(1.0, 4.0),
                            Point(1.0, 6.0),
                            Point(1.0, 8.0)};
    World wd(wd_p, c);

    Swarm s = Swarm(6, wd);
    s.set_h();
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

    clock_t finish = clock();
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%.4lf seconds passed!\n", duration);
    return 0;
}