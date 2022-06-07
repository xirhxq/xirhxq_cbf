//
// Created by xirhxq on 2022/3/3.
//

#ifndef V8_0_FIRST_ORDER_UGV_H
#define V8_0_FIRST_ORDER_UGV_H

#include "Robot.h"
#include "utils.h"
#include "computing_geometry/Point.h"
#include "Energy_CBF.h"
#include "World.h"

class First_Order_UGV: public Robot{
public:
    int x_ord = 0, y_ord = 1, batt_ord = 2;
    Energy_CBF energy_cbf;

public:
    First_Order_UGV();
    explicit First_Order_UGV(int);
    explicit First_Order_UGV(VectorXd&);
    explicit First_Order_UGV(MatrixXd&);
    First_Order_UGV(MatrixXd&, VectorXd&);
    First_Order_UGV(VectorXd&, MatrixXd&);
    First_Order_UGV(VectorXd&, MatrixXd&, VectorXd&);

    void set_position(Point);
    void set_battery(double);

    void set_xy_order(int, int);

    double x();
    double y();
    double batt();
    bool is_charging();

    Point xy();

    void time_forward(VectorXd &_v, double _t, World _w);

    void output();
};


#endif //V8_0_FIRST_ORDER_UGV_H
