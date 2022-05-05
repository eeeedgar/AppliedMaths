#ifndef APPLIEDMATHS_LAB1__GOLDENRATIO_H_
#define APPLIEDMATHS_LAB1__GOLDENRATIO_H_

#include <cmath>
#include "general.h"

struct GoldenRatioLimits {
    double a, b, x1, x2;
};

class goldenRatioMethod {
private:
    int functionCallsNumber;
    logger log;
    double (*func)(double);
    GoldenRatioLimits goldenRatioGetNewLimits(GoldenRatioLimits limits);
public:
    goldenRatioMethod(double (*func)(double), const logger& log);
    double findMinimum(double a, double b, double eps);
    void reset();
    static double goldenRatio();
};

#endif //APPLIEDMATHS_LAB1__GOLDENRATIO_H_
