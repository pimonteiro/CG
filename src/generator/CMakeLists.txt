cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(generator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")
add_executable(${PROJECT_NAME} generator.cpp box.cpp cone.cpp plane.cpp sphere.cpp annulus.cpp outputAux.cpp bezierPatch.cpp normal.cpp ../lib/matrix.cpp ../lib/point.cpp)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")
