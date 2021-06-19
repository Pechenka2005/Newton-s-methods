//
// Created by llSoK on 18.06.2021.
//

#include "AbstractMethods.h"
#include <cmath>
#include <utility>

Point AbstractMethods::slay(std::vector<std::vector<double>> h, std::vector<double> f) {
    int n = f.size();

    std::vector<int> realRows(n);
    for (int i = 0; i < n; i++) {
        realRows[i] = i;
    }

    for (int row = 0; row < n; row++) {
        int sel = row;
        for (int i = row + 1; i < n; i++) {
            if (std::abs(h[realRows[i]][row]) > std::abs(h[realRows[sel]][row])) {
                sel = i;
            }
        }
        int tmp = realRows[sel];
        realRows[sel] = realRows[row];
        realRows[row] = tmp;

        tmp = realRows[sel];
        realRows[sel] = realRows[row];
        realRows[row] = tmp;

        for (int i = row + 1; i < n; ++i) {
            double c = h[realRows[i]][row] / h[realRows[row]][row];
            for (int j = row; j < n; ++j) {
                h[realRows[i]][j] -= h[realRows[row]][j] * c;
            }
            f[realRows[i]] -= f[realRows[row]] * c;
        }
    }

    std::vector<double> result(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = n - 1; j > i; j--) {
            sum += h[realRows[i]][j] * result[j];
        }
        result[i] = (f[realRows[i]] - sum) / h[realRows[i]][i];
    }
    return Point(result);
}

double AbstractMethods::getLearningRate(Function function, Point x, Point y) {
    double phi = 2 - (1 + std::sqrt(5)) / 2;
    double eps = 0.000001;
    double a = -1000, b = 1000, x1, x2, f1, f2; //todo как выбирать a и b?
    x1 = a + phi * (b - a);
    x2 = b - phi * (b - a);
    f1 = function.getValue(evaluateValueForLR(x, y, x1));
    f2 = function.getValue(evaluateValueForLR(x, y, x2));
    while (std::abs(b - a) > eps) {
        if (f1 < f2) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = a + phi * (b - a);
            f1 = function.getValue(evaluateValueForLR(x, y, x1));
        } else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = b - phi * (b - a);
            f2 = function.getValue(evaluateValueForLR(x, y, x2));
        }
    }
    return (x1 + x2) / 2;
}

Point AbstractMethods::evaluateValueForLR(const Point& x, const Point& y, double value) {
    std::vector<double> coordY = y.getCoord();
    for (double & i : coordY) {
        i *= value;
    }

    return Point(coordY) + x;
}

Point AbstractMethods::mulMatrixPoint(std::vector<std::vector<double>> vector, Point x) {
    std::vector<double> result(x.getCoord().size());
    for (int i = 0; i < vector.size(); i++) {
        for (int j = 0; j < vector[i].size(); j++) {
            result[i] += vector[i][j] * x.getCoord()[j];
        }
    }

    return Point(result);
}

std::vector<std::vector<double>> AbstractMethods::nextHessianForPowell(std::vector<std::vector<double>> nowH,
                                                                       const Point& x, const Point& y) {
    double znam = 0.0;
    for (int i = 0; i < x.getCoord().size(); i++) {
        znam += x.getCoord()[i] * y.getCoord()[i];
    }


    for (int i = 0; i < x.getCoord().size(); i++) {
        for (int j = 0; j < x.getCoord().size(); i++) {
            nowH[i][j] -= x.getCoord()[i] * y.getCoord()[j] * 1 / znam;
        }
    }

    return nowH;
}

std::vector<std::vector<double>>
AbstractMethods::nextHessianForBFGS(std::vector<std::vector<double>> nowH, const Point &x, const Point &y) {
    double znam = 0.0;
    std::vector<std::vector<double>> newHessian(x.getCoord().size());
    std::vector<std::vector<double>> helpForHessian(x.getCoord().size());
    std::vector<std::vector<double>> squareX(x.getCoord().size());
    for (int i = 0; i < x.getCoord().size(); i++) {
        newHessian[i].resize(x.getCoord().size());
        helpForHessian[i].resize(x.getCoord().size());
        squareX[i].resize(x.getCoord().size());
        znam += x.getCoord()[i] * y.getCoord()[i];
    }
    for (int i = 0; i < newHessian.size(); i++) {
        for (int j = 0; j < newHessian[i].size(); j++) {
            newHessian[i][j] = (i == j) ? 1 : 0 - y.getCoord()[i] * x.getCoord()[j] * 1 / znam;
            helpForHessian[i][j] = (i == j) ? 1 : 0 - x.getCoord()[i] * y.getCoord()[j] * 1 / znam;
            squareX[i][j] = x.getCoord()[i] * x.getCoord()[j] * 1 / znam;
        }
    }

    newHessian = matrixMulMatrix(newHessian, std::move(nowH));
    newHessian = matrixMulMatrix(newHessian, helpForHessian);
    for (int i = 0; i < newHessian.size(); i++) {
        for (int j = 0; j < newHessian[i].size(); j++) {
            newHessian[i][j] += squareX[i][j];
        }
    }

    return newHessian;
}

std::vector<std::vector<double>>
AbstractMethods::matrixMulMatrix(std::vector<std::vector<double>> x, std::vector<std::vector<double>> y) {
    std::vector<std::vector<double>> ans(x.size());
    for (int i = 0; i < ans.size(); i++) {
        ans[i].resize(ans.size());
    }
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans.size(); j++) {
            for (int k = 0; k < ans.size(); k++) {
                ans[i][j] += x[i][k] * y[k][j];
            }
        }
    }

    return ans;
}
