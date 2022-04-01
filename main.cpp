#include <iostream>
#include "general.h"
#include "dichotomy.h"
#include "fibonacci.h"
#include "goldenRatio.h"
#include "parabolic.h"

using namespace std;

void test(double a, double b, double eps, string sourcedir, int num) {
    auto limits = Limits{a, b};
    double xDichotomy = dichotomyGetMinimum(limits, eps, sourcedir + "dichotomy" + to_string(num) + ".txt");
    cout << "dichotomy:\t" << xDichotomy << "\t" << f(xDichotomy) << endl;

    double xGoldenRatio = goldenRatioGetMinimum(limits, eps, sourcedir + "golden_ratio" + to_string(num) + ".txt");
    cout << "golden ratio:\t" << xGoldenRatio << "\t" << f(xGoldenRatio) << endl;

    double xFibonacci = fibonacciGetMinimum(limits, eps, sourcedir + "fibonacci" + to_string(num) + ".txt");
    cout << "fibonacci:\t" << xFibonacci << "\t" << f(xFibonacci) << endl;

    double xParabolic = parabolicGetMinimum(limits, eps, sourcedir + "parabolic" + to_string(num) + ".txt");
    cout << "parabolic:\t" << xParabolic << "\t" << f(xParabolic) << endl;
}

int main() {
    test(-5, 1, 1e-9, "/Users/vekajp/Desktop/примат/lab1/res/", 1);
    test(-5, 10, 1e-5, "/Users/vekajp/Desktop/примат/lab1/res/", 2);
}
