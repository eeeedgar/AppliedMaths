#ifndef APPLIEDMATHS_LAB1__BRENT_H_
#define APPLIEDMATHS_LAB1__BRENT_H_

#include "general.h"

struct BrentLimits
{
	double a, b, x, w, v, u;
	double dCur, dPrv;
};

struct Parabola
{
	double a, b, c, u, fu;
};

Parabola getParabola(double, double, double, double, double, double);

Parabola getParabolaCenter(Parabola);

double brentGetMinimum(Limits, double);

#endif //APPLIEDMATHS_LAB1__BRENT_H_
