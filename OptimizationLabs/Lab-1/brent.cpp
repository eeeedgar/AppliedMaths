#include "brent.h"

double brentMethod::findMinimum(double a, double b, double eps) {
    log.log("Итерация\ta\tb\tВызовов функции\n");

	double microEps = 1e-12;
	Limits limits = {a, b};
	double aX = limits.a;
	double aY = func(aX);
	double cX = limits.b;
	double cY = func(cX);
	double xX = aX + goldenRatio() * (cX - aX);
	double xY = func(xX);

	double wX = xX;
	double wY = xY;
	double vX = xX;
	double vY = xY;
	double d = cX - aX;
	double e = d;

	int iteration = 0;

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

		if (!isEnough(xX, wX, vX, microEps))
		{
			double parabolaMinX = getParabolaMinX(xX, xY, wX, wY, vX, vY);
			functionCallsNumber += 3;

			uX = parabolaMinX;
			uY = func(parabolaMinX);

			if (aX <= uX <= cX and std::abs(uX - xX) < g / 2)
			{
				parabolic = true;
				if (uX - aX < 2 * tol or cX - uX < 2 * tol)
				{
					uX = xX - sign(xX - (aX + cX) / 2) * tol;
					uY = func(uX);
				}
			}
		}

		if (not parabolic)
		{
			if (xX < (aX + cX) / 2)
			{
				double g = xX + goldenRatio() * (cX - xX);
				uX = g;
				uY = func(g);
				e = cX - xX;
			}
			else
			{
				double g = xX - goldenRatio() * (xX - aX);
				uX = g;
				uY = func(g);
				e = xX - aX;
			}
		}

		if (std::abs(uX - xX) < tol)
		{
			double minProximity = xX + sign(uX - xX) * eps;
			uX = minProximity;
			uY = func(minProximity);
		}

		d = std::abs(uX - xX);

		functionCallsNumber++;
		if (parabolic) functionCallsNumber++;

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

			if (parabolic) functionCallsNumber++;

			if (uY <= wY or std::abs(wX - xX) < microEps)
			{
				vX = wX;
				vY = wY;
			}
			else
			{
				if (parabolic) functionCallsNumber++;
				if (uY <= vY or std::abs(vX - xX) < microEps or std::abs(vX - wX) < microEps)
				{
					vX = uX;
					vY = uY;
				}
			}
		}
        log.log({aX, cX}, ++iteration, functionCallsNumber);
	}

	return xX;
}

double brentMethod::goldenRatio() {
    return (3 - sqrt(5)) / 2;
}

bool brentMethod::isEnough(double a_x, double b_x, double c_x, double microEps) {
    return std::abs(a_x - b_x) < microEps and std::abs(b_x - c_x) < microEps;
}

double brentMethod::sign(double x) {
    if (x >= 0)
        return 1;
	return -1;
}

double brentMethod::getParabolaMinX(double p1_x, double p1_y, double p2_x, double p2_y, double p3_x, double p3_y) {
    double denominator = 2 * (
            (p2_x - p1_x) * (p2_y - p3_y) -
            (p2_x - p3_x) * (p2_y - p1_y));
    if (denominator == 0)
        return 0;
    return p2_x - ((p2_x - p1_x) * (p2_x - p1_x) * (p2_y - p3_y) -
                   (p2_x - p3_x) * (p2_x - p3_x) * (p2_y - p1_y) / denominator);
}

brentMethod::brentMethod(double (*func)(double), const logger &log) : func(func), log(log) {
    functionCallsNumber = 0;
}

void brentMethod::reset() {
    functionCallsNumber = 0;
}

