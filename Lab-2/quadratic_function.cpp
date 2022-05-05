#include "quadratic_function.h"
quadratic_function::quadratic_function(double a, double b, double c, double d, double e, double f)
: a(a), b(b), c(c), d(d), e(e), f(f) {
}
double quadratic_function::value(vector point) {
    double x = point.x;
    double y = point.y;
    return a * x * x + b * x * y + c * y * y + d * x + e * y + f;
}
vector quadratic_function::derivative(vector point) {
    double x = point.x;
    double y = point.y;
    return {2 * a * x + b * y + d, b * x + 2 * c * y + e};
}

double distance(vector a, vector b) {
    return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}