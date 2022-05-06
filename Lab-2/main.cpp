#include <iostream>
#include "general.h"
#include "gradient_descend_step.h"
#include "gradient_descend.h"
#include "quadratic_function.h"
#include <string>
#include <vector>
#include <fstream>
#include "conjugate_gradients_method.h"

const std::string output_directory = "../outputs";

// param for all kinds of steps
double eps = 1e-3;
// recommended params for fractional step
double delta = 0.95;
double start_step = 1;

// bounds for searching step;
double left = 0;
double right = 1;

std::vector<quadratic_function> test_functions = {
        quadratic_function(1, 0, 1, 0, 0, 0),
        quadratic_function(10, 0, 1, 0, 0, 0),
        quadratic_function(1, 1, -6, 0, 0, 0),
};

std::vector<std::vector<vector>> starting_points = {
        {{-5, -5}, {5, 0}},
        {{-5, -5}, {0, 5}},
        {{3, 0}, {-2, 2}},
};

void get_constant_step_data() {
    std::string output = output_directory + "/constant_step/";
    std::vector<double> steps = {0.1, 0.3, 0.5};
    int num = 0;
    for (int i = 0; i < test_functions.size(); i++) {
        for (int j = 0; j < steps.size(); j++) {
            for (int k = 0; k < starting_points[i].size(); k++) {
                std::ofstream out;
                out.open(output + "(function" + std::to_string(i + 1) + ")" + std::to_string(++num) + ".txt");
                logger log = logger(out);
                constant_step step = constant_step(steps[j], test_functions[i]);
                gradient_descend gradientDescend = gradient_descend(test_functions[i], step, log, eps);
                gradientDescend.execute(starting_points[i][k]);
                out.close();
            }
        }
    }
}

void get_fractional_step_data() {
    std::string output = output_directory + "/fractional_step/";
    int num = 0;
    for (int i = 0; i < test_functions.size(); i++) {
        for (int k = 0; k < starting_points[i].size(); k++) {
            std::ofstream out;
            out.open(output + "(function" + std::to_string(i + 1) + ")" + std::to_string(++num) + ".txt");
            logger log = logger(out);
            fractional_step step = fractional_step(start_step, delta, eps, test_functions[i]);
            gradient_descend gradientDescend = gradient_descend(test_functions[i], step, log, eps);
            gradientDescend.execute(starting_points[i][k]);
            out.close();
        }
    }
}

void get_golden_ratio_step_data() {
    std::string output = output_directory + "/golden_ratio_step/";
    int num = 0;
    for (int i = 0; i < test_functions.size(); i++) {
        for (int k = 0; k < starting_points[i].size(); k++) {
            std::ofstream out;
            out.open(output + "(function" + std::to_string(i + 1) + ")" + std::to_string(++num) + ".txt");
            logger log = logger(out);
            golden_ratio_step step = golden_ratio_step(left, right,  eps, starting_points[i][k], test_functions[i]);
            gradient_descend gradientDescend = gradient_descend(test_functions[i], step, log, eps);
            gradientDescend.execute(starting_points[i][k]);
            out.close();
        }
    }
}

void get_fibonacci_step_data() {
    std::string output = output_directory + "/fibonacci_step/";
    int num = 0;
    for (int i = 0; i < test_functions.size(); i++) {
        for (int k = 0; k < starting_points[i].size(); k++) {
            std::ofstream out;
            out.open(output + "(function" + std::to_string(i + 1) + ")" + std::to_string(++num) + ".txt");
            logger log = logger(out);
            fibonacci_step step = fibonacci_step(left, right,  eps, starting_points[i][k], test_functions[i]);
            gradient_descend gradientDescend = gradient_descend(test_functions[i], step, log, eps);
            gradientDescend.execute(starting_points[i][k]);
            out.close();
        }
    }
}

int main() {
//    get_constant_step_data();
//    get_fractional_step_data();
//    get_golden_ratio_step_data();
//    get_fibonacci_step_data();
//    get_conjugate_gradients_data();
    get_linear_data();
}
