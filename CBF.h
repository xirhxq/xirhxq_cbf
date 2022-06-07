//
// Created by xirhxq on 2022/2/28.
//

#ifndef V8_0_CBF_H
#define V8_0_CBF_H
#include "utils.h"

class CBF {
public:
    std::function<double(VectorXd)> h;
    double delta = 0.05;
    std::function<double(double)> alpha = [](double _h) {return 0.1 * pow(_h, 3);};

public:
    CBF();
    CBF(std::function<double(VectorXd)>&);

    double dh(VectorXd, int);

    VectorXd dhdx(VectorXd);
    VectorXd constraint_u_coe(VectorXd&, MatrixXd&, VectorXd&);
    double constraint_const(VectorXd&, MatrixXd&, VectorXd&);
};


#endif //V8_0_CBF_H
