//
// Created by edgar on 3/31/2022.
//

#ifndef APPLIEDMATHS_LAB1__FIBONACCI_H_
#define APPLIEDMATHS_LAB1__FIBONACCI_H_

#include <vector>
#include "general.h"

struct FibonacciLimits
{
  double a, b, x1, x2, y1, y2;
};

int getFibonacciSequenceElementNumberByValue(int, std::vector<int>&);

FibonacciLimits fibonacciGetNewLimits(FibonacciLimits);

int fibonacciGetIterationNumberAndFillFibonacciSequence(Limits, double, const std::vector<int>&);

double fibonacciGetMinimum(Limits, double);

#endif //APPLIEDMATHS_LAB1__FIBONACCI_H_
