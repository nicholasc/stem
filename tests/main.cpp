#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <iostream>

#if ENABLE_GL_TESTS

#include <glad/gl.h>
#include <GLFW/glfw3.h>

const int initGL() {
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  GLFWwindow *window = glfwCreateWindow(640, 480, "", NULL, NULL);

  glfwMakeContextCurrent(window);

  const int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    printf("Failed to initialize OpenGL context\n");
    return -1;
  }

  return version;
}

void terminateGL() {
  glfwTerminate();
}

#endif

int main(int argc, char *argv[]) {
#if ENABLE_GL_TESTS
  const int version = initGL();
  if (version == -1) return version;

  std::cout << "OpenGL " << GLAD_VERSION_MAJOR(version) << "."
            << GLAD_VERSION_MINOR(version) << std::endl;
#else
  std::cout << "OpenGL: disabled" << std::endl;
#endif

  const int result = Catch::Session().run(argc, argv);

#if ENABLE_GL_TESTS
  terminateGL();
#endif

  return result;
}