// Created by XIRHXQ on 12/29/21.

#include "CVT.h"

#include <functional>

CVT::CVT() {

}

CVT::CVT(int _n, const Polygon &_wd) {
    n = _n;
    wd = _wd;
    for (int i = 1; i <= n; i++){
        pt[i] = Point();
        pl[i] = _wd;
    }
}

CVT::CVT(int _n, const Point *_pt, const Polygon &_wd) {
    n = _n;
    wd = _wd;
    for (int i = 1; i <= n; i++){
        pt[i] = _pt[i - 1];
        pl[i] = _wd;
    }
}

void CVT::reset_point(int _n, const Point *_pt) {
    n = _n;
    for (int i = 1; i <= n; i++){
        pt[i] = _pt[i - 1];
        pl[i] = wd;
    }
}

void CVT::cal_poly() {
    Line l;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i == j) continue;
            l = median_line(pt[i], pt[j]);
            pl[i].intersect_with_halfplane(l, pt[i]);
        }
    }
}

void CVT::output() {
    printf("An CVT with %d points:----------\n", n);
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

void CVT::cal_centroid(const std::function<double(Point)>& f, double spacing) {
    for (int i = 1; i <= n; i++){
        std::function<double(Point)> fx = [=](Point _p){return f(_p) * _p.x;};
        std::function<double(Point)> fy = [=](Point _p){return f(_p) * _p.y;};
        ct[i] = Point(pl[i].area_with_function(fx, spacing),
                      pl[i].area_with_function(fy, spacing)) /
                pl[i].area_with_function(f, spacing);
    }
}
