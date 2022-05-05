#ifndef LAB_2_FUNCTION_H
#define LAB_2_FUNCTION_H

#include <cmath>

struct vector{
    double x, y;
};

double distance(vector a, vector b);

class quadratic_function {
private:
    double a, b, c, d, e, f;
public:
    quadratic_function(double a, double b, double c, double d, double e, double f);
    double value(vector point);
    vector derivative(vector point);
};


#endif //LAB_2_FUNCTION_H
