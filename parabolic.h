//
// Created by edgar on 3/31/2022.
//

#ifndef APPLIEDMATHS_LAB1__PARABOLIC_H_
#define APPLIEDMATHS_LAB1__PARABOLIC_H_

#include "general.h"

struct ParabolicLimits
{
  double x1, x2, x3, f1, f2, f3, x_;
};

struct Parabola
{
  double a0, a1, a2;
};

Parabola getParabola(ParabolicLimits);

ParabolicLimits getParabolicLimitsFunctionValues(ParabolicLimits);

ParabolicLimits getNewParabolicLimits(ParabolicLimits);

double parabolicGetMinimum(Limits, double);

#endif //APPLIEDMATHS_LAB1__PARABOLIC_H_
