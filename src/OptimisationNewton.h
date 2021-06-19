//
// Created by llSoK on 19.06.2021.
//

#ifndef SRC_OPTIMISATIONNEWTON_H
#define SRC_OPTIMISATIONNEWTON_H

#include "AbstractMethods.h"
#include "Point.h"
#include "Function.h"
#include <vector>
class OptimisationNewton : AbstractMethods, Point {
public:
    Point findMin(const Point& x, Function function, double eps);
};


#endif //SRC_OPTIMISATIONNEWTON_H
