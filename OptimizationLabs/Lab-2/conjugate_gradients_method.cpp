//
// Created by Veka Belaia on 06.05.2022.
//

#include <goldenRatio.h>
#include "conjugate_gradients_method.h"

conjugate_gradients_method::conjugate_gradients_method(quadratic_function &func, logger &log, double eps)
: function(func), log(log), eps(eps) {
}

vector conjugate_gradients_method::execute(vector point) {
    int iteration  = 0;
    log.log(function.to_string());
    log.log("Conjugate gradients");
    log.log(std::to_string(point.x) + ";" + std::to_string(point.y));
    log.log("iteration\tx(k)\ty(k)\tx(k + 1)\ty(k + 1)\tstep");
    vector p_prev;
    vector p_curr;
    vector curr = point;
    vector grad_prev = {0, 0};
    vector grad_curr = function.derivative(curr);
    p_curr = grad_curr;
    double a = minimize(curr, p_curr);
    vector prev = curr;
    curr = {curr.x - a * grad_curr.x, curr.y - a * grad_curr.y};
    log.log(std::to_string(++iteration) + "\t" + std::to_string(prev.x) + "\t" + std::to_string(prev.y) + "\t" + std::to_string(curr.x)+ "\t" + std::to_string(curr.y) + "\t" + std::to_string(a));
    while (distance(prev, curr) >= eps && grad_curr.len() >= eps) {
        grad_prev = grad_curr;
        grad_curr = function.derivative(curr);
        double bk = iteration % 3 == 0 ? 0 : grad_curr.len() /  grad_prev.len();
        p_prev = p_curr;
        p_curr = {grad_curr.x + bk * p_prev.x, grad_curr.y + bk * p_prev.y};
        a = minimize(curr, p_curr);
        prev = curr;
        curr = {curr.x - a * grad_curr.x, curr.y - a * grad_curr.y};
        log.log(std::to_string(++iteration) + "\t" + std::to_string(prev.x) + "\t" + std::to_string(prev.y) + "\t" + std::to_string(curr.x)+ "\t" + std::to_string(curr.y) + "\t" + std::to_string(a));
        if (iteration > 1000 || curr.x < -1e3 || curr.y < -1e3) {
            log.log("Does not converge");
            return curr;
        }
    }
    log.log("ans = (" + std::to_string(curr.x) + "; " + std::to_string(curr.y) + ")");
    return curr;
}

double conjugate_gradients_method::minimize(vector xk, vector pk) {
    Limits limits = {0, 1};
    double ceps = 0.0001;
    double x1 = limits.b - (limits.b - limits.a) / goldenRatioMethod::goldenRatio();
    double x2 = limits.a + (limits.b - limits.a) / goldenRatioMethod::goldenRatio();
    auto goldenRatioLimits = GoldenRatioLimits{limits.a, limits.b, x1, x2};

    while (!isEnough({goldenRatioLimits.a, goldenRatioLimits.b}, ceps)) {
        vector arg1 = {xk.x - goldenRatioLimits.x1 * pk.x, xk.y - goldenRatioLimits.x1 * pk.y};
        vector arg2 = {xk.x - goldenRatioLimits.x2 * pk.x, xk.y - goldenRatioLimits.x2 * pk.y};
        if (function.value(arg1) >= function.value(arg2)) {
            goldenRatioLimits.a = goldenRatioLimits.x1;
            goldenRatioLimits.x1 = goldenRatioLimits.x2;
            goldenRatioLimits.x2 = goldenRatioLimits.b - (goldenRatioLimits.x1 - goldenRatioLimits.a);
        } else {
            goldenRatioLimits.b = goldenRatioLimits.x2;
            goldenRatioLimits.x2 = goldenRatioLimits.x1;
            goldenRatioLimits.x1 = goldenRatioLimits.a + (goldenRatioLimits.b - goldenRatioLimits.x2);
        }
    }
    return (goldenRatioLimits.a + goldenRatioLimits.b) / 2;
}
