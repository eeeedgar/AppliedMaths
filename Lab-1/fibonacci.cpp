#include "fibonacci.h"

int fibonacciMethod::fibonacciGetIterationNumberAndFillFibonacciSequence(Limits limits, double eps, std::vector<int> &fibonacciSequence) {
    int fn = ceil(std::abs(limits.a - limits.b) / eps);
    return getFibonacciSequenceElementNumberByValue(fn, fibonacciSequence);
}

FibonacciLimits fibonacciMethod::fibonacciGetNewLimits(FibonacciLimits limits) {
    if (limits.y1 > limits.y2) {
        limits.a = limits.x1;
        limits.x1 = limits.x2;
        limits.x2 = limits.b - (limits.x1 - limits.a);
        limits.y1 = limits.y2;
        limits.y2 = func(limits.x2);
    } else {
        limits.b = limits.x2;
        limits.x2 = limits.x1;
        limits.x1 = limits.a + (limits.b - limits.x2);
        limits.y2 = limits.y1;
        limits.y1 = func(limits.x1);
    }
    ++functionCallsNumber;

    return limits;
}

int fibonacciMethod::getFibonacciSequenceElementNumberByValue(int value, std::vector<int> &fibonacciSequence) {
    int a = 1;
    int b = 1;
    fibonacciSequence.push_back(a);
    fibonacciSequence.push_back(b);
    int n = 1;
    int c;
    while (b < value) {
        c = b;
        b = b + a;
        n++;
        fibonacciSequence.push_back(b);
        a = c;
    }
    return n;
}

double fibonacciMethod::findMinimum(double a, double b, double eps) {
    log.log("Итерация\ta\tb\tВызовов функции\n");

    int iteration = 0;
    std::vector<int> fibonacciSequence = std::vector<int>();
    Limits limits = {a, b};
    int n = fibonacciGetIterationNumberAndFillFibonacciSequence(limits, eps, fibonacciSequence);

    double x1 = limits.a + (limits.b - limits.a) * fibonacciSequence[n - 2] / fibonacciSequence[n];
    double x2 = limits.b - (limits.b - limits.a) * fibonacciSequence[n - 2] / fibonacciSequence[n];

    double y1 = func(x1);
    double y2 = func(x2);
    functionCallsNumber += 2;


    auto fibonacciLimits = FibonacciLimits{limits.a, limits.b, x1, x2, y1, y2};

    for (int i = n; i > 1; i--) {
        fibonacciLimits = fibonacciGetNewLimits(fibonacciLimits);
        log.log({fibonacciLimits.a, fibonacciLimits.b}, ++iteration, functionCallsNumber);
    }

    return (fibonacciLimits.x1 + fibonacciLimits.x2) / 2;
}

fibonacciMethod::fibonacciMethod(double (*func)(double), const logger &log) : func(func), log(log) {
    functionCallsNumber = 0;
}

void fibonacciMethod::reset() {
    functionCallsNumber = 0;
}

