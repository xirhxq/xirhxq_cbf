// Created by XIRHXQ on 12/29/21.

#ifndef CPP_V1_0_XIRHXQ_POINT_H
#define CPP_V1_0_XIRHXQ_POINT_H

class XIRHXQ_Point{
public:
    double x;
    double y;
public:
    XIRHXQ_Point();
    XIRHXQ_Point(double _x, double _y);
    void input();
    void output() const;

    bool operator == (const XIRHXQ_Point &b)const;
    bool operator < (const XIRHXQ_Point &b)const;
    bool operator > (const XIRHXQ_Point &b)const;

    XIRHXQ_Point operator + (const XIRHXQ_Point &b)const;
    XIRHXQ_Point operator - (const XIRHXQ_Point &b)const;

    double operator ^ (const XIRHXQ_Point &b)const;
    double operator * (const XIRHXQ_Point &b)const;
    XIRHXQ_Point operator * (double b)const;

    XIRHXQ_Point operator / (double b)const;

    XIRHXQ_Point operator - ()const;

    double len() const;
    double len2() const;
    double angle() const;
    double angle_to(const XIRHXQ_Point &b) const;
    double distance_to(const XIRHXQ_Point &b) const;
    XIRHXQ_Point normalize() const;
    XIRHXQ_Point transform(double &b) const;
    XIRHXQ_Point saturation(double &b);
    XIRHXQ_Point rotate(double &b) const;
    XIRHXQ_Point rotate_around(const XIRHXQ_Point &b, double a) const;

};

XIRHXQ_Point operator * (double a, const XIRHXQ_Point &p);

#endif //CPP_V1_0_XIRHXQ_POINT_H