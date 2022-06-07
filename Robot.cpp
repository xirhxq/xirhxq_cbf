//
// Created by xirhxq on 2022/3/3.
//

#include "Robot.h"

Robot::Robot() {}

Robot::Robot(const int &_d){
    G = MatrixXd::Identity(_d, _d);
    X.resize(_d);
    F.resize(_d);
}

Robot::Robot(VectorXd & _x) {
    X = _x;
    G = MatrixXd::Identity(_x.size(), _x.size());
    F.resize(_x.size());
}

Robot::Robot(MatrixXd& _g) {
    G = _g;
    X.resize(G.rows());
    F.resize(G.rows());
}

Robot::Robot(MatrixXd& _g, VectorXd& _x) {
    G = _g;
    X = _x;
    F.resize(G.rows());
}

Robot::Robot(VectorXd& _f, MatrixXd& _g) {
    F = _f;
    G = _g;
    X.resize(G.rows());
}

Robot::Robot(VectorXd& _f, MatrixXd& _g, VectorXd& _x) {
    F = _f;
    G = _g;
    X = _x;
}

VectorXd Robot::state() {
    return X;
}

void Robot::output() {
    std::cout << "------Robot State is:\n" << X << "\n----------------\n";
}

void Robot::time_forward(VectorXd& _dx, double _t) {
    X += (F + G * _dx) * _t;
}