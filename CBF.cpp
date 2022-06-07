//
// Created by xirhxq on 2022/3/7.
//

#include "CBF.h"

#include <utility>

CBF::CBF() {
}

//double CBF::h(VectorXd _v) {
//    return _v(2) - log(dist_to_charge_place(Point(_v)) / charge_dist[nearest_charge_place(Point(_v))]);
//}

double CBF::dh(VectorXd _x, int _i){
    VectorXd x_plus_dx = _x, x_minus_dx = _x;
    x_plus_dx(_i) += delta;
    x_minus_dx(_i) -= delta;
    return (h(x_plus_dx) - h(x_minus_dx)) / 2.0 / delta;
}



VectorXd CBF::dhdx(VectorXd _x) {
    VectorXd res = _x;
    for (int i = 0; i < _x.size(); i++){
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
