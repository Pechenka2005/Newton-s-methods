//
// Created by llSoK on 19.06.2021.
//

#include "BFGSMethod.h"

Point BFGSMethod::findMin(Point &x, Function function, double eps) {
    int countIteration = 0;
    Point gradient(function.getGradient(x));
    std::vector<std::vector<double>> Hessian;
    while (gradient.getValue() >= eps) {
        countIteration++;
        Point y = mulMatrixPoint(Hessian, gradient);
        double learningRate = getLearningRate(function, x, y);
        Point scalar = scalarMul(y, learningRate);
        Point xk = x + scalar;
        Point gradientK = Point(function.getGradient(xk));
        Hessian = nextHessianForBFGS(Hessian, xk - x, gradientK - gradient);
        x = xk;
        gradient = gradientK;
    }

    return x;
}
