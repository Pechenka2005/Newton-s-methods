//
// Created by llSoK on 18.06.2021.
//

#ifndef SRC_ABSTRACTMETHODS_H
#define SRC_ABSTRACTMETHODS_H

#include "Point.h"
#include "Function.h"
#include <vector>
class AbstractMethods {
protected:
    Point slay(std::vector<std::vector<double>> h, std::vector<double> f);
    double getLearningRate(Function function, Point x, Point y);
    Point mulMatrixPoint(std::vector<std::vector<double>> vector, Point x);
    std::vector<std::vector<double>> nextHessianForPowell(std::vector<std::vector<double>> nowH, const Point& x, const Point& y);
    std::vector<std::vector<double>> nextHessianForBFGS(std::vector<std::vector<double>> nowH, const Point& x, const Point& y);
private:
    Point evaluateValueForLR(const Point& x, const Point& y, double value);
    std::vector<std::vector<double>> matrixMulMatrix(std::vector<std::vector<double>> x, std::vector<std::vector<double>> y);
};


#endif //SRC_ABSTRACTMETHODS_H
