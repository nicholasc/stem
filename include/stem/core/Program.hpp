#pragma once

#include <string>
#include <variant>
#include <utility>
#include <vector>
#include <unordered_map>

#include <glad/gl.h>
#include <stem/Exception.hpp>

namespace stem {

class ShaderSyntaxError : public Exception {
public:
  /// @brief ShaderSyntaxError's class constructor
  /// @param id The faulty shader's OpenGL identifier
  /// @return ShaderSyntaxError
  ShaderSyntaxError(const uint32_t id);
};

class ProgramLinkException : public Exception {
public:
  /// @brief ProgramLinkException's class constructor
  /// @param id The faulty program's OpenGL identifier
  /// @return ProgramLinkException
  ProgramLinkException(const uint32_t id);
};

class Program {
private:
  /// @brief Allows a variation of types for a uniform value
  typedef std::variant<std::monostate, float, double> UniformValue;

  /// @brief
  struct Uniform {
    std::string name;
    UniformValue value;
  };

  struct ActiveUniform {
  private:
    const int location;
    const uint32_t type;
    UniformValue _value;

  public:
    ActiveUniform(const int location, const uint32_t type) :
      location(location), type(type) {
    }

    void setValue(const UniformValue value) {
      _value = value;
    }
  };

  /// @brief The internal gl program identifier
  uint32_t _id;

  std::unordered_map<std::string, UniformValue> _uniforms;

  /// @brief The program's active uniforms
  std::unordered_map<std::string, ActiveUniform> _activeUniforms;

  /// @brief Compiles, attaches and destroys a shader to the program.
  /// @param type The type of shader we're compiling
  /// @param source The shader's source code
  /// @return void
  void compile(const GLenum type, const std::string &source) const;

public:
  /// @brief Allowed settings when creating a program
  struct Settings {
    const std::string vertex;
    const std::string fragment;
    const std::string geometry;
    const std::vector<Uniform> uniforms;
  };

  /// @brief Program constructor
  /// @param settings The program settings
  /// @return Program
  Program(const Settings settings = Settings());

  /// @brief Program destructor
  /// @return void
  ~Program();

  /// @brief Returns the shader identifier
  /// @return The shader identifier
  const uint32_t getId() const;

  /// @brief Binds the program for usage in the current rendering state
  /// @return void
  void use() const;

  /// @brief Destroys the program instance
  /// @return void
  void destroy();
};

} // namespace stem