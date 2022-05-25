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

std::string quadratic_function::to_string() {
    std::string ans = "";
    if (a != 0) {
        ans += std::to_string(a) + "x ^ 2 ";
    }
    if (b != 0) {
        if (b > 0) {
            ans += "+ ";
        }
        ans += std::to_string(b) + "xy ";
    }

    if (c != 0) {
        if (c > 0) {
            ans += "+ ";
        }
        ans += std::to_string(c) + "y ^ 2 ";
    }

    if (d != 0) {
        if (d > 0) {
            ans += "+ ";
        }
        ans += std::to_string(d) + "x ";
    }

    if (e != 0) {
        if (e > 0) {
            ans += "+ ";
        }
        ans += std::to_string(e) + "y ";
    }

    if (f != 0) {
        if (f > 0) {
            ans += "+ ";
        }
        ans += std::to_string(f);
    }
    return ans;
}

double distance(vector a, vector b) {
    return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}

double vector::len() {
    return std::sqrt(x * x + y * y);
}
