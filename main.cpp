#include <iostream>
#include "general.h"
#include "dichotomy.h"
#include "fibonacci.h"
#include "goldenRatio.h"
#include "parabolic.h"

using namespace std;

int main()
{
  double a = -4;
  double b = 4;
  double eps = 0.01;
  auto limits = Limits{a, b};

  double xDichotomy = dichotomyGetMinimum(limits, eps);
  cout << "dichotomy:\t" << xDichotomy << "\t" << f(xDichotomy) << endl;

  double xGoldenRatio = goldenRatioGetMinimum(limits, eps);
  cout << "golden ratio:\t" << xGoldenRatio << "\t" << f(xGoldenRatio) << endl;

  double xFibonacci = fibonacciGetMinimum(limits, eps);
  cout << "fibonacci:\t" << xFibonacci << "\t" << f(xFibonacci) << endl;

  double xParabolic = parabolicGetMinimum(limits, eps);
  cout << "parabolic:\t" << xParabolic << "\t" << f(xParabolic) << endl;
}
