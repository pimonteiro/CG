cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(generator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
add_executable(${PROJECT_NAME} main.cpp box.cpp cone.cpp plane.cpp sphere.cpp outputAux.cpp)

