cmake_minimum_required(VERSION 3.19.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# project name
project(stem)

# setup version number
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

# find opengl implementation
find_package(OpenGL REQUIRED)

# add dependencies 
add_subdirectory(libs/glfw)

# include header directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# locate all source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/**.cpp)

# add library target
add_library(stem ${SOURCES})

# link with dependencies
target_link_libraries(stem
  ${OPENGL_LIBRARIES}
  glfw
)

# add examples
add_subdirectory(examples)