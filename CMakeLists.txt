cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
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
include(cmake/glad.cmake)
include(cmake/glfw.cmake)
include(cmake/glm.cmake)

# detect debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DSTEM_DEBUG)
endif()

# include header directory
include_directories(include)

# locate all source files
file(GLOB_RECURSE SOURCES src/**.cpp)

# add library target
add_library(stem ${SOURCES})

# link with dependencies
target_link_libraries(stem
  ${OPENGL_LIBRARIES}
  glad
  glfw
  glm_static
)

# add examples
add_subdirectory(examples)

# add tests
add_subdirectory(tests)