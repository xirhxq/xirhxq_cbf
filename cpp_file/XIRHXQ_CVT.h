// Created by XIRHXQ on 12/29/21.

#ifndef CPP_V1_0_XIRHXQ_CVT_H
#define CPP_V1_0_XIRHXQ_CVT_H

#include "XIRHXQ_Polygon.h"

class XIRHXQ_CVT {
public:
    int n;
    XIRHXQ_Polygon wd;
    XIRHXQ_Point pt[maxp];
    XIRHXQ_Polygon pl[maxp];
    XIRHXQ_Point ct[maxp];
public:
    XIRHXQ_CVT();
    XIRHXQ_CVT(int _n, const XIRHXQ_Polygon &_wd);
    XIRHXQ_CVT(int _n, const XIRHXQ_Point _pt[], const XIRHXQ_Polygon &_wd);
    void reset_point(int _n, const XIRHXQ_Point _pt[]);
    void cal_poly();
    void output();
    void cal_centroid(const std::function<double(XIRHXQ_Point)>& f, double spacing);
};


#endif //CPP_V1_0_XIRHXQ_CVT_H
