//
// Created by xirhxq on 2022/3/7.
//

#ifndef V7_0_ENERGY_CBF_H
#define V7_0_ENERGY_CBF_H

#include "CBF.h"

class Energy_CBF{
public:
    int x_ord = 0, y_ord = 1, b_ord = 2;
    std::vector<Point> charge_place;
    std::vector<double> charge_dist;
    double delta = 0.001;
    std::function<double(double)> alpha = [](double _h) {return 0.1 * pow(_h, 3);};


public:
    Energy_CBF();

    void new_charge_place(Point, double);
    int nearest_charge_place(Point);
    double dist_to_charge_place(Point);
    bool is_charging(Point);

    double h(VectorXd);
    double dh(VectorXd, int);
    double dh_dx(VectorXd);
    double dh_dy(VectorXd);
    double dh_db(VectorXd);

    Point constraint(VectorXd, Point);
};

#endif //V7_0_ENERGY_CBF_H
