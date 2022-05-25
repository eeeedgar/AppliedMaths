//
// Created by Veka Belaia on 06.05.2022.
//

#ifndef LAB_2_CONJUGATE_GRADIENTS_METHOD_H
#define LAB_2_CONJUGATE_GRADIENTS_METHOD_H
#include "quadratic_function.h"
#include "general.h"


class conjugate_gradients_method {
private:
    quadratic_function& function;
    logger log;
    double eps;
    double minimize(vector xk, vector pk);
public:
    conjugate_gradients_method(quadratic_function& func, logger& log, double eps);
    vector execute(vector point);
};


#endif //LAB_2_CONJUGATE_GRADIENTS_METHOD_H
