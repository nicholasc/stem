# include header directory
include_directories(libs/glad/include)

# define source files
set(GLAD_SOURCES libs/glad/src/gl.c)

# add library target
add_library(glad ${GLAD_SOURCES})

# set target properties
set_target_properties(glad
  PROPERTIES
   LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libs/glad
   ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libs/glad
)