//
// Created by xirhxq on 2022/2/28.
//

#include "CBF.h"

#include <utility>

CBF::CBF() = default;

CBF::CBF(std::function<double(Point, double)>& _h) {
    h = std::move(_h);
}

CBF::CBF(std::function<double(Point, double)>& _h, std::function<double(Point, double)>& _hx,
         std::function<double(Point, double)>& _hy, std::function<double(Point, double)>& _hb) {
    h = std::move(_h);
    hx = std::move(_hx);
    hy = std::move(_hy);
    hb = std::move(_hb);
}

double CBF::get_h(Point _p, double _b) {
    return h(_p, _b);
}

double CBF::get_hx(Point _p, double _b) {
    return hx(_p, _b);
}

double CBF::get_hy(Point _p, double _b) {
    return hy(_p, _b);
}

double CBF::get_hb(Point _p, double _b) {
    return hb(_p, _b);
}

Point CBF::constraint(Point _p, double _b, Point _v) {
    double alpha_h = alpha(h(_p, _b));
    Point hxy = Point(hx(_p, _b), hy(_p, _b));
    if (_v * hxy + alpha_h - hb(_p, _b) >= 0){
        return _v;
    }
    else {
        return Line(hxy.x, hxy.y, alpha_h - hb(_p, _b)).project_point(_v);
    }
}
