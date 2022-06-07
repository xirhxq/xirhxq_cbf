//
// Created by xirhxq on 2022/3/3.
//

#include "First_Order_UGV.h"

First_Order_UGV::First_Order_UGV() = default;

First_Order_UGV::First_Order_UGV(int _d) : Robot(_d){
}

First_Order_UGV::First_Order_UGV(VectorXd& _x) : Robot(_x.size()){
    X = _x;
}

First_Order_UGV::First_Order_UGV(MatrixXd& _g) : Robot(_g.rows()){
    G = _g;
}

First_Order_UGV::First_Order_UGV(MatrixXd& _g, VectorXd& _x) : Robot(_g.rows()){
    G = _g;
    X = _x;
}

First_Order_UGV::First_Order_UGV(VectorXd& _f, MatrixXd& _g) : Robot(_g.rows()){
    F = _f;
    G = _g;
}

First_Order_UGV::First_Order_UGV(VectorXd& _f, MatrixXd& _g, VectorXd& _x) : Robot(_x.size()){
    F = _f;
    G = _g;
    X = _x;
}

void First_Order_UGV::set_position(Point _p) {
    X(x_ord) = _p.x;
    X(y_ord) = _p.y;
}

void First_Order_UGV::set_battery(double _b) {
    if (X.size() > 2){
        X(batt_ord) = _b;
    }
}

void First_Order_UGV::set_xy_order(int _x_ord, int _y_ord) {
    x_ord = _x_ord;
    y_ord = _y_ord;
}

double First_Order_UGV::x(){
    return X(x_ord);
}

double First_Order_UGV::y() {
    return X(y_ord);
}

double First_Order_UGV::batt() {
    return X(batt_ord);
}

bool First_Order_UGV::is_charging() {
    return energy_cbf.is_charging(Point(X)) && batt() <= 40;
}

Point First_Order_UGV::xy() {
    return Point(X(x_ord), X(y_ord));
}

void First_Order_UGV::CVT_forward(VectorXd& _v, double _t, World _w) {
    if (is_charging()){
        X(batt_ord) += _t * (10);
    }
    else{
        Point tmp = energy_cbf.constraint(X, Point(_v));
        VectorXd u{3};
        u << tmp.x, tmp.y, 0;
        time_forward(u, _t);
    }
}

void First_Order_UGV::output() {
    std::cout << "A UGV @ (" << x() << ", " << y() << ")";
    if (X.size() > 2){
        std::cout << " with Battery " << X(batt_ord);
    }
    std::cout << std::endl;
}
