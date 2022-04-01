#include <fstream>
#include "parabolic.h"

std::ofstream foutParabolic;
int functionCallsNumberParabolic = 0;


ParabolicLimits getParabolicLimitsFunctionValues(ParabolicLimits parabolicLimits) {
    parabolicLimits.f1 = f(parabolicLimits.x1);
    functionCallsNumberParabolic++;
    parabolicLimits.f2 = f(parabolicLimits.x2);
    functionCallsNumberParabolic++;
    parabolicLimits.f3 = f(parabolicLimits.x3);
    functionCallsNumberParabolic++;

    return parabolicLimits;
}

ParabolicLimits getNewParabolicLimits(ParabolicLimits parabolicLimits) {
    double x1 = parabolicLimits.x1;
    double x2 = parabolicLimits.x2;
    double x3 = parabolicLimits.x3;

    double f1 = parabolicLimits.f1;
    double f2 = parabolicLimits.f2;
    double f3 = parabolicLimits.f3;

    double x_ = x2 - ((x2 - x1) * (x2 - x1) * (f2 - f3) - (x2 - x3) * (x2 - x3) * (f2 - f1)) /
                     ((x2 - x1) * (f2 - f3) - (x2 - x3) * (f2 - f1)) / 2;

    if (x_ < x2) {
        parabolicLimits.x1 = x_;
        parabolicLimits.f1 = f(x_);
        functionCallsNumberParabolic++;
    } else {
        parabolicLimits.x3 = x_;
        parabolicLimits.f3 = f(x_);
        functionCallsNumberParabolic++;
    }

    return parabolicLimits;
}

bool areCloseEnough(double a, double b, double eps) {
    return std::abs(a - b) <= eps;
}

double parabolicGetMinimum(Limits limits, double eps, std::string file) {
    foutParabolic.open(file);
    foutParabolic.clear();

    int iteration = 0;

    double x1 = limits.a;
    double x3 = limits.b;
    double x2 = (limits.a + limits.b) / 2;

    auto parabolicLimits = ParabolicLimits{x1, x2, x3};
    parabolicLimits = getParabolicLimitsFunctionValues(parabolicLimits);

    x1 = 1;
    x3 = -1;

    while (
            !areCloseEnough(parabolicLimits.x1, parabolicLimits.x2, eps)
            && !areCloseEnough(parabolicLimits.x2, parabolicLimits.x3, eps)
            && (!areCloseEnough(parabolicLimits.x1, x1, eps) || !areCloseEnough(parabolicLimits.x3, x3, eps))
            && (parabolicLimits.x1 >= x1)
            && (parabolicLimits.x3 <= x3)) {
        x1 = parabolicLimits.x1;
        x3 = parabolicLimits.x3;
        parabolicLimits = getNewParabolicLimits(parabolicLimits);

        foutParabolic << ++iteration << ";\t" << parabolicLimits.x1 << ";\t" << parabolicLimits.x3 << ";\t" << functionCallsNumberParabolic
                      << "\n";
    }

    foutParabolic.close();
    return parabolicLimits.x2;
}
