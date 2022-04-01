#include <iostream>
#include "general.h"
#include "dichotomy.h"
#include "fibonacci.h"
#include "goldenRatio.h"
#include "parabolic.h"
#include "brent.h"

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

	double xBrent = brentGetMinimum(limits, eps, sourcedir + "brent" + to_string(num) + ".txt");
	cout << "brent's:\t" << xBrent << "\t" << f(xBrent) << endl;
}

int main() {
    test(-5, 1, 1e-9, "D:/appliedMaths/", 1);
    test(-5, 10, 1e-5, "D:/appliedMaths/", 2);
}
