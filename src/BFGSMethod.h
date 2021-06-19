//
// Created by llSoK on 19.06.2021.
//

#ifndef SRC_BFGSMETHOD_H
#define SRC_BFGSMETHOD_H

#include "AbstractMethods.h"
#include "Point.h"
#include "Function.h"
#include <vector>
class BFGSMethod : AbstractMethods, Point {
public:
    Point findMin(Point& x, Function function, double eps);
};


#endif //SRC_BFGSMETHOD_H
