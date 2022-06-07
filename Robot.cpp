//
// Created by xirhxq on 2022/3/3.
//

#include "Robot.h"

Robot::Robot() = default;

Robot::Robot(int _d) {
    G = MatrixXd::Identity(_d, _d);
    X.resize(_d);
    F.resize(_d);
}

void Robot::set_position(Point _p) {
    X(x_ord) = _p.x;
    X(y_ord) = _p.y;
}

void Robot::set_battery(double _b) {
    if (X.size() > 2){
        X(batt_ord) = _b;
    }
}

void Robot::set_xy_order(int _x_ord, int _y_ord) {
    x_ord = _x_ord;
    y_ord = _y_ord;
}

double Robot::x(){
    return X(x_ord);
}

double Robot::y() {
    return X(y_ord);
}

double Robot::batt() {
    return X(batt_ord);
}

double Robot::camera() {
    return X(camera_ord);
}


Point Robot::xy() {
    return Point(X(x_ord), X(y_ord));
}

void Robot::time_forward(VectorXd& _v, double _t, World _w) {
    if (_w.is_charging(X) && X(batt_ord) <= 40.0){
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
                var_v.push_back(model.addVar(-100.0, 100.0, 0.0, GRB_CONTINUOUS, s));
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

//            std::cout << "Model contains: " << std::endl;
//            std::cout << "_v" << std::endl <<  _v << std::endl;
//            std::cout << "u_coe" << std::endl << u_coe << std::endl;
//            std::cout << "const " << -energy_cbf.constraint_const(F, G, X) << std::endl;

            // Optimize model
//            model.set(GRB_IntParam_OutputFlag, 0);
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
            assert(0);
        } catch(...) {
            std::cout << "Exception during optimization" << std::endl;
            assert(0);
        }

        X += (F + G * opt_res) * _t;
    }
}

void Robot::output() {
    std::cout << "A UGV @ (" << x() << ", " << y() << ")";
    if (X.size() > 2){
        std::cout << " with Battery " << X(batt_ord);
    }
    std::cout << std::endl;
}
