//
// Created by llSoK on 19.06.2021.
//

#include "PowellMethod.h"

Point PowellMethod::findMin(Point &x, Function function, double eps) {
    int countIteration = 0;
    Point y = Point(function.getGradient(x)).negate();
    std::vector<std::vector<double>> hessian(y.getCoord().size());
    for (auto & item : hessian) {
        hessian.resize(y.getCoord().size());
    }
    for(int i = 0; i < hessian.size(); i++) {
        hessian[i][i] = 1;
    }
    while (y.getValue() >= eps) {
        countIteration++;
        Point point = mulMatrixPoint(hessian, y);
        double learningRate = getLearningRate(function, x, point);
        Point help = scalarMul(point, learningRate);
        Point xk = x + help;
        Point yk = Point(function.getGradient(xk)).negate();
        hessian = nextHessianForPowell(hessian, xk - x, yk - y);
        x = xk;
        y = yk;
    }
    return x;
}
