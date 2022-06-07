// Created by XIRHXQ on 12/29/21.

#include "utils.h"
#include "Point.h"

Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(double _x, double _y){
    x = _x;
    y = _y;
}

void Point::input(){
    scanf("%lf%lf", &x, &y);
}

void Point::output() const{
    printf("A Point @ (%.4lf, %.4lf)\n", x, y);
}

bool Point::operator == (const Point &b)const{
    return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
}

bool Point::operator < (const Point &b)const{
    return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
}

bool Point::operator > (const Point &b)const{
    return sgn(x - b.x) == 0 ? sgn(y - b.y) > 0 : x > b.x;
}

Point Point::operator + (const Point &b)const{
    return Point(x + b.x, y + b.y);
}

Point Point::operator - (const Point &b)const{
    return Point(x - b.x, y - b.y);
}

double Point::operator ^ (const Point &b)const{
    return x * b.y - y * b.x;
}

double Point::operator * (const Point &b)const{
    return x * b.x + y * b.y;
}

Point Point::operator * (const double b)const{
    return Point(x * b, y * b);
}

Point operator * (double a, const Point &p){
    return Point(p.x * a, p.y * a);
}

Point Point::operator / (const double b)const{
    return Point(x / b, y / b);
}

Point Point::operator - ()const{
    return Point(-x, -y);
}

double Point::len() const{
    return sqrt(x * x + y * y);
}

double Point::len2() const{
    return x * x + y * y;
}

double Point::angle() const{
    return atan2(y, x);
}

double Point::angle_to(const Point &b) const{
    return (b - *this).angle();
}

double Point::distance_to(const Point &b) const{
    return (b - *this).len();
}

Point Point::normalize() const{
    return *this / this->len();
}

Point Point::transform(double &b) const{
    return *this / this->len() * b;
}

Point Point::saturation(double &b){
    if (this->len() > b){
        return this->transform(b);
    }
    else return *this;
}

Point Point::rotate(double &b) const{
    double c = cos(this->angle()), s = sin(this->angle());
    return Point(x * c - y * s, x * s + y * c);
}

Point Point::rotate_around(const Point &p, double a) const{
    Point v = *this - p;
    double c = cos(a), s = sin(a);
    return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
}