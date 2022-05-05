//
// Created by Veka Belaia on 02.05.2022.
//

#include <cmath>
#include "fibonacci.h"
#include "gradient_descend_step.h"
#include "goldenRatio.h"

gradient_descend_step::gradient_descend_step(double value, double eps, quadratic_function& func) : value(value), function(func), eps(eps) {
}

double gradient_descend_step::get_value_and_update(vector x0) {
    return value;
}

std::string gradient_descend_step::name() {
    return "Gradient descend abstract step";
}

constant_step::constant_step(double value, quadratic_function& func)
: gradient_descend_step(value, 0, func) {
}

double constant_step::get_value_and_update(vector x0) {
    return value;
}

std::string constant_step::name() {
    return "Constant step";
}

fractional_step::fractional_step(double value, double delta, double eps, quadratic_function& func) : gradient_descend_step(value, eps, func), delta(delta) {
}

double fractional_step::get_value_and_update(vector x0) {
    double val = value;
    while (!predicate(x0, val, eps)) {
        val *= delta;
    }
    return val;
}

bool fractional_step::predicate(vector x0, double val, double eps) {
    vector grad = function.derivative(x0);
    vector point = {x0.x - val * grad.x, x0.y - val * grad.y};
    double left = function.value(point);
    double len = std::pow(grad.x, 2) + std::pow(grad.y, 2);
    return left <= function.value(x0) - eps * val * len;
}

std::string fractional_step::name() {
    return "Fractional step";
}

double golden_ratio_step::get_value_and_update(vector x0) {
    return value;
}

golden_ratio_step::golden_ratio_step(double left_bound, double right_bound, double eps, vector x0, quadratic_function &func)
        : gradient_descend_step(0, eps, func), left_bound(left_bound), right_bound(right_bound) {
    Limits limits = {left_bound, right_bound};
    double ceps = 0.0001;
    double x1 = limits.b - (limits.b - limits.a) / goldenRatioMethod::goldenRatio();
    double x2 = limits.a + (limits.b - limits.a) / goldenRatioMethod::goldenRatio();
    auto goldenRatioLimits = GoldenRatioLimits{limits.a, limits.b, x1, x2};

    gradient_descend_iterations_counter counter = gradient_descend_iterations_counter(func, eps, x0);
    while (!isEnough({goldenRatioLimits.a, goldenRatioLimits.b}, ceps)) {
        if (counter.execute(goldenRatioLimits.x1) >= counter.execute(goldenRatioLimits.x2)) {
            goldenRatioLimits.a = goldenRatioLimits.x1;
            goldenRatioLimits.x1 = goldenRatioLimits.x2;
            goldenRatioLimits.x2 = goldenRatioLimits.b - (goldenRatioLimits.x1 - goldenRatioLimits.a);
        } else {
            goldenRatioLimits.b = goldenRatioLimits.x2;
            goldenRatioLimits.x2 = goldenRatioLimits.x1;
            goldenRatioLimits.x1 = goldenRatioLimits.a + (goldenRatioLimits.b - goldenRatioLimits.x2);
        }
    }
    value = (goldenRatioLimits.a + goldenRatioLimits.b) / 2;
}

std::string golden_ratio_step::name() {
    return "Golden ratio step";
}


fibonacci_step::fibonacci_step(double left_bound, double right_bound, double eps, vector x0, quadratic_function &func)
: gradient_descend_step(0, eps, func), left_bound(left_bound), right_bound(right_bound) {
    gradient_descend_iterations_counter counter = gradient_descend_iterations_counter(func, eps, x0);

    double ceps = 0.0001;
    std::vector<int> fibonacciSequence = std::vector<int>();
    Limits limits = {left_bound, right_bound};
    int n = fibonacciMethod::fibonacciGetIterationNumberAndFillFibonacciSequence(limits, ceps, fibonacciSequence);

    double x1 = limits.a + (limits.b - limits.a) * fibonacciSequence[n - 2] / fibonacciSequence[n];
    double x2 = limits.b - (limits.b - limits.a) * fibonacciSequence[n - 2] / fibonacciSequence[n];

    double y1 = counter.execute(x1);
    double y2 = counter.execute(x2);

    auto fibonacciLimits = FibonacciLimits{limits.a, limits.b, x1, x2, y1, y2};

    for (int i = n; i > 1; i--) {
        if (fibonacciLimits.y1 > fibonacciLimits.y2) {
            fibonacciLimits.a = fibonacciLimits.x1;
            fibonacciLimits.x1 = fibonacciLimits.x2;
            fibonacciLimits.x2 = fibonacciLimits.b - (fibonacciLimits.x1 - fibonacciLimits.a);
            fibonacciLimits.y1 = fibonacciLimits.y2;
            fibonacciLimits.y2 = counter.execute(fibonacciLimits.x2);
        } else {
            fibonacciLimits.b = fibonacciLimits.x2;
            fibonacciLimits.x2 = fibonacciLimits.x1;
            fibonacciLimits.x1 = fibonacciLimits.a + (fibonacciLimits.b - fibonacciLimits.x2);
            fibonacciLimits.y2 = fibonacciLimits.y1;
            fibonacciLimits.y1 = counter.execute(fibonacciLimits.x1);
        }
    }

    value = (fibonacciLimits.x1 + fibonacciLimits.x2) / 2;
}

double fibonacci_step::get_value_and_update(vector x0) {
    return value;
}

std::string fibonacci_step::name() {
    return "Fibonacci step";
}
