// Created by XIRHXQ on 12/29/21.

#include "utils.h"
#include "XIRHXQ_Point.h"

XIRHXQ_Point::XIRHXQ_Point(){
    x = 0;
    y = 0;
}

XIRHXQ_Point::XIRHXQ_Point(double _x, double _y){
    x = _x;
    y = _y;
}

void XIRHXQ_Point::input(){
    scanf("%lf%lf", &x, &y);
}

void XIRHXQ_Point::output() const{
    printf("A XIRHXQ_Point @ (%.4lf, %.4lf)\n", x, y);
}

bool XIRHXQ_Point::operator == (const XIRHXQ_Point &b)const{
    return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
}

bool XIRHXQ_Point::operator < (const XIRHXQ_Point &b)const{
    return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
}

bool XIRHXQ_Point::operator > (const XIRHXQ_Point &b)const{
    return sgn(x - b.x) == 0 ? sgn(y - b.y) > 0 : x > b.x;
}

XIRHXQ_Point XIRHXQ_Point::operator + (const XIRHXQ_Point &b)const{
    return XIRHXQ_Point(x + b.x, y + b.y);
}

XIRHXQ_Point XIRHXQ_Point::operator - (const XIRHXQ_Point &b)const{
    return XIRHXQ_Point(x - b.x, y - b.y);
}

double XIRHXQ_Point::operator ^ (const XIRHXQ_Point &b)const{
    return x * b.y - y * b.x;
}

double XIRHXQ_Point::operator * (const XIRHXQ_Point &b)const{
    return x * b.x + y * b.y;
}

XIRHXQ_Point XIRHXQ_Point::operator * (const double b)const{
    return XIRHXQ_Point(x * b, y * b);
}

XIRHXQ_Point operator * (double a, const XIRHXQ_Point &p){
    return XIRHXQ_Point(p.x * a, p.y * a);
}

XIRHXQ_Point XIRHXQ_Point::operator / (const double b)const{
    return XIRHXQ_Point(x / b, y / b);
}

XIRHXQ_Point XIRHXQ_Point::operator - ()const{
    return XIRHXQ_Point(-x, -y);
}

double XIRHXQ_Point::len() const{
    return sqrt(x * x + y * y);
}

double XIRHXQ_Point::len2() const{
    return x * x + y * y;
}

double XIRHXQ_Point::angle() const{
    return atan2(y, x);
}

double XIRHXQ_Point::angle_to(const XIRHXQ_Point &b) const{
    return (b - *this).angle();
}

double XIRHXQ_Point::distance_to(const XIRHXQ_Point &b) const{
    return (b - *this).len();
}

XIRHXQ_Point XIRHXQ_Point::normalize() const{
    return *this / this->len();
}

XIRHXQ_Point XIRHXQ_Point::transform(double &b) const{
    return *this / this->len() * b;
}

XIRHXQ_Point XIRHXQ_Point::saturation(double &b){
    if (this->len() > b){
        return this->transform(b);
    }
    else return *this;
}

XIRHXQ_Point XIRHXQ_Point::rotate(double &b) const{
    double c = cos(this->angle()), s = sin(this->angle());
    return XIRHXQ_Point(x * c - y * s, x * s + y * c);
}

XIRHXQ_Point XIRHXQ_Point::rotate_around(const XIRHXQ_Point &p, double a) const{
    XIRHXQ_Point v = *this - p;
    double c = cos(a), s = sin(a);
    return XIRHXQ_Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
}