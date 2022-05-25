#include "general.h"
#include <iostream>
bool isEnough(Limits limits, double eps) {
    return abs(limits.a - limits.b) < eps;
}

logger::logger(std::ostream& ostream) :
    stream(ostream) {
}

void logger::log(Limits limits, int iteration, int functionCalls) {
    stream << iteration << "\t" << limits.a << "\t" << limits.b << "\t" << functionCalls << "\n";
}

logger::~logger() {
}

void logger::log(std::string str) {
    stream << str << std::endl;
}

nullLogger::nullLogger() : logger(std::cout) {

}

void nullLogger::log(Limits limits, int iteration, int functionCalls) {}

void nullLogger::log(std::string) {
}
