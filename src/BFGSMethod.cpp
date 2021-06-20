//
// Created by llSoK on 19.06.2021.
//

#include "BFGSMethod.h"

Point BFGSMethod::findMin(Point &x, Function function, double eps) {
    int countIteration = 0;
    Point gradient(function.getGradient(x));
    std::vector<std::vector<double>> hessian(gradient.getCoord().size());

    for (auto & item : hessian) {
        hessian.resize(gradient.getCoord().size());
    }

    for(int i = 0; i < hessian.size(); i++) {
        hessian[i][i] = 1;
    }

    while (gradient.getValue() >= eps) {
        countIteration++;
        Point y = mulMatrixPoint(hessian, gradient);
        double learningRate = getLearningRate(function, x, y);
        Point scalar = scalarMul(y, learningRate);
        Point xk = x + scalar;
        Point gradientK = Point(function.getGradient(xk));
        hessian = nextHessianForBFGS(hessian, xk - x, gradientK - gradient);
        x = xk;
        gradient = gradientK;
    }

    return x;
}
