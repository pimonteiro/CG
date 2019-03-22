cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(solarSystemGen)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")
add_executable(solarSysGen solarSystemGen.cpp ../generator/sphere.cpp ../generator/outputAux.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
