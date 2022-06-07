//
// Created by xirhxq on 2022/3/3.
//

#include "First_Order_UGV.h"

First_Order_UGV::First_Order_UGV() = default;

First_Order_UGV::First_Order_UGV(int _d) : Robot(_d){
    G(2, 2) = 0;
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

void First_Order_UGV::time_forward(VectorXd& _v, double _t, World _w) {
    if (is_charging()){
        X(batt_ord) += _t * (10);
    }
    else{
        VectorXd opt_res = _v;
        try {
            // Create an environment
            GRBEnv env = GRBEnv(true);
            env.set("LogFile", "energy_cbf.log");
            env.set("OutputFlag", "0");
            env.start();

            // Create an empty model
            GRBModel model = GRBModel(env);

            // Create variables
            std::vector<GRBVar> var_v;
            char s[10];
            for (int i = 0; i < X.size(); i++){
                sprintf(s, "var_%d", i);
                var_v.push_back(model.addVar(-10.0, 10.0, 0.0, GRB_CONTINUOUS, s));
            }

            // Set objective:
            GRBQuadExpr obj = 0.0;
            for (int i = 0; i < X.size(); i++){
                obj += (var_v[i] - _v[i]) * (var_v[i] - _v[i]);
            }
            model.setObjective(obj, GRB_MINIMIZE);

            // Add constraint:
            GRBLinExpr c = 0.0;
            VectorXd u_coe = energy_cbf.constraint_u_coe(F, G, X);
            for (int i = 0; i < X.size(); i++){
                c += u_coe(i) * var_v[i];
            }
            model.addConstr(c, '>', -energy_cbf.constraint_const(F, G, X));

            // Optimize model
            model.set(GRB_IntParam_OutputFlag, 0);
            model.optimize();

            for (int i = 0; i < X.size(); i++) opt_res(i)  = var_v[i].get(GRB_DoubleAttr_X);

//            for (int i = 0; i < X.size(); i++){
//                std::cout << var_v[i].get(GRB_StringAttr_VarName) << " "
//                    << var_v[i].get(GRB_DoubleAttr_X) << std::endl;
//            }
//
//            std::cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << std::endl;

        } catch(GRBException e) {
            std::cout << "Error code = " << e.getErrorCode() << std::endl;
            std::cout << e.getMessage() << std::endl;
        } catch(...) {
            std::cout << "Exception during optimization" << std::endl;
        }



        Point tmp = energy_cbf.constraint(X, Point(_v));
        VectorXd u{3};
        u << tmp.x, tmp.y, 0;
//        std::cout << "get best input: " << tmp.x << " " << tmp.y << std::endl;
        if ((opt_res - u).norm() > 1e-1){
            std::cout << "error between optimiser and computing geometry : --------" << std::endl;
            std::cout << "from optimiser: " << std::endl << opt_res << std::endl;
//            for (int i = 0; i < opt_res.size(); i++) std::cout << opt_res(i) << " ";
//            std::cout << std::endl;
            std::cout << "from computing geometry: " << std::endl << u << std::endl;
//            for (int i = 0; i < u.size(); i++) std::cout << u(i) << " ";
//            std::cout << std::endl;
            assert(0);
        }
        Robot::time_forward(opt_res, _t);
//        Robot::time_forward(u, _t);
    }
}

void First_Order_UGV::output() {
    std::cout << "A UGV @ (" << x() << ", " << y() << ")";
    if (X.size() > 2){
        std::cout << " with Battery " << X(batt_ord);
    }
    std::cout << std::endl;
}
