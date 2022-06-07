// Created by XIRHXQ on 12/29/21.

#ifndef V8_0_CVT_H
#define V8_0_CVT_H

#include "Polygon.h"

class CVT {
public:
    int n;
    Polygon wd;
    Point pt[maxp];
    Polygon pl[maxp];
    Point ct[maxp];
public:
    CVT();
    CVT(int _n, const Polygon &_wd);
    CVT(int _n, const Point _pt[], const Polygon &_wd);
    void reset_point(int _n, const Point _pt[]);
    void cal_poly();
    void output();
    void cal_centroid(const std::function<double(Point)>& f, double spacing);
};


#endif //V8_0_CVT_H
