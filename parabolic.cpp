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

double getParabollicMin(double x1, double x2, double x3, double f1, double f2, double f3) {
    return x2 - ((x2 - x1) * (x2 - x1) * (f2 - f3) - (x2 - x3) * (x2 - x3) * (f2 - f1)) /
         ((x2 - x1) * (f2 - f3) - (x2 - x3) * (f2 - f1)) / 2;
}

ParabolicLimits getNewParabolicLimits(ParabolicLimits parabolicLimits) {
    double x1 = parabolicLimits.x1;
    double x2 = parabolicLimits.x2;
    double x3 = parabolicLimits.x3;

    double f1 = parabolicLimits.f1;
    double f2 = parabolicLimits.f2;
    double f3 = parabolicLimits.f3;

    double x_ = getParabollicMin(x1, x2, x3, f1, f2, f3);
    double f_ = f(x_);
    functionCallsNumberParabolic++;

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
    parabolicLimits.f2 = f(parabolicLimits.x2);

    return parabolicLimits;
}

bool areCloseEnough(double a, double b, double eps) {
    return std::abs(a - b) <= eps;
}

double parabolicGetMinimum(Limits limits, double eps, std::string file) {
    foutParabolic.open(file);
    foutParabolic.clear();
	foutParabolic << "Итерация" << "\t" << "a" << "\t" << "b" << "\t" << "Вызовов функции" << "\n";

    int iteration = 0;

    double x1 = limits.a;
    double x3 = limits.b;
    double x2 = (limits.a + limits.b) / 2;

    auto parabolicLimits = ParabolicLimits{x1, x2, x3};
    parabolicLimits = getParabolicLimitsFunctionValues(parabolicLimits);

	x1 = parabolicLimits.x1;
	x3 = parabolicLimits.x3;
	parabolicLimits = getNewParabolicLimits(parabolicLimits);

	foutParabolic << ++iteration << "\t" << parabolicLimits.x1 << "\t" << parabolicLimits.x3 << "\t" << functionCallsNumberParabolic
				  << "\n";

    while (!areCloseEnough(x1, x3, eps))
	{
        x1 = parabolicLimits.x1;
        x3 = parabolicLimits.x3;
        parabolicLimits = getNewParabolicLimits(parabolicLimits);

        foutParabolic << ++iteration << "\t" << parabolicLimits.x1 << "\t" << parabolicLimits.x3 << "\t" << functionCallsNumberParabolic
                      << "\n";
    }

    foutParabolic.close();
    return parabolicLimits.x2;
}
