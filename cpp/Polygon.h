// Created by XIRHXQ on 12/29/21.

#ifndef CPP_V1_0_POLYGON_H
#define CPP_V1_0_POLYGON_H

#include "utils.h"
//#include "Point.h"
#include "Line.h"

#include <functional>

class Polygon {
public:
    int n;
    Point p[maxp];
    Point in;

public:
    Polygon();
    Polygon(int n_, Point p_[]);

    void input();
    void output();

    void get_inner_point();
    void polar_sort();
    void simplify();
    void checking_convex();
    void rearrange();

    Point get_random_point();

    void direct_add(const Point &p_);
    void direct_delete_at_position(const Point &p_);
    void direct_delete_at_index(int &index);

    void add_one_point(const Point &p_);
    void delete_one_point_at_position(const Point &p_);
    void delete_one_point_at_index(int &index);

    void intersect_with_halfplane(Line &l_, int dir);
    void intersect_with_halfplane(Line &l_, Point &p_);
    void intersect_with_polygon(Polygon &p_);

    double circumference();
    double area();
    double area_with_function(const std::function<double(Point)>& f, double spacing);

    void get_x_limit(double x[]);
    void get_y_limit(double y[]);

};

#endif //CPP_V1_0_POLYGON_H
