cmake_minimum_required(VERSION 3.17)
project(OptimizationLabs)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(Lab-1 Lab-1/cmake-build-debug)
add_subdirectory(Lab-2 Lab-2/cmake-build-debug)

add_executable(OptimizationLabs Lab-1/main.cpp Lab-2/main.cpp)