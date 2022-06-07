#include "utils.h"
#include "First_Order_UGV.h"
#include "Point.h"

using namespace Eigen;

int main() {
    VectorXd u{3};
    u << 2, 1, 0;
    std::cout << u << std::endl;

    VectorXd x{3};
    x << 0, 0, 10;

    First_Order_UGV r(x);
    r.F << 0, 0, -1;
    r.output();
    r.time_forward(u, 0.5);
    r.output();
    r.time_forward(u, 1.0);
    r.output();

    Point p = u;
    p.output();

    std::cout << p.vec() << std::endl;


    return 0;
}
