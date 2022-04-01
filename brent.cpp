#include "brent.h"
#include <cmath>
#include <fstream>

std::ofstream foutBrent;
int functionCallNumberBrent = 0;

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

double brentGetMinimum(Limits limits, double eps, std::string file)
{
	foutBrent.open(file);
	foutBrent.clear();

	double microEps = 1e-12;
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

		double uX = 0;
		double uY = 0;

		if (not isEpsEqual(xX, wX, vX, microEps))
		{
			double parabolaMinX = getParabolaMinX(xX, xY, wX, wY, vX, vY);
			functionCallNumberBrent += 3;

			uX = parabolaMinX;
			uY = f(parabolaMinX);

			if (aX <= uX <= cX and std::abs(uX - xX) < g / 2)
			{
				parabolic = true;
				if (uX - aX < 2 * tol or cX - uX < 2 * tol)
				{
					uX = xX - sign(xX - (aX + cX) / 2) * tol;
					uY = f(uX);
				}
			}
		}

		if (not parabolic)
		{
			if (xX < (aX + cX) / 2)
			{
				double goldenRatio = xX + r() * (cX - xX);
				uX = goldenRatio;
				uY = f(goldenRatio);
				e = cX - xX;
			}
			else
			{
				double goldenRatio = xX - r() * (xX - aX);
				uX = goldenRatio;
				uY = f(goldenRatio);
				e - xX - aX;
			}
		}

		if (std::abs(uX - xX) < tol)
		{
			double minProximity = xX + sign(uX - xX) * eps;
			uX = minProximity;
			uY = f(minProximity);
		}

		d = std::abs(uX - xX);

		functionCallNumberBrent++;
		if (parabolic) functionCallNumberBrent++;

		if (uY <= xY)
		{
			if (uX >= xX)
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
			xX = uX;
			xY = uY;
		}
		else
		{
			if (uX >= xX)
			{
				cX = uX;
				cY = uY;
			}
			else
			{
				aX = uX;
				aY = uY;
			}

			if (parabolic) functionCallNumberBrent++;

			if (uY <= wY or std::abs(wX - xX) < microEps)
			{
				vX = wX;
				vY = wY;
			}
			else
			{
				if (parabolic) functionCallNumberBrent++;
				if (uY <= vY or std::abs(vX - xX) < microEps or std::abs(vX - wX) < microEps)
				{
					vX = uX;
					vY = uY;
				}
			}
		}

		foutBrent << ++iterationNumber << "\t" << aX << "\t" << cX << "\t" << functionCallNumberBrent << "\n";
	}

	foutBrent.close();
	return xX;
}
