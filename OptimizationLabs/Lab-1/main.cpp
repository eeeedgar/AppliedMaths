#include <iostream>
#include "general.h"
#include "dichotomy.h"
#include "fibonacci.h"
#include "goldenRatio.h"
#include "parabolic.h"
#include "brent.h"

using namespace std;
double f(double x) {
    return sin(x) * pow(x, 3);
}


int main() {
    logger* log = new logger(std::cout);
    auto method = new fibonacciMethod(&f, *log);
    method->findMinimum(-5, 10, 1e-3);
}
