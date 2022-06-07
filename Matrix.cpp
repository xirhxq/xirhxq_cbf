//
// Created by xirhxq on 2022/3/1.
//

#include <cstring>
#include "Matrix.h"

Matrix::Matrix() {

}

Matrix::Matrix(int _r, int _c){
    r = _r;
    c = _c;
    std::memset(d, 0, sizeof(d));
}

Matrix::Matrix(int _r, int _c, double _d[][mat_max]) {
    r = _r;
    c = _c;
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            d[i][j] = _d[i][j];
        }
    }
}

void Matrix::output() {
    printf("An %d x %d Matrix\n", r, c);
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            printf("%lf%c", d[i][j], j == c? '\n': '\t');
        }
    }
}

bool Matrix::operator==(const Matrix &b) const {
    if (r != b.r || c != b.c) return false;
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) if (d[i][j] != b.d[i][j]) return false;
    return true;
}

bool Matrix::operator<(const Matrix &b) const {
    assert(r == b.r && c == b.c);
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            if (d[i][j] >= b.d[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator<=(const Matrix &b) const {
    assert(r == b.r && c == b.c);
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            if (d[i][j] > b.d[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator>(const Matrix &b) const {
    assert(r == b.r && c == b.c);
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            if (d[i][j] <= b.d[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator>=(const Matrix &b) const {
    assert(r == b.r && c == b.c);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (d[i][j] < b.d[i][j]) {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::operator+(const Matrix &b) const {
    assert(r == b.r && c == b.c);
    Matrix res = *this;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            res.d[i][j] += b.d[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix &b) const {
    assert(r == b.r && c == b.c);
    Matrix res = *this;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            res.d[i][j] -= b.d[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator*(const Matrix &b) const {
    assert(c == b.r);
    Matrix res(r, b.c);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= b.c; j++) {
            for (int k = 1; k <= c; k++){
                res.d[i][j] += d[i][k] * b.d[k][j];
            }
        }
    }
    return res;
}

Matrix Matrix::operator*(const double &a) const {
    Matrix res = *this;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            res.d[i][j] *= a;
        }
    }
    return res;
}

Matrix operator * (double &a, const Matrix &m){
    Matrix res = m;
    for (int i = 1; i <= res.r; i++) {
        for (int j = 1; j <= res.c; j++) {
            res.d[i][j] *= a;
        }
    }
    return res;
}