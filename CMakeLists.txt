cmake_minimum_required(VERSION 3.20)
project(AppliedMaths_Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DichotomyMethod main.cpp dichotomy.cpp dichotomy.h general.cpp general.h fibonacci.cpp fibonacci.h goldenRatio.cpp goldenRatio.h)
