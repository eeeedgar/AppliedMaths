//
// Created by Veka Belaia on 04.05.2022.
//

#ifndef LAB_2_GRADIENT_DESCEND_ITERATIONS_COUNTER_H
#define LAB_2_GRADIENT_DESCEND_ITERATIONS_COUNTER_H
#include "quadratic_function.h"

class gradient_descend_iterations_counter {
private:
    quadratic_function& function;
    double eps;
    vector point;
public:
    gradient_descend_iterations_counter(quadratic_function&, double eps, vector point);
    double execute(double step);
};


#endif //LAB_2_GRADIENT_DESCEND_ITERATIONS_COUNTER_H
