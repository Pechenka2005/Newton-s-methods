//
// Created by llSoK on 18.06.2021.
//

#ifndef SRC_POINT_H
#define SRC_POINT_H
#include <vector>
class Point {
private:
    std::vector<double> coord;
public:

    Point(std::vector<double> coord);

    Point(Point const &x);

    [[nodiscard]] const std::vector<double> &getCoord() const;

    Point scalarMul(Point x, double value);
    double getValue() const;
    Point negate();
    friend Point operator+(Point x, Point y);
    friend Point operator+=(Point x, Point y);
    friend double operator*(Point x, Point y);
    friend Point operator-(Point x, Point y);
};


#endif //SRC_POINT_H
