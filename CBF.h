//
// Created by xirhxq on 2022/2/28.
//

#ifndef V6_0_CBF_H
#define V6_0_CBF_H
#include "Line.h"

class CBF {
public:
    std::function<double(Point, double)> h, hx, hy, hb;
    std::function<double(double)> alpha = [](double _h) {return 0.1 * pow(_h, 3);};

public:
    CBF();
    CBF(std::function<double(Point, double)>&);
    CBF(std::function<double(Point, double)>&, std::function<double(Point, double)>&,
        std::function<double(Point, double)>&, std::function<double(Point, double)>&);

    double get_h(Point, double);
    double get_hx(Point ,double);
    double get_hy(Point, double);
    double get_hb(Point, double);

    Point constraint(Point, double, Point);
};


#endif //V6_0_CBF_H
