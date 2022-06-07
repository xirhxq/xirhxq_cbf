// Created by XIRHXQ on 12/29/21.
#ifndef CPP_V1_0_UTILS_H
#define CPP_V1_0_UTILS_H

#include <iostream>
#include <cmath>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 110;

inline int index_before(int n, int id, int d){
    int res = id - (d % n);
    if (res < 1) res += n;
    return res;
}

inline int index_after(int n, int id, int d){
    int res = id + (d % n);
    if (res > n) res -= n;
    return res;
}

inline int sgn(double val){
    if (fabs(val) < eps) return 0;
    if (val < 0) return -1;
    else return 1;
}

#endif //CPP_V1_0_UTILS_H
