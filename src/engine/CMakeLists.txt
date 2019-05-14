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

if (NOT APPLE)
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif(NOT APPLE)

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

find_package(DevIL REQUIRED)
link_libraries(${IL_LIBRARIES} )
include_directories(${IL_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")
add_executable(engine engine.cpp model.cpp tinyxml2.cpp parser.cpp ../lib/point.cpp group.cpp transformation.cpp translation.cpp scale.cpp rotation.cpp ../lib/matrix.cpp catmull.cpp material.cpp texture.cpp light.cpp spotLight.cpp pointLight.cpp directionalLight.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY} ${IL_LIBRARIES})
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")
