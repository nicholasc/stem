# include dependencies
include(${PROJECT_SOURCE_DIR}/cmake/catch.cmake)

# add test sources 
add_executable(tests
  main.cpp
  core/Program.cpp
)

# link with stem
target_link_libraries(tests stem)