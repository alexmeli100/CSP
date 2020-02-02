cmake_minimum_required(VERSION 3.13)
project(csp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fconcepts" )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(csp main.cpp csp.h variable.h csp.cpp csp.h domain.h domain.h assignment.h constraint.h)
target_link_libraries(csp ${CONAN_LIBS})