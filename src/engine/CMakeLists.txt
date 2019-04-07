cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(engine)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")
add_executable(engine engine.cpp model.cpp tinyxml2.cpp parser.cpp point.cpp group.cpp transformation.cpp translation.cpp scale.cpp rotation.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
