//
// Created by llSoK on 19.06.2021.
//

#include "NewtonDirectionDescent.h"

Point NewtonDirectionDescent::findMin(const Point &x, Function function, double eps) {
    int countIteration = 1;
    Point y = Point(negateVector(function.getGradient(x)));
    double learningRate = getLearningRate(function, x, y);
    Point scalarOnLR = scalarMul(y, learningRate);
    x += scalarOnLR;

    while (scalarOnLR.getValue() >= eps) {
        countIteration++;
        Point gradient = Point(function.getGradient(x));
        scalarOnLR = slay(function.getHessian(x), negateVector(gradient.getCoord()));

        if (scalarOnLR * gradient < 0) {
            y = scalarOnLR;
        } else {
            y = Point(x.getCoord()).negate();
        }

        learningRate = getLearningRate(function, x, y);
        scalarOnLR = scalarMul(y, learningRate);
        x += scalarOnLR;
    }

    return x;
}
