// Created by XIRHXQ on 12/29/21.

#ifndef V9_0_LINE_H
#define V9_0_LINE_H

#include "Point.h"

class Line {
    Point s;
    Point e;
public:
    Line();
    Line(const Point &_s, const Point &_e);
    Line(const Point &_s, double a);
    Line(double _a, double _b, double _c);

    void input();
    void output() const;

    void adjust();
    double len();
    double len2();
    double angle();

    int relation(const Point &p);
    int relation_to_seg(const Point &p);

    bool is_on_line(const Point &p);
    bool is_on_seg(const Point &p);

    bool is_parallel(const Line &l);
    bool is_the_same_line(const Line &l);

    bool line_cross_line(const Line &l);
    Point cross_point(const Line &l);

    bool line_cross_seg(const Line &l);
    bool seg_cross_seg(Line &l);

    double dis_line_to_point(const Point &p);
    double dis_seg_to_point(const Point &p);
    double dis_seg_to_seg(Line &l);

    Point project_point(const Point &p);
    Point symmetry_point(const Point &p);
};

Line median_line(Point &p, Point &q);
#endif //V9_0_LINE_H
