#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stem/core/Program.hpp>

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

  float positions[6] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

  stem::Program program({
    .vertex = R"(
      #version 330 core
      layout(location = 0) in vec2 position;

      void main() {
        gl_Position = vec4(position, 0.0f, 1.0f);
      }
    )",
    .fragment = R"(
      #version 330 core
      layout(location = 0) out vec4 color;

      void main() {
        color = vec4(1.0, 0.0, 0.0, 1.0);
      }
    )",
  });

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  GLuint vertex_array;
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);

  const int pos = glGetAttribLocation(program.getId(), "position");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(
    pos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)0
  );

  glBindVertexArray(vertex_array);
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    program.use();

    // glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  program.destroy();

  glfwTerminate();
  return 0;
}