//
// Created by edgar on 3/31/2022.
//

#include "dichotomy.h"

Limits dichotomyGetNewLimits(Limits limits, double eps)
{
  double c = (limits.a + limits.b) / 2;
  double x1 = c - eps / 3;
  double x2 = c + eps / 3;
  if (f(x1) > f(x2))
	return Limits{x1, limits.b};
  else if (f(x1) < f(x2))
	return Limits{limits.a, x2};
  return Limits{x1, x2};
}

bool isEnough(Limits limits)
{
  return std::abs(limits.a - limits.b) < epsilon;
}


double dichotomyGetMinimum(Limits limits, double eps)
{
  while (!isEnough(limits))
  {
	limits = dichotomyGetNewLimits(limits, eps);
  }
  return limits.a;
}