//
// Created by llSoK on 18.06.2021.
//

#include "AbstractMethods.h"
#include <cmath>
#include <utility>

Point AbstractMethods::slay(std::vector<std::vector<double>> h, std::vector<double> f) {

    std::vector<int> help(f.size());
    for (int i = 0; i < f.size(); i++) {
        help[i] = i;
    }

    for (int k = 0; k < f.size(); k++) {
        int sel = k;
        for (int i = k + 1; i < f.size(); i++) {
            if (std::abs(h[help[i]][k]) > std::abs(h[help[sel]][k])) {
                sel = i;
            }
        }

        for (int i = k + 1; i < f.size(); ++i) {
            double c = h[help[i]][k] / h[help[k]][k];
            for (int j = k; j < f.size(); ++j) {
                h[help[i]][j] -= h[help[k]][j] * c;
            }
            f[help[i]] -= f[help[k]] * c;
        }
    }

    std::vector<double> result(f.size());
    for (int i = (int)f.size() - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = (int)f.size() - 1; j > i; j--) {
            sum += h[help[i]][j] * result[j];
        }
        result[i] = (f[help[i]] - sum) / h[help[i]][i];
    }
    return Point(result);
}

double AbstractMethods::getLearningRate(Function function, const Point& x, const Point& y) {
    double phi = 2 - (1 + std::sqrt(5)) / 2;
    double eps = 0.000001;
    double a = -1000, b = 1000, x1, x2, f1, f2;
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

std::vector<double> AbstractMethods::negateVector(std::vector<double> vector) {
    for (auto & item : vector) {
        item *= -1;
    }
    return vector;
}
