// Created by XIRHXQ on 12/29/21.

#include "utils.h"
#include "XIRHXQ_Line.h"

XIRHXQ_Line::XIRHXQ_Line() {
    s = XIRHXQ_Point(0, 0);
    e = XIRHXQ_Point(1, 0);
    adjust();
}

XIRHXQ_Line::XIRHXQ_Line(const XIRHXQ_Point &_s, const XIRHXQ_Point &_e) {
    s = _s;
    e = _e;
    adjust();
}

XIRHXQ_Line::XIRHXQ_Line(const XIRHXQ_Point &_s, double a) {
    s = _s;
    if (sgn(a - pi / 2) == 0){
        e = s + XIRHXQ_Point(0, 1);
    }
    else{
        e = s + XIRHXQ_Point(1, tan(a));
    }
}

XIRHXQ_Line::XIRHXQ_Line(double _a, double _b, double _c) {
    if (sgn(_a) == 0){
        s = XIRHXQ_Point(0, -_c / _b);
        e = XIRHXQ_Point(1, -_c / _b);
    }
    else if (sgn(_b) == 0){
        s = XIRHXQ_Point(-_c / _a, 0);
        e = XIRHXQ_Point(-_c / _a, 1);
    }
    else{
        s = XIRHXQ_Point(0, -_c / _b);
        e = XIRHXQ_Point(1, -(_c + _a) / _b);
    }
    adjust();
}

void XIRHXQ_Line::input(){
    s.input();
    e.input();
}

void XIRHXQ_Line::output() const {
    printf("A XIRHXQ_Line from (%.4lf, %.4lf) to (%.4lf, %.4lf)\n", s.x, s.y, e.x, e.y);
}

void XIRHXQ_Line::adjust() {
    if (s > e){
        XIRHXQ_Point tmp_point = s;
        s = e;
        e = tmp_point;
    }
}

double XIRHXQ_Line::len() {
    return s.distance_to(e);
}

double XIRHXQ_Line::len2() {
    return (s - e).len2();
}

double XIRHXQ_Line::angle() {
    return (e - s).angle();
}

int XIRHXQ_Line::relation(const XIRHXQ_Point &p) {
    int c = sgn((p - s) ^ (p - e));
    if (c < 0) return -1;
    else if (c > 0) return 1;
    else return 0;
}

int XIRHXQ_Line::relation_to_seg(const XIRHXQ_Point &p) {
    return sgn((p - s) ^ (e - s)) == 0 && sgn((p - s) * (p - e)) <= 0;
}

bool XIRHXQ_Line::is_on_line(const XIRHXQ_Point &p) {
    return relation(p) == 0;
}

bool XIRHXQ_Line::is_on_seg(const XIRHXQ_Point &p) {
    return relation_to_seg(p) == 0;
}

bool XIRHXQ_Line::is_parallel(const XIRHXQ_Line &l) {
    return sgn((e - s) ^ (l.e - l.s)) == 0;
}

bool XIRHXQ_Line::is_the_same_line(const XIRHXQ_Line &l) {
    return is_on_line(l.s) && is_on_line(l.e);
}

bool XIRHXQ_Line::line_cross_line(const XIRHXQ_Line &l) {
    return !is_parallel(l);
}

XIRHXQ_Point XIRHXQ_Line::cross_point(const XIRHXQ_Line &l) {
    double a1 = (l.e - l.s) ^ (s - l.s);
    double a2 = (l.e - l.s) ^ (e - l.s);
    return XIRHXQ_Point((s.x * a2 - e.x * a1) / (a2 - a1),
                        (s.y * a2 - e.y * a1) / (a2 - a1));
}

bool XIRHXQ_Line::line_cross_seg(const XIRHXQ_Line &l) {
    return (!is_parallel(l)) && (relation(l.s) * relation(l.e) < 0);
}

bool XIRHXQ_Line::seg_cross_seg(XIRHXQ_Line &l) {
    if (!is_parallel(l)) return false;
    XIRHXQ_Point cp = cross_point(l);
    return is_on_seg(cp) && l.is_on_seg(cp);
}

double XIRHXQ_Line::dis_line_to_point(const XIRHXQ_Point &p) {
    return fabs((p - s) ^ (e - s)) / len();
}

double XIRHXQ_Line::dis_seg_to_point(const XIRHXQ_Point &p) {
    if (sgn((p - s) * (e - s)) < 0 || sgn((p - e) * (s - e) < 0)){
        return fmin(s.distance_to(p), e.distance_to(p));
    }
    return dis_line_to_point(p);
}

double XIRHXQ_Line::dis_seg_to_seg(XIRHXQ_Line &l) {
    return fmin(fmin(dis_seg_to_point(l.s), dis_seg_to_point(l.e)),
               fmin(l.dis_seg_to_point(s), l.dis_seg_to_point(e)));
}

XIRHXQ_Point XIRHXQ_Line::project_point(const XIRHXQ_Point &p) {
    return s + (((e - s) * ((e - s) * (p - s))) / (e - s).len2() );
}

XIRHXQ_Point XIRHXQ_Line::symmetry_point(const XIRHXQ_Point &p) {
    XIRHXQ_Point q = project_point(p);
    return q * 2.0 - p;
}

XIRHXQ_Line median_line(XIRHXQ_Point &p, XIRHXQ_Point &q){
    return XIRHXQ_Line((p + q) / 2.0, p.angle_to(q) + pi / 2);
}