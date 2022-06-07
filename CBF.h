//
// Created by xirhxq on 2022/3/7.
//

#ifndef V9_0_CBF_H
#define V9_0_CBF_H

#include "computing_geometry/Line.h"

class CBF{
public:
    double delta = 0.001;
    std::function<double(double)> alpha = [](double _h) {return 0.1 * pow(_h, 3);};
    std::function<double(VectorXd)> h;

public:
    CBF();

    double dh(VectorXd, int);

    VectorXd dhdx(VectorXd);
    VectorXd constraint_u_coe(VectorXd&, MatrixXd&, VectorXd&);
    double constraint_const(VectorXd&, MatrixXd&, VectorXd&);
};

#endif //V9_0_CBF_H
