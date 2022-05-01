#include "goldenRatio.h"


GoldenRatioLimits goldenRatioMethod::goldenRatioGetNewLimits(GoldenRatioLimits limits) {
    if (func(limits.x1) >= func(limits.x2)) {
        limits.a = limits.x1;
        limits.x1 = limits.x2;
        limits.x2 = limits.b - (limits.x1 - limits.a);
    } else {
        limits.b = limits.x2;
        limits.x2 = limits.x1;
        limits.x1 = limits.a + (limits.b - limits.x2);
    }
    functionCallsNumber++;
    return limits;
}

goldenRatioMethod::goldenRatioMethod(double (*func)(double), const logger &log) : func(func), log(log) {
    functionCallsNumber = 0;
}

double goldenRatioMethod::findMinimum(double a, double b, double eps) {
    log.log("Итерация\ta\tb\tВызовов функции\n");

    Limits limits = {a, b};
    double x1 = limits.b - (limits.b - limits.a) / goldenRatio();
    double x2 = limits.a + (limits.b - limits.a) / goldenRatio();
    auto goldenRatioLimits = GoldenRatioLimits{limits.a, limits.b, x1, x2};
    int iteration = 0;
    functionCallsNumber++;

    while (!isEnough({goldenRatioLimits.a, goldenRatioLimits.b}, eps)) {
        goldenRatioLimits = goldenRatioGetNewLimits(goldenRatioLimits);
        log.log({goldenRatioLimits.a, goldenRatioLimits.b}, ++iteration, functionCallsNumber);
    }
    return (goldenRatioLimits.a + goldenRatioLimits.b) / 2;
}

double goldenRatioMethod::goldenRatio() {
    return (1 + sqrt(5)) / 2;
}

void goldenRatioMethod::reset() {
    functionCallsNumber = 0;
}

