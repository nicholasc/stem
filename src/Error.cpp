#include <iostream>
#include <glad/gl.h>
#include <stem/Error.hpp>

namespace stem {

void glCheckError(
  const char *file,
  const uint32_t line,
  const char *expression
) {
  // attempt to retrieve error or return
  const uint32_t errorCode = glGetError();
  if (!errorCode) return;

  std::string fileString = file;
  std::string error = "Unknown error";
  std::string description = "No description";

  switch (errorCode) {
  case GL_INVALID_ENUM: {
    error = "GL_INVALID_ENUM";
    description = "Invalid enumeration specified as argument in statement";
    break;
  }

  case GL_INVALID_VALUE: {
    error = "GL_INVALID_VALUE";
    description = "A numeric argument is out of range.";
    break;
  }

  case GL_INVALID_OPERATION: {
    error = "GL_INVALID_OPERATION";
    description =
      "The specified operation is not allowed in the current state.";
    break;
  }

  case GL_STACK_OVERFLOW: {
    error = "GL_STACK_OVERFLOW";
    description = "This command would cause a stack overflow.";
    break;
  }

  case GL_STACK_UNDERFLOW: {
    error = "GL_STACK_UNDERFLOW";
    description = "This command would cause a stack underflow.";
    break;
  }

  case GL_OUT_OF_MEMORY: {
    error = "GL_OUT_OF_MEMORY";
    description = "There is not enough memory left to execute the command.";
    break;
  }
  }

  std::cerr << "OpenGL Error: " << error << std::endl
            << description << std::endl
            << std::endl
            << fileString.substr(fileString.find_last_of("\\/") + 1)
            << std::endl
            << line << " | " << expression << std::endl
            << std::endl;
}

} // namespace stem