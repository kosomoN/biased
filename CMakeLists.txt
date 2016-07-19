cmake_minimum_required(VERSION 2.8.9)
project(survival)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

include_directories(include)
include_directories("src/")

file(GLOB SOURCES "src/*.cpp")

add_executable(survival ${SOURCES})
target_link_libraries(survival ${OPENGL_LIBRARY})
target_link_libraries(survival GLEW)
target_link_libraries(survival glfw)

