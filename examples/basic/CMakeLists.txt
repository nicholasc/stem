# example sources
set(SOURCES main.cpp)

# create executable target
add_executable(basic ${SOURCES})

# link with stem
target_link_libraries(basic stem)
