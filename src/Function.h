//
// Created by llSoK on 18.06.2021.
//

#ifndef SRC_FUNCTION_H
#define SRC_FUNCTION_H

#include <vector>
#include "Point.h"
class Function {
private:

public:
    std::vector<std::vector<double>> getHessian(Point x);
    std::vector<double> getGradient(Point x);
    double getValue(Point x);
};


#endif //SRC_FUNCTION_H
