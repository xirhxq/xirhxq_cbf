//
// Created by xirhxq on 2022/3/1.
//

#include "utils.h"
#include "Point.h"

int main(){
    Point p(2, 1);
    p.output();

    Point q = p;
    q.output();
    q.x = 4;
    q.output();

    q = p;
    p.output();
    q.output();
    return 0;
}