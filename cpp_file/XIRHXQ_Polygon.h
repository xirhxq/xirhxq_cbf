// Created by XIRHXQ on 12/29/21.

#ifndef CPP_V1_0_XIRHXQ_POLYGON_H
#define CPP_V1_0_XIRHXQ_POLYGON_H

#include "utils.h"
//#include "XIRHXQ_Point.h"
#include "XIRHXQ_Line.h"

#include <functional>

class XIRHXQ_Polygon {
public:
    int n;
    XIRHXQ_Point p[maxp];
    XIRHXQ_Point in;

public:
    XIRHXQ_Polygon();
    XIRHXQ_Polygon(int n_, XIRHXQ_Point p_[]);

    void input();
    void output();

    void get_inner_point();
    void polar_sort();
    void simplify();
    void checking_convex();
    void rearrange();

    XIRHXQ_Point get_random_point();

    void direct_add(const XIRHXQ_Point &p_);
    void direct_delete_at_position(const XIRHXQ_Point &p_);
    void direct_delete_at_index(int &index);

    void add_one_point(const XIRHXQ_Point &p_);
    void delete_one_point_at_position(const XIRHXQ_Point &p_);
    void delete_one_point_at_index(int &index);

    void intersect_with_halfplane(XIRHXQ_Line &l_, int dir);
    void intersect_with_halfplane(XIRHXQ_Line &l_, XIRHXQ_Point &p_);
    void intersect_with_polygon(XIRHXQ_Polygon &p_);

    double circumference();
    double area();
    double area_with_function(const std::function<double(XIRHXQ_Point)>& f, double spacing);

    void get_x_limit(double x[]);
    void get_y_limit(double y[]);

};

#endif //CPP_V1_0_XIRHXQ_POLYGON_H
