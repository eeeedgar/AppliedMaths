#ifndef APPLIEDMATHS_LAB1__PARABOLIC_H_
#define APPLIEDMATHS_LAB1__PARABOLIC_H_

#include "general.h"

struct ParabolicLimits {
    double x1, x2, x3, f1, f2, f3, x_;
};

class parabolicMethod {
private:
    int functionCallsNumber;
    logger log;
    double (*func)(double);
    ParabolicLimits parabolicGetNewLimits(ParabolicLimits);
    double getParabolicMinimum(double x1, double x2, double x3, double f1, double f2, double f3);
    ParabolicLimits getParabolicLimitsFunctionValues(ParabolicLimits);
public:
    parabolicMethod(double (*func)(double), const logger& log);
    double findMinimum(double a, double b, double eps);
    void reset();
};

#endif //APPLIEDMATHS_LAB1__PARABOLIC_H_
