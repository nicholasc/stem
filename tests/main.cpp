#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main(int argc, char *argv[]) {
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  GLFWwindow *window = glfwCreateWindow(640, 480, "", NULL, NULL);

  glfwMakeContextCurrent(window);

  const int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    printf("Failed to initialize OpenGL context\n");
    return -1;
  }

  printf(
    "OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version)
  );

  const int result = Catch::Session().run(argc, argv);

  glfwTerminate();

  return result;
}