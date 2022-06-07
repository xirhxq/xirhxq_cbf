//
// Created by xirhxq on 2022/3/3.
//

#ifndef V7_0_ROBOT_H
#define V7_0_ROBOT_H

#include "utils.h"
#include "World.h"

class Robot {
public:
    MatrixXd G;
    VectorXd F, X;

public:
    Robot();
    explicit Robot(const int&);
    explicit Robot(VectorXd&);
    explicit Robot(MatrixXd&);
    Robot(MatrixXd&, VectorXd&);
    Robot(VectorXd&, MatrixXd&);
    Robot(VectorXd&, MatrixXd&, VectorXd&);

    VectorXd state();

    virtual void output();

    void time_forward(VectorXd&, double);
};


#endif //V7_0_ROBOT_H
