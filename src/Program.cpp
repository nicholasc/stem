#include <glm/gtc/type_ptr.hpp>
#include <stem/Error.hpp>
#include <stem/Program.hpp>

namespace stem {

ShaderSyntaxError::ShaderSyntaxError(const uint32_t id) {
  // get error log length
  int length = 0;
  glAssert(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

  // fetch the error log buffer
  char buffer[length];
  glAssert(glGetShaderInfoLog(id, length, NULL, buffer));

  // store as error message
  _message = buffer;
}

ProgramLinkException::ProgramLinkException(const uint32_t id) {
  // get terror log length
  int length = 0;
  glAssert(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length));

  // fetch the error log buffer
  char buffer[length];
  glAssert(glGetProgramInfoLog(id, length, NULL, buffer));

  // store as error message
  _message = buffer;
}

inline void
Program::compile(const GLenum type, const std::string &source) const {
  // empty source code are not compiled
  if (source.empty()) return;

  // create & compile the shader
  const char *src = source.c_str();
  const int shaderId = glCreateShader(type);
  glAssert(glShaderSource(shaderId, 1, &src, 0));
  glAssert(glCompileShader(shaderId));

  // throw syntax error on failure
  int success;
  glAssert(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success));
  if (!success) throw ShaderSyntaxError(shaderId);

  // attach shader & release
  glAssert(glAttachShader(_id, shaderId));
  glAssert(glDeleteShader(shaderId));
}

Program::Program(const Settings settings) {
  // create program
  _id = glCreateProgram();

  // compile shaders
  compile(GL_VERTEX_SHADER, settings.vertex);
  compile(GL_GEOMETRY_SHADER, settings.geometry);
  compile(GL_FRAGMENT_SHADER, settings.fragment);

  // link & validate
  glAssert(glLinkProgram(_id));
  glAssert(glValidateProgram(_id));

  // throw linking error on failure
  int success;
  glAssert(glGetProgramiv(_id, GL_LINK_STATUS, &success));
  if (!success) throw ProgramLinkException(_id);

  int count;

  // get active uniforms count
  glAssert(glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &count));

  // iterate & store for value binding on usage
  for (size_t index = 0; index < count; index++) {
    char buffer[64];
    int length = 0;
    int size = 0;
    uint32_t type = 0;

    // get active uniform information
    glAssert(glGetActiveUniform(
      _id, index, sizeof(buffer), &length, &size, &type, buffer
    ));

    // get location & convert buffer to name
    const int location = glGetUniformLocation(_id, buffer);
    const std::string name(buffer);

    // store active uniform
    _activeUniforms.insert(std::make_pair(name, ActiveUniform(location, type)));
  }

  // iterate uniforms settings
  for (const Uniform uniform : settings.uniforms) {
    setUniform(uniform);
  }

  // get active attributes count
  glAssert(glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTES, &count));

  // iterate & store for geometry attributes binding
  for (size_t index = 0; index < count; index++) {
    char buffer[64];
    int length = 0;
    int size = 0;
    uint32_t type = 0;

    // get active attribute information
    glAssert(glGetActiveAttrib(
      _id, index, sizeof(buffer), &length, &size, &type, buffer
    ));

    // get location & convert buffer to name
    const int location = glGetAttribLocation(_id, buffer);
    const std::string name(buffer);

    // store active attribute
    _activeAttributes.insert(
      std::make_pair(name, ActiveAttribute(location, type))
    );
  }
}

const uint32_t Program::getId() const {
  return _id;
}

void Program::setUniform(const std::string name, const UniformValue value) {
  // find matching active uniform or skip
  auto iterator = _activeUniforms.find(name);
  if (iterator == _activeUniforms.end()) return;

  // store the uniform value
  ActiveUniform &activeUniform = iterator->second;
  activeUniform.value = value;
  activeUniform.needsUpdate = true;
}

void Program::setUniform(const Uniform uniform) {
  setUniform(uniform.first, uniform.second);
};

const std::optional<Program::ActiveAttribute>
Program::getAttribute(const std::string name) const {
  auto iterator = _activeAttributes.find(name);
  if (iterator == _activeAttributes.end()) return {};

  return iterator->second;
}

const std::unordered_map<std::string, Program::ActiveAttribute> &
Program::getAttributes() const {
  return _activeAttributes;
}

void Program::use() {
  // bind program for usage
  glAssert(glUseProgram(_id));

  // iterate active uniforms
  for (std::pair<const std::string, ActiveUniform> &pair : _activeUniforms) {
    // get a reference to the active uniform
    ActiveUniform &uniform = pair.second;

    // only proceed with changed uniforms
    if (!uniform.needsUpdate) continue;

    // send the value the program on the gpu
    switch (uniform.type) {
    case GL_INT:
      glAssert(glUniform1i(uniform.location, std::get<int>(uniform.value)));
      break;
    case GL_UNSIGNED_INT:
      glAssert(
        glUniform1f(uniform.location, std::get<unsigned int>(uniform.value))
      );
      break;
    case GL_FLOAT:
      glAssert(glUniform1f(uniform.location, std::get<float>(uniform.value)));
      break;
    case GL_DOUBLE:
      glAssert(glUniform1f(uniform.location, std::get<double>(uniform.value)));
      break;
    case GL_INT_VEC2:
      glAssert(glUniform2iv(
        uniform.location, 1, glm::value_ptr(std::get<Vector2i>(uniform.value))
      ));
      break;
    case GL_UNSIGNED_INT_VEC2:
      glAssert(glUniform2uiv(
        uniform.location, 1, glm::value_ptr(std::get<Vector2u>(uniform.value))
      ));
      break;
    case GL_FLOAT_VEC2:
      glAssert(glUniform2fv(
        uniform.location, 1, glm::value_ptr(std::get<Vector2f>(uniform.value))
      ));
      break;
    case GL_DOUBLE_VEC2:
      glAssert(glUniform2dv(
        uniform.location, 1, glm::value_ptr(std::get<Vector2d>(uniform.value))
      ));
      break;
    }

    // mark uniform as updated
    uniform.needsUpdate = false;
  }
}

void Program::destroy() {
  glAssert(glDeleteProgram(_id));
  _id = 0;
}

} // namespace stem