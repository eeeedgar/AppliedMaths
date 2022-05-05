#ifndef LAB_2_GRADIENT_DESCEND_H
#define LAB_2_GRADIENT_DESCEND_H

#include "quadratic_function.h"
#include "gradient_descend_step.h"
#include "general.h"

class gradient_descend {
private:
    quadratic_function& function;
    gradient_descend_step& step;
    logger& log;
    double eps;
    vector curr, prev;
public:
    gradient_descend(quadratic_function& func, gradient_descend_step& step, logger& log, double eps);
    vector execute(vector start_point);
    vector make_iteration();
};


#endif
