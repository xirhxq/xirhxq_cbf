//
// Created by xirhxq on 2022/3/1.
//

#ifndef V6_0_MATRIX_H
#define V6_0_MATRIX_H

#include "utils.h"


class Matrix {
public:
    int r, c;
    double d[mat_max][mat_max]{};

public:
    Matrix();
    Matrix(int, int);
    Matrix(int, int, double[][mat_max]);

    void output();

    bool operator == (const Matrix &b)const;
    bool operator < (const Matrix &b)const;
    bool operator <= (const Matrix &b)const;
    bool operator > (const Matrix &b)const;
    bool operator >= (const Matrix &b)const;

    Matrix operator + (const Matrix &b)const;
    Matrix operator - (const Matrix &b)const;
    Matrix operator * (const Matrix &b)const;
    Matrix operator * (const double &a)const;

};

Matrix operator * (const double &a, const Matrix &m);

#endif //V6_0_MATRIX_H
