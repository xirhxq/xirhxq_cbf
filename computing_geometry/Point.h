// Created by XIRHXQ on 12/29/21.

#ifndef V9_0_POINT_H
#define V9_0_POINT_H

#include "../utils.h"

class Point{

public:
    double x, y;

public:
    Point();
    Point(double _x, double _y);
    Point(const Point &);
    Point(const Eigen::VectorXd&);
    Eigen::VectorXd vec();

    void input();
    void output() const;

    bool operator == (const Point &b)const;
    bool operator < (const Point &b)const;
    bool operator > (const Point &b)const;

    Point operator + (const Point &b)const;
    Point operator - (const Point &b)const;

    double operator ^ (const Point &b)const;
    double operator * (const Point &b)const;
    Point operator * (double b)const;

    Point operator / (double b)const;

    Point operator - ()const;

    double len() const;
    double len2() const;
    double angle() const;
    double angle_to(const Point &b) const;
    double distance_to(const Point &b) const;
    Point normalize() const;
    Point transform(double &b) const;
    Point saturation(double &b);
    Point rotate(double &b) const;
    Point rotate_around(const Point &b, double a) const;

};

Point operator * (double a, const Point &p);

#endif //V9_0_POINT_H