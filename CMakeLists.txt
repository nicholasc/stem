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

# include dependencies
include(cmake/glfw.cmake)
include(cmake/glad.cmake)

# include header directory
include_directories(include)

# locate all source files
file(GLOB_RECURSE SOURCES src/**.cpp)

# add library target
add_library(stem ${SOURCES})

# link with dependencies
target_link_libraries(stem
  ${OPENGL_LIBRARIES}
  glfw
  glad
)

# add examples
add_subdirectory(examples)