#pragma once

#include <string>
#include <glad/gl.h>
#include <stem/Exception.hpp>

class VertexShader;
class FragmentShader;

namespace stem {

class ProgramLinkException : public Exception {
public:
  /// @brief ProgramLinkException's class constructor
  /// @param id The faulty program's OpenGL identifier
  /// @return ProgramLinkException
  ProgramLinkException(const uint32_t id);
};

class Program {
private:
  /// @brief The internal gl program identifier
  uint32_t _id;

public:
  /// @brief Program constructor
  /// @return Program
  Program();

  /// @brief Program destructor
  /// @return void
  ~Program();

  /// @brief Returns the shader identifier
  /// @return The shader identifier
  const uint32_t getId() const;

  /// @brief Sets the program's shaders source code
  /// @param vertexSource The source of the vertex shader
  /// @param fragmentShader The source of the fragment shader
  /// @return void
  void setSource(
    const std::string &vertexSource,
    const std::string &fragmentSource
  ) const;

  /// @brief Sets the program's shaders source code & compiles them
  /// @param vertexSource The source of the vertex shader
  /// @param geometrySource The source of the geometry shader
  /// @param fragmentShader The source of the fragment shader
  /// @return void
  void setSource(
    const std::string &vertexSource,
    const std::string &geometrySource,
    const std::string &fragmentSource
  ) const;

  /// @brief Links the program object
  /// @return void
  void link() const;

  /// @brief Binds the program for usage in the current rendering state
  /// @return void
  void use() const;

  /// @brief Destroys the program instance
  /// @return void
  void destroy();
};

} // namespace stem