#include <iostream>
#include "dichotomy.h"
#include "general.h"

Limits dichotomyMethod::dichotomyGetNewLimits(Limits limits, double eps) {
    double c = (limits.a + limits.b) / 2;
    double x1 = c - eps / 3;
    double x2 = c + eps / 3;
    double f1 = func(x1);
    functionCallsNumber++;
    double f2 = func(x2);
    functionCallsNumber++;

    if (f1 > f2)
        return Limits{x1, limits.b};
    else if (f1 < f2)
        return Limits{limits.a, x2};
    return Limits{x1, x2};
}

dichotomyMethod::dichotomyMethod(double (*func)(double), const logger& log)
: func(func), log(log) {
    functionCallsNumber = 0;
}

double dichotomyMethod::findMinimum(double a, double b, double eps) {
    log.log("Итерация\ta\tb\tВызовов функции\n");

    int iteration = 0;
    Limits limits = {a, b};

    while (!isEnough(limits, eps)) {
        limits = dichotomyGetNewLimits(limits, eps);
        log.log(limits, ++iteration, functionCallsNumber);
    }

    return limits.a;
}

void dichotomyMethod::reset() {
    functionCallsNumber = 0;
}

