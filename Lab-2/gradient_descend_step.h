//
// Created by Veka Belaia on 02.05.2022.
//

#ifndef LAB_2_GRADIENT_DESCEND_STEP_H
#define LAB_2_GRADIENT_DESCEND_STEP_H
#include "quadratic_function.h"
#include "gradient_descend_iterations_counter.h"
#include <string>

class gradient_descend_step {
protected:
    double eps;
    double value;
    quadratic_function& function;
public:
    gradient_descend_step(double, double, quadratic_function& func);
    virtual double get_value_and_update(vector x0);
    virtual std::string name();
};

class constant_step : public gradient_descend_step {
public:
    constant_step(double, quadratic_function&);
    double get_value_and_update(vector x0) override;
    std::string name() override;
};

class fractional_step : public gradient_descend_step {
private:
    double delta;
    bool predicate(vector, double, double);
public:
    fractional_step(double, double, double, quadratic_function&);
    double get_value_and_update(vector x0) override;
    std::string name() override;
};

class golden_ratio_step : public gradient_descend_step {
private:
    double left_bound, right_bound;
public:
    golden_ratio_step(double left_bound, double right_bound, double eps, vector x0, quadratic_function& func);
    double get_value_and_update(vector x0) override;
    std::string name() override;
};

class fibonacci_step : public gradient_descend_step {
private:
    double left_bound, right_bound;
public:
    fibonacci_step(double left_bound, double right_bound, double eps, vector x0, quadratic_function& func);
    double get_value_and_update(vector x0) override;
    std::string name() override;
};
#endif //LAB_2_GRADIENT_DESCEND_STEP_H
