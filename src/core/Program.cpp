#include <iostream>
#include <stem/core/Program.hpp>

namespace stem {

ShaderSyntaxError::ShaderSyntaxError(const uint32_t id) {
  int length = 0;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

  char buffer[length];
  glGetShaderInfoLog(id, length, NULL, buffer);

  _message = buffer;
}

ProgramLinkException::ProgramLinkException(const uint32_t id) {
  int length = 0;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

  char buffer[length];
  glGetProgramInfoLog(id, length, NULL, buffer);

  _message = buffer;
}

void Program::compile(const GLenum type, const std::string &source) const {
  if (source.empty()) return;

  const char *src = source.c_str();

  int shaderId = glCreateShader(type);
  glShaderSource(shaderId, 1, &src, 0);
  glCompileShader(shaderId);

  GLint success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if (!success) {
    throw ShaderSyntaxError(shaderId);
  }

  // attach shader to the program & release
  glAttachShader(_id, shaderId);
  glDeleteShader(shaderId);
}

Program::Program(const Settings settings) {
  _id = glCreateProgram();

  compile(GL_VERTEX_SHADER, settings.vertex);
  compile(GL_GEOMETRY_SHADER, settings.geometry);
  compile(GL_FRAGMENT_SHADER, settings.fragment);

  glLinkProgram(_id);
  glValidateProgram(_id);

  int success;
  glGetProgramiv(_id, GL_LINK_STATUS, &success);

  if (!success) {
    throw ProgramLinkException(_id);
  }
}

Program::~Program() {
  destroy();
}

const uint32_t Program::getId() const {
  return _id;
}

void Program::use() const {
  glUseProgram(_id);
}

void Program::destroy() {
  glDeleteProgram(_id);
  _id = 0;
}

} // namespace stem