//
// Created by edgar on 3/31/2022.
//

#ifndef APPLIEDMATHS_LAB1__GOLDENRATIO_H_
#define APPLIEDMATHS_LAB1__GOLDENRATIO_H_

#include <cmath>
#include "general.h"

struct GoldenRatioLimits
{
  double a, b, x1, x2;
};

double goldenRatio();

GoldenRatioLimits goldenRatioGetNewLimits(GoldenRatioLimits);

double goldenRatioGetMinimum(Limits, double);


#endif //APPLIEDMATHS_LAB1__GOLDENRATIO_H_
