cmake_minimum_required(VERSION 2.8.9)
project(survival)

set(CMAKE_BUILD_TYPE Debug)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(anax REQUIRED)

include_directories(include)
include_directories("src/")

file(GLOB SOURCES "src/*.cpp")

add_executable(survival ${SOURCES})
target_link_libraries(survival ${OPENGL_LIBRARY})
target_link_libraries(survival GLEW)
target_link_libraries(survival glfw)
target_link_libraries(survival anax)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
