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

