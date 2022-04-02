#include <fstream>
#include "goldenRatio.h"

std::ofstream foutGoldenRatio;
int functionCallsNumberGoldenRatio;

double goldenRatio() {
    return (1 + sqrt(5)) / 2;
}

GoldenRatioLimits goldenRatioGetNewLimits(GoldenRatioLimits limits) {
    if (f(limits.x1) >= f(limits.x2)) {
        limits.a = limits.x1;
        limits.x1 = limits.x2;
        limits.x2 = limits.b - (limits.x1 - limits.a);
    } else {
        limits.b = limits.x2;
        limits.x2 = limits.x1;
        limits.x1 = limits.a + (limits.b - limits.x2);
    }
    ++functionCallsNumberGoldenRatio;

    return limits;
}

double goldenRatioGetMinimum(Limits limits, double eps, std::string file) {
	functionCallsNumberGoldenRatio = 0;
    foutGoldenRatio.open(file);
    foutGoldenRatio.clear();
	foutGoldenRatio << "Итерация" << "\t" << "a" << "\t" << "b" << "\t" << "Вызовов функции" << "\n";

    double x1 = limits.b - (limits.b - limits.a) / goldenRatio();
    double x2 = limits.a + (limits.b - limits.a) / goldenRatio();
    auto goldenRatioLimits = GoldenRatioLimits{limits.a, limits.b, x1, x2};
    int iteration = 0;
    while ((goldenRatioLimits.b - goldenRatioLimits.a) / 2 >= eps) {
        goldenRatioLimits = goldenRatioGetNewLimits(goldenRatioLimits);
        foutGoldenRatio << ++iteration << "\t" << goldenRatioLimits.a << "\t" << goldenRatioLimits.b << "\t"
                        << functionCallsNumberGoldenRatio << "\n";
    }

    foutGoldenRatio.close();
    return (goldenRatioLimits.a + goldenRatioLimits.b) / 2;
}