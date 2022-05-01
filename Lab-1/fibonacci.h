#ifndef APPLIEDMATHS_LAB1__FIBONACCI_H_
#define APPLIEDMATHS_LAB1__FIBONACCI_H_

#include <vector>
#include "general.h"

struct FibonacciLimits {
    double a, b, x1, x2, y1, y2;
};

int getFibonacciSequenceElementNumberByValue(int, std::vector<int> &);

FibonacciLimits fibonacciGetNewLimits(FibonacciLimits);

int fibonacciGetIterationNumberAndFillFibonacciSequence(Limits, double, const std::vector<int> &);

double fibonacciGetMinimum(Limits, double, std::string);

class fibonacciMethod {
private:
    int functionCallsNumber;
    logger log;
    double (*func)(double);
    int fibonacciGetIterationNumberAndFillFibonacciSequence(Limits, double, std::vector<int> &);
    FibonacciLimits fibonacciGetNewLimits(FibonacciLimits);
    int getFibonacciSequenceElementNumberByValue(int, std::vector<int> &);
public:
    fibonacciMethod(double (*func)(double), const logger& log);
    double findMinimum(double a, double b, double eps);
    void reset();
};

#endif //APPLIEDMATHS_LAB1__FIBONACCI_H_
