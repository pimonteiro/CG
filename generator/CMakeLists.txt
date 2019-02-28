cmake_minimum_required(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
add_executable(generator box.cpp cone.cpp main.cpp plane.cpp sphere.cpp)
