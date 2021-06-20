#include <iostream>
#include <tuple>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;
#include "Function.h"

int main() {
    Function first;
    first.setFunction([](Point x){
        return x.get(0) * x.get(0) + x.get(1) * x.get(1) - 1.2 * x.get(0) * x.get(1);
    });
    first.setGradient([](Point x){
        return vector<double>{ (2 * x.get(0) - 1.2 * x.get(1)),
                               (2 * x.get(1) - 1.2 * x.get(0))};
    });

    first.setHessian([](const Point& x) {
        return vector<vector<double>> {
            vector<double> {2.0, -1.2},
            vector<double> {-1.2, 2.0}
        };
    });

    Function second;
    second.setFunction([](Point x){
        return 100 * pow(x.get(0), 4) +
               100 * pow(x.get(1), 2) - 200 * pow(x.get(0), 2) * x.get(1) +
               pow(x.get(0), 2) - 2 * x.get(0) + 1;
    });
    second.setGradient([](Point x){
        return vector<double>{
            400 * pow(x.get(0), 3) - 400 * x.get(0) * x.get(1) + 2 * x.get(0) - 2,
            200 * x.get(1) - 200 * pow(x.get(0), 2)
        };
    });

    second.setHessian([](Point x) {
        return vector<vector<double>> {
                vector<double> {1200 * pow(x.get(0), 2) - 400 * x.get(1) + 2, -400 * x.get(0)},
                vector<double> {-400 * x.get(0), 200.0}
        };
    });

    Function third;
    third.setFunction([](Point x){
        return pow(pow(x.get(0), 2) + x.get(1) - 11, 2) +
               pow(x.get(0) + pow(x.get(1), 2) - 7, 2);
    });

    third.setGradient([](Point x){
        return vector<double>{
                4 * (pow(x.get(0),3) + x.get(0) * x.get(1) - 11
                * x.get(0)) + 2 * (x.get(0) + pow(x.get(1), 2) - 7),
                2 * (pow(x.get(0), 2) + x.get(1) - 11)
                + 4 * (x.get(0) * x.get(1) + pow(x.get(1), 3) - 7 * x.get(1))
        };
    });

    third.setHessian([](Point x) {
        return vector<vector<double>> {
                vector<double> {12 * pow(x.get(0), 2) + 4 * x.get(1) - 42, 4 * (x.get(0) + x.get(1))},
                vector<double> {4 * (x.get(0) + x.get(1)), 4 * x.get(0) + 12 * pow(x.get(1), 2) - 26}
        };
    });

    Function fourth;
    fourth.setFunction([](Point x){
        return pow(x.get(0) + 10 * x.get(1), 2) + 5 * pow(x.get(2) - x.get(3), 2) +
                pow(x.get(1) - 2 * x.get(2), 4) + 10 * pow(x.get(0) - x.get(3), 4);
    });

    fourth.setGradient([](Point x){
        return vector<double>{
                2 * (20 * pow(x.get(0) - x.get(3), 3) + x.get(0) + 10 * x.get(1)),
                4 * (5 * (x.get(0) + 10 * x.get(1)) + pow(x.get(1) - 2 * x.get(2), 3)),
                10 * (x.get(2) - x.get(3)) - 8 * pow(x.get(1) - 2 * x.get(2), 3),
                10 * (-4 * pow(x.get(0) - x.get(3), 3) - x.get(2) + x.get(3))
        };
    });

    fourth.setHessian([](Point x) {
        return vector<vector<double>> {
                vector<double> {120 * pow(x.get(0) - x.get(3), 2) + 2, 20, 0, -120 * pow(x.get(0) - x.get(3), 2)},
                vector<double> {20, 200 + 12 * pow((x.get(1) - 2 * x.get(2)), 2), -24 * pow(x.get(1) - 2 * x.get(2), 2), 0},
                vector<double> {0, -24 * pow(x.get(1) - 2 * x.get(2), 2), 10 + 48 * (x.get(1) - 2 * x.get(2)), -10},
                vector<double> {-120 * pow(x.get(0) - x.get(3), 2), 0, -10, 120 * pow(x.get(0) - x.get(3), 2) + 10}

        };
    });

    Function fifth;
    fifth.setFunction([](Point x){
        return (-2.0 / (0.25 * pow(x.get(0) - 1, 2) + 1.0 /
        9 * pow(x.get(1) - 1, 2) + 1) - 1.0 / (0.25 * pow(x.get(0) - 2, 2) + 1.0 /
        9 * pow(x.get(1) - 1, 2) + 1) + 100);
    });

    fifth.setGradient([](Point x){
        return vector<double>{
                (648 * (x.get(0) - 2)) / pow(9 * pow(x.get(0), 2) - 36 * x.get(0)
                + 4 * pow(x.get(1), 2) - 8 * x.get(1) + 76, 2) + (x.get(0) - 1) /
                pow(0.25 * pow(x.get(0) - 1, 2) + 1.0 / 9 * pow(x.get(1) - 1, 2) + 1, 2),
                2.0 / 9 * (x.get(1) - 1) * (2.0 / pow(0.25 * pow(x.get(0) - 1, 2) + 1.0 /
                9 * pow(x.get(1) - 1, 2) + 1, 2) + 1.0 / pow(0.25 * pow(x.get(0) - 2, 2) +
                1.0 / 9 * pow(x.get(1) - 1, 2) + 1, 2))
        };
    });

    fifth.setHessian([](Point x) {
        return vector<vector<double>> {
                vector<double> {(-pow(-1 + x.get(0), 2) / pow(1 + 0.25 * pow(-1 + x.get(0), 2) +
                1.0 / 9 * pow(-1 + x.get(1), 2), 3) + 1.0 / pow(1 + 0.25 *
                pow(-1 + x.get(0), 2) + 1.0 / 9 * pow(-1 + x.get(1), 2), 2) -
                (23328 * pow(-2 + x.get(0), 2)) / pow(76 - 36 * x.get(0) + 9 *
                x.get(0) * x.get(0) - 8 * x.get(1) + 4 * x.get(1) *
                x.get(1), 3) + 648 / pow(76 - 36 * x.get(0) + 9 * x.get(0) * x.get(0) -
                8 * x.get(1) + 4 * x.get(1) * x.get(1), 2)),
                                4.0 / 9 * (-1 + x.get(1)) * (-(-1 + x.get(0)) /
                                pow(1 + 1.0 / 4 * pow(-1 + x.get(0), 2) + 1.0 / 9 * pow(-1 + x.get(1), 2), 3) -
                                (23328 * (-2 + x.get(0))) / pow(76 - 36 * x.get(0) + 9 * x.get(0) * x.get(0) -
                                8 * x.get(1) + 4 * x.get(1) * x.get(1), 3))},
                vector<double> {4.0 / 9 * (-1 + x.get(1)) * (-(-1 + x.get(0)) /
                pow(1 + 1.0 / 4 * pow(-1 + x.get(0), 2) + 1.0 / 9 * pow(-1 + x.get(1), 2), 3) -
                (23328 * (-2 + x.get(0))) / pow(76 - 36 * x.get(0) + 9 * x.get(0) *
                x.get(0) - 8 * x.get(1) + 4 * x.get(1) * x.get(1), 3)),
                                2.0 / 9 * (4.0 / 9 * pow(x.get(1) - 1, 2) *
                                (-2.0 / pow(1.0 / 4 * pow(x.get(0) - 1, 2) + 1.0 / 9 *
                                pow(x.get(1) - 1, 2) + 1, 3) - 1.0 / pow(1.0 / 4 *
                                pow(x.get(0) - 2, 2) + 1.0 / 9 * pow(x.get(1) - 1, 2) + 1, 3)) +
                                1.0 / pow(1.0 / 4 * pow(x.get(0) - 2, 2) + 1.0 / 9 *
                                pow(x.get(1) - 1, 2) + 1, 2) + 2.0 / pow(1.0 / 4 *
                                pow(x.get(0) - 1, 2) + 1.0 / 9 * pow(x.get(1) - 1, 2) + 1, 2))}

        };
    });

    Function sixth;
    sixth.setFunction([](Point x){
        return 3 * pow(x.get(0), 2) + x.get(0) * x.get(1) +
        2 * pow(x.get(1), 2) - x.get(0) - 4 * x.get(1);
    });

    sixth.setGradient([](Point x){
        return vector<double>{
                (6 * x.get(0) + x.get(1) - 1),
                (x.get(0) + 4 * x.get(1) - 4)
        };
    });

    sixth.setHessian([](const Point& x) {
        return vector<vector<double>> {
                vector<double> {6, 1},
                vector<double> {1, 4}
        };
    });


    return 0;
}
