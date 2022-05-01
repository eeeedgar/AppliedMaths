cmake_minimum_required(VERSION 3.17)
project(applied_maths)

set(CMAKE_CXX_STANDARD 20)
include_directories(Lab-1 Lab-1/build-debug-output)
include_directories(Lab-2 Lab-2/build-debug-output)

add_executable(applied-maths Lab-1/dichotomy.cpp Lab-1/dichotomy.h Lab-1/general.cpp Lab-1/general.h Lab-1/fibonacci.cpp Lab-1/fibonacci.h Lab-1/goldenRatio.cpp Lab-1/goldenRatio.h Lab-1/parabolic.cpp Lab-1/parabolic.h Lab-1/brent.cpp Lab-1/brent.h Lab-1/function_minimize.cpp Lab-1/function_minimize.h)