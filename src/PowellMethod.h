//
// Created by llSoK on 19.06.2021.
//

#ifndef SRC_POWELLMETHOD_H
#define SRC_POWELLMETHOD_H

#include "AbstractMethods.h"
#include "Point.h"
#include "Function.h"
#include <vector>
class PowellMethod : AbstractMethods, Point {
public:
    Point findMin(Point& x, Function function, double eps);
};


#endif //SRC_POWELLMETHOD_H
