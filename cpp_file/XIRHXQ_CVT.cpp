// Created by XIRHXQ on 12/29/21.

#include "XIRHXQ_CVT.h"

#include <functional>

XIRHXQ_CVT::XIRHXQ_CVT() {

}

XIRHXQ_CVT::XIRHXQ_CVT(int _n, const XIRHXQ_Polygon &_wd) {
    n = _n;
    wd = _wd;
    for (int i = 1; i <= n; i++){
        pt[i] = XIRHXQ_Point();
        pl[i] = _wd;
    }
}

XIRHXQ_CVT::XIRHXQ_CVT(int _n, const XIRHXQ_Point *_pt, const XIRHXQ_Polygon &_wd) {
    n = _n;
    wd = _wd;
    for (int i = 1; i <= n; i++){
        pt[i] = _pt[i - 1];
        pl[i] = _wd;
    }
}

void XIRHXQ_CVT::reset_point(int _n, const XIRHXQ_Point *_pt) {
    n = _n;
    for (int i = 1; i <= n; i++){
        pt[i] = _pt[i - 1];
        pl[i] = wd;
    }
}

void XIRHXQ_CVT::cal_poly() {
    XIRHXQ_Line l;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i == j) continue;
            l = median_line(pt[i], pt[j]);
            pl[i].intersect_with_halfplane(l, pt[i]);
        }
    }
}

void XIRHXQ_CVT::output() {
    printf("An XIRHXQ_CVT with %d points:----------\n", n);
    for (int i = 1; i <= n; i++) {
        printf("Point #%d: ", i);
        pt[i].output();
        printf("Poly #%d: ", i);
        pl[i].output();
        printf("Centroid #%d: ", i);
        ct[i].output();
        printf("-------\n");
    }
    printf("---------------\n");
}

void XIRHXQ_CVT::cal_centroid(const std::function<double(XIRHXQ_Point)>& f, double spacing) {
    for (int i = 1; i <= n; i++){
        std::function<double(XIRHXQ_Point)> fx = [=](XIRHXQ_Point _p){return f(_p) * _p.x;};
        std::function<double(XIRHXQ_Point)> fy = [=](XIRHXQ_Point _p){return f(_p) * _p.y;};
        ct[i] = XIRHXQ_Point(pl[i].area_with_function(fx, spacing),
                             pl[i].area_with_function(fy, spacing)) /
                                     pl[i].area_with_function(f, spacing);
    }
}
