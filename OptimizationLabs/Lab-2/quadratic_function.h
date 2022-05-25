#ifndef LAB_2_FUNCTION_H
#define LAB_2_FUNCTION_H

#include <cmath>
#include <string>

struct vector {
    double x, y;
    double len();
};

double distance(vector a, vector b);

class quadratic_function {
private:
    double a, b, c, d, e, f;
public:
    quadratic_function(double a, double b, double c, double d, double e, double f);
    double value(vector point);
    vector derivative(vector point);
    std::string to_string();
};


#endif //LAB_2_FUNCTION_H
