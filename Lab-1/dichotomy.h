#ifndef DICHOTOMYMETHOD__DICHOTOMY_H_
#define DICHOTOMYMETHOD__DICHOTOMY_H_

#include "general.h"
class dichotomyMethod {
private:
    int functionCallsNumber;
    logger log;
    double (*func)(double);
    Limits dichotomyGetNewLimits(Limits, double eps);
public:
    dichotomyMethod(double (*func)(double), const logger& log);
    double findMinimum(double a, double b, double eps);
    void reset();
};

#endif //DICHOTOMYMETHOD__DICHOTOMY_H_
