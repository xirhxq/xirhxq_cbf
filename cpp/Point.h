// Created by XIRHXQ on 12/29/21.

#ifndef CPP_V1_0_POINT_H
#define CPP_V1_0_POINT_H

class Point{
public:
    double x;
    double y;
public:
    Point();
    Point(double _x, double _y);
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

#endif //CPP_V1_0_POINT_H