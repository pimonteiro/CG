cmake_minimum_required(VERSION 3.5)

project(globalProject)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/generator)
add_subdirectory(src/engine)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
