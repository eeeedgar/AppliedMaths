//
// Created by edgar on 3/31/2022.
//

#include <vector>
#include <iostream>
#include "fibonacci.h"

int getFibonacciSequenceElementNumberByValue(int value, std::vector<int>& fibonacciSequence)
{
  int a = 1;
  int b = 1;
  fibonacciSequence.push_back(a);
  fibonacciSequence.push_back(b);
  int n = 1;
  int c;
  while (b < value)
  {
	c = b;
	b = b + a;
	n++;
	fibonacciSequence.push_back(b);
	a = c;
  }
  return n;
}

int fibonacciGetIterationNumberAndFillFibonacciSequence(Limits limits, double eps, std::vector<int>& fibonacciSequence)
{
  int fn = ceil(std::abs(limits.a - limits.b) / eps);
  return getFibonacciSequenceElementNumberByValue(fn, fibonacciSequence);
}

FibonacciLimits fibonacciGetNewLimits(FibonacciLimits limits)
{
  if (limits.y1 > limits.y2)
  {
	limits.a = limits.x1;
	limits.x1 = limits.x2;
	limits.x2 = limits.b - (limits.x1 - limits.a);
	limits.y1 = limits.y2;
	limits.y2 = f(limits.x2);
  }
  else
  {
	limits.b = limits.x2;
	limits.x2 = limits.x1;
	limits.x1 = limits.a + (limits.b - limits.x2);
	limits.y2 = limits.y1;
	limits.y1 = f(limits.x1);
  }

  return limits;
}

double fibonacciGetMinimum(Limits limits, double eps)
{
  std::vector<int> fibonacciSequence = std::vector<int>();
  int n = fibonacciGetIterationNumberAndFillFibonacciSequence(limits, eps, fibonacciSequence);

  double x1 = limits.a + (limits.b - limits.a) * fibonacciSequence[n - 2] / fibonacciSequence[n];
  double x2 = limits.b - (limits.b - limits.a) * fibonacciSequence[n - 2] / fibonacciSequence[n];

  double y1 = f(x1);
  double y2 = f(x2);


  auto fibonacciLimits = FibonacciLimits{limits.a, limits.b, x1, x2, y1, y2};

  for (int i = n; i > 1; i--)
  {
	fibonacciLimits = fibonacciGetNewLimits(fibonacciLimits);
  }

  return (fibonacciLimits.x1 + fibonacciLimits.x2) / 2;
}
