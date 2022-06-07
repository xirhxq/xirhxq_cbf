// Created by XIRHXQ on 12/29/21.

#ifndef CPP_V1_0_XIRHXQ_LINE_H
#define CPP_V1_0_XIRHXQ_LINE_H

#include "XIRHXQ_Point.h"

class XIRHXQ_Line {
    XIRHXQ_Point s;
    XIRHXQ_Point e;
public:
    XIRHXQ_Line();
    XIRHXQ_Line(const XIRHXQ_Point &_s, const XIRHXQ_Point &_e);
    XIRHXQ_Line(const XIRHXQ_Point &_s, double a);
    XIRHXQ_Line(double _a, double _b, double _c);

    void input();
    void output() const;

    void adjust();
    double len();
    double len2();
    double angle();

    int relation(const XIRHXQ_Point &p);
    int relation_to_seg(const XIRHXQ_Point &p);

    bool is_on_line(const XIRHXQ_Point &p);
    bool is_on_seg(const XIRHXQ_Point &p);

    bool is_parallel(const XIRHXQ_Line &l);
    bool is_the_same_line(const XIRHXQ_Line &l);

    bool line_cross_line(const XIRHXQ_Line &l);
    XIRHXQ_Point cross_point(const XIRHXQ_Line &l);

    bool line_cross_seg(const XIRHXQ_Line &l);
    bool seg_cross_seg(XIRHXQ_Line &l);

    double dis_line_to_point(const XIRHXQ_Point &p);
    double dis_seg_to_point(const XIRHXQ_Point &p);
    double dis_seg_to_seg(XIRHXQ_Line &l);

    XIRHXQ_Point project_point(const XIRHXQ_Point &p);
    XIRHXQ_Point symmetry_point(const XIRHXQ_Point &p);
};

XIRHXQ_Line median_line(XIRHXQ_Point &p, XIRHXQ_Point &q);
#endif //CPP_V1_0_XIRHXQ_LINE_H
