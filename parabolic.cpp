//
// Created by edgar on 3/31/2022.
//

#include <iostream>
#include "parabolic.h"

//Parabola getParabola(ParabolicLimits limits)
//{
//  double x1 = limits.x1;
//  double x2 = limits.x2;
//  double x3 = limits.x3;
//
//  double f1 = limits.f1;
//  double f2 = limits.f2;
//  double f3 = limits.f3;
//
//  double a0 = f1;
//  double a1 = (f2 - f1) / (x2 - x1);
//  double a2 = (f3 - f1) * (f2 - f1) / (x3 - x1) / (x2 - x1) / (x3 - x2);
//
//  return Parabola{a0, a1, a2};
//}

ParabolicLimits getParabolicLimitsFunctionValues(ParabolicLimits parabolicLimits)
{
  parabolicLimits.f1 = f(parabolicLimits.x1);
  parabolicLimits.f2 = f(parabolicLimits.x2);
  parabolicLimits.f3 = f(parabolicLimits.x3);

  return parabolicLimits;
}

ParabolicLimits getNewParabolicLimits(ParabolicLimits parabolicLimits)
{
  double x1 = parabolicLimits.x1;
  double x2 = parabolicLimits.x2;
  double x3 = parabolicLimits.x3;

  double f1 = parabolicLimits.f1;
  double f2 = parabolicLimits.f2;
  double f3 = parabolicLimits.f3;

  double x_ = x2 - ((x2 - x1) * (x2 - x1) * (f2 - f3) - (x2 - x3) * (x2 - x3) * (f2 - f1))/((x2 - x1) * (f2 - f3) - (x2 - x3) * (f2 - f1)) / 2;

  if (x_ < x2)
  {
	parabolicLimits.x1 = x_;
	parabolicLimits.f1 = f(x_);
  }
  else
  {
	parabolicLimits.x3 = x_;
	parabolicLimits.f3 = f(x_);
  }

  return parabolicLimits;
}

bool areCloseEnough(double a, double b, double eps)
{
  return std::abs(a - b) <= eps;
}

double parabolicGetMinimum(Limits limits, double eps)
{
  double x1 = limits.a;
  double x3 = limits.b;
  double x2 = (limits.a + limits.b) / 2;

  auto parabolicLimits = ParabolicLimits{x1, x2, x3};
  parabolicLimits = getParabolicLimitsFunctionValues(parabolicLimits);

  x1 = 1;
  x3 = -1;

  while (
	  !areCloseEnough(parabolicLimits.x1, parabolicLimits.x2, eps)
	  && !areCloseEnough(parabolicLimits.x2, parabolicLimits.x3, eps)
	  && (!areCloseEnough(parabolicLimits.x1, x1, eps) || !areCloseEnough(parabolicLimits.x3, x3, eps))
	  && (parabolicLimits.x1 >= x1)
	  && (parabolicLimits.x3 <= x3))
  {
	x1 = parabolicLimits.x1;
	x3 = parabolicLimits.x3;
	parabolicLimits = getNewParabolicLimits(parabolicLimits);
	std::cout << parabolicLimits.x1 << " " << parabolicLimits.x2 << " " << parabolicLimits.x3 << std::endl;
  }

  return parabolicLimits.x2;
}
