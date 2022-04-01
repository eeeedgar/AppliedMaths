#ifndef DICHOTOMYMETHOD__DICHOTOMY_H_
#define DICHOTOMYMETHOD__DICHOTOMY_H_

#include "general.h"

Limits dichotomyGetNewLimits(Limits, double);

double dichotomyGetMinimum(Limits, double, std::string);

bool isEnough(Limits);

#endif //DICHOTOMYMETHOD__DICHOTOMY_H_
