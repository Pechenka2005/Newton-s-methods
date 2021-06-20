//
// Created by llSoK on 18.06.2021.
//

#include "Newton.h"

Point Newton::findMin(const Point& x, Function function, double eps) {
    int countIteration = 1;
    Point y = slay(function.getHessian(x), negateVector(function.getGradient(x)));
    while (y.getValue() > eps) {
        countIteration++;
        x += y;
        y = slay(function.getHessian(x), negateVector(function.getGradient(x)));
    }
    return x;
}
