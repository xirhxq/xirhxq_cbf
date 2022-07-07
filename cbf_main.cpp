#include "utils.h"
#include "computing_geometry/Point.h"
#include "Swarm.h"

#include <fstream>
#include <ctime>

Point loop(double x_min, double x_max, double y_min, double y_max, double t, double v){
    double dxt = (x_max - x_min) / v, dyt = (y_max - y_min) / v;
    double dt = 2 * dxt + 2 * dyt;
    while (t >= dt) t -= dt;
    if (t < dxt){
        return {x_min + v * t, y_min};
    }
    else if (t < dxt + dyt){
        return {x_max, y_min + (t - dxt) * v};
    }
    else if (t < 2 * dxt + dyt){
        return {x_max - (t - dxt - dyt) * v, y_max};
    }
    else {
        return {x_min, y_max - (t - 2 * dxt - dyt) * v};
    }
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

    // dens = e ^ (- k * |distance - r|)
    double target_x_min = 8, target_x_max = 12, target_y_min = 4, target_y_max = 6;
    double target_v = 0.5;
    double dens_k = 10, dens_r = 2;

    World wd(wd_p, c);
    wd.dens = [=](Point p_, double t_) {
        return exp(-fabs((p_ - loop(target_x_min, target_x_max,
                                    target_y_min, target_y_max,
                                    t_, target_v)).len() - dens_r) * dens_k);
    };
    wd.target_pos = [=] (double t_) {
        return loop(target_x_min, target_x_max,
                    target_y_min, target_y_max,
                    t_, target_v);
    };

    Swarm s = Swarm(6, wd);
    s.set_h();
    s.init_log_path(data_out_path);
    s.para_log_once();
    s.data_j["para"]["dens"]["k"] = dens_k;
    s.data_j["para"]["dens"]["r"] = dens_r;

    s.output();

    double t_total = 40, t_gap = 0.02;
    for (int iter = 1; iter <= t_total / t_gap; iter++) {
        s.set_h_with_time();
        s.log_once();
//        printf("time : %.2lf -------------\n", t_gap * iter);
//        s.time_forward(t_gap);
        s.cvt_forward(t_gap);
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