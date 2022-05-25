#include "parabolic.h"
ParabolicLimits parabolicMethod::parabolicGetNewLimits(ParabolicLimits parabolicLimits) {
    double x1 = parabolicLimits.x1;
    double x2 = parabolicLimits.x2;
    double x3 = parabolicLimits.x3;

    double f1 = parabolicLimits.f1;
    double f2 = parabolicLimits.f2;
    double f3 = parabolicLimits.f3;

    double x_ = getParabolicMinimum(x1, x2, x3, f1, f2, f3);
    double f_ = func(x_);
    functionCallsNumber++;

    if (x_ < x2) {
        if (f_ < f2) {
            parabolicLimits.x3 = x2;
            parabolicLimits.f3 = f3;
        } else {
            parabolicLimits.x1 = x_;
            parabolicLimits.f1 = f_;
        }

    } else {
        if (f_ < f2) {
            parabolicLimits.x1 = x2;
            parabolicLimits.f1 = f2;
        } else {
            parabolicLimits.x3 = x_;
            parabolicLimits.f3 = f_;
        }
    }
    parabolicLimits.x2 = (parabolicLimits.x1 + parabolicLimits.x3) / 2;
    parabolicLimits.f2 = func(parabolicLimits.x2);
    functionCallsNumber++;

    return parabolicLimits;
}

parabolicMethod::parabolicMethod(double (*func)(double), const logger &log) : func(func), log(log) {
    functionCallsNumber = 0;
}

double parabolicMethod::findMinimum(double a, double b, double eps) {
    log.log("Итерация\ta\tb\tВызовов функции\n");

    int iteration = 0;

    Limits limits = {a, b};

    double x1 = limits.a;
    double x3 = limits.b;
    double x2 = (limits.a + limits.b) / 2;

    auto parabolicLimits = ParabolicLimits{x1, x2, x3};
    parabolicLimits = getParabolicLimitsFunctionValues(parabolicLimits);

	x1 = parabolicLimits.x1;
	x3 = parabolicLimits.x3;
	parabolicLimits = parabolicGetNewLimits(parabolicLimits);
    log.log(limits, ++iteration, functionCallsNumber);

    while (!isEnough({x1, x3}, eps))
	{
        x1 = parabolicLimits.x1;
        x3 = parabolicLimits.x3;
        parabolicLimits = parabolicGetNewLimits(parabolicLimits);

        log.log({parabolicLimits.x1, parabolicLimits.x3}, ++iteration, functionCallsNumber);
    }
    return parabolicLimits.x2;
}

void parabolicMethod::reset() {
    functionCallsNumber = 0;
}

double parabolicMethod::getParabolicMinimum(double x1, double x2, double x3, double f1, double f2, double f3) {
        return x2 - ((x2 - x1) * (x2 - x1) * (f2 - f3) - (x2 - x3) * (x2 - x3) * (f2 - f1)) /
         ((x2 - x1) * (f2 - f3) - (x2 - x3) * (f2 - f1)) / 2;
}

ParabolicLimits parabolicMethod::getParabolicLimitsFunctionValues(ParabolicLimits parabolicLimits) {
    parabolicLimits.f1 = func(parabolicLimits.x1);
    functionCallsNumber++;
    parabolicLimits.f2 = func(parabolicLimits.x2);
    functionCallsNumber++;
    parabolicLimits.f3 = func(parabolicLimits.x3);
    functionCallsNumber++;
    return parabolicLimits;
}
