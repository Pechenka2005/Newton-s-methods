//
// Created by llSoK on 19.06.2021.
//

#include "OptimisationNewton.h"

Point OptimisationNewton::findMin(const Point &x, Function function, double eps) {
    int countIteration = 1;
    Point y = x;
    Point scalar = x;

    while(scalar.getValue() >= eps) {
        countIteration++;
        y = slay(function.getHessian(x), negateVector(function.getGradient(x)));
        double learningRate = getLearningRate(function, x, y);
        scalar = scalarMul(y, learningRate);
        x += scalar;
    }

    return x;
}
