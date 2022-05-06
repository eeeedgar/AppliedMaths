//
// Created by Veka Belaia on 02.05.2022.
//

#include "gradient_descend.h"
#include <string>

gradient_descend::gradient_descend(quadratic_function &f, gradient_descend_step &s, logger &l, double eps)
: function(f), step(s), log(l), eps(eps) {
}

vector gradient_descend::execute(vector start_point) {
    int iteration = 0;
    curr = start_point;
    prev = {curr.x + 2 * eps, curr.y + 2 * eps};
    log.log(function.to_string());
    log.log(step.name());
    log.log( std::to_string(start_point.x) + ";" + std::to_string(start_point.y));
    log.log("iteration\tx(k)\ty(k)\tx(k + 1)\ty(k + 1)\tstep");
    vector grad = function.derivative(start_point);

    while (distance(curr, prev) >= eps && grad.len() >= eps) {
        prev = curr;
        grad = function.derivative(prev);
        double s = step.get_value_and_update(prev);
        curr = {prev.x - s * grad.x, prev.y - s * grad.y};
        log.log(std::to_string(++iteration) + "\t" + std::to_string(prev.x) + "\t" + std::to_string(prev.y) + "\t" + std::to_string(curr.x)+ "\t" + std::to_string(curr.y) + "\t" + std::to_string(s));
        if (iteration > 1000 || curr.x < -1e3 || curr.y < -1e3) {
            log.log("Does not converge");
            return curr;
        }
    }
    log.log("ans = (" + std::to_string(curr.x) + "; " + std::to_string(curr.y) + ")");
    return curr;
}