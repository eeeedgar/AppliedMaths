#include <iostream>
#include "general.h"
#include "dichotomy.h"
#include "fibonacci.h"
#include "goldenRatio.h"

using namespace std;

int main()
{
  double a = 0;
  double b = 10;
  double eps = 0.01;
  auto limits = Limits{a, b};

  double xDichotomy = dichotomyGetMinimum(limits, eps);
  cout << xDichotomy << "\t" << f(xDichotomy) << endl;

  double xGoldenRatio = goldenRatioGetMinimum(limits, eps);
  cout << xGoldenRatio << "\t" << f(xGoldenRatio) << endl;

  double xFibonacci = fibonacciGetMinimum(limits, eps);
  cout << xFibonacci << "\t" << f(xFibonacci) << endl;
}
