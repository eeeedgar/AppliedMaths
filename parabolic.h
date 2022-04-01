//
// Created by edgar on 3/31/2022.
//

#ifndef APPLIEDMATHS_LAB1__PARABOLIC_H_
#define APPLIEDMATHS_LAB1__PARABOLIC_H_

#include "general.h"

struct ParabolicLimits {
    double x1, x2, x3, f1, f2, f3, x_;
};

ParabolicLimits getParabolicLimitsFunctionValues(ParabolicLimits);

ParabolicLimits getNewParabolicLimits(ParabolicLimits);

double parabolicGetMinimum(Limits, double, std::string);

#endif //APPLIEDMATHS_LAB1__PARABOLIC_H_
