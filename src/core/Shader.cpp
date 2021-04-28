#include <stem/core/Shader.hpp>

namespace stem {

ShaderSyntaxError::ShaderSyntaxError(const uint32_t id) {
  int length = 0;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

  char buffer[length];
  glGetShaderInfoLog(id, length, NULL, buffer);

  _message = buffer;
}

} // namespace stem