//
// Created by llSoK on 18.06.2021.
//

#include "Point.h"
#include <cmath>
#include <functional>
Point::Point(std::vector<double> coord) : coord(std::move(coord)) {
}

Point::Point(const Point &x) {
    this->coord = x.getCoord();
}

const std::vector<double> &Point::getCoord() const {
    return coord;
}

Point operator+(Point x, Point y) {
    int n = x.getCoord().size();
    std::vector<double> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = x.coord[i] + y.coord[i];
    }

    return Point(ans);
}

Point operator+=(Point x, Point y) {
    int n = x.getCoord().size();
    std::vector<double> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = x.coord[i] + y.coord[i];
    }

    return Point(ans);
}

double Point::getValue() const {
    double ans = 0.0;
    for (auto item : this->getCoord()) {
        ans += item * item;
    }

    return std::sqrt(ans);
}

Point Point::scalarMul(Point x, double value) {
    for (auto & item : x.coord) {
        item *= value;
    }
    return x;
}

double operator*(Point x, Point y) {
    double result = 0.0;

    for (int i = 0; i < x.coord.size(); i++) {
        result += x.coord[i] * y.coord[i];
    }

    return result;
}

Point Point::negate() {
    for(auto & item : this->coord) {
        item *= -1;
    }
    return *this;
}

Point operator-(Point x, Point y) {
    std::vector<double> result(x.coord.size());

    for (int i = 0; i < x.coord.size(); i++) {
        result[i] = x.coord[i] - y.coord[i];
    }

    return Point(result);
}

double Point::get(int index) {
    return coord[index];
}
