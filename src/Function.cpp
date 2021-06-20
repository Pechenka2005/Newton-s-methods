//
// Created by llSoK on 18.06.2021.
//

#include "Function.h"


std::vector<std::vector<double>> Function::getHessian(const Point& x) {
    return hessian.operator()(x);
}

std::vector<double> Function::getGradient(const Point& x) {
    return gradient.operator()(x);
}

double Function::getValue(const Point& x) {
    return function.operator()(x);
}

void Function::setFunction(const std::function<double(Point)> &function) {
    Function::function = function;
}

void Function::setHessian(const std::function<std::vector<std::vector<double>>(Point)> &hessian) {
    Function::hessian = hessian;
}

void Function::setGradient(const std::function<std::vector<double>(Point)> &gradient) {
    Function::gradient = gradient;
}

Function::Function() = default;
