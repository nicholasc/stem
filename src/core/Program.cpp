#include <iostream>
#include <stem/core/Program.hpp>

namespace stem {

ShaderSyntaxError::ShaderSyntaxError(const uint32_t id) {
  // get terror log length
  int length = 0;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

  // fetch the error log buffer
  char buffer[length];
  glGetShaderInfoLog(id, length, NULL, buffer);

  // store as error message
  _message = buffer;
}

ProgramLinkException::ProgramLinkException(const uint32_t id) {
  // get terror log length
  int length = 0;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

  // fetch the error log buffer
  char buffer[length];
  glGetProgramInfoLog(id, length, NULL, buffer);

  // store as error message
  _message = buffer;
}

void Program::compile(const GLenum type, const std::string &source) const {
  // empty source code are not compiled
  if (source.empty()) return;

  // create & compile the shader
  const char *src = source.c_str();
  const int shaderId = glCreateShader(type);
  glShaderSource(shaderId, 1, &src, 0);
  glCompileShader(shaderId);

  // throw syntax error on failure
  int success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
  if (!success) {
    throw ShaderSyntaxError(shaderId);
  }

  // attach shader & release
  glAttachShader(_id, shaderId);
  glDeleteShader(shaderId);
}

Program::Program(const Settings settings) {
  // create program
  _id = glCreateProgram();

  // compile shaders
  compile(GL_VERTEX_SHADER, settings.vertex);
  compile(GL_GEOMETRY_SHADER, settings.geometry);
  compile(GL_FRAGMENT_SHADER, settings.fragment);

  // link & validate
  glLinkProgram(_id);
  glValidateProgram(_id);

  // throw linking error on failure
  int success;
  glGetProgramiv(_id, GL_LINK_STATUS, &success);
  if (!success) {
    throw ProgramLinkException(_id);
  }

  // get active uniforms count
  int count;
  glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &count);

  // iterate & store for value binding on usage
  for (int index = 0; index < count; index++) {
    char buffer[64];
    int length = 0;
    int size = 0;
    uint32_t type = 0;

    // get active uniform information
    glGetActiveUniform(
      _id, index, sizeof(buffer), &length, &size, &type, buffer
    );

    // get location & convert buffer to name
    const int location = glGetUniformLocation(_id, buffer);
    const std::string name(buffer);

    // store active uniform
    _activeUniforms.insert(std::make_pair(name, ActiveUniform(location, type)));
  }

  // iterate uniforms settings
  for (const Uniform uniform : settings.uniforms) {
    // find matching active uniform or skip
    auto iterator = _activeUniforms.find(uniform.name);
    if (iterator == _activeUniforms.end()) continue;

    // store the user uniform value
    ActiveUniform &activeUniform = iterator->second;
    activeUniform.value = uniform.value;
    activeUniform.needsUpdate = true;
  }
}

Program::~Program() {
  destroy();
}

const uint32_t Program::getId() const {
  return _id;
}

void Program::use() {
  // bind program for usage
  glUseProgram(_id);

  // iterate active uniforms
  for (std::pair<const std::string, ActiveUniform> &pair : _activeUniforms) {
    // get a reference to the active uniform
    ActiveUniform &uniform = pair.second;

    // only proceed with changed uniforms
    if (!uniform.needsUpdate) continue;

    // send the value the program on the gpu
    switch (uniform.type) {
    case GL_FLOAT:
      glUniform1f(uniform.location, std::get<float>(uniform.value));
      break;
    case GL_DOUBLE:
      glUniform1f(uniform.location, std::get<double>(uniform.value));
      break;
    }

    // mark uniform as updated
    uniform.needsUpdate = false;
  }
}

void Program::destroy() {
  glDeleteProgram(_id);
  _id = 0;
}

} // namespace stem