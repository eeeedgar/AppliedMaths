#ifndef DICHOTOMYMETHOD_CMAKE_BUILD_DEBUG_GENERAL_H_
#define DICHOTOMYMETHOD_CMAKE_BUILD_DEBUG_GENERAL_H_

#include <cmath>
#include <string>

struct Limits {
    double a;
    double b;
};

bool isEnough(Limits, double);

class logger {
private:
    std::ostream& stream;
public:
    logger(std::ostream& ostream);
    virtual void log(Limits, int iteration, int functionCalls);
    virtual void log(std::string);
    ~logger();
};

class nullLogger : logger {
public:
    nullLogger();
    void log(Limits, int iteration, int functionCalls) override;
    void log(std::string) override;
};
#endif //DICHOTOMYMETHOD_CMAKE_BUILD_DEBUG_GENERAL_H_
