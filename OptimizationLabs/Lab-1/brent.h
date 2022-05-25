#ifndef APPLIEDMATHS_LAB1__BRENT_H_
#define APPLIEDMATHS_LAB1__BRENT_H_

#include <string>
#include "general.h"

class brentMethod {
private:
    int functionCallsNumber;
    logger log;
    double (*func)(double);
    double goldenRatio();
    bool isEnough(double a_x, double b_x, double c_x, double microEps);
    double getParabolaMinX(double p1_x, double p1_y, double p2_x, double p2_y, double p3_x, double p3_y);
    double sign(double x);
public:
    brentMethod(double (*func)(double), const logger& log);
    double findMinimum(double a, double b, double eps);
    void reset();
};

#endif //APPLIEDMATHS_LAB1__BRENT_H_
