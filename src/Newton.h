//
// Created by llSoK on 18.06.2021.
//

#ifndef SRC_NEWTON_H
#define SRC_NEWTON_H

#include "Point.h"
#include "Function.h"
#include "AbstractMethods.h"
class Newton : AbstractMethods {

public:
    Point findMin(const Point& x, Function function, double eps);
};


#endif //SRC_NEWTON_H
