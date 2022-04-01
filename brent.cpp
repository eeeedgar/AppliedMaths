#include "brent.h"
#include <cmath>
#include <exception>

double r()
{
	return (3 - sqrt(5)) / 2;
}

//Parabola getParabola(double x1, double y1, double x2, double y2, double x3, double y3)
//{
//  try
//  {
//	double a = (y3 - (x3 * (y2 - y1) + x2 * y1 - x1 * y2)/(x2 - x1)) / (x3 * (x3 - x1 - x2) + x1 * x2);
//	double b = (y2 - y1) / (x2 - x1) - a * (x1 + x2);
//	double c = (x2 * y1 - x1 * y2) / (x2 - x1) + a * x1 * x2;
//	double u = - b / (2 * a);
//	return Parabola{a, b, c, u};
//  }
//  catch (const std::exception& e)
//  {
//	return null;
//  }
//}
//
//Parabola getParabolaCenter(Parabola parabola)
//{
//  parabola.u = - parabola.b / (2 * parabola.a);
//
//  return parabola;
//}

//double brentGetMinimum(Limits limits, double eps)
//{
//  double a = limits.a;
//  double b = limits.b;
//  double x = a + r() * (b - a);
//  double w = x;
//  double v = x;
//
//  double fx = f(x);
//  double fw = fx;
//  double fv = fx;
//
//  double u;
//
//  double dCur = b - a;
//  double dPrv = dCur;
//
//  // iteration limit
//  while (true)
//  {
//	double m = (x - a > b - x) ? x - a : b - x;
//	if (m < eps)
//	{
//	  return x;
//	}
//
//	double g = dPrv / 2;
//	dPrv = dCur;
//
//
//  }
//}
//

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

double getParabolMinX(
	double p1_x, double p1_y,
	double p2_x, double p2_y,
	double p3_x, double p3_y)
{
	double denumerator = 2 * (
		(p2_x - p1_x) * (p2_y - p3_y) -
			(p2_x - p3_x) * (p2_y - p1_y));
	if (denumerator == 0)
		return 0;
	return p2_x - ((p2_x - p1_x) * (p2_x - p1_x) * (p2_y - p3_y) -
		(p2_x - p3_x) * (p2_x - p3_x) * (p2_y - p1_y) / denumerator);
}

int functionCallNumber;

double brentGetMinimum(Limits limits, double eps)
{
	double microEps = 1e-12;
	functionCallNumber = 0;
	double a_x = limits.a;
	double a_y = f(a_x);
	double c_x = limits.b;
	double c_y = f(c_x);
	double x_x = a_x + r() * (c_x - a_x);
	double x_y = f(x_x);

	double w_x = x_x;
	double w_y = x_y;
	double v_x = x_x;
	double v_y = x_y;
	double d = c_x - a_x;
	double e = d;

	int iterationNumber = 0;

	while (std::abs(c_x - a_x) > eps)
	{
		double g = e;
		e = d;
		double tol = eps * std::abs(x_x) + eps / 10;

		if (std::abs(x_x - (a_x + c_x) / 2) + (c_x - a_x) / 2 <= 2 * tol)
			break;

		bool parabolic = false;

		double u_x = 0;
		double u_y = 0;

		if (not isEpsEqual(x_x, w_x, v_x, microEps))
		{
			double parabolaMinX = getParabolMinX(x_x, x_y, w_x, w_y, v_x, v_y);
			functionCallNumber += 3;

			u_x = parabolaMinX;
			u_y = f(parabolaMinX);

			if (a_x <= u_x <= c_x and std::abs(u_x - x_x) < g / 2)
			{
				parabolic = true;
				if (u_x - a_x < 2 * tol or c_x - u_x < 2 * tol)
				{
					u_x = x_x - sign(x_x - (a_x + c_x) / 2) * tol;
					u_y = f(u_x);
				}
			}
		}

		if (not parabolic)
		{
			if (x_x < (a_x + c_x) / 2)
			{
				double goldenRatio = x_x + r() * (c_x - x_x);
				u_x = goldenRatio;
				u_y = f(goldenRatio);
				e = c_x - x_x;
			}
			else
			{
				double goldenRatio = x_x - r() * (x_x - a_x);
				u_x = goldenRatio;
				u_y = f(goldenRatio);
				e - x_x - a_x;
			}
		}

		if (std::abs(u_x - x_x) < tol)
		{
			double minProximity = x_x + sign(u_x - x_x) * eps;
			u_x = minProximity;
			u_y = f(minProximity);
		}

		d = std::abs(u_x - x_x);

		functionCallNumber++;
		if (parabolic) functionCallNumber++;

		if (u_y <= x_y)
		{
			if (u_x >= x_x)
			{
				a_x = x_x;
				a_y = x_y;
			}
			else
			{
				c_x = x_x;
				c_y = x_y;
			}
			v_x = w_x;
			v_y = w_y;
			w_x = x_x;
			w_y = x_y;
			x_x = u_x;
			x_y = u_y;
		}
		else
		{
			if (u_x >= x_x)
			{
				c_x = u_x;
				c_y = u_y;
			}
			else
			{
				a_x = u_x;
				a_y = u_y;
			}

			if (parabolic) functionCallNumber++;

			if (u_y <= w_y or std::abs(w_x - x_x) < microEps)
			{
				v_x = w_x;
				v_y = w_y;
			}
			else
			{
				if (parabolic) functionCallNumber++;
				if (u_y <= v_y or std::abs(v_x - x_x) < microEps or std::abs(v_x - w_x) < microEps)
				{
					v_x = u_x;
					v_y = u_y;
				}
			}
		}
		iterationNumber++;
	}
	return x_x;
}