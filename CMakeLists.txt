cmake_minimum_required(VERSION 3.13)
project(csp)

set(CMAKE_CXX_STANDARD 20)

add_executable(csp main.cpp csp.h variable.cpp variable.h csp.cpp csp.h)