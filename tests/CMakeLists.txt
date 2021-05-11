# include dependencies
include(${PROJECT_SOURCE_DIR}/cmake/catch.cmake)

# define testing options
option(ENABLE_GL_TESTS "Build tests with OpenGL calls" ON)

# set default sources
set(SOURCES main.cpp)

# check gl tests 
if(ENABLE_GL_TESTS)
  # add flag to source code
  add_definitions(-DENABLE_GL_TESTS)

  # append gl tests
  list(APPEND SOURCES
    Program.cpp
  )
endif()

# add test sources 
add_executable(tests ${SOURCES})

# link with stem
target_link_libraries(tests stem)