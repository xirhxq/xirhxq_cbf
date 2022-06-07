//
// Created by xirhxq on 2022/2/28.
//

#ifndef V7_0_CBF_H
#define V7_0_CBF_H
#include "Line.h"

class CBF {
public:
    std::function<double(VectorXd)> h;
    double delta = 0.05;
    std::function<double(double)> alpha = [](double _h) {return 0.1 * pow(_h, 3);};

public:
    CBF();
    CBF(std::function<double(VectorXd)>&);

    virtual double dh(VectorXd, int);
};


#endif //V7_0_CBF_H
