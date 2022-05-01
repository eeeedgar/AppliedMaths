cmake_minimum_required(VERSION 3.17)
project(Lab-2)

set(CMAKE_CXX_STANDARD 20)

include_directories(../Lab-1/)

add_executable(Lab-2 main.cpp ../Lab-1/dichotomy.cpp ../Lab-1/dichotomy.h
        ../Lab-1/fibonacci.cpp ../Lab-1/fibonacci.h
        ../Lab-1/brent.cpp ../Lab-1/brent.h
        ../Lab-1/goldenRatio.cpp ../Lab-1/goldenRatio.h
        ../Lab-1/parabolic.cpp ../Lab-1/parabolic.h
        ../Lab-1/general.h ../Lab-1/general.cpp)
