//
// Created by xirhxq on 2022/2/28.
//

#include "CBF.h"

#include <utility>

CBF::CBF() = default;

CBF::CBF(std::function<double(VectorXd)>& _h) {
    h = std::move(_h);
}

double CBF::dh(VectorXd _x, int _i){
    VectorXd x_dx = _x;
    x_dx(_i) += delta;
    return (h(x_dx) - h(_x)) / delta;
}

VectorXd CBF::dhdx(VectorXd _x) {
    VectorXd res = _x;
    for (int i = 0; i <= _x.size(); i++){
        res(i) = dh(_x, i);
    }
    return res;
}

VectorXd CBF::constraint_u_coe(VectorXd& _f, MatrixXd& _g, VectorXd& _x) {
    return dhdx(_x).transpose() * _g;
}

double CBF::constraint_const(VectorXd & _f, MatrixXd & _g, VectorXd & _x) {
    return dhdx(_x).dot(_f) + alpha(h(_x));
}