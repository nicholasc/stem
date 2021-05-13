#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stem/Program.hpp>
#include <stem/Vector.hpp>
#include <stem/Buffer.hpp>
#include <stem/Geometry.hpp>

const std::string vertex = R"(
  #version 330 core
  in vec2 position;

  void main() {
    gl_Position = vec4(position, 0.0f, 1.0f);
  }
)";

const std::string fragment = R"(
  #version 330 core
  out vec4 color;
  uniform vec2 resolution;

  void main() {
    vec2 uv = gl_FragCoord.xy / resolution;
    color = vec4(uv.x, uv.y, 0.0, 1.0);
  }
)";

int main(void) {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    printf("Failed to initialize OpenGL context\n");
    return -1;
  }

  // create a simple program
  stem::Program program({
    .vertex = vertex,
    .fragment = fragment,
    .uniforms = {{"resolution", stem::Vector2f{640.f, 480.f}}},
  });

  // clang-format off
  // create a simple square geometry
  stem::Geometry geometry({
    {
      .name = "position",
      .size = 2,
      .buffer = stem::FloatBuffer({
        -1.f, -1.f,
        1.f, -1.f,
        1.f, 1.0f,

        1.f, 1.f,
        -1.f, 1.f,
        -1.f, -1.f
      })
    }
  });
  // clang-format on

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    program.use();
    geometry.draw(program);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  geometry.destroy();
  program.destroy();

  glfwTerminate();
  return 0;
}