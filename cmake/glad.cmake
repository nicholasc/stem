# include header directory
include_directories(libs/glad/include)

# define source files
set(GLAD_SOURCES libs/glad/src/glad.c)

# add library target
add_library(glad ${GLAD_SOURCES})