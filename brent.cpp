#include "brent.h"
#include <cmath>

double r()
{
	return (3 - sqrt(5)) / 2;
}

double sign(double x)
{
	if (x >= 0)
		return 1;
	return -1;
}

bool isEpsEqual(double a_x, double b_x, double c_x, double microEps)
{
	return std::abs(a_x - b_x) < microEps and std::abs(b_x - c_x) < microEps;
}

double getParabolaMinX(
	double p1_x, double p1_y,
	double p2_x, double p2_y,
	double p3_x, double p3_y)
{
	double denominator = 2 * (
		(p2_x - p1_x) * (p2_y - p3_y) -
			(p2_x - p3_x) * (p2_y - p1_y));
	if (denominator == 0)
		return 0;
	return p2_x - ((p2_x - p1_x) * (p2_x - p1_x) * (p2_y - p3_y) -
		(p2_x - p3_x) * (p2_x - p3_x) * (p2_y - p1_y) / denominator);
}

int functionCallNumber;

double brentGetMinimum(Limits limits, double eps)
{
	double microEps = 1e-12;
	functionCallNumber = 0;
	double aX = limits.a;
	double aY = f(aX);
	double cX = limits.b;
	double cY = f(cX);
	double xX = aX + r() * (cX - aX);
	double xY = f(xX);

	double wX = xX;
	double wY = xY;
	double vX = xX;
	double vY = xY;
	double d = cX - aX;
	double e = d;

	int iterationNumber = 0;

	while (std::abs(cX - aX) > eps)
	{
		double g = e;
		e = d;
		double tol = eps * std::abs(xX) + eps / 10;

		if (std::abs(xX - (aX + cX) / 2) + (cX - aX) / 2 <= 2 * tol)
			break;

		bool parabolic = false;

		double u_x = 0;
		double u_y = 0;

		if (not isEpsEqual(xX, wX, vX, microEps))
		{
			double parabolaMinX = getParabolaMinX(xX, xY, wX, wY, vX, vY);
			functionCallNumber += 3;

			u_x = parabolaMinX;
			u_y = f(parabolaMinX);

			if (aX <= u_x <= cX and std::abs(u_x - xX) < g / 2)
			{
				parabolic = true;
				if (u_x - aX < 2 * tol or cX - u_x < 2 * tol)
				{
					u_x = xX - sign(xX - (aX + cX) / 2) * tol;
					u_y = f(u_x);
				}
			}
		}

		if (not parabolic)
		{
			if (xX < (aX + cX) / 2)
			{
				double goldenRatio = xX + r() * (cX - xX);
				u_x = goldenRatio;
				u_y = f(goldenRatio);
				e = cX - xX;
			}
			else
			{
				double goldenRatio = xX - r() * (xX - aX);
				u_x = goldenRatio;
				u_y = f(goldenRatio);
				e - xX - aX;
			}
		}

		if (std::abs(u_x - xX) < tol)
		{
			double minProximity = xX + sign(u_x - xX) * eps;
			u_x = minProximity;
			u_y = f(minProximity);
		}

		d = std::abs(u_x - xX);

		functionCallNumber++;
		if (parabolic) functionCallNumber++;

		if (u_y <= xY)
		{
			if (u_x >= xX)
			{
				aX = xX;
				aY = xY;
			}
			else
			{
				cX = xX;
				cY = xY;
			}
			vX = wX;
			vY = wY;
			wX = xX;
			wY = xY;
			xX = u_x;
			xY = u_y;
		}
		else
		{
			if (u_x >= xX)
			{
				cX = u_x;
				cY = u_y;
			}
			else
			{
				aX = u_x;
				aY = u_y;
			}

			if (parabolic) functionCallNumber++;

			if (u_y <= wY or std::abs(wX - xX) < microEps)
			{
				vX = wX;
				vY = wY;
			}
			else
			{
				if (parabolic) functionCallNumber++;
				if (u_y <= vY or std::abs(vX - xX) < microEps or std::abs(vX - wX) < microEps)
				{
					vX = u_x;
					vY = u_y;
				}
			}
		}
		iterationNumber++;
	}
	return xX;
}
