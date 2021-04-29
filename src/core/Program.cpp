#include <stem/core/Shader.hpp>
#include <stem/core/Program.hpp>

namespace stem {

ProgramLinkException::ProgramLinkException(const uint32_t id) {
  int length = 0;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

  char buffer[length];
  glGetProgramInfoLog(id, length, NULL, buffer);

  _message = buffer;
}

Program::Program() {
  _id = glCreateProgram();
}

Program::~Program() {
  destroy();
}

void Program::setSource(
  const std::string &vertexSource,
  const std::string &fragmentSource
) const {
  setSource(vertexSource, NULL, fragmentSource);
}

void Program::setSource(
  const std::string &vertexSource,
  const std::string &geometrySource,
  const std::string &fragmentSource
) const {
  if (vertexSource.c_str()) {
    VertexShader vertex;
    vertex.setSource(vertexSource.c_str());
    vertex.compile();

    glAttachShader(_id, vertex.getId());

    vertex.destroy();
  }

  if (geometrySource.c_str()) {
    GeometryShader geometry;
    geometry.setSource(geometrySource.c_str());
    geometry.compile();

    glAttachShader(_id, geometry.getId());

    geometry.destroy();
  }

  if (fragmentSource.c_str()) {
    FragmentShader fragment;
    fragment.setSource(fragmentSource.c_str());
    fragment.compile();

    glAttachShader(_id, fragment.getId());

    fragment.destroy();
  }
}

void Program::link() const {
  glLinkProgram(_id);

  GLint success;
  glGetProgramiv(_id, GL_LINK_STATUS, &success);

  if (!success) {
    throw ProgramLinkException(_id);
  }
}

void Program::use() const {
  glUseProgram(_id);
}

void Program::destroy() {
  glDeleteProgram(_id);
  _id = 0;
}

} // namespace stem