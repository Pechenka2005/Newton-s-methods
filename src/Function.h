//
// Created by llSoK on 18.06.2021.
//

#ifndef SRC_FUNCTION_H
#define SRC_FUNCTION_H

#include <functional>
#include <vector>
#include "Point.h"

class Function {
public:
    Function();

    void setFunction(const std::function<double(Point)> &function);

    void setHessian(const std::function<std::vector<std::vector<double>>(Point)> &hessian);

    void setGradient(const std::function<std::vector<double>(Point)> &gradient);

    std::function<double(Point)> function;
    std::function<std::vector<std::vector<double>>(Point)> hessian;
    std::function<std::vector<double>(Point)> gradient;
    std::vector<std::vector<double>> getHessian(const Point& x);
    std::vector<double> getGradient(const Point& x);
    double getValue(const Point& x);
};


#endif //SRC_FUNCTION_H
