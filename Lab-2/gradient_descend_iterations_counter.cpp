//
// Created by Veka Belaia on 04.05.2022.
//

#include <cmath>
#include <iostream>
#include "gradient_descend_iterations_counter.h"

gradient_descend_iterations_counter::gradient_descend_iterations_counter(quadratic_function &func, double eps, vector point)
: function(func), eps(eps), point(point) {
}

double gradient_descend_iterations_counter::execute(double step) {
    int iteration = 0;
    vector curr = point;
    vector prev = {curr.x + 2 * eps, curr.y + 2 * eps};
    while (distance(curr, prev) >= eps) {
        prev = curr;
        vector grad = function.derivative(prev);
        curr = {prev.x - step * grad.x, prev.y - step * grad.y};
        ++iteration;
        if (iteration > 1000) {
            return INT16_MAX;
        }
    }

    return iteration;
}
